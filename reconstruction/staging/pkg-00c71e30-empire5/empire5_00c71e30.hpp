#pragma once

// Reconstruction of FUN_00c71e30 @ 0x00c71e30 (SporeApp.exe 3.1.0.22,
// snapshot 2540f2ca).
//
// EVIDENCE BASIS (every claim below traces to exactly one of these; nothing
// else is claimed).
//
//  1. Live Ghidra listing of the body - twenty-one instructions, complete, and
//     read live from the program database as raw bytes over 0x00c71e30..0x00c71e73
//     (/read_memory @ 0x00c71e30, 64 bytes):
//
//       0x00c71e30  56                 PUSH ESI
//       0x00c71e31  8b f1              MOV ESI,ECX
//       0x00c71e33  8b 8e 3c 01 00 00  MOV ECX,dword ptr [ESI + 0x13c]
//       0x00c71e39  85 c9              TEST ECX,ECX
//       0x00c71e3b  74 2a              JZ 0x00c71e67
//       0x00c71e3d  e8 6e bc f1 ff     CALL 0x00b8dab0
//       0x00c71e42  83 f8 05           CMP EAX,0x5
//       0x00c71e45  75 20              JNZ 0x00c71e67
//       0x00c71e47  8b 86 d4 00 00 00  MOV EAX,dword ptr [ESI + 0xd4]
//       0x00c71e4d  8b 50 4c           MOV EDX,dword ptr [EAX + 0x4c]
//       0x00c71e50  8d 8e d4 00 00 00  LEA ECX,[ESI + 0xd4]
//       0x00c71e56  ff d2              CALL EDX
//       0x00c71e58  50                 PUSH EAX
//       0x00c71e59  e8 42 b4 ec ff     CALL 0x00b3d2a0
//       0x00c71e5e  8b c8              MOV ECX,EAX
//       0x00c71e60  e8 0b 75 f3 ff     CALL 0x00ba9370
//       0x00c71e65  5e                 POP ESI
//       0x00c71e66  c3                 RET
//       0x00c71e67  33 c0              XOR EAX,EAX
//       0x00c71e69  5e                 POP ESI
//       0x00c71e6a  c3                 RET
//       0x00c71e6b  cc cc cc cc cc     INT3 padding, NOT part of the body
//
//     The same fifty-nine bytes were read a second, independent way - a
//     read-only `objdump -d -M intel` over 0x00c71e20..0x00c71e80 of the pinned
//     image - and the two byte streams are identical. The body is therefore 59
//     bytes, 0x00c71e30..0x00c71e6a, matching the live `ghidra_function` record's
//     `body_span_bytes: 59` / `body_end: "00c71e6a"`. The five 0xcc bytes at
//     0x00c71e6b..0x00c71e6f are alignment padding between this entry and the
//     next (which begins at 0x00c71e70 with `PUSH EBX`) and are deliberately
//     not modelled. `raw hex: 568bf18b8e3c01000085c9742ae86ebcf1ff83f8057520
//     8b86d40000008b504c8d8ed4000000ffd250e842b4ecff8bc8e80b75f3ff5ec333c05
//     ec3cccccccccc`.
//
//  2. Live Ghidra decompilation, consistent with (1) and adding nothing:
//       undefined4 __fastcall FUN_00c71e30(int param_1)
//       {
//         int iVar1;  undefined4 uVar2;
//         if (*(int *)(param_1 + 0x13c) != 0) {
//           iVar1 = FUN_00b8dab0();
//           if (iVar1 == 5) {
//             uVar2 = (**(code **)(*(int *)(param_1 + 0xd4) + 0x4c))();
//             FUN_00b3d2a0(uVar2);
//             uVar2 = FUN_00ba9370(uVar2);
//             return uVar2;
//           }
//         }
//         return 0;
//       }
//     Two things in it are evidence and two are not. That the first test is on
//     `*(int *)(param_1 + 0x13c)`, that the second test is `== 5`, and that the
//     false arm returns 0 are evidence, and they are read off the listing above.
//     The `__fastcall` spelling is NOT evidence, and neither is the rendering of
//     `FUN_00ba9370(uVar2)` as taking the same word twice: the live
//     `ghidra_function` record carries `ghidra_calling_convention: null`,
//     `ghidra_has_calling_convention: false`,
//     `ghidra_calling_convention_signal: "no_information"`,
//     `ghidra_calling_convention_role: "cross-validation-only"`,
//     `ghidra_parameter_count: 0` and `parameters: []`, so every parameter the
//     decompiler printed is the rendering of an unregistered prototype and
//     weighs nothing. What the parameters ARE is settled from the listing
//     instead - see notes 3, 4 and 6.
//
//  3. THE PUSH ESI / POP ESI PAIR IS THE CALLEE-SAVED REGISTER CONTRACT FOR
//     ESI, NOT A WAY OF CARRYING THE RECEIVER ACROSS A CALL. This is the
//     load-bearing fact of the body and it is settled from the listing plus the
//     i386 register rules, with nothing added:
//
//       * 0x00c71e31 is `8b f1` - ModRM 0xf1 is mod=11, reg=110 (ESI), rm=001
//         (ECX) - so the body WRITES ESI. ESI is callee-saved on i386: EBX, ESI,
//         EDI and EBP must come back unchanged. A body that writes ESI and
//         returns without restoring it breaks its caller's contract, which is
//         why 0x00c71e30 pushes ESI before the write and 0x00c71e65 / 0x00c71e69
//         pop it after. That is the whole reason the pair exists.
//       * The pairing is proved from the listing itself: both reachable exits
//         restore ESI before returning (0x00c71e65 before the RET at 0x00c71e66,
//         0x00c71e69 before the RET at 0x00c71e6a), so neither path can escape
//         with a clobbered ESI. The derived ABI record agrees independently -
//         `saved_registers: ["ESI"]`.
//       * The receiver is NOT what crosses the calls in ESI. It is copied to ESI
//         at 0x00c71e31 and read back out of ESI at 0x00c71e33, 0x00c71e47 and
//         0x00c71e50. Between the first of those reads and the last of them sits
//         `CALL 0x00b8dab0` at 0x00c71e3d. So the receiver's survival across
//         that call is 0x00b8dab0's obligation to leave ESI alone - which it
//         does: its body is the seven bytes `8b 81 94 01 00 00 c3`, written live
//         for this package (note 4), and it names ESI nowhere. The push does not
//         help across that boundary; the callee's convention does.
//       * ECX does not cross `CALL 0x00b3d2a0` at all, and cannot be said to.
//         0x00c71e5e is `8b c8` - ModRM 0xc8, mod=11, reg=001 (ECX), rm=000 (EAX)
//         - which OVERWRITES ECX with that call's return value before
//         0x00ba9370 is reached at 0x00c71e60. So the receiver of the last call
//         is the RESULT of 0x00b3d2a0, not this body's receiver. Nothing about
//         ECX needs to survive that call, and nothing in this package asserts
//         that it does.
//       * The record corroborates the aliasing shape rather than a different one:
//         `receiver.register: "ECX"`, `receiver.shape: "R-ALIAS"`,
//         `receiver.written_through: 0`, `receiver.bounds_only: true`.
//
//  4. THE DELEGATION AT 0x00c71e3d IS A RECEIVER HAND-OVER, PROVED BY THE CHAIN
//     OF ECX. Read straight out of the listing:
//
//       * 0x00c71e33 writes ECX with a 32-bit LOAD (opcode 0x8b, not LEA's 0x8d)
//         of the word the receiver holds at displacement 0x13c. The ModRM byte is
//         0x8e - mod=10 so a disp32 follows, reg=001 so the destination is ECX,
//         rm=110 so the base is ESI - and the disp32 is 0x0000013c.
//       * ECX is not rewritten between 0x00c71e33 and 0x00c71e3d. The only
//         instructions in between are 0x00c71e39 (`85 c9`, TEST - writes EFLAGS
//         only) and 0x00c71e3b (`74 2a`, JZ - writes EFLAGS only).
//       * Therefore at the moment of the call ECX still holds the word 0x00c71e33
//         loaded, and 0x00b8dab0 - `MOV EAX,dword ptr [ECX + 0x194]` / `RET`,
//         seven bytes read live at that address - receives THAT word as its own
//         receiver.
//       * So `CMP EAX,0x5` at 0x00c71e42 compares the 32-bit word at
//         (word at receiver+0x13c) + 0x194 against 5. The +0x194 belongs to the
//         DELEGATED object, not to this body's receiver, and the two are
//         different objects at different displacements; no member of this body's
//         receiver is named by either number.
//       * The promoted sibling package `pkg-00b8dab0-field194-getter`
//         (src/reconstruction/pkg_00b8dab0_field194_getter/, promoted, runtime
//         GATED) is the record of that address. Its mechanism - one 32-bit load
//         at displacement 0x194, one return - is reproduced locally below as
//         `helper_00b8dab0` so that the handed-over receiver is observable, and
//         that local copy is a model of the target's MECHANISM, not a second
//         reconstruction of it.
//       * The displacement 0x13c is not this package's own invention. The
//         committed xref export's caller 0x00c3828b is `8b 8e 3c 01 00 00` =
//         `MOV ECX,dword ptr [ESI + 0x13c]` - the same displacement, the same
//         base, in a caller of this very function - and the sibling body at
//         0x00c70e00 reads it too at `8b 89 3c 01 00 00`. Three independent sites
//         agree that 0x13c is a word of the receiver this body is handed.
//
//  5. THE COMPARISON IS A SIGN-EXTENDED imm8 AGAINST FIVE. 0x00c71e42 is
//     `83 f8 05`: 0x83 is the `CMP r/m32, imm8` form - opcode 0x3d would be
//     `CMP EAX, imm32` - and 0x83 sign-extends its immediate to 32 bits before
//     comparing. The immediate byte is 0x05, so the constant is +5 and the
//     comparison is against all thirty-two bits of EAX. There is no narrower
//     form in the body: no `3d` and no `66` prefix appears anywhere in the
//     fifty-nine bytes, so nothing here compares 8 or 16 bits.
//
//  6. THE DISPATCH AT 0x00c71e47..0x00c71e56 IS A TWO-LEVEL TABLE LOAD, AND THE
//     ARGUMENT IS AN ADDRESS. Four instructions, each decidable from its bytes:
//
//       * 0x00c71e47 `8b 86 d4 00 00 00` - MOV EAX,dword ptr [ESI + 0xd4]. A
//         32-bit LOAD (0x8b, not LEA's 0x8d) of the word the receiver holds at
//         displacement 0xd4. ModRM 0x86: mod=10 (disp32), reg=000 (EAX),
//         rm=110 (ESI). So EAX now holds a POINTER; 0xd4 is 212.
//       * 0x00c71e4d `8b 50 4c` - MOV EDX,dword ptr [EAX + 0x4c]. A 32-bit LOAD
//         of the word that pointer addresses, at displacement 0x4c. ModRM 0x50
//         is mod=01, so the displacement is a single disp8 byte, and that byte
//         is 0x4c; reg=010 (EDX), rm=000 (EAX). 0x4c is 76, which is 19 four-byte
//         words, so this reads the word nineteen slots along from the table's
//         base. EDX is now the callee.
//       * 0x00c71e50 `8d 8e d4 00 00 00` - LEA ECX,[ESI + 0xd4]. THE OPCODE IS
//         0x8d. This is the load/LEA distinction, and it is decidable here
//         because the very same displacement was LOADED with opcode 0x8b four
//         instructions earlier: 0x00c71e47 dereferences receiver+0xd4 and
//         0x00c71e50 forms its address. Same operand, different question, two
//         different opcodes in the same body. So the callee's receiver is
//         `&(receiver's word at +0xd4)` - the address of the embedded object -
//         and NOT the word stored there and NOT this body's own receiver.
//       * 0x00c71e56 `ff d2` - CALL EDX. ModRM 0xd2 is mod=11 (register), so
//         this is a register-indirect transfer with no displacement operand at
//         all. There is exactly one indirect transfer in the body, and the
//         derived record counts exactly one: `dispatch.indirect_calls: 1`.
//
//     What that SHAPE is, and what it is not. The shape is proven: a word loaded
//     out of the receiver, a second word loaded out of what that word addresses,
//     and a call through the second. That is the canonical x86-32 virtual-call
//     shape and the repository's own dispatch classifier reads this very listing
//     as `VTABLE_SLOT` at slot displacement 0x4c. What is NOT proven is the
//     IDENTITY behind it: no class is named for the object at receiver+0xd4
//     anywhere in this pack (`categories.types`, `categories.globals` and
//     `categories.vtables` are all MISSING; `vtable_at` is empty), so the words
//     "class" and "override" appear nowhere below and the modelled table is
//     called a table because its shape is a table, not because a C++ vtable was
//     identified. The record's own `dispatch.vtable_shaped_loads: 0` is reported
//     at note 12 rather than argued with: this package does not need it, because
//     the shape is established from the listing bytes and the tool that
//     adjudicates the dimension reads those bytes and not that count.
//
//  7. THE STACK: ONE WORD IS PUSHED AND THE LAST CALLEE POPS IT, AND THE
//     `POP ESI` IS A DIFFERENT WORD. Three independent facts settle this, and
//     the third is in-binary corroboration rather than an assumption:
//
//       * 0x00c71e58 is `50` - PUSH EAX, one dword, the value the dispatch at
//         0x00c71e56 returned.
//       * 0x00b3d2a0 - the callee at 0x00c71e59 - is TWO instructions, SIX bytes,
//         read live at that address: `a1 e4 ea 67 01 c3`, which is
//         `MOV EAX, moffs32 [0x0167eae4]` / `RET`. The opcode 0xa1 is the moffs
//         form and carries NO ModRM byte at all, so there is no register field a
//         receiver could have arrived in and no register field a stack argument
//         could have been read through: this callee takes nothing. Its `RET` is
//         then the bare 0xc3, so it pops nothing either, and the word pushed
//         above survives it.
//       * 0x00ba9370 - the callee at 0x00c71e60 - READS that word. Its first
//         three instructions are `PUSH ECX` (0x00ba9370),
//         `CMP dword ptr [ESP + 0x8],-0x1` (0x00ba9371) and `PUSH ESI`
//         (0x00ba9376). At 0x00ba9371, one PUSH below its own entry, [ESP+0x8]
//         IS the word the caller pushed at 0x00c71e58 - the `PUSH ECX` having
//         moved the return address from [ESP] to [ESP+4]. So the pushed word is
//         0x00ba9370's ONE stack argument. And both of 0x00ba9370's returns are
//         `RET 0x4` - 0x00ba93a1 on the found path and 0x00ba93a8 on the
//         not-found path - so the callee pops exactly that one word.
//       * Which leaves `POP ESI` at 0x00c71e65 popping the OTHER word: the
//         CALLER'S ESI, saved by `PUSH ESI` at 0x00c71e30. It cannot be popping
//         the dispatch's result - 0x00ba9370's `RET 0x4` has already taken that,
//         and a POP cannot reach below a word a callee's RET consumed.
//       * The corroboration is 0x00ba9370 itself, which writes ESI at 0x00ba9377
//         (`8b f1`, MOV ESI,ECX) and therefore does the IDENTICAL PUSH ESI /
//         POP ESI dance at 0x00ba9376 and 0x00ba939f for the identical reason -
//         and it does it while also ending in `RET 0x4`. One function, one
//         listing, both facts: a callee that pops its own argument is a function
//         that also honours the callee-saved rule, and `POP ESI` and `RET 0x4`
//         are visibly different mechanisms doing different work.
//
//     So the entry's own stack effect is: zero ordinary stack arguments, zero
//     bytes of callee cleanup, and the caller owns cleanup - `cleanup: bytes 0,
//     side "caller", evidence "ret with no immediate, no stack reads"`, with
//     `ret_form: RET` and both `RET`s being the bare 0xc3. The words the body
//     pushes and pops are all consumed inside the body or by its own callee,
//     and the net displacement across 0x00c71e30..0x00c71e66 is zero.
//
//  8. THE RETURN IS EAX, AT A FULL THIRTY-TWO BITS ON BOTH REACHABLE EXITS, AND
//     NOTHING MORE IS PROVABLE. There are exactly two reachable returns,
//     0x00c71e66 and 0x00c71e6a, and `parse.flow_complete: true` with
//     `parse.unparsed: 0` over `declared_count: 21` says the listing is the
//     whole body rather than a slice.
//
//       * The null arm, 0x00c71e67: `33 c0` is XOR EAX,EAX - ModRM 0xc0, mod=11,
//         reg=000, rm=000 - which writes all thirty-two bits of EAX with zero.
//         Not the 8-bit `xor al,al` (which would be `30 c0`) and not a `MOV
//         EAX,imm32`, so nothing of the register is left unproven on this path.
//       * The passing arm, 0x00c71e60: EAX is whatever 0x00ba9370 returned.
//         This body performs no arithmetic or masking on it - 0x00c71e65 is a POP
//         into ESI and 0x00c71e66 is a RET, neither of which touches EAX - so it
//         crosses verbatim, and the WIDTH of what comes back is 0x00ba9370's to
//         establish, not this listing's. 0x00ba9370's own listing does establish
//         it: its only writes to EAX are `33 c0` at 0x00ba93a4 and
//         `8b 40 14` at 0x00ba939c, both full 32-bit.
//       * So the machine claim is exact and narrow: EAX is the return register
//         and a full dword arrives in it on both paths. The claim is NOT that
//         the value is 32 bits WIDE in a C sense. `return.type` is null,
//         `register_class` is the single-heuristic "integral",
//         `sret.present: false` is an APPROXIMATION whose own `basis` warns the
//         absence is weak, and `variadic` is UNKNOWN.
//       * Nor is the SOURCE-LEVEL TYPE decided, and the evidence points both
//         ways, so it is left UNKNOWN and spelled as the widest type both paths
//         provably agree on. Three sampled callers, all of which put the receiver
//         in ECX and push nothing before the call:
//           0x00ad4a2a  call ; 0x00ad4a2f `85 c0` TEST EAX,EAX ; 0x00ad4a31 JZ
//                       -> a NULL TEST, which a pointer and an integer share;
//           0x00ad4a3a  call ; 0x00ad4a3f `8b 80 84 00 00 00` MOV EAX,[EAX+0x84]
//                       -> a DEREFERENCE of the result at +0x84, which is
//                          pointer-shaped use;
//           0x00c382b5  call ; 0x00c382ba `8b f8` MOV EDI,EAX
//                       -> carried in a register, saying nothing.
//         One caller dereferences the result and one null-tests it, so the value
//         behaves like a pointer to those two and like a plain dword to the
//         machine. `std::uint32_t` is the spelling that is true of both readings
//         and asserts neither.
//
//  9. THE CALLING CONVENTION, AND WHAT THE BYTES DO NOT DECIDE. The derived ABI
//     record for this VA (`categories.abi_derived`, schema
//     `openspore-abi-inference-1`) reports, verbatim:
//
//       verdict               ABI_INFERRED
//       completeness          CORE_RESOLVED
//       conventions           calling_convention "__thiscall",
//                             candidate_conventions ["__thiscall","__fastcall"],
//                             ambiguities [], confidence INFERRED,
//                             corroboration "not_available"
//       receiver              present true, register ECX,
//                             hidden_this_register ECX,
//                             offsets [212, 316], max_offset 316,
//                             shape R-ALIAS, written_through 0,
//                             bounds_only TRUE
//       cleanup               bytes 0, side "caller"
//       stack_arguments       observed_slots 0, derived_slots 0, total_bytes 0
//       dispatch              indirect_calls 1, vtable_shaped_loads 0,
//                             call_offsets []
//       tail_call             present false
//       return                register EAX, register_class "integral", type null
//       cross_validation      agreement false, ghidra "no_information",
//                             persisted "no_information", both conventions null
//
//     PROVEN, and discriminating, read off the listing with nothing added:
//       * EXACTLY ONE register argument, arriving in ECX. 0x00c71e31 reads ECX
//         on entry and copies it; the record names `receiver_register: ECX` and
//         `hidden_this_register: ECX`; and three sampled call sites put the
//         receiver in ECX immediately before the call with NOTHING pushed in
//         between (0x00ad4a28/0x00ad4a2a, 0x00ad4a38/0x00ad4a3a,
//         0x00c382b3/0x00c382b5). Under __cdecl the receiver would arrive at
//         [ESP+4] and 0x00c71e31's copy would have nothing to copy; that is what
//         REFUTES __cdecl, and it is the only convention the bytes eliminate.
//       * ZERO ordinary stack arguments. No instruction in the body names a
//         memory operand relative to ESP - the only memory operands in all
//         fifty-nine bytes are `[ESI + 0x13c]`, `[ESI + 0xd4]`, `[EAX + 0x4c]`
//         and `[ESI + 0xd4]` again - and the record agrees
//         (`observed_slots: 0`, `derived_slots: 0`, `total_bytes: 0`).
//       * ZERO bytes of callee cleanup, owned by the CALLER. Both exits are the
//         bare 0xc3; 0xc2 would carry an imm16. With zero stack arguments even
//         __stdcall would pop nothing, so cleanup is 0 under every candidate
//         convention and it separates none of them. It is stated because it is
//         provable, not because it decides anything.
//
//     NOT PROVEN, and NOT discriminated by any byte of this body:
//       * __thiscall versus __fastcall. For a function of one register argument
//         and zero stack arguments the two conventions emit IDENTICAL machine
//         code. No byte here distinguishes them, and the record says so in its
//         own `candidate_conventions` list. What would distinguish them is a
//         SOURCE-LEVEL fact this evidence does not carry: that the register
//         argument is a C++ `this` on a class rather than an ordinary first
//         parameter. Nothing in this pack names a class for the receiver -
//         `receiver.bounds_only` is true, and `class_type`, `namespace`,
//         `sdk_type` and `sdk_name` are all null in the live record. THE
//         DISTINCTION IS THEREFORE UNKNOWN.
//       * The `PKG_00C71E30_THISCALL` macro below is spelled __thiscall because
//         that is the derived record's OWN `calling_convention`, and this
//         package follows the repository's machine-derived record rather than
//         the decompiler's unregistered-prototype rendering (note 2). It is a
//         NAMING of a shape the record names, NOT a claim that the bytes chose
//         between two byte-identical encodings. Nothing in this package depends
//         on the difference: the modelled interfaces at note 7 put every callee
//         receiver in ECX and push nothing, which is what both conventions
//         describe, and the model test measures that shape off ESP rather than
//         asserting a convention. `confidence: INFERRED` and
//         `corroboration: not_available` are recorded here rather than glossed:
//         the two-oracle corroboration the record asks for does not exist for
//         this VA, and `cross_validation.agreement` is false with both oracles
//         reporting "no_information".
//       * Whether the register argument is variadic-adjacent: the record's
//         `variadic` is UNKNOWN and nothing here bears on it.
//
//  10. THE COMMITTED XREF EXPORT, READ WHOLE FOR THIS VA.
//     knowledgegraph/triage/xrefs-2540f2ca.tsv records exactly THREE edges OUT
//     of 0x00c71e30, all `direct-call`, and they are the three `CALL rel32` the
//     listing shows:
//
//       00c71e30  00b3d2a0  direct-call  00c71e59
//       00c71e30  00b8dab0  direct-call  00c71e3d
//       00c71e30  00ba9370  direct-call  00c71e60
//
//     and FORTY rows INTO it. The three callsite_va values are the three call
//     sites the listing carries, one for one. So the CALL set has an independent
//     machine oracle, and the entry names each callee by suffixing its VA onto
//     the symbol, which is the repository's convention for making the two
//     comparable. The export has no row for the indirect transfer at 0x00c71e56,
//     which is consistent: it records direct calls, and this one has no immediate
//     target.
//
//     knowledgegraph/triage/datarefs-2540f2ca.tsv contains ZERO rows for
//     0x00c71e30. That is the right answer and it is consistent with the
//     listing: all three of the body's memory operands are REGISTER-relative,
//     and the one absolute data address in the chain, 0x0167eae4, belongs to the
//     body of 0x00b3d2a0 and not to this one (note 7). This is a recorded
//     absence, not an exhaustive proof that no data reference exists.
//
//  11. THE TWO DISPLACEMENTS ARE SPELLED AS VALUES, NEVER AS MEMBERS. 0x13c and
//     0xd4 are where this body was observed reaching; they are not field
//     identities. The derived receiver record says so in its own words -
//     `bounds_only: true` means "where the body was SEEN reaching", not a layout
//     - and this pack carries `categories.types: MISSING`,
//     `categories.globals: MISSING` and `categories.vtables: MISSING`. A member
//     name here would be a field-identity assertion with nothing behind it,
//     exactly as the two promoted sibling packages decline to name their words
//     at 0x194 and 0x13c. This package names neither word, and it names no class
//     for the receiver.
//
//  12. TWO PROPERTIES OF THE DERIVED RECORD, RECORDED AND NOT ARGUED WITH.
//       * `dispatch.vtable_shaped_loads: 0` beside `dispatch.indirect_calls: 1`.
//         The record sees the one indirect transfer and does not classify its
//         shape. The shape is nevertheless decidable from the listing bytes
//         (note 6), and the repository's own VIRTUAL DISPATCH dimension reads
//         those bytes rather than that count, reaching `VTABLE_SLOT` at 0x4c on
//         this listing. Nothing in this package is relaxed to accommodate the
//         zero; `kMachineIndirectCallCount` and
//         `kMachineVtableShapedLoadCount` below pin BOTH numbers as the record
//         states them, disagreement included, so the model test cannot be used
//         to quietly assert the record said otherwise.
//       * `record.abi` - the PERSISTED projection - is the empty object `{}`
//         while `categories.abi_derived` holds the whole derivation. The record's
//         own `cross_validation` reports `persisted: "no_information"`, which is
//         consistent: there is no second opinion stored to compare against.
//
// WHAT IS NOT CLAIMED
//  * Whether the register argument is a C++ `this` or an ordinary first
//    parameter. See note 9. The bytes do not discriminate __thiscall from
//    __fastcall, no class is named for the receiver anywhere in the pack, and
//    the difference is left UNKNOWN.
//  * The source-level type of the return. One sampled caller dereferences the
//    result and one null-tests it; the record's "integral" class comes from a
//    single heuristic. See note 8. `std::uint32_t` is a width both readings
//    agree on and asserts no game concept.
//  * Any name for the word at receiver+0x13c, for the word at receiver+0xd4, or
//    for the receiver's class. See note 11.
//  * Any name for the word the delegated object holds at +0x194, and any claim
//    that it means the same kind of thing as anything here. It belongs to
//    0x00b8dab0's body.
//  * The class behind the table reached through receiver+0xd4, or that it is a
//    C++ vtable. The two-level load SHAPE is proven; the identity is not. See
//    note 6.
//  * 0x00ba9370's internals. Its interface is transcribed (note 7); its
//     container walk - the `[EAX+0x14]` load at 0x00ba939c, the
//     `LEA ECX,[ESI+0x150]` at 0x00ba9385 and the `ADD ESI,0x154` at 0x00ba9392
//     - is observed and NOT modelled, and `EmpireIndex`'s extent below is
//     pointer-sized precisely so that it is not read as a recovered layout for
//     an object the real 0x00ba9370 reaches at least to +0x154.
//  * 0x00b3d2a0's global. `MOV EAX,dword ptr [0x0167eae4]` is what the real
//    0x00b3d2a0 does, and 0x0167eae4 is that function's data address, not this
//    body's. No `g_`-named global appears in this package, and the zero rows in
//    the datarefs sidecar for 0x00c71e30 say so independently.
//  * The receiver's size. 0x140 below is a MODELLING BOUND - the prefix through
//    the furthest word the body reads - not a recovered allocation size.
//  * Any nullability, ownership, AddRef/Release, thread-safety or lifetime
//    contract for the receiver, for the word it holds at +0x13c, or for the
//    dispatch's result.
//  * Any ordinary stack argument of the entry, any variadic behaviour
//    (`variadic: UNKNOWN`), and any callee-side cleanup of the entry.
//  * Any runtime, Wine, trace, differential or OBSERVED-behaviour claim. No
//    runtime evidence exists for this VA; the runtime gate is left open.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00c71e30 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00C71E30_THISCALL __thiscall
#else
#define PKG_00C71E30_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c71e30_empire5 {

