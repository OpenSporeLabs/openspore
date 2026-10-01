# Validation 0x00582d70

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b02/b582d70_editor_remove_creature.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 199-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 199-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x360, 0x36c, 0x370), all of which the record accounts for or the listing is the better witness on; the 199-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=199, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x360, 0x36c, 0x370) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 6 displacement(s) (0x360, 0x364, 0x368, 0x36c, 0x370, 0x385), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 3 of those (0x364, 0x368, 0x385) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (199 of 199 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 15 conditional branch target(s) in the complete 199-instruction listing lie inside the recovered body span 0x00582d70..0x00582fdb, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 199-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c80e2c0326a5e625b8a626ee065852c25de312a311a990335db2a9dac5f2c5a1`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `700e067d805fdda3202ba32f359a81f73e1e791ab087b7ec371f2cde325a5f3a`
- Pack digest quoted by the briefing: `c80e2c0326a5e625b8a626ee065852c25de312a311a990335db2a9dac5f2c5a1`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace is required to confirm modes 0 and 2 are never taken, since no static reference to them exists.`, `A runtime trace is required to confirm no entry destructor is needed, i.e. that the removed 0x30-byte entries leak or are owned elsewhere by design.`, `A runtime trace is required to observe the 0x03f1bf57 notification reaching a listener, which is the only way to learn what the detach protocol announces.`, `No original-process trace has ever been captured for 0x00582d70; every claim here is static. The original Cell stage has never been entered in any recorded run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace is required to confirm modes 0 and 2 are never taken, since no static reference to them exists.
- A runtime trace is required to confirm no entry destructor is needed, i.e. that the removed 0x30-byte entries leak or are owned elsewhere by design.
- A runtime trace is required to observe the 0x03f1bf57 notification reaching a listener, which is the only way to learn what the detach protocol announces.
- Are modes 0 and 2 reachable at runtime through a patch or a function pointer? No static reference exists, and no differential trace has been captured.
- Is the owning class really Editors::cEditor? The evidence is the SDK address table's neighbourhood plus the receiver being the pointer stored at caller+0x3614; no vtable was located and the binary has no RTTI.
- No original-process trace has ever been captured for 0x00582d70; every claim here is static. The original Cell stage has never been entered in any recorded run.
- What are the eleven unread dwords of the 0x30-byte entry? AddCreature writes them, but no SDK structure describes the element.
- What are the two EDX-side divisions at 0x00582e6b..0x00582e7d and 0x00582ef6..0x00582f06 for? They recompute the same count; the pseudocode's variable naming makes them look like distinct quantities.
- What is the SDK method name of the target? The cEditor address table jumps from sub_581F70 at 0x00582250 to AddCreature at 0x00582fe0, leaving the target unnamed.
- What is the attach flag at +0x385? Its setter 0x0057e340 has three distinct effect groups (model slot +0xc4, the array at +0x98, 0x0043cfc0) and none is identified.
- What is the notification key 0x03f1bf57 and what does the 12-byte payload mean? 0x0045af60 forwards both to 0x0045ac20, which was not read.
- What singleton lives at 0x015d0c14? Its only reader in this body is 0x00401050.
