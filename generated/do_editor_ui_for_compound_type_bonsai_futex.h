// src/engine/editor.cpp:183:0

link_internal void
DoEditorUi(renderer_2d *Ui, window_layout *Window, bonsai_futex *Element, cs Name, ui_render_params *Params = &DefaultUiRenderParams_Generic)
{
  if (Element)
  {
    if (ToggleButton(Ui, FSz("v %S", Name), FSz("> %S", Name), UiId(Window, "toggle bonsai_futex", Element), &DefaultUiRenderParams_Generic))
    {
      PushNewRow(Ui);

      PushTableStart(Ui);
      OPEN_INDENT_FOR_TOGGLEABLE_REGION();
      DoEditorUi(Ui,
        Window,
&Element->SignalValue,
        CSz("SignalValue"),
        Params
        );





      PushNewRow(Ui);

      DoEditorUi(Ui,
        Window,
&Element->ThreadsWaiting,
        CSz("ThreadsWaiting"),
        Params
        );





      PushNewRow(Ui);

      DoEditorUi(Ui,
        Window,
        Cast(b8*,&Element->Initialized),
        CSz("Initialized"),
        &DefaultUiRenderParams_Checkbox
        );





      PushNewRow(Ui);
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

