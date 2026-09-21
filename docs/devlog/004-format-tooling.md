# 004 — Format tooling: from /tmp to first-class

## 2026-09-20, evening (commit `8a2caf5`, 18:23)

State of play: the RenderWare research report ([chapter 003](003-renderware-research.md))
had landed about an hour earlier at 17:29 (commit `36e704a`), with the DBPF, RW4 and
GMDL formats validated by throwaway parsers developed in `/tmp/opencode/spore/` —
scratch code that worked, but lived outside the repository and would vanish on the next
reboot. The decision of the evening, taken at 18:23, was to promote those parsers into
the repository as first-class tooling: directly-runnable scripts, stdlib-only, with
clean CLIs and no third-party dependencies. That promotion is commit `8a2caf5`,
"Promote DBPF/RW4/GMDL asset tooling into tools/spore/ with clean CLIs" — 8 files,
633 insertions, zero deletions.

## Why format tooling matters to a clean-room reimplementation

This was not a housekeeping step. A from-scratch reimplementation of a 5 GB asset
pipeline needs reference implementations of every container it will ever touch, and the
reasoning went in five directions at once:

- **Every downstream consumer needs a trusted reference.** The later C++ asset
  loaders, the differential tests, and the knowledge graph all read Spore packages.
  If each of them re-derives the container layout independently, every one of them can
  be subtly wrong in a different way, and there is no arbiter. One committed,
  executable reference per format is the single source of truth the whole rest of the
  project can lean on.
- **A parser that walks a real file to the exact end is a format specification.**
  The GMDL module docstring, for example, carries the complete field layout of the
  GameModel asset — every field, its offset arithmetic, its size, and every assumption
  (like the `unk` u32 observed as 0). Documenting that in prose alone would mean
  maintaining a second copy of the truth; here the layout exists exactly once, in
  executable form, and the walk-to-end behavior is what keeps it honest.
- **`tools/` is the regression surface.** When a C++ port of a parser is written later,
  the Python tool is the oracle it is diffed against, field by field. That comparison
  is only possible if the Python side is stable, committed, and reproducible — not
  ephemeral `/tmp` code.
- **Stdlib-only means runnable anywhere.** No `pip install`, no venv, no package
  manager. The same script runs in CI, on another machine, and in another agent's
  session. That property is what lets the knowledge graph and the test suite call the
  tools as plain subprocesses.
- **Promotion ends the ephemerality problem.** `/tmp` is wiped; the repository is not.
  Every format fact that had been established during the research phase now has a
  permanent, auditable home, and the legal boundary is explicit in the README: the tools
  are analysis-only, and `SPORE/` contents never enter the repository.

The shape of the result:

```
SPORE/Data/*.package  (git-ignored, real GOG install, ~5 GB, 7 packages)
        |
        v
dbpf.py  ----  index walk + QFS/RefPack decompress  ---->  out/ records (git-ignored)
        |                                                     |
        |        typescan.py: type histogram + name map       |
        v                                                     v
rw4.py  <----  RW4 envelope  <----  rw4 records    gmdl.py  <----  gmdl records
 (structural summary per section)                    (walk-to-end; exit code 0/1)
```

## What landed

Commit `8a2caf5` added the `tools/spore/` tree (633 lines, all new) plus two
`.gitignore` entries (`__pycache__/`, `*.pyc`) so that running the tools in place
does not pollute the repository:

```
tools/spore/
  README.md           usage, layout, legal note
  __init__.py         package docstring (what these tools are and how to run them)
  dbpf/dbpf.py        DBPF v3 container reader + QFS (RefPack) decompression
  rw4/rw4.py          RW4 container: header, manifest, type codes, sections
  gmdl/gmdl.py        GMDL GameModel (RenderAsset 0xE6BCE5) full-layout parser
  types/typenames.json  canonical typeID -> name map
  typescan.py         per-package type histogram with decoded names
```

**dbpf.py (178 lines)** — the DBPF v3 reader. The 96-byte header is documented in the
module docstring (magic `DBPF`/`DBBF`, major=3 minor=0, index minor=3, no name table,
32-bit binary IDs that are FNV-1a hashes of the asset names), and the index record
layout too: `instance/group/type` IDs, chunk offset, compressed size (bit 31 set),
memory size, and the two-byte compression flag where `0xFFFF` means QFS/RefPack.
QFS is the non-trivial part: a 5-byte header (`0x10FB`/`0x50FB` plus a 3-byte
big-endian decompressed size) and LZ-style control bytes — it is *not* zlib. The
command surface: `exts` (histogram of 4CC type codes), `list` (every index record:
type/group/instance/offset/sizes/comp flag, with pattern filtering), `get` (extract
record `idx`, decompressing if the comp flag is set, into `--out`), `find` (search by
4CC/group/instance), `dumpdir` (locate and dump the directory prop record, identified
by group==instance==`0x1C7AC81` — the record that carries the package's own type-name
map), and `decompress` (run the QFS path on one record).