// The unit this body's two return arms are both proven to produce: a full
// 32-bit dword in EAX (note 8). Unsigned because both arms copy bits and the
// only immediate write, at 0x00c71e67, is an unsigned 32-bit zero.
using SlotWord = std::uint32_t;

// ---------------------------------------------------------------------------
// Types. Four distinct objects, kept as four distinct types so no two of them
// can be passed for one another. Which of them the body actually reaches, and
// how far into each, is note 11 and note 6 respectively.
// ---------------------------------------------------------------------------

// Receiver of 0x00c71e30, modelled at exactly the width the machine reaches
// and no more: 0x140 bytes, the prefix through the word at +0x13c, which is the
// furthest of the two reached displacements. No member is declared. The extent
// is a MODELLING BOUND, not a recovered allocation size.
struct alignas(4) OpaqueReceiver {
  std::array<std::uint8_t, 0x140> opaque_bytes{};  // 0x00..0x13f
};

// The object the word at receiver+0x13c POINTS AT - a different object from the
// receiver above, and the one 0x00b8dab0 receives as its own receiver (note 4).
// Modelled at 0x198 so the single word 0x00b8dab0 reads at +0x194 is
// addressable; that is the same modelling bound the promoted sibling package
// uses and for the same reason. Declared as its own type so that passing this
// body's own receiver straight through would not compile.
struct alignas(4) DelegatedReceiver {
  std::array<std::uint8_t, 0x198> opaque_bytes{};  // 0x00..0x197
};

