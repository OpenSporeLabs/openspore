# pdtk-text-widget — FUN_00a4e9c0

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00a4e9c0 / 0x0064e9c0 |
| symbol | FUN_00a4e9c0 (sdk: —) |
| subsystem | UTFWin |
| category | ENGINE_IMPLEMENTATION |
| priority | P3 |
| evidence | SUPPORTED |
| size | 2415 B |
| replacement candidate | partial (recon-relevant: 1) |

## Purpose

pdtk text widget create/update: wraps text into lines, sizes widget, syncs via pdtk commands (pdtk_text_new, select, focus, icursor); blue/black selection colors

## Inputs / outputs

- in: widget ptr, text, font, size mode (0=skip,1=create,2=update)
- out: *param_2/3 new w/h
- out: *param_4 cursor

## State (read / write)

- read: font descriptor (+0x1e)
- read: DAT_01675490 font sentinel
- write: widget w/h fields

## Structs / fields

- (none named)

## Decompilation evidence

```
wraps text into lines (\n + trailing-space trim), computes new w/h, syncs via pdtk commands: "pdtk_text_new .x%lx.c %s %f %f {%.*s} %d %s" (create, param_1==1) or resize + "select from/to/clear", "focus", "icursor" (param_1==2; 0 skips); selection colors "blue"/"black"; *param_2/3=new size, *param_4=cursor; font descriptor +0x1e flags; DAT_01675490 font sentinel.
```

## Callers

- 00a4e190
- 00a4e1e0
- 00a4e460
- 00a4f120
- 00a4f380

## Key callees

- 00a4d340
- 00a4c740
- 00a4c690
- 00a4d410

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

The UTFWin pdtk text-widget sync: wraps text into lines, sizes the widget, and drives the runtime UI toolkit through constructed pdtk command strings (pdtk_text_new / select / focus / icursor) with blue/black selection colors. 5 callers in the 00a4e190..00a4f380 region. Engine implementation (UTFWin), not gameplay. The pdtk command grammar is a runtime toolkit interface with no SDK symbols - that is the main unknown. Replacement partial: the widget-side logic is readable; the pdtk command set must be re-specified from the observed strings, not from any SDK.

## Uncertainty / open questions

- pdtk command grammar (runtime UI toolkit; no SDK symbols)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00a4e9c0 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00a4e9c0.c (session artifact, not committed)
