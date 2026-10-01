# Validation 0x00c0b9c0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 2-instruction listing names through ECX (0xbbc) are all within the machine-derived receiver bounds (0xbbc), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `6234ccc80da3b8832a1bcb26d1264ce1e7b9f20d9ed061b9297864f4a5391738`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `192792ea581d7df912b844e0ea53ed24d4359074fb2502bbaa7b50d8d037af50`
- Pack digest quoted by the briefing: `6234ccc80da3b8832a1bcb26d1264ce1e7b9f20d9ed061b9297864f4a5391738`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential fixture is cheap for this target - it is one load - but it still requires a constructed receiver to be meaningful.`, `No original-process trace exists for this address, so the runtime value of +0xbbc and the real contents of the tuning globals are unverified.`, `The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential fixture is cheap for this target - it is one load - but it still requires a constructed receiver to be meaningful.
- Is 0x00c0b9c0 ever reached through a vtable at runtime even though no static DATA reference exists? A runtime patch or a dynamically built table would not show up statically and cannot be excluded.
- No original-process trace exists for this address, so the runtime value of +0xbbc and the real contents of the tuning globals are unverified.
- The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.
- What are the four tuning globals 0x01687a00, 0x01687a0c, 0x01687a10 and 0x01687a14 that the callers compare against? They were never read by a tool in this batch, so no value is claimed for any of them.
- What are the four unreported callsites at 0x00d760e7, 0x00d768eb, 0x00d77160 and 0x00d77234, which lie outside any Ghidra function body? Their surrounding code was not inspected.
- What class owns this function? 31 live references, all UNCONDITIONAL_CALL, and no DATA reference, so it is not a vtable slot and no owner can be named.
- What does the float at +0xbbc mean? The callers prove it is used as a threshold and as a bounded term in a weighted sum, but no SDK field, no global name and no string ties it to a game concept.
- What does the sibling accessor 0x00c0b8e0 read? It is called on the same receiver at 0x00ba27be and compared against 0x0156c198 and 0x0156c194, so it is a second parameter of the same kind, but its offset was not read.
- Who writes +0xbbc? No writer was found in this batch, so the field's lifecycle and default are unknown.
