link_internal b32
Serialize(native_file *File, u8 *Element, memory_arena *Ignored = 0)
{
  b32 Result = WriteToFile(File, Cast(u8*, Element), sizeof(u8));
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, u8* Element, memory_arena *Ignored = 0)
{
  *Element = *Cast(u8*, Bytes->At);
  Bytes->At += sizeof(u8);
  Assert(Bytes->At <= Bytes->End);
  return True;
}

link_internal b32
SerializeArray(native_file *File, u8 *Element, umm Count)
{
  Assert(Count);
  {
    RangeIterator_t(umm, ElementIndex, Count)
    {
      Serialize(File, Element+ElementIndex);
    }
  }
  return True;
}

link_internal b32
DeserializeArray(u8_stream *Bytes, u8 **Dest, umm Count, memory_arena *Memory)
{
  Assert(Count);
  if (*Dest == 0) { *Dest = Allocate(u8, Memory, Count); }
  RangeIterator_t(umm, ElementIndex, Count)
  {
    Deserialize(Bytes, (*Dest)+ElementIndex, Memory);
  }
  return True;
}


link_internal b32
Serialize(native_file *File, s8 *Element, memory_arena *Ignored = 0)
{
  b32 Result = WriteToFile(File, Cast(u8*, Element), sizeof(s8));
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, s8* Element, memory_arena *Ignored = 0)
{
  *Element = *Cast(s8*, Bytes->At);
  Bytes->At += sizeof(s8);
  Assert(Bytes->At <= Bytes->End);
  return True;
}

link_internal b32
SerializeArray(native_file *File, s8 *Element, umm Count)
{
  Assert(Count);
  {
    RangeIterator_t(umm, ElementIndex, Count)
    {
      Serialize(File, Element+ElementIndex);
    }
  }
  return True;
}

link_internal b32
DeserializeArray(u8_stream *Bytes, s8 **Dest, umm Count, memory_arena *Memory)
{
  Assert(Count);
  if (*Dest == 0) { *Dest = Allocate(s8, Memory, Count); }
  RangeIterator_t(umm, ElementIndex, Count)
  {
    Deserialize(Bytes, (*Dest)+ElementIndex, Memory);
  }
  return True;
}


link_internal b32
Serialize(native_file *File, u16 *Element, memory_arena *Ignored = 0)
{
  b32 Result = WriteToFile(File, Cast(u8*, Element), sizeof(u16));
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, u16* Element, memory_arena *Ignored = 0)
{
  *Element = *Cast(u16*, Bytes->At);
  Bytes->At += sizeof(u16);
  Assert(Bytes->At <= Bytes->End);
  return True;
}

link_internal b32
SerializeArray(native_file *File, u16 *Element, umm Count)
{
  Assert(Count);
  {
    RangeIterator_t(umm, ElementIndex, Count)
    {
      Serialize(File, Element+ElementIndex);
    }
  }
  return True;
}

link_internal b32
DeserializeArray(u8_stream *Bytes, u16 **Dest, umm Count, memory_arena *Memory)
{
  Assert(Count);
  if (*Dest == 0) { *Dest = Allocate(u16, Memory, Count); }
  RangeIterator_t(umm, ElementIndex, Count)
  {
    Deserialize(Bytes, (*Dest)+ElementIndex, Memory);
  }
  return True;
}


link_internal b32
Serialize(native_file *File, s16 *Element, memory_arena *Ignored = 0)
{
  b32 Result = WriteToFile(File, Cast(u8*, Element), sizeof(s16));
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, s16* Element, memory_arena *Ignored = 0)
{
  *Element = *Cast(s16*, Bytes->At);
  Bytes->At += sizeof(s16);
  Assert(Bytes->At <= Bytes->End);
  return True;
}

link_internal b32
SerializeArray(native_file *File, s16 *Element, umm Count)
{
  Assert(Count);
  {
    RangeIterator_t(umm, ElementIndex, Count)
    {
      Serialize(File, Element+ElementIndex);
    }
  }
  return True;
}

