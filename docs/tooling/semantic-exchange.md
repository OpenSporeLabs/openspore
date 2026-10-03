# `spore-semantic` — semantic exchange interface

`spore-semantic` is a **read-only** CLI that exports OpenSpore's accumulated
per-function knowledge into one deterministic snapshot, and answers
`binary_sha256 + VA` lookups against it.

It exists so that sibling projects (first: `spore-recomp`) can ask OpenSpore
"what do you already know about this function?" **without** depending on the
OpenSpore repository, on Python, or on Ghidra.

```
OpenSpore (Python authoritative)
   ↓  spore-semantic export
deterministic JSON Lines snapshot
   ↓  copied / versioned by the consumer
spore-recomp
```

Nothing flows the other way. The snapshot is optional; OpenSpore is not a build
or runtime dependency of any consumer.

---

## 1. What is authoritative, and what this tool consumes

Python stays authoritative for reconstruction, evidence, ABI inference,
vftable inference, validation, frontier, promotion and Ghidra integration.
`spore-semantic` **does not re-derive any of it**. It reads the committed /
exported artifacts those systems already write, and projects them into one
lookup-shaped record.

The rule the implementation follows: *if a fact already exists in an
OpenSpore artifact, copy it with its provenance; if it does not exist, say
`UNKNOWN` — never guess, never infer, never silently drop.*

### 1.1 Field → authoritative source mapping

This is the normative mapping. `spore-semantic` reads **only** these files.

