"use strict";

const API = Object.freeze({
  summary: "/api/summary",
  evidence: "/api/evidence",
  readiness: "/api/readiness",
  nodes: "/api/nodes",
  subsystems: "/api/subsystems",
  node: (ref) => `/api/node/${encodeURIComponent(String(ref))}`,
  function: (ref, limit = 80) =>
    `/api/function/${encodeURIComponent(String(ref))}?limit=${limit}`,
  neighbors: (ref, depth = 1, limit = 140) =>
    `/api/node/${encodeURIComponent(String(ref))}/neighbors?depth=${depth}&limit=${limit}`,
  investigation: (id) => `/api/investigation/${encodeURIComponent(String(id))}`,
  search: "/api/search",
  architecture: "/api/architecture",
  packages: "/api/packages",
  types: "/api/types",
  functions: "/api/functions",
  states: "/api/states",
  events: "/api/events",
  simulator: "/api/simulator"
});

const VIEW_DEFINITIONS = Object.freeze({
  architecture: {
    title: "Architecture",
    endpoint: API.architecture,
    fallbackLabels: ["Subsystem"],
    parentParam: "root",
    rootDepth: 1,
    expandMode: "root",
    sort: "hotspots",
    description: "Subsystems and their reverse-engineering neighborhoods."
  },
  packages: {
    title: "Packages",
    endpoint: API.packages,
    fallbackLabels: ["Package"],
    expandMode: "neighbors",
    sort: "name",
    description: "Reconstruction packages and contained architecture."
  },
  types: {
    title: "Types",
    endpoint: API.types,
    fallbackLabels: ["Structure", "Class", "VTable"],
    expandMode: "aggregate",
    sort: "hotspots",
    description: "Semantic type facets and their reverse-engineering usage."
  },
  functions: {
    title: "Functions",
    endpoint: API.functions,
    fallbackLabels: ["Function"],
    expandMode: "neighbors",
    sort: "hotspots",
    description: "Function symbols ranked by reverse-engineering attention."
  },
  events: {
    title: "State / events",
    endpoint: API.events,
    stateEndpoint: API.states,
    fallbackLabels: [],
    parentQuery: "event",
    expandMode: "neighbors",
    sort: "evidence",
    description: "State transitions, messages, and event-bearing owners."
  }
});

const CANONICAL_EVIDENCE_LEVELS = Object.freeze([
  "UNKNOWN", "APPROXIMATION", "INFERRED", "SUPPORTED", "OBSERVED", "CONFIRMED", "VERIFIED"
]);
const ROOT_LIMIT = 64;
const CHILD_LIMIT = 48;
const SEARCH_LIMIT = 24;
const DETAIL_LIMIT = 80;
const MAX_GRAPH_NODES = 80;
const MAX_LOADED_NODES = 240;
const MAX_GRAPH_EDGES = 220;
const MAX_TRACE_NODES = 24;
const REQUEST_TIMEOUT_MS = 12000;
const SVG_WIDTH = 1000;
const SVG_HEIGHT = 680;

const state = {
  view: "architecture",
  viewEpoch: 0,
  viewState: "booting",
  nodes: new Map(),
  aliases: new Map(),
  edges: new Map(),
  rootIds: new Set(),
  expanded: new Set(),
  positions: new Map(),
  visibleNodes: [],
  selectedId: null,
  details: new Map(),
  investigation: null,
  summary: null,
  evidence: {},
  evidenceLevels: [...CANONICAL_EVIDENCE_LEVELS],
  readiness: [],
  readinessLevels: [],
  readinessAvailable: false,
  filter: { evidence: "all", readiness: "all", sort: "hotspots" },
  searchResults: [],
  searchCompatibility: false,
  graphFeedbackTimer: null,
  transform: { x: 0, y: 0, k: 1 },
  drag: null,
  detailLoading: false,
  detailToken: 0,
  simulator: {
    active: false,
    playing: false,
    origin: null,
    visited: [],
    trail: [],
    queue: [],
    timer: null,
    advancing: false
  }
};

const dom = {};

function cacheDom() {
  for (const id of [
    "db-line", "connection-dot", "connection-label", "system-banner",
    "global-search", "global-query", "view-state", "evidence-filter",
    "readiness-filter", "sort-filter", "search-results", "close-search-results",
    "search-meta", "search-result-list", "breadcrumbs", "scope-description",
    "node-list", "node-list-count", "graph-scope", "simulator-toggle",
    "zoom-out", "zoom-in", "fit-view", "focus-selection", "collapse-view",
    "metrics", "graph-shell", "graph-canvas", "graph-viewport", "edge-layer",
    "node-layer", "graph-feedback", "zoom-readout", "simulator-panel",
    "simulator-status", "simulator-play", "simulator-step", "simulator-reset",
    "simulator-trail", "clear-selection", "selection-content", "footer-status"
  ]) {
    dom[id] = document.getElementById(id);
  }
}

function el(tag, text, className) {
  const node = document.createElement(tag);
  if (text !== undefined && text !== null) node.textContent = String(text);
  if (className) node.className = className;
  return node;
}

function svgEl(tag, attributes = {}) {
  const node = document.createElementNS("http://www.w3.org/2000/svg", tag);
  for (const [key, value] of Object.entries(attributes)) {
    node.setAttribute(key, String(value));
  }
  return node;
}

class ApiError extends Error {
  constructor(message, status = 0, payload = null) {
    super(message);
    this.name = "ApiError";
    this.status = status;
    this.payload = payload;
  }
}

async function requestJSON(path, options = {}) {
  const controller = new AbortController();
  const timeout = window.setTimeout(() => controller.abort(), REQUEST_TIMEOUT_MS);
  let response;
  try {
    response = await fetch(path, {
      method: "GET",
      credentials: "same-origin",
      headers: { Accept: "application/json" },
      signal: options.signal || controller.signal
    });
  } catch (error) {
    if (error && error.name === "AbortError") {
      throw new ApiError(`Request timed out: ${path}`, 0);
    }
    throw new ApiError(`Network request failed: ${error.message}`, 0);
  } finally {
    window.clearTimeout(timeout);
  }
  let payload = null;
  try {
    payload = await response.json();
  } catch (_) {
    if (!response.ok) throw new ApiError(`HTTP ${response.status}: ${path}`, response.status);
    throw new ApiError(`Invalid JSON response: ${path}`, response.status);
  }
  if (!response.ok || payload.status === "error" || payload.status === "degraded") {
    throw new ApiError(payload.message || `HTTP ${response.status}: ${path}`, response.status, payload);
  }
  return payload;
}

function viewDefinition() {
  return VIEW_DEFINITIONS[state.view];
}

function canonicalEvidence(value) {
  if (value && typeof value === "object") value = value.level || value.name;
  const text = String(value || "UNKNOWN").trim().toUpperCase();
  return CANONICAL_EVIDENCE_LEVELS.includes(text) ? text : "UNKNOWN";
}

function evidenceIndex(value) {
  return CANONICAL_EVIDENCE_LEVELS.indexOf(canonicalEvidence(value));
}

function evidenceClass(level) {
  return `ev-${canonicalEvidence(level).toLowerCase()}`;
}

function readinessKey(value) {
  if (value && typeof value === "object") value = value.status || value.level || value.name;
  const text = String(value ?? "").trim();
  return text || "not reported";
}

function readinessClass(value) {
  return `readiness-${readinessKey(value).toLowerCase().replace(/[^a-z0-9]+/g, "-")}`;
}

function nodeReadiness(node) {
  return readinessKey(node.readiness ?? node.triage_status ??
    node.attrs?.readiness ?? node.attrs?.implementation_readiness);
}

function categoryFor(node) {
  const label = String(node.label || node.type || "").toLowerCase();
  const name = String(node.name || "").toLowerCase();
  const attrs = node.attrs || {};
  if (/event|state|transition|message/.test(label) || /event|transition/.test(name) ||
      Array.isArray(attrs.events) || attrs.event_value !== undefined ||
      attrs.state_event || attrs.state_machine) return "event";
  if (/package|subsystem/.test(label)) return label.includes("package") ? "package" : "architecture";
  if (/class|struct|type|vtable|implement/.test(label)) return "type";
  if (/function|method|thunk/.test(label)) return "function";
  if (/asset|format/.test(label)) return "asset";
  if (/test|contract|assert/.test(label)) return "test";
  if (/event|state|transition/.test(name)) return "event";
  return "other";
}

function categoryLabel(category) {
  return {
    architecture: "Architecture",
    package: "Package",
    type: "Type",
    function: "Function",
    event: "State / event",
    asset: "Asset",
    test: "Validation",
    other: "Node"
  }[category] || "Node";
}

function nodeParent(raw) {
  const attrs = raw.attrs || {};
  return raw.parent_id ?? raw.parentId ?? raw.parent ?? raw.package_id ?? raw.type_id ??
    raw.owner_id ?? attrs.parent_id ?? attrs.parentId ?? attrs.package_id ??
    attrs.type_id ?? attrs.owner_id ?? null;
}

