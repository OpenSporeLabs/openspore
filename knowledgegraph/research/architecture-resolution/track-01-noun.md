# Track 01 — noun-manager slots

## Result

**Classification:** `ARCHITECTURE_CHANGING`  
**Resolution:** partial static resolution; aliasing and global publication/lifecycle remain open. The two noun-slot globals must not be merged. Runtime equality was not observed.

## Scope and method

Read-only Ghidra analysis used explicit program `SporeApp.exe`. No Ghidra mutation, source implementation, runtime/Wine experiment, `SPORE/` access, `knowledgegraph/spore.db` access, or historical-artifact modification was performed. No subagent interface was exposed; three independent evidence lanes were executed in parallel: Ghidra decomp/callers-callees, Ghidra structures/globals/xrefs/teardown, and historical/community/runtime evidence. `followup-03-root-publication.{json,md}` was incorporated for physical-alias rejection and bounded publication uncertainty.

## Nine-step adversarial record

| Step | Predictions | For / against | Independence vs repetition | Separator and result |
|---|---|---|---|---|
| 1 | Enumerate permanent alias, physical alias, phase rebinding, distinct publication, generic context, receiver, lookup, ownership, and cache hypotheses | Broader set retained; no fan-in shortcut | Prior singleton wording is not a new hypothesis or proof | Physical storage/value equality and exact-find/lower-bound separated |
| 2 | State falsifiable writer, equality, phase, field-use, and key-check predictions | Predictions remain testable without selecting a runtime outcome | Predictions derive from ABI/layout, not copied conclusions | Runtime equality remains the unperformed separator |
| 3 | Collect direct Ghidra bodies, xrefs, structures, and lifecycle | Accessors, `bff2d0` receiver, noun fields, map helpers supported | Fresh Ghidra evidence is independent of historical summaries | Instruction-level chains and direct loads recovered |
| 4 | Incorporate followup-03 without counting derivatives as fresh proof | Physical alias rejected; value/publication left open | Followup-03 is provenance/corroboration, not runtime proof | Distinct words versus unresolved values |
| 5 | Mark support and contradiction for every hypothesis | Generic context, special receiver, exact-find, physical alias rejected; value aliases remain possible | Negative searches are bounded, not universal | Rejected claims narrowed; alternatives preserved |
| 6 | Audit repeated assumptions | Singleton wording, high fan-in, and “five callbacks” are not equality/ABI proof | Direct bodies, layouts, and scans are independent; historical repetition is one source family | Assumption echoes quarantined |
| 7 | Perform smallest separators | Direct noun reads, `DAT_016dc0fc` chain, and lower-bound body are separating | Direct observations are independent bounded evidence | Physical storage and receiver provenance separated; value equality not closed |
| 8 | Record runtime feasibility | Runtime could close equality, phase, liveness, and publication | No runtime evidence is promoted to proof | Not performed; unresolved, not negative |
| 9 | Run architecture-dependence test and freeze safe semantics | Separate opaque handles are safe under all surviving outcomes; they do not assert runtime inequality | Decision follows uncertainty, not repeated singleton assumption | Top-level classification remains `ARCHITECTURE_CHANGING` |

## Competing hypotheses

| ID | Hypothesis | Status | Decisive evidence |
|---|---|---|---|
| H1 | `DAT_0167eae0` and `DAT_0167eb60` always publish the same manager instance | Unresolved, unsupported as fact | One direct read per global; no writer/equality recovered in bounded surfaces; value equality remains open |
| H2 | The two slots are phase-specific, stale, or independently published | Plausible, unproven | Distinct globals and separate consumer paths; bounded negative search does not close publication |
| H3 | `0x00b3d300` is an alternate noun-manager accessor; `0x00b3d400` is canonical | Supported with alias limit | Exact getter bodies plus `0x00b3d300 -> 0x00b21340` field use |
| H4 | `0x00b3d300` is only a generic context/service locator | Rejected | `0x00bff408/0x00bff426/0x00bff428` passes its result into noun data lookup |
| H5 | `0x01002bd0` returns one of the noun slots | Rejected | It returns distinct `DAT_016dc0fc`; exact `0x00bff3ad..0x00bff3b4` chain |
| H6 | `0x00e5c780` is exact find | Rejected | Ordered lower-bound plus end-sentinel-only check in `0x00b21340` |
| H7 | The two noun words are physically aliased | Rejected | Distinct four-byte storage; physical alias rejection from followup-03 |
| H8 | An opaque/common publisher can value-alias both words | Plausible generic mechanism, not identified | Bounded scans recover no concrete writer, but do not exclude opaque/runtime/bulk publication |
| H9 | Inspected noun lifecycle directly publishes/unpublishes both roots | Unsupported for inspected paths; global absence not proven | Record/map teardown is field-owned and has no recovered target-word xref |

