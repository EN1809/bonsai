#include <bonsai_engine.h>
#include <unix_platform.cpp>
global_variable memory_arena *TranArena = PlatformAllocateArena();
#include <bonsai_engine.cpp>
#include <bonsai_asset_loaders.cpp>

#define RANDOM_HOTKEY_MASHING 0
#if RANDOM_HOTKEY_MASHING
static u32 HotkeyFrameTimeout = 0;
static random_series HotkeyEntropy = {};
static hotkeys StashedHotkeys = {};
#endif


void
SimulatePlayers(game_state *GameState, entity* LocalPlayer, hotkeys *Hotkeys, r32 dt)
{
  for (u32 PlayerIndex = 0;
      PlayerIndex < MAX_CLIENTS;
      ++PlayerIndex)
  {
    entity *Entity = GameState->Player;
    if (LocalPlayer == Entity)
    {
      SimulatePlayer(GameState, Entity, Hotkeys, dt );
    }
    else
    {
      SimulatePlayer(GameState, Entity, 0, dt );
    }

  }
}

model *
AllocateGameModels(game_state *GameState, memory_arena *Memory)
{
  model *Result = Allocate(model, GameState->Memory, ModelIndex_Count);

  Result[ModelIndex_Enemy] = LoadVoxModel(Memory, &GameState->Heap, ENEMY_MODEL);
  Result[ModelIndex_Player] = LoadCollada(Memory, &GameState->Heap, "models/two-axis-animated-cube.dae");
  /* Result[ModelIndex_Player] = LoadVoxModel(Memory, PLAYER_MODEL); */
  Result[ModelIndex_Loot] = LoadVoxModel(Memory, &GameState->Heap, LOOT_MODEL);

  /* chunk_dimension ProjectileDim = Chunk_Dimension(1,30,1); */
  /* Result[ModelIndex_Projectile].Chunk = AllocateChunk(Memory, &GameState->Heap, ProjectileDim); */
  /* Result[ModelIndex_Projectile].Dim = ProjectileDim; */
  /* FillChunk(Result[ModelIndex_Projectile].Chunk, ProjectileDim, GREEN); */

  Result[ModelIndex_Proton] = LoadVoxModel(Memory, &GameState->Heap, PROJECTILE_MODEL);

  return Result;
}

BONSAI_API_WORKER_THREAD_CALLBACK()
{
  switch (Entry->Type)
  {
    case WorkEntryType_InitWorldChunk:
    {
      world_chunk* DestChunk = (world_chunk*)Entry->Input;
      if (!ChunkIsGarbage(DestChunk))
      {
        s32 Amplititude = 100;
        s32 StartingZDepth = -100;
        InitializeWorldChunkPerlinPlane(Thread,
                                        DestChunk,
                                        Amplititude, StartingZDepth);

        /* Assert(DestChunk->CurrentTriangles->SurfacePoints->Count == 0); */
        /* GetBoundingVoxels(DestChunk, DestChunk->CurrentTriangles->SurfacePoints); */

        /* Triangulate(DestChunk->LodMesh, DestChunk, WORLD_CHUNK_DIM, Thread->TempMemory); */
        /* Triangulate(DestChunk->LodMesh, DestChunk->CurrentTriangles, DestChunk, Thread->TempMemory); */
      }
    } break;

    case WorkEntryType_CopyBuffer:
    {
      untextured_3d_geometry_buffer* Src = Entry->GpuCopyParams.Src;
      untextured_3d_geometry_buffer* Dest = &Entry->GpuCopyParams.Dest;
      Assert(Src->At <= Dest->End);

      v3 Basis = Entry->GpuCopyParams.Basis;
      BufferVertsChecked(Src, Dest, Basis, V3(1.0f));
    } break;

    InvalidDefaultCase;
  }

  return;
}

