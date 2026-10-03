# Consuming the OpenSpore semantic snapshot from another project

This page is for a **sibling project** — `spore-recomp`, or anything else that
wants to ask "what does OpenSpore already know about this function?" — without
depending on OpenSpore.

Read [`semantic-exchange.md`](semantic-exchange.md) first for what the tool
is and how the format is built. This page is only about consuming it.

---

## The five things that matter

1. **The snapshot is optional.** Nothing requires you to have one. If you do not
   have a snapshot, none of this applies and your project is unaffected.
2. **OpenSpore is not a build or runtime dependency.** You need the JSON file
   and (optionally) the `spore-semantic` executable. You never need the OpenSpore
   repository, Python, Ghidra, or a network connection.
3. **You may copy or version the snapshot freely.** It is one file, it is
   deterministic, and it carries the SHA-256 of every OpenSpore artifact it was
   built from, so a consumer can record exactly which analysis produced it.
4. **`binary_sha256` must match.** The join key is
   `binary_sha256 + canonical VA`. Before trusting any answer, compare the
   snapshot's `binary.binary_sha256` against the binary *you* are analysing.
   `spore-semantic` does this for you if you set `OPENSPORE_REQUIRE_SHA`.
5. **Facts keep their provenance.** Every fact group states where it came from
   and how confident it is. Nothing is flattened into a bare value, so you can
   tell a machine fact from a researcher's claim, and you can tell "we looked
   and found nothing" from "we never looked".

**OpenSpore source is not imported as production code.** No OpenSpore file is
linked, vendored, compiled into, or `go get`-ed by a consumer. The only contract
is the JSON Lines file.

---

## What you get

```
knowledge/semantic/function-passport-v1.jsonl
```

One file:

* line 1 — the metadata record (schema, binary identity, per-input digests,
  coverage counters, content digest);
* lines 2..N — one function passport per line, sorted ascending by
  `identity.canonical_va`.

Regenerate it with:

```sh
spore-semantic export --out knowledge/semantic/function-passport-v1.jsonl
```

Regeneration from the same OpenSpore state is **byte-for-byte identical**. If
your committed snapshot and a fresh export differ, the OpenSpore artifacts
changed; diff the `metadata.inputs` digests to see which.

---

## Three ways to consume it

### 1. The CLI, as a subprocess

Simplest, and enough for a build step or an agent.

```sh
spore-semantic lookup 0x00925050 --json
spore-semantic lookup 0x00e3a400 --json          # interior VA: resolves
spore-semantic lookup-symbol RenderWare::CompiledState::SetRaster --json
spore-semantic explain 0x0040ccb0                # why OpenSpore believes this
spore-semantic stats --json
spore-semantic validate                           # exit 0 iff the file is sound
```

```jsonc
// spore-semantic lookup 0x0040ccb0 --json  (abridged)
{
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "image_base": "0x00400000",
  "requested_va": "0x0040ccb0",
  "canonical_va": "0x0040ccb0",
  "rva": "0x0000ccb0",
  "identity_resolution": null,
  "names": {
    "ghidra_name": "Transform::PreTransformBy",
    "normalized_symbol": "transform_pre_transform_by_0040ccb0",
    "sdk_name": "Transform::PreTransformBy",
    "sdk_name_source": "sdk_functions.tsv",
    "identity_refuted": null
  },
  "abi": {
    "state": "available",
    "evidence_level": "INFERRED",
    "evidence_state": "DERIVED",
    "provenance": ["reconstruction/knowledge/index.json"],
    "value": {
      "origin": "abi_inference",
      "schema": "openspore-abi-inference-1",
      "convention": "__thiscall",
      "convention_confidence": "INFERRED",
      "receiver": { "present": "true", "register": "ECX", "bounds_only": true },
      "declared": { "calling_convention": "__thiscall observed" }
    }
  },
  "vtable": { "state": "unavailable", "evidence_level": "UNKNOWN",
              "evidence_state": "MISSING", "reason": "no_vtable_membership" },
  "reconstruction": {
    "state": "available",
    "value": { "package": "WAVE6-PRESENTATION", "promoted": "false", "status": "reconstructed" }
  },
  "evidence": {
    "pack": "reconstruction/evidence/0040ccb0/evidence.json",
    "pack_state": "PERSISTED",
    "pack_content_sha256": "9975a67935c1b350d88a3b1f6ec9eca8ecaed1ffc9a0921d34fe584f98d9a47f"
  }
}
```

