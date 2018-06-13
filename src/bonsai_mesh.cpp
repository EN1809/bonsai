#ifndef BONSAI_MESH_CPP
#define BONSAI_MESH_CPP

#include <colors.h>

void
RenderGBuffer(untextured_3d_geometry_buffer *Target, graphics *Graphics);

inline void
BufferVertsDirect(
    untextured_2d_geometry_buffer *Dest,
    u32 NumVerts,
    v3 *Positions,
    v4 *Colors
  )
{
  /* TIMED_FUNCTION(); */
  if (BufferIsFull(Dest, NumVerts))
  {
    Assert(false);
    Error("Ran out of memory pushing %d Verts onto Mesh with %d/%d used", NumVerts, Dest->At, Dest->End-1);
    return;
  }

  memcpy( &Dest->Verts[Dest->At] , Positions, sizeof(*Positions)*NumVerts );
  memcpy( &Dest->Colors[Dest->At], Colors   , sizeof(*Colors)*NumVerts );
  Dest->At += NumVerts;

  return;
}

inline void
BufferVertsDirect(
    untextured_3d_geometry_buffer *Dest,

    u32 NumVerts,

    v3 *Positions,
    v3 *Normals,
    v4 *Colors
  )
{
  /* TIMED_FUNCTION(); */
  if (BufferIsFull(Dest, NumVerts))
  {
    Assert(false);
    Error("Ran out of memory pushing %d Verts onto Mesh with %d/%d used", NumVerts, Dest->At, Dest->End -1);
    return;
  }

  memcpy( &Dest->Verts[Dest->At]  , Positions, sizeof(*Positions)*NumVerts );
  memcpy( &Dest->Normals[Dest->At], Normals,   sizeof(*Normals)*NumVerts );
  memcpy( &Dest->Colors[Dest->At] , Colors   , sizeof(*Colors)*NumVerts );

  Dest->At += NumVerts;
}

inline void
BufferVertsDirect(
    untextured_3d_geometry_buffer *Dest,

    u32 NumVerts,

    v3 *VertsPositions,
    v3 *Normals,
    v4 *VertColors,

    v3 Offset,
    v3 Scale
  )
{
  /* TIMED_FUNCTION(); */
  if (BufferIsFull(Dest, NumVerts))
  {
    Assert(false);
    Error("Ran out of memory pushing %d Verts onto Mesh with %d/%d used", NumVerts, Dest->At, Dest->End-1);
    return;
  }

#if 1
  __m128 mmScale = _mm_set_ps(0, Scale.z, Scale.y, Scale.x);
  __m128 mmOffset = _mm_set_ps(0, Offset.z, Offset.y, Offset.x);

  Assert(NumVerts % 3 == 0);

  memcpy( &Dest->Normals[Dest->At],  Normals,    sizeof(*Normals)*NumVerts );
  memcpy( &Dest->Colors[Dest->At],   VertColors, sizeof(*VertColors)*NumVerts );


  for ( u32 VertIndex = 0;
        VertIndex < NumVerts;
        VertIndex += 3 )
  {
    v3 VertSrc0 = VertsPositions[VertIndex + 0];
    v3 VertSrc1 = VertsPositions[VertIndex + 1];
    v3 VertSrc2 = VertsPositions[VertIndex + 2];

    f32_reg Vert0;
    f32_reg Vert1;
    f32_reg Vert2;

    Vert0.Sse = _mm_set_ps(0, VertSrc0.z, VertSrc0.y, VertSrc0.x);
    Vert1.Sse = _mm_set_ps(0, VertSrc1.z, VertSrc1.y, VertSrc1.x);
    Vert2.Sse = _mm_set_ps(0, VertSrc2.z, VertSrc2.y, VertSrc2.x);

    Vert0.Sse = _mm_add_ps( _mm_mul_ps(Vert0.Sse, mmScale), mmOffset);
    Vert1.Sse = _mm_add_ps( _mm_mul_ps(Vert1.Sse, mmScale), mmOffset);
    Vert2.Sse = _mm_add_ps( _mm_mul_ps(Vert2.Sse, mmScale), mmOffset);

    v3 Result0 = {{ Vert0.F[0], Vert0.F[1], Vert0.F[2] }};
    v3 Result1 = {{ Vert1.F[0], Vert1.F[1], Vert1.F[2] }};
    v3 Result2 = {{ Vert2.F[0], Vert2.F[1], Vert2.F[2] }};

    Dest->Verts[Dest->At + 0] = Result0;
    Dest->Verts[Dest->At + 1] = Result1;
    Dest->Verts[Dest->At + 2] = Result2;

    Dest->At += 3;
  }

#else

  // Left this here for futrue benchmarking.  The memcpy path is fastest by ~2x
#if 1
  for ( u32 VertIndex = 0;
        VertIndex < NumVerts;
        ++VertIndex )
  {
    Dest->Verts[Dest->At] = VertsPositions[VertIndex]*Scale + Offset;
    Dest->Normals[Dest->At] = Normals[VertIndex];
    Dest->Colors[Dest->At] = VertColors[VertIndex];
    ++Dest->At;
  }
#else
  s32 sizeofData = NumVerts * sizeof(v3);
  memcpy( &Dest->Verts[Dest->At]  , Positions, sizeof(*Positions)*NumVerts );
  memcpy( &Dest->Normals[Dest->At], Normals,   sizeof(*Normals)*NumVerts );
  memcpy( &Dest->Colors[Dest->At] , Colors   , sizeof(*Colors)*NumVerts );
  Dest->At += NumVerts;
#endif


#endif


  return;
}

