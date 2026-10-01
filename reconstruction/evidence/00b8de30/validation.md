# Validation 0x00b8de30

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00b8de30-sim-record-lookup-chain/sim_record_lookup_chain_00b8de30.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 10-instruction listing name the same 3 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 4 outgoing call edge row(s) over 3 distinct address(es) for 0x00b8de30; 160 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 4 outgoing call edge row(s) and 3 distinct callee(s) the export records; 3 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00b3d2a0, 0x00ba6440, 0x00ba6d80; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 4 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 3 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 10-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00b8de30; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 10-instruction listing names through ECX (0x184) are all within the machine-derived receiver bounds (0x184), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (10 of 10 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 10-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 10-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b158ca312389be20e5199d3bc8d1f7700077a4ad26197247d58adfa89865cb5d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `22debb746cef6a353c0b464ace5afadbdf12ed6aefd94ac38dc79bba29aa7f6d`
- Pack digest quoted by the briefing: `b158ca312389be20e5199d3bc8d1f7700077a4ad26197247d58adfa89865cb5d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-simulator-callee-00ba6440-semantics`, `gate-simulator-callee-00ba6d80-semantics`, `gate-simulator-receiver-field-identity`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Runtime behaviour. No original-process trace exists in this repository for this target; nothing was run and nothing failed.
- The C type of the return, and specifically whether the RETURN SEMANTICS PASS is worth anything. The machine's last value-producing op is a CALL, so the width is not determinable and the validator's must-analysis classes the state UNCLASSIFIED. A caller listing (0x00bbe608, `mov edi,eax` immediately after the call) shows at least one consumer reading EAX, so the body is not provably void at the ABI level. The declared void reflects that this body produces no value of its own, and the discrepancy is left open rather than resolved. Note also that the PASS is source-vs-THIS-SIDECAR agreement: the committed index record carries abi {}, so with no worker return_type on record the check is NOT_AVAILABLE.
- What the dword at receiver + 0x184 denotes. The receiver record is bounds_only and no evidence in this package names the member.
- Whether the two thiscall callees 0x00ba6440 and 0x00ba6d80 are members of one class, which would make this a two-step forward. 0x00ba6440 does not read ECX at all and 0x00ba6d80 reads two fields of it; that is a fact about those bodies and no claim is made about a shared class.
- Why the record's dependencies.edges projects zero outgoing callees for this target. The export records four outgoing rows over three addresses, and the projection's 30-row window is spent entirely on the 160 incoming ones. CALLS reads the export whole and PASSes; the projection is a scheduler artefact and is not used as the callee oracle.
- gate-simulator-callee-00ba6440-semantics
- gate-simulator-callee-00ba6d80-semantics
- gate-simulator-receiver-field-identity
