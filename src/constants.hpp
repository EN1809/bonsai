#ifndef GAME_CONSTANTS
#define GAME_CONSTANTS

#define True 0
#define False 1

#define DEBUG_GLOBAL static
#define GLOBAL_VARIABLE static

#define BONSAI_INTERNAL 1

#define CHUNK_VOL (CHUNK_HEIGHT*CHUNK_WIDTH*CHUNK_DEPTH)

// 6 verticies per face, 6 faces per voxel
#define VERT_PER_VOXEL (6*6)

// 3 floats per vert
#define BYTES_PER_VERT (sizeof(float)*3)

#define VOXEL_DIAMETER (1.0f)
#define VOXEL_RADIUS (VOXEL_DIAMETER/2.0f)

#define CD_X 30
#define CD_Y 30
#define CD_Z 30

// Visible Region XYZ - Must be > (3,3,3)
#define VR_X 24
#define VR_Y 24
#define VR_Z 24

#define VOLUME_VISIBLE_REGION (VR_X*VR_X*VR_X)

#define WORLD_X V3(1,0,0)
#define WORLD_Y V3(0,1,0)
#define WORLD_Z V3(0,0,1)

#define CHUNK_DIMENSION Chunk_Dimension(CD_X,CD_Y,CD_Z)

#define VISIBLE_REGION Chunk_Dimension(VR_X,VR_Y,VR_Z)

#define NOISE_FREQUENCY 400

#define WORLD_HASH_SIZE VOLUME_VISIBLE_REGION
#define FREELIST_SIZE VOLUME_VISIBLE_REGION

#define WORLD_GRAVITY V3(0, -20.0f, 0)

#define PLAYER_STEP_MAX          1
#define PLAYER_JUMP_STRENGTH     20.0f
#define PLAYER_ACCEL_MULTIPLIER  50.0f


#define DEBUG_SCROLL_WORLD            1
#define DEBUG_CHUNK_AABB              1
#define DEBUG_CAMERA_FOCUS_ORIGIN     0
#define DEBUG_WORLD_GENERATION        0
#define DEBUG_LOD_RENDER              0
#define DEBUG_DRAW_SHADOW_MAP_TEXTURE 0
#define DEBUG_HIGHLIGHT_VOID_CHUNKS   0
#define DEBUG_DRAW_AXIES              1

#define DEBUG_FRAMES_TO_RUN            -1

//
// Screen Resolution

// #define SCR_WIDTH 800
// #define SCR_HEIGHT 600

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

/* #define SCR_WIDTH 3840 */
/* #define SCR_HEIGHT 2160 */

#define Proj_XY 50
#define Proj_Z  100
#define SHADOW_MAP_RESOLUTION 2048
#define DEBUG_TEXTURE_SIZE    512

GLOBAL_VARIABLE float CAMERA_FOCAL_LENGTH = 150.0f;
GLOBAL_VARIABLE float DEBUG_CAMERA_FOCAL_LENGTH = 100.0f;
#define DEBUG_CAMERA_SCROLL_SPEED  20.0f

#define CAMERA_INITIAL_P Canonical_Position(&world, V3(1,1,1), World_Position(world.VisibleRegion/2))

// NOTE(Jesse): The position storage needs to be as large as the largest model
// that will ever be loaded. Can we load models in chunks as well?
#define POSITION_BIT_WIDTH 5
#define COLOR_BIT_WIDTH 8

#define FINAL_POSITION_BIT (POSITION_BIT_WIDTH*3)
#define FINAL_COLOR_BIT ((FINAL_POSITION_BIT+COLOR_BIT_WIDTH))


DEBUG_GLOBAL double DEBUG_NOISE_SEED = 43165.43543;

DEBUG_GLOBAL int numFrames = 0;
DEBUG_GLOBAL float accumulatedTime = 0;

DEBUG_GLOBAL int tris = 0;
DEBUG_GLOBAL int VoxelsIndexed = 0;

DEBUG_GLOBAL float GlobalLightTheta = 0;

DEBUG_GLOBAL AABB LastFreeSlice(V3(0,0,0), V3(0,0,0));
DEBUG_GLOBAL AABB LastQueuedSlice(V3(0,0,0), V3(0,0,0));

GLOBAL_VARIABLE PerlinNoise GlobalNoise;

DEBUG_GLOBAL bool UseDebugCamera = true;

#define FACE_COLOR_SIZE 32
#define PALETTE_SIZE 256

#endif