**rw4.py (64 lines)** — the RW4 envelope. It checks the 28-byte magic
(`\x89RW4w32\0\r\n\x1a\x0a` + 16 bytes), then the file type code, object/section
counts, the `SectionManifest` (type code `0x10004`, at offset 0x98), the `SectionTypes`
list (`0x10005`), and each 24-byte section info record (type code, size, alignment,
data pointer, base-resource indirection for `0x10030` sections). It prints a full
structural summary per file — type-code names included from a built-in map of ~30
RenderWare section types, with the undocumented Spore-specific `0x2000b`/`0x7000b`
codes left visible as raw hex.

**gmdl.py (272 lines)** — the full byte-layout parser for the GMDL GameModel render
asset (version ≤ 9). The module docstring carries the complete field layout, from
`version`/`refCount` through bounding box, index buffers, vertex descriptors
(12-byte `RWVertexElement` structs), vertex buffers, mesh bindings, material info
(including the `ShaderData::getDataSize` skip table for non-texture-set entries),
bone ranges, animation data, and a trailing `unknownKey`. `inspect` prints a human
summary; `dump` prints the raw section walk with offsets. The parser is its own
validator: the exit code is 0 on a clean walk to file end, 1 on a size mismatch
(`gmdl.py:269`), which turns "we think we know the layout" into a machine-checkable
claim. The docstring records the verification status: "Verified against real
version-8 samples (parse walks to the exact file size)".

**typescan.py (40 lines)** — per-package type histogram. The names are not guessed:
they come from the package's own `0x1C7AC81` prop record (the type-name map stored
inside every package), merged with the canonical `types/typenames.json` map.

**types/typenames.json** — the canonical typeID→name map, 21 entries (jpeg, png, bem,
crt, bld, vcl, ufo, flr, prop, gmdl, raster, plt, hm, summary, summary_pill,
creature_traits, building_traits, vehicle_traits, trait_pill, pollen_metadata, gmsh).
The keys are the FNV-1a type IDs from the research report's type table, stored as
decimal strings. This file is the semantic vocabulary of the asset pipeline — derived
from the SDK structures and the packages' own prop records, not from any proprietary
content.

## Validation against Spore data

"Real validation" here meant running the parsers against the actual GOG install's
packages — `SPORE/Data`, git-ignored, never committed — and checking that the tools
survive the full ~5 GB of real content:

- **Per-package type histograms** via `typescan.py`. For `Spore_Graphics` this
  measured: rw4 ×9368, png ×8360, prop ×3761, gmsh ×2422 — plus type IDs not in the
  canonical map, notably the undocumented `0x250FE9A2` ×394, which the tool reports
  with a `?` name rather than failing. The histogram is how we see the long tail of
  unclassified types.
- **Record extraction** via `dbpf.py get` — individual records pulled out of packages,
  QFS-decompressed where the comp flag was set, written into `tools/spore/out/`
  (git-ignored). Extracting records and then parsing them with rw4.py/gmdl.py is what
  proved the three tools agree with each other on real data, not just on hand-crafted
  samples.
- **GMDL walk-to-end** on real version-8 samples: the parse walked to the exact file
  size (exit code 0), which is the verification the module docstring claims.

The data boundary was deliberate and is documented in `tools/spore/README.md`: the
packages never enter the repository. What *is* committed is the tools themselves, the
type-name map (semantic vocabulary), and — in the follow-up commit — the extracted
samples stayed in git-ignored `out/` directories. The one semantic snapshot of a real
record that does get committed (a field-only JSON of one small GMDL record) lives in
`tests/` and is covered in [chapter 005](005-deterministic-tests.md).

## Bugs found and corrected

The `8a2caf5` diff is purely additive — 633 insertions, 0 deletions — so the promoted
files landed exactly as they stood in `/tmp/opencode/spore/`, with no in-commit code
changes to the parsers themselves. The small follow-up that did touch the tools landed
in the *next* commit, `9f073dd` (18:59, 36 minutes later), when the test suite started
importing them as modules: each of dbpf.py, gmdl.py and rw4.py replaced
`x = open(path, 'rb').read()` with a `with open(path, 'rb') as f:` block (+2/−1 per
file, 3 lines deleted in total). That is file-handle hygiene — deterministic closing of
handles so the tools behave identically whether run as scripts or imported — not an
argument-handling change, and the diff verifies nothing further than that; we do not
claim any additional parser bugs were fixed during promotion. What the promotion
*did* add as a first-class contract is the gmdl exit code (0 clean / 1 mismatch),
which converts a size drift during a walk from a silent assumption into a
machine-checkable signal that later tooling can assert on.

### Outcome

| | |
|---|---|
| **Proven** | Tools committed to `tools/spore/` (8 files, 633 L), directly runnable, stdlib-only |
| | Validated on the real GOG packages (histograms, extraction to git-ignored `out/`, QFS decompression on real records) |
| | GMDL v8 samples walked to exact file size (exit 0); exit-code contract 0/1 is machine-checkable |
| | Data boundary held: `SPORE/` and `out/` git-ignored; only tools + semantic vocabulary committed |
| **Open** | RW section type codes `0x2000b` / `0x7000b` remain undocumented (Spore-specific) |
| | Undocumented type IDs (e.g. `0x250FE9A2` ×394 in Spore_Graphics) remain unclassified |
| | The Python tools are the reference oracle — the C++ ports they will be diffed against are not started yet |

Next: the test suite that pins these tools down — fixtures, semantic snapshots, and
the opt-in real-asset differential — is [chapter 005](005-deterministic-tests.md).
