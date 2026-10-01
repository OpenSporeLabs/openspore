# Validation 0x004a88d0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 12-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 2 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (12 of 12 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 12-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 12-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7c339cda171bf81827e519d7a02dbc741acd9dc175394ae51cc8b29f91870e41`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6f21dc201e91edd597fb6aaea73e848e75a80af3e7c079055253b03b64312f2d`
- Pack digest quoted by the briefing: `7c339cda171bf81827e519d7a02dbc741acd9dc175394ae51cc8b29f91870e41`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test is required to (a) observe the singleton being installed, (b) capture the concrete implementations behind slots +0x20, +0x38, +0x40 and +0x58, and (c) read the three key strings out of the sibling module once that module is available. Without (a) the static observation that the function is a no-op in the imported image says nothing about the shipping build.`, `No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.`, `The undo/redo inference additionally requires observing a listener that reacts to the emitted record.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test is required to (a) observe the singleton being installed, (b) capture the concrete implementations behind slots +0x20, +0x38, +0x40 and +0x58, and (c) read the three key strings out of the sibling module once that module is available. Without (a) the static observation that the function is a no-op in the imported image says nothing about the shipping build.
- Does the tag have a stable public meaning, or is it a per-build hash of a source identifier? Every inspected argument is an opaque 32-bit value with no accompanying string, and no decoding table was found.
- Is the record an undo/redo transaction, a change notification, or a telemetry event? The call sites immediately preceding cEditor::Undo and cEditor::Redo make an undo/redo reading the most economical, but the +0x38 and +0x40 targets are unresolved, so this stays INFERRED.
- No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.
- The undo/redo inference additionally requires observing a listener that reacts to the emitted record.
- What class is behind DAT_0166D9F4? Its shape - slot +0x20 returning a context value, +0x38 taking a scope name, +0x3C/+0x40 taking key/value pairs, +0x58 closing, and +0xC4 as a no-argument update called from 0x00a228b0 - is observed, but no SDK header matches it and no vtable for it was located. Spore/App/IMessageManager.h was read and rejected: its +0x38 is ProcessQueue2() with no argument and its +0x40 is Lock(bool), which contradicts both observed shapes.
- What do the strings at 0x03475365, 0x03475381 and 0x03475385 say? All three lie outside SporeApp.exe's image span and carry no base relocation, so they address literals in a sibling Spore module. 2661 dwords in this image's .rdata point into 0x02xxxxxx-0x05xxxxxx, which is consistent with Spore's modules sharing one fixed address map, but no such module is present in this installation and none of the installed PE files has a preferred base near 0x03470000.
- What is slot +0x3C for? It appears only in the sibling 0x00435f40, never in this target's sequence, so the difference between the two records is not established.
- Who installs the singleton? A raw byte scan of the whole .text for the four-byte pattern of 0x0166D9F4 finds exactly the 24 references Ghidra reports, and every one of the three observed writes stores zero. No instruction in SporeApp.exe ever stores a non-null value, so the installation must happen in another module of the same process.
- Why does 0x00435ed0 open with PUSH ECX (0x00435ed3)? It reserves the four-byte local at [EBP-4] and the following CALL passes no argument, so it is not a thiscall receiver. This is stated so the decompiler's phantom __thiscall signature on 0x00435ed0 is not mistaken for evidence.
