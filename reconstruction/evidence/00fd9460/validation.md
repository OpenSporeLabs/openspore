# Validation 0x00fd9460

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-utfwin-settiling-wave13/utfwin_settiling_wave13.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 8-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00fd9460; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 8-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 2 displacement(s) the source span declares (0x4, 0x8) and the 0 the complete 8-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x4, 0x8), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (8 of 8 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 8-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 8-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `73b2fd93424fdb89127adbab0d76c3164aa400c17069cd5d009c9251ec56743b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `7faa4ad60c2ca8baf3936ac3a3af58dcc137ed1713f1908ddde3a165360b3376`
- Pack digest quoted by the briefing: `73b2fd93424fdb89127adbab0d76c3164aa400c17069cd5d009c9251ec56743b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation or indirect-caller trace was captured, so no concrete caller is known and the tiling values a real caller passes cannot be observed.`, `The C++ type, class name and role of the shared static object whose pointer is published at +0x08 are unestablished; its vtable 0x014f6f80 carries no names, and SporeApp.exe has no MSVC RTTI.`, `The declared C++ types of receiver +0x04 and +0x08 are not established. +0x04 is stored verbatim with no validation, and the import label ImageTiling is a candidate label, not machine evidence.`, `The interface identity of vtable slot +0x70 of 0x01493d00 is unresolved; the eighteen purecall entries show it is a wide interface but not which one.`, `Which constructor initialises +0x04 and +0x08 is unresolved: 0x00fd95f0 installs only the vtable and writes no field beyond +0x00.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the sibling SDK-named GetTiling at 0x00fc7e10 the matching accessor for this target's +0x04 word? It publishes two stack words at +0x08 and +0x10 of a receiver in the 0x01491730/0x01492140/0x01493990 family, which is a different class from this one, so the pairing is not established.
- No original-process invocation or indirect-caller trace was captured, so no concrete caller is known and the tiling values a real caller passes cannot be observed.
- The C++ type, class name and role of the shared static object whose pointer is published at +0x08 are unestablished; its vtable 0x014f6f80 carries no names, and SporeApp.exe has no MSVC RTTI.
- The declared C++ types of receiver +0x04 and +0x08 are not established. +0x04 is stored verbatim with no validation, and the import label ImageTiling is a candidate label, not machine evidence.
- The interface identity of vtable slot +0x70 of 0x01493d00 is unresolved; the eighteen purecall entries show it is a wide interface but not which one.
- What are the fifteen purecall slots at +0x2c..+0x64 of 0x01493d00? They are unresolved by definition, and the width of the interface constrains but does not identify it.
- What is the declared C++ type of the word at receiver +0x04? The Spore-ModAPI import calls the argument ImageTiling tiling, but the body stores it verbatim with no mask, comparison or conversion, so the import label is not machine-confirmed.
- What is the shared static object whose pointer is published at receiver +0x08? Its storage is 0x016f4afc, its pointer slot 0x016f4af4, its vtable 0x014f6f80 and its base vtable at destruction 0x0140de80, but no name or element type is recoverable and no other function in this reconstruction reads +0x08.
- Which C++ class and which interface own vtable 0x01493d00, and what is slot +0x70 of it? The eighteen purecall entries show a wide interface; the name is not recoverable without RTTI.
- Which constructor initialises +0x04 and +0x08 is unresolved: 0x00fd95f0 installs only the vtable and writes no field beyond +0x00.
- Which constructor initialises receiver +0x04 and +0x08? 0x00fd95f0, which installs vtable 0x01493d00, is only 22 bytes and writes no field beyond +0x00.
- Why does the target publish the shared-object pointer at all? SetTiling's own contract needs only the tiling word, so the +0x08 store is an incidental side effect of the source it was compiled from, whose shape is not established.
