// src/engine/editor.cpp:225:0

link_internal void
DoEditorUi(renderer_2d *Ui, window_layout *Window, model *Element, cs Name, ui_render_params *Params = &DefaultUiRenderParams_Generic)
{
  if (Element)
  {
    if (ToggleButton(Ui, FSz("v %S", Name), FSz("> %S", Name), UiId(Window, "toggle model", Element), &DefaultUiRenderParams_Generic))
    {
      PushNewRow(Ui);

      PushTableStart(Ui);
      OPEN_INDENT_FOR_TOGGLEABLE_REGION();
      DoEditorUi(Ui,
        Window,
&Element->Vox,
        CSz("Vox"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&Element->Meshes,
        CSz("Meshes"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&Element->TransparentMesh,
        CSz("TransparentMesh"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&Element->Animation,
        CSz("Animation"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&Element->Dim,
        CSz("Dim"),
        Params
        );
      CLOSE_INDENT_FOR_TOGGLEABLE_REGION();
      PushTableEnd(Ui);
    }
    else
    {
      PushNewRow(Ui);
    }

  }
  else
  {
    PushColumn(Ui, Name, Params);
    PushColumn(Ui, CSz("(null)"), Params);
    PushNewRow(Ui);
  }

}

