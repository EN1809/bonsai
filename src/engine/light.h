struct light
{
  v3 Position;
  v3 Color;
};

struct game_lights
{
  texture *ColorTex;
  texture *PositionTex;

  r32 IndexToUV;

  s32 Count; // Must be signed because of the shader
  light *Lights;
};

struct shadow_render_group
{
  u32 FramebufferName;
  s32 MVP_ID;

  shader DebugTextureShader;
  shader DepthShader;

  m4 MVP;

  texture *ShadowMap;
  light Sun;
};

struct lighting_render_group
{
  game_lights Lights;

  // This has both the Lighting and Bloom textures attached
  framebuffer FBO;

  // NOTE(Jesse): This is an FBO with only the Bloom texture attached; for
  // writing the final result of the gaussian blur to
  framebuffer BloomTextureFBO;

  texture *LightingTex;
  texture *BloomTex;

  shader Shader;

  shader DebugBloomShader;
  shader DebugLightingShader;
};

void
DoLight(game_lights *Lights, v3 Position, v3 Color)
{
  Assert(Lights->Count < MAX_LIGHTS);

  if (Lights->Count < MAX_LIGHTS)
  {
    light *Light = Lights->Lights + Lights->Count++;
    Light->Position = Position;
    Light->Color = Color;
  }

 return;
}

#define LUMINANCE_MAP_RESOLUTION_X (SCR_WIDTH)
#define LUMINANCE_MAP_RESOLUTION_Y (SCR_HEIGHT)

// TODO(Jesse): Make a shadow.h ?
// NOTE(Jesse): 32x1024 x2 == 64k at 32bit float
#define SHADOW_MAP_RESOLUTION_X (16*1024)
#define SHADOW_MAP_RESOLUTION_Y (16*1024)
/* #define SHADOW_MAP_RESOLUTION_X (2*1024) */
/* #define SHADOW_MAP_RESOLUTION_Y (2*1024) */

#define SHADOW_MAP_X 1024
#define SHADOW_MAP_Y 1024
#define SHADOW_MAP_Z_MIN -1024
#define SHADOW_MAP_Z_MAX  1024

/* #define SHADOW_MAP_X 512 */
/* #define SHADOW_MAP_Y 512 */
/* #define SHADOW_MAP_Z_MIN -512 */
/* #define SHADOW_MAP_Z_MAX  512 */
