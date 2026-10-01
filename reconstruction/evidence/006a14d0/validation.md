# Validation 0x006a14d0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_app_proplist_copyall_wave16/all_copy_from_properties_006a14d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 25-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x006a14d0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 25-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 25-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x30), all of which the record accounts for or the listing is the better witness on; the 25-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=25, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x30) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x30), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x0) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (25 of 25 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 25-instruction listing lie inside the recovered body span 0x006a14d0..0x006a1506, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 25-instruction body names 3 indirect transfer(s): 0x006a14ef dispatches slot 0x4 through the table word in EAX; 0x006a14f8 dispatches slot 0x48 through the table word in EAX; 0x006a1502 dispatches slot 0x38 through the table word in EAX; the machine parse consumed 25 of 25 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 5 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x4, 0x38, 0x48, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `079aa8b946650f4a7be5b12687a97d21cc959ed74ca450248b88de489e415a6f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5ba7b493e06de7ca6807197d136860e8f4682b6fcaa97b2bd6390c71560259fb`
- Pack digest quoted by the briefing: `079aa8b946650f4a7be5b12687a97d21cc959ed74ca450248b88de489e415a6f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Can the adding step see a stale view of the source? 0x006a1510 reads its argument's word at displacement 0x30 and, when it is non-null, recurses through its own slot +0x38 before calling its own slot +0x30. This body has just cleared the RECEIVER, and on every path past the guard the source is a different object, so the interaction is presumably benign -- but this body performs no check that would make it so, and the recursion inside 0x006a1510 is not characterised here.
- Can the re-read of the receiver's table pointer at 0x006a14fa matter? The listing reads it twice, and this body models the re-read. Whether anything between the two reads can change the receiver's table pointer is not determinable from this body, and neither of the two +0x48 targets has been characterised for such a write here.
- Is 0x00432b50 the right slot +0x04 target at run time? Both table images agree on it, which is as strong as static evidence gets, but the transfer is dispatched on the HELD OBJECT and that object's dynamic type may be a third class not represented by either image.
- No evidence pack. reconstruction/evidence/006a14d0/evidence.json does not exist, so the reconstruction's facts are cited by live address rather than by a persisted artefact. An integrator may want to generate one before promotion.
- Return-type evidence. Unlike the pkg-app-proplist-wave13 sibling, no machine-derived ABI record for this target was available to contradict void, so RETURN SEMANTICS has no known conflict. That is an absence of counter-evidence, not positive confirmation; the positive basis is the listing and the Ghidra prototype.
- What is the word the receiver holds at displacement 0x30? The machine supports exactly three claims: it is 4 bytes wide, it is compared against zero and it is dispatched through slot +0x04 of a table reached by dereferencing it. Whether it is a parent, an owner, a back-link or something else is not established by any record for this target, and the name mpParent is decompiler-derived from the imported SDK symbols. The model types it only as an object whose first word is a table pointer, which is the least that survives the evidence.
- What receiver+0x30 actually holds. Ghidra's imported SDK structure names it mpParent, and the dispatch at 0x006a14ea treats it as an object with its own vtable (it is used as a thiscall receiver), which is strong evidence it is an object pointer. The binary carries no MSVC RTTI, so the name is decompiler-derived from the imported SporeGhidra_march2017 symbols and is not independently confirmed here.
- Whether 0x00432b50 is the correct slot +0x04 target for BOTH classes at runtime. The two images agree on 0x00432b50 in that slot, which is as strong as static evidence gets, but the release is dispatched on the PARENT, whose dynamic type may be a third class not represented by either image.
- Whether the add step can see a stale view of the source. Slot +0x38 target 0x006a1510 dispatches slot +0x38 again on the receiver when the SOURCE has a parent (its own live decompilation reads argument+0x30 and, if non-null, recurses through its own slot +0x38 before calling slot +0x30). This body has just cleared the RECEIVER, and the source is a different object, so the interaction is presumably benign -- but this body performs no check that would make it so, and the recursion inside 0x006a1510 is not characterised here.
- Which of the two table images is the receiver at run time? The body is shared and the +0x48 step is the only one that differs, so the answer changes which clearing code runs. Nothing in the evidence picks one, and the model dispatches through the table pointer in memory, which is the honest shape rather than a choice.
- Who calls this, and with what? fan_in is 0, callers is empty and the only two xrefs are the table placements. Nothing establishes the entry conditions, so no precondition, no aliasing expectation beyond the pointer-identity guard, and no null-source expectation is claimed.
- Why is slot +0x48 overridden but slot +0x38 not? The two images share this body at +0x34 and the same 0x006a1510 at +0x38, yet carry different targets at +0x48. Whether the source-adding step was deliberately left un-overridden because it must behave identically for both list kinds, or was simply never needed as an override, is not decidable from the images alone.
- Why is the word detached before it is released? The store at 0x006a14e3 precedes the transfer at 0x006a14ef and the order is observable. Nothing in this body states a reason, and 0x00432b50's own listing shows no path that reads a child's word at 0x30, so the motivation is not recoverable from what is here. It reads like an unlink-then-release to break a cycle or to satisfy a re-entrancy invariant in the callee; that is a reading, not a record, and is not modelled as one.
- Why slot +0x48 is overridden but slot +0x38 is not. The two vtable images share this body at +0x34 and 0x006a1510 at +0x38, yet carry different Clear implementations at +0x48. Whether the add step was deliberately left non-virtual (because it must behave identically for both list kinds) or was simply not needed as an override is not decidable from the vtable images alone.
- Why the parent is detached before being released. The body stores zero at receiver+0x30 and only then dispatches the release on the parent, which reads like a deliberate unlink-then-release to break a cycle or to satisfy a re-entrancy invariant in 0x00432b50. Nothing in this body states the reason, and 0x00432b50's own body shows no path that reads the child's +0x30 word, so the ordering is observable but its motivation is not established here.
