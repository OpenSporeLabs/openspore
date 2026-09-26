#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-EDITOR-SAFE-WAVE11 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_EDITOR_SAFE_WAVE11_THISCALL __thiscall
#define PKG_EDITOR_SAFE_WAVE11_CDECL __cdecl
#define PKG_EDITOR_SAFE_WAVE11_STDCALL __stdcall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_EDITOR_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#define PKG_EDITOR_SAFE_WAVE11_CDECL __attribute__((cdecl))
#define PKG_EDITOR_SAFE_WAVE11_STDCALL __attribute__((stdcall))
#else
#error "PKG-EDITOR-SAFE-WAVE11 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_editor_safe_wave11 {

using Word = std::uint32_t;
using Signed = std::int32_t;
using Half = std::int16_t;
using Byte = std::uint8_t;
using Real = float;

static_assert(sizeof(void*) == 4,
              "editor safe wave11 requires 32-bit pointers");
static_assert(sizeof(Word) == 4, "editor safe wave11 requires 32-bit words");
static_assert(sizeof(Real) == 4, "editor safe wave11 requires 32-bit floats");

inline constexpr Word kMask003 = 0x00000008u;
inline constexpr Word kClear003 = 0xfffffff7u;
inline constexpr Word kElementStride = 0x00000018u;
inline constexpr Word kHalfStride = 0x0000000cu;
inline constexpr Word kMarkBit = 0x0000000au;
inline constexpr Word kProbeStride = 0x0000008cu;
inline constexpr Word kSeatStride = 0x00000038u;

inline constexpr Word kStateZero = 0u;
inline constexpr Word kStateOne = 1u;
inline constexpr Word kStateTwo = 2u;
inline constexpr Word kStateFour = 4u;
inline constexpr Word kStateFive = 5u;

inline constexpr Signed kModeZero = 0;
inline constexpr Signed kModeOne = 1;
inline constexpr Signed kModeTwo = 2;

inline constexpr Word kRequestTag = 0xabb455b7u;
inline constexpr Word kRequestSpan = 0x0000000au;
inline constexpr Word kRequestFirst = 0x00000008u;
inline constexpr Word kRequestSecond = 0x00000010u;
inline constexpr Word kProbeBudget = 0x00000080u;
inline constexpr Byte kUninitialisedFallbackByte = 0x00u;

struct alignas(4) OpaqueWords3 {
  Word word_00;
  Word word_04;
  Word word_08;
};

struct alignas(4) OpaqueFloats3 {
  Real x_00;
  Real y_04;
  Real z_08;
};

struct alignas(4) OpaqueTail3 {
  Byte head_00[3];
  Byte tail_03;
  Byte rest_04[8];
};

struct alignas(4) OpaqueNotifyTable {
  Byte opaque_00[0x28];
  void(PKG_EDITOR_SAFE_WAVE11_STDCALL* notify_028)(Word, Word);
};

struct alignas(4) OpaquePaintNode {
  OpaqueNotifyTable* slot_000;
  Word word_004;
  Byte opaque_008[0x54];
  Byte code_05c;
  Byte opaque_05d[0x1a3];
};

struct alignas(4) OpaquePaintPair {
  Byte mark_00;
  Byte tag_01;
  Byte pad_02[2];
};

struct alignas(4) OpaquePaintState {
  Byte opaque_000[0x10];
  OpaquePaintNode* node_010;
  Byte opaque_014[0x24];
  union {
    OpaquePaintPair pair_038;
    Word word_038;
  };
  Word value_03c;
  union {
    OpaquePaintPair pair_040;
    Word word_040;
  };
  Word applied_044;
  Byte opaque_048[0x3a4];
  OpaquePaintNode* node_3ec;
  OpaquePaintNode* node_3f0;
  Byte opaque_3f4[0x0c];
};

struct alignas(4) OpaqueRecord {
  Byte opaque_00[0x18];
};

struct alignas(4) OpaqueBox {
  std::uint16_t code_00;
  std::uint16_t count_02;
  Word span_04[3];
  Real extra_10;
  Word basis_14[9];
};

struct alignas(4) OpaqueEntryElement {
  Byte opaque_000[0x48];
  Word seed_048[3];
  Byte opaque_054[0x0c];
  Word basis_060[9];
  Byte opaque_084[0x154];
  Real span_1d8;
  Byte opaque_1dc[0xbec];
  Word marks_0dc8;
  Byte opaque_0dcc[4];
};

