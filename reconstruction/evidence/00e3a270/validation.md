# Validation 0x00e3a270

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
| GLOBALS | `WARN` | `partial` | global references are recorded but they are reconstruction-authored; the data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 5 data reference row(s) out of 0x00e3a270 over 5 distinct address(es); 5 of them name writable storage (0x01654c00, 0x01654c01, 0x01654c02, 0x01654c04, 0x01654c05), which is where a mutable global can live; segment breakdown: .data=5; access modes recorded: 5 other; no complete listing is available for a second machine side |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 2 type(s) |
| CONSTANTS | `NOT_AVAILABLE` | `none` | no constant evidence available |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no complete listing is collected |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no machine dispatch evidence is collected for this target; the xref export records 0 vtable reference(s) and the record associates 0 vtable(s), which are not independent of each other |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 1 of 8 static checks evaluated, 0 passed, 7 had no evidence to evaluate; 8 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 8 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `PERSISTED`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b21fa705a9260c4b0b2acfd1c646ff5e2333e9e4e39ca14643906732b4e5315d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `90912476df884fe4fb82e7c6de236426c41d173b91d01524744475184aa7dab7`
- Pack digest quoted by the briefing: `b21fa705a9260c4b0b2acfd1c646ff5e2333e9e4e39ca14643906732b4e5315d`

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
