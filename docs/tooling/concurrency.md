# Concurrency

The tooling is conservative around the existing dirty and concurrently modified worktree.

## Read paths

Before planning, the frontier reads:

- `knowledgegraph/research/source-reconstruction-manifest.json` through the existing index;
- `knowledgegraph/triage/queue-f0e310e0-v6.json`;
- canonical manifest/triage/xref/semantic/metadata/handoff inputs through an ephemeral `reconstruction_knowledge.build_index` projection; the checked-in/generated index is never treated as an authority;
- SQLite `investigations` using a read-only URI;
- metadata, handoff, source, and committed Ghidra snapshot paths.

## Write paths

The default `frontier`, `swarm` and `orchestrate plan` paths are non-mutating. `evidence`, `context`, `recover`, and `validate` write deterministic target-local artifacts unless `--no-write` is supplied; each file write is atomic, but a multi-file recover is not presented as a transactional generation. `integrate status` and `integrate check` are non-writing; `integrate apply` uses the existing generated-index atomic writer.

The orchestrator is the only command family in this layer that writes SQLite `investigations`, and it writes nothing directly: every insert, claim, checkpoint, release and close is issued through the existing canonical `queue_op`, so the same owner, terminal-row and stale-lease rules apply. `queue_op update` and `queue_op claim` both compare-and-set on `(status, implementer_id)` inside `BEGIN IMMEDIATE` and require `rowcount == 1`, so two writers produce exactly one winner and never a silent last-write-wins. A displaced worker's writes are refused with `not_owner`. See `orchestration.md`.

No command overwrites `src/reconstruction`, staging, metadata, handoffs, or the manifest.

## Live and runtime boundaries

`--live` is explicit and read-only with respect to Ghidra. It does not imply original-process runtime evidence. A missing or failed live query is reported as unavailable and may use a persisted snapshot without changing its evidence class.

## Concurrent changes

The generated evidence directory is additive. Existing target artifacts are replaced only by an explicit rerun of the same command; no unrelated target is touched. The CLI does not run a broad formatter, generator, or database migration as a side effect.
