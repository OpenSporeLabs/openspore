# RE Dossier Schema (re-dossier-1)

A dossier is a **bounded topic** — one behavior / function cluster of the
original — assembled only from committed evidence. It is the unit the
replacement gate (docs/BOUNDARIES.md, docs/replacement-status.json) reads.
Generator: `tools/re/dossier.py <topic>` → `docs/analysis/dossiers/<topic>.md`
(human) + `<topic>.json` (machine, this schema).

**Rule — decompiler output is EVIDENCE, NOT TRUTH.** SporeApp.exe has no MSVC
RTTI: Ghidra callee types are decompiler guesses (e.g. `ITextureManager*`
casts are not trusted). SDK symbol names are real (march2017 SDK XML import);
`FUN_*` names are Ghidra address autogen, not real names. Every decompiler-
sourced claim carries that label.

## Evidence labels (dossier vocabulary)

| Label | Meaning |
|---|---|
| OBSERVED | byte-level or runtime evidence only (disassembly, constants, traced calls) |
| VERIFIED | reproduced/differentially checked (e.g. SDK import, oracle match) |
| CONFIRMED | OBSERVED + independently corroborated (second source) |
| SUPPORTED | multiple consistent sources, no contradiction |
| INFERRED | reasoned from evidence, single source or untested |
| APPROXIMATION | best-effort value/behavior standing in for the real one |
| UNKNOWN | no evidence yet |

These mirror the lowercase vocabulary in `docs/replacement-status.json`
(`unknown, hypothesis, inferred, supported, verified, approximated`).

## Sections (JSON keys in `<>`)

```
RE Dossier
├── topic                    <topic>                 kebab-case behavior cluster name
├── evidence summary         <evidence_summary>      one paragraph, highest-confidence claims only
├── original functions       <functions>             name, RVA, module, size, namespace,
│                                                   signature, dispatch/vtable, evidence label
├── callers                  <callers>               per function (vtable-dispatched = none static)
├── callees                  <callees>               per function
├── strings / constants      <constants>             address + inferred meaning + evidence label
├── runtime observations     <runtime>               {obtained: bool, reason, traces_scanned,
│                                                   matched_events[{trace,T,args,return}]}
│                                                   NO trace ⇒ obtained=false + reason. NEVER fabricate.
├── resource references      <resource_refs>         exact type/group/instance IDs only;
│                                                   never invent human names for opaque IDs;
│                                                   presence confirmed against the DBPF index
├── asset relationships      <asset_relationships>   which records the behavior touches, with labels
├── hypotheses               <hypotheses>            falsifiable claims, each labeled
├── known unknowns           <known_unknowns>        what evidence is missing, and why
├── OpenSpore counterpart    <openspore_counterpart> which OpenSpore file/function approximates
│                                                   this, and how faithfully (label)
└── replacement readiness    <replacement_readiness> {status, gate, missing_evidence}
```

## Generation rules
- Inputs are committed files only (Ghidra snapshot JSON, vtable scan,
  knowledge graph, DBPF index, Observatory traces). No live Ghidra server.
- Idempotent: same inputs ⇒ byte-identical output (no timestamps).
- Absent optional inputs (no `SPORE/`, no trace) degrade to explicit records
  (`resource_refs: []` + note; `runtime.obtained=false` + reason) — never
  failure, never fabrication.
