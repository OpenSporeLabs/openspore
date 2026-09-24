-- OpenSpore shared knowledge-graph sidecar
-- Small, versioned, git-committable memory shared across agents/tools.
-- The binary/structure analysis graph lives in Ghidra; this store holds the
-- cross-tool results: test outcomes, decisions, asset-format mappings.

PRAGMA journal_mode = WAL;

CREATE TABLE IF NOT EXISTS node (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    label       TEXT NOT NULL,          -- Class | Function | Structure | Resource | Renderer | Method | ...
    name        TEXT NOT NULL,
    attrs_json  TEXT NOT NULL DEFAULT '{}',
    confidence  REAL NOT NULL DEFAULT 0.0,   -- 0..1
    origin      TEXT NOT NULL DEFAULT 'unknown', -- static | dynamic | sdk | llm | manual
    note        TEXT,
    created_at  TEXT NOT NULL DEFAULT (datetime('now')),
    evidence_level TEXT NOT NULL DEFAULT 'UNKNOWN'
        CHECK (evidence_level IN ('UNKNOWN','APPROXIMATION','INFERRED',
            'SUPPORTED','OBSERVED','CONFIRMED','VERIFIED')),
    updated_at  TEXT NOT NULL DEFAULT (datetime('now')),
    binary_sha256 TEXT,
    UNIQUE (label, name)
);

CREATE TABLE IF NOT EXISTS edge (
    id    INTEGER PRIMARY KEY AUTOINCREMENT,
    src   INTEGER NOT NULL REFERENCES node(id) ON DELETE CASCADE,
    dst   INTEGER NOT NULL REFERENCES node(id) ON DELETE CASCADE,
    rel   TEXT NOT NULL,                -- hasPart | usedBy | inheritsFrom | calls | loads | ...
    UNIQUE (src, dst, rel)
);

CREATE TABLE IF NOT EXISTS test_result (
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    name       TEXT NOT NULL,
    stage      TEXT,                    -- cell | creature | tribe | civ | space
    seed       TEXT,
    expected   TEXT,
    actual     TEXT,
    pass       INTEGER,                -- 0 | 1 | NULL (unknown)
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);

CREATE TABLE IF NOT EXISTS field (
  id            INTEGER PRIMARY KEY,
  struct_id     INTEGER NOT NULL REFERENCES node(id) ON DELETE CASCADE, -- Class/Structure node
  offset        TEXT    NOT NULL,            -- '0x4C' / '0x4C..0x4F'
  role          TEXT    NOT NULL,            -- 'cellPos'
  offset_evidence  TEXT NOT NULL DEFAULT 'UNKNOWN' CHECK (offset_evidence  IN ('UNKNOWN','APPROXIMATION','INFERRED','SUPPORTED','OBSERVED','CONFIRMED','VERIFIED')),
  meaning_evidence TEXT NOT NULL DEFAULT 'UNKNOWN' CHECK (meaning_evidence IN ('UNKNOWN','APPROXIMATION','INFERRED','SUPPORTED','OBSERVED','CONFIRMED','VERIFIED')),
  value         TEXT,                        -- current known/assumed value
  source        TEXT,                        -- hash-pinned provenance
  binary_sha256 TEXT,
  created_at    TEXT NOT NULL DEFAULT (datetime('now')),
  updated_at    TEXT NOT NULL DEFAULT (datetime('now')),
  UNIQUE (struct_id, offset)
);

CREATE TABLE IF NOT EXISTS trace_run (
  id            INTEGER PRIMARY KEY AUTOINCREMENT,
  binary_sha256 TEXT NOT NULL,
  probes_sha256 TEXT,                        -- hash of the probe set file
  wine_version  TEXT,
  display_env   TEXT,
  xdotool       TEXT,
  captured_at   TEXT NOT NULL DEFAULT (datetime('now')),
  events_total  INTEGER,
  jsonl_path    TEXT,                        -- committed trace archive
  screenshots_count           INTEGER,
  screenshots_first           TEXT,
  screenshots_last            TEXT,
  screenshots_manifest_path   TEXT,
  outcome     TEXT,
  replayable  TEXT DEFAULT 'input-logged, stage-deterministic, non-bit-exact'
);

CREATE TABLE IF NOT EXISTS investigations (
  id             TEXT PRIMARY KEY,  -- 'fn:0x00e5b790:MovePlayerToMousePosition' | 'sub:resource-manager-full'
  kind           TEXT NOT NULL,     -- 'function' | 'subsystem'
  va             TEXT, name         TEXT, subsystem     TEXT,
  mode           TEXT NOT NULL,     -- 'replace' | 'understand'
  why_interesting TEXT NOT NULL,
  stage          TEXT NOT NULL,     -- stage vocabulary; QUEUED when status='queued'
  status         TEXT NOT NULL,     -- 'queued'|'active'|'blocked'|'done'|'dropped'
  block_reason   TEXT,              -- 'approval_required:<tool>'|'escalated'|'ghidra_offline'|'no_spo'|'machine_locked'
  prerequisites  TEXT,              -- JSON: [task ids / gate keys]
  attempts       TEXT,              -- JSON {stage: count}
  checkpoint     TEXT,              -- JSON blob
  evidence_refs  TEXT,              -- JSON [artifact paths + KG node names]
  implementer_id TEXT, adjudicator_id TEXT,
  created_at TEXT, updated_at TEXT,
  binary_sha256 TEXT NOT NULL,
  -- Queue lifecycle (triage-v4): canonical queue_state vocabulary is the 7
  -- lowercase values. Pre-v4 UPPERCASE values remain accepted by the CHECK
  -- for backward compat but are retired: all rows were backfilled
  -- (QUEUED->queued, RECON_CANDIDATE->candidate, DONE->implemented,
  -- UNTRIAGED->queued/implemented by workflow status). New rows must use
  -- the lowercase set. Legacy map: queued=QUEUED, candidate=RECON_CANDIDATE,
  -- analyzing=ASSIGNED, understood/implemented/replacement-tested/
  -- runtime-validated=DONE (collapsed).
  triage_status TEXT NOT NULL DEFAULT 'candidate'
      CHECK (triage_status IN ('candidate','queued','analyzing','understood',
          'implemented','replacement-tested','runtime-validated',
          'UNTRIAGED','QUEUED','PRIORITIZED','RECON_CANDIDATE','ASSIGNED',
          'DONE','DROPPED','SUPERSEDED'))
);

