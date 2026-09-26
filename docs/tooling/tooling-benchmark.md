# Tooling benchmark

Measurements were taken on 2026-09-25 against the current repository state. They are workflow measurements, not claims about reconstruction correctness.

## Command and time

| Workflow | Baseline | Automated result |
|---|---:|---:|
| Manual evidence assembly protocol | 7 distinct reads/commands: manifest, triage queue, index, metadata/handoff, xref data, Ghidra snapshot, candidate source | 1 `recover` command; no-write run 0.923 s, including an ephemeral canonical projection rebuild |
| Existing function query | `python3 -m tools.reconstruction_knowledge function --va 0x00e5b790`, 12,840 bytes, one unstructured line | bounded evidence/context/validation pack |
| Frontier listing | separate queue/index/claim inspection | one JSON frontier query, 0.947 s for 20 targets, including projection rebuild |

The manual baseline count is a reproducible assembly protocol, not a claim that every analyst performs exactly those reads. The automated timing excludes human interpretation and source review.

## Context size and coverage

Measured generated artifacts:

| Target | Evidence JSON | Context JSON | Available categories | Context sections |
|---|---:|---:|---:|---:|
| `0x00e5b790` | 33,220 bytes | 22,540 bytes | 10/17 | 15 |
| `0x008db310` | 19,940 bytes | 12,215 bytes | 7/17 | 15 |
| `0x00576c50` | 38,379 bytes | 27,812 bytes | 7/17 | 15 |

The context is larger than the legacy function query because it deliberately adds ABI, dependency, semantic, conflict, question, validation, and provenance sections. It is bounded and structured; oversized values carry a digest and preview rather than an unbounded dump.

## Information quality

For `0x00e5b790`, the pack retained nine distinct provenance references and exposed ten available categories out of seventeen. For both unclaimed dogfood targets, it exposed seven available categories and explicitly marked missing decompilation/source/runtime evidence instead of filling gaps. The context always has fifteen sections, including `missing` and `conflicted` states.

The automated path reduced command count from seven assembly steps to one orchestration command, preserved exact source references, and made duplicate/provenance handling deterministic. It did not reduce the need for source review; it reduced context acquisition and coordination overhead.

## Orchestrated pipeline

Measured 2026-09-25 after the orchestration layer landed. All figures are
wall-clock medians from the machine that produced the dogfood run; the
repository state was unchanged during measurement. Cold means the first call
in a fresh process; warm means the projection is already built in memory.

| Stage | Cold | Warm | Notes |
|---|---:|---:|---|
| `orchestrate plan --limit 400` | 1.40 s | 0.30 s | rebuilds the canonical projection from the manifest, triage queue, xref table and semantic ledger |
| `swarm --limit 200` | ~1.3 s | ~0.3 s | shares the projection rebuild; a separate call is the dominant cost of any second planning command |
| `collect_inputs` persisted (evidence + context + validate) | 1.10 s | 1.7 ms | the cold cost is the projection rebuild, not the per-target work |
| `collect_inputs` with live Ghidra | 0.26 s | 0.26 s | one GhidraMCP round trip for decompilation, disassembly and function metadata |
| `briefing` build | 0.2 ms | 0.2 ms | pure projection of already-collected inputs |
| `queue_op claim` + `release` round trip | 6.0 ms | 6.0 ms | `BEGIN IMMEDIATE` plus compare-and-set, against the real 109 MB sidecar |
| `orchestrate run`, 8 targets, 8 workers | 0.59 s | 0.59 s | plan, 8 claims, 8 briefings, 8 fixture workers, 8 validations, 8 releases |

Two facts in that table matter more than the numbers themselves.

**The projection rebuild dominates every cold path.** A cold `collect_inputs`
costs 1.10 s and a warm one 1.7 ms, a 650x difference, and the difference is
entirely `reconstruction_knowledge.build_index`. The orchestrator builds the
plan once and reuses the cached projection for every target in the run, which
is why an 8-target run costs 0.59 s rather than 8 x 1.10 s. Any future caller
that calls `frontier`, `swarm` or `plan` once per target instead of once per
batch will pay the rebuild per target and lose an order of magnitude.

**Claim latency is not the bottleneck.** 6 ms for a full lease acquire and
release round trip against the real database means the compare-and-set lease
is not a scaling concern at swarm sizes measured here, even with several
workers contending for the same file.

## Baseline comparison

The manual baseline for the same work is not a single command. Before the
orchestration layer, one target required a human or agent to: run `frontier` or
`swarm` to find it, read the claim state separately, claim nothing (there was no
claim verb reachable outside MCP), assemble the evidence, assemble the context,
hand the target to a worker with prose instructions, parse the worker's prose
reply, run `validate` by hand, decide what the verdict meant, and update the
manifest and handoff by hand. The comparison the automated path makes:

| Outcome | Manual | Automated |
|---|---|---|
| Ownership acquisition | none available outside MCP stdio | one `queue_op claim`, 6 ms |
| Double-ownership protection | none | compare-and-set; concurrency-tested |
| Worker handoff | prose, unparseable | one JSON briefing, digest-tracked |
| Worker result | prose, unparseable | one JSON document, strictly validated |
| Target completion decision | human judgement per target | fixed verdict-by-outcome table |
| Stale-lease recovery | manual inspection | explicit `allow_stale` reclaim with an audit trail |

The pipeline does not make reconstruction faster in the sense of writing more
C++ per hour, and it does not claim to. What it removes is the coordination tax:
the sequence of reads, the ownership ambiguity, and the interpretation step
between a validator verdict and a queue state.

## Dogfood measurements

Two live batches were run on real frontier targets.

**Live-agent batch, 6 targets.** Six real reconstruction workers were given
real briefings built from live Ghidra evidence, one per target, spanning six
clusters and six subsystems. Each produced a candidate header, implementation
and model test plus a metadata sidecar. All six results were ingested by the
real `parse_result`, all six were validated by the real validator, and all six
resolved to `review_required` with verdict `WARN` and `source.role = "staging"`,
which is the correct outcome: a staged candidate with structural warnings is a
review item, never a completion. The run took 1.37 s of orchestration time for
the six, excluding worker time.

**Fixture batch, 12 targets.** Twelve real frontier targets across 10 clusters
were run through the whole pipeline with a deterministic worker, exercising all
four outcome classes. Result: 2 `review_required` (the honest `STILL_UNKNOWN`
and `FAILED_VALIDATION` outcomes, correctly routed to review) and 10 blocked at
`escalated:candidate_not_validatable` after exactly 3 attempts each. 32 worker
invocations for 12 targets, no unbounded loop, 0 leases left held.

The validator returning `NOT_AVAILABLE` for the fixture batch is the honest
result and not a defect: the fixture claims an implementation without producing
a source artifact, so there is nothing for the validator to check. The pipeline
treated that as a retryable candidate defect rather than a review item, which
is the routing that stopped the run from silently marking unvalidatable work
complete.