link_internal b32
DeserializeArray(u8_stream *Bytes, s16 **Dest, umm Count, memory_arena *Memory)
{
  Assert(Count);
  if (*Dest == 0) { *Dest = Allocate(s16, Memory, Count); }
  RangeIterator_t(umm, ElementIndex, Count)
  {
    Deserialize(Bytes, (*Dest)+ElementIndex, Memory);
  }
  return True;
}


link_internal b32
Serialize(native_file *File, u32 *Element, memory_arena *Ignored = 0)
{
  b32 Result = WriteToFile(File, Cast(u8*, Element), sizeof(u32));
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, u32* Element, memory_arena *Ignored = 0)
{
  *Element = *Cast(u32*, Bytes->At);
  Bytes->At += sizeof(u32);
  Assert(Bytes->At <= Bytes->End);
  return True;
}

link_internal b32
SerializeArray(native_file *File, u32 *Element, umm Count)
{
  Assert(Count);
  {
    RangeIterator_t(umm, ElementIndex, Count)
    {
      Serialize(File, Element+ElementIndex);
    }
  }
  return True;
}

link_internal b32
DeserializeArray(u8_stream *Bytes, u32 **Dest, umm Count, memory_arena *Memory)
{
  Assert(Count);
  if (*Dest == 0) { *Dest = Allocate(u32, Memory, Count); }
  RangeIterator_t(umm, ElementIndex, Count)
  {
    Deserialize(Bytes, (*Dest)+ElementIndex, Memory);
  }
  return True;
}


link_internal b32
Serialize(native_file *File, s32 *Element, memory_arena *Ignored = 0)
{
  b32 Result = WriteToFile(File, Cast(u8*, Element), sizeof(s32));
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, s32* Element, memory_arena *Ignored = 0)
{
  *Element = *Cast(s32*, Bytes->At);
  Bytes->At += sizeof(s32);
  Assert(Bytes->At <= Bytes->End);
  return True;
}

link_internal b32
SerializeArray(native_file *File, s32 *Element, umm Count)
{
  Assert(Count);
  {
    RangeIterator_t(umm, ElementIndex, Count)
    {
      Serialize(File, Element+ElementIndex);
    }
  }
  return True;
}

link_internal b32
DeserializeArray(u8_stream *Bytes, s32 **Dest, umm Count, memory_arena *Memory)
{
  Assert(Count);
  if (*Dest == 0) { *Dest = Allocate(s32, Memory, Count); }
  RangeIterator_t(umm, ElementIndex, Count)
  {
    Deserialize(Bytes, (*Dest)+ElementIndex, Memory);
  }
  return True;
}


link_internal b32
Serialize(native_file *File, u64 *Element, memory_arena *Ignored = 0)
{
  b32 Result = WriteToFile(File, Cast(u8*, Element), sizeof(u64));
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, u64* Element, memory_arena *Ignored = 0)
{
  *Element = *Cast(u64*, Bytes->At);
  Bytes->At += sizeof(u64);
  Assert(Bytes->At <= Bytes->End);
  return True;
}

link_internal b32
SerializeArray(native_file *File, u64 *Element, umm Count)
{
  Assert(Count);
  {
    RangeIterator_t(umm, ElementIndex, Count)
    {
      Serialize(File, Element+ElementIndex);
    }
  }
  return True;
}

link_internal b32
DeserializeArray(u8_stream *Bytes, u64 **Dest, umm Count, memory_arena *Memory)
{
  Assert(Count);
  if (*Dest == 0) { *Dest = Allocate(u64, Memory, Count); }
  RangeIterator_t(umm, ElementIndex, Count)
  {
    Deserialize(Bytes, (*Dest)+ElementIndex, Memory);
  }
  return True;
}


link_internal b32
Serialize(native_file *File, s64 *Element, memory_arena *Ignored = 0)
{
  b32 Result = WriteToFile(File, Cast(u8*, Element), sizeof(s64));
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, s64* Element, memory_arena *Ignored = 0)
{
  *Element = *Cast(s64*, Bytes->At);
  Bytes->At += sizeof(s64);
  Assert(Bytes->At <= Bytes->End);
  return True;
}

