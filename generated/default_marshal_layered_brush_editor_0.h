// src/engine/editor.h:959:0

Live->LayerCount = Stored->LayerCount;

RangeIterator(Index, 16)
{
  Live->Layers[Index] = Stored->Layers[Index];
}

Live->Preview = Stored->Preview;

Live->SeedBrushWithSelection = Stored->SeedBrushWithSelection;

