#include "app_wave10.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_app_wave10 {
namespace {

#if defined(_MSC_VER)
#define PKG_APP_WAVE10_THISCALL __thiscall
#else
#define PKG_APP_WAVE10_THISCALL __attribute__((thiscall))
#endif

constexpr TargetWord kElementStride = 0x18u;
constexpr TargetWord kPropertyFlagStorageMask = 0x0030u;
constexpr TargetHalf kPropertyKindBool = 0x0001u;
constexpr TargetHalf kPropertyKindVoid = 0x0010u;
constexpr TargetSignedWord kExpandThreshold = 2;
constexpr TargetWord kPairedSlotCount = 6u;
constexpr TargetWord kPairStride = 0x08u;
constexpr TargetWord kHandlePayloadOffset = 0x0cu;
constexpr TargetWord kResolveKey = 0x004c6ba3cu;
constexpr TargetWord kVerifyKey = 0x026cd3c9u;
constexpr TargetWord kTokenKey = 0x011ac1acu;
constexpr TargetWord kJobTag = 0x2f4e681cu;
constexpr TargetWord kStampMask = 0xffff00ffu;
constexpr TargetWord kStampBody = 0x00002900u;
constexpr TargetWord kStampSelectorMask = 0xffffff00u;
constexpr TargetWord kDispatchKey = 0x052deb9eu;
constexpr std::uintptr_t kVerifyOwnerGlobal = 0x015fd918u;
constexpr std::uintptr_t kSentinel = 0x015d115du;

TargetWord payload_of(std::uintptr_t handle) {
  return handle == 0u ? 0u
                      : static_cast<TargetWord>(handle + kHandlePayloadOffset);
}

TargetWord stamp_word(TargetWord source, TargetWord selector) {
  const TargetWord blended = (source & kStampMask) | kStampBody;
  return (blended & kStampSelectorMask) | (selector & 0xffu);
}

TargetWord pair_table_extra(const OpaqueFieldRun* run) {
  TargetWord value = 0;
  std::memcpy(&value, run->opaque_40_4f.data(), sizeof(value));
  return value;
}

TargetWord PKG_APP_WAVE10_THISCALL default_emit_element(void*, TargetWord) {
  return 0u;
}

void PKG_APP_WAVE10_THISCALL default_grow_and_emit(OpaqueCursorBuffer*,
                                                   TargetWord, TargetWord) {}

void default_read_field(void*, TargetWord*, TargetWord, TargetWord) {}

void default_read_flag(void*, TargetByte*) {}

void default_prepare_source(void*, void*) {}

void PKG_APP_WAVE10_THISCALL default_bind_pair_table(OpaquePairTable*,
                                                     OpaqueModelQuery*,
                                                     TargetWord) {}

void PKG_APP_WAVE10_THISCALL default_reserve_pair_slots(OpaquePairTable*,
                                                        TargetWord) {}

void PKG_APP_WAVE10_THISCALL default_release_entry(void*) {}

void default_resolve_enum(TargetWord, TargetWord, TargetWord*) {}

bool PKG_APP_WAVE10_THISCALL default_resolve_bool(void*, TargetWord) {
  return false;
}

TargetWord default_acquire_token(TargetWord, TargetWord) { return 0u; }

void default_submit_resolve(TargetWord, TargetWord, TargetWord, TargetWord*) {}

TargetByte default_submit_graphics_job(TargetWord, OpaqueJobDescriptor*,
                                       TargetWord) {
  return 0u;
}

OpaqueModelService* default_model_service() { return nullptr; }

OpaqueFactoryService* default_factory_service() { return nullptr; }

OpaqueRenderService* default_render_service() { return nullptr; }

OpaqueAppService* default_app_service() { return nullptr; }

#undef PKG_APP_WAVE10_THISCALL

}

CursorRuntime& cursor_runtime() {
  static CursorRuntime runtime{default_emit_element, default_grow_and_emit};
  return runtime;
}

RecordRuntime& record_runtime() {
  static RecordRuntime runtime{default_read_field, default_read_flag,
                               default_prepare_source, default_bind_pair_table,
                               default_reserve_pair_slots};
  return runtime;
}

