// src/engine/serdes.cpp:500:0

link_internal bonsai_type_info
TypeInfo(layered_brush_editor *Ignored)
{
  bonsai_type_info Result = {};

  Result.Name = CSz("layered_brush_editor");
  Result.Version = 0 ;

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
Serialize(u8_cursor_block_array *Bytes, layered_brush_editor *BaseElement, umm Count = 1)
{
  Assert(Count > 0);

  u64 PointerTrue = True;
  u64 PointerFalse = False;

  b32 Result = True;

  

  RangeIterator_t(umm, ElementIndex, Count)
  {
    layered_brush_editor *Element = BaseElement + ElementIndex;
    Result &= Serialize(Bytes, &Element->LayerCount);





    Result &= Serialize(Bytes, Element->Layers, 8);







    

    MAYBE_WRITE_DEBUG_OBJECT_DELIM();
  }

  return Result;
}

