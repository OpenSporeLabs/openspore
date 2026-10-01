# Validation 0x00b3d290

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b06/b3d290_global_slot_accessor.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 2-instruction listing names 1 data address(es) (0x167ead4) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a5662fa2b6b17ac1ea7fe18893d0c1ab6e2ee11dcde5114a393c27047c9dbd07`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d6db0acb8c0c909ea0ea66f3984d1595372aafc4c65ce7fd26134247726c0a33`
- Pack digest quoted by the briefing: `a5662fa2b6b17ac1ea7fe18893d0c1ab6e2ee11dcde5114a393c27047c9dbd07`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test would have to establish (a) that 0x0167EAD4 is non-zero once the owning subsystem is up, and (b) the concrete type of the pointee, which is the withheld claim.`, `Because the slot has no static writer, static analysis alone cannot enumerate the set of objects that can land there; a runtime write watchpoint on 0x0167EAD4 is the only way to close this.`, `No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test would have to establish (a) that 0x0167EAD4 is non-zero once the owning subsystem is up, and (b) the concrete type of the pointee, which is the withheld claim.
- Because the slot has no static writer, static analysis alone cannot enumerate the set of objects that can land there; a runtime write watchpoint on 0x0167EAD4 is the only way to close this.
- CONFLICT, recorded and NOT adopted: Spore-ModAPI 'Spore ModAPI/Spore/Simulator/SubSystem/GamePersistenceManager.h:65' declares `DeclareAddress(Get);  // 0xB3D2A0 0xB3D440`, and 0x00b3d290 falls inside that range. The attribution is not adopted because 0x00b3d2a0, the range's stated entry point, demonstrably returns an object read at +0x184 (ordered map header, 0x00bb99fc) and at +0x1F4 (lazily resolved pointer slot, 0x00c4b221), while the same header asserts ASSERT_SIZE(cGamePersistenceManager, 0x4C). The SDK's address range therefore covers a cluster of unrelated Simulator singleton accessors, and only 0x00b3d2a0 is claimed by name. Adopting cGamePersistenceManager for 0x00b3d290 would contradict an observed field offset.
- Is 0x0167EAD4 the same type as the neighbouring slot 0x0167EAD8 (read by 0x00b3d260, whose pointee is dereferenced through vtable slot +0x30 at 0x00b32ad0)? The two accessors are adjacent but nothing observed relates the two pointees.
- No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.
- The briefing's canonical ledger recorded caller_count 32; the live xref query finds 37 call sites across 33 distinct caller functions, because several callers call it more than once. The fan-in figure is not a contradiction, only a different counting convention.
- What object does 0x0167EAD4 point to at runtime? No vtable was located for it and no instruction in the binary names it. This is the material bound on this record.
- Which runtime code writes 0x0167EAD4? There is no static writer and no DATA xref, so the writer is reached through a pointer, a registration table, or a runtime patch that Ghidra cannot attribute.
