link_internal bonsai_type_info
TypeInfo(entity_game_data *Ignored)
{
  bonsai_type_info Result = {};

  Result.Name = CSz("entity_game_data");

  {
    member_info Member = {CSz("FireballChargeLevel"), CSz("FireballChargeLevel"), 0x14F5CFDE};
    Push(&Result.Members, &Member);
  }
  {
    member_info Member = {CSz("FireballCharges"), CSz("FireballCharges"), 0x25D35A3F};
    Push(&Result.Members, &Member);
  }
  {
    member_info Member = {CSz("IceBlockCharges"), CSz("IceBlockCharges"), 0x1635CD32};
    Push(&Result.Members, &Member);
  }
  {
    member_info Member = {CSz("HoldingItem"), CSz("HoldingItem"), 0x12373165};
    Push(&Result.Members, &Member);
  }

  return Result;
}

link_internal b32
Serialize(native_file *File, entity_game_data *Element)
{
  u64 PointerTrue = True; 
  u64 PointerFalse = False; 

  b32 Result = True;

  

  Result &= Serialize(File, &Element->FireballChargeLevel);





  Result &= Serialize(File, &Element->FireballCharges);





  Result &= Serialize(File, &Element->IceBlockCharges);





  Result &= Serialize(File, &Element->HoldingItem);

  

  MAYBE_WRITE_DEBUG_OBJECT_DELIM();
  return Result;
}


link_internal b32
DeserializeUnversioned(u8_stream *Bytes, entity_game_data *Element, memory_arena *Memory)
{
  b32 Result = True;
  // NOTE(Jesse): Unfortunately we can't check for primitives because
  // strings are considered primitive, but need memory to deserialize
  Result &= Deserialize(Bytes, &Element->FireballChargeLevel, Memory);





  // NOTE(Jesse): Unfortunately we can't check for primitives because
  // strings are considered primitive, but need memory to deserialize
  Result &= Deserialize(Bytes, &Element->FireballCharges, Memory);





  // NOTE(Jesse): Unfortunately we can't check for primitives because
  // strings are considered primitive, but need memory to deserialize
  Result &= Deserialize(Bytes, &Element->IceBlockCharges, Memory);





  // NOTE(Jesse): Unfortunately we can't check for primitives because
  // strings are considered primitive, but need memory to deserialize
  Result &= Deserialize(Bytes, &Element->HoldingItem, Memory);

  
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, entity_game_data *Element, memory_arena *Memory)
{
  b32 Result = True;

  Result &= DeserializeUnversioned(Bytes, Element, Memory);
  MAYBE_READ_DEBUG_OBJECT_DELIM();


  return Result;
}