// The EMBEDDED object at receiver+0xd4: the thing 0x00c71e50 takes the ADDRESS
// of and passes as the dispatch's receiver. Its first word is the table pointer
// 0x00c71e47 loads. Four bytes is all THIS BODY reads of it - it reads no
// displacement but zero - so four bytes is all that is modelled. The dispatch
// callee may reach further; that is the callee's business and is not claimed
// here, so this extent says nothing about the real object's size.
struct alignas(4) DispatchedObject {
  const void* table;  // +0x00: the word 0x00c71e47 loads
};

// The receiver of 0x00ba9370. Pointer-sized, deliberately, and NOT because the
// real 0x00ba9370's receiver is four bytes: that body reaches +0x150 and +0x154,
// so this extent is a token, not a layout, and no offset of it is claimed. The
// only fact about it this package uses is that it arrives in ECX (note 7).
struct alignas(4) EmpireIndex {
  std::uint32_t opaque_word;  // +0x00
};

// The dispatched slot's type: a receiver in ECX, zero ordinary stack
// arguments, and one 32-bit dword back in EAX. `kDispatchedCalleeShape` below
// pins that shape against the listing's own two-level load.
using SlotFunction = SlotWord(PKG_00C71E30_THISCALL*)(DispatchedObject*);

// The dispatch table as this body reads it: nineteen four-byte words along, and
// not one word more that this body names. The prefix is the seventeen words
// before +0x40, which the body never reaches - it is here so that the observed
// slot sits at the address the listing says it sits at, rather than at the
// address its index would give a table that started at its own slot. The decoys
// on BOTH sides and the sentinel immediately past the last one exist so that a
// slot index that is wrong is OBSERVABLE instead of aliased onto a neighbouring
// valid pointer - the fixture defect described in
// src/reconstruction/pkg_job_continuation_0068f9b0/, where a table whose two
// slots sat next to one another let a one-slot-too-far dispatch land on a
// perfectly callable pointer and the test passed anyway. Here every word from
// +0x40 to +0x5c is its own callable slot, so a wrong index by one, two, three
// or four lands on a DIFFERENT callee rather than off the end, one further lands
// on `sentinel`, and one inside the prefix cannot land on a valid pointer at all.
struct DispatchTable {
  std::array<std::uint8_t, 0x40> unreachable_prefix{};  // +0x00..+0x3f
  SlotFunction decoy_40;  // +0x40
  SlotFunction decoy_44;  // +0x44
  SlotFunction decoy_48;  // +0x48
  SlotFunction slot_4c;   // +0x4c  <- THE slot 0x00c71e4d reads
  SlotFunction decoy_50;  // +0x50
  SlotFunction decoy_54;  // +0x54
  SlotFunction decoy_58;  // +0x58
  SlotFunction decoy_5c;  // +0x5c
  SlotFunction sentinel;  // +0x60  <- immediately past the last modelled slot
};

