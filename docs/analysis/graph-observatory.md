# Reverse-Engineering Graph Observatory

## Purpose and current shape

The Reverse-Engineering Graph Observatory is the local, read-only human view over the OpenSpore knowledge graph and the committed reverse-engineering artifacts. It is an evidence browser, not an agent, not a Ghidra client, and not an implementation status board. Its job is to let a researcher answer four bounded questions:

1. What does the corpus contain?
2. Which evidence and provenance support a node?
3. What is missing or unresolved?
4. What bounded neighborhood should be investigated next?

The current implementation is the five-view application in `tools/viewer/static/` backed by `tools/viewer/query.py` and `tools/viewer/server.py`. The shell title is **Graph Observatory** (`tools/viewer/static/index.html:7-18`). The default runtime URL is:

```text
http://127.0.0.1:8787/
```

The old viewer baseline is documented in `tools/viewer/README.md` and the older design proposal in `docs/analysis/VIEWER.md`. Those documents are useful history, but the route list in the current `server.py` and the current static shell are the implementation source of truth. In particular, the older `VIEWER.md` describes a larger design with hash-routed pages and a different database-era shape; it is not a claim that all of those proposed views exist now.

## What the old viewer already did

The original viewer already established the safety and lifecycle model that the upgraded observatory retains:

- A single local stdlib Python process served a static HTML/JS/CSS page and JSON routes.
- SQLite was opened in strict read-only mode for each request, with explicit read-only connection handling (`tools/viewer/query.py:1-17`, `126-147`).
- The server bound to loopback only and refused non-loopback addresses (`tools/viewer/server.py:40-45`).
- `POST`, `PUT`, and `DELETE` had no write handlers and returned `405` (`tools/viewer/server.py:263-269`).
- Static serving used a fixed asset map plus a realpath containment check (`tools/viewer/server.py:70-86`).
- Unknown API paths returned structured JSON errors without terminating the worker (`tools/viewer/server.py:228-253`).
- The page was built around summary, evidence, investigation, node, and bounded-neighborhood inspection rather than preloading the entire corpus (`tools/viewer/README.md:31-49`).
- The old implementation already used structured `ok`, `degraded`, and `error` envelopes, bounded limits, escaped SQL `LIKE` searches, and a no-500 degradation contract (`tools/viewer/query.py:88-120`, `210-217`; `tools/viewer/README.md:27-29`).

The upgrade keeps those properties and adds a coherent hierarchy, richer graph views, artifact-backed projections, evidence/readiness filtering, selection dossiers, and a bounded trace simulator.

## Current views and hierarchy

The shell is one page with a fixed view navigation, an explorer, a graph canvas, and a selection dossier (`tools/viewer/static/index.html:35-200`).

| view | API root | primary source | what it exposes |
|---|---|---|---|
| **Architecture** | `/api/architecture` or `/api/hierarchy` | DB `Subsystem` and `Package` nodes, then DB `edge` neighborhoods | subsystem/package roots, contained architecture, and reverse-engineering relationships |
| **Packages** | `/api/packages` | DB `Package` nodes and incident DB edges | package inventory and package-owned anchors/dependencies |
| **Types** | `/api/types` | DB `node.attrs_json` type facets | `type`, `value_type`, and `type_semantics` values with holder counts |
| **Functions** | `/api/functions` | canonical per-function JSONL when available, with DB `triage` fallback | function identity, category, cluster, xrefs, decompilation availability, package ownership, and readiness |
| **State / events** | `/api/states` plus `/api/events` | DB event attributes merged with committed gameplay research JSON | state machines, events, callbacks, and transitions, with source references |

The browser definitions, expansion modes, and descriptions live in `tools/viewer/static/viewer.js:25-70`. Architecture is the default view (`viewer.js:87-125`). The server exposes additional APIs for hotspots, summaries, node details, function details, simulator hierarchy, investigations, and search; those APIs are not necessarily separate top-level navigation buttons.

### Architecture view

The architecture hierarchy starts with DB nodes labelled `Subsystem` or `Package`. The root request uses `depth=1` by default and returns a bounded graph slice. `query.architecture()` selects root rows, traverses `edge` rows, returns only nodes whose IDs are in the loaded node set, and reports `truncated` when node or edge caps are reached (`tools/viewer/query.py:1297-1361`).

The returned payload contains:

- `roots`: the selected root nodes;
- `hierarchy`: an alias for the selected roots;
- `nodes`: the bounded node union;
- `edges`: bounded relation rows;
- `total`: the number of root candidates, not the number of all descendants;
- `limit`, `offset`, `edge_limit`, and `truncated`: paging and truncation metadata.

The current local DB has 41 `Subsystem` rows and 23 `Package` rows, so the architecture root total observed during inspection was 64. This is a **DB-derived root count**, not the number of functions and not the canonical 58,757-function artifact universe.

If the architecture route is unavailable, the browser has a compatibility fallback to `/api/subsystems`; normal operation uses `/api/architecture` (`viewer.js:634-656`).

### Packages view

