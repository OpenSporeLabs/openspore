# Evidence 0x005a2600

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7a5aa4527ec89212df7ace44c0f4983fe0419314dfb4c54fa4089901d733d12a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "ST0 (per the machine record; nothing is produced there, see return_semantics.record_disagreement)",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBX",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +84, so the listing is not one path"
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
  "content_sha256": "a182c4b353045d8006fb2c06b95479f87b9d8d38fb21281021e9c329e726a6c8",
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
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 28,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0051",
        "obs-0055",
        "obs-0059",
        "obs-0063"
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
        "obs-0001",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0019",
        "obs-0040",
        "obs-0044",
        "obs-0050",
        "obs-0054",
        "obs-0058",
        "obs-0062"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          16,
          20,
          24,
          28,
          40,
          48,
          52,
          56,
          60,
          64,
          68,
          72,
          76,
          80,
          84,
          88,
          92,
          96,
          100,
          104,
          108,
          112,
          156
        ],
        "register": "ECX",
        "written_through": 18
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0019",
        "obs-0040",
        "obs-0044",
        "obs-0050",
        "obs-0051",
        "obs-0054",
        "obs-0055",
        "obs-0058",
        "obs-0059",
        "obs-0062",
        "obs-0063"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0051",
        "obs-0055",
        "obs-0059",
        "obs-0063"
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
        "obs-0063"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x005a2600",
      "count": 99,
      "first_use": 0,
      "first_write_index": 4,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005a2601",
      "count": 1,
      "first_use": 1,
      "first_write_index": 10,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x005a2602",
      "count": 54,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005a2603",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x005a2605",
      "definite": true,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x10]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005a260f",
      "definite": true,
      "id": "obs-0006",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005a2611",
      "count": 84,
      "first_use": 7,
      "first_write_index": 6,
      "id": "obs-0007",
      "index": 7,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x1c]",
      "reg": "EAX"
    },
    {
      "at": "0x005a2611",
      "definite": true,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x1c]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005a2619",
      "count": 30,
      "first_use": 9,
      "first_write_index": 7,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x005a2619",
      "base": "EDX",
      "disp": null,
      "id": "obs-0010",
      "index": 9,
      "kind": "CALL_INDIRECT",
      "raw": "CALL 
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
    "va": "0x005a3220"
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
  "count": 450,
  "instructions": [
    {
      "address": "005a2600",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005a2601",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005a2602",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005a2603",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005a2605",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "005a2608",
      "instruction": "MOV byte ptr [ESI + 0x9c],0x0"
    },
    {
      "address": "005a260f",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005a2611",
      "instruction": "MOV EDX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "005a2614",
      "instruction": "PUSH 0xc7c4f8"
    },
    {
      "address": "005a2619",
      "instruction": "CALL EDX"
    },
    {
      "address": "005a261b",
      "instruction": "MOV BL,0x30"
    },
    {
      "address": "005a261d",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "005a261f",
      "instruction": "JZ 0x005a265e"
    },
    {
      "address": "005a2621",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "005a2624",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005a2626",
      "instruction": "MOV EDX,dword ptr [EAX + 0x28]"
    },
    {
      "address": "005a2629",
      "instruction": "PUSH 0xc7c4f8"
    },
    {
      "address": "005a262e",
      "instruction": "CALL EDX"
    },
    {
      "address": "005a2630",
      "instruction": "MOVZX ECX,word ptr [EAX + 0x12]"
    },
    {
      "address": "005a2634",
      "instruction": "CMP CX,0xd"
    },
    {
      "address": "005a2638",
      "instruction": "JZ 0x005a2647"
    },
    {
      "address": "005a263a",
      "instruction": "CMP CX,0x10"
    },
    {
      "address": "005a263e",
      "instruction": "JZ 0x005a2647"
    },
    {
      "address": "005a2640",
      "instruction": "MOV ECX,0x15d1168"
    },
    {
      "address": "005a2645",
      "instruction": "JMP 0x005a2659"
    },
    {
      "address": "005a2647",
      "instruction": "TEST byte ptr [EAX + 0x10],BL"
    },
    {
      "address": "005a264a",
      "instruction": "JZ 0x005a2650"
    },
    {
      "address": "005a264c",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "005a264e",
      "instruction": "JMP 0x005a2659"
    },
    {
      "address": "005a2650",
      "instruction": "MOVZX ECX,CX"
    },
    {
      "address": "005a2653",
      "instruction": "NEG ECX"
    },
    {
      "address": "005a2655",
      "instruction": "SBB ECX,ECX"
    },
    {
      "address": "005a2657",
      "instruction": "AND ECX,EAX"
    },
    {
      "address": "005a2659",
      "instruction": "FLD float ptr [ECX]"
    },
    {
      "address": "005a265b",
      "instruction": "FSTP float ptr [ESI + 0x14]"
    },
    {
      "address": "005a265e",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "005a2661",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005a2663",
      "instruction": "MOV EDX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "005a2666",
      "instruction": "PUSH 0xc7c4fa"
    },
    {
      "address": "005a266b",
      "instruction": "CALL EDX"
    },
    {
      "address": "005a266d",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "005a266f",
      "instruction": "JZ 0x005a26ae"
    },
    {
      "address": "005a2671",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "005a2674",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005a2676",
      "instruction": "MOV EDX,dword ptr [EAX + 0x28]"
    },
    {
      "address": "005a2679",
      "instruction": "PUSH 0xc7c4fa"
    },
    {
      "address": "005a267e",
      "instruction": "CALL EDX"
    },
    {
      "address": "005a2680",
      "instruction": "MOVZX ECX,word ptr [EAX + 0x12]"
    },
    {
      "address": "005a2684",
      "instruction": "CMP CX,0xd"
    },
    {
      "address": "005a2688",
      "instruction": "JZ 0x005a2697"
    },
    {
      "address": "005a268a",
      "instruction": "CMP CX,0x10"
    },
    {
      "address": "005a268e",
      "instruction": "JZ 0x005a2697"
    },
    {
      "address": "005a2690",
      "instruction": "MOV ECX,0x15d1168"
    },
    {
      "address": "005a2695",
      "instruction": "JMP 0x005a26a9"
    },
    {
      "address": "005a2697",
      "instruction": "TEST byte ptr [EAX + 0x10],BL"
    },
    {
      "address": "005a269a",
      "instruction": "JZ 0x005a26a0"
    },
    {
      "address": "005a269c",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "005a269e",
      "instruction": "JMP 0x005a26a9"
    },
    {
      "address": "005a26a0",
      "instruction": "MOVZX ECX,CX"
    },
    {
      "address": "005a26a3",
      "instruction": "NEG ECX"
    },
    {
      "address": "005a26a5",
      "instruction": "SBB ECX,ECX"
    },
    {
      "address": "005a26a7",
      "instruction": "AND ECX,EAX"
    },
    {
      "address": "005a26a9",
      "instruction": "FLD float ptr [ECX]"
    },
    {
      "address": "005a26ab",
      "instruction": "FSTP float ptr [ESI + 0x18]"
    },
    {
      "address": "005a26ae",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "005a26b1",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005a26b3",
      "instruction": "MOV EDX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "005a26b6",
      "instruction": "PUSH 0xc7c4f9"
    },
    {
      "address": "005a26bb",
      "instruction": "CALL EDX"
    },
    {
      "address": "005a26bd",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "005a26bf",
      "instruction": "JZ 0x005a26fe"
    },
    {
      "address": "005a26c1",
      "instruction": "MOV E
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
  "original_bytes": 10696,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"ST0 (per the machine record; nothing is produced there, see return_semantics.record_disagreement)\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f69b4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"editor_camera_func24h_005a2050\",\n      \"va\": \"0x005a2050\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f69b4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"editor_camera_func54h_005a2320\",\n      \"va\": \"0x005a2320\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005a3220\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005a33a8\",\n        \"direction\": \"in\",\n        \"other\": \"0x005a3220\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005a2a4f\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041ea70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005a2a80\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041ea70\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0102\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:WARN\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_005a2600\",\n  \"normalized_symbol\": \"FUN_005a2600\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w2-005a2600/sw2_005a2600.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-005a2600/sw2_005a2600_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-005a2600/sw2_005a2600_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w2-005a2600/005a2600.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Editor\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"editor-core\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:005a2600\",\n    \"name\": \"FUN_005a2600\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"013f69b4\"\n      ]\
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
  "body_end": "005a2b20",
  "body_span_bytes": 1313,
  "body_start": "005a2600",
  "callees": [
    "FUN_0041ea70"
  ],
  "callers": [
    "FUN_005a3220"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005a2600",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005a2600",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1a2600",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005a2600(void)",
  "size_bytes": 1313,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005a2600",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f69b4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "005a33a8"
    },
    {
      "from": "013f6a18"
    }
  ]
}
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:WARN"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-005a2600/sw2_005a2600.cpp",
    "reconstruction/staging/pkg-swarm-w2-005a2600/sw2_005a2600_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-005a2600/sw2_005a2600_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-005a2600/005a2600.json"
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
  "gates": [],
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
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f69b4"
]
```

## Conflicts

```json
[]
```