CREATE INDEX IF NOT EXISTS idx_node_label    ON node(label);
CREATE INDEX IF NOT EXISTS idx_edge_src      ON edge(src);
CREATE INDEX IF NOT EXISTS idx_edge_dst      ON edge(dst);
CREATE INDEX IF NOT EXISTS idx_node_name     ON node(name);
CREATE INDEX IF NOT EXISTS idx_node_evidence ON node(evidence_level);
CREATE INDEX IF NOT EXISTS idx_inv_status    ON investigations(status, stage);
CREATE UNIQUE INDEX IF NOT EXISTS ix_inv_dedup ON investigations(kind, va, binary_sha256);
CREATE INDEX IF NOT EXISTS idx_field_struct  ON field(struct_id);
CREATE INDEX IF NOT EXISTS idx_trace_run_sha ON trace_run(binary_sha256);

CREATE TABLE IF NOT EXISTS triage (
    va          TEXT PRIMARY KEY,   -- canonical VA8: 8-char lowercase hex, no prefix
    rva         TEXT NOT NULL,      -- derived: va - 0x400000 (ImageBase); never a key
    ghidra_name TEXT NOT NULL,
    norm_name   TEXT NOT NULL,      -- ghidra_name minus leading 'thunk_' prefix
    subsystem   TEXT NOT NULL,
    category    TEXT NOT NULL
        CHECK (category IN ('ENGINE_INTERFACE','ENGINE_IMPLEMENTATION',
            'GAMEPLAY_SUPPORT','GAMEPLAY_LOGIC','THIRD_PARTY_OR_RUNTIME',
            'UNKNOWN')),
    priority    TEXT NOT NULL CHECK (priority IN ('P0','P1','P2','P3','IGNORE')),
    evidence    TEXT NOT NULL DEFAULT 'UNKNOWN'
        CHECK (evidence IN ('UNKNOWN','APPROXIMATION','INFERRED',
            'SUPPORTED','OBSERVED','CONFIRMED','VERIFIED')),
    sdk_name    TEXT,               -- community SDK name, if any (else NULL)
    vtable_addrs TEXT NOT NULL DEFAULT '[]', -- JSON list of vt:<va8> holders
    struct_names TEXT NOT NULL DEFAULT '[]', -- JSON list, best-effort assoc
    caller_count INTEGER,           -- NULL until an xref export runs; the
    callee_count INTEGER,           -- xref export backfills 0 for scanned
                                    -- functions with no call-type edges
    decomp_path TEXT,               -- export-relative .c path, if decompiled
    recon_candidate INTEGER NOT NULL DEFAULT 0 CHECK (recon_candidate IN (0,1)),
    rationale   TEXT NOT NULL DEFAULT '',
    kg_node_id  TEXT NOT NULL,      -- 'fun:<va8>'
    snapshot_sha256 TEXT NOT NULL,
    classifier_version TEXT NOT NULL DEFAULT 'triage-v4',
    classified_at TEXT NOT NULL DEFAULT (datetime('now'))
);

CREATE INDEX IF NOT EXISTS idx_triage_prio_cat ON triage(priority, category);
CREATE INDEX IF NOT EXISTS idx_triage_sub_prio ON triage(subsystem, priority);
CREATE INDEX IF NOT EXISTS idx_inv_triage_status ON investigations(triage_status);

-- xref-export (tools/ghidra/ExportXrefs.java + tools/triage/export_xrefs.py):
-- one row per (caller, callee, callsite) triple. Callers are pinned VA8;
-- callees are pinned VA8, EXT:<lib>::<name> (external/import), or VT:<va8>
-- (known vtable base from vtables.json). Counts in triage.caller_count /
-- triage.callee_count cover CALL-type edges only (direct-call, thunk,
-- external, computed-call); data-ref / vtable-ref rows are kept here.
CREATE TABLE IF NOT EXISTS xref (
    caller_va       TEXT NOT NULL,  -- canonical VA8, pinned universe
    callee_va       TEXT NOT NULL,  -- VA8 | EXT:<lib>::<name> | VT:<va8>
    reference_type  TEXT NOT NULL
        CHECK (reference_type IN ('direct-call','thunk','external',
            'computed-call','vtable-ref','data-ref')),
    callsite_va     TEXT NOT NULL,  -- VA8 of the referencing instruction
    source          TEXT NOT NULL,  -- 'ghidra:SporeApp.exe'
    snapshot_sha256 TEXT NOT NULL,
    PRIMARY KEY (caller_va, callee_va, callsite_va)
);

CREATE INDEX IF NOT EXISTS idx_xref_caller ON xref(caller_va);
CREATE INDEX IF NOT EXISTS idx_xref_callee ON xref(callee_va);

PRAGMA user_version = 4;