| Passport field | Authoritative source | Exact current representation |
|---|---|---|
| `identity.canonical_va` | `.spore-analysis/ghidra-exports/functions.tsv` (frozen universe) | TSV, header `address\tname\tsize\tis_thunk\tis_external\tsection`; `address` is bare 8-char lowercase hex; 58,757 rows |
| `identity.canonical_va` (tracked fallback) | `knowledgegraph/research/21-decompilation-coverage.json` | `ledger[].va` bare 8-hex, `ledger[].function_body_size_bytes` int |
| `identity.rva` | derived `va - 0x400000` | matches `tools/triage/classify.py` (`format(va_int - IMAGE_BASE, "08x")`) |
| `identity.size`, `identity.is_thunk`, `identity.section` | `functions.tsv` columns 3/4/6 | `size` is a **decimal** integer; `is_thunk` is `true`/`false` |
| `identity.requested[]`, `identity.identity_resolution` | `reconstruction/knowledge/index.json` → `records[va].identity_resolution` | `{"canonical_va": "0x00e3a270", "rule": "containing_function_entry", "requested": [{"offset": 400, "va": "0x00e3a400"}]}` — emitted only when a non-entry was resolved |
| interior-VA → entry rule | `tools/reconstruction_knowledge.py::canonical_identity` (bisect on entry starts, exact `start <= a < start + size`) | replicated verbatim in `internal/openspore/identity.go`; no new algorithm |
| `names.ghidra_name` | `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl` | JSONL, `va` bare 8-hex, field `ghidra_name` |
| `names.normalized_symbol` | `index.json` → `records[va].normalized_symbol` | `"0x%08x"`-keyed dict; falls back to triage `norm_name` |
| `names.sdk_name` | triage JSONL field `sdk_name` | `string \| null`; 1,666 VAs, from `sdk_functions.tsv` (SDK `FUNCTION_ADDRESSES`) |
| `names.identity_refuted` | `index.json` → `records[va].identity_refuted` | `{name, superseded, superseded_source, declared_by, reason, refuted}` when a worker refuted the SDK-derived name |
| `classification.category`, `.priority`, `.evidence` | triage JSONL `category` / `priority` / `evidence` | `ENGINE_INTERFACE\|ENGINE_IMPLEMENTATION\|GAMEPLAY_SUPPORT\|GAMEPLAY_LOGIC\|THIRD_PARTY_OR_RUNTIME\|UNKNOWN`; `P0..P3\|IGNORE`; `UNKNOWN\|APPROXIMATION\|INFERRED\|SUPPORTED\|OBSERVED\|CONFIRMED\|VERIFIED` |
| `classification.subsystem` | `index.json` → `records[va].subsystem` (3-way fallback: manifest `functions[].subsystem` → triage queue `subsystem` → `semantic-decomp.json`) | dotted and single-word vocabularies coexist **by design**; `null` for 95/618 |
| `classification.cluster` | triage queue / triage JSONL `cluster` | e.g. `"unknown-fun-mass"` |
| `classification.sdk_structs` | triage JSONL `struct_names` | `string[]` of `/Spore/...` names |
| `classification.renderware` | triage JSONL `subsystem == "RenderWare"` (23 rows) | derived boolean + role string; **not** `render-boundary.json`, which is keyed by boundary id, not VA |
| `abi.*` (machine) | `reconstruction/evidence/<bare8>/evidence.json` → `categories.abi_derived.value` | envelope `{availability, evidence_level, evidence_state, provenance, reason, value}`; `value.schema == "openspore-abi-inference-1"` |
| `abi.convention`, `.convention_confidence` | same, `conventions.calling_convention` / `conventions.confidence` | `__cdecl\|__stdcall\|__thiscall\|__fastcall` or `null`; confidence from `CONFIDENCE_ORDER` |
| `abi.receiver` | same, `receiver` | `{"present": true\|false\|**null**, "register": "ECX"\|null, "confidence", "shape", "bounds_only", "provenance"}` — `present: null` is a load-bearing known-unknown |
| `abi.cleanup` | same, `cleanup` | `{"side": "caller"\|"callee"\|"CONFLICT"\|null, "bytes": int\|null, "confidence", "corroboration"}` |
| `abi.return`, `abi.sret`, `abi.variadic`, `abi.stack_argument_slots` | same, `return` / `sret` / `variadic` / `stack_arguments` | `register_class: "pointer_like"\|...`, `type` is **always** `null` by contract |
| `abi.declared.*` (semantic) | `index.json` → `records[va].abi` (worker metadata, hand-authored) | free-form prose strings such as `"__thiscall observed"` — kept in a **separate** block from the machine record |
| `vtable.memberships[]` | `.spore-analysis/cache/vftables-<binary_sha>.json` → `memberships[va]` | `{"0x00402ab0": [["0x013f05d8", 2], ...]}` — `[table_va, slot]` pairs, 14,627 VAs. This is the only source the ABI engine accepts (`VFTABLE_BASIS = "vftable_predicate"`). |
| `vtable.abi_attributed` | evidence pack ABI record `inferences[*]` with `id ∈ {R1-VFT, R2-VFT, V1-VFT}` | `{"based_on": [...], "confidence": "INFERRED", "id": "R1-VFT", "value": {"table": "0x013f57f8", "slot_index": 8, "receiver_provenance": "vftable_slot_dispatch", ...}}` |
| `vtable.triage_addresses[]` | triage JSONL `vtable_addrs` (5,948 VAs) and `vtable_family` (1,501) | `string[]` of bare 8-hex, no slot |
| `graph.callers`, `graph.callees` | `knowledgegraph/triage/xrefs-2540f2ca.tsv` | `caller_va\tcallee_va\treference_type\tcallsite_va\tsource\tsnapshot_sha256`, closure-validated against the pinned universe + EXT/VT allowlists |
| `graph.external_callees` | same, callee spelled `EXT:<library>::<name>` | allowlist in `xrefs-2540f2ca.externals.tsv` |
| `graph.data_reference_count` | `knowledgegraph/triage/datarefs-2540f2ca.tsv` | `caller_va\ttarget_va\taccess_mode\tsegment\tcallsite_va\tsource\tsnapshot_sha256`; count only — the addresses themselves stay in the authoritative TSV |
| `globals[]` | `index.json` → `records[va].globals` | `["global:0x00005198"]` (may be prose — reproduced verbatim, never rewritten) |
| `types[]` | `index.json` → `records[va].types` | `string[]` |
| `semantics.classification`, `.confidence`, `.notes` | `index.json` → `records[va].semantic` | `{"classification": "BOUNDED_SEMANTIC", "confidence": {...per-axis...}, "evidence": [{claim, class, source}], ...}` |
| `semantics.status` | `index.json` → `records[va].semantic_status` | free-form, e.g. `"static_reconstruction_runtime_gated"` |
| `semantics.unresolved_questions[]` | `index.json` → `records[va].unresolved_questions` | `string[]`, copied verbatim |
| `reconstruction.package`, `.status`, `.review_status`, `.integration_status`, `.runtime_gated` | `index.json` → `records[va]` | `reconstructed` / `candidate` / `unresolved` / `queued` / `implemented` / `blocked` |
| `reconstruction.generated_source[]` | `index.json` → `records[va].source.files` | `string[]` repo-relative paths |
| `reconstruction.promoted` | `reconstruction/evidence/<bare8>/promotion.json` | `{"schema": "openspore-promotion-record-1", "static_status": "PASS", "runtime_status": "GATED", "package", "sources", "promoted_on", ...}` — 92 records |
| `reconstruction.validation{}` | `reconstruction/evidence/<bare8>/validation.json` → `checks` | `{"ABI": {"status": "PASS", "coverage": "complete", "detail": ..., "evidence": [...]}, ...}` — 677 records |
| `reconstruction.evidence_pack`, `.evidence_content_sha256`, `.evidence_state` | `reconstruction/evidence/<bare8>/evidence.json` | pack is `{schema, binary, target, categories, record, provenance, conflicts, collector, evidence_state, content_sha256}`; `content_sha256` = SHA-256 over the canonical JSON with that field set to `null` (`indent=2, sort_keys=True, ensure_ascii=False`, trailing `\n`) |
| `provenance[]` | evidence pack `provenance[]` | `[{"mode": "live"\|"derived"\|"persisted", "ref": "...", "source_class": "ghidra"\|"derived"\|"committed_artifact"\|"generated_index"}]` |
| `metadata.binary_sha256`, `.image_base`, `.architecture`, `.program`, `.version` | `index.json` → `binary` | `{"architecture": "x86:LE:32", "ghidra_program": "SporeApp.exe", "image_base": "0x00400000", "program": "SporeApp.exe", "sha256": "25d4…", "version": "3.1.0.22"}` |
| `metadata.inputs{}` | SHA-256 of every file read | computed at export time |

