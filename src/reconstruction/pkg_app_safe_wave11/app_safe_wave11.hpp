#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG app wave11 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_APP_SAFE_WAVE11_CDECL __cdecl
#define PKG_APP_SAFE_WAVE11_THISCALL __thiscall
#define PKG_APP_SAFE_WAVE11_FASTCALL __fastcall
#else
#define PKG_APP_SAFE_WAVE11_CDECL __attribute__((cdecl))
#define PKG_APP_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#define PKG_APP_SAFE_WAVE11_FASTCALL __attribute__((fastcall))
#endif

namespace openspore::reconstruction::pkg_app_safe_wave11 {

using TargetWord = std::uint32_t;
using TargetHalf = std::uint16_t;
using TargetByte = std::uint8_t;
using TargetSigned = std::int32_t;
using TargetFloat = float;

constexpr TargetWord kKindFloat = 0x000du;
constexpr TargetWord kKindPairArray = 0x00012u;
constexpr TargetWord kKindPair = 0x00013u;
constexpr TargetHalf kFlagLocked = 0x0004u;
constexpr TargetHalf kFlagLive = 0x0002u;
constexpr TargetHalf kFlagArrayMask = 0x0030u;
constexpr TargetWord kPairStride = 8u;
constexpr TargetWord kPairSourceSpan = 0x10u;
constexpr TargetWord kLinkSuppressA = 0x2ca33bdbu;
constexpr TargetWord kLinkValueSentinel = 0x9e6e561cu;
constexpr TargetWord kProbePrimary = 0x0f43029au;
constexpr TargetWord kProbeClassA = 0x3d97a8e4u;
constexpr TargetWord kProbeClassB = 0x2b978c46u;
constexpr TargetWord kProbeClassC = 0x2399be55u;
constexpr TargetWord kProbeClassD = 0x24682294u;
constexpr TargetWord kProbeClassE = 0x476a98c7u;
constexpr TargetWord kProbeClassF = 0x438f6347u;
constexpr TargetWord kProbeReport = 0x0bu;

struct OpaquePropertyRecord {
  TargetWord slot_00;
  TargetWord slot_04;
  TargetWord slot_08;
  std::array<TargetByte, 4> opaque_0c_0f;
  TargetHalf flags_10;
  TargetHalf kind_12;
};

struct OpaqueWordVector {
  TargetWord first;
  TargetWord last;
  TargetWord limit;
  TargetWord arena;
  TargetWord inline_sentinel;
  TargetWord reserved_14;
  std::array<TargetByte, 0x400> payload_18;
};

struct OpaqueSlotVector {
  TargetWord first;
  TargetWord last;
  TargetWord limit;
  TargetWord arena;
};

struct OpaquePairVector {
  TargetWord first;
  TargetWord last;
  TargetWord limit;
  TargetWord arena;
  TargetWord inline_sentinel;
  TargetWord reserved_14;
  std::array<TargetByte, 0x100> payload_18;
};

struct OpaqueVtableHolder {
  TargetWord* table;
};

struct OpaquePartEntry {
  std::array<TargetByte, 0x8c> opaque_00_8b;
  TargetWord key_8c;
  std::array<TargetByte, 0x1c> opaque_90_ab;
  TargetWord link_value_ac;
  TargetWord link_value_b0;
  TargetWord link_b4;
  std::array<TargetByte, 0x64> opaque_b8_11b;
  TargetWord pair_slot_11c;
  std::array<TargetByte, 0xb4> opaque_120_1d3;
  TargetByte flag_1d4;
  TargetByte flag_1d5;
  std::array<TargetByte, 2> opaque_1d6_1d7;
};

struct OpaqueTreeBlob {
  std::array<TargetByte, 0x1c> opaque_00_1b;
};

struct OpaqueAssocBlob {
  std::array<TargetByte, 0x9c> opaque_00_9b;
};

struct OpaquePartList {
  std::array<TargetByte, 0x0c> opaque_00_0b;
  void* property_list;
  std::array<TargetByte, 0x1a0> opaque_10_1af;
  TargetWord find_root_1b0;
  TargetWord find_key_a_1b4;
  TargetWord find_key_b_1b8;
  TargetWord find_key_c_1bc;
  std::array<TargetByte, 0x454> opaque_1c0_613;
  OpaqueTreeBlob tree_614;
  OpaqueAssocBlob assoc_630;
  TargetWord elements_first_6cc;
  TargetWord elements_last_6d0;
  std::array<TargetByte, 0x0c> opaque_6d4_6df;
};

struct OpaqueWordPair {
  TargetWord first;
  TargetWord second;
};

using AssignNotify_0093db80 =
    void(PKG_APP_SAFE_WAVE11_THISCALL*)(OpaquePropertyRecord*, TargetByte);
using AssignStore_0093dd80 = TargetByte(PKG_APP_SAFE_WAVE11_THISCALL*)(
    OpaquePropertyRecord*, TargetSigned, TargetWord, void*, TargetSigned,
    TargetSigned);
using AssignInsert_00423650 = OpaquePropertyRecord*(
    PKG_APP_SAFE_WAVE11_THISCALL*)(OpaquePropertyRecord*, void*, TargetWord);
using FindRoot_0043c0a0 =
    TargetWord(PKG_APP_SAFE_WAVE11_FASTCALL*)(const OpaquePartList*);
using FindKey_0043c120 = TargetSigned(PKG_APP_SAFE_WAVE11_THISCALL*)(
    const OpaquePartList*, TargetWord);
using WordReserve_00454b80 =
    void(PKG_APP_SAFE_WAVE11_THISCALL*)(OpaqueWordVector*, TargetWord);
using PairInsert_00454cb0 = OpaqueWordVector*(
    PKG_APP_SAFE_WAVE11_THISCALL*)(TargetWord, TargetWord, TargetWord);
using PairReserve_00454640 =
    void(PKG_APP_SAFE_WAVE11_THISCALL*)(OpaqueAssocBlob*, TargetWord);
using PairSlot_00454750 = TargetWord*(
    PKG_APP_SAFE_WAVE11_THISCALL*)(OpaqueAssocBlob*, const TargetWord*);
using TreeInsert_004544d0 = OpaqueTreeBlob*(
    PKG_APP_SAFE_WAVE11_THISCALL*)(OpaqueTreeBlob*, const TargetWord*,
                                   const OpaqueWordPair*);
using NodeAppend_005402c0 =
    void(PKG_APP_SAFE_WAVE11_THISCALL*)(OpaqueTreeBlob*);
using WordRelease_004c0b80 =
    void(PKG_APP_SAFE_WAVE11_FASTCALL*)(OpaqueWordVector*);
using ArrayBool_006a0760 = TargetWord(PKG_APP_SAFE_WAVE11_CDECL*)(
    void*, TargetWord, std::size_t*, const TargetByte**);
using HasProperty_00447150 =
    TargetByte(PKG_APP_SAFE_WAVE11_THISCALL*)(OpaqueVtableHolder*, TargetWord);
using GetProperty_00447150 = const OpaquePropertyRecord*(
    PKG_APP_SAFE_WAVE11_THISCALL*)(OpaqueVtableHolder*, TargetWord);
using Allocate_0042dee0 = TargetWord(PKG_APP_SAFE_WAVE11_CDECL*)(TargetWord,
                                                                 TargetWord,
                                                                 TargetWord,
                                                                 TargetWord);
using Release_00f47380 = void(PKG_APP_SAFE_WAVE11_CDECL*)(TargetWord);
using Push_004b7290 = void(PKG_APP_SAFE_WAVE11_THISCALL*)(OpaquePairVector*,
                                                          TargetWord,
                                                          TargetWord,
                                                          TargetByte);
using StreamLookup_004c0500 =
    TargetWord(PKG_APP_SAFE_WAVE11_CDECL*)(TargetWord);
using StreamRead_004bf430 = TargetWord(PKG_APP_SAFE_WAVE11_CDECL*)(TargetWord,
                                                                   TargetWord);
using StreamApply_004bc6d0 = TargetByte(PKG_APP_SAFE_WAVE11_CDECL*)(TargetWord,
                                                                    TargetWord,
                                                                    TargetWord);
using StreamReport_006ac0a0 =
    TargetWord(PKG_APP_SAFE_WAVE11_CDECL*)(TargetWord, TargetWord);
using HolderProbe_004bc540 =
    TargetWord(PKG_APP_SAFE_WAVE11_THISCALL*)(OpaqueVtableHolder*);
using HolderResolve_004bc540 =
    TargetWord(PKG_APP_SAFE_WAVE11_THISCALL*)(OpaqueVtableHolder*, TargetWord);
using GlobalKey_015d = TargetWord(PKG_APP_SAFE_WAVE11_CDECL*)(void);

struct OpaquePropertyPorts {
  AssignNotify_0093db80 notify_0093db80;
  AssignStore_0093dd80 store_0093dd80;
  AssignInsert_00423650 insert_00423650;
  FindRoot_0043c0a0 find_root_0043c0a0;
  FindKey_0043c120 find_key_0043c120;
  WordReserve_00454b80 reserve_00454b80;
  PairInsert_00454cb0 pair_insert_00454cb0;
  PairReserve_00454640 pair_reserve_00454640;
  PairSlot_00454750 pair_slot_00454750;
  TreeInsert_004544d0 tree_insert_004544d0;
  NodeAppend_005402c0 node_append_005402c0;
  WordRelease_004c0b80 release_004c0b80;
  ArrayBool_006a0760 array_bool_006a0760;
  HasProperty_00447150 has_property_00447150;
  GetProperty_00447150 get_property_00447150;
  GlobalKey_015d global_key_015d25b0;
  GlobalKey_015d global_key_015d2180;
  GlobalKey_015d global_key_015d22a4;
};

// 0x004af260 is the anchor of four conflict ledgers that are still open
// (editor_message_names_and_payloads, editor_ui_command_names,
// history_budget_semantics and history_redo_truncation), so it stays in
// staging. The stage lookup 0x004b0010, the class query 0x004bb860, the
// record grow and reserve 0x004afdd0 and 0x004afd00, the weight and key
// reserves 0x004afc80 and 0x004cd3c0 and the element gate 0x0044f220 were
// its ports alone and are dropped with it.
struct OpaqueSlotPorts {
  Allocate_0042dee0 allocate_0042dee0;
  Release_00f47380 release_00f47380;
  Push_004b7290 push_004b7290;
};

struct OpaqueStreamPorts {
  StreamLookup_004c0500 lookup_004c0500;
  StreamRead_004bf430 read_004bf430;
  StreamApply_004bc6d0 apply_004bc6d0;
  StreamReport_006ac0a0 report_006ac0a0;
  HolderProbe_004bc540 probe_004bc540;
  HolderResolve_004bc540 resolve_004bc540;
};

struct OpaquePropertyRuntime {
  OpaquePropertyPorts ports;
};

struct OpaqueSlotRuntime {
  OpaqueSlotPorts ports;
};

struct OpaqueStreamRuntime {
  OpaqueStreamPorts ports;
};

OpaquePropertyRuntime& property_runtime();
OpaqueSlotRuntime& slot_runtime();
OpaqueStreamRuntime& stream_runtime();

constexpr TargetSigned sar_shift(TargetSigned value, TargetSigned bits) {
  return static_cast<TargetSigned>(value >> bits);
}

constexpr TargetWord sar_count(TargetSigned value, TargetSigned bits) {
  return static_cast<TargetWord>(sar_shift(value, bits));
}

constexpr TargetWord array_mask(TargetHalf flags) {
  return static_cast<TargetWord>(flags & kFlagArrayMask);
}

TargetWord array_kind(const OpaquePropertyRecord* record);
const TargetWord* array_data(const OpaquePropertyRecord* record);

extern "C" OpaquePropertyRecord* PKG_APP_SAFE_WAVE11_THISCALL
property_record_assign_pair_004279d0(OpaquePropertyRecord* receiver,
                                     void* source);
extern "C" OpaquePropertyRecord* PKG_APP_SAFE_WAVE11_THISCALL
property_record_assign_scalar_00428060(OpaquePropertyRecord* receiver,
                                       const TargetFloat* source);
extern "C" void PKG_APP_SAFE_WAVE11_THISCALL
model_parts_apply_properties_00447150(OpaquePartList* receiver,
                                      OpaqueVtableHolder* service);
extern "C" void PKG_APP_SAFE_WAVE11_THISCALL pair_vector_insert_004786e0(
    OpaqueSlotVector* receiver, TargetWord position, const TargetWord* value);
extern "C" OpaquePairVector* PKG_APP_SAFE_WAVE11_THISCALL
pair_vector_construct_004b62a0(OpaquePairVector* receiver,
                               const TargetWord* source);
extern "C" TargetByte PKG_APP_SAFE_WAVE11_THISCALL
stream_probe_dispatch_004bc540(OpaqueVtableHolder* receiver,
                               OpaqueVtableHolder* holder_08,
                               OpaqueVtableHolder* holder_0c,
                               TargetWord unused_10, TargetWord code_14);

static_assert(sizeof(void*) == 4, "pkg-app-safe-wave11 needs 32-bit pointers");
static_assert(sizeof(TargetFloat) == 4,
              "pkg-app-safe-wave11 needs 32-bit floats");
static_assert(sizeof(TargetSigned) == 4,
              "pkg-app-safe-wave11 needs 32-bit words");
static_assert(sizeof(OpaquePropertyRecord) == 0x14, "property record size");
static_assert(offsetof(OpaquePropertyRecord, slot_00) == 0x00,
              "property record slot_00");
static_assert(offsetof(OpaquePropertyRecord, slot_04) == 0x04,
              "property record slot_04");
static_assert(offsetof(OpaquePropertyRecord, slot_08) == 0x08,
              "property record slot_08");
static_assert(offsetof(OpaquePropertyRecord, flags_10) == 0x10,
              "property record flags_10");
static_assert(offsetof(OpaquePropertyRecord, kind_12) == 0x12,
              "property record kind_12");
static_assert(sizeof(OpaqueWordVector) == 0x418, "word vector size");
static_assert(offsetof(OpaqueWordVector, first) == 0x00, "word vector first");
static_assert(offsetof(OpaqueWordVector, last) == 0x04, "word vector last");
static_assert(offsetof(OpaqueWordVector, limit) == 0x08, "word vector limit");
static_assert(offsetof(OpaqueWordVector, arena) == 0x0c, "word vector arena");
static_assert(offsetof(OpaqueWordVector, inline_sentinel) == 0x10,
              "word vector inline sentinel");
static_assert(offsetof(OpaqueWordVector, payload_18) == 0x18,
              "word vector payload");
static_assert(sizeof(OpaqueSlotVector) == 0x10, "slot vector size");
static_assert(offsetof(OpaqueSlotVector, limit) == 0x08, "slot vector limit");
static_assert(offsetof(OpaqueSlotVector, arena) == 0x0c, "slot vector arena");
static_assert(sizeof(OpaquePairVector) == 0x118, "pair vector size");
static_assert(offsetof(OpaquePairVector, first) == 0x00, "pair vector first");
static_assert(offsetof(OpaquePairVector, last) == 0x04, "pair vector last");
static_assert(offsetof(OpaquePairVector, limit) == 0x08, "pair vector limit");
static_assert(offsetof(OpaquePairVector, arena) == 0x0c, "pair vector arena");
static_assert(offsetof(OpaquePairVector, inline_sentinel) == 0x10,
              "pair vector inline sentinel");
static_assert(offsetof(OpaquePairVector, payload_18) == 0x18,
              "pair vector payload");
static_assert(sizeof(OpaqueVtableHolder) == 4, "vtable holder size");
static_assert(sizeof(OpaquePartEntry) == 0x1d8, "part entry size");
static_assert(offsetof(OpaquePartEntry, key_8c) == 0x8c, "part entry key_8c");
static_assert(offsetof(OpaquePartEntry, link_value_ac) == 0xac,
              "part entry link_value_ac");
static_assert(offsetof(OpaquePartEntry, link_value_b0) == 0xb0,
              "part entry link_value_b0");
static_assert(offsetof(OpaquePartEntry, link_b4) == 0xb4, "part entry link_b4");
static_assert(offsetof(OpaquePartEntry, pair_slot_11c) == 0x11c,
              "part entry pair_slot_11c");
static_assert(offsetof(OpaquePartEntry, flag_1d4) == 0x1d4,
              "part entry flag_1d4");
static_assert(offsetof(OpaquePartEntry, flag_1d5) == 0x1d5,
              "part entry flag_1d5");
static_assert(sizeof(OpaqueTreeBlob) == 0x1c, "tree blob size");
static_assert(sizeof(OpaqueAssocBlob) == 0x9c, "assoc blob size");
static_assert(sizeof(OpaquePartList) == 0x6e0, "part list size");
static_assert(offsetof(OpaquePartList, property_list) == 0x0c,
              "part list property_list");
static_assert(offsetof(OpaquePartList, find_root_1b0) == 0x1b0,
              "part list find_root_1b0");
static_assert(offsetof(OpaquePartList, find_key_a_1b4) == 0x1b4,
              "part list find_key_a_1b4");
static_assert(offsetof(OpaquePartList, find_key_b_1b8) == 0x1b8,
              "part list find_key_b_1b8");
static_assert(offsetof(OpaquePartList, find_key_c_1bc) == 0x1bc,
              "part list find_key_c_1bc");
static_assert(offsetof(OpaquePartList, tree_614) == 0x614,
              "part list tree_614");
static_assert(offsetof(OpaquePartList, assoc_630) == 0x630,
              "part list assoc_630");
static_assert(offsetof(OpaquePartList, elements_first_6cc) == 0x6cc,
              "part list elements_first_6cc");
static_assert(offsetof(OpaquePartList, elements_last_6d0) == 0x6d0,
              "part list elements_last_6d0");
static_assert(sizeof(OpaqueWordPair) == 8, "word pair size");
static_assert(offsetof(OpaqueWordPair, second) == 4, "word pair second");

}  // namespace openspore::reconstruction::pkg_app_safe_wave11
