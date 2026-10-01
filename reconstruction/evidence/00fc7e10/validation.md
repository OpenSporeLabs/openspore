# Validation 0x00fc7e10

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 5-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00fc7e10; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 5-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 2 displacement(s) the source span declares (0x8, 0x10) and the 2 the complete 5-instruction listing names through ECX (0x8, 0x10) are all within the machine-derived receiver bounds (0x8, 0x10), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (5 of 5 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 5-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 5-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `44995772e3c70c4e226b3cb9104adbb6822822e75016d7e514f850fa2479093d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e1a7ced82ec7195de623d376a8d51750ab9a5f0924cb77748ad4db0d760fab36`
- Pack digest quoted by the briefing: `44995772e3c70c4e226b3cb9104adbb6822822e75016d7e514f850fa2479093d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation or indirect-caller trace was captured, so no concrete caller is known and the argument values a real caller passes cannot be observed.`, `The declared types of the words at receiver +0x08 and +0x10 are not established. Their observed uses are a CALL target and a call argument respectively, which constrains but does not prove them.`, `The owning C++ class name and the interface identity of slot +0x1c are not established. SporeApp.exe carries no MSVC RTTI, so class identity cannot be read from the binary; the 0x01493990 class is known only to derive from the 0x01491730 class because its constructor calls the latter's constructor.`, `Whether the +0x10 and +0x14 words belong to the same sub-object as the constructor-initialised words is unresolved; none of the three constructors initialises them.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Do the two arguments form a related pair, such as a callback and its context? 0x00fc7ec0 consumes them together as a call target and a call argument, which is consistent with that reading, but no arithmetic or relation is applied between them in this function.
- Is the return register value intentional? No instruction produces a result in EAX, so the source level return type is unknown; the SDK label says ImageTiling but the body is setter shaped.
- No original-process invocation or indirect-caller trace was captured, so no concrete caller is known and the argument values a real caller passes cannot be observed.
- The declared types of the words at receiver +0x08 and +0x10 are not established. Their observed uses are a CALL target and a call argument respectively, which constrains but does not prove them.
- The owning C++ class name and the interface identity of slot +0x1c are not established. SporeApp.exe carries no MSVC RTTI, so class identity cannot be read from the binary; the 0x01493990 class is known only to derive from the 0x01491730 class because its constructor calls the latter's constructor.
- What is the declared type and role of the word at receiver +0x10? 0x00fc7ec0 passes it as the third stack word to the +0x08 call, so its role is a call argument, but its type is not proven.
- What is the declared type of the word at receiver +0x08? It is executed as a code address by 0x00fc7ec0 and returned as a dword by 0x0093b6c0, but no declared type is proven.
- Whether the +0x10 and +0x14 words belong to the same sub-object as the constructor-initialised words is unresolved; none of the three constructors initialises them.
- Which C++ class owns vtables 0x01491730, 0x01492140 and 0x01493990, and what interface is slot +0x1c of? The 0x01493990 class provably derives from the 0x01491730 class, but no name is recoverable without RTTI.
- Which function does the SDK mean by GetTiling, this setter shaped slot +0x1c or the zero-argument dword read of receiver +0x08 at 0x0093b6c0 in slot +0x20?
- Why do none of the three constructors initialise +0x10 or +0x14 while this target writes +0x10 and 0x00fc7ec0 reads both? Either the constructors rely on zeroed storage, or those words sit in a different sub-object.
