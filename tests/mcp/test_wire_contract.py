"""Wire-contract test for the GhidraMCP REST client (no mocks of the
client itself).

Starts a local ThreadingHTTPServer stub on 127.0.0.1 that replays the
REAL headless GhidraMCP bridge contract (verified live, 2026-09-22):

  (a) /search_functions?name_pattern=cCell&limit=3
      -> {"functions": [...3...], "count": 3, "offset": 0,
          "limit": 3, "total": 27}          (no top-level "status")
  (b) /search_functions?pattern=cCell        (the old broken client
      shape: bridge binds name_pattern only from the query, so the
      term arrives empty)
      -> {"error": "Search term is required"}

The stub records every request's path + query string.  The REAL
GhidraClient then talks HTTP to it, which pins:

  F-1  the client sends ``name_pattern`` (and ``limit``) in the query
       string, never ``pattern``;
  F-2  a bridge ``{"error": ...}`` payload (no "status") surfaces as
       ``status=error`` / ``code=ghidra_rest_error`` / ``message=<text>``
       at the client, and as ``mode=live`` with NO ``search_status`` at
       the ghidra_search tool (never ``matched_zero``);
  -    payloads that DO carry a "status" key pass through untouched.

Run from the repo root:
    python3 -m unittest tests.mcp.test_wire_contract -v
"""
import json
import threading
import unittest
import urllib.parse
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

from tools.mcp import ghidra_client, ghidra_tools as gt

# Bridge-shaped fixture (live contract, ListingService.searchFunctionsByName):
# matches are "Name @ address" strings, response has no "status" key.
_CELL_MATCHES = [
    "cCell::Move @ 0045a1f0",
    "cCell::MoveTowards @ 0045a3a0",
    "cCell::SetMoveSpeed @ 0045a910",
]
_BRIDGE_REJECT = {"error": "Search term is required"}


def _bridge_reply(path, query):
    """Replay the real bridge's answer for (path, flat query dict)."""
    if path == "/search_functions":
        term = query.get("name_pattern", "")
        if term == "":
            # The bridge never saw a term (empty name_pattern, including
            # the old broken pattern= shape): it rejects the request.
            return dict(_BRIDGE_REJECT)
        if term == "REJECT":
            # Simulates any other bridge-level refusal of a well-formed
            # query (e.g. a malformed program name).
            return dict(_BRIDGE_REJECT)
        try:
            limit = int(query.get("limit", "100"))
        except ValueError:
            limit = 100
        if limit <= 0:
            limit = len(_CELL_MATCHES)
        page = _CELL_MATCHES[:limit]
        return {"functions": list(page), "count": len(page),
                "offset": 0, "limit": len(page), "total": 27}
    if path == "/get_metadata":
        # Status-bearing payloads pass through the client untouched.
        return {"status": "ok", "program": "SporeApp.exe",
                "ghidra_version": "12.1.2"}
    return {"error": "unknown endpoint"}


class _StubHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parts = urllib.parse.urlsplit(self.path)
        flat = {k: v[0] for k, v in urllib.parse.parse_qs(parts.query).items()}
        self.server.requests.append(
            {"method": "GET", "path": parts.path, "query": flat})
        payload = json.dumps(_bridge_reply(parts.path, flat)).encode("utf-8")
        self.send_response(200)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(payload)))
        self.end_headers()
        self.wfile.write(payload)

    def log_message(self, fmt, *args):
        pass


class TestWireContract(unittest.TestCase):
    """Real GhidraClient -> local HTTP stub replaying the live bridge."""

    @classmethod
    def setUpClass(cls):
        cls.srv = ThreadingHTTPServer(("127.0.0.1", 0), _StubHandler)
        cls.srv.requests = []
        cls.port = cls.srv.server_address[1]
        cls._thread = threading.Thread(target=cls.srv.serve_forever,
                                       name="ghidra-stub", daemon=True)
        cls._thread.start()
        cls._old_factory = gt._CLIENT_FACTORY
        gt._CLIENT_FACTORY = lambda: ghidra_client.GhidraClient(
            host="127.0.0.1", port=cls.port)

    @classmethod
    def tearDownClass(cls):
        gt._CLIENT_FACTORY = cls._old_factory
        cls.srv.shutdown()
        cls.srv.server_close()
        cls._thread.join(timeout=2)

    def _client(self):
        return ghidra_client.GhidraClient(host="127.0.0.1", port=self.port)

    def _search_calls(self):
        return [r for r in self.srv.requests
                if r["path"] == "/search_functions"]

    # -- F-1: wire shape of the search request ----------------------------

    def test_search_sends_name_pattern_in_query_not_pattern(self):
        res = gt.ghidra_search({"pattern": "cCell", "limit": 3})
        self.assertEqual(res.get("status"), "ok", res)
        self.assertEqual(res.get("search_status"), "matched", res)
        self.assertEqual(res.get("count"), 3, res)
        calls = self._search_calls()
        self.assertTrue(calls, "client never called /search_functions")
        query = calls[-1]["query"]
        self.assertEqual(query.get("name_pattern"), "cCell",
                         "query must bind name_pattern: %r" % query)
        self.assertNotIn("pattern", query,
                         "old param name leaked onto the wire: %r" % query)
        self.assertEqual(query.get("limit"), "3",
                         "limit must ride the query string: %r" % query)

    def test_search_match_entries_come_from_bridge_page(self):
        res = gt.ghidra_search({"pattern": "cCell", "limit": 2})
        self.assertEqual(res.get("search_status"), "matched", res)
        self.assertEqual(res.get("count"), 2, res)
        self.assertEqual([m["name"] for m in res.get("matches", [])],
                         _CELL_MATCHES[:2], res)

    # -- F-2: bridge {"error": ...} payloads (no "status") ----------------

    def test_client_maps_bridge_error_to_ghidra_rest_error(self):
        # The old broken wire shape (pattern=... only): the bridge never
        # receives a term and answers {"error": ...} with no "status".
        res = self._client().request("/search_functions",
                                     {"pattern": "cCell"})
        self.assertEqual(res.get("status"), "error", res)
        self.assertIs(res.get("ok"), False, res)
        self.assertEqual(res.get("code"), "ghidra_rest_error", res)
        self.assertEqual(res.get("message"), "Search term is required", res)

    def test_tool_level_bridge_rejection_is_live_not_matched_zero(self):
        # Well-formed query, bridge refuses: mode=live, no search_status
        # at all (definitely not matched_zero, which means a real search
        # ran and found nothing).
        res = gt.ghidra_search({"pattern": "REJECT"})
        self.assertEqual(res.get("status"), "error", res)
        self.assertEqual(res.get("code"), "ghidra_rest_error", res)
        self.assertEqual(res.get("mode"), "live", res)
        self.assertNotIn("search_status", res,
                         "bridge rejection is not matched_zero: %r" % res)

    # -- no-regression: status-bearing payloads pass through untouched -----

    def test_status_payload_passes_through_unwrapped(self):
        res = self._client().get_metadata()
        self.assertEqual(res.get("status"), "ok", res)
        self.assertEqual(res.get("program"), "SporeApp.exe", res)
        self.assertNotIn("data", res,
                         "status-bearing payload must not be re-wrapped: %r"
                         % res)


if __name__ == "__main__":
    unittest.main()
