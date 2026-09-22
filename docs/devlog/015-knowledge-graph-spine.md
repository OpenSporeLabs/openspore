# 015 — S1: the KG spine (2026-09-22)

The knowledge graph stopped being hand-maintained state. Everything below landed in
three commits (`6fc46ee` architecture baseline, `9e72a57` schema + scale,
`d304c70` seed generator) and was verified by an independent review pass against the
resulting tree, not against implementer claims.

## What changed

**Schema** (`knowledgegraph/schema.sql`, `kg.py:_migrate`). `node` gains
`evidence_level` (CHECK against the 7-level enum), `updated_at`, and `binary_sha256`
(NULL = build-agnostic). Three new tables: `field` (structure fields with
per-attribute evidence), `trace_run` (provenance of every runtime capture), and
`investigations` (the orchestrator queue: per-stage counters, checkpoint blob,
`UNIQUE(kind, va, binary_sha256)` dedup). Six new indexes. Migration is additive-only
and idempotent — the `node` table is rebuilt copy-then-rename so fresh and migrated
DBs are schema-identical; `PRAGMA user_version` goes 0→1 once, never downgraded. The
pre-patch schema with legacy rows migrates byte-for-byte.

**One scale** (`knowledgegraph/scale.py`). The canonical 7-level evidence scale
`UNKNOWN 0.0 < APPROXIMATION 0.3 < INFERRED 0.5 < SUPPORTED 0.75 < OBSERVED 0.85 <
CONFIRMED 0.9 < VERIFIED 1.0`, the 9-status `STATUS2EV` map, and the read-only
5-level legacy compat map. Every code path now derives evidence from this module
(`dossier.py`'s vocab is filtered from it, not redefined). The stale 7-key
`STATUS2EV` in `seed_sprint.py` — which `KeyError`d on `approximated` /
`replaced-approx` — is gone, with a regression test that fails if the old dict
returns.

**Canonical seed** (`knowledgegraph/seed.py` + `seed-literals.json`). The generator
is deterministic (sorted emit), idempotent, and bare-clone-safe: it reads committed
inputs only (literals, `replacement-status.json`, dossiers, vtables, ABI fields,
trace manifests); machine-local inputs (SDK XML, binaries) are optional flags,
gracefully skipped. The 96-node / 115-edge / 14-test-row baseline is committed
verbatim; `seed_sprint.py` is now a deprecation shim that forwards to `seed.py`
(its hand-written data is deleted, not duplicated).

**Provenance + staleness.** Every seeded record carries `binary_sha256`. Re-seeding
under a new build identity preserves the old rows (parked, queryable as
`binary_sha256 != current`, never dropped) while rebuilding build-bound nodes under
the new identity.

## Verification (measured, from the committed tree)

- Fresh worktree of HEAD: `python3 -m unittest discover -s tests -t .` → 77/77 OK
  (run three times, stable); seed → 96/115/14, 18 `Subsystem` nodes, 19
  investigations (18 subsystems + the one done/RECORDED cell row), 15 `field` rows.
- Two independent worktrees of HEAD seed byte-identical logical dumps; re-seed is a
  logical no-op.
- Identity A→B re-seed: 1,681 A-rows preserved and detectably stale; matches the
  architecture doc §3/§5/§6 wording exactly.
- C++ from scratch: `cmake -S . -B …` (Vulkan 1.4.357 present), build with
  `-Wall -Wextra -Werror` → zero warnings; `ctest` 10/10 passed.
- Clean-room audit of all three commits: text files only, no binary blobs, `SPORE/`
  stays git-ignored.

One process note: a test (`test_dossier.py`) regenerates
`docs/analysis/dossiers/cell-movement.json` in place; the committed copy is the
generator's fixed point, so suite runs no longer dirty the tree.

## Where this leaves us

The KG is now canonical, reproducible shared memory: fresh clone → `kg.py init` →
`seed.py` → the same 96/115/14 graph, with provenance columns and a queue table the
orchestrator (S2+) can own. Next: S2 (MCP stdlib surface over this spine).
