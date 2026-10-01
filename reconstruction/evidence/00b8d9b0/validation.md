# Validation 0x00b8d9b0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b06/b8d9b0_planet_record_resolve_context.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 24-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 24-instruction listing names no memory operand through any register at all and it was consumed in full by the machine parse (declared_count=24, degraded=false, unparsed=0), which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (24 of 24 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 24-instruction listing lie inside the recovered body span 0x00b8d9b0..0x00b8d9e5, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 24-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7d94b8f8507ed7f3c9adac6b97204d60b1e8bd4f4a33e561e94100e069f7e4be`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b5db4e5af8be4f3e56d35aa21349fddfb36ee6c8c00b4cf82a3bb76ac62233a6`
- Pack digest quoted by the briefing: `7d94b8f8507ed7f3c9adac6b97204d60b1e8bd4f4a33e561e94100e069f7e4be`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime write watchpoint on the singleton at 0x0167EAE4 and on the context field at +0x1F4 is required to confirm the lazy-resolution claim about 0x00c4b220, which this batch inferred from static structure only.`, `No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.`, `The concrete type of the returned handle can only be established by observing a receiver at a callsite and locating its vtable, neither of which is possible statically.`, `The tier-1/tier-2 split is a runtime-behavioural claim about which registry is populated in a given game state. A differential test must exercise at least one planet that resolves through tier 1 and one that falls through to tier 2, and observe that tier 1's cross-context write is invisible to the caller.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime write watchpoint on the singleton at 0x0167EAE4 and on the context field at +0x1F4 is required to confirm the lazy-resolution claim about 0x00c4b220, which this batch inferred from static structure only.
- Does tier 2 ever need to run in practice? Tier 1 covers records whose planet id is in the manager's registry, and 0x00bba870 already iterates a list calling this function per element, which suggests tier 1 usually succeeds. No static evidence establishes how often tier 2 is reached.
- No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.
- The briefing's canonical ledger recorded callee_count 5 and caller_count 11; both match the live xref query, with the note that 0x00bba870 calls it inside a loop rather than once.
- The concrete type of the returned handle can only be established by observing a receiver at a callsite and locating its vtable, neither of which is possible statically.
- The tier-1/tier-2 split is a runtime-behavioural claim about which registry is populated in a given game state. A differential test must exercise at least one planet that resolves through tier 1 and one that falls through to tier 2, and observe that tier 1's cross-context write is invisible to the caller.
- What class owns the singleton at 0x0167EAE4? It has a registry header at +0x184 and a lazily resolved pointer at +0x1F4, so it is at least 0x1F8 bytes. The SDK's attribution of the containing address range 0xB3D2A0-0xB3D440 to Simulator::cGamePersistenceManager is NOT adopted, because that class is ASSERT_SIZE 0x4C and 0x00b3d2a0 demonstrably returns something larger. The conflict is recorded rather than resolved.
- What is 0x00bb7940? It is a large (roughly 300-instruction) ensure-or-refresh routine with a do/while retry loop, a four-way classification of an input against the thresholds -2.0 and 2.0 (0x00bb7e3b region), four vtable dispatches and an error report carrying the constant 0x3D03F84. Its full contract was not reconstructed, so 'refresh the cache slot' is a description of its observable effect from the two callsites, not a claim about its semantics.
- What is the byte at cPlanetRecord+0x15? 0x00fee220 tests it as a short-circuit flag for the tier-2 acceptance predicate. Offset 0x15 falls inside cPlanetRecord::mName (eastl::string16 spanning 0x00-0x17), so no named member covers it. It may be a byte of an unrelated field, a deliberately overloaded test, or a decompilation artefact of a differently-typed access; nothing read here resolves it, and no meaning is claimed.
- What is the constant 0x463329E, passed to each mission's vtable slot +0x0C? It behaves as a type-acceptance query key. No SDK constant with that value exists (grepped across the ModAPI tree), so its meaning is unestablished.
- What is the returned handle's type? It is passed as a receiver and as a context pointer, but no vtable for it was located and no SDK class matches. This is the material bound on the record.
