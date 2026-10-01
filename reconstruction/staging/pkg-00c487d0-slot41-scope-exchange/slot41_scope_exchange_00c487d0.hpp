#pragma once

// Reconstruction of FUN_00c487d0 @ 0x00c487d0 (SporeApp.exe 3.1.0.22, binary
// sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// EVIDENCE BASIS
// -------------
// The whole of section 05/06 of reconstruction/evidence/00c487d0 (96
// instructions, 0x00c487d0..0x00c488f1) plus the four GLOBALS rows in
// knowledgegraph/triage/datarefs-2540f2ca.tsv:
//
//   00c487d0..00c488f1  disassembly, read from the live bridge
//   00c487d0            MOV EAX,dword ptr [ESI]            ; EAX = this->f00
//   00c487da            MOV EDX,dword ptr [EAX + 0xa4]     ; EDX = table[0xa4]
//   00c487e1            CALL EDX                           ; __thiscall, 0 stack args
//   00c487e3            MOV ECX,dword ptr [0x016e0d08]     ; OBS-0014 (GLOBALS row)
//   00c487e9            MOV EDX,dword ptr [ECX + 0x18]     ; save
//   00c487ec            MOV dword ptr [ECX + 0x18],ESI     ; publish self
//   00c487ef            MOV ECX,dword ptr [0x016e0d08]     ; OBS/GLOBALS row
//   00c487f5            MOV dword ptr [ESP + 0x20],EDX     ; stash the saved word
//   00c487f9            MOV EDX,dword ptr [ECX + 0x48]     ; save
//   00c487fc            MOV dword ptr [ESP + 0x18],EAX     ; stash the slot-41 result
//   00c48800            MOV dword ptr [ESP + 0x24],EDX     ; stash the saved word
//   00c48804            MOV dword ptr [ECX + 0x48],EAX     ; publish the result
//   00c48807            CALL 0x01021260                    ; no arguments
//   00c4880c/0e         TEST EAX,EAX / JZ 0x00c48818
//   00c48810            MOV EBP,dword ptr [EAX + 0x13c]    ; or
//   00c48818            XOR EBP,EBP                        ; zero when null
//   00c4881c/0x23       CALL 0x00c452a0 / 0x00c451e0      ; both with ECX = self
//   00c48828            LEA ECX,[ESP + 0x28]               ; receiver for 0x006b5060
//   00c48835..0x3f      MOV EAX,[ESI+0x17c] / TEST / JZ / MOV ESI,EAX
//   00c48841/0x48       CALL 0x00aed4d0                    ; twice, no arguments
//   00c48862            CALL 0x01021300                    ; no arguments
//   00c4887b            CALL EDX   (ECX = first accessor, slot +0x24 of its table)
//   00c48891            CALL EDX   (ECX = second accessor, slot +0x0c of its table)
//   00c48893/0x97       LEA ECX,[ESP + 0x28] / CALL 0x006b55c0
//   00c4889c..0xbb      CMP word ptr [EAX],0 / ADD ECX,0x2 loop / SUB / SAR 0x1 / LEA
//   00c488c1/0xc5/0xc6  MOV ECX,[ESP + 0x4c] / PUSH EAX / CALL 0x00423650
//   00c488cb/0xd8       MOV EDX/ ECX,dword ptr [0x016e0d08]  ; GLOBALS rows
//   00c488d5            MOV dword ptr [EDX + 0x18],EAX     ; restore
//   00c488e2            MOV dword ptr [ECX + 0x48],EDX     ; restore
//   00c488e5/0xe9       LEA ECX,[ESP + 0x18] / CALL 0x006b5240
//   00c488ee/0xf1       ADD ESP,0x40 / RET 0x8
//
// Callee conventions confirmed by decompiling the callees themselves (each is a
// __thiscall or a nullary cdecl; none of them pops 0x00c487d0's own frame):
//   0x01021300  undefined4 FUN_01021300(void)   - nullary cdecl, pops nothing
//   0x01021260  undefined4 FUN_01021260(void)   - nullary cdecl, reads a global
//   0x00c452a0 / 0x00c451e0  __fastcall f(this) - thiscall, 0 stack args
//   0x006b5060 / 0x006b55c0 / 0x006b5240  __fastcall f(this) - thiscall on the
//       0x14-byte local wrapper; the ctor writes +0x00,+0x04,+0x08,+0x0c and
//       two bytes at +0x10/+0x11, and 0x006b55c0 hands back the wide pointer
//       stored at +0x08, which is why the loop at 00c4889c steps by 2.
//   0x00423650  __thiscall f(this, begin, end)  - copies the wide range
//       [begin, end) into the two-word descriptor at `this`, popping its two
//       stack arguments.  The receiver the body loads for it is [ESP+0x4c].
//
// GLOBALS SIDE CAR - WHAT IT DOES AND DOES NOT SAY
// -------------------------------------------------
// All four datarefs-2540f2ca.tsv rows for this function are the SAME address,
// 0x016e0d08, in mode `read`, at instructions 00c487e3, 00c487ef, 00c488cb and
// 00c488d8. Those are exactly the four `MOV reg,dword ptr [0x016e0d08]` pointer
// loads. The sidecar therefore records a READ of the pointer global 0x016e0d08
// and nothing else; it does NOT record a writing mode anywhere for this target.
// The stores at 00c487ec, 00c48804, 00c488d5 and 00c488e2 are written through a
// register (ECX/EDX) at displacements +0x18 and +0x48, i.e. at 0x016e0d20 and
// 0x016e0d50, which are DIFFERENT addresses from the four recorded rows. This
// package models them as writes to ScopeState::field_18 / field_48 - to the
// object the pointer points at, never to the pointer cell 0x016e0d08 itself.
// No claim is made about 0x016e0d08 being written.
//
// ABI - WHAT IS OBSERVED
// ----------------------
//   __thiscall.  MOV ESI,ECX at 00c487d6 is the receiver copy (OBS-0006), the
//   callee pops the stack arguments (RET 0x8 at 00c488f1, OBS-0054) which rules
//   out cdecl and fastcall, and EBX/EBP/ESI/EDI are pushed and popped in
//   matching pairs. EAX is the return register (RT1) but the last thing written
//   to EAX before the epilogue is 0x00c488a5's POP EBX and the artifact classes
//   it `aggregate_unknown`; the body then falls into ADD ESP,0x40 / RET 0x8 with
//   no value computation, so this reconstruction returns void and reports the
//   EAX question as unresolved rather than inventing a return type.
//   The two popped words are never read. Entry slot 0 (entry ESP+0x4) and slot 1
//   (entry ESP+0x8) are both recorded `observed:false, read:false` by the abi
//   artifact (A1-IMM, S2), so they are modelled as two untyped stack words that
//   only exist to be discarded.
//
// FRAME - RECOVERED BY BALANCING, NOT GUESSED
// -------------------------------------------
// The abi artifact abstained on the frame ("flow_not_modelled: the linear ESP
// walk ends at +44"). The frame below is forced by three independent
// observations and closes exactly:
//   (1) `POP EDI/ESI/EBP/EBX` at 00c488a0..00c488a5 must consume the four
//       prologue pushes, so ESP = entry_ESP - 0x50 entering that block;
//   (2) 0x00423650 is a __thiscall taking exactly two stack words, so its two
//       PUSHes plus its own 8-byte cleanup land ESP on entry_ESP - 0x40, which
//       is also what `ADD ESP,0x40` at 00c488ee requires before `RET 0x8`;
//   (3) with ESP = entry_ESP - 0x40 the two restore reads land on the two words
//       that 00c487f5 / 00c48800 stashed (a save/restore pair), and the destroy
//       receiver `LEA ECX,[ESP + 0x18]` lands on the object 00c48828 built.
// From that base every local the listing touches resolves:
//
//   entry_ESP-0x40  0x00c4882c  result of 0x00c451e0(self)
//   entry_ESP-0x3c  0x00c4885e  table pointer of accessor #1   [EDI]
//   entry_ESP-0x38  0x00c487fc  result of self table slot +0xa4
//   entry_ESP-0x34  0x00c4885a  table pointer of accessor #2   [EBX]
//   entry_ESP-0x30  0x00c487f5  SAVED ScopeState::field_18
//   entry_ESP-0x2c  0x00c48800  SAVED ScopeState::field_48
//   entry_ESP-0x28  0x006b5060  0x14-byte local wrapper (ctor/dtor 0x006b5xxx)
//   entry_ESP-0x14  0x00c4886d  address handed to the slot-+0x24 dispatch
//   entry_ESP-0x08  0x00c488c1  receiver of 0x00423650 (wide-string descriptor)
//   entry_ESP-0x04  0x00c48882  second word of that descriptor
//
// THE ONE DERIVED STEP (stated, not hidden)
// ----------------------------------------
// The dispatch arities are INFERRED, and they are the only non-observable claim
// in this file. Nine stack words are pushed between 0x00c4884d and 0x00c48891
// and both dispatch callees clean up, so their two cleanups sum to 36. The
// split used here is 5 then 4:
//
//   * 5+4 is the split under which EVERY subsequent `[ESP+d]` read lands on a
//     local this package can name - entry_ESP-0x38 (slot-41 result),
//     entry_ESP-0x04 (descriptor tail), entry_ESP-0x34 (accessor #2 table) -
//     and under which the five arguments of the first dispatch are exactly the
//     five pushes emitted in source order 00c48871, 00c4886c, 00c4886b,
//     00c48859, 00c48858, leaving the `LEA ECX,[ESP+0x28]` pushed early at
//     00c48851 to be consumed as the fourth argument of the second dispatch.
//   * 6+3 is arithmetically possible, but it makes one dispatch read
//     `[ESP+0x28]` at entry_ESP-0x30, which is the SAVED field_18 word, and use
//     that as a table pointer. That reading is recorded as a conflict rather
//     than adopted.
// No arity is OBSERVED. If a future differential run disagrees, the arity split
// is the first thing to move.
//
// WHAT IS NOT CLAIMED
// -------------------
// The receiver's class, the meaning of table slot +0xa4, the meaning of
// receiver+0x17c, the meaning of the two `MOV EDI,EAX / MOV EBX,EAX` accessor
// results beyond "two argument-free accessors that each hand back an object
// whose first word is a table pointer", the identity of 0x016e0d08, the meaning
// of the player-data word at +0x13c, the contents of the wide descriptor, and
// the EAX return value. The two unnamed callees' behaviour is modelled through
// injected hooks rather than guessed.