function normalizeNode(raw, fallbackCategory = null) {
  if (!raw || typeof raw !== "object") return null;
  if (raw.node && typeof raw.node === "object") {
    const owner = raw.node;
    const eventId = raw.id || `event:${owner.id ?? owner.name}:${safeJSON(raw.value, 500)}`;
    raw = {
      ...owner,
      id: eventId,
      api_ref: String(owner.id ?? owner.name),
      event_record: true,
      event_value: raw.value,
      attrs: { ...(owner.attrs || {}), event_value_recorded: true, event_value: raw.value }
    };
  }
  const aggregate = Boolean(raw.aggregate || (raw.type && !raw.id && !raw.node_id && fallbackCategory === "type"));
  const typeValue = raw.type_value ?? raw.type_name ?? (aggregate ? raw.type : null);
  const label = String(raw.label || (aggregate ? "Type facet" : raw.type) || raw.category || fallbackCategory || "Node");
  const name = String(raw.name || raw.title || raw.symbol || typeValue || raw.id || raw.ref || "Unnamed node");
  const evidence = raw.evidence_level ?? raw.evidence ?? raw.evidenceLevel ??
    (raw.evidence && typeof raw.evidence === "object" ? raw.evidence.level : null);
  const attrs = raw.attrs || raw.attributes || {};
  const idValue = raw.id ?? raw.node_id ?? raw.ref ?? (aggregate ? `type:${typeValue}:${label}` : `${name}::${label}`);
  const id = String(idValue);
  const existing = state.nodes.get(id) || findNodeByApiRef(raw.id ?? raw.node_id ?? raw.ref ?? name);
  const mergedAttrs = { ...(existing?.attrs || {}), ...(attrs && typeof attrs === "object" ? attrs : {}) };
  if (raw.event_value !== undefined) mergedAttrs.event_value = raw.event_value;
  const node = {
    ...(existing || {}),
    id,
    api_ref: String(existing?.api_ref ?? (raw.api_ref ?? raw.id ?? raw.node_id ?? raw.ref ?? typeValue ?? name)),
    label,
    name,
    evidence_level: canonicalEvidence(existing?.evidence_level || evidence),
    confidence: numberOr(existing?.confidence, numberOr(raw.confidence, 0)),
    origin: existing?.origin ?? raw.origin ?? raw.source ?? null,
    updated_at: existing?.updated_at || raw.updated_at || null,
    binary_sha256: existing?.binary_sha256 || raw.binary_sha256 || attrs.binary_sha256 || null,
    readiness: existing?.readiness ?? raw.readiness ?? raw.triage_status ??
      attrs.readiness ?? attrs.implementation_readiness ?? null,
    state: existing?.state || raw.state || attrs.state || null,
    address: existing?.address || raw.address || mergedAttrs.address || mergedAttrs.rva || null,
    rva: existing?.rva || raw.rva || mergedAttrs.rva || null,
    va: existing?.va || raw.va || attrs.va || raw.address || attrs.address || null,
    subsystem: existing?.subsystem || raw.subsystem || attrs.subsystem || null,
    package: existing?.package || raw.package || attrs.package || attrs.package_ids || null,
    priority: existing?.priority || raw.priority || attrs.priority || null,
    semantic_status: existing?.semantic_status || raw.semantic_status || attrs.semantic_status || null,
    related_structures: existing?.related_structures || raw.related_structures ||
      attrs.related_structures || attrs.struct_names || attrs.structure_name || null,
    state_transitions: existing?.state_transitions || raw.state_transitions ||
      attrs.state_transitions || attrs.state_machine || null,
    engine_boundary: existing?.engine_boundary || raw.engine_boundary ||
      attrs.engine_boundary || attrs.boundary || null,
    unresolved_questions: existing?.unresolved_questions || raw.unresolved_questions ||
      attrs.unresolved_questions || attrs.unresolved || null,
    parent_id: nodeParent(raw) ?? existing?.parent_id ?? null,
    child_count: Math.max(numberOr(existing?.child_count, 0), numberOr(raw.child_count, 0), numberOr(raw.children_count, 0)),
    has_children: raw.has_children ?? existing?.has_children ?? null,
    count: Math.max(numberOr(existing?.count, 0), numberOr(raw.count, 0)),
    type_value: existing?.type_value || typeValue || null,
    facet_value: existing?.facet_value ?? raw.value ?? null,
    event_value: existing?.event_value ?? raw.event_value ?? null,
    event_record: existing?.event_record || raw.event_record || false,
    aggregate,
    attrs: mergedAttrs,
    raw: { ...(existing?.raw || {}), ...raw },
    fields: existing?.fields || raw.fields || [],
    investigations: existing?.investigations || raw.investigations || [],
    provenance: existing?.provenance || raw.provenance || null
  };
  node.category = categoryFor(node);
  if (node.category === "other" && fallbackCategory && fallbackCategory !== "other") node.category = fallbackCategory;
  return node;
}

function normalizeEdge(raw) {
  if (!raw || typeof raw !== "object") return null;
  const src = raw.src ?? raw.source ?? raw.from;
  const dst = raw.dst ?? raw.target ?? raw.to;
  if (src === undefined || dst === undefined) return null;
  const srcId = resolveNodeReference(src)?.id || String(src);
  const dstId = resolveNodeReference(dst)?.id || String(dst);
  const rel = String(raw.rel || raw.relation || raw.type || "related");
  return {
    id: String(raw.id ?? `${srcId}|${dstId}|${rel}`),
    src: srcId,
    dst: dstId,
    rel,
    evidence_level: canonicalEvidence(raw.evidence_level || raw.evidence),
    raw
  };
}

function firstCollection(payload, keys) {
  if (Array.isArray(payload)) return payload;
  for (const key of keys) {
    if (Array.isArray(payload?.[key])) return payload[key];
    if (Array.isArray(payload?.data?.[key])) return payload.data[key];
  }
  if (Array.isArray(payload?.data)) return payload.data;
  if (Array.isArray(payload?.graph?.nodes)) return payload.graph.nodes;
  return [];
}

function firstEdgeCollection(payload) {
  for (const candidate of [payload, payload?.graph, payload?.data]) {
    for (const key of ["edges", "relationships", "links"]) {
      if (Array.isArray(candidate?.[key])) return candidate[key];
    }
  }
  return [];
}

function findNodeByApiRef(ref) {
  if (ref === undefined || ref === null) return null;
  const key = String(ref);
  return state.aliases.get(key) || state.nodes.get(key) || null;
}

function resolveNodeReference(ref) {
  if (ref && typeof ref === "object") return ref.label || ref.name ? normalizeNode(ref) : null;
  const direct = findNodeByApiRef(ref);
  if (direct) return direct;
  const list = [...state.nodes.values()];
  return list.find((node) => node.name === String(ref)) || null;
}

function mergePayload(payload, options = {}) {
  const graph = payload?.graph && typeof payload.graph === "object" ? payload.graph : payload || {};
  let rawNodes = firstCollection(graph, ["nodes", "items", "results", "children", "subsystems", "packages", "types", "functions", "events", "states", "state_events", "hierarchy"]);
  const rootCandidates = [payload?.node, payload?.root, graph?.root, payload?.data?.root]
    .filter((item) => item && typeof item === "object");
  for (const root of rootCandidates) {
    if (!rawNodes.some((item) => String(item?.id ?? item?.node_id ?? item?.ref ?? "") === String(root.id ?? root.node_id ?? root.ref ?? root.name ?? ""))) {
      rawNodes = [root, ...rawNodes];
    }
  }
  if (options.parentId && !rawNodes.some((item) => item?.parent_id || item?.parentId)) {
    rawNodes = rawNodes.map((item) => ({ ...item, parent_id: options.parentId }));
  }
  rawNodes = rawNodes.slice(0, MAX_LOADED_NODES);
  const fallbackCategory = categoryFor({ label: viewDefinition().title });
  const added = [];
  for (const raw of rawNodes) {
    const lookup = raw.id ?? raw.node_id ?? raw.ref ?? raw.name;
    const wasKnown = Boolean(findNodeByApiRef(lookup));
    if (!wasKnown && state.nodes.size >= MAX_LOADED_NODES) break;
    const node = normalizeNode(raw, fallbackCategory);
    if (!node) continue;
    state.nodes.set(node.id, node);
    state.aliases.set(node.id, node);
    state.aliases.set(node.api_ref, node);
    state.aliases.set(node.name, node);
    added.push(node.id);
  }
  const edges = firstEdgeCollection(payload).concat(firstEdgeCollection(graph));
  const seenEdges = new Set();
  for (const raw of edges) {
    const edge = normalizeEdge(raw);
    if (!edge || seenEdges.has(edge.id) || state.edges.size >= MAX_GRAPH_EDGES) continue;
    seenEdges.add(edge.id);
    state.edges.set(edge.id, edge);
  }
  return { added: [...new Set(added)], count: added.length };
}

function stateChildren(parentId) {
  return [...state.nodes.values()].filter((node) => String(node.parent_id) === String(parentId));
}

function nodeDegree(node) {
  let count = numberOr(node.raw?.degree ?? node.raw?.edge_degree ?? node.raw?.degree_in + node.raw?.degree_out, 0);
  if (count) return count;
  for (const edge of state.edges.values()) {
    if (edge.src === node.id || edge.dst === node.id) count += 1;
  }
  return count;
}

function nodeDirectionCounts(node) {
  let inbound = 0;
  let outbound = 0;
  for (const edge of state.edges.values()) {
    if (edge.dst === node.id) inbound += 1;
    if (edge.src === node.id) outbound += 1;
  }
  return { inbound, outbound };
}

function canExpand(node) {
  if (!node) return false;
  return node.has_children === true || numberOr(node.child_count, 0) > 0 || stateChildren(node.id).length > 0;
}

function belongsToView(node) {
  const category = categoryFor(node);
  if (state.view === "architecture") return ["architecture", "package", "type", "function", "event"].includes(category);
  if (state.view === "packages") return category === "package";
  if (state.view === "types") return category === "type";
  if (state.view === "functions") return category === "function";
  if (state.view === "events") return category === "event";
  return true;
}

function hotspotScore(node) {
  const details = state.details.get(node.id);
  const degree = nodeDegree(node);
  const eventCount = Array.isArray(node.attrs?.events) ? node.attrs.events.length : 0;
  const fieldCount = numberOr(node.fields?.length, numberOr(node.raw?.field_count, 0));
  const investigationCount = numberOr(details?.investigations?.length, numberOr(node.investigations?.length, 0));
  const weak = Math.max(0, 6 - evidenceIndex(node.evidence_level)) * 2;
  return degree * 4 + eventCount * 3 + fieldCount + investigationCount * 5 +
    numberOr(node.confidence, 0) * 2 + weak;
}

function matchesFilters(node) {
  if (state.filter.readiness !== "all" &&
      nodeReadiness(node).toLowerCase() !== state.filter.readiness.toLowerCase()) return false;
  if (state.filter.evidence !== "all" &&
      evidenceIndex(node.evidence_level) < evidenceIndex(state.filter.evidence)) return false;
  return true;
}

function sortedNodes(nodes) {
  const sort = state.filter.sort;
  return [...nodes].sort((a, b) => {
    if (a.id === state.selectedId) return -1;
    if (b.id === state.selectedId) return 1;
    if (sort === "name") return a.name.localeCompare(b.name, undefined, { numeric: true });
    if (sort === "evidence") return evidenceIndex(b.evidence_level) - evidenceIndex(a.evidence_level) || a.name.localeCompare(b.name);
    if (sort === "degree") return nodeDegree(b) - nodeDegree(a) || a.name.localeCompare(b.name);
    if (sort === "confidence") return numberOr(b.confidence, 0) - numberOr(a.confidence, 0) || a.name.localeCompare(b.name);
    return hotspotScore(b) - hotspotScore(a) || a.name.localeCompare(b.name);
  });
}

function visibleNodes() {
  const filtered = [...state.nodes.values()].filter((node) => belongsToView(node) && matchesFilters(node));
  const sorted = sortedNodes(filtered);
  const selected = state.selectedId ? state.nodes.get(state.selectedId) : null;
  if (selected && matchesFilters(selected) && !sorted.some((node) => node.id === selected.id)) sorted.unshift(selected);
  return sorted.slice(0, MAX_GRAPH_NODES);
}

function numberOr(value, fallback = 0) {
  const parsed = Number(value);
  return Number.isFinite(parsed) ? parsed : fallback;
}

function displayValue(value) {
  if (value === null || value === undefined || value === "") return "—";
  if (Array.isArray(value)) return value.length ? value.join(", ") : "none";
  if (typeof value === "object") return safeJSON(value);
  return String(value);
}

