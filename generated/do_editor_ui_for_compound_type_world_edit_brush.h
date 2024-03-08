// src/engine/editor.h:794:0

link_internal void
DoEditorUi(renderer_2d *Ui, window_layout *Window, world_edit_brush *Element, cs Name, ui_render_params *Params = &DefaultUiRenderParams_Generic)
{
  if (Element)
  {
    if (ToggleButton(Ui, FSz("v %S", Name), FSz("> %S", Name), UiId(Window, "toggle world_edit_brush", Element), &DefaultUiRenderParams_Generic))
    {
      PushNewRow(Ui);

      PushTableStart(Ui);
      PushForceUpdateBasis(Ui, V2(20.f, 0.f));
      DoEditorUi(Ui,
        Window,
&Element->Shape,
        CSz("Shape"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&Element->Mode,
        CSz("Mode"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&Element->Modifier,
        CSz("Modifier"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&Element->SimFloodOrigin,
        CSz("SimFloodOrigin"),
        Params
        );
      PushForceUpdateBasis(Ui, V2(-20.f, 0.f));
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

