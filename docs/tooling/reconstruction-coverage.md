# Reconstruction coverage report

Engine: `tools/reconstruction_tooling/coverage.py`
Artifact: `reconstruction/knowledge/coverage.json`, schema `openspore-reconstruction-coverage-1`
CLI: `python3 tools/openspore.py coverage`

## 1. What this report is, and the number it refuses to give

This report answers one question: *of the parts of `SporeApp.exe` that OpenSpore has
touched, which parts are actually reconstructed, decompiled, semantically classified,
evidenced, queued, or runtime-validated?* It answers it as a **matrix of
separately-defined dimensions**, each with its own universe, its own provenance class,
its own source of truth, and its own explicit counting rule.

It deliberately publishes **no single "percent complete" number**, and any tool or
document that presents one is doing arithmetic the evidence does not support. The
reason is not stylistic caution. The dimensions are not measurements of the same
quantity at different precision; they are measurements of *different* quantities:

* they are defined over **different universes** — 58,757 internal functions, 2,149
  gameplay functions, 300 manifest records, 368 triage-queue rows, and 8 evidence
  classes that overlap none of these;
* they are drawn from **different provenance classes** — git-tracked artifacts that
  survive a fresh clone, untracked-but-not-ignored artifacts, and a gitignored SQLite
  sidecar that does not survive a fresh clone at all;
* they sit on **different evidence ladders** — a `name_evidence` of `SUPPORTED` and a
  `contract_status.semantic_understanding` of `partial` are not commensurable;
* a meaningful fraction of them are **saturated by construction**, where the covered
  set *is* the universe and any percentage would be the identity `100.0` rather than a
  measurement.

Averaging them requires weights, and any weight vector is an editorial claim about
what "complete" means. The report therefore emits a matrix plus an explicit
`cannot_determine` list (`coverage.json#cannot_determine`) whose last entry is named
`a single overall completion percentage`. `coverage.json#generator_status.composite_score`
reads `deliberately absent; see caveats`.

The engine's own header states the same contract (`coverage.py:1-38`), and the
determinism and read-only contracts are separate sections of the same docstring.

## 2. How to reproduce

```bash
# read-only, writes nothing, prints the report
python3 tools/openspore.py coverage
python3 tools/openspore.py coverage --json
python3 tools/openspore.py coverage --markdown

# restrict the matrix to the gameplay universe / add history checkpoints
python3 tools/openspore.py coverage --gameplay
python3 tools/openspore.py coverage --history --json

# skip the gitignored machine-local SQLite inputs
python3 tools/openspore.py coverage --no-local-db

# the only permitted write, and it is explicit opt-in
python3 tools/openspore.py coverage --out reconstruction/knowledge/coverage.json
```

### Determinism check

The engine is deterministic: two runs on the same artifact bytes produce byte-identical
output. Verified on this repository state:

```bash
python3 tools/openspore.py coverage --out /tmp/a.json
python3 tools/openspore.py coverage --out /tmp/b.json
cmp /tmp/a.json /tmp/b.json          # no output
```

Both runs produce the same sha256, and so do two `--json` runs to stdout. **Do not expect
that digest to match `reconstruction/knowledge/coverage.json`**: that file is *untracked*
and is a point-in-time snapshot, so it drifts behind the generator as soon as any agent
touches an untracked input. Regenerate it (`--out reconstruction/knowledge/coverage.json`)
before treating it as the reference, and re-run this check if you do. The determinism claim
is about two runs over identical inputs, never about a stored digest.

### Read-only contract

* `coverage.json#generator_status.read_only` = `true`;
  `writes` = `none unless --out is passed explicitly`.
* `generator_status.takes_machine_lock` = `false`. A read-only reporter must never park
  other agents, so it does not take `tools/observatory/lock.py`'s machine lock.
* `generator_status.imports_no_writing_subsystem` = `true`. The module imports nothing
  from `queue`, `orchestrate`, `integrate`, `swarm`, `evidence`, `context`, or
  `recover`.
* `generator_status.sqlite_mode` = `ro`; the database is opened through a read-only URI
  (`coverage.py:579`).
* `generator_status.timestamp_free` = `true` and
  `no_absolute_paths_in_body` = `true`.
* `openspore coverage` with no flags writes no file, no database row, no queue row, no
  claim, and no manifest entry.

### Flag caveat

The engine reads a `no_untracked` argument (`coverage.py:2501`) but
`tools/reconstruction_tooling/cli.py:110-115` does not register a `--no-untracked`
flag, so the switch is reachable only through the Python API, not the CLI. This is a
real gap between the engine and its parser; it is recorded here rather than silently
worked around.

## 3. Snapshot identity

> **The committed artifact is a snapshot, not the source of truth.**
> `reconstruction/knowledge/coverage.json` is untracked and lags the generator whenever an
> agent adds an untracked input. Every number in this document was transcribed from one
> run; if a row disagrees with the artifact, **regenerate the artifact** rather than
> trusting either copy. The generator is `coverage.py`; the artifact is only its output.

`coverage.json#snapshot` pins the binary identity and fingerprints every input.

| field | value |
|---|---|
| `binary_sha256` | `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e` |
| `binary_version` | `3.1.0.22` |
| `image_base` | `0x00400000` |
| `input_drift` | `[]` |

`binary_sha256` agrees with the file on disk: `sha256sum SPORE/SporeBin/SporeApp.exe`
returns the same digest. The reporter does **not** hash that file itself — it copies
the identity block out of the manifest, because hashing a gitignored directory would
make the report depend on a path a fresh clone does not have
(`coverage.json#caveats`, entry 6).

`input_drift: []` is the load-bearing field. Every input is fingerprinted
(sha256 + size + mtime) *before* it is read, the hash is taken from the very buffer that
is parsed, and the input is fingerprinted again afterwards. A changed fingerprint, or a
member that is present but unparseable, raises
`ToolError("input_changed_during_read", ...)` rather than retrying a torn read. A member
that has merely *vanished* is benign and skipped. `input_drift` is emitted as a stable
empty list — the assertion is the point (`coverage.py:26-35`).

### Per-input table

14 inputs. Directory inputs have `sha256: null` by design, because a directory has no
single content hash; member hashes are individually reproducible.

| input | path | present | bytes | members | tracked members | `git_tracked` | `tracked_verdict` |
| --- | --- | --- | ---: | ---: | ---: | --- | --- |
| `coverage_ledger` | `knowledgegraph/research/21-decompilation-coverage.json` | yes | 49,709,906 | — | — | true | `tracked` |
| `decomp_gap_parts` | `knowledgegraph/research/decomp-gap/*.json` | yes | 36,016,940 | 16 | 16 | true | `tracked` |
| `evidence_dir` | `reconstruction/evidence/*/` | yes | — | 20 | 0 | false | `untracked` |
| `handoff_dir` | `reconstruction/integrated/**/handoff.json` | yes | 349,936 | 25 | 14 | true | `tracked` |
| `kg_db` | `knowledgegraph/spore.db` | yes | 109,469,696 | — | — | false | `untracked` |
| `knowledge_index` | `reconstruction/knowledge/index.json` | yes | 6,868,101 | — | — | false | `untracked` |
| `manifest` | `knowledgegraph/research/source-reconstruction-manifest.json` | yes | 1,664,241 | — | — | true | `tracked` |
| `metadata_dir` | `reconstruction/metadata/**/*.json` | yes | — | 338 | 101 | true | `tracked` |
| `residual_unknown` | `knowledgegraph/research/residual-unknown-priority.json` | yes | 49,365,824 | — | — | true | `tracked` |
| `runtime_oracle` | `knowledgegraph/research/runtime-oracle.json` | yes | 89,076 | — | — | true | `tracked` |
| `semantic_blueprint` | `knowledgegraph/research/semantic-blueprint.json` | yes | 28,839,863 | — | — | true | `tracked` |
| `semantic_decomp` | `knowledgegraph/research/semantic-decomp.json` | yes | 1,332,852 | — | — | true | `tracked` |
| `staging_dir` | `reconstruction/staging/*/` | yes | 4,405,568 | 472 | 168 | false | `untracked` |
| `triage_queue` | `knowledgegraph/triage/queue-f0e310e0-v6.json` | yes | 454,392 | — | — | true | `tracked` |

Ten inputs are git-tracked; four are not.

### The one non-content-deterministic field

`git_tracked` and `tracked_verdict` are the report's **only** host probe, and
`generator_status.host_probes` discloses it rather than hiding it. They come from
`git ls-files --error-unmatch` (`coverage.py:259`), i.e. from the **git index at read
time**, not from the working tree. A concurrent `git add` or `git rm --cached` changes
those fields with no artifact byte changing. The report says so itself: *two reports of
byte-identical artifacts can differ in these fields alone; that difference is NOT engine
nondeterminism*. It also states the mitigation: no other host probe is performed — no
source-index presence check, no hostname, no environment read, no developer-tool index
probe. `generator_status.host_probes[0].content_deterministic` is `false`; every other
field is a pure function of artifact content.

Note that `git_tracked: true` on a *directory* input is a partial truth, and the
snapshot publishes member counts next to the verdict precisely so a reader is not misled:
`metadata_dir` is tracked but only 101 of its members are, and `handoff_dir` is tracked
but only 14 of 25. `decomp_gap_parts` is the one directory with
`tracked_members_is_all: true`.

`staging_dir` is the exception to the "no single content hash" rule: it carries a real
`sha256`, computed as a member aggregate over the sorted
`relpath\0member-sha256\0member-bytes` lines of every `.json`/`.cpp`/`.hpp`/`.sh`
member, so a C++ edit changes it and it is content-derived, never mtime-derived.

### What is not reproducible from a fresh clone

Stated plainly, dimension by dimension, because this is the difference between a number
you may publish and a number that only exists on one machine:

| class | inputs | survives a fresh clone |
|---|---|---|
| tracked | the 10 tracked inputs above | yes |
| machine-local | `knowledgegraph/spore.db` | **no** — gitignored (`.gitignore:29`, `*.db`); a fresh clone has no `xref` table at all |
| untracked | `reconstruction/knowledge/index.json`, `reconstruction/evidence/*/`, `reconstruction/staging/*/` | **no** — present only in a working tree that has run the generators and waves |
| partially tracked | `reconstruction/metadata` (101/328), `reconstruction/integrated` handoffs (14/25) | only the tracked fraction |

`coverage.json#snapshot.source_input_hash_verification.agrees_with_recomputed` is `true`,
so the ledger's self-reported census is reconciled against the recomputed one rather
than trusted.

## 4. Denominators, and the denominator trap

This is the section that decides whether a reader of the matrix is misled or informed.

### The three universes

