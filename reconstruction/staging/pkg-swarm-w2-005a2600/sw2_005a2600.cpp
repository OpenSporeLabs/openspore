// PKG-SWARM-W2-005A2600 -- reconstruction of FUN_005a2600, VA 0x005a2600
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Body span 0x005a2600..0x005a2b20 inclusive, 450 instructions, 1313 bytes, five
// terminators, 28 indirect transfers and 2 direct ones. The evidence for every
// constant, displacement and callee used below is partitioned in the package header;
// this file cites the instruction each statement comes from and claims nothing that
// the bytes do not fix.
//
// WHAT THE BODY IS. One entry sequence that harvests fifteen key ids out of a
// parameter object the receiver holds at its +0x10 and writes each result into its
// own displacement. Twelve of the fifteen are the same 43-instruction block: ask the
// object's +0x1c slot whether the id is present, ask its +0x28 slot for the record,
// and if the record's type word is 0xd or 0x10 read a float out of it -- from the
// record itself, or from the address in the record's leading word when the byte at
// the record's +0x10 has a bit of 0x30 set, or from the 0.0f at 0x015d1168 when the
// type word is neither tag. Two more are the same idea through a third slot: the
// +0x24 slot is asked for a record through an out-parameter in the frame, the record's
// type word must be exactly 0xd, and the float comes from this body's one direct
// callee 0x0041ea70. The fifteenth is the same read followed by a multiply and a
// fallback that stores the multiplier itself.
//
// The order of the fifteen is the order of the listing and it is load-bearing for one
// thing only: the out-parameter slot at [ESP+0x8] is the same word for both +0x24
// calls, so the second one overwrites the first one's record, and the two are read
// back before either is used, which is why the order between them changes nothing this
// body can show. The order is kept anyway because the listing fixes it.
//
// NOT MODELLED, AND WHY. (1) The parameter object's class and its three slots are
// declared but not described: no record in this repository names the class, so the
// model says only what the three call sites fix. (2) The twenty-one float
// displacements are named after the key id that writes them and grouped into nothing:
// ten of them come in pairs a fixed 0x14 apart and one id writes three, which is
// consistent with parallel float runs and is not asserted to be so. (3) The
// classification of the class this body belongs to, and the table at 0x013f69b4 it is
// an entry of, are recorded for the integrator and not used here: the body never reads
// the receiver's own leading word as a table word. (4) Nothing is claimed about what
// any of the fifteen key ids MEANS, or about the byte the receiver clears at its
// +0x9c, or about the frame word at [ESP+0x8] beyond the fact that the two +0x24
// callees are handed its address and this body reads the record back through it.

#include "sw2_005a2600_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_005a2600 {

namespace {

// The twelve-fold repeated block, de-duplicated. Every one of the twelve is 43
// instructions long and byte-identical apart from its two call sites and its one or
// two stores; the ranges are listed at the declaration of param_record_float() in the
// header. The de-duplication is a modelling choice and the model test checks it
// against a decoder written independently from the listing, so a wrong factorisation
// cannot pass silently.
//
//   out-of-line callee 0x0041ea70  returns a POINTER TO A FLOAT, and the twelve inline
//   copies read that float themselves; the test asserts the call count is zero for
//   these twelve ids, which is what keeps the two shapes apart.
bool harvest_id(EditorTransform005a2600* self, Word id, float& out) {
  std::uint8_t* base = raw(self);
  // 0x005a2621 MOV ECX,[ESI+0x10] / 0x005a2624 MOV EAX,[ECX] / 0x005a2626 MOV EDX,[EAX+0x28]
  if (!sw2_obj_slot_has_query(source_object(base), id)) {
    return false;  // 0x005a261d TEST AL,AL / 0x005a261f JZ
  }
  const std::uint8_t* record = sw2_obj_slot_get_query(source_object(base), id);
  out = param_record_float(record);
  return true;
}

}  // namespace