`query.packages()` reads DB nodes with `label='Package'`, optionally filters their names, and returns the page plus edges touching the selected package nodes (`tools/viewer/query.py:1364-1397`). Package nodes may therefore have incident relationships even when the edge is not itself a package hierarchy edge.

Package ownership in the Functions view is not taken from this DB label count alone. The function projection consults the committed package artifact and its cluster-to-package ownership map (`query.py:349-370`). Those package assignments are research-derived ownership boundaries, not a claim that every function in a package has reconstruction readiness.

### Types view

`query.types()` groups DB nodes by the first available JSON attribute among `$.type`, `$.value_type`, and `$.type_semantics` (`query.py:1401-1433`). The response is a paginated list of `{type, label, count, value}` records. This is a **DB-derived type-facet count**, not a complete Ghidra type inventory and not a semantic claim that every occurrence has the same meaning.

The browser turns a type facet into an aggregate node. Expanding a type searches for bounded holders and adds synthetic `has type` edges in the browser (`viewer.js:264-343`, `710-741`). That search is intentionally a compatibility projection; it is not a database relation and does not prove a class or ownership hierarchy.

### Functions view

`query.functions()` prefers the complete canonical per-function ledger:

```text
knowledgegraph/research/track-b-function-accounting.jsonl
```

When that artifact is available, the endpoint reads its rows, applies the requested search and filters, attaches reconstruction readiness by normalized VA, and returns the selected page. If the canonical artifact is unavailable, it falls back to the DB `triage` table (`tools/viewer/query.py:824-997`).

The current canonical path returns a number of research-derived fields that are not all present in the DB node table:

- VA, name, category, subsystem, and deterministic cluster;
- SDK name, struct names, and vtable addresses;
- caller and callee counts from the canonical xref projection;
- decompilation path/availability;
- gameplay affinity and infrastructure classification;
- reconstruction relevance and unresolved reasons;
- package ownership from the package artifact;
- readiness and its source.

The browser’s function sorting is intentionally a loaded-slice operation. It ranks visible nodes by loaded degree, event/field/investigation counts, confidence, and weak evidence (`viewer.js:475-512`). Those are **derived UI metrics**, not stored graph facts and not canonical global rankings.

The server also provides `/api/hotspots` and `/api/centrality`. `query.hotspots()` computes a SQL degree CTE over DB `edge` rows and, when present, adds DB `triage.caller_count` and `callee_count` to the score (`query.py:1789-1833`). It is a bounded degree/attention ranking, not betweenness centrality and not the artifact’s separate dependency-graph ranking.

### State / events view

The State / events view loads `/api/states` and `/api/events` in parallel and combines their returned collections (`viewer.js:607-631`). The server has two related data paths:

1. `_json_attribute_values()` reads DB `node.attrs_json` values for an attribute such as `states` or `events`.
2. `_load_research_index()` reads the committed `knowledgegraph/research/gameplay-state-machines.json` index and exposes state machines, events, callbacks, and transitions.

`query.states()` and `query.events()` merge DB attribute records with research records, preserve `origin` and `source_refs`, and return bounded pages (`query.py:1436-1556`). The current local output reported 115 state items and 289 event items, with 546 transitions and 242 callbacks. Those totals are **combined endpoint counts**. The endpoint does not label every item’s origin in the same way as a pure DB query, so they must not be described as DB-only counts.

Research evidence labels in the state/event artifact are not automatically identical to the DB’s seven-level `evidence_level`. For example, a research record may contain `CONFIRMED`, `SUPPORTED`, `INFERRED`, `UNRESOLVED`, `CONFIRMED_NAME_ONLY`, or a confidence object with a lower-case level. The viewer preserves the record in the detail payload and does not promote it to original runtime behavior merely because the graph renders it.

## Exact server-side query and API architecture

### Process and request flow

`tools/viewer/server.py` is a stdlib-only `ThreadingHTTPServer`:

1. `make_server()` validates the bind address and resolves the DB path (`server.py:272-283`).
2. A request is parsed into a path and repeated query-string values (`server.py:228-236`).
3. Static `/` and `/static/<fixed-name>` requests are served from a fixed map; other paths go to `_api()` (`server.py:70-86`, `238-245`).
4. `_api()` dispatches one query-layer function and returns its structured envelope.
5. `_status_code()` maps `ok` and `degraded` to HTTP 200, `not_found` and `db_missing` to 404, and other domain errors to 400 (`server.py:255-261`).
6. An unexpected exception is logged to stderr and converted to a generic JSON 500 without killing the worker (`server.py:249-253`).

Every DB query function opens its own read-only connection and closes it in a `finally` block. The connection path is:

```text
file:<absolute-db-path>?mode=ro
PRAGMA query_only=ON
```

If the first open fails, `query.py` retries with `immutable=1` (`tools/viewer/query.py:126-147`). The fallback is intended to handle stale SQLite side-files, but it has an important freshness limitation: `immutable=1` does not see uncommitted WAL pages. The primary `mode=ro` path is therefore the normal path. The implementation expects the committed local DB to be checkpointed; a live writer can change what a reader sees.

