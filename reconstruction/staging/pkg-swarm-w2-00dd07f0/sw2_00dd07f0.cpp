// PKG-SWARM-W2-00DD07F0 -- VA 0x00dd07f0 (FUN_00dd07f0)
//
// The complete body: 68 instructions, 0x00dd07f0..0x00dd08f1 inclusive, 258
// bytes. The listing this was written against was RE-DERIVED from the image for
// this package (objdump over the 0x14c bytes at file offset 0x9c07f0, RVA
// 0x9d07f0) and reproduces the 68 committed instructions at the same addresses
// with the same lengths, branch targets and operand displacements -- see the
// ASCII listing in the header. Nothing here depends on a difference from the
// committed listing, because there is none.
//
// WHAT THE BODY DOES, IN ONE SENTENCE: it chases two pointers out of a dword of
// the receiver, refuses twice on what it finds there, and otherwise writes ONE
// dword of the receiver -- a small code chosen by a two-level switch over the
// receiver's kind word and the record's sub-state word, with three of the arms
// doing nothing at all and one arm asking three callees a question whose answer
// becomes the code.
//
//   kResultDisplacement  (0x8c) receives one of exactly seven values, or is
//                        left alone:
//     0xfffffffe  when *(record+0x10) == 6
//     0xfffffffd  when *(record+0x20) == -1
//     0x7fffffff  the tag arm, when *(receiver+0x88) == 0x53dbcf1
//     0x00000005  the tag arm's other answer
//     0x7fffffff  the three-callee block, when the comparison came back true
//     0x00000005  the three-callee block's other answer
//     0, 1, 2, 3, 4  the switch's own five small codes
//   and it is untouched when the link is null, when the kind word is 3, when the
//   kind word is 0 or greater than 5, or when the sub-state is out of range for
//   the arm the kind word selected.
//
// FRAME, resolved once so every displacement below is a fact. One linear walk of
// ESP through all 68 instructions. Entry ESP is 0 in the walk:
//
//   00dd07f0  PUSH ESI        ESP = -4
//   ...                          (nothing touches ESP for 33 instructions)
//   00dd0871  PUSH EAX        ESP = -8      (the word 0x00401090 ignores)
//   00dd0872  CALL 0x00401090             (bare C3: removes only the return address)
//   00dd0879  CALL 0x004df400             (bare C3: thiscall, no stack argument)
//   00dd087e  PUSH EAX        ESP = -12     (the word 0x004eb930's first argument)
//   00dd087f  CALL 0x004eb930             (bare C3: removes only the return address)
//   00dd0887  ADD ESP,0x8     ESP = -4      (both callees' C3s cannot do it)
//   00dd0814  POP ESI         ESP = 0       (first early return)
//   00dd0835  POP ESI         ESP = 0       (second early return)
//   00dd086c  POP ESI         ESP = 0       (store-2 return)
//   00dd089d  POP ESI         ESP = 0       (three-callee return)
//   00dd08b4  POP ESI         ESP = 0       (store-0 return)
//   00dd08c0  POP ESI         ESP = 0       (store-1 return)
//   00dd08cc  POP ESI         ESP = 0       (store-3 return)
//   00dd08f0  POP ESI         ESP = 0       (the shared epilogue, reached by four
//                                           different no-write paths)
//
// The walk ends at 0 on all seven paths, which balances, and no return site
// carries an immediate: all seven are a bare C3. So the frame holds exactly two
// things and neither is a parameter -- entry-4 is the saved ESI and entry-8 is
// the word pushed at 0x00dd0871. There is no ordinary stack argument slot
// anywhere: the receiver is the hidden `this` in ECX and the only two words ever
// pushed are the two call arguments that 0x00dd0887 drops.
//
// CALLING CONVENTION. The receiver arrives in ECX: 0x00dd07f1 copies it into
// ESI and 0x00dd07f3 dereferences it, while ECX is never dereferenced as the
// receiver again -- it is REUSED, at 0x00dd0801, to hold a level-2 pointer, and
// at 0x00dd0837, to hold the kind word. That is why the record's receiver shape
// is R-ALIAS (base register ECX, but the listing's own receiver operands all name
// ESI) and why a naive ECX-only displacement scan finds nothing in bounds. Both
// candidate conventions in the record are [__thiscall, __fastcall]; __fastcall
// is excluded because the body's only EDX use is the guard constant 0x00dd083e
// sets for its own compares and passes to nobody, so the second fastcall register
// is unused. Ghidra's own prototype says __fastcall with `int param_1`; the
// record and the listing both say __thiscall. The disagreement is recorded, not
// resolved by picking the convenient answer.
//
// CONTROL FLOW. Six conditional branches in the whole body, all with targets
// inside the recovered 258-byte span:
//
//   00dd07fb  JZ  0x00dd08f0   rel32, the null-link exit
//   00dd0808  JNZ 0x00dd0816   rel8,  the record-kind discriminator
//   00dd0829  JNZ 0x00dd0837   rel8,  the sub-state sentinel
//   00dd0845  JA  0x00dd08f0   rel32, the outer index guard
//   00dd0855  JA  0x00dd08f0   rel32, the kind-1 sub-state guard
//   00dd08a1  JA  0x00dd08f0   rel32, the other arm's sub-state guard
//
// plus THREE unconditional indirect transfers, all switch dispatches:
//
//   00dd084b  JMP DWORD PTR [ECX*0x4 + 0xdd08f4]
//   00dd085b  JMP DWORD PTR [EAX*0x4 + 0xdd0908]
//   00dd08a3  JMP DWORD PTR [EAX*0x4 + 0xdd0928]
//
// FIVE of the six conditional branches share the target 0x00dd08f0, the bare
// `POP ESI / RET` tail, which writes nothing. So the single most travelled
// destination in this function is the one that changes nothing. All three tables
// are transcribed word for word in the header, from the bytes at their own bases,
// and the model dispatches on the decoded targets by name.
//
// VIRTUAL DISPATCH: none, and none declared. The three indirect transfers are
// jump-table indices over data the body itself established, not loads of an
// object's slot table: abi_derived.dispatch records vtable_shaped_loads 0 and
// call_offsets [], and the record's four associated data tables come with no slot
// boundary this body establishes. The model therefore declares no slot boundary
// and names nothing at any offset it does not itself read.
//
// GLOBALS: none named by the body. No instruction in the 68 references a
// data-segment address: the jump-table bases 0xdd08f4, 0xdd0908 and 0xdd0928 lie
// in the body's own .text immediately after it, and every other immediate is a
// small value. The data word 0x00401090 returns is the CALLEE's global; it is
// recorded in the header as context and read by nothing here.

