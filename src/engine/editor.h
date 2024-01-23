#define EDITOR_UI_VALUE_RANGE_PROTO_DEFAULTS r32 MinValue = 0.f, r32 MaxValue = 1.f
#define EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES MinValue, MaxValue

poof(
  func do_editor_ui_for_vector_type(type_poof_symbol type_list)
  {
    type_list.map(type)
    {
      link_internal void
      DoEditorUi(renderer_2d *Ui, window_layout *Window, type.name *Value, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS, EDITOR_UI_VALUE_RANGE_PROTO_DEFAULTS)
      {
        type.member(0, (E) 
        {
          /* PushTableStart(Ui); */
            if (Name) { PushColumn(Ui, CS(Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES); }

            if (Value)
            {
              u32 Start = StartColumn(Ui, EDITOR_UI_FUNCTION_INSTANCE_NAMES);
                PushTableStart(Ui);
                  E.map_array(e_index)
                  {
                    DoEditorUi(Ui, Window, &Value->(E.name)[e_index], {}, EDITOR_UI_FUNCTION_INSTANCE_NAMES, EDITOR_UI_VALUE_RANGE_INSTANCE_NAMES );
                  }
                PushTableEnd(Ui);
                /* PushNewRow(Ui); */
              EndColumn(Ui, Start);
            }
          /* PushTableEnd(Ui); */
        })
        PushNewRow(Ui);
      }
    }
  }
)

poof(
  func do_editor_ui_for_primitive_type(type_poof_symbol type_list)
  {
    type_list.map(type)
    {
      link_internal void
      DoEditorUi(renderer_2d *Ui, window_layout *Window, type.name *Value, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS, EDITOR_UI_VALUE_RANGE_PROTO_DEFAULTS)
      {
        if (Name) { PushColumn(Ui,    Name, EDITOR_UI_FUNCTION_INSTANCE_NAMES); }

        if (Value)
        {
          u32 Start = StartColumn(Ui, EDITOR_UI_FUNCTION_INSTANCE_NAMES);
            PushTableStart(Ui);
              if (Button(Ui, CSz("-"), UiId(Window, "decrement", Value), EDITOR_UI_FUNCTION_INSTANCE_NAMES)) { *Value = *Value - 1; }
                  PushColumn(Ui, CS(*Value), EDITOR_UI_FUNCTION_INSTANCE_NAMES);
              if (Button(Ui, CSz("+"), UiId(Window, "increment", Value), EDITOR_UI_FUNCTION_INSTANCE_NAMES)) { *Value = *Value + 1; }
            PushTableEnd(Ui);
          EndColumn(Ui, Start);
        }
        else
        {
          PushColumn(Ui, CSz("(null)"), EDITOR_UI_FUNCTION_INSTANCE_NAMES);
          PushNewRow(Ui);
        }

      }

      link_internal void
      DoEditorUi(renderer_2d *Ui, window_layout *Window, volatile type.name *Value, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS)
      {
        DoEditorUi(Ui, Window, ((type.name)*) Value, Name, EDITOR_UI_FUNCTION_INSTANCE_NAMES);
      }

    }
  }
)

poof(
  func do_editor_ui_for_compound_type(type)
  {
    link_internal void
    DoEditorUi(renderer_2d *Ui, window_layout *Window, type.name *Element, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS)
    {
      if (Element)
      {
        if (ToggleButton(Ui, FSz("v %S", Name), FSz("> %S", Name), UiId(Window, "toggle type.name", Element), EDITOR_UI_FUNCTION_INSTANCE_NAMES))
        {
          PushNewRow(Ui);

          PushTableStart(Ui);
          PushForceUpdateBasis(Ui, V2(20.f, 0.f));
            type.map(member)
            {
              member.has_tag(ui_skip)?
              {
              }
              {
                member.is_array?
                {
                  if (ToggleButton(Ui, CSz("v member.type member.name[member.array]"), CSz("> member.type member.name[member.array]"), UiId(Window, "toggle type.name member.type member.name", Element->(member.name)), EDITOR_UI_FUNCTION_INSTANCE_NAMES ))
                  {
                    PushForceUpdateBasis(Ui, V2(20.f, 0.f));
                      PushNewRow(Ui);
                      RangeIterator(ArrayIndex, member.array)
                      {
                        DoEditorUi(Ui, Window, Element->(member.name)+ArrayIndex, FSz("member.type member.name[%d]", ArrayIndex), EDITOR_UI_FUNCTION_INSTANCE_NAMES);
                        member.is_primitive?  { PushNewRow(Ui); }
                      }
                    PushForceUpdateBasis(Ui, V2(-20.f, 0.f));
                  }
                  PushNewRow(Ui);
                }
                {
                  member.is_pointer?
                  {
                    DoEditorUi(Ui, Window, Element->(member.name), CSz("member.type member.name"), EDITOR_UI_FUNCTION_INSTANCE_NAMES);
                  }
                  {
                    member.has_tag(ui_value_range)?
                    {
                      DoEditorUi(Ui, Window, &Element->(member.name), CSz("member.type member.name"), EDITOR_UI_FUNCTION_INSTANCE_NAMES, member.tag_value(ui_value_range));
                    }
                    {
                      member.has_tag(custom_ui)?
                      {
                        member.tag_value(custom_ui);
                      }
                      {
                        member.is_type(b32)?
                        {
                          DoEditorUi(Ui, Window, Cast(b8*, &Element->(member.name)), CSz("member.type member.name"), EDITOR_UI_FUNCTION_INSTANCE_NAMES);
                        }
                        {
                          DoEditorUi(Ui, Window, &Element->(member.name), CSz("member.type member.name"), EDITOR_UI_FUNCTION_INSTANCE_NAMES);
                        }
                      }
                    }
                  }
                }
              }

              member.is_primitive?
              {
                PushNewRow(Ui);
              }
            }
          PushForceUpdateBasis(Ui, V2(-20.f, 0.f));
          PushTableEnd(Ui);
        }

        PushNewRow(Ui);
      }
      else
      {
        PushColumn(Ui, Name, EDITOR_UI_FUNCTION_INSTANCE_NAMES);
        PushColumn(Ui, CSz("(null)"), EDITOR_UI_FUNCTION_INSTANCE_NAMES);
        PushNewRow(Ui);
      }

    }
  }
)

poof(
  func do_editor_ui_for_enum(enum_t)
  {
    link_internal void
    DoEditorUi(renderer_2d *Ui, window_layout *Window, enum_t.name *Element, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS)
    {
      if (Name) { PushColumn(Ui, CS(Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES); }

      cs ElementName = ToString(*Element);
      if (ToggleButton(Ui, ElementName, ElementName, UiId(Window, "enum value.type value.name", Element), EDITOR_UI_FUNCTION_INSTANCE_NAMES))
      {
        PushNewRow(Ui);
        enum_t.map(value)
        {
          PushColumn(Ui, CSz("")); // Skip the first Name column
          if (Button(Ui, CSz("value.name"), UiId(Window, "enum value.name", Element), EDITOR_UI_FUNCTION_INSTANCE_NAMES))
          {
            enum_t.has_tag(bitfield)?
            {
              if ((*Element & value.name) == value.name)
              {
                *Element = enum_t.name(*Element&~value.name);
              }
              else
              {
                *Element = enum_t.name(*Element|value.name);
              }
            }
            {
              *Element = value.name;
            }
          }
          PushNewRow(Ui);
        }
      }
      else
      {
        PushNewRow(Ui);
      }
    }
  }
)

poof(
  func do_editor_ui_for_container(type)
  {
    link_internal void
    DoEditorUi(renderer_2d *Ui, window_layout *Window, type.name *Container, cs Name, EDITOR_UI_FUNCTION_PROTO_DEFAULTS)
    {
      if (Container)
      {
        if (ToggleButton(Ui, FSz("v %S", Name), FSz("> %S", Name), UiId(Window, Name.Start, Container), EDITOR_UI_FUNCTION_INSTANCE_NAMES))
        {
          PushNewRow(Ui);
          IterateOver(Container, Element, ElementIndex)
          {
            DoEditorUi(Ui, Window, Element, CS(ElementIndex), EDITOR_UI_FUNCTION_INSTANCE_NAMES);
            PushNewRow(Ui);
          }
        }
        PushNewRow(Ui);
      }
      else
      {
        PushColumn(Ui, FSz("%S", Name), EDITOR_UI_FUNCTION_INSTANCE_NAMES);
        PushColumn(Ui, CSz("(null)"), EDITOR_UI_FUNCTION_INSTANCE_NAMES);
      }
    }
  }
)

/* link_internal void */
/* DoEditorUi(renderer_2d *Ui, aabb *Element, cs Name, EDITOR_UI_FUNCTION_PROTO_ARGUMENTS); */

/* link_internal void */
/* DoEditorUi(renderer_2d *Ui, v3i *Element, cs Name, EDITOR_UI_FUNCTION_PROTO_ARGUMENTS); */

struct asset_thumbnail
{
  texture *Texture;
  camera   Camera;
};

poof(block_array_h(asset_thumbnail, {8}))
#include <generated/block_array_h_asset_thumbnail_688856411.h>

struct selection_modification_state
{
  face_index ClickedFace;
  v3 ClickedP[2];
};

enum level_editor_flags
{
  LevelEditorFlags_Noop                              = (1 << 0),
  /* LevelEditorFlags_RecomputeStandingSpotsOnLevelLoad = (1 << 1), */
};

poof(radio_button_group_for_bitfield_enum(level_editor_flags));
#include <generated/radio_button_group_for_bitfield_enum_level_editor_flags.h>

struct level_editor
{
  u64 EngineDebugViewModeToggleBits;

  u16 SelectedColorIndex;
  u16 HoverColorIndex;

  u32 SelectionClicks;
  cp SelectionBase;

  rect3cp SelectionRegion;
  rect3cp CopyRegion;

  // Recorded when accel-clicking on the selection to manipulate it
  selection_modification_state Selection;
  selection_modification_state Entity;

  asset_thumbnail_block_array AssetThumbnails;
};

link_internal b32
SelectionIncomplete(u32 SelectionClicks)
{
  return SelectionClicks == 0 || SelectionClicks == 1;
}

link_internal void
ResetSelection(level_editor *Editor)
{
  Editor->SelectionClicks = 0;
  Editor->SelectionBase = {};
  Editor->SelectionRegion = {};
}

link_internal void
ResetSelectionIfIncomplete(level_editor *Editor)
{
  if (SelectionIncomplete(Editor->SelectionClicks)) { ResetSelection(Editor); }
}

struct maybe_v3
{
  maybe_tag Tag;
  v3 V3;
};

enum selection_mode
{
  SelectionMode_Noop,

  SelectionMode_Resize,
  SelectionMode_TranslateLinear,
  SelectionMode_TranslatePlanar,
};

enum world_edit_mode
{
  WorldEditMode_Select          = (1 << 0),

  WorldEditMode_FillSelection   = (1 << 1),
  WorldEditMode_PaintSelection  = (1 << 2),
  WorldEditMode_DeleteSelection = (1 << 3),

  WorldEditMode_Eyedropper      = (1 << 4),

  WorldEditMode_AddSingle       = (1 << 5),
  WorldEditMode_RemoveSingle    = (1 << 6),
  WorldEditMode_PaintSingle     = (1 << 7),

  WorldEditMode_AssetBrush      = (1 << 8),
  WorldEditMode_BlitEntity      = (1 << 9),

  WorldEditMode_RecomputeStandingSpots = (1 << 10),
};

poof(string_and_value_tables(world_edit_mode))
#include <generated/string_and_value_tables_world_edit_mode.h>

poof(radio_button_group_for_bitfield_enum(world_edit_mode));
#include <generated/radio_button_group_for_bitfield_enum_world_edit_mode.h>