The query layer probes the DB before serving a route. `probe()` reports existence, schema status, `user_version`, required tables, and optional tables (`query.py:149-175`). The required table set is `node`, `edge`, `test_result`, `field`, `trace_run`, and `investigations`; `triage` and `xref` are optional (`query.py:44-51`). Missing or unmigrated required tables return a `degraded` envelope rather than a traceback (`query.py:178-196`).

All SQL is centralized in `tools/viewer/query.py`; the server does not contain SQL. SQL parameters are bound, table names are fixed by the query implementation, and user search text is escaped for `LIKE` (`query.py:220-222`, `668-717`, `1029-1055`, `1080-1095`). The query module also provides a CLI with the same read layer (`query.py:2080-2175`).

### Route map

The current exact HTTP route map is:

| route | query function | important parameters and behavior |
|---|---|---|
| `GET /` | static | serves `index.html` |
| `GET /static/viewer.js` | static | fixed asset name only |
| `GET /static/viewer.css` | static | fixed asset name only |
| `/api/summary` | `summary()` | direct DB counts for the six required tables, distinct binary builds, and `user_version` |
| `/api/statistics`, `/api/stats` | `statistics()` | direct DB distributions plus canonical artifact headline/xref projections |
| `/api/architecture`, `/api/hierarchy` | `architecture()` / alias | `root`, `depth=1..3`, `limit`, `offset`, `edge_limit`; DB `Subsystem`/`Package` roots and graph slice |
| `/api/packages` | `packages()` | `q`, `limit`, `offset`; DB package page and incident edges |
| `/api/functions` | `functions()` | `q`, `evidence`, `readiness`, `subsystem`, `package`, `limit`, `offset`; canonical artifact or DB triage fallback |
| `/api/search` | `search()` | non-empty `q`, `label`, `evidence`, `origin`, `readiness`, `limit`, `offset`; DB node name/attribute search |
| `/api/evidence` | `evidence_distribution()` | seven DB evidence levels, including zero levels, plus off-scale values |
| `/api/readiness` | `readiness_distribution()` | artifact readiness states and counts; no DB table is queried |
| `/api/types` | `types()` | `q`, `limit`, `offset`; DB JSON type facets grouped by label |
| `/api/states` | `states()` | `limit`, `offset`; DB `states` attributes plus research state machines/transitions |
| `/api/events` | `events()` | `limit`, `offset`; DB `events` attributes plus research events/callbacks/transitions |
| `/api/simulator`, `/api/simulator-hierarchy` | `simulator_hierarchy()` | `root`, `depth=1..3`, `limit`, `edge_limit`; DB Simulator subsystem/functions plus shared-state artifact |
| `/api/hotspots`, `/api/centrality` | `hotspots()` / alias | `label`, `relation`, `limit`, `offset`; DB degree score with optional triage counts |
| `/api/labels` | `node_label_distribution()` | paginated DB label distribution |
| `/api/investigations` | `investigation_status_distribution()` | DB status and stage distributions |
| `/api/investigation-list` | `investigations_list()` | `kind`, `q`, `status`, `limit`, `offset`; or `keys=a,b,c` exact bounded join with at most 200 keys |
| `/api/subsystems` | `subsystem_summary()` | DB subsystem nodes and investigation rollup |
| `/api/nodes` | `nodes()` | `label`, `q`, `evidence`, `origin`, `readiness`, `limit`, `offset`; DB node page |
| `/api/subgraph?ref=...` | `subgraph()` | bounded graph slice with `subgraph.nodes` and `subgraph.edges` |
| `/api/subgraph/<ref>` | `subgraph()` | same, with the path suffix URL-decoded as the reference |
| `/api/function/<ref>` | `function_detail()` | function dossier, triage, xrefs, structures, fields, state/event research, provenance, and bounded detail lists |
| `/api/node/<ref>` | `node_detail()` | DB node, fields, exact bounded investigation lookup, and provenance |
| `/api/node/<ref>/neighbors` | `node_neighbors()` | bounded BFS, `depth=1..3`, `limit`, `edge_limit`, `truncated` |
| `/api/node/<ref>/subgraph` | `subgraph()` | bounded graph slice for the selected node |
| `/api/investigation/<id>` | `investigation_detail()` | exact DB investigation row and parsed JSON fields |

`/api/investigation-list?readiness=...` deliberately returns `unsupported_filter`: `investigations.triage_status` is a queue lifecycle field, not reconstruction readiness (`query.py:668-700`). The function and readiness APIs are the supported reconstruction-readiness surfaces.

### DB path precedence

The implementation in `query.db_path()` uses the effective DB argument first and then `OPENSPORE_DB` (`tools/viewer/query.py:62-85`). The server passes its `--db` argument into that function, so in the current implementation `--db` wins when both are supplied. The older `tools/viewer/README.md` wording says the environment variable wins; that wording is stale relative to the current code. With neither supplied, the default is `<repo-root>/knowledgegraph/spore.db`.

## Read-only guarantees and boundaries

The read-only boundary has several independent layers:

