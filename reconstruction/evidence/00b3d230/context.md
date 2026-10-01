# Reconstruction context 0x00b3d230

- Status: `complete`
- Content SHA-256: `e3146ec818a7c3f3990946127c92f366a47a80caf25e8390ac5d7257d134b234`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d230",
  "phase": "reconstruction",
  "target": "0x00b3d230"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b3d230",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b3d230"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "c7b9f5576440eec6382727f32d67600e7a653b4e2840e485f8e7fee2dd6aa2ef",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_00b3d230(void)

{
  return DAT_0167eac0;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": false,
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": false,
  "receiver_register": null,
  "ret_form": "RET",
  "return_register": [
    "EAX",
    "AL"
  ],
  "return_semantics": "the four bytes stored at absolute address 0x0167eac0, whole, in EAX",
  "return_type": "uint32",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "none",
  "termination": "RET at 0x00b3d235 (bare C3, no immediate operand); the instruction after it, 0x00b3d236, is a CC int3 pad byte, so the function has exactly one exit and it is the terminal RET"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00adad70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00adf840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b279e0"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b69990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0d3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c38510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c69540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccc640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccefb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd9da0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cde660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce0a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce8ab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf1440"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00adad9d",
      "direction": "in",
      "other": "0x00adad70",
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:g_0167eac0, a reference alias to the single modelled slot word"
  ],
  "types": [
    "std::uint32_t",
    "uint32"
  ],
  "vtables": []
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
      "A differential run must call this VA through a direct call, as all 60 recorded callers do; there is no vtable slot and therefore no dispatch path to reconstruct for it.",
      "The static validator reported no target source span (validation.json source.path null), so no structural check has been run against the staged sources for this package; that is an orchestrator-side gap, not a pass.",
      "The value returned by 0x00b3d230 is whatever is stored at 0x0167eac0 at the moment of the call, so a differential run must establish that dword's value first; the body itself does not determine it and the image carries no initializer for that address."
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00adad70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00adf840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b279e0"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b69990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0d3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c38510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c69540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccc640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccefb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd9da0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cde660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce0a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce8ab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf1440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf14d0"
 
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 6,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 6,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230.cpp",
    "reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230.hpp",
    "reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00b3d230/00b3d230.json"
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
    "A differential run must call this VA through a direct call, as all 60 recorded callers do; there is no vtable slot and therefore no dispatch path to reconstruct for it.",
    "The static validator reported no target source span (validation.json source.path null), so no structural check has been run against the staged sources for this package; that is an orchestrator-side gap, not a pass.",
    "The value returned by 0x00b3d230 is whatever is stored at 0x0167eac0 at the moment of the call, so a differential run must establish that dword's value first; the body itself does not determine it and the image carries no initializer for that address.",
    "What the word at 0x0167eac0 denotes. The body at 0x00b3d230 loads it and returns it; it does not dereference it, test it or store it, so the body fixes the location and the width and nothing about the meaning.",
    "Whether the 60 callers share a common owner or a common subsystem role. The index record labels the VA subsystem Simulator, but that is a triage label and no caller was reconstructed here to corroborate it.",
    "Whether the pointer_like classification of the returned word (inference RT2) is a real type or a shape heuristic. Two null-testing callers (0x00c0d3c0, 0x00c38532) are consistent with a pointer but do not establish one.",
    "Which calling convention the original compiler used. Zero parameters, no receiver and a bare RET make the four x86-32 conventions byte-identical here, and 60 direct call sites that push nothing narrow the field to 'no arguments pas
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-00b3d230/00b3d230.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "GhidraMCP REST /decompile_function @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "ghidra"
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
      "ref": "reconstruction/metadata/pkg-w2-00b3d230/00b3d230.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00b3d230/root_acce
[TRUNCATED]
```