### 1.2 What is deliberately *not* projected

`spore-semantic` is a lookup surface, not a mirror of OpenSpore's database.
Excluded on purpose:

* full ABI inference records (observations, rule graph, `abstained_because`,
  `content_sha256`) — only the decided fields are projected;
* data-reference addresses (only a count; the TSV stays authoritative);
* `type`-level field tables (`index.json` `types[]` — type-scoped, not
  function-scoped);
* frontier scores, scheduling, ownership arbitration, staging/runtime state;
* `docs/replacement-status.json` (asset/replacement track, not function-scoped);
* `render-boundary.json` (48 boundaries keyed by id, not by VA);
* the contradiction ledger (255 entries, adjudication-process state);
* anything volatile: clocks, PIDs, absolute paths, Ghidra URLs.

---

## 2. Snapshot format

One JSON Lines file. **Line 1 is the metadata record.** Lines 2..N are
function records, sorted ascending by `identity.canonical_va`.

```
{"record":"metadata",  "schema":"spore-semantic-snapshot-1", ...}
{"record":"function",  "identity":{...}, ...}
{"record":"function",  ...}
```

On the shipped 3.1.0.22 checkout that is 58,757 records in ~98 MB, with a
median record of ~1.3 kB. Loading and indexing the whole file takes ~0.6 s.

* **Deterministic.** Field order is Go struct order; no map is ever
  serialised; every list is sorted; no timestamp, PID, absolute path or host
  name is written. Two exports from the same repository state are byte-identical.
* **Integrity.** `metadata.content_sha256` is SHA-256 over the concatenation of
  the **function record lines only** (each including its `\n`). The metadata
  line is excluded, so the field is not self-referential. Verified on load.
* **Self-describing inputs.** `metadata.inputs` maps every repo-relative file
  the export read to its SHA-256 (685 files on the current checkout, including
  one line per evidence pack), so a consumer can tell *which* OpenSpore state
  produced the snapshot.
* **Export-side facts are separated.** `metadata.counts` holds counters that
  `validate` recomputes from the record bodies and cross-checks.
  `metadata.export` holds what only the write knows — which universe artifact
  supplied identity, whether it was the fallback, how many evidence-pack
  directories were read, and which packs no passport can reference.

Default path:

```
knowledge/semantic/function-passport-v1.jsonl
```

---

## 3. Canonical identity

The primary cross-project identity is:

```
binary_sha256 + canonical VA
```

Canonical VA spelling is **always** `"0x%08x"` lowercase, matching
`tools/reconstruction_knowledge.py::normalize_va`. Input is tolerant
(`0x` prefix, upper/lower case, bare hex, decimal, `rva:` prefix); output is
not.

An RVA is never silently accepted as a VA or vice versa. `rva` is always
derived as `canonical_va - image_base` and is reported alongside the VA so a
consumer can check the arithmetic itself. A VA below `image_base` is rejected
(`address_below_image_base`).

### 3.1 Interior addresses

If the requested VA is not a function entry, the repo's existing rule applies:
bisect on entry starts, then the exact `start <= a < start + size` containment
test (`canonical_identity` in `tools/reconstruction_knowledge.py`). A hit is
resolved and reported explicitly; a miss is **not** resolved and is reported as
a non-function entity. Padding between entries resolves to nothing — that is
the conservative direction the repository already chose.

Lookup output always carries both:

```json
{
  "requested_va": "0x00e3a400",
  "canonical_va": "0x00e3a270",
  "identity_resolution": {
    "rule": "containing_function_entry",
    "offset": 400,
    "range": {"start": "0x00e3a270", "end": "0x00e3a438"}
  }
}
```

`identity_resolution` is `null` when the requested VA was already an entry.
Because canonicalization is deterministic, the lookup recomputes it from the
snapshot's own `size`/`canonical_va` rather than trusting a stored hint — and a
stored `identity_resolution` (evidence that OpenSpore itself once corrected
this address) is reported separately as `recorded_resolution`.

---

## 4. Tri-state semantics: `UNKNOWN` vs `false` vs "not applicable"

Consumers need to distinguish three different statements, and this format never
uses a zero value to smuggle one into another.