| universe | count | source of truth | notes |
|---|---:|---|---|
| `internal_functions` | 58,757 | `knowledgegraph/research/21-decompilation-coverage.json#ledger` | the **only** per-function artifact covering the whole binary; 58,757 rows, 58,757 distinct VAs, `duplicate_vas: 0` |
| `gameplay_functions` | 2,149 | same ledger, `triage_category ∈ {GAMEPLAY_LOGIC, GAMEPLAY_SUPPORT}` | cross-confirmed twice over, below |
| `non_gameplay_functions` | 56,608 | universe minus the gameplay set | a **residual**, not an independently sourced universe |

The gameplay set is cross-confirmed three ways, which is why it is safe to use as a
denominator:

1. by definition — the ledger's `triage_category` in the two gameplay categories;
2. by an independent field — selecting ledger rows where `gameplay_affinity ==
   "gameplay"` yields the identical VA set (both 2,149, set-equal);
3. by an independent artifact — `knowledgegraph/research/semantic-blueprint.json#functions[]`
   contains 2,149 distinct VAs whose set is set-equal to the gameplay set.

`coverage.json#universes.gameplay_definition.independently_confirmed_by` records (3) as
the artifact-level confirmation.

### The trap

Three distinct hazards, all of which appear in the matrix:

**Different dimensions use different denominators.** Some rows divide by 58,757, some
by 2,149, and two (`integrated_reconstruction_record` and
`runtime_gated_reconstruction_va`) use 300; three more use a saturated self-defined
denominator (56,608, 42 and 1). The `universe` column is in the table
precisely so that a reader never has to guess. Dividing a gameplay numerator by 58,757
understates it by a factor of roughly 27; dividing a universe numerator by 2,149
overstates it by the same factor.

**A few dimensions are saturated by construction.** Where the covered set *is* the
universe, any percentage is the identity `100.0`, not a measurement. The report marks
these `pct: null` plus `pct_is_tautological: true`, with the reason in
`pct_null_because`, and `render_markdown` renders them as `-`
(`_md_cell` at `coverage.py:2443-2444`, table loop at `2466-2473`). There are 6 such dimensions: `total_internal_functions`,
`gameplay_functions`, `non_gameplay_functions`, `staged_va`, `blocked_va`, and
`has_subsystem`. Three more are emitted `available: false`: `withheld_va` and
`runtime_unavailable` because the underlying category does not exist at all, and
`evidence_runtime` because the category exists but is *empty* — no decomp-gap record
carries positive runtime evidence, so it is reported unavailable rather than
available-with-zero.

**The universe is not closed.** Seven real, accounted-for addresses lie *outside* the
58,757-row universe, so any percentage quoted against 58,757 silently excludes them:

| out-of-universe set | count | addresses | source |
|---|---:|---|---|
| reconstructed manifest VAs | 4 | `00b5b880`, `00b5b8a0`, `00b5b8c0`, `00b5b8e0` | `coverage.json#reconstruction.out_of_universe` |
| triage-queue rows | 3 | `00e3a400`, `00e7b6c0`, `00e7d2c0` | `coverage.json#dependencies.out_of_universe` |

They are **preserved and reported separately, never discarded and never merged**
(`coverage.json#caveats`, entry 7). The 4 reconstructed VAs are *also* absent from
`metrics.accounting_exclusions`, so no frozen list accounts for them either
(`coverage.json#blind_spots[7]`). Metadata records land the same way: 332 of 336
distinct metadata VAs are in the universe and 4 are outside it.

The three out-of-universe queue rows are real actionable work items, which is why
`in_actionable_frontier` is deliberately **not** intersected with the universe; the
in-universe subset (228) is published alongside it (231).

## 5. The coverage matrix

All 50 dimensions, in eight labelled blocks.

> **Snapshot drift.** The rows derived from `reconstruction/metadata`,
> `reconstruction/staging` and `reconstruction/evidence` are functions of
> *untracked* working-tree directories, so they move whenever an agent adds a
> file. The transcribed values below were taken from one run; if a row disagrees
> with `reconstruction/knowledge/coverage.json`, regenerate
> (`python3 tools/openspore.py coverage --out reconstruction/knowledge/coverage.json`)
> rather than trusting this document. The ledger-derived rows (universe, gameplay,
> all six decompilation rows, manifest, queue, semantics) are git-tracked inputs
> and do not drift. Table shape matches `render_markdown`.
`-` in a numeric column means the value is `null` in the artifact: either a tautological
percentage (§4) or a dimension emitted `available: false`.

### UNIVERSE

These three rows are the scaffolding, not findings. Each is a census with zero
information content by construction, which is exactly why they carry `-` rather than
`100.0`.

| dimension | covered | universe | pct | gameplay covered | gameplay pct | provenance | available |
| --- | ---: | ---: | ---: | ---: | ---: | --- | --- |
| total_internal_functions | 58757 | 58757 | - | 2149 | 100.0 | tracked | yes |
| gameplay_functions | 2149 | 2149 | - | 2149 | 100.0 | tracked | yes |
| non_gameplay_functions | 56608 | 56608 | - | 0 | 0.0 | derived | yes |

`non_gameplay_functions` is `derived`, not `tracked`: it is the universe minus the
gameplay set and has no independent source of truth. Its `gameplay_covered` of 0 is
correct by construction (a non-gameplay set cannot contain a gameplay row) and is
therefore also a tautology in the gameplay column.

### DECOMPILATION

This block is the real shape of the analysis gap. 478 of 58,757 functions have a
persisted decompiler body; 58,277 have no **ledger-recorded** decompilation evidence. Note
that `staging_decomp_candidate` (184) is *the same 478 body population narrowed by queue
membership*, not additional decompilation, and that `live_only_decomp_observation` (184)
is a dimension union over the decomp-gap partitions, not a decompilation count.

**The three decompilation dimensions live in three different universes and must never be
added.** `persisted_decompilation` and `any_decompilation_evidence` are read off the
ledger's `body_available` / `decomp_state`; `live_only_decomp_observation` is read off the
tracked `decomp-gap/*.json` partitions. The report computes the relations rather than
asserting them, and they are the whole explanation for why 480 looks too small:

| relation | value | published as |
|---|---:|---|
| `persisted ∩ any_decomp` | 478 | `superset_of_persisted_decompilation: true` |
| `any_decomp − persisted` | 2 | `any_minus_persisted`, both `snapshot_only` |
| `any_decomp + no_decomp` | 58,757 | `any_plus_no_equals_universe: true` |
| `live_only ∩ any_decomp` | **0** | `intersects_any_decompilation_evidence: []` |
| `live_only ⊆ no_decomp` | **184** | `contains_live_only_observations: 184` |
| `any_decomp ∪ live_only` | **664** | `union_with_live_only` |
| `persisted ∪ live_only` | 662 | `persisted_union_with_live_only` |
| `(any_decomp ∪ live_only) ∩ gameplay` | 357 | `union_with_live_only_gameplay` |
| `live_only ⊆ any_decomp` | **false** | `live_only_is_subset_of_any: false` |
| `live_only ⊆ gameplay` | true | `all_gameplay: true` |
| decomp-gap records read / with a VA | 1,977 / 1,977 | `gap_records_read`, `gap_records_with_va` |

So 480 is not "every function anyone ever decompiled" — it is "every function the ledger
records as decompiled", and the 184 live-only observations sit *outside* that set, inside
`no_decompilation_evidence`. So 480 + 184 is **not** a decompilation total: it adds a
persistence census to an observation census. Because the two sets happen to be disjoint,
480 + 184 does happen to equal `any_decomp ∪ live_only` = 664 — but the union of the
*persisted* bodies with live-only is 662, because `any_decomp` is 2 rows larger than
`persisted_decompilation`. The two unions differ by exactly those 2 `snapshot_only` rows,
and conflating them is how 480 gets "corrected" to 662.

| dimension | covered | universe | pct | gameplay covered | gameplay pct | provenance | available |
| --- | ---: | ---: | ---: | ---: | ---: | --- | --- |
| persisted_decompilation | 478 | 58757 | 0.8135 | 172 | 8.0037 | tracked | yes |
| any_decompilation_evidence | 480 | 58757 | 0.8169 | 173 | 8.0503 | tracked | yes |
| no_decompilation_evidence | 58277 | 58757 | 99.1831 | 1976 | 91.9497 | tracked | yes |
| live_only_decomp_observation | 184 | 58757 | 0.3132 | 184 | 8.5621 | tracked | yes |
| staging_decomp_candidate | 184 | 58757 | 0.3132 | 59 | 2.7455 | derived | yes |
| reconstructed_without_persisted_decompilation | 149 | 58757 | 0.2536 | 47 | 2.1871 | derived | yes |

`no_decompilation_evidence` is an **absence of evidence**, not a claim that decompilation
is impossible, and it is a *persistence* census rather than a "never decompiled" census:
all 184 `live_only_decomp_observation` VAs are counted inside it, because the ledger
records `decomp_state: "unavailable"` for each of them even though a decompiler body was
observed. Read it as "no **ledger-recorded** decompilation evidence"; the plain reading
("no decompilation evidence of any kind") is contradicted by the same artifact.
`any_decompilation_evidence` (480) is a strict superset of `persisted_decompilation` (478)
and includes 2 `snapshot_only` rows that are *not* persisted bodies — but it is **not** a
superset of `live_only_decomp_observation`, which is a different universe entirely. 477 of
the 478 bodies live under the gitignored `.spore-analysis/` (the 478th, `00e806b0`, is
tracked at `tools/re/data/decompiled/`), so the tracked decompiler `.c` output does not
account for the block.

`reconstructed_without_persisted_decompilation` is a historical id whose `covered` (149) is
the **with**-set: manifest VAs that *also* carry a persisted body. The label states what is
counted, and the complement the id implies is published as
`covered_without_persisted_body` (151). The id is retained so existing consumers do not
break.

### RECONSTRUCTION

300 manifest records, 299 integrated, 1 blocked. The 42 staged VAs are a work state and
are never added into any integrated figure. `withheld_va` is emitted `available: false`
on purpose: the word "withheld" is not a canonical term anywhere in this repository, and
inventing a count for it would invent a category (§11).