- **SQLite:** every DB connection uses `mode=ro` and `PRAGMA query_only=ON`; there are no insert, update, delete, schema, or transaction-writing statements in the query layer.
- **HTTP:** only `GET` is routed. `POST`, `PUT`, and `DELETE` return `405` with a read-only message (`server.py:263-269`).
- **Network exposure:** `--bind` accepts only `127.0.0.1` or `::1`; there is no authentication, remote binding, or internet-facing mode.
- **Filesystem:** static files are selected from a fixed name map and checked with `os.path.commonpath()` containment (`server.py:70-86`). The server does not expose arbitrary files and does not open `SPORE/`.
- **Artifacts:** JSON/JSONL loaders read only the committed paths named in `query.py` under the repository. They do not write, rewrite, normalize, or import those artifacts.
- **Provenance:** API results carry `source_refs`, source paths, snapshot IDs, or source classifications where the underlying record provides them. A source reference is a pointer to evidence, not permission to claim a stronger status.
- **No orchestration calls:** the viewer does not call MCP, Ghidra REST, the observatory tracer, or the game. It is a parallel reader of the stores.
- **No original payload surface:** the viewer does not display `SPORE/**` bytes. Research source references may mention those paths, but the viewer does not fetch them.

The read-only guarantee is not equivalent to a freshness guarantee. The `immutable=1` fallback can skip uncommitted WAL pages, and a different `--db` can point at a different snapshot. The header displays the resolved DB path, and API responses include `db_path` where applicable.

## Sources and data authority

### DB tables

The core DB schema is in `knowledgegraph/schema.sql:8-172`. The viewer’s primary DB reads include:

| table | viewer use |
|---|---|
| `node` | identity, labels, names, evidence, origin, confidence, binary hash, JSON attributes, update time |
| `edge` | graph relations and degree/neighbor traversal |
| `test_result` | summary and test distributions |
| `field` | structure field rows attached to a node detail |
| `trace_run` | summary and trace outcome counts |
| `investigations` | investigation list, status/stage distributions, subsystem rollups, and node detail joins |
| `triage` | optional fallback function inventory and caller/callee metadata |
| `xref` | optional function xref detail and counts |

The DB is a local, ignored sidecar. It is a live snapshot when the viewer runs, not a committed research conclusion. Current DB values are consequently reported separately below.

### Committed function/accounting artifacts

The upgraded function path prioritizes the canonical per-function JSONL:

```text
knowledgegraph/research/track-b-function-accounting.jsonl
```

Its related summary and provenance inputs are:

```text
knowledgegraph/research/global-campaign-2026/track-b-function-accounting.json
knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl
knowledgegraph/triage/reconstruction-readiness-f0e310e0.json
knowledgegraph/triage/xrefs-2540f2ca.summary.json
knowledgegraph/triage/xrefs-2540f2ca.tsv
knowledgegraph/research/21-decompilation-coverage.json
```

The canonical ledger is described as an exact 58,757-row, unique-VA universe with ascending lexical VA order. The campaign summary reports 58,757 canonical rows, 365 queue rows inside the canonical universe, and three readiness rows outside it (`knowledgegraph/research/global-campaign-2026/track-b-function-accounting.json:11-78`, `262-269`). The 58,757 value is therefore **research-artifact-derived**, not a `node` table count.

The viewer’s `functions` response labels this source explicitly with `source`, `accounting_source`, `source_refs`, `canonical_function`, and `inventory`. Consumers should not treat a `functions[].id` as a DB node ID without following its `source_refs`.

### Packages and semantic ownership

Package ownership is read from:

```text
knowledgegraph/research/global-campaign-2026/track-o-packages-testability.json
```

The package artifact defines 23 semantic ownership packages and a 20-cluster mapping. It explicitly says packages are ownership boundaries, not per-function reconstruction claims, and that the unresolved package covers the long tail without inventing subsystem splits (`track-o-packages-testability.json:53-83`). The function projection maps canonical clusters to one or more package IDs where that artifact has a mapping (`query.py:349-370`).

### Shared-state and simulator artifact

The Simulator hierarchy is assembled from:

```text
knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json
```

The artifact has an 11-root ordered interface set plus a generic map prerequisite, static structures/fields, and nine direct interface edges. It states that the set is Phase-0 reconnaissance and that no runtime evidence is present (`simulator-shared-state-interface-f0e310e0.json:10-25`, `27-39`, `122-282`). `query.simulator_hierarchy()` joins those artifact roots to DB `Function` rows and returns the artifact’s interfaces and bounded structures (`query.py:1694-1784`).

The simulator endpoint has two availability fields. `artifact_available` means the shared-state JSON could be loaded; `available` means the DB Simulator subsystem row was found. Neither means that a runtime trace exists. The artifact’s `runtime_evidence: false` remains authoritative.

### State/event research

The State / events view reads:

```text
knowledgegraph/research/gameplay-state-machines.json
```

The committed merge index is backed by the files under:

```text
knowledgegraph/research/state-machines/
```

