# Reconstruction context 0x006a2a80

- Status: `partial`
- Content SHA-256: `f6b9a4ff38008bdd5cabcca5207277c68b085d669ea3f6da3bdaf1b4f31eb42d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a2a80",
  "phase": "reconstruction",
  "target": "0x006a2a80"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::PropertyList::Clear",
  "package": "pkg-property-clear-wave13",
  "subsystem": "App",
  "va": "0x006a2a80"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "20a297619332bbfefe69949cb6741de471c7c548c99e92ba32d02df506fd6c3f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a2a80 failed: Decompilation did not complete. Reason: ",
      "mode": "LIVE",
      "status": "unavailable"
    }
  ],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "ordinary_stack_arguments": [],
  "ret_form": "RET",
  "return_register": "none",
  "return_type": "void",
  "stack_cleanup_bytes": 0
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x006a2a92",
      "direction": "out",
      "other": "0x00612b20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2aa1",
      "direction": "out",
      "other": "0x00685a30",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "PropertyList",
    "void"
  ],
  "vtables": [
    "vtable:0x01408820"
  ]
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408820 is a runtime gate.",
      "The meaning of the element type and of the flag words the release and copy helpers test cannot be recovered from this body; only the traversal stride is claimed.",
      "The real body of 0x00612b20 is not reproduced here. It has now been read, and at this call site the pushed range is degenerate (the end cursor is pushed twice), so the port's contract is exactly the observed degenerate return of the third word, the begin cursor. The general non-empty movement path stays unmodelled.",
      "The real body of 0x00685a30 is not reproduced here. It has now been read, and the port reproduces its unsigned 0x18-stride traversal but not the per-entry `TEST byte ptr [ESI + 0x14],0x4` release of 0x0093db80, which is out of scope for this record.",
      "The semantic identity of the counter word at receiver+0x34 is unknown. Only the unconditional increment is claimed; its initial value and its readers are not observable here."
    ],
    "validated": 0
  },
  "semantic": {}
}
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006a2a92",
      "direction": "out",
      "other": "0x00612b20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2aa1",
      "direction": "out",
      "other": "0x00685a30",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0212",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "pkg-app-proplist-copyall-wave16",
    "score": 12,
    "symbol": "all_copy_from_properties_006a14d0",
    "va": "0x006a14d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "pkg-proplist-dispatch-wave14",
    "score": 12,
    "symbol": "app_property_list_add_all_properties_from_006a1510",
    "va": "0x006a1510"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "pkg-dfw-006a1540",
    "score": 12,
    "symbol": "proplist_write_006a1540",
    "va": "0x006a1540"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "pkg-property-remove-006a2ef0",
    "score": 12,
    "symbol": "property_list_remove_property_006a2ef0",
    "va": "0x006a2ef0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "pkg-dfw-006a2e20",
    "score": 10,
    "symbol": "dfw_property_set_006a2e20",
    "va": "0x006a2e20"
  },
  {
    "match_basis": [
      "shared_types:PropertyList",
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 9,
    "symbol": "property_list_copy_from_006a2a40",
    "va": "0x006a2a40"
  },
  {
    "mat
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Clear.c",
  "file": "src/reconstruction/pkg_property_clear_wave13/006a2a80_property_list_clear.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Clear.c",
    "reconstruction/staging/pkg-property-clear-wave13/006a2a80_property_list_clear.cpp",
    "src/reconstruction/pkg_property_clear_wave13/006a2a80_property_list_clear.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-property-clear-wave13/006a2a80.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "Identity and initial value of the counter word at receiver+0x34 and its readers elsewhere in the binary.",
    "No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408820 is a runtime gate.",
    "The concrete layout of the 0x18 entry. What is observable from the two callees is a dword at +0x00 and a sub-object at +0x04 spanning to the 0x18 stride boundary, carrying a flag word at its +0x10 and a count word at its +0x12. That is a callee-derived shape, not a claim about 0x006a2a80, and the candidate still declares the element type incomplete.",
    "The concrete layout of the receiver between offsets 0x00 and 0x17 and between 0x20 and 0x33, which this body never touches.",
    "The general (non-degenerate) arm of 0x00612b20, now read but not ported: per element it writes the dword at +0x00 inline and thiscall-calls 0x00542b80 with ECX = out_element+0x4 and the source's +0x4 pushed, so each 0x18 entry is a four-dword block plus two flag words copied with flag-dependent side effects rather than a flat memcpy. Only the degenerate return observed at this call site is claimed here.",
    "The identity of the receiver words at 0x18, 0x1c and 0x34. The machine-derived receiver record is bounds_only and enumerates displacements, not members, so the candidate deliberately names none. A struct layout naming these words requires a source outside this body (the SDK header, or a writer elsewhere in the binary that documents them).",
    "The meaning of the element type and of 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Clear.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-property-clear-wave13/006a2a80.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-property-clear-wave13/006a2a80_property_list_clear.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_property_clear_wave13/006a2a80_property_list_clear.cpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
    },
    {
      "mode": "derived",
      "ref": "tools/reconstruction_tooling/abi_infer.py",
      "source_class": "derived"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "persisted",
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Clear.c",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/research/source-reconstruction-manifest.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/triage/queue-f0e310e0-v6.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-property-clear-wave13/006a2a80.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-property-clear-wave13/006a2a80_property_list_clear.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_property_clear_wave13/006a2a80_property_list_clear.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    
[TRUNCATED]
```
