# Blocker C — Adversarial Critique

**Review target:** `knowledgegraph/research/architecture-blockers/blocker-c-primary.md`
**Corroborating material:** `docs/analysis/serialization-model.md`; `knowledgegraph/research/architecture-resolution/track-04-persistence.md`; `track-03-mode.md`; `followup-06-persistence.md`; `track-08-cell-lifecycle.md`; `track-06-forwarded-state.md`; `followup-02-forwarded-state.md`; `followup-04-cell-boundary.md`
**Scope:** static claims and clean-room design implications only. No original-wire, runtime, `SPORE/`, Ghidra, or canonical-SQLite evidence is added.

## Bottom line

Blocker C is directionally conservative, but its “minimum semantic model” is stronger than its evidence warrants. The static evidence supports several useful seams:

- `PropertyList` has explicit local-entry stream operations.
- `ClassSerializer` has callback-driven class/attribute serialization machinery.
- `cSavedGameHeader` and `cCellSerializableData` participate in serializer-vtable paths.
- App mode lifecycle and Simulator strategy state are separate axes.
- Selected save/load paths use temporary-file and replacement helpers.

It does **not** establish a recovered universal save document, a durable object-reference scheme, a class/object registry on the save path, parent-list wire semantics, automatic mode persistence, manager ownership of the save/load candidates, complete `cCellSerializableData` field survival, or an original transaction protocol.

The safe conclusion is therefore: **OpenSpore may implement its own explicit, deterministic persistence and handoff seams, but it may not present the proposed graph as the minimum original architecture or use it to justify compatibility claims.** The proposed model is a reasonable design hypothesis, not the smallest proven semantic model.

## Highest-risk contradictions and overstatements

### AC-01 — Same class ID is incompatible with the stated class-identity interpretation

The primary describes `ClassSerializer` as using class identity before field dispatch (`blocker-c-primary.md:137-149,167-175,256-260`). However, the header and the Cell serializable wrapper are both reported with class ID `0x01A80D26` (`blocker-c-primary.md:193-199`; `track-04-persistence.md:56-58,126-127`).

That is a direct tension. If `0x01A80D26` is a globally unique class/schema ID, header and Cell records cannot be distinct classes with the same value. Possible explanations remain open:

1. the value is a serializer family, base-class, or default ID;
2. the descriptor/table pointer is the actual class discriminator;
3. class IDs are scoped by another registry or record type;
4. the decompiler interpretation of the argument is wrong;
5. the Cell and header wrappers share a generic serializer class and distinguish content elsewhere.

The primary must not simultaneously call this a class ID, make class mismatch rejection a core invariant, and propose a `ClassId` component of a universal `ObjectId`. The smallest static separator is the runtime-populated descriptor contents and the read resolver’s key domain. Until then, use an opaque `SchemaKey` in OpenSpore, not a recovered class ID.

**Impact:** This can invalidate the claimed class/object graph, reference-key format, migration identity, and duplicate-class detection. It is the most important unresolved issue in the report.

### AC-02 — The “minimum” model is a design target, not an evidence-derived minimum

The primary says the evidence supports a “callback/schema + stable-reference + deferred-association” model (`blocker-c-primary.md:8-30`) and then makes `ObjectRegistry`, `ObjectReference`, `DeferredBindQueue`, `SaveDocument`, `ClassObjectTable`, `MultiArtifactPolicy`, and `NounFactoryPort` required elements (`blocker-c-primary.md:336-373`).

The binary evidence does not require those exact constructs. The strongest proven shapes are narrower:

- callback/schema dispatch exists;
- an association helper creates or reuses in-memory records;
- a Cell state holder and copy/adopt helpers exist;
- mode transitions and save candidates are separate call surfaces.

The association helpers do not prove that the association key is persisted, that it is stable across process runs, or that the same path is used by `.spo` load. A queue for forward references is a valid OpenSpore implementation choice, but cycles and forward references are explicitly unresolved (`blocker-c-primary.md:254-274`; `track-04-persistence.md:100-112`).

