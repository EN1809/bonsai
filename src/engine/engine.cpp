#if PLATFORM_GL_IMPLEMENTATIONS
#include <engine/debug_draw.cpp>
#endif

#include <engine/game_api.cpp>
#include <engine/asset.cpp>
#include <engine/canonical_position.cpp>
#include <engine/chunk.cpp>
#include <engine/threadsafe.cpp>
#include <engine/mesh.cpp>
#include <engine/work_queue.cpp>
#include <engine/triangle.cpp>

#include <engine/camera.cpp>
#include <engine/lod.cpp>

#if PLATFORM_GL_IMPLEMENTATIONS
#include <engine/shader.cpp>
#include <engine/gpu_mapped_buffer.cpp>

#include <engine/render/render_init.cpp>
#include <engine/render/render_utils.cpp>
#include <engine/render/entity.cpp>
#include <engine/render.cpp> // TODO(Jesse): Probably time to split this up?
#endif

#include <engine/world_chunk.cpp>
#include <engine/world.cpp>
#include <engine/physics.cpp>
#include <engine/entity.cpp>
#include <engine/asset_loaders.cpp>

#if PLATFORM_GL_IMPLEMENTATIONS
#include <engine/debug_visualize.cpp>
#endif

#include <engine/api.cpp>
#include <engine/simulate.cpp>
#include <engine/voxel_synthesis.cpp>

