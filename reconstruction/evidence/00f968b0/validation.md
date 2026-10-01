# Validation 0x00f968b0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 39-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; 2 intra-procedural jump(s) target inside the recovered body span 0x00f968b0..0x00f968fd are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00f968c0, 0x00f968de; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00f968b0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 39-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field anchor_04, vtable and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (39 of 39 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 39-instruction listing lie inside the recovered body span 0x00f968b0..0x00f968fd, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 39-instruction body names 2 indirect transfer(s): 0x00f968cd dispatches slot 0x58 through the table word in EAX; 0x00f968e7 dispatches slot 0x58 through the table word in EAX; the machine parse consumed 39 of 39 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 4 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x58, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2b70b7ac4c38b2b21b53aed5fb111c8847a7cc34c64c5a7a356deb6a3bda0967`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `416c8421cef908c5f17cb241ce7f4d37ef75f7f4df77f1761484b0e328594cdd`
- Pack digest quoted by the briefing: `2b70b7ac4c38b2b21b53aed5fb111c8847a7cc34c64c5a7a356deb6a3bda0967`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No caller exists in the image, so the caller's expected argument, whether the id 0x8/0x7 answers are meant to alias one object, and whether the null-receiver path is reachable are all unobserved.
- Return type: the machine writes EAX with 1 (0x00f968ef) or 0 (0x00f968fa) and nothing else, so the source span declares bool; Ghidra's persisted signature and the SDK-derived label say 'Raster *'. A 0/1-valued pointer return cannot be excluded from this body alone. If the integrator prefers the pointer reading, the span's return type and this sidecar's observed_original_abi.return_type must change together.
- The briefing's single analogue (PKG-16-SPOREPEDIA-ONLINE, 0x00641770, matched on shared_vtable vtable:0x01490be8) is not usable prior art: 0x00641770 sits at slot index 2 of that table and is a Sporepedia asset-data predicate, so the match basis is a slot-index coincidence, not a shared class.
- The declared type of the second parameter is unknown. Ghidra calls it 'int quadIndex', but the body dereferences it twice as an object pointer and passes it as the callee's this, so the label is wrong; the owning class of vtable slot +0x58 is unidentified (the dispatch is register-indirect, so no xref names the implementation).
- The extents are not observable here. Only addresses of the anchored sub-object are taken, so neither its size nor the receiver's size follows from this target; the receiver's 0x100 modelled extent and the sibling pointers at +0x30/+0x74/+0xb8/+0xfc are borrowed from the sibling virtual 0x00f96870 in the same vtable, and the anchored sub-object's 4-byte blob is a modelling floor only.
- The owner of vtable:0x01490be8 was not established: the Ghidra label is address-only, its two xrefs were not traced to a constructor, and whether cTerrainSphere has a second vtable (the briefing lists vtable:0x01490c7c, which is this function's own slot) is open.
- Why the same address (receiver+0x04) is compared against two different selector ids cannot be decided from this body: it is equally consistent with source that queried the provider twice and with a compiler that duplicated an anchor load around an inlined call. The staged model reproduces the machine, not the intent.