// ---------------------------------------------------------------------------
// Displacements, spelled as values (note 11).
// ---------------------------------------------------------------------------

// The word this body's own receiver holds at +0x13c, taken from the disp32 of
// `MOV ECX,dword ptr [ESI + 0x13c]` at 0x00c71e33. 316.
constexpr std::size_t kDelegatedDisplacement = 0x13c;

// The word this body's own receiver holds at +0xd4, taken from the disp32 of
// `MOV EAX,dword ptr [ESI + 0xd4]` at 0x00c71e47. 212. It is LOADED there and
// its ADDRESS is taken at 0x00c71e50.
constexpr std::size_t kDispatchedDisplacement = 0xd4;

// The slot displacement `MOV EDX,dword ptr [EAX + 0x4c]` reads at 0x00c71e4d,
// taken from the disp8 byte of ModRM 0x50 (mod=01). 76, which is nineteen
// four-byte words.
constexpr std::size_t kSlotDisplacement = 0x4c;

// The word index that displacement names, for the check that it is a word
// offset rather than a byte count read the other way round.
constexpr std::size_t kSlotIndex = kSlotDisplacement / sizeof(SlotFunction);

// The displacement 0x00b8dab0 reads on the DELEGATED object. It belongs to
// that target's body, not to this one (note 4), and it is stated here only so
// the modelled mechanism below has somewhere to read from.
constexpr std::size_t kDelegatedTargetDisplacement = 0x194;

// The immediate `83 f8 05` compares EAX against at 0x00c71e42. Five, as a full
// 32-bit sign-extended comparison (note 5). NOT a semantic truth and not a
// "mode" - nothing in the evidence names what the value 5 means.
constexpr SlotWord kRequiredDelegatedScalar = 0x5;

// What `XOR EAX,EAX` at 0x00c71e67 writes: a full 32-bit zero. Transcribed, not
// interpreted - one sampled caller null-tests the result and another dereferences
// it, and both a null pointer and an integer 0 satisfy that pair.
constexpr SlotWord kNullArmValue = 0;

// The displacement is in BYTES. Read as a word COUNT instead, +0x13c would
// address byte 0x4f0 and +0x4c would address byte 0x130, both outside the
// modelled table and past the receiver for the first.
constexpr std::size_t kDelegatedIndexInWords =
    kDelegatedDisplacement / sizeof(SlotWord);
constexpr std::size_t kDispatchedIndexInWords =
    kDispatchedDisplacement / sizeof(SlotWord);

// ---------------------------------------------------------------------------
// Addresses, and the arithmetic that must reach them. The branch displacements
// are recomputed from their encoded operands rather than restated, so a wrong
// rel8 cannot pass.
// ---------------------------------------------------------------------------

constexpr std::uint32_t kEntryAddress = 0x00c71e30;
constexpr std::uint32_t kNullArmAddress = 0x00c71e67;

// 0x00c71e3b `74 2a` - JZ rel8 = +42. 0x00c71e45 `75 20` - JNZ rel8 = +32.
// Both branches converge on 0x00c71e67, which is why there are exactly two
// returns and not three.
constexpr std::int8_t kJzDisplacement = 0x2a;
constexpr std::int8_t kJnzDisplacement = 0x20;

// 0x00c71e3e..0x00c71e41 - CALL rel32 = 0x00b8dab0. Stored as the UNSIGNED
// 32-bit pattern, because that is the byte order the encoding array is checked
// against.
constexpr std::uint32_t kDelegateCallEncodedDisplacement = 0xfff1bc6eu;
// 0x00c71e5a..0x00c71e5d - CALL rel32 = 0x00b3d2a0.
constexpr std::uint32_t kGlobalSlotCallEncodedDisplacement = 0xffecb442u;
// 0x00c71e61..0x00c71e64 - CALL rel32 = 0x00ba9370.
constexpr std::uint32_t kLookupCallEncodedDisplacement = 0xfff3750bu;

// The three direct callees, as the committed xref export spells them and as the
// listing's CALL operands resolve (notes 2 and 10). The entry names each of
// them by suffixing its VA onto the symbol.
constexpr std::uint32_t kDelegateTargetVa = 0x00b8dab0;
constexpr std::uint32_t kGlobalSlotTargetVa = 0x00b3d2a0;
constexpr std::uint32_t kLookupTargetVa = 0x00ba9370;

// 0x00b8dab0's own seven bytes, read live at that address (note 4). Carried so
// the modelled hand-over is checked against bytes and not against a name.
constexpr std::uint8_t kDelegateTargetEncoding[7] = {
    139,                          // MOV r32, r/m32
    129,                          // ModRM: mod=10 (disp32), reg=000 (EAX),
                                  //       rm=001 (ECX)
    148, 1, 0, 0,                 // disp32 = 0x00000194
    195,                          // RET
};

// 0x00b3d2a0's own two instructions, read live at that address (note 7): SIX
// bytes, `a1 e4 ea 67 01 c3`. The opcode is 0xa1, which is `MOV EAX, moffs32` -
// the moffs form, which carries a 32-bit absolute address and NO ModRM byte at
// all. That is stronger than a ModRM with rm=000: there is no register field
// present that a receiver could have arrived in and no register field a stack
// argument could have been read through. It takes nothing and it pops nothing.
// Only its INTERFACE is modelled below; the address belongs to that function's
// body and is named nowhere in this package.
constexpr std::uint8_t kGlobalSlotTargetEncoding[6] = {
    161,                          // MOV EAX, moffs32 - no ModRM byte follows
    228, 234, 103, 1,             // the 32-bit absolute address it reads
    195,                          // RET - the bare form, so it pops nothing
};

