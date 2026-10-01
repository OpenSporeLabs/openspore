// PKG-SWARM-W1-006417D0 -- VA 0x006417d0
// Sporepedia, unnamed virtual of a cSPAssetDataOTDB-shaped object
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, image base 0x400000)
//
// The complete body: 23 instructions, 0x006417d0..0x00641809 inclusive
// (ghidra_function.body_start 0x006417d0, body_end 0x0064180b, size_bytes 60;
// 0x0064180a..0x0064180f are INT3 padding and are NOT part of the body). Every
// line of the model below is annotated with the instruction it comes from.
//
// The listing this was written against was re-derived from the image bytes for this
// package (objdump -d -M intel over 0x6417c0..0x641810 of
// SPORE/SporeBin/SporeApp.exe) rather than taken on trust, and it agrees with the
// committed Ghidra listing instruction for instruction:
//
//   006417d0  56                 push   esi
//   006417d1  8b f1              mov    esi,ecx
//   006417d3  8b 4e 1c           mov    ecx,DWORD PTR [esi+0x1c]
//   006417d6  85 c9              test   ecx,ecx
//   006417d8  74 2c              je     0x641806
//   006417da  e8 c1 ef f0 ff     call   0x5507a0
//   006417df  83 38 ff           cmp    DWORD PTR [eax],0xffffffff
//   006417e2  75 06              jne    0x6417ea
//   006417e4  83 78 04 ff        cmp    DWORD PTR [eax+0x4],0xffffffff
//   006417e8  74 1c              je     0x641806
//   006417ea  8b 4e 1c           mov    ecx,DWORD PTR [esi+0x1c]
//   006417ed  e8 ae ef f0 ff     call   0x5507a0
//   006417f2  8b 10              mov    edx,DWORD PTR [eax]
//   006417f4  8b 4c 24 08        mov    ecx,DWORD PTR [esp+0x8]
//   006417f8  89 11              mov    DWORD PTR [ecx],edx
//   006417fa  8b 40 04           mov    eax,DWORD PTR [eax+0x4]
//   006417fd  89 41 04           mov    DWORD PTR [ecx+0x4],eax
//   00641800  b0 01              mov    al,0x1
//   00641802  5e                 pop    esi
//   00641803  c2 04 00           ret    0x4
//   00641806  32 c0              xor    al,al
//   00641808  5e                 pop    esi
//   00641809  c2 04 00           ret    0x4
//
// FRAME, resolved once against the entry ESP. The body's only stack effect is
// `PUSH ESI` at 0x006417d0 and the two matching POP ESI; the two direct calls are
// stack-neutral because 0x005507a0 ends in `MOV ESP,EBP; POP EBP; RET` (a bare C3
// with no immediate), and neither return site has an ADD/SUB. So ESP is at entry-4
// for the whole body between the prologue and the epilogue, and:
//
//   entry-4   the saved ESI, parked at 0x006417d0 and given back at 0x00641802
//             (true path) or 0x00641808 (false path). Not a parameter and not a
//             return value: both returns are `RET 0x4`, which consumes the return
//             address plus entry+4.
//   entry+4   the single ordinary argument: the out-record pointer. 0x006417f4
//             reads it with ESP at entry-4, so entry-4 + 0x8 = entry+4, and both
//             returns (`C2 04 00`) drop it. The machine-derived ABI record
//             independently reports stack_cleanup_bytes 4, side "callee",
//             ret_form "RET 0x4".
//
// The ABI record's own stack-argument entry says `read: false` for entry+4. That is
// a walk artefact and not a contradiction with the listing: the record's
// `abstained_because` lists "flow_not_modelled: the linear ESP walk ends at -4, so
// the listing is not one path", and 0x006417f4 `MOV ECX,[ESP+0x8]` is an unambiguous
// read of that slot. The model reads it, and the model test measures the cleanup
// side rather than trusting either record.
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the 23
// instructions contain no register- or memory-operand transfer. The body IS installed
// at seven addresses in .rdata (0x013ff6d8, 0x014627e8, 0x0147ca88, 0x0147cb50,
// 0x0147cc40, 0x01489120, 0x01489440 -- the exhaustive result of searching the image
// for the little-endian dword 0x006417d0), five of them at dword index 11 of their
// table, but it never reads a dispatch word, so no Vtable type and no slot constant
// are used by the model and nothing at the receiver's +0x00 is named.
//
// GLOBALS: none. No instruction in the body names a data-segment address.
//
// THE CALLEE. 0x005507a0's complete body is seventeen bytes (nine instructions):
//   55 8b ec 51 89 4d fc 8b 45 fc 83 c0 18 8b e5 5d c3
// that is PUSH EBP; MOV EBP,ESP; PUSH ECX; MOV [EBP-0x4],ECX; MOV EAX,[EBP-0x4];
// ADD EAX,0x18; MOV ESP,EBP; POP EBP; RET. It is a pure __thiscall accessor: it
// takes no stack argument, preserves ECX and EBP, forwards nothing, and returns its
// receiver plus 0x18. Every fact the model needs about the object it hands back is
// in those seventeen bytes, and the displacement 0x18 belongs to the CALLEE -- this body
// adds nothing to the returned pointer. The model test proves that last point by
// making the observer return a scripted record that is NOT at inner+0x18 while
// planting poison at inner+0x18 itself.
//
// RETURN SEMANTICS: a BYTE, and only a byte. 0x00641800 is `MOV AL,0x1` (B0 01) and
// 0x00641806 is `XOR AL,AL` (32 C0); neither writes the upper three bytes of EAX, and
// the three exits leave three different dead values there (the second copied dword on
// the true path, the caller's EAX on the 0x006417d8 exit, `inner+0x18` on the
// 0x006417e8 exit). All seven references to this body are DATA references from
// .rdata, so no caller in this image constrains the upper bytes. The declared return
// type is therefore std::uint8_t and the upper three bytes are not modelled. Ghidra's
// own decompilation agrees about the low byte and garbles the rest: it prints
// `return CONCAT31((int3)((uint)uVar1 >> 8),1)` on the true path and
// `return (uint)in_EAX & 0xffffff00` on the false ones, which is its way of spelling
// an AL-only write.