| dimension | covered | universe | pct | gameplay covered | gameplay pct | provenance | available |
| --- | ---: | ---: | ---: | ---: | ---: | --- | --- |
| integrated_reconstruction_record | 299 | 300 | 99.6667 | 146 | 6.7939 | tracked | yes |
| integrated_unique_va | 299 | 58757 | 0.5089 | 146 | 6.7939 | derived | yes |
| integrated_gameplay_va | 146 | 2149 | 6.7939 | 146 | 6.7939 | derived | yes |
| staged_va | 42 | 42 | - | 25 | 1.1633 | untracked | yes |
| blocked_va | 1 | 1 | - | 1 | 0.0465 | tracked | yes |
| withheld_va | - | 58757 | - | - | - | derived | no |
| metadata_only_record | 37 | 58757 | 0.063 | 24 | 1.1168 | untracked | yes |
| runtime_validated_reconstruction_va | 0 | 58757 | 0.0 | 0 | 0.0 | mixed | yes |
| runtime_gated_reconstruction_va | 299 | 300 | 99.6667 | 136 | 6.3285 | tracked | yes |

99.6667% of the *manifest* is integrated, which sounds near-complete and is the single
most misleading number in the report if quoted alone: the manifest is a work list of
chosen targets, not a sample of the binary. 146 of 2,149 gameplay functions are
integrated (6.7939%), and 0 are runtime-validated.

### SEMANTICS

Every row in this block except `semantic_positive_any` is a count over a 32-record
corpus presented against a 58,757 denominator, which the report flags directly: the
58,757 figure is overwhelmingly **not-applicable**, not failed. The tiers are only ever
assigned to gameplay rows.

| dimension | covered | universe | pct | gameplay covered | gameplay pct | provenance | available |
| --- | ---: | ---: | ---: | ---: | ---: | --- | --- |
| semantic_strong | 4 | 58757 | 0.0068 | 4 | 0.1861 | tracked | yes |
| semantic_bounded | 8 | 58757 | 0.0136 | 8 | 0.3723 | tracked | yes |
| semantic_structural_only | 5 | 58757 | 0.0085 | 5 | 0.2327 | tracked | yes |
| semantic_needs_runtime | 15 | 58757 | 0.0255 | 15 | 0.698 | tracked | yes |
| semantic_still_unknown | 0 | 58757 | 0.0 | 0 | 0.0 | tracked | yes |
| semantic_unclassified | 58725 | 58757 | 99.9455 | 2117 | 98.5109 | derived | yes |
| semantic_positive_any | 976 | 2149 | 45.4165 | 976 | 45.4165 | derived | yes |

`semantic_unclassified` at 99.9455% **is** the finding, not a failure of the report.
See §8.

### EVIDENCE

Eight classes, each with an `available` and a `sufficient` count that are deliberately
different claims. `evidence_calls` (49,451) is dominated by the gitignored SQLite xref
table and is therefore a lower bound and not clone-reproducible; `evidence_runtime` is
emitted `available: false`.

| dimension | covered | universe | pct | gameplay covered | gameplay pct | provenance | available |
| --- | ---: | ---: | ---: | ---: | ---: | --- | --- |
| evidence_globals | 20 | 58757 | 0.034 | 14 | 0.6515 | untracked | yes |
| evidence_fields_offsets | 51 | 58757 | 0.0868 | 36 | 1.6752 | untracked | yes |
| evidence_constants | 21 | 58757 | 0.0357 | 17 | 0.7911 | untracked | yes |
| evidence_control_flow | 50 | 58757 | 0.0851 | 21 | 0.9772 | untracked | yes |
| evidence_virtual_dispatch | 26 | 58757 | 0.0443 | 14 | 0.6515 | untracked | yes |
| evidence_abi | 337 | 58757 | 0.5735 | 171 | 7.9572 | mixed | yes |
| evidence_calls | 49451 | 58757 | 84.1619 | 2104 | 97.906 | mixed | yes |
| evidence_runtime | - | 58757 | - | 0 | 0.0 | tracked | no |

### KNOWLEDGE GRAPH

The first three rows are `machine_local`; `has_type_association` is `mixed` but carries a
`machine_local: true` flag because half of it comes from the same
gitignored SQLite sidecar. All four are the reason §17
exists: they read the whose `triage` table is classifier **triage-v4**, not the v6
the ledger was built from. The local DB therefore *undercounts* the gameplay set, so the
`gameplay pct` column here understates reality. `has_subsystem` is saturated and carries
almost no information: 27 distinct subsystem values over 58,757 rows, while the
knowledge-graph edge census for `belongsToSubsystem` covers only 3,880.

| dimension | covered | universe | pct | gameplay covered | gameplay pct | provenance | available |
| --- | ---: | ---: | ---: | ---: | ---: | --- | --- |
| functions_with_caller | 33643 | 58757 | 57.2579 | 1780 | 82.8292 | machine_local | yes |
| functions_with_callee | 41031 | 58757 | 69.8317 | 1681 | 78.2224 | machine_local | yes |
| functions_with_any_call_role | 49451 | 58757 | 84.1619 | 2104 | 97.906 | machine_local | yes |
| has_triage_classification | 19041 | 58757 | 32.4064 | 2149 | 100.0 | tracked | yes |
| has_name_evidence | 18874 | 58757 | 32.1221 | 2149 | 100.0 | tracked | yes |
| has_subsystem | 58757 | 58757 | - | 2149 | 100.0 | tracked | yes |
| has_type_association | 6807 | 58757 | 11.585 | 611 | 28.4318 | mixed | yes |
| has_package_membership | 2344 | 58757 | 3.9893 | 2149 | 100.0 | derived | yes |
| has_dependency_record | 204 | 58757 | 0.3472 | 78 | 3.6296 | tracked | yes |

`has_triage_classification` and `has_name_evidence` at 100% on the gameplay column mean
*the gameplay set was triaged*, not that the classifications are strong. `UNKNOWN` on
either axis means unclassified or unevidenced, never incorrectly classified.

### RUNTIME

Two zeros, one gated count, and one null. The null row is deliberate: no record in the
repository
carries a `runtime_unavailable` field, so the report emits `available: false` plus the
capability status instead of fabricating a count. See §7 for why 299 gated is not
failure.

| dimension | covered | universe | pct | gameplay covered | gameplay pct | provenance | available |
| --- | ---: | ---: | ---: | ---: | ---: | --- | --- |
| runtime_validated | 0 | 58757 | 0.0 | 0 | 0.0 | mixed | yes |
| runtime_gated | 299 | 58757 | 0.5089 | - | - | tracked | yes |
| runtime_unavailable | - | - | - | - | - | derived | no |
| runtime_negative | 0 | 58757 | 0.0 | 0 | 0.0 | tracked | yes |

### FRONTIER / DEPENDENCY

231 of 58,757 functions are in the actionable frontier, cross-checked against the
knowledge index at the same value. `dependency_closed` (500) and `dependency_uncertain`
(0) are **alternative states**, not additive quantities; both are counted against the
2,149 gameplay universe because the callee lists come from the gameplay blueprint. Zero
uncertain means no truncation flag is set, *not* that every dependency is genuinely
known.

| dimension | covered | universe | pct | gameplay covered | gameplay pct | provenance | available |
| --- | ---: | ---: | ---: | ---: | ---: | --- | --- |
| in_triage_queue | 365 | 58757 | 0.6212 | 236 | 10.9819 | tracked | yes |
| in_actionable_frontier | 231 | 58757 | 0.3931 | 182 | 8.4691 | derived | yes |
| dependency_closed | 500 | 2149 | 23.2666 | 500 | 23.2666 | tracked | yes |
| dependency_uncertain | 0 | 2149 | 0.0 | 0 | 0.0 | tracked | yes |

## 6. Counting rules that prevent double counting

Every rule below is implemented in `coverage.py` and re-derived independently against
the raw artifacts for this document. The rules are not stylistic; each one exists
because the naive reading produces a wrong number.

**1. A function with both a persisted body and an integrated reconstruction is ONE unique
VA.** Dedup is by normalized VA: `normalize_va(f.get("va") or f.get("function_address"))`,
lowercased 8-hex, via `tools/reconstruction_tooling/models.py:21-33`. The
`persisted_decompilation` and `integrated_unique_va` sets are separate universes and are
never added together. The manifest holds 300 records with 300 distinct VAs (0
duplicates), which is why the record count and the unique-VA count coincide here — a
coincidence of this snapshot, not a rule.

**2. A package is not a function.** 65 package records ≠ 300 function records, and this
is a live trap, not a hypothetical one:

| quantity | value | source |
|---|---:|---|
| `packages[]` records | 65 | `coverage.json#reconstruction.packages` |
| packages carrying a `functions` key | 43 | `reconstruction.packages_with_functions_key` |
| distinct VAs inside `packages[].functions` | 154 | `reconstruction.packages_functions_distinct_vas` |
| `functions[]` records | 300 | `reconstruction.records` |
| distinct package ids referenced by function records | 86 | `reconstruction.record_package_ids` |
| referenced package ids **absent** from `packages[]` | 21 | `reconstruction.record_package_ids_absent_count` |

`packages[].functions` covers only 154 of 300 records, and 21 of the 86 referenced
package ids do not exist in `packages[]` at all. Deriving function coverage from
packages is therefore wrong by construction. Note also that
there is also **no** declared completion split to check a total against: no package
record carries a `complete` field, and the `packages[]` status census is
`{integrated: 64, in_progress: 1}` over 65 records — every package is accounted for, so
"complete + in_progress ≠ declared" is not a claim any artifact supports. Never derive
functions from packages.

**3. A live Ghidra observation that was never persisted is NOT persisted
decompilation.** The 184 live-only VAs are disjoint from the 172 gameplay persisted bodies
*and* from the whole 480-row ledger-recordable decomp population. The report computes
`persisted_vs_live_overlap` and `intersects_any_decompilation_evidence` rather than
asserting disjointness. A live observation that was never written to disk is an
observation, not a decompilation artifact.

The disjointness holds, but the mechanism is a **cross-artifact identity**, not anything
`has_live_static_body` does. `has_live_static_body` (`coverage.py`, a verbatim port of
`synthesize.py:250-264`) is a *content filter over record leaves*: it says which records
mention a recovered body, and it says nothing about how those records were selected. The
real guarantee is upstream of it: the 16 tracked partitions are an exact, complete,
non-overlapping partition of the track-B gap universe, defined at `synthesize.py:159` as
`gameplay_affinity == "gameplay" and decomp.available is False` (1,977 VAs — the same
number as 2,149 gameplay − 172 gameplay persisted), and the ledger's `body_available` is
the same fact as that `decomp.available` under a different name. Verified on this
snapshot: the partition VA set equals the track-B gap universe set-equal in both
directions, and the two fields disagree on 0 of 58,757 rows. So `persisted ⊆ complement of
the gap universe` and `live_only ⊆ gap universe`.

