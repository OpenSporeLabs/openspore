# Validation 0x00bb9b00

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-pilot-core-b01/bb9b00_star_record_set_flags.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 9-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 9-instruction listing names through ECX (0x5c) are all within the machine-derived receiver bounds (0x5c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (9 of 9 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 9-instruction listing lie inside the recovered body span 0x00bb9b00..0x00bb9b1a, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 9-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `40670a2c1f497ad9bfad569304fdf3c06158f4d67e311a4c58e786e574d934a6`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `912c23a076564566a765234330e7b2b7ac2d7eb103bf73e943775674c75f8238`
- Pack digest quoted by the briefing: `40670a2c1f497ad9bfad569304fdf3c06158f4d67e311a4c58e786e574d934a6`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace would be needed to observe the actual flag word of a real star record before and after a state transition, and to confirm that no other code path writes +0x5c outside this function and the two siblings that read it.`, `No original-process trace exists for 0x00bb9b00; every claim is static.`, `The undocumented bit meanings can only be resolved by correlating runtime flag values with game events, which no recorded run provides.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace would be needed to observe the actual flag word of a real star record before and after a state transition, and to confirm that no other code path writes +0x5c outside this function and the two siblings that read it.
- Do all 24 callers use only single-bit masks? The three inspected windows pass 0x1, 0x2, 0x4, 0x8000 and 0x40000000, all single-bit, but 0x00bb4f30's loop passes the SAME mask for every entry while loading a different dword from the table into ECX's target field via the callee - so the per-entry value is read but not used as a mask. That inconsistency is unexplained and the remaining callers were not checked.
- Is the +0x5c word shared with any other structure? cStarRecord.h places mFlags there, and the SDK's own TODO comment at cStarRecord.h:105 reads 'TODO 1 << 4 (16) is visited? sub_BB8B50', which suggests the reverse engineer was themselves unsure about this field's flag discipline.
- Is the function ever called with a mask of 0? That would be a no-op in both directions, and no inspected caller does it, but nothing in the code forbids it.
- No original-process trace exists for 0x00bb9b00; every claim is static.
- The undocumented bit meanings can only be resolved by correlating runtime flag values with game events, which no recorded run provides.
- What do bits 2, 15 and 30 mean? They are set or cleared by shipping callers but are undocumented in cStarRecord.h, and their names cannot be recovered statically.
- What do bits 3, 6 and 9 mean? cStarRecord.h speculates in comments about 0x8 (monolith), 0x40 (destroyed planet) and 0x200 (raid), but no inspected caller of this function exercises them, so the speculation is untested here.
- Which cStarManager member is 0x00bb5640? The SDK symbol table places cStarManager::RecordToPlanet at 0x00BB5B50 and StarGenerationMessageHandler at 0x00BB5F00, so 0x00bb5640 is an unnamed member of the same class, and it is the caller that exercises three of the five masks.
