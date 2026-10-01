# Validation 0x00b8dde0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b06/b8dde0_planet_record_store_terrain_key.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 17-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 3 the complete 17-instruction listing names through ECX (0x1a4, 0x1a8, 0x1ac) are all within the machine-derived receiver bounds (0x1a4, 0x1a8, 0x1ac), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (17 of 17 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 17-instruction listing lie inside the recovered body span 0x00b8dde0..0x00b8de1e, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 17-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d7b2856e1c4e6ce1adf1185e9f13212579647aa1ab3cde22341e3cde189a0355`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `94d9792cc80edf31ca58e7606803750b003e7c8731bb02c496e224b44487bc6d`
- Pack digest quoted by the briefing: `d7b2856e1c4e6ce1adf1185e9f13212579647aa1ab3cde22341e3cde189a0355`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.`, `No runtime evidence can distinguish 'write the same value' from 'skip the write' by observing memory alone, so any differential fixture for this function must observe side channels, not state.`, `The change check is only observable through a watcher. A differential test must instrument the field or the paired getter to confirm that a redundant write really is suppressed, and to establish why the compiler emitted the check.`, `The consume-once behaviour of the paired getter 0x00b8dd60 is a runtime claim about the materialisation service obtained from 0x00f48a80; a write watchpoint on record+0x1A4 across a full planet load is required to confirm it.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is 0xB0 or 0xAF the correct fifth IDGenerator argument? cPlanetRecord.h:342 records 0xAF while the observed callsites push 0xB0. The property id 0x00B1B104 and the offset 0x84 match exactly, so the discrepancy is isolated to one argument of a related SDK function and does not affect any claim made here.
- No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.
- No runtime evidence can distinguish 'write the same value' from 'skip the write' by observing memory alone, so any differential fixture for this function must observe side channels, not state.
- The briefing's canonical ledger recorded caller_count 12; the live xref query finds 16 call sites in 13 distinct caller functions. The four additional callers (0x00bbac80, 0x00c713c0, 0x00de6f20, 0x00f37690) are not a contradiction but a more complete count; 0x00bb2a50 alone accounts for five of the sixteen sites.
- The change check is only observable through a watcher. A differential test must instrument the field or the paired getter to confirm that a redundant write really is suppressed, and to establish why the compiler emitted the check.
- The consume-once behaviour of the paired getter 0x00b8dd60 is a runtime claim about the materialisation service obtained from 0x00f48a80; a write watchpoint on record+0x1A4 across a full planet load is required to confirm it.
- What does the +0x13C back-pointer at 0x00c713c0 point to, and why does that owner clear the key by writing a zero first word rather than calling a dedicated clear? Not established.
- What is 0x00ba8010, the function that computes the key at nine of the sixteen callsites? Its body was not read by this batch, so the provenance of the written key is unestablished.
- Which SDK method, if any, corresponds to this address? Spore-ModAPI declares `inline void cPlanetRecord::SetGeneratedTerrainKey(const ResourceKey& key) { mGeneratedTerrainKey = key; }` with no change check, so the name is explicitly withheld. The reconstructed name is descriptive and carries the VA token.
- Why does the change check exist? Nothing observable distinguishes skipping an identical write from performing it for a pure consumer, so the reason is unestablished. The most plausible purpose is suppressing a redundant change notification, but the notification for this setter's path was not found.