#include <cstddef>
#include <cstdint>
#include <functional>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00c487d0 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00c487d0_slot41_scope_exchange {

using Word = std::uint32_t;

// A code pointer held in a table word. Modelled as an opaque address so a test
// can install a distinct stub per slot without this header inventing a type.
using CodeAddress = std::uintptr_t;

// Displacements read out of the listing. None of these is invented.
inline constexpr std::size_t kReceiverTableWord = 0x00;    // MOV EAX,[ESI]
inline constexpr std::size_t kReceiverReplacement = 0x17c; // MOV EAX,[ESI+0x17c]
inline constexpr std::size_t kReceiverDispatchSlot = 0xa4;  // MOV EDX,[EAX+0xa4]
inline constexpr std::size_t kPlayerDataWord = 0x13c;      // MOV EBP,[EAX+0x13c]
inline constexpr std::size_t kScopeField18 = 0x18;
inline constexpr std::size_t kScopeField48 = 0x48;
inline constexpr std::size_t kAccessor1Slot = 0x24; // MOV EDX,[EAX+0x24]
inline constexpr std::size_t kAccessor2Slot = 0x0c; // MOV EDX,[EAX+0x0c]

// The one absolute address in the body, and the only one the GLOBALS sidecar
// records (four rows, all mode `read`).
inline constexpr Word kScopeStatePointer = 0x016e0d08u;