The same problem applies to the proposed nested `SaveDocument` graph. Static call order from a save function to a header serializer and a service operation is not proof that the resulting file contains those records in that nesting or that a class-object table is present. `serialization-model.md:253-299` explicitly says that the order among header, properties, object records, database records, and mode reconstruction is unknown.

**Required correction:** call the proposed model a **candidate clean-room architecture** or **implementation contract**, not a minimum recovered model.

### AC-03 — The primary overstates the property carrier despite an explicit unresolved layout conflict

The primary and `track-04-persistence.md:28-30,52-53,88-94` treat a `0x18` map-entry stride and observed type/flag access as strong evidence for a `0x14` runtime `Property` carrier. The primary then describes typed values, flags, and payloads as required semantics (`blocker-c-primary.md:177-191,340-346`).

That is safe only at the semantic level: typed values and flags are a useful implementation abstraction. It is not safe to freeze a `0x14` runtime or wire layout. `serialization-model.md:164-182` retains the conflict between the SDK’s `0x14` `Property` and the imported Ghidra `4`-byte `Property`, and says neither is authoritative for runtime or wire representation. The map stride alone cannot prove whether `0x18` is a key plus value, a node with allocator metadata, or a different entry representation.

Likewise, “type/flags order” is not established by the presence of writer/reader callbacks. The safest OpenSpore implementation is a value variant plus explicit codec code. It should not claim that the original writes flags before type, or that array count/size is the universal array encoding.

### AC-04 — Parent PropertyList state is not safely “runtime-only”

The primary says parent linkage is runtime overlay state unless future evidence proves its wire form (`blocker-c-primary.md:177-191`). The read path has a negative-count branch that reads three words, resolves a parent/list manager, and replaces the parent (`blocker-c-primary.md:177-182`; `track-04-persistence.md:52-53,103-105`).

This proves more than “parent is merely an in-memory overlay”: the reader has an explicit parent-related stream branch. It does not prove whether the three words are a parent object ID, manager key, serialized pointer token, or a compatibility sentinel. Therefore:

- the parent is not safely excluded from the original stream model;
- “local entries only” is not a complete round-trip claim;
- a clean-room reader must define its own parent policy and test the negative/parent case;
- no recursive parent encoding should be assumed.

The safe architectural wording is “local entries are directly evidenced; parent is an unresolved stream relationship with runtime resolution,” not “parent is runtime-only.”

### AC-05 — `PropertyList` is not demonstrated to be the outer `.spo` format

The primary correctly rejects the claim that `PropertyList` is the exact `.spo` outer envelope (`blocker-c-primary.md:375-389`). That rejection should remain stronger than the report’s “explicit stream substrate” phrasing. A local `PropertyList::Write` path is not evidence that the save candidate reaches that path, that the file begins with a property list, or that `.prop` and `.spo` share an envelope.

The prior reports agree: `.prop` is filename/path evidence and has no direct link from the recovered `.spo` body (`track-04-persistence.md:37-46`; `followup-06-persistence.md:98-108`). This is a good boundary, not a minor caveat. Any OpenSpore design that uses a `PropertyList`-shaped document must label it as an OpenSpore format choice.

## Surface-by-surface challenge

### PropertyList and `Property`

**Supported:** explicit `Read`/`Write`; local map entries; `uint32` property IDs; typed dispatch; local-first lookup and parent fallback; mutation counter separated from persisted data by the evidence policy (`serialization-model.md:130-182`).

**Not supported:** exact count sign semantics, entry byte layout, parent encoding, type/flags byte order, all property types, round-trip survival, compression, versioning, or relation to `.spo`.

The prior report’s statement that Write and Read “agree on signed count” is too strong (`track-04-persistence.md:28-30`). The read side demonstrably has a negative parent branch; that is not the same as symmetric signed-count encoding. A clean-room implementation should define its own integer format and parent policy and test negative counts as an explicit input.

### ClassSerializer and `Attribute`

**Supported:** a bounded callback-based serializer with a bounded attribute table; identity/count checks in the read path; attribute resolution; callback failure/status handling (`blocker-c-primary.md:65-76,167-175`; `followup-06-persistence.md:110-136`).

**Not supported:** a universal class ID namespace, a universal object table, a stable instance ID, a durable reference token, a cycle encoding, or complete field order. The association helpers are evidence of runtime association, not proof of persisted identity. The same-class-ID tension in AC-01 is unresolved.

