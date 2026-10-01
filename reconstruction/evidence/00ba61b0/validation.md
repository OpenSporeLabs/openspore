# Validation 0x00ba61b0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 44-instruction listing names 1 data address(es) (0x1465ef0) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (44 of 44 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 44-instruction listing lie inside the recovered body span 0x00ba61b0..0x00ba6223, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 44-instruction body names 1 indirect transfer(s): 0x00ba620a dispatches slot 0x0 through the table word in EAX; the machine parse consumed 44 of 44 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c930089bb23ec2b3c144e6fdd418597b186b505a24c31f2fe5b14110aad26468`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b7fb11b16eb4ff0987028027fea1758f7808d65c7ef565a805fad6671c40d22d`
- Pack digest quoted by the briefing: `c930089bb23ec2b3c144e6fdd418597b186b505a24c31f2fe5b14110aad26468`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists. A differential run must confirm the allocation size 0x1B0, the type name and the three header writes in the shipping build.`, `The 0x5220CB8 constant can only be attributed by observing what reads +0x0C on a constructed record at runtime.`, `The concrete callee behind vtable slot +0x00 can only be fixed by dumping the vtable pointer of a constructed record.`, `The crash-on-allocation-failure path can only be confirmed as intentional or as a latent defect by forcing an allocation failure in a controlled run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process trace exists. A differential run must confirm the allocation size 0x1B0, the type name and the three header writes in the shipping build.
- The 0x5220CB8 constant can only be attributed by observing what reads +0x0C on a constructed record at runtime.
- The concrete callee behind vtable slot +0x00 can only be fixed by dumping the vtable pointer of a constructed record.
- The crash-on-allocation-failure path can only be confirmed as intentional or as a latent defect by forcing an allocation failure in a controlled run.
- What do 0x006AC040(record, 1) and 0x006AD010(record) do? Both are engine-boundary calls, 82 and 28 instructions, neither characterised.
- What does the 459-byte constructor 0x00B8E180 initialise? It was located and its ret form read, but its body was not reconstructed, so no field claim is made beyond the first dword being the vtable pointer.
- What is 0x01465EF0? It is the type descriptor passed to the allocator. The decompiler renders the allocator's second argument as the literal "Simulator/cPlanetRecord" and the corresponding bytes are present in .rdata, but this worker did not follow the pointer 0x01465EF0 to its target, so the association is strong rather than byte-traced end to end.
- What is 0x5220CB8? It is read as an immediate at 0x00ba61f4 and stored at +0x0C. No name, type, key or hash is claimed for it.
- What is at +0x10, set to 1? A count, a flag, a reference count and a version are all consistent with the single observed write.
- What is the calling convention of the six callers' own sites? None of the six callers was disassembled, so the argument order at each callsite is unverified even though the callee's own reads fix it.
- Which class does vtable slot +0x00 belong to? The table address is written by the constructor 0x00B8E180, whose body was not reconstructed, so the concrete callee is unresolved.