// 0x00ba9370's cleanup form, read live: BOTH of its returns are `RET 0x4`. The
// model test pins this and the entry's own zero, because the two are what
// distinguishes "the callee pops the pushed word" from "this body pops it" -
// and they are not the same thing (note 7).
constexpr std::size_t kLookupCleanupBytes = 4;

// This body's own cleanup: zero. Both of its RETs are the bare 0xc3, and it
// takes no stack argument, so the caller owns cleanup.
constexpr std::size_t kEntryCleanupBytes = 0;

// 0x00c71e30..0x00c71e6a inclusive is fifty-nine bytes.
constexpr std::size_t kTargetBodyBytes = 59;

// The body's bytes exactly as read, in decimal so that no hexadecimal literal
// is introduced that is not an operand of the machine listing (note 1). Kept in
// the header so the encoding is a claim the model test can check.
constexpr std::uint8_t kTargetEncoding[kTargetBodyBytes] = {
    86,                           // 0x00c71e30  PUSH ESI
    139, 241,                     // 0x00c71e31  MOV ESI,ECX (8b f1)
    139, 142, 60, 1, 0, 0,        // 0x00c71e33  MOV ECX,[ESI+0x13c]
    133, 201,                     // 0x00c71e39  TEST ECX,ECX (85 c9)
    116, 42,                      // 0x00c71e3b  JZ rel8 = +42 (74 2a)
    232, 110, 188, 241, 255,      // 0x00c71e3d  CALL rel32 (e8 6e bc f1 ff)
    131, 248, 5,                  // 0x00c71e42  CMP EAX,imm8 = 5 (83 f8 05)
    117, 32,                      // 0x00c71e45  JNZ rel8 = +32 (75 20)
    139, 134, 212, 0, 0, 0,       // 0x00c71e47  MOV EAX,[ESI+0xd4]
    139, 80, 76,                  // 0x00c71e4d  MOV EDX,[EAX+0x4c] (8b 50 4c)
    141, 142, 212, 0, 0, 0,       // 0x00c71e50  LEA ECX,[ESI+0xd4]
    255, 210,                     // 0x00c71e56  CALL EDX (ff d2)
    80,                           // 0x00c71e58  PUSH EAX
    232, 66, 180, 236, 255,       // 0x00c71e59  CALL rel32 (e8 42 b4 ec ff)
    139, 200,                     // 0x00c71e5e  MOV ECX,EAX (8b c8)
    232, 11, 117, 243, 255,       // 0x00c71e60  CALL rel32 (e8 0b 75 f3 ff)
    94,                           // 0x00c71e65  POP ESI
    195,                          // 0x00c71e66  RET
    51, 192,                      // 0x00c71e67  XOR EAX,EAX (33 c0)
    94,                           // 0x00c71e69  POP ESI
    195,                          // 0x00c71e6a  RET
};

// The five bytes at 0x00c71e6b: INT3 padding, NOT part of the body. The next
// entry begins at 0x00c71e70.
constexpr std::uint8_t kTargetPadByte = 0xcc;
constexpr std::size_t kTargetPadBytes = 5;
constexpr std::uint32_t kNextEntryAddress = 0x00c71e70;

// The xref export's counts for this VA (note 10), as counts because no call
// site is transcribed into any metadata this package writes.
constexpr std::size_t kRecordedOutgoingDirectCallEdges = 3;
constexpr std::size_t kRecordedIncomingDirectCallEdges = 40;

// The derived ABI record's own words, pinned so that a claim about what the
// record says cannot be edited away. `kMachineVtableShapedLoadCount` is 0
// BESIDE a real indirect call, and that disagreement is recorded rather than
// reconciled away (note 12).
constexpr const char* kAbiVerdict = "ABI_INFERRED";
constexpr const char* kAbiCompleteness = "CORE_RESOLVED";
constexpr const char* kAbiConventionNamed = "__thiscall";
constexpr const char* kAbiConventionCandidateA = "__thiscall";
constexpr const char* kAbiConventionCandidateB = "__fastcall";
constexpr std::size_t kAbiCandidateConventionCount = 2;
constexpr std::size_t kMachineIndirectCallCount = 1;
constexpr std::size_t kMachineVtableShapedLoadCount = 0;
constexpr std::size_t kAbiReceiverDisplacementCount = 2;
constexpr std::size_t kAbiSavedRegisterCount = 1;

// ---------------------------------------------------------------------------
// Accessors. These perform the same arithmetic the body performs, in named
// form. The entry writes the displacements LITERALLY so the validator can see
// the declared offsets in the target span, and the model test checks the two
// against each other rather than taking either on trust.
// ---------------------------------------------------------------------------

// The word at +0x13c of the receiver - 0x00c71e33's single memory operand, read
// as a 32-bit LOAD and not as an address.
inline std::uint32_t delegated_word_at(const OpaqueReceiver* receiver) {
  return *reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(receiver) + kDelegatedDisplacement);
}

// The STORED WORD at receiver+0xd4 - 0x00c71e47's single memory operand, a
// 32-bit LOAD, and therefore a POINTER to the embedded object, whose first word
// in turn is the table pointer. It is NOT the dispatch's receiver; see
// `dispatched_address_at` immediately below, which reads the same address and
// answers the other question. Two accessors rather than one, on purpose: the
// whole distinction this body makes at 0x00c71e47/0x00c71e50 is that one
// displacement is read once as a value and once as an address.
inline const void* embedded_object_pointer_at(const OpaqueReceiver* receiver) {
  return *reinterpret_cast<const void* const*>(
      reinterpret_cast<std::uintptr_t>(receiver) + kDispatchedDisplacement);
}

// The ADDRESS of the embedded object at receiver+0xd4 - 0x00c71e50's single
// memory operand, an LEA (opcode 0x8d, not the 0x8b of 0x00c71e47). THIS is
// the receiver the dispatch is given.
//
// And it is NOT the value `embedded_object_pointer_at` returns: one is the
// address of the object's first word, the other is the pointer stored IN that
// word. Two different pointers, and conflating them is the classic mistake in
// this shape - the object and its table pointer are not the same thing.
inline DispatchedObject* dispatched_address_at(const OpaqueReceiver* receiver) {
  return reinterpret_cast<DispatchedObject*>(
      reinterpret_cast<std::uintptr_t>(receiver) + kDispatchedDisplacement);
}

// The slot at `displacement` of the table 0x00c71e47 loaded - 0x00c71e4d's
// single memory operand, a LOAD of one four-byte word, dispatched through
// 0x00c71e56. The displacement is a parameter so the model test can drive every
// neighbouring offset through this ONE accessor and show what each of them
// reaches; the entry passes the observed one.
inline SlotFunction slot_target_at(const void* table,
                                   std::size_t displacement) {
  return *reinterpret_cast<const SlotFunction*>(
      reinterpret_cast<std::uintptr_t>(table) + displacement);
}

// The word the delegated object holds at +0x194 - 0x00b8dab0's own single
// memory operand. Used by the modelled mechanism below.
inline std::uint32_t delegated_target_word_at(
    const DelegatedReceiver* receiver) {
  return *reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(receiver) + kDelegatedTargetDisplacement);
}

// The modelled shape of the dispatch callee, as the two-level load states it:
// one receiver in a register, no ordinary stack argument, one dword back.
using DispatchedCalleeShape = SlotWord(PKG_00C71E30_THISCALL*)(
    DispatchedObject*);

// x86-32: one register argument in ECX, zero ordinary stack arguments, zero
// bytes of callee cleanup (bare RET at 0x00c71e66), caller owns cleanup, one
// 32-bit dword back in EAX.
using AbiEmpire5_00c71e30 = SlotWord(PKG_00C71E30_THISCALL*)(OpaqueReceiver*);

// Injection points for the two callees whose BODIES this package deliberately
// does not reconstruct (note 7). They are neither machine state nor a model of
// anything the listing shows: 0x00b3d2a0's word lives in a data segment this
// package does not name, and 0x00ba9370's result comes out of a container walk
// that is observed and not modelled. They exist so the model test can drive
// both and observe WHICH value reaches the last call - which is the fact the
// entry's stack behaviour turns on. They are spelled without the `g_`
// eight-hex-digit form on purpose: that form is the repository's way of NAMING a
// data-segment address, and this body reaches no data-segment address of its own
// (note 10).
extern SlotWord g_global_slot_value;
extern SlotWord g_lookup_result;

// What the modelled lookup observed on its way through. The two callees whose
// bodies this package does not reconstruct are modelled for their INTERFACE
// (note 7), and an interface that is not observed is an interface nothing can be
// asserted about: "the word pushed at 0x00c71e58 is THIS call's argument, and
// the receiver of that call is the PREVIOUS call's result" would otherwise be a
// claim about a comment rather than about the code. So the modelled lookup
// records both of its inputs here, and the model test reads them back.
struct LookupObservation {
  const EmpireIndex* receiver;  // the ECX the modelled lookup was given
  std::uint32_t argument;       // the word pushed at 0x00c71e58
  std::uint32_t call_count;     // how many times it was entered
};

extern LookupObservation g_lookup_observation;

// The modelled interface of 0x00b3d2a0: NO receiver and NO argument, because
// its body is `MOV EAX,[absolute] / RET` - a bare RET that pops nothing. It is
// spelled with no parameter on purpose (note 7).
using AbiGlobalSlot00b3d2a0 = SlotWord(PKG_00C71E30_THISCALL*)();

