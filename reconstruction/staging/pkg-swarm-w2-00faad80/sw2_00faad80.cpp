// PKG-SWARM-W2-00FAAD80 -- reconstruction of FUN_00faad80 @ 0x00faad80
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// 242 instructions, 15 direct callees, 6 indirect dispatch sites, 851 bytes from
// 0x00faad80 to 0x00fab0d1 (RET 0x8). The listing is not truncated: an independent
// objdump pass over the image at file offset 0x0baa180 reproduces all 242
// instructions at the same addresses with the same lengths, and every branch target
// closes inside the span, so no part of the body is missing.
//
// WHAT THE BODY DOES, in one paragraph. The receiver carries a page counter at its
// +0xa48. A counter of exactly 1 is a one-shot arm: it is decremented to 0, a virtual
// call is made through the receiver's table at slot +0x80, and a five-argument
// notifier is told the caller's first argument twice BY ADDRESS, the receiver's +0xfc
// flag and 10.0f. Any other non-zero counter is decremented and the call returns. A
// counter of 0 is the steady-state arm: a resync of a bounds object is done when the
// receiver's two extent floats no longer match the bounds it came from, a phase byte
// is recomputed, a call counter is incremented, an optional settle is reported, six
// matrix rows are read, copied and applied, a relay word is cleared, rebuilt and
// committed, a distance test sets a flag, and a peer object is notified. The body
// returns nothing.
//
// FRAME, walked by hand over all 242 instructions with entry_esp = 0. The header's
// `Frame` reproduces it as a real object; this is the walk:
//
//   0x00faad80 SUB ESP,0x14                    esp = -0x14
//   0x00faad83 PUSH ESI                        esp = -0x18
//   0x00faad8c PUSH EDI                        esp = -0x1c   <- steady state
//   0x00faadff PUSH EBX                        esp = -0x20   main arm only
//   0x00faaf3e PUSH EBP                        esp = -0x24   row loop only
//   0x00fab02b POP EBP                         esp = -0x20
//   0x00fab0bb POP EBX                         esp = -0x1c
//   0x00fab0cc POP EDI; POP ESI; ADD ESP,0x14  esp =  0, then RET 0x8 consumes 8 more
//
// Two independent corroborations, because a hand walk is exactly the kind of claim
// that goes wrong quietly:
//
//   (1) The one-shot arm returns at 0x00faade0 with `POP EDI; POP ESI; ADD ESP,0x14`.
//       That arm pushed EBX? No -- the PUSH EBX at 0x00faadff is AFTER the branch at
//       0x00faad91 that selects this arm, so this arm never pushed it, and indeed it
//       pops only EDI and ESI. Under the walk above ESP is -0x1c on entry to that
//       sequence, so the two pops land exactly on the PUSH EDI/PUSH ESI words and
//       ADD ESP,0x14 lands on entry_esp. One walk, two different exits, both balanced.
//   (2) 0x00fab0c0 reads `MOV ECX,dword ptr [ESP + 0x24]`. Under the walk ESP is
//       -0x1c there (EBP and EBX already popped, the PUSH EBX at 0x00fab0a7 consumed
//       by 0x00fa5610), so the word is at entry_esp+0x8 -- the SECOND argument -- and
//       it is the word handed to the peer notifier. The first argument is read the
//       same way at 0x00fab055, where ESP is -0x20, giving entry_esp+0x4. Two reads of
//       the same displacement, two different slots, and each one matches the argument
//       its own callee is documented to take.
//
// The 16 bytes at entry_esp-0x10 are the only frame slots the body addresses. The
// three bound floats (0x00faae4f/0x00faae55/0x00faae5b, ESP = -0x1c) and the four row
// floats (0x00faaf71/0x00faaf7c/0x00faaf87 at ESP = -0x24, plus 0x00faafaf at
// ESP = -0x28 after the PUSH 0x8) are the same three words plus a fourth, used at
// disjoint times, so ONE slot serves both. That is why `Frame` has one `Row4`.
//
// TWO THINGS A NAIVE READING GETS WRONG, both pinned by the model test:
//
//   * The five arguments of 0x00f9b8c0 do NOT start with the caller's first argument.
//     The first two are BOTH its address: `LEA EDX,[ESP+0x2c]` at 0x00faadca with
//     ESP = -0x28 and `LEA EAX,[ESP+0x30]` at 0x00faadcf with ESP = -0x2c both compute
//     entry_esp+0x4. So the notifier is handed one out-parameter twice.
//   * The call at 0x00faaf0b does NOT pass the receiver's +0x20c word. `PUSH ECX` at
//     0x00faaf06 reserves a slot and `FSTP float ptr [ESP]` at 0x00faaf07 writes the
//     100.0f over it. The word is loaded, tested, and then destroyed.

