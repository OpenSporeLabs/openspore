#include "simulator_wave11.hpp"

namespace openspore::reconstruction::pkg_simulator_wave11 {
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
constexpr TargetWord kForwardKey00628af0 = 0x09u;
constexpr TargetWord kAssetKey00628af0 = 0x03f67620u;
constexpr TargetWord kSelectKey00628af0_0 = 0x04581d50u;
constexpr TargetWord kSelectKey00628af0_1 = 0x04581d78u;
constexpr TargetWord kSelectKey00628af0_2 = 0x04581d90u;
constexpr TargetWord kQueryArgument00628af0 = 0x00000000u;
constexpr TargetWord kDirectKey00628af0 = 0x43u;
constexpr TargetWord kDirectArgument00628af0 = 0x03a8ede4u;
constexpr TargetWord kPeerCount00628 = 4u;
constexpr TargetWord kDebugTag00628d50 = 0x0a03e74b2u;
constexpr TargetWord kFlagBit00628d50 = 0x00000001u;
constexpr TargetWord kFlagClear00628d50 = 0xfffffffeu;
constexpr TargetWord kRouteKey00628d50_0 = 0x0445b018u;
constexpr TargetWord kRouteKey00628d50_1 = 0x0445b318u;
constexpr TargetWord kRouteKey00628d50_2 = 0x0445b340u;
constexpr TargetWord kRouteKey00628d50_3 = 0x0445b388u;
constexpr TargetWord kBlendConstant00628d50 = 0x04330667u;
constexpr TargetWord kPostEvent00628d50 = 0x70842ef6u;
constexpr TargetWord kPostEventMask00628d50 = 0xffffffffu;
constexpr TargetWord kSelectionNone00628d50 = 0xffffffffu;
constexpr TargetWord kSelection00628d50_0 = 0x00000000u;
constexpr TargetWord kSelection00628d50_1 = 0x00000001u;
constexpr TargetWord kSelection00628d50_2 = 0x00000002u;
constexpr TargetWord kSelection00628d50_3 = 0x00000003u;
constexpr TargetFloat kPostEventScale00628d50 = 1.0f;
constexpr TargetFloat kPostEventOffset00628d50 = 0.0f;

template <typename Slot>
Slot load_slot(TargetWord raw) {
  return reinterpret_cast<Slot>(static_cast<std::uintptr_t>(raw));
}

OpaqueObject00628 *peer_slot_00628(OpaqueEditor00628 *subject,
                                   TargetWord index) {
  switch (index) {
    case 0u:
      return subject->field_c8;
    case 1u:
      return subject->field_cc;
    case 2u:
      return subject->field_d0;
    default:
      return subject->field_d4;
  }
}

OpaqueObject00628 *PKG_SIMULATOR_WAVE11_CDECL default_provider_0067ddd0() {
  return nullptr;
}

OpaqueObject00628 *PKG_SIMULATOR_WAVE11_CDECL default_view_manager_0067caa0() {
  return nullptr;
}

TargetWord PKG_SIMULATOR_WAVE11_CDECL default_asset_view_00401030() {
  return 0u;
}

OpaqueObject00628 *PKG_SIMULATOR_WAVE11_CDECL default_debug_service_00a206f0() {
  return nullptr;
}

void PKG_SIMULATOR_WAVE11_CDECL default_emit_debug_00435ed0(TargetWord,
                                                            TargetWord) {
}

OpaqueObject00628 *PKG_SIMULATOR_WAVE11_THISCALL
default_resolve_00634e40(OpaqueObject00628 *, TargetWord) {
  return nullptr;
}

TargetWord PKG_SIMULATOR_WAVE11_THISCALL
default_random_00a68fb0(TargetWord *state, TargetWord range) {
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

TargetByte PKG_SIMULATOR_WAVE11_THISCALL
default_submit_0062f7f0(OpaqueQueue00628 *, TargetWord) {
  return 0u;
}

TargetByte PKG_SIMULATOR_WAVE11_THISCALL
default_probe_0062f6c0(OpaqueQueue00628 *) {
  return 0u;
}

TargetByte PKG_SIMULATOR_WAVE11_THISCALL
default_release_0062c340(OpaqueEditor00628 *) {
  return 0u;
}

void PKG_SIMULATOR_WAVE11_THISCALL default_apply_00628ca0(OpaqueEditor00628 *,
                                                          TargetByte) {
}

void PKG_SIMULATOR_WAVE11_THISCALL default_post_event_00574110(
    OpaqueOwner00628 *, TargetWord, TargetWord, TargetFloat, TargetFloat) {
}

void PKG_SIMULATOR_WAVE11_THISCALL default_select_005dbbb0(OpaqueOwner00628 *,
                                                           TargetWord) {
}

bool probe_select_00628af0(OpaqueObject00628 *owner, TargetWord probe_key) {
  SimulatorRuntime00628 &runtime = simulator_runtime_00628();
  OpaqueObject00628 *const manager = runtime.view_manager_0067caa0();
  const Slot004800628 query =
      load_slot<Slot004800628>(manager->vtable->slot_48);
  const OpaqueObject00628 *const current =
      query(manager, kQueryArgument00628af0);
  const OpaqueObject00628 *const resolved =
      runtime.resolve_00634e40(owner, probe_key);
  return current == resolved;
}

void blend_00628d50(OpaqueEditor00628 *subject, TargetWord handle,
                    TargetWord second, TargetWord third, TargetWord fourth,
                    TargetWord fifth) {
  OpaqueBlend00628 *const blend = &subject->field_3588;
  const Slot000c00628 blend_slot =
      load_slot<Slot000c00628>(blend->vtable->slot_0c);
  (void)blend_slot(blend, handle, second, third, fourth, fifth);
}

}  // namespace

SimulatorRuntime00628 &simulator_runtime_00628() {
  static SimulatorRuntime00628 runtime{default_provider_0067ddd0,
                                       default_view_manager_0067caa0,
                                       default_asset_view_00401030,
                                       default_debug_service_00a206f0,
                                       default_emit_debug_00435ed0,
                                       default_resolve_00634e40,
                                       default_random_00a68fb0,
                                       default_submit_0062f7f0,
                                       default_probe_0062f6c0,
                                       default_release_0062c340,
                                       default_apply_00628ca0,
                                       default_post_event_00574110,
                                       default_select_005dbbb0,
                                       nullptr,
                                       0u};
  return runtime;
}

void PKG_SIMULATOR_WAVE11_CDECL
dispatch_key_00628450(OpaqueObject00628 *subject, TargetWord key, TargetWord,
                      TargetWord context) {
  if (subject == nullptr) {
    OpaqueObject00628 *const provider =
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

TargetWord PKG_SIMULATOR_WAVE11_THISCALL
cycle_key_006286a0(OpaqueEditor00628 *subject) {
  SimulatorRuntime00628 &runtime = simulator_runtime_00628();
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

TargetByte PKG_SIMULATOR_WAVE11_THISCALL forward_key_00628af0(
    OpaqueEditor00628 *subject, TargetWord key, TargetWord extra) {
  SimulatorRuntime00628 &runtime = simulator_runtime_00628();
  OpaqueObject00628 *const manager = runtime.view_manager_0067caa0();
  const Slot008400628 prepare =
      load_slot<Slot008400628>(manager->vtable->slot_84);
  prepare(manager);
  (void)runtime.asset_view_00401030();

  if (key == kForwardKey00628af0) {
    OpaqueObject00628 *const asset =
        runtime.resolve_00634e40(subject->field_0c, kAssetKey00628af0);
    if (asset != nullptr) {
      const Slot002800628 asset_probe =
          load_slot<Slot002800628>(asset->vtable->slot_28);
      if ((asset_probe(asset) & 1u) != 0u) {
        OpaqueObject00628 *const owner = subject->field_0c;
        TargetWord action_key = kSelectKey00628af0_0;
        if (probe_select_00628af0(owner, kSelectKey00628af0_0)) {
          action_key = kSelectKey00628af0_1;
        } else if (probe_select_00628af0(owner, kSelectKey00628af0_1)) {
          action_key = kSelectKey00628af0_2;
        } else if (probe_select_00628af0(owner, kSelectKey00628af0_2)) {
          action_key = kSelectKey00628af0_0;
        }
        OpaqueObject00628 *const actor = runtime.view_manager_0067caa0();
        const Slot004c00628 select =
            load_slot<Slot004c00628>(actor->vtable->slot_4c);
        select(actor, kQueryArgument00628af0,
               runtime.resolve_00634e40(owner, action_key));
      }
    }
  }

  if (key == kDirectKey00628af0 && extra == 0u) {
    const Slot002400628n1 direct =
        load_slot<Slot002400628n1>(subject->vtable->slot_24);
    direct(reinterpret_cast<OpaqueObject00628 *>(subject),
           kDirectArgument00628af0);
    return kAcceptedByte;
  }

  TargetByte accumulated = 0u;
  for (TargetWord index = 0u; index < kPeerCount00628; ++index) {
    OpaqueObject00628 *const peer = peer_slot_00628(subject, index);
    if (peer != nullptr) {
      const Slot002400628 route =
          load_slot<Slot002400628>(peer->vtable->slot_24);
      accumulated =
          static_cast<TargetByte>(accumulated | route(peer, key, extra));
    }
  }
  return accumulated;
}

TargetByte PKG_SIMULATOR_WAVE11_THISCALL
route_key_00628d50(OpaqueEditor00628 *subject, TargetWord key) {
  SimulatorRuntime00628 &runtime = simulator_runtime_00628();
  OpaqueQueue00628 *const queue = &subject->field_3618;
  TargetByte accumulated = 0u;

  if (runtime.submit_0062f7f0(queue, key) == 0u) {
    for (TargetWord index = 0u; index < kPeerCount00628; ++index) {
      OpaqueObject00628 *const peer = peer_slot_00628(subject, index);
      const Slot002c00628 route =
          load_slot<Slot002c00628>(peer->vtable->slot_2c);
      accumulated = static_cast<TargetByte>(accumulated | route(peer, key));
    }
    return accumulated;
  }

  TargetWord word_code = 0u;
  OpaqueObject00628 *const service = runtime.debug_service_00a206f0();
  if (service != nullptr) {
    const Slot002000628 read_word =
        load_slot<Slot002000628>(service->vtable->slot_20);
    word_code = read_word(service);
  }
  runtime.emit_debug_00435ed0(kDebugTag00628d50, word_code);

  OpaqueOwner00628 *const owner = subject->field_3614;
  OpaqueFlag00628 *const flag = owner->field_ac;
  if (flag != nullptr) {
    if (runtime.probe_0062f6c0(queue) != 0u) {
      flag->field_04 |= kFlagBit00628d50;
    } else {
      flag->field_04 &= kFlagClear00628d50;
    }
  }

  const TargetByte state = runtime.probe_0062f6c0(queue);
  runtime.apply_00628ca0(subject, state);

  if (key == kRouteKey00628d50_0 || key == kRouteKey00628d50_1 ||
      key == kRouteKey00628d50_2 || key == kRouteKey00628d50_3) {
    const TargetWord cycle = cycle_key_006286a0(subject);
    blend_00628d50(subject, owner->field_364, cycle, 0u, 1u, 0u);
    blend_00628d50(subject, owner->field_364, kBlendConstant00628d50, 1u, 0u,
                   0u);
    runtime.post_event_00574110(owner, kPostEvent00628d50,
                                kPostEventMask00628d50, kPostEventScale00628d50,
                                kPostEventOffset00628d50);

    TargetWord selection = kSelectionNone00628d50;
    if (static_cast<std::int32_t>(key) >
        static_cast<std::int32_t>(kRouteKey00628d50_2)) {
      if (key == kRouteKey00628d50_3) {
        selection = kSelection00628d50_3;
      }
    } else if (key == kRouteKey00628d50_2) {
      selection = kSelection00628d50_2;
    } else if (key == kRouteKey00628d50_0) {
      selection = kSelection00628d50_0;
    } else if (key == kRouteKey00628d50_1) {
      selection = kSelection00628d50_1;
    }
    if (selection != kSelectionNone00628d50) {
      runtime.select_005dbbb0(owner, selection);
    }
  }

  return kAcceptedByte;
}

void PKG_SIMULATOR_WAVE11_THISCALL
release_child_0062c910(OpaqueEditor00628 *subject) {
  OpaqueObject00628 *const held_94 = subject->field_94;
  if (held_94 != nullptr) {
    subject->field_94 = nullptr;
    const Slot000400628 destroy =
        load_slot<Slot000400628>(held_94->vtable->slot_04);
    destroy(held_94);
  }

  if (subject->field_c8 != nullptr) {
    (void)simulator_runtime_00628().release_0062c340(subject);
  }

  OpaqueObject00628 *const held_cc = subject->field_cc;
  const Slot000800628n0 release_cc =
      load_slot<Slot000800628n0>(held_cc->vtable->slot_08);
  release_cc(held_cc);
  subject->field_cc = nullptr;

  OpaqueBlend00628 *const blend = &subject->field_3588;
  const Slot000800628n0 release_blend =
      load_slot<Slot000800628n0>(blend->vtable->slot_08);
  release_blend(reinterpret_cast<OpaqueObject00628 *>(blend));

  OpaqueObject00628 *const held_global =
      simulator_runtime_00628().global_015f7cf4;
  if (held_global != nullptr) {
    simulator_runtime_00628().global_015f7cf4 = nullptr;
    const Slot000800628n0 release_global =
        load_slot<Slot000800628n0>(held_global->vtable->slot_08);
    release_global(held_global);
  }

  // 0x0062c977..0x0062c988 is pop edi; pop esi; jmp edx, so the last release
  // is a real tail call: the destroy is the epilogue and nothing follows it.
  OpaqueObject00628 *const held_0c = subject->field_0c;
  if (held_0c != nullptr) {
    subject->field_0c = nullptr;
    const Slot000400628 destroy =
        load_slot<Slot000400628>(held_0c->vtable->slot_04);
    destroy(held_0c);
  }
}

}  // namespace openspore::reconstruction::pkg_simulator_wave11