link_internal b32
SerializeArray(native_file *File, s64 *Element, umm Count)
{
  Assert(Count);
  {
    RangeIterator_t(umm, ElementIndex, Count)
    {
      Serialize(File, Element+ElementIndex);
    }
  }
  return True;
}

link_internal b32
DeserializeArray(u8_stream *Bytes, s64 **Dest, umm Count, memory_arena *Memory)
{
  Assert(Count);
  if (*Dest == 0) { *Dest = Allocate(s64, Memory, Count); }
  RangeIterator_t(umm, ElementIndex, Count)
  {
    Deserialize(Bytes, (*Dest)+ElementIndex, Memory);
  }
  return True;
}


link_internal b32
Serialize(native_file *File, b8 *Element, memory_arena *Ignored = 0)
{
  b32 Result = WriteToFile(File, Cast(u8*, Element), sizeof(b8));
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, b8* Element, memory_arena *Ignored = 0)
{
  *Element = *Cast(b8*, Bytes->At);
  Bytes->At += sizeof(b8);
  Assert(Bytes->At <= Bytes->End);
  return True;
}

link_internal b32
SerializeArray(native_file *File, b8 *Element, umm Count)
{
  Assert(Count);
  {
    RangeIterator_t(umm, ElementIndex, Count)
    {
      Serialize(File, Element+ElementIndex);
    }
  }
  return True;
}

link_internal b32
DeserializeArray(u8_stream *Bytes, b8 **Dest, umm Count, memory_arena *Memory)
{
  Assert(Count);
  if (*Dest == 0) { *Dest = Allocate(b8, Memory, Count); }
  RangeIterator_t(umm, ElementIndex, Count)
  {
    Deserialize(Bytes, (*Dest)+ElementIndex, Memory);
  }
  return True;
}


link_internal b32
Serialize(native_file *File, r32 *Element, memory_arena *Ignored = 0)
{
  b32 Result = WriteToFile(File, Cast(u8*, Element), sizeof(r32));
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, r32* Element, memory_arena *Ignored = 0)
{
  *Element = *Cast(r32*, Bytes->At);
  Bytes->At += sizeof(r32);
  Assert(Bytes->At <= Bytes->End);
  return True;
}

link_internal b32
SerializeArray(native_file *File, r32 *Element, umm Count)
{
  Assert(Count);
  {
    RangeIterator_t(umm, ElementIndex, Count)
    {
      Serialize(File, Element+ElementIndex);
    }
  }
  return True;
}

link_internal b32
DeserializeArray(u8_stream *Bytes, r32 **Dest, umm Count, memory_arena *Memory)
{
  Assert(Count);
  if (*Dest == 0) { *Dest = Allocate(r32, Memory, Count); }
  RangeIterator_t(umm, ElementIndex, Count)
  {
    Deserialize(Bytes, (*Dest)+ElementIndex, Memory);
  }
  return True;
}


link_internal b32
Serialize(native_file *File, r64 *Element, memory_arena *Ignored = 0)
{
  b32 Result = WriteToFile(File, Cast(u8*, Element), sizeof(r64));
  return Result;
}

link_internal b32
Deserialize(u8_stream *Bytes, r64* Element, memory_arena *Ignored = 0)
{
  *Element = *Cast(r64*, Bytes->At);
  Bytes->At += sizeof(r64);
  Assert(Bytes->At <= Bytes->End);
  return True;
}

link_internal b32
SerializeArray(native_file *File, r64 *Element, umm Count)
{
  Assert(Count);
  {
    RangeIterator_t(umm, ElementIndex, Count)
    {
      Serialize(File, Element+ElementIndex);
    }
  }
  return True;
}

link_internal b32
DeserializeArray(u8_stream *Bytes, r64 **Dest, umm Count, memory_arena *Memory)
{
  Assert(Count);
  if (*Dest == 0) { *Dest = Allocate(r64, Memory, Count); }
  RangeIterator_t(umm, ElementIndex, Count)
  {
    Deserialize(Bytes, (*Dest)+ElementIndex, Memory);
  }
  return True;
}


