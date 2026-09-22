// OpenSpore KG viewer — single-page read-only dashboard.
// Vanilla fetch + DOM only. Every displayed value comes from /api/*;
// nothing is hardcoded (no counts, no evidence-level names).

const PAGE_SIZE = 50;

const state = {
  tab: "all",        // "all" | "functions"
  page: 0,
  q: "",
  label: "",         // applies to the "all" tab
  total: 0,
};

// -- helpers ---------------------------------------------------------------

function el(tag, text, cls) {
  const n = document.createElement(tag);
  if (text !== undefined) n.textContent = text;
  if (cls) n.className = cls;
  return n;
}

async function getJSON(path) {
  const resp = await fetch(path, { credentials: "same-origin" });
  return resp.json();
}

function card(label, value, sub) {
  const c = el("div", null, "card");
  c.appendChild(el("div", String(value), "card-value"));
  c.appendChild(el("div", label, "card-label"));
  if (sub) c.appendChild(el("div", sub, "card-sub"));
  return c;
}

function h2(root, title) {
  root.replaceChildren();
  root.appendChild(el("h2", title));
  return root;
}

function subPanel(title, inner) {
  const s = el("section", null, "subpanel");
  s.appendChild(el("h3", title));
  if (inner) s.appendChild(inner);
  return s;
}

function thead(cols) {
  const tr = el("tr");
  for (const c of cols) tr.appendChild(el("th", c));
  const t = el("thead");
  t.appendChild(tr);
  return t;
}

function bar(pct, zero) {
  const td = el("td", null, "barcell");
  const b = el("div", null, "bar" + (zero ? " zero" : ""));
  b.style.width = Math.max(0, Math.min(100, Math.round(pct))) + "%";
  td.appendChild(b);
  return td;
}

function kvTable(rows) {
  const t = el("table", null, "kv");
  for (const [k, v] of rows) {
    const tr = el("tr");
    tr.appendChild(el("td", k));
    tr.appendChild(el("td",
      v === null || v === undefined || v === "" ? "—" : String(v)));
    t.appendChild(tr);
  }
  return t;
}

// -- header + summary --------------------------------------------------------

async function initHeaderAndSummary() {
  const s = await getJSON("/api/summary");
  const pathEl = document.getElementById("db-path");
  const stateEl = document.getElementById("db-state");
  const banner = document.getElementById("degraded-banner");
  const root = document.getElementById("summary");
  if (s.status === "ok") {
    pathEl.textContent = s.db_path || "";
    stateEl.textContent = "ok — schema v" + s.user_version;
    h2(root, "Project summary");
    const grid = el("div", null, "cards");
    const names = { node: "nodes", edge: "edges", test_result: "tests",
                    investigations: "investigations", field: "fields",
                    trace_run: "trace runs" };
    for (const [k, v] of Object.entries(s.counts))
      grid.appendChild(card(names[k] || k, v));
    grid.appendChild(card("distinct builds", s.distinct_builds));
    root.appendChild(grid);
    return true;
  }
  const p = s.probe || {};
  pathEl.textContent = p.db_path || "";
  banner.hidden = false;
  banner.textContent = (s.message || "knowledge graph unavailable") +
    " — the DB is not present (fresh clone?): seed knowledgegraph/spore.db " +
    "and restart the viewer.";
  h2(root, "Project summary");
  root.appendChild(el("div", "degraded — no data", "muted"));
  return false;
}

// -- evidence ----------------------------------------------------------------

