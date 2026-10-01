# Validation 0x004adc40

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-editor-adc40-flag/adc40_flag.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 9-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x004adc40; 68 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 9-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x4f) and the 0 the complete 9-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x4f), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (9 of 9 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 9-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 9-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is WIDTH_1_IN_EAX and the source span declares return type 'Field', whose width cannot be computed from the declaration (a typedef, a class, a template or an alias); the machine width is a fact and the C type is a source-side choice, so there is nothing to compare |

Static evidence basis: 7 of 8 static checks evaluated, 7 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `6f2bc2d767ecfa7503633524fcbeb6ed9e5164e8b7ad63feffda536251ddf015`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `873959763469695bc11b11cdb727031f65c87fb3a77f3a35f009e786932cd3fc`
- Pack digest quoted by the briefing: `6f2bc2d767ecfa7503633524fcbeb6ed9e5164e8b7ad63feffda536251ddf015`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Do all 64 direct callers pass the same concrete receiver type, given the +0x28-member and stack-local receiver provenances already observed?
- Is the +0x4F byte a bool, a small enum, or a bitfield-style flags byte? Callers only ever test it for zero, so the evidence cannot separate these.
- What concrete class is the receiver, and does its +0x4F byte carry a name in the Spore ModAPI SDK?
- What values are observed at receiver+0x4F in the original process?
- Which of the two independent packages for this VA, pkg-editor-adc40-flag or pkg-editor-adc40-smoke01, should the integrator promote? They agree on every machine-derived fact and differ only in the justification for not using a hand-written body, where this package's justification is the measured one. The index currently resolves this VA to pkg-editor-adc40-flag because that path sorts first.
- Which owner constructs and publishes receivers for this accessor?