The exact class/attribute wire details remain open as the primary admits (`blocker-c-primary.md:28,257-274`). Consequently, the report should not present `ClassSchema` with a `class ID` or `ObjectId` as a recovered invariant. It may use them as OpenSpore-defined keys with explicit scope and version.

### `ISimulatorSerializable`

**Supported:** an interface/vtable capability associated with serialization eligibility; several named owners expose related vtables or write/read anchors (`serialization-model.md:201-205,367-374`).

**Not supported:** complete field coverage, that every subtype uses `ClassSerializer`, that every interface method participates in the binary save path, or that the interface’s `WriteToXML` method is relevant to the binary transaction.

The proposed `SerializableContract` should not make XML part of the minimum binary model. XML may be a separate optional adapter, or be omitted until a real requirement exists.

### `cCellSerializableData`

**Supported:** a `0xEC` serializable/refcounted object; a Cell game slot at `+0x5190`; primary and secondary vtables; vtable methods that construct `ClassSerializer` state and call write/read dispatch; in-memory copy/adopt helpers (`blocker-c-primary.md:78-89,193-199,296-304`; `track-08-cell-lifecycle.md:60-74,142-153`).

**Not supported:** that this object is the object written by `FUN_00B28EC0`, read by `FUN_00B279E0`, or automatically transferred by Cell mode exit. The save candidate’s Cell-specific call (`FUN_00E5C4D0`) and the load candidate’s Cell-specific call (`FUN_00E61510`) are not, in the report, a direct demonstrated call chain to `0x00E51300/0x00E51370`. “Save candidate” should therefore remain a candidate, not a confirmed profile-persistence participant.

The field table is useful as a candidate whitelist only. `serialization-model.md:222-249` correctly requires field coverage, emission order, defaults, and round trip to remain unknown. The primary’s `CellSaveData` design can use that table as a source of candidate fields, but must not call those fields “persisted” or “surviving.”

### Save/load operations and transactions

**Supported:** static call order within the two operation candidates; serializer/database-like context creation and open/close calls; header serializer calls; service dispatch; a Cell branch; temporary-path and replacement helpers; separate `stars.db` replacement surfaces (`blocker-c-primary.md:201-252`; `followup-06-persistence.md:39-71,154-187`).

**Not supported:** a complete transaction abstraction, close-and-check-before-replace, rollback, crash atomicity, lock ownership, a manifest, or a commit marker covering `.spo` and `stars.db`.

The primary’s proposed `SaveTransaction` is an OpenSpore policy choice, not a recovered original transaction. The static evidence does not show a successful-status check between `FUN_00693900` and `FUN_006891F0`; it shows close/release followed by replacement. Likewise, `.old` and marker names do not prove an ordered recovery protocol. The prior reports correctly narrow this to bounded temp/backup/replacement plus recovery surfaces (`track-04-persistence.md:25-35,67-73`; `followup-06-persistence.md:154-187`).

The term “save/load transaction sequence” should be changed to “static operation sequence” unless the report means only helper-local call order. A function-level call sequence is not evidence of serialized record order or outer framing.

### Manager binding

**Supported:** `cGamePersistenceManager::Get` returns an imported global; imported SDK declarations expose a `LoadGame` slot; several bodies consume the service accessor (`blocker-c-primary.md:90-99,434-455`; `serialization-model.md:267-299`).

**Not supported:** that the save/load candidates are manager members, that the returned global is the concrete instance used by them, or that the service is necessarily the owner of the serializer/database operations. The primary’s “runtime message-aware strategy service exists” wording is stronger than the evidence. Service consumption is not operation ownership.

`GamePersistenceManager.h` has an uncertain parameter size and is name-level SDK evidence, not a resolved manager layout. The report correctly leaves manager membership open; that limitation must survive into the implementation contract.

### Object identity, reference restoration, and cycles

**Supported:** class/attribute metadata exists; association helpers can link existing or newly created runtime records; a refcounted-object pairing discipline is a sensible implementation invariant.

