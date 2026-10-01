# Reconstruction context 0x0057ac00

- Status: `partial`
- Content SHA-256: `6d7c37744fe31d1b38e508ce99ddeb7d140c97d1fd4f6f83c99f696678d4142c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0057ac00",
  "phase": "reconstruction",
  "target": "0x0057ac00"
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
  "va": "0x0057ac00"
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
  "content_sha256": "6b7427f646045602fed83d43ddfffc7b5c0cc016b5a69581bf934caa7adb65d0",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0057ac00 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall with a hidden pointer return",
  "hidden_receiver": "read",
  "hidden_this_register": "ECX, spilled to ESI at 0x0057ac07; the body reads [ESI + 0x24], [ESI + 0x48], [ESI + 0x98], [ESI + 0x2a8], [ESI + 0x4b1] and [ESI + 0x4b2] and, through 0x0057a960 and 0x0057a9e0, [ESI + 0x1cc]",
  "ordinary_stack_argument_slots": 4,
  "receiver": true,
  "ret_form": "RET 0x10",
  "return_note": "(a pointer to a 16-byte four-dword structure)",
  "return_observation": "0x0057add8 MOV EAX,dword ptr [ESP + 0x64] loads argument 1 into EAX after the last helper call, and 0x0057ade8/0x0057adee/0x0057adf7/0x0057adfa write the four dwords through EAX. EAX is never otherwise written between 0x0057add8 and the RET. The early path agrees: 0x0057ac1d MOV EAX,dword ptr [ESP + 0x5c] then four stores through EAX then 0x0057ac35 RET 0x10.",
  "return_register": "EAX",
  "return_semantics": "returns the same pointer that was passed as argument 1; all six callers immediately dereference EAX as [EAX], [EAX + 4], [EAX + 8] and [EAX + 0xc]",
  "return_type": "EditMask0057ac00*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "frame_offset": "[ESP + 0x5c]",
      "read_at": [
        "0x0057ac1d",
        "0x0057add8"
      ],
      "role": "pointer to the 16-byte output buffer; also the return value",
      "slot": 1,
      "written_at": [
        "0x0057ac23",
        "0x0057ac25",
        "0x0057ac28",
        "0x0057ac2b",
        "0x0057ade8",
        "0x00
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "app_direct_property_list_get_direct_bool_006a25a0",
      "reconstructed": true,
      "va": "0x006a25a0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057ea30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058d1c0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0057eb7c",
      "direction": "in",
      "other": "0x0057ea30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057f79e",
      "direction": "in",
      "other": "0x0057f6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057f7d9",
      "direction": "in",
      "other": "0x0057f6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00586635",
      "direction": "in",
      "other": "0x00586410",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058a768",
      "direction": "in",
      "other": "0x0058a5a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058aaf3",
      "direction": "in",
      "other": "0x0058a950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058d2fb",
      "direction": "i
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "EditMask0057ac00* (a pointer to a 16-byte four-dword structure)"
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
      "A differential trace that mutates a model with and without a mouth part would be required to confirm the bit-0x400 polarity end to end.",
      "A runtime trace is required to read the eight mask globals after initialisation, to observe the actual property values behind ids 0x055D7CA1, 0x7A926123 and 0xF5CBE065, to see which capability bits the evaluator grants in practice, and to confirm the runtime class of the object at cEditor + 0x1CC.",
      "No original-process trace has been captured for 0x0057ac00. Every claim in this record is static.",
      "The Cell stage has never been entered in any recorded run, so the cll branch of the mouth scan has no runtime oracle."
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
  "callees": [
    {
      "name": "app_direct_property_list_get_direct_bool_006a25a0",
      "reconstructed": true,
      "va": "0x006a25a0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057ea30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057f6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058d1c0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0057eb7c",
      "direction": "in",
      "other": "0x0057ea30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057f79e",
      "direction": "in",
      "other": "0x0057f6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057f7d9",
      "direction": "in",
      "other": "0x0057f6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00586635",
      "direction": "in",
      "other": "0x00586410",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058a768",
      "direction": "in",
      "other": "0x0058a5a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058aaf3",
      "direction": "in",
      "other": "0x0058a950",
      "reference_ty
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-20-PROPERTY-ADAPTER",
    "score": 3,
    "symbol": "app_direct_property_list_get_direct_bool_006a25a0",
    "va": "0x006a25a0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b05/0057ac00.json"
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
    "A differential trace that mutates a model with and without a mouth part would be required to confirm the bit-0x400 polarity end to end.",
    "A runtime trace is required to read the eight mask globals after initialisation, to observe the actual property values behind ids 0x055D7CA1, 0x7A926123 and 0xF5CBE065, to see which capability bits the evaluator grants in practice, and to confirm the runtime class of the object at cEditor + 0x1CC.",
    "Is the SDK's /* 48h */ int field_48 really the same storage this function passes by address to two mutating helpers, or is the SDK's declaration of that offset stale? The address-taken use is observed; the SDK's intent is not confirmed.",
    "No original-process trace has been captured for 0x0057ac00. Every claim in this record is static.",
    "The Cell stage has never been entered in any recorded run, so the cll branch of the mouth scan has no runtime oracle.",
    "What are the 0x14-byte records at rigblock + 0xC0C that 0x00435b60 searches, and what is the meaning of the third dword it returns? Only the stride, the key offset and the result offset are established.",
    "What do the individual capability bits mean? For bits 0x400, 0x800, 0x40000 and 0x20 the semantics are pinned by the code; for the other fifteen observed inside 0x004F3DE0 nothing beyond their bit positions is known, and this function's own request for them is unobservable for the reason above.",
    "What does 0x004BAC30 actually hand to 0x004F3DE0? 0x004bac5c pushes dword ptr [EBP + 0x8], which in that frame
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b05/0057ac00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b05/0057ac00.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/i
[TRUNCATED]
```
