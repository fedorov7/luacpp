#pragma once

namespace lua {
  namespace type_policy {
    template <typename T>
    struct boolean {
      // Booleans are ints in Lua
      typedef int write_type;
      typedef T read_type;
      
      inline static bool type_matches(::lua::state s, int idx) {
        return s.isboolean(idx);
      }
    
      inline static read_type get_unsafe(::lua::state s, int idx) {
        return s.toboolean(idx);
      }

      inline static read_type get(::lua::state s, int idx) {
        if (type_matches(s, idx)) {
          return get_unsafe(s, idx);
        }
      }

      template <typename F>
      inline static void apply(::lua::state s, int idx, F f) {
        if (type_matches(s, idx)) {
          f(s, idx);
        }
      }

      inline static void set(::lua::state s, int idx, T value) {
        s.pushboolean(write_type(value));
        if (idx != 0) s.replace(idx);
      }
    };
  
  }
  
  template <>
  struct get_type_policy<bool> {
    typedef type_policy::boolean<bool> value;
  };

  template <>
  struct get_type_policy<const bool> {
    typedef type_policy::boolean<const bool> value;
  };
}