async function initEvidence() {
  const ev = await getJSON("/api/evidence");
  const sec = document.getElementById("evidence");
  h2(sec, "Evidence levels");
  if (ev.status !== "ok") {
    sec.appendChild(el("div", ev.message || "unavailable", "muted"));
    return;
  }
  const levels = Object.keys(ev.dist);
  const max = Math.max(1, ...levels.map((l) => ev.dist[l]));
  const t = el("table", null, "evid");
  t.appendChild(thead(["level", "nodes", "share", ""]));
  const tb = el("tbody");
  for (const l of levels) {
    const n = ev.dist[l];
    const tr = el("tr");
    tr.appendChild(el("td", l, "lvl " + String(l).toLowerCase()));
    tr.appendChild(el("td", String(n), "num" + (n ? "" : " zero")));
    tr.appendChild(el("td",
      ev.total ? (100 * n / ev.total).toFixed(1) + "%" : "0.0%", "num"));
    tr.appendChild(bar(100 * n / max, !n));
    tb.appendChild(tr);
  }
  t.appendChild(tb);
  sec.appendChild(t);
  const off = ev.off_scale || {};
  for (const [l, n] of Object.entries(off))
    sec.appendChild(el("div", "off-scale: " + l + " = " + n, "muted"));
}

// -- investigation status ------------------------------------------------------

async function initInvestigationStatus() {
  const iv = await getJSON("/api/investigations");
  const sec = document.getElementById("inv-status");
  h2(sec, "Investigation status");
  if (iv.status !== "ok") {
    sec.appendChild(el("div", iv.message || "unavailable", "muted"));
    return;
  }
  const mk = (title, dist) => {
    const box = el("div");
    const t = el("table");
    t.appendChild(thead(["state", "count"]));
    const tb = el("tbody");
    let total = 0;
    for (const [k, v] of Object.entries(dist)) {
      total += v;
      const tr = el("tr");
      tr.appendChild(el("td", k, "st-" + String(k).toLowerCase()));
      tr.appendChild(el("td", String(v), "num" + (v ? "" : " zero")));
      tb.appendChild(tr);
    }
    t.appendChild(tb);
    box.appendChild(t);
    box.appendChild(el("div", "total " + total, "muted"));
    return subPanel(title, box);
  };
  const duo = el("div", null, "duo");
  duo.appendChild(mk("status", iv.status_counts || {}));
  duo.appendChild(mk("stage", iv.stage_counts || {}));
  sec.appendChild(duo);
}

// -- subsystems -----------------------------------------------------------------

async function initSubsystems() {
  const ss = await getJSON("/api/subsystems");
  const sec = document.getElementById("subsystems");
  h2(sec, "Subsystems");
  if (ss.status !== "ok") {
    sec.appendChild(el("div", ss.message || "unavailable", "muted"));
    return;
  }
  if (!ss.subsystems.length) {
    sec.appendChild(el("div", "none recorded", "muted"));
    return;
  }
  const wrap = el("div", null, "tblwrap");
  const t = el("table");
  t.appendChild(thead(["subsystem", "evidence", "investigations", "by status"]));
  const tb = el("tbody");
  for (const s of ss.subsystems) {
    const tr = el("tr");
    tr.appendChild(el("td", s.name, "name"));
    tr.appendChild(el("td", s.evidence_level,
      "lvl " + String(s.evidence_level).toLowerCase()));
    tr.appendChild(el("td", String(s.investigations), "num"));
    tr.appendChild(el("td",
      Object.entries(s.investigations_by_status || {})
        .map(([st, n]) => st + " " + n).join("  "), "muted"));
    tr.addEventListener("click", () => showDetail(s.name));
    tb.appendChild(tr);
  }
  t.appendChild(tb);
  wrap.appendChild(t);
  sec.appendChild(wrap);
}

// -- node inventory ---------------------------------------------------------------

function fillLabelOptions(dist) {
  const sel = document.querySelector("#node-search select");
  for (const label of Object.keys(dist)) {
    sel.appendChild(el("option", label + " (" + dist[label] + ")"));
  }
}

// Server-side join: one bounded query for THIS page's keys only.
async function pageInvestigationMap(nodes) {
  const keys = new Set();
  for (const n of nodes) for (const k of vaKeys(n)) keys.add(k);
  if (!keys.size) return {};
  const p = new URLSearchParams();
  p.set("keys", [...keys].join(","));
  const r = await getJSON("/api/investigation-list?" + p.toString());
  const map = {};
  if (r.status !== "ok") return map;
  for (const iv of r.investigations) {
    for (const raw of [iv.va, iv.name]) {
      const key = String(raw || "").replace(/^0x/i, "").toLowerCase();
      if (key) (map[key] = map[key] || []).push(iv);
    }
  }
  return map;
}