Every optional fact group carries the **same envelope the evidence packs
already use** (`reconstruction/evidence/*/evidence.json`), with three additions
that make the absence legible:

```jsonc
// a fact is known
{ "state": "available",
  "evidence_level": "INFERRED",        // the shared 7-rung scale
  "evidence_state": "DERIVED",         // LIVE | DERIVED | PERSISTED
  "provenance": ["reconstruction/knowledge/index.json"],
  "value": { ... } }

// OpenSpore looked and found nothing
{ "state": "unavailable",
  "evidence_level": "UNKNOWN",
  "evidence_state": "MISSING",
  "reason": "no_evidence_pack" }
```

* `state: "unavailable"` + `evidence_level: "UNKNOWN"` +
  `evidence_state: "MISSING"` + `reason` is how **explicit absence** is
  published. Consumers can see that OpenSpore looked and found nothing, which
  is different from OpenSpore never having looked.
* `value` is **omitted**, not `null`, when unavailable. A `null` would be a
  weaker statement than `state: "unavailable"`, and an empty skeleton would be
  a lie about what was searched.
* An unavailable envelope carries **no `provenance` list**. The provenance of a
  non-finding is fully determined by its reason code (the table below maps each
  code to the artifact consulted), and repeating five long repo paths on 59k
  records would cost ~21 MB to say nothing that is not already implied. An
  available envelope always carries its provenance.
* `reason` is a **closed vocabulary** for generic absences, not prose: the same
  code appears on tens of thousands of records, so the explanation lives here
  and in `spore-semantic explain`, not in every line. A `reason` outside the
  table is source-supplied text carried verbatim from the artifact.

| reason code | meaning |
|---|---|
| `no_evidence_pack` | no evidence pack exists for this VA, so no ABI inference record was ever derived |
| `no_abi_derived_record` | a pack exists but its `abi_derived` category holds no value |
| `no_vtable_membership` | neither the sound vftable scan nor the triage vtable index associates a table with this function |
| `vftable_scan_absent` | the sound vftable scan was not in the exporting checkout, so it could not be consulted at all |
| `no_global_references` | the knowledge index records no global reference |
| `no_associated_types` | the knowledge index associates no type |
| `no_semantic_record` | no semantic research record exists |
| `no_reconstruction_package` | no package, staged source, validation report or promotion record exists |
| `no_validation_report` | a reconstruction exists but carries no validation report |
* Inside `abi.receiver`, `present` is `true` / `false` / **`null`**, and `null`
  is meaningful: in `abi_infer.py` a `present: null` receiver blocks the `C6`/
  `C9` rules and makes the record abstain. It is not the same as `false`.
* `abi.convention` is `null` when undetermined. There is no `"UNKNOWN"`
  sentinel string and no `"none"`.
* Only **successful** facts are never emitted alone: `abi`, `vtable`,
  `semantics`, `reconstruction`, `globals` and `validation` are all present as
  keys on every record, unavailable ones carrying the envelope above.

`NOT_AVAILABLE` and `REFUTED` are not invented here. Where the repository
already has a vocabulary for them, that vocabulary is preserved verbatim
(`validation.json` `status: "NOT_AVAILABLE"` / `"FAIL"`, `identity_refuted`).

---

## 5. Machine fact vs semantic interpretation

Four kinds of statement live in one passport and are never merged:

| Kind | Where | Marker |
|---|---|---|
| Machine fact (from disassembly analysis) | `abi.*` | `abi.origin == "abi_inference"`; envelope `evidence_state: "DERIVED"` |
| SDK name | `names.sdk_name` | `names.sdk_name_source == "sdk_functions.tsv"`; never becomes `name` |
| Semantic interpretation (a researcher's claim) | `semantics.*`, `abi.declared.*` | prose strings and per-axis confidence maps, kept separate from machine fields |
| Runtime observation | `reconstruction.runtime_gated`, `reconstruction.runtime_validated`, `validation.RUNTIME` | `runtime.gated: true` means *the gate is open, nothing was attempted, nothing failed* — it is **not** a failure |

`validation.json` is carried with its `status`, `coverage` and `evidence` refs
per dimension. `PASS` / `WARN` / `FAIL` / `UNKNOWN` / `NOT_AVAILABLE` and
coverage `none` / `partial` / `complete` are reproduced unchanged.

---

## 6. CLI

```
spore-semantic export        [--out PATH] [--root DIR]
spore-semantic lookup        <VA>     [--snapshot PATH] [--json]
spore-semantic lookup-symbol <NAME>   [--snapshot PATH] [--json]
spore-semantic explain       <VA>     [--snapshot PATH]
spore-semantic stats                  [--snapshot PATH] [--json]
spore-semantic validate               [--snapshot PATH] [--json]
```

`--snapshot` defaults to `knowledge/semantic/function-passport-v1.jsonl`
under `--root`, which defaults to `$OPENSPORE_ROOT` or the nearest ancestor
directory containing OpenSpore's tracked markers. Flags may appear before or
after the positional argument.

Lookup accepts `0x00925050`, `925050`, `00925050`, `0x925050`, `dec:9588816`
(explicit decimal), `0d9588816` and `rva:00525050`. Output addresses are always
`0x%08x`.

**Bare digits are hex.** That is the repository's own convention — every
committed OpenSpore artifact keys on a bare 8-char lowercase hex VA8 — and it is
the only reading under which `925050` and `00925050` cannot be confused. Reading
bare digits as decimal instead would answer a different question silently
(`lookup 925050` would resolve to `0x000e1f92`), so decimal requires an explicit
`dec:` or `0d` prefix and an explicit RVA is the only form that is offset.

`$OPENSPORE_REQUIRE_SHA` makes every command refuse a snapshot whose
`binary_sha256` differs from the one the consumer expects (exit 4).

### 6.1 Exit codes

| Code | Meaning |
|---|---|
| 0 | success |
| 1 | usage / generic error |
| 2 | unknown function (no containing entry) |
| 3 | unknown symbol |
| 4 | binary mismatch (snapshot `binary_sha256` ≠ requested) |
| 5 | corrupted snapshot (bad JSON, truncated, `content_sha256` mismatch, duplicate canonical VA) |
| 6 | unsupported schema version |
| 7 | source/snapshot unavailable (universe missing, no snapshot file) |
| 8 | ambiguous symbol (multiple canonical functions share a name) |
| 9 | image base mismatch (`runtime` overlay declares a different image base) |

`lookup` never prints an empty object. A miss prints an explicit error naming
the requested VA, the image base and the searched identity.

### 6.2 Worked example

```sh
$ spore-semantic lookup 0x00e3a400 --root .
0x00e3a270  FUN_00e3a270
  requested_va    0x00e3a400  -> resolved to containing entry, rule=containing_function_entry offset=400 range=0x00e3a270..0x00e3a56b
  rva             0x00a3a270
  image_base      0x00400000   binary 25d42a7a5c4d438f
  size            763 bytes (section .text, thunk=false)

  identity
    sdk_name          UNKNOWN (not stated by any authoritative OpenSpore artifact)
    normalized_symbol FUN_00e3a270

  classification
    category          GAMEPLAY_LOGIC   evidence=INFERRED priority=P3
    subsystem         Simulator   [triage_queue]

  abi  [unavailable / MISSING / UNKNOWN]
    reason: no_evidence_pack
      no evidence pack exists for this VA, so no ABI inference record was ever
      derived; absence of a pack is not evidence of a convention
  ...

$ spore-semantic lookup 0x00925050 --root . ; echo "exit=$?"
spore-semantic: unknown function: 0x00925050 is not a function entry and is not
inside any known function body in binary 25d42a7a5c4d438f (image base
0x00400000); 58757 functions indexed
exit=2
```

### 6.3 Runtime overlays: the consumer side, made explicit

Runtime observations belong to **you**, not to OpenSpore. What follows is the
contract OpenSpore now validates, so that a producer can emit the overlay
directly instead of every consumer inventing one.

```
knowledge/semantic/function-passport-v1.jsonl   -- OpenSpore's static truth
runtime-overlay-v1.jsonl                        -- YOUR runtime truth
                    ↘                          ↙
             spore-semantic runtime lookup      -- a VIEW over both
```

The two files stay separate on disk. There is deliberately **no** `runtime
merge` command: a command named "merge" invites a caller to produce a combined
artifact and then trust it as one source of truth. The join is a view, so no
combined artifact can be mistaken for either.

#### Schema: `spore-semantic-runtime-overlay-1`

JSON Lines, deliberately the same shape as the static snapshot. Line 1 is the
metadata record; lines 2..N are entry records sorted **strictly ascending** by
`requested_va`. `content_sha256` covers the entry lines only. No timestamp, no
PID, no absolute path, no host name.

**metadata (line 1)**

| Field | Meaning |
|---|---|
| `record` | `"metadata"` |
| `schema` | `"spore-semantic-runtime-overlay-1"` |
| `binary.binary_sha256` | **required.** The join key. 64 lowercase hex. |
| `binary.image_base` | **required.** e.g. `"0x00400000"` |
| `binary.architecture` / `program` / `version` | verbatim from the producer |
| `producer.project` | **required.** e.g. `"spore-recomp"` |
| `producer.name` / `version` | the producing program and its version |
| `producer.artifact` | **required.** A *portable* identifier (`work/reports/startup-recovery14.json`), never an absolute path |
| `producer.source_schema` | the producer's own report schema, if it has one |
| `counts` | the producer's tallies, cross-checked against the body on load |
| `content_sha256` | SHA-256 over the entry lines; verified when present |

**entry (lines 2..N)**

| Field | Meaning |
|---|---|
| `requested_va` | **required**, canonical `"0x%08x"`. Reproduced verbatim, never rewritten. |
| `canonical_va` | the producer's canonicalization, or `null`. A **claim**, not the join decision. |
| `canonicalization` | `function_entry`, `containing_function_entry`, `non_function_entity`, `not_stated` |
| `canonical_offset` | non-null only for `containing_function_entry` |
| `reached` | tri-state `"true"` / `"false"` / `"null"` |
| `entry_count` | `*int`. `null` = not counted, `0` = observed zero times. |
| `first_reached_from`, `max_call_depth` | optional |
| `runtime_callers[]` | `{caller_function_va, callsite_va, count, min_depth, max_depth}` — sorted, de-duplicated |
| `runtime_targets[]` | `{target_va, indirect, unresolved, classification}` — sorted by `target_va` |
| `runtime_imports[]` | `{module, symbol, slot_va, loaded_value, bound, reached_count}` — sorted by `(module, symbol, slot_va)` |
| `observations[]` | typed facts, never a free-form blob — sorted by `(sequence, kind, callsite, target, eip, canonical json)` |
| `provenance[]` | **required, non-empty.** `{source_class:"runtime", producer, artifact}` |

**observation kinds** (closed vocabulary, nine):

| kind | required fields | may also carry |
|---|---|---|
| `entry` | `eip` | `sequence`, `call_depth`, `detail` |
| `call` | `callsite_va`, `target_va` | `sequence`, `call_depth`, `count`, `caller_function_va` |
| `indirect_call` | `callsite_va`, `target_va` | `indirect` (tri-state), `sequence`, `call_depth`, `detail` |
| `return` | `return_address` | `return_register`, `sequence`, `call_depth` |
| `import` | `module`, `symbol` | `slot_va`, `address` |
| `exception` | `eip`, `exception_class` | `call_depth`, `detail` |
| `memory` | `address`, `access` (`read`/`write`) | `width_bytes`, `value` |
| `register` | `register`, `register_value` | `detail` |
| `stack` | `entry_esp`, `return_esp`, `stack_delta_bytes` | `call_depth` |

The loader enforces **both** halves of that table: a kind must carry its required
fields, and it must *not* carry another kind's fields. Without the second half an
observation could claim `kind: "import"` while carrying only a register value,
and a consumer scanning for imports would find it.

#### What the loader refuses

`spore-semantic runtime validate` (exit 5 unless noted) rejects: a wrong
`schema` id (exit 6), an unknown JSON field (exit 6), an unknown observation kind
or canonicalization (exit 5), a `binary_sha256` that is absent, non-hex or
different from the one required (exit 4), an `image_base` that differs (exit 9),
a missing `producer.project`/`name`, an absolute path in `provenance.artifact`, a
non-canonical VA spelling (only lowercase `0x%08x` is accepted, so `"925050"`
and `"0x00925050"` cannot become two entries for one address), records not
strictly ascending or a repeated `requested_va`, a negative `entry_count`,
`count`, `call_depth`, `min_depth`, `max_depth` or `reached_count`, a
non-positive `width_bytes`, `min_depth > max_depth`, `reached: "false"` together
with `entry_count > 0`, `indirect: "true"` together with `unresolved: "false"`,
a `canonical_va` without one of the two canonicalizing rules, an
`canonical_offset` outside `containing_function_entry`, a byte-identical
duplicate observation, two JSON values on one line, a truncated line, a
`content_sha256` mismatch, and a header whose `counts` disagree with its body.

#### Tri-state, not boolean

`reached: "null"` means **the producer did not observe or state it**. That is not
the same as `reached: "false"`, which means the producer watched and saw no
entry. Collapsing the two turns "we did not look" into "we looked and found
nothing", which is how a runtime observation becomes a fabricated negative. The
same rule applies to `entry_count: null` (not counted) versus `0` (observed
zero), and to a `[]` list (the category was observed and is empty) versus an
absent entry.

#### Commands

```sh
spore-semantic runtime validate        [--overlay PATH] [--json]
spore-semantic runtime lookup   <VA>    [--overlay PATH] [--snapshot PATH] [--json]
spore-semantic runtime frontier         [--overlay PATH] [--census PATH]
                                       [--snapshot PATH] [--va VA]... [--json]
spore-semantic runtime stats            [--overlay PATH] [--snapshot PATH] [--json]
spore-semantic runtime import-recomp --report PATH [--out PATH] [--artifact ID]
spore-semantic runtime census           [--root DIR] [--out PATH] [--json]
```

The **snapshot is optional everywhere**. With an overlay and no OpenSpore
checkout, `validate`, `lookup`, `frontier` and `stats` all work; every
static-derived field is then `null` rather than `0`.

`runtime lookup` shows the two halves separately and reports identity from both
sides without preferring either: OpenSpore's canonical-identity rule is
authority, the producer's `canonical_va` is a claim, and a disagreement between
them is reported as a disagreement. Every joined output carries
`"verdict_unchanged": "no static verdict was modified by this lookup"`.

#### Runtime-only addresses are first-class

An address the producer reached and OpenSpore cannot place is representable, and
it is the most valuable thing an overlay can contain:

```
requested_va = 0x00925050
canonical_va = null
static_status = static_non_function_entity
reached       = "true"
```

`0x00925050` is the live case: it lies between `FUN_00925000` (ending
`0x0092504a`) and `FUN_009250c0`, so the conservative canonical-identity rule
resolves it to nothing, and `spore-recomp` reached it through a real vtable
indirect call. The bridge preserves the discrepancy — it does **not** map
padding to a function, does **not** manufacture a passport, and does **not**
insert the address into the static function universe.

#### `runtime frontier`: which blockers now have runtime evidence

`runtime frontier` intersects a static blocker list with runtime observations and
answers, per target: the static blockers (with the artifact that stated each),
whether the overlay holds observations in categories this build maps to that
blocker, whether the function is already reconstructed, whether a new static task
is justified, and why.

`resolution_class` is a closed vocabulary and is a **prioritisation** answer,
never a verdict change:

| class | meaning |
|---|---|
| `runtime_evidence_relevant` | the overlay holds observations in categories mapped to a recorded blocker — the state worth a focused investigation |
| `reached_without_relevant_observation` | reached, but nothing relevant was recorded; the missing evidence is not what this producer run collected |
| `not_reached` | the overlay carries no entry for this VA. **Not** the same as observed-and-not-reached. |
| `runtime_only_address` | the producer reached an address OpenSpore cannot place — a **static identity** task, not a blocker resolution |
| `already_reconstructed` | a promotion record exists; runtime evidence does not reopen it |
| `no_static_blocker` | nothing recorded for this VA to bear on |

The blocker list itself comes from artifacts OpenSpore already wrote: a
validation dimension whose status is not `PASS`, an abstaining derived ABI record,
an open runtime gate, and — when a census is supplied — the knowledge index's own
`blockers` prose and `unresolved_questions`, reproduced verbatim. The mapping from
a dimension to the observation categories that could bear on it is a declared,
closed table in the consumer (`blockerRelevance`), and a dimension absent from it
yields **no** relevance rather than a default.

#### `runtime census`: the static blocker projection

The static Passport deliberately does not carry `index.json`'s `blockers` prose or
`unresolved_questions`: projecting them would change the snapshot's
`content_sha256`, which consumers pin. So the census is a separate OpenSpore-side
sidecar (`openspore-runtime-blocker-census-1`):

```sh
spore-semantic runtime census --root . --out knowledge/semantic/blocker-census-v1.json
```

It projects `reconstruction/knowledge/index.json` plus the **promotion markers**,
because the index lags promotion by design and the marker is the authoritative,
self-maintaining record. It derives no eligibility, no scoring and no blocker
codes: `tools/reconstruction_tooling/frontier.py` owns eligibility, and
duplicating it in a second language would create a second answer to "which targets
are eligible". Counts are computed over the full projection *before* any filter,
so they stay checkable against the repository's own statements (89 markers, 92
promoted VAs, 618 index records, 427 runtime-gated).