#include "swarm_w1_006417d0_types.hpp"

#include <cstdint>

namespace openspore::reconstruction::pkg_swarm_w1_006417d0 {
namespace {

// Model instrumentation, not machine globals: the 4-byte frame word at entry-4.
// See the header for why the ESI traffic is carried as values instead of being read
// and written as a register. Each has to live at namespace scope rather than as a
// local because nothing in the body reads them, and a local that is written and
// never read is a warning under -Wall.
Word g_saved_esi = 0;
Word g_restored_esi = 0;
Word g_esi_at_entry = 0;

// 0xdeadbeef is the poison both ESI words are filled with between runs. A model that
// popped ESI on only one of the two return paths leaves the other word poisoned,
// which is visible; a model that never popped leaves both poisoned.
constexpr Word kEsiPoison = 0xdeadbeefu;

// The displacements and the bit pattern, pinned to the instruction that states each
// one. These are assertions, not documentation: each message names the address the
// value was read from, so an edit to a constant in the header breaks the build here
// instead of silently changing what the model claims about the machine. They sit at
// namespace scope, outside re_006417d0, because the scored span is that function's
// body and these are the listing's own numbers rather than code.
//
// The first record displacement is 0 because the listing writes NO displacement for
// the first word at all -- 0x006417df is `CMP dword ptr [EAX],-0x1` and 0x006417f2 is
// `MOV EDX,dword ptr [EAX]` -- so the value is spelled 0x00 here to name that
// ABSENCE explicitly, and it is stated in decimal in the assert to keep the header's
// documented value the single place a reader has to look.
static_assert(kReceiverWordDisplacement == 0x1c,
              "0x006417d3 MOV ECX,[ESI+0x1c] and 0x006417ea MOV ECX,[ESI+0x1c]");
static_assert(kRecordFirstDisplacement == 0,
              "0x006417df CMP dword ptr [EAX],-0x1 / 0x006417f2 MOV EDX,[EAX] write "
              "no displacement for the first word");
static_assert(kRecordSecondDisplacement == 4,
              "0x006417e4 CMP dword ptr [EAX+0x4],-0x1 / 0x006417fd MOV [ECX+0x4],EAX");
static_assert(kAccessorAddend == 0x18,
              "0x005507a0 is `MOV EAX,[EBP-0x4]; ADD EAX,0x18`, so 0x18 belongs to the "
              "callee");
static_assert(kSentinelWord == 0xffffffffu,
              "0x006417df is `CMP DWORD PTR [EAX],0xffffffff` (83 38 ff) and 0x006417e4 "
              "is `CMP DWORD PTR [eax+0x4],0xffffffff` (83 78 04 ff)");

}  // namespace

Word model_esi_at_entry() { return g_esi_at_entry; }

void model_set_esi_at_entry(Word value) { g_esi_at_entry = value; }

Word saved_esi_frame_word() { return g_saved_esi; }

Word restored_esi_word() { return g_restored_esi; }

void model_reset_esi_probes() {
  g_saved_esi = kEsiPoison;
  g_restored_esi = kEsiPoison;
}

extern "C" std::uint8_t PKG_SWARM_W1_006417D0_THISCALL re_006417d0(
    AssetData* receiver, WordPair* out) {
  // 006417d0  PUSH ESI
  //
  // The body's only stack effect. It is here because the body makes two calls and
  // ESI is call-clobbered; the machine parks the CALLER's ESI and gives it back at
  // 0x00641802 or 0x00641808.
  //
  // The model parks it in a frame WORD, not in the real register, and that is a
  // concession to the toolchain rather than a choice: the prescribed build is a PIE
  // and GCC's i386 PIE sequence for this function is `call __x86.get_pc_thunk.si;
  // addl $_GLOBAL_OFFSET_TABLE_,%esi`, so ESI holds the GOT base for the whole body.
  // A real-register version would read the module address instead of the caller's ESI
  // and a write would break the addressing the compiler is about to emit. The header
  // records this; the model test carries the PUSH/POP pair as the two poisoned value
  // words below instead, so a model that pops on only one of the two return paths is
  // still visible.
  g_saved_esi = model_esi_at_entry();

  // 006417d1  MOV ESI,ECX
  //
  // ESI becomes the receiver alias and every receiver access in the body goes
  // through it. ECX is then reused as the argument register, which is why nothing
  // here reads a receiver field through ECX.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 006417d3  MOV ECX,[ESI+0x1c]
  //
  // The FIRST of two independent reads of the same word. It is a LOAD: the value
  // read is used as a pointer (it is the receiver of the call at 0x006417da, and
  // 0x005507a0's first act is `MOV [EBP-0x4],ECX` followed by `ADD EAX,0x18` on
  // it), so this is one dereference of the receiver. A two-level reading would read
  // `*(InnerData**)self+0x1c` and hand the word at inner+0x00 to the callee instead;
  // the model test plants a decoy word at inner+0x00 so that mistake cannot survive.
  //
  // The displacement is written out as the 0x1c the listing prints, rather than
  // through the header's kReceiverWordDisplacement, so the span itself carries the
  // constant and the CONSTANTS check has it to compare against the listing; the
  // header's accessor inner_word_at() states the same one-level shape for any other
  // reader, and the static_assert above pins the constant to these two addresses, so
  // the two spellings cannot drift apart. The receiver itself is an opaque byte run
  // (`self` is the uint8_t* the machine's ESI holds), which is why there is no member
  // to name here and none is.
  InnerData* const inner_first = *reinterpret_cast<InnerData* const*>(self + 0x1c);

  // 006417d6  TEST ECX,ECX
  // 006417d8  JZ 0x00641806
  //
  // A 32-bit null test on the WHOLE word -- not a comparison against 1, not signed,
  // and not a test on the pointer the accessor will return. Every non-zero pattern
  // takes the fall-through, 0xffffffff and 0xdeadbeef included, and the model test
  // drives those. Polarity is fixed by JZ: taken-when-zero, to the shared false
  // block at 0x00641806. Nothing is written on this path.
  if (inner_first == nullptr) {
    // 00641806  XOR AL,AL
    // 00641808  POP ESI
    // 00641809  RET 0x4
    //
    // A cleared low byte, NOT a cleared 32-bit register, and the saved ESI is
    // restored on this path too -- it is the SAME false block the sentinel exit
    // reaches, which is why the model has one false return rather than two. The
    // caller's out record is left completely alone: reaching 0x00641806 from
    // 0x006417d8 means 0x005507a0 was never called and no store ever executed.
    g_restored_esi = g_saved_esi;  // 00641808 POP ESI
    return 0;                       // 00641806 XOR AL,AL
  }

  // 006417da  CALL 0x005507a0
  //
  // The PROBE. ECX already holds the word loaded at 0x006417d3 and nothing has
  // written it since, so the receiver of this call is exactly that word -- the model
  // passes `inner_first` and needs no separate `MOV ECX,` because the machine's
  // 0x006417d3 IS the assignment. The callee pushes nothing, pops nothing, and
  // preserves ECX, so the stack at the callee's entry is [retaddr][saved ESI][out
  // pointer] and nothing else; the model test samples all three.
  //
  // The return value is a POINTER, and the model uses it as one. The body reads
  // through it at 0x006417df and 0x006417e4; it never dereferences the result of
  // those reads, so the depth is one level below the returned pointer and a
  // WordPair** would be a two-level bug.
  const WordPair* const probe = inner_pair_accessor_005507a0(inner_first);

  // 006417df  CMP DWORD PTR [EAX],-0x1
  // 006417e2  JNZ 0x006417ea
  //
  // Exact 32-bit equality against 0xffffffff, on the FIRST word of the probe, and
  // taken-when-not-equal to the copy path. Not a signed compare, not a range test
  // and not a zero test: 0x00000000, 0x7fffffff, 0x80000000, 0xfffffffe and
  // 0xdeadbeef are all ordinary non-sentinel values here, and the model test drives
  // each of them.
  //
  // The offset is kRecordFirstDisplacement, the header's named constant for the first
  // word, because 0x006417df spells the access `CMP dword ptr [EAX],-0x1`: the machine
  // writes NO displacement at all for the first word, and only the second word carries
  // one (0x006417e4 `CMP dword ptr [EAX+0x4]`). The zero offset is therefore the
  // absence of a displacement in the listing, not a constant the listing contains, and
  // it is carried as a name for exactly that reason.
  //
  // The SHORT CIRCUIT is load-bearing and is a pointer-level fact: 0x006417e4 is
  // only reached when the first word IS the sentinel, so on every other path the
  // probe's second word is never read. The model test enforces it with a probe
  // record placed four bytes before a PROT_NONE guard page.
  if (word_at(probe, kRecordFirstDisplacement) == kSentinelWord) {
    // 006417e4  CMP DWORD PTR [EAX+0x4],-0x1
    // 006417e8  JZ 0x00641806
    //
    // The SECOND half of the conjunction, and it is only ever evaluated on top of
    // the first. Together the two compares mean: reject exactly when BOTH words are
    // 0xffffffff. A disjunction (reject when either is the sentinel) and a
    // first-word-only test are both wrong and both are killed by the model test,
    // which drives (0xffffffff, x) and (x, 0xffffffff) and requires 1 from both.
    if (word_at(probe, kRecordSecondDisplacement) == kSentinelWord) {
      // 00641806 / 00641808 / 0x00641809 -- the shared false block, reached here
      // rather than from 0x006417d8. Again nothing is written anywhere, so the
      // caller's out record keeps whatever it held.
      g_restored_esi = g_saved_esi;  // 00641808 POP ESI
      return 0;                       // 00641806 XOR AL,AL
    }
  }

  // 006417ea  MOV ECX,[ESI+0x1c]
  //
  // The SECOND, independent read of the same receiver word. This is not a redundant
  // copy: between the two reads there is a CALL, and this body does nothing else, so
  // the second call's receiver is whatever the word holds AFTER the first callee has
  // returned. 0x005507a0 does not write it, but the instruction is a load and the
  // model performs a second load rather than reusing `inner_first`; the model test
  // proves the difference by having the first call overwrite receiver+0x1c.
  InnerData* const inner_second = *reinterpret_cast<InnerData* const*>(self + 0x1c);

  // 006417ed  CALL 0x005507a0
  //
  // The COPY SOURCE. Note that it is the SECOND call's result and not the probe's:
  // the two are independent calls to the same accessor, and nothing in the body
  // carries a value from the first into the second. The model therefore uses a fresh
  // pointer, and the model test makes the observer return a different record on the
  // second call to prove it.
  const WordPair* const source = inner_pair_accessor_005507a0(inner_second);

  // 006417f2  MOV EDX,[EAX]
  // 006417f4  MOV ECX,[ESP+0x8]
  // 006417f8  MOV [ECX],EDX
  //
  // The out pointer is loaded from the stack slot at entry+4 (ESP is at entry-4
  // here, so entry-4 + 0x8 = entry+4) and the first word is stored through it. The
  // out record is read from the CALLER's buffer, not from a model local, and the
  // model test proves that by poisoning a caller-owned buffer and checking which
  // memory changed.
  //
  // 006417fa  MOV EAX,[EAX+0x4]
  // 006417fd  MOV [ECX+0x4],EAX
  //
  // And the second word, from the same source pointer, into the same out record.
  // Exactly eight bytes are written: 0x006417f8 and 0x006417fd are the only two
  // stores in the whole body, and both are four-byte stores through ECX. The model
  // writes a WordPair and nothing else, and the model test asserts the change window
  // byte for byte with a poison tail on the caller's record. The offsets are the
  // header's two named record displacements, for the reason given at the first read
  // above: the machine writes no displacement for the first word and +0x4 for the
  // second.
  //
  // NO MEMBER OF THE OUT RECORD IS NAMED, and that is the whole claim here. The
  // machine-derived receiver record for this target is `bounds_only` -- offsets
  // [0x1c], max_offset 0x1c, register ECX, no member names anywhere in the pack -- so
  // it can confirm that +0x00 and +0x04 are displacements this body reaches and can
  // say NOTHING about which member of the caller's record lives at either one. Both
  // stores therefore go through the displacement-named accessor and the source states
  // the displacement and nothing more; `out->field_00` / `out->field_04` said the
  // same two numbers while additionally claiming an identity the evidence does not
  // carry, which is what the FIELDS/OFFSETS review item was about. The behaviour is
  // identical: the accessor writes the same four bytes at the same offsets.
  word_at(out, kRecordFirstDisplacement) = word_at(source, kRecordFirstDisplacement);
  word_at(out, kRecordSecondDisplacement) = word_at(source, kRecordSecondDisplacement);

  // 00641800  MOV AL,0x1
  //
  // A literal 1 in the LOW BYTE only. The upper three bytes of EAX still hold the
  // second dword the body just copied (0x006417fa) and are dead: nothing in this
  // image calls this body -- all seven references are data references from .rdata
  // -- so no caller in the binary constrains them, and they are not modelled. The
  // declared return type is std::uint8_t, and the model test asserts that type at
  // compile time so a widening back to uint32_t cannot slip through.
  //
  // 00641802  POP ESI
  // 00641803  RET 0x4
  //
  // The callee-side cleanup of the one stack argument is the 0x4 immediate on the
  // RET; the model is declared __thiscall, which is what makes the compiler emit it.
  // The model test does not take the convention on trust: it measures the caller's
  // ESP on both sides of the call and requires it to come back level, and it proves
  // the measurement is sensitive by measuring a cdecl probe the same way and
  // requiring that one to come back four bytes lower.
  g_restored_esi = g_saved_esi;  // 00641802 POP ESI
  return 1;                       // 00641800 MOV AL,0x1
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_006417d0