function vaKeys(n) {
  const keys = new Set();
  const name = String(n.name || "");
  if (name) keys.add(name.toLowerCase());
  if (name.startsWith("fun:")) keys.add(name.slice(4).toLowerCase());
  const attrs = n.attrs || {};
  for (const k of ["address", "rva"]) {
    const v = attrs[k];
    if (typeof v === "string")
      keys.add(v.replace(/^0x/i, "").toLowerCase());
  }
  return [...keys];
}

function invStateCell(n, invMap) {
  const hits = [];
  for (const k of vaKeys(n)) {
    const ivs = (invMap || {})[k];
    if (ivs) hits.push(...ivs);
  }
  if (!hits.length) return el("td", "—", "num zero");
  const by = {};
  for (const iv of hits) by[iv.status] = (by[iv.status] || 0) + 1;
  const text = hits.length + "× (" +
    Object.entries(by)
      .map(([s, c]) => s + (c > 1 ? "×" + c : "")).join(", ") + ")";
  const blocked = hits.some((i) => i.status === "blocked");
  return el("td", text, "num" + (blocked ? " st-blocked" : ""));
}

function nodesUrl() {
  const p = new URLSearchParams();
  if (state.tab === "functions") p.set("label", "Function");
  else if (state.label) p.set("label", state.label);
  if (state.q) p.set("q", state.q);
  p.set("limit", String(PAGE_SIZE));
  p.set("offset", String(state.page * PAGE_SIZE));
  return "/api/nodes?" + p.toString();
}

function renderPager(r) {
  const pages = Math.max(1, Math.ceil(r.total / PAGE_SIZE));
  const cur = Math.floor(r.offset / PAGE_SIZE) + 1;
  const bar = el("div", null, "pager");
  const prev = el("button", "← prev", "pagerbtn");
  const next = el("button", "next →", "pagerbtn");
  prev.disabled = r.offset === 0;
  next.disabled = r.offset + r.nodes.length >= r.total;
  prev.addEventListener("click", () => {
    state.page = Math.max(0, state.page - 1);
    loadNodes();
  });
  next.addEventListener("click", () => {
    state.page += 1;
    loadNodes();
  });
  bar.appendChild(prev);
  bar.appendChild(el("span",
    "page " + cur + " / " + pages + " — " + r.total + " rows", "muted"));
  bar.appendChild(next);
  return bar;
}

async function loadNodes() {
  const box = document.getElementById("node-results");
  box.replaceChildren(el("div", "loading…", "muted"));
  const r = await getJSON(nodesUrl());
  box.replaceChildren();
  if (r.status !== "ok") {
    box.appendChild(el("div", r.message || "query failed", "muted"));
    return;
  }
  state.total = r.total;
  const isFn = state.tab === "functions";
  const invMap = isFn ? await pageInvestigationMap(r.nodes) : {};
  const wrap = el("div", null, "tblwrap");
  const t = el("table");
  t.appendChild(thead(isFn
    ? ["name", "addr", "evidence", "provenance", "investigation"]
    : ["label", "name", "evidence", "origin", "confidence", "updated_at"]));
  const tb = el("tbody");
  for (const n of r.nodes) {
    const tr = el("tr");
    if (isFn) {
      const attrs = n.attrs || {};
      const addr = attrs.address || attrs.rva || "—";
      const prov = attrs.sdk_name
        || (attrs.src && "dossier:" + attrs.src)
        || (attrs.trace && "trace:" + attrs.trace)
        || n.origin;
      tr.appendChild(el("td", n.name, "name"));
      tr.appendChild(el("td", addr, "addr"));
      tr.appendChild(el("td", n.evidence_level,
        "lvl " + String(n.evidence_level).toLowerCase()));
      tr.appendChild(el("td", prov, "muted"));
      tr.appendChild(invStateCell(n, invMap));
    } else {
      tr.appendChild(el("td", n.label, "muted"));
      tr.appendChild(el("td", n.name, "name"));
      tr.appendChild(el("td", n.evidence_level,
        "lvl " + String(n.evidence_level).toLowerCase()));
      tr.appendChild(el("td", n.origin, "muted"));
      tr.appendChild(el("td", Number(n.confidence).toFixed(2), "num"));
      tr.appendChild(el("td", n.updated_at, "muted"));
    }
    const ref = n.id;
    tr.addEventListener("click", () => showDetail(ref));
    tb.appendChild(tr);
  }
  t.appendChild(tb);
  wrap.appendChild(t);
  box.appendChild(wrap);
  box.appendChild(renderPager(r));
}

