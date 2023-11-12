link_internal void
DoEditorUi(renderer_2d *Ui, entity *Element, const char* Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS)
{
  /* PushTableStart(Ui); */
  if (ToggleButton(Ui, CS(Name), CS(Name), umm(Element) ^ umm(Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES))
  {
    PushNewRow(Ui);
    DoEditorUi(Ui, &Element->Id, "umm Id", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, &Element->P, "cp P", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, &Element->Rotation, "Quaternion Rotation", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, &Element->Scale, "r32 Scale", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, &Element->CollisionVolumeRadius, "v3 CollisionVolumeRadius", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, &Element->Physics, "physics Physics", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, Element->Model, "model Model", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, Element->Emitter, "particle_system Emitter", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, &Element->State, "entity_state State", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, &Element->Behavior, "entity_behavior_flags Behavior", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, &Element->UserType, "u64 UserType", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


    DoEditorUi(Ui, &Element->UserData, "umm UserData", EDITOR_UI_FUNCTION_INSTANCE_NAMES);


  }
  else
  {
    PushNewRow(Ui);
  }
  /* PushTableEnd(Ui); */
}
