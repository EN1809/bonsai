// src/engine/editor.h:664:0

link_internal void
RadioSelect(ui_toggle_button_group *RadioGroup, world_edit_brush_type Selection)
{
  ui_toggle_button_handle *ToggleHandle = RadioGroup->Buttons.Start + Selection;
  SetRadioButton(RadioGroup, ToggleHandle, True);
  /* Ensure( ToggleRadioButton(RadioGroup, ToggleHandle) ); */
}

// NOTE(Jesse): This could be implemented by reconstructing the button ID
// but I'm very unsure that's worth it.  Seems like just
link_internal b32
Clicked(ui_toggle_button_group *ButtonGroup, world_edit_brush_type Enum)
{
  b32 Result = False;
  NotImplemented;
  return Result;
}

link_internal ui_toggle_button_group
RadioButtonGroup_world_edit_brush_type( renderer_2d *Ui,
  window_layout *Window,
  cs  GroupName,
  world_edit_brush_type *Element,
  ui_render_params *Params     = &DefaultUiRenderParams_Generic,
  ui_toggle_button_group_flags  ExtraFlags = ToggleButtonGroupFlags_None)
{
  cs ButtonNames[] =
  {
    CSz("Disabled"),
    CSz("Selection"),
    CSz("Single"),
    CSz("Asset"),
    CSz("Entity"),
    CSz("Shape"),
    CSz("Noise"),
    CSz("Layered"),
  };

  u32 ButtonCount = ArrayCount(ButtonNames);

  ui_toggle_button_handle_buffer ButtonBuffer = UiToggleButtonHandleBuffer(ButtonCount, GetTranArena());
  IterateOver(&ButtonBuffer, Button, ButtonIndex)
  {
    cs ButtonName = ButtonNames[ButtonIndex];
    *Button = UiToggle(ButtonName, UiId(Window, Cast(void*, Element), Cast(void*, ButtonName.Start)));
  }

  ui_toggle_button_group Result = DrawButtonGroupForEnum(Ui, &ButtonBuffer, GroupName, Cast(u32*, Element), Params, ui_toggle_button_group_flags(ExtraFlags|ToggleButtonGroupFlags_RadioButtons));
  return Result;
}




link_internal ui_toggle_button_group
DoEditorUi( renderer_2d *Ui,
  window_layout *Window,
  world_edit_brush_type *Element,
  cs GroupName,
  ui_render_params *Params = &DefaultUiRenderParams_Generic,
  ui_toggle_button_group_flags ExtraFlags = ToggleButtonGroupFlags_None)
{
  ui_toggle_button_group RadioGroup = RadioButtonGroup_world_edit_brush_type(Ui, Window, GroupName, Element, Params, ExtraFlags);
  return RadioGroup;
}