struct alignas(4) OpaqueEntryList {
  Byte opaque_000[0x18];
  OpaqueEntryElement** begin_018;
  OpaqueEntryElement** end_01c;
  Byte opaque_020[0xa8];
  OpaqueWords3 range_0c8;
  OpaqueTail3 tail_0d4;
  Byte opaque_0e0[8];
};

struct alignas(4) OpaqueVector {
  Word* begin_00;
  Word* end_04;
};

struct alignas(4) OpaqueProbeTable {
  Byte opaque_00[0x38];
  bool(PKG_EDITOR_SAFE_WAVE11_STDCALL* slot_038)(const void*, Word);
};

struct alignas(4) OpaqueProbeOwner {
  OpaqueProbeTable* table_000;
};

struct alignas(4) OpaqueProbeRequest {
  Word tag_00;
  Word span_04;
};

struct alignas(4) OpaqueBakeRow {
  Byte opaque_000[0x18];
  Byte opaque_018[0x80];
  OpaqueVector block_098;
  Byte opaque_0a0[0x0c];
  OpaqueVector block_0ac;
  Byte opaque_0b4[0x0c];
  void* keys_0c0;
  Byte opaque_0c4[0x10];
  void* marks_0d4;
  Byte opaque_0d8[0x10];
  OpaqueVector block_0e8;
  Byte opaque_0f0[0x0c];
  void* weights_0fc;
  Byte opaque_100[0x10];
  Byte head_110;
  Byte opaque_111[3];
  OpaqueVector block_114;
  Byte opaque_11c[4];
};

struct alignas(4) OpaqueBakeEntryPair {
  void* first_00;
  void* second_04;
};

struct alignas(4) OpaqueEntryPairVector {
  OpaqueBakeEntryPair* begin_00;
  OpaqueBakeEntryPair* end_04;
};

struct alignas(4) OpaqueBakeRoot {
  Byte opaque_000[0x18];
  void* primary_018;
  void* secondary_01c;
  Byte opaque_020[0x28];
  OpaqueEntryPairVector entries_048;
  Byte opaque_050[4];
};

static_assert(offsetof(OpaqueNotifyTable, notify_028) == 0x28, "notify slot");
static_assert(offsetof(OpaquePaintNode, word_004) == 0x04, "node mask");
static_assert(offsetof(OpaquePaintNode, code_05c) == 0x5c, "node code");
static_assert(offsetof(OpaquePaintState, node_010) == 0x10, "paint node");
static_assert(offsetof(OpaquePaintState, pair_038) == 0x38, "paint mark");
static_assert(offsetof(OpaquePaintState, value_03c) == 0x3c, "paint value");
static_assert(offsetof(OpaquePaintState, pair_040) == 0x40, "paint shadow");
static_assert(offsetof(OpaquePaintState, applied_044) == 0x44, "paint applied");
static_assert(offsetof(OpaquePaintState, node_3ec) == 0x3ec, "paint notify");
static_assert(offsetof(OpaquePaintState, node_3f0) == 0x3f0, "paint peer");
static_assert(offsetof(OpaquePaintPair, tag_01) == 0x01, "paint pair tag");
static_assert(sizeof(OpaqueRecord) == 0x18, "record size");
static_assert(sizeof(OpaqueBox) == 0x38, "box size");
static_assert(offsetof(OpaqueBox, span_04) == 0x04, "box span");
static_assert(offsetof(OpaqueBox, extra_10) == 0x10, "box extra");
static_assert(offsetof(OpaqueBox, basis_14) == 0x14, "box basis");
static_assert(offsetof(OpaqueEntryElement, seed_048) == 0x48, "element seed");
static_assert(offsetof(OpaqueEntryElement, basis_060) == 0x60, "element basis");
static_assert(offsetof(OpaqueEntryElement, span_1d8) == 0x1d8, "element span");
static_assert(offsetof(OpaqueEntryElement, marks_0dc8) == 0xdc8,
              "element marks");
