#pragma once

#include <cstddef>
#include <cstdint>

namespace openspore::reconstruction::wave13_pilot_dispatch_b00 {

// ---------------------------------------------------------------------------
// Opaque types
// ---------------------------------------------------------------------------

// The target and both of its callees read one process-wide pointer,
// DAT_0166D9F4 (read live as 00 00 00 00). FUN_00A206F0 is a one-instruction
// accessor for it. SporeApp.exe itself never stores a non-null value into it,
// so the installing code lives outside this image; the type is not established.
struct OpaqueKeyedRecordSink;

// Vtable slots actually read out of SporeApp.exe. Names are descriptive only:
// no class identity, RTTI or SDK name is claimed for this interface.
struct OpaqueKeyedRecordSinkVtable {
  void *slot_00;        // +0x00
  void *slots_04_1c[7]; // +0x04 .. +0x1C

  // 0x00435e90 @ 0x00435eac: no argument, 32-bit result, returned to the
  // target. Also inlined at 0x005def18.
  std::uint32_t (*get_current_value)(void *); // +0x20

  void *slots_24_34[5]; // +0x24 .. +0x34

  // 0x00435ed0 @ 0x00435eef: exactly one pointer argument, a string address.
  void (*begin_named_scope)(void *, const char *); // +0x38

  // Only observed in the sibling 0x00435f40, never by the target. Two
  // arguments, first a string address.
  void (*set_keyed_value_alt)(void *, const char *, std::uint32_t); // +0x3C

  // 0x00435ed0 @ 0x00435f08 and 0x00435f1e: two arguments, first a string
  // address, second a 32-bit value. Called twice per record.
  void (*set_keyed_value)(void *, const char *, std::uint32_t); // +0x40

  void *slots_44_54[5]; // +0x44 .. +0x54

  // 0x00435ed0 @ 0x00435f2b: no argument, called last.
  void (*commit)(void *); // +0x58
};

struct OpaqueKeyedRecordSinkHolder {
  OpaqueKeyedRecordSinkVtable *vtable;
};

// The slot offsets below are evidence for the 32-bit layout, so they are
// only asserted on a 32-bit target.
#if defined(__i386__) || defined(_M_IX86)
static_assert(offsetof(OpaqueKeyedRecordSinkVtable, get_current_value) == 0x20,
              "vtable+0x20 is the 0x00435e90 accessor");
static_assert(offsetof(OpaqueKeyedRecordSinkVtable, begin_named_scope) == 0x38,
              "vtable+0x38 takes the single scope-name pointer");
static_assert(offsetof(OpaqueKeyedRecordSinkVtable, set_keyed_value_alt) ==
                  0x3C,
              "vtable+0x3C is the sibling-only keyed setter");
static_assert(offsetof(OpaqueKeyedRecordSinkVtable, set_keyed_value) == 0x40,
              "vtable+0x40 takes (key, value)");
static_assert(offsetof(OpaqueKeyedRecordSinkVtable, commit) == 0x58,
              "vtable+0x58 is the closing call");
static_assert(sizeof(void *) == 4, "the target is an x86-32 reconstruction");
#endif

// ---------------------------------------------------------------------------
// Record keys.
// These three immediates are the link-time addresses of string literals. They
// all point outside SporeApp.exe's own image (0x00400000..0x018D2000) and carry
// no base relocation, so they address string literals inside a sibling Spore
// module that is not shipped in this installation and cannot be read here.
// The 17 / 11 / 4 byte gaps between 0x03475365, 0x03475376, 0x03475381 and
// 0x03475385 are consistent with a contiguous NUL-terminated ASCII table
// (0x03475365 and 0x03475376 come from the sibling 0x00435f40), but the
// characters themselves are unverified.
// ---------------------------------------------------------------------------
inline constexpr std::uint32_t kRecordScopeName = 0x03475365u;
inline constexpr std::uint32_t kRecordEventTagKey = 0x03475381u;
inline constexpr std::uint32_t kRecordCurrentValueKey = 0x03475385u;

// ---------------------------------------------------------------------------
// Opaque ports. Neither callee body is reconstructed here; only the observed
// contracts are declared.
//
// 0x00435e90  cdecl, no argument, EBP frame, 32-bit result.
//             if (DAT_0166D9F4) return sink->vtable[0x20](); else return 0.
//
// 0x00435ed0  cdecl, two 4-byte arguments, bare RET (caller cleans 8 bytes).
//             if (DAT_0166D9F4) { vtable[0x38](kRecordScopeName);
//                                  vtable[0x40](kRecordEventTagKey, arg0);
//                                  vtable[0x40](kRecordCurrentValueKey, arg1);
//                                  vtable[0x58](); }
// ---------------------------------------------------------------------------
// C linkage so the byte-exact body below can call them by their literal names.
extern "C" std::uint32_t editor_record_current_value_port();
extern "C" void editor_record_emit_port(std::uint32_t event_tag,
                                        std::uint32_t value);

// ---------------------------------------------------------------------------
// Target: 0x004a88d0
//   12 instructions, 0x004a88d0..0x004a88ea, 28 bytes.
//   cdecl, void return, one 4-byte stack argument, EBP frame with SUB ESP,8.
//   Order of operations, exactly as emitted:
//     value = editor_record_current_value_port();   // 0x004a88d6
//     push value;                                  // 0x004a88db
//     push [EBP+8];                                // 0x004a88dc/0x004a88df
//     editor_record_emit_port(arg, value);         // 0x004a88e0
//     ADD ESP,8;                                   // 0x004a88e5
// ---------------------------------------------------------------------------
void __cdecl Editor_004a88d0_record_tagged_action_raw(std::uint32_t);
void __cdecl Editor_004a88d0_record_tagged_action(std::uint32_t event_tag);

} // namespace openspore::reconstruction::wave13_pilot_dispatch_b00
