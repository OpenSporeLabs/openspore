# Architecture

The tooling is an adapter layer around the existing control plane:

```text
canonical manifest + triage queue + metadata/handoffs
                    ↓
       reconstruction_knowledge index
          ↙                    ↘
     frontier/swarm       evidence/context
                               ↓
                         validation report
                               ↓
                 existing integration projection
```

SQLite `knowledgegraph/spore.db` remains the coordination and cross-tool evidence store. Ghidra remains the binary-analysis source. `reconstruction/knowledge/index.json` and `bootstrap.json` remain generated projections. `tools/reconstruction_tooling/` does not migrate the KG, and it does not own claim logic: the orchestrator is the single writer of claims, and it writes them exclusively through the existing canonical `queue_op`. `frontier`, `swarm` and `orchestrate plan` remain read-only.

## Modules

- `models.py`: address normalization, deterministic serialization, hashes, atomic writes.
- `frontier.py`: persisted target pool, score components, reasons, claim overlays, filters.
- `evidence.py`: persisted snapshot fallback and explicit live Ghidra queries.
- `context.py`: fixed 15-section agent brief.
- `validate.py`: bounded structural comparison and status aggregation.
- `recover.py`: safe composition of the three read/validation phases.
- `integrate.py`: check/apply wrapper around the existing generated-index builder.
- `swarm.py`: machine-readable dependency-aware work plan, and the queue-addressable projection of a frontier target.
- `schedule.py`: dependency-aware grouping of targets into maximally parallel dispatch waves.
- `queue.py`: claim, checkpoint, release and close adapter over `queue_op`; owns no claim logic.
- `worker_contract.py`: the worker briefing and the strict result parser.
- `orchestrate.py`: the claim-aware worker lifecycle. See `orchestration.md`.
- `cli.py`: one coherent command family and JSON envelope.

## Authority boundaries

- Manifest controls reconstruction status and ownership.
- Metadata and handoffs are evidence/review records, not replacement authority.
- The generated index is derived and may be stale.
- The triage queue controls candidate membership and classifier priority.
- SQLite `investigations` controls live claims.
- Ghidra output is evidence; decompilation is not runtime truth.

## Output policy

Generated evidence and context files are deterministic, bounded, and provenance-aware. They are artifacts for agent handoff, not new status authorities. No raw binary bytes are copied into the pack.
