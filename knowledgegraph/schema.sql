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

CREATE INDEX IF NOT EXISTS idx_node_label ON node(label);
CREATE INDEX IF NOT EXISTS idx_edge_src   ON edge(src);
CREATE INDEX IF NOT EXISTS idx_edge_dst   ON edge(dst);
