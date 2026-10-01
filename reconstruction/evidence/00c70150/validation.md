# Validation 0x00c70150

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 96-instruction listing names 2 data address(es) (0x145f924, 0x167a60c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (96 of 96 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 12 conditional branch target(s) in the complete 96-instruction listing lie inside the recovered body span 0x00c70150..0x00c70252, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 96-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `81c904593ff2baa0a69df067d7e1bd3d9b88b4b187deb2cd3e445b2c5e9101f5`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `982e851cdac46b1a759d8b434b3f4461bed6a77de4ab67da1e01a7833fb1abd8`
- Pack digest quoted by the briefing: `81c904593ff2baa0a69df067d7e1bd3d9b88b4b187deb2cd3e445b2c5e9101f5`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test must confirm the owner's +0x194 value is 5 whenever the scan is expected to run, since a different value would make every call return 0.`, `No original-process trace has been captured for 0x00c70150. The 0x00c701d0 read of an apparently uninitialised stack slot is the single most important runtime gate: a trace must record the flag value at that address on entry to each of the ten call sites.`, `The 0x00c70221 ADD ESP,0x18 and the 0x00f473a0 argument order must be observed live to confirm the six-argument allocation contract.`, `The population-count computation in 0x00ff0870 must be checked against a live element, because the acceptance threshold of 1 depends on its exact result.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test must confirm the owner's +0x194 value is 5 whenever the scan is expected to run, since a different value would make every call return 0.
- How many stack arguments does 0x00c70150 really take? The body reads a fourth slot at ESP0+0x10 (0x00c701d0) but all ten inspected call sites push three words and clean twelve bytes. Either a caller that pushes four was not found, or the read is of an uninitialised slot whose observed value happens to be zero.
- If the fourth slot is uninitialised, what is its value at run time, and does the non-strict accept branch therefore execute by accident at some call sites? This changes the meaning of eight of the ten observed call sites.
- No original-process trace exists for any function in this batch. Every statement here is static.
- No original-process trace has been captured for 0x00c70150. The 0x00c701d0 read of an apparently uninitialised stack slot is the single most important runtime gate: a trace must record the flag value at that address on entry to each of the ten call sites.
- The 0x00c70221 ADD ESP,0x18 and the 0x00f473a0 argument order must be observed live to confirm the six-argument allocation contract.
- The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.
- The population-count computation in 0x00ff0870 must be checked against a live element, because the acceptance threshold of 1 depends on its exact result.
- Three of the ten call sites (0x00c308ec, 0x00c34568, 0x00c59711) were not disassembled.
- What class owns argument 1? The +0x15c/+0x160 list, the +0x194 kind and the +0x14c/+0x150 text buffer are observed, but nothing identifies the type.
- What do the +0x24 total and the +0x28 mask of an inner element mean? dword[+0x24] minus popcount(byte[+0x28]) is a remaining count, and the acceptance threshold is strictly greater than one, but neither the writer of those fields nor their unit was located.
- What is 0x00c451e0, called at 0x00c61a2d and 0x00c61b53 to build argument 2? Its body resolves this->+0x90 from the id at +0x8c through 0x00b3d2a0 and 0x00ba9370, with a virtual call at slot 0 and slot +0x4 on the old value, but its role is not established.
- What is the key at argument_3->[0x84] and the key at element->[0x14]? Both are only ever compared. 0x00c451e0 in the callers returns the object at this->+0x90, resolved lazily from an id at +0x8c, which suggests a resource or prototype id, but that is inference and is not claimed.
- What is the kind value 5? 0x00c47cc0 reaches an App::IAppSystem::Init transition when the mode field at +0x84 equals 3, so the receiver carries both a mode and a kind; the enum behind +0x194 is not in any ModAPI header.
- Why does the inlined analogue at 0x00c61a93 use the magic constant 0x18ea2cc where the out-of-line version consults the strict flag? The two are not obviously the same predicate, and the analogue additionally calls 0x00ff0760 at 0x00c61b07, which 0x00c70150 never does.
