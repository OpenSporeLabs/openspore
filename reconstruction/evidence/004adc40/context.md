# Reconstruction context 0x004adc40

- Status: `partial`
- Content SHA-256: `117b26b825cf98644d2c7947d2e1d02adb6bff764bcc1f90e20bd25df7cae04c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004adc40",
  "phase": "reconstruction",
  "target": "0x004adc40"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_004adc40",
  "package": null,
  "subsystem": "Editor",
  "va": "0x004adc40"
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
  "content_sha256": "6f2bc2d767ecfa7503633524fcbeb6ed9e5164e8b7ad63feffda536251ddf015",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004adc40 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall-compatible ECX-only machine ABI",
  "hidden_this": "OpaqueEditorFlag* receiver in ECX",
  "return_note": "Byte; Field",
  "return_register": "EAX",
  "return_semantics": [
    "Returns the unsigned byte stored at receiver+0x4F. In the original only AL is written, so the upper 24 bits of EAX are NOT zero-extended: they retain receiver address bits 8..31 because EAX was reloaded from the spilled ECX immediately before the byte load. Consumers must read AL only; all three sampled call sites do. The reconstructed source returns a std::uint8_t and therefore zero-extends, which is a strictly stronger guarantee; see source_fidelity.",
    "Returns the unsigned byte stored at receiver+0x4F. In the original only AL is written, so the upper 24 bits of EAX are NOT zero-extended: they retain receiver address bits 8..31 because EAX was reloaded from the spilled ECX immediately before the byte load. Consumers must read AL only; all three sampled call sites do. The reconstructed source returns a std::uint8_t and therefore zero-extends, which is a strictly stronger guarantee."
  ],
  "return_width_bytes": 1,
  "stack_arguments": [],
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
      "va": "0x00435a10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004370a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00438700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00438a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00439110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043c450"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043e7e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043e9c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043ea40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043eae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043eb50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043fc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043ffa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00440020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00440090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00448d60"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00435aa5",
      "direction": "in",
      "other": "0x00435a10",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "Byte",
    "Field"
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
      "va": "0x00435a10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004370a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00438700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00438a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00439110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043c450"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043e7e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043e9c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043ea40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043eae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043eb50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043fc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043ffa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00440020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00440090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00448d60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00448e90"
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
    "package": "pkg-vft-preinc-0051e340",
    "score": 6,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "subobject-forward-0051e380",
    "score": 6,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 6,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 6,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 6,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-editor-child-007f30d0",
    "score": 6,
    "symbol": "FUN_007f30d0",
    "va": "0x007f30d0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-00a85070",
    "score": 6,
    "symbol": "re_00a85070",
    "va": "0x00a85070"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w2-00a980b0",
    "score": 6,
    "symbol": "re_00a980b0",
    "va": "0x00a980b0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-editor-adc40-flag/adc40_flag.cpp",
    "reconstruction/staging/pkg-editor-adc40-flag/adc40_flag.hpp",
    "reconstruction/staging/pkg-editor-adc40-flag/adc40_flag_model_test.cpp",
    "reconstruction/staging/pkg-editor-adc40-smoke01/adc40_smoke01.cpp",
    "reconstruction/staging/pkg-editor-adc40-smoke01/adc40_smoke01.hpp",
    "reconstruction/staging/pkg-editor-adc40-smoke01/adc40_smoke01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-editor-adc40-flag/004adc40.json",
    "reconstruction/metadata/pkg-editor-adc40-smoke01/004adc40.json"
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
    "Do all 64 direct callers pass the same concrete receiver type, given the +0x28-member and stack-local receiver provenances already observed?",
    "Is the +0x4F byte a bool, a small enum, or a bitfield-style flags byte? Callers only ever test it for zero, so the evidence cannot separate these.",
    "What concrete class is the receiver, and does its +0x4F byte carry a name in the Spore ModAPI SDK?",
    "What values are observed at receiver+0x4F in the original process?",
    "Which of the two independent packages for this VA, pkg-editor-adc40-flag or pkg-editor-adc40-smoke01, should the integrator promote? They agree on every machine-derived fact and differ only in the justification for not using a hand-written body, where this package's justification is the measured one. The index currently resolves this VA to pkg-editor-adc40-flag because that path sorts first.",
    "Which owner constructs and publishes receivers for this accessor?"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-adc40-flag/004adc40.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-adc40-smoke01/004adc40.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-adc40-flag/adc40_flag.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-adc40-flag/adc40_flag.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-adc40-flag/adc40_flag_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-adc40-smoke01/adc40_smoke01.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-adc40-smoke01/adc40_smoke01.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-adc40-smoke01/adc40_smoke01_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-editor-adc40-flag/004adc40.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-editor-adc40-smoke01/004adc40.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-editor-adc40-flag/adc40_flag.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-editor-adc40-flag/adc40_flag.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-editor
[TRUNCATED]
```
