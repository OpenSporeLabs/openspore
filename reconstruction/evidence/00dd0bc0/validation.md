# Validation 0x00dd0bc0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00dd0bc0/sw1_00dd0bc0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 14-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00dd0bc0; the source span names 2 of them and no others |
| GLOBALS | `WARN` | `partial` | 3 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 2 displacement(s) the source span declares (0x10, 0x14) and the 0 the complete 14-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x0, 0x10, 0x14), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (14 of 14 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 14-instruction listing lie inside the recovered body span 0x00dd0bc0..0x00dd0bef, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 14-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `dc43df67a225809a0d4ed80807ec77201684dfc6add18a6586f2703e2c73d191`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `78318bcd84c08a4169c987ffb6b58b7c6d9b70344914cd7d56c4bdff063407ce`
- Pack digest quoted by the briefing: `dc43df67a225809a0d4ed80807ec77201684dfc6add18a6586f2703e2c73d191`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is 0x00641340, the word immediately after this body in both tables at 0x0147c9f8+0x04 and 0x0147ca70+0x54, the class's vector deleting destructor? Its 18 bytes read as `MOV EAX,[ECX] / MOV EDX,[ESP+4] / MOV EAX,[EAX+0xa0] / PUSH 0 / PUSH EDX / CALL EAX / RET 0x4`, i.e. it reads the receiver's own dispatch word, takes a slot at +0xa0 of it and calls it with the flag and a zero. That is the shape of a two-argument thiscall through a slot, which is what MSVC emits for a vector deleting destructor, and its adjacency to this body in two separate tables is what such a pair looks like. It is NOT claimed: 0x00641340 is a different VA, outside this target, and nothing in this package's scope was used to settle it.
- Is the flag a one-byte argument or a four-byte one? RET 0x4 pops four bytes, so the SLOT is four bytes wide; the TEST reads one byte of it, and both Ghidra's `Stack[0x4]:1` and the record's `sizes: [1]` call the argument one byte. This package declares the parameter `std::uint8_t` because that is what is read. It must be said plainly that the choice is NOT observable from this body: bit 0 of the low byte IS bit 0 of the four-byte slot, so no input whatsoever distinguishes a one-byte read from a four-byte read of bit 0, and a reconstruction declaring the parameter `int` would be behaviourally identical here. The four-byte slot is a fact; the one-byte reading of it is a fact; what a caller actually pushes is not established by this body.
- Is the ten-byte 0xcc run at 0x00dd0bf2 the whole gap to the next function, or does the image carry a second entry inside it? The bytes are ten 0xcc and Ghidra's body_end is 0x00dd0bf1, so the two agree that there is no second entry -- but no disassembly of the padding was requested, and MSVC's padding is padding, so this is treated as settled.
- Not fixable from this package, reported not chased: GLOBALS and EVIDENCE COVERAGE are structurally WARN. See validation.expected_reasons and known_blockers.
- The derived ABI record and the listing disagree on the RETURN CLASSIFICATION, and the listing wins. abi_derived.return is {register EAX, register_class aggregate_unknown, type null} and the persisted projection renders it as return_semantics 'unclassified_in_EAX'. The listing is unambiguous: 0x00dd0bec `MOV EAX,ESI` on both arms, with ESI the receiver alias, so the C type is a pointer to the receiver. A register-to-register move of an aliased pointer is the simplest shape there is for a width classifier, so this looks like a classifier limitation rather than a listing problem -- but it is recorded as a disagreement, not corrected, because no record in this repository adjudicates it and the validator reads the record. It costs the RETURN SEMANTICS check a PASS it would otherwise earn.
- The record's vtables list (0x0147c9e8, 0x0147ca30, 0x0147ca70) does not include 0x0147c9f8, which IS the constant this body stores at receiver+0x00 and which the image shows beginning with this body's own address. Either the collector's table-start heuristic missed it or it classifies 0x0147c9f8 differently. This package did not resolve it: the constant was taken from the instruction's immediate and the table's contents from the image, and the record's list is reported unchanged. It is worth the integrator's attention because three of the four table addresses this body is associated with would then be mis-attributed.
- What class is this? The three stored constants, the two adjusting thunks that subtract 0x10 and 0x14, and the base destructor's identical three-store prologue together establish a class with one primary subobject at +0x00 and two further subobjects at +0x10 and +0x14 -- and nothing beyond that. No record in this repository names the class, no SDK symbol was recovered for 0x00dd0bc0 (ghidra_function.sdk_name is null), and the binary has no MSVC RTTI. The model therefore names no class and declares no member, and the `OpaqueSporepediaAsset` type name is a placeholder for 'the object this destructor runs on' and is NOT a claim that the SDK has a type of that name.
- Who calls this body, and with what flag? There is no direct caller anywhere in the image -- all four inbound xrefs are two vtable slots and two adjusting thunks -- so every invocation is a virtual call through a table, and the flag value each caller passes is not recoverable from this body. The ordinary C++ convention is a compiler-generated `delete` expression passing 1, but that is a convention, not a measurement, and no trace in this repository would settle it. This is also the reason the runtime gate below asks for a specific flag rather than just a specific receiver.
