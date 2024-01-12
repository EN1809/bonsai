link_internal void
DoEditorUi(renderer_2d *Ui, model_buffer *Container, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS)
{
  if (Container)
  {
    if (ToggleButton(Ui, FSz("v %S", Name), FSz("> %S", Name), UiId(Container, Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES))
    {
      IterateOver(Container, Element, ElementIndex)
      {
        DoEditorUi(Ui, Element, CS(ElementIndex), EDITOR_UI_FUNCTION_INSTANCE_NAMES);
      }
    }
  }
  else
  {
    PushColumn(Ui, FSz("%S = (null)", Name));
    PushNewRow(Ui);
  }
}