function safeJSON(value, maxLength = 12000) {
  let text;
  try {
    text = JSON.stringify(value, null, 2);
  } catch (_) {
    text = String(value);
  }
  if (text && text.length > maxLength) return `${text.slice(0, maxLength)}\n… truncated in UI`;
  return text || "—";
}

function setConnection(status, label, path) {
  dom["connection-dot"].className = `connection-dot ${status}`;
  dom["connection-label"].textContent = label;
  dom["db-line"].textContent = path || dom["db-line"].textContent;
}

function setSystemBanner(message) {
  dom["system-banner"].hidden = !message;
  dom["system-banner"].textContent = message || "";
}

function setViewState(status, label) {
  state.viewState = status;
  dom["view-state"].className = `state-pill ${status}`;
  dom["view-state"].textContent = label;
}

function showFeedback(message, error = false, sticky = false) {
  if (state.graphFeedbackTimer) window.clearTimeout(state.graphFeedbackTimer);
  dom["graph-feedback"].textContent = message;
  dom["graph-feedback"].className = `graph-feedback${error ? " error" : ""}`;
  dom["graph-feedback"].hidden = false;
  if (!sticky) {
    state.graphFeedbackTimer = window.setTimeout(() => {
      dom["graph-feedback"].hidden = true;
    }, 2200);
  }
}

function hideFeedback() {
  if (state.graphFeedbackTimer) window.clearTimeout(state.graphFeedbackTimer);
  dom["graph-feedback"].hidden = true;
}

function setFormBusy(form, busy) {
  for (const control of form.elements) control.disabled = busy;
}

function buildQuery(params) {
  const query = new URLSearchParams();
  for (const [key, value] of Object.entries(params)) {
    if (value === undefined || value === null || value === "") continue;
    query.set(key, String(value));
  }
  return query;
}

function viewParams(definition, parentId, limit, offset = 0) {
  const params = { ...(definition.rootParams || {}), limit, offset };
  if (parentId && definition.parentParam) params[definition.parentParam] = parentId;
  else if (definition.parentQuery) params.q = definition.parentQuery;
  if (definition.rootDepth) params.depth = parentId ? 1 : definition.rootDepth;
  if (state.view === "functions" && state.filter.readiness !== "all") {
    params.readiness = state.filter.readiness;
  }
  return params;
}

async function loadCurrentLabels(labels, limitPerLabel = 40) {
  const responses = await Promise.all(labels.map((label) => requestJSON(
    `${API.nodes}?${buildQuery({ label, limit: limitPerLabel, offset: 0 })}`
  )));
  return {
    status: "ok",
    nodes: responses.flatMap((response) => response.nodes || []),
    fallback: true
  };
}

async function loadStateEventPayload(limit, offset = 0) {
  const perRoute = Math.max(1, Math.ceil(limit / 2));
  const results = await Promise.allSettled([
    requestJSON(`${API.states}?${buildQuery({ limit: perRoute, offset })}`),
    requestJSON(`${API.events}?${buildQuery({ limit: perRoute, offset })}`)
  ]);
  const fulfilled = results.filter((result) => result.status === "fulfilled");
  if (!fulfilled.length) throw results[0].reason;
  const states = results[0].status === "fulfilled"
    ? firstCollection(results[0].value, ["states", "items", "nodes"])
    : [];
  const events = results[1].status === "fulfilled"
    ? firstCollection(results[1].value, ["events", "items", "nodes"])
    : [];
  return {
    status: "ok",
    nodes: [...states, ...events].slice(0, limit),
    states,
    events
  };
}

async function requestViewPayload(definition, limit, offset = 0) {
  if (definition.stateEndpoint) return loadStateEventPayload(limit, offset);
  return requestJSON(`${definition.endpoint}?${buildQuery(viewParams(definition, null, limit, offset))}`);
}

async function fallbackViewPayload(definition) {
  if (state.view === "architecture") return requestJSON(API.subsystems);
  if (state.view === "functions") {
    return requestJSON(`${API.nodes}?${buildQuery({
      label: "Function",
      readiness: state.filter.readiness !== "all" ? state.filter.readiness : null,
      limit: ROOT_LIMIT,
      offset: 0
    })}`);
  }
  if (definition.fallbackLabels.length) {
    const perLabel = Math.max(16, Math.floor(ROOT_LIMIT / definition.fallbackLabels.length));
    return loadCurrentLabels(definition.fallbackLabels, perLabel);
  }
  if (definition.parentQuery) {
    return requestJSON(`${API.nodes}?${buildQuery({
      q: definition.parentQuery,
      readiness: state.filter.readiness !== "all" && state.view === "functions" ? state.filter.readiness : null,
      limit: ROOT_LIMIT,
      offset: 0
    })}`);
  }
  return { status: "ok", nodes: [] };
}

function isMissingRoute(error) {
  return error instanceof ApiError && [404, 405, 501].includes(error.status);
}

async function loadViewRoot() {
  const epoch = state.viewEpoch;
  const definition = viewDefinition();
  setViewState("loading", "loading");
  showFeedback(`Loading a bounded ${definition.title.toLowerCase()} slice…`);
  let payload;
  try {
    payload = await requestViewPayload(definition, ROOT_LIMIT);
  } catch (error) {
    if (!isMissingRoute(error)) throw error;
    payload = await fallbackViewPayload(definition);
    dom["footer-status"].textContent = `API adapter: ${definition.title} compatibility route / bounded slice`;
  }
  if (epoch !== state.viewEpoch) return;
  const merged = mergePayload(payload);
  if (!merged.count) {
    for (const node of state.nodes.values()) delete node.parent_id;
  }
  const explicitRootId = payload.root?.id || payload.node?.id || payload.graph?.root?.id;
  const roots = explicitRootId
    ? [String(explicitRootId)]
    : [...state.nodes.values()].filter((node) => !node.parent_id).map((node) => node.id);
  state.rootIds = new Set(roots.length ? roots : [...state.nodes.keys()].slice(0, ROOT_LIMIT));
  for (const node of state.nodes.values()) {
    if (stateChildren(node.id).length) state.expanded.add(node.id);
  }
  state.viewState = "ready";
  setViewState("ready", `${state.nodes.size} loaded`);
  hideFeedback();
  renderAll();
  requestAnimationFrame(() => fitGraph(false));
}

async function fetchNeighborPayload(node) {
  const payload = await requestJSON(API.neighbors(node.api_ref || node.id, 1, MAX_GRAPH_NODES * 2));
  const matching = (payload.nodes || []).filter((item) => belongsToView(normalizeNode(item)));
  return { ...payload, nodes: matching.length ? matching : payload.nodes || [] };
}

function holderMatchesType(holder, typeValue) {
  const needle = String(typeValue || "").toLowerCase();
  if (!needle) return false;
  const attrs = holder.attrs || {};
  return [attrs.type, attrs.value_type, attrs.type_semantics]
    .some((value) => String(typeof value === "object" ? safeJSON(value, 1000) : value || "").toLowerCase().includes(needle));
}

async function expandAggregate(node) {
  showFeedback(`Finding bounded holders of ${node.name}…`);
  try {
    const payload = await requestJSON(`${API.search}?${buildQuery({ q: node.type_value || node.name, limit: SEARCH_LIMIT })}`);
    const holders = firstCollection(payload, ["results", "nodes", "items", "matches"])
      .map((raw) => normalizeNode(raw))
      .filter((holder) => holder && !holder.aggregate && holderMatchesType(holder, node.type_value));
    if (!holders.length) {
      showFeedback(`No bounded holders found for ${node.name}`);
      return false;
    }
    const merged = mergePayload({ status: "ok", nodes: holders });
    for (const holder of holders) {
      if (state.edges.size >= MAX_GRAPH_EDGES) break;
      const edge = {
        id: `has-type|${holder.id}|${node.id}`,
        src: holder.id,
        dst: node.id,
        rel: "has type",
        evidence_level: holder.evidence_level
      };
      state.edges.set(edge.id, edge);
    }
    state.expanded.add(node.id);
    renderAll();
    focusNode(node.id);
    showFeedback(`Loaded ${Math.min(merged.count, SEARCH_LIMIT)} bounded type holders`);
    return true;
  } catch (error) {
    showFeedback(error.message, true);
    return false;
  }
}

async function expandNode(ref, options = {}) {
  const node = findNodeByApiRef(ref) || resolveNodeReference(ref);
  if (!node) return false;
  if (state.expanded.has(node.id)) {
    showFeedback(`${node.name} is already expanded`);
    return true;
  }
  if (node.aggregate || viewDefinition().expandMode === "aggregate") return expandAggregate(node);
  const definition = viewDefinition();
  showFeedback(`Expanding ${node.name}…`);
  let payload;
  if (definition.expandMode === "neighbors") {
    try {
      payload = await fetchNeighborPayload(node);
    } catch (error) {
      showFeedback(error.message, true);
      return false;
    }
  } else {
    try {
      const params = viewParams(definition, node.api_ref || node.id, CHILD_LIMIT);
      payload = await requestJSON(`${definition.endpoint}?${buildQuery(params)}`);
    } catch (error) {
      if (!isMissingRoute(error)) {
        showFeedback(error.message, true);
        return false;
      }
      try {
        payload = await fetchNeighborPayload(node);
      } catch (neighborError) {
        showFeedback(neighborError.message, true);
        return false;
      }
    }
  }
  const merged = mergePayload(payload);
  state.expanded.add(node.id);
  renderAll();
  if (options.focus !== false) focusNode(node.id);
  showFeedback(merged.count ? `Loaded ${Math.min(merged.count, CHILD_LIMIT)} bounded neighbors of ${node.name}` : `${node.name} has no loaded children`);
  return true;
}

function descendantsOf(nodeId) {
  const output = new Set();
  const queue = [String(nodeId)];
  while (queue.length) {
    const current = queue.shift();
    for (const child of stateChildren(current)) {
      if (!output.has(child.id)) {
        output.add(child.id);
        queue.push(child.id);
      }
    }
  }
  return output;
}

function removeNodes(ids) {
  for (const id of ids) {
    state.nodes.delete(id);
    state.details.delete(id);
    state.positions.delete(id);
    state.expanded.delete(id);
  }
  for (const [alias, node] of [...state.aliases]) {
    if (ids.has(node.id)) state.aliases.delete(alias);
  }
  for (const [id, edge] of [...state.edges]) {
    if (ids.has(edge.src) || ids.has(edge.dst)) state.edges.delete(id);
  }
}

function collapseSelected() {
  const anchorId = state.selectedId;
  if (anchorId && stateChildren(anchorId).length) {
    removeNodes(descendantsOf(anchorId));
    state.expanded.delete(anchorId);
    renderAll();
    focusNode(anchorId);
    showFeedback("Collapsed the selected branch");
    return;
  }
  const selected = anchorId ? state.nodes.get(anchorId) : null;
  const ancestry = selected ? nodeTrail(selected).map((node) => node.id) : [];
  const keep = new Set([...state.rootIds, ...ancestry]);
  removeNodes(new Set([...state.nodes.keys()].filter((id) => !keep.has(id))));
  state.expanded.clear();
  renderAll();
  requestAnimationFrame(() => fitGraph(false));
  showFeedback("Collapsed to bounded roots");
}

