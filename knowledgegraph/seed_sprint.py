#!/usr/bin/env python3
"""DEPRECATED — forward-only shim to knowledgegraph/seed.py.

The hand-written literal seed (Objective 10 sprint) is replaced by the
canonical, byte-deterministic generator ``seed.py``
(docs/RE-AUTOMATION-ARCHITECTURE.md §5; SCALABILITY row #5). This module
exists only so pre-existing invocations (``seed_sprint.py init`` /
``seed_sprint.py seed``) keep working; it forwards to ``seed.py``.

Run the real generator directly:
    python3 knowledgegraph/seed.py [--db PATH] [--dry-run] [--build-agnostic]
"""
import sys

import seed


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    # The old {init, seed} subcommands both meant "build the full seed".
    if argv and argv[0] not in ("init", "seed"):
        seed.main(argv)  # passthrough of any unrecognized flag
        return
    seed.main([])  # canonical full seed


if __name__ == "__main__":
    main()
