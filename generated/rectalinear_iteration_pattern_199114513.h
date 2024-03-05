// src/engine/world_chunk.cpp:4260:0

DimIterator(x, y, z, SimSpaceQueryDim)
{
  v3i SimRelVoxP = V3i(x,y,z);
  v3i SimVoxP = SimRelVoxP + SimSpaceQueryAABB.Min;
  V = CopiedVoxels + GetIndex(SimRelVoxP, SimSpaceQueryDim);

  
              v3i CenterToVoxP = SimVoxP - SimSphereP;
              if (LengthSq(CenterToVoxP) < RadiusSquared) { V->Flags = Voxel_Filled; }
            
}


