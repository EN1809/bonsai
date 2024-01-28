link_internal bonsai_type_info
TypeInfo(vertex_material *Ignored)
{
  bonsai_type_info Result = {};

  Result.Name = CSz("vertex_material");
  Result.Version = 0 ;

  {
    member_info Member = {CSz("Color"), CSz("Color"), 0x30B3790A};
    Push(&Result.Members, &Member);
  }
  {
    member_info Member = {CSz("Transparency"), CSz("Transparency"), 0x1606BB8C};
    Push(&Result.Members, &Member);
  }
  {
    member_info Member = {CSz("Emission"), CSz("Emission"), 0x1938DEBC};
    Push(&Result.Members, &Member);
  }

  return Result;
}

link_internal b32
Serialize(native_file *File, vertex_material *Element)
{
  u64 PointerTrue = True; 
  u64 PointerFalse = False; 

  b32 Result = True;

  

  Result &= Serialize(File, &Element->Color);





  Result &= Serialize(File, &Element->Transparency);





  Result &= Serialize(File, &Element->Emission);

  

  MAYBE_WRITE_DEBUG_OBJECT_DELIM();
  return Result;
}

link_internal b32
DeserializeUnversioned(u8_stream *Bytes, vertex_material *Element, memory_arena *Memory)
{
  b32 Result = True;
  // NOTE(Jesse): Unfortunately we can't check for primitives because
  // strings are considered primitive, but need memory to deserialize
  Result &= Deserialize(Bytes, &Element->Color, Memory);





  // NOTE(Jesse): Unfortunately we can't check for primitives because
  // strings are considered primitive, but need memory to deserialize
  Result &= Deserialize(Bytes, &Element->Transparency, Memory);





  // NOTE(Jesse): Unfortunately we can't check for primitives because
  // strings are considered primitive, but need memory to deserialize
  Result &= Deserialize(Bytes, &Element->Emission, Memory);

  
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, vertex_material *Element, memory_arena *Memory)
{
  b32 Result = True;

  Result &= DeserializeUnversioned(Bytes, Element, Memory);
  MAYBE_READ_DEBUG_OBJECT_DELIM();


  return Result;
}


