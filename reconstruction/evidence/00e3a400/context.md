# Reconstruction context 0x00e3a400

- Status: `complete`
- Content SHA-256: `a359d7ba375b7c0b3841a33624caebc5b95d449b164c1488600b932b3e9612b9`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e3a400",
  "phase": "reconstruction",
  "target": "0x00e3a400"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00e3a400"
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
  "content_sha256": "f5d3cf5959ff0de2bf6a93e97691d501f5fd3d756feb12886e385e5ffeb8118c",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void __thiscall FUN_00e3a270(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (param_2 < -0xd876cb5) {
    if (param_2 != -0xd876cb6) {
      if (param_2 < -0x55095553) {
        if (param_2 == -0x55095554) {
LAB_00e3a2c0:
          *(undefined4 *)(param_1 + 0x324) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);
          FUN_00e39420(param_3,3,param_1 + 0x2c0);
          return;
        }
        if (param_2 < -0x6086d4b3) {
          if (param_2 == -0x6086d4b4) {
            if (*(int *)(param_1 + 0x32c) == -1) {
              *(undefined **)(param_1 + 0x32c) = &DAT_01654c05;
            }
            uVar1 = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);
            *(undefined4 *)(param_1 + 0x328) = uVar1;
            if (*(int *)(param_1 + 0x324) != 0) {
              return;
            }
            *(undefined4 *)(param_1 + 0x324) = uVar1;
            return;
          }
          if (param_2 == -0x7ecc04d2) goto LAB_00e3a4e4;
          if (param_2 != -0x67f1bc0e) {
            if (param_2 != -0x660f2e26) {
              return;
            }
            goto LAB_00e3a2c0;
          }
        }
        else if ((param_2 != -0x5f68cc8c) && (param_2 != -0x5934b361)) {
          return;
        }
      }
      else if (param_2 < -0x27cd4fa6) {
        if (param_2 != -0x27cd4fa7) {
          if (param_2 == -0x52189332) {
            if (*(int *)(param_1 + 0x32c) == -1) {
              *(undefined **)(param_1 + 0x32c) = &DAT_01654c01;
            }
            *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);
            
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_note": "(declared) against unclassified_in_EAX (record)",
  "return_register": "EAX",
  "return_type": "Word",
  "saved_registers": [
    "none -- the body never pushes a register, so it has no frame and saves nothing"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:WARN"
  ],
  "types": [
    "Word",
    "Word (declared) against unclassified_in_EAX (record)"
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0515",
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
      "same_calling_convention"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 8,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 8,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
  },
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
    "reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400.cpp",
    "reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00e3a400/00e3a400.json"
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
    "ABI/CALLS/RETURN SEMANTICS are NOT_AVAILABLE with the detail 'target source span is not deterministically available', and the cause is NOT the reconstruction source. validate._target_span binds a span only through record['name'] or record['normalized_symbol'] (tools/reconstruction_tooling/validate.py:242-291), and the index record for 0x00e3a400 carries BOTH AS NULL: the triage row knowledgegraph/triage/queue-f0e310e0-v6.json has name=null for this VA (source: unknown-high-investigation) and the manifest has no functions[] row for it, so reconstruction_knowledge.build_index projects name=null. No staging-side edit can supply it -- verified by adding a name/normalized_symbol key to THIS sidecar and rebuilding the index in process: the record stayed null, because build_index reads the name from the manifest and the triage queue only, never from a metadata sidecar. Both of those are campaign-owned read paths (docs/tooling/concurrency.md: 'No command overwrites ... the manifest'), so a worker cannot fix this and a validator must not be weakened to accommodate it. Injected in process as a diagnostic ONLY (validate._record monkeypatched, no file or tool edited), a name of re_00e3a400 makes the span resolve and flips ABI, CONSTANTS, CONTROL FLOW and RETURN SEMANTICS to PASS, which confirms the staged source is itself sound and correctly named; CALLS still FAILs for the separate interior-address reason already recorded above, and GLOBALS stays WARN because the five immediates 0x1654c00..0x1654c05 fall in the validator's 0x130000
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w2-00e3a400/00e3a400.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w2-00e3a400/00e3a400.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00e
[TRUNCATED]
```