#if 1
inline void
BufferVertsChecked(
    untextured_3d_geometry_buffer *Target,
    graphics *Graphics,

    u32 NumVerts,

    v3* Positions,
    v3* Normals,
    v4* Colors,

    v3 Offset = V3(0),
    v3 Scale = V3(1)
  )
{
  /* TIMED_FUNCTION(); */

  if (BufferIsFull(Target, NumVerts))
  {
    u32 VertsRemaining = Target->End - Target->At;
    u32 Pad = VertsRemaining % 3;
    u32 PushVerts = VertsRemaining - Pad;
    BufferVertsChecked( Target, Graphics, PushVerts, Positions, Normals, Colors, Offset, Scale);

    Positions += PushVerts;
    Normals += PushVerts;
    Colors += PushVerts;

    RenderGBuffer(Target, Graphics);

    BufferVertsChecked(Target, Graphics, NumVerts-PushVerts, Positions, Normals, Colors, Offset, Scale);
  }
  else
  {
    BufferVertsDirect( Target, NumVerts, Positions, Normals, Colors, Offset, Scale);
  }

  return;
}
#endif

inline void
BufferVerts(
    untextured_3d_geometry_buffer *Source,
    untextured_3d_geometry_buffer *Dest,
    graphics *Graphics
  )
{
  /* TIMED_FUNCTION(); */

#if 1
  BufferVertsChecked(Dest, Graphics, Source->At, Source->Verts,
      Source->Normals, Source->Colors);
  return;
#else
  for ( s32 VertIndex = 0;
        VertIndex < Source->At;
        ++VertIndex )
  {
    v3 XYZ = (Source->VertexData[VertIndex]*Scale) + RenderOffset;

#if 1
    Dest->VertexData[Dest->At] =  XYZ;
    Dest->NormalData[Dest->At] = Source->NormalData[VertIndex];
    Dest->ColorData[Dest->At]  = Source->ColorData[VertIndex];
    ++Dest->At;
#else

    BufferVerts(Dest, gBuffer, SG, Camera,
        1,
        &XYZ,
        Source->NormalData + VertIndex,
        Source->ColorData + VertIndex);
#endif

  }
#endif

}