async function loadSummaryAndEvidence() {
  try {
    const summary = await requestJSON(API.summary);
    state.summary = summary;
    setConnection("ok", "Read-only", summary.db_path || "knowledge graph");
  } catch (error) {
    const payload = error.payload?.probe || error.payload;
    setConnection("error", "Unavailable", payload?.db_path || error.message);
    setSystemBanner(`${error.message}. Existing bounded API routes may be degraded.`);
    setViewState("error", "offline");
    return false;
  }
  const [evidenceResult, readinessResult] = await Promise.allSettled([
    requestJSON(API.evidence),
    requestJSON(API.readiness)
  ]);
  state.evidence = evidenceResult.status === "fulfilled" ? evidenceResult.value.dist || {} : {};
  state.evidenceLevels = [...CANONICAL_EVIDENCE_LEVELS];
  fillEvidenceFilter();
  if (evidenceResult.status === "rejected") {
    showFeedback(`Evidence counts unavailable: ${evidenceResult.reason.message}`, true);
  }
  if (readinessResult.status === "fulfilled") {
    const payload = readinessResult.value;
    state.readiness = firstCollection(payload, ["readiness", "readiness_counts"]);
    state.readinessAvailable = payload.available !== false && state.readiness.length > 0;
    state.readinessLevels = state.readiness
      .map((item) => readinessKey(typeof item === "object" ? item.status ?? item.value : item))
      .filter((value, index, values) => value !== "not reported" && values.indexOf(value) === index);
  } else {
    state.readiness = [];
    state.readinessAvailable = false;
    state.readinessLevels = [];
    showFeedback(`Readiness statuses unavailable: ${readinessResult.reason.message}`, true);
  }
  fillReadinessFilter();
  return true;
}

function fillEvidenceFilter() {
  const select = dom["evidence-filter"];
  const selected = state.filter.evidence;
  select.replaceChildren(new Option("All evidence", "all"));
  for (const level of state.evidenceLevels) {
    select.appendChild(new Option(`${level} · ${numberOr(state.evidence[level], 0)}`, level));
  }
  select.value = state.evidenceLevels.includes(selected) ? selected : "all";
  state.filter.evidence = select.value;
}

function fillReadinessFilter() {
  const select = dom["readiness-filter"];
  const selected = state.filter.readiness;
  select.replaceChildren(new Option("All readiness", "all"));
  const counts = new Map(state.readiness.map((item) => [
    readinessKey(typeof item === "object" ? item.status ?? item.value : item),
    numberOr(typeof item === "object" ? item.count : null, 0)
  ]));
  for (const status of state.readinessLevels) {
    select.appendChild(new Option(`${status} · ${counts.get(status) || 0}`, status));
  }
  select.value = state.readinessLevels.some((status) => status.toLowerCase() === selected.toLowerCase()) ? selected : "all";
  state.filter.readiness = select.value;
}

async function handleGlobalSearch(event) {
  event.preventDefault();
  const query = dom["global-query"].value.trim();
  if (query.length < 2) {
    dom["global-query"].setCustomValidity("Enter at least two characters.");
    dom["global-query"].reportValidity();
    return;
  }
  dom["global-query"].setCustomValidity("");
  dom["search-result-list"].replaceChildren(el("div", "Searching bounded indexes…", "loading-note"));
  dom["search-meta"].textContent = `Query: ${query}`;
  dom["search-results"].hidden = false;
  let payload;
  state.searchCompatibility = false;
  try {
    payload = await requestJSON(`${API.search}?${buildQuery({ q: query, limit: SEARCH_LIMIT })}`);
  } catch (error) {
    if (!isMissingRoute(error)) {
      dom["search-result-list"].replaceChildren(el("div", error.message, "error-note"));
      return;
    }
    try {
      payload = await requestJSON(`${API.nodes}?${buildQuery({ q: query, limit: SEARCH_LIMIT, offset: 0 })}`);
      state.searchCompatibility = true;
    } catch (fallbackError) {
      dom["search-result-list"].replaceChildren(el("div", fallbackError.message, "error-note"));
      return;
    }
  }
  const results = firstCollection(payload, ["results", "nodes", "items", "matches"]);
  state.searchResults = results.map((raw) => normalizeNode(raw)).filter((node) => node && matchesFilters(node));
  renderSearchResults();
}

function renderSearchResults() {
  dom["search-results"].hidden = false;
  const indexLabel = state.searchCompatibility ? "name-only compatibility index" : "name and attribute index";
  dom["search-meta"].textContent = `${state.searchResults.length} bounded result${state.searchResults.length === 1 ? "" : "s"} · ${indexLabel}`;
  dom["search-result-list"].replaceChildren();
  if (!state.searchResults.length) {
    dom["search-result-list"].appendChild(el("div", "No bounded matches returned.", "empty-list"));
    return;
  }
  for (const node of state.searchResults.slice(0, SEARCH_LIMIT)) {
    const item = el("div", null, "result-item");
    const button = el("button", null, "result-main");
    button.type = "button";
    button.appendChild(el("span", node.name, "result-name"));
    button.appendChild(el("span", `${categoryLabel(node.category)} · ${node.evidence_level} · ${nodeReadiness(node)}`, "result-meta"));
    button.addEventListener("click", () => {
      if (!state.nodes.has(node.id) && state.nodes.size >= MAX_LOADED_NODES) {
        const removable = [...state.nodes.keys()].find((id) => !state.rootIds.has(id));
        if (removable) removeNodes(new Set([removable]));
      }
      state.nodes.set(node.id, node);
      state.aliases.set(node.id, node);
      state.aliases.set(node.api_ref, node);
      state.aliases.set(node.name, node);
      selectNode(node.id);
    });
    item.appendChild(button);
    item.appendChild(el("span", displayValue(node.address || node.label), evidenceClass(node.evidence_level)));
    dom["search-result-list"].appendChild(item);
  }
}

function resetViewCorpus() {
  state.viewEpoch += 1;
  state.nodes.clear();
  state.aliases.clear();
  state.edges.clear();
  state.rootIds.clear();
  state.expanded.clear();
  state.positions.clear();
  state.details.clear();
  state.selectedId = null;
  state.investigation = null;
  state.transform = { x: 0, y: 0, k: 1 };
  resetTransform();
}

async function reloadFunctionReadiness() {
  resetViewCorpus();
  state.visibleNodes = [];
  renderAll();
  try {
    await loadViewRoot();
  } catch (error) {
    setViewState("error", "error");
    dom["node-list"].replaceChildren(el("div", error.message, "error-note"));
    showFeedback(error.message, true, true);
  }
}

function switchView(view) {
  if (!VIEW_DEFINITIONS[view] || view === state.view) return;
  stopSimulator();
  state.view = view;
  resetViewCorpus();
  for (const button of document.querySelectorAll(".view-button")) {
    const active = button.dataset.view === view;
    button.classList.toggle("active", active);
    button.setAttribute("aria-pressed", String(active));
  }
  dom["graph-scope"].textContent = `${viewDefinition().title} / root slice`;
  dom["scope-description"].textContent = viewDefinition().description;
  state.visibleNodes = [];
  renderAll();
  loadViewRoot().catch((error) => {
    setViewState("error", "error");
    dom["node-list"].replaceChildren(el("div", error.message, "error-note"));
    dom["edge-layer"].replaceChildren();
    dom["node-layer"].replaceChildren();
    showFeedback(error.message, true, true);
  });
}

function renderAll() {
  state.visibleNodes = visibleNodes();
  renderBreadcrumbs();
  renderNodeList();
  renderMetrics();
  renderGraph();
  renderSelection();
  renderSimulator();
}

function nodeTrail(node) {
  const trail = [];
  const seen = new Set();
  let current = node;
  while (current && !seen.has(current.id)) {
    seen.add(current.id);
    trail.unshift(current);
    current = current.parent_id ? state.nodes.get(String(current.parent_id)) || findNodeByApiRef(current.parent_id) : null;
  }
  return trail;
}

function renderBreadcrumbs() {
  const root = document.createDocumentFragment();
  const selected = state.selectedId ? state.nodes.get(state.selectedId) : null;
  const trail = selected ? nodeTrail(selected) : [];
  if (!trail.length) {
    root.appendChild(el("span", viewDefinition().title, "crumb"));
    root.appendChild(el("span", "/", "crumb-separator"));
    root.appendChild(el("span", "root slice", "crumb"));
    root.appendChild(el("span", " / ", "crumb-separator"));
    root.appendChild(el("span", "bounded corpus", "crumb"));
  } else {
    trail.forEach((node, index) => {
      if (index) root.appendChild(el("span", "›", "crumb-separator"));
      const button = el("button", node.name, "crumb");
      button.type = "button";
      if (index === trail.length - 1) button.setAttribute("aria-current", "page");
      else button.addEventListener("click", () => selectNode(node.id));
      root.appendChild(button);
    });
  }
  dom.breadcrumbs.replaceChildren(root);
}

function renderNodeList() {
  const nodes = state.visibleNodes;
  dom["node-list-count"].textContent = String(nodes.length);
  dom["scope-description"].textContent =
    `${viewDefinition().description} ${state.expanded.size} expanded · ${Math.min(nodes.length, MAX_GRAPH_NODES)} of ${state.nodes.size} loaded shown.`;
  dom["node-list"].replaceChildren();
  if (!nodes.length) {
    dom["node-list"].appendChild(el("div", state.nodes.size ? "No loaded nodes match these filters." : "No bounded nodes returned.", "empty-list"));
    return;
  }
  for (const node of nodes) {
    const row = el("div", null, `tree-row${node.id === state.selectedId ? " selected" : ""}`);
    row.setAttribute("role", "listitem");
    row.style.setProperty("--depth", String(Math.min(5, nodeTrail(node).length - 1)));
    const button = el("button", null, "tree-main");
    button.type = "button";
    button.setAttribute("aria-label", `Select ${node.name}, ${categoryLabel(node.category)}, evidence ${node.evidence_level}`);
    button.appendChild(el("span", node.name, "tree-name"));
    button.appendChild(el("span", `${categoryLabel(node.category)} · ${node.evidence_level} · ${nodeReadiness(node)} · ${nodeDegree(node)} links`, "tree-meta"));
    button.addEventListener("click", () => selectNode(node.id));
    row.appendChild(button);
    if (canExpand(node) || node.id === state.selectedId) {
      const expand = el("button", state.expanded.has(node.id) ? "−" : "+", "expand-node");
      expand.type = "button";
      expand.setAttribute("aria-label", state.expanded.has(node.id) ? `Collapse children of ${node.name}` : `Expand children of ${node.name}`);
      expand.addEventListener("click", () => {
        if (state.expanded.has(node.id)) collapseBranch(node.id);
        else expandNode(node.id);
      });
      row.appendChild(expand);
    } else {
      row.appendChild(el("span", ""));
    }
    dom["node-list"].appendChild(row);
  }
}

