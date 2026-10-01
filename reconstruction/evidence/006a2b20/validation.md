# Validation 0x006a2b20

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_direct_property_clear_wave14/006a2b20_direct_property_list_clear.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 39-instruction listing name the same 3 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x006a2b20; the source span names 3 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 39-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 4 displacement(s) the source span declares (0x18, 0x1c, 0x38, 0x3c) and the 0 the complete 39-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x18, 0x1c, 0x38, 0x3c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (39 of 39 instruction(s), 0 unparsed) and all 7 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 39-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 39-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `32e4f470bfede7a2bbba3cf7ed8747bbbfbd52d5e5d4d82702cd9f218cebdaad`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5569b44385ec8b6896bac5152fcbfbdf7e27a75b77f0d4bf61ff179851cc2f3a`
- Pack digest quoted by the briefing: `32e4f470bfede7a2bbba3cf7ed8747bbbfbd52d5e5d4d82702cd9f218cebdaad`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation and no indirect-caller trace were captured for 0x006a2b20, so the reachability of this body through the shared vtable 0x01408870, and the real values held at receiver+0x38 and receiver+0x3c, remain runtime gates.`, `No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408870 is a runtime gate.`, `The real body of 0x00612b20 is not reproduced here beyond its observed 0x18-stride move and its degenerate-range return. Its non-empty movement path remains unmodelled.`, `The real body of 0x00685a30 is not reproduced here beyond its 0x18-stride traversal. Its per-entry release call to 0x0093db80 on the sub-object at entry+4, taken when byte entry+0x14 has its 0x4 bit set, is out of scope for this record.`, `The real body of 0x0092cb00 is not reproduced here beyond its observed dword-fill contract. Its count word is read from receiver+0x38, whose meaning and initial value this body never establishes.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process invocation and no indirect-caller trace were captured for 0x006a2b20, so the reachability of this body through the shared vtable 0x01408870, and the real values held at receiver+0x38 and receiver+0x3c, remain runtime gates.
- No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408870 is a runtime gate.
- The concrete layout of the receiver between offsets 0x00 and 0x17, and between 0x20 and 0x37, which this body never touches.
- The identity of the receiver words at 0x18, 0x1c, 0x38 and 0x3c. The machine-derived receiver record is bounds_only and enumerates displacements, not members, so the candidate deliberately names none. A layout naming these words needs a source outside this body (the SDK header, or a writer elsewhere in the binary).
- The meaning of the pair at receiver+0x38 and receiver+0x3c. The 0x0092cb00 body fills count consecutive dwords at dest with a value word and returns dest, so the shape is a (count, destination) pair for a companion array, but whether that array is parallel to the 0x18-stride entry range, indexed by the same stride, or unrelated is not observable from this body.
- The real body and general contract of 0x0092cb00 beyond the dword fill, and of 0x00612b20 beyond the 0x18-stride move and its degenerate-range return.
- The real body of 0x00612b20 is not reproduced here beyond its observed 0x18-stride move and its degenerate-range return. Its non-empty movement path remains unmodelled.
- The real body of 0x00685a30 is not reproduced here beyond its 0x18-stride traversal. Its per-entry release call to 0x0093db80 on the sub-object at entry+4, taken when byte entry+0x14 has its 0x4 bit set, is out of scope for this record.
- The real body of 0x0092cb00 is not reproduced here beyond its observed dword-fill contract. Its count word is read from receiver+0x38, whose meaning and initial value this body never establishes.
- The release call 0x00685a30 makes per qualifying entry (0x0093db80 on the sub-object at entry+4, gated on byte entry+0x14 bit 0x4), and what that sub-object owns.
- The return-type disagreement recorded in observed_original_abi: the machine-derived envelope calls the last EAX write pointer_like while this record claims void. Resolving it needs either a caller-side use of EAX or a source outside this binary.
- Whether the byte span at receiver+0x18..0x1c is always an exact multiple of the 0x18 stride. The rewind only lands on the begin cursor when it is; for a ragged span the end cursor is rewound to the nearest lower stride boundary.
- Whether the immediate 0x0 pushed as the fill value is a null pointer or a zero fill word. The callee stores it as a dword with a repeated store, so only its 32-bit value is claimed.
- Whether the shared vtable 0x01408870 dispatches this body at a fixed slot, and which callers reach it. The record carries one vtable xref and no direct caller xref.
