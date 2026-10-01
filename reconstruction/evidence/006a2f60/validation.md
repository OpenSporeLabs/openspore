# Validation 0x006a2f60

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 106-instruction listing name the same 4 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x006a2f60..0x006a306a are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x006a3057; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 6 outgoing call edge row(s) over 4 distinct address(es) for 0x006a2f60; 2 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 106-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field entries_begin, key, parent, properties and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (106 of 106 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 8 conditional branch target(s) in the complete 106-instruction listing lie inside the recovered body span 0x006a2f60..0x006a306a, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 106-instruction body names 2 indirect transfer(s): 0x006a2fcb dispatches slot 0x4 through the table word in EDX; 0x006a2fe3 dispatches slot 0x2c through the table word in EDX; the machine parse consumed 106 of 106 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a959d68ce42fdf9f07273dbcf65ddea911f22cfed223ac57504e2e63b4c5810b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b7137c09db9c51a450f9677b220aaa4b021008a84a2213c01120d4128b3b7998`
- Pack digest quoted by the briefing: `a959d68ce42fdf9f07273dbcf65ddea911f22cfed223ac57504e2e63b4c5810b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- One-dword stack-slot discrepancy at the header read: 0x006a2f70 LEA EAX,[ESP+0x2c] (ESP = entry-0x28) targets entry ESP+0x04, which is the pInputStream argument slot, while 0x006a2f7f MOV EAX,[ESP+0x34] (ESP = entry-0x2c) reads entry ESP+0x08, one dword higher. The persisted decompilation aliases both onto the argument slot. Write @ 0x006a1540 shows the same idiom gap-free (0x006a1560 LEA ECX,[ESP+0x14] and 0x006a156b MOV [ESP+0x1c],EAX both resolve to the same address), so the gap is specific to Read. The reconstruction models the intended single 32-bit header word, which is the decompiler's reading, but the exact slot the machine consumes is not settled.
- The identity of the DAT_015fd8a8 service and the meaning of block[0] and block[2] as its port arguments. The pointer is zero in the static image, so neither its vtable identity nor the parameter meaning can be recovered without runtime evidence.
- What the header word's sign bit and the 0x7fffffff mask on block[1] actually encode. The mask proves one flag bit is carried alongside the count, but no second writer of this format was located in the binary.
- Whether the 16-bit ObjectTYPE switch and array-dimension handling inside 0x00694440 belong to this record's value layout, and whether the conflicting 'App::Property 4-byte versus 0x14-byte layout' ledger entry (knowledgegraph/research/conflicts/track-b-vtable-fields.json, TB-FL-006) is settled by this evidence. The 0x04 value offset and 0x18 stride are observed here, but the ledger is left at preserved_alternatives and is not claimed as resolved.