This is a verified fact about the current artifacts, **not** an invariant the code
enforces: nothing asserts the `body_available ≡ decomp.available` identity. 14 of the 16 partitions state the
`decomp.available == false` predicate in a dedicated machine-readable field
(`partition.active_target_predicate`, `assignment.track_b_predicate`,
`assignment.exact_track_b_predicate_source`, `partition.predicate`); the two that do not
are `hold-infrastructure` (its predicate covers cluster and readiness only) and
`ui-shell-00` (whose `selection_predicate` names `decomp_path == null`). So the guarantee
rests on their provenance as `synthesize.py` output, not on anything uniform the report
can read — and the reporter does not check it. Treat the
disjointness as something the report *measures* and re-checks on every run, not as
something it can rely on. A live observation that was never written to disk is an
observation, not a decompilation artifact.

**3a. The three decompilation dimensions are not addable.** `any_decompilation_evidence`
(480) is a *ledger* count; `live_only_decomp_observation` (184) is a *decomp-gap
partition* count; the 184 are all inside `no_decompilation_evidence` (58,277), i.e. inside
the complement of the 480. `480 + 184` is not a decompilation total, and
`58,757 − 58,277 = 480` does not mean 480 functions have a body. Because the two sets are
disjoint, `any_decomp ∪ live_only` = 480 + 184 = **664**; the *persisted* union is
**662**. The report publishes both under names that say which sets they union
(`union_with_live_only` = 664, `persisted_union_with_live_only` = 662) plus
`do_not_add_to_ledger_decomp_dimensions`, so the 2-row difference cannot be lost and the
addition cannot be made by accident.

**4. A metadata record without a function VA must not inflate function coverage.** 37
metadata VAs have no manifest record (`reconstruction.metadata_vas_without_manifest_record`),
and all 37 are also absent from `metrics.accounting_exclusions` — nothing else accounts
for them. Metadata files (338) outnumber manifest records (300), and 338 files resolve
to only 336 distinct VAs, because 2 VAs carry two metadata files each (`005bf9d0`,
`008db310`). So both the file count (338) and the record count (300) are wrong
denominators for "how many functions have metadata".

**5. Multiple metadata records for one VA must not inflate unique-function coverage.**
338 files → 336 distinct VAs. The dimension `metadata_only_record` counts *distinct VAs*,
never files.

**6. Runtime-gated is NOT runtime-failed. UNKNOWN is NOT incorrect.** Both are absences
of evidence. `UNKNOWN` on `triage_category` or `name_evidence` means unclassified;
`runtime_gated` means a required capability on the original process is still open.
See §7.

**7. `metrics.accounting_exclusions` (5 VAs) is a frozen PRESERVATION list, not a live
exclusion set.** The five VAs are `00b28ec0`, `00e7a190`, `00e7e6c0`, `00e7fc00`,
`01073700`, and `reconstruction.accounting_exclusions_all_integrated` is `true`: every
one of them is an integrated function record. Subtracting them would understate
integration from 299 to 294, which is a fabricated number. The list exists to prove those
records were *deliberately retained*, not to be removed from a total.

**8. `body_status` is not the 299/1 field.** That split is `integration_status`. The two
axes are independent:

| axis | source | census |
|---|---|---|
| `integration_status` | `manifest#functions[].integration_status` | `{integrated: 299, blocked: 1}` |
| `body_status` | `manifest#functions[].body_status` | `{integrated: 285, runtime_gated: 3, ABSENT: 12}` |

The 12 `ABSENT` records are exactly the 12 `function_address`-only records of rule 9.

**9. 12 manifest records carry no `va` key and use `function_address` instead.** Reading
only `va` yields 288, not 300. Both keys must be read through `normalize_va`, or the
dedup collapses 12 records and any per-record statistic computed over them (notably
`signature_status`, 288 of 300) is silently wrong.

Two further non-additivity warnings the report carries inline:

* `staged_va` (42) is **never** added into any integrated figure. Staging is a work
  state; a staged VA may be blocked, deferred, or never promoted.
* `dependency_closed` and `dependency_uncertain` are alternative states, not additive
  quantities.

## 7. Runtime: gated is not failed

`coverage.json#runtime`:

| measure | value | reading |
|---|---:|---|
| `validated` | 0 | zero functions have been validated against the original process |
| `gated` | 299 | a capability gate on the original process is still open |
| `unavailable` | `null` | no such field exists; see §11 |
| `negative` | 0 | zero observed negative runtime results |
| `capability_status` | `TECHNICALLY_FEASIBLE_NOT_IMPLEMENTED` | `runtime-oracle.json#current_capability.overall_status` |

The report states the semantics in its own words:
`runtime_gated=299 means a capability gate on the original process is still open.
Nothing was attempted and nothing failed.`

### The "not run" token inventory

Reproduced from `coverage.json#runtime.not_run_values_must_not_be_read_as_failed`:

| token | count | meaning as recorded |
|---|---:|---|
| `not_established` | 58,757 | a disclaimer, not a classification |
| `not_run` | 154 manifest function records / 85 metadata files | the experiment was never attempted |
| `required` | 16 | a promotion prerequisite, not a failure |
| `not run` | 3 | the experiment was never attempted |
| `blocked` | 2 | a static integration or dependency blocker, not a runtime failure |
| `NOT_PRESENT` | 1 | evidence absent, not evidence negative |
| `NOT_AVAILABLE` | 0 | a capability/verdict token, never a runtime failure |
| `not performed` | 0 | the experiment was never attempted |
| `not_promoted` | 0 | the experiment was never attempted |

Every one of these nine tokens means **the observation was never attempted**. The
report's stated principle: *a not-run observation is an ABSENCE of evidence, never
evidence of failure.*

`blocked` is flagged with `misread_risk: HIGH` and appears in
`high_misread_risk_tokens` alongside `UNKNOWN`, `NOT_AVAILABLE`, and `not_established`.
The reason is concrete: the triage queue's own `queue_state` vocabulary contains a
literal state named `blocked`, and the manifest carries a record with
`integration_status: blocked`. Both are static integration states, and both sit one
substring away from a runtime failure.

`OBSERVED_NEGATIVE` and `HISTORICAL_NEGATIVE` are **reachability** negatives, not
correctness negatives. `OBSERVED_NEGATIVE` is recorded as *original Cell stage never
entered* — the process never reached that stage, so nothing about its behaviour was
observed. `HISTORICAL_NEGATIVE` is a prior run record under its recorded environment.

### Why `NOT_AVAILABLE` is not `FAIL`

`tools/reconstruction_tooling/worker_contract.py:48` defines:

```python
VALIDATION_VERDICTS = ("PASS", "WARN", "FAIL", "UNKNOWN", "NOT_AVAILABLE")
```

`UNKNOWN` and `NOT_AVAILABLE` are **siblings of `FAIL` in the same enumeration**, which
is the whole point: they occupy the same verdict axis and are all emitted when the
check could not be completed. `validate.py` uses `NOT_AVAILABLE` with explicit reason
strings such as `"no canonical source artifact"`, `"no named canonical call oracle"`
(`validate.py:295`), `"no virtual dispatch evidence available"` (`validate.py:335`), and
for runtime specifically `"no original-process trace was supplied"`
(`validate.py:388`). The runtime section of the human output says it outright
(`validate.py:410`): *Runtime remains `NOT_AVAILABLE` unless an exact original-process
trace is supplied.* The report records
`not_available_is_a_sibling_of_fail_not_a_failure: true`.

### The negative-observation proof

`runtime_negative` is 0, and the report does not merely assert that nothing failed — it
**computes** the classification. `dimensions[runtime_negative]` carries a
`all_non_zero_failed_counts_are_static_gates_evidence` block:

* it walks every key in the manifest and every handoff that names a failure with a
  non-zero value;
* it found `non_zero_failed_counter_count: 5`;
* it classified all 5 as `static_gate`, with `unclassified_count: 0`.

The five counters, with their source paths:

| check | failed | source | sibling status / reason |
|---|---:|---|---|
| `batch_wave6_integrator_clean_clang_format` | 3 | `manifest#metrics.tests_passing` | — |
| `batch_wave6_integrator_clean_python_unittest` | 3 | `manifest#metrics.tests_passing` | `failed_isolated_machine_lock` |
| `clang_format_dry_run` | 3 | `wave6-integrator-clean/handoff.json#validation_results` | — |
| `python_unittest` | 3 | `wave6-integrator-clean/handoff.json#validation_results` | `failed_isolated_machine_lock` |
| `python` | 3 | `batch-2026-09-25/handoff.json#validation_results` | `transient_blocked`; reason: *Another process held /tmp/openspore-machine.lock; the three failures are test_run lock-precedence assertions, not reconstruction behavior* |

The declared static-gate token vocabulary is 12 tokens (`clang-format`, `clang_format`,
`unittest`, `cmake`, `git diff`, `machine lock`, `machine_lock`, `py_compile`, `pyflakes`,
`json.tool`, `sha256sum`, `lock`) over 5 families (`clang-format --dry-run`,
`python3 -m unittest`, `cmake --build`, `git diff --check`, machine lock). Not one of
the five is an original-process observation. `manifest#audit.unresolved_contradiction`
is `null`, so there is no unresolved static contradiction either.

## 8. Semantics: what the canonical vocabulary actually is

The canonical semantic vocabulary is
`knowledgegraph/research/semantic-decomp.json#records[].classification`, documented in
`docs/analysis/semantic-decomp.md`. It has 5 tiers and covers **32 functions**.

| tier | count |
|---|---:|
| `STRONG_SEMANTIC` | 4 |
| `BOUNDED_SEMANTIC` | 8 |
| `STRUCTURAL_ONLY` | 5 |
| `NEEDS_RUNTIME` | 15 |
| `STILL_UNKNOWN` | 0 |

58,725 of 58,757 functions carry no semantic-strength classification at all
(`semantics.unclassified`; 99.9455% in the matrix). **That is the finding.** It is not a
reporting failure, and it is not the same as "unknown": *unclassified is not the same as
unknown — no one asserted anything about them.*

The 32 classified records are all gameplay rows, and all 32 VAs are distinct.

### The 976 positive union

`semantic_positive_any` is the union of three **differently-defined** positive axes, and
its denominator is the 2,149 gameplay set, not 58,757:

| axis | positive gameplay VAs | source |
|---|---:|---|
| `semantic_decomp_classified` | 32 | `semantic-decomp.json#records[]` |
| `blueprint_claim_kind_not_unknown` | 895 | `semantic-blueprint.json#functions[].evidence.claim_kind` |
| `blueprint_semantic_understanding_not_not_established` | 173 | `semantic-blueprint.json#functions[].contract_status.semantic_understanding` |
| **union, deduplicated over VAs** | **976** | `semantics.positive_any_gameplay` |
| **complement** | **1,173** | `semantics.positive_complement_gameplay` |

**The three axes OVERLAP and must not be summed.** The report publishes the wrong answer
on purpose so a reader can recognise it: `positive_axes_sum_if_you_were_wrong: 1,100`,
with `positive_axes_sum_is_wrong_because: the axes share VAs, so the sum double-counts
them`. The correct union (976) is computed by deduplicating over VAs, not by adding axis
tallies. 976 + 1,173 = 2,149.

### There is no canonical semantic tier named "inferred"

`semantics.canonical_vocabulary.no_inferred_tier` is `true`, and the report's
`honest_note` is explicit: *There is NO canonical semantic tier named 'inferred' or
'hypothesized'. `INFERRED` is an EVIDENCE-ladder rung and a blueprint claim_kind, not a
semantic tier. Mapping it onto the strong/bounded/structural axis would require inventing
a category name that no artifact in this repository uses, so this report does not do it.*

`INFERRED` lives on two other axes, each with its own denominator, and is reported
separately under `semantics.evidence_ladder_axes`:

| axis | `INFERRED` count | denominator |
|---|---:|---|
| `ledger_name_evidence_gameplay` (`INFERRED`) | 1,413 | 2,149 gameplay |
| `blueprint_claim_kind_gameplay` (`INFERRED`) | 484 | 2,149 gameplay |
| `ledger_name_evidence_total` (`INFERRED`) | 12,371 | 58,757 universe |

For completeness, the full evidence-ladder censuses the report publishes:

| axis | census |
|---|---|
| `ledger_name_evidence_total` | `APPROX: 1500`, `CONFIRMED: 1167`, `INFERRED: 12371`, `SUPPORTED: 3836`, `UNKNOWN: 39883` |
| `ledger_name_evidence_gameplay` | `APPROX: 94`, `CONFIRMED: 487`, `INFERRED: 1413`, `SUPPORTED: 155` |
| `blueprint_claim_kind_gameplay` | `INFERRED: 484`, `SEMANTIC: 411`, `UNKNOWN: 1254` |
| `blueprint_contract_state_gameplay` | `body_partial: 171`, `dossier_partial: 2`, `identity_graph_partial: 388`, `unresolved: 1588` |
| `blueprint_semantic_understanding_gameplay` | `not_established: 1976`, `partial: 173` |

`ledger_name_evidence` is the **evidence ladder**, not a semantic tier. `APPROX` and
`INFERRED` are weak rungs and must not be read as identification.

### Two disclaimers that look like data

**`ledger[].semantic_understanding` is the constant `not_established` on all 58,757
rows.** Re-derived directly: the set of distinct values across all ledger rows is
exactly `{'not_established'}`. It is a disclaimer, not a classification, and it carries
zero information. The only gameplay axis with real variance is the *blueprint's*
`contract_status.semantic_understanding` (`partial: 173` / `not_established: 1976`).

**`residual-unknown-priority`'s 1,976 records are a NEGATIVE label.**
`residual-unknown-priority.json#records` has 1,976 entries, and the report sets
`is_a_negative_label: true` and `must_not_be_unioned_into_positive_coverage: true` with
the reason: *it is the exact complement of the 173 'partial' set within gameplay, so
unioning it into a positive-coverage figure trivially reaches 100% and means nothing.*
The artifact's own `quality_status` reinforces this:
`runtime_evidence: NOT_PRESENT`, `semantic_promotion: NOT_PERFORMED`,
`status: COMPLETE_WITH_EVIDENCE_LIMITATIONS`. Unioning 1,976 negatives into the 173
positives yields 2,149 — a meaningless 100%.

## 9. Evidence classes: available is not sufficient

`coverage.json#evidence` reports, per class, both an `available_evidence` and a
`sufficient_evidence` count. The two are different claims, and the report is explicit
about the boundary.

| class | available (universe) | sufficient (universe) | available (gameplay) | sufficient (gameplay) | available |
|---|---:|---:|---:|---:|---|
| `CALLS` | 49,451 | 143 | 2,104 | 83 | yes |
| `GLOBALS` | 20 | 8 | 14 | 4 | yes |
| `FIELDS_OFFSETS` | 51 | 35 | 36 | 26 | yes |
| `CONSTANTS` | 21 | 6 | 17 | 3 | yes |
| `CONTROL_FLOW` | 50 | 24 | 21 | 15 | yes |
| `VIRTUAL_DISPATCH` | 26 | 21 | 14 | 12 | yes |
| `ABI` | 337 | 183 | 171 | 91 | yes |
| `RUNTIME` | — | — | 0 | 0 | **no** |

**Definition of "sufficient".** `coverage.json#evidence.sufficient_definition`, verbatim:
*A class is AVAILABLE when the class's artifact field is present and non-empty. A class
is SUFFICIENT only when the record's evidence level is SUPPORTED, CONFIRMED, or VERIFIED
-- the canonical ladder in manifest.policy.semantic_labels. An existing field is never
called verified merely because it exists.* The ladder is hardcoded as
`SUFFICIENT_LADDER = ("SUPPORTED", "CONFIRMED", "VERIFIED")` at `coverage.py:53`. Note
what the ladder **excludes**: `OBSERVED` is deliberately not in it, and neither is
`INFERRED` or `APPROX`.

The rule, stated in the report's own words: *An existing field is never called verified
merely because it exists.* The report sets the guard as a machine-readable flag,
`evidence.never_called_verified_because_present: true`. The gap between available and
sufficient is the point of the table: `CALLS` has 49,451 available and 143 sufficient; a
static ABI signature says nothing about runtime behaviour.

### The universe-scale limitation

`evidence.universe_scale_limitation`, verbatim: *Every evidence class below is measured
against the 58,757-row universe, but evidence is only ever RECORDED for reconstructed
or triaged functions. The gameplay figures are the meaningful ones; the universe figures
are dominated by rows no human or agent has looked at. Reading a class percentage as
"how much of the game we understand" would invert the meaning.*

Two further limitations a consumer must know:

* Per-class coverage is derived from **reconstruction metadata key presence**, not from
  a universal evidence pack. The keys per class are enumerated in `EVIDENCE_KEYS`
  (`coverage.py:85-94`); `evidence_controls` has no dedicated artifact field
  (`coverage.py:95`).
* VA-level evidence packs live under `reconstruction/evidence/*/`, and
  `reconstruction.evidence_pack_count` is **volatile** (it was 8 when this document was
  first written and grows as agents add packs; read it from the artifact). Of the original
  eight, `00576c50`, `007d9410`, `008db310`, `00980510`, `00b1fbf0`, `00e5b790`,
  `00fc7e10` and `01053790` were present — and `evidence_packs_git_tracked` is 0, so no
  pack survives a fresh clone.
* `evidence_abi` is `mixed`: it combines the manifest's `signature_status` (present
  on 288 of 300 records) with metadata ABI keys, so its covered count moves with the
  metadata tree. The 12-record shortfall on the manifest side is exactly the
  12 `function_address`-only records of §6 rule 9 — that part is stable.

## 10. Dependency and frontier

`coverage.json#dependencies`:

| quantity | value |
|---|---:|
| queue rows | 368 |
| in the 58,757 universe | 365 |
| out of the universe (preserved separately) | 3 |
| actionable frontier | 231 |
| actionable frontier, in-universe | 228 |
| frontier cross-check against `reconstruction/knowledge/index.json` | 231, `agrees_with_derived_actionable_frontier: true` |

The derived frontier is `queue VA set minus manifest VA set`, so it is disjoint from the
manifest by construction and does **not** require the untracked `index.json`. The index is
used only as a cross-check, never as a hard input, precisely because it is
untracked-but-not-ignored.

### `queue_state` and `readiness` censuses

These are two independent partitions of the same 365 in-universe queue rows. They do not
add up to anything together.

`readiness` (6 declared states, sum 365):

| state | count |
|---|---:|
| `LIKELY_INFRASTRUCTURE` | 182 |
| `NEEDS_RE` | 101 |
| `READY_WITH_LOCAL_CONTEXT` | 29 |
| `DEPENDENCY_FIRST` | 24 |
| `ENGINE_BOUNDARY` | 23 |
| `READY` | 6 |

`queue_state` crosstab, on the 365 ledger-side rows (the queue *file* has 368, and the 3
out-of-universe rows are all `candidate` — 177 + 3 = 180):

| queue_state | `DEPENDENCY_FIRST` | `ENGINE_BOUNDARY` | `LIKELY_INFRASTRUCTURE` | `NEEDS_RE` | `READY` | `READY_WITH_LOCAL_CONTEXT` | total |
|---|---:|---:|---:|---:|---:|---:|---:|
| `candidate` | — | — | 76 | 101 | — | — | 177 |
| `implemented` | 14 | 7 | 3 | — | — | 11 | 35 |
| `queued` | 10 | 16 | 103 | — | 6 | 18 | 153 |
| total | 24 | 23 | 182 | 101 | 6 | 29 | 365 |

### Blockers

| quantity | value |
|---|---:|
| ledger rows with a non-null queue | 365 |
| ledger rows with a **non-empty** blocker list | 359 |
| ledger rows with an **empty** blocker list | 6 |
| those 6 are exactly `readiness == READY` | yes |
| distinct blocker tokens | 6 |
| blocker tokens summed with multiplicity | 540 |

The 6 empty-blocker rows are `004ae250`, `005c8bc0`, `00641400`, `00641770`,
`006417c0`, `00c8b6b0` — and their readiness census is `READY: 6` with queue_state
`queued: 6`. The sets coincide exactly, which the test
`blockers_empty_set_is_exactly_the_ready_rows` locks down.

Blocker token census (the ledger row's top-level `blockers` list, which is where the
field lives — not inside `queue`):

| blocker | rows |
|---|---:|
| `outside_reconstruction_scope` | 182 |
| `decompilation_not_persisted` | 181 |
| `needs_reverse_engineering` | 101 |
| `local_type_context_required` | 29 |
| `callee_dependencies_unresolved` | 24 |
| `engine_interface_boundary` | 23 |

### DO NOT SUM the blocked axes

`dependencies.blocked_axes.do_not_sum` is `true`, with the warning: *These axes are
ALTERNATIVE STATES of the same 365 queue rows, not additive quantities. Summing them
would double-count every row that carries more than one signal.*

The arithmetic proof is in the numbers: 359 rows carry 540 blocker tokens, so tokens
overlap rows. Summing the six blocker counts gives 540 "blocked rows" from a universe of
365. The blocked axes enumerated are:

1. **integration blocked** — `manifest#functions[].integration_status == blocked` (1 record);
2. **boundary reconcile** — `engine_interface_boundary` (23) and the manifest audit's
   resolved/unresolved contradiction boundary;
3. **readiness blocker** — the 6 `readiness` states, which are alternatives to
   `queue_state`, not additions;
