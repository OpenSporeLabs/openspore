# The semantic bridge — what a consumer actually finds

`crates/spore-semantic-bridge` reads `knowledge/semantic/function-passport-v1.jsonl`
(58 757 records, 93.5 MiB) and lets engine code ask questions of it.

This file is **not** the format contract. That is
`docs/tooling/semantic-exchange.md` (normative) and
`docs/tooling/semantic-exchange-consumer.md` (normative). This is a report of
what is *in* the artifact as of the committed snapshot, because several things in
it are surprising and a consumer that has not measured will get them wrong.

## What it is for

Reverse-engineering knowledge, projected into an address-keyed table:

```
u32 VA -> Passport { identity, names, classification, abi, vtable, graph,
                     globals, types, semantics, reconstruction, evidence }
```

Every graded field returns `spore_core::Fact<T>`, so "we looked and found
nothing" is a first-class answer and never a zero or an empty collection.
The bridge **derives nothing**: no ABI inference, no vftable detection, no
validation. If a fact is not in the passport, the answer is `Unknown`.

It is **optional**. A missing snapshot is a typed error; the engine builds and
runs without it. That is a contract requirement, not an accident — the exchange
format says the snapshot is not a build or runtime dependency of any consumer.

## Cost

```
open              808 ms   RSS 3.4 MiB -> 14.4 MiB   (peak 16.1 MiB)
lookup one record 342 µs   RSS +1.0 MiB
stream all 58757  4.6 s     RSS +0.8 MiB
verify            338 ms   RSS +0.0 MiB
```

`open` parses line 1 eagerly, validates every record line in a streaming pass,
and keeps only a sorted 24-byte-per-record entry table (1.3 MiB) plus a name
index. It holds a **path, not a handle**: lookups open their own read-only
handle and seek. Peak growth is 11.7 % of the file size.

`verify()` reproduces `content_sha256`, which covers the **record lines only** —
line 1 is excluded, so the field is not self-referential. Verified independently:

```
sha256(record lines only) = 5920dfa1827f55c6c7d09197d77cc3e5e989f1a441b58b341a4d9ec9410f3a81
record lines               = 58757
record_bytes + header_bytes = file_bytes  (98080685)   <- proves line 1 is excluded
```

## Canonical addresses

Canonical VA spelling is **always lowercase `0x%08x`**. Input is tolerant, output
is not. `"925050"` and `"0X00925050"` are refused so one address cannot become
two entries. Bare digits are hex throughout this repository.

Interior VAs resolve by the repository's existing rule — bisect on entry starts,
then `start <= a < start + size`. The three known cases, verified independently
against the committed snapshot:

| interior | entry | offset |
|---|---|---|
| `0x00e3a400` | `0x00e3a270` | 400 |
| `0x00e7b6c0` | `0x00e7b630` | 144 |
| `0x00e7d2c0` | `0x00e7d070` | 592 |

And the case that must resolve to **nothing**: `0x00925050` lies between
`FUN_00925000` (ends `0x0092504a`) and `FUN_009250c0`. `spore-recomp` reached it
through a real vtable indirect call and OpenSpore cannot place it. The bridge
reports `NonFunctionEntity` with `canonical: None`. **That discrepancy is the
deliverable** — do not invent a mapping, do not snap it to a neighbour, and do
not widen the universe to include it.

This is a *third* transcription of that rule (`tools/reconstruction_knowledge.py`
→ `spore-semantic/internal/openspore/identity.go` → here). A second rule would be
a second source of truth for identity, which is exactly what the format forbids.
A test cross-checks against the Go CLI when it is installed.

## Engine-facing fields

Ranked by usefulness to a game engine:

| need | field | coverage |
|---|---|---|
| routing | `classification.subsystem` | 58 757 have the field; **49 340 of them say `"Unknown"`** |
| routing | `classification.category` | 6 closed values |
| named entry points | `names.sdk_name` | **1 171** of 58 757 |
| call graph | `graph.callers` / `callees` / `scc_size` | 34 639 / 41 248 / all |
| platform imports | `graph.external_callees` | 1 599 (`EXT:KERNEL32.DLL::…`) |
| dispatch | `vtable.memberships[{table_va, slot, slot_width}]` | 6 340 |
| reconstruction state | `reconstruction.value.{package, promoted, runtime_gated}` | 727 / 92 promoted |
| open questions | `semantics.value.unresolved_questions[]` | 536 |

Filter on `subsystem`, **not** `cluster`: `cluster` is null on 58 389 of 58 757.
And check `has_named_subsystem()` before routing — an always-present field that
usually says `Unknown` is not the same as a populated one.

`vtable.memberships` is exposed with a `byte_displacement()` method so the
documented trap has no spelling available: **reach a slot by byte displacement,
never by array subscript**, because `table[1].slot1` advances by
`sizeof(StateInterface)` — a whole *pair* of slots — while `MOV EDX,[EAX+n]`
advances by `n * 4`. They agree only at `n == 0`.

`reconstruction.value.runtime_gated` is a tri-state, and `true` means **"the gate
is open, nothing was attempted, nothing failed"** — not a failure, not a pass.
It is `null` on 113 of the 727 reconstructed records, so the `Unstated` variant
is not hypothetical.

## Six things in the artifact that will bite a consumer

1. **`classification.evidence` uses `APPROX`**, not `APPROXIMATION`, on 1 500
   records. It is the only grade in the whole file off the shared 7-rung scale;
   envelope `evidence_level`, `abi.*.confidence` and `vtable.abi_attributed.confidence`
   are all on-scale. The bridge degrades this one field to `Unknown` and keeps the
   raw spelling, because mapping it would be a cross-vocabulary guess and
   refusing it would make 1 500 records unreadable over a spelling.
2. **`metadata.counts.with_subsystem` is 58 757** — every record has a subsystem
   field — while `classification.subsystem` is the literal string `"Unknown"` on
   49 340 of them.
3. **All 92 promotion records and all 672 validation reports spell their path
   with a literal zero VA**: `reconstruction/evidence/00000000/promotion.json`,
   while the sibling `pack` field on the same records is correct
   (`reconstruction/evidence/0040ccb0/evidence.json`). These are placeholders, not
   per-VA paths.
4. **The docs say `vtable.triage_addresses` is a `string[]` of bare 8-hex.** All
   19 646 emitted values are `0x`-prefixed lowercase. The bridge follows the bytes
   and refuses a bare `013f05d8`.
5. **`globals.value` is sometimes prose**: `"global:No direct gameplay-global
   data references were identified in the target body."` Carried verbatim.
6. **`metadata` is 1 028 861 bytes** — 1.05 % of the file — and carries 685 input
   digests. Read it once; do not assume it is a header.

## Rules the bridge enforces, and one place it cannot

Enforced: unknown JSON field is a **schema** error, not corruption (mirroring
the Go exit 6 vs exit 5 split); only lowercase `0x%08x` is a canonical VA;
`provenance[].source_class` claiming `runtime` on a static record is refused (a
static artifact wearing a runtime file's schema); an ambiguous symbol name is
reported as ambiguous, not resolved; unavailable facts are never defaults.

**Not enforced, by necessity**: six upstream fields are open-shaped
(`promotion_supersedes`, `runtime_blocking_reason`, `semantics.value.confidence`,
`validation.static_rollup`, `identity_refuted.*`). Their field *names* are
checked and their bytes carried verbatim, but a schema change *inside* one of
them passes through instead of being refused. Enforcing more would mean inventing
a shape for an artifact this crate does not own. The full list, with reasoning,
is in the crate's own documentation.

Runtime overlays are **not read**. OpenSpore is the static side; the overlay is a
consumer's own artifact, and the format deliberately has no `merge` command.