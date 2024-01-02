

//
// world_chunk_x_x_x file layout

// -- Header

// name : type : description
//
// f1   : u32  : 'WHNK'
// f2   : u32  : version number
// f3   : u64  : 0xdeadbeef <-- Future home of a checksum
//
// f5   : u32  : voxel element count
// f6   : u32  : size of voxel element
//
// f7   : u64  : element count in each (VERT, COLO, NORM) array
// f8   : u32  : 'VERT' (vertex)  element size
// f9   : u32  : 'COLO' (colors)  element size
// f10  : u32  : 'NORM' (normals) element size
//
// f11  : u64  : elements in the SPOT array
// f12  : u32  : 'SPOT' (standing spots) element size

// -- Data
// -- Array lengths refer to values in the header found in the 'name' column

// type       : bytes  : description
//
// u32        : 4      : 'VOXD'
// voxel[f5]  : f5*f6  : voxel elements data
//
// u32        : 4      : 'VERT'
// vertex[f7] : f7*f8  : vertex elements data
//
// u32        : 4      : 'COLO'
// colors[f7] : f7*f9  : color elements data
//
// u32        : 4      : 'NORM'
// normls[f7] : f7*f10 : normal elements data
//
// // TODO(Jesse): Add the standing_spot computations
//

enum world_chunk_file_tag
{
  // v1
  WorldChunkFileTag_WHNK = 'KNHW', // world_chunk header

  WorldChunkFileTag_VOXD = 'DXOV', // Voxel data

  WorldChunkFileTag_VERT = 'TREV', // Vertex data
  WorldChunkFileTag_NORM = 'MRON', // Normal data

  WorldChunkFileTag_COLO = 'OLOC', // Color data @@ DEPRECATED @@

  // v2
  WorldChunkFileTag_SPOT = 'TOPS', // Standing spots

  // v3
  WorldChunkFileTag_MATL = 'LTAM', // Material data
  WorldChunkFileTag_END  = ' DNE', // Chunk book-end
};

struct world_chunk_file_header_v1
{
  u64 WHNK; // WorldChunkFileTag_WHNK
  u32 Version = 1;
  u64 Checksum;

  u32 VoxelElementCount;
  u32 VoxelElementSize;

  u64 MeshElementCount;

  u32 VertexElementSize;
  u32 ColorElementSize;
  u32 NormalElementSize;
};

#pragma pack(push, 1)
struct world_chunk_file_header_v2
{
  u32 WHNK; // WorldChunkFileTag_WHNK
  u32 Version = 2;
  u64 Checksum;

  u32 VoxelElementCount;
  u32 StandingSpotElementCount;

  u64 MeshElementCount;

  u8 VertexElementSize;
  u8 ColorElementSize;
  u8 NormalElementSize;
  u8 StandingSpotElementSize;

  u8 VoxelElementSize;
  u8 pad[3];
};

struct world_chunk_file_header_v3
{
  u32 WHNK; // WorldChunkFileTag_WHNK
  u32 Version = 3;
  u64 Checksum;

  s32 Px;
  s32 Py;
  s32 Pz;

  u32 VoxelElementCount;
  u32 StandingSpotElementCount;

  u64 MeshElementCount;

  u8 VertexElementSize;
  u8 NormalElementSize;
  u8 MaterialElementSize;
  u8 StandingSpotElementSize;

  u8 VoxelElementSize;
  u8 pad[3];
};
#pragma pack(pop)

typedef world_chunk_file_header_v3 world_chunk_file_header;

enum asset_load_state
{
  AssetLoadState_Unloaded,

  // On work queue
  AssetLoadState_Queued,

  AssetLoadState_Loaded,
  AssetLoadState_Error,
};

#define INVALID_ASSET_INDEX (u16_MAX)
struct asset_slot
{
  u16 Index;        // Physical slot in asset table
  u16 Generation;   // Monotonically increasing integer to identify the allocation of the asset slot in time
};

struct asset_id
{
  asset_slot Slot; poof(@no_serialize)
  file_traversal_node FileNode;
};

poof(maybe(asset_id))
#include <generated/maybe_asset_id.h>

link_internal asset_id
AssetId(file_traversal_node FileNode)
{
  asset_id Result = {};
  Result.FileNode = FileNode;
  return Result;
}

link_internal asset_id
AssetId(file_traversal_node *FileNode)
{
  asset_id Result = {};
  Result.FileNode = *FileNode;
  return Result;
}

struct asset
{
  volatile asset_load_state LoadState;

  asset_id Id;

  // At 120fps we get 9k hours worth of frames in a u32.. should be enough.
  // 9k hours == 385 days
  //
  // TODO(Jesse)(frame-index): Should this just be 32-bit?
  u64 LRUFrameIndex;

  model_buffer Models;
};


poof(buffer(asset))
#include <generated/buffer_asset.h>

typedef asset* asset_ptr;
poof(maybe(asset_ptr))
#include <generated/maybe_asset_ptr.h>

poof(maybe(asset_slot))
#include <generated/maybe_asset_slot.h>

poof(buffer(asset_slot))
#include <generated/buffer_asset_slot.h>

struct asset_file
{
  file_traversal_node FileNode;
  asset_slot_buffer AssetSlots;
};

link_internal counted_string
GetAssetFilenameFor(counted_string AssetPath, world_position WorldP, memory_arena *Memory)
{
  counted_string Result = FormatCountedString(Memory, CSz("%S/world_chunk_%d_%d_%d"), AssetPath, WorldP.x, WorldP.y, WorldP.z);
  return Result;
}

link_internal maybe_model_buffer
LoadVoxModels(memory_arena *PermMemory, heap_allocator *Heap, char const *filepath, memory_arena *TempMemory);

/* link_internal b32 Serialize(native_file *File, untextured_3d_geometry_buffer *Mesh); */