**Exit codes are stable.** Branch on them; do not parse stderr.

| code | meaning |
|---|---|
| 0 | success |
| 1 | usage / generic error |
| 2 | unknown function (no containing entry) |
| 3 | unknown symbol |
| 4 | binary mismatch |
| 5 | corrupted snapshot |
| 6 | unsupported schema |
| 7 | source or snapshot unavailable |
| 8 | ambiguous symbol (two or more canonical functions share a name) |

A miss never yields an empty object: it yields an explicit error naming the
requested address, the binary, and the number of functions indexed.

### 2. The snapshot as a data file

Parse the JSON Lines directly if you would rather not shell out. It is one
object per line, so it streams.

```python
import json

with open("function-passport-v1.jsonl", encoding="utf-8") as handle:
    meta = json.loads(handle.readline())
    assert meta["binary"]["sha256"] == EXPECTED_SHA
    passports = {int(r["identity"]["canonical_va"], 16): r
                 for r in map(json.loads, handle)}
```

Load time for the full 58,757-record file is ~0.65 s end to end (the CLI's own
measured peak RSS is ~164 MB). If you only need a handful of addresses, index
lazily:

```python
index = {}                     # va -> byte offset
with open(PATH, "rb") as handle:
    handle.readline()          # metadata
    offset = handle.tell()
    for line in handle:
        if b'"canonical_va":"0x00e3a270"' in line:
            index[0x00E3A270] = offset
        offset += len(line)
```

### 3. The CLI's index as a long-lived process

The CLI exits per invocation, which is fine for tens or hundreds of lookups. If
you want interactive latency, either (a) read the JSONL yourself into a
`dict`, or (b) just accept 0.6 s per invocation — the export is deliberately
built so that startup stays in the sub-second range without a database.

No SQLite, no server, no daemon.

---

## Reading the result correctly

### Unknown is not false

Six fact groups — `abi`, `vtable`, `globals`, `types`, `semantics`,
`reconstruction` — are always present as keys. Each is an envelope:

```jsonc
{ "state": "available",   "evidence_level": "...", "evidence_state": "...",
  "provenance": ["..."], "value": { ... } }

{ "state": "unavailable", "evidence_level": "UNKNOWN",
  "evidence_state": "MISSING", "reason": "no_evidence_pack" }
```

`state: "unavailable"` with a `reason` means OpenSpore *looked and found
nothing*. That is different from OpenSpore never having looked, and different
from the fact being false. `value` is omitted, not `null` — `state` is the
authority.

Inside `abi.receiver`, `present` is the **string** `"true"`, `"false"` or
`"null"`. `"null"` is meaningful: in the ABI engine it means the receiver is
undetermined and the record deliberately abstains. Do not coerce it to `false`.

Inside `abi`, `convention` is `null` when undetermined. There is no `"UNKNOWN"`
sentinel string.

`reconstruction.value.promoted` is `"true"` / `"false"` — `"false"` means there
is no promotion record, which for a reconstructed function is a real answer.

The closed set of `reason` codes:

| code | meaning |
|---|---|
| `no_evidence_pack` | no evidence pack exists for this VA, so no ABI record was derived |
| `no_abi_derived_record` | a pack exists but its `abi_derived` category holds no value |
| `no_vtable_membership` | neither the sound vftable scan nor the triage index associates a table |
| `vftable_scan_absent` | the vftable scan was not in the exporting checkout, so it could not be consulted |
| `no_global_references` | the knowledge index records no global reference |
| `no_associated_types` | the knowledge index associates no type |
| `no_semantic_record` | no semantic research record exists |
| `no_reconstruction_package` | no package, staged source, validation report or promotion record |
| `no_validation_report` | a reconstruction exists but carries no validation report |

A `reason` that is *not* in this table is source-supplied prose, carried
verbatim from the artifact (evidence packs state their own `reason`).

### Machine fact vs interpretation

Four kinds of statement live side by side and are never merged:

