// Target 0x007d9410 - App::cMouseCamera::OnKeyDown
// See mouse_camera_on_key_down_007d9410.hpp for the machine evidence and for
// what this package deliberately does not claim.
//
// The entry is two instructions. The whole reconstruction of it is: rewind the
// incoming receiver word by four bytes, transfer control to 0x007d9bb0 without
// building a frame, and hand the caller whatever word that transfer leaves in
// the return register.

#include "mouse_camera_on_key_down_007d9410.hpp"

#if defined(_MSC_VER)
#define PKG_MCKD_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_MCKD_THISCALL __attribute__((thiscall))
#else
#error "pkg-app-mouse-camera-keydown requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_app_mouse_camera_keydown {

TailTargetPort g_tail_target_007d9bb0 = nullptr;
EntryTrace g_entry_trace_007d9410 = EntryTrace{};

// 007d9410  83 e9 04  SUB ECX,0x4
//
// Unconditional, and the only arithmetic the complete listing performs. The
// listing holds no conditional branch, so no input is special: a zero word is
// rewound like any other and wraps. Exposed as a word operation because the
// pointer the entry receives is only ever a carrier for the word.
OpaqueWord rewind_receiver_007d9410(OpaqueWord receiver) {
  return receiver - 0x4u;
}

namespace {

// The incoming receiver is a word in a register; nothing more about it is
// observed, so it is carried as a word.
OpaqueWord to_word(const void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The entry's only transfer, modelled as a boundary rather than as a call.
//
// Three properties of the machine drive this shape. The transfer is a jump and
// not a call, so nothing the target does can come back here. The entry pushed
// nothing before transferring, so the target finds the caller's frame exactly
// as the caller left it and no cleanup belongs to this entry. And the entry
// never writes the return register, so the return word is the target's, adopted
// unchanged.
//
// The trace is filled in here rather than in the entry so that the entry's own
// span stays exactly the two machine operations and nothing else.
OpaqueWord tail_transfer_007d9bb0(OpaqueWord receiver, OpaqueWord argument) {
  TailTransferBoundary boundary;
  boundary.receiver = receiver;
  boundary.argument = argument;
  boundary.entry_frame_words = 0u;
  boundary.eax = 0u;

  g_entry_trace_007d9410.transfers += 1u;
  g_entry_trace_007d9410.target_va = kTailTargetVa;
  g_entry_trace_007d9410.receiver = receiver;
  g_entry_trace_007d9410.argument = argument;
  g_entry_trace_007d9410.entry_frame_words = boundary.entry_frame_words;
  g_entry_trace_007d9410.branched = false;
  g_entry_trace_007d9410.completed = true;

  if (g_tail_target_007d9bb0 != nullptr) {
    g_tail_target_007d9bb0(&boundary);
  }

  g_entry_trace_007d9410.observed_eax = boundary.eax;
  return boundary.eax;
}

}  // namespace

extern "C" bool PKG_MCKD_THISCALL on_key_down_007d9410(
    OpaqueListenerSubobject* listener, OpaqueWord argument) {
  // 007d9410  83 e9 04  SUB ECX,0x4
  const OpaqueWord adjusted = rewind_receiver_007d9410(to_word(listener));
  // 007d9413  e9 98 07 00 00  JMP 0x007d9bb0
  // A tail jump to the one direct target: no frame, no cleanup, no return of
  // this body's own.
  const OpaqueWord forwarded = tail_transfer_007d9bb0(adjusted, argument);
  // The declaration-site return type is bool, so the word the transfer target
  // leaves is narrowed the way a 32-bit return register is narrowed to bool.
  return forwarded != 0u;
}

}  // namespace openspore::reconstruction::pkg_app_mouse_camera_keydown

#undef PKG_MCKD_THISCALL