#include "sw2_00dd07f0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00dd07f0 {

// Every constant and displacement the model below uses, tied to the instruction
// operand it came from, as a compile-time consequence rather than as a comment.
// The literals in the assertions are the instruction's own operands, so a reader
// can check them against the listing without leaving this file, and a
// reconstruction that changed one would not compile rather than merely fail.
//
// The model's text below then uses the same literals directly, at the
// displacement each instruction names, because that is what makes the code
// checkable against the listing by eye. The per-instruction transcription of the
// two arithmetic blocks, the three decoded jump tables, and every address that is
// NOT an operand of one of the 68 instructions live in the header -- outside this
// span, so that no hexadecimal literal the machine listing does not contain can
// reach the model's own text.
static_assert(0x98u == kLinkDisplacement,
              "0x00dd07f3's displacement, the only word of the receiver this "
              "body follows a pointer out of");
static_assert(0x84u == kKindDisplacement,
              "0x00dd0837's displacement, the outer switch's index word");
static_assert(0x88u == kTagDisplacement,
              "0x00dd08ce's displacement, the word the tag arm tests");
static_assert(0x8cu == kResultDisplacement,
              "the displacement of all nine store sites and of nothing else");
static_assert(0x06u == kRecordKindSentinel,
              "0x00dd0804's immediate: the single word that takes the -2 exit, "
              "because 0x00dd0808 is JNZ");