## Smallest separating observations

1. **Noun-slot publication scan:** Ghidra found exactly one direct read for each noun-slot global:
   - `0x00b3d300: mov eax,[0x0167eae0]`
   - `0x00b3d400: mov eax,[0x0167eb60]`
   No direct writer, equality check, second publication site, or static pointer initializer was recovered in the analyzed surfaces. The loaded `.data` words are zero. This proves distinct physical storage and accessor mechanics, not runtime inequality; opaque, external, loader/runtime, and bulk publication remain possible.
2. **Receiver window:** `0x01002bd0` is `mov eax,[0x016dc0fc]; ret`. At `0x00bff3ad`, `0x00bff3b2`, and `0x00bff3b4`, `0x00bff2d0` calls it, moves the result to `ECX`, and calls `0x00b1fdb0`. This receiver is not either noun-slot global.
3. **Lookup contract:** `0x00e5c780` returns the first node whose unsigned key is not below the requested key, or the map end sentinel. `0x00b21340` checks only the end sentinel and does not compare the returned key.

## Accessor, ownership, and slot identity

- `0x00b3d300` returns raw `DAT_0167eae0`; `0x00b3d400` is named `Simulator::cGameNounManager::Get` and returns raw `DAT_0167eb60`.
- Both are six-byte borrowed loaders: no validation, allocation, `AddRef`, `Release`, write, lock, or ownership transfer.
- `DAT_0167eae0` is strongly cGameNounManager-compatible because `0x00b3d300`'s return is passed to `0x00b21340`, which uses `this+0x78` (`mNouns`) and `this+0x98` (`mNounMap`).
- The two noun-slot words are physically distinct; physical aliasing is rejected. Their runtime values may still be equal, unequal, null, or phase-rebound because publication/value equality remain unresolved. Shared noun consumers do not prove shared storage.
- Separate opaque noun-root handles are a safe interim design under uncertainty and do not assert runtime inequality. A single canonical-slot model is unsafe until publication and runtime equality are observed.

## `0x00b21340` lookup/materialization

Fresh Ghidra decompilation shows the actual implementation takes `ECX` plus four callback pointers and a `uint32_t` noun ID:

1. Lower-bound lookup in the receiver's noun map through `0x00e5c780`.
2. End sentinel only: call the create callback and invoke `0x00ba8420` for insertion.
3. Non-end successor: load its payload without exact-key equality.
4. If `tGameDataVectorT::needsUpdate` is nonzero, call the clear callback.
5. Walk receiver `mNouns` at `+0x78`; call filter `(object,nounID)`; append matches through add.
6. Clear `needsUpdate` and return the raw vector record.

The historical SDK-named address `0x00b212d0` is boundary-contaminated/split in the committed analysis; the independent implementation body is `0x00b21340`. The current ModAPI header and docs corroborate four callbacks plus noun ID, not five callbacks.

## Map allocation and invalidation

- `0x00ba8420` is a generic ordered-map insertion/try-emplace helper.
- `0x00ba83a0` allocates a `0x18`-byte node with `0x00f473a0`, copies the key/value pair, links/rebalances it, and increments the map count.
- Equal keys return an existing node with `inserted=false`; insertion returns `inserted=true`. `0x00b21340` does not use the inserted flag.
- `0x00b21410` finds a noun object's map node and calls `0x01045590`, which unlinks/decrements the map, releases the payload through virtual slot `+4`, frees the node, and clears owner `+0x70` when matching.
- `0x00b25fe0` and related noun cleanup paths iterate records and invoke erase/cleanup helpers. This is record teardown, not noun-slot publication invalidation.
- The producer-side `needsUpdate` writer, indirect slot publication, failure/exception behavior, and locking/reentrancy remain unresolved. The create callback result versus the separate map-node allocation is not ownership-closed.
- followup-03's direct, exact-literal, table/base, bounded P-code, accessor-pair, and inspected-lifecycle searches recovered no concrete noun-slot writer or equality operation. This is a bounded negative, not proof that opaque, external, loader/runtime, unresolved, or bulk publication is absent.