void
BuildEntityMesh(chunk_data *chunk, chunk_dimension Dim)
{
  for ( int z = 0; z < Dim.z ; ++z )
  {
    for ( int y = 0; y < Dim.y ; ++y )
    {
      for ( int x = 0; x < Dim.x ; ++x )
      {
        voxel_position LocalVoxelP = Voxel_Position(x,y,z);

        if ( NotFilled( chunk, LocalVoxelP, Dim) )
          continue;

        voxel_position P = Voxel_Position(x,y,z);

        voxel *Voxel = &chunk->Voxels[GetIndex(P, Dim)];

        v3 VP = V3(P);
        v3 Diameter = V3(1.0f);
        v3 VertexData[6];

        v4 FaceColors[FACE_VERT_COUNT];
        FillColorArray(Voxel->Color, FaceColors, FACE_VERT_COUNT);


        voxel_position rightVoxel = LocalVoxelP + Voxel_Position(1, 0, 0);
        voxel_position leftVoxel = LocalVoxelP - Voxel_Position(1, 0, 0);

        voxel_position topVoxel = LocalVoxelP + Voxel_Position(0, 0, 1);
        voxel_position botVoxel = LocalVoxelP - Voxel_Position(0, 0, 1);

        voxel_position frontVoxel = LocalVoxelP + Voxel_Position(0, 1, 0);
        voxel_position backVoxel = LocalVoxelP - Voxel_Position(0, 1, 0);



        // FIXME(Jesse): This should use a BufferVertsChecked path
        if ( (!IsInsideDim(Dim, rightVoxel)) || NotFilled( chunk, rightVoxel, Dim))
        {
          RightFaceVertexData( VP, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, RightFaceNormalData, FaceColors);
        }
        if ( (!IsInsideDim( Dim, leftVoxel  )) || NotFilled( chunk, leftVoxel, Dim))
        {
          LeftFaceVertexData( VP, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, LeftFaceNormalData, FaceColors);
        }
        if ( (!IsInsideDim( Dim, botVoxel   )) || NotFilled( chunk, botVoxel, Dim))
        {
          BottomFaceVertexData( VP, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, BottomFaceNormalData, FaceColors);
        }
        if ( (!IsInsideDim( Dim, topVoxel   )) || NotFilled( chunk, topVoxel, Dim))
        {
          TopFaceVertexData( VP, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, TopFaceNormalData, FaceColors);
        }
        if ( (!IsInsideDim( Dim, frontVoxel )) || NotFilled( chunk, frontVoxel, Dim))
        {
          FrontFaceVertexData( VP, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, FrontFaceNormalData, FaceColors);
        }
        if ( (!IsInsideDim( Dim, backVoxel  )) || NotFilled( chunk, backVoxel, Dim))
        {
          BackFaceVertexData( VP, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, BackFaceNormalData, FaceColors);
        }

      }
    }
  }
}

