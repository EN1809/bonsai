// src/engine/editor.cpp:273:0

link_internal void
DoEditorUi(renderer_2d *Ui, window_layout *Window, entity_position_info *Element, cs Name, ui_render_params *Params = &DefaultUiRenderParams_Generic)
{
  if (Element)
  {
    // NOTE(Jesse): This is wacky as fuck, but it's a pretty easy way to
    // support not drawing the toggl-y thing if we just want to dump the members.
    b32 DrawChildren = True;
    b32 DidToggle = False;
    if (Name)
    {
      if (ToggleButton(Ui, FSz("v %S", Name), FSz("> %S", Name), UiId(Window, "toggle entity_position_info", Element), &DefaultUiRenderParams_Generic))
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
&Element->P,
        CSz("P"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&Element->_CollisionVolumeRadius,
        CSz("_CollisionVolumeRadius"),
        Params
        );





      
      DoEditorUi(Ui,
        Window,
&Element->Scale,
        CSz("Scale"),
        Params
        );





      PushNewRow(Ui);

      DoEditorUi(Ui,
        Window,
&Element->EulerAngles,
        CSz("EulerAngles"),
        Params
        );
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

