// src/engine/editor.cpp:90:0

link_internal void
DoEditorUi(renderer_2d *Ui, window_layout *Window, perlin_noise_params *Element, cs Name, ui_render_params *Params = &DefaultUiRenderParams_Generic)
{
  if (Element)
  {
    if (ToggleButton(Ui, FSz("v %S", Name), FSz("> %S", Name), UiId(Window, "toggle perlin_noise_params", Element), &DefaultUiRenderParams_Generic))
    {
      PushNewRow(Ui);

      PushTableStart(Ui);
      PushForceUpdateBasis(Ui, V2(20.f, 0.f));
      DoEditorUi(Ui,
        Window,
&Element->Threshold,
        CSz("Threshold"),
        Params
        );





      PushNewRow(Ui);

      DoEditorUi(Ui,
        Window,
&Element->Period,
        CSz("Period"),
        Params
        );





      PushNewRow(Ui);

      DoEditorUi(Ui,
        Window,
&Element->Amplitude,
        CSz("Amplitude"),
        Params
        );





      PushNewRow(Ui);
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

