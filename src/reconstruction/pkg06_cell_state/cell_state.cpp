#include <cstddef>
#include <cstdint>
#include <cstring>

#include "cell_state_abi.hpp"

namespace openspore::reconstruction::pkg06_cell_state {

struct CellObjectData {
  alignas(1) std::byte opaque[920];
};

struct OpaqueCellDirectionPayload;

static_assert(sizeof(CellObjectData) == 920,
              "CellObjectData must preserve the observed object extent");
}  // namespace openspore::reconstruction::pkg06_cell_state

namespace openspore::reconstruction::pkg06_cell_state {
namespace model {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using i32 = std::int32_t;

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-06 staging requires an x86-32 target"
#endif
static_assert(sizeof(void*) == 4, "PKG-06 staging requires 32-bit pointers");
static_assert(sizeof(std::uintptr_t) == 4,
              "PKG-06 staging requires 32-bit target addresses");
static_assert(sizeof(u32) == 4, "PKG-06 target words are 32-bit");
static_assert(sizeof(i32) == 4, "PKG-06 signed target words are 32-bit");
static_assert(sizeof(float) == 4, "PKG-06 target floats are 32-bit");

struct alignas(4) ObservedObjectPool {
  u32 data;
  i32 next_available_index;
  i32 object_pool_identifier;
  i32 object_count;
  i32 allocated_object_count;
  i32 object_size;
  i32 field_18;
};

static_assert(sizeof(ObservedObjectPool) == 28,
              "Object-pool layout must retain its observed 28-byte extent");

struct alignas(4) ObservedStageRecord {
  u32 field_00;
  i32 upper_bound_04;
  std::byte opaque_08[8];
  float scale_10;
  std::byte opaque_14[8];
};

static_assert(sizeof(ObservedStageRecord) == 0x1c,
              "Stage-record stride must remain 0x1c");
static_assert(offsetof(ObservedStageRecord, scale_10) == 0x10,
              "Stage scale must remain at record offset 0x10");

struct ObservedCallbackVtablePrefix {
  std::byte opaque_00[4];
  u32 slot_04;
  u32 opaque_08;
  u32 slot_0c;
  std::byte opaque_10[0x24];
  u32 slot_34;
};

static_assert(offsetof(ObservedCallbackVtablePrefix, slot_04) == 0x04,
              "callback slot moved");
static_assert(offsetof(ObservedCallbackVtablePrefix, slot_0c) == 0x0c,
              "callback slot moved");
static_assert(offsetof(ObservedCallbackVtablePrefix, slot_34) == 0x34,
              "callback slot moved");
static_assert(sizeof(ObservedCallbackVtablePrefix) >= 0x38,
              "callback-vtable prefix must cover the observed 0x38 bytes");

struct OpaqueResourceScope {
  u32 opaque;
};

struct E52a40Stack6 {
  i32 scale;
  i32 adjustment;
  float resource_scale;
  float effect_scale;
  u32 trailing_zero_5;
  u32 trailing_zero_6;
};

static_assert(sizeof(E52a40Stack6) == 24,
              "PKG-06 scale adapter must retain six 32-bit stack slots");

struct ObservedAudioConfig {
  u32 serializable_value_10;
  u32 constant_2f7d0004;
  u32 serializable_value_18;
};

static_assert(sizeof(ObservedAudioConfig) == 12,
              "PKG-06 audio record must retain only three observed fields");

extern std::byte* g_cell_game_016b3c04;
extern std::byte* g_cell_gfx_016b3c08;
extern std::byte* g_cell_ui_016b3c0c;

extern const std::byte g_default_position_016b3c28[12];
extern const std::byte g_default_color_015a7c4c[16];
extern float g_visible_background_bbox_016b3c88;
extern float g_visible_background_bbox_016b3c8c;
extern float g_visible_background_bbox_016b3c90;
extern float g_visible_background_bbox_016b3c94;
extern float g_visible_background_bbox_016b3c98;
extern float g_visible_background_bbox_016b3c9c;

extern const ObservedStageRecord g_stage_table_01483c14[];
extern const ObservedStageRecord g_stage_table_1000_01483e60;
extern const float g_anchor_015a7d3c[3];

std::byte* game_bytes() {
  return reinterpret_cast<std::byte*>(g_cell_game_016b3c04);
}

std::byte* ui_bytes() {
  return reinterpret_cast<std::byte*>(g_cell_ui_016b3c0c);
}

extern u32 g_rollover_ids_016b4178[64];
extern u8 g_rollover_active_016b4278[64];

u8 read_u8(const void* base, std::size_t offset) {
  u8 value;
  std::memcpy(&value, static_cast<const std::byte*>(base) + offset,
              sizeof(value));
  return value;
}

u32 read_u32(const void* base, std::size_t offset) {
  u32 value;
  std::memcpy(&value, static_cast<const std::byte*>(base) + offset,
              sizeof(value));
  return value;
}

i32 read_i32(const void* base, std::size_t offset) {
  i32 value;
  std::memcpy(&value, static_cast<const std::byte*>(base) + offset,
              sizeof(value));
  return value;
}

float read_f32(const void* base, std::size_t offset) {
  float value;
  std::memcpy(&value, static_cast<const std::byte*>(base) + offset,
              sizeof(value));
  return value;
}

void write_u8(void* base, std::size_t offset, u8 value) {
  std::memcpy(static_cast<std::byte*>(base) + offset, &value, sizeof(value));
}

void write_u32(void* base, std::size_t offset, u32 value) {
  std::memcpy(static_cast<std::byte*>(base) + offset, &value, sizeof(value));
}

void write_i32(void* base, std::size_t offset, i32 value) {
  std::memcpy(static_cast<std::byte*>(base) + offset, &value, sizeof(value));
}

void write_f32(void* base, std::size_t offset, float value) {
  std::memcpy(static_cast<std::byte*>(base) + offset, &value, sizeof(value));
}

void copy_bytes(void* destination, std::size_t destination_offset,
                const void* source, std::size_t source_offset,
                std::size_t size) {
  std::memcpy(static_cast<std::byte*>(destination) + destination_offset,
              static_cast<const std::byte*>(source) + source_offset, size);
}

ObservedObjectPool* cell_pool(CellObjectData*) {
  return reinterpret_cast<ObservedObjectPool*>(game_bytes() + 0x1c);
}

ObservedObjectPool* effect_pool() {
  return reinterpret_cast<ObservedObjectPool*>(game_bytes() + 0x54);
}

ObservedObjectPool* game_pool_38() {
  return reinterpret_cast<ObservedObjectPool*>(game_bytes() + 0x38);
}

ObservedObjectPool* game_pool_8c() {
  return reinterpret_cast<ObservedObjectPool*>(game_bytes() + 0x8c);
}

ObservedObjectPool* game_pool_a8() {
  return reinterpret_cast<ObservedObjectPool*>(game_bytes() + 0xa8);
}

u32 cell_index(const CellObjectData* cell) { return read_u32(cell, 0x000); }

CellResourceRef* cell_resource(const CellObjectData* cell) {
  return reinterpret_cast<CellResourceRef*>(
      static_cast<std::uintptr_t>(read_u32(cell, 0x108)));
}

const void* cell_address(const CellObjectData* cell, std::size_t offset) {
  return reinterpret_cast<const std::byte*>(cell) + offset;
}

void* cell_address(CellObjectData* cell, std::size_t offset) {
  return reinterpret_cast<std::byte*>(cell) + offset;
}

struct MachineAbiAdapters {
  // RE: native object-pool accessors use ECX for the pool receiver. The
  // indexed accessors return with RET 4, so the index remains a stack slot.
  static u32 pool_create_ecx(ObservedObjectPool* ecx_this);
  static void* pool_get_ecx_ret4(ObservedObjectPool* ecx_this,
                                 u32 stack_packed_index);
  static bool pool_is_live_ecx_ret4(ObservedObjectPool* ecx_this,
                                    u32 stack_packed_index);
  static void pool_release_ecx_ret4(ObservedObjectPool* ecx_this,
                                    u32 stack_packed_index);
  static void pool_clear_ecx(ObservedObjectPool* ecx_this);
  static u32 pool_iterator_begin_ecx(ObservedObjectPool* ecx_this);
  static void* pool_iterator_next_ecx_ret4(ObservedObjectPool* ecx_this,
                                           u32* stack_iterator);