// Local wrapper built by 0x006b5060 and destroyed by 0x006b5240. Its size is
// taken from the constructor, which writes +0x00..+0x0b as words and +0x10 /
// +0x11 as bytes; the extent below is the smallest 4-aligned size covering
// every access, which is 0x14.
inline constexpr std::size_t kLocalWrapperBytes = 0x14;
inline constexpr std::size_t kLocalWrapperDataWord = 0x08; // wide pointer

// Frame geometry, derived as described in the file comment.
inline constexpr std::size_t kFrameBytes = 0x40;
inline constexpr std::size_t kPrologueSavedWords = 4;  // EBX, EBP, ESI, EDI
inline constexpr std::size_t kStackCleanupBytes = 8;    // RET 0x8

struct Table {
  CodeAddress words[64];
};

// Receiver of 0x00c487d0. Only the two words the body actually reads are
// declared: the table pointer at +0x00 and the replacement pointer at +0x17c.
struct Receiver {
  const Table* table;
  Word field_17c;
};

// The object the 0x016e0d08 pointer cell addresses. Only the two words the body
// saves, publishes and restores are declared.
struct ScopeState {
  Word field_18;
  Word field_48;
};

// Object handed back by each 0x00aed4d0 accessor. The body reads its word 0 and
// then indexes that table; no other member is observed.
struct Accessor {
  const Table* table;
};

// The 0x14-byte local the constructor/destructor pair builds.
struct LocalWrapper {
  Word word_00;
  Word word_04;
  Word word_08;  // wide pointer consumed by the 00c4889c scan
  Word word_0c;
  unsigned char byte_10;
  unsigned char byte_11;
};