The research document explicitly says it is clean-room research documentation, not an implementation plan, and that static evidence is not positive original-process evidence for gameplay transitions (`docs/analysis/gameplay-state-machines.md:3-18`). The viewer preserves source records and provenance rather than making the state/event graph an execution trace.

### Historical and design artifacts

The viewer does not ingest every analysis document as a new graph node. Existing dossiers, research reports, and historical triage files are references and source material. The older `docs/analysis/VIEWER.md` design describes broader planned functionality; it should be read as historical architecture, not as a current route contract.

## Count semantics: DB-derived, artifact-derived, and derived metrics

### Current local DB snapshot observed during inspection

The following values came from the current local `knowledgegraph/spore.db` on 2026-09-24 through the read-only query layer. They are a local DB snapshot, not hard-coded viewer values and not committed source-of-truth counts.

| direct DB source | observed value |
|---|---:|
| `node` rows | 67,871 |
| `edge` rows | 28,853 |
| `test_result` rows | 28 |
| `field` rows | 25,561 |
| `trace_run` rows | 2 |
| `investigations` rows | 1,704 |
| distinct non-null `node.binary_sha256` values | 1 |
| `PRAGMA user_version` | 4 |
| optional `triage` rows | 58,757 |
| optional `xref` rows | 223,704 |

The current `/api/summary` response contains the first six direct counts. The optional counts appear in `/api/statistics`, not `/api/summary`. The browser’s “corpus nodes” metric is the direct `summary.counts.node` value (`viewer.js:1116-1131`).

### Direct DB distributions observed locally

The current local DB evidence distribution was:

```text
APPROXIMATION  2
CONFIRMED      3,707
INFERRED       3,836
OBSERVED         2
SUPPORTED     59,042
UNKNOWN        1,234
VERIFIED          48
```

The current investigation status distribution was `queued=1,665` and `done=39`; the stage distribution was `QUEUED=1,665` and `RECORDED=39`. These are direct DB group-by counts. The current label inventory includes semantic and provenance labels in addition to the original KG labels; it is not interchangeable with the canonical function category distribution.

The architecture endpoint reported 64 root candidates: 41 DB `Subsystem` rows plus 23 DB `Package` rows. The types endpoint reported 8 DB JSON type-facet groups. Both are direct DB route results.

### Research-artifact counts

The following figures are read from committed research artifacts and are not direct DB counts:

- Canonical function universe: **58,757** unique VAs.
- Canonical gameplay population: **2,149** functions (`GAMEPLAY_LOGIC` or `GAMEPLAY_SUPPORT`).
- Readiness queue: **368** rows; **365** inside the canonical function universe and **3** outside it.
- Readiness states in the queue artifact: `READY=6`, `READY_WITH_LOCAL_CONTEXT=29`, `DEPENDENCY_FIRST=24`, `ENGINE_BOUNDARY=23`, `NEEDS_RE=101`, `LIKELY_INFRASTRUCTURE=185`.
- Canonical xref artifact: **223,704** unique rows, including **207,757** call-type rows; data and vtable references are retained but excluded from call-type counts.
- Persisted decompilation body accounting: **478** bodies and **58,279** unavailable rows across the canonical ledger; this is a coverage ledger, not a claim that Ghidra cannot decompile the unavailable functions.
- Package artifact: **23** semantic ownership packages over a 20-cluster source partition.

These figures appear in artifact-backed `statistics`, `functions`, and `readiness` payloads. They must not be compared directly with `node` or `edge` counts without checking the response field’s `source` and `source_refs`.

### Derived metrics

The following are computed or assembled by the viewer and are not persisted KG facts:

- visible node count after client filters;
- loaded edge count after endpoint union and client visibility filtering;
- readiness-reported fraction among visible nodes;
- mean visible-node confidence;
- browser hotspot score, which combines loaded degree, events, fields, investigations, confidence, and weak evidence;
- loaded degree and in/out direction counts when an edge is not already cached;
- graph layout coordinates and hierarchy display;
- research item counts after DB/research merging;
- `truncated` and `available` display states.

The old hotspot endpoint’s SQL score is also derived from current DB degree and optional triage counts. It is not a canonical global centrality claim.

## Evidence semantics

The DB’s canonical evidence scale is defined once in `knowledgegraph/scale.py:8-21`:

```text
UNKNOWN < APPROXIMATION < INFERRED < SUPPORTED < OBSERVED < CONFIRMED < VERIFIED
```

`scale.py` also defines mappings for replacement status and legacy evidence strings, but the viewer does not apply the replacement-status mapping to every record. The DB `node.evidence_level` column is constrained to the seven-level scale (`knowledgegraph/schema.sql:8-22`), and `/api/evidence` returns those levels with zero entries included (`query.py:593-622`).

The artifact function accounting uses a different accounting vocabulary for name evidence, including `APPROX`, `CONFIRMED`, `INFERRED`, `SUPPORTED`, and `UNKNOWN` (`knowledgegraph/research/track-b-function-accounting.md:50-58`). The function endpoint exposes that artifact value in its statistics and row projection. The browser’s `canonicalEvidence()` accepts only the seven canonical names and maps anything else to `UNKNOWN` (`viewer.js:206-218`). Therefore an artifact `APPROX` value is not silently promoted to `APPROXIMATION`; it can display as an unknown/unmatched value until an explicit adapter is added. This is a normalization limitation, not a semantic claim.

