# tools/viewer — knowledge-graph web viewer

Local, read-only web dashboard for the OpenSpore knowledge graph
(`knowledgegraph/spore.db`).

**Read-only, guaranteed.** The server opens SQLite in strict read-only mode
(`file:...?mode=ro`, per request, closed after each response). No write
endpoints exist (POST/PUT/DELETE → 405); nothing in this tool can mutate the
DB — a full route crawl leaves `spore.db` bit-identical (covered by the test
suite).

## Launch

From the repo root:

    python3 tools/viewer/server.py
    → http://127.0.0.1:8787

Flags:

| flag | meaning |
|------|---------|
| `--port N` | listen port (default 8787) |
| `--bind H` | loopback only: `127.0.0.1` or `::1`; anything else is refused |
| `--db PATH` | DB path (abs, or rel vs repo root); `OPENSPORE_DB` env wins |

Default DB: `knowledgegraph/spore.db`. If it is missing (e.g. fresh clone)
the viewer keeps running and reports a **degraded** envelope with a banner on
the page — it never crashes and never 500s.

## Views

One page, every value fetched from the API (nothing hardcoded):

- header: project name + DB path + degraded banner
- project summary: node / edge / test / investigation / field / trace-run
  counts, distinct builds (`/api/summary`)
- evidence: canonical evidence-level distribution, zeros included
  (`/api/evidence`)
- investigation status: status + stage counts (`/api/investigations`)
- subsystems: per-subsystem investigation rollup (`/api/subsystems`)
- node inventory: name search + label filter, paginated table; the
  **Functions** tab adds address/RVA, provenance (sdk_name / dossier src /
  trace), and per-function investigation state via one bounded server-side
  join for the visible page only (`/api/nodes`,
  `/api/investigation-list?keys=...`)
- node detail (row click): identity, provenance (dossier ref shown, never
  fetched), fields, neighbors depth 1, investigations with
  `/api/investigation/<id>` drill-in

## API

`/api/summary`, `/api/evidence`, `/api/labels`, `/api/investigations`,
`/api/investigation-list?kind=&q=&status=&limit=&offset=`
(`?keys=a,b,c` = bounded exact-match join lookup, ≤200 keys),
`/api/subsystems`, `/api/nodes?label=&q=&limit=&offset=`,
`/api/node/<id|name>`, `/api/node/<id|name>/neighbors?depth=1|2`,
`/api/investigation/<id>`. Envelope: `{"status":"ok",...}` /
`{"status":"error","code":...,"message":...}` / `{"status":"degraded",...}`.

The query layer is also a CLI: `python3 tools/viewer/query.py summary` (and
`nodes`, `node`, `neighbors`, `investigation`, `investigations-list`, ...).

## Implementation

One stdlib-only Python process (`http.server`) + one static HTML/JS/CSS page
(vanilla fetch + DOM). No framework, no build step, no CDN, no external
assets.

## Tests

    python3 -m unittest discover -s tests -t .

The viewer subset lives in `tests/viewer/` (route crawl, read-only
guarantees, degraded mode, bind validation, committed-DB bit-identity).
