// src/engine/serdes.cpp:396:0

link_internal bonsai_type_info
TypeInfo(level_header *Ignored)
{
  bonsai_type_info Result = {};

  Result.Name = CSz("level_header");
  Result.Version =2 ;

  /* type.map(member) */
  /* { */
  /*   { */
  /*     member_info Member = {CSz("member.name"), CSz("member.name"), 0x(member.hash)}; */
  /*     Push(&Result.Members, &Member); */
  /*   } */
  /* } */

  return Result;
}

link_internal b32
Serialize(u8_cursor_block_array *Bytes, level_header *Element)
{
  u64 PointerTrue = True; 
  u64 PointerFalse = False; 

  b32 Result = True;

  Upsert(TypeInfo(Element), &Global_SerializeTypeTable, Global_SerializeTypeTableArena );
  u64 VersionNumber =2;
  Serialize(Bytes, &VersionNumber);


  Result &= Serialize(Bytes, &Element->ChunkCount);





  Result &= Serialize(Bytes, &Element->EntityCount);





  Result &= Serialize(Bytes, &Element->WorldFlags);





  Result &= Serialize(Bytes, &Element->WorldCenter);





  Result &= Serialize(Bytes, &Element->VisibleRegion);





  Result &= Serialize(Bytes, &Element->Camera);





  Result &= Serialize(Bytes, &Element->CameraTarget);

  

  MAYBE_WRITE_DEBUG_OBJECT_DELIM();
  return Result;
}