## `0x00bff2d0` receiver provenance

- `0x01002bd0` returns `DAT_016dc0fc`, a distinct Simulator/context parent global.
- `0x00fda750` allocates a `0xf0` Simulator object, stores it at parent `+0x15c`, and constructs it through `0x010066e0`.
- `0x010066e0` publishes the parent in `DAT_016dc0fc`, allocates a `0x108` child through `0x00f473a0`, constructs it with `0x00fe68a0`, and stores it at parent `+0x30`.
- `0x01006880` releases that child, clears `DAT_016dc0fc`, and tears down parent fields. `0x010077c0` calls the destructor and conditionally frees the parent through `0x00f47380`.
- Therefore `0x00bff2d0:0x00bff3b4` is a separate parent/context receiver, not `DAT_0167eae0` or `DAT_0167eb60`. Its exact class and the exact identity of its `+0x54` field remain bounded.

`0x00b1fdb0` returns raw `receiver+0x54`. `0x00b1fd50` implements reference-managed replacement: new-value virtual `+0`, store, old-value virtual `+4`. This is strongly compatible with `cGameNounManager::mpAvatar`, but the special `DAT_016dc0fc` receiver must not be equated with either noun slot without new evidence.

## Independence and repetition

Fresh Ghidra decompilation, disassembly, structure layouts, global audits, xrefs, memory inspection, and a read-only instruction reference scan independently support the mechanics above. followup-03 independently adds physical-alias rejection and bounded direct/table/computed/lifecycle negative observations, while preserving value-alias and publication uncertainty. Historical artifacts preserve the same contradiction but do not add equality proof. Community documentation supports noun-registry, avatar, and four-callback concepts only; it is not ABI proof. Repeated “same instance” wording and high fan-in are assumption echoes, not separating evidence. The “five noun-data callbacks” wording is a counting error: the binary and current header show four callbacks plus noun ID.

## Architecture decision

The distinction is architecture-changing. Physical aliasing is rejected, but value aliasing and publication remain unresolved. OpenSpore must preserve separate opaque noun-root handles as a safe interim design; that design does not claim runtime pointers are unequal. It cannot assume one singleton, shared noun storage, or canonical-slot publication order. It may safely defer runtime equality and global teardown characterization, but it must not merge `DAT_0167eae0` with `DAT_0167eb60`, route the `0x01002bd0` receiver through either slot, or replace the observed lower-bound contract with exact find.

## References and limitations

- `knowledgegraph/research/root-closure/followup-global-slots.md:11-22,39-61,102-143,199-245`
- `knowledgegraph/research/root-closure/followup-receiver-provenance.md:15-20,24-40,44-86,88-141`
- `knowledgegraph/research/root-closure/followup-noun-boundary.md:7-14,53-82,84-103,176-184`
- `knowledgegraph/research/root-closure/root-closure-f0e310e0.json:112-166,1363-1393`
- `knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json:600-789`
- `knowledgegraph/research/root-closure/followup-global-slots.json:55-120`
- `knowledgegraph/research/root-closure/followup-receiver-provenance.json:132-139,352-395`
- `knowledgegraph/research/architecture-resolution/followup-03-root-publication.json:103-149,150-186,329-412`
- `knowledgegraph/research/architecture-resolution/followup-03-root-publication.md:26-91,107-117`
- `/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/SubSystem/GameNounManager.h:36-152`
- `https://modapi-docs.sporecommunity.com/class_simulator_1_1c_game_noun_manager.html`

No runtime evidence was available. No source implementation was performed. The full evidence ledger, hypothesis predictions, blocker list, and confidence fields are in `knowledgegraph/research/architecture-resolution/track-01-noun.json`.
