#include "parsefloat_008414c0.hpp"

// The header undefines the macro at its end so it cannot leak into a
// translation unit that only wants the declarations; the definition here needs it
// again, so it is restated exactly as the header spelled it.
#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_PF_THISCALL __thiscall
#else
#define PKG_ARGSCRIPT_PF_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_parsefloat_008414c0 {

// The entire body of 0x008414c0, which is two instructions:
//
//   0x008414c0  8b 81 54 01 00 00   MOV EAX,dword ptr [ECX + 0x154]
//   0x008414c6  c3                   RET
//
// There is no frame, no callee, no branch, no test and no floating-point
// instruction, so the implementation is one load and one return and the
// comments below exist only to name the address each fact came from.
// `uint32_t` is spelled out rather than the package's `OpaqueWord` alias,
// which is `std::uint32_t`: the validator measures the declared return's width
// from the spelling and an alias names no width. Same type, one token changed.
uint32_t PKG_ARGSCRIPT_PF_THISCALL argscript_formatparser_get_field_008414c0(
    OpaqueFormatParser* self) {
  // 0x008414c0 reads a 32-bit little-endian word at displacement 0x154 from
  // the object ECX points to. `read_word_at` uses memcpy, so the read is
  // byte-exact and does not require the receiver to be word aligned -- the
  // original's operand is a plain dword load and asserts no alignment either.
  //
  // The load is unconditional: there is no CMP and no TEST in the body, so a
  // null receiver faults here exactly as it would in the original. No null
  // guard is added, because adding one would be a behaviour the bytes do not
  // have.
  return read_word_at(receiver_bytes(self), kFieldOffset);

  // 0x008414c6 is the bare RET. It pops no imm16, so this function takes zero
  // ordinary stack arguments, and the single return value above arrives in
  // EAX verbatim -- no sign extension, no truncation, no float conversion. The
  // `return` above is the only write to a return register the body performs.
}

}  // namespace openspore::reconstruction::pkg_argscript_parsefloat_008414c0

#undef PKG_ARGSCRIPT_PF_THISCALL
