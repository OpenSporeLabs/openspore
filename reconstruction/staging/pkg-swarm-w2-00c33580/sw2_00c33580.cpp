// PKG-SWARM-W2-00C33580 -- VA 0x00c33580
// FUN_00c33580 (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000),
// 79 instructions, 0x00c33580..0x00c33685 inclusive, 262 bytes.
//
// THE COMPLETE BODY, re-derived from the image for this package with
// `objdump -D -b binary -m i386 -M intel` over the 272 bytes at this VA's file
// offset (0x832980). It reproduces the committed Ghidra listing instruction
// for instruction, at the same addresses and with the same lengths; the six
// bytes after the last RET are INT3 padding.
//
//   00c33580  83 ec 24                 sub    esp,0x24
//   00c33583  56                       push   esi
//   00c33584  8b f1                    mov    esi,ecx
//   00c33586  8b 86 b0 00 00 00        mov    eax,DWORD PTR [esi+0xb0]
//   00c3358c  83 f8 ff                 cmp    eax,0xffffffff
//   00c3358f  0f 84 ec 00 00 00        je     0xc33681
//   00c33595  50                       push   eax
//   00c33596  e8 05 9d f0 ff           call   0xb3d2a0
//   00c3359b  8b c8                    mov    ecx,eax
//   00c3359d  e8 de 37 f7 ff           call   0xba6d80
//   00c335a2  85 c0                    test   eax,eax
//   00c335a4  0f 84 d7 00 00 00        je     0xc33681
//   00c335aa  8b c8                    mov    ecx,eax
//   00c335ac  e8 cf 65 f8 ff           call   0xbb9b80
//   00c335b1  8b 08                    mov    ecx,DWORD PTR [eax]
//   00c335b3  8b 50 04                 mov    edx,DWORD PTR [eax+0x4]
//   00c335b6  8b 40 08                 mov    eax,DWORD PTR [eax+0x8]
//   00c335b9  89 54 24 10              mov    DWORD PTR [esp+0x10],edx
//   00c335bd  89 44 24 14              mov    DWORD PTR [esp+0x14],eax
//   00c335c1  85 c9                    test   ecx,ecx
//   00c335c3  0f 84 b8 00 00 00        je     0xc33681
//   00c335c9  8b 86 b0 00 00 00        mov    eax,DWORD PTR [esi+0xb0]
//   00c335cf  83 f8 ff                 cmp    eax,0xffffffff
//   00c335d2  0f 84 a9 00 00 00        je     0xc33681
//   00c335d8  50                       push   eax
//   00c335d9  e8 c2 9c f0 ff           call   0xb3d2a0
//   00c335de  8b c8                    mov    ecx,eax
//   00c335e0  e8 9b 37 f7 ff           call   0xba6d80
//   00c335e5  85 c0                    test   eax,eax
//   00c335e7  0f 84 94 00 00 00        je     0xc33681
//   00c335ed  57                       push   edi
//   00c335ee  8b c8                    mov    ecx,eax
//   00c335f0  e8 0b 6f f8 ff           call   0xbba500
//   00c335f5  8b f8                    mov    edi,eax
//   00c335f7  85 ff                    test   edi,edi
//   00c335f9  0f 84 81 00 00 00        je     0xc33680
//   00c335ff  8d 4c 24 10              lea    ecx,[esp+0x10]
//   00c33603  51                       push   ecx
//   00c33604  8b ce                    mov    ecx,esi
//   00c33606  e8 c5 f6 ff ff           call   0xc32cd0
//   00c3360b  b8 ac 7b 66 01           mov    eax,0x1667bac
//   00c33610  8d 54 24 1c              lea    edx,[esp+0x1c]
//   00c33614  52                       push   edx
//   00c33615  8b cf                    mov    ecx,edi
//   00c33617  89 44 24 20              mov    DWORD PTR [esp+0x20],eax
//   00c3361b  89 44 24 24              mov    DWORD PTR [esp+0x24],eax
//   00c3361f  c7 44 24 28 ae 7b 66 01  mov    DWORD PTR [esp+0x28],0x1667bae
//   00c33627  e8 04 6d 8a ff           call   0x4da330
//   00c3362c  8d 44 24 1c              lea    eax,[esp+0x1c]
//   00c33630  50                       push   eax
//   00c33631  8d 4e 0c                 lea    ecx,[esi+0xc]
//   00c33634  e8 47 bd f3 ff           call   0xb6f380
//   00c33639  8d 4c 24 08              lea    ecx,[esp+0x8]
//   00c3363d  51                       push   ecx
//   00c3363e  8d 54 24 10              lea    edx,[esp+0x10]
//   00c33642  52                       push   edx
//   00c33643  8d 4e 14                 lea    ecx,[esi+0x14]
//   00c33646  c7 44 24 10 02 00 00 00  mov    DWORD PTR [esp+0x10],0x2
//   00c3364e  e8 2d 91 22 00           call   0xe5c780
//   00c33653  8b 00                    mov    eax,DWORD PTR [eax]
//   00c33655  8b 48 14                 mov    ecx,DWORD PTR [eax+0x14]
//   00c33658  51                       push   ecx
//   00c33659  8d 4e 3c                 lea    ecx,[esi+0x3c]
//   00c3365c  e8 2f 07 99 ff           call   0x5c3d90
//   00c33661  8b 54 24 24              mov    edx,DWORD PTR [esp+0x24]
//   00c33665  8b 44 24 1c              mov    eax,DWORD PTR [esp+0x1c]
//   00c33669  2b d0                    sub    edx,eax
//   00c3366b  83 e2 fe                 and    edx,0xfffffffe
//   00c3366e  83 fa 02                 cmp    edx,0x2
//   00c33671  7e 0d                    jle    0xc33680
//   00c33673  85 c0                    test   eax,eax
//   00c33675  74 09                    je     0xc33680
//   00c33677  50                       push   eax
//   00c33678  e8 03 3d 31 00           call   0xf47380
//   00c3367d  83 c4 04                 add    esp,0x4
//   00c33680  5f                       pop    edi
//   00c33681  5e                       pop    esi
//   00c33682  83 c4 24                 add    esp,0x24
//   00c33685  c3                       ret
//
// WHAT THE BODY IS. A guarded pipeline with five early exits and one
// conditional tail. It resolves a handle held at receiver+0xb0 through a
// two-step global-table lookup, twice, re-reading the handle the second time;
// gates on the first word of a three-word record that the lookup target owns;
// resolves a child from the second lookup target; asks 0x00c32cd0 to fill a
// twelve-byte colour out-parameter with two of the record's words pre-seeded in
// it; publishes a four-word block of which three words are two .rdata pointers;
// looks key 2 up in an ordered map that lives at receiver+0x14; hands the text
// pointer found at the found node's +0x14 to a sink at receiver+0x3c; and then,
// only if the published block holds a non-null begin pointer at least four
// bytes below its element 2, releases that begin pointer.
//
// THE SIX THINGS A READER GETS WRONG, each of which the model test attacks:
//
//  1. THE HANDLE PUSH IS NOT THE GETTER'S ARGUMENT. 0x00c33595 pushes the
//     handle, 0x00c33596 calls 0x00b3d2a0 whose `RET` at 0x00b3d2a5 is BARE,
//     and 0x00c3359d calls 0x00ba6d80 which reads that word at [ESP+0x4]
//     (0x00ba6d80) and pops it (`RET 0x4`). So the getter takes nothing, the
//     handle is the LOOKUP's argument, and the getter's return is the LOOKUP's
//     receiver. Swapping any two of the three is the easiest mistake in this
//     body and the test measures all three.
//  2. THE HANDLE IS READ TWICE (0x00c33586 and 0x00c335c9) and the second read
//     is a re-read of the same slot, not a cached copy: nothing in the body
//     writes receiver+0xb0, but a callee it calls could, and the machine's
//     second read would see that.
//  3. THE SENTINEL IS -1, NOT 0. `CMP EAX,-0x1` / `JE` twice; a handle of 0 is
//     an ordinary value that 0x00ba6d80 treats specially (it returns the
//     receiver's own +0x14c word), so treating 0 as the sentinel would drop a
//     live path.
//  4. THE GATE IS THE RECORD'S FIRST WORD AND IT IS A VALUE, NOT A POINTER.
//     0x00c335b1 loads word 0 into ECX and 0x00c335c1 `TEST ECX,ECX` tests
//     THAT register. The word is never stored, so the twelve-byte block's first
//     word is whatever the colour callee later writes there. A reading that
//     treats word 0 as a pointer and dereferences it, or that tests word 1
//     instead, is refuted by the test.
//  5. 0x0c, 0x14 AND 0x3c ARE ADDRESSES, NOT VALUES. All three are `LEA ECX,[ESI+disp]`
//     and each is the ECX receiver of a different callee. The words stored at
//     those offsets are never loaded by this body.
//  6. THE TAIL GUARD IS `(end - begin) & 0xfffffffe > 2` COMPARED AS A SIGNED
//     INT, and `begin` is the block's element 0, which this body never writes.
//     `JLE` (0x00c33671) is signed, so a `begin` above `end` -- an enormous
//     unsigned difference -- SKIPS the release; the `AND` makes a difference
//     of 3 skip it too; and the null test at 0x00c33673 comes AFTER the range
//     test, so the two are not interchangeable.
//
// POINTER LEVELS, in order, because this body has four of them and each is
// wrong in a different way:
//
//   lookup result  (opaque pointer, never dereferenced by this body)
//     -> record  = result + 0x74                     (0x00bb9b80 returns an address)
//        -> record[0], record[4], record[8]          (0x00c335b1/b3/b6, ONE level)
//     -> child  (opaque, never dereferenced by this body)
//   colour out-parameter = FR+0x08, 12 bytes         (0x00c335ff; three FSTPs)
//   map find: out-parameter at FR+0x04; the CALL RETURNS that address
//     (0x00e5c7b2 `MOV EAX,[ESP+0x8]`), so 0x00c33653 `MOV EAX,[EAX]` is the
//     read of the slot the callee just wrote -- ONE level, not two
//       -> node[0x14]                               (0x00c33655)
//          -> passed to 0x005c3d90 AS A POINTER, which dereferences it
//             (`CMP WORD PTR [EDX],0` at 0x005c3d94) and this body does not.
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and none of the
// 79 instructions is a register- or memory-operand transfer. No slot boundary
// and no member is declared anywhere in this package.
//
// GLOBALS: two .rdata words, 0x1667bac (stored twice) and 0x1667bae, and no
// other data-segment address. The xref export carries no data-reference edge
// type at all, so there is no second machine side to corroborate the store's
// mode and the GLOBALS dimension cannot pass for this target. That is a
// property of the evidence, not a defect here: the store is in the listing, so
// omitting it would falsify the body.
//
// RETURN SEMANTICS: void, with the disagreement recorded rather than hidden --
// see the header's closing paragraph and unresolved_questions. Nothing coherent
// is ever in EAX at the single RET.