| kind | where |
|---|---|
| machine fact from disassembly analysis | `abi` (with `origin: "abi_inference"`) |
| SDK name | `names.sdk_name` (with `names.sdk_name_source`) |
| researcher's interpretation | `semantics`, `abi.value.declared` |
| runtime observation | `reconstruction.value.runtime_gated`, `reconstruction.value.validation.runtime` |

`reconstruction.value.runtime_gated: true` means **the gate is open, nothing was
attempted, and nothing failed**. It is not a failure and not a pass.

### Validation verdicts

`reconstruction.value.validation.coverage` carries OpenSpore's own per-dimension
verdicts verbatim: `status` is one of `PASS`, `WARN`, `FAIL`, `UNKNOWN`,
`NOT_AVAILABLE`, and `coverage` is one of `none`, `partial`, `complete`.
Reproduce those strings rather than mapping them onto your own enum, or you will
lose the distinction between `FAIL` and `NOT_AVAILABLE`.

### Interior addresses

A requested VA that is not a function entry is resolved to the entry containing
it, using the rule the OpenSpore repository already applies (bisect on entry
starts, then require `start <= a < start + size`). The response reports both:

```jsonc
{
  "requested_va": "0x00e3a400",
  "canonical_va": "0x00e3a270",
  "identity_resolution": {
    "rule": "containing_function_entry",
    "offset": 400,
    "range": { "start": "0x00e3a270", "end": "0x00e3a56b" },
    "recorded": { ... }        // what OpenSpore had already corrected, if anything
  }
}
```

`identity_resolution` is `null` when the requested VA was already an entry.

An address in the gap **between** two bodies (real padding) resolves to nothing
and is reported as an unknown function with exit code 2. That is deliberate: an
address the universe cannot place is left alone rather than guessed at.

### Names are a convenience index; addresses are the key

The universe contains duplicate names — the triage export's own notes record 92
duplicate normalized-name groups across 190 rows. So:

* `lookup` by VA is authoritative and never ambiguous.
* `lookup-symbol` exits 8 and lists every matching canonical VA when a name is
  shared. Pick by address.
* `lookup-symbol` also searches `normalized_symbol`, `sdk_name` and
  `ghidra_name`, case-insensitively.

---

## Attaching your own observations: the runtime overlay

Runtime observations belong to **you**, not to OpenSpore. Do not write them into
the snapshot. Keep a **separate overlay** keyed by
`binary_sha256 + canonical VA`, and join the two as a view.

