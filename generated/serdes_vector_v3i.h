// src/engine/serdes.cpp:15:0

link_internal b32
Serialize(u8_cursor_block_array *Bytes, v3i *Element, umm Count = 1)
{
  Assert(Count > 0);
  b32 Result = Write(Bytes, Cast(u8*, Element), sizeof(v3i)*Count);

  MAYBE_WRITE_DEBUG_OBJECT_DELIM();
  return Result;
}

link_internal b32
Deserialize(u8_cursor *Bytes, v3i* Element, memory_arena *Ignored, umm Count = 1)
{
  Assert(Count > 0);
  *Element = *Cast(v3i*, Bytes->At);
  Bytes->At += sizeof(v3i)*Count;
  Assert(Bytes->At <= Bytes->End);

  b32 Result = True;
  MAYBE_READ_DEBUG_OBJECT_DELIM();
  return Result;
}


