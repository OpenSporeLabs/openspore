# Validation 0x0045b210

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b01/0045b210_lookup.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 45-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 2 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (45 of 45 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 45-instruction listing lie inside the recovered body span 0x0045b210..0x0045b286, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 45-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `3b9afbd14b59fcdc538610172d644018854d2c19629dd7ee1f0fefb77e7048fc`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `38d6d47c507d50192df3dedb386022a3088d4406976e5a3b148e79225dc94e00`
- Pack digest quoted by the briefing: `3b9afbd14b59fcdc538610172d644018854d2c19629dd7ee1f0fefb77e7048fc`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime pass would need to record the bucket count and the resolved object pointer for a handful of the hardcoded ids to confirm the id-to-class mapping.`, `No original-process trace exists, so the claim that the global at 0x015d0c14 is populated and that lookups succeed is static only.`, `The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime pass would need to record the bucket count and the resolved object pointer for a handful of the hardcoded ids to confirm the id-to-class mapping.
- Are 0x0045afc0 / 0x0045b000 / 0x0045b040 / 0x0045b110 thin wrappers over a named SDK method or a hand-rolled dispatch table? The body shape is a bare guarded virtual call, which fits either.
- Can a mapped value legitimately equal 0? If so, that entry is permanently invisible to every caller. Nothing in the static evidence answers this.
- Fourteen of the twenty-five reported call sites were not disassembled window-by-window in this batch; their receiver provenances come from the briefing's call graph.
- Is the bucket count fixed or rehashed at runtime? 0x0045b4c0 (the miss-path inserter reached from 0x0045b290) was not read, so rehash behaviour is unestablished.
- No original-process trace exists, so the claim that the global at 0x015d0c14 is populated and that lookups succeed is static only.
- The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.
- What are the concrete classes behind the mapped objects? Six virtual slots are observed across five call sites but no vtable base was resolved, so the interface is unnamed.
- What class owns the map? The only proven address is the global slot 0x015d0c14 and no vtable was located for the registry object, so the owning type is unnamed.
- What does the 32-bit id denote? Two sampled values look like hashed type ids, but no hashing routine was located and the SDK exposes no matching enumeration, so 'type id' stays a candidate.
- Which code writes a non-zero value into the global at 0x015d0c14? Only the clearing write at 0x005d61e7 was located; the populating write is not in the observed xref set, so it may be an indirect or registration-time store.