The seven-level badges also do not make every claim equivalent. In the research policy:

- `CONFIRMED` can be direct static evidence or name-level provenance depending on the source;
- `SUPPORTED` can be multiple consistent sources or a bounded deterministic differential;
- `OBSERVED` requires a pinned artifact or runtime observation under the source’s scope;
- `VERIFIED` requires byte- or runtime-validated evidence under a validation gate;
- `UNKNOWN`, `UNRESOLVED`, and `NOT_OBTAINED` remain explicit gaps.

The function-accounting artifact specifically says SDK names and vtable relationships are evidence, not observed behavior or verified semantics, and that the supplied contract status is unknown for all canonical rows (`knowledgegraph/research/global-campaign-2026/track-b-function-accounting.json:234-252`, `289-325`). The viewer must preserve that distinction when displaying a badge, source reference, or detail panel.

## Readiness semantics and absent states

Reconstruction readiness is not the same as `investigations.triage_status`.

### Queue readiness

`readiness_distribution()` reads only:

```text
knowledgegraph/triage/reconstruction-readiness-f0e310e0.json
```

It parses `queue.per_function`, keyed by normalized VA, and returns the declared queue vocabulary and counts (`query.py:294-347`, `1559-1575`). The current artifact has 368 per-function queue rows and six declared states. The endpoint’s `total` is the number of declared states; `function_total` is the number of per-function readiness rows.

The function projection attaches readiness only when a canonical function VA matches a readiness row. The function response distinguishes:

- `readiness_artifact_total`: all readiness artifact rows, including the three outside the canonical function universe;
- `readiness_total`: readiness rows matched to canonical functions;
- `readiness_outside_canonical`: the explicit out-of-universe delta.

The three outside rows are retained in the artifact summary but cannot be selected as canonical function nodes in the function ledger. The viewer does not fabricate matching function or xref rows for them.

### Not assessed is not a selectable readiness state

The canonical accounting summary reports `not_assessed=58,392` for the full function universe, but this is a summary of the queue-scoped readiness policy: most functions have no queue readiness record. It is not a seventh queue state emitted by `/api/readiness`.

The current browser readiness filter is populated from the six artifact states returned by `/api/readiness`. There is no `not_assessed` or `not reported` option. A function without a readiness match displays `not reported` in the UI because `readinessKey()` uses that fallback (`viewer.js:220-233`), but users cannot select that state through the current filter. This is an explicit absent-state limitation.

Similarly, a DB node with no readiness attribute displays no readiness claim. The UI may fall back to an investigation’s `triage_status` when displaying a selected function (`viewer.js:1438-1457`), but that is a compatibility display fallback, not a conversion of queue lifecycle into reconstruction readiness. Server-side readiness filters reject this ambiguity rather than inventing a normalized state.

### Normalized-state limitations

The viewer performs limited normalization only:

- VAs are lowercased and an optional `0x` prefix is removed in `_normalize_va()` (`query.py:289-291`).
- Function lookup can use `fun:<va>`, a raw VA in selected attributes, and a `fun:` node name in the simulator/function paths.
- Node lookup itself is exact by numeric ID or exact name; an ambiguous name returns `ambiguous` (`query.py:1122-1138`).
- Frontend aliases map raw API references, node IDs, and names to loaded nodes (`viewer.js:384-395`).
- The browser maps evidence to the seven-level display scale and all unrecognized values to `UNKNOWN` (`viewer.js:206-218`).

There is no general alias graph that automatically equates arbitrary names, historical addresses, RVA/VA forms, SDK aliases, snapshot-only rows, and semantic package IDs. There is also no single universal state normalizer across the DB triage lifecycle, the reconstruction queue vocabulary, package statuses, research confidence objects, and the old replacement-status vocabulary. Extending the viewer should add an explicit, source-aware adapter rather than silently collapsing these fields.

## Bounds, paging, and lazy expansion

### Server bounds

The current query constants are (`tools/viewer/query.py:44-53`):

| bound | value | purpose |
|---|---:|---|
| `_MAX_LIMIT` | 1,000 | general collection page maximum |
| `_MAX_GRAPH_NODES` | 500 | graph node maximum |
| `_MAX_GRAPH_EDGES` | 2,000 | graph edge maximum |
| `_MAX_ITEMS` | 500 | bounded detail/centrality item maximum |
| `_MAX_DETAIL_ITEMS` | 100 | research detail list maximum |
| `_MARK_CHUNK` | 400 | SQL `IN` chunk size |
| `_MAX_KEYS` | 200 | exact investigation join keys |

Graph `depth` is constrained to `1..3`; invalid values return `invalid_params`. Graph traversal is breadth-first and chunked, and stops with `truncated=true` when either cap is reached (`query.py:1190-1253`, `1256-1283`). The architecture endpoint uses the same bounded graph slice (`query.py:1297-1361`).

