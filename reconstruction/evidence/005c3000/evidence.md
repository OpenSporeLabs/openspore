# Evidence 0x005c3000

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `fdece4baec41dece08cea17948ba5a442d86e0651d35f5302c52754ec4b1bb81`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall, receiver only, no stack arguments",
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_width_bytes": 0,
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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "EBX",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path"
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
  "content_sha256": "37b23c84f887d1991875652e563e43e1242fd0d46508c081bd37f9af53c2c010",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall, receiver only, no stack arguments"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 7,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0053"
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
        "obs-0008",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          16,
          28,
          32,
          36,
          40,
          44,
          108,
          116,
          120
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0008",
        "obs-0011",
        "obs-0053"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0053"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x005c3000",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x18",
      "sub": 24
    },
    {
      "at": "0x005c3000",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x18",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x005c3003",
      "count": 1,
      "first_use": 1,
      "first_write_index": 11,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x005c3004",
      "count": 13,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005c3005",
      "count": 8,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005c3005",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x005c3007",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x78]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005c300d",
      "definite": true,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x10]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005c301d",
      "definite": true,
      "id": "obs-0009",
      "index": 11,
      "kind": "REG_WRITE",
      "raw": "SETGE BL",
      "reg": "EBX",
      "write_kind": "unknown"
    },
    {
      "at": "0x005c3020",
      "id": "obs-0010",
      "index": 12,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x008105b0",
      "target": "0x008105b0"
    },
    {
      "at": "0x005c302a",
      "count": 25,
      "first_use": 15,
      "first_write_index": 4,
      "id": "obs-0011",
      "index": 15,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [EAX + 0x10]",
      "reg": "EAX"
    },
    {
      "at": "0x005c302d",
      "count": 24,
      "first_use": 16,
      "first_write_index": 0,
      "id": "obs-0012",
      "index": 16,
      "kind": "REG_READ",
      "raw": "SETNZ byte ptr [ESP + 0xb]",
      "reg": "ESP"
    },
    {
      "at": "0x005c302d"
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
    "va": "0x005c50b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005c51e0"
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
  "count": 122,
  "instructions": [
    {
      "address": "005c3000",
      "instruction": "SUB ESP,0x18"
    },
    {
      "address": "005c3003",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005c3004",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005c3005",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005c3007",
      "instruction": "MOV EAX,dword ptr [ESI + 0x78]"
    },
    {
      "address": "005c300a",
      "instruction": "SUB EAX,dword ptr [ESI + 0x74]"
    },
    {
      "address": "005c300d",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "005c3010",
      "instruction": "AND EAX,0xfffffffc"
    },
    {
      "address": "005c3013",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005c3015",
      "instruction": "CMP EAX,0x4"
    },
    {
      "address": "005c3018",
      "instruction": "PUSH 0x5d3f56b"
    },
    {
      "address": "005c301d",
      "instruction": "SETGE BL"
    },
    {
      "address": "005c3020",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005c3025",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005c3027",
      "instruction": "MOV EAX,dword ptr [ESI + 0x6c]"
    },
    {
      "address": "005c302a",
      "instruction": "MOV ECX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "005c302d",
      "instruction": "SETNZ byte ptr [ESP + 0xb]"
    },
    {
      "address": "005c3032",
      "instruction": "SUB ECX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "005c3035",
      "instruction": "AND ECX,0xfffffffc"
    },
    {
      "address": "005c3038",
      "instruction": "CMP ECX,0x4"
    },
    {
      "address": "005c303b",
      "instruction": "JG 0x005c3048"
    },
    {
      "address": "005c303d",
      "instruction": "CMP byte ptr [EAX + 0x70],0x0"
    },
    {
      "address": "005c3041",
      "instruction": "MOV byte ptr [ESP + 0xa],0x0"
    },
    {
      "address": "005c3046",
      "instruction": "JZ 0x005c304d"
    },
    {
      "address": "005c3048",
      "instruction": "MOV byte ptr [ESP + 0xa],0x1"
    },
    {
      "address": "005c304d",
      "instruction": "MOV EDX,dword ptr [0x015fd918]"
    },
    {
      "address": "005c3053",
      "instruction": "MOV EAX,dword ptr [EDX + 0x3c]"
    },
    {
      "address": "005c3056",
      "instruction": "CMP dword ptr [EAX + 0x118],0x0"
    },
    {
      "address": "005c305d",
      "instruction": "JZ 0x005c306d"
    },
    {
      "address": "005c305f",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005c3061",
      "instruction": "CALL 0x005c2aa0"
    },
    {
      "address": "005c3066",
      "instruction": "CMP EAX,0x1"
    },
    {
      "address": "005c3069",
      "instruction": "JGE 0x005c306d"
    },
    {
      "address": "005c306b",
      "instruction": "XOR BL,BL"
    },
    {
      "address": "005c306d",
      "instruction": "MOVSS XMM0,dword ptr [0x01486110]"
    },
    {
      "address": "005c3075",
      "instruction": "MOVSS dword ptr [ESP + 0xc],XMM0"
    },
    {
      "address": "005c307b",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "005c307d",
      "instruction": "JZ 0x005c30a0"
    },
    {
      "address": "005c307f",
      "instruction": "MOV ECX,dword ptr [ESI + 0x20]"
    },
    {
      "address": "005c3082",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "005c3084",
      "instruction": "JZ 0x005c30a0"
    },
    {
      "address": "005c3086",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "005c3088",
      "instruction": "MOV EAX,dword ptr [EDX + 0x38]"
    },
    {
      "address": "005c308b",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c308d",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0xc]"
    },
    {
      "address": "005c3092",
      "instruction": "ADDSS XMM0,dword ptr [0x01486110]"
    },
    {
      "address": "005c309a",
      "instruction": "MOVSS dword ptr [ESP + 0xc],XMM0"
    },
    {
      "address": "005c30a0",
      "instruction": "CMP byte ptr [ESP + 0xb],0x0"
    },
    {
      "address": "005c30a5",
      "instruction": "JZ 0x005c3117"
    },
    {
      "address": "005c30a7",
      "instruction": "MOV ECX,dword ptr [ESI + 0x24]"
    },
    {
      "address": "005c30aa",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "005c30ac",
      "instruction": "JZ 0x005c3117"
    },
    {
      "address": "005c30ae",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "005c30b0",
      "instruction": "MOV EAX,dword ptr [EDX + 0x38]"
    },
    {
      "address": "005c30b3",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c30b5",
      "instruction": "MOVSS XMM0,dword ptr [EAX]"
    },
    {
      "address": "005c30b9",
      "instruction": "MOV ECX,dword ptr [ESI + 0x24]"
    },
    {
      "address": "005c30bc",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM0"
    },
    {
      "address": "005c30c2",
      "instruction": "MOVSS XMM1,dword ptr [EAX + 0x4]"
    },
    {
      "address": "005c30c7",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM1"
    },
    {
      "address": "005c30cd",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x8]"
    },
    {
      "address": "005c30d2",
      "instruction": "MOVSS dword ptr [ESP + 0x18],XMM0"
    },
    {
      "address": "005c30d8",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0xc]"
    },
    {
      "address": "005c30dd",
      "instruction": "SUBSS XMM0,XMM1"
    },
    {
      "address": "005c30e1",
      "instruction": "MOVSS XMM1,dword ptr [ESP + 0xc]"
    },
    {
      "address": "005c30e7",
      "instruction": "ADDSS XMM0,XMM1"
    },
    {
      "address": "005c30eb",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM1"
    },
    {
      "address": "005c30f1",
      "instruction": "MOVSS dword ptr [ESP + 0x1c],XMM0"
    },
   
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
  "original_bytes": 8243,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall, receiver only, no stack arguments\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:OpaqueRect\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE10\",\n      \"score\": 17,\n      \"symbol\": \"page_visible_slots_refresh_005c0a60\",\n      \"va\": \"0x005c0a60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"property_value_resolve_0041e920\",\n      \"va\": \"0x0041e920\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"sporepedia_asset_destroy_00642190\",\n      \"va\": \"0x00642190\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaquePalette\",\n  \"cluster\": null,\n  \"confidence\": 0.88,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005c50b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005c51e0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005c51c4\",\n        \"direction\": \"in\",\n        \"other\": \"0x005c50b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c5220\",\n        \"direction\": \"in\",\n        \"other\": \"0x005c51e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c3061\",\n        \"direction\": \"out\",\n        \"other\": \"0x005c2aa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c3020\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 2,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x008105b0\",\n      \"0x005c2aa0\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0115\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"palette_row_layout_005c3000\",\n  \"normalized_symbol\": \"palette_row_layout_005c3000\",\n  \"observed_mechanics\": [\n    \"Compute the row span from the rows vector at +0x74 and +0x78, clear the low two bits and set the stacked decision when the result is at least 4.\",\n    \"Query the feature port 0x008105b0 with the fixed feature id 0x05d3f56b and count 1 on the feature host at +0x10.\",\n    \"Derive the wide decision from the group vector at group+0x0c and +0x10 cleared by 0xfffffffc greater than 4, or the group byte at +0x70.\",\n    \"Clear the stacked decision when the application property flag at +0x118 is nonzero and the distinct row port 0x005c2aa0 returns below 1.\",\n    \"Seed the running offset from the row gap global 0x01486110.\",\n    \"When stacked and the lead at +0x20 is non null, raise the offset to the lead height plus the gap.\",\n    \"When the feature is present and the title at +0x24 is non null, apply {x, offset, w, (h - y) + offset} and continue the chain from the applied height plus the gap.\",\n    \"When the body at +0x28 is null, return without touching any element.\",\n    \"When wide and the host at +0x1c is non null, take the body height from host.y minus the gap.\",\n    \"Otherwise when the tail at +0x2c is non null, take the body height from (tail.h - tail.y) minus the gap.\",\n    \"Apply the body rectangle through the element vtable slot +0x6c exactly once.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-PALETTE-SAFE-WAVE10\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-PALETTE-SAFE-WAVE10\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-PALETTE-SAFE-WAVE10\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"The element vtable owner behind slot +0x38 and +0x6c is unattributed in the live database.\",\n      \"The feature query port 0x008105b0 and the distinct row port 0x005c2aa0 are opaque seams and are not promoted.\",\n      \"The group pointer at +0x6c is dereferenced without a null c
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
  "body_end": "005c31b6",
  "body_span_bytes": 439,
  "body_start": "005c3000",
  "callees": [
    "FUN_008105b0",
    "FUN_005c2aa0"
  ],
  "callers": [
    "FUN_005c51e0",
    "FUN_005c50b0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005c3000",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "local_15",
      "storage": "Stack[-0x15]:1",
      "type": "undefined1"
    },
    {
      "name": "local_16",
      "storage": "Stack[-0x16]:1",
      "type": "undefined1"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_005c3000",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1c3000",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005c3000(void)",
  "size_bytes": 439,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005c3000",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "005c51c4"
    },
    {
      "from": "005c5220"
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
  "file": "src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.cpp",
    "src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.hpp",
    "src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-palette-safe-wave10/005c3000.json"
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
    "The element vtable owner behind slot +0x38 and +0x6c is unattributed in the live database.",
    "The feature query port 0x008105b0 and the distinct row port 0x005c2aa0 are opaque seams and are not promoted.",
    "The group pointer at +0x6c is dereferenced without a null check, exactly as the native body does.",
    "The row gap global at 0x01486110 is modelled as a float whose runtime value is not established.",
    "The semantic identity of the feature id 0x05d3f56b is inferred from the call shape only.",
    "gate-palette-row-layout-runtime-group-and-feature-values",
    "runtime validation not performed; static decompilation and disassembly only",
    "the element vtable owner behind slot +0x38 and +0x6c is unattributed in the live database",
    "the feature query port 0x008105b0 and the distinct row port 0x005c2aa0 are opaque seams and are not promoted",
    "the group vector at group+0x0c/+0x10 is dereferenced without a null group check, exactly as the native body does",
    "the row gap global at 0x01486110 is modelled as a float whose runtime value is not established",
    "the semantic identity of the feature id 0x05d3f56b is inferred from the call shape only"
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
  "OpaqueApp",
  "OpaqueAppProps",
  "OpaqueElement",
  "OpaquePalette",
  "OpaquePalette*",
  "OpaquePaletteGroup",
  "OpaqueRect",
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
