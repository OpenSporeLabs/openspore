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
python3 tools/spore/asset_resolver.py <file> [--typeinfo|--map|--type 0x..|--group 0x..|--record T:G:I|--near G I]
```

## Layout

```
tools/spore/
  dbpf/dbpf.py        DBPF v3 container reader + QFS (RefPack) decompression
  rw4/rw4.py          RW4 container: header, manifest, type codes, sections
  gmdl/gmdl.py        GMDL GameModel (RenderAsset 0xE6BCE5) full-layout parser
  types/typenames.json  canonical typeID -> name map (SDK-sourced + prop map)
  types/groupnames.json SDK groupID -> name map (CommonIDs.h)
  typescan.py         per-package type histogram with decoded names
  asset_resolver.py   record-level resolver: type/group/instance lookup + names
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

## asset_resolver.py

Resolves individual DBPF records to `(type_id, type_name, group_id, group_name,
instance_id, size, offset, stage, category)`. Names come from
`types/typenames.json` and `types/groupnames.json`.

Commands:

- `--typeinfo` — type histogram with decoded names.
- `--type 0x...` — list all records of a given type.
- `--group 0x...` — list all records in a given group.
- `--record T:G:I` — look up a specific record (all hex, colon-separated).
- `--near GROUP INST --near-count N` — find records with the same group and
  nearby instance IDs, plus same-type records in nearby groups.
- `--map` — dump the full type and group name maps.
- `--json` — JSON output for any of the above.

Example:

```bash
python3 tools/spore/asset_resolver.py SPORE/Data/Spore_Content.package \
    --record 0x00E6BCE5:0x40637E02:0x067A0801 --json
```

## Legal note

Analysis-only reimplementation. Never commit EA assets, decompiled source, or
any `SPORE/` contents. `out/` and everything under `SPORE/` are git-ignored.
