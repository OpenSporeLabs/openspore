"""OpenSpore asset-format tooling.

Clean-room, stdlib-only readers for Spore (RenderWare 4 / DBPF) asset formats.
Each tool lives in its own sub-package and can be run directly as a script:

    python3 tools/spore/dbpf/dbpf.py --out out <file> list
    python3 tools/spore/rw4/rw4.py <file>
    python3 tools/spore/gmdl/gmdl.py inspect <file>

No third-party dependencies. See tools/spore/README.md.
"""
