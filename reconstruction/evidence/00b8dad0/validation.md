# Validation 0x00b8dad0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b34ca72bf45cbb741336d4af034d0d394ef8c36f89bbc984bcd09631e08588e7`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `7cc0368b261cd4a3cb01341b574803460b81c2f6960e9715cdb07212376b8a75`
- Pack digest quoted by the briefing: `b34ca72bf45cbb741336d4af034d0d394ef8c36f89bbc984bcd09631e08588e7`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists. A differential run must confirm the returned address is still receiver + 0x198 in the shipping build.`, `The class attribution rests on a type-name literal read at 0x00ba61b0. A run that dumps the concrete vtable pointer of a constructed record would confirm or refute it.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does any caller write through the returned pointer, or do all 17 only read? Comparison sites were confirmed; a writing site was not searched for exhaustively.
- Fifteen of the seventeen recorded callsites were not individually disassembled, so their receiver setup and result use come from the canonical xref list only.
- Is the block at +0x188, the second address-taken accessor at 0x00b8da60, the same kind of three-dword block? Its extent was not bounded; only its address was observed.
- Is the twelve-byte block at +0x198 a ResourceKey, three separate uint32, or a struct of three ids? The three-dword extent is observed; the field names are the SDK candidate's, not the binary's.
- No original-process trace exists. A differential run must confirm the returned address is still receiver + 0x198 in the shipping build.
- Spore-ModAPI's cPlanetRecord header is itself a third-party reconstruction, so the layout agreement is corroboration, not proof. The binary is the authority for the offsets; the header only supplies plausible names.
- The class attribution rests on a type-name literal read at 0x00ba61b0. A run that dumps the concrete vtable pointer of a constructed record would confirm or refute it.
- What is this accessor called in the original source? Spore-ModAPI declares mSpiceGen at +0x198 but no accessor for it, and declares GetGeneratedTerrainKey() for the +0x1A4 sibling instead. The names GetSpiceGenKey and SetSpiceGenKey used in this worker's reconstruction and filenames are this worker's invention, not SDK or original names.
