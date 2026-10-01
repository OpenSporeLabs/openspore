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

### 6.3 Consumer-side overlays

Runtime observations belong to the consumer, not to OpenSpore. A consumer may
maintain its own overlay keyed by `binary_sha256 + canonical_va`:

```json
{
  "binary_sha256": "25d4…",
  "entries": {
    "0x00925050": {
      "reached": true,
      "entry_count": 412,
      "first_reached_from": "0x00924f80",
      "runtime_callers": ["0x00924f80"],
      "runtime_targets": ["0x00e5c780"]
    }
  }
}
```

Nothing in `spore-semantic` writes or reads that file. It is the consumer's.

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
```

No network access. No Python at runtime. No Ghidra at runtime. Standard library
only — `go.mod` has no `require` block.

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

Two exports from the same checkout state are byte-for-byte identical.