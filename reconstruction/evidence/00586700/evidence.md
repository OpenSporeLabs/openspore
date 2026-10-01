# Evidence 0x00586700

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `79c77d444ca1657a5af6ce7b039074a7f2f5909d5106c4a6f4ae881ea0d7017c`

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
  "receiver_register": "ECX",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
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
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "850431559517498532628bc6f0e38ad006e9d1645cbc9f80f7730d34765ba5a2",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0042"
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
        "obs-0013",
        "obs-0014"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          1240,
          1260,
          1288,
          1292
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0013",
        "obs-0014",
        "obs-0042"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0042"
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
        "obs-0042"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0042"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00586700",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0xc",
      "sub": 12
    },
    {
      "at": "0x00586700",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0xc",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00586703",
      "count": 7,
      "first_use": 1,
      "first_write_index": 30,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00586704",
      "count": 9,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00586705",
      "count": 3,
      "first_use": 3,
      "first_write_index": 9,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EBP,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00586705",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ECX",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x00586707",
      "base": "EBP",
      "disp": 1240,
      "id": "obs-0007",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + 0x4d8]",
      "reason": "untrusted_frame",
      "resolved": false,
      "size": 4,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x00586707",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + 0x4d8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0058670d",
      "count": 13,
      "first_use": 5,
      "first_write_index": 46,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0058670e",
      "base": "EBP",
      "disp": 1240,
      "id": "obs-0010",
      "index": 6,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "
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
  "count": 89,
  "instructions": [
    {
      "address": "00586700",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "00586703",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00586704",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00586705",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00586707",
      "instruction": "MOV EAX,dword ptr [EBP + 0x4d8]"
    },
    {
      "address": "0058670d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0058670e",
      "instruction": "LEA ESI,[EBP + 0x4d8]"
    },
    {
      "address": "00586714",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00586715",
      "instruction": "MOV EDI,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00586718",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0058671a",
      "instruction": "SUB ECX,EAX"
    },
    {
      "address": "0058671c",
      "instruction": "CMP ECX,0x23"
    },
    {
      "address": "0058671f",
      "instruction": "JNC 0x0058673b"
    },
    {
      "address": "00586721",
      "instruction": "LEA EDX,[ESP + 0x13]"
    },
    {
      "address": "00586725",
      "instruction": "SUB EAX,EDI"
    },
    {
      "address": "00586727",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00586728",
      "instruction": "ADD EAX,0x23"
    },
    {
      "address": "0058672b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0058672c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0058672d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0058672f",
      "instruction": "MOV byte ptr [ESP + 0x1f],0x0"
    },
    {
      "address": "00586734",
      "instruction": "CALL 0x005151b0"
    },
    {
      "address": "00586739",
      "instruction": "JMP 0x00586752"
    },
    {
      "address": "0058673b",
      "instruction": "LEA EBX,[EAX + 0x23]"
    },
    {
      "address": "0058673e",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00586740",
      "instruction": "SUB EAX,EDI"
    },
    {
      "address": "00586742",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00586743",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00586744",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00586745",
      "instruction": "CALL 0x011e0744"
    },
    {
      "address": "0058674a",
      "instruction": "SUB EBX,EDI"
    },
    {
      "address": "0058674c",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "0058674f",
      "instruction": "ADD dword ptr [ESI + 0x4],EBX"
    },
    {
      "address": "00586752",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00586754",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00586756",
      "instruction": "MOV byte ptr [EAX + ECX*0x1],0x0"
    },
    {
      "address": "0058675a",
      "instruction": "INC EAX"
    },
    {
      "address": "0058675b",
      "instruction": "CMP EAX,0x23"
    },
    {
      "address": "0058675e",
      "instruction": "JL 0x00586754"
    },
    {
      "address": "00586760",
      "instruction": "LEA EDX,[EBP + 0x4f0]"
    },
    {
      "address": "00586766",
      "instruction": "MOV dword ptr [EBP + 0x4ec],0x0"
    },
    {
      "address": "00586770",
      "instruction": "MOV dword ptr [ESP + 0x14],EDX"
    },
    {
      "address": "00586774",
      "instruction": "ADD EBP,0x50c"
    },
    {
      "address": "0058677a",
      "instruction": "MOV dword ptr [ESP + 0x18],0x6"
    },
    {
      "address": "00586782",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00586786",
      "instruction": "MOV dword ptr [EAX],0x0"
    },
    {
      "address": "0058678c",
      "instruction": "MOV ESI,dword ptr [EBP]"
    },
    {
      "address": "0058678f",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "00586792",
      "instruction": "LEA EDI,[EBP + -0x4]"
    },
    {
      "address": "00586795",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00586797",
      "instruction": "SUB ECX,EAX"
    },
    {
      "address": "00586799",
      "instruction": "CMP ECX,0x23"
    },
    {
      "address": "0058679c",
      "instruction": "JNC 0x005867b8"
    },
    {
      "address": "0058679e",
      "instruction": "LEA EDX,[ESP + 0x13]"
    },
    {
      "address": "005867a2",
      "instruction": "SUB EAX,ESI"
    },
    {
      "address": "005867a4",
      "instruction": "PUSH EDX"
    },
    {
      "address": "005867a5",
      "instruction": "ADD EAX,0x23"
    },
    {
      "address": "005867a8",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005867a9",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005867aa",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "005867ac",
      "instruction": "MOV byte ptr [ESP + 0x1f],0x0"
    },
    {
      "address": "005867b1",
      "instruction": "CALL 0x005151b0"
    },
    {
      "address": "005867b6",
      "instruction": "JMP 0x005867cf"
    },
    {
      "address": "005867b8",
      "instruction": "LEA EBX,[EAX + 0x23]"
    },
    {
      "address": "005867bb",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "005867bd",
      "instruction": "SUB EAX,ESI"
    },
    {
      "address": "005867bf",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005867c0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005867c1",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005867c2",
      "instruction": "CALL 0x011e0744"
    },
    {
      "address": "005867c7",
      "instruction": "SUB EBX,ESI"
    },
    {
      "address": "005867c9",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "005867cc",
      "instruction": "ADD dword ptr [EBP],EBX"
    },
    {
      "address": "005867cf",

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
  "original_bytes": 9644,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver_register\": \"ECX\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00586734\",\n        \"direction\": \"out\",\n        \"other\": \"0x005151b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005867b1\",\n        \"direction\": \"out\",\n        \"other\": \"0x005151b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00586745\",\n        \"direction\": \"out\",\n        \"other\": \"0x011e0744\",\n        \"reference_type\": \"thunk\"\n      },\n      {\n        \"callsite\": \"0x005867c2\",\n        \"direction\": \"out\",\n        \"other\": \"0x011e0744\",\n        \"reference_type\": \"thunk\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0076\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS -- no data-segment address in the listing and none in the span\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00586700\",\n  \"normalized_symbol\": \"FUN_00586700\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w2-00586700/sw2_00586700.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00586700/sw2_00586700_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00586700/sw2_00586700_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w2-00586700/00586700.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Editor\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"editor-core\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00586700\",\n    \"name\": \"FUN_00586700\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"013f57f8\"\n      ]\n    },\n    \"queue_state\": \"candidate\",\n    \"rank\": 214\n  },\n  \"types\": [],\n  \"unresolved_questions\": [\n    \"EVIDENCE COVERAGE is a WARN because 10 of the 1
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
  "body_end": "005867f3",
  "body_span_bytes": 244,
  "body_start": "00586700",
  "callees": [
    "memcpy",
    "FUN_005151b0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00586700",
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
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_9",
      "storage": "Stack[-0x9]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00586700",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x186700",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00586700(void)",
  "size_bytes": 244,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00586700",
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
      "from": "013f5848"
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
  "global:PASS -- no data-segment address in the listing and none in the span"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00586700/sw2_00586700.cpp",
    "reconstruction/staging/pkg-swarm-w2-00586700/sw2_00586700_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00586700/sw2_00586700_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00586700/00586700.json"
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
[]
```
