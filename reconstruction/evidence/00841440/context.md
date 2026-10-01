# Reconstruction context 0x00841440

- Status: `partial`
- Content SHA-256: `3f3d2e4623c657630b28f32d99df7a8fdadb9c717205efab772343193a69684e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00841440",
  "phase": "reconstruction",
  "target": "0x00841440"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "ArgScript::FormatParser::CreateDefinitionSafe",
  "package": "pkg-argscript-createdefsafe-00841440",
  "subsystem": "ArgScript",
  "va": "0x00841440"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "9388e237d2edc0a3550ad26ab490fd84158293b1376915517de14e45723731d6",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00841440 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": [
    "x86-32 thiscall; receiver in ECX, two ordinary stack arguments, callee cleanup",
    "__thiscall"
  ],
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "hidden_this_type": "FormatParser * per the SDK/Ghidra import label; the object is opaque here because no FormatParser vtable could be corroborated (see vtables)",
  "ordinary_stack_argument_slots": 2,
  "ordinary_stack_arguments": [
    {
      "declared_name": "pName",
      "declared_type": "char *",
      "provenance": "SDK FUNCTION_DEF CreateDefinitionSafe(FormatParser* this, char* pName, Line* argumentsLine); the slot assignment is fixed by the unsafe sibling CreateDefinition (0x00844fb0..0x0084524e), which strlen-scans [EBP+0x8] and formats it as a name",
      "slot": "[ESP+0x4]"
    },
    {
      "declared_name": "argumentsLine",
      "declared_type": "Line *",
      "provenance": "the same unsafe sibling dereferences [EBP+0xc] as an object (MOV EDI,dword ptr [ECX + 0x10] at 0x008450b8) and hands the loaded word to a string-length helper, so this slot is the line pointer",
      "slot": "[ESP+0x8]"
    }
  ],
  "receiver_register": "ECX",
  "ret_form": [
    "absent in the target body; inherited RET 0x8 from 0x0083c780",
    "RET 0x8, inherited from 0x0083c78e rather than present in this body"
  ],
  "return_note": "declared. The target body never writes EAX; the value a caller observes is whatever 0x0083c780 leaves there, and that function's last write to EAX is MOV EAX,dword ptr [ESP + 0x4] at 0x0083c780, i.e. the first stack argument. So the 
[TRUNCATED]
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
      "callsite": "0x00841452",
      "direction": "out",
      "other": "0x0083c780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00841460",
      "direction": "out",
      "other": "0x0083c780",
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
  "globals": [
    "global:PASS"
  ],
  "types": [
    "FormatParser * per the SDK/Ghidra import label; the object is opaque here because no FormatParser vtable could be corroborated (see vtables)",
    "bool",
    "bool, declared. The target body never writes EAX; the value a caller observes is whatever 0x0083c780 leaves there, and that function's last write to EAX is MOV EAX,dword ptr [ESP + 0x4] at 0x0083c780, i.e. the first stack argument. So the observed return is the low byte of the pName word, consistent with the declared bool.",
    "openspore::reconstruction::pkg_argscript_createdefsafe_00841440::CreateDefinitionSafePorts",
    "openspore::reconstruction::pkg_argscript_createdefsafe_00841440::OpaqueFormatParser",
    "openspore::reconstruction::pkg_argscript_createdefsafe_00841440::OpaqueLine",
    "openspore::reconstruction::pkg_argscript_createdefsafe_00841440::SharedTail0083c780"
  ],
  "vtables": [
    "vtable:0x0141c0f4"
  ]
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
  "edges": [
    {
      "callsite": "0x00841452",
      "direction": "out",
      "other": "0x0083c780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00841460",
      "direction": "out",
      "other": "0x0083c780",
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
    "id": "scc-0260",
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
      "same_subsystem"
    ],
    "package": "PKG-ARGSCRIPT-WAVE9",
    "score": 6,
    "symbol": "pkg_argscript_get_current_scope_00d1dcd0",
    "va": "0x00d1dcd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__CreateDefinitionSafe.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__CreateDefinitionSafe.c",
    "reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440.cpp",
    "reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440.hpp",
    "reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440_model_test.cpp",
    "reconstruction/staging/pkg-dfw-00841440/dfw_00841440.cpp",
    "reconstruction/staging/pkg-dfw-00841440/dfw_00841440_model_test.cpp",
    "reconstruction/staging/pkg-dfw-00841440/dfw_00841440_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-argscript-createdefsafe-00841440/00841440.json",
    "reconstruction/metadata/pkg-dfw-00841440/00841440.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 9401,
  "preview": "{\n  \"conflicts\": [\n    {\n      \"anchors\": [\n        \"0x00845310\",\n        \"0x00b1fdb0\",\n        \"0x00845310\",\n        \"0x00b1fdb0\",\n        \"0x00844f70\",\n        \"0x00841440\",\n        \"0x00846e60\",\n        \"0x00841d40\",\n        \"0x00845790\",\n        \"0x00842d10\",\n        \"0x00844180\",\n        \"0x00843000\",\n        \"0x00845310\",\n        \"0x0067dd90\",\n        \"0x00e66280\",\n        \"0x00e66840\"\n      ],\n      \"conflict_id\": \"unresolved:knowledgegraph/research/state-machines/additional-domains.json:1\",\n      \"kind\": \"conflict_ledger\",\n      \"rejected\": [],\n      \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n      \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n      \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n      \"subject\": null,\n      \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n    },\n    {\n      \"anchors\": [\n        \"0x005c7d00\",\n        \"0x005c7d00\",\n        \"0x00844f70\",\n        \"0x00841440\",\n        \"0x00846e60\",\n        \"0x00841d40\",\n        \"0x00845790\",\n        \"0x005c7d00\",\n        \"0x005c7cb0\",\n        \"0x005c7f10\",\n        \"0x005c7f70\",\n        \"0x00842d10\",\n        \"0x
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__CreateDefinitionSafe.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-argscript-createdefsafe-00841440/00841440.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-00841440/00841440.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-00841440/dfw_00841440.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-00841440/dfw_00841440_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-00841440/dfw_00841440_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__CreateDefinitionSafe.c",
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
      "ref": "reconstruction/metadata/pkg-argscript-createdefsafe-00841440/00841440.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-dfw-00841440/00841440.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440.cpp",
      "source_class": "committed_artifact"
    },
  
[TRUNCATED]
```
