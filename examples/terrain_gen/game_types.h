
enum terrain_gen_type
{
  /* TerrainGenType_Undefined       = (0), */
  TerrainGenType_Flat            = (1 << 0),
  TerrainGenType_Checkerboard    = (1 << 1),
  TerrainGenType_Perlin2D        = (1 << 2),
  TerrainGenType_Perlin3D        = (1 << 3),
  TerrainGenType_FBM2D           = (1 << 4),
  TerrainGenType_TerracedTerrain = (1 << 5),
  TerrainGenType_GrassyIsland    = (1 << 6),
  TerrainGenType_Hoodoo          = (1 << 7),
  TerrainGenType_Warped          = (1 << 8),
};

poof(radio_button_group_for_bitfield_enum(terrain_gen_type))
#include <generated/radio_button_group_for_bitfield_enum_terrain_gen_type.h>

poof(string_and_value_tables(terrain_gen_type))
#include <generated/string_and_value_tables_terrain_gen_type.h>

struct game_state
{
  terrain_gen_type TerrainGenType;
};

