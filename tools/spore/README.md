# Spore asset-format tools

Clean-room, from-scratch, **stdlib-only** Python readers for Spore asset formats.
No third-party dependencies. These are reverse-engineered *by analysis* — they
contain no EA code and no proprietary assets.

Every tool is a directly-runnable script:

```bash
python3 tools/spore/dbpf/dbpf.py  <file> [exts|list <pat>|get <idx>|find <pat>|dumpdir|decompress <idx>]
python3 tools/spore/rw4/rw4.py    <file> [<file> ...]
python3 tools/spore/gmdl/gmdl.py  <inspect|dump> <file>
python3 tools/spore/typescan.py   <file> [<file> ...]
```

## Layout

```
tools/spore/
  dbpf/dbpf.py        DBPF v3 container reader + QFS (RefPack) decompression
  rw4/rw4.py          RW4 container: header, manifest, type codes, sections
  gmdl/gmdl.py        GMDL GameModel (RenderAsset 0xE6BCE5) full-layout parser
  types/typenames.json  canonical typeID -> name map (from the 0x1C7AC81 prop map)
  typescan.py         per-package type histogram with decoded names
```

## dbpf.py

Reads a Spore `.package` (DBPF v3, little- or big-endian `DBPF`/`DBBF`).

Commands:

- `exts` — histogram of 4CC type codes in the package.
- `list [pat]` — list every index record (type, group, instance, offset, sizes, comp flag).
- `get <idx>` — extract record `idx` (QFS-decompressing if compressed) into `--out`.
- `find [pat]` — search records by 4CC / group / instance, print matches.
- `dumpdir` — locate and dump the directory prop record (group==inst==0x1C7AC81).
- `decompress <idx>` — run the QFS decompression path on record `idx`, write to `--out`.

`--out DIR` sets the extraction directory (default `<tools/spore>/out/`, git-ignored).

## rw4.py

Parses the RW4 container envelope: 28-byte magic, object/section counts, the
`SectionManifest`, the `SectionTypes` type-code list, and each section info
(type, size, alignment, data pointer). Prints a full structural summary per file.

## gmdl.py

Full byte-layout parser for the GMDL `GameModel` render asset (version ≤ 9).
Verified against real version-8 samples (parse walks to the exact file size).
`inspect` prints a human summary; `dump` prints the raw section walk with
offsets. Exit code is 0 on a clean match, 1 on a size mismatch.

See the module docstring for the complete field layout.

## typescan.py

Prints a per-package type histogram. Names come from the package's own
0x1C7AC81 prop record merged with the canonical `types/typenames.json` map.

## Legal note

Analysis-only reimplementation. Never commit EA assets, decompiled source, or
any `SPORE/` contents. `out/` and everything under `SPORE/` are git-ignored.