#include "sw2_00faad80_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00faad80 {
namespace {

// The three words the body zeroes at 0x00faaec8 (address 0x016c9e7c), 0x00faaece
// (0x016c9e80) and 0x00faaed4 (0x016c9e84) -- a contiguous 12-byte run in the original's
// .data. The model keeps them here rather than writing to a fixed address, and starts
// them non-zero so a dropped store is visible.
Word g_cleared[3] = {1u, 1u, 1u};

// The ECX value the body hands to 0x00fbf570. Not a machine address; see the header.
void* const g_unfixed_ecx = reinterpret_cast<void*>(static_cast<std::uintptr_t>(0xfeedec70));

const float* g_last_frame = nullptr;
const float* g_last_row_slot = nullptr;
std::ptrdiff_t g_last_row_slot_entry_offset = 0;
std::ptrdiff_t g_last_picked_word_offset = 0;

}  // namespace

Word cleared_word(unsigned which) { return which < 3u ? g_cleared[which] : 0xffffffffu; }
void poison_cleared_words() {
  g_cleared[0] = 1u;
  g_cleared[1] = 1u;
  g_cleared[2] = 1u;
}
void* indeterminate_receiver() { return g_unfixed_ecx; }
const float* last_frame() { return g_last_frame; }
const float* last_row_slot() { return g_last_row_slot; }
std::ptrdiff_t last_row_slot_entry_offset() { return g_last_row_slot_entry_offset; }
std::ptrdiff_t last_picked_word_offset() { return g_last_picked_word_offset; }

