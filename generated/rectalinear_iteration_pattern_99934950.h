// src/engine/world_chunk.cpp:4349:0

DimIterator(x, y, z, SimSpaceQueryDim)
{
  v3i SimRelVoxP = V3i(x,y,z);
  v3i SimVoxP = SimRelVoxP + SimSpaceQueryAABB.Min;
  V = CopiedVoxels + GetIndex(SimRelVoxP, SimSpaceQueryDim);

  
              if (Contains(SSRect, SimVoxP)) { if (V->Flags & Voxel_Filled) { V->Color = NewColor; } }
            
}