function collapseBranch(parentId) {
  const aggregate = state.nodes.get(parentId);
  if (aggregate?.aggregate) {
    const linked = [...state.edges.values()].filter((edge) => edge.dst === aggregate.id && edge.rel === "has type");
    removeNodes(new Set(linked.map((edge) => edge.src)));
    for (const edge of linked) state.edges.delete(edge.id);
    state.expanded.delete(parentId);
  } else {
    removeNodes(descendantsOf(parentId));
    state.expanded.delete(parentId);
  }
  renderAll();
  showFeedback("Collapsed branch");
}

function renderMetrics() {
  const nodes = state.visibleNodes;
  const edgeCount = [...state.edges.values()].filter((edge) =>
    nodes.some((node) => node.id === edge.src) && nodes.some((node) => node.id === edge.dst)).length;
  const reported = nodes.filter((node) => nodeReadiness(node) !== "not reported").length;
  const confidence = nodes.length
    ? nodes.reduce((sum, node) => sum + numberOr(node.confidence, 0), 0) / nodes.length
    : 0;
  const corpus = numberOr(state.summary?.counts?.node, 0);
  const metrics = [
    [String(nodes.length), "visible nodes"],
    [String(edgeCount), "loaded edges"],
    [`${reported}/${nodes.length}`, "readiness reported"],
    [confidence ? confidence.toFixed(2) : "—", "mean confidence"],
    [corpus ? compactNumber(corpus) : "—", "corpus nodes"]
  ];
  dom.metrics.replaceChildren();
  for (const [value, label] of metrics) {
    const item = el("div", null, "metric");
    item.appendChild(el("dd", value, "metric-value"));
    item.appendChild(el("dt", label, "metric-label"));
    dom.metrics.appendChild(item);
  }
}

function compactNumber(value) {
  return new Intl.NumberFormat(undefined, { notation: "compact", maximumFractionDigits: 1 }).format(value);
}

function layoutNodes(nodes) {
  const positions = new Map();
  const byId = new Map(nodes.map((node) => [node.id, node]));
  const unassigned = new Set(nodes.map((node) => node.id));
  const assignLevel = (node, depth, seen = new Set()) => {
    if (!node || seen.has(node.id)) return;
    seen.add(node.id);
    if (!positions.has(node.id)) {
      positions.set(node.id, { x: 0, y: 72 + depth * 132, depth });
    }
    unassigned.delete(node.id);
    for (const child of nodes.filter((candidate) => String(candidate.parent_id) === node.id)) {
      assignLevel(child, depth + 1, new Set(seen));
    }
  };
  for (const node of nodes) {
    if (node.parent_id && byId.has(String(node.parent_id))) continue;
    assignLevel(node, 0);
  }
  let fallbackDepth = 0;
  for (const id of unassigned) {
    assignLevel(byId.get(id), fallbackDepth++ % 4);
  }
  const maxDepth = Math.max(0, ...[...positions.values()].map((position) => position.depth));
  for (let depth = 0; depth <= maxDepth; depth += 1) {
    const row = nodes.filter((node) => positions.get(node.id)?.depth === depth);
    const columnTarget = depth === 0 ? 8 : 6;
    const columns = row.length <= columnTarget ? Math.max(1, row.length) : Math.min(columnTarget, Math.ceil(Math.sqrt(row.length)));
    const rows = Math.max(1, Math.ceil(row.length / columns));
    const horizontalSpan = 1240;
    const verticalSpan = 540;
    row.forEach((node, index) => {
      const current = positions.get(node.id);
      const column = index % columns;
      const gridRow = Math.floor(index / columns);
      current.x = 110 + horizontalSpan * (column + 0.5) / columns;
      current.y = 70 + depth * verticalSpan + verticalSpan * (gridRow + 0.5) / rows;
    });
  }
  state.positions = positions;
}

function graphEdgeSet(nodes) {
  const ids = new Set(nodes.map((node) => node.id));
  const edges = new Map();
  for (const edge of state.edges.values()) {
    if (ids.has(edge.src) && ids.has(edge.dst)) edges.set(edge.id, { ...edge, kind: "relation" });
  }
  for (const node of nodes) {
    if (!node.parent_id || !ids.has(String(node.parent_id))) continue;
    const id = `hierarchy|${node.parent_id}|${node.id}`;
    edges.set(id, { id, src: String(node.parent_id), dst: node.id, rel: "contains", kind: "hierarchy" });
  }
  const traced = new Set(state.simulator.trail.map((step) => step.edgeId).filter(Boolean));
  for (const [id, edge] of edges) if (traced.has(id)) edge.kind = "trace";
  return [...edges.values()].slice(0, MAX_GRAPH_EDGES);
}

function shapeFor(node) {
  if (node.category === "type") {
    return svgEl("polygon", { points: "0,-22 34,0 0,22 -34,0", class: "node-shape" });
  }
  if (node.category === "function") {
    return svgEl("circle", { r: 20, class: "node-shape" });
  }
  if (node.category === "event") {
    return svgEl("polygon", { points: "0,-24 25,0 0,24 -25,0", class: "node-shape" });
  }
  if (node.category === "package") {
    return svgEl("rect", { x: -42, y: -19, width: 84, height: 38, rx: 3, class: "node-shape" });
  }
  if (node.category === "architecture") {
    return svgEl("rect", { x: -38, y: -19, width: 76, height: 38, rx: 12, class: "node-shape" });
  }
  if (node.category === "asset") {
    return svgEl("path", { d: "M-38,-19 L34,-19 L42,0 L34,19 L-38,19 L-46,0 Z", class: "node-shape" });
  }
  return svgEl("rect", { x: -36, y: -19, width: 72, height: 38, rx: 8, class: "node-shape" });
}

function truncate(value, length) {
  const text = String(value || "");
  return text.length > length ? `${text.slice(0, length - 1)}…` : text;
}

function renderGraph() {
  const nodes = state.visibleNodes;
  dom["edge-layer"].replaceChildren();
  dom["node-layer"].replaceChildren();
  if (!nodes.length) {
    dom["graph-feedback"].hidden = false;
    dom["graph-feedback"].className = "graph-feedback";
    dom["graph-feedback"].textContent = state.nodes.size ? "No nodes match the active evidence/readiness filters." : "No bounded nodes are loaded.";
    return;
  }
  layoutNodes(nodes);
  const edges = graphEdgeSet(nodes);
  for (const edge of edges) {
    const source = state.positions.get(edge.src);
    const target = state.positions.get(edge.dst);
    if (!source || !target) continue;
    const middle = (source.x + target.x) / 2;
    const path = svgEl("path", {
      d: `M ${source.x} ${source.y} C ${middle} ${source.y}, ${middle} ${target.y}, ${target.x} ${target.y}`,
      class: `graph-edge ${edge.kind || "relation"}`
    });
    const title = svgEl("title");
    title.textContent = `${edge.rel}: ${edge.src} → ${edge.dst}`;
    path.appendChild(title);
    dom["edge-layer"].appendChild(path);
  }
  for (const node of nodes) {
    const position = state.positions.get(node.id);
    const group = svgEl("g", {
      transform: `translate(${position.x} ${position.y})`,
      class: `graph-node cat-${node.category} ${evidenceClass(node.evidence_level)}${node.id === state.selectedId ? " selected" : ""}${evidenceIndex(node.evidence_level) <= 1 ? " weak-evidence" : ""}`,
      tabindex: "0",
      role: "button",
      "aria-label": `${node.name}. ${categoryLabel(node.category)}. Evidence ${node.evidence_level}. Readiness ${nodeReadiness(node)}. ${nodeDegree(node)} loaded relationships. Press E to expand.`
    });
    group.dataset.nodeId = node.id;
    const title = svgEl("title");
    title.textContent = `${node.name}\n${categoryLabel(node.category)} · ${node.evidence_level} · ${nodeReadiness(node)}\n${displayValue(node.address)}`;
    group.appendChild(title);
    group.appendChild(svgEl("ellipse", { cx: 0, cy: 0, rx: 48, ry: 27, class: "node-halo" }));
    group.appendChild(shapeFor(node));
    const name = svgEl("text", { x: 0, y: -2, class: "node-name" });
    name.textContent = truncate(node.name, node.category === "function" ? 14 : 18);
    group.appendChild(name);
    const evidence = svgEl("text", { x: 0, y: 12, class: `node-evidence ${evidenceClass(node.evidence_level)}` });
    evidence.textContent = truncate(`${node.evidence_level} · ${nodeReadiness(node)}`, 21);
    group.appendChild(evidence);
    group.addEventListener("click", (event) => {
      event.stopPropagation();
      selectNode(node.id);
    });
    group.addEventListener("dblclick", (event) => {
      event.stopPropagation();
      expandNode(node.id);
    });
    group.addEventListener("keydown", (event) => {
      if (event.key === "Enter" || event.key === " ") {
        event.preventDefault();
        selectNode(node.id);
      } else if (event.key.toLowerCase() === "e") {
        event.preventDefault();
        expandNode(node.id);
      }
    });
    dom["node-layer"].appendChild(group);
  }
  applyTransform();
}

function applyTransform() {
  const { x, y, k } = state.transform;
  dom["graph-viewport"].setAttribute("transform", `translate(${x} ${y}) scale(${k})`);
  dom["zoom-readout"].textContent = `${Math.round(k * 100)}%`;
}

function setTransform(transform) {
  state.transform = {
    x: Math.max(-SVG_WIDTH * 2, Math.min(SVG_WIDTH * 2, transform.x)),
    y: Math.max(-SVG_HEIGHT * 2, Math.min(SVG_HEIGHT * 2, transform.y)),
    k: Math.max(0.2, Math.min(3.5, transform.k))
  };
  applyTransform();
}

function resetTransform() {
  setTransform({ x: 0, y: 0, k: 1 });
}

function fitGraph(animate = true) {
  if (!state.positions.size) {
    resetTransform();
    return;
  }
  const values = [...state.positions.values()];
  const minX = Math.min(...values.map((point) => point.x)) - 65;
  const maxX = Math.max(...values.map((point) => point.x)) + 65;
  const minY = Math.min(...values.map((point) => point.y)) - 45;
  const maxY = Math.max(...values.map((point) => point.y)) + 45;
  const width = Math.max(1, maxX - minX);
  const height = Math.max(1, maxY - minY);
  const k = Math.max(0.2, Math.min(1.2, 0.9 / Math.max(width / SVG_WIDTH, height / SVG_HEIGHT)));
  const target = {
    k,
    x: SVG_WIDTH / 2 - ((minX + maxX) / 2) * k,
    y: SVG_HEIGHT / 2 - ((minY + maxY) / 2) * k
  };
  if (!animate) setTransform(target);
  else animateTransform(target);
}

