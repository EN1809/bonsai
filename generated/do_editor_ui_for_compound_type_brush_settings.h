// src/engine/editor.cpp:124:0

link_internal void
DoEditorUi(renderer_2d *Ui, window_layout *Window, brush_settings *Element, cs Name, ui_render_params *Params = &DefaultUiRenderParams_Generic)
{
  if (Element)
  {
    // NOTE(Jesse): This is wacky as fuck, but it's a pretty easy way to
    // support not drawing the toggl-y thing if we just want to dump the members.
    b32 DrawChildren = True;
    b32 DidToggle = False;
    if (Name)
    {
      if (ToggleButton(Ui, FSz("v %S", Name), FSz("> %S", Name), UiId(Window, "toggle brush_settings", Element), &DefaultUiRenderParams_Generic))
      {
        DidToggle = True;
        PushNewRow(Ui);
      }
      else
      {
        DrawChildren = False;
      }
    }

    if (DrawChildren)
    {
      PushTableStart(Ui);
      if (DidToggle) { OPEN_INDENT_FOR_TOGGLEABLE_REGION(); }
      DoEditorUi(Ui,
        Window,
&Element->Type,
        CSz("Type"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&Element->Noise,
        CSz("Noise"),
        Params
        );





      
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
&Element->Iterations,
        CSz("Iterations"),
        Params
        );





      PushNewRow(Ui);

      DoEditorUi(Ui,
        Window,
&Element->Offset,
        CSz("Offset"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&Element->Color,
        CSz("Color"),
        Params
        );





      PushNewRow(Ui);
      if (DidToggle) { CLOSE_INDENT_FOR_TOGGLEABLE_REGION(); }
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

