// src/engine/editor.cpp:346:0

link_internal void
DoEditorUi(renderer_2d *Ui, window_layout *Window, plane *Element, cs Name, ui_render_params *Params = &DefaultUiRenderParams_Generic)
{
  if (Element)
  {
    if (ToggleButton(Ui, FSz("v %S", Name), FSz("> %S", Name), UiId(Window, "toggle plane", Element), &DefaultUiRenderParams_Generic))
    {
      PushNewRow(Ui);

      PushTableStart(Ui);
      PushForceUpdateBasis(Ui, V2(20.f, 0.f));
      DoEditorUi(Ui,
        Window,
&(Element->P),
        CSz("v3 P"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&(Element->Normal),
        CSz("v3 Normal"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&(Element->d),
        CSz("r32 d"),
        Params
        );





      PushNewRow(Ui);


      PushForceUpdateBasis(Ui, V2(-20.f, 0.f));
      PushTableEnd(Ui);
    }

    PushNewRow(Ui);
  }
  else
  {
    PushColumn(Ui, Name, Params);
    PushColumn(Ui, CSz("(null)"), Params);
    PushNewRow(Ui);
  }

}

