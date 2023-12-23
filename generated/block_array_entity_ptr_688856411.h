struct entity_ptr_block
{
  u32 Index;
  u32 At;
  entity_ptr *Elements;
  entity_ptr_block *Next;
};

struct entity_ptr_block_array_index
{
  void *Block;
  u32 BlockIndex;
  u32 ElementIndex;
};

struct entity_ptr_block_array
{
  entity_ptr_block First;
  entity_ptr_block *Current;
  memory_arena *Memory;
};

link_internal entity_ptr_block_array_index
operator++(entity_ptr_block_array_index &I0)
{
  if (I0.Block)
  {
    if (I0.ElementIndex == 8-1)
    {
      I0.ElementIndex = 0;
      I0.BlockIndex++;
      I0.Block = Cast(entity_ptr_block*, I0.Block)->Next;
    }
    else
    {
      I0.ElementIndex++;
    }
  }
  else
  {
    I0.ElementIndex++;
  }
  return I0;
}

link_internal b32
operator<(entity_ptr_block_array_index I0, entity_ptr_block_array_index I1)
{
  b32 Result = I0.BlockIndex < I1.BlockIndex || (I0.BlockIndex == I1.BlockIndex & I0.ElementIndex < I1.ElementIndex);
  return Result;
}

link_inline umm
GetIndex(entity_ptr_block_array_index *Index)
{
  umm Result = Index->ElementIndex + (Index->BlockIndex*8);
  return Result;
}

link_internal entity_ptr_block_array_index
ZerothIndex(entity_ptr_block_array *Arr)
{
  entity_ptr_block_array_index Result = {};
  Result.Block = &Arr->First;
  Assert(Cast(entity_ptr_block*, Result.Block)->Index == 0);
  return Result;
}

link_internal umm
TotalElements(entity_ptr_block_array *Arr)
{
  umm Result = 0;
  if (Arr->Current)
  {
    Result = (Arr->Current->Index * 8) + Arr->Current->At;
  }
  return Result;
}

link_internal entity_ptr_block_array_index
AtElements(entity_ptr_block_array *Arr)
{
  entity_ptr_block_array_index Result = {};
  if (Arr->Current)
  {
    Result.Block = Arr->Current;
    Result.BlockIndex = Cast(entity_ptr_block*, Arr->Current)->Index;
    Result.ElementIndex = Cast(entity_ptr_block*, Arr->Current)->At;
  }
  return Result;
}

link_internal entity_ptr *
GetPtr(entity_ptr_block_array *Arr, entity_ptr_block_array_index Index)
{
  entity_ptr *Result = {};
  if (Index.Block) { Result = Cast(entity_ptr_block *, Index.Block)->Elements + Index.ElementIndex; }
  return Result;
}

link_internal entity_ptr *
GetPtr(entity_ptr_block *Block, umm Index)
{
  entity_ptr *Result = 0;
  if (Index < Block->At) { Result = Block->Elements + Index; }
  return Result;
}

link_internal entity_ptr *
GetPtr(entity_ptr_block_array *Arr, umm Index)
{
  umm BlockIndex = Index / 8;
  umm ElementIndex = Index % 8;

  umm AtBlock = 0;
  entity_ptr_block *Block = &Arr->First;
  while (AtBlock++ < BlockIndex)
  {
    Block = Block->Next;
  }

  entity_ptr *Result = Block->Elements+ElementIndex;
  return Result;
}

link_internal u32
AtElements(entity_ptr_block *Block)
{
  return Block->At;
}


link_internal entity_ptr_block*
Allocate_entity_ptr_block(memory_arena *Memory)
{
  entity_ptr_block *Result = Allocate(entity_ptr_block, Memory, 1);
  Result->Elements = Allocate(entity_ptr, Memory, 8);
  return Result;
}

link_internal cs
CS(entity_ptr_block_array_index Index)
{
  return FSz("(%u)(%u)", Index.BlockIndex, Index.ElementIndex);
}

link_internal void
RemoveUnordered(entity_ptr_block_array *Array, entity_ptr_block_array_index Index)
{
  Leak("RemoveUnordered");
}

link_internal entity_ptr *
Push(entity_ptr_block_array *Array, entity_ptr *Element)
{
  if (Array->Memory == 0) { Array->Memory = AllocateArena(); }

  if (Array->Current == 0) { Array->First = *Allocate_entity_ptr_block(Array->Memory); Array->Current = &Array->First; }

  if (Array->Current->At == 8)
  {
    entity_ptr_block *Next = Allocate_entity_ptr_block(Array->Memory);
    Next->Index = Array->Current->Index + 1;

    Array->Current->Next = Next;
    Array->Current = Next;
    /* Array->At = 0; */
  }

  entity_ptr *Result = Array->Current->Elements + Array->Current->At;

  Array->Current->Elements[Array->Current->At++] = *Element;

  return Result;
}