#### `runtime import-recomp`: consuming a real producer report today

A spore-recomp startup-recovery report already carries everything the overlay
needs, so an adapter ships with the tool:

```sh
spore-semantic runtime import-recomp   --report ../spore-recomp/work/reports/startup-recovery14.json   --out runtime-overlay-v1.jsonl
```

The adapter is one-way and read-only. It never asks `spore-recomp` to change, never
writes into that repository, and introduces no OpenSpore dependency on the
`spore-recomp` side. Every fact is a projection with the producer's own vocabulary
preserved (its event classes, its import spellings, its final register dump), and
the adapter derives exactly one thing: the set of addresses the report mentions.
It leaves `canonical_va` **null on every entry**, because identity is OpenSpore's
to decide and an adapter that answered it would be creating a second identity
scheme.

Three things it deliberately does not do:

- it does not set `reached` from a call-edge callsite. Control certainly passed
  through that address, but "entered as a function" is a stronger claim, so the
  flag stays `null` and `entry_count` speaks;
- it emits **no** `stack_delta_bytes`. The producer's register map is a single CPU
  sample at its stop point, and a delta derived from one sample would read as
  "the callee restored the stack", which nothing observed;
- it records an IAT cell check as an import observation that says what the cell
  *holds*. `reached_count` stays `null`, because the report does not establish
  that the import was ever called.

