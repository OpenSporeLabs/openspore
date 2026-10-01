# Reconstruction context 0x00b3d3d0

- Status: `partial`
- Content SHA-256: `b68c8af3fd2c5929714c8c0bcf08ff9545e427913febd01d118676a608d9760e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d3d0",
  "phase": "reconstruction",
  "target": "0x00b3d3d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b3d3d0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b3d3d0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "16246cc5cbe3928738c8d719a9a0840c3e70712b21b12ccc09d42f464a5b47eb",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_00b3d3d0(void)

{
  return DAT_0167eb20;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "receiver_register": null,
  "ret_form": "bare RET (c3), no immediate",
  "return_register": "EAX",
  "return_semantics": "the 32-bit word loaded from 0x0167eb20",
  "return_width_bytes": 4
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
      "va": "0x00b5f670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba8830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4da10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c54380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c71750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c829e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fda750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdd5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdeac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdfbc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe5a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01000000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01038410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103bf70"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b5f759",
      "direction": "in",
      "other": "0x00b5f670",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
      "va": "0x00b5f670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba8830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4da10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c54380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c71750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c829e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fda750"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdc150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdd5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdeac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fdfbc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe5a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01000000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01038410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103bf70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103d580"
    },
    {
      "name": null,
      "reconst
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
  "files": [],
  "handoffs": [],
  "metadata": []
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
    "What class or role does 0x0167eb20 hold? No artifact in this repository names it; it shares the .data tail with the four characterized manager slots but sits at an unidentified address, so no identity is asserted.",
    "Which calling convention do the 37 distinct callers actually use? The six-byte body cannot discriminate __cdecl/__stdcall/__thiscall/__fastcall; resolving this needs a caller-side stack contract or an SDK declaration.",
    "Who writes 0x0167eb20, and when? datarefs-2540f2ca.tsv records exactly one row targeting it and that row is `read`, so direct references are exhausted; publication is presumably indirect and needs a computed-publication scan.",
    "docs/analysis/reconstruction-research-queue.md:339 files 0x00b3d3d0 in an 'engine implementation / do-not-reconstruct cluster', which is inconsistent with the six-byte getter body two independent machine sources agree on. The triage record was not modified; the integrator should reconcile the classification."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "derived"
    },
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
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
    "RETURN SEMANTICS",
    "EVIDENCE COVERAGE"
  ]
}
```
