# Validation 0x007c66b0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-camera-msg-007c66b0/camera_msg_007c66b0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 32-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x007c66b0; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 32-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 3 displacement(s) (0x4, 0x8, 0x60) and every one of them is a displacement the complete 32-instruction listing shows: 1 attributed to the receiver ECX as proven (0x60); 2 more (0x4, 0x8) are shown by the listing under a base that is not the receiver -- 0x4 under EAX, ESI; 0x8 under ESI, ESP -- so the body does use those displacements, on an object this check cannot identify; that is a limit of the attribution here and not a disagreement with the receiver, and no receiver contradiction is claimed for them; the 32-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=32, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 4 displacement(s) to the receiver as proven (0x0, 0x60, 0x64, 0x68) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 3 displacement(s) the record does not enumerate (0x60, 0x64, 0x68), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (32 of 32 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 32-instruction listing lie inside the recovered body span 0x007c66b0..0x007c66f8, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 32-instruction body names 1 indirect transfer(s): 0x007c66e5 dispatches slot 0x54 through the table word in EDX; the machine parse consumed 32 of 32 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x54, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c85a94e93a4bcf8990a6a9010a31a49dcc0501dcba2b9031c5cec4ab49cdf321`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `47f36368f6df7e080c6005a0c14f8f09fb99d7979c12c3165857dcd5552fca11`
- Pack digest quoted by the briefing: `c85a94e93a4bcf8990a6a9010a31a49dcc0501dcba2b9031c5cec4ab49cdf321`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No Wine/original trace was run for this target; no runtime promotion is claimed.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does any caller pass a second message argument? The body never reads [ESP+8] and RET 0x4 pops one dword, so a second declared argument is possible but unconfirmed.
- Ghidra's function boundaries in this neighbourhood are unreliable: the SDK entry 0x007c64c0 sits inside the flow that starts at 0x007c6480, so slot identities that depend on Ghidra function extents (0x007c64c0 SetActiveCamera, 0x007c6e50 Dispose) are taken from the live listing rather than from Ghidra's function records.
- Is the receiver's dispatch vptr 0x014106a8 (ctor field +0x00) or 0x014106a4 (ctor field +0x04)? The byte offset 0x54 resolves to 0x007c6420 under the first and to 0x007c6480 under the second. No call site of HandleMessage was found to disambiguate, and the SDK label for 0x007c6420 is unknown.
- Is virtual slot 0x54 named SetActiveCameraByIndex, SetActiveView or something else in the SDK? 0x007c6420 is only an unnamed vtable entry; the name is not guessed here.
- No Wine/original trace was run for this target; no runtime promotion is claimed.
- What populates the registry at +0x60, i.e. which message ids map to which camera slots? No inserter for this map was located from this target.