// Two-word wide-string descriptor: 0x00423650 copies [begin, end) into it.
struct WideDescriptor {
  Word begin;
  Word end;
};

// Everything the reconstruction is allowed to observe or drive. Each hook
// stands for exactly one callee named in the listing; none of them is invented
// behaviour, and none is called with an argument the listing does not show.
struct Hooks {
  // 00c487e1  CALL EDX, ECX = this, table word at +0xa4, 0 stack arguments.
  std::function<Word(const Receiver* self)> dispatch_slot41;

  // 00c48807 / 00c48862  nullary cdecl callees.
  // `read_player_data` is 0x01021260. Its result is only used as the base of the
  // `+0x13c` load at 00c48810, and only when the result is non-zero - the
  // `TEST EAX,EAX / JZ` pair at 00c4880c/0x00c4880e.
  std::function<Word()> read_player_data;
  std::function<Word(const void* player_data)> read_player_data_word_13c;
  std::function<Word()> read_empire;

  // 00c4881c / 00c48823  __thiscall on self, 0 stack arguments.
  std::function<Word(const Receiver* self)> sub_00c452a0;
  std::function<Word(const Receiver* self)> sub_00c451e0;

  // 00c48830 / 00c48897 / 00c488e9  __thiscall on the local wrapper.
  std::function<void(LocalWrapper* wrapper)> construct_wrapper;
  std::function<const std::uint16_t*(const LocalWrapper* wrapper)> wrapper_data;
  std::function<void(LocalWrapper* wrapper)> destroy_wrapper;

  // 00c48841 / 00c48848  two identical nullary cdecl accessors.
  std::function<const Accessor*()> acquire_accessor;

  // 00c4887b  ECX = accessor #1, table word at +0x24, five stack arguments.
  std::function<Word(const Accessor* accessor, Word arg1, Word arg2, Word arg3,
                   Word arg4, Word arg5)>
      dispatch_accessor1;

  // 00c48891  ECX = accessor #2, table word at +0x0c, four stack arguments.
  std::function<Word(const Accessor* accessor, Word arg1, Word arg2, Word arg3,
                   Word arg4)>
      dispatch_accessor2;

  // 00c488c6  __thiscall, receiver plus the wide range [begin, end).
  std::function<void(WideDescriptor* descriptor, const std::uint16_t* begin,
                   const std::uint16_t* end)>
      assign_range;
};

// Result trace. Every field is a fact the listing fixes; nothing here is
// inferred. `slot41_result`, `sub_00c451e0_result` and the two dispatch
// results are recorded so a test can prove which value reached which argument
// slot instead of merely counting calls.
struct Trace {
  Word slot41_result = 0;
  Word sub_00c451e0_result = 0;
  Word player_data_word_13c = 0;
  Word empire_result = 0;
  Word dispatch_accessor1_result = 0;
  Word dispatch_accessor2_result = 0;

  Word dispatch_accessor1_args[5] = {0, 0, 0, 0, 0};
  Word dispatch_accessor2_args[4] = {0, 0, 0, 0};

  // Which accessor object each dispatch received. The listing calls the same
  // argument-free accessor twice and keeps the two results in EDI and EBX, so
  // dispatch 1 must see the first result and dispatch 2 the second.
  CodeAddress dispatch1_receiver = 0;
  CodeAddress dispatch2_receiver = 0;
  bool receiver_replaced_by_field_17c = false;
  bool wrapper_constructed = false;
  bool wrapper_destroyed = false;
  bool player_data_was_null = false;

  Word published_field_18 = 0;
  Word published_field_48 = 0;
  std::size_t published_field_18_argv = 0;
  std::size_t published_field_48_argv = 0;

  std::size_t wide_code_units = 0;
};

// The reconstructed body. `self` is the ECX receiver; `stack_arg1` and
// `stack_arg2` are the two words RET 0x8 discards and that the body never reads,
// so they are accepted and ignored exactly as the listing does.
// `scope_state_cell` is the model of the cell the body reads at 0x016e0d08: a
// pointer to a pointer to the ScopeState. The four GLOBALS rows are reads, so
// the reconstruction never writes through it; a test proves that by checking the
// cell's value afterwards.
void Simulator_Slot41ScopeExchangeAndDispatch_00c487d0(
    const Receiver* self, Word stack_arg1, Word stack_arg2,
    ScopeState* const* scope_state_cell, Hooks& hooks, Trace& trace);

}  // namespace openspore::reconstruction::pkg_00c487d0_slot41_scope_exchange