// The modelled interface of 0x00ba9370: a receiver in ECX AND one ordinary
// stack argument, which its `RET 0x4` pops. On i386 `__thiscall` with a stack
// parameter emits exactly that, which is why this is spelled as a parameter
// rather than as a hand-rolled frame: the cleanup becomes real and measurable
// instead of asserted.
using AbiLookup00ba9370 = SlotWord(PKG_00C71E30_THISCALL*)(
    EmpireIndex*, std::uint32_t);

// ---------------------------------------------------------------------------
// Layout facts.
// ---------------------------------------------------------------------------

static_assert(sizeof(void*) == 4, "x86-32 target pointers are 32-bit");
static_assert(sizeof(SlotWord) == 4, "the dword both arms produce is 32-bit");
static_assert(sizeof(SlotFunction) == 4, "a slot is one 32-bit function pointer");
static_assert(sizeof(DispatchTable) == 0x64,
              "nine function pointers, +0x40 through +0x60");

static_assert(sizeof(OpaqueReceiver) == 0x140,
              "the modelled receiver runs through the word at +0x13c");
static_assert(kDelegatedDisplacement + sizeof(SlotWord) ==
                  sizeof(OpaqueReceiver),
              "the furthest displacement this body reaches ends the extent");
static_assert(kDispatchedDisplacement + sizeof(void*) < kDelegatedDisplacement,
              "the dispatched object at +0xd4 is reached BEFORE the word at "
              "+0x13c, so the two cannot be one field");

static_assert(sizeof(DelegatedReceiver) == 0x198,
              "the delegated extent runs through the word 0x00b8dab0 reads");
static_assert(kDelegatedTargetDisplacement + sizeof(SlotWord) ==
                  sizeof(DelegatedReceiver),
              "0x194 ends the DELEGATED object's extent, not the receiver's");
static_assert(kDelegatedTargetDisplacement > sizeof(OpaqueReceiver),
              "0x194 is past this body's own receiver: the delegated object is "
              "strictly the larger of the two and cannot be the receiver");
static_assert(kDelegatedTargetDisplacement != kDelegatedDisplacement,
              "0x13c and 0x194 are displacements of DIFFERENT objects");

static_assert(sizeof(DispatchedObject) == sizeof(void*),
              "this body reads exactly one word of the dispatched object");
static_assert(offsetof(DispatchedObject, table) == 0,
              "the table word is the object's FIRST word - displacement zero");

// The table's layout, so the 0x4c slot is a slot and not a coincidence.
static_assert(offsetof(DispatchTable, decoy_40) == 0x40, "decoy at +0x40");
static_assert(offsetof(DispatchTable, decoy_44) == 0x44, "decoy at +0x44");
static_assert(offsetof(DispatchTable, decoy_48) == 0x48, "decoy at +0x48");
static_assert(offsetof(DispatchTable, slot_4c) == 0x4c,
              "THE slot 0x00c71e4d reads is at table+0x4c");
static_assert(offsetof(DispatchTable, slot_4c) == kSlotDisplacement,
              "the named slot and the observed displacement are one address");
static_assert(offsetof(DispatchTable, decoy_50) == 0x50, "decoy at +0x50");
static_assert(offsetof(DispatchTable, decoy_54) == 0x54, "decoy at +0x54");
static_assert(offsetof(DispatchTable, decoy_58) == 0x58, "decoy at +0x58");
static_assert(offsetof(DispatchTable, decoy_5c) == 0x5c, "decoy at +0x5c");
static_assert(offsetof(DispatchTable, sentinel) == 0x60,
              "the sentinel sits IMMEDIATELY past the last modelled slot, so a "
              "one-slot-too-far dispatch is a trap and not a valid neighbour");
static_assert((kSlotDisplacement % sizeof(SlotFunction)) == 0,
              "a slot displacement on a dword table is 4-byte aligned");
static_assert(kSlotIndex == 19u, "0x4c is nineteen four-byte slots along");
static_assert(kSlotIndex >= 1u,
              "the slot is not slot zero, so a base-relative mix-up is possible "
              "and the fixture has to be able to catch it");
static_assert(kSlotDisplacement + sizeof(SlotFunction) <=
                  offsetof(DispatchTable, sentinel),
              "the observed slot lies inside the modelled table and never on "
              "the sentinel");

// The decoys are contiguous, so an off-by-one in EITHER direction is caught.
static_assert(offsetof(DispatchTable, decoy_40) + sizeof(SlotFunction) ==
                  offsetof(DispatchTable, decoy_44),
              "the modelled slots are contiguous downwards from +0x44");
static_assert(offsetof(DispatchTable, decoy_5c) + sizeof(SlotFunction) ==
                  offsetof(DispatchTable, sentinel),
              "the modelled slots are contiguous upwards into the sentinel");

// The displacements are byte offsets.
static_assert(kDelegatedDisplacement == 0x13cu, "the displacement is 0x13c");
static_assert(kDelegatedDisplacement == 316u, "0x13c is the value 316");
static_assert((kDelegatedDisplacement * sizeof(SlotWord)) >
                  sizeof(OpaqueReceiver),
              "reading the disp32 as an element count would address byte 0x4f0, "
              "past the modelled receiver");
static_assert(kDispatchedDisplacement == 0xd4u, "the displacement is 0xd4");
static_assert(kDispatchedDisplacement == 212u, "0xd4 is the value 212");
static_assert(kDelegatedIndexInWords == 79u,
              "0x13c is 79 four-byte words past the base");
static_assert(kDispatchedIndexInWords == 53u,
              "0xd4 is 53 four-byte words past the base");
static_assert(kDispatchedDisplacement != kDelegatedDisplacement,
              "0xd4 and 0x13c are two different words of the receiver");

// The modelled dispatch callee shape and the modelled entry carry the same
// interface, which is the one 0x00c71e4d/0x00c71e50/0x00c71e56 state.
static_assert(std::is_same<DispatchedCalleeShape, SlotFunction>::value,
              "the dispatched callee and the slot type are one interface");

// ---------------------------------------------------------------------------
// Encoding facts.
// ---------------------------------------------------------------------------

// The three reaches this body makes, decoded.
static_assert(kTargetEncoding[0] == 86u, "0x00c71e30 is PUSH ESI");
static_assert(kTargetEncoding[0] == 0x56u, "0x56 is the PUSH r32 opcode, EAX+r");
static_assert(kTargetEncoding[0] != 94u,
              "0x5e is POP ESI; the prologue's byte must be the PUSH");

static_assert(kTargetEncoding[1] == 139u && kTargetEncoding[2] == 241u,
              "0x00c71e31 is MOV ESI,ECX");
static_assert(kTargetEncoding[1] == 0x8bu, "0x8b is MOV r32, r/m32");
static_assert(kTargetEncoding[1] != 141u,
              "0x8d is LEA; the alias copy must be a MOVE");
static_assert((kTargetEncoding[2] >> 6) == 3u, "mod=11 is register-direct");
static_assert(((kTargetEncoding[2] >> 3) & 7u) == 6u, "reg=110 selects ESI");
static_assert((kTargetEncoding[2] & 7u) == 1u, "rm=001 selects ECX");

static_assert(kTargetEncoding[3] == 139u && kTargetEncoding[4] == 142u,
              "0x00c71e33 is a MOV with a disp32");
static_assert(kTargetEncoding[5] == 60u,
              "the low disp32 byte is 0x3c, so the displacement is 0x13c");
static_assert((kTargetEncoding[4] >> 6) == 2u, "mod=10 selects a disp32");
static_assert(((kTargetEncoding[4] >> 3) & 7u) == 1u, "reg=001 selects ECX");
static_assert((kTargetEncoding[4] & 7u) == 6u,
              "rm=110 selects ESI, so base and destination differ and the load "
              "is NOT in place - the word lands in a different register");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[5]) |
               (static_cast<std::uint32_t>(kTargetEncoding[6]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[7]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[8]) << 24)) ==
                  kDelegatedDisplacement,
              "the instruction's disp32 IS the header's kDelegatedDisplacement");

static_assert(kTargetEncoding[9] == 133u && kTargetEncoding[10] == 201u,
              "0x00c71e39 is TEST ECX,ECX");
static_assert(kTargetEncoding[10] == 0xc9u,
              "TEST's ModRM is reg=ECX rm=ECX, so the FLAGS come from the "
              "LOADED word at +0x13c, not from the incoming receiver");
static_assert(kTargetEncoding[11] == 116u, "0x00c71e3b is JZ rel8");
static_assert(static_cast<std::int8_t>(kTargetEncoding[12]) ==
                  kJzDisplacement,
              "the JZ rel8 is the +42 the listing carries");

static_assert(kTargetEncoding[13] == 232u, "0x00c71e3d is CALL rel32");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[14]) |
               (static_cast<std::uint32_t>(kTargetEncoding[15]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[16]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[17]) << 24)) ==
                  kDelegateCallEncodedDisplacement,
              "the delegation's rel32 is the encoded pattern the listing "
              "carries, and it resolves to 0x00b8dab0");

static_assert(kTargetEncoding[18] == 131u && kTargetEncoding[19] == 248u &&
                  kTargetEncoding[20] == 5u,
              "0x00c71e42 is CMP EAX,imm8");
static_assert(kTargetEncoding[18] == 0x83u,
              "0x83 sign-extends its imm8 to 32 bits; 0x3d would be imm32 and "
              "0x80 would be a byte-wide compare");
static_assert(kTargetEncoding[18] != 0x3du,
              "3d is CMP EAX,imm32 - a different opcode, not a narrower "
              "comparison");
static_assert(kTargetEncoding[20] == static_cast<std::uint8_t>(
                                         kRequiredDelegatedScalar),
              "the compared immediate is the constant the header declares");
static_assert(kTargetEncoding[21] == 117u, "0x00c71e45 is JNZ rel8");
static_assert(static_cast<std::int8_t>(kTargetEncoding[22]) ==
                  kJnzDisplacement,
              "the JNZ rel8 is the +32 the listing carries");