static_assert(offsetof(OpaqueEntryList, begin_018) == 0x18, "list head");
static_assert(offsetof(OpaqueEntryList, end_01c) == 0x1c, "list tail");
static_assert(offsetof(OpaqueEntryList, range_0c8) == 0xc8, "list range");
static_assert(offsetof(OpaqueEntryList, tail_0d4) == 0xd4, "list tail slot");
static_assert(sizeof(OpaqueTail3) == 0x0c, "tail size");
static_assert(offsetof(OpaqueProbeTable, slot_038) == 0x38, "probe slot");
static_assert(sizeof(OpaqueProbeRequest) == 0x08, "request size");
static_assert(offsetof(OpaqueBakeRow, block_098) == 0x98, "row block a");
static_assert(offsetof(OpaqueBakeRow, block_0ac) == 0xac, "row block b");
static_assert(offsetof(OpaqueBakeRow, keys_0c0) == 0xc0, "row keys");
static_assert(offsetof(OpaqueBakeRow, marks_0d4) == 0xd4, "row marks");
static_assert(offsetof(OpaqueBakeRow, block_0e8) == 0xe8, "row block c");
static_assert(offsetof(OpaqueBakeRow, weights_0fc) == 0xfc, "row weights");
static_assert(offsetof(OpaqueBakeRow, head_110) == 0x110, "row head");
static_assert(offsetof(OpaqueBakeRow, block_114) == 0x114, "row block d");
static_assert(offsetof(OpaqueBakeRoot, primary_018) == 0x18, "root primary");
static_assert(offsetof(OpaqueBakeRoot, secondary_01c) == 0x1c,
              "root secondary");
static_assert(offsetof(OpaqueBakeRoot, entries_048) == 0x48, "root entries");

extern Real g_real_013ef54c;

extern "C" bool PKG_EDITOR_SAFE_WAVE11_THISCALL
unresolved_00526430(OpaqueWords3*);
extern "C" void PKG_EDITOR_SAFE_WAVE11_THISCALL
unresolved_004b1cc0(void*, OpaqueWords3*, void*, Byte);
extern "C" void PKG_EDITOR_SAFE_WAVE11_THISCALL unresolved_004aff80(void*,
                                                                    Signed);
extern "C" const OpaqueRecord* PKG_EDITOR_SAFE_WAVE11_THISCALL
unresolved_0044ae00(void*, OpaqueRecord*, Word, Word, Word);
extern "C" void PKG_EDITOR_SAFE_WAVE11_CDECL unresolved_0041dba0(void*,
                                                                 const Real*);
extern "C" void PKG_EDITOR_SAFE_WAVE11_THISCALL unresolved_00409930(OpaqueBox*);
extern "C" void PKG_EDITOR_SAFE_WAVE11_THISCALL
unresolved_00409dd0(OpaqueRecord*, const OpaqueBox*);
extern "C" bool PKG_EDITOR_SAFE_WAVE11_CDECL unresolved_004bf0a0(void*, void*,
                                                                 Word);
extern "C" bool PKG_EDITOR_SAFE_WAVE11_THISCALL
unresolved_004ccae0(void*, OpaqueFloats3, OpaqueFloats3, OpaqueWords3*,
                    OpaqueWords3*, Real*, Word);

extern "C" bool PKG_EDITOR_SAFE_WAVE11_THISCALL
editor_paint_commit_0043ac40(OpaquePaintState*, Word, Word, Byte);
extern "C" void PKG_EDITOR_SAFE_WAVE11_THISCALL
editor_entry_expand_004ad6f0(OpaqueEntryList*, OpaqueRecord*);
extern "C" bool PKG_EDITOR_SAFE_WAVE11_CDECL
editor_bake_probe_004bf770(OpaqueProbeOwner*, OpaqueBakeRow*);
// 0x004c5910 carries the open alias ceditor_skin_ispainting_alias, 0x004df550
// is the still-open TB-FL-002 conflict and 0x004c73f0 was never reconstructed.
// All three stay in staging; none of their receiver types, ports or
// constants survives into this package.
extern "C" bool PKG_EDITOR_SAFE_WAVE11_THISCALL
editor_bake_select_004c4a30(OpaqueBakeRoot*, Signed, Real, Real, Real, Real,
                            Real, Real, Word*, Word*, Real*, Byte);

}  // namespace openspore::reconstruction::pkg_editor_safe_wave11

#undef PKG_EDITOR_SAFE_WAVE11_THISCALL
#undef PKG_EDITOR_SAFE_WAVE11_CDECL
#undef PKG_EDITOR_SAFE_WAVE11_STDCALL