  // RE: callback slots +0x04/+0x0c/+0x34 receive the object in ECX.
  static void callback_slot_04_ecx(const ObservedCallbackVtablePrefix* vtable,
                                   void* ecx_receiver);
  static void callback_slot_0c_ecx(const ObservedCallbackVtablePrefix* vtable,
                                   void* ecx_receiver, u32 stack_value);
  static void callback_slot_34_ecx(const ObservedCallbackVtablePrefix* vtable,
                                   void* ecx_receiver);

  // RE: unresolved native boundaries are adapters, not ordinary cdecl calls.
  static void e514c0_edi(CellObjectData* edi_receiver);
  static void e57910_esi(CellObjectData* esi_receiver);
  // RE: e576f0 keeps the clamped-health target pointer in ESI and forwards
  // its incoming source-index stack slot to e575f0 on the 0x1001 branch.
  static void e576f0_esi_stack(CellObjectData* esi_receiver,
                               u32 stack_source_index);
  static void e66010_eax_stack(u32 eax_cell_index, u32 stack_reason);
  static i32 e4ee60_edx(i32 edx_mode);
  static void e7e130_edi_ecx_stack(ObservedObjectPool* ecx_effect_pool,
                                   void* edi_record, float stack_value_0,
                                   u32 stack_value_1, u32 stack_value_2);
  static void e6eb60_esi(CellObjectData* esi_receiver);
  static void e6ecb0_esi(CellObjectData* esi_receiver);
  static void e82690_stack(u32 stack_marker, float stack_value);
  static u8 e59170_stack(u32 stack_cell_index,
                         float ignored_stack_effect_scale);
  // RE: 0x00e72130 is interior to 0x00e72060 in live Ghidra, not a
  // standalone call target; keep its unresolved ESI contract explicit.
  static void e72130_interior_esi(CellObjectData* esi_receiver);
  static void e82130_ecx(OpaqueResourceScope* ecx_scope);
  static void e50810_esi(const float* esi_anchor);
  static void e52a40_stack6_cleanup8_then_e771d0(const E52a40Stack6& stack_call,
                                                 CellResourceRef* resource,
                                                 const void* model_key,
                                                 u32 query,
                                                 const void* position,
                                                 float position_scale);
  static void e771d0_stack10(CellResourceRef* resource, const void* model_key,
                             u32 query, const void* position,
                             float position_scale, i32 scale,
                             float resource_scale, float effect_scale,
                             u32 field_54, u32* field_58);
  static u8 e810590_ecx_ret4(u32 ecx_value, u32 stack_mode);
  static u32 e8105b0_ecx_ret8(u32 ecx_receiver, u32 stack_hash, u32 stack_mode);

