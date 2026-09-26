#include "simulator_safe_wave11.hpp"

namespace openspore::reconstruction::pkg_simulator_safe_wave11 {
namespace {

constexpr TargetByte kAcceptedByte = 0x01u;
constexpr TargetWord kFallbackKey00628450 = 0xe18d6423u;
constexpr TargetWord kRandomRange006286a0 = 6u;
constexpr TargetWord kCandidate006286a0_0 = 0x0431df93u;
constexpr TargetWord kCandidate006286a0_1 = 0x0431df9au;
constexpr TargetWord kCandidate006286a0_2 = 0x0431df9fu;
constexpr TargetWord kCandidate006286a0_3 = 0x0431dfa6u;
constexpr TargetWord kCandidate006286a0_4 = 0x044d798cu;
constexpr TargetWord kCandidate006286a0_5 = 0x044d7999u;

template <typename Slot>
Slot load_slot(TargetWord raw) {
  return reinterpret_cast<Slot>(static_cast<std::uintptr_t>(raw));
}

OpaqueObject00628* PKG_SIMULATOR_SAFE_WAVE11_CDECL default_provider_0067ddd0() {
  return nullptr;
}

TargetWord PKG_SIMULATOR_SAFE_WAVE11_THISCALL
default_random_00a68fb0(TargetWord* state, TargetWord range) {
  const std::uint64_t product =
      static_cast<std::uint64_t>(*state) * 0x41c64e6du + 0x3039u;
  const TargetWord low = static_cast<TargetWord>(product);
  const TargetWord high = static_cast<TargetWord>(product >> 32);
  *state = low;
  const TargetWord folded =
      static_cast<TargetWord>(low >> 16) | static_cast<TargetWord>(high << 16);
  return static_cast<TargetWord>((static_cast<std::uint64_t>(folded) * range) >>
                                 32);
}

TargetByte PKG_SIMULATOR_SAFE_WAVE11_THISCALL
default_release_0062c340(OpaqueEditor00628*) {
  return 0u;
}

}  // namespace

SimulatorRuntime00628& simulator_runtime_00628() {
  static SimulatorRuntime00628 runtime{default_provider_0067ddd0,
                                       default_random_00a68fb0,
                                       default_release_0062c340, nullptr, 0u};
  return runtime;
}

void PKG_SIMULATOR_SAFE_WAVE11_CDECL
dispatch_key_00628450(OpaqueObject00628* subject, TargetWord key, TargetWord,
                      TargetWord context) {
  if (subject == nullptr) {
    OpaqueObject00628* const provider =
        simulator_runtime_00628().provider_0067ddd0();
    const Slot005c00628 acquire =
        load_slot<Slot005c00628>(provider->vtable->slot_5c);
    subject = acquire(provider);
  }
  const Slot000800628 dispatch =
      load_slot<Slot000800628>(subject->vtable->slot_08);
  const TargetByte outcome = dispatch(subject, key, 0u, context);
  if (outcome != kAcceptedByte) {
    dispatch(subject, kFallbackKey00628450, 0u, context);
  }
}

TargetWord PKG_SIMULATOR_SAFE_WAVE11_THISCALL
cycle_key_006286a0(OpaqueEditor00628* subject) {
  SimulatorRuntime00628& runtime = simulator_runtime_00628();
  // 0x006286a0 pushes ECX and reads it straight back with MOV ESI,[ESP+4], so
  // the seeded id is the receiver itself and there is no stack argument.
  TargetWord candidate =
      static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(subject));
  for (;;) {
    switch (runtime.random_00a68fb0(&runtime.random_state_01601760,
                                    kRandomRange006286a0)) {
      case 0u:
        candidate = kCandidate006286a0_0;
        break;
      case 1u:
        candidate = kCandidate006286a0_1;
        break;
      case 2u:
        candidate = kCandidate006286a0_2;
        break;
      case 3u:
        candidate = kCandidate006286a0_3;
        break;
      case 4u:
        candidate = kCandidate006286a0_4;
        break;
      case 5u:
        candidate = kCandidate006286a0_5;
        break;
      default:
        break;
    }
    if (subject->state_36d4 != candidate) {
      break;
    }
  }
  subject->state_36d4 = candidate;
  return candidate;
}

void PKG_SIMULATOR_SAFE_WAVE11_THISCALL
release_child_0062c910(OpaqueEditor00628* subject) {
  OpaqueObject00628* const held_94 = subject->field_94;
  if (held_94 != nullptr) {
    subject->field_94 = nullptr;
    const Slot000400628 destroy =
        load_slot<Slot000400628>(held_94->vtable->slot_04);
    destroy(held_94);
  }

  if (subject->field_c8 != nullptr) {
    (void)simulator_runtime_00628().release_0062c340(subject);
  }

  OpaqueObject00628* const held_cc = subject->field_cc;
  const Slot000800628n0 release_cc =
      load_slot<Slot000800628n0>(held_cc->vtable->slot_08);
  release_cc(held_cc);
  subject->field_cc = nullptr;

  OpaqueBlend00628* const blend = &subject->field_3588;
  const Slot000800628n0 release_blend =
      load_slot<Slot000800628n0>(blend->vtable->slot_08);
  release_blend(reinterpret_cast<OpaqueObject00628*>(blend));

  OpaqueObject00628* const held_global =
      simulator_runtime_00628().global_015f7cf4;
  if (held_global != nullptr) {
    simulator_runtime_00628().global_015f7cf4 = nullptr;
    const Slot000800628n0 release_global =
        load_slot<Slot000800628n0>(held_global->vtable->slot_08);
    release_global(held_global);
  }

  // 0x0062c977..0x0062c988 is pop edi; pop esi; jmp edx, so the last release
  // is a real tail call: the destroy is the epilogue and nothing follows it.
  OpaqueObject00628* const held_0c = subject->field_0c;
  if (held_0c != nullptr) {
    subject->field_0c = nullptr;
    const Slot000400628 destroy =
        load_slot<Slot000400628>(held_0c->vtable->slot_04);
    destroy(held_0c);
  }
}

}  // namespace openspore::reconstruction::pkg_simulator_safe_wave11