void
BuildWorldChunkMesh(world_chunk *ReadChunk, chunk_dimension ReadChunkDim, world_chunk *WriteChunk, chunk_dimension WriteChunkDim)
{
  /* TIMED_FUNCTION(); */

  chunk_data *WriteChunkData = WriteChunk->Data;
  chunk_data *ReadChunkData = ReadChunk->Data;

  Assert(IsSet(ReadChunk, Chunk_Initialized));
  Assert(IsSet(WriteChunk, Chunk_Initialized));

  Assert(NotSet(WriteChunkData, Chunk_Queued));
  Assert(NotSet(ReadChunkData, Chunk_Queued));

  voxel_position rightVoxel;
  voxel_position leftVoxel;
  voxel_position topVoxel;
  voxel_position botVoxel;
  voxel_position frontVoxel;
  voxel_position backVoxel;

  s32 rightVoxelReadIndex;
  s32 leftVoxelReadIndex;
  s32 topVoxelReadIndex;
  s32 botVoxelReadIndex;
  s32 frontVoxelReadIndex;
  s32 backVoxelReadIndex;

  random_series ColorEntropy = {33453};

  for ( int z = 0; z < WriteChunkDim.z ; ++z )
  {
    for ( int y = 0; y < WriteChunkDim.y ; ++y )
    {
      for ( int x = 0; x < WriteChunkDim.x ; ++x )
      {
        voxel_position CurrentP  = Voxel_Position(x,y,z);

        v4 Perturb = 0.08f*V4(RandomBilateral(&ColorEntropy),
                              RandomBilateral(&ColorEntropy),
                              RandomBilateral(&ColorEntropy),
                              1.0f);

        if ( NotFilledInChunk( WriteChunkData, CurrentP, WriteChunkDim ) )
          continue;

        v3 Diameter = V3(1.0f);
        v3 VertexData[FACE_VERT_COUNT];
        v4 FaceColors[FACE_VERT_COUNT];

        voxel *Voxel = &WriteChunkData->Voxels[GetIndex(CurrentP, WriteChunkDim)];
        FillColorArray(Voxel->Color, FaceColors, FACE_VERT_COUNT);

#if 0
        for (u32 ColorIndex = 0;
            ColorIndex < FACE_VERT_COUNT;
            ++ColorIndex)
        {
          FaceColors[ColorIndex] += Perturb*FaceColors[0];
        }
#endif

        rightVoxel = CurrentP + Voxel_Position(1, 0, 0);
        rightVoxelReadIndex = GetIndex(rightVoxel+1, ReadChunkDim);

        leftVoxel  = CurrentP - Voxel_Position(1, 0, 0);
        leftVoxelReadIndex  = GetIndex(leftVoxel+1, ReadChunkDim);

        topVoxel   = CurrentP + Voxel_Position(0, 0, 1);
        topVoxelReadIndex   = GetIndex(topVoxel+1, ReadChunkDim);

        botVoxel   = CurrentP - Voxel_Position(0, 0, 1);
        botVoxelReadIndex   = GetIndex(botVoxel+1, ReadChunkDim);

        frontVoxel = CurrentP + Voxel_Position(0, 1, 0);
        frontVoxelReadIndex = GetIndex(frontVoxel+1, ReadChunkDim);

        backVoxel  = CurrentP - Voxel_Position(0, 1, 0);
        backVoxelReadIndex  = GetIndex(backVoxel+1, ReadChunkDim);

        // FIXME(Jesse): This should use a BufferVertsChecked path
        if ( NotFilledInChunk( ReadChunkData, rightVoxelReadIndex) )
        {
          RightFaceVertexData( V3(CurrentP), Diameter, VertexData);
          BufferVertsDirect(&WriteChunkData->Mesh, 6, VertexData, RightFaceNormalData, FaceColors);
        }
        if ( NotFilledInChunk( ReadChunkData, leftVoxelReadIndex) )
        {
          LeftFaceVertexData( V3(CurrentP), Diameter, VertexData);
          BufferVertsDirect(&WriteChunkData->Mesh, 6, VertexData, LeftFaceNormalData, FaceColors);
        }
        if ( NotFilledInChunk( ReadChunkData, botVoxelReadIndex) )
        {
          BottomFaceVertexData( V3(CurrentP), Diameter, VertexData);
          BufferVertsDirect(&WriteChunkData->Mesh, 6, VertexData, BottomFaceNormalData, FaceColors);
        }
        if ( NotFilledInChunk( ReadChunkData, topVoxelReadIndex) )
        {
          TopFaceVertexData( V3(CurrentP), Diameter, VertexData);
          BufferVertsDirect(&WriteChunkData->Mesh, 6, VertexData, TopFaceNormalData, FaceColors);
        }
        if ( NotFilledInChunk( ReadChunkData, frontVoxelReadIndex) )
        {
          FrontFaceVertexData( V3(CurrentP), Diameter, VertexData);
          BufferVertsDirect(&WriteChunkData->Mesh, 6, VertexData, FrontFaceNormalData, FaceColors);
        }
        if ( NotFilledInChunk( ReadChunkData, backVoxelReadIndex) )
        {
          BackFaceVertexData( V3(CurrentP), Diameter, VertexData);
          BufferVertsDirect(&WriteChunkData->Mesh, 6, VertexData, BackFaceNormalData, FaceColors);
        }
      }
    }
  }
}

