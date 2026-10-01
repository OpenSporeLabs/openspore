# Validation 0x007f8d10

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 158-instruction listing names 2 data address(es) (0x013f63fc, 0x013f6400); the data-reference artifact is read whole and records 0 reference row(s) out of this body, none of which is 2 of the address(es) under review (0x013f63fc, 0x013f6400), so those claims are unbacked by Ghidra's reference database rather than refuted by it |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (158 of 158 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 15 conditional branch target(s) in the complete 158-instruction listing lie inside the recovered body span 0x007f8d10..0x007f8ef0, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 158-instruction body names 6 indirect transfer(s): 0x007f8e35 dispatches slot 0xc through the table word in EBP; 0x007f8e72 dispatches slot 0x4 through the table word in EAX; 0x007f8e81 dispatches slot 0x4 through the table word in EAX; 0x007f8e98 dispatches slot 0x0 through the table word in EAX; 0x007f8ea7 dispatches slot 0x4 through the table word in EAX; 0x007f8ed9 is FUNCTION_POINTER; the machine parse consumed 158 of 158 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 6, so the dispatch is visible in the machine listing but is not proven: 1 of the 6 indirect transfer(s) classify as FUNCTION_POINTER (0x007f8ed9), so the dispatch's identity is not established: EDX is loaded from [EDI + 0xc], but EDI is defined by an immediate or register assignment, not a memory load earlier in the listing, so the word it names is not shown to be a table word |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 2 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e4f60f9a3a339509ef24bf7375e12b3339a0c855eaa2dcf52e11d5546f78d680`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `1784a35e0e6ec095fd453b3daa9636b79ecbe773a2e2456830cb132f35834c67`
- Pack digest quoted by the briefing: `e4f60f9a3a339509ef24bf7375e12b3339a0c855eaa2dcf52e11d5546f78d680`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x007f8e0c (`CMP ECX,EBX` on the old end pointer) is only reachable when end is a null pointer with capacity still ahead. For a self-consistent container that cannot happen: end == 0 forces begin == 0, which forces capacity == 0, which routes to the grow branch instead. The branch is reproduced verbatim but no test can reach it.
- No caller was inspected. The seventeen-plus recorded callers pass the same three arguments, and one of them would settle what argument 1 and argument 3 mean, but that is outside this target's budget.
- On the grow route (0x007f8e58 -> 0x007f8820) the new element is initialised by 0x007f7c00 from the LAST live element, whereas on the in-place route (0x007f8e15 -> 0x007f6d90) it is initialised from the prototype, whose +0x00 is null. Whether 0x007f8ea7 releases a displaced handle therefore depends on a callee that was not resolved. Resolving 0x007f7c00 and 0x007f7920 would settle it.
- The two constants at element+0x08 and element+0x10 have the shape of a multiple-inheritance vptr pair, but the word the body dispatches through sits between them at element+0x0c and is a runtime value copied from argument 1, not a vtable. Whether +0x08 and +0x10 are vptrs of two bases or plain constants is not settled by this body.
