"""OpenSpore MCP server: stdlib-only JSON-RPC 2.0 over stdio.

Subpackages:
  config   -- repo-root resolution, path helpers, sha256 helper.
  registry -- the 24 tool schemas plus the dispatch table.
  server   -- the stdio JSON-RPC loop (protocol on stdout, logs on stderr).

No third-party dependencies. Later subagents add safety.py, cache.py and
the real tool implementations behind the stub handlers in registry.py.
"""
