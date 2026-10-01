# Evidence 0x011f9710

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3e7d9bd2d0fef2556e711e6b722b58fa8bbb260983dea4eb5c115c4ae6de1d03`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "Mesh*",
  "return_register": null,
  "return_type": "void",
  "stack_arguments": [],
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
    "flow_not_modelled: the linear ESP walk ends at +64, so the listing is not one path"
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
  "content_sha256": "47b81ba7a3b9874abb8b6c7ca010c4e555c02c467773f4abf6c60a1bcecbd6cc",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall observed"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0046",
        "obs-0052"
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
        "obs-0004",
        "obs-0005",
        "obs-0012",
        "obs-0024",
        "obs-0032",
        "obs-0040"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          16,
          36
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0012",
        "obs-0024",
        "obs-0032",
        "obs-0040",
        "obs-0046",
        "obs-0052"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0046",
        "obs-0052"
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
        "obs-0046",
        "obs-0052"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0046",
        "obs-0052"
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
      "and_esp": null,
      "at": "0x011f9710",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 23,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x011f9710",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x011f9713",
      "count": 21,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x011f9714",
      "count": 13,
      "first_use": 2,
      "first_write_index": 13,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x011f9714",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x011f9716",
      "count": 16,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP + 0x10],ESI",
      "reg": "ESP"
    },
    {
      "at": "0x011f9716",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP + 0x10],ESI",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x011f971a",
      "id": "obs-0008",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x011f21a0",
      "target": "0x011f21a0"
    },
    {
      "at": "0x011f971f",
      "definite": true,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016f6568]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x011f9724",
      "count": 33,
      "first_use": 6,
      "first_write_index": 5,
      "id": "obs-0010",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x14]",
      "reg": "EAX"
    },
    {
      "at": "0x011f9728",
      "base": "EAX",
      "disp": null,
      "id": "obs-0011",
      "i
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006e7110"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006e7270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006eae40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0073ede0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00759ec0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00faef10"
  }
]
```

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
  "count": 173,
  "instructions": [
    {
      "address": "011f9710",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "011f9713",
      "instruction": "PUSH ESI"
    },
    {
      "address": "011f9714",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "011f9716",
      "instruction": "MOV dword ptr [ESP + 0x10],ESI"
    },
    {
      "address": "011f971a",
      "instruction": "CALL 0x011f21a0"
    },
    {
      "address": "011f971f",
      "instruction": "MOV EAX,[0x016f6568]"
    },
    {
      "address": "011f9724",
      "instruction": "MOV EAX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "011f9727",
      "instruction": "PUSH ESI"
    },
    {
      "address": "011f9728",
      "instruction": "CALL EAX"
    },
    {
      "address": "011f972a",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "011f972d",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "011f972f",
      "instruction": "JZ 0x011f9910"
    },
    {
      "address": "011f9735",
      "instruction": "MOV dword ptr [0x016f9110],0x0"
    },
    {
      "address": "011f973f",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "011f9742",
      "instruction": "CMP ECX,0x1"
    },
    {
      "address": "011f9745",
      "instruction": "JNZ 0x011f9757"
    },
    {
      "address": "011f9747",
      "instruction": "MOV EAX,dword ptr [ESI + 0x24]"
    },
    {
      "address": "011f974a",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "011f974d",
      "instruction": "MOV [0x01718614],EAX"
    },
    {
      "address": "011f9752",
      "instruction": "MOV [0x01718618],EAX"
    },
    {
      "address": "011f9757",
      "instruction": "PUSH EBX"
    },
    {
      "address": "011f9758",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "011f975a",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "011f975c",
      "instruction": "PUSH EBP"
    },
    {
      "address": "011f975d",
      "instruction": "PUSH EDI"
    },
    {
      "address": "011f975e",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "011f9762",
      "instruction": "JBE 0x011f9818"
    },
    {
      "address": "011f9768",
      "instruction": "ADD ESI,0x24"
    },
    {
      "address": "011f976b",
      "instruction": "MOV EBX,0x16f913c"
    },
    {
      "address": "011f9770",
      "instruction": "MOV dword ptr [ESP + 0x18],ESI"
    },
    {
      "address": "011f9774",
      "instruction": "MOV EDI,dword ptr [ESI]"
    },
    {
      "address": "011f9776",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "011f9778",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "011f977a",
      "instruction": "CMP EDI,ESI"
    },
    {
      "address": "011f977c",
      "instruction": "MOV dword ptr [ESP + 0x14],ESI"
    },
    {
      "address": "011f9780",
      "instruction": "JZ 0x011f97b7"
    },
    {
      "address": "011f9782",
      "instruction": "MOV ECX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "011f9785",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "011f9787",
      "instruction": "MOVZX EBP,byte ptr [EDX + 0xf]"
    },
    {
      "address": "011f978b",
      "instruction": "MOV dword ptr [ESP + 0x14],ECX"
    },
    {
      "address": "011f978f",
      "instruction": "CALL 0x011f8af0"
    },
    {
      "address": "011f9794",
      "instruction": "TEST byte ptr [EAX + 0xd4],0x1"
    },
    {
      "address": "011f979b",
      "instruction": "JZ 0x011f97b1"
    },
    {
      "address": "011f979d",
      "instruction": "MOV ESI,dword ptr [EDI + 0x8]"
    },
    {
      "address": "011f97a0",
      "instruction": "IMUL ESI,EBP"
    },
    {
      "address": "011f97a3",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "011f97a5",
      "instruction": "MOV [0x01718614],EAX"
    },
    {
      "address": "011f97aa",
      "instruction": "MOV [0x01718618],EAX"
    },
    {
      "address": "011f97af",
      "instruction": "JMP 0x011f97b3"
    },
    {
      "address": "011f97b1",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "011f97b3",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "011f97b7",
      "instruction": "MOV EDX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "011f97bb",
      "instruction": "CMP dword ptr [EBX + -0x4],EDX"
    },
    {
      "address": "011f97be",
      "instruction": "JNZ 0x011f97c9"
    },
    {
      "address": "011f97c0",
      "instruction": "CMP dword ptr [EBX],ESI"
    },
    {
      "address": "011f97c2",
      "instruction": "JNZ 0x011f97c9"
    },
    {
      "address": "011f97c4",
      "instruction": "CMP dword ptr [EBX + 0x4],EBP"
    },
    {
      "address": "011f97c7",
      "instruction": "JZ 0x011f97f4"
    },
    {
      "address": "011f97c9",
      "instruction": "MOV ECX,dword ptr [0x016f89d0]"
    },
    {
      "address": "011f97cf",
      "instruction": "MOV EDI,dword ptr [ECX]"
    },
    {
      "address": "011f97d1",
      "instruction": "PUSH EBP"
    },
    {
      "address": "011f97d2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "011f97d3",
      "instruction": "PUSH EDX"
    },
    {
      "address": "011f97d4",
      "instruction": "PUSH EAX"
    },
    {
      "address": "011f97d5",
      "instruction": "PUSH ECX"
    },
    {
      "address": "011f97d6",
      "instruction": "CALL dword ptr [EDI + 0x190]"
    },
    {
      "address": "011f97dc",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "011f97de",
      "instruction": "JL 0x011f990d"
    },
    {
      "address": "011f97e4",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "011f97e8",
      "instruction": "MOV dword ptr [EBX + -0x4],EAX"
    },
    {
      "address": "011f97eb",
      "instruction":
[TRUNCATED]
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
  "original_bytes": 8330,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"Mesh*\",\n    \"return_register\": null,\n    \"return_type\": \"void\",\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:IndexBuffer,Mesh,Mesh*,MeshBoundaryPorts\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 30,\n      \"symbol\": \"renderware_mesh_set_indices_count_011f96e0\",\n      \"va\": \"0x011f96e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 10,\n      \"symbol\": \"transform_pre_transform_by_0040ccb0\",\n      \"va\": \"0x0040ccb0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 8,\n      \"symbol\": \"graphics_global_state_set_transform_005291f0\",\n      \"va\": \"0x005291f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 2,\n      \"symbol\": \"wave6_reference_00432a50\",\n      \"va\": \"0x00432a50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-RESOURCE-ADAPTER\",\n      \"score\": 2,\n      \"symbol\": \"TexturePtr_Set\",\n      \"va\": \"0x00576650\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"editor_query_reset_005dd750\",\n      \"va\": \"0x005dd750\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 2,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Preparation gate, four-triple cache, stream publication and clearing, count selection, primitive/indexed draw branches, index binding, and negative-error returns are preserved; runtime graphics state remains unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"D3D device vtable calls are represented as package-local typed ports despite verified imported-slot identities.\",\n    \"No runtime D3D or RenderWare mesh trace is available.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"Mesh\",\n  \"cluster\": null,\n  \"confidence\": 0.91,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006e7110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006e7270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006eae40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0073ede0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00759ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00faef10\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006e7238\",\n        \"direction\": \"in\",\n        \"other\": \"0x006e7110\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006e738d\",\n        \"direction\": \"in\",\n        \"other\": \"0x006e7270\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006eb272\",\n        \"direction\": \"in\",\n        \"other\": \"0x006eae40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0073eff1\",\n        \"direction\": \"in\",\n        \"other\": \"0x0073ede0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00759fc5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00759ec0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00faef7b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00faef10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x011f971a\",\n        \"direction\": \"out\",\n        \"other\": \"0x011f21a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x011f978f\",\n        \"direction\": \"out\",\n        \"other\": \"0x011f8af0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x011f9884\",\n        \"direction\": \"out\",\n        \"other\": \"0x011f95c0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 6,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x011f21a0\",\n      \"0x011f8af0\",\n      \"0x011f95c0\",\n      \"D3D vtable +0x144\",\n      \"D3D vtable +0x148\",\n      \"D3D vtable +0x190\",\n      \"D3D vtable +0x1a0\"\n    ],\n    \"manifest_callers\": [\n      \"direct_caller_functions_6\",\n      \"function_xrefs_6\"\n    ],\n    \"nearby_reconstructed\": [],\n 
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
  "body_end": "011f9914",
  "body_span_bytes": 517,
  "body_start": "011f9710",
  "callees": [
    "FUN_011f8af0",
    "FUN_011f95c0",
    "FUN_011f21a0"
  ],
  "callers": [
    "FUN_006e7110",
    "FUN_00faef10",
    "FUN_006e7270",
    "FUN_0073ede0",
    "FUN_006eae40",
    "FUN_00759ec0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "011f9710",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "RenderWare::Mesh::SetIndexBuffer",
  "namespace": "RenderWare",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "Mesh *"
    },
    {
      "name": "pBuffer",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "IndexBuffer *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0xdf9710",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void RenderWare::Mesh::SetIndexBuffer(Mesh * this, IndexBuffer * pBuffer)",
  "size_bytes": 517,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x011f9710",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "006e7238"
    },
    {
      "from": "006e738d"
    },
    {
      "from": "006eb272"
    },
    {
      "from": "0073eff1"
    },
    {
      "from": "00759fc5"
    },
    {
      "from": "00faef7b"
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
  "file": "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
  "files": [
    "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
    "src/reconstruction/wave6_presentation/presentation_boundary.hpp",
    "src/reconstruction/wave6_presentation/presentation_boundary_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-presentation/011f9710.json"
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
    "gate-renderware-d3d-stream-draw-and-index-state"
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
  "D3dBoundaryPorts",
  "GraphicsActiveState",
  "IndexBuffer",
  "Mesh",
  "Mesh*",
  "MeshBoundaryPorts",
  "VertexBuffer",
  "void"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
