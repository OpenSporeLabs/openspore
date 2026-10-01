# Validation 0x0105a890

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/df2-live-listing/simulator_query_0105a890.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 155-instruction listing name the same 19 direct transfer target(s); 3 intra-procedural jump(s) target inside the recovered body span 0x0105a890..0x0105aa4d are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x0105a9fb, 0x0105aa0e, 0x0105aa38; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 22 outgoing call edge row(s) over 19 distinct address(es) for 0x0105a890; the source span names 19 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 155-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (155 of 155 instruction(s), 0 unparsed) and all 11 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 17 conditional branch target(s) in the complete 155-instruction listing lie inside the recovered body span 0x0105a890..0x0105aa4d, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 155-instruction body names 4 indirect transfer(s): 0x0105a8f7 dispatches slot 0xc through the table word in EDX; 0x0105a919 dispatches slot 0xc through the table word in EDX; 0x0105aa02 dispatches slot 0x14 through the table word in EDX; 0x0105aa32 dispatches slot 0x20 through the table word in EDX; the machine parse consumed 155 of 155 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b12d8df2e64dd4dd1a578cfea3062a645edc58fb31569ab9849f8e96dc2aae22`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `94f6120ec835f1ca45dfd6091024d8e2b696b74a2bf55ca7c028bf0d115e2bbb`
- Pack digest quoted by the briefing: `b12d8df2e64dd4dd1a578cfea3062a645edc58fb31569ab9849f8e96dc2aae22`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `no original-process trace exists in this repository; the static reconstruction of 0x0105a890 is unvalidated at runtime`, `the committed evidence pack's disassembly is a truncated envelope, so no listing-dependent check could be adjudicated from committed evidence`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- ECX is not established at the 0x00a206f0 call site, so that callee's receiver is unknown; the reconstruction declares it argumentless and says so.
- The committed pack's disassembly category is a truncated envelope, so every listing-dependent validation check reads NOT_AVAILABLE for this target. The listing used here came from the live bridge; a reader must not mistake it for the pack's own.
- The enumeration compared against the word at displacement 0x88 accepts 0, 1 and 2 but nothing here says what those three states are.
- The identity of 0x0105a050, the gate every path runs through, is not established; nothing in this body says what the three forwarded arguments mean.
- The receiver is forwarded and never dereferenced, so the machine-derived ABI record cannot name a receiver register and this reconstruction cannot say what the receiver is. Whether __stdcall with a register convention is excluded is not settled by this body alone.
- The three keys 0xce9f6639, 0x3ed590d and 0x75c412dd, and the two tags 0xf46092d3 and 0xf46093da, are immediates with no recoverable meaning in this body.
- What the word at displacement 0x124 of the first argument is, and whether 0x006e87e0 and 0x00cb5bb0 form an acquire/release pair on it, is not established.
- Whether the three-word local is a command, an event or a scoped context, and what the word at displacement 0x8 of it means, is not established; only the tag immediates distinguish the two construction paths.
- no original-process trace exists in this repository; the static reconstruction of 0x0105a890 is unvalidated at runtime
- the committed evidence pack's disassembly is a truncated envelope, so no listing-dependent check could be adjudicated from committed evidence
