# Validation 0x00f967d0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 27-instruction listing name the same 3 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x00f967d0; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 27-instruction listing names 1 data address(es) (0x140f334) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 27-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 1 displacement(s) (0x20c), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
| CONSTANTS | `WARN` | `partial` | the machine listing is not fully parsed: 27 of 27 instruction(s) consumed, degraded=True, unparsed=1 |
| CONTROL FLOW | `PASS` | `complete` | the complete 27-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 27-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `WARN` | `partial` | return type differs or is semantically renamed; review required |

Static evidence basis: 8 of 8 static checks evaluated, 4 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ad0e9bf260b971ee4e00119e9256c99b36952b388dc721357c1c39e902f74a79`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `26bdf89a3c52581aaca684406ce77fe23b98b6343df9558681ccb19893230fdc`
- Pack digest quoted by the briefing: `ad0e9bf260b971ee4e00119e9256c99b36952b388dc721357c1c39e902f74a79`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Conditions are listed in full under runtime_gate.conditions; the shortest form is that a live receiver of this vtable's class, with a non-null word at +0x20c, must be driven through both floor arms and through a NaN, and the three callee returns plus the three out-pointer addresses must be captured at the call sites.`, `RUNTIME is required and gated at 0: no trace was run and no differential evidence was gathered for this VA.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Conditions are listed in full under runtime_gate.conditions; the shortest form is that a live receiver of this vtable's class, with a non-null word at +0x20c, must be driven through both floor arms and through a NaN, and the three callee returns plus the three out-pointer addresses must be captured at the call sites.
- RUNTIME is required and gated at 0: no trace was run and no differential evidence was gathered for this VA.
- The class that owns vtable 0x01490be8 is not established. ghidra_function.namespace and ghidra_function.sdk_name are null for this VA, and the sibling package that read the same table could not establish the owner either. The receiver is therefore an opaque 0x210-byte run and no member is named.
- The meaning of the three values is not established. The listing fixes where each comes from -- a scaled, floored float and the two words at the pointee's +0x5c0 and +0x5c4 -- and nothing fixes what any of them is for. The two words are one dword apart and are read by two separate two-instruction accessors, which is the shape of an adjacent pair of counters, a size and an alignment, or a key and a value; no record available here chooses between those.
- The one unparsed line in the derived ABI record (abstained_because: 'unparsed_lines_present: 1 line(s) matched no grammar rule') was not located. All 27 instructions of the listing are accounted for by the model and the frame walk balances, so no reconstruction claim rests on it, but which line the tool could not parse is not known.
- What the word at receiver+0x20c points to is not established beyond the three displacements its consumers read (+0x08, +0x5c0, +0x5c4) and the fact that it is a pointer. Its type, its owner, whether it is ever null and whether the pointee is the same object every call are all open; nothing in this body or in the three callees says.
- Whether the multiplier at 0x0140f334 is a constant, a tunable or a per-instance scale is not established. It is a .rdata word, so it is a compile-time constant as far as this image is concerned, but the body only reads it and nothing here says whether a writer exists elsewhere in the binary.
- Why the pointer is re-loaded three times is not established. The listing shows three identical MOVs with no write to the receiver between them, so on any ordinary execution all three loads return the same value and the re-reads are redundant. The model reproduces them because they are in the listing and because the difference is observable if a callee ever changed the word -- but no such writer is known, so whether the redundancy is deliberate (a debug or thread-safety concern) or a compiler artefact is open.