static_assert(kTargetEncoding[23] == 139u && kTargetEncoding[24] == 134u,
              "0x00c71e47 is a MOV with a disp32");
static_assert(kTargetEncoding[23] == 0x8bu,
              "0x00c71e47 is a LOAD of the table word");
static_assert(kTargetEncoding[24] != 141u,
              "0x8d is LEA; the table word is loaded, not addressed - and the "
              "very same displacement IS addressed by LEA three instructions "
              "later, so the two opcodes are the distinction");
static_assert(((kTargetEncoding[24] >> 3) & 7u) == 0u, "reg=000 selects EAX");
static_assert((kTargetEncoding[24] & 7u) == 6u, "rm=110 selects ESI");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[25]) |
               (static_cast<std::uint32_t>(kTargetEncoding[26]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[27]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[28]) << 24)) ==
                  kDispatchedDisplacement,
              "the disp32 IS the header's kDispatchedDisplacement");

static_assert(kTargetEncoding[29] == 139u && kTargetEncoding[30] == 80u &&
                  kTargetEncoding[31] == 76u,
              "0x00c71e4d is MOV EDX,[EAX+0x4c]");
static_assert((kTargetEncoding[30] >> 6) == 1u,
              "mod=01 selects a disp8, and 0x00c71e4d really is three bytes");
static_assert(((kTargetEncoding[30] >> 3) & 7u) == 2u, "reg=010 selects EDX");
static_assert((kTargetEncoding[30] & 7u) == 0u, "rm=000 selects EAX");
static_assert(kTargetEncoding[31] == static_cast<std::uint8_t>(
                                         kSlotDisplacement),
              "the disp8 IS the header's kSlotDisplacement, so the slot name "
              "and the machine's byte cannot drift apart");

static_assert(kTargetEncoding[32] == 141u && kTargetEncoding[33] == 142u,
              "0x00c71e50 is LEA ECX,[ESI+0xd4]");
static_assert(kTargetEncoding[32] == 0x8du,
              "0x00c71e50 is the LEA - the ADDRESS of receiver+0xd4 is the "
              "dispatch's receiver, not the word stored there");
static_assert(kTargetEncoding[32] != 139u,
              "0x8b here would make the callee's receiver the STORED word, "
              "which is the opposite of what the machine does");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[34]) |
               (static_cast<std::uint32_t>(kTargetEncoding[35]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[36]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[37]) << 24)) ==
                  kDispatchedDisplacement,
              "the LEA and the earlier MOV name the SAME displacement, which "
              "is what makes the load/address distinction decidable here");

static_assert(kTargetEncoding[38] == 255u && kTargetEncoding[39] == 210u,
              "0x00c71e56 is CALL EDX");
static_assert(kTargetEncoding[38] == 0xffu,
              "0xff /2 is the register-indirect CALL group");
static_assert((kTargetEncoding[39] >> 6) == 3u,
              "mod=11 means a REGISTER target, so there is no displacement "
              "operand to confuse with the slot");
static_assert((kTargetEncoding[39] & 7u) == 2u, "rm=010 selects EDX");
static_assert((kTargetEncoding[39] >> 3) & 7u,
              "reg=010 selects the CALL /2 form");

static_assert(kTargetEncoding[40] == 80u, "0x00c71e58 is PUSH EAX");
static_assert(kTargetEncoding[40] == 0x50u,
              "0x50 is PUSH EAX; 0x8b would be a MOV and 0xff a CALL");

static_assert(kTargetEncoding[41] == 232u, "0x00c71e59 is CALL rel32");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[42]) |
               (static_cast<std::uint32_t>(kTargetEncoding[43]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[44]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[45]) << 24)) ==
                  kGlobalSlotCallEncodedDisplacement,
              "the second CALL's rel32 is the encoded pattern the listing "
              "carries, and it resolves to 0x00b3d2a0");

static_assert(kTargetEncoding[46] == 139u && kTargetEncoding[47] == 200u,
              "0x00c71e5e is MOV ECX,EAX");
static_assert(((kTargetEncoding[47] >> 3) & 7u) == 1u,
              "reg=001 selects ECX: the last call's receiver is OVERWRITTEN "
              "with the previous call's result, so ECX does not survive");
static_assert((kTargetEncoding[47] & 7u) == 0u, "rm=000 selects EAX");

static_assert(kTargetEncoding[48] == 232u, "0x00c71e60 is CALL rel32");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[49]) |
               (static_cast<std::uint32_t>(kTargetEncoding[50]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[51]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[52]) << 24)) ==
                  kLookupCallEncodedDisplacement,
              "the third CALL's rel32 is the encoded pattern the listing "
              "carries, and it resolves to 0x00ba9370");

static_assert(kTargetEncoding[53] == 94u, "0x00c71e65 is POP ESI");
static_assert(kTargetEncoding[53] == 0x5eu,
              "0x5e is POP ESI - it restores the CALLER's ESI saved at "
              "0x00c71e30, and it does not reach the word pushed at 0x00c71e58");
static_assert(kTargetEncoding[54] == 195u, "0x00c71e66 is RET");
static_assert(kTargetEncoding[54] == 0xc3u,
              "a bare RET carries no imm16, so the entry pops nothing");

static_assert(kTargetEncoding[55] == 51u && kTargetEncoding[56] == 192u,
              "0x00c71e67 is XOR EAX,EAX");
static_assert(kTargetEncoding[55] == 0x33u,
              "0x33 is the XOR r/m32,r32 form: ALL THIRTY-TWO bits of EAX are "
              "written on the null arm");
static_assert(kTargetEncoding[56] == 0xc0u,
              "ModRM 0xc0 is mod=11 reg=000 rm=000 - EAX both sides, so the "
              "zero is written in full and no byte of the return is unproven");
static_assert(kTargetEncoding[56] != 0xc8u,
              "0x33 0xc8 would be XOR EAX,ECX and would leave EAX's value "
              "depending on ECX - not the machine's instruction");

static_assert(kTargetEncoding[57] == 94u, "0x00c71e69 is POP ESI");
static_assert(kTargetEncoding[58] == 195u, "0x00c71e6a is RET");
static_assert(kTargetEncoding[58] == 0xc3u,
              "the second exit is a bare RET too, so both exits pop nothing");
static_assert(sizeof(kTargetEncoding) == kTargetBodyBytes,
              "the encoding array is exactly the modelled body length");
static_assert(kTargetBodyBytes == 1u + 2u + 6u + 2u + 2u + 5u + 3u + 2u + 6u +
                               3u + 6u + 2u + 1u + 5u + 2u + 5u + 1u + 1u + 2u +
                               1u + 1u,
              "the body is twenty-one instructions whose lengths sum to fifty-"
              "nine");
static_assert(kTargetPadByte == 0xccu, "0x00c71e6b is INT3 pad, not body");
static_assert(kTargetPadBytes == 5u,
              "five pad bytes were read live between the body and the next "
              "entry");

// The branch arithmetic, recomputed from the ENCODED operands. A wrong rel8
// cannot pass, and both branches are shown to land on the same address - which
// is why this body has two returns and not three.
constexpr std::uint32_t kJzSiteAddress = 0x00c71e3b;
constexpr std::uint32_t kJnzSiteAddress = 0x00c71e45;
constexpr std::uint32_t kJzInstructionBytes = 2;
constexpr std::uint32_t kJnzInstructionBytes = 2;
constexpr std::uint32_t kComputedNullArm =
    kJzSiteAddress + kJzInstructionBytes +
    static_cast<std::uint32_t>(kJzDisplacement);
constexpr std::uint32_t kComputedNullArmSecond =
    kJnzSiteAddress + kJnzInstructionBytes +
    static_cast<std::uint32_t>(kJnzDisplacement);
static_assert(kComputedNullArm == kNullArmAddress,
              "0x00c71e3b + 2 + 42 is 0x00c71e67, the JZ's own operand");
static_assert(kComputedNullArmSecond == kNullArmAddress,
              "0x00c71e45 + 2 + 32 is ALSO 0x00c71e67, so both guards share one "
              "null arm and there are exactly two returns");
static_assert(kComputedNullArm == kComputedNullArmSecond,
              "the two branches converge, so a model that treated them as "
              "separate arms would be modelling a body that does not exist");
static_assert(kNullArmAddress - kEntryAddress == 55u,
              "the null arm sits 55 bytes in, and the zeroing instruction plus "
              "its POP and RET are the last six bytes of the body");
static_assert(kNullArmAddress + 4u == kEntryAddress + kTargetBodyBytes,
              "XOR EAX,EAX ; POP ESI ; RET are the final four bytes, so the "
              "null arm is a leaf of the body and reaches nothing further");

// The CALL arithmetic, recomputed the same way. A rel32 is a SIGNED
// displacement; each stored pattern has its sign bit set, so the sign extension
// is the identity in 32-bit unsigned arithmetic and the two constants compare
// equal - stated so the addition below cannot be read as an unsigned add.
constexpr std::uint32_t kDelegateCallSiteAddress = 0x00c71e3d;
constexpr std::uint32_t kGlobalSlotCallSiteAddress = 0x00c71e59;
constexpr std::uint32_t kLookupCallSiteAddress = 0x00c71e60;
constexpr std::uint32_t kCallInstructionBytes = 5;

constexpr std::uint32_t kSignExtend(std::uint32_t pattern) {
  return (pattern ^ 0x80000000u) - 0x80000000u;
}
static_assert(kSignExtend(kDelegateCallEncodedDisplacement) ==
                  kDelegateCallEncodedDisplacement,
              "the delegation's stored rel32 has its sign bit set");
