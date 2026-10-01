# Reconstruction context 0x00b8dab0

- Status: `partial`
- Content SHA-256: `e6621026cdf2eee4c2352af1c794b42e8f9dab459d111e59efaffba143f88cf5`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b8dab0",
  "phase": "reconstruction",
  "target": "0x00b8dab0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b8dab0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b8dab0"
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
  "content_sha256": "0e6a2ae3a962f5ec94dcd985fd99c04de44c622e22d7bb5259e50f474024a184",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 __fastcall FUN_00b8dab0(int param_1)

{
  return *(undefined4 *)(param_1 + 0x194);
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (ECX carries the receiver and is dereferenced before any definite write; bare RET with no immediate; no stack word read as an argument)",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "ECX, read at 0x00b8dab0 as the base of the single memory operand `dword ptr [ECX + 0x194]`; never saved to another register and never written",
  "ret_form": "RET (0x00b8dab6, byte 0xc3, no imm16)",
  "return_note": "32-bit scalar",
  "return_register": "EAX",
  "return_semantics": "the 32-bit word STORED at receiver+0x194, copied bit for bit into EAX",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
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
      "va": "0x00ae5840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00badd10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb9b70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd8a00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd8aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd8b10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd9a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be9b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf4370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c00b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c341a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c34ee0"
    },
    {
      "name": "FUN_00c47e20",
      "reconstructed": false,
      "va": "0x00c47e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4bc00"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ae587b",
      "direction": "in",
      "other": "0x00ae5840",
      "reference_type": "direct-cal
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "32-bit scalar"
  ],
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
      "va": "0x00ae5840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00badd10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb5ae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb9b70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd8a00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd8aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd8b10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd9a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be9b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf4370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c00b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c341a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c34ee0"
    },
    {
      "name": "FUN_00c47e20",
      "reconstructed": false,
      "va": "0x00c47e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4bc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5f770"
    },
    {
      "name": null,
    
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
    "Are the sibling words of this receiver related - +0x184 (which HAS a setter at 0x00b8da80 and a transform getter at 0x00b8da70), +0x188 (LEA only), +0x190 (written at 0x00b8da48), +0x198 (LEA getter, setter at 0x00b8dae6) and +0x19c (written at 0x00b8daef) - a single structure whose fields mean different things, or independent slots? Adjacency in the accessor block is not a layout.",
    "Does the receiver need an AddRef, and by whom? The body has no room for a reference call, so ownership is undetermined.",
    "What does the word at receiver+0x194 mean? Four callers show ordinal/threshold behaviour (compared against 2 and 5, reduced with JLE) but no SDK import, committed note or sampled caller names the concept.",
    "Which class is the receiver? Every sampled caller reaches it through FUN_010212a0, i.e. `dword [esi+0x13c]` of another object, and nothing names the resulting class.",
    "Who writes the word at +0x194, and when? No access to [ECX+0x194] exists in the 0x400-byte window 0x00b8d900..0x00b8dd00, but indirect or bulk publication outside that window is unexcluded."
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
