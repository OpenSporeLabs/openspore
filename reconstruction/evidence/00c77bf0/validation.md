# Validation 0x00c77bf0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00c77bf0-bucket-membership-insert/bucket_membership_insert_00c77bf0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 39-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00c77bf0; 66 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 1 outgoing call edge row(s) and 1 distinct callee(s) the export records; 1 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00de5df0; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 1 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 39-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00c77bf0; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `WARN` | `partial` | 3 source field-offset declaration(s) (displacement 0x111c, displacement 0x4, displacement 0x8) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (39 of 39 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 39-instruction listing lie inside the recovered body span 0x00c77bf0..0x00c77c4c, so the branch graph is closed inside it; the source span declares if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 39-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `33129ca39c05c71b0ee68e0c19ab56f19cc1ed5ab9872ec289850908347655db`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `76c7432ee828c8301e6dbb273c7302d0a8bf666e9b44631385e2a2b02c9be43f`
- Pack digest quoted by the briefing: `33129ca39c05c71b0ee68e0c19ab56f19cc1ed5ab9872ec289850908347655db`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-simulator-callee-00de5df0-semantics`, `gate-simulator-receiver-identity`, `gate-simulator-table-purpose`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Runtime behaviour. No original-process trace exists in this repository for this target; nothing was run and nothing failed.
- The original source expression behind the third argument. The value the callee observes is `key & 0xffffff00` and that is what is claimed and tested, but a flag argument sharing a reused stack slot is indistinguishable from a mask at this boundary.
- What the table is and what the key identifies. Sixteen callers are recorded, one carries a name, and none of that evidence licenses a purpose for the body.
- Whether 0x00de5df0's own semantics make it an insert, a notification, or a registration. The body discards its return value and only the miss path reaches it; the name used here ('insert') describes the ROLE this body gives it, not what it does.
- Whether the three words the callee removes are twelve bytes of arguments or a mix of arguments and something else. The body pushes three words and pops none, so the total is twelve; nothing here says what the callee does with them internally.
- Why the index record's callee_dependencies is MISSING while callers_dependencies is populated. The complete listing's single E8 is the callee oracle used here, and it agrees with the decompilation's FUN_00de5df0.
- gate-simulator-callee-00de5df0-semantics
- gate-simulator-receiver-identity
- gate-simulator-table-purpose
