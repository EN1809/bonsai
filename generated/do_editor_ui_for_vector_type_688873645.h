link_internal void
DoEditorUi(renderer_2d *Ui, v4i *Value, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS, EDITOR_UI_VALUE_RANGE_PROTO_DEFAULTS)
{
  /* PushTableStart(Ui); */
  if (Name) { PushColumn(Ui, CS(Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES); }

  if (Value)
  {
    u32 Start = StartColumn(Ui, EDITOR_UI_FUNCTION_INSTANCE_NAMES);
    PushTableStart(Ui);
    DoEditorUi(Ui, &Value->E[0], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[1], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[2], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[3], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    PushTableEnd(Ui);
    /* PushNewRow(Ui); */
    EndColumn(Ui, Start);
  }
  /* PushTableEnd(Ui); */

  PushNewRow(Ui);
}
link_internal void
DoEditorUi(renderer_2d *Ui, v4 *Value, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS, EDITOR_UI_VALUE_RANGE_PROTO_DEFAULTS)
{
  /* PushTableStart(Ui); */
  if (Name) { PushColumn(Ui, CS(Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES); }

  if (Value)
  {
    u32 Start = StartColumn(Ui, EDITOR_UI_FUNCTION_INSTANCE_NAMES);
    PushTableStart(Ui);
    DoEditorUi(Ui, &Value->E[0], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[1], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[2], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[3], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    PushTableEnd(Ui);
    /* PushNewRow(Ui); */
    EndColumn(Ui, Start);
  }
  /* PushTableEnd(Ui); */

  PushNewRow(Ui);
}
link_internal void
DoEditorUi(renderer_2d *Ui, v3i *Value, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS, EDITOR_UI_VALUE_RANGE_PROTO_DEFAULTS)
{
  /* PushTableStart(Ui); */
  if (Name) { PushColumn(Ui, CS(Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES); }

  if (Value)
  {
    u32 Start = StartColumn(Ui, EDITOR_UI_FUNCTION_INSTANCE_NAMES);
    PushTableStart(Ui);
    DoEditorUi(Ui, &Value->E[0], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[1], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[2], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    PushTableEnd(Ui);
    /* PushNewRow(Ui); */
    EndColumn(Ui, Start);
  }
  /* PushTableEnd(Ui); */

  PushNewRow(Ui);
}
link_internal void
DoEditorUi(renderer_2d *Ui, v3 *Value, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS, EDITOR_UI_VALUE_RANGE_PROTO_DEFAULTS)
{
  /* PushTableStart(Ui); */
  if (Name) { PushColumn(Ui, CS(Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES); }

  if (Value)
  {
    u32 Start = StartColumn(Ui, EDITOR_UI_FUNCTION_INSTANCE_NAMES);
    PushTableStart(Ui);
    DoEditorUi(Ui, &Value->E[0], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[1], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[2], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    PushTableEnd(Ui);
    /* PushNewRow(Ui); */
    EndColumn(Ui, Start);
  }
  /* PushTableEnd(Ui); */

  PushNewRow(Ui);
}
link_internal void
DoEditorUi(renderer_2d *Ui, v2 *Value, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS, EDITOR_UI_VALUE_RANGE_PROTO_DEFAULTS)
{
  /* PushTableStart(Ui); */
  if (Name) { PushColumn(Ui, CS(Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES); }

  if (Value)
  {
    u32 Start = StartColumn(Ui, EDITOR_UI_FUNCTION_INSTANCE_NAMES);
    PushTableStart(Ui);
    DoEditorUi(Ui, &Value->E[0], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[1], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    PushTableEnd(Ui);
    /* PushNewRow(Ui); */
    EndColumn(Ui, Start);
  }
  /* PushTableEnd(Ui); */

  PushNewRow(Ui);
}
link_internal void
DoEditorUi(renderer_2d *Ui, Quaternion *Value, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS, EDITOR_UI_VALUE_RANGE_PROTO_DEFAULTS)
{
  /* PushTableStart(Ui); */
  if (Name) { PushColumn(Ui, CS(Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES); }

  if (Value)
  {
    u32 Start = StartColumn(Ui, EDITOR_UI_FUNCTION_INSTANCE_NAMES);
    PushTableStart(Ui);
    DoEditorUi(Ui, &Value->E[0], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[1], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[2], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    DoEditorUi(Ui, &Value->E[3], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
    PushTableEnd(Ui);
    /* PushNewRow(Ui); */
    EndColumn(Ui, Start);
  }
  /* PushTableEnd(Ui); */

  PushNewRow(Ui);
}

