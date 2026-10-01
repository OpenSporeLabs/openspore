# Validation 0x0068f9b0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-job-continuation-0068f9b0/job_continuation_0068f9b0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 25-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x0068f9b0; 50 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 25-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x0068f9b0; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 25-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x8), all of which the record accounts for or the listing is the better witness on; the 25-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=25, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x8) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x8), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (25 of 25 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 25-instruction listing lie inside the recovered body span 0x0068f9b0..0x0068f9df, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 25-instruction body names 2 indirect transfer(s): 0x0068f9ca dispatches slot 0x0 through the table word in EAX; 0x0068f9da dispatches slot 0x4 through the table word in EAX; the machine parse consumed 25 of 25 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 3 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `caller_supplied`
- Pack integrity: `unchecked`
- Content SHA-256: `89ca8e7dc1788db36f54ce50c660a8c451ec4cbbb740bc41ab023a0de425c15c`

## Worker briefing

- Source: `caller_supplied`
- Briefing status: `complete`
- Content SHA-256: `89f4adf0b7c9b556cbebc912ee09a2a5c24ff3e9cb696007ae5b35cae98c924b`
- Pack digest quoted by the briefing: `89ca8e7dc1788db36f54ce50c660a8c451ec4cbbb740bc41ab023a0de425c15c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A live receiver whose +0x8 field differs from the incoming pointer is required for any dispatch to be observed; when they are equal (0x0068f9be) the body is a total no-op.`, `Both dispatched objects must carry a table with at least two dword slots before slot 0 can be entered; the machine test dereferences [obj] and then [table+0] and [table+0x4] unconditionally on the non-null path.`, `The two slot targets must be real thiscall functions taking only an ECX pointer; a differential run needs the concrete receiver type and the concrete slot implementations identified first, which the bytes do not establish.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A live receiver whose +0x8 field differs from the incoming pointer is required for any dispatch to be observed; when they are equal (0x0068f9be) the body is a total no-op.
- Are the three recorded table occurrences genuine vtables at all? They mix code pointers with non-code words and no vtable pass has been run on this program.
- Both dispatched objects must carry a table with at least two dword slots before slot 0 can be entered; the machine test dereferences [obj] and then [table+0] and [table+0x4] unconditionally on the non-null path.
- Do the 50 direct callers all pass the same kind of object, or do the tables at 0x014018b0 / 0x0143dcc4 / 0x0143ddf4 correspond to several distinct receiver types?
- The two slot targets must be real thiscall functions taking only an ECX pointer; a differential run needs the concrete receiver type and the concrete slot implementations identified first, which the bytes do not establish.
- What are the concrete targets behind vtable slots 0 and 1? The xref export constrains neither, because both dispatches are indirect and no data reference to this VA exists.
- What are the concrete types of the receiver and of the dispatched object? The bytes name neither, and SporeApp.exe carries no RTTI.
- What is the meaning of the dword at receiver+0x8, and what do the two slots called around the store actually do? A retain/acquire plus release reading is a hypothesis; the bytes fix only the order and the guards.
- What is the receiver's total size? Only the single dword at +0x8 is touched, so the surrounding layout is unknown.
