// src/engine/world_chunk.cpp:4400:0

DimIterator(x, y, z, UpdateDim)
{
  b32 OverwriteVoxel = False;

  v3i VoxP = V3i(x,y,z);
  v3i SimVoxP = VoxP + SimSpaceUpdateBounds.Min;
  voxel *V = CopiedChunk->Voxels + GetIndex(VoxP, UpdateDim);

  

        v3i OriginToCurrentVoxP = SimVoxP - SimOrigin;
        voxel *NewVoxelValue = TryGetVoxel(Data, OriginToCurrentVoxP);

        if ((V->Flags&Voxel_Filled)==False && Contains(SSRect, SimVoxP))
        {
          b32 IsUnfilledBorder = False;
          poof_check_for_unfilled_border()
          if (IsUnfilledBorder)
          {
            *V = *NewVoxelValue;
            V->Flags = voxel_flag(V->Flags&~VoxelFaceMask); // Knock out face flags so the algorithm doesn't "self-apply"
          }
        }
      

  if ( ((OverwriteVoxel == True)  && (Invert == False)) ||
    ((OverwriteVoxel == False) && (Invert == True))  )
  {
    *V = *NewVoxelValue;
  }
}