void
BuildWorldChunkMesh(world *World, world_chunk *WorldChunk, chunk_dimension WorldChunkDim)
{
  TIMED_FUNCTION();

  chunk_data *chunk = WorldChunk->Data;

  Assert(IsSet(chunk, Chunk_Initialized));

  Assert(NotSet(chunk, Chunk_Queued));

  canonical_position rightVoxel;
  canonical_position leftVoxel;
  canonical_position topVoxel;
  canonical_position botVoxel;
  canonical_position frontVoxel;
  canonical_position backVoxel;

  random_series ColorEntropy = {33453};

  for ( int z = 0; z < WorldChunkDim.z ; ++z )
  {
    for ( int y = 0; y < WorldChunkDim.y ; ++y )
    {
      for ( int x = 0; x < WorldChunkDim.x ; ++x )
      {
        canonical_position CurrentP  = Canonical_Position(WorldChunkDim, V3(x,y,z), WorldChunk->WorldP);

        v4 Perturb = 0.08f*V4(RandomBilateral(&ColorEntropy),
                              RandomBilateral(&ColorEntropy),
                              RandomBilateral(&ColorEntropy),
                              1.0f);

        if ( !IsFilledInWorld( World, WorldChunk, CurrentP ) )
          continue;

        voxel *Voxel = &chunk->Voxels[GetIndex(CurrentP.Offset, WorldChunkDim)];

        v3 Diameter = V3(1.0f);
        v3 VertexData[FACE_VERT_COUNT];
        v4 FaceColors[FACE_VERT_COUNT];
        FillColorArray(Voxel->Color, FaceColors, FACE_VERT_COUNT);


        for (u32 ColorIndex = 0;
            ColorIndex < FACE_VERT_COUNT;
            ++ColorIndex)
        {
          FaceColors[ColorIndex] += Perturb*FaceColors[0];
        }

        TIMED_BLOCK("Canonicalize");
          rightVoxel = Canonicalize(WorldChunkDim, CurrentP + V3(1, 0, 0));
          leftVoxel  = Canonicalize(WorldChunkDim, CurrentP - V3(1, 0, 0));
          topVoxel   = Canonicalize(WorldChunkDim, CurrentP + V3(0, 0, 1));
          botVoxel   = Canonicalize(WorldChunkDim, CurrentP - V3(0, 0, 1));
          frontVoxel = Canonicalize(WorldChunkDim, CurrentP + V3(0, 1, 0));
          backVoxel  = Canonicalize(WorldChunkDim, CurrentP - V3(0, 1, 0));
        END_BLOCK("Canonicalize");

        // FIXME(Jesse): This should use a BufferVertsChecked path
        if ( !IsFilledInWorld( World, WorldChunk, rightVoxel ) )
        {
          RightFaceVertexData( CurrentP.Offset, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, RightFaceNormalData, FaceColors);
        }
        if ( !IsFilledInWorld( World, WorldChunk, leftVoxel ) )
        {
          LeftFaceVertexData( CurrentP.Offset, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, LeftFaceNormalData, FaceColors);
        }
        if ( !IsFilledInWorld( World, WorldChunk, botVoxel   ) )
        {
          BottomFaceVertexData( CurrentP.Offset, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, BottomFaceNormalData, FaceColors);
        }
        if ( !IsFilledInWorld( World, WorldChunk, topVoxel   ) )
        {
          TopFaceVertexData( CurrentP.Offset, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, TopFaceNormalData, FaceColors);
        }
        if ( !IsFilledInWorld( World, WorldChunk, frontVoxel ) )
        {
          FrontFaceVertexData( CurrentP.Offset, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, FrontFaceNormalData, FaceColors);
        }
        if ( !IsFilledInWorld( World, WorldChunk, backVoxel  ) )
        {
          BackFaceVertexData( CurrentP.Offset, Diameter, VertexData);
          BufferVertsDirect(&chunk->Mesh, 6, VertexData, BackFaceNormalData, FaceColors);
        }
      }
    }
  }
}




#endif
