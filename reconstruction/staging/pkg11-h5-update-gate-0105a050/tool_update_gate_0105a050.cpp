#include "tool_update_gate_0105a050.hpp"

#if defined(_MSC_VER)
#define PKG11H5_THISCALL __thiscall
#define PKG11H5_CDECL __cdecl
#else
#define PKG11H5_THISCALL __attribute__((thiscall))
#define PKG11H5_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg11_h5_update_gate_0105a050 {

NativePorts g_tool_update_gate_0105a050_ports{};

extern "C" bool PKG11H5_THISCALL func_0105a050(OpaqueToolState* tool_state,
                                               TargetWord mode_word,
                                               TargetWord selector,
                                               TargetWord unused_slot) {
  (void)unused_slot;
  NativePorts& ports = g_tool_update_gate_0105a050_ports;

  if (!ports.mode_update_010593e0(tool_state, mode_word, selector,
                                  kForwardedImmediate)) {
    return false;
  }

  if (!(ports.active_time_0104bdb0(tool_state) > 0.0f)) {
    return true;
  }

  OpaqueToolSubject* const subject = tool_state->owned_subject_124;
  if (subject == nullptr) {
    return true;
  }

  if (!ports.subject_live_00cb5ba0(subject) && subject->flag_16c == 0 &&
      subject->flag_16d == 0) {
    return true;
  }

  if (!ports.tool_gate_0104cd40(tool_state)) {
    return true;
  }

  TrailEnds ends;
  ports.subject_trail_ends_00cb8ba0(subject, &ends.first, &ends.last);

  const float reach = ports.active_time_0104bdb0(tool_state);
  ports.axis_snap_00bbec40(ports.root_accessor_00b3d430(), &ends.last, reach);

  return true;
}

bool tool_update_gate_0105a050_model(OpaqueToolState* tool_state,
                                     TargetWord mode_word, TargetWord selector,
                                     TargetWord unused_slot) {
  return func_0105a050(tool_state, mode_word, selector, unused_slot);
}

}

#undef PKG11H5_THISCALL
#undef PKG11H5_CDECL
