# Validation 0x0051e340

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-vft-preinc-0051e340/vft_preinc_0051e340.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 20-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x0051e340; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 20-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 20-instruction listing is the whole body: it was consumed in full by the machine parse (declared_count=20, degraded=false, unparsed=0); the alias-aware scan of it over receiver register ECX finds no memory operand addressed through the receiver or through any register derived from it -- it follows a copy, an XCHG, an address chain and a push/pop pair, so a field access made through a register the receiver was moved into would still be seen -- which is evidence that this body addresses no receiver field; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist; which member sits at which displacement is not established by any record in this pack and is not claimed here |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (20 of 20 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 20-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 20-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 9 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 9 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7e20aed089b2b97ab4ee92102ae26f19a7bb2cd6451b6789213999b823817b3c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `0004ffeac4142da9286251b834ea88685abc3b1fce56a82e3df8fd6db2ba2810`
- Pack digest quoted by the briefing: `7e20aed089b2b97ab4ee92102ae26f19a7bb2cd6451b6789213999b823817b3c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The class is unknown and unknowable from this evidence: 42 vptr-backed tables hold the body, which is ICF collapse, so 'virtual member of some class' is the strongest true statement.
- The engine's return classifier says pointer_like (the last EAX write is a load from memory) while the source reads the value as an integral dword. The width (4 bytes) is the machine fact both agree on; the classification difference is recorded rather than resolved.
- The machine reads the field dword twice, both reads before the store. The source spells a single-read pre-increment, which is observationally identical because nothing runs between the reads; whether the original source was '++x', 'x = x + 1' or 'return x++ + 1' cannot be decided from the bytes.
- The receiver-relative offset 0x8 is not machine-attested as a single operand: the machine states 0x4 twice. A runtime trace of a constructed object would settle the layout, but no original-process trace exists in this repository.
- Which member sits at receiver+8 is not established. The offset is a composition of two machine displacements; the member's name, type and purpose (a counter? a version? an index?) are not recoverable from a 20-instruction body that only increments it.