General list endpoints accept `limit` and `offset`, reject non-positive limits or negative offsets, and cap limits. The default limit is generally 200; architecture and simulator use graph defaults of 500 nodes and 2,000 edges. `subgraph` defaults to depth 2, while `neighbors` defaults to depth 1. Function detail is capped by the general detail limit, while its internal research lists are further bounded by `_MAX_DETAIL_ITEMS`.

### Browser bounds

The static shell adds a second, smaller display budget (`tools/viewer/static/viewer.js:72-85`):

| bound | value |
|---|---:|
| root request | 64 |
| child expansion | 48 |
| global search | 24 |
| function detail | 80 |
| visible graph nodes | 80 |
| loaded nodes | 240 |
| rendered graph edges | 220 |
| simulator queue/trail | 24 |
| request timeout | 12 seconds |

These are UI bounds, not claims about total corpus size. A user can navigate and expand more branches over time, but each response and the client corpus remain bounded.

### Lazy-loading strategy

The observatory intentionally avoids a full corpus preload:

1. Load only the current view’s root slice.
2. Render a bounded root graph and mark nodes with children as expandable.
3. Fetch one level of neighbors when the user expands a node.
4. Fetch a bounded type-holder search only for aggregate type facets.
5. On selection, fetch the node/function dossier and a one-level neighbor slice in parallel.
6. Merge only nodes and edges relevant to the visible slice.
7. Remove descendants and incident edges when a branch is collapsed.
8. Run the simulator only over already loaded, view-compatible edges; do not perform an unbounded graph walk.

The relevant browser flow is `loadViewRoot()`, `mergePayload()`, `expandNode()`, `collapseBranch()`, and `selectNode()` (`viewer.js:398-435`, `663-785`, `787-835`, `1402-1472`). The server does the actual filtering and paging; the browser still applies category, evidence, readiness, and visible-node limits before rendering.

### Artifact loading performance

The DB connection is short-lived and per request, which keeps locking and mutable state out of the process. The large canonical JSONL ledger is loaded into a bounded LRU cache keyed by path, modification time, and size (`query.py:418-445`). This is a server-side process cache, not browser preload and not a persisted viewer cache. JSON artifact loads are checked for availability and source metadata, and malformed or missing artifacts become explicit unavailable/degraded states rather than silent claims.

The artifact files are large: the per-function JSONL is a 58,757-row source, and the gameplay state-machine index is a large merged JSON document. The viewer reads the bounded projections it needs but does not render the entire source file into the DOM. A future extension should preserve artifact caching and explicit source references, not add an unbounded raw-artifact route.

## Search behavior

There are two distinct search paths.

### Global graph search

The browser global search requires at least two non-whitespace characters and caps browser input at 120 characters (`index.html:19-25`; `viewer.js:902-911`). It calls:

```text
/api/search?q=<text>&limit=24
```

The server rejects an absent or empty `q`, and searches the DB `node.name` and `attrs_json` with escaped, case-insensitive-style `LIKE` patterns. The SQL shape is:

```text
(name LIKE ? ESCAPE '\' OR attrs_json LIKE ? ESCAPE '\')
```

Optional `label`, `evidence`, and `origin` filters are applied. A `readiness` filter is accepted only for Function nodes and only when the readiness artifact has per-function rows (`query.py:1059-1119`). Results are ordered by label/name/id and paginated. `%` and `_` are escaped so a user query is literal rather than an accidental SQL wildcard.

The browser normalizes the returned DB nodes, applies the active evidence/readiness filters, and displays at most 24 results. Clicking a result loads that node into the current view if capacity permits (`viewer.js:902-965`). If `/api/search` is unavailable, the browser can fall back to the older name-only `/api/nodes?q=...` route and labels that result source as a compatibility index (`viewer.js:914-940`).

Global search does not search the complete canonical JSONL by default and does not infer semantic package membership. It searches the current DB node surface. The Functions view’s own `q` is a separate canonical-artifact search.

### Function and artifact search

`/api/functions?q=...` searches the canonical ledger’s VA, name, SDK name, KG node ID, and struct names before applying evidence, subsystem, package, and readiness filters (`query.py:833-856`). If the canonical ledger is unavailable, the fallback searches DB `triage` names, normalized names, VA, and KG node ID (`query.py:914-944`).

Type expansion uses `/api/search` with a bounded type token and then checks the candidate’s raw `attrs.type`, `attrs.value_type`, or `attrs.type_semantics` fields. State/event detail matching for a function is performed inside `query.function_detail()` against the research index, not by global search (`query.py:529-560`, `1931-1941`).

The search routes do not promise fuzzy matching, stemming, full-text ranking, alias resolution, or search across all committed Markdown reports. Those would be new features, not existing behavior.

## Validation and test status

The viewer’s current test entry point is:

```bash
python3 -m unittest discover -s tests -t .
```

The focused suites are `tests/viewer/test_server.py` and `tests/test_viewer.py`. They cover the current safety and core query contract, including:

- static shell and core API envelope responses;
- summary, evidence, labels, investigation, subsystem, node, and neighbor behavior;
- exact node lookup and ambiguous-name behavior;
- escaped search wildcards, filters, paging, and empty results;
- depth- and limit-bounded graph traversal and `truncated` reporting;
- missing DB degradation without a 500;
- unknown paths returning 404 while the server remains alive;
- static traversal refusal;
- non-loopback bind refusal;
- read-only DB snapshots and write attempts against the test DB.

`tests/viewer/test_server.py` also checks that a full crawl of its route list leaves the local committed DB’s hash, mtime, and side-file names unchanged when that DB is present (`test_server.py:277-325`). The contract suite independently checks that a read-only DB cannot be mutated (`test_viewer.py:299-340`).

The existing route list in `tests/viewer/test_server.py` is older than the current upgraded API surface. It does not exhaustively crawl every new architecture, package, canonical-function, type, state/event, simulator, hotspot, or function-detail combination.

The focused command run during this documentation inspection ran 21 tests with 20 passing and 1 failure. The failure is in `tests/test_viewer.py:242-261`, `test_package_evidence_and_readiness_filters_are_applied`: the current `query.py` readiness path uses the reconstruction-readiness artifact and returns artifact-matched Function nodes, while that test still expects the older DB `triage_status` behavior for `sub:movement` and `fun:00100000`. This is recorded as a current implementation/test-contract gap; no query code or test was changed for this documentation task.

Before changing or extending the observatory, add focused tests for:

- the current architecture/root and depth contract;
- artifact-backed function paging and source precedence;
- readiness absence, out-of-universe readiness rows, and unsupported filters;
- research/DB state-event origin preservation;
- simulator artifact availability versus DB availability;
- current static assets and client-side view switching;
- the exact server route map and all invalid-limit/depth responses.

The historical test description in `docs/analysis/VIEWER.md` describes a broader old route plan and should not be used as a claim that those routes are currently tested.

## How to run

From the repository root:

```bash
python3 tools/viewer/server.py
```

The exact default URL is:

```text
http://127.0.0.1:8787/
```

The server prints the resolved URL and DB path to stderr. The default bind is `127.0.0.1`; the default port is `8787`. Stop with `Ctrl-C`.

Available flags in the current server are:

```bash
python3 tools/viewer/server.py --bind 127.0.0.1 --port 8787 --db knowledgegraph/spore.db
```

- `--bind`: only `127.0.0.1` or `::1`; any other value is refused.
- `--port`: TCP port, default `8787`.
- `--db`: absolute path, or a path relative to the repository root. `OPENSPORE_DB` is used when no effective CLI DB argument is supplied; the current `query.db_path()` implementation gives the effective CLI argument precedence.
- Default DB: `<repo-root>/knowledgegraph/spore.db`.

There is no `--root` flag in the current `server.py`; the old `docs/analysis/VIEWER.md` proposal described a different root-oriented harness. Use the current server flags and `OPENSPORE_DB`/current relative path behavior.

If the DB is missing, the process still serves the static page and returns a structured `degraded` summary; it does not repair or initialize the DB. If the DB schema is missing required tables, the same degradation policy applies. The viewer never runs `kg.py init`, never seeds data, and never opens `SPORE/`.

## How to extend safely

1. **Add a bounded query function in `tools/viewer/query.py`.** Keep SQL in that module, use explicit parameters, validate paging and depth, return an envelope, close the connection, and include source provenance for any artifact-derived value.
2. **Add the server route in `tools/viewer/server.py`.** Parse only the query parameters it needs, keep the route read-only, use a stable envelope, and add the route to the exact route map. Do not add a write handler or an arbitrary static file path.
3. **Declare source authority.** Decide whether the route reads the DB, a committed artifact, or a merge of both. Put the distinction in fields such as `source`, `source_refs`, `origin`, `available`, and `truncated`; do not let a derived number look like a direct count.
4. **Set server and browser bounds.** Choose a server cap that protects SQLite/JSON parsing and a smaller client cap that protects the SVG/DOM. Return truncation metadata rather than silently returning a partial answer.
5. **Add lazy expansion rather than corpus preload.** Extend the current root → child → selection flow, and use collapse removal and visible-node filtering to keep the graph bounded.
6. **Add a UI view only if the API contract is useful.** Add a `VIEW_DEFINITIONS` entry, category membership, root parameters, expansion mode, detail rendering, and a compatibility fallback only when the old route is genuinely absent.
7. **Add validation and normalization explicitly.** For a new evidence or readiness vocabulary, add a source-aware adapter and tests. Do not silently map `APPROX` to `APPROXIMATION`, map investigation lifecycle to reconstruction readiness, or turn a name/vtable association into runtime behavior.
8. **Test read-only behavior.** Add a route crawl, malformed parameter cases, a missing-source case, and a DB/artifact snapshot check. Keep the test independent of `SPORE/`, Wine, Ghidra, and network access.

The observatory is ready for bounded human inspection when its source labels, caps, and absence states remain visible. It is not a semantic completion signal: an empty or truncated result, an unknown evidence badge, a missing readiness state, and a research artifact gap are all valid findings and must remain distinguishable from success.
