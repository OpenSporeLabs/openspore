# Evidence 0x00585d10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a16cb9d24558f08ff4cb41c5f70a3870e889e8960b891c90967d65fa25a9cbc6`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup",
  "return_semantics": "bool in AL from the wheel hook result",
  "return_type": "bool",
  "stack_cleanup_bytes": 16,
  "stack_cleanup_owner": "caller"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__stdcall",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": false,
    "ret_form": "RET 0x10",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x10",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "b99eaba59ce9a2a60f3bc983ae521d1753fbfdd8dee01b380104bc41650ab9a6",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__stdcall",
    "candidate_conventions": [
      "__stdcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 5,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0015"
      ],
      "claim": "the callee pops 16 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 16,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0004",
        "obs-0005",
        "obs-0011"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 4,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0015"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0015"
      ],
      "claim": "calling convention is __stdcall: a callee that pops stack arguments with no register receiver",
      "confidence": "INFERRED",
      "id": "C6",
      "value": "__stdcall"
    },
    {
      "based_on": [
        "obs-0015"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confidence": "APPROXIMATION",
      "id": "S2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0008"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00585d10",
      "count": 6,
      "first_use": 0,
      "first_write_index": 5,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00585d10",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0002",
      "index": 0,
      "key": 16,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00585d10",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00585d14",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 1,
      "key": 12,
      "kind": "STACK_SLOT_READ",
      "raw": "FLD float ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00585d18",
      "base": "ESP",
      "disp": 
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00584300",
      "0x00584300",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x00584300",
      "0x00584300",
      "0x00585d10",
      "0x00585d10",
      "0x00586410",
      "0x00586410",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "U-001-mission-transitions",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.",
    "resolution_status": "Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e4a0",
      "0x00d2e4a0",
      "0x00aeb7b0",
      "0x005737d0",
      "0x005737d0",
      "0x00585d10",
      "0x00585d10",
      "0x00586410",
      "0x00586410",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058a5a0"
    ],
    "conflict_id": "U-002-tribe-plans",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb7b0",
      "0x00aeb7b0",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x00582fe0",
      "0x00582fe0",
      "0x00584300",
      "0x00584300",
      "0x00585d10"
    ],
    "conflict_id": "U-007-communication-completion",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.",
    "resolution_status": "Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x00582fe0",
      "0x00582fe0",
      "0x00584300",
      "0x00584300",
      "0x00585d10",
      "0x00585d10",
      "0x00586410",
      "0x00586410",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "U-008-runtime-validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

## decompilation

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 12,
  "instructions": [
    {
      "address": "00585d10",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00585d14",
      "instruction": "FLD float ptr [ESP + 0xc]"
    },
    {
      "address": "00585d18",
      "instruction": "MOV EDX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00585d1c",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00585d1e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00585d1f",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00585d22",
      "instruction": "FSTP float ptr [ESP + 0x4]"
    },
    {
      "address": "00585d26",
      "instruction": "FLD float ptr [ESP + 0x18]"
    },
    {
      "address": "00585d2a",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00585d2d",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00585d2e",
      "instruction": "CALL 0x005858f0"
    },
    {
      "address": "00585d33",
      "instruction": "RET 0x10"
    }
  ]
}
```

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 7815,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"bool in AL from the wheel hook result\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 16,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00585d2e\",\n        \"direction\": \"out\",\n        \"other\": \"0x005858f0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0075\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Editors::cEditor::OnMouseWheel\",\n  \"normalized_symbol\": \"editor_input_00585d10\",\n  \"observed_mechanics\": [\n    \"Forwards wheel delta, x, y, and mouse state to dispatch_wheel with a literal zero sixth word.\",\n    \"Returns the hook byte as a nonzero boolean without local mutation.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-EDITOR-INPUT-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"runtime validation not run\",\n      \"wheel dispatch hook and runtime pointer/input state remain gated\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_triage_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseWheel.c\
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00585d35",
  "body_span_bytes": 38,
  "body_start": "00585d10",
  "callees": [
    "FUN_005858f0"
  ],
  "callers": [],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00585d10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "Editors::cEditor::OnMouseWheel",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 5,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cEditor *"
    },
    {
      "name": "wheelDelta",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "mouseX",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "float"
    },
    {
      "name": "mouseY",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "float"
    },
    {
      "name": "mouseState",
      "ordinal": 4,
      "storage": "Stack[0x14]:4",
      "type": "MouseState"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x185d10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Editors::cEditor::OnMouseWheel(cEditor * this, int wheelDelta, float mouseX, float mouseY, MouseState mouseState)",
  "size_bytes": 38,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00585d10",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f57f8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "013f5830"
    }
  ]
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseWheel.c",
  "file": "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseWheel.c",
    "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-input-wave6/00585d10.json"
  ]
}
```

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [
    "runtime validation not run",
    "wheel dispatch hook and runtime pointer/input state remain gated"
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "bool",
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor",
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks",
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget",
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget",
  "openspore::reconstruction::pkg_editor_input_wave6::TargetWord"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f57f8"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00584300",
      "0x00584300",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x00584300",
      "0x00584300",
      "0x00585d10",
      "0x00585d10",
      "0x00586410",
      "0x00586410",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "U-001-mission-transitions",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.",
    "resolution_status": "Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d2e4a0",
      "0x00d2e4a0",
      "0x00aeb7b0",
      "0x005737d0",
      "0x005737d0",
      "0x00585d10",
      "0x00585d10",
      "0x00586410",
      "0x00586410",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058a5a0"
    ],
    "conflict_id": "U-002-tribe-plans",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aeb7b0",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb7b0",
      "0x00aeb7b0",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x00582fe0",
      "0x00582fe0",
      "0x00584300",
      "0x00584300",
      "0x00585d10"
    ],
    "conflict_id": "U-007-communication-completion",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.",
    "resolution_status": "Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x00582fe0",
      "0x00582fe0",
      "0x00584300",
      "0x00584300",
      "0x00585d10",
      "0x00585d10",
      "0x00586410",
      "0x00586410",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "U-008-runtime-validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "derived": "__stdcall",
    "field": "calling_convention",
    "kind": "derived_vs_persisted",
    "persisted": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup",
    "resolution_status": "unresolved"
  }
]
```
