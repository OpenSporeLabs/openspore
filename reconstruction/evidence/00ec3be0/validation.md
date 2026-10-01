# Validation 0x00ec3be0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 58-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00ec3be0; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 58-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 5 displacement(s) the source span declares (0x78, 0x79, 0x7a, 0x7b, 0x7c) and the 0 the complete 58-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x78, 0x79, 0x7a, 0x7b, 0x7c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (58 of 58 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 11 conditional branch target(s) in the complete 58-instruction listing lie inside the recovered body span 0x00ec3be0..0x00ec3c8e, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 58-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `bcc8383bcf8c83b980d9d12f12245f2962c3ff322cbee4a2dbd9c399efde207d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `4914cded4a22ff1990338d80656a00ab5e0455e1b657ec050fae6883bf228750`
- Pack digest quoted by the briefing: `bcc8383bcf8c83b980d9d12f12245f2962c3ff322cbee4a2dbd9c399efde207d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- EVIDENCE COVERAGE is expected to stay WARN at 14 of 17 static categories. This pack reports availability unavailable/MISSING for callees_dependencies, callers_dependencies, contradictions, external_callees, globals, runtime and types, and validate derives the check purely from that field. Nothing in a source file or a sidecar can move it.
- RETURN SEMANTICS is expected to stay WARN and no source edit can move it. The machine ABI envelope names EAX, classifies it aggregate_unknown, sets void_possible false, and the body contains a CALL at 0x00ec3be9 -- which evidence_returns treats as defeating a width claim on its own. So the dimension reports UNCLASSIFIED, which never passes, whatever the reconstructed return type says. The declared void is the honest reading of the listing and the decompilation; it just cannot be corroborated by this pack's evidence.
- The ABI envelope's stack_arguments entry for entry_ESP+0x4 carries read: false while obs-0003 in the same envelope is a STACK_SLOT_READ at 0x00ec3be1 with resolved true and size 4. The bytes plainly read that slot (8B 74 24 08) and push it again at 0x00ec3be6, and the model follows the bytes. The two fields of one record disagree and I could not determine which the inference meant; it does not affect the reconstruction, only the record's self-consistency.
- What 0x00642530 does to the receiver when this body has already stored its flag. The two bodies are siblings over the same record and the same type hash, and the call precedes the flag write on every path, so any order-dependence between the flag and whatever the callee leaves at 0x28..0x38 would be invisible in this body alone. Not resolvable from either listing.
- What the five hashed key ids are, and therefore what the five flag bytes mean. 0x15e8afc8, 0x5a3584a7, 0xb91fba14, 0xd22f5e35 and 0xdb4675dd are 32-bit hashed property names; no record in this repository maps any of them to a string, and this package will not invent a preimage. The C++ property name/ID vocabulary that would resolve them lives outside the binary. The same applies to the type hash 0x2e1a75d, which the sibling callee 0x00642530 also compares against and which is therefore a real constant of this vocabulary rather than a coincidence -- but still unnamed here.
- Whether the five flag bytes and the flags 0x00642530 writes are the same kind of thing. This body writes five CONSECUTIVE bytes at 0x78..0x7c; the callee writes a dword at 0x28 and reads/writes 0x2c, 0x30, 0x34 and 0x38. Nothing in either body establishes a type or a layout, so this package asserts neither a five-bool block nor any relationship between the two groups.
- Whether the object is larger than 0x80. This body never reads a receiver byte and never writes past 0x7c, and 0x00642530 reaches only +0x38, so 0x80 is a lower bound derived from two bodies and not a size. The real class extends past 0x7c -- five consecutive flag bytes at the very top of a type that other members live below is unusual -- but no record here gives the size.
- Whether this VA should be reconstructed at all as an independent target. The triage cluster is sporepedia-online and the frontier reason is 'no_open_internal_callees' with role 'independent', and the only reference to the body is a table slot -- so the natural caller is a virtual dispatch from elsewhere and the body has no static caller to check it against. The 0x014890f4 table is the place to start if a caller-side reconstruction is ever wanted.
- Why the five ids are sorted into an unsigned binary search tree rather than a switch, and whether the compiler chose the shape or the source did. The tree is perfectly balanced as written (1 pivot, 2 below, 3 above) which is what an MSVC switch over a sparse 32-bit hash compiles to; that is a plausible reading of the shape, not a claim about the original source, and nothing here depends on it.