The three notes are emitted with every conversion so a reviewer reads them with
the numbers.

### 6.4 Determinism

Two conversions of one report, two overlay writes from one set of entries, two
joined lookups of one snapshot, and two census projections of one checkout are all
byte-identical. There is no clock, no PID, no absolute path, no map
serialisation, and the entry list is sorted in both the writer and the loader, so
input order cannot leak into the output.

---

## 7. Layout

```
tools/spore-semantic/
  cmd/spore-semantic/main.go     CLI entry point
  internal/semantic/             FunctionPassport types, JSON encoding, envelopes
  internal/openspore/            readers for the authoritative artifacts (§1.1)
  internal/snapshot/             deterministic write, load, schema validation
  internal/index/                in-memory VA + symbol index, interior resolution
  internal/cli/                  commands, output formatting, exit codes
  internal/runtime/              runtime overlay schema, fail-closed loader,
                                 spore-recomp adapter, the join, frontier, stats
```

No network access. No Python at runtime. No Ghidra at runtime. Standard library
only — `go.mod` has no `require` block. The same holds for the `runtime`
namespace: an overlay is consumed without an OpenSpore checkout, and the
dependency never runs in the other direction.

### 7.1 Build and install

```sh
cd tools/spore-semantic
CGO_ENABLED=0 go build -trimpath -ldflags '-s -w' \
  -o ~/.local/bin/spore-semantic ./cmd/spore-semantic
```