`spore-semantic runtime` now implements and validates that overlay, so you do not
have to invent a format. The full schema, the exact list of refusals and the
tri-state rules are in
[`semantic-exchange.md`](semantic-exchange.md#63-runtime-overlays-the-consumer-side-made-explicit).
This section is the short version.

### The four rules

1. **Runtime stays external.** An overlay is a separate file. `spore-semantic
   runtime` reads it; nothing writes a runtime fact into the snapshot, an
   evidence pack, the knowledge index, a validation report or a promotion
   marker. There is no `runtime merge` command, precisely so no combined artifact
   can be mistaken for one source of truth.
2. **The join key is `binary_sha256 + canonical VA`.** Every overlay must carry
   the binary SHA-256 (mandatory) and its image base. A mismatching binary is
   refused, and so is a matching binary at a different image base (exit 9),
   because every address in the file would then mean something else.
3. **Different provenance.** Static facts carry the snapshot's vocabulary
   (`generated_index`, `committed_artifact`, `ghidra`, `derived`). Runtime facts
   carry exactly one source class, `"runtime"`, naming the producer and a portable
   artifact identifier. A runtime artifact that claimed `source_class: "ghidra"`
   would be refused.
4. **A runtime observation never upgrades a static verdict.** Every joined output
   carries `"verdict_unchanged"`. `runtime frontier` is a prioritisation report:
   `runtime_evidence_relevant` means the overlay holds observations in categories
   this build maps to a recorded blocker, **not** that the blocker is settled.

### Do you need an OpenSpore checkout? No.

```sh
# Overlay only. Every static-derived field comes back null, not zero.
spore-semantic runtime stats   --overlay ./runtime-overlay-v1.jsonl --json
spore-semantic runtime lookup  0x00925050 --overlay ./runtime-overlay-v1.jsonl --json
```

### You may already have the data

A `spore-recomp` startup-recovery report carries binary identity, the entry VA,
final EIP and CPU state, call edges (callsite, target, count, first sequence,
min/max depth), events (class, caller function, callsite, target, return address,
depth, detail), and IAT cell checks (slot, loaded value, module, symbol, bound).
Convert one without changing the producer:

```sh
spore-semantic runtime import-recomp \
  --report ../spore-recomp/work/reports/startup-recovery14.json \
  --out ./runtime-overlay-v1.jsonl
```

The adapter is one-way and read-only, and it leaves `canonical_va` null on every
entry: identity is OpenSpore's to decide.

### Unknown runtime addresses are the point

`0x00925050` is real: `spore-recomp` reached it through a vtable indirect call
during execution, and OpenSpore cannot place it — it lies between two function
bodies. A joined lookup preserves that:

```json
{
  "requested_va": "0x00925050",
  "identity": {
    "canonical_va": null,
    "canonicalization": "non_function_entity",
    "static_status": "static_non_function_entity"
  },
  "static": null,
  "runtime": { "reached": "true", "entry_count": 1, "runtime_callers": [ ... ] }
}
```

`runtime discovered, static identity not established`. No passport is
manufactured, padding is never mapped to a function, and nothing is inserted into
the static function universe.

### Producing one yourself

Join by requested VA. Note the three states that are *not* interchangeable:

```python
p   = passports.get(va)                     # static, or None
obs = overlay_by_va.get(f"0x{va:08x}")     # runtime, or None
# obs["reached"] == "null"   -> the producer did not observe this address
# obs["reached"] == "false"  -> observed, and not entered
# obs is None                 -> this address was not observed at all
```

Record the overlay's `content_sha256` and `producer.artifact` alongside your own
build metadata. That pair identifies both the exact OpenSpore analysis state and
the exact producer run a joined answer came from.

### Pinning

```sh
spore-semantic runtime validate --overlay ./runtime-overlay-v1.jsonl
OPENSPORE_REQUIRE_SHA=<my sha256> spore-semantic runtime validate --overlay ./runtime-overlay-v1.jsonl
spore-semantic runtime validate --overlay ./runtime-overlay-v1.jsonl --require-image-base 0x00400000
```

`validate` re-checks the header's own tallies against the record bodies, so a
hand-edited header is caught even when the content digest still matches.

---

## Checking the snapshot you were given

```sh
# 1. does it describe the binary I care about?
spore-semantic stats --snapshot ./function-passport-v1.jsonl --json | jq -r .binary_sha256

# 2. is it internally consistent?
spore-semantic validate --snapshot ./function-passport-v1.jsonl    # exit 0 iff OK

# 3. refuse anything that is not the binary I expect
OPENSPORE_REQUIRE_SHA=<my sha256> spore-semantic lookup 0x00925050 --snapshot ./passport.jsonl
```

`validate` recomputes the coverage counters from the record bodies and compares
them with the metadata line, so a header edited by hand is caught even when the
content digest still matches. It also confirms the records are sorted ascending
by canonical VA and that no canonical VA appears twice.

Record the snapshot's `content_sha256` and `metadata.inputs` alongside your own
build metadata. Those two together identify the exact OpenSpore analysis state a
fact came from.

---

## Versioning

The snapshot declares `schema: "spore-semantic-snapshot-1"`. This build accepts
that id and nothing else; a different id exits 6, and a record carrying fields
this build does not know also exits 6 rather than being silently half-read.
That is deliberate: a consumer must not read a future schema as if it were
today's.

A runtime overlay declares `schema: "spore-semantic-runtime-overlay-1"` and is
held to the same rule. Its observation vocabulary is closed at nine kinds
(`entry`, `call`, `indirect_call`, `return`, `import`, `exception`, `memory`,
`register`, `stack`) and its canonicalization vocabulary at four. An unknown kind
is refused rather than carried, because a producer that has started emitting a
kind this build does not know is a producer whose *meaning* may have moved, and a
half-read observation is worse than a rejected file.

When you pin a snapshot, pin it **with** its schema id and content digest.