static_assert(kSignExtend(kGlobalSlotCallEncodedDisplacement) ==
                  kGlobalSlotCallEncodedDisplacement,
              "the global-slot call's stored rel32 has its sign bit set");
static_assert(kSignExtend(kLookupCallEncodedDisplacement) ==
                  kLookupCallEncodedDisplacement,
              "the lookup call's stored rel32 has its sign bit set");

static_assert(kDelegateCallSiteAddress + kCallInstructionBytes +
                      kSignExtend(kDelegateCallEncodedDisplacement) ==
                  kDelegateTargetVa,
              "0x00c71e3d + 5 + rel32 is 0x00b8dab0, the xref export's second "
              "out-edge and the promoted sibling package's address");
static_assert(kGlobalSlotCallSiteAddress + kCallInstructionBytes +
                      kSignExtend(kGlobalSlotCallEncodedDisplacement) ==
                  kGlobalSlotTargetVa,
              "0x00c71e59 + 5 + rel32 is 0x00b3d2a0");
static_assert(kLookupCallSiteAddress + kCallInstructionBytes +
                      kSignExtend(kLookupCallEncodedDisplacement) ==
                  kLookupTargetVa,
              "0x00c71e60 + 5 + rel32 is 0x00ba9370");

// The three targets are three DIFFERENT addresses, and the two direct calls that
// follow the guard are distinct, so swapping them cannot be equivalent.
static_assert(kDelegateTargetVa != kGlobalSlotTargetVa &&
                  kDelegateTargetVa != kLookupTargetVa &&
                  kGlobalSlotTargetVa != kLookupTargetVa,
              "the three callees are three distinct addresses");
static_assert(kDelegateTargetVa == 0x00b8dab0u, "the delegation target");
static_assert(kGlobalSlotTargetVa == 0x00b3d2a0u, "the global-slot target");
static_assert(kLookupTargetVa == 0x00ba9370u, "the lookup target");
static_assert(kRecordedOutgoingDirectCallEdges == 3u,
              "the export records exactly three direct call edges out");
static_assert(kRecordedIncomingDirectCallEdges == 40u,
              "the export records forty rows into this VA");

// The delegation target's own seven bytes, so the hand-over is checked against
// the image and not against a name.
static_assert(kDelegateTargetEncoding[0] == 139u,
              "0x00b8dab0 is MOV r32, r/m32");
static_assert(kDelegateTargetEncoding[0] != 141u,
              "0x8d is LEA; the delegated object's word is LOADED, so the value "
              "0x00c71e42 compares is a stored word and not an address");
static_assert((kDelegateTargetEncoding[1] >> 6) == 2u,
              "ModRM 0x81 is mod=10 (disp32)");
static_assert(((kDelegateTargetEncoding[1] >> 3) & 7u) == 0u,
              "reg=000 selects EAX");
static_assert((kDelegateTargetEncoding[1] & 7u) == 1u,
              "rm=001 selects ECX, so the target reads through the register "
              "this body left holding the word it loaded from +0x13c");
static_assert((static_cast<std::uint32_t>(kDelegateTargetEncoding[2]) |
               (static_cast<std::uint32_t>(kDelegateTargetEncoding[3]) << 8) |
               (static_cast<std::uint32_t>(kDelegateTargetEncoding[4]) << 16) |
               (static_cast<std::uint32_t>(kDelegateTargetEncoding[5]) << 24)) ==
                  kDelegatedTargetDisplacement,
              "the delegation target's disp32 is 0x194");
static_assert(kDelegateTargetEncoding[6] == 195u,
              "0x00b8dab6 is a bare RET: it writes no register other than EAX "
              "and names none, so ESI survives the call and the receiver can "
              "still be read at 0x00c71e47");
static_assert(kDelegateTargetEncoding[6] != 194u,
              "0xc2 would be RET imm16; this one pops nothing");

// 0x00b3d2a0's two instructions, so the "consumes nothing" claim rests on bytes.
static_assert(kGlobalSlotTargetEncoding[0] == 161u,
              "0x00b3d2a0 is MOV EAX,moffs32");
static_assert(kGlobalSlotTargetEncoding[0] == 0xa1u,
              "0xa1 is the moffs32 form: a 32-bit absolute address and NO ModRM "
              "byte at all, so there is no register field a receiver could have "
              "arrived in and none a stack argument could be read through");
static_assert(kGlobalSlotTargetEncoding[0] != 139u,
              "0x8b would be MOV r32,r/m32 and WOULD carry a ModRM byte, which "
              "is not what 0x00b3d2a0 is");
static_assert(sizeof(kGlobalSlotTargetEncoding) == 6u,
              "five bytes of MOV EAX,moffs32 plus one byte of RET");
static_assert(kGlobalSlotTargetEncoding[5] == 195u,
              "0x00b3d2a5 is the bare 0xc3, so it pops NO argument and the word "
              "pushed at 0x00c71e58 survives it untouched");
static_assert(kGlobalSlotTargetEncoding[5] != 194u,
              "0xc2 would carry an imm16 and the pushed word would be consumed "
              "here instead of by 0x00ba9370");

// 0x00ba9370's cleanup, and the contrast that carries the whole of note 7.
static_assert(kLookupCleanupBytes == 4u,
              "0x00ba9370's two exits are both `RET 0x4`, so the CALLEE pops "
              "the word this body pushed at 0x00c71e58");
static_assert(kLookupCleanupBytes != kEntryCleanupBytes,
              "the callee's four bytes of cleanup and the entry's zero are "
              "different facts, so 'the callee pops the pushed word' and 'this "
              "body pops it with POP ESI' cannot both be true");
static_assert(kEntryCleanupBytes == 0u,
              "this body's own cleanup is zero: two bare RETs and no stack "
              "argument, so the caller owns cleanup");

// The record's own words (note 12).
static_assert(kAbiSavedRegisterCount == 1u &&
                  sizeof("ESI") - 1u == kAbiSavedRegisterCount + 2u,
              "the record names exactly one saved register, ESI, which is the "
              "register this body writes and restores");
static_assert(kMachineIndirectCallCount == 1u,
              "the record counts exactly one indirect call, the CALL EDX at "
              "0x00c71e56");
static_assert(kMachineVtableShapedLoadCount == 0u,
              "the record's vtable-shaped load count is ZERO beside that one "
              "indirect call; the disagreement is pinned, not reconciled, and "
              "nothing in this package depends on that count");
static_assert(kAbiCandidateConventionCount == 2u,
              "the record lists TWO candidate conventions for a body of one "
              "register argument and zero stack arguments - which is the "
              "acknowledgement that the bytes choose between neither");

static_assert(std::is_same<AbiEmpire5_00c71e30,
                           SlotWord(PKG_00C71E30_THISCALL*)(
                               OpaqueReceiver*)>::value,
              "the modelled entry carries the ECX receiver, no stack argument, "
              "and returns one dword");
static_assert(sizeof(AbiEmpire5_00c71e30) == sizeof(void*),
              "the modelled entry is a plain code pointer");
static_assert(std::is_same<AbiGlobalSlot00b3d2a0,
                           SlotWord(PKG_00C71E30_THISCALL*)()>::value,
              "0x00b3d2a0 takes NO receiver and NO argument - the bare RET is "
              "the reason");
static_assert(std::is_same<AbiLookup00ba9370,
                           SlotWord(PKG_00C71E30_THISCALL*)(
                               EmpireIndex*, std::uint32_t)>::value,
              "0x00ba9370 takes a receiver in ECX AND one stack argument, which "
              "its `RET 0x4` pops");

// ---------------------------------------------------------------------------
// The modelled mechanisms of the three callees, and the entry.
// ---------------------------------------------------------------------------

// 0x00b8dab0 - the promotion target of the hand-over at 0x00c71e3d. A LOCAL
// model of that target's MECHANISM (one 32-bit load at displacement 0x194, one
// return), reproduced so that the receiver this entry hands over is observable
// and can be asserted. It is not a second reconstruction of 0x00b8dab0: the
// promoted package `pkg-00b8dab0-field194-getter` is the record of that
// address and is not restated here (note 4).
SlotWord PKG_00C71E30_THISCALL helper_00b8dab0(DelegatedReceiver* receiver);

// 0x00b3d2a0 - modelled for its INTERFACE only, which is what this body's
// stack behaviour turns on (note 7). The real body is
// `MOV EAX,dword ptr [0x0167eae4]` / `RET`: it takes no receiver and no
// argument and pops nothing. Its data address belongs to that function and is
// named nowhere here, so what it actually reads is NOT modelled and NOT
// claimed; the model test drives this function's result from a planted value,
// which is how the entry's argument routing is made observable.
SlotWord PKG_00C71E30_THISCALL helper_00b3d2a0();

// 0x00ba9370 `Simulator_LookupEmpireByPoliticalId` - likewise modelled for its
// interface: a receiver in ECX and ONE ordinary stack argument, which its
// `RET 0x4` pops. Spelling the argument as a parameter makes that cleanup REAL
// on i386 rather than asserted, so the model test can measure the stack rather
// than believe a comment. Its internals - the container walk over +0x14, +0x150
// and +0x154 - are observed and deliberately not modelled.
SlotWord PKG_00C71E30_THISCALL lookup_empire_00ba9370(EmpireIndex* receiver,
                                                     std::uint32_t political_id);

// Entry point under reconstruction. The name embeds the 8-hex target VA so the
// validator can bind this span to 0x00c71e30.
SlotWord PKG_00C71E30_THISCALL empire5_00c71e30(OpaqueReceiver* receiver);

}

#undef PKG_00C71E30_THISCALL