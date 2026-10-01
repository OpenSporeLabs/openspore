#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-orchestrate-dogfood-00b72370 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL __attribute__((cdecl))
#else
#error "pkg-orchestrate-dogfood-00b72370 requires MSVC or GCC CCs"
#endif

// Simulator::cObjectPool_::DeleteObject @ 0x00b72370.
//
// The SDK import names the function; the machine body is the only evidence
// used for every claim below. Nothing here reproduces an EA type name, an
// RTTI class identity, or a pool index type: 0x00b72370 pushes no stack
// argument and returns with a plain RET, so the second formal the SDK
// decompilation shows (`cObjectPoolIndex index`) is the derived word
// `receiver - 4`, not a parameter.
namespace openspore::reconstruction::pkg_orchestrate_dogfood_00b72370 {

using OpaqueWord = std::uint32_t;

// 0x00b72370 .. 0x00b723c0, 31 instructions, 0x51 bytes.
inline constexpr OpaqueWord kTargetVa = 0x00b72370u;
inline constexpr OpaqueWord kTargetBodyEndInclusive = 0x00b723c0u;
inline constexpr OpaqueWord kTargetInstructionCount = 31u;

// 0x00b72385 MOV dword ptr [ESI + 0x28], 0x1465004  and
// 0x00b723a4 MOV ECX, dword ptr [ESI + 0x1465004].
// The receiver publishes this absolute address and the loop reads through it.
inline constexpr OpaqueWord kSourceTableVa = 0x01465004u;
// 0x00b7238c MOV dword ptr [ESI + 0x2c], 0x8
inline constexpr OpaqueWord kSourceTableWordCount = 8u;
// 0x00b723b8 CMP ESI, 0x20 / 0x00b723bb JC -- the byte-wise loop bound.
inline constexpr OpaqueWord kSourceTableWindowBytes = 0x20u;
// 0x00b72385 MOV dword ptr [ESI + 0x20], EDI
inline constexpr OpaqueWord kRecordBaseOffset = 0x20u;
// 0x00b723ac MOV EDX, dword ptr [EAX + 0x24]
inline constexpr OpaqueWord kDispatchSlotDisplacement = 0x24u;
// 0x00883860 is `undefined4 FUN_00883860(void) { return DAT_016514cc; }` and
// 0x00883870 is its setter: it returns the old word and stores its argument.
// The two accessor words are the only xrefs to 0x016514cc
// (READ 0x00883860, READ 0x00883874, WRITE 0x00883879).
inline constexpr OpaqueWord kDispatchTargetGlobalVa = 0x016514ccu;
// 0x00b723c0 is a plain RET: no callee-popped words, no returned value.
inline constexpr OpaqueWord kStackCleanupBytes = 0u;

struct OpaqueDispatchTarget;

struct OpaqueDispatchTargetVtable;

// 0x00b723af PUSH ECX / 0x00b723b0 PUSH EBX / 0x00b723b3 CALL EDX.
// Callee-visible stack order is slot 0 = the receiver-minus-four word, slot 1 =
// the current 0x01465004 word. The loop advances with no stack adjustment, so
// the callee reclaims both words.
using OpaqueDispatchTargetOperation24 =
    void(PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL*)(OpaqueDispatchTarget*,
                                                     OpaqueWord, OpaqueWord);

// Documentation only, NOT called by 0x00b72370. The vtable word that follows
// this function's own word in the containing table (0x00b79a60 at
// 0x014650f4) reads the five words this function publishes and hands them to
// 0x00571db0, which dispatches a *different* slot, displacement 0x2c, with
// three stack words. The two operations are kept apart on purpose.
using OpaqueDispatchTargetOperation2c = bool(
    PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL*)(OpaqueDispatchTarget*, OpaqueWord,
                                                OpaqueWord, OpaqueWord);

struct alignas(4) OpaqueDispatchTargetVtable {
  std::uint8_t opaque_slots_00[0x24]{};
  OpaqueDispatchTargetOperation24 operation_24;
};

// Only offset +0x00 of the dispatch target is observed: 0x00b723aa reads
// dword ptr [EDI] and 0x00b723ac reads dword ptr [EAX + 0x24]. No other field
// is claimed.
struct alignas(4) OpaqueDispatchTarget {
  const OpaqueDispatchTargetVtable* vtable_00;
};

// The five words published at receiver +0x20 .. +0x30, in publish order.
// 0x00b79a60 reads the same five offsets and forwards them to 0x00571db0 in
// this order, which is the only independent corroboration that the block is
// one five-word descriptor and not five unrelated fields.
struct alignas(4) PublishedDeleteRecord {
  OpaqueDispatchTarget* target_00;   // receiver + 0x20, the 0x00883860 result
  OpaqueWord token_04;               // receiver + 0x24, the receiver word - 4
  OpaqueWord source_base_08;         // receiver + 0x28, absolute 0x01465004
  OpaqueWord source_word_count_0c;   // receiver + 0x2c, absolute 8
  OpaqueWord trailing_10;            // receiver + 0x30, absolute 0
};

// Receiver of the target function. The body writes offsets 0x20 through 0x30
// and reads no other receiver field; the 0x20-byte prefix stays opaque and the
// 0x34 trailing extent is a modeling bound, not a recovered allocation size.
struct alignas(4) OpaqueObjectPoolReceiver {
  std::uint8_t opaque_00[0x20]{};
  OpaqueDispatchTarget* record_target_20;
  OpaqueWord record_token_24;
  OpaqueWord record_source_base_28;
  OpaqueWord record_source_word_count_2c;
  OpaqueWord record_trailing_30;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(kSourceTableWindowBytes == kSourceTableWordCount * 4u,
              "the loop bound is the source table extent in bytes");
static_assert(offsetof(OpaqueDispatchTargetVtable, operation_24) ==
                  kDispatchSlotDisplacement,
              "dispatch vtable operation slot offset");
static_assert(sizeof(OpaqueDispatchTargetVtable) == 0x28,
              "dispatch vtable modeled window extent");
static_assert(offsetof(OpaqueDispatchTarget, vtable_00) == 0x00,
              "dispatch target vtable pointer offset");
static_assert(sizeof(OpaqueDispatchTarget) == 4,
              "dispatch target header extent");
static_assert(offsetof(PublishedDeleteRecord, target_00) == 0x00,
              "published record target offset");
static_assert(offsetof(PublishedDeleteRecord, token_04) == 0x04,
              "published record token offset");
static_assert(offsetof(PublishedDeleteRecord, source_base_08) == 0x08,
              "published record source base offset");
static_assert(offsetof(PublishedDeleteRecord, source_word_count_0c) == 0x0c,
              "published record word count offset");
static_assert(offsetof(PublishedDeleteRecord, trailing_10) == 0x10,
              "published record trailing word offset");
static_assert(sizeof(PublishedDeleteRecord) == 0x14,
              "published record extent matches the five stores");
static_assert(offsetof(OpaqueObjectPoolReceiver, record_target_20) ==
                  kRecordBaseOffset,
              "published record base offset");
static_assert(offsetof(OpaqueObjectPoolReceiver, record_token_24) == 0x24,
              "receiver token word offset");
static_assert(offsetof(OpaqueObjectPoolReceiver, record_source_base_28) == 0x28,
              "receiver source base word offset");
static_assert(offsetof(OpaqueObjectPoolReceiver, record_source_word_count_2c) ==
                  0x2c,
              "receiver source word count offset");
static_assert(offsetof(OpaqueObjectPoolReceiver, record_trailing_30) == 0x30,
              "receiver trailing word offset");
static_assert(sizeof(OpaqueDispatchTargetOperation24) == 4,
              "dispatch operation slot width");
static_assert(
    std::is_same<OpaqueDispatchTargetOperation24,
                 void(PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL*)(
                     OpaqueDispatchTarget*, OpaqueWord, OpaqueWord)>::value,
    "dispatch operation carries the receiver plus two stack words");

// 0x00883860 is the only direct callee: it is called at 0x00b72375 with no
// pushed argument and its EAX result is consumed as an object pointer, so the
// port stays a bare cdecl accessor. No other ordinary stack argument is pushed
// anywhere in the body.
using OpaqueDispatchTargetGet00883860 =
    OpaqueDispatchTarget*(PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL*)();

struct DeleteObjectPorts {
  OpaqueDispatchTargetGet00883860 acquire_dispatch_target_00883860 = nullptr;
};

// The loop reads 0x20 bytes from 0x01465004, that is eight 32-bit words. The
// values observed live in the image are 0x025630b7, 0x0477c00d, 0x031018b9,
// 0x02e9973e, 0x032f76e7, 0x04d80d9e, 0x00f62def, 0x0182c582. The body only
// reads this window; it never writes it back.
struct DeleteObjectGlobals {
  OpaqueWord word_01465004[8]{};
};

static_assert(sizeof(DeleteObjectGlobals) == kSourceTableWindowBytes,
              "modeled source table window extent");

extern DeleteObjectPorts g_dogfood_00b72370_ports;
extern DeleteObjectGlobals g_dogfood_00b72370_globals;

OpaqueWord word_of(const void* pointer);

// Publishes the five-word descriptor and, when both the dispatch target and the
// receiver-minus-four word are non-zero, dispatches the eight iterations. Split
// out of the ABI-exact entry so the two guard arms are reachable from a test
// without a faulting receiver address.
void publish_and_dispatch_delete_record(OpaqueObjectPoolReceiver* pool,
                                        OpaqueDispatchTarget* dispatch_target,
                                        void* receiver_minus_four);

// ABI-exact body of 0x00b72370: `this` in ECX, no ordinary stack argument,
// callee-cleanup of 0 bytes, plain RET, no returned value.
extern "C" void PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL
delete_object_00b72370(OpaqueObjectPoolReceiver* pool);

// Portable model of the same body, used by the semantic test.
void delete_object_model(OpaqueObjectPoolReceiver* pool);

// Entry point of the staged semantic test translation unit.
int run_model();

}

#undef PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL
