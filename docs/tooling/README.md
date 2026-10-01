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
openspore promote plan|apply PACKAGE [--va VA] [--overwrite] [--no-build] [--no-ctest] [--rebuild]
openspore satisfy plan|apply [VA ...] [--reason TEXT] [--verify-build] [--dry-run]
openspore swarm [--limit N] [--out PATH]
openspore orchestrate plan|brief|run|reap|reclaim [VA] [--worker CMD] [--worker-channel auto|jsonl|argv] [--worker-id ID]
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
- Validation reports all requested structural categories over the static dimension, and the runtime dimension separately. A static verdict is never a runtime claim, and a gated runtime is an open gate rather than a failure. See `validation-dimensions.md`.
- Integrate check is non-writing; apply uses the existing atomic generated-index writer.
- Promote installs a staged package into `src/reconstruction/` only when its static `PASS` and runtime `GATED` compose and a scratch build-and-test gate is green; the gate verdict is recorded in the per-VA provenance record.
- Satisfy is the only writer of the manifest transition that ends a dependency. It refuses unless the promotion is static-validated, carries a test, has a provenance record, and has a green recorded build verdict, and it writes no runtime field.
- Swarm emits a dependency-aware queue and does not launch workers.
- Orchestration groups the plan into dependency waves, claims each target atomically through the canonical queue, and dispatches a worker per dispatchable unit. Only a validator `PASS` on a candidate the worker produced may close a target.
- The orchestrator is the single writer of claims. `frontier`, `swarm` and `orchestrate plan` stay read-only, and there is no second claim store.

## Orchestration

`orchestrate` is the claim-aware half of the layer: `plan`, `brief`, `run`, `reap` and `reclaim`, plus the standalone `claim`, `release` and `worker-template` verbs. It owns worker lifecycle, not analysis. Every target transition goes through the existing canonical `queue_op` on the `investigations` table, and there is no second scheduler database, no second claim system and no second manifest.

See `orchestration.md` for the runbook: the pipeline, the dependency scheduler, the lease and claim rules, the worker result contract, the retry bounds, failure recovery, CLI recipes, and how to wire an external worker.

See `reconstruction-failure-modes.md` for the worker's side: the recurring ways a
correct reconstruction still fails a dimension, the check each one fires, and the
source shape that satisfies it without falsifying anything. Read it before
writing a candidate — a green `g++` build is not the gate, and several of these
only appear under `clang++ -Werror -m32` with the package linked as a static
library.

See `architecture.md`, `commands.md`, `evidence-model.md`, `frontier-scoring.md`, `concurrency.md`, and `validation-dimensions.md` for contracts.

## Read-only exchange: `spore-semantic`

`tools/spore-semantic/` is a standalone Go CLI (stdlib only, no Python and no
Ghidra at runtime) that exports everything above into ONE deterministic
snapshot and answers `binary_sha256 + VA` lookups against it. It is a
*read-only projection*, not a second source of truth: it copies facts from the
artifacts listed in `semantic-exchange.md` with their provenance intact and
derives none of them.

```text
spore-semantic export        [--out PATH] [--root DIR]
spore-semantic lookup        <VA>      [--snapshot PATH] [--json]
spore-semantic lookup-symbol <NAME>    [--snapshot PATH] [--json]
spore-semantic explain       <VA>      [--snapshot PATH]
spore-semantic stats                   [--snapshot PATH] [--json]
spore-semantic validate                [--snapshot PATH] [--json]
```

Snapshot: `knowledge/semantic/function-passport-v1.jsonl` (JSON Lines, metadata
first, then one passport per canonical VA ascending). Regenerating from the
same repository state is byte-for-byte identical. `OPENSPORE_REQUIRE_SHA`
makes every command refuse a snapshot describing a different binary.

See `semantic-exchange.md` for the field-to-authoritative-source mapping, the
snapshot schema, and what `UNKNOWN` means; and `semantic-exchange-consumer.md`
for how a sibling project (`spore-recomp`) consumes it without depending on
OpenSpore.

Installed on this machine at `~/.local/bin/spore-semantic`:

```bash
cd tools/spore-semantic
CGO_ENABLED=0 go build -trimpath -ldflags '-s -w' -o ~/.local/bin/spore-semantic ./cmd/spore-semantic
gofmt -l . && go vet ./... && go test ./...
```

Run it from anywhere: the checkout is found by walking up from the working
directory, or via `--root`, or `$OPENSPORE_ROOT`.

## Verification

```bash
python3 -m unittest tests.test_openspore_tooling -v
python3 -m unittest discover -s tests -t . -v
python3 tools/openspore.py frontier --json --limit 10
```

The live Ghidra path is explicit. A live integration check should be run only when the documented Ghidra bridge is available; persisted tests do not pretend to be live.
