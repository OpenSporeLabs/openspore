#!/usr/bin/env python3
"""Lightweight read-only web viewer for the OpenSpore knowledge graph.

A single small stdlib-only process: ``http.server.ThreadingHTTPServer`` on
loopback (default 127.0.0.1:8787). Serves the static shell plus explicit
JSON API routes backed by tools/viewer/query.py. Every request opens a fresh
read-only DB connection and closes it after the response.

Safety:
  * --bind is validated against {127.0.0.1, ::1}; anything else is refused;
  * static serving is a fixed name map + realpath containment check
    (no traversal, no arbitrary filesystem reads, no SPORE/ access);
  * no POST/PUT/DELETE write handlers; the DB is never written;
  * all logging goes to stderr; unknown paths return a JSON 404 and the
    server stays alive.

Run from the repo root:
    python3 tools/viewer/server.py --port 8787
"""
import argparse
import json
import os
import sys
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import unquote, urlsplit

_HERE = os.path.dirname(os.path.abspath(__file__))
_ROOT = os.path.dirname(os.path.dirname(_HERE))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

from tools.viewer import query  # noqa: E402

STATIC_DIR = os.path.realpath(os.path.join(_HERE, "static"))
_STATIC = {"index.html": "text/html; charset=utf-8",
           "viewer.js": "text/javascript; charset=utf-8",
           "viewer.css": "text/css; charset=utf-8"}


def validate_bind(host):
    """(ok, message): the viewer is loopback-only, full stop."""
    if host in ("127.0.0.1", "::1"):
        return True, ""
    return False, ("refusing non-loopback bind %r: the viewer is "
                   "loopback-only (127.0.0.1 or ::1)" % host)


class ViewerHandler(BaseHTTPRequestHandler):
    server_version = "OpenSporeViewer/0.1"
    db_path = None

    def log_message(self, fmt, *args):  # stderr only, compact.
        sys.stderr.write("[viewer] %s %s\n"
                         % (self.address_string(), fmt % args))

    # -- helpers ---------------------------------------------------------- #
    def _send_bytes(self, code, body, content_type):
        self.send_response(code)
        self.send_header("Content-Type", content_type)
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def _send_json(self, obj, code=200):
        # No sort_keys: dict order is deterministic by construction and
        # carries meaning (e.g. evidence levels follow EV_ORDER).
        self._send_bytes(code, json.dumps(obj).encode("utf-8"),
                         "application/json; charset=utf-8")

    def _static(self, name):
        if name not in _STATIC:
            return self._send_json(
                {"status": "error", "code": 404,
                 "message": "unknown static asset %r" % name}, 404)
        full = os.path.realpath(os.path.join(STATIC_DIR, name))
        if os.path.commonpath([STATIC_DIR, full]) != STATIC_DIR:
            return self._send_json(
                {"status": "error", "code": 404,
                 "message": "path escapes static dir"}, 404)
        try:
            with open(full, "rb") as fh:
                self._send_bytes(200, fh.read(), _STATIC[name])
        except OSError:
            self._send_json({"status": "error", "code": 503,
                             "message": "static asset missing: %s" % name},
                            503)

    # -- routes ----------------------------------------------------------- #
    def _api(self, path, qs):
        if path == "/api/summary":
            return query.summary(self.db_path)
        if path == "/api/evidence":
            return query.evidence_distribution(self.db_path)
        if path == "/api/labels":
            return query.node_label_distribution(self.db_path)
        if path == "/api/investigations":
            return query.investigation_status_distribution(self.db_path)
        if path == "/api/investigation-list":
            keys = qs.get("keys", [None])[0]
            if keys is not None:  # bounded page-join lookup
                return query.investigations_by_keys(
                    keys.split(","), self.db_path)
            return query.investigations_list(
                kind=qs.get("kind", [None])[0],
                q=qs.get("q", [None])[0],
                status=qs.get("status", [None])[0],
                limit=qs.get("limit", ["200"])[0],
                offset=qs.get("offset", ["0"])[0])
        if path == "/api/subsystems":
            return query.subsystem_summary(self.db_path)
        if path == "/api/nodes":
            return query.nodes(
                label=qs.get("label", [None])[0],
                q=qs.get("q", [None])[0],
                limit=qs.get("limit", ["200"])[0],
                offset=qs.get("offset", ["0"])[0])
        if path.startswith("/api/node/") and path.endswith("/neighbors"):
            ref = unquote(path[len("/api/node/"):-len("/neighbors")])
            try:
                depth = int(qs.get("depth", ["1"])[0])
            except ValueError:
                depth = "bad"  # query.node_neighbors rejects it
            return query.node_neighbors(ref, depth, self.db_path)
        if path.startswith("/api/node/"):
            return query.node_detail(unquote(path[len("/api/node/"):]),
                                     self.db_path)
        if path.startswith("/api/investigation/"):
            return query.investigation_detail(
                unquote(path[len("/api/investigation/"):]), self.db_path)
        return None

    def do_GET(self):
        parts = urlsplit(self.path)
        path = unquote(parts.path)
        qs = {}
        for pair in parts.query.split("&"):
            if not pair:
                continue
            key, _, value = pair.partition("=")
            qs.setdefault(unquote(key), []).append(unquote(value))
        try:
            if path == "/":
                return self._static("index.html")
            if path.startswith("/static/"):
                return self._static(path[len("/static/"):])
            env = self._api(path, qs)
            if env is None:
                return self._send_json(
                    {"status": "error", "code": 404,
                     "message": "unknown path %r" % path}, 404)
            code = self._status_code(env)
            return self._send_json(env, code)
        except Exception as exc:  # never crash a worker; stay alive.
            self.log_message("handler error: %r" % (exc,))
            return self._send_json(
                {"status": "error", "code": 500,
                 "message": "internal error: %s" % type(exc).__name__}, 500)

    @staticmethod
    def _status_code(env):
        if env.get("status") in ("ok", "degraded"):
            return 200  # degraded = banner, not a failure
        if env.get("code") in ("not_found", "db_missing"):
            return 404
        return 400

    def _method_not_allowed(self):
        self._send_json({"status": "error", "code": 405,
                         "message": "read-only server: no write methods"}, 405)

    do_POST = _method_not_allowed
    do_PUT = _method_not_allowed
    do_DELETE = _method_not_allowed


def make_server(host, port, db_arg=None):
    ok, msg = validate_bind(host)
    if not ok:
        raise SystemExit(msg)
    db = query.db_path(db_arg)

    class BoundHandler(ViewerHandler):
        db_path = db

    srv = ThreadingHTTPServer((host, port), BoundHandler)
    srv.daemon_threads = True
    return srv


def main(argv=None):
    ap = argparse.ArgumentParser(
        description="Read-only loopback web viewer for the knowledge graph.")
    ap.add_argument("--bind", default="127.0.0.1",
                    help="loopback only: 127.0.0.1 or ::1 (default)")
    ap.add_argument("--port", type=int, default=8787)
    ap.add_argument("--db", default=None,
                    help="DB path (abs, or rel vs repo root; OPENSPORE_DB wins)")
    args = ap.parse_args(argv)
    ok, msg = validate_bind(args.bind)
    if not ok:
        print(msg, file=sys.stderr)
        return 2
    srv = make_server(args.bind, args.port, args.db)
    print("[viewer] serving on http://%s:%d (db=%s)"
          % (args.bind, args.port, query.db_path(args.db)), file=sys.stderr)
    try:
        srv.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        srv.server_close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