4. **capture conflict** — `availability_conflicts`, e.g. `0093b630`
   (`multiple_sdk_export_files_for_one_va`) and `00e5b790` (`duplicate_body_capture`);
5. **claim blocked** — SQLite `investigations` claim state, machine-local and not in this
   report;
6. **batch exclusion** — `metrics.tests_passing` and handoff `validation_results` gates;
7. **package dependency-only exclusion** — handoff `excluded_addresses` and
   `deferred_full_package_claims`, which are *exclusions*, not blocks.

The word "blocked" means at least seven different things on seven different axes. The
**only defensible narrow figure** is `ledger_rows_with_non_empty_blockers` = **359**,
because it is a single, explicitly-defined set over one named field. Any other "blocked"
number in this repository is a different measurement.

### Dependency records are coarse

| quantity | value |
|---|---:|
| in-universe VAs whose queue row carries a non-empty `dependencies` list | 204 |
| distinct dependency tokens across the whole queue | 6 |
| gameplay functions with dependencies closed | 500 |
| gameplay functions with dependency evidence explicitly truncated | 0 |

The 6 tokens are `app-lifecycle`, `editor-core`, `graphics-render`, `resource-io`,
`runtime-crt-stl`, `utfwin-framework`. With 6 coarse resource tokens for 204 rows, this
is a **resource classification, not a call-graph dependency record**. The real
call-graph dependency record lives in the blueprint (gameplay only) and in the gitignored
SQLite sidecar.

### There is no "dependencies resolved" field

No record in this repository carries a field meaning *dependencies resolved*. The report
therefore does not compute one. It uses the tooling's own `eligible` disposition
semantics instead: `tools/reconstruction_tooling/frontier.py:339` assigns
`disposition = "eligible"` when a target has no claim conflict, no coordination gap, no
open callees, and no truncation flag; `frontier.py:286` implements
`--dependency ready` as exactly `disposition == "eligible"`. The 500 / 0
`dependency_closed` / `dependency_uncertain` split in this report mirrors the same
predicate at `frontier.py:208-213`. If you need a "resolved" number, use `eligible`
from `openspore frontier` and say so.

## 11. What could NOT be determined

Reproduced from `coverage.json#cannot_determine`. This list is a feature, not a failure:
a coverage tool that silently fills these cells is worse than one that leaves them empty.

| metric | reason |
|---|---|
| `functions_with_caller` | source is the gitignored, stale (triage-v4) SQLite database; a fresh clone has no xref table, so this dimension is not reproducible. Marked machine_local. |
| `functions_with_callee` | source is the gitignored, stale (triage-v4) SQLite database; a fresh clone has no xref table, so this dimension is not reproducible. Marked machine_local. |
| `functions_with_any_call_role` | source is the gitignored, stale (triage-v4) SQLite database; a fresh clone has no xref table, so this dimension is not reproducible. Marked machine_local. |
| `runtime_unavailable` | no record in the repository carries a `runtime_unavailable` field; NOT_AVAILABLE is a capability/verdict token, so a VA count would require inventing the category. Emitted available=false with the capability status instead. |
| `withheld_va` | 'withheld' is not a canonical term in this repository: no field, enum, or status carries that name. The two closest sourced quantities (handoff excluded_addresses, deferred_full_package_claims.withheld_body_count) are reported by name; the latter has no VA list, so no VA count is derivable. |
| `withheld_va_from_deferred_full_package_claims` | `deferred_full_package_claims.withheld_body_count` is a bare integer (10) with no VA list, so it cannot be resolved to addresses. |
| `a single overall completion percentage` | the dimensions are defined over different universes, provenances, and evidence ladders; any weighted composite would be a fabrication. Deliberately absent. |

The first three are the honest cost of reading a gitignored sidecar. The fourth and fifth
are refusals to invent categories. The seventh is this document's thesis.

The two closest sourced quantities to `withheld_va`, as published by the report:

| quantity | value | usable as a VA count? |
|---|---:|---|
| `handoff_excluded_addresses_distinct_vas` | 50 | yes — but it is an **exclusion**, not a withholding decision |
| `handoff_excluded_addresses_handoffs` | 5 | no |
| `deferred_full_package_claims.withheld_body_count` | 10 | **no** — a bare integer with no VA list |

## 12. Biggest blind spots

All 12, from `coverage.json#blind_spots` (item 2 is annotated in prose here; the artifact
carries the same claim without the annotation):

1. call-graph, field, and type knowledge depends solely on a gitignored, stale
   (classifier triage-v4) SQLite database: 0% of the caller/callee, has_type_association
   and evidence_calls dimensions survives a fresh clone.
2. 477 of the 478 persisted decompilation bodies live under gitignored `.spore-analysis/`
   (the 478th, `00e806b0`, is tracked at `tools/re/data/decompiled/`); the tracked
   decompiler `.c` output does not account for the block.
3. a second decompiler cache under `tools/mcp/cache/decompiled/` holds further bodies and
   is gitignored and self-described as disposable; this reporter does not count it,
   because counting it would mean trusting a cache its own author calls throwaway.
4. 0 runtime-validated functions and 0 negative runtime observations exist; the original
   Cell stage was never entered in any Wine run recorded by
   `knowledgegraph/research/runtime-oracle.json`.
5. ledger `semantic_understanding` is the constant `not_established` on all 58,757 rows:
   zero information, a disclaimer rather than a classification.
6. 96.0% of the universe (56,413 functions) has no package or cluster membership claim
   at all.
7. `reconstruction/metadata` is 70.1% untracked; only 101 of 338 metadata files survive a
   fresh clone. (The percentage is computed from those two counts; it used to be a
   hand-typed "roughly 66%" literal that matched nothing derivable. The file count moves
   as agents add metadata, so regenerate rather than trust this line.)
8. 4 reconstructed VAs (00b5b880, 00b5b8a0, 00b5b8c0, 00b5b8e0) lie outside the 58,757-row
   universe and are also absent from `metrics.accounting_exclusions`.
9. 182 of 300 manifest records reference a runtime gate token absent from the canonical
   `runtime_gates[]` list.
10. `packages[].functions` covers only 154 of 300 records; 21 record package ids are
    missing from `packages[]`; `packages_complete` + `packages_in_progress` (65) does not
    equal the 65 declared packages.
11. 3 of the 368 triage-queue rows lie outside the canonical universe and have no
    function or xref data; they are preserved separately rather than forced into the
    ledger.
12. the live-only decompilation dimension is clone-reproducible because it is derived
    from the git-tracked `decomp-gap/*.json` partitions; the 142 MB synthesis output
    `decomp-gap-excavation.json` is gitignored and is neither read nor regenerated
    here.

### The top three, with consequences

**#1 — the entire call-graph layer is one uncloneable file.** Consequences: no
caller/callee dimension, no `has_type_association` from the DB half, and the 49,451-row
`evidence_calls` figure are all local-only. Worse, the DB is classifier **triage-v4**
against a **v6** ledger, so its own category census *disagrees* with the ledger and
undercounts gameplay. Any citation of 57.2579% / 69.8317% / 84.1619% is a claim about
one developer's machine, not about the project. The correct engineering response is to
treat the call graph as unmeasured and rebuild it from the tracked xref export before
quoting anything.

**#4 — zero runtime-validated functions, and zero negatives too.** Consequences: no
semantic claim in this repository can be promoted past static evidence, and no claim can
be *refuted* either. The `NEEDS_RUNTIME` tier (15 functions) and the 299 runtime gates
are all waiting on a capability whose status is
`TECHNICALLY_FEASIBLE_NOT_IMPLEMENTED`. This is the single gap that no amount of static
analysis closes, and it is the one worth funding.

**#6 — 96.0% of the universe (56,413 functions) has no package or cluster membership.**
Consequences: package-based reasoning, cluster-based frontier ranking, and any
"which subsystem is this function in" query silently fall back to *no answer* for the
majority of the binary. The 39,716 ledger rows with an `UNKNOWN` triage category and the
39,883 rows with `UNKNOWN` name evidence — the exact complements of
`has_triage_classification` (19,041) and `has_name_evidence` (18,874) — are the same gap
seen from two angles. Combined
with #5, the honest summary is: outside the gameplay set and the manifest's 300 chosen
targets, the repository has almost no *claims* about the binary — which is not the same
as knowing nothing about it, but is not a claim either.

## 13. Volatility: which numbers are safe to quote

The report does not just stamp determinism on itself; it publishes a per-input
provenance class, and that class is the volatility contract. Split by where the input
comes from.

### STABLE — safe to quote as durable facts

Derived only from git-tracked, non-concurrently-written inputs:

| input | tracked members |
|---|---|
| `knowledgegraph/research/21-decompilation-coverage.json` | — |
| `knowledgegraph/triage/queue-f0e310e0-v6.json` | — |
| `knowledgegraph/research/source-reconstruction-manifest.json` | — |
| `knowledgegraph/research/semantic-decomp.json` | — |
| `knowledgegraph/research/semantic-blueprint.json` | — |
| `knowledgegraph/research/residual-unknown-priority.json` | — |
| `knowledgegraph/research/runtime-oracle.json` | — |
| `knowledgegraph/research/decomp-gap/*.json` | 16 of 16 (all) |

A fresh clone reproduces these exactly, so the dimensions computed purely from them are
durable: `total_internal_functions` 58,757, `gameplay_functions` 2,149,
`non_gameplay_functions` 56,608, `persisted_decompilation` 478,
`no_decompilation_evidence` 58,277, the five semantic tiers (4/8/5/15/0),
`semantic_unclassified` 58,725, `semantic_positive_any` 976, the `readiness` census, the
`blocked_va` 1, the `name_evidence` and `triage_category` censuses, and
`runtime_validated` 0.

These are the only numbers that may go in a commit message, a paper, or a status report
without an expiry date.

**A contradiction found during review, and how it was resolved.** An earlier revision of
the engine emitted a blind spot and a dimension caveat claiming that
`live_only_decomp_observation` (184) was *not* reproducible from a fresh clone "because
the decomp-gap synthesis artifact is gitignored". That was wrong, and the report
contradicted itself: `snapshot.inputs.decomp_gap_parts` reports `member_count: 16` with
`tracked_members: 16` and `tracked_members_is_all: true`, and all 16 partition files are
in the index. The dimension is computed by a verbatim reimplementation of
`synthesize.py`'s `has_live_static_body` applied to those **tracked** partitions, so it
**is** clone-reproducible. What is gitignored is the *synthesized output*,
`knowledgegraph/research/decomp-gap-excavation.json` (`.gitignore:38`), which this
reporter deliberately never reads or regenerates because `synthesize.py`'s `main()`
writes it. The blind spot and the caveat were corrected to say so; the count (184) and
its STABLE classification are unchanged. The episode is recorded here because it is the
failure mode this document exists to prevent: a caveat that is more alarming than the
evidence supports, and worse, contradicted by a field two sections away.