// -- detail view -------------------------------------------------------------------

async function showInvestigation(id) {
  const r = await getJSON("/api/investigation/" + encodeURIComponent(id));
  if (r.status !== "ok") return;
  const iv = r.investigation;
  const fmt = (v) => (v && typeof v === "object") ? JSON.stringify(v) : v;
  const box = el("div");
  box.appendChild(kvTable([
    ["why_interesting", iv.why_interesting],
    ["mode", iv.mode],
    ["subsystem", iv.subsystem],
    ["prerequisites", fmt(iv.prerequisites)],
    ["attempts", fmt(iv.attempts)],
    ["checkpoint", fmt(iv.checkpoint)],
    ["evidence_refs", fmt(iv.evidence_refs)],
  ]));
  const head = el("div", "investigation " + id, "muted");
  const sec = el("div", null, "inv-detail");
  sec.appendChild(head);
  sec.appendChild(box);
  document.getElementById("detail").appendChild(sec);
}

async function showDetail(ref) {
  const root = document.getElementById("detail");
  root.hidden = false;
  root.replaceChildren(el("h2", "Node detail"), el("div", "loading…", "muted"));
  const enc = encodeURIComponent(String(ref));
  const [det, nb] = await Promise.all([
    getJSON("/api/node/" + enc),
    getJSON("/api/node/" + enc + "/neighbors?depth=1"),
  ]);
  root.replaceChildren(el("h2", "Node detail"));
  if (det.status !== "ok") {
    root.appendChild(el("div", det.message || "not found", "muted"));
    return;
  }
  const n = det.node;
  const attrs = n.attrs || {};
  const prov = det.provenance || {};

  root.appendChild(subPanel("Identity", kvTable([
    ["id", n.id],
    ["label", n.label],
    ["name", n.name],
    ["evidence", n.evidence_level],
    ["confidence", Number(n.confidence).toFixed(2)],
    ["origin", n.origin],
    ["created_at", n.created_at],
    ["updated_at", n.updated_at],
    ["note", n.note],
  ])));

  const evLines = Array.isArray(attrs.events) ? attrs.events : null;
  root.appendChild(subPanel("Provenance / binary identity", kvTable([
    ["origin", n.origin],
    ["binary_sha256", n.binary_sha256],
    ["address", prov.address],
    ["rva", prov.rva],
    ["sdk_name", prov.sdk_name],
    ["events", evLines
      ? String(evLines.length) +
        (evLines[0] ? " — first: " + evLines[0] : "")
      : null],
    ["trace", attrs.trace],
    ["dossier ref (display only)", attrs.src || prov.dossier],
  ])));

  if (det.fields && det.fields.length) {
    const t = el("table");
    t.appendChild(thead(["offset", "role", "offset ev", "meaning ev",
                         "value", "source"]));
    const tb = el("tbody");
    for (const f of det.fields) {
      const tr = el("tr");
      tr.appendChild(el("td", f.offset, "addr"));
      tr.appendChild(el("td", f.role, "name"));
      tr.appendChild(el("td", f.offset_evidence,
        "lvl " + String(f.offset_evidence).toLowerCase()));
      tr.appendChild(el("td", f.meaning_evidence,
        "lvl " + String(f.meaning_evidence).toLowerCase()));
      tr.appendChild(el("td", f.value || "—", "muted"));
      tr.appendChild(el("td", f.source || "—", "muted"));
      tb.appendChild(tr);
    }
    t.appendChild(tb);
    root.appendChild(subPanel("Fields", t));
  }

  if (nb.status === "ok") {
    const rels = {};
    for (const e of nb.edges) {
      if (e.src === n.id) (rels[e.dst] = rels[e.dst] || []).push(e.rel);
      if (e.dst === n.id) (rels[e.src] = rels[e.src] || []).push(e.rel);
    }
    const t = el("table");
    t.appendChild(thead(["rel", "label", "name", "evidence"]));
    const tb = el("tbody");
    for (const m of nb.nodes) {
      if (m.id === n.id) continue;
      const rs = rels[m.id] || [];
      for (let i = 0; i < Math.max(1, rs.length); i++) {
        const tr = el("tr");
        tr.appendChild(el("td", i === 0 ? rs.join(", ") : "", "muted"));
        tr.appendChild(el("td", m.label, "muted"));
        const nm = el("td", m.name, "name linkish");
        nm.addEventListener("click", (e) => {
          e.stopPropagation();
          showDetail(m.id);
        });
        tr.appendChild(nm);
        tr.appendChild(el("td", m.evidence_level,
          "lvl " + String(m.evidence_level).toLowerCase()));
        tr.addEventListener("click", () => showDetail(m.id));
        tb.appendChild(tr);
      }
    }
    t.appendChild(tb);
    root.appendChild(subPanel("Related nodes (depth 1)", t));
  }

  if (det.investigations && det.investigations.length) {
    const t = el("table");
    t.appendChild(thead(["id", "kind", "va", "stage", "status",
                         "block_reason", "updated_at"]));
    const tb = el("tbody");
    for (const iv of det.investigations) {
      const tr = el("tr");
      const idCell = el("td", iv.id, "name linkish");
      idCell.addEventListener("click", (e) => {
        e.stopPropagation();
        showInvestigation(iv.id);
      });
      tr.appendChild(idCell);
      tr.appendChild(el("td", iv.kind, "muted"));
      tr.appendChild(el("td", iv.va || "—", "addr"));
      tr.appendChild(el("td", iv.stage, "muted"));
      tr.appendChild(el("td", iv.status,
        "st-" + String(iv.status).toLowerCase()));
      tr.appendChild(el("td", iv.block_reason || "—", "muted"));
      tr.appendChild(el("td", iv.updated_at || "—", "muted"));
      tb.appendChild(tr);
    }
    t.appendChild(tb);
    root.appendChild(subPanel("Investigations", t));
  }

  root.scrollIntoView({ behavior: "smooth", block: "start" });
}

