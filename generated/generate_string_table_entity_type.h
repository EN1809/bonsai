// examples/turn_based/game_types.h:42:0

link_internal counted_string
ToString(entity_type Type)
{
  counted_string Result = {};
  switch (Type)
  {
    case EntityType_Default: { Result = CSz("EntityType_Default"); } break;
    case EntityType_Enemy: { Result = CSz("EntityType_Enemy"); } break;
    case EntityType_Player: { Result = CSz("EntityType_Player"); } break;
    case EntityType_Fireball: { Result = CSz("EntityType_Fireball"); } break;
    case EntityType_Loot: { Result = CSz("EntityType_Loot"); } break;
    case EntityType_ItemSpawn: { Result = CSz("EntityType_ItemSpawn"); } break;

    
  }
  return Result;
}

