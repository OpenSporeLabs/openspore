# OpenSpore reconstruction tooling

The repository-local tooling facade is `tools/openspore.py`. It composes the existing reconstruction index, canonical triage queue, SQLite coordination table, and Ghidra adapters without changing the MCP server or creating a second source of truth.

## Commands

```text
openspore frontier [filters]
openspore evidence VA [--live]
openspore context VA [--live]
openspore recover VA [--live]
openspore validate VA
openspore integrate status|check|apply
openspore swarm [--limit N] [--out PATH]
openspore orchestrate plan|brief|run|reap|reclaim [VA] [--worker CMD] [--worker-id ID]
openspore claim VA --worker-id ID
openspore release VA --worker-id ID [--to queued|blocked]
openspore worker-template VA
```

Use `python3 tools/openspore.py ...` or `python3 -m tools.openspore ...`. Add `--json` for one machine-readable result document.

Default source selection is persisted. `frontier` and `swarm` are read-only; `evidence`, `context`, `recover`, and `validate` write target-local generated artifacts unless `--no-write` is supplied. `--live` adds a Ghidra query; fallback data remains labelled `snapshot` or `persisted`, never `live`.

## Implemented behavior

- Frontier draws from the canonical triage queue and generated index, not arbitrary `UNKNOWN` functions.
- Frontier reasons include priority, evidence, fan-in/fan-out, inspectability, dependencies, cluster, runtime gates, and claim state.
- SQLite `investigations` is read-only during planning. Active owners, blocked rows, terminal rows, and stale binary identities are surfaced.
- Evidence packs are deterministic JSON plus Markdown under `reconstruction/evidence/<va8>/`.
- Context briefs contain 15 fixed sections and preserve provenance.
- Recover safely composes evidence, context, and validation and is rerunnable.
- Validation reports all requested structural categories and keeps runtime status `NOT_AVAILABLE` without an exact oracle.
- Integrate check is non-writing; apply uses the existing atomic generated-index writer.
- Swarm emits a dependency-aware queue and does not launch workers.
- Orchestration groups the plan into dependency waves, claims each target atomically through the canonical queue, and dispatches a worker per dispatchable unit. Only a validator `PASS` on a candidate the worker produced may close a target.
- The orchestrator is the single writer of claims. `frontier`, `swarm` and `orchestrate plan` stay read-only, and there is no second claim store.

## Orchestration

`orchestrate` is the claim-aware half of the layer: `plan`, `brief`, `run`, `reap` and `reclaim`, plus the standalone `claim`, `release` and `worker-template` verbs. It owns worker lifecycle, not analysis. Every target transition goes through the existing canonical `queue_op` on the `investigations` table, and there is no second scheduler database, no second claim system and no second manifest.

See `orchestration.md` for the runbook: the pipeline, the dependency scheduler, the lease and claim rules, the worker result contract, the retry bounds, failure recovery, CLI recipes, and how to wire an external worker.

See `architecture.md`, `commands.md`, `evidence-model.md`, `frontier-scoring.md`, and `concurrency.md` for contracts.

## Verification

```bash
python3 -m unittest tests.test_openspore_tooling -v
python3 -m unittest discover -s tests -t . -v
python3 tools/openspore.py frontier --json --limit 10
```

The live Ghidra path is explicit. A live integration check should be run only when the documented Ghidra bridge is available; persisted tests do not pretend to be live.