Caveat that survives the STABLE label: a tracked file can still be *edited* by a future
commit. "Stable" means reproducible from a fresh clone of a given commit, not immutable.

### SEMI-STABLE — machine-local, valid only while nothing re-seeds

These read `knowledgegraph/spore.db`, which is gitignored and is a live snapshot:

| dimension | value |
|---|---:|
| `functions_with_caller` | 33,643 |
| `functions_with_callee` | 41,031 |
| `functions_with_any_call_role` | 49,451 |
| `has_type_association` (DB half) | contributes to 6,807 |
| `evidence_calls` (xref half) | contributes to 49,451 |

They are valid only while nobody runs `knowledgegraph/kg.py`, because a re-seed rebuilds
the DB and the xref census changes. The three `functions_with_*` rows are marked
`provenance: machine_local` in the matrix and are listed in `cannot_determine` as not
reproducible; `has_type_association` and `evidence_calls` are `mixed` (each has a
DB-derived half) and appear in **neither** list, so a reader must not generalise the
machine-local verdict to them. Additionally, the DB's
`triage` table is `triage-v4`, so its category census disagrees with the v6 ledger; its
gameplay figures *understate* reality.

### VOLATILE — changes when a concurrent reconstruction wave lands

Anything walking the reconstruction working trees, or reading the git index:

Every row of this table is volatile; the counts are from one run and are listed to show
*which* inputs move, not to be quoted.

| volatile input | member count | tracked members |
|---|---:|---:|
| `reconstruction/metadata/**/*.json` | read from the artifact | read from the artifact |
| `reconstruction/staging/*/` | read from the artifact | read from the artifact |
| `reconstruction/integrated/**/handoff.json` | read from the artifact | read from the artifact |
| `reconstruction/evidence/*/` | read from the artifact | read from the artifact |
| `reconstruction/knowledge/index.json` | — | — |

The volatile dimensions are `staged_va`, `metadata_only_record`,
`reconstruction.metadata_distinct_vas`, `evidence_packs_git_tracked`,
`reconstruction.staging_*`, all five `evidence_*` class dimensions, and — because they
read the git index — `in_actionable_frontier`'s cross-check and every `git_tracked` /
`tracked_members` field. The *ledger-derived* dimensions (universe, gameplay, and all six
decompilation rows) read git-tracked inputs and do **not** drift.

For volatile quantities, quote **structural invariants**, not literals:

* `distinct_VA(metadata files) <= file_count(metadata)`, and the strict inequality is
  asserted (2 VAs carry two metadata files each: `005bf9d0`, `008db310`);
* `records(integrated) + records(blocked) == records(total)` — 299 + 1 = 300;
* `records(carrying a gate token) <= metrics.runtime_gated` — 288 ≤ 299;
* `sum(readiness counts) == in_universe queue rows` — 365;
* `queue file rows == in_universe + out_of_universe` — 368 = 365 + 3;
* `manifest change_log entry count >= number of entries carrying added_function_records`
  — 26 ≥ 3;
* `positive union <= sum(positive axes)` and `union + complement == gameplay universe` —
  976 + 1,173 = 2,149;
* `actions landing on a VA already in the corpus` must be reported as a conflict, never
  merged.

This is exactly the discipline `tests/test_coverage.py` uses, and it is why that suite
does not false-fail when a wave lands mid-run.

### Where the core metrics land

| core metric | bucket | may be cited durably? |
|---|---|---|
| 58,757 internal functions | STABLE | yes |
| 2,149 gameplay functions | STABLE | yes |
| 478 persisted decompilation bodies | STABLE (count) | yes; the *bodies themselves* are gitignored |
| 58,277 with no decompilation evidence | STABLE | yes |
| 32 semantically classified / 58,725 unclassified | STABLE | yes |
| 976 positive gameplay VAs | STABLE | yes |
| 0 runtime-validated | STABLE | yes |
| 300 manifest records / 299 integrated / 1 blocked | STABLE | yes |
| 368 queue rows / 365 in-universe / 3 preserved | STABLE | yes |
| 231 actionable frontier | derived from STABLE inputs | yes, with the in-universe split (228) alongside |
| 42 staged VAs | VOLATILE | no — quote the invariant only |
| 27 metadata-only VAs | VOLATILE | no — quote the invariant only |
| 8 evidence packs | VOLATILE | no |
| 184 live-only observations | STABLE | safe to quote; always state that they are a dimension union, never persisted decompilation |
| 33,643 / 41,031 / 49,451 call-graph counts | SEMI-STABLE | no |

One live observation made while writing this document, which is itself the volatility
claim: `snapshot.inputs.metadata_dir.tracked_members` is **101** in the committed
`coverage.json`, and a live `git ls-files reconstruction/metadata` at the time of writing
returned **102** entries. The extra index entry is for a path whose worktree file is
absent, so the reporter's count of *files it actually read* is the correct 101. The
field moved because the git index moved, with no artifact byte changing — precisely the
`host_probes` disclosure in §3.

## 14. History

Only what is explicitly recoverable from the manifest. The report's own
`history.limitation` is the governing rule: *ONLY what the artifacts explicitly record is
reported here. 26 change_log entries with their own date and change fields, plus
`metrics.delta_since_previous`. Wave-by-wave history is NOT reconstructed: no artifact
records it, and inventing a timeline would manufacture history the repository does not
contain. Entries whose artifact records no date carry date=null and say so.*

`coverage.json#history` is emitted with `checkpoints: []` unless `--history` is passed;
the data is always recoverable from the manifest, the flag only controls whether it is
included in the output.

### What `change_log` actually records

| property | value |
|---|---:|
| `change_log` entries | 26 |
| entries carrying a `date` | 26 (all of them) |
| distinct dates present | 2 (`2026-09-24`, `2026-09-25`) |
| entries carrying a `batch` id | 3 |
| entries carrying `added_function_records` | 3 (values 12, 12, 30; sum 54) |
| entries carrying `runtime_validated` | 3 (all 0) |
| entries with a null `change` text | 0 |

So: **no checkpoint lacks a date** in this snapshot. Were one to, the report would emit
`date: null` with `date_is_recorded_by_the_artifact: false`, and the artifact records no
date to fall back on.

The 3 named batches are `batch-2026-09-25-wave9-safe-core` (12 records),
`batch-2026-09-25-wave10-safe-core` (12), and `batch-2026-09-25-wave11-clean` (30). The
other 23 entries carry a `change` narrative but no `batch` id and no
`added_function_records` field, so their size is not recoverable.

### `metrics.delta_since_previous`

| field | value |
|---|---:|
| `function_records` | 300 |
| `previous_function_records` | 270 |
| `added_function_records` | 30 |
| `packages` | 65 |
| `previous_packages` | 58 |
| `types` | 137 |
| `previous_types` | 137 |
| `runtime_gates` | 262 |
| `previous_runtime_gates` | 119 |
| `runtime_validated_delta` | 0 |

Read this as a single-step delta, not a series. Note one internal inconsistency a
consumer should know about: `metrics.runtime_gated` is **299** while the
`runtime_gates[]` array has **262** entries. The report surfaces the metric (299) as
canonical and the 288-record gate-token count as a separate figure (§6), but the 262 vs
299 gap is in the manifest and is not reconciled by any artifact. Treat 299 as the
record-level gate metric and 262 as the size of the gate-token vocabulary.

### What is NOT recoverable

Wave history was **not** reconstructed from memory and is not in the repository. The
repository has 26 change-log entries spanning 2 calendar days; the report refuses to
extrapolate a timeline from them. In particular there is no artifact that records, for
any wave, the number of functions attempted, rejected, or abandoned. Do not present a
per-wave success rate.

## 15. Tests

`tests/test_coverage.py` — 43 tests, in three classes. All pass; `python3 -m unittest
tests.test_coverage` reports `OK`.

`test_cli_is_read_only` is the one machine-state-sensitive test in the suite: it compares
`reconstruction/knowledge`, `knowledgegraph/triage` and `reconstruction/metadata` before
and after a CLI run, so it fails if a *concurrent agent* writes to those untracked trees
during the ~8 s window. That failure is environmental — the test's own control phase
reports it as such — and is not a read-only violation by the reporter.

### `CoverageTest` (19 tests) — the core contract

| test | guarantees |
|---|---|
| `test_universe_is_exact` | the 58,757-row universe is the ledger, exactly |
| `test_unique_va_dedup` | VA dedup is by `normalize_va`, across both `va` and `function_address` |
| `test_persisted_versus_live_only` | a live observation is not a persisted body, and the two sets are disjoint |
| `test_any_versus_no_decomp_evidence_is_a_true_partition` | `any + no == 58,757` over one universe, and `any − persisted` is exactly 2 `snapshot_only` rows |
| `test_live_only_is_disjoint_from_the_ledger_decomp_partition` | the 184 live-only VAs are inside `no`, never inside `any`; `any ∪ live` = 664 and `persisted ∪ live` = 662 are not interchangeable |
| `test_no_decomp_evidence_is_a_persistence_census_not_a_never_decompiled_census` | `no` is labelled and scoped as a persistence census, so it cannot be read as "never decompiled" |
| `test_gap_va_extraction_reaches_every_record` | all 1,977 decomp-gap records yield a VA, including the 793 nested under `identity.va` |
| `test_reconstructed_with_persisted_body_id_is_not_contradictory` | the historical `..._without_...` id and its `covered` value cannot silently disagree |
| `test_untracked_percentage_is_computed_not_asserted` | no percentage is a hand-typed literal; the untracked fraction is recomputed from its own denominator |
| `test_staged_versus_integrated` | staged is never folded into integrated |
| `test_stale_metadata_safety` | metadata-only records do not inflate function coverage |
| `test_semantic_classification` | the canonical tier vocabulary and its counts |
| `test_gameplay_subset_accounting` | the gameplay denominator is applied to the gameplay columns only |
| `test_runtime_gated_is_not_runtime_failed` | gated is never reported as failed |
| `test_percentages_are_not_a_composite` | no composite score is emitted |
| `test_cannot_determine_is_explicit` | the seven undeterminable metrics are listed, not filled |
| `test_deterministic_output` | two runs are byte-identical |
| `test_cli_is_read_only` | the CLI writes nothing without `--out` |
| `test_no_queue_or_claim_mutation` | queue rows, claims, and the SQLite DB are untouched |

### `CoverageSemanticsTest` (22 tests) — the counting rules