static_assert(0x01u == kOuterIndexBias,
              "0x00dd083d's DEC is the only bias on the outer index");
static_assert(0x04u == kIndexLimit && 0x04u == kLeftoverGuardWord,
              "0x00dd083e's MOV EDX,0x4 is the outer guard's bound AND, because "
              "nothing overwrites EDX before the bare store, the value that bare "
              "store writes; the model keeps the two roles as two names for one "
              "immediate because the listing uses one register for both");
static_assert(0x07u == kKindOneSubLimit,
              "0x00dd0852's immediate, the bound of the kind-1 table's index");
static_assert(0x04u == kOtherArmSubLimit,
              "0x00dd089f compares against the same EDX, so the other arm's "
              "index bound is the same four");
static_assert(0xfffffffeu == kStoreKindSentinel && 0xfffffffdu == kStoreSubSentinel,
              "0x00dd080a and 0x00dd082b are the two negative answers the two "
              "early exits store, and they are one apart");
static_assert(0x03u == kStoreProgress && 0x02u == kStore2 && 0x01u == kStore1 &&
                  0x00u == kStore0,
              "the four small codes, each one instruction's immediate, and the "
              "order they are stored in is 3, 2, 1, 0 across 0x00dd0816, "
              "0x00dd0862, 0x00dd08b6 and 0x00dd08aa");
static_assert(0x53dbcf1u == kTagArmSubtractand &&
                  0x80000006u == kTagArmSelectMask &&
                  0x7fffffffu == kTagArmSelectAddend,
              "0x00dd08d4, 0x00dd08de and 0x00dd08e4's three immediates");
static_assert(0x7ffffffau == kCalleeArmSelectMask && 0x05u == kCalleeArmSelectAddend,
              "0x00dd088e and 0x00dd0894's two immediates; note the mask and the "
              "addend are 0x7ffffffa and 5 here and 0x80000006 and 0x7fffffff in "
              "the tag arm, so the two blocks are not interchangeable");
static_assert(0x08u == kCallArgumentCleanupBytes,
              "0x00dd0887's ADD ESP,0x8 drops the two words the two bare-C3 "
              "callees left behind");
static_assert(static_cast<Word>(- 0x1) == kSubStateSentinel,
              "0x00dd0826 compares against all ones, written as a signed -0x1 in "
              "the listing; the test is a full-word equality, so 0x7fffffff and "
              "0xfffffffe both miss it");
static_assert(0x04u == kCompareArgumentDisplacement,
              "0x00dd086e's LEA forms receiver+0x4 and nothing else; the twelve "
              "bytes 0x004eb930 reads there end at receiver+0x10, which is the "
              "named constant rather than a second literal so that a "
              "reconstruction moving this displacement cannot move the model's "
              "own view of it in step");
static_assert(0x04u + kCompareWidthBytes == 0x10u,
              "0x00dd086e forms receiver+0x4 and 0x004eb930 reads twelve bytes "
              "from there, so the record it compares ends at receiver+0x10");

