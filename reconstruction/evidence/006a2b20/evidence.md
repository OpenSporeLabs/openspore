# Evidence 0x006a2b20

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `32e4f470bfede7a2bbba3cf7ed8747bbbfbd52d5e5d4d82702cd9f218cebdaad`

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
  "saved_registers": [
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
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
  "content_sha256": "f289fd1a484a12e844c79263d5343bd678ad03a5a3b363118a92938cf5b13bee",
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
        "obs-0020"
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
        "obs-0003",
        "obs-0004",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          24,
          28,
          56,
          60
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0006",
        "obs-0020"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020"
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
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x006a2b20",
      "count": 3,
      "first_use": 0,
      "first_write_index": 10,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x006a2b21",
      "count": 8,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x006a2b22",
      "count": 2,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x006a2b22",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x006a2b24",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x38]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a2b27",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x3c]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a2b2a",
      "count": 3,
      "first_use": 5,
      "first_write_index": 11,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x006a2b2b",
      "count": 10,
      "first_use": 6,
      "first_write_index": 3,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x006a2b2f",
      "id": "obs-0009",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0092cb00",
      "target": "0x0092cb00"
    },
    {
      "at": "0x006a2b34",
      "definite": true,
      "id": "obs-0010",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESI + 0x18]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a2b37",
      "definite": true,
      "id": "obs-0011",
      "index": 11,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESI + 0x1c]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a2b40",
      "id": "obs-0012",
      "index": 16,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00612b20",
      "target": "0x00612b20"
    },
    {
      "at": "0x006a2b45",
      "definite": true,
      "id": "obs-0013",
      "index": 17,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESI +
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
  "count": 39,
  "instructions": [
    {
      "address": "006a2b20",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a2b21",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2b22",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006a2b24",
      "instruction": "MOV EAX,dword ptr [ESI + 0x38]"
    },
    {
      "address": "006a2b27",
      "instruction": "MOV ECX,dword ptr [ESI + 0x3c]"
    },
    {
      "address": "006a2b2a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a2b2b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a2b2c",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "006a2b2e",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a2b2f",
      "instruction": "CALL 0x0092cb00"
    },
    {
      "address": "006a2b34",
      "instruction": "MOV EBX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "006a2b37",
      "instruction": "MOV EDI,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006a2b3a",
      "instruction": "ADD ESI,0x18"
    },
    {
      "address": "006a2b3d",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a2b3e",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a2b3f",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a2b40",
      "instruction": "CALL 0x00612b20"
    },
    {
      "address": "006a2b45",
      "instruction": "MOV EDX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "006a2b48",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "006a2b4b",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a2b4c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a2b4d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "006a2b4f",
      "instruction": "CALL 0x00685a30"
    },
    {
      "address": "006a2b54",
      "instruction": "SUB EDI,EBX"
    },
    {
      "address": "006a2b56",
      "instruction": "MOV EAX,0xd5555555"
    },
    {
      "address": "006a2b5b",
      "instruction": "IMUL EDI"
    },
    {
      "address": "006a2b5d",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "006a2b60",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "006a2b62",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "006a2b65",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "006a2b67",
      "instruction": "LEA EAX,[EAX + EAX*0x2]"
    },
    {
      "address": "006a2b6a",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "006a2b6c",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "006a2b6e",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "006a2b70",
      "instruction": "ADD dword ptr [ESI + 0x4],EAX"
    },
    {
      "address": "006a2b73",
      "instruction": "POP EDI"
    },
    {
      "address": "006a2b74",
      "instruction": "POP ESI"
    },
    {
      "address": "006a2b75",
      "instruction": "POP EBX"
    },
    {
      "address": "006a2b76",
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
  "original_bytes": 9529,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_arguments\": [],\n    \"ret_form\": \"RET\",\n    \"return_register\": \"none\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 12,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 12,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DirectPropertyList\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 9,\n      \"symbol\": \"direct_property_list_add_properties_from_006a1600\",\n      \"va\": \"0x006a1600\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DirectPropertyList\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 9,\n      \"symbol\": \"direct_property_list_get_property_alt_006a1e50\",\n      \"va\": \"0x006a1e50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 8,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 8,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DirectPropertyList\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-PROPERTY-ADAPTER\",\n      \"score\": 5,\n      \"symbol\": \"app_direct_property_list_get_direct_bool_006a25a0\",\n      \"va\": \"0x006a25a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"opaque_list_has_property_006a27d0\",\n      \"va\": \"0x006a27d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a2b40\",\n        \"direction\": \"out\",\n        \"other\": \"0x00612b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2b4f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00685a30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2b2f\",\n        \"direction\": \"out\",\n        \"other\": \"0x0092cb00\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0214\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::DirectPropertyList::Clear\",\n  \"normalized_symbol\": \"direct_property_list_clear_006a2b20\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"pkg-direct-property-clear-wave14\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"pkg-direct-property-clear-wave14\",\n  \"reconstructed\": true,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process invocation and no indirect-caller trace were captured for 0x006a2b20, so the reachability of this body through the shared vtable 0x01408870, and the real values held at receiver+0x38 and receiver+0x3c, remain runtime gates.\",\n      \"No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408870 is a runtime gate.\",\n      \"The real body of 0x00612b20 is not reproduced here beyond its observed 0x18-stride move and its degenerate-range return. Its non-empty movement path remains unmodelled.\",\n      \"The real body of 0x00685a30 is not reproduced here beyond its 0x18-stride traversal. Its per-entry release call to 0x0093db80 on the sub-object at entry+4, taken when byte entry+0x14 has its 0x4 bit set, is out of scope for this record.\",\n      \"The real body of 0x0092cb00 is not reproduced here beyond its observed dword-fill contract. Its count word is read from receiver+0x38, whose meaning and initial value this body never establishes.\"\n    ],\n   
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
  "body_end": "006a2b76",
  "body_span_bytes": 87,
  "body_start": "006a2b20",
  "callees": [
    "FUN_00685a30",
    "FUN_0092cb00",
    "FUN_00612b20"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a2b20",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::DirectPropertyList::Clear",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "DirectPropertyList *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x2a2b20",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::DirectPropertyList::Clear(DirectPropertyList * this)",
  "size_bytes": 87,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a2b20",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408870"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "014088b8"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__Clear.c",
  "file": "src/reconstruction/pkg_direct_property_clear_wave14/006a2b20_direct_property_list_clear.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__Clear.c",
    "reconstruction/staging/pkg-direct-property-clear-wave14/006a2b20_direct_property_list_clear.cpp",
    "src/reconstruction/pkg_direct_property_clear_wave14/006a2b20_direct_property_list_clear.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-direct-property-clear-wave14/006a2b20.json"
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
    "No original-process invocation and no indirect-caller trace were captured for 0x006a2b20, so the reachability of this body through the shared vtable 0x01408870, and the real values held at receiver+0x38 and receiver+0x3c, remain runtime gates.",
    "No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408870 is a runtime gate.",
    "The real body of 0x00612b20 is not reproduced here beyond its observed 0x18-stride move and its degenerate-range return. Its non-empty movement path remains unmodelled.",
    "The real body of 0x00685a30 is not reproduced here beyond its 0x18-stride traversal. Its per-entry release call to 0x0093db80 on the sub-object at entry+4, taken when byte entry+0x14 has its 0x4 bit set, is out of scope for this record.",
    "The real body of 0x0092cb00 is not reproduced here beyond its observed dword-fill contract. Its count word is read from receiver+0x38, whose meaning and initial value this body never establishes."
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
  "DirectPropertyList",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01408870"
]
```

## Conflicts

```json
[]
```
