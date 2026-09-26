#include "dogfood_00580cb0_a1.hpp"

// The header undefines its convention macros at the end, so the implementation
// restates them before it declares anything.
#if defined(_MSC_VER)
#define PKG_DF5_THISCALL __thiscall
#define PKG_DF5_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_DF5_THISCALL __attribute__((thiscall))
#define PKG_DF5_CDECL __attribute__((cdecl))
#else
#error "PKG-DOGFOOD-00580CB0-A1 requires an MSVC or GCC calling convention"
#endif

#if defined(_MSC_VER)
#define PKG_DF5_ALWAYS_INLINE __forceinline
#else
#define PKG_DF5_ALWAYS_INLINE __attribute__((always_inline)) inline
#endif

namespace openspore::reconstruction::pkg_dogfood_00580cb0_a1 {

// The two format strings, at the two absolute addresses the body pushes.
// 0x00580ccd pushes 0x013f5c74 and 0x00580ce9 pushes 0x013f5c68. These two
// objects carry the CONTENT read at those addresses; the body itself pushes the
// addresses, so the call sites below pass the address literals rather than
// these objects. A translation unit cannot link against the original image, so
// the immediates are reproduced exactly as the machine encodes them, which
// keeps the address in the code instead of only in a comment.
const OpaqueChar kFmtDbTmp[] = u"%s.db.tmp";
const OpaqueChar kFmtDb[] = u"%s.db";

// The body pushes two further data addresses, 0x01897c18 (three times, at
// 0x00580d22, 0x00580d27 and 0x00580d2c) and 0x0150d100 (once, at 0x00580d77),
// and the constant 0x1a80d26 (once, at 0x00580d72). None of the three is
// dereferenced by this body, so there is nothing here to model but the address
// itself, and the call sites below pass each immediate literally for that
// reason. What the addresses hold is recorded in the header: the twenty-four
// bytes read at 0x01897c18 are a dword table whose entries rise in a constant
// stride of eight, and the twenty-four bytes read at 0x0150d100 are zero.

namespace detail {

// The six indirect dispatches of the body are MOV/CALL pairs through a table
// word, with the receiver moved into ECX immediately before the call. These
// helpers restate exactly that shape with inline asm, so the emitted code keeps
// a register-indirect call and an ECX receiver instead of being rewritten into
// something the machine never contained. They are always inlined so the six
// pairs appear in the body of the entry rather than behind six calls of their
// own.
//
// The result is returned through memory rather than a register because EAX is
// both an input to the ABI here and the register the callee produces, so naming
// it as a register output would be a constraint the compiler cannot honour.
template <typename Function>
PKG_DF5_ALWAYS_INLINE void call_slot_void(Function function, void *receiver) {
  __asm__ volatile(
      "movl %0, %%ecx\n\t"
      "call *%1\n\t"
      :
      : "r"(receiver), "r"(function)
      : "eax", "ecx", "edx", "cc", "memory");
}

template <typename Function>
PKG_DF5_ALWAYS_INLINE OpaqueWord call_slot_word(Function function,
                                                void *receiver) {
  OpaqueWord result = 0u;
  __asm__ volatile(
      "movl %1, %%ecx\n\t"
      "call *%2\n\t"
      "movl %%eax, %0\n\t"
      : "=m"(result)
      : "r"(receiver), "r"(function)
      : "eax", "ecx", "edx", "cc", "memory");
  return result;
}

template <typename Function>
PKG_DF5_ALWAYS_INLINE void *call_slot_pointer(Function function,
                                              void *receiver) {
  void *result = nullptr;
  __asm__ volatile(
      "movl %1, %%ecx\n\t"
      "call *%2\n\t"
      "movl %%eax, %0\n\t"
      : "=m"(result)
      : "r"(receiver), "r"(function)
      : "eax", "ecx", "edx", "cc", "memory");
  return result;
}

}  // namespace detail

// 0x00580cb0, 307 bytes, 91 instructions, 12 outgoing direct-call edges and no
// incoming direct-call edge.
//
// Raw bytes read from SporeApp.exe 3.1.0.22 at 0x00580cb0 this attempt; the
// same 307 bytes and the same 91 instructions came back from the disassembler,
// so the listing and the byte image agree:
//
//   b824100000 e846fac500 5657 8d442418 50 8bf9 e848ffffff
//   8d4c241c 51 68745c3f01 8d942424020000 6800010000 52 e84c8d3b00
//   8d44242c 50 68685c3f01 8d8c2434040000 6800010000 51 e8308d3b00
//   8d94243c020000 52 e893821000 8bf0 83c428 85f6 0f8489000000
//   8b06 8b10 8bce ffd2 68187c8901 68187c8901 68187c8901 56 8d4c241c
//   e825301100 8d4c240c e85c211100 8b4c2414 8b01 8b5020 ffd2 8b10
//   8bc8 8b4218 8c7442408010000 ffd0 6a00 6a01 8d4c2410 51 50 e8019d3b00
//   83c410 68260da801 6800d15001 57 8d8c2424060000 e807221100
//   8b542414 52 8d8c241c060000 e8661b1100 8d4c240c e85d2b1100
//   8b4604 8b501c 8d7e04 8bce ffd2 8b07 8b5008 8bce ffd2
//   8d842418040000 50 8d8c241c020000 51 e822841000 8b16 8b4204
//   83c408 8bce ffd0 5f 5e 81c424100000 c3
//
// What the body proves, and what this reconstruction relies on:
//
//   - One receiver, in ECX, and nothing else. "MOV EDI,ECX" at 0x00580cc1 is
//   the
//     only instruction that reads the incoming ECX, and "PUSH EDI" at
//     0x00580d7c is the only place that copy is used. The receiver is never
//     dereferenced: no instruction in the span loads or stores through it.
//   - Zero ordinary stack arguments. Every [ESP + k] operand resolves below the
//     entry stack pointer. The persisted ABI inference lists eight candidate
//     stack slots and marks every one of them read:false and written:false,
//     which is the same statement from a different tool.
//   - Twelve direct calls, matching the twelve outgoing edges in the Ghidra
//   xref
//     export, and six register-indirect calls, one per vtable slot.
//   - Six vtable slots, at byte offsets 0x00 and 0x04 of the table reached
//     through the handle's first word, 0x1c and 0x08 of the table reached
//     through the handle's second word, 0x20 of the table reached through the
//     frame object's field +0x08, and 0x18 of the table reached through what
//     that returns.
//   - Four absolute data addresses, pushed as immediates: 0x013f5c74,
//   0x013f5c68,
//     0x01897c18 three times over, and 0x0150d100. The immediate 0x1a80d26 is a
//     constant rather than an address.
//   - Exactly one branch, the forward JZ at 0x00580d14, so three basic blocks:
//     0x00580cb0..0x00580d14, 0x00580d1a..0x00580d9e and
//     0x00580da3..0x00580de2.
//   - ESI and EDI are the only saved registers, pushed at 0x00580cba/0x00580cbb
//     and popped at 0x00580dda/0x00580ddb. There is no EBP frame.
//
// Return semantics, read from the instruction stream rather than from the
// decompilation: the last instruction that produces a value is "MOV EAX,[EDX +
// 0x4]" at 0x00580dd0 feeding "CALL EAX" at 0x00580dd8, and the only
// instructions after that call are POP EDI, POP ESI, ADD ESP,0x1024 and RET,
// none of which touches EAX. So the dword that the table slot +0x04 of the
// handle returns in EAX leaves the frame untouched, and that dword is the
// return value of this method.
//
// That cannot be measured the way a directly called function's can, because the
// body has no direct call sites at all: it is entered only through the table
// word at 0x013f57f8 + 0x54. So the return is reported as the dword the final
// dispatch leaves in EAX, with no claim about how the indirect callers consume
// it. The Ghidra record types the function as undefined, which is consistent
// with the machine and is not evidence of a void return.
//
// The Ghidra decompilation of this body reads
//   void __fastcall FUN_00580cb0(undefined4 param_1)
// and four defects in it are corrected here, each recorded in the sidecar.
//
// First, the convention. __fastcall is wrong: EDX is never read and never
// forwarded. So is the parameter: Ghidra reports "param_1" at
// register:00000004:4, which is its reading of the ECX value, but the body
// forwards that value as the first stack argument of 0x00692f90 and reads no
// entry stack slot, so it is a receiver.
//
// Second, the receivers of three calls. Ghidra gives 0x00693d60 the handle as
// its first argument and no receiver at all, gives 0x00692f90 "param_1" as its
// first argument and no receiver at all, and gives 0x00692900 and 0x00693900 no
// arguments whatsoever. All four are thiscall and all four take a stack object
// this body builds: 0x00693d60 and 0x00693900 take the twelve byte object at
// frame +0x004, and 0x00692f90 and 0x00692900 take the object at frame +0x610.
// That is why the decompilation never mentions the +0x610 object at all, and
// reads those two calls as free functions.
//
// Third, the frame. The decompilation renders three of the frame's objects as
// unrelated byte arrays, local_1014, local_e14 and local_c14, and never shows
// that the twelve byte object at 0x004 is one object with a vtable word, a word
// at +0x04 and a pointer at +0x08. The decompilation does connect
// "auStack_1024" and "piStack_1018" to the right words, so that part is
// evidence, not a defect.
//
// Fourth, the return. The decompilation types the function void. The machine
// leaves the final dispatch's EAX untouched through the epilogue.
//
// Two things the decompilation gets RIGHT are worth keeping as evidence rather
// than correcting. It renders the tail's two peer dispatches and the promote
// call outside the "if (piVar1 != 0)" block, so its output independently shows
// that the null result is dereferenced anyway. And it names both format strings
// correctly, which is what fixed the order of the two destinations here.
//
// The unguarded dereference is the one that matters, and this model reproduces
// it rather than repairing it. The tail at 0x00580da3 is reached both by
// falling out of the guarded block and by the JZ itself, and its first
// instruction is "MOV EAX,dword ptr [ESI + 4]". So when 0x00688fa0 returns
// null the original dereferences null. That is what the bytes say, and a model
// that added a guard there would be modelling a different function.
extern "C" OpaqueWord PKG_DF5_THISCALL
dogfood_editor_commit_fun_00580cb0(OpaqueEditorCommitOwner *self) {
  // Left uninitialised on purpose: the 91 instructions contain no zero fill,
  // and every word the model later reads is written by a call or by the store
  // below.
  OpaqueCommitFrame frame;

  // 0x00580cbc/0x00580cc3: fill the base buffer at frame +0x010.
  unresolved_00580c10(frame.base_path);

  // 0x00580ccc..0x00580cdf: format the temporary name into frame +0x210. The
  // three pushed immediates are the element count 0x100 and the address
  // 0x13f5c74, whose content is kFmtDbTmp, L"%s.db.tmp".
  unresolved_00939a30(frame.db_tmp_path, 0x100,
                      reinterpret_cast<const OpaqueChar *>(0x13f5c74u),
                      frame.base_path);

  // 0x00580ce8..0x00580cfb: format the final name into frame +0x410 with the
  // same count 0x100 and the address 0x13f5c68, whose content is kFmtDb,
  // L"%s.db".
  unresolved_00939a30(frame.db_path, 0x100,
                      reinterpret_cast<const OpaqueChar *>(0x13f5c68u),
                      frame.base_path);

  // 0x00580d00..0x00580d0d: open the temporary. 0x00688fa0 is cdecl and returns
  // the object in EAX, which becomes ESI.
  OpaqueHandle *handle = unresolved_00688fa0(frame.db_tmp_path);

  // 0x00580d12/0x00580d14: the only branch. Taken when the handle is null, and
  // it jumps to 0x00580da3, which is the first instruction of the tail rather
  // than the end of the function.
  if (handle != nullptr) {
    // 0x00580d1a..0x00580d20: slot +0x00 of the table at [handle + 0x00]. No
    // instruction was pushed, so the call takes no stack argument.
    detail::call_slot_void(handle->vtable_00->slot_00, handle);

    // 0x00580d22..0x00580d36: construct the twelve byte object at frame +0x004
    // from the handle and the address 0x1897c18, which is pushed three times as
    // the second, third and fourth arguments. 0x00693d60 pops all four itself.
    // The address is never dereferenced here, so the same immediate is written
    // three times exactly as the machine writes it three times.
    const auto *const kCommitTableAddr =
        reinterpret_cast<const OpaqueWord *>(0x1897c18u);
    unresolved_00693d60(&frame.context, handle, kCommitTableAddr,
                        kCommitTableAddr, kCommitTableAddr);

    // 0x00580d3b/0x00580d3f: the predicate on field +0x08. Its dword result is
    // discarded: 0x00580d44 overwrites ECX and nothing reads EAX before the
    // next call.
    (void)unresolved_00692ea0(&frame.context);

    // 0x00580d44: read field +0x08 back out of the object at frame +0x004.
    OpaqueContextField08 *field_08 = frame.context.field_08;

    // 0x00580d48..0x00580d4d: slot +0x20 of field +0x08's own table. The result
    // is a polymorphic object, which 0x00580d4f proves by reading [EAX].
    void *const sub =
        detail::call_slot_pointer(field_08->vtable_00->slot_20, field_08);
    OpaqueSlot20Result *const nested = static_cast<OpaqueSlot20Result *>(sub);

    // 0x00580d4f..0x00580d53: slot +0x18 of the table at [nested], with the
    // receiver moved into ECX. The table word is loaded before the store below,
    // so the two are ordered exactly as the original orders them.
    const auto dispatch_18 = nested->vtable_00->slot_18;

    // 0x00580d56: store 1 into frame +0x000, the word the probe left its return
    // address copy in. It sits between the load above and the call below, and
    // it is the address handed to 0x0093aa70 as its second argument.
    frame.one = 0x1u;

    // 0x00580d5e: the dispatch, then 0x00580d60..0x00580d6a push the four
    // arguments of 0x0093aa70 in reverse: 0x0, 0x1, the address of the word
    // just stored, and the word slot +0x18 returned. 0x0093aa70 is cdecl and
    // the body reclaims the four words itself with ADD ESP,0x10.
    void *const produced = detail::call_slot_pointer(dispatch_18, nested);
    (void)unresolved_0093aa70(static_cast<OpaqueSlot18Result *>(produced),
                              &frame.one, 0x1u, 0x0u);

    // 0x00580d72..0x00580d84: the receiver is the object at frame +0x610. The
    // three stack arguments are the constant 0x1a80d26 (kCommitTag), then the
    // address 0x150d100, then the original receiver. 0x00692f90 pops all three
    // and returns its own receiver in EAX, which nothing here reads. Neither
    // 0x1a80d26 nor 0x150d100 is dereferenced by this body.
    (void)unresolved_00692f90(&frame.sink, self,
                              reinterpret_cast<const OpaqueWord *>(0x150d100u),
                              0x1a80d26u);

    // 0x00580d89..0x00580d95: the same object at frame +0x610, with field +0x08
    // read back out of the frame object as the one stack argument. 0x00692900
    // pops it and its dword result is discarded.
    (void)unresolved_00692900(&frame.sink, field_08);

    // 0x00580d9a/0x00580d9e: destroy the twelve byte object at frame +0x004.
    unresolved_00693900(&frame.context);
  }

  // 0x00580da3..0x00580db7: the tail, reached by fall-through AND by the JZ at
  // 0x00580d14, with no test of the handle. The receiver of both calls is the
  // word at [handle + 0x4], which is a second polymorphic object with its own
  // table, not a second entry of the handle's table.
  detail::call_slot_void(handle->peer_04->vtable_00->slot_1c, handle->peer_04);
  detail::call_slot_void(handle->peer_04->vtable_00->slot_08, handle->peer_04);

  // 0x00580db9..0x00580dc9: two arguments, the temporary name then the final
  // name in push order, so the temporary is the source. 0x006891f0 is cdecl and
  // the body reclaims the two words itself with ADD ESP,0x8.
  unresolved_006891f0(frame.db_tmp_path, frame.db_path);

  // 0x00580dce..0x00580dd8: slot +0x04 of the table at [handle + 0x00]. Its
  // dword result in EAX is what leaves the frame, because nothing after this
  // call touches EAX.
  return detail::call_slot_word(handle->vtable_00->slot_04, handle);
}

}  // namespace openspore::reconstruction::pkg_dogfood_00580cb0_a1