BONSAI_API_MAIN_THREAD_CALLBACK()
{
  TIMED_FUNCTION();

  glDisable(GL_CULL_FACE);

#if BONSAI_INTERNAL
  if (!GetDebugState)
  {
    GetDebugState = GameState->GetDebugState;
  }
#endif

  world                 *World         = GameState->World;
  chunk_dimension        WorldChunkDim = World->ChunkDim;
  graphics              *Graphics      = GameState->Graphics;
  g_buffer_render_group *gBuffer       = Graphics->gBuffer;
  ao_render_group       *AoGroup       = Graphics->AoGroup;
  camera                *Camera        = Graphics->Camera;

  GameState->GpuBufferWriteIndex = (GameState->GpuBufferWriteIndex + 1) % 2;
  gpu_mapped_element_buffer* GpuMap = GameState->GpuBuffers + GameState->GpuBufferWriteIndex;

  MapGpuElementBuffer(GpuMap);

  entity *Player = GameState->Player;
  ClearFramebuffers(Graphics);

#if RANDOM_HOTKEY_MASHING
  if (HotkeyFrameTimeout == 0)
  {
    Hotkeys->Left = RandomChoice(&HotkeyEntropy);
    Hotkeys->Right = RandomChoice(&HotkeyEntropy);
    Hotkeys->Forward = RandomChoice(&HotkeyEntropy);
    Hotkeys->Backward = RandomChoice(&HotkeyEntropy);
    StashedHotkeys = *Hotkeys;
    HotkeyFrameTimeout = 100;
  }
  else
  {
    HotkeyFrameTimeout--;
    *Hotkeys = StashedHotkeys;
  }
#endif


#if DEBUG_DRAW_WORLD_AXIES
  DEBUG_DrawLine(&World->Mesh, Graphics, V3(0,0,0), V3(10000, 0, 0), RED, 0.5f );
  DEBUG_DrawLine(&World->Mesh, Graphics, V3(0,0,0), V3(0, 10000, 0), GREEN, 0.5f );
  DEBUG_DrawLine(&World->Mesh, Graphics, V3(0,0,0), V3(0, 0, 10000), BLUE, 0.5f );
#endif

  if (Hotkeys->Player_Spawn)
  {
    Unspawn(Player);
    world_position PlayerChunkP = World_Position(0, 0, -2);
    SpawnPlayer(GameState, Player,  Canonical_Position(V3(0,0,2), World_Position(0,0,0))  );
    World->Center = PlayerChunkP;
  }

  SimulatePlayers(GameState, Player, Hotkeys, Plat->dt);

  CollectUnusedChunks(World, &GameState->MeshFreelist, GameState->Memory);

  v2 MouseDelta = GetMouseDelta(Plat);
  input* GameInput = &Plat->Input;

#if BONSAI_INTERNAL
  if (GetDebugState()->UiGroup.PressedInteraction.ID != StringHash("GameViewport"))
  {
    GameInput = 0;
  }
#endif

  UpdateGameCamera(MouseDelta, GameInput, Player->P, Camera);

  SimulateEntities(GameState, Plat->dt);

  SimulateAndRenderParticleSystems(GameState->EntityTable, &GpuMap->Buffer, Graphics, Plat->dt);

  gBuffer->ViewProjection =
    ProjectionMatrix(Camera, Plat->WindowWidth, Plat->WindowHeight) *
    ViewMatrix(WorldChunkDim, Camera);

  DEBUG_COMPUTE_PICK_RAY(Plat, &gBuffer->ViewProjection, Hotkeys);

  TIMED_BLOCK("BufferMeshes");
    BufferWorld(GameState, &GpuMap->Buffer, World, Graphics, VISIBLE_REGION_RADIUS, Hotkeys);
    BufferEntities( GameState->EntityTable, &GpuMap->Buffer, Graphics, World, Plat->dt);
  END_BLOCK("BufferMeshes");

#if BONSAI_INTERNAL
  for (u32 ChunkIndex = 0;
      ChunkIndex < GetDebugState()->PickedChunkCount;
      ++ChunkIndex)
  {
    world_chunk *Chunk = GetDebugState()->PickedChunks[ChunkIndex];
    untextured_3d_geometry_buffer CopyDest = ReserveBufferSpace(&GpuMap->Buffer, VERTS_PER_AABB);
    u8 Color = GREEN;

    if (Chunk == GetDebugState()->HotChunk)
    {
      Color = PINK;
    }

    DEBUG_DrawChunkAABB(&CopyDest, Graphics, Chunk, WORLD_CHUNK_DIM, Color, 0.35f);
  }
#endif

  TIMED_BLOCK("Wait for worker threads");
    for (;;) { if (QueueIsEmpty(&Plat->HighPriority)) { break; } }
  END_BLOCK("Wait for worker threads");

  TIMED_BLOCK("RenderToScreen");
    RenderGBuffer(GpuMap, Graphics);
    RenderAoTexture(AoGroup);
    DrawGBufferToFullscreenQuad(Plat, Graphics);
  END_BLOCK("RenderToScreen");

  Graphics->Lights->Count = 0;

  return;
}

BONSAI_API_MAIN_THREAD_INIT_CALLBACK()
{
  Info("Initializing Game");

  Init_Global_QuadVertexBuffer();

#if BONSAI_INTERNAL
  GetDebugState = GetDebugState_in;
#endif

  game_state *GameState = Allocate(game_state, GameMemory, 1);

#if BONSAI_INTERNAL
  Assert(GetDebugState_in);
  GameState->GetDebugState = GetDebugState_in;
#endif

  GameState->Memory = GameMemory;
  GameState->Noise = perlin_noise(DEBUG_NOISE_SEED);

  GameState->Graphics = GraphicsInit(GameMemory);
  if (!GameState->Graphics) { Error("Initializing Graphics"); return False; }

  StandardCamera(GameState->Graphics->Camera, 10000.0f, 300.0f);

  GameState->Plat = Plat;
  GameState->Entropy.Seed = DEBUG_NOISE_SEED;

  world_position WorldCenter = World_Position(0, 0, 0);

  GameState->Heap = InitHeap(Gigabytes(4));
  GameState->World = AllocateAndInitWorld(GameState, WorldCenter, WORLD_CHUNK_DIM, VISIBLE_REGION);

  AllocateEntityTable(GameState);

  GameState->Models = AllocateGameModels(GameState, GameState->Memory);

  GameState->Player = GetFreeEntity(GameState);
  SpawnPlayer(GameState, GameState->Player, Canonical_Position(Voxel_Position(0), WorldCenter));

  AllocateGpuElementBuffer(GameState->GpuBuffers + 0, (u32)Megabytes(4));
  AllocateGpuElementBuffer(GameState->GpuBuffers + 1, (u32)Megabytes(4));

  return GameState;
}

BONSAI_API_WORKER_THREAD_INIT_CALLBACK()
{
  Thread->MeshFreelist = &GameState->MeshFreelist;
  Thread->Noise = &GameState->Noise;
}