  // RE: 0x00e78b20 and 0x00e78b80 are ECX/EDX helpers with stack arguments.
  static void e78b20_ecx_edx_stack(const float* ecx_query, u32 edx_pool,
                                   float stack_query,
                                   u32 stack_exclusion_index);
  static void e78b80_ecx_edx_hidden_edi_stack(const float* ecx_query,
                                              u32 edx_pool, float stack_query,
                                              u32 hidden_edi_exclusion);
  static u8 e78c00_stack2(CellObjectData* stack_cell,
                          const void* stack_details);
  // RE: 0x00e72060 has four stack slots; the caller's earlier ECX temporary
  // is overwritten by FSTP and must not be modeled as a player index.
  static u8 e72060_stack4(CellObjectData* stack_target,
                          CellPoolIndex stack_source_index,
                          CellResourceRef* stack_resource, float stack_scale);
};

CellObjectData* object_at(u32 packed_index) {
  return static_cast<CellObjectData*>(
      MachineAbiAdapters::pool_get_ecx_ret4(cell_pool(nullptr), packed_index));
}

const ObservedCallbackVtablePrefix* callback_vtable(const void* object) {
  u32 address = read_u32(object, 0);
  return reinterpret_cast<const ObservedCallbackVtablePrefix*>(
      static_cast<std::uintptr_t>(address));
}

i32 clamp_scale(i32 scale, i32 adjustment) {
  const i32 adjusted = scale + adjustment;
  if (adjusted < 0) {
    return 0;
  }
  if (adjusted > 19) {
    return 19;
  }
  return adjusted;
}

const ObservedStageRecord* stage_record(i32 mode) {
  // RE: the live scan advances through 0x1c-byte records and reads the
  // signed threshold at record+0x04; no table length is asserted.
  if (mode == 1000) {
    return &g_stage_table_1000_01483e60;
  }
  std::size_t index = 0;
  if (mode >= 0) {
    do {
      ++index;
    } while (mode >= g_stage_table_01483c14[index].upper_bound_04);
  }
  return &g_stage_table_01483c14[index];
}

void initialize_effect_record(std::byte* record, float animation_time,
                              u32 source_index) {
  write_f32(record, 0x1c, animation_time);
  write_f32(record, 0x20, animation_time);
  write_u32(record, 0x24, 6);
  write_u32(record, 0x28, source_index);
  write_u32(record, 0x2c, 0);
  write_u32(record, 0x30, 0xffffffffu);
  write_u32(record, 0x34, 0xffffffffu);
  write_u32(record, 0x38, 0);
  write_u32(record, 0x3c, 0);
  write_f32(record, 0x40, 0.0f);
  write_f32(record, 0x44, 0.0f);
  copy_bytes(record, 0x48, g_default_position_016b3c28, 0, 12);
  copy_bytes(record, 0x54, g_default_position_016b3c28, 0, 12);
  copy_bytes(record, 0x60, g_default_color_015a7c4c, 0, 16);
  write_u32(record, 0x70, 0);
  write_u8(record, 0x74, 0);
  write_u32(record, 0x78, 0);
  write_u32(record, 0x04, 0);
  write_u8(record, 0x08, 0);
}

extern "C" {

u8 opaque_00e52960();
bool opaque_00e57460(const CellObjectData* target,
                     const CellObjectData* source);
void opaque_00e71ce0(const CellObjectData* target, u32 source_index);
i32 opaque_00e58980(const CellObjectData* source, const CellObjectData* target);
void opaque_00e62340(const CellObjectData* target, i32 health);
float opaque_00e6d200(CellObjectData* cell, const CellObjectData* other,
                      u32 animation, u32 current_animation);
void opaque_00e7a770(u32 target_index, u32 source_index,
                     CellResourceRef* resource, u8 player_related,
                     u32 effect_kind, float effect_scale);
u32 opaque_00e51ee0(u32 event_kind, float initial_time, u32 target_index,
                    u32 source_index, u32 field_2c, u32 field_30,
                    u32 effect_kind, CellResourceRef* resource, float field_3c,
                    float field_40, const OpaqueCellDirectionPayload* direction,
                    u32 field_48, u32 field_4c, u32 field_50,
                    u32 player_related, u32 field_60);
u8 opaque_00e59010(u32 target_index, u32 source_index, u32 effect_kind,
                   u8 update_animation, float blend_time,
                   const OpaqueCellDirectionPayload* direction);

i32 opaque_00e57340(const CellObjectData* cell);
u32 opaque_00932e80(const char* name, u32 hash, u32 mode);
u32 opaque_00571cf0(const char* name);
void opaque_00e66840(const CellObjectData* cell, u32 effect_id);
void opaque_00e71f00(const CellObjectData* target, u32 source_index);

void opaque_00e86980(u32 owner, void* node);
void opaque_00bbbde0(u32 owner, u32 value);
void opaque_00bbb0e0(u32 owner);
void opaque_00e67890(const CellObjectData* cell);
void opaque_00e59200(u32 packed_index);

void opaque_00e86980_link_release(u32 owner, void* node);
void opaque_00e86b60();
void opaque_00e65180(u32 begin, u32 end);
void opaque_00d018d0(u32 begin, u32 end);
const void* opaque_00e4ce40(OpaqueResourceScope* scope);
const void* opaque_00e4cc40(CellResourceRef* resource,
                            OpaqueResourceScope* scope);
u32 opaque_00e4cce0(u32 key);
void opaque_00e750c0(const float* anchor, float scale);
void opaque_00e7d370(u32 value, void* table, u32 flag);
void opaque_00e5f360();
void opaque_807bb0(u32 source, const ObservedAudioConfig* config, u32 value);
}

}  // namespace model

using namespace model;

extern "C" std::uint8_t cell_state_apply_damage_00e7a7c0(
    CellObjectData* target, CellObjectData* source,
    const OpaqueCellDirectionPayload* direction, std::uint32_t damage_kind,
    std::uint32_t effect_kind, float effect_scale) {
  if (opaque_00e52960() == 0) {
    return 0;
  }
  if (opaque_00e57460(target, source) || read_u8(target, 0x17c) != 0 ||
      read_u8(target, 0x111) != 0) {
    return 0;
  }

  const u32 source_index = cell_index(source);
  opaque_00e71ce0(target, source_index);
  const i32 damage = opaque_00e58980(source, target);
  if (damage > 0) {
    const u32 player_index = read_u32(g_cell_game_016b3c04, 0x411c);
    if (player_index == cell_index(target) || player_index == source_index ||
        read_u8(source, 0x110) != 0) {
      opaque_00e62340(target, read_i32(target, 0x244));
    }
    write_i32(target, 0x244, read_i32(target, 0x244) - damage);
    if (read_i32(target, 0x244) < 0) {
      write_i32(target, 0x244, 0);
    }
    MachineAbiAdapters::e57910_esi(source);
    MachineAbiAdapters::e576f0_esi_stack(target, source_index);
  }

  if (read_i32(target, 0x244) == 0) {
    const u32 player_index = read_u32(g_cell_game_016b3c04, 0x411c);
    const u32 player_related =
        player_index == source_index || read_u8(source, 0x110) != 0 ? 1u : 0u;
    return cell_state_remove_or_kill_00e7a4a0(
        target, CellPoolIndex{static_cast<i32>(source_index)},
        cell_resource(source), static_cast<u8>(player_related), effect_kind,
        effect_scale);
  }

  OpaqueResourceScope resource_scope;
  const void* resource_details =
      opaque_00e4cc40(cell_resource(target), &resource_scope);

  u32 animation = 0x10;
  if (damage_kind == 1) {
    animation = 0x0e;
  } else if (damage_kind == 3) {
    animation = 0x0f;
  } else if (damage_kind == 5) {
    animation = 0x11;
  }

  CellObjectData* resolved_target = object_at(cell_index(target));
  const float animation_time = opaque_00e6d200(
      resolved_target, nullptr, animation, read_u32(target, 0x1b0));

  const u32 player_index = read_u32(g_cell_game_016b3c04, 0x411c);
  const u32 player_related =
      player_index == source_index || read_u8(source, 0x110) != 0 ? 1u : 0u;

  // RE: 0x00e7a993 uses JBE, so unordered animation-time values take the
  // remove-or-kill path. The explicit negation preserves that NaN behavior.
  if (!(animation_time > 0.0f)) {
    opaque_00e7a770(cell_index(target), source_index, cell_resource(source),
                    static_cast<u8>(player_related), damage_kind, effect_scale);
  } else {
    (void)resource_details;
    opaque_00e51ee0(2, 0.0f, cell_index(target), source_index, 0xffffffffu,
                    0xffffffffu, damage_kind, cell_resource(source), 0.0f, 0.0f,
                    direction, 0, 0, 0, player_related, 0);
    opaque_00e59010(cell_index(target), source_index, damage_kind, 1, 0.0f,
                    direction);
  }
  MachineAbiAdapters::e82130_ecx(&resource_scope);
  return 1;
}

extern "C" std::uint8_t cell_state_remove_or_kill_00e7a4a0(
    CellObjectData* target, CellPoolIndex source_index,
    CellResourceRef* resource_ref, std::uint8_t player_related,
    std::uint32_t effect_kind, float effect_scale) {
  // RE: argument five is forwarded by no observed path in this body.
  (void)effect_kind;

  if (read_u8(target, 0x112) != 0 || read_u8(target, 0x113) != 0) {
    return 0;
  }

  const u32 player_index = read_u32(g_cell_game_016b3c04, 0x411c);
  if (cell_index(target) == player_index) {
    const i32 mode = read_i32(g_cell_game_016b3c04, 0x5158);
    if (read_u8(g_cell_game_016b3c04, 0x5169) != 0 || mode == 5 || mode == 3) {
      return 0;
    }
    return MachineAbiAdapters::e72060_stack4(target, source_index, resource_ref,
                                             effect_scale);
  }

  write_u8(target, 0x113, 1);
  if (opaque_00e57340(target) < 2) {
    const u32 effect =
        opaque_00932e80("cell_death_oneshot_small", 0x811c9dc5u, 1);
    opaque_00e66840(target, effect);
  } else {
    const char* name = opaque_00e57340(target) < 3 ? "cell_death_oneshot"
                                                   : "cell_death_oneshot_large";
    opaque_00e66840(target, opaque_00571cf0(name));
  }

  opaque_00e71f00(target, source_index.value);
  if (player_related != 0) {
    // RE: 0x00e514c0 consumes the target through live EDI state in the
    // original.
    MachineAbiAdapters::e514c0_edi(target);
    const u32 serializable = read_u32(g_cell_game_016b3c04, 0x5190);
    write_i32(game_bytes() + serializable, 0x6c,
              read_i32(game_bytes() + serializable, 0x6c) + 1);
  }

  if (read_u32(target, 0x358) != 0) {
    OpaqueResourceScope resource_scope;
    const std::byte* resource_details = static_cast<const std::byte*>(
        opaque_00e4cc40(cell_resource(target), &resource_scope));
    const u32 serializable = read_u32(g_cell_game_016b3c04, 0x5190);
    const i32 current_scale = read_i32(target, 0x358);
    const i32 expected_scale = MachineAbiAdapters::e4ee60_edx(
        read_i32(game_bytes() + serializable, 0x1c));
    if (current_scale > expected_scale - 1 &&
        current_scale < expected_scale + 2) {
      const float resource_scale = read_f32(resource_details, 0xd4);
      MachineAbiAdapters::e52a40_stack6_cleanup8_then_e771d0(
          {current_scale, -1, resource_scale, effect_scale, 0, 0},
          cell_resource(target), cell_address(target, 0xfc),
          read_u32(target, 0x35c), cell_address(target, 0x4c),
          read_f32(target, 0x58));
    }
    MachineAbiAdapters::e82130_ecx(&resource_scope);
  }

  CellObjectData* resolved_target = object_at(cell_index(target));
  const float discarded_animation_time =
      opaque_00e6d200(resolved_target, nullptr, 0x0a, read_u32(target, 0x1b0));
  (void)discarded_animation_time;
  resolved_target = object_at(cell_index(target));
  const float second_animation_time =
      opaque_00e6d200(resolved_target, nullptr, 0x07, read_u32(target, 0x1b0));

  const u32 record_index = MachineAbiAdapters::pool_create_ecx(effect_pool());
  std::byte* record = static_cast<std::byte*>(
      MachineAbiAdapters::pool_get_ecx_ret4(effect_pool(), record_index));
  initialize_effect_record(record, second_animation_time, cell_index(target));
  (void)MachineAbiAdapters::e59170_stack(cell_index(target), effect_scale);
  return 1;
}

extern "C" void cell_state_remove_object_00e780a0(std::int32_t object_index,
                                                  std::uint8_t apply_effect,
                                                  float effect_scale,
                                                  std::uint32_t effect_kind) {
  const u32 packed_index = static_cast<u32>(object_index);
  if (!MachineAbiAdapters::pool_is_live_ecx_ret4(cell_pool(nullptr),
                                                 packed_index)) {
    return;
  }

  if (object_index == read_i32(g_cell_game_016b3c04, 0x411c)) {
    write_u32(g_cell_game_016b3c04, 0x411c, 0);
  }

  CellObjectData* cell = static_cast<CellObjectData*>(
      MachineAbiAdapters::pool_get_ecx_ret4(cell_pool(nullptr), packed_index));
  opaque_00e86980(read_u32(cell, 0x35c), cell_address(cell, 0x360));
  const i32 attached_id = read_i32(cell, 0x364);
  if (attached_id != -1) {
    opaque_00bbbde0(read_u32(g_cell_game_016b3c04, 0x4104),
                    static_cast<u32>(attached_id));
  }

  if (read_u32(cell, 0x248) != 0) {
    MachineAbiAdapters::e66010_eax_stack(packed_index, effect_kind);
    if (apply_effect != 0) {
      opaque_00e67890(cell);
    }
  }

  const u32 related_index = read_u32(cell, 0x370);
  if (related_index != 0) {
    opaque_00e59200(related_index);
  }

  if (apply_effect != 0) {
    OpaqueResourceScope resource_scope;
    const std::byte* resource_details = static_cast<const std::byte*>(
        opaque_00e4cc40(cell_resource(cell), &resource_scope));
    const u32 serializable = read_u32(g_cell_game_016b3c04, 0x5190);
    const i32 expected_scale = MachineAbiAdapters::e4ee60_edx(
        read_i32(game_bytes() + serializable, 0x1c));
    const i32 clamped_scale = clamp_scale(expected_scale, -1);
    if (read_i32(cell, 0x358) != clamped_scale) {
      MachineAbiAdapters::e771d0_stack10(
          cell_resource(cell), cell_address(cell, 0xfc), read_u32(cell, 0x35c),
          cell_address(cell, 0x4c), read_f32(cell, 0x58), clamped_scale,
          read_f32(resource_details, 0xd4), effect_scale, 0, 0);
    }
    MachineAbiAdapters::e82130_ecx(&resource_scope);
  }

  MachineAbiAdapters::pool_release_ecx_ret4(cell_pool(nullptr), packed_index);
}

extern "C" void cell_state_reset_or_initialize_00e7fd00(
    std::int32_t mode, std::uint32_t value_2, std::uint32_t value_3,
    std::uint32_t value_4, std::uint8_t flag_5, std::uint32_t value_6,
    std::uint8_t flag_7) {
  MachineAbiAdapters::e82690_stack(0x1e08f6au, 0.0f);
  MachineAbiAdapters::e82690_stack(0x8a4d210eu, 0.0f);
  write_u8(g_cell_game_016b3c04, 0x51d8, 0);
  write_u32(g_cell_game_016b3c04, 0x411c, 0);
  write_u32(g_cell_game_016b3c04, 0x51d4, 0);

  u32 effect_iterator =
      MachineAbiAdapters::pool_iterator_begin_ecx(effect_pool());
  while (void* record = MachineAbiAdapters::pool_iterator_next_ecx_ret4(
             effect_pool(), &effect_iterator)) {
    MachineAbiAdapters::e7e130_edi_ecx_stack(effect_pool(), record, 0.0f, 0, 1);
  }
  MachineAbiAdapters::pool_clear_ecx(effect_pool());

  u32 cell_iterator =
      MachineAbiAdapters::pool_iterator_begin_ecx(cell_pool(nullptr));
  while (void* record = MachineAbiAdapters::pool_iterator_next_ecx_ret4(
             cell_pool(nullptr), &cell_iterator)) {
    const u32 packed_index = read_u32(record, 0);
    if (!MachineAbiAdapters::pool_is_live_ecx_ret4(cell_pool(nullptr),
                                                   packed_index)) {
      continue;
    }
    if (static_cast<i32>(packed_index) ==
        read_i32(g_cell_game_016b3c04, 0x411c)) {
      write_u32(g_cell_game_016b3c04, 0x411c, 0);
    }
    CellObjectData* cell =
        static_cast<CellObjectData*>(MachineAbiAdapters::pool_get_ecx_ret4(
            cell_pool(nullptr), packed_index));
    opaque_00e86980(read_u32(cell, 0x35c), cell_address(cell, 0x360));
    const i32 attached_id = read_i32(cell, 0x364);
    if (attached_id != -1) {
      opaque_00bbbde0(read_u32(g_cell_game_016b3c04, 0x4104),
                      static_cast<u32>(attached_id));
    }
    if (read_u32(cell, 0x248) != 0) {
      MachineAbiAdapters::e66010_eax_stack(packed_index, 1);
    }
    const u32 related_index = read_u32(cell, 0x370);
    if (related_index != 0 && MachineAbiAdapters::pool_is_live_ecx_ret4(
                                  game_pool_8c(), related_index)) {
      void* related_record =
          MachineAbiAdapters::pool_get_ecx_ret4(game_pool_8c(), related_index);
      const u32 related_cell_index = read_u32(related_record, 0x0c);
      if (MachineAbiAdapters::pool_is_live_ecx_ret4(cell_pool(nullptr),
                                                    related_cell_index)) {
        CellObjectData* related_cell =
            static_cast<CellObjectData*>(MachineAbiAdapters::pool_get_ecx_ret4(
                cell_pool(nullptr), related_cell_index));
        write_u32(related_cell, 0x370, 0);
        write_u32(related_cell, 0x36c, 0);
      }
      MachineAbiAdapters::pool_release_ecx_ret4(game_pool_8c(), related_index);
    }
    MachineAbiAdapters::pool_release_ecx_ret4(cell_pool(nullptr), packed_index);
  }

  opaque_00bbb0e0(read_u32(g_cell_game_016b3c04, 0x4104));
  opaque_00e86b60();

  ObservedObjectPool* rollover_pool =
      reinterpret_cast<ObservedObjectPool*>(ui_bytes() + 0x9c);
  u32 rollover_iterator =
      MachineAbiAdapters::pool_iterator_begin_ecx(rollover_pool);
  while (void* record = MachineAbiAdapters::pool_iterator_next_ecx_ret4(
             rollover_pool, &rollover_iterator)) {
    const u32 key = read_u32(record, 0x34);
    MachineAbiAdapters::e810590_ecx_ret4(key, 0);
    for (std::size_t index = 0; index < 64; ++index) {
      if (g_rollover_ids_016b4178[index] == key) {
        g_rollover_active_016b4278[index] = 0;
        break;
      }
    }
    MachineAbiAdapters::pool_release_ecx_ret4(rollover_pool,
                                              read_u32(record, 0));
  }

  u32 callback_iterator =
      MachineAbiAdapters::pool_iterator_begin_ecx(game_pool_38());
  while (void* record = MachineAbiAdapters::pool_iterator_next_ecx_ret4(
             game_pool_38(), &callback_iterator)) {
    const u32 callback_address = read_u32(record, 0x300);
    if (callback_address != 0) {
      // RE: no callback owner or concrete object subtype is established; only
      // the observed slot offsets and calling sequence are asserted.
      void* callback = reinterpret_cast<void*>(
          static_cast<std::uintptr_t>(callback_address));
      MachineAbiAdapters::callback_slot_0c_ecx(callback_vtable(callback),
                                               callback, 1);
      const u32 remaining_address = read_u32(record, 0x300);
      if (remaining_address != 0) {
        write_u32(record, 0x300, 0);
        callback = reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(remaining_address));
        MachineAbiAdapters::callback_slot_04_ecx(callback_vtable(callback),
                                                 callback);
      }
    }
  }
  MachineAbiAdapters::pool_clear_ecx(game_pool_38());
  MachineAbiAdapters::pool_clear_ecx(game_pool_8c());
  opaque_00d018d0(read_u32(g_cell_game_016b3c04, 0x4128),
                  read_u32(g_cell_game_016b3c04, 0x412c));
  MachineAbiAdapters::pool_clear_ecx(game_pool_a8());

  const u32 gfx_begin = read_u32(g_cell_gfx_016b3c08, 0x161dc);
  const u32 gfx_end = read_u32(g_cell_gfx_016b3c08, 0x161e0);
  const i32 gfx_count =
      (static_cast<i32>(gfx_end) - static_cast<i32>(gfx_begin)) / 0x74;
  for (i32 index = 0; index < gfx_count; ++index) {
    std::byte* record =
        reinterpret_cast<std::byte*>(static_cast<std::uintptr_t>(gfx_begin)) +
        static_cast<std::size_t>(index) * 0x74u;
    const u32 callback_address = read_u32(record, 0x70);
    void* callback =
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(callback_address));
    MachineAbiAdapters::callback_slot_0c_ecx(callback_vtable(callback),
                                             callback, 1);
    const u32 remaining_address = read_u32(record, 0x70);
    if (remaining_address != 0) {
      write_u32(record, 0x70, 0);
      callback = reinterpret_cast<void*>(
          static_cast<std::uintptr_t>(remaining_address));
      MachineAbiAdapters::callback_slot_04_ecx(callback_vtable(callback),
                                               callback);
    }
  }
  opaque_00e65180(gfx_begin, gfx_end);
  write_u32(g_cell_gfx_016b3c08, 0x16258, 0);

  const u32 world_161bc = read_u32(g_cell_gfx_016b3c08, 0x161bc);
  void* world =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(world_161bc));
  MachineAbiAdapters::callback_slot_34_ecx(callback_vtable(world), world);
  const u32 world_161ac = read_u32(g_cell_gfx_016b3c08, 0x161ac);
  world = reinterpret_cast<void*>(static_cast<std::uintptr_t>(world_161ac));
  MachineAbiAdapters::callback_slot_34_ecx(callback_vtable(world), world);
  const u32 world_161c8 = read_u32(g_cell_gfx_016b3c08, 0x161c8);
  world = reinterpret_cast<void*>(static_cast<std::uintptr_t>(world_161c8));
  MachineAbiAdapters::callback_slot_34_ecx(callback_vtable(world), world);

  OpaqueResourceScope config_scope;
  const std::byte* config =
      static_cast<const std::byte*>(opaque_00e4ce40(&config_scope));
  write_u8(g_cell_game_016b3c04, 0x410c, flag_5);
  write_u32(g_cell_game_016b3c04, 0x4110, value_6);
  if (flag_5 == 0) {
    write_u32(g_cell_game_016b3c04, 0x4114, read_u32(config, 0x04));
    write_u32(g_cell_game_016b3c04, 0x4118, read_u32(config, 0x18));
  } else {
    write_u32(g_cell_game_016b3c04, 0x4114, opaque_00e4cce0(5));
    write_u32(g_cell_game_016b3c04, 0x4118, opaque_00e4cce0(6));
  }

  write_f32(g_cell_ui_016b3c0c, 0xbc, 1.0f);
  write_f32(g_cell_ui_016b3c0c, 0x78, 0.0f);
  write_f32(g_cell_ui_016b3c0c, 0x7c, 0.0f);
  write_f32(g_cell_ui_016b3c0c, 0x80, 20.0f);
  write_f32(g_cell_ui_016b3c0c, 0x6c, read_f32(g_cell_ui_016b3c0c, 0x78));
  write_f32(g_cell_ui_016b3c0c, 0x70, read_f32(g_cell_ui_016b3c0c, 0x7c));
  write_f32(g_cell_ui_016b3c0c, 0x74, read_f32(g_cell_ui_016b3c0c, 0x80));
  write_f32(g_cell_ui_016b3c0c, 0x84, 0.0f);
  write_f32(g_cell_ui_016b3c0c, 0x908, 1.0f);
  write_f32(g_cell_ui_016b3c0c, 0xf8, 0.0f);
  write_u32(g_cell_ui_016b3c0c, 0xe0, 0);
  write_f32(g_cell_ui_016b3c0c, 0xf4, 192.0f);
  copy_bytes(g_cell_ui_016b3c0c, 0x48, g_anchor_015a7d3c, 0, 12);
  copy_bytes(g_cell_ui_016b3c0c, 0x54, g_anchor_015a7d3c, 0, 12);
  copy_bytes(g_cell_ui_016b3c0c, 0x60, g_anchor_015a7d3c, 0, 12);
  write_u32(g_cell_ui_016b3c0c, 0xb8, 0);

  const ObservedStageRecord* selected_stage = stage_record(mode);
  const float selected_scale = selected_stage->scale_10 * 0.5f;
  write_f32(g_cell_game_016b3c04, 0x514c, selected_scale);
  write_f32(g_cell_game_016b3c04, 0x5150, selected_scale);
  const u32 serializable = read_u32(g_cell_game_016b3c04, 0x5190);
  write_i32(game_bytes() + serializable, 0x1c, mode);
  write_u32(game_bytes() + serializable, 0x20, value_2);
  write_u32(game_bytes() + serializable, 0x24, value_3);
  write_u32(game_bytes() + serializable, 0x28, value_4);
  write_f32(g_cell_gfx_016b3c08, 0x4c,
            1.0f / (read_f32(g_cell_game_016b3c04, 0x514c) * 2.0f));
  opaque_00e750c0(g_anchor_015a7d3c,
                  read_f32(g_cell_game_016b3c04, 0x514c) * 2.0f);
  MachineAbiAdapters::e50810_esi(g_anchor_015a7d3c);

  selected_stage = stage_record(mode);
  opaque_00e7d370(selected_stage->field_00, game_bytes() + 0x4128, 1);

  const float anchor_x = g_anchor_015a7d3c[0];
  const float anchor_y = g_anchor_015a7d3c[1];
  const float anchor_z = g_anchor_015a7d3c[2];
  g_visible_background_bbox_016b3c88 = anchor_x - 10.0f;
  g_visible_background_bbox_016b3c8c = anchor_y - 7.5f;
  g_visible_background_bbox_016b3c90 = anchor_z;
  g_visible_background_bbox_016b3c94 = anchor_x + 10.0f;
  g_visible_background_bbox_016b3c98 = anchor_y + 7.5f;
  g_visible_background_bbox_016b3c9c = anchor_z;

  MachineAbiAdapters::e78b80_ecx_edx_hidden_edi_stack(
      g_anchor_015a7d3c, read_u32(g_cell_game_016b3c04, 0x40fc),
      read_f32(config, 0xb8), read_u32(g_cell_game_016b3c04, 0x411c));
  MachineAbiAdapters::e78b80_ecx_edx_hidden_edi_stack(
      g_anchor_015a7d3c, read_u32(g_cell_game_016b3c04, 0x4100),
      read_f32(config, 0xb8), read_u32(g_cell_game_016b3c04, 0x411c));
  MachineAbiAdapters::e78b20_ecx_edx_stack(
      g_anchor_015a7d3c, read_u32(g_cell_game_016b3c04, 0x40fc),
      read_f32(config, 0xbc), read_u32(g_cell_game_016b3c04, 0x411c));
  write_u32(g_cell_game_016b3c04, 0x5158, 0);
  opaque_00e5f360();

  const std::byte* serializable_bytes = game_bytes() + serializable;
  ObservedAudioConfig audio_config{};
  audio_config.serializable_value_10 = read_u32(serializable_bytes, 0x10);
  audio_config.constant_2f7d0004 = 0x2f7d0004u;
  audio_config.serializable_value_18 = read_u32(serializable_bytes, 0x18);
  const u32 audio_source = MachineAbiAdapters::e8105b0_ecx_ret8(
      read_u32(ui_bytes(), 0x90), 0x03d99151u, 1);
  opaque_807bb0(audio_source, &audio_config, 0xffffffffu);

  CellObjectData* player_cell =
      static_cast<CellObjectData*>(MachineAbiAdapters::pool_get_ecx_ret4(
          cell_pool(nullptr), read_u32(g_cell_game_016b3c04, 0x411c)));
  OpaqueResourceScope player_resource_scope;
  const void* player_resource_details =
      opaque_00e4cc40(cell_resource(player_cell), &player_resource_scope);
  (void)MachineAbiAdapters::e78c00_stack2(player_cell, player_resource_details);

  // RE: the two hatch entry points consume the live player cell and FPU state
  // left by surrounding setup; no semantic owner is asserted for that state.
  if (read_u8(g_cell_game_016b3c04, 0x410c) == 0 && flag_7 != 0) {
    MachineAbiAdapters::e6ecb0_esi(player_cell);
  } else {
    MachineAbiAdapters::e6eb60_esi(player_cell);
  }
  MachineAbiAdapters::e82130_ecx(&player_resource_scope);
  MachineAbiAdapters::e82130_ecx(&config_scope);
}

}  // namespace openspore::reconstruction::pkg06_cell_state