That produces a ~3.3 MB static, stripped binary. `-trimpath` and `-ldflags` are
cosmetic and do **not** affect the output: the export is byte-identical whether
built this way or with a plain `go build`.

Indexing is a plain `map[uint32]*Passport` plus a `map[string][]uint32` for
symbols. Measured end to end on the shipped 98 MB snapshot: **~0.65 s** per CLI
invocation, including the full parse. SQLite is not introduced because no
measurement asked for it.

### 7.2 Verified behaviour on the current checkout

| case | VA | result |
|---|---|---|
| promoted, SDK-named, full record | `0x0040ccb0` | `WAVE6-PRESENTATION`, `__thiscall`/`ECX`, 9 validation dimensions, integration `integrated` |
| promoted with a promotion record | `0x00c0bbd0` | `promoted: "true"`, `validation.ABI = PASS / partial` |
| UNKNOWN ABI (record abstains) | `0x0041dc10` | `convention: null`, `verdict: ABI_UNKNOWN`, `receiver.present: "null"` |
| vftable-backed | `0x00402ab0` | membership pairs with slot widths from the sound scan |
| RenderWare | `0x011ee700` | `RenderWare::CompiledState::SetRaster`, `/Spore/RenderWare/CompiledState` |
| interior VA | `0x00e3a400` | → `0x00e3a270`, offset 400, matching the index's own recorded correction |
| padding VA | `0x00925050` | unknown function, exit 2 — it lies between two bodies |
| refuted identity | `0x008414c0` | SDK `ArgScript::FormatParser::ParseFloat` superseded, reason kept as an object |

### 7.3 Verified behaviour of the runtime namespace

Measured against the real checkout and the real `spore-recomp`
`startup-recovery14.json` / `startup-recovery12.json` reports.

| case | result |
|---|---|
| `runtime import-recomp` on `startup-recovery14.json` | 281 addresses, 8 imports, 1 unresolved target, 2 reached; validates clean |
| two conversions of one report | byte-identical |
| `runtime validate` on the converted overlay | OK, `content_sha256` verified over 281 entry lines |
| `runtime census --root .` | 618 index records, 89 promotion markers, 92 promoted VAs, 427 runtime-gated — each matching the repository's own statement |
| `runtime lookup 0x00925050` on `startup-recovery12.json` | `canonical_va: null`, `static_status: static_non_function_entity`, `reached: "true"`, caller `0x00925b00@0x00925b33`, exit 0 |
| `runtime stats` | 281 addresses; 154 with a passport, 127 runtime-only (87 of them inside the image), 0 promoted |
| `runtime frontier` over the 10 remaining ceilings | every ceiling carries its adjudicated blockers and census prose; none classified closed |
| static artifacts after a full runtime workflow | `function-passport-v1.jsonl`, `index.json` and `xrefs-2540f2ca.tsv` all byte-for-byte unchanged |
| new build vs. `HEAD` build, same export | byte-identical, so the runtime namespace is provably neutral on the static exporter |

Note on the committed snapshot: `knowledge/semantic/function-passport-v1.jsonl`
was last exported at 17:41 and is **stale** with respect to the current checkout
— `reconstruction/knowledge/index.json` and
`reconstruction/evidence/00c71e30/evidence.json` have moved since, shifting four
coverage counters (`with_globals` 119→120, `with_semantics` 536→538,
`with_types` 529→531, `explicitly_unavailable` 401364→401359). That is a
pre-existing condition, not a consequence of the runtime work; the runtime
namespace never rewrites the snapshot, and the `spore-semantic runtime`
commands work against the stale one as-is. Re-export when convenient.

Two exports from the same checkout state are byte-for-byte identical.