extern "C" void PKG_SWARM_W2_00FAAD80_THISCALL re_00faad80(Receiver* receiver, Word first_argument,
                                                          Word second_argument) {
  // The 16 frame bytes, as four floats. Word 0 sits at entry_esp-0x10 and the other
  // three at -0xc, -0x8 and -0x4; see the header's frame walk. They are declared as
  // one array because the machine's two uses of these words ALIAS: the bound floats
  // written at 0x00faae4f..0x00faae5b and the row words written at
  // 0x00faaf71..0x00faafaf are the same three words plus a fourth.
  float scratch[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  g_last_frame = scratch;

  // ---- 0x00faad86..0x00faada2: the three-way branch on the page counter ------
  // 0x00faad8f CMP EAX,EDI / 0x00faad91 JZ 0x00faade3 -- equal takes the steady state.
  const Word page = load_word(receiver, kOffPageCounter);
  if (page != 0) {
    // 0x00faad93 JLE 0x00fab0cc. A SIGNED compare, so a counter whose top bit is set
    // returns here and does not take the decrement below. The model test drives that
    // case, because an unsigned reading would decrement it instead.
    if (static_cast<std::int32_t>(page) <= 0) {
      return;
    }
    // 0x00faad99 DEC EAX / 0x00faad9a MOV dword ptr [ESI + 0xa48],EAX
    store_word(receiver, kOffPageCounter, page - 1u);
    // 0x00faada0 CMP EAX,EDI / 0x00faada2 JNZ 0x00fab0cc -- only a counter that was
    // exactly 1 falls through.
    if ((page - 1u) != 0) {
      return;
    }

    // ---- the one-shot arm, reachable only when the counter was exactly 1 ------
    // 0x00faada8 MOV EAX,[ESI] / 0x00faadaa MOV EDX,[EAX + 0x80] / 0x00faadb0 CALL EDX
    reinterpret_cast<FnVoid>(load_slot(receiver, kSlotPageEntered))(receiver);
    // 0x00faadb2 FLD dword ptr [0x01473c70] loads 10.0f, which 0x00faadc2 FSTP's into
    // the argument slot 0x00faadbe reserved with `PUSH ECX`. That PUSH pushed the
    // incoming ECX and the FSTP overwrites it, so the pushed value is dead.
    // 0x00faadbf SETNZ AL / 0x00faadc5 MOVZX ECX,AL: 1 when the +0xfc word is
    // non-zero, 0 otherwise, compared as a full 32-bit word.
    const Word gate_flag = (load_word(receiver, kOffGate) != 0) ? 1u : 0u;
    // The two pointer arguments are the SAME address -- the caller's first argument --
    // and the last one is the float. See the file header for the arithmetic.
    one_shot_notify_00f9b8c0(receiver, &first_argument, &first_argument, gate_flag, 0u,
                            kOneShotSeconds);
    return;
  }

  // ---- 0x00faade3..0x00faae27: the steady-state arm --------------------------
  // 0x00faade3 CMP dword ptr [ESI + 0xfc],EDI / 0x00faade9 JNZ 0x00fab0cc
  if (load_word(receiver, kOffGate) != 0) {
    return;
  }
  // 0x00faadef MOV ECX,dword ptr [ESI + 0x2c] -- a pointer, and every bounds
  // displacement below is read THROUGH it. It is re-read at 0x00fab06d before the
  // distance test, because a callee in between may have changed it.
  void* const bounds = load_pointer(receiver, kOffBoundsObject);

  // 0x00faadf2 MOVSS XMM0,[ESI + 0x360] and 0x00faae0f MOVSS XMM1,[ESI + 0x364].
  const float extent_near = load_float(receiver, kOffExtentNear);
  const float extent_span = load_float(receiver, kOffExtentSpan);
  // The resync condition, in the listing's own order, with the listing's own
  // short-circuit: the second product is only computed when the first compare came
  // out "the same", and the byte is only tested when both compares did.
  //
  // Each of the first two is the UCOMISS/LAHF/TEST AH,0x44/JP sequence, which is
  // taken when ZF is clear, i.e. when the operands are unequal IN IEEE ORDER -- and an
  // unordered pair sets ZF, so an unordered pair is reported as "the same" here. C's
  // `!=` reports it as different. The model follows the machine, and the model test
  // drives an unordered pair to hold it to that.
  const bool resync = ordered_differs(extent_near, load_float(bounds, kBoundsNear)) ||
                      ordered_differs(extent_span, load_float(bounds, kBoundsScaleLeft) *
                                                      load_float(bounds, kBoundsScaleRight)) ||
                      (load_byte(receiver, kOffResyncFlag) != 0);
  if (resync) {
    // 0x00faae29 MOV ECX,ESI / 0x00faae2b CALL 0x00f977c0
    bounds_resync_00f977c0(receiver);
    // 0x00faae33/0x00faae38/0x00faae3d: the recomputed near bound, in that order.
    const float computed_bound =
        load_float(bounds, kBoundsScaleLeft) * load_float(bounds, kBoundsScaleRight) +
        load_float(bounds, kBoundsNear);
    // 0x00faae42 MOVSS XMM1,[EAX + 0x50] and 0x00faae4a MOVSS XMM2,[EAX + 0x54].
    const float stored_limit = load_float(bounds, kBoundsLimit);
    const float stored_second = load_float(bounds, kBoundsSecondLimit);
    // 0x00faae4f/0x00faae55/0x00faae5b: the three frame words at entry_esp-0x10,
    // entry_esp-0xc and entry_esp-0x8 (ESP = -0x1c).
    scratch[0] = computed_bound;
    scratch[1] = stored_limit;
    scratch[2] = stored_second;
    // 0x00faae61 LEA EBX,[ESP + 0xc] points at the computed bound; 0x00faae65 JA
    // keeps it when the computed bound is GREATER, and 0x00faae67 LEA EBX,[ESP + 0x10]
    // switches to the stored limit otherwise. So the word that is read back at
    // 0x00faae7e is the maximum of the two, and an unordered pair takes the stored
    // limit (JA is not taken), which is what `>` does for a NaN as well.
    // The pick is a WORD index into the frame row; the instrumentation reports it as the
    // byte offset the LEA displacement implies, so a reader can check it against the
    // listing's ESP+0xc and ESP+0x10.
    const std::ptrdiff_t pick_word = (computed_bound > stored_limit) ? 0 : 1;
    const float* const picked = scratch + pick_word;
    g_last_picked_word_offset = pick_word * static_cast<std::ptrdiff_t>(sizeof(float));
    // 0x00faae6b CALL 0x0067dd80 -- no pushed word; the callee's own six bytes end in a
    // plain RET, so it pops nothing and its EAX is the object to dispatch on.
    void* const stage_root = renderer_global_get_0067dd80();
    // 0x00faae70/0x00faae72/0x00faae74: the two-level read, table word then slot.
    void* const stage = reinterpret_cast<FnVoidToVoid>(load_slot(stage_root, kSlotStageMake))(
        stage_root, kStageId);
    // 0x00faae7e FLD dword ptr [EBX] happens AFTER the call above, so the value handed
    // on is read out of the frame slot at that point, not before.
    reinterpret_cast<FnNotify>(load_slot(stage, kSlotStageNotify))(stage, 0u, kNotifyVectorAddress,
                                                                   *picked);
  }

  // ---- 0x00faae96..0x00faaebb: the phase byte --------------------------------
  // 0x00faae96 CMP byte ptr [ESI + 0x33d],0x0 / 0x00faae9d JNZ 0x00faaeb4 -- when the
  // byte is already set the new value is 1 and the +0x36c word is NOT read.
  bool phase_dirty = load_byte(receiver, kOffPhaseDirty) != 0;
  if (!phase_dirty) {
    // 0x00faae9f MOV ECX,ESI / 0x00faaea1 SUB ECX,dword ptr [ESI + 0x36c] /
    // 0x00faaea7 TEST byte ptr [ECX + 0x369],0x7. The byte is therefore at
    // receiver + 0x369 - page, in 32-bit arithmetic that is allowed to wrap: a page
    // larger than 0x369 sends the address below the receiver. The model reproduces the
    // wrap instead of clamping it, because a clamp would read a byte the machine does
    // not read.
    const Word page_index = load_word(receiver, kOffPageIndex);
    const std::uint8_t phase_byte =
        load_byte(receiver, static_cast<std::uint32_t>(kOffRowPhase - page_index));
    phase_dirty = (phase_byte & kRowPhaseMask) != 0;
  }
  // 0x00faaeb0/0x00faaeb4 choose 0 or 1, and 0x00faaebb stores the low byte of EAX.
  store_byte(receiver, kOffPhaseDirty, phase_dirty ? 1u : 0u);
  // 0x00faaeb9/0x00faaec1/0x00faaec4/0x00faaec6
  reinterpret_cast<FnVoid>(load_slot(receiver, kSlotPhaseResync))(receiver);

  // ---- 0x00faaec8..0x00faaed4: three globals cleared to zero ------------------
  g_cleared[0] = 0u;
  g_cleared[1] = 0u;
  g_cleared[2] = 0u;

  // ---- 0x00faaeda..0x00faaf0b: counter and the optional settle ---------------
  // 0x00faaeda reads the settle target BEFORE the counter increment, and the value is
  // then destroyed: 0x00faaf06 `PUSH ECX` is overwritten in place by the FSTP at
  // 0x00faaf07. So the callee is told the amount and the mode, never the target.
  const Word settle_target = load_word(receiver, kOffSettleTarget);
  // 0x00faaee0 INC dword ptr [ESI + 0x114] -- the one increment this body makes, and it
  // makes it on every path that reaches this point.
  store_word(receiver, kOffCallCounter, load_word(receiver, kOffCallCounter) + 1u);
  // 0x00faaee6 CMP ECX,EDI / 0x00faaee8 JZ 0x00faaf10
  if (settle_target != 0) {
    // 0x00faaeea MOV EDX,[ESI + 0x1d0] and 0x00faaef6..0x00faaeff:
    //   MOV EAX,EDX / SUB EAX,0x4 / NEG EAX / SBB EAX,EAX / AND EAX,EDX
    // NEG sets CF unless the operand was 0, so EAX is 0 when the mode is exactly 4 and
    // 0xffffffff otherwise, and the AND then yields 0 or the mode word itself.
    const Word mode = load_word(receiver, kOffMode);
    const Word reduced_mode = (mode == kModeNeutral) ? 0u : mode;
    settle_amount_00fbf570(g_unfixed_ecx, first_argument, kSettleAmount, reduced_mode);
  }

  // ---- 0x00faaf10..0x00fab053: the six-row block ------------------------------
  // 0x00faaf10/0x00faaf17, 0x00faaf1d/0x00faaf24, then 0x00faaf2a..0x00faaf38's
  // slot +0xd8 call whose AL is tested. The byte 0x370 is the "already done" latch and
  // the phase byte is re-read here, after the 0x00f977c0 call and the slot +0x10 call,
  // so it is not the value stored above if either of those changed it.
  if (load_byte(receiver, kOffPhaseDirty) != 0 && load_byte(receiver, kOffPhaseDone) == 0) {
    // TEST AL,AL tests the low byte only, so a callee returning 256 is "not ready".
    const Word ready = reinterpret_cast<FnBool>(load_slot(receiver, kSlotPhaseReady))(receiver);
    if ((ready & 255u) != 0) {
      // 0x00faaf3e/0x00faaf3f/0x00faaf41. The callee changes the receiver's +0x36c --
      // its own body is `MOV EAX,[ECX+0x36c]` / clear the byte at +0x368+page /
      // `MOV EDX,1` / `SUB EDX,[ECX+0x36c]` / store -- so the loop below must read the
      // page index again rather than reuse the value read before the block.
      page_turn_00f96370(receiver);
      for (Word index = 0; index < kRowCount; ++index) {
        // 0x00faaf52..0x00faaf5e, re-read every iteration:
        //   MOV EAX,[ESI+0x36c] / LEA EAX,[EAX+EAX*0x2] / LEA ECX,[EDI+EAX*0x2] /
        //   SHL ECX,0x4
        // which is (index + 6*page) * 0x10, added to the receiver and to 0x374.
        const Word row_page = load_word(receiver, kOffPageIndex);
        const std::uint32_t source =
            kOffRowSource + kRowStride * (index + kRowCount * row_page);
        // 0x00faaf61/0x00faaf77/0x00faaf82/0x00faaf8d: the row's four words.
        const float v0 = load_float(receiver, source);
        const float v1 = load_float(receiver, source + 4u);
        const float v2 = load_float(receiver, source + 8u);
        const float v3 = load_float(receiver, source + 12u);
        // 0x00faaf71/0x00faaf7c/0x00faaf87: the first THREE words reach the frame row,
        // at entry_esp-0x10, -0xc and -0x8.
        scratch[0] = v0;
        scratch[1] = v1;
        scratch[2] = v2;
        // 0x00faafa6..0x00faafa1: all FOUR words reach the receiver, through the 0x828
        // cursor which advances by 0x10 per iteration. The cursor is the second word
        // of the element, so the stores are at cursor-8, cursor-4, cursor and cursor+4.
        const std::uint32_t dest = kOffRowDestCursor + kRowStride * index;
        store_float(receiver, dest - 8u, v0);
        store_float(receiver, dest - 4u, v1);
        store_float(receiver, dest, v2);
        store_float(receiver, dest + 4u, v3);
        // 0x00faafa8/0x00faafab/0x00faafad/0x00faafaf/0x00faafb5: the slot +0x4c call,
        // and the FOURTH word reaches the frame row only here -- after the PUSH 0x8,
        // through `MOVSS dword ptr [ESP + 0x24],XMM3` with ESP = entry_esp-0x28, which
        // is entry_esp-0x4. So the callee is entered with all four words in place.
        scratch[3] = v3;
        const Word query =
            reinterpret_cast<FnQuery>(load_slot(receiver, kSlotRowQuery))(receiver, kRowQuerySize);
        // 0x00faafb7/0x00faafb9 and then 0x00faafbb..0x00faafd8: on a non-zero AL the row
        // becomes (0, 0, 1, 1). The receiver's destination row is NOT rewritten.
        if ((query & 255u) != 0) {
          scratch[0] = 0.0f;
          scratch[1] = 0.0f;
          scratch[2] = kUnitScale;
          scratch[3] = kUnitScale;
        }
        // 0x00faafde..0x00fab000. The row object is re-loaded from the +0x118 cursor
        // on each of the three calls (0x00faafe3, 0x00faafeb, 0x00faaff8), and the
        // cursor advances by 4 (0x00fab009), so element i is the word at +0x118 + 4*i.
        void* const row_object = load_pointer(receiver, kOffRowObject + 4u * index);
        g_last_row_slot = scratch;
        g_last_row_slot_entry_offset = kFrameRowFromEntryEsp;
        const Row4* const row = reinterpret_cast<const Row4*>(scratch);
        row_apply_first_00fb0d20(row_object, index, row);
        row_apply_second_00faf140(row_object, index, row);
        row_apply_third_00faf400(row_object, index, row);
      }
      // 0x00fab015/0x00fab017
      row_block_finish_00f96f90(receiver);
      // 0x00fab01c LEA EDI,[ESI + 0x81c] -- an ADDRESS, taken before the latch byte is
      // set and before the value at it is read.
      void* const relay_slot = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(receiver) +
                                                        kOffRelaySlot);
      // 0x00fab022
      store_byte(receiver, kOffPhaseDone, 1u);
      // 0x00fab029 MOV ECX,[EDI] / 0x00fab02b POP EBP / 0x00fab02c TEST ECX,ECX
      const Word relay_first = load_word(relay_slot, 0u);
      if (relay_first != 0) {
        // 0x00fab030 MOV dword ptr [EDI],0x0 -- the word is CLEARED BEFORE the call, and
        // the callee is handed the value, not the address.
        store_word(relay_slot, 0u, 0u);
        relay_release_00690120(reinterpret_cast<void*>(static_cast<std::uintptr_t>(relay_first)));
      }
      // 0x00fab03b/0x00fab03c/0x00fab03d, cleaned by the body's own ADD ESP,0x8.
      relay_build_00faacd0(receiver, relay_slot);
      // 0x00fab042 re-reads the word, so this callee is given the value the builder may
      // have stored -- not the value 0x00fab030 cleared and not the original.
      relay_commit_006909b0(
          reinterpret_cast<void*>(static_cast<std::uintptr_t>(load_word(relay_slot, 0u))));
      // 0x00fab04c
      store_byte(receiver, kOffPhaseDirty, 0u);
    }
  }

  // ---- 0x00fab055..0x00fab0c7: the tail ---------------------------------------
  // 0x00fab055 reads the caller's FIRST argument out of the frame into EBX, which is
  // then what both remaining callees are given.
  frame_commit_00f9ba40(receiver, first_argument);
  // 0x00fab06d re-reads the bounds pointer, four instructions after the three FLDs
  // that load the extents, and none of the callees in between is given the receiver.
  void* const bounds_now = load_pointer(receiver, kOffBoundsObject);
  // 0x00fab061..0x00fab082. Load order is 0x314, 0x310, 0x30c and the sum order is
  // 0x30c^2, then + 0x310^2, then + 0x314^2: the three FMULP/FADDP pairs pair the
  // oldest value with the newest product each time, which is what makes it a sum of
  // three squares in that order rather than in load order.
  const float extent_u = load_float(receiver, kOffExtentU);
  const float extent_v = load_float(receiver, kOffExtentV);
  const float extent_w = load_float(receiver, kOffExtentW);
  // 0x00fab084 FSQRT / 0x00fab086 FSUB dword ptr [EAX + 0x34].
  //
  // THIS BLOCK IS x87, NOT SSE, and that is why it is written in long double. The three
  // FLDs put 24-bit mantissas into the 80-bit x87 stack, and from there FMULP, FADDP,
  // FSQRT, FSUB, FADD, FMUL and FCOMIP all work at x87's 64-bit mantissa: nothing is
  // rounded to single precision between the three squares and the final comparison.
  // float arithmetic would round after every operation and would NOT be this body. The
  // two blocks above it are different -- the resync compares are UCOMISS and the bound is
  // MULSS/ADDSS, both single precision -- and they are written in float for that reason.
  const long double reach =
      std::sqrt(static_cast<long double>(extent_u) * extent_u +
                static_cast<long double>(extent_v) * extent_v +
                static_cast<long double>(extent_w) * extent_w) -
      static_cast<long double>(load_float(bounds_now, kBoundsNear));
  // 0x00fab089/0x00fab08c/0x00fab08f/0x00fab092: (far + left) * right - 1.0f, in that
  // order, with 1.0f read from 0x01485720.
  const long double limit =
      (static_cast<long double>(load_float(bounds_now, kBoundsReach)) +
       static_cast<long double>(load_float(bounds_now, kBoundsScaleLeft))) *
          static_cast<long double>(load_float(bounds_now, kBoundsScaleRight)) -
      static_cast<long double>(kUnitScale);
  // 0x00fab098 FCOMIP ST0,ST1 compares the limit (ST0) against the reach (ST1) and
  // pops; 0x00fab0a5/0x00fab09e choose 0 or 1 on JBE. An unordered pair sets CF and ZF,
  // so JBE is taken and the flag is 0 -- which is what `<` does for a NaN as well, and for
  // the negative square root of a negative sum of squares, which is where the NaN here
  // comes from.
  const bool inside = reach < limit;
  // 0x00fab0a7/0x00fab0aa: the byte is stored AFTER the argument push and BEFORE the
  // call, so the callee is entered with it already written.
  store_byte(receiver, kOffInsideFlag, inside ? 1u : 0u);
  inside_flag_commit_00fa5610(receiver, first_argument);
  // 0x00fab0b5 MOV ESI,dword ptr [ESI + 0x210] / 0x00fab0bb POP EBX /
  // 0x00fab0bc CMP ESI,EDI / 0x00fab0be JZ 0x00fab0cc. A NULL peer is a normal
  // outcome, not an error, and the call's receiver is the PEER, not this receiver.
  const Word peer = load_word(receiver, kOffPeer);
  if (peer != 0) {
    peer_notify_00fc7b30(reinterpret_cast<void*>(static_cast<std::uintptr_t>(peer)),
                         second_argument);
  }
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00faad80
