// src/engine/editor.cpp:158:0

link_internal counted_string
ToStringPrefixless(engine_debug_view_mode Type)
{
  counted_string Result = {};
  switch (Type)
  {
    case EngineDebugViewMode_Level: { Result = CSz("Level"); } break;
    case EngineDebugViewMode_WorldEdit: { Result = CSz("WorldEdit"); } break;
    case EngineDebugViewMode_Entities: { Result = CSz("Entities"); } break;
    case EngineDebugViewMode_Assets: { Result = CSz("Assets"); } break;
    case EngineDebugViewMode_WorldChunks: { Result = CSz("WorldChunks"); } break;
    case EngineDebugViewMode_Textures: { Result = CSz("Textures"); } break;
    case EngineDebugViewMode_RenderSettings: { Result = CSz("RenderSettings"); } break;
    case EngineDebugViewMode_EngineDebug: { Result = CSz("EngineDebug"); } break;

    
  }
  /* if (Result.Start == 0) { Info("Could not convert value(%d) to (EnumType.name)", Type); } */
  return Result;
}

link_internal counted_string
ToString(engine_debug_view_mode Type)
{
  counted_string Result = {};
  switch (Type)
  {
    case EngineDebugViewMode_Level: { Result = CSz("EngineDebugViewMode_Level"); } break;
    case EngineDebugViewMode_WorldEdit: { Result = CSz("EngineDebugViewMode_WorldEdit"); } break;
    case EngineDebugViewMode_Entities: { Result = CSz("EngineDebugViewMode_Entities"); } break;
    case EngineDebugViewMode_Assets: { Result = CSz("EngineDebugViewMode_Assets"); } break;
    case EngineDebugViewMode_WorldChunks: { Result = CSz("EngineDebugViewMode_WorldChunks"); } break;
    case EngineDebugViewMode_Textures: { Result = CSz("EngineDebugViewMode_Textures"); } break;
    case EngineDebugViewMode_RenderSettings: { Result = CSz("EngineDebugViewMode_RenderSettings"); } break;
    case EngineDebugViewMode_EngineDebug: { Result = CSz("EngineDebugViewMode_EngineDebug"); } break;

    
  }
  /* if (Result.Start == 0) { Info("Could not convert value(%d) to (EnumType.name)", Type); } */
  return Result;
}

link_internal engine_debug_view_mode
EngineDebugViewMode(counted_string S)
{
  engine_debug_view_mode Result = {};

  if (StringsMatch(S, CSz("EngineDebugViewMode_Level"))) { return EngineDebugViewMode_Level; }
  if (StringsMatch(S, CSz("EngineDebugViewMode_WorldEdit"))) { return EngineDebugViewMode_WorldEdit; }
  if (StringsMatch(S, CSz("EngineDebugViewMode_Entities"))) { return EngineDebugViewMode_Entities; }
  if (StringsMatch(S, CSz("EngineDebugViewMode_Assets"))) { return EngineDebugViewMode_Assets; }
  if (StringsMatch(S, CSz("EngineDebugViewMode_WorldChunks"))) { return EngineDebugViewMode_WorldChunks; }
  if (StringsMatch(S, CSz("EngineDebugViewMode_Textures"))) { return EngineDebugViewMode_Textures; }
  if (StringsMatch(S, CSz("EngineDebugViewMode_RenderSettings"))) { return EngineDebugViewMode_RenderSettings; }
  if (StringsMatch(S, CSz("EngineDebugViewMode_EngineDebug"))) { return EngineDebugViewMode_EngineDebug; }

  return Result;
}


