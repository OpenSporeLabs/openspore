# Validation 0x005a9200

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 199-instruction listing names 8 data address(es) (0x13eb844, 0x13eb90c, 0x13ebc58, 0x15da7c4, 0x15da7c8, 0x15da7cc, 0x15da7d0, 0x15fd918) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (199 of 199 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 44 conditional branch target(s) in the complete 199-instruction listing lie inside the recovered body span 0x005a9200..0x005a94bc, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 199-instruction body names 5 indirect transfer(s): 0x005a920f dispatches slot 0x38 through the table word in EDX; 0x005a9278 dispatches slot 0x18 through the table word in EDX; 0x005a92c3 dispatches slot 0x4 through the table word in EDX; 0x005a92e3 dispatches slot 0x18 through the table word in EDX; 0x005a945e dispatches slot 0x8 through the table word in EDX; the machine parse consumed 199 of 199 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 5. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 1 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7181801f73ac2b07547d06236952d3a9a39f7586ab9987ac7408e7e15fe80bdb`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8147071f880fc73b966fbf1f295ccf7c4b7fafb4b809f37d925ef80138a11888`
- Pack digest quoted by the briefing: `7181801f73ac2b07547d06236952d3a9a39f7586ab9987ac7408e7e15fe80bdb`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace is required to confirm 0x00676ed0's dead first argument is genuinely dead in the shipping build rather than read by an inlined or patched variant.`, `A runtime trace is required to observe the actual value of [[0x015fd918]+0x3c]+0x118 at editor entry and therefore whether the mask write ever fires in the shipping configuration.`, `A runtime trace is required to read the runtime-initialised 16 bytes at 0x015da7c4 and confirm the seeded ContentValidation matches the shipped illegal-character set.`, `A runtime trace with a resolved IAppSystem vtable pointer is required to name the two notification consumers.`, `No original-process trace has ever been captured for 0x005a9200; every claim here is static. The original Cell stage has never been entered in any recorded run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace is required to confirm 0x00676ed0's dead first argument is genuinely dead in the shipping build rather than read by an inlined or patched variant.
- A runtime trace is required to observe the actual value of [[0x015fd918]+0x3c]+0x118 at editor entry and therefore whether the mask write ever fires in the shipping configuration.
- A runtime trace is required to read the runtime-initialised 16 bytes at 0x015da7c4 and confirm the seeded ContentValidation matches the shipped illegal-character set.
- A runtime trace with a resolved IAppSystem vtable pointer is required to name the two notification consumers.
- Is 0x00676ed0 really SetProgressFlags? Its class attribution is solid; the method attribution within the class is a body-shape inference and the SDK's own address for SetProgressFlags resolves to a sibling function.
- No original-process trace has ever been captured for 0x005a9200; every claim here is static. The original Cell stage has never been entered in any recorded run.
- The three remaining callers (0x00b1dee0, 0x00d3c6a0, 0x00d43e30) and the second site in 0x00e84600 were not disassembled.
- The values of 0x015da7c4..0x015da7d0 and of 0x015fd918 are runtime state; the file image is zero, so the seeded ContentValidation and the gate outcome cannot be predicted statically.
- What are the ids 0xb03bc30c and 0x00e11332? 0x00e11332 sits one below the SDK's kMsgSetGameModeByName = 0x00E11333, which is a family resemblance in the same message-id space and is not claimed as an identity.
- What class is the 0x40-byte App object allocated at 0x005a9289? Its vtable 0x013eb844 is IMessageRC-shaped (dtor/AddRef/Release) and is followed in .rdata by the literals 'queuing %ls for bake\n' and 'No key -- you need to save the model first.\n', which places it in a model-baking code path, but no class identity is established.
- What does the achievement/progress key 0x00d082675a denote, and what do bit indices 5..15 mean? No cross-reference or listener for these was located.
- What interface is the singleton at 0x015fd890? It has one writer (0x0067deb0) with no callers and no located vtable, and the observed four-argument call at slot +0x18 does not fit the SDK's IAppSystem. Both notifications are therefore identified only by their raw ids 0xb03bc30c and 0x00e11332.
- What is 0x00001003, the discarded probe key? Its answer is thrown away, so either the probe is dead in this build or its side effect (0x008027e0) is the point; the evidence does not distinguish these.
- What is the id 0x00dbdba1 stored at msg+0x08, and what reads it back? No reader of msg+0x08 was located.
