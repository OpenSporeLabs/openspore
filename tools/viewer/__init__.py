"""OpenSpore knowledge-graph viewer: read-only loopback web dashboard.

Submodules:
  query  -- parameterized read-only SQL over knowledgegraph/spore.db.
  server -- stdlib http.server serving the static shell + JSON API.

No third-party dependencies; the DB is opened read-only per request.
"""
