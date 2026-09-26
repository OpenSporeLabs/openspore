# Validation 0x00580cb0

- Static reconstruction: `UNKNOWN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | every one of the 10 address-named source call(s) is a machine callee; 1 further callee(s) are not address-named in the source |
| GLOBALS | `WARN` | `partial` | global references are recorded but they are reconstruction-authored; the xref export carries 0 independent data reference(s) for this target |
| FIELDS/OFFSETS | `WARN` | `partial` | 15 source field-offset declaration(s) (field base_path, field context, field db_path, field db_tmp_path) are reconstruction-declared and no machine-derived struct layout exists to corroborate them |
| CONSTANTS | `NOT_AVAILABLE` | `none` | no constant evidence available |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no listing is collected |
| VIRTUAL DISPATCH | `UNKNOWN` | `partial` | the source declares an opaque slot boundary and no machine listing exists to confirm or contradict it |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 6 of 8 static checks evaluated, 3 passed, 2 had no evidence to evaluate; 9 of 16 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 9 of 16 static evidence categories are available

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation was captured, so no live handle, no live path buffer contents and no live return value was observed. Every statement in this record is a static reading of the 3.1.0.22 image.`, `The body is reached only through the table entry at 0x013f57f8 + 0x54, so its callers are indirect and cannot be enumerated from the binary. Whether it runs in a given play session, and with what receiver, is a runtime question.`, `The null-handle path cannot be exercised without a filesystem that refuses the open, and the observable it would produce is a fault rather than a value.`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the element width of the three path buffers really 16 bits? The two formats are written with the count 0x100 and the buffers are measured exactly 0x200 apart, so each holds at most 0x100 elements of some width. Sixteen-bit units agree with the UTF-16 literals and with 0x00580c10's own 0x100, but this body does not prove the width independently.
- No original-process invocation was captured, so no live handle, no live path buffer contents and no live return value was observed. Every statement in this record is a static reading of the 3.1.0.22 image.
- The body is reached only through the table entry at 0x013f57f8 + 0x54, so its callers are indirect and cannot be enumerated from the binary. Whether it runs in a given play session, and with what receiver, is a runtime question.
- The frame-size reconciliation. 0x011e0700's nineteen instructions leave the stack pointer 0x1024 below entry, while the epilogue releases two pops plus 0x1024, four bytes more. The alternative reading balances the epilogue but shifts every local address by four and pushes the sink past the top of the block. The local geometry is self-consistent only under the adopted reading, so the byte accounting stays open and the model asserts only the return form. A runtime trace of the original would decide it.
- The narrow string "Casual" sits at 0x013f586c, immediately after the table's twenty-eight pointer slots. Is it a string constant the linker happened to place there, or is one of the slots a pointer that this analysis has misread? The four bytes at +0x74 are 43 61 73 75, which is "Casu" and not a plausible address, so the first reading is better supported, but the placement is unexplained.
- The null-handle path cannot be exercised without a filesystem that refuses the open, and the observable it would produce is a fault rather than a value.
- The table entry at +0x58 is 0x00580df0 and Ghidra reports no function there. Is that an entry this analysis has not yet created a function for, or something else? The other twenty-seven entries are code addresses, so the first reading is more likely, but it is unconfirmed.
- What do 0x00692f90 and 0x00692900 do with the three arguments this body gives the first of them, the original receiver, the address 0x0150d100 and the constant 0x1a80d26? 0x00692900 walks a 0x14 byte element array at receiver +0x10 with a count at +0xa00 and a cursor at +0xa04, and it contains an INT3 at 0x00692ae5 on one error path, so the sink is a substantial object whose semantics belong to its own reconstruction.
- What is 0x0150d100? The body pushes the address once and never dereferences it, and the twenty-four bytes read there are zero. Which section it lies in was not determined, so whether it is a zero-initialised global that some other code fills is open.
- What is 0x01897c18? The body pushes the address three times and never dereferences it. The twenty-four bytes read there are a dword table whose entries rise in a constant stride of eight, which fixes an entry width and nothing else. It is passed as three of the constructor's four arguments, so it is plausibly a property descriptor rather than a data table, but the binary does not say.
- What is the declared return type? The machine forwards a 4-byte dword, and there are no direct call sites to measure how the indirect callers consume it, so the model returns an opaque 32-bit word.
- Which C++ class owns the receiver, and is the body a method of it or of something it holds? The word below the table at 0x013f57f8 is zero, so there is no RTTI, and the body never dereferences its receiver. The six sibling entries that other packages have reconstructed and the entry at +0x1c are consistent with one class's virtual set, which is evidence about the table and not a class name.
- Why does the guard cover the commit block but not the tail? The bytes are unambiguous, so this is not a question about the reading. Whether a null result from 0x00688fa0 is reachable in a shipping session, and whether the unguarded dereference is a latent defect or a path that never runs, is a runtime question this repository has no instrument for.
- runtime validation not run