function animateTransform(target) {
  if (window.matchMedia("(prefers-reduced-motion: reduce)").matches) {
    setTransform(target);
    return;
  }
  const start = { ...state.transform };
  const startTime = performance.now();
  const duration = 180;
  const step = (time) => {
    const progress = Math.min(1, (time - startTime) / duration);
    const eased = 1 - (1 - progress) ** 3;
    setTransform({
      x: start.x + (target.x - start.x) * eased,
      y: start.y + (target.y - start.y) * eased,
      k: start.k + (target.k - start.k) * eased
    });
    if (progress < 1) requestAnimationFrame(step);
  };
  requestAnimationFrame(step);
}

function focusNode(ref) {
  const node = findNodeByApiRef(ref) || resolveNodeReference(ref);
  if (!node) return;
  if (!state.positions.has(node.id)) {
    selectNode(node.id);
    return;
  }
  const point = state.positions.get(node.id);
  const k = Math.max(1.05, state.transform.k);
  animateTransform({ x: SVG_WIDTH / 2 - point.x * k, y: SVG_HEIGHT / 2 - point.y * k, k });
  const graphNode = dom["node-layer"].querySelector(`[data-node-id="${CSS.escape(node.id)}"]`);
  graphNode?.focus({ preventScroll: true });
}

function clientToSvg(clientX, clientY) {
  const canvas = dom["graph-canvas"];
  const matrix = canvas.getScreenCTM?.();
  if (matrix?.inverse) {
    const point = canvas.createSVGPoint();
    point.x = clientX;
    point.y = clientY;
    return point.matrixTransform(matrix.inverse());
  }
  const rect = canvas.getBoundingClientRect();
  return {
    x: (clientX - rect.left) * SVG_WIDTH / Math.max(1, rect.width),
    y: (clientY - rect.top) * SVG_HEIGHT / Math.max(1, rect.height)
  };
}

function zoomAt(factor, clientX, clientY) {
  const screen = clientX === undefined
    ? { x: SVG_WIDTH / 2, y: SVG_HEIGHT / 2 }
    : clientToSvg(clientX, clientY);
  const current = state.transform;
  const graphX = (screen.x - current.x) / current.k;
  const graphY = (screen.y - current.y) / current.k;
  const k = Math.max(0.2, Math.min(3.5, current.k * factor));
  setTransform({ k, x: screen.x - graphX * k, y: screen.y - graphY * k });
}

async function selectNode(ref, options = {}) {
  const existing = findNodeByApiRef(ref) || resolveNodeReference(ref);
  if (!existing) return;
  state.selectedId = existing.id;
  state.investigation = null;
  const token = ++state.detailToken;
  if (existing.aggregate) {
    state.detailLoading = false;
    state.visibleNodes = visibleNodes();
    renderNodeList();
    renderMetrics();
    renderGraph();
    renderSelection();
    if (options.focus !== false) focusNode(existing.id);
    return;
  }
  state.detailLoading = true;
  state.visibleNodes = visibleNodes();
  renderNodeList();
  renderMetrics();
  renderGraph();
  renderSelection();
  if (options.focus !== false) focusNode(existing.id);
  const refValue = existing.api_ref || existing.id;
  const detailRequest = existing.category === "function"
    ? requestJSON(API.function(refValue, DETAIL_LIMIT)).catch((error) => {
      if (!isMissingRoute(error)) throw error;
      return requestJSON(API.node(refValue));
    })
    : requestJSON(API.node(refValue));
  const [detailResult, neighborResult] = await Promise.allSettled([
    detailRequest,
    requestJSON(API.neighbors(refValue, 1, MAX_GRAPH_NODES * 2))
  ]);
  if (token !== state.detailToken || state.selectedId !== existing.id) return;
  const errorMessages = [];
  if (detailResult.status === "fulfilled") {
    const payload = detailResult.value;
    const detailed = normalizeNode(payload.function || payload.node || existing);
    const readiness = payload.readiness ??
      payload.investigations?.find((investigation) => investigation.triage_status)?.triage_status ??
      detailed.readiness;
    detailed.readiness = readiness;
    if (!existing.event_record) {
      state.nodes.set(detailed.id, detailed);
      state.aliases.set(detailed.id, detailed);
      state.aliases.set(detailed.api_ref, detailed);
      state.aliases.set(detailed.name, detailed);
    }
    state.details.set(existing.id, {
      ...payload,
      fields: payload.fields || [],
      investigations: payload.investigations || [],
      provenance: payload.provenance || null,
      readiness
    });
  } else {
    errorMessages.push(detailResult.reason.message);
  }
  if (neighborResult.status === "fulfilled") {
    mergePayload(neighborResult.value);
  } else {
    errorMessages.push(neighborResult.reason.message);
  }
  state.detailLoading = false;
  if (errorMessages.length === 2) {
    showFeedback(`Selection loaded with API errors: ${errorMessages.join(" · ")}`, true);
  }
  renderAll();
  if (options.focus !== false) focusNode(existing.id);
}

function renderEmptySelection() {
  dom["selection-content"].replaceChildren();
  const empty = el("div", null, "empty-selection");
  empty.appendChild(el("span", null, "empty-orbit"));
  empty.setAttribute("aria-hidden", "true");
  empty.appendChild(el("h3", "No node selected"));
  empty.appendChild(el("p", "Select a graph node or search result. Identity, evidence, provenance, fields, and bounded relationships remain visible here."));
  dom["selection-content"].appendChild(empty);
}

function selectionHero(node) {
  const hero = el("section", null, "selection-hero");
  const badges = el("div", null, "selection-kind");
  badges.appendChild(el("span", categoryLabel(node.category), "category-badge"));
  badges.appendChild(el("span", `Evidence ${node.evidence_level}`, `evidence-badge ${evidenceClass(node.evidence_level)}`));
  badges.appendChild(el("span", `Readiness ${nodeReadiness(node)}`, `readiness-badge ${readinessClass(nodeReadiness(node))}`));
  hero.appendChild(badges);
  hero.appendChild(el("h3", node.name, "selection-name"));
  hero.appendChild(el("p", `ID ${node.id} · API ref ${node.api_ref}`, "selection-id"));
  const actions = el("div", null, "selection-actions");
  const focus = el("button", "Focus graph");
  focus.type = "button";
  focus.addEventListener("click", () => focusNode(node.id));
  const expand = el("button", node.aggregate
    ? (state.expanded.has(node.id) ? "Hide type holders" : "Find type holders")
    : (state.expanded.has(node.id) ? "Collapse branch" : "Lazy expand"));
  expand.type = "button";
  expand.addEventListener("click", () => {
    if (state.expanded.has(node.id)) collapseBranch(node.id);
    else expandNode(node.id);
  });
  const trace = el("button", "Start trace here");
  trace.type = "button";
  trace.addEventListener("click", () => {
    state.simulator.origin = node.id;
    if (!state.simulator.active) toggleSimulator(true);
    else resetSimulator();
  });
  actions.append(focus, expand, trace);
  hero.appendChild(actions);
  return hero;
}

function dossierSection(title, rows, extra) {
  const section = el("section", null, "dossier-section");
  section.appendChild(el("h3", title));
  if (rows.length) {
    const grid = el("dl", null, "dossier-grid");
    for (const [key, value] of rows) {
      grid.appendChild(el("dt", key));
      grid.appendChild(el("dd", displayValue(value)));
    }
    section.appendChild(grid);
  }
  if (extra) section.appendChild(extra);
  return section;
}

function fieldsTable(fields) {
  if (!Array.isArray(fields) || !fields.length ||
      !fields.some((field) => field && typeof field === "object" && !Array.isArray(field))) return null;
  const wrap = el("div", null, "table-wrap");
  const table = el("table");
  const header = el("tr");
  for (const title of ["offset", "role", "offset evidence", "meaning evidence", "value", "source"]) {
    header.appendChild(el("th", title));
  }
  const thead = el("thead");
  thead.appendChild(header);
  table.appendChild(thead);
  const body = el("tbody");
  for (const field of fields.slice(0, 80)) {
    const row = el("tr");
    row.appendChild(el("td", field.offset, evidenceClass(field.offset_evidence)));
    row.appendChild(el("td", field.role));
    row.appendChild(el("td", field.offset_evidence, evidenceClass(field.offset_evidence)));
    row.appendChild(el("td", field.meaning_evidence, evidenceClass(field.meaning_evidence)));
    row.appendChild(el("td", field.value ?? "—"));
    row.appendChild(el("td", field.source ?? "—"));
    body.appendChild(row);
  }
  table.appendChild(body);
  wrap.appendChild(table);
  return wrap;
}

function relationshipsTable(node) {
  const relationships = [];
  for (const edge of state.edges.values()) {
    if (edge.src === node.id || edge.dst === node.id) relationships.push(edge);
  }
  if (!relationships.length) return null;
  const wrap = el("div", null, "table-wrap");
  const table = el("table");
  const header = el("tr");
  for (const title of ["direction", "relationship", "neighbor", "category", "evidence"]) header.appendChild(el("th", title));
  const head = el("thead");
  head.appendChild(header);
  table.appendChild(head);
  const body = el("tbody");
  for (const edge of relationships.slice(0, 80)) {
    const outbound = edge.src === node.id;
    const otherId = outbound ? edge.dst : edge.src;
    const other = state.nodes.get(otherId);
    const row = el("tr");
    row.appendChild(el("td", outbound ? "out" : "in"));
    row.appendChild(el("td", edge.rel));
    const cell = el("td");
    if (other) {
      const button = el("button", other.name, "table-link");
      button.type = "button";
      button.addEventListener("click", () => selectNode(other.id));
      cell.appendChild(button);
    } else {
      cell.appendChild(el("span", otherId, "unloaded-ref"));
    }
    row.appendChild(cell);
    row.appendChild(el("td", other ? categoryLabel(other.category) : "Unloaded"));
    row.appendChild(el("td", edge.evidence_level, evidenceClass(edge.evidence_level)));
    body.appendChild(row);
  }
  table.appendChild(body);
  wrap.appendChild(table);
  return wrap;
}

function investigationsTable(investigations) {
  if (!Array.isArray(investigations) || !investigations.length) return null;
  const wrap = el("div", null, "table-wrap");
  const table = el("table");
  const header = el("tr");
  for (const title of ["id", "stage", "status", "block reason"]) header.appendChild(el("th", title));
  const head = el("thead");
  head.appendChild(header);
  table.appendChild(head);
  const body = el("tbody");
  for (const investigation of investigations) {
    const row = el("tr");
    const idCell = el("td");
    const button = el("button", investigation.id, "table-link");
    button.type = "button";
    button.addEventListener("click", () => showInvestigation(investigation.id));
    idCell.appendChild(button);
    row.appendChild(idCell);
    row.appendChild(el("td", investigation.stage));
    row.appendChild(el("td", investigation.status));
    row.appendChild(el("td", investigation.block_reason || "—"));
    body.appendChild(row);
  }
  table.appendChild(body);
  wrap.appendChild(table);
  return wrap;
}

