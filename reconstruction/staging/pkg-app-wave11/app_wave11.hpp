#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG app wave11 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_APP_WAVE11_CDECL __cdecl
#define PKG_APP_WAVE11_THISCALL __thiscall
#define PKG_APP_WAVE11_FASTCALL __fastcall
#else
#define PKG_APP_WAVE11_CDECL __attribute__((cdecl))
#define PKG_APP_WAVE11_THISCALL __attribute__((thiscall))
#define PKG_APP_WAVE11_FASTCALL __attribute__((fastcall))
#endif

namespace openspore::reconstruction::pkg_app_wave11 {

using TargetWord = std::uint32_t;
using TargetHalf = std::uint16_t;
using TargetByte = std::uint8_t;
using TargetSigned = std::int32_t;
using TargetFloat = float;

constexpr TargetWord kNoIndex = 0xffffffffu;
constexpr TargetWord kKindFloat = 0x000du;
constexpr TargetWord kKindPairArray = 0x00012u;
constexpr TargetWord kKindPair = 0x00013u;
constexpr TargetHalf kFlagLocked = 0x0004u;
constexpr TargetHalf kFlagLive = 0x0002u;
constexpr TargetHalf kFlagArrayMask = 0x0030u;
constexpr TargetWord kPairStride = 8u;
constexpr TargetWord kPairSourceSpan = 0x10u;
constexpr TargetWord kRecordStride = 0x1d8u;
constexpr TargetWord kHeaderSpan = 0x48u;
constexpr TargetWord kHeaderClearSpan = 0x80u;
constexpr TargetWord kBlockStride = 0x20u;
constexpr TargetWord kMinCount = 8u;
constexpr TargetWord kBitSpan = 0x3cu;
constexpr TargetWord kStageSuppressA = 0x3d97a8e4u;
constexpr TargetWord kStageSuppressB = 0x2b978c46u;
constexpr TargetWord kStageSuppressC = 0x438f6347u;
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
constexpr TargetWord kSlotRecordFlagStorage = 0x39u;
constexpr TargetWord kSlotRecordFlagScaleA = 0x0bu;
constexpr TargetWord kSlotRecordFlagScaleB = 0x1fu;
constexpr TargetWord kSlotRecordFlagPresent = 0x0cu;

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
  TargetWord *table;
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
  void *property_list;
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

struct OpaqueStageEntry {
  std::array<TargetByte, 0x10> opaque_00_0f;
  TargetWord gate_10;
  std::array<TargetByte, 4> opaque_14_17;
  TargetWord field_18;
  TargetWord field_1c;
  TargetWord field_20;
  std::array<TargetByte, 0x24> opaque_24_47;
  TargetWord field_48;
  TargetWord field_4c;
  TargetWord field_50;
  std::array<TargetByte, 0x54> opaque_54_a7;
  std::array<TargetWord, 9> block_a8;
  std::array<TargetByte, 0x24> opaque_cc_ef;
  std::array<TargetWord, 9> block_f0;
  std::array<TargetByte, 0x48> opaque_114_15b;
  std::array<TargetByte, 0x70> opaque_15c_1cb;
  TargetWord field_1cc;
  TargetFloat value_1d0;
  TargetFloat value_1d4;
  TargetFloat value_1d8;
  std::array<TargetByte, 0x160> opaque_1dc_33b;
  TargetWord ref_33c;
  std::array<TargetByte, 0x60> opaque_340_39f;
  TargetWord field_3a0;
  TargetWord field_3a4;
  TargetWord field_3a8;
  TargetWord field_3ac;
  TargetWord field_3b0;
  TargetWord field_3b4;
  std::array<TargetByte, 0x28> opaque_3b8_3df;
  TargetWord ref_3e0;
  TargetWord ref_3e4;
  std::array<TargetByte, 0xe0> opaque_3e8_4c7;
  TargetWord blocks_first_4c8;
  TargetWord blocks_last_4cc;
  TargetWord blocks_limit_4d0;
  std::array<TargetByte, 0x1f8> opaque_4d4_6cb;
  TargetWord kids_first_6cc;
  TargetWord kids_last_6d0;
  TargetWord kids_limit_6d4;
  std::array<TargetByte, 0x2c> opaque_6d8_703;
  TargetWord weights_first_704;
  TargetWord weights_last_708;
  TargetWord weights_limit_70c;
  std::array<TargetByte, 0x2c> opaque_710_73b;
  TargetWord keys_first_73c;
  TargetWord keys_last_740;
  TargetWord keys_limit_744;
  std::array<TargetByte, 0x680> opaque_748_dc7;
  TargetWord bits_dc8;
  TargetWord bits_dcc;
  TargetWord bits_dd0;
  std::array<TargetByte, 0x30> opaque_dd4_e03;
  TargetWord index_e04;
  std::array<TargetByte, 4> opaque_e08_e0b;
};

struct OpaqueStageModel {
  std::array<TargetByte, 0x0c> opaque_00_0b;
  TargetWord field_0c;
  TargetWord field_10;
  TargetWord field_14;
  TargetWord elements_first_18;
  TargetWord elements_last_1c;
  std::array<TargetByte, 0x0c> opaque_20_2b;
  TargetByte flag_2c;
  std::array<TargetByte, 0x22> opaque_2d_4e;
  TargetByte flag_4f;
  std::array<TargetByte, 8> opaque_50_57;
  TargetWord kind_58;
  std::array<TargetByte, 0x30> opaque_5c_8b;
  TargetWord triplet_8c;
  TargetWord triplet_90;
  TargetWord triplet_94;
  TargetWord triplet_98;
  TargetWord triplet_9c;
  TargetWord triplet_a0;
  std::array<TargetWord, 3> triple_a4;
  std::array<TargetWord, 3> triple_b0;
  std::array<TargetWord, 3> triple_bc;
  std::array<TargetByte, 0x14> opaque_c8_db;
  TargetWord field_dc;
  std::array<TargetByte, 0x3e8> opaque_e0_4c7;
  std::array<TargetByte, 0x20c> opaque_4c8_6d3;
};

struct OpaqueStage {
  std::array<TargetByte, 8> opaque_00_07;
  TargetWord field_08;
  TargetWord field_0c;
  TargetWord field_10;
  std::array<TargetByte, 4> opaque_14_17;
  std::array<TargetByte, kHeaderSpan> header_18;
  std::array<TargetByte, 0x38> opaque_60_97;
  OpaqueSlotVector records_98;
};

struct OpaqueStageRecord {
  TargetWord field_00;
  TargetWord field_04;
  TargetWord parent_08;
  TargetWord secondary_0c;
  TargetFloat value_10;
  TargetWord field_14;
  TargetWord field_18;
  TargetWord field_1c;
  TargetWord field_20;
  TargetWord field_24;
  TargetWord field_28;
  TargetWord field_2c;
  TargetWord field_30;
  TargetWord field_34;
  std::array<TargetWord, 9> block_38;
  std::array<TargetWord, 9> block_5c;
  TargetByte flag_80;
  TargetByte flag_81;
  std::array<TargetByte, 2> opaque_82_83;
  TargetWord field_84;
  TargetFloat value_88;
  TargetFloat value_8c;
  TargetWord weight_count_90;
  std::array<TargetFloat, 8> weights_94;
  std::array<TargetWord, 8> keys_b4;
  TargetWord block_count_d4;
  std::array<TargetWord, 8> block_key_d8;
  std::array<TargetWord, 8> block_tag_f8;
  std::array<std::array<TargetWord, 3>, 8> block_head_118;
  std::array<std::array<TargetWord, 3>, 8> block_tail_178;
};

struct OpaqueWordPair {
  TargetWord first;
  TargetWord second;
};

using AssignNotify_0093db80 =
    void(PKG_APP_WAVE11_THISCALL *)(OpaquePropertyRecord *, TargetByte);
using AssignStore_0093dd80 = TargetByte(PKG_APP_WAVE11_THISCALL *)(
    OpaquePropertyRecord *, TargetSigned, TargetWord, void *, TargetSigned,
    TargetSigned);
using AssignInsert_00423650 = OpaquePropertyRecord *(
    PKG_APP_WAVE11_THISCALL *)(OpaquePropertyRecord *, void *, TargetWord);
using FindRoot_0043c0a0 =
    TargetWord(PKG_APP_WAVE11_FASTCALL *)(const OpaquePartList *);
using FindKey_0043c120 =
    TargetSigned(PKG_APP_WAVE11_THISCALL *)(const OpaquePartList *, TargetWord);
using WordReserve_00454b80 = void(PKG_APP_WAVE11_THISCALL *)(OpaqueWordVector *,
                                                             TargetWord);
using PairInsert_00454cb0 = OpaqueWordVector *(
    PKG_APP_WAVE11_THISCALL *)(TargetWord, TargetWord, TargetWord);
using PairReserve_00454640 = void(PKG_APP_WAVE11_THISCALL *)(OpaqueAssocBlob *,
                                                             TargetWord);
using PairSlot_00454750 = TargetWord *(
    PKG_APP_WAVE11_THISCALL *)(OpaqueAssocBlob *, const TargetWord *);
using TreeInsert_004544d0 = OpaqueTreeBlob *(
    PKG_APP_WAVE11_THISCALL *)(OpaqueTreeBlob *, const TargetWord *,
                               const OpaqueWordPair *);
using NodeAppend_005402c0 = void(PKG_APP_WAVE11_THISCALL *)(OpaqueTreeBlob *);
using WordRelease_004c0b80 =
    void(PKG_APP_WAVE11_FASTCALL *)(OpaqueWordVector *);
using ArrayBool_006a0760 = TargetWord(PKG_APP_WAVE11_CDECL *)(
    void *, TargetWord, std::size_t *, const TargetByte **);
using HasProperty_00447150 =
    TargetByte(PKG_APP_WAVE11_THISCALL *)(OpaqueVtableHolder *, TargetWord);
using GetProperty_00447150 = const OpaquePropertyRecord *(
    PKG_APP_WAVE11_THISCALL *)(OpaqueVtableHolder *, TargetWord);
using Allocate_0042dee0 = TargetWord(PKG_APP_WAVE11_CDECL *)(TargetWord,
                                                             TargetWord,
                                                             TargetWord,
                                                             TargetWord);
using Release_00f47380 = void(PKG_APP_WAVE11_CDECL *)(TargetWord);
using Push_004b7290 = void(PKG_APP_WAVE11_THISCALL *)(OpaquePairVector *,
                                                      TargetWord, TargetWord,
                                                      TargetByte);
using StageLookup_004b0010 = TargetWord(PKG_APP_WAVE11_CDECL *)(TargetWord);
using StageClass_004bb860 = TargetWord(PKG_APP_WAVE11_CDECL *)(TargetWord);
using RecordGrow_004afdd0 = void(PKG_APP_WAVE11_THISCALL *)(OpaqueSlotVector *,
                                                            TargetWord);
using RecordReserve_004afd00 =
    void(PKG_APP_WAVE11_THISCALL *)(OpaqueSlotVector *, TargetWord);
using WeightReserve_004afc80 = void(PKG_APP_WAVE11_THISCALL *)(TargetWord,
                                                               TargetWord);
using KeyReserve_004cd3c0 = void(PKG_APP_WAVE11_THISCALL *)(TargetWord,
                                                            TargetWord);
using ElementGate_0044f220 = TargetWord(PKG_APP_WAVE11_FASTCALL *)(TargetWord);
using StreamLookup_004c0500 = TargetWord(PKG_APP_WAVE11_CDECL *)(TargetWord);
using StreamRead_004bf430 = TargetWord(PKG_APP_WAVE11_CDECL *)(TargetWord,
                                                               TargetWord);
using StreamApply_004bc6d0 = TargetByte(PKG_APP_WAVE11_CDECL *)(TargetWord,
                                                                TargetWord,
                                                                TargetWord);
using StreamReport_006ac0a0 = TargetWord(PKG_APP_WAVE11_CDECL *)(TargetWord,
                                                                 TargetWord);
using HolderProbe_004bc540 =
    TargetWord(PKG_APP_WAVE11_THISCALL *)(OpaqueVtableHolder *);
using HolderResolve_004bc540 =
    TargetWord(PKG_APP_WAVE11_THISCALL *)(OpaqueVtableHolder *, TargetWord);
using GlobalKey_015d = TargetWord(PKG_APP_WAVE11_CDECL *)(void);

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

struct OpaqueSlotPorts {
  Allocate_0042dee0 allocate_0042dee0;
  Release_00f47380 release_00f47380;
  StageLookup_004b0010 lookup_004b0010;
  StageClass_004bb860 classify_004bb860;
  RecordGrow_004afdd0 record_grow_004afdd0;
  RecordReserve_004afd00 record_reserve_004afd00;
  WeightReserve_004afc80 weight_reserve_004afc80;
  KeyReserve_004cd3c0 key_reserve_004cd3c0;
  ElementGate_0044f220 element_gate_0044f220;
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

OpaquePropertyRuntime &property_runtime();
OpaqueSlotRuntime &slot_runtime();
OpaqueStreamRuntime &stream_runtime();

constexpr TargetSigned sar_shift(TargetSigned value, TargetSigned bits) {
  return static_cast<TargetSigned>(value >> bits);
}

constexpr TargetWord sar_count(TargetSigned value, TargetSigned bits) {
  return static_cast<TargetWord>(sar_shift(value, bits));
}

constexpr TargetWord array_mask(TargetHalf flags) {
  return static_cast<TargetWord>(flags & kFlagArrayMask);
}

TargetWord array_kind(const OpaquePropertyRecord *record);
const TargetWord *array_data(const OpaquePropertyRecord *record);
TargetByte record_bit(const OpaqueStageEntry *entry, TargetWord bit);

extern "C" OpaquePropertyRecord *PKG_APP_WAVE11_THISCALL
property_record_assign_pair_004279d0(OpaquePropertyRecord *receiver,
                                     void *source);
extern "C" OpaquePropertyRecord *PKG_APP_WAVE11_THISCALL
property_record_assign_scalar_00428060(OpaquePropertyRecord *receiver,
                                       const TargetFloat *source);
extern "C" void PKG_APP_WAVE11_THISCALL model_parts_apply_properties_00447150(
    OpaquePartList *receiver, OpaqueVtableHolder *service);
extern "C" void PKG_APP_WAVE11_THISCALL pair_vector_insert_004786e0(
    OpaqueSlotVector *receiver, TargetWord position, const TargetWord *value);
extern "C" TargetByte PKG_APP_WAVE11_THISCALL
model_stage_serialize_004af260(OpaqueStageModel *receiver, TargetWord source);
extern "C" OpaquePairVector *PKG_APP_WAVE11_THISCALL
pair_vector_construct_004b62a0(OpaquePairVector *receiver,
                               const TargetWord *source);
extern "C" TargetByte PKG_APP_WAVE11_THISCALL stream_probe_dispatch_004bc540(
    OpaqueVtableHolder *receiver, OpaqueVtableHolder *holder_08,
    OpaqueVtableHolder *holder_0c, TargetWord unused_10, TargetWord code_14);

static_assert(sizeof(void *) == 4, "pkg-app-wave11 needs 32-bit pointers");
static_assert(sizeof(TargetFloat) == 4, "pkg-app-wave11 needs 32-bit floats");
static_assert(sizeof(TargetSigned) == 4, "pkg-app-wave11 needs 32-bit words");
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
static_assert(sizeof(OpaqueStageEntry) == 0xe0c, "stage entry size");
static_assert(offsetof(OpaqueStageEntry, gate_10) == 0x10,
              "stage entry gate_10");
static_assert(offsetof(OpaqueStageEntry, field_1c) == 0x1c,
              "stage entry field_1c");
static_assert(offsetof(OpaqueStageEntry, field_20) == 0x20,
              "stage entry field_20");
static_assert(offsetof(OpaqueStageEntry, field_48) == 0x48,
              "stage entry field_48");
static_assert(offsetof(OpaqueStageEntry, field_4c) == 0x4c,
              "stage entry field_4c");
static_assert(offsetof(OpaqueStageEntry, field_50) == 0x50,
              "stage entry field_50");
static_assert(offsetof(OpaqueStageEntry, block_a8) == 0xa8,
              "stage entry block_a8");
static_assert(offsetof(OpaqueStageEntry, block_f0) == 0xf0,
              "stage entry block_f0");
static_assert(offsetof(OpaqueStageEntry, field_1cc) == 0x1cc,
              "stage entry field_1cc");
static_assert(offsetof(OpaqueStageEntry, value_1d0) == 0x1d0,
              "stage entry value_1d0");
static_assert(offsetof(OpaqueStageEntry, value_1d4) == 0x1d4,
              "stage entry value_1d4");
static_assert(offsetof(OpaqueStageEntry, value_1d8) == 0x1d8,
              "stage entry value_1d8");
static_assert(offsetof(OpaqueStageEntry, ref_33c) == 0x33c,
              "stage entry ref_33c");
static_assert(offsetof(OpaqueStageEntry, field_3a0) == 0x3a0,
              "stage entry field_3a0");
static_assert(offsetof(OpaqueStageEntry, field_3b4) == 0x3b4,
              "stage entry field_3b4");
static_assert(offsetof(OpaqueStageEntry, ref_3e0) == 0x3e0,
              "stage entry ref_3e0");
static_assert(offsetof(OpaqueStageEntry, ref_3e4) == 0x3e4,
              "stage entry ref_3e4");
static_assert(offsetof(OpaqueStageEntry, blocks_first_4c8) == 0x4c8,
              "stage entry blocks_first_4c8");
static_assert(offsetof(OpaqueStageEntry, blocks_last_4cc) == 0x4cc,
              "stage entry blocks_last_4cc");
static_assert(offsetof(OpaqueStageEntry, kids_first_6cc) == 0x6cc,
              "stage entry kids_first_6cc");
static_assert(offsetof(OpaqueStageEntry, kids_last_6d0) == 0x6d0,
              "stage entry kids_last_6d0");
static_assert(offsetof(OpaqueStageEntry, weights_first_704) == 0x704,
              "stage entry weights_first_704");
static_assert(offsetof(OpaqueStageEntry, weights_last_708) == 0x708,
              "stage entry weights_last_708");
static_assert(offsetof(OpaqueStageEntry, keys_first_73c) == 0x73c,
              "stage entry keys_first_73c");
static_assert(offsetof(OpaqueStageEntry, keys_last_740) == 0x740,
              "stage entry keys_last_740");
static_assert(offsetof(OpaqueStageEntry, bits_dc8) == 0xdc8,
              "stage entry bits_dc8");
static_assert(offsetof(OpaqueStageEntry, bits_dcc) == 0xdcc,
              "stage entry bits_dcc");
static_assert(offsetof(OpaqueStageEntry, bits_dd0) == 0xdd0,
              "stage entry bits_dd0");
static_assert(offsetof(OpaqueStageEntry, index_e04) == 0xe04,
              "stage entry index_e04");
static_assert(sizeof(OpaqueStageModel) == 0x6d4, "stage model size");
static_assert(offsetof(OpaqueStageModel, field_0c) == 0x0c,
              "stage model field_0c");
static_assert(offsetof(OpaqueStageModel, field_10) == 0x10,
              "stage model field_10");
static_assert(offsetof(OpaqueStageModel, field_14) == 0x14,
              "stage model field_14");
static_assert(offsetof(OpaqueStageModel, elements_first_18) == 0x18,
              "stage model elements_first_18");
static_assert(offsetof(OpaqueStageModel, elements_last_1c) == 0x1c,
              "stage model elements_last_1c");
static_assert(offsetof(OpaqueStageModel, kind_58) == 0x58,
              "stage model kind_58");
static_assert(offsetof(OpaqueStageModel, triplet_8c) == 0x8c,
              "stage model triplet_8c");
static_assert(offsetof(OpaqueStageModel, triplet_98) == 0x98,
              "stage model triplet_98");
static_assert(offsetof(OpaqueStageModel, triple_a4) == 0xa4,
              "stage model triple_a4");
static_assert(offsetof(OpaqueStageModel, triple_b0) == 0xb0,
              "stage model triple_b0");
static_assert(offsetof(OpaqueStageModel, triple_bc) == 0xbc,
              "stage model triple_bc");
static_assert(offsetof(OpaqueStageModel, field_dc) == 0xdc,
              "stage model field_dc");
static_assert(offsetof(OpaqueStageModel, flag_2c) == 0x2c,
              "stage model flag_2c");
static_assert(offsetof(OpaqueStageModel, flag_4f) == 0x4f,
              "stage model flag_4f");
static_assert(sizeof(OpaqueStage) == 0xa8, "stage size");
static_assert(offsetof(OpaqueStage, field_08) == 0x08, "stage field_08");
static_assert(offsetof(OpaqueStage, field_0c) == 0x0c, "stage field_0c");
static_assert(offsetof(OpaqueStage, field_10) == 0x10, "stage field_10");
static_assert(offsetof(OpaqueStage, header_18) == 0x18, "stage header_18");
static_assert(offsetof(OpaqueStage, records_98) == 0x98, "stage records_98");
static_assert(sizeof(OpaqueStageRecord) == kRecordStride, "stage record size");
static_assert(offsetof(OpaqueStageRecord, parent_08) == 0x08,
              "stage record parent_08");
static_assert(offsetof(OpaqueStageRecord, secondary_0c) == 0x0c,
              "stage record secondary_0c");
static_assert(offsetof(OpaqueStageRecord, value_10) == 0x10,
              "stage record value_10");
static_assert(offsetof(OpaqueStageRecord, field_14) == 0x14,
              "stage record field_14");
static_assert(offsetof(OpaqueStageRecord, block_38) == 0x38,
              "stage record block_38");
static_assert(offsetof(OpaqueStageRecord, block_5c) == 0x5c,
              "stage record block_5c");
static_assert(offsetof(OpaqueStageRecord, flag_80) == 0x80,
              "stage record flag_80");
static_assert(offsetof(OpaqueStageRecord, flag_81) == 0x81,
              "stage record flag_81");
static_assert(offsetof(OpaqueStageRecord, field_84) == 0x84,
              "stage record field_84");
static_assert(offsetof(OpaqueStageRecord, value_88) == 0x88,
              "stage record value_88");
static_assert(offsetof(OpaqueStageRecord, value_8c) == 0x8c,
              "stage record value_8c");
static_assert(offsetof(OpaqueStageRecord, weight_count_90) == 0x90,
              "stage record weight_count_90");
static_assert(offsetof(OpaqueStageRecord, weights_94) == 0x94,
              "stage record weights_94");
static_assert(offsetof(OpaqueStageRecord, keys_b4) == 0xb4,
              "stage record keys_b4");
static_assert(offsetof(OpaqueStageRecord, block_count_d4) == 0xd4,
              "stage record block_count_d4");
static_assert(offsetof(OpaqueStageRecord, block_key_d8) == 0xd8,
              "stage record block_key_d8");
static_assert(offsetof(OpaqueStageRecord, block_tag_f8) == 0xf8,
              "stage record block_tag_f8");
static_assert(offsetof(OpaqueStageRecord, block_head_118) == 0x118,
              "stage record block_head_118");
static_assert(offsetof(OpaqueStageRecord, block_tail_178) == 0x178,
              "stage record block_tail_178");
static_assert(sizeof(OpaqueWordPair) == 8, "word pair size");
static_assert(offsetof(OpaqueWordPair, second) == 4, "word pair second");

}  // namespace openspore::reconstruction::pkg_app_wave11
