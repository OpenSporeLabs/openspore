# Validation 0x00688fa0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b02/b688fa0_gge_user_data_reset.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 203-instruction listing names 1 data address(es) (0x13f09b4) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (203 of 203 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 13 conditional branch target(s) in the complete 203-instruction listing lie inside the recovered body span 0x00688fa0..0x006891e5, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 203-instruction body names 6 indirect transfer(s): 0x00688ff0 dispatches slot 0x28 through the table word in EDX; 0x00689103 dispatches slot 0x0 through the table word in EDX; 0x00689148 dispatches slot 0x4 through the table word in EDX; 0x00689152 dispatches slot 0x2c through the table word in EDX; 0x0068915e dispatches slot 0x3c through the table word in EDX; 0x00689176 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 203 of 203 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 6. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 2 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b5b2b0a7a5cf277b13ef05c2333f66d04a717704400e55b5973a9f149411112b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3ab20653bec6f3a06b427c6197b7916f8d07d3c4f20e82c8109d7e43cf7c4840`
- Pack digest quoted by the briefing: `b5b2b0a7a5cf277b13ef05c2333f66d04a717704400e55b5973a9f149411112b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace is required to confirm the delete actually targets a removable file, since the predicate that would guard it is discarded.`, `A runtime trace is required to observe what the service locator returns for the key 0x04729a47 and therefore what base directory is actually used.`, `A runtime trace is required to resolve the four unknown virtual callees and the identity of the Simulator class at runtime.`, `No original-process trace has ever been captured for 0x00688fa0; every claim here is static. The original Cell stage has never been entered in any recorded run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace is required to confirm the delete actually targets a removable file, since the predicate that would guard it is discarded.
- A runtime trace is required to observe what the service locator returns for the key 0x04729a47 and therefore what base directory is actually used.
- A runtime trace is required to resolve the four unknown virtual callees and the identity of the Simulator class at runtime.
- No original-process trace has ever been captured for 0x00688fa0; every claim here is static. The original Cell stage has never been entered in any recorded run.
- Three of the four callers were not disassembled, so their argument provenance is unverified.
- What are the 0x68-byte App object and its derived 8-byte sub-object created inside 0x0069fa60, and what stores them at small+0x1c?
- What are the four unresolved virtual callees at 0x01408698 slots +0x04 and +0x2c, and at PTR_FUN_0143679c slots +0x00 and +0x04?
- What class is registered under the name Simulator? The registry is only reachable through 0x00926020 and no SDK type matches either object.
- What does 0x0069df20, the one resolved virtual callee at slot +0x3c, do with the arguments 0 and 1?
- What does the concatenated path (base ++ name) get used for? It is built, compared against the output header, freed, and never passed to a syscall at this level.
- What is 0x00932960, the fallback of the directory predicate?
- Which of the four intermediate string headers does each of the four length-guarded frees target? The ESP-relative slots shift by four between each guard and its free.
- Why is the directory test's result discarded?