function hasValue(value) {
  if (value === null || value === undefined || value === "") return false;
  if (Array.isArray(value)) return value.length > 0;
  return true;
}

function firstProvided(...values) {
  return values.find(hasValue);
}

function valueBlock(value) {
  const block = el("pre", typeof value === "object" ? safeJSON(value) : displayValue(value), "code-block");
  return block;
}

function objectRows(value) {
  if (!value || typeof value !== "object" || Array.isArray(value)) return [];
  return Object.entries(value).map(([key, item]) => [key.replaceAll("_", " "), item]);
}

function normalizedAddress(value) {
  return String(value ?? "").trim().toLowerCase().replace(/^0x/, "");
}

function functionCandidates(node, details) {
  const attrs = node.attrs || {};
  const metadata = details.metadata || {};
  const triage = details.triage || {};
  const candidates = [metadata.va, metadata.address, metadata.addr, metadata.rva,
    triage.va, triage.rva, node.va, node.address, node.rva, attrs.va, attrs.address,
    attrs.addr, attrs.rva, node.name];
  return new Set(candidates.map(normalizedAddress).filter(Boolean));
}

function xrefsTable(xrefs, candidates) {
  if (!Array.isArray(xrefs) || !xrefs.length) return null;
  const wrap = el("div", null, "table-wrap");
  const table = el("table");
  const header = el("tr");
  for (const title of ["direction", "caller VA", "callee VA", "reference", "callsite", "source"]) {
    header.appendChild(el("th", title));
  }
  const head = el("thead");
  head.appendChild(header);
  table.appendChild(head);
  const body = el("tbody");
  for (const xref of xrefs.slice(0, DETAIL_LIMIT)) {
    const caller = candidates.has(normalizedAddress(xref.caller_va));
    const callee = candidates.has(normalizedAddress(xref.callee_va));
    const direction = caller && callee ? "self" : caller ? "caller" : callee ? "callee" : "related";
    const row = el("tr");
    for (const value of [direction, xref.caller_va, xref.callee_va, xref.reference_type,
      xref.callsite_va, xref.source]) {
      row.appendChild(el("td", value ?? "—"));
    }
    body.appendChild(row);
  }
  table.appendChild(body);
  wrap.appendChild(table);
  return wrap;
}

function appendFunctionDossier(content, node, details) {
  const attrs = node.attrs || {};
  const metadata = details.metadata || {};
  const triage = details.triage || {};
  const investigations = details.investigations || node.investigations || [];
  const investigation = investigations[0] || {};
  const firstInvestigation = (items) => items.find((item) => item && hasValue(item.subsystem))?.subsystem;
  const rows = [
    ["VA", firstProvided(metadata.va, triage.va, node.va, node.address)],
    ["name", metadata.name || node.name],
    ["category", firstProvided(triage.category, details.category, node.label)],
    ["subsystem", firstProvided(triage.subsystem, details.subsystem, attrs.subsystem, firstInvestigation(investigations))],
    ["package", firstProvided(details.package, triage.package, node.package, attrs.package, attrs.package_ids)],
    ["priority", firstProvided(triage.priority, details.priority, node.priority, attrs.priority)],
    ["evidence", node.evidence_level],
    ["triage evidence", triage.evidence],
    ["decomp", firstProvided(metadata.decompiled_file, triage.decomp_path, attrs.decompiled_file)],
    ["decomp status", firstProvided(attrs.ghidra_status, details.decomp_status, triage.decomp_status)],
    ["semantic status", firstProvided(details.semantic_status, triage.semantic_status,
      node.semantic_status, attrs.semantic_status, attrs.semantic_understanding, attrs.semantics)],
    ["readiness", firstProvided(details.readiness, node.readiness, investigation.triage_status)],
    ["callers", triage.caller_count],
    ["callees", triage.callee_count],
    ["SDK name", firstProvided(metadata.sdk_name, triage.sdk_name, attrs.sdk_name)],
    ["signature", metadata.signature],
    ["state", node.state]
  ];
  content.appendChild(dossierSection("Function dossier", rows));
  const candidates = functionCandidates(node, details);
  const xrefs = xrefsTable(details.xrefs, candidates);
  const relationshipTitle = `Representative relationships (${numberOr(details.xref_total, details.xrefs?.length || 0)}${details.xref_truncated ? "+" : ""})`;
  content.appendChild(dossierSection(relationshipTitle, [],
    xrefs || el("p", "No bounded xrefs were provided.", "microcopy")));
  const structures = firstProvided(details.related_structures, triage.struct_names,
    node.related_structures, attrs.related_structures, attrs.struct_names, attrs.structure_name);
  if (hasValue(structures)) content.appendChild(dossierSection("Related structures", [], valueBlock(structures)));
  const fieldData = firstProvided(details.fields, node.fields, attrs.fields, attrs.field);
  if (hasValue(fieldData) && (!Array.isArray(fieldData) || fieldData.length)) {
    const fieldTable = fieldsTable(fieldData);
    content.appendChild(dossierSection(`Fields (${Array.isArray(fieldData) ? Math.min(DETAIL_LIMIT, fieldData.length) : "provided"})`, [],
      fieldTable || valueBlock(fieldData)));
  }
  const events = firstProvided(details.events, attrs.events, node.attrs?.events);
  if (hasValue(events)) content.appendChild(dossierSection("Events", [], valueBlock(events)));
  const transitions = firstProvided(details.state_transitions, node.state_transitions,
    attrs.state_transitions, attrs.state_machine);
  if (hasValue(transitions)) content.appendChild(dossierSection("State transitions", [], valueBlock(transitions)));
  const boundary = firstProvided(details.engine_boundary, node.engine_boundary, triage.engine_boundary,
    attrs.engine_boundary, attrs.boundary);
  if (hasValue(boundary)) content.appendChild(dossierSection("Engine boundary", [], valueBlock(boundary)));
  const questions = firstProvided(details.unresolved_questions, node.unresolved_questions,
    attrs.unresolved_questions, attrs.unresolved);
  if (hasValue(questions)) content.appendChild(dossierSection("Unresolved questions", [], valueBlock(questions)));
  const provenance = firstProvided(details.provenance, node.provenance);
  const provenanceRows = objectRows(provenance);
  const provenanceLabels = new Set(provenanceRows.map(([key]) => key));
  for (const [key, value] of [["source", metadata.source], ["trace", metadata.trace]]) {
    if (hasValue(value) && !provenanceLabels.has(key)) provenanceRows.push([key, value]);
  }
  content.appendChild(dossierSection("Provenance", provenanceRows));
}

function renderSelection() {
  const node = state.selectedId ? state.nodes.get(state.selectedId) : null;
  if (!node) {
    renderEmptySelection();
    return;
  }
  const content = dom["selection-content"];
  content.replaceChildren();
  content.appendChild(selectionHero(node));
  if (state.detailLoading) content.appendChild(el("div", "Loading selection evidence and bounded relationships…", "loading-note"));
  const details = state.details.get(node.id) || {};
  if (node.category === "function") {
    appendFunctionDossier(content, node, details);
  } else {
    const directions = nodeDirectionCounts(node);
    const eventCount = Array.isArray(node.attrs?.events) ? node.attrs.events.length : numberOr(node.attrs?.event_count, 0);
    const provenance = details.provenance || node.provenance || {};
    const identityRows = [
      ["label", node.label],
      ["name", node.name],
      ["type value", node.type_value],
      ["facet value", node.facet_value],
      ["event value", node.event_record ? (node.event_value ?? "null value recorded") : null],
      ["evidence", node.evidence_level],
      ["confidence", numberOr(node.confidence, 0).toFixed(2)],
      ["readiness", nodeReadiness(node)],
      ["state", node.state],
      ["origin", node.origin],
      ["address", node.address],
      ["rva", node.rva],
      ["updated", node.updated_at]
    ];
    content.appendChild(dossierSection("Identity", identityRows));
    const provenanceRows = [
      ["binary sha256", node.binary_sha256 || provenance.binary_sha256],
      ["origin", provenance.origin || node.origin],
      ["SDK name", provenance.sdk_name || node.attrs?.sdk_name],
      ["source ref", provenance.src_ref || node.attrs?.src],
      ["dossier", provenance.dossier || node.attrs?.dossier],
      ["trace", node.attrs?.trace],
      ["address", provenance.address || node.attrs?.address],
      ["rva", provenance.rva || node.attrs?.rva]
    ];
    content.appendChild(dossierSection("Provenance / binary identity", provenanceRows));
    const metricRows = [
      ["loaded degree", nodeDegree(node)],
      ["facet holders", node.count],
      ["inbound", directions.inbound],
      ["outbound", directions.outbound],
      ["fields", details.fields?.length || node.fields?.length || 0],
      ["investigations", details.investigations?.length || node.investigations?.length || 0],
      ["events", eventCount],
      ["parent", node.parent_id]
    ];
    content.appendChild(dossierSection("Selection metrics", metricRows));
  }
  if (node.category !== "function") {
    const fieldTable = fieldsTable(details.fields || node.fields);
    if (fieldTable) content.appendChild(dossierSection(`Fields (${Math.min(DETAIL_LIMIT, (details.fields || node.fields).length)})`, [], fieldTable));
  }
  const relations = relationshipsTable(node);
  content.appendChild(dossierSection(`Bounded relationships (${Math.min(DETAIL_LIMIT, [...state.edges.values()].filter((edge) => edge.src === node.id || edge.dst === node.id).length)})`, [], relations || el("p", "No relationships are loaded. Use lazy expand or the simulator to fetch a bounded neighborhood.", "microcopy")));
  const investigations = investigationsTable(details.investigations || node.investigations);
  if (investigations) content.appendChild(dossierSection("Investigations", [], investigations));
  if (state.investigation) content.appendChild(renderInvestigationDossier());
  const attrs = document.createElement("pre");
  attrs.className = "json-block";
  attrs.textContent = safeJSON(node.attrs || node.raw || {});
  content.appendChild(dossierSection("Raw attributes (UI-bounded)", [], attrs));
}

function renderInvestigationDossier() {
  const investigation = state.investigation;
  const box = el("div");
  const values = el("dl", null, "dossier-grid");
  for (const [key, value] of [
    ["kind", investigation.kind],
    ["mode", investigation.mode],
    ["subsystem", investigation.subsystem],
    ["why interesting", investigation.why_interesting]
  ]) {
    values.appendChild(el("dt", key));
    values.appendChild(el("dd", displayValue(value)));
  }
  box.appendChild(values);
  for (const key of ["prerequisites", "attempts", "checkpoint", "evidence_refs"]) {
    if (investigation[key] === null || investigation[key] === undefined) continue;
    const pre = el("pre", safeJSON(investigation[key]), "code-block");
    box.appendChild(dossierSection(key.replaceAll("_", " "), [], pre));
  }
  return dossierSection(`Investigation ${investigation.id || "dossier"}`, [
    ["stage", investigation.stage],
    ["status", investigation.status],
    ["block reason", investigation.block_reason],
    ["updated", investigation.updated_at]
  ], box);
}

