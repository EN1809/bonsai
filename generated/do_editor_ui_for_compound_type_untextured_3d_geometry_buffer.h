link_internal void
DoEditorUi(renderer_2d *Ui, untextured_3d_geometry_buffer *Element, const char* Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS)
{
  /* PushTableStart(Ui); */
  if (ToggleButton(Ui, CS(Name), CS(Name), umm(Element) ^ umm(Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES))
  {
    PushNewRow(Ui);
    DoEditorUi(Ui, Element->Verts, "v3 Verts", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, Element->Normals, "v3 Normals", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, Element->Mat, "vertex_material Mat", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, &Element->End, "u32 End", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, &Element->At, "u32 At", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


  }
  else
  {
    PushNewRow(Ui);
  }
  /* PushTableEnd(Ui); */
}