RenderRuntime& render_runtime() {
  static RenderRuntime runtime{
      default_release_entry,  default_resolve_enum,
      default_resolve_bool,   default_acquire_token,
      default_submit_resolve, default_submit_graphics_job,
      default_model_service,  default_factory_service,
      default_render_service, default_app_service};
  return runtime;
}

const TargetByte* property_value_sentinel() {
  return reinterpret_cast<const TargetByte*>(kSentinel);
}

OpaqueVector3* vector3_add(OpaqueVector3* destination,
                           const OpaqueVector3* left,
                           const OpaqueVector3* right) {
  const TargetFloat sum_x = left->x + right->x;
  const TargetFloat sum_y = left->y + right->y;
  const TargetFloat sum_z = left->z + right->z;
  destination->x = sum_x;
  destination->y = sum_y;
  destination->z = sum_z;
  return destination;
}

#if defined(_MSC_VER)
#define PKG_APP_WAVE10_THISCALL __thiscall
#else
#define PKG_APP_WAVE10_THISCALL __attribute__((thiscall))
#endif

void PKG_APP_WAVE10_THISCALL cursor_buffer_emit(OpaqueCursorBuffer* buffer,
                                                TargetWord argument) {
  if (buffer->cursor < buffer->limit) {
    auto* const element = reinterpret_cast<TargetByte*>(
        static_cast<std::uintptr_t>(buffer->cursor));
    buffer->cursor = buffer->cursor + kElementStride;
    if (element != nullptr) {
      static_cast<void>(cursor_runtime().emit_element(element, argument));
    }
    return;
  }
  cursor_runtime().grow_and_emit(buffer, buffer->cursor, argument);
}

const TargetByte* PKG_APP_WAVE10_THISCALL
property_value_resolve(const OpaquePropertyValueSlot* slot) {
  const TargetHalf kind = slot->kind;
  if (kind == kPropertyKindBool || kind == kPropertyKindVoid) {
    if ((slot->flags & kPropertyFlagStorageMask) != 0) {
      TargetWord stored = 0;
      std::memcpy(&stored, slot->data.data(), sizeof(stored));
      return reinterpret_cast<const TargetByte*>(
          static_cast<std::uintptr_t>(stored));
    }
    if (kind != 0) {
      return reinterpret_cast<const TargetByte*>(
          reinterpret_cast<std::uintptr_t>(slot));
    }
    return nullptr;
  }
  return property_value_sentinel();
}

void record_field_run_load(OpaqueSourceService* source, OpaqueFieldRun* run,
                           TargetSignedWord shape) {
  RecordRuntime& runtime = record_runtime();
  runtime.prepare_source(source, &run->head);
  for (TargetWord index = 0; index < kPairedSlotCount; ++index) {
    runtime.read_field(source, &run->cells[index], 1u, 0u);
  }
  source->vtable->reserve_30(source, run->opaque_30_37.data(), 8u);
  for (TargetWord index = 0; index < 4u; ++index) {
    runtime.read_flag(source, &run->opaque_38_3b[index]);
  }
  if (shape < kExpandThreshold) {
    runtime.bind_pair_table(run->table, run->table->begin,
                            pair_table_extra(run));
    run->tail = 0u;
    return;
  }
  TargetWord count = 0;
  runtime.read_field(source, &count, 1u, 0u);
  runtime.reserve_pair_slots(run->table, count);
  const auto base = static_cast<TargetWord>(
      reinterpret_cast<std::uintptr_t>(run->table->begin));
  for (TargetSignedWord index = 0; index < static_cast<TargetSignedWord>(count);
       ++index) {
    const TargetWord low = base + static_cast<TargetWord>(index) * kPairStride;
    const TargetWord high = low + 4u;
    runtime.read_field(
        source, reinterpret_cast<TargetWord*>(static_cast<std::uintptr_t>(low)),
        1u, 0u);
    runtime.read_field(
        source,
        reinterpret_cast<TargetWord*>(static_cast<std::uintptr_t>(high)), 1u,
        0u);
  }
  runtime.read_flag(source, &run->tail);
}