**Not supported:** the persistence meaning of an instance ID, object-count mapping, object-table placement, class-local versus document-global ID scope, reference token format, forward-reference policy, cycle policy, duplicate-ID behavior, missing-ID behavior, or restoration order.

The primary currently collapses several distinct domains into `ObjectId` (`blocker-c-primary.md:348-354,256-265`):

- class/serializer metadata IDs;
- runtime association keys;
- document instance IDs;
- political/noun IDs;
- ResourceKey triples;
- Cell pool indices.

The primary itself says these domains are separate, so combining them into a universal `ObjectId` is internally inconsistent. Keep them separate until a concrete object-table consumer and mapping routine prove otherwise. A deferred queue is safe as an implementation policy, but its presence cannot be used as evidence that the original supports cycles or forward references.

### Mode handoff

**Supported:** App helper-local order; separate Simulator strategy committed/pending slots; first-request-wins for the strategy path; Cell `OnExit`/`Dispose` cleanup separate from the observed direct serializer/file calls; in-memory Cell state copy/adopt helpers (`blocker-c-primary.md:276-334`; `track-03-mode.md:39-90`; `followup-04-cell-boundary.md:106-153`).

**Not supported:** that the App mode helper’s announcement send is synchronous listener execution, that strategy mode state is persistence mode state, that `FUN_00E63D10` is invoked by a mode transition, that a persisted DTO is transferred across mode boundaries, or that a fresh runtime owner is constructed by the observed handoff path.

The primary correctly says the first-request-wins strategy behavior is separate and listener timing is unknown, but the top-level graph still makes “mode transition” flow naturally into “explicit persisted-DTO handoff.” That is a proposed clean-room transition, not a recovered original call path. Label it as such.

The negative evidence about Cell `OnExit`/`Dispose` is also narrower than “automatic save is rejected.” It rejects a direct static call in those bodies. It does not exclude an indirect higher-level caller, callback, or strategy action. The primary’s wording “rejects a static claim” is defensible; a stronger negative would not be.

### Outer framing

**Supported:** path and replacement surfaces; serializer/database-like context calls; class metadata strings; header serializer wrappers; no recovered first bytes or record boundary.

**Not supported:** that the first serialized record is the header, that the `.spo` file is a direct serializer stream, that COM strings are or are not part of an outer record, or that a generic CRC/compression wrapper is absent from a higher level.

The primary is appropriately cautious that outer framing is unresolved (`blocker-c-primary.md:28,375-401`). The safe implementation should put its own explicit container/version policy around its own records and call it an OpenSpore format. It should not name a database/COM envelope as recovered original behavior.

## Smallest decisive observations

These are the smallest observations that would materially change a claim, grouped by the decision they settle.

### Static observations, no original-runtime parity required

1. **Class/descriptor identity:** inspect the runtime-populated header and Cell descriptor tables and the read resolver’s lookup key. Determine whether the shared `0x01A80D26` is a class key, family/default key, or misidentified argument. This is decisive for the proposed `ClassSchema` and `ObjectId`.
2. **Association-to-save edge:** follow the actual callers/callees from `FUN_00B28EC0` and `FUN_00B279E0` through the Cell-specific helpers to `0x00E51300/0x00E51370`, or establish that the path is absent. This separates a Cell serializer boundary from a Cell save participant.
3. **Property carrier/parent:** resolve the constructor/getter and map-node layout, and follow the negative-count branch to its parent/list-manager lookup. This can narrow the `Property` value layout and establish whether parent state is serialized or merely resolved.
4. **Operation framing:** trace the first database/stream write and the first read after context open, including any record header, index, checksum, or compression call. This distinguishes local call order from outer file order.
5. **Replacement check:** recover the branch/status values around close and `FUN_006891F0`, including whether a failed close or failed callback can reach replacement. This narrows the transaction claim without claiming crash atomicity.
6. **Manager ownership:** recover the concrete manager instance/vtable or direct `this` binding to the candidate operation. This is decisive for manager membership, not needed for an abstract persistence port.

### Bounded original or disposable observations, required for runtime/wire claims

