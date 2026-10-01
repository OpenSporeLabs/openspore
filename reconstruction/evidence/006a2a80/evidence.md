# Evidence 0x006a2a80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `20a297619332bbfefe69949cb6741de471c7c548c99e92ba32d02df506fd6c3f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
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

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "7ebdbeea4c21f078005f82cce672668c8cf5f3c359cb8031fc3ec3c07eb3ef34",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0022"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          24,
          28,
          52
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0011",
        "obs-0022"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0022"
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
        "obs-0022"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0022"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    }
  ],
  "observations": [
    {
      "at": "0x006a2a80",
      "count": 5,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x006a2a81",
      "count": 3,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x006a2a81",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x006a2a82",
      "count": 5,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x006a2a83",
      "count": 2,
      "first_use": 3,
      "first_write_index": 12,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EBX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x006a2a83",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,ECX",
      "reg": "EBX",
      "write_kind": "reg"
    },
    {
      "at": "0x006a2a85",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,dword ptr [EBX + 0x18]",
      "reg": "EBP",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a2a88",
      "count": 3,
      "first_use": 5,
      "first_write_index": 6,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x006a2a89",
      "definite": true,
      "id": "obs-0009",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [EBX + 0x1c]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a2a92",
      "id": "obs-0010",
      "index": 11,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00612b20",
      "target": "0x00612b20"
    },
    {
      "at": "0x006a2a97",
      "definite": true,
      "id": "obs-0011",
      "index": 12,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a2a9a",
      "definite": true,
      "id": "obs-0012",
      "index": 13,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0xc",
      "reg": "ESP",
      "write_kind": "arit
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
  "count": 36,
  "instructions": [
    {
      "address": "006a2a80",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a2a81",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006a2a82",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2a83",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "006a2a85",
      "instruction": "MOV EBP,dword ptr [EBX + 0x18]"
    },
    {
      "address": "006a2a88",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a2a89",
      "instruction": "MOV EDI,dword ptr [EBX + 0x1c]"
    },
    {
      "address": "006a2a8c",
      "instruction": "LEA ESI,[EBX + 0x18]"
    },
    {
      "address": "006a2a8f",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006a2a90",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a2a91",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a2a92",
      "instruction": "CALL 0x00612b20"
    },
    {
      "address": "006a2a97",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "006a2a9a",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "006a2a9d",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a2a9e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a2a9f",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "006a2aa1",
      "instruction": "CALL 0x00685a30"
    },
    {
      "address": "006a2aa6",
      "instruction": "SUB EDI,EBP"
    },
    {
      "address": "006a2aa8",
      "instruction": "MOV EAX,0xd5555555"
    },
    {
      "address": "006a2aad",
      "instruction": "IMUL EDI"
    },
    {
      "address": "006a2aaf",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "006a2ab2",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "006a2ab4",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "006a2ab7",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "006a2ab9",
      "instruction": "LEA EDX,[EAX + EAX*0x2]"
    },
    {
      "address": "006a2abc",
      "instruction": "ADD EDX,EDX"
    },
    {
      "address": "006a2abe",
      "instruction": "ADD EDX,EDX"
    },
    {
      "address": "006a2ac0",
      "instruction": "POP EDI"
    },
    {
      "address": "006a2ac1",
      "instruction": "ADD EDX,EDX"
    },
    {
      "address": "006a2ac3",
      "instruction": "ADD dword ptr [ESI + 0x4],EDX"
    },
    {
      "address": "006a2ac6",
      "instruction": "INC dword ptr [EBX + 0x34]"
    },
    {
      "address": "006a2ac9",
      "instruction": "POP ESI"
    },
    {
      "address": "006a2aca",
      "instruction": "POP EBP"
    },
    {
      "address": "006a2acb",
      "instruction": "POP EBX"
    },
    {
      "address": "006a2acc",
      "instruction": "RET"
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
  "original_bytes": 9484,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_arguments\": [],\n    \"ret_form\": \"RET\",\n    \"return_register\": \"none\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 12,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 12,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 12,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:PropertyList\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 9,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:PropertyList\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 9,\n      \"symbol\": \"property_list_get_property_ids_006a3070\",\n      \"va\": \"0x006a3070\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 8,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:PropertyList\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 7,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:PropertyList\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 7,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a2a92\",\n        \"direction\": \"out\",\n        \"other\": \"0x00612b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2aa1\",\n        \"direction\": \"out\",\n        \"other\": \"0x00685a30\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0212\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::PropertyList::Clear\",\n  \"normalized_symbol\": \"property_list_clear_006a2a80\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"pkg-property-clear-wave13\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"pkg-property-clear-wave13\",\n  \"reconstructed\": true,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408820 is a runtime gate.\",\n      \"The meaning of the element type and of the flag words the release and copy helpers test cannot be recovered from this body; only the traversal stride is claimed.\",\n      \"The real body of 0x00612b20 is not reproduced here. It has now been read, and at this call site the pushed range is degenerate (the end cursor is pushed twice), so the port's contract is exactly the observed degenerate return of the third word, the begin cursor. The general non-empty movement path stays unmodelled.\",\n      \"The real body of 0x00685a30 is not reproduced here. It has now been read, and the port reproduces its unsigned 0x18-stride traversal but not the per-entry `TEST byte ptr [ESI + 0x14],0x4` release of 0x0093db80, which is out of scope for this record.\",\n      \"The semantic identity of the counter word at receiver+0x34 is unknown. Only the unconditional increment is claimed; its initial value and its readers are not observable here.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/
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
  "body_end": "006a2acc",
  "body_span_bytes": 77,
  "body_start": "006a2a80",
  "callees": [
    "FUN_00685a30",
    "FUN_00612b20"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a2a80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::PropertyList::Clear",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "PropertyList *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x2a2a80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::PropertyList::Clear(PropertyList * this)",
  "size_bytes": 77,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a2a80",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408820"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01408868"
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
    "No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408820 is a runtime gate.",
    "The meaning of the element type and of the flag words the release and copy helpers test cannot be recovered from this body; only the traversal stride is claimed.",
    "The real body of 0x00612b20 is not reproduced here. It has now been read, and at this call site the pushed range is degenerate (the end cursor is pushed twice), so the port's contract is exactly the observed degenerate return of the third word, the begin cursor. The general non-empty movement path stays unmodelled.",
    "The real body of 0x00685a30 is not reproduced here. It has now been read, and the port reproduces its unsigned 0x18-stride traversal but not the per-entry `TEST byte ptr [ESI + 0x14],0x4` release of 0x0093db80, which is out of scope for this record.",
    "The semantic identity of the counter word at receiver+0x34 is unknown. Only the unconditional increment is claimed; its initial value and its readers are not observable here."
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
  "PropertyList",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01408820"
]
```

## Conflicts

```json
[]
```