// 0x005a2600 PUSH ECX / 0x005a2601 PUSH EBX / 0x005a2602 PUSH ESI
//   Three pushes and no SUB ESP, so ESP is entry-12 for the whole body and [ESP+0x8]
//   is entry-4: the word 0x005a2600's PUSH ECX just filled. Every terminator is
//   POP ESI / POP EBX / POP ECX / RET, i.e. caller-owned cleanup of zero bytes, and
//   the return address is left where the callee put it.
// 0x005a2603 MOV ESI,ECX
//   The receiver is aliased into ESI and every receiver access in the body goes
//   through that alias, which is why the machine-derived receiver record reports
//   register ECX with shape R-ALIAS and its own literal-operand scan finds nothing.
extern "C" void PKG_SWARM_W2_005A2600_THISCALL re_005a2600(
    EditorTransform005a2600* self) {
  std::uint8_t* base = raw(self);
  // The two values the listing keeps in registers across blocks rather than in memory:
  // XMM0 / ST0 is the loaded value of the block being executed (reloaded at every
  // block, never carried across one) and EAX is the record the +0x28 slot returned.
  // Both are given a home here only so the stores can be written as stores.
  float scratch = 0.0f;
  // The frame word at [ESP+0x8] -- entry-4, the word 0x005a2600's PUSH ECX filled --
  // is the out-parameter of both +0x24 calls. The two blocks below pass the address
  // of this one variable to the second of them, exactly as the listing passes the same
  // address twice, and read the record back through it.
  const std::uint8_t* out_record = nullptr;

  // 0x005a2605 MOV ECX,dword ptr [ESI + 0x10]
  //   The only receiver displacement this body READS: the parameter object every one
  //   of the fifteen blocks goes through. It is re-read at each block in the listing
  //   (fifteen times) and the helper harvest_id() re-reads it through source_object()
  //   on both of its own call paths, so no copy of it is cached here.
  // 0x005a2608 MOV byte ptr [ESI + 0x9c],0x0
  //   The only receiver byte store before any of the harvesting, and the only
  //   non-float receiver store in the body.
  byte_at(base + 0x9c) = 0;

  // ---- 0x005a260f..0x005a265b  key 0x00c7c4f8 -> +0x14 ----
  // The first of the twelve. Written out in full here so the shape of the block is
  // visible once; the other eleven call the same helper.
  if (harvest_id(self, kIdC7c4f8, scratch)) {
    float_at(base + 0x14) = scratch;  // 0x005a265b FSTP float ptr [ESI+0x14]
  }

  // ---- 0x005a265e..0x005a26ab  key 0x00c7c4fa -> +0x18 ----
  if (harvest_id(self, kIdC7c4fa, scratch)) {
    float_at(base + 0x18) = scratch;  // 0x005a26ab FSTP float ptr [ESI+0x18]
  }

  // ---- 0x005a26ae..0x005a26fb  key 0x00c7c4f9 -> +0x1c ----
  if (harvest_id(self, kIdC7c4f9, scratch)) {
    float_at(base + 0x1c) = scratch;  // 0x005a26fb FSTP float ptr [ESI+0x1c]
  }

  // ---- 0x005a26fe..0x005a2757  key 0x00c7c4fb -> +0x28, +0x38, +0x4c ----
  //   The only key that writes three displacements, and the only one of the twelve
  //   that does not scale. All three stores take the same loaded value: 0x005a2749
  //   loads it once into XMM0 and 0x005a274d, 0x005a2752 and 0x005a2757 store it
  //   three times.
  if (harvest_id(self, kIdC7c4fb, scratch)) {
    float_at(base + 0x28) = scratch;  // 0x005a274d MOVSS dword ptr [ESI+0x28],XMM0
    float_at(base + 0x38) = scratch;  // 0x005a2752 MOVSS dword ptr [ESI+0x38],XMM0
    float_at(base + 0x4c) = scratch;  // 0x005a2757 MOVSS dword ptr [ESI+0x4c],XMM0
  }

  // ---- 0x005a275c..0x005a27b8  key 0x00c7c4fc -> +0x34, +0x48 ----
  //   The first of the four scaled blocks. 0x013f6960 is the degrees-to-radians
  //   reciprocal (0.01745329238474369f) and the multiply is 0x005a27ab, once, on the
  //   value before either store.
  if (harvest_id(self, kIdC7c4fc, scratch)) {
    scratch *= g_unmodelled_013f6960;  // 0x005a27ab MULSS XMM0,dword ptr [0x013f6960]
    float_at(base + 0x34) = scratch;   // 0x005a27b3 MOVSS dword ptr [ESI+0x34],XMM0
    float_at(base + 0x48) = scratch;   // 0x005a27b8 MOVSS dword ptr [ESI+0x48],XMM0
  }

  // ---- 0x005a27bd..0x005a2819  key 0x00c7c4fd -> +0x30, +0x44 ----
  if (harvest_id(self, kIdC7c4fd, scratch)) {
    scratch *= g_unmodelled_013f6960;  // 0x005a280c
    float_at(base + 0x30) = scratch;   // 0x005a2814
    float_at(base + 0x44) = scratch;   // 0x005a2819
  }

  // ---- 0x005a281e..0x005a2872  key 0x6fda2e1c -> +0x3c, +0x50 ----
  if (harvest_id(self, kId6fda2e1c, scratch)) {
    float_at(base + 0x3c) = scratch;  // 0x005a286d
    float_at(base + 0x50) = scratch;  // 0x005a2872
  }

  // ---- 0x005a2877..0x005a28cb  key 0x8fda2e23 -> +0x40, +0x54 ----
  if (harvest_id(self, kId8fda2e23, scratch)) {
    float_at(base + 0x40) = scratch;  // 0x005a28c6
    float_at(base + 0x54) = scratch;  // 0x005a28cb
  }

  // ---- 0x005a28d0..0x005a291d  key 0x00fe23b2 -> +0x58 ----
  if (harvest_id(self, kIdFe23b2, scratch)) {
    float_at(base + 0x58) = scratch;  // 0x005a291d FSTP float ptr [ESI+0x58]
  }

  // ---- 0x005a2920..0x005a296d  key 0x00fe2437 -> +0x5c ----
  if (harvest_id(self, kIdFe2437, scratch)) {
    float_at(base + 0x5c) = scratch;  // 0x005a296d FSTP float ptr [ESI+0x5c]
  }

  // ---- 0x005a2970..0x005a29c7  key 0x00fe243b -> +0x60, scaled ----
  if (harvest_id(self, kIdFe243b, scratch)) {
    scratch *= g_unmodelled_013f6960;  // 0x005a29bf
    float_at(base + 0x60) = scratch;   // 0x005a29c7 MOVSS dword ptr [ESI+0x60],XMM0
  }

  // ---- 0x005a29cc..0x005a2a23  key 0x00fe243f -> +0x64, scaled ----
  if (harvest_id(self, kIdFe243f, scratch)) {
    scratch *= g_unmodelled_013f6960;  // 0x005a2a1b
    float_at(base + 0x64) = scratch;   // 0x005a2a23 MOVSS dword ptr [ESI+0x64],XMM0
  }

  // ---- 0x005a2a28..0x005a2a56  key 0x01102b20 -> +0x68 ----
  //
  // The first of the two blocks that go through the object's +0x24 slot, and the only
  // two in the body that null-check the parameter object before using it
  // (0x005a2a2b TEST ECX,ECX / 0x005a2a2d JZ). Argument order is right to left:
  // LEA EDX,[ESP+0x8] then PUSH EDX then PUSH 0x01102b20, so the callee sees the id
  // as its first stack word and the out-parameter as its second, and it pops both
  // (nothing adjusts ESP after it).
  if (source_object(base) != nullptr) {  // 0x005a2a28..0x005a2a2d
    if (sw2_obj_slot_find_query(source_object(base), kId1102b20, &out_record)) {
      // 0x005a2a40 TEST AL,AL / 0x005a2a42 JZ
      // 0x005a2a44 MOV ECX,[ESP+0x8] -- the record the callee wrote through the
      //   out-parameter, read back out of the frame slot the LEA handed it.
      // 0x005a2a48 CMP WORD PTR [ECX+0x12],0xd / 0x005a2a4d JNZ
      //   Exactly one accepted tag here, and NOT the pair 0xd/0x10 the twelve
      //   inline blocks accept. A record of type 0x10 is read by those and skipped
      //   here; the model test drives that disagreement.
      if (half_at(out_record + 0x12) == 0x0d) {
        // 0x005a2a4f CALL 0x0041ea70 -- no register is reloaded, so ECX still holds
        //   the record and that is the callee's argument (0x0041ea76 MOV [EBP-8],ECX).
        // 0x005a2a54 FLD float ptr [EAX] / 0x005a2a56 FSTP float ptr [ESI+0x68]
        const float* loaded = unresolved_0041ea70(out_record);
        float_at(base + 0x68) = *loaded;
      }
    }
  }

  // ---- 0x005a2a59..0x005a2a87  key 0x01102b2f -> +0x6c ----
  // The same block again with the second id, the same frame slot as the out-parameter
  // (LEA EAX,[ESP+0x8] at 0x005a2a65 this time, and MOV ECX,[ESP+0x8] at
  // 0x005a2a75), and the same exactly-0xd tag test at 0x005a2a79.
  if (source_object(base) != nullptr) {  // 0x005a2a5c..0x005a2a5e
    if (sw2_obj_slot_find_query(source_object(base), kId1102b2f, &out_record)) {
      if (half_at(out_record + 0x12) == 0x0d) {
        const float* loaded = unresolved_0041ea70(out_record);  // 0x005a2a80
        float_at(base + 0x6c) = *loaded;                        // 0x005a2a87
      }
    }
  }

  // ---- 0x005a2a8a..0x005a2b20  key 0x044c6220 -> +0x70, scaled the other way ----
  //
  // The last block, and the only one with no null check: 0x005a2a8a MOV ECX,[ESI+0x10]
  // then 0x005a2a8d MOV EAX,[ECX] with no TEST in between, unlike the two blocks
  // above. Four terminators leave it, one per arm of the record-reading idiom, and
  // the arm that the +0x1c slot's answer takes stores 0x013f6964 ITSELF
  // (0x005a2b10 MOVSS XMM0,dword ptr [0x013f6964]) rather than a scaled zero, which
  // is why the fallback is not modelled as a multiply of anything.
  if (sw2_obj_slot_has_query(source_object(base), kId44c6220)) {  // 0x005a2a97, JZ 0x005a2b10
    const std::uint8_t* record = sw2_obj_slot_get_query(source_object(base), kId44c6220);
    scratch = param_record_float(record);
    scratch *= g_unmodelled_013f6964;  // 0x005a2ac5 / 0x005a2ae1 / 0x005a2aff
    float_at(base + 0x70) = scratch;   // 0x005a2acd / 0x005a2ae9 / 0x005a2b07
  } else {
    float_at(base + 0x70) = g_unmodelled_013f6964;  // 0x005a2b10 / 0x005a2b18
  }
  // 0x005a2ad2 / 0x005a2aee / 0x005a2b0c / 0x005a2b1d POP ESI; POP EBX; POP ECX
  // 0x005a2ad5 / 0x005a2af1 / 0x005a2b0f / 0x005a2b20 RET
  //   No return value on any of the four arms: the machine leaves whatever was last in
  //   EAX or XMM0 and none of the four paths produces a value. EAX is dead at each
  //   terminator, and it holds four different dead words depending on the arm.
  //   Note that POP ECX restores the frame word at [ESP+0x8], which the two +0x24
  //   blocks overwrote with a record address, so the value ECX ends up holding is not
  //   the receiver on the paths that took those blocks. Nothing here is claimed about
  //   ECX and the model test asserts nothing about it.
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_005a2600