#include "sw2_00c33580_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00c33580 {

extern "C" void SW2_00C33580_THISCALL re_00c33580(SimRecord* self) {
  // 00c33580  sub esp,0x24      the 0x24-byte frame, FR = entry_ESP-0x24
  // 00c33583  push esi          saved at FR-0x04, restored at 00c33681
  // 00c33584  mov esi,ecx       the receiver alias: every receiver access in
  //                             the body goes through ESI, which is why the
  //                             machine-derived receiver record reports
  //                             shape R-ALIAS and enumerates only 0xb0
  alignas(4) std::uint8_t frame[kFrameBytes];

  // The model test plants this word; on the original it is whatever the
  // caller's frame held. Read exactly once, at 00c33665.
  *word_at(&frame, kFrameNames0) = w2_00c33580_stack_residue();

  // Seeds the map-find out-parameter so the read at 00c33653 is defined
  // behaviour; the real callee overwrites it on both of its exits.
  *word_at(&frame, kFrameMapOut) = kOutSlotSeed;

  // Seeds the twelve-byte block's FIRST word, which 0x00c335b1 leaves in ECX
  // and this body therefore never stores. 0x00c32cd0 is its only writer; on
  // the original the slot holds whatever the caller's frame held.
  *word_at(&frame, kFrameBlock) = kBlockFirstWordSeed;

  // 00c33586  mov eax,[esi+0xb0]
  const Word handle = *word_at(self, kReceiverHandle);
  // 00c3358c  cmp eax,-0x1
  // 00c3358f  je  0x00c33681
  if (handle == kInvalidHandle) {
    return;
  }

  // 00c33595  push eax          <-- the LOOKUP's argument, pushed BEFORE the
  // 00c33596  call 0x00b3d2a0       getter is called, and that getter's bare
  // 00c3359b  mov ecx,eax           RET leaves it there
  // 00c3359d  call 0x00ba6d80       `MOV edx,[esp+0x4]` takes it, `RET 0x4`
  LookupObject* const first =
      table_lookup_00ba6d80(global_word_00b3d2a0(), handle);

  // 00c335a2  test eax,eax
  // 00c335a4  je  0x00c33681
  if (first == nullptr) {
    return;
  }

  // 00c335aa  mov ecx,eax
  // 00c335ac  call 0x00bb9b80   LEA eax,[ecx+0x74]; RET -- an ADDRESS
  const RecordBlock* const record = record_slot_00bb9b80(first);

  // 00c335b1  mov ecx,[eax]    word 0 -- stays in the register
  // 00c335b3  mov edx,[eax+4]  word 1
  // 00c335b6  mov eax,[eax+8]  word 2
  // 00c335b9  mov [esp+0x10],edx   FR+0x0c
  // 00c335bd  mov [esp+0x14],eax   FR+0x10
  //
  // One level of indirection: the record is read through the address the
  // getter returned, and word 0 is never stored -- the twelve-byte block's
  // first word is left for the callee below to fill.
  const Word gate = *word_at(record, kRecordGateWord);
  *word_at(&frame, kFrameBlockWord1) = *word_at(record, kRecordSeedWord1);
  *word_at(&frame, kFrameBlockWord2) = *word_at(record, kRecordSeedWord2);

  // 00c335c1  test ecx,ecx     the FIRST word, as a value
  // 00c335c3  je  0x00c33681
  if (gate == 0u) {
    return;
  }

  // 00c335c9  mov eax,[esi+0xb0]   the same slot, read AGAIN -- not a cached
  // 00c335cf  cmp eax,-0x1          copy of the value above
  // 00c335d2  je  0x00c33681
  const Word handle_again = *word_at(self, kReceiverHandle);
  if (handle_again == kInvalidHandle) {
    return;
  }

  // 00c335d8  push eax
  // 00c335d9  call 0x00b3d2a0
  // 00c335de  mov ecx,eax
  // 00c335e0  call 0x00ba6d80
  LookupObject* const second =
      table_lookup_00ba6d80(global_word_00b3d2a0(), handle_again);

  // 00c335e5  test eax,eax
  // 00c335e7  je  0x00c33681
  if (second == nullptr) {
    return;
  }

  // 00c335ed  push edi        ESP stays at entry_ESP-0x2c from here to the
  //                           epilogue, which is what fixes every [esp+...]
  //                           displacement in the rest of the body
  // 00c335ee  mov ecx,eax
  // 00c335f0  call 0x00bba500
  ChildHandle* const child = child_selector_00bba500(second);
  // 00c335f5  mov edi,eax
  // 00c335f7  test edi,edi
  // 00c335f9  je  0x00c33680   the epilogue WITHOUT popping edi
  if (child == nullptr) {
    return;
  }

  // 00c335ff  lea ecx,[esp+0x10]   FR+0x08 -- the BASE of the twelve-byte
  // 00c33603  push ecx             block, whose words 1 and 2 were seeded
  // 00c33604  mov ecx,esi          above; the receiver is this body itself
  // 00c33606  call 0x00c32cd0
  //
  // The return is discarded on purpose: the next instruction is 00c3360b
  // `mov eax,0x1667bac`, which overwrites EAX without reading it.
  (void)color_fill_00c32cd0(reinterpret_cast<ColorSubject*>(self),
                            interior<RecordBlock>(&frame, kFrameBlock));

  // 00c3360b  mov eax,0x1667bac
  // 00c33617  mov [esp+0x20],eax   FR+0x18  element 1
  // 00c3361b  mov [esp+0x24],eax   FR+0x1c  element 2
  // 00c3361f  mov [esp+0x28],0x1667bae  FR+0x20  element 3
  //
  // All three stores precede every consumer of the block, and element 0 is
  // left exactly as the stack residue above: the machine never writes it.
  *word_at(&frame, kFrameNames1) = kRdataWordA;
  *word_at(&frame, kFrameNames2) = kRdataWordA;
  *word_at(&frame, kFrameNames3) = kRdataWordB;

  // 00c33610  lea edx,[esp+0x1c]   FR+0x14 -- the block's base again, and the
  // 00c33614  push edx             FIRST element
  // 00c33615  mov ecx,edi          the child, not the receiver
  // 00c33627  call 0x004da330
  array_check_004da330(reinterpret_cast<ArrayTarget*>(child),
                       word_at(&frame, kFrameNames0));

  // 00c3362c  lea eax,[esp+0x1c]   the same block
  // 00c33630  push eax
  // 00c33631  lea ecx,[esi+0xc]    an ADDRESS, not the word stored there
  // 00c33634  call 0x00b6f380
  list_sync_00b6f380(interior<SyncTarget>(self, kReceiverSync),
                     word_at(&frame, kFrameNames0));

  // 00c33639  lea ecx,[esp+0x8]    FR+0x00, the key slot
  // 00c3363d  push ecx             the SECOND stack word
  // 00c3363e  lea edx,[esp+0x10]   FR+0x04, the out-parameter
  // 00c33642  push edx             the FIRST stack word
  // 00c33643  lea ecx,[esi+0x14]   an ADDRESS
  // 00c33646  mov [esp+0x10],0x2   the key value, stored BEFORE the call
  // 00c3364e  call 0x00e5c780
  *word_at(&frame, kFrameMapKey) = kMapKeyValue;
  MapNode* const node =
      *map_find_00e5c780(interior<OrderedMap>(self, kReceiverMap),
                         slot_at<MapNode>(&frame, kFrameMapOut),
                         word_at(&frame, kFrameMapKey));

  // 00c33653  mov eax,[eax]    ONE level: the callee RETURNS the address of the
  // 00c33655  mov ecx,[eax+0x14]   out-parameter (0x00e5c7b2), so this reads
  //                              the slot the callee just wrote
  const OpaqueWideText* const text = reinterpret_cast<const OpaqueWideText*>(
      *word_at(node, kNodeTextDisplacement));

  // 00c33658  push ecx        the word, used AS A POINTER by 0x005c3d90
  // 00c33659  lea ecx,[esi+0x3c]  an ADDRESS
  // 00c3365c  call 0x005c3d90
  text_emit_005c3d90(interior<TextSink>(self, kReceiverEmit), text);

  // 00c33661  mov edx,[esp+0x24]   FR+0x1c -- element 2, the END
  // 00c33665  mov eax,[esp+0x1c]   FR+0x14 -- element 0, the BEGIN, read from a
  //                                 slot this body never writes
  const auto* const range_end = reinterpret_cast<const std::uint8_t*>(
      *word_at(&frame, kFrameNames2));
  const auto* const range_begin = reinterpret_cast<const std::uint8_t*>(
      *word_at(&frame, kFrameNames0));

  // 00c33669  sub edx,eax
  // 00c3366b  and edx,0xfffffffe   an EVEN byte count: 3 rounds down to 2
  // 00c3366e  cmp edx,0x2
  // 00c33671  jle 0x00c33680       SIGNED, so begin > end skips the release
  const Word span =
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(range_end) -
                        reinterpret_cast<std::uintptr_t>(range_begin)) &
      0xfffffffeu;
  if (static_cast<std::int32_t>(span) > static_cast<std::int32_t>(kRangeThreshold)) {
    // 00c33673  test eax,eax     the null test comes SECOND
    // 00c33675  je  0x00c33680
    if (range_begin != nullptr) {
      // 00c33677  push eax
      // 00c33678  call 0x00f47380   bare RET: the caller cleans up
      // 00c3367d  add esp,0x4
      buffer_destroy_00f47380(const_cast<std::uint8_t*>(range_begin));
    }
  }
  // 00c33680  pop edi
  // 00c33681  pop esi
  // 00c33682  add esp,0x24
  // 00c33685  ret
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00c33580