async function showInvestigation(id) {
  try {
    const response = await requestJSON(API.investigation(id));
    state.investigation = response.investigation;
    renderSelection();
  } catch (error) {
    showFeedback(error.message, true);
  }
}

function clearSelection() {
  state.selectedId = null;
  state.investigation = null;
  state.detailLoading = false;
  state.detailToken += 1;
  renderAll();
}

function simulatorNeighbors(ref) {
  const node = findNodeByApiRef(ref) || resolveNodeReference(ref);
  if (!node) return [];
  return [...state.edges.values()]
    .filter((edge) => edge.src === node.id || edge.dst === node.id)
    .map((edge) => ({
      id: edge.src === node.id ? edge.dst : edge.src,
      edgeId: edge.id,
      rel: edge.rel
    }))
    .filter((item) => state.nodes.has(item.id) && belongsToView(state.nodes.get(item.id)) &&
      matchesFilters(state.nodes.get(item.id)))
    .sort((a, b) => hotspotScore(state.nodes.get(b.id)) - hotspotScore(state.nodes.get(a.id)));
}

function resetSimulator() {
  const origin = state.simulator.origin || state.selectedId;
  if (!origin) {
    state.simulator.visited = [];
    state.simulator.trail = [];
    state.simulator.queue = [];
    renderSimulator();
    return;
  }
  state.simulator.origin = origin;
  state.simulator.visited = [origin];
  state.simulator.trail = [];
  state.simulator.queue = simulatorNeighbors(origin).slice(0, MAX_TRACE_NODES);
  renderSimulator();
  renderGraph();
}

async function toggleSimulator(force) {
  const active = typeof force === "boolean" ? force : !state.simulator.active;
  if (!active) {
    stopSimulator();
    renderGraph();
    return;
  }
  state.simulator.active = true;
  dom["simulator-toggle"].setAttribute("aria-pressed", "true");
  dom["simulator-panel"].hidden = false;
  if (!state.simulator.origin) state.simulator.origin = state.selectedId;
  if (!state.simulator.origin) {
    showFeedback("Select a node before starting the trace simulator", true);
    state.simulator.active = false;
    dom["simulator-toggle"].setAttribute("aria-pressed", "false");
    dom["simulator-panel"].hidden = true;
    return;
  }
  const origin = state.nodes.get(state.simulator.origin);
  if (origin?.aggregate) {
    await expandAggregate(origin);
  } else {
    try {
      const payload = await requestJSON(`${API.simulator}?${buildQuery({
        root: origin?.api_ref || state.simulator.origin,
        depth: 1,
        limit: MAX_GRAPH_NODES,
        edge_limit: MAX_GRAPH_EDGES
      })}`);
      mergePayload(payload);
    } catch (error) {
      if (!simulatorNeighbors(state.simulator.origin).length) await selectNode(state.simulator.origin);
      if (!isMissingRoute(error) && state.nodes.size < 2) showFeedback(error.message, true);
    }
  }
  resetSimulator();
}

async function advanceSimulator() {
  if (!state.simulator.active || state.simulator.advancing) return;
  state.simulator.advancing = true;
  try {
    if (!state.simulator.origin) state.simulator.origin = state.selectedId;
    if (!state.simulator.queue.length) {
      const current = state.simulator.visited[state.simulator.visited.length - 1] || state.simulator.origin;
      state.simulator.queue = simulatorNeighbors(current)
        .filter((item) => !state.simulator.visited.includes(item.id))
        .slice(0, MAX_TRACE_NODES);
    }
    const next = state.simulator.queue.shift();
    if (!next) {
      state.simulator.trail.push({ id: state.simulator.origin, edgeId: null, rel: "bounded frontier exhausted" });
      stopSimulatorPlayback();
      renderSimulator();
      return;
    }
    state.simulator.visited.push(next.id);
    state.simulator.trail.push({ id: next.id, edgeId: next.edgeId, rel: next.rel });
    await selectNode(next.id, { focus: true });
    if (state.simulator.active) renderSimulator();
  } finally {
    state.simulator.advancing = false;
  }
}

function stopSimulatorPlayback() {
  state.simulator.playing = false;
  state.simulator.advancing = false;
  if (state.simulator.timer) {
    window.clearInterval(state.simulator.timer);
    state.simulator.timer = null;
  }
}

function stopSimulator() {
  stopSimulatorPlayback();
  state.simulator.active = false;
  state.simulator.origin = null;
  state.simulator.visited = [];
  state.simulator.trail = [];
  state.simulator.queue = [];
  dom["simulator-toggle"].setAttribute("aria-pressed", "false");
  dom["simulator-panel"].hidden = true;
}

function toggleSimulatorPlayback() {
  if (state.simulator.playing) {
    stopSimulatorPlayback();
    renderSimulator();
    return;
  }
  if (!state.simulator.queue.length) resetSimulator();
  state.simulator.playing = true;
  state.simulator.timer = window.setInterval(advanceSimulator, 1200);
  renderSimulator();
}

function renderSimulator() {
  if (!state.simulator.active) return;
  const queueLength = state.simulator.queue.length;
  const visited = state.simulator.visited.length;
  dom["simulator-status"].textContent = state.simulator.playing
    ? `Running · ${visited} visited · ${queueLength} queued`
    : `${visited} visited · ${queueLength} queued · bounded to ${MAX_TRACE_NODES} steps`;
  dom["simulator-play"].textContent = state.simulator.playing ? "Pause" : "Run";
  dom["simulator-step"].disabled = state.simulator.advancing || (!state.simulator.queue.length && visited > 1);
  dom["simulator-trail"].replaceChildren();
  for (const step of state.simulator.trail.slice(-MAX_TRACE_NODES)) {
    const node = state.nodes.get(step.id);
    dom["simulator-trail"].appendChild(el("li", `${step.rel} → ${node?.name || step.id}`));
  }
}

function clearSearchResults() {
  state.searchResults = [];
  dom["search-results"].hidden = true;
  dom["search-result-list"].replaceChildren();
}

function applyFilters() {
  state.visibleNodes = visibleNodes();
  renderNodeList();
  renderMetrics();
  renderGraph();
  requestAnimationFrame(() => fitGraph(false));
}

function updateFilterFromForm() {
  const previousReadiness = state.filter.readiness;
  state.filter.evidence = dom["evidence-filter"].value;
  state.filter.readiness = dom["readiness-filter"].value;
  state.filter.sort = dom["sort-filter"].value;
  if (state.view === "functions" && previousReadiness !== state.filter.readiness) {
    reloadFunctionReadiness();
    return;
  }
  applyFilters();
}

function setupGraphPointer() {
  dom["graph-canvas"].addEventListener("wheel", (event) => {
    event.preventDefault();
    const factor = event.deltaY < 0 ? 1.13 : 1 / 1.13;
    zoomAt(factor, event.clientX, event.clientY);
  }, { passive: false });
  dom["graph-canvas"].addEventListener("pointerdown", (event) => {
    if (event.button !== 0 || event.target.closest(".graph-node")) return;
    state.drag = {
      pointerId: event.pointerId,
      start: clientToSvg(event.clientX, event.clientY),
      transform: { ...state.transform }
    };
    dom["graph-canvas"].setPointerCapture(event.pointerId);
    dom["graph-canvas"].classList.add("panning");
  });
  dom["graph-canvas"].addEventListener("pointermove", (event) => {
    if (!state.drag || state.drag.pointerId !== event.pointerId) return;
    const current = clientToSvg(event.clientX, event.clientY);
    setTransform({
      x: state.drag.transform.x + current.x - state.drag.start.x,
      y: state.drag.transform.y + current.y - state.drag.start.y,
      k: state.drag.transform.k
    });
  });
  const endDrag = (event) => {
    if (!state.drag || state.drag.pointerId !== event.pointerId) return;
    state.drag = null;
    dom["graph-canvas"].classList.remove("panning");
    if (dom["graph-canvas"].hasPointerCapture(event.pointerId)) dom["graph-canvas"].releasePointerCapture(event.pointerId);
  };
  dom["graph-canvas"].addEventListener("pointerup", endDrag);
  dom["graph-canvas"].addEventListener("pointercancel", endDrag);
  dom["graph-canvas"].addEventListener("keydown", (event) => {
    if (event.key === "+" || event.key === "=") {
      event.preventDefault();
      zoomAt(1.2);
    } else if (event.key === "-") {
      event.preventDefault();
      zoomAt(1 / 1.2);
    } else if (event.key.toLowerCase() === "f") {
      event.preventDefault();
      fitGraph();
    } else if (event.key === "Escape") {
      stopSimulatorPlayback();
      renderSimulator();
    }
  });
}

async function init() {
  cacheDom();
  setupGraphPointer();
  dom["global-search"].addEventListener("submit", handleGlobalSearch);
  dom["close-search-results"].addEventListener("click", clearSearchResults);
  for (const control of [dom["evidence-filter"], dom["readiness-filter"], dom["sort-filter"]]) {
    control.addEventListener("change", updateFilterFromForm);
  }
  for (const button of document.querySelectorAll(".view-button")) {
    button.addEventListener("click", () => switchView(button.dataset.view));
  }
  dom["zoom-in"].addEventListener("click", () => zoomAt(1.2));
  dom["zoom-out"].addEventListener("click", () => zoomAt(1 / 1.2));
  dom["fit-view"].addEventListener("click", () => fitGraph());
  dom["focus-selection"].addEventListener("click", () => {
    if (state.selectedId) focusNode(state.selectedId);
    else showFeedback("Select a node to focus");
  });
  dom["collapse-view"].addEventListener("click", collapseSelected);
  dom["simulator-toggle"].addEventListener("click", () => toggleSimulator());
  dom["simulator-play"].addEventListener("click", toggleSimulatorPlayback);
  dom["simulator-step"].addEventListener("click", advanceSimulator);
  dom["simulator-reset"].addEventListener("click", resetSimulator);
  dom["clear-selection"].addEventListener("click", clearSelection);
  setConnection("pending", "Connecting", "Opening bounded read-only routes…");
  const available = await loadSummaryAndEvidence();
  if (!available) {
    dom["node-list"].replaceChildren(el("div", "Summary is unavailable; additional API calls are disabled to avoid a misleading observatory.", "error-note"));
    dom["edge-layer"].replaceChildren();
    dom["node-layer"].replaceChildren();
    return;
  }
  dom["global-search"].setAttribute("data-ready", "true");
  try {
    await loadViewRoot();
  } catch (error) {
    setViewState("error", "error");
    dom["node-list"].replaceChildren(el("div", error.message, "error-note"));
    showFeedback(error.message, true, true);
  }
}

document.addEventListener("DOMContentLoaded", init, { once: true });
