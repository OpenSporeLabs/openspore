# Reconstruction staging

Workers own disjoint directories under `staging/`. A worker writes source and focused tests only inside its assigned package directory, then reports:

- source files changed
- functions reconstructed
- types added or changed
- tests added
- unresolved questions
- evidence references
- dependency blockers

`metadata/` stores per-function and per-type evidence handoffs. `integrated/` is integrator-owned and is not a worker scratch area. The canonical manifest remains `knowledgegraph/research/source-reconstruction-manifest.json`.