TargetByte PKG_APP_WAVE10_THISCALL
render_host_select(OpaqueRenderHost* host, const OpaqueSelection* selection) {
  RenderRuntime& runtime = render_runtime();
  const TargetWord requested = selection->index;
  TargetWord kind = 0u;
  runtime.resolve_enum(host->resolver, kResolveKey, &kind);

  OpaqueModelQuery query_bc{0xffffffffu, 0xffffffffu};
  OpaqueModelQuery query_b8{0xffffffffu, 0xffffffffu};
  OpaqueModelQuery query_b4{0xffffffffu, 0xffffffffu};

  OpaqueModelService* const model_bc = runtime.model_service();
  model_bc->vtable->query_bc(model_bc, &query_bc);
  OpaqueFactoryService* const factory_bc = runtime.factory_service();
  const TargetWord slot_bc = factory_bc->vtable->resolve_1c(
      factory_bc, query_bc.first, query_bc.second);
  static_cast<void>(slot_bc);

  OpaqueModelService* const model_b8 = runtime.model_service();
  model_b8->vtable->query_b8(model_b8, &query_b8);
  OpaqueFactoryService* const factory_b8 = runtime.factory_service();
  const TargetWord slot_b8 = factory_b8->vtable->resolve_1c(
      factory_b8, query_b8.first, query_b8.second);

  OpaqueModelService* const model_b4 = runtime.model_service();
  model_b4->vtable->query_b4(model_b4, &query_b4);
  OpaqueFactoryService* const factory_b4 = runtime.factory_service();
  const TargetWord slot_b4 = factory_b4->vtable->resolve_1c(
      factory_b4, query_b4.first, query_b4.second);

  OpaqueTriple group_two{};
  OpaqueTriple group_four{};
  OpaqueTriple group_three{};

  OpaqueModelService* const model_two = runtime.model_service();
  model_two->vtable->query_ec(model_two, 2u, &group_two);
  OpaqueModelService* const model_four = runtime.model_service();
  model_four->vtable->query_ec(model_four, 4u, &group_four);
  OpaqueModelService* const model_three = runtime.model_service();
  model_three->vtable->query_ec(model_three, 3u, &group_three);

  const TargetWord value_two = group_two.slots[0];
  const TargetWord value_four = group_four.slots[0];
  const TargetWord value_three = group_three.slots[0];

  TargetWord selector = 0u;
  if (kind == value_four) {
    selector = 1u;
  } else if (kind == value_three) {
    selector = 2u;
  }

  const TargetWord packed = stamp_word(host->stamp, selector);

  TargetWord handle = 0u;
  const TargetWord source_payload =
      payload_of(reinterpret_cast<std::uintptr_t>(host->source_handle));
  runtime.submit_resolve(source_payload, host->owner, packed, &handle);

  if (handle != 0u) {
    if (runtime.resolve_bool(reinterpret_cast<void*>(kVerifyOwnerGlobal),
                             kVerifyKey)) {
      OpaqueJobDescriptor descriptor{host->owner, kJobTag, packed};
      const TargetWord holder_payload =
          payload_of(reinterpret_cast<std::uintptr_t>(host->holder));
      const TargetWord token = runtime.acquire_token(kTokenKey, 1u);
      static_cast<void>(
          runtime.submit_graphics_job(holder_payload, &descriptor, token));
      OpaqueRenderService* const adopt_render = runtime.render_service();
      adopt_render->vtable->adopt_54(adopt_render, handle, 0u);
    }
  }

  OpaqueHolder* const pending = host->holder;
  if (pending != nullptr) {
    host->holder = nullptr;
    if (pending != nullptr) {
      pending->vtable->release_04(pending);
    }
  }

  const bool route_first = (kind == 1u || kind == 2u) && requested == value_two;
  const bool route_second = kind == 2u && requested == value_four;
  const bool route_third = (kind == 0u && requested == value_two) ||
                           (kind == 1u && requested == value_four) ||
                           (kind == 2u && requested == value_three);

  if (route_first) {
    OpaqueRenderService* const render = runtime.render_service();
    render->vtable->submit_5c(render, slot_b8, 0u, 1u, 0u);
  } else if (route_second) {
    OpaqueRenderService* const render = runtime.render_service();
    render->vtable->submit_5c(render, slot_b4, 0u, 1u, 0u);
  } else if (route_third) {
    OpaqueAppService* const app = runtime.app_service();
    app->vtable->dispatch_14(app, kDispatchKey, 0u, 0u);
  }

  TargetByte outcome = 1u;
  if (handle != 0u) {
    runtime.release_entry(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(handle)));
  }
  return outcome;
}

#undef PKG_APP_WAVE10_THISCALL

}