| test | guarantees |
|---|---|
| `test_caller_callee_absolute_counts` | the two absolute xref counts |
| `test_caller_callee_direction_is_not_swapped` | caller/callee are not transposed |
| `test_call_reference_type_filter_is_exact` | only the 4 declared call reference types are counted |
| `test_ext_and_vt_pseudo_targets_are_excluded` | `EXT:` / `VT:` pseudo-targets are dropped from both columns |
| `test_summary_matches_dimensions_and_exclusions_are_computed` | the summary is derived from the dimensions, and `accounting_exclusions` is computed rather than assumed |
| `test_tautological_percentages_are_null_and_flagged` | saturated dimensions get `pct: null` + `pct_is_tautological: true` |
| `test_available_and_sufficient_are_different_claims` | the available/sufficient split is preserved |
| `test_sufficient_evidence_ladder_is_exact` | the ladder is exactly `SUPPORTED`/`CONFIRMED`/`VERIFIED` |
| `test_blockers_empty_set_is_exactly_the_ready_rows` | the 6 empty-blocker rows are exactly the `READY` rows |
| `test_positive_axes_count_records_not_categories` | the positive axes are counted over records, and not summed |
| `test_queue_census` | the queue row census |
| `test_readiness_census` | the readiness state census |
| `test_runtime_gate_census` | the runtime-gate census |
| `test_static_gate_claim_is_computed_with_evidence` | the "all failures are static gates" claim is *computed*, with the evidence attached |
| `test_actionable_frontier_agrees_with_the_knowledge_index` | the derived frontier cross-checks against the index |
| `test_git_index_probe_is_disclosed_not_hidden` | the single host probe is declared in the artifact |
| `test_manifest_types_census` | the type-record census |
| `test_package_membership_count` | the package-membership union |
| `test_type_association_count` | the type-association union |
| `test_torn_member_raises_and_vanished_member_is_tolerated` | a changed fingerprint aborts the report; a deleted member is benign |
| `test_torn_member_aborts_the_whole_report` | a torn read fails the whole report rather than publishing partial numbers |
| `test_volatile_counts_hold_structural_invariants` | volatile dimensions satisfy invariants, not literals |

### `TestDisciplineTest` (2 tests)

| test | guarantees |
|---|---|
| `test_determinism_test_can_never_skip` | the determinism test cannot be silently skipped |
| `test_input_aggregate_sees_a_directory_only_change` | a directory-input content change (a C++ edit) is detected via the member aggregate |

### Volatility discipline in the suite

The suite splits its assertions deliberately:

* **exact literals** for stable counts — 58,757, 2,149, 478, the tier census 4/8/5/15/0,
  32, 299/1, 368/365/3;
* **structural invariants** for volatile counts — e.g. `integrated + blocked == total`,
  `sum(readiness) == in_universe`, `distinct metadata VAs <= metadata files`,
  `positive union + complement == gameplay universe`.

That is why the suite does not false-fail when a concurrent reconstruction wave lands
mid-run. The read-only assertions are the strictest part: `MUTATION_SENSITIVE` files must
be unchanged in **both content and mtime**, while the SQLite WAL/SHM sidecars are
`CONTENT_SENSITIVE` only, because opening a WAL database read-only re-stamps their mtime
and can trigger SQLite's one-time stale-WAL recovery — a SQLite artefact, not a mutation
by this reporter. Watched trees are `reconstruction/knowledge`,
`knowledgegraph/triage`, and `reconstruction/metadata`.

### One claim this document does not make

The suite is structured for adversarial review and it encodes the discipline described
above, but **this repository contains no record of a mutation-testing campaign on it.**
No artifact, docstring, commit message, or test names an injected-mutant count or a
count of tests added in response to one. Those figures are therefore not stated here.
If you need them, they must be produced by actually running the campaign and recording
the result in an artifact; they cannot be cited from the current tree.

## 16. Integration with the Graph Observatory

`docs/analysis/graph-observatory.md` describes the Reverse-Engineering Graph
Observatory: the five-view, read-only, loopback-only application in `tools/viewer/`
served by `tools/viewer/server.py` over `tools/viewer/query.py`, defaulting to
`http://127.0.0.1:8787/`. What I found while reading it, and what follows for this report:

**No viewer endpoint was added, and none is needed.** The Observatory's route map
(`docs/analysis/graph-observatory.md`, the "exact HTTP route map" table) has no coverage
route, and a search of `tools/viewer/{server,query}.py` and
`tools/viewer/static/{index.html,viewer.js}` for `coverage` returns exactly one hit —
`query.py:368` reading a `cluster_coverage` field from a *package* artifact, which is
unrelated to this report. There is no existing surface through which
`reconstruction/knowledge/coverage.json` is served, and the Observatory's own contract
forbids inventing one casually: it routes `GET` only, has no write handlers (`POST`,
`PUT`, `DELETE` return `405`), binds only `127.0.0.1`/`::1`, serves a fixed asset map
with a realpath containment check, and every artifact-derived value must declare its
`source`, `source_refs`, `origin`, `available`, and `truncated` fields so a derived
number cannot look like a direct count.

**The two tools are complementary, not competing.** The Observatory answers *what does
the corpus contain, what evidence supports a node, what is missing, what should I look at
next* — per node, per bounded neighborhood. This report answers *how much of the whole
binary is reconstructed / decompiled / classified / evidenced / queued / runtime-validated*
— per dimension, over the whole binary. The Observatory explicitly states it is *not a
semantic completion signal*; this report explicitly states it is *not a per-node evidence
browser*. Neither can substitute for the other.

**How to consume the report through the Observatory today — the manual path.** No
integration is required; the artifacts are already readable side by side:

```bash
# the report, as JSON or as markdown, without writing anything
python3 tools/openspore.py coverage --json
python3 tools/openspore.py coverage --markdown

# the Observatory, on loopback only
python3 tools/viewer/server.py     # http://127.0.0.1:8787/
```

Correlate the two by VA. The report's `universes`, `snapshot`, and `dimensions` give the
per-VA denominators and the counted sets; the Observatory's Functions view gives the
per-VA dossier. Because `in_actionable_frontier` is derived as *queue VAs minus manifest
VAs* without touching the untracked `reconstruction/knowledge/index.json`, the two views
agree on frontier membership by construction, and the report publishes the index
cross-check (231 = 231) so a divergence is detectable rather than silent.

**If someone later wants a viewer route,** the Observatory's own extension rules
(`docs/analysis/graph-observatory.md`, "How to extend safely") already prescribe the
shape: a bounded query function in `tools/viewer/query.py` with all SQL in that module,
a read-only route in `server.py`, declared source authority, server and browser caps
with explicit `truncated`, lazy expansion rather than corpus preload, and a route-crawl
test. A coverage route would be a *summary* route, not a graph view, and would need the
`source` / `available` / `truncated` fields so a `-` in a `pct` column is never
rendered as `0%`. That work is deliberately not done here.

**Two provenance hazards the Observatory itself flags**, both of which this report
corrects for: the DB-derived counts in the Observatory are a local snapshot, not
committed research conclusions; and the Observatory's canonical function path prefers
`knowledgegraph/research/track-b-function-accounting.jsonl`, which is gitignored
(`.gitignore:37`) — see §17.

## 17. Stale-artifact deny-list

A coverage consumer must **not** read these. Each is stale in a specific, nameable way,
and in each case the current number is the one in
`reconstruction/knowledge/coverage.json`.

| artifact | why it is on the list | stale number | current number |
|---|---|---|---|
| `knowledgegraph/spore.db` | gitignored (`.gitignore:29`, `*.db`) **and** its `triage` table is classifier `triage-v4`, not the v6 the ledger was built from | gameplay count from `triage` where `triage_category ∈ {GAMEPLAY_LOGIC, GAMEPLAY_SUPPORT}`: **192** (117 `GAMEPLAY_LOGIC` + 75 `GAMEPLAY_SUPPORT`) | **2,149** — wrong by a factor of roughly 11 |
| `docs/analysis/function-triage.md` | prose document for triage-**v4**; the title line reads `Full-Function Triage — triage-v4 (snapshot 2540f2ca)` and it mentions `triage-v4` twice and `triage-v6` zero times | GAMEPLAY_LOGIC 117, GAMEPLAY_SUPPORT 75 (P1 5,759; CONFIRMED 474; SUPPORTED 3,440) | GAMEPLAY_LOGIC 1,656, GAMEPLAY_SUPPORT 493 (P1 6,261; CONFIRMED 1,167; SUPPORTED 3,836) |
| `docs/analysis/source-reconstruction.md` | campaign prose from an earlier wave | "Function records: 65, including 60 reviewed/integrated bodies and 5 blocked seeded records" | **300** function records, **299** integrated, **1** blocked; 65 is the *package* count |
| `knowledgegraph/research/track-b-function-accounting.jsonl` | gitignored (`.gitignore:37`) — the Observatory's preferred canonical function path | 58,757 rows, byte-current on this machine but **redundant** with the tracked `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl` | use the tracked triage jsonl (also 58,757 rows) |

A fifth entry, for completeness rather than because it is on the mission list:

| artifact | why | stale number | current number |
|---|---|---|---|
| `tools/mcp/cache/decompiled/` | a decompiler cache that is gitignored and self-described by its own author as disposable | bodies not counted by this report | `persisted_decompilation` = **478**; the cache is deliberately excluded because counting it would mean trusting a cache its author calls throwaway |

The `spore.db` gameplay count of 192 is the worst of these, because it is a *plausible*
number: it is 192 real functions, correctly categorised by a v4 classifier, applied to a
58,757-row universe that is identical. Only the classifier version differs. A reader
with no version check would take it as current.

## Appendix: consuming the artifact directly

```python
import json
r = json.load(open("reconstruction/knowledge/coverage.json"))

assert r["$schema"] == "openspore-reconstruction-coverage-1"

dims = {d["id"]: d for d in r["dimensions"]}
# a dimension is only usable if it is available AND you accept its denominator
for did, d in dims.items():
    if not d["available"]:
        continue
    if d["pct_is_tautological"]:
        print(did, d["covered"], d["universe"], "(saturated: no pct)")
    else:
        print(did, d["covered"], d["universe"], d["pct"], d["provenance"])

# provenance class is part of the number
assert {d["provenance"] for d in r["dimensions"]} <= {
    "tracked", "derived", "untracked", "machine_local", "mixed"}
```

Three checks a consumer should always make before quoting a figure:

1. `available` is `true` — otherwise the category does not exist and the `null` is the
   answer;
2. `pct_is_tautological` is falsy — otherwise the percentage is the identity, not a
   measurement;
3. `provenance` is `tracked` (or the figure is documented as machine-local) — otherwise
   the number does not survive a fresh clone.
