# Validation 0x00a649a0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00a649a0; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 2-instruction listing names through ECX (0x6c) are all within the machine-derived receiver bounds (0x6c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a7b42ecb593cd56ff7fe5374debd6d93d061b6ee46d94839df450da4cd9d8ae6`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5ce49f0bceb2bf89dca5e2c4a9903448d1fd7e4afe0cb3f7b8df164b9cda1d48`
- Pack digest quoted by the briefing: `a7b42ecb593cd56ff7fe5374debd6d93d061b6ee46d94839df450da4cd9d8ae6`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The class hierarchy this accessor belongs to. 0x005c0dd0 sits in the same vtable run 0x00a5 bytes away and appears in the same residual-unknown row, but no reconstruction package for it exists yet, so the shared receiver layout is unconfirmed from the other side.
- The vtable slot number, and therefore what a caller of this slot is asking for. The entry sits 0x88 = 34 dwords past the head at 0x013ff648, but whether that head dword is slot 0 is the convention this target does not settle, so the package declares no slot. Resolving it needs the RTTI complete-object-locator question settled for the Sporepedia vtable family first.
- What the 4-byte word at receiver+0x6c is. The body, the seven verified vtable installations and the single caller give no name, no type and no nullability, and abi_derived's `pointer_like_in_EAX` is an INFERRED register class rather than a type -- recorded on its own in observed_original_abi.machine_return_class and deliberately kept out of observed_original_abi.return_type, since a register-class phrase is not a C or C++ type and no name in this package is derived from it. Whether the value really is pointer-like is itself open: nothing in these 4 bytes ever dereferences it, and the one caller stores it as an ordinary integer word. docs/analysis/residual-unknown-priority.md groups 0x00a649a0 with 0x005507a0, 0x005508c0, 0x005c0dd0 and 0x00ff3f00 as 'Local asset field projection' and says the open task is to bind one receiver field to a fixture-backed local metadata contract. Settling the name needs the class it belongs to, which needs RTTI this binary does not carry.
- Whether the 4 bytes at +0x6c and the 4 bytes at +0x70 (which 0x00a649a8 reads, the next function in the image) belong to the same logical record. The adjacency is a fact and the grouping is a guess; nothing in this set joins them.
- Whether the four neighbouring vtable runs the index lists (0x0147c9e8, 0x0147ca30, 0x0147ca70, 0x0147caf8 and the other heads in referenced_by_vtables) install a different function at the same position, or a different slot of this one. Only 7 of the 14 listed heads contain a dword equal to 0x00a649a0, and the three re-read for this package are among those 7; the rest were not read.
