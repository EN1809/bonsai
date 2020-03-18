
    function counted_string
    ToString( metaprogramming_directive Type)
    {
      counted_string Result = {};
      switch (Type)
      {
        
            case meta_directive_noop: { Result = CSz("meta_directive_noop"); } break;

            case generate_cursor_deprecated: { Result = CSz("generate_cursor_deprecated"); } break;

            case enum_only: { Result = CSz("enum_only"); } break;

            case d_union: { Result = CSz("d_union"); } break;

            case for_all_datatypes: { Result = CSz("for_all_datatypes"); } break;

            case named_list: { Result = CSz("named_list"); } break;

            case func: { Result = CSz("func"); } break;

      }
      return Result;
    }