extern "C" void PKG_SWARM_W2_00DD07F0_THISCALL re_00dd07f0(
    OpaqueSporepediaAsset* receiver) {
  // 00dd07f0  PUSH ESI
  // 00dd07f1  MOV ESI,ECX
  //
  // ESI becomes the receiver alias and every receiver access in the body goes
  // through it, including the LEA at 0x00dd086e. ECX is never used as the
  // receiver again -- it is reused twice, at 0x00dd0801 for a level-2 pointer
  // and at 0x00dd0837 for the kind word -- which is why the record's receiver
  // shape is R-ALIAS and why an ECX-only displacement scan finds nothing in
  // bounds.
  //
  // The receiver is taken as a byte run and every access below is a
  // DISPLACEMENT into it. The record enumerates offsets [132, 136, 140, 152] and
  // is bounds_only: it says where the body was seen reaching and not which member
  // is which, so no member name is written for any of them. The three receiver
  // words it reads, the one it writes, and the zero words it writes on the other
  // five exits are all of this body's memory surface on the receiver.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00dd07f3  MOV EAX,DWORD PTR [ESI + 0x98]
  // 00dd07f9  TEST EAX,EAX
  // 00dd07fb  JZ 0x00dd08f0
  //
  // The first receiver read, and the only one that produces a pointer. A NULL
  // link leaves the function through the shared bare epilogue WITHOUT writing
  // anything: this is the first of the five no-write exits, and the receiver is
  // left byte for byte as it was found. The TEST is on the pointer itself, so
  // the test is for null and not for a zero-valued sub-state -- a link that
  // points at a zeroed record is NOT this exit.
  std::uint8_t* const link = link_from(self);  // == kLinkDisplacement, 0x00dd07f3
  if (link == nullptr) {
    return;
  }

  // 00dd0801  MOV ECX,DWORD PTR [EAX + 0xc]
  // 00dd0804  CMP DWORD PTR [ECX + 0x10],0x6
  // 00dd0808  JNZ 0x00dd0816
  //
  // The second pointer level, and the one the two-level rule is about: the dword
  // at link+0xc IS the record, and the word compared is 0x10 bytes INTO the
  // record, not 0x10 bytes into the link. Reading link+0x10 instead, or reading
  // the record's first member, is a different function. The model test plants a
  // decoy at both wrong depths for exactly this.
  //
  // The compare is a full-word equality against 6, and the JNZ means exactly 6
  // takes the -2 exit. 5 and 7 do not, and neither does any word that merely has
  // 6 somewhere in it.
  std::uint8_t* const record = record_from(link);  // 0x00dd0801
  if (*word_at(record + kRecordKindDisplacement) == 0x06u) {
    // 00dd080a  MOV DWORD PTR [ESI + 0x8c],0xfffffffe
    // 00dd0814  POP ESI
    // 00dd0815  RET
    *word_at(self + 0x8c) = kStoreKindSentinel;  // 0x00dd080a
    return;
  }

  // 00dd0816  MOV DWORD PTR [ESI + 0x8c],0x3
  //
  // The FIRST of the result word's nine writes, and the only one that is not
  // immediately followed by a return: the function keeps going, so every path
  // that reaches any later arm has already written 3 here. That ordering is
  // observable and the test measures it -- an observer planted at any of the
  // three calls reads 3 out of the result word, and an observer planted on an
  // earlier no-write exit reads whatever was there before.
  *word_at(self + 0x8c) = kStoreProgress;  // 0x00dd0816

  // 00dd0820  MOV EDX,DWORD PTR [EAX + 0xc]
  // 00dd0823  MOV EAX,DWORD PTR [EDX + 0x20]
  // 00dd0826  CMP EAX,-0x1
  // 00dd0829  JNZ 0x00dd0837
  //
  // 0x00dd0820 reloads the SAME dword 0x00dd0801 loaded -- same level-1 object,
  // same displacement -- and 0x00dd0823 then reads 0x20 bytes into the record it
  // points at. So the model reuses the value rather than loading it twice, and
  // the reuse is a fact about the listing and not an optimisation: nothing
  // between the two loads can change the link, because nothing between them
  // branches, calls or stores. It is a two-level read all the same, and this is
  // the second place a one-level reconstruction would go wrong.
  //
  // The sentinel is ALL ONES, compared as a full word. It is not a sign test and
  // not a zero test, so 0x7fffffff and 0xfffffffe both fall through to the
  // switch and so does every other word including 0.
  const Word sub_state = *word_at(record + kRecordSubDisplacement);  // 0x00dd0823
  if (sub_state == kSubStateSentinel) {
    // 00dd082b  MOV DWORD PTR [ESI + 0x8c],0xfffffffd
    // 00dd0835  POP ESI
    // 00dd0836  RET
    //
    // The second of the two negative answers, and it OVERWRITES the 3 that
    // 0x00dd0816 just stored. The result word is written twice on this path, and
    // a reconstruction that returned before the first write would leave 3 there.
    *word_at(self + 0x8c) = kStoreSubSentinel;  // 0x00dd082b
    return;
  }

  // 00dd0837  MOV ECX,DWORD PTR [ESI + 0x84]
  // 00dd083d  DEC ECX
  // 00dd083e  MOV EDX,0x4
  // 00dd0843  CMP ECX,EDX
  // 00dd0845  JA 0x00dd08f0
  //
  // The outer index, and its guard. The index is the kind word MINUS ONE, and the
  // guard is UNSIGNED above-or-equal-5, so the legal kinds are 1..5 and kind 0
  // falls out. That is a fact about the comparison and not about the range: a
  // signed compare would let kind 0 wrap to 0xffffffff and the table would then
  // be indexed out of bounds, so the model writes the comparison as the unsigned
  // one it is and the test drives kind 0 and kind 0x80000000 specifically.
  //
  // Two no-write exits live here and one further down: kind 0, kind 6 and kind 7
  // and kind 0x80000000 all reach 0x00dd08f0 with the result word still holding
  // the 3 from 0x00dd0816 -- or, on the null-link and sentinel paths, never
  // written at all.
  const Word kind = *word_at(self + 0x84);  // == kKindDisplacement, 0x00dd0837
  const Word outer_index = kind - 0x01u;    // 0x00dd083d
  if (outer_index > 0x04u) {                // 0x00dd0843, 0x00dd0845
    return;
  }

  // 00dd084b  JMP DWORD PTR [ECX*0x4 + 0xdd08f4]
  //
  // The outer dispatch, on the header's transcription of the five words at
  // 0xdd08f4. The model dispatches on the DECODED target rather than on the raw
  // index, because the table's whole content is which arms are shared: entries 1,
  // 3 and 4 are the same address, and entry 2 is the bare epilogue. A model that
  // switched on the index and re-derived the sharing would be a second guess at
  // bytes already read.
  switch (kOuterTable[outer_index]) {
    case kTargetKindOneArm: {
      // 00dd0852  CMP EAX,0x7
      // 00dd0855  JA 0x00dd08f0
      // 00dd085b  JMP DWORD PTR [EAX*0x4 + 0xdd0908]
      //
      // The kind-1 arm's own guard and dispatch, on the header's transcription of
      // the eight words at 0xdd0908. Its bound is 7, not 4, which is the visible
      // difference between this table and the other two and the reason indices 6
      // and 7 exist at all.
      if (sub_state > 0x07u) {  // 0x00dd0852, 0x00dd0855
        return;
      }
      switch (kKindOneSubTable[sub_state]) {
        case kTargetStore3:
          *word_at(self + 0x8c) = kStoreProgress;  // 0x00dd08c2, for indices 0 and 3
          return;
        case kTargetStore2:
          *word_at(self + 0x8c) = kStore2;  // 0x00dd0862
          return;
        case kTargetStore1:
          *word_at(self + 0x8c) = kStore1;  // 0x00dd08b6
          return;
        case kTargetBareStore:
          // The bare store at 0x00dd08ea, reached from index 4 and NOT through
          // the recomputing block above it. EDX was set to 4 at 0x00dd083e, is
          // read but never written by 0x00dd0843's CMP, and the jump dispatch
          // writes no register -- so what lands in the result word is 4, the
          // guard's own bound, and the tag word is not read on this path at all.
          *word_at(self + 0x8c) = kLeftoverGuardWord;
          return;
        case kTargetStore0:
          *word_at(self + 0x8c) = kStore0;  // 0x00dd08aa
          return;
        case kTargetThreeCalleeBlock:
          break;  // fall through to the shared block below
        default:
          return;
      }
      break;
    }

    case kTargetOtherArm: {
      // 00dd089f  CMP EAX,EDX
      // 00dd08a1  JA 0x00dd08f0
      // 00dd08a3  JMP DWORD PTR [EAX*0x4 + 0xdd0928]
      //
      // The other arm, reached by outer entries 1, 3 and 4 -- kinds 2, 4 and 5.
      // Its guard compares against EDX, which is still the 4 from 0x00dd083e, so
      // its index bound is the same four and its table has five entries. Its
      // dispatch is on the header's transcription of the words at 0xdd0928.
      if (sub_state > 0x04u) {  // 0x00dd089f, 0x00dd08a1
        return;
      }
      switch (kOtherArmSubTable[sub_state]) {
        case kTargetStore0:
          *word_at(self + 0x8c) = kStore0;  // 0x00dd08aa
          return;
        case kTargetStore1:
          *word_at(self + 0x8c) = kStore1;  // 0x00dd08b6
          return;
        case kTargetStore3:
          *word_at(self + 0x8c) = kStoreProgress;  // 0x00dd08c2
          return;
        case kTargetBareStore:
          // 0x00dd08ea again, reached here from index 3 rather than 4, and for
          // the same reason: the leftover EDX. The two tables put the bare store
          // on OPPOSITE indices, which is the single easiest thing to transpose
          // in this body and the reason this arm and the one above are kept
          // visibly separate.
          *word_at(self + 0x8c) = kLeftoverGuardWord;
          return;
        case kTargetTagArm: {
          // 00dd08ce  MOV EDX,DWORD PTR [ESI + 0x88]
          // 00dd08d4  SUB EDX,0x53dbcf1
          // 00dd08da  NEG EDX
          // 00dd08dc  SBB EDX,EDX
          // 00dd08de  AND EDX,0x80000006
          // 00dd08e4  ADD EDX,0x7fffffff
          // 00dd08ea  MOV DWORD PTR [ESI + 0x8c],EDX
          // 00dd08f0  POP ESI / RET
          //
          // The tag arm, and the only place the body reads its fourth receiver
          // word. It is six arithmetic instructions with no branch in it, and it
          // makes its selection through NEG's carry rather than through a
          // compare, so the selection is bit-exact equality against 0x53dbcf1
          // and not a range.
          //
          // The ADD at 0x00dd08e4 is UNCONDITIONAL, and that is the whole
          // subtlety of this arm. SBB's 0 is not a result: it falls straight into
          // the ADD and comes out as the addend on its own, 0x7fffffff. The other
          // arm's value is 0x80000006 + 0x7fffffff, which WRAPS: it is 5, not
          // 0x80000005, and a reconstruction that adds without truncating
          // produces a nine-digit word here and is refuted on every tag value
          // other than the subtractand.
          //
          // The arm writes the result word once, at 0x00dd08ea, and then FALLS
          // THROUGH into the shared epilogue rather than jumping to it -- so this
          // is the one path that reaches 0x00dd08f0 with a write already done.
          // That is why the epilogue is shared by five no-write paths and one
          // write path, and why the model returns here rather than branching.
          const Word tag = *word_at(self + 0x88);  // == kTagDisplacement, 0x00dd08ce
          const Word wide = (tag == 0x53dbcf1u) ? 0u : kNegSelectFill;  // NEG/SBB
          *word_at(self + 0x8c) = kTagArmSelectAddend + (wide & kTagArmSelectMask);
          return;
        }
        default:
          return;
      }
    }

    case kTargetBareEpilogue:
    default:
      // 00dd08f0  POP ESI
      // 00dd08f1  RET
      //
      // Outer entry 2 -- kind 3 -- reaches the bare epilogue directly and writes
      // NOTHING. The result word is left holding whatever it held, and for kind 3
      // that is the 3 stored at 0x00dd0816; for a kind of 0, 6, 7 or 0x80000000
      // the guard above returns before this point with the same 3 in place. The
      // model returns without touching the receiver on every one of those paths,
      // and the test compares the whole object byte for byte to prove it.
      return;
  }

  // 00dd086e  LEA EAX,[ESI + 0x4]
  // 00dd0871  PUSH EAX
  // 00dd0872  CALL 0x00401090
  //
  // The three-callee block, reached from kind-1 indices 6 and 7 -- the only arm
  // in the body that leaves the machine at all, and the only one whose result
  // depends on anything outside the receiver.
  //
  // The LEA forms an ADDRESS; the word on the stack is not a value read here.
  // 0x00401090's own body is four instructions that read no stack slot and no
  // argument register, so it takes zero arguments and IGNORES the word just
  // pushed. Its terminator is a bare C3, which is why that word is still on the
  // stack eleven instructions later and becomes 0x004eb930's SECOND argument.
  // That the word survives is a fact about the two bare C3s; what the address
  // means is not fixed by them.
  std::uint8_t* const compare_argument = self + kCompareArgumentDisplacement;

  // 00dd0877  MOV ECX,EAX
  // 00dd0879  CALL 0x004df400
  //
  // The second callee takes the FIRST callee's return as its own thiscall
  // receiver, in ECX, and no stack argument. Its whole body is `return this +
  // kCalleeShiftDisplacement`. So its return is a pointer 0xa4 bytes past the
  // species-manager word, and NOT a copy of anything in the receiver.
  std::uint8_t* const shifted = sporepedia_member_shift_004df400(
      sporepedia_species_manager_global_00401090());

  // 00dd087e  PUSH EAX
  // 00dd087f  CALL 0x004eb930
  // 00dd0884  MOVZX ECX,AL
  // 00dd0887  ADD ESP,0x8
  // 00dd088a  NEG ECX
  // 00dd088c  SBB ECX,ECX
  // 00dd088e  AND ECX,0x7ffffffa
  // 00dd0894  ADD ECX,0x5
  // 00dd0897  MOV DWORD PTR [ESI + 0x8c],ECX
  // 00dd089d  POP ESI
  // 00dd089e  RET
  //
  // The third callee compares three dwords at [arg1+0], [arg1+4] and [arg1+8]
  // against the three at the same offsets of arg2, and returns 1 only if all
  // three match. Arg1 is the word just pushed -- the second callee's return --
  // and arg2 is the word 0x00dd0871 pushed, still on the stack, which points at
  // receiver+0x4. So the comparison is between the twelve bytes at
  // (species-manager + 0xa4) and the twelve bytes at receiver+4, and the twelve
  // bytes at receiver+4 are read by the CALLEE, not by this body. That is why
  // this body's own receiver reach stays at 0x98 while the callee reads further
  // down the object.
  //
  // The answer is consumed as ONE BYTE: 0x00dd0884's MOVZX zero-extends AL, so a
  // callee that returned 0x00000100 would read as false here. The model's
  // declared bool is the narrowest type that reproduces that.
  const bool equal = sporepedia_equal_three_dwords_004eb930(
      shifted, compare_argument);

  // 00dd088a..0x00dd0894, then the store at 0x00dd0897.
  //
  // The same six-instruction shape as the tag arm, with the two immediates
  // SWAPPED: the mask is 0x7ffffffa and the addend is 5 here, where the tag arm
  // masked with 0x80000006 and added 0x7fffffff. Both pairs produce the same two
  // words, 0x7fffffff and 5, so a reconstruction that transposed the two
  // blocks' constants would still be right about the answers and wrong about why;
  // the test pins the answers of both blocks independently to catch the case
  // where a transposition changes them.
  const Word wide = equal ? kNegSelectFill : 0u;  // 0x00dd0884, 0x00dd088a, 0x00dd088c
  *word_at(self + 0x8c) = kCalleeArmSelectAddend + (wide & kCalleeArmSelectMask);
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00dd07f0
