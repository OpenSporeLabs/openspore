# Validation 0x0095fd60

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 26-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x0095fd60; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 26-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 7 displacement(s) (0x0, 0x10, 0x14, 0x90, 0xa8, 0x114, 0x1dc) and every one of them is a displacement the complete 26-instruction listing shows: 1 attributed to the receiver ECX as proven (0xa8); 2 more (0x0, 0x1dc) are grounded in the machine-derived receiver record rather than in the scan; 4 more (0x10, 0x14, 0x90, 0x114) are shown by the listing under a base that is not the receiver -- 0x10 under ESP; 0x14 under ESP; 0x90 under EAX; 0x114 under EAX -- so the body does use those displacements, on an object this check cannot identify; that is a limit of the attribution here and not a disagreement with the receiver, and no receiver contradiction is claimed for them; the 26-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=26, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0xa8) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x0, 0xa8, 0x1dc), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x0, 0x1dc) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (26 of 26 instruction(s), 0 unparsed) and all 7 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 26-instruction listing lie inside the recovered body span 0x0095fd60..0x0095fdb4, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 26-instruction body names 2 indirect transfer(s): 0x0095fd99 dispatches slot 0x114 through the table word in EAX; 0x0095fdae dispatches slot 0x90 through the table word in EAX; the machine parse consumed 26 of 26 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 54 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7518932e28a63ee615c86e2fcfc1cc6f4be9a3a82b5dcfd65717d022bd4835f0`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3f16181406a5888be4dcb98f3cf8f35534097d8331e5b8c01533f358068b93db`
- Pack digest quoted by the briefing: `7518932e28a63ee615c86e2fcfc1cc6f4be9a3a82b5dcfd65717d022bd4835f0`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `ownership and lifetime of the word stored at +0xa8 unresolved`, `producer of the +0x1dc gate unresolved`, `record consumer semantics (vtable slot 0x114) unresolved`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The declaring class of func35 within UTFWin::Window: no MSVC RTTI exists in SporeApp.exe, so the owning class and its position in the hierarchy are not provable from this target alone.
- What the constant 0x13 in record +0x08 denotes: the SDK gives no name for func35, and the decompiler's 'Enum ObjectTYPE' warning is program-wide rather than tied to this literal, so no enum meaning is claimed.
- What vtable slot 0x114 does with the record. Its two observed implementations are an address with no defined function (0x00993200) and a stub returning 0 (0x006f2f20), so the consumer-side meaning of (0x13, new, previous) is unresolved.
- Whether the +0x1dc gate is a dirty/needs-invalidate flag. Only a zero test is observed here; the flag's producer and full field extent beyond 0x1df are unestablished (0x1e0 is only the arithmetic end of the last dword, not an observed object size).
- Whether the word at +0xa8 and the argument are object pointers or plain identifiers: this function only compares, stores and forwards the word, so nothing here distinguishes a pointer from an id; the value is kept as an opaque 32-bit word.
- ownership and lifetime of the word stored at +0xa8 unresolved
- producer of the +0x1dc gate unresolved
- record consumer semantics (vtable slot 0x114) unresolved