// -- init ---------------------------------------------------------------------------

async function init() {
  const ok = await initHeaderAndSummary();
  if (!ok) return;  // degraded: banner shown, nothing else to load
  await Promise.all([initEvidence(), initInvestigationStatus(),
                     initSubsystems()]);
  const lbl = await getJSON("/api/labels");
  if (lbl.status === "ok") fillLabelOptions(lbl.dist);

  const form = document.getElementById("node-search");
  form.addEventListener("submit", (e) => {
    e.preventDefault();
    const fd = new FormData(form);
    state.q = (fd.get("q") || "").trim();
    state.label = state.tab === "all" ? (fd.get("label") || "") : "";
    state.page = 0;
    loadNodes();
  });

  const tabs = {
    all: document.getElementById("tab-all"),
    functions: document.getElementById("tab-functions"),
  };
  for (const [key, btn] of Object.entries(tabs)) {
    btn.addEventListener("click", () => {
      state.tab = key;
      for (const [k, b] of Object.entries(tabs))
        b.classList.toggle("active", k === key);
      const sel = document.querySelector("#node-search select");
      sel.value = key === "functions" ? "Function" : state.label;
      state.page = 0;
      loadNodes();
    });
  }

  loadNodes();
}

document.addEventListener("DOMContentLoaded", init);
