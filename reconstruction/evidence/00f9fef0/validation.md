# Validation 0x00f9fef0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 112-instruction listing name the same 5 direct transfer target(s); 4 intra-procedural jump(s) target inside the recovered body span 0x00f9fef0..0x00fa0006 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00f9ff00, 0x00f9ff5f, 0x00f9ff78, 0x00f9ff91; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 6 outgoing call edge row(s) over 5 distinct address(es) for 0x00f9fef0; the source span names 5 of them and no others |
| GLOBALS | `PASS` | `complete` | the machine-vs-machine rule: all 1 data address(es) the source span names are recorded as Ghidra data references out of this body, and the complete 112-instruction listing corroborates 1 of them; the artifact records 1 read across 1 reference row(s)the data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 1 data reference row(s) out of 0x00f9fef0 over 1 distinct address(es); 1 of them name writable storage (0x015fd918), which is where a mutable global can live; segment breakdown: .data=1; access modes recorded: 1 read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 112-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x4), all of which the record accounts for or the listing is the better witness on; the 112-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=112, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x4) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the listing shows 1 displacement(s) the record does not enumerate (0x4), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (112 of 112 instruction(s), 0 unparsed) and all 19 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 112-instruction listing lie inside the recovered body span 0x00f9fef0..0x00fa0006, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 112-instruction body names 10 indirect transfer(s): 0x00f9ff0d dispatches slot 0x58 through the table word in EAX; 0x00f9ff6b dispatches slot 0x4c through the table word in EDX; 0x00f9ff84 dispatches slot 0x4c through the table word in EDX; 0x00f9ff9d dispatches slot 0x4c through the table word in EDX; 0x00f9ffb0 dispatches slot 0x1c through the table word in EDX; 0x00f9ffc4 dispatches slot 0x13c through the table word in EDX; 0x00f9ffcc dispatches slot 0x4c through the table word in EBX; 0x00f9ffda dispatches slot 0x134 through the table word in EAX; 0x00f9ffed dispatches slot 0x54 through the table word in EDX; 0x00fa0001 dispatches slot 0xc through the table word in EDX; the machine parse consumed 112 of 112 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 10. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'Word*': the return register EAX is written at a width this module cannot bound on at least one of the 2 reachable return(s) in the complete 112-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 7 passed, 1 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `67c16fa0e3ae44c198af45465cde4dbed1dd7a78d91c46943b2ee3c3dde0de70`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `d6992d76a41f970751811d2c3147c9b4e67255fa3de569990229e27105e13012`
- Pack digest quoted by the briefing: `67c16fa0e3ae44c198af45465cde4dbed1dd7a78d91c46943b2ee3c3dde0de70`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the first callee-popped stack word a parameter at all? It is established that the body reads it, dereferences it five times, spills a byte into it, tests that byte, and zeroes it before a tail transfer. Whether it is a declared parameter, and of what type and meaning, is not established by this listing and is not guessed.
- The machine record and the listing DISAGREE about the first callee-popped stack word: the record says read: false and written: false, and the listing reads it at 0x00f9ff00 and writes it at 0x00f9ff38 and 0x00f9fff4. The record's own abstention ("flow_not_modelled: the linear ESP walk ends at +60, so the listing is not one path") explains why, and the record was deliberately not edited, but the disagreement is real and is not resolved here. Which reading the game's own callers would confirm is an open question.
- What are the stack effects of the seven virtual callees? Their terminators are resolved at run time and are not in this image at this address, so the frame balance constrains only their sum. Many assignments close both epilogues and the tail transfer, so no per-callee figure is derivable here.
- What do the immediates mean? 0x201a4e50 and 0xe13ce337 are passed as one 32-bit word each to 0x006a25a0, whose low byte return is the only part the body consumes; 0x7, 0x8 and 0x21 select the three consecutive slot-0x4c calls; 0x3fbae24 is passed to both the slot-0x1c and the slot-0x54 call; 0xa and 0x1 are passed to the slot-0x13c and slot-0x134 calls. The listing says which bytes are pushed and nothing about what they mean, and no meaning is claimed here.
- What does 0x00f9e3a0 do with the receiver? It is entered with the receiver in ECX and its own body reads the receiver at +0x8d8 and +0x8dc, but that is a fact about 0x00f9e3a0 and NOT a field claim about this body's receiver: those offsets are inside a different function and are recorded here only so that a reader does not mistake them for this body's layout evidence.
- What is at 0x015fd918, and is it a pointer? The body loads it and hands it to two 0x006a25a0 calls as the register-carried value, and never writes it, so it is read-only here; its type, its owner and its lifetime are not established.
- Which class, if any, does this address belong to? R1-VFT establishes that it is a virtual member of SOME class, and that is as far as the evidence goes. This binary carries no MSVC RTTI, the record names no owning class, and identical folding means one address can be a virtual member of several classes at once, so no class identity is claimed.
