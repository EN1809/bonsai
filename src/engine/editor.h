struct level_editor
{
  /* level_edit_mode Mode; */

  interactable SelectedColorSquare;
  s32 SelectedColorIndex;

  u32 SelectionClicks;

  rect3 SelectionRegion;
  rect3 CopyRegion;

  // Recorded when shift-clicking on the selection to manipulate it
  face_index SelectionShiftClickedFace;
  v3 SelectionShiftClickedP[2];
};

link_internal b32
SelectionIncomplete(u32 SelectionClicks)
{
  return SelectionClicks == 0 || SelectionClicks == 1;
}

struct maybe_v3
{
  maybe_tag Tag;
  v3 V3;
};


enum selection_mode
{
  SelectionMode_Noop,

  SelectionMode_Resize,
  SelectionMode_Translate,
};

enum world_edit_mode
{
  WorldEditMode_Select          = (1 << 0),
  WorldEditMode_FillSelection   = (1 << 1),
  WorldEditMode_DeleteSelection = (1 << 2),

  WorldEditMode_AddSingle       = (1 << 3),
  WorldEditMode_RemoveSingle    = (1 << 4),
  WorldEditMode_PaintSingle     = (1 << 5),
};

poof(string_and_value_tables(world_edit_mode))
#include <generated/string_and_value_tables_world_edit_mode.h>

poof(radio_button_group_for_bitfield_enum(world_edit_mode));
#include <generated/radio_button_group_for_bitfield_enum_world_edit_mode.h>

link_internal world_chunk_ptr_buffer
GatherChunksOverlappingArea(world *World, aabb Region, memory_arena *Memory)
{
  auto MinP = Canonicalize(World->ChunkDim, GetMin(Region), {});
  auto MaxP = Canonicalize(World->ChunkDim, GetMax(Region), {});

  world_position Delta = MaxP.WorldP - MinP.WorldP + 1;
  u32 TotalChunkCount = Abs(Volume(Delta));

  world_chunk_ptr_buffer Result = {};

  // NOTE(Jesse): These need to be aligned to the cache line size, so don't use the constructor fn
  Result.Start = AllocateAligned(world_chunk*, Memory, TotalChunkCount, CACHE_LINE_SIZE);
  Result.Count = TotalChunkCount;

  u32 ChunkIndex = 0;
  for (s32 zChunk = MinP.WorldP.z; zChunk <= MaxP.WorldP.z; ++zChunk)
  {
    for (s32 yChunk = MinP.WorldP.y; yChunk <= MaxP.WorldP.y; ++yChunk)
    {
      for (s32 xChunk = MinP.WorldP.x; xChunk <= MaxP.WorldP.x; ++xChunk)
      {
        world_position ChunkP = World_Position(xChunk, yChunk, zChunk);
        world_chunk *Chunk = GetWorldChunkFromHashtable(World, ChunkP);
        if (Chunk)
        {
          Assert(ChunkIndex < TotalChunkCount);
          Result.Start[ChunkIndex++] = Chunk;
        }
      }
    }
  }
  return Result;
}

link_internal void
GatherVoxelsOverlappingArea(world *World, rect3i AABB, world_chunk_ptr_buffer *ChunkBuffer, voxel *Voxels, s32 VoxelCount)
{
  Assert(Volume(AABB) == VoxelCount);

  v3i QueryDim = GetDim(AABB);
  v3i SimSpaceQueryDim = QueryDim;

  s32 TotalVoxels_signed = Volume(AABB);
  Assert(TotalVoxels_signed > 0);

  u32 TotalVoxels = (u32)TotalVoxels_signed;

  // TODO(Jesse): Put this behind a debug/internal flag ?
  voxel UnsetVoxel = { 0xff, 0xff, 0xff };
  for (u32 VoxelIndex = 0; VoxelIndex < TotalVoxels; ++VoxelIndex) { Voxels[VoxelIndex] = UnsetVoxel; }

  v3i SimSpaceQueryMinP = AABB.Min;

  for (u32 ChunkIndex = 0; ChunkIndex < ChunkBuffer->Count; ++ChunkIndex)
  {
    world_chunk *Chunk = ChunkBuffer->Start[ChunkIndex];
    auto SimSpaceChunkRect = GetSimSpaceAABBi(World, Chunk);
    auto SimSpaceIntersectionRect = Union(&SimSpaceChunkRect, &AABB);

    auto SimSpaceIntersectionMin = SimSpaceIntersectionRect.Min;
    auto SimSpaceIntersectionMax = SimSpaceIntersectionRect.Max;

    auto SimSpaceChunkMin = SimSpaceChunkRect.Min;
    auto SimSpaceChunkMax = SimSpaceChunkRect.Max;

    auto ChunkRelRectMin = SimSpaceIntersectionMin - SimSpaceChunkMin;
    auto ChunkRelRectMax = SimSpaceIntersectionMax - SimSpaceChunkMin;

    for (s32 zVoxel = s32(ChunkRelRectMin.z); zVoxel < s32(ChunkRelRectMax.z); zVoxel += 1)
    {
      for (s32 yVoxel = s32(ChunkRelRectMin.y); yVoxel < s32(ChunkRelRectMax.y); yVoxel += 1)
      {
        for (s32 xVoxel = s32(ChunkRelRectMin.x); xVoxel < s32(ChunkRelRectMax.x); xVoxel += 1)
        {
          voxel_position RelVoxP = Voxel_Position(s32(xVoxel), s32(yVoxel), s32(zVoxel));
          voxel *V = GetVoxel(Chunk, RelVoxP);
          Assert( (V->Flags & Voxel_MarkBit) == 0);

          v3i SimSpaceVoxPExact = V3i(xVoxel, yVoxel, zVoxel) + SimSpaceChunkMin;

          Assert(SimSpaceQueryMinP <= SimSpaceVoxPExact);
          u32 Index = MapIntoQueryBox(SimSpaceVoxPExact, SimSpaceQueryMinP, QueryDim);
          Assert(Index < TotalVoxels);
          Assert(Voxels[Index] == UnsetVoxel);
          Voxels[Index] = *V;
        }
      }
    }
  }
}

