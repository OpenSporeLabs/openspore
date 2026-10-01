# Reconstruction context 0x00409c00

- Status: `partial`
- Content SHA-256: `98938aec3e65a47a966590d0764747cc14cc1d8af9b2a50654ee325410a2378e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00409c00",
  "phase": "reconstruction",
  "target": "0x00409c00"
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
  "subsystem": null,
  "va": "0x00409c00"
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
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "202c87b8674ad3261ab0ef75bcf7083a14a2d15288491bbe6b60aef084eb878f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00409c00 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall (receiver in ECX), no stack arguments",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is read only by the spill at 0x00409c06",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "no value is produced for the caller; the decompiler also gives the function a void return, and no instruction writes a result register",
  "return_register": null,
  "return_semantics": "no value; the constructor communicates entirely through the 24 bytes at the receiver",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single RET at 0x00409cd6"
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
      "va": "0x00407280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0041aaa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043eef0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00441440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00449d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044a070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044aaa0"
    },
    {
      "name": "FUN_0044ae00",
      "reconstructed": false,
      "va": "0x0044ae00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471b50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ad550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004aff80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ba150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004f01f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00507380"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00407a3e",
      "direction": "in",
      "other": "0x00407280",
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
    "Math::BoundingBox (SDK candidate, exact layout match)",
    "void"
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
      "No original-process trace has been captured. Whether any of the 28 callsites actually passes the constructed object on to a union or intersection without overwriting it first is a runtime fact.",
      "Runtime patching of either global constant cannot be excluded statically; both were read from the on-disk image only."
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
      "va": "0x00407280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0041aaa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043eef0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00441440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00449d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044a070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044aaa0"
    },
    {
      "name": "FUN_0044ae00",
      "reconstructed": false,
      "va": "0x0044ae00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471b50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00471ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ad550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004aff80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ba150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004f01f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00507380"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00507c70"
    },
    {
      "name": null,
    
[TRUNCATED]
```

## 11_related_functions

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b04/00409c00_bounding_box_ctor.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/00409c00_bounding_box_ctor.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/00409c00.json"
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
    "Do all 24 uninspected callsites pass the result as an out-parameter, or do some keep it as a member? The four inspected ones all do.",
    "Is the inverted state read back anywhere as a sentinel - for example a containment test that relies on it - or is it only ever an initial value? No reader was identified.",
    "Is the type really Math::BoundingBox? The 24-byte size and the 0x0C second-vector offset match the SDK declaration exactly, but any other 24-byte aggregate of two unaligned 12-byte vectors would match equally well, and the binary names it nowhere.",
    "No original-process trace has been captured. Whether any of the 28 callsites actually passes the constructed object on to a union or intersection without overwriting it first is a runtime fact.",
    "Runtime patching of either global constant cannot be excluded statically; both were read from the on-disk image only.",
    "The neighbouring constants at 0x013eb254 (00 00 80 00) and 0x013eb260 (ff ff ff 7f) were read while locating the real one and are recorded as context only. Whether they belong to the same table of float constants, and what else references them, was not investigated.",
    "Why is the constructor out of line? Six constant stores would normally be inlined; the 28 direct callsites and 0 vtable references argue against a virtual override, so an unoptimised translation unit or an address taken somewhere is the likely explanation, and neither was checked."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b04/00409c00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/00409c00_bounding_box_ctor.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/00409c00_bounding_box_ctor.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b04/00409c00.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/00409c00_bounding_box_ctor.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/00409c00_bounding_box_ctor.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
  
[TRUNCATED]
```