7. **One explicit save/load round trip:** capture class/descriptor identity, callback order, object associations, and field whitelist behavior. Include one forward reference and one naturally occurring back-reference/cycle if reachable; otherwise record cycles as unobserved.
8. **One Cell teardown without a manual save:** observe whether mode exit/dispose reaches any serializer/file path and whether `FUN_00E63D10/0x00E627A0` participate. This tests automatic persistence rather than inferring it from cleanup.
9. **One controlled callback failure:** record cleanup, replacement, marker creation, retry, and whether an existing target remains valid. This is required before claiming transaction or recovery behavior.
10. **One bounded original artifact/parser boundary:** capture only the first bytes, first record boundary, and metadata needed to distinguish a direct stream from a wrapper. This is a framing question, not a requirement for OpenSpore’s own format.
11. **One two-object reference round trip:** compare domain identities before/after load and observe whether references preserve identity, are re-resolved by domain key, or become invalid. Pointer equality, stable token equality, and domain equality must be recorded separately.

## Exactly what can proceed safely

### Safe without original-wire or original-runtime parity

- Build a clean-room stream/codec interface with explicit version tags, bounds checks, deterministic ordering, and a documented failure policy.
- Use a semantic typed-property variant with local property entries. Keep parent behavior explicit and test it; do not copy either candidate byte layout.
- Use schema descriptors and read/write callbacks or an equivalent explicit tagged-field model. Reject mismatched or malformed records according to the OpenSpore policy.
- Use logical OpenSpore object handles and reference tokens that are never host addresses, Cell pool indices, GFX handles, or raw pointers. Keep class, instance, political, noun, and ResourceKey identities in separate typed domains.
- Provide deferred binding and cycle detection as an OpenSpore implementation feature, with deterministic missing/duplicate/cycle behavior. Do not describe it as recovered original behavior.
- Build an explicit `CellState` DTO adapter from `cCellSerializableData` candidates, with a field whitelist marked provisional. Exclude live Cell pools, GFX/UI services, world handles, and transient cache state.
- Use separate App mode, Simulator strategy, input, SpaceContext, scenario, and Cell lifecycle state. Make synchronous/deferred notification timing a policy boundary.
- Implement a stronger OpenSpore transaction if desired: stage, close/flush, validate, replace, and expose recovery behavior. Label it as an OpenSpore guarantee, not a reverse-engineered original guarantee.
- Implement independent artifact replacement or add an OpenSpore manifest/journal. Do not claim the original already has one.

### Not safe to claim or freeze yet

- Original `.spo`, `.prop`, database, COM, CRC, compression, or record framing.
- Original byte order, property carrier layout, parent encoding, attribute IDs, class IDs, object table, or reference tokens.
- That `cCellSerializableData` fields survive save/load or are written by the candidate operation.
- That Cell mode exit automatically saves or transfers a persisted DTO.
- That `FUN_00B28EC0`/`FUN_00B279E0` are `cGamePersistenceManager` members.
- Original object identity, cycle handling, cross-file atomicity, migration, defaults, or restore order.

## Required edits to the primary’s interpretation

No source change is needed for this critique. The primary report itself would be more accurate if it made the following semantic substitutions:

1. Replace “minimum semantic model required by OpenSpore” with “candidate clean-room reference architecture.”
2. Replace “class ID” with `SchemaKey` until the shared `0x01A80D26` value is explained.
3. Split `ObjectId` into class/serializer keys, document instance handles, domain IDs, and ResourceKeys until a concrete mapping is recovered.
4. Describe parent PropertyList state as an unresolved stream relationship, not runtime-only state.
5. Describe the save/load sequence as static helper-local order, not a transaction or serialized-record order.
6. Keep the Cell object as a serializer vtable/in-memory handoff candidate until a direct save/load call edge or runtime trace connects it to persistence.
7. Keep manager binding, cycles, field survival, and automatic mode save explicitly open even if a clean-room policy is chosen.

## Final disposition

`PARTIALLY_RESOLVED` is appropriate for the existence of serializer, property, mode, and replacement surfaces. The primary report’s own “compatibility excluded” caveat is the right boundary. Its strongest unsupported move is presenting a coherent candidate architecture as if its object graph, class identity, parent policy, and transaction edges were the smallest proven original model. Those portions should remain design hypotheses until the decisive observations above exist.
