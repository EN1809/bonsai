struct post_processing_group
{
  framebuffer FBO;
  shader Shader;

  u32 VertexBuffer;
  u32 ColorBuffer;
};

struct graphics
{
  camera *Camera;

  g_buffer_render_group * gBuffer;
  ao_render_group       * AoGroup;
  shadow_render_group   * SG;
  post_processing_group * PostGroup;
  lighting_render_group * Lighting;

  gpu_mapped_element_buffer GpuBuffers[2];
  u32 GpuBufferWriteIndex;

  memory_arena *Memory;
};
