# Validation 0x00e3a400

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 172-instruction listing names 5 data address(es) (0x1654c00, 0x1654c01, 0x1654c02, 0x1654c04, 0x1654c05) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 172-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x324), all of which the record accounts for or the listing is the better witness on; the 172-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=172, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x324) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x324), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (172 of 172 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 42 conditional branch target(s) in the complete 172-instruction listing lie inside the recovered body span 0x00e3a270..0x00e3a568, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 172-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f5d3cf5959ff0de2bf6a93e97691d501f5fd3d756feb12886e385e5ffeb8118c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `a359d7ba375b7c0b3841a33624caebc5b95d449b164c1488600b932b3e9612b9`
- Pack digest quoted by the briefing: `f5d3cf5959ff0de2bf6a93e97691d501f5fd3d756feb12886e385e5ffeb8118c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- ABI/CALLS/RETURN SEMANTICS are NOT_AVAILABLE with the detail 'target source span is not deterministically available', and the cause is NOT the reconstruction source. validate._target_span binds a span only through record['name'] or record['normalized_symbol'] (tools/reconstruction_tooling/validate.py:242-291), and the index record for 0x00e3a400 carries BOTH AS NULL: the triage row knowledgegraph/triage/queue-f0e310e0-v6.json has name=null for this VA (source: unknown-high-investigation) and the manifest has no functions[] row for it, so reconstruction_knowledge.build_index projects name=null. No staging-side edit can supply it -- verified by adding a name/normalized_symbol key to THIS sidecar and rebuilding the index in process: the record stayed null, because build_index reads the name from the manifest and the triage queue only, never from a metadata sidecar. Both of those are campaign-owned read paths (docs/tooling/concurrency.md: 'No command overwrites ... the manifest'), so a worker cannot fix this and a validator must not be weakened to accommodate it. Injected in process as a diagnostic ONLY (validate._record monkeypatched, no file or tool edited), a name of re_00e3a400 makes the span resolve and flips ABI, CONSTANTS, CONTROL FLOW and RETURN SEMANTICS to PASS, which confirms the staged source is itself sound and correctly named; CALLS still FAILs for the separate interior-address reason already recorded above, and GLOBALS stays WARN because the five immediates 0x1654c00..0x1654c05 fall in the validator's 0x1300000..0x02000000 data window while being operand immediates and not addresses.
- CALLS: the xref export is keyed by function entry and 0x00e3a400 is an interior address, so the export has no row for it and validate's source-vs-xref arm reports FAIL against the one address-named callee in the span. The call is real and is corroborated three ways: by the listing (CALL 0x00e39420 at 0x00e3a2da, a4fe, a560), by the export's three rows for the containing function's entry 0x00e3a270 at exactly those callsites, and by the callee's own 47 bytes. The FAIL is a property of the target address. Reported, not worked around: naming the callee without the address suffix would only move the FAIL to the machine-vs-machine arm, and omitting the call would falsify the body.
- The class name and the object's real size. The triage subsystem says 'Simulator' and the type is named Simulator for readability, but SporeApp.exe carries no MSVC RTTI, no persisted symbol names this address and no record associates a type with it. 0x330 is a lower bound from this body's own accesses; the only caller passes its own EBP, so the real object is at least as large as that and nothing here bounds it above.
- The meaning of the value the body returns. The machine classifies EAX's content as aggregate_unknown, the body writes it four different ways, and the only caller in the binary does not read it. The reconstruction reproduces the register's content per path and claims nothing about meaning; if a caller outside this binary exists, its use of the value is unknown here.
- What the nineteen receiver displacements MEAN. Three of them (0x29c, 0x2b4, 0x2c0) are 12-byte destinations a helper fills; 0x2a8/0x2ac/0x2b0 and 0x2cc/0x2d0/0x2d4 are triples each written by one arm; 0x314/0x318, 0x31c/0x320 and 0x324/0x328 are pairs one of whose members is written only while the other is zero; and 0x32c takes five of the six consecutive values 0x1654c00..0x1654c05. NONE of that is named as a field, because the machine-derived receiver record is bounds_only and no machine record anywhere in this repository names a member at any displacement.
- What the six tag immediates 0x1654c00..0x1654c05 denote, and why 0x1654c03 never appears. The guard (CMP [ECX+0x32c],-1 / JNZ skip) and the values are reproduced exactly; the meaning is not claimed. Note also that 0x1654c00 is the one tag written UNCONDITIONALLY, and it is written by the arm that also stores 0x308 -- an asymmetry that is reproduced and not explained.
- What the twenty-seven selector values are hashes OF. They are the immediates of twenty-seven CMP EAX,<imm32> and nothing in this repository inverts any of them, so no arm is named for a property and no preimage is claimed.
- Whether the three lazy pairs really are one quantity each, or three unrelated coincidences of adjacency. The secondary store is unconditional and the primary is conditional in all three, and the primary of one pair (0x31c) is written unconditionally by a different arm, which is what a defaulting-eager-setter pair would look like -- but the byte listing does not prove the pairing and no other evidence here does either. LABELLED INFERRED, not asserted.
- Why the arms at 0x00e3a3e2 and 0x00e3a517 write the same three block words in DIFFERENT orders (swapped middle pair at 0x2ac/0x2a8 versus ascending at 0x2d0/0x2cc/0x2d4), and why the arm at 0x00e3a517 is the only one of the ten with a null test. Both are reproduced exactly and neither is explained; a plausible reading is that the two are different quantities of the same shape, and that is labelled INFERRED, not asserted.
