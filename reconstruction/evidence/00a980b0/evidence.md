# Evidence 0x00a980b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9e37133623f2ea5bfdcf1880d236510d085c871a464ab81f32b40462e3b349c1`

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
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "XMM0",
  "return_type": "void",
  "saved_registers": [
    "EDI",
    "EBP",
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4 (0x00a981f2, bytes C2 04 00)"
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "EBP",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +48, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "c13803461db3b5ba504b45df3bb05910b85550fcb69b24d8ecc571d9b5be7128",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0044"
      ],
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0044"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0015",
        "obs-0020",
        "obs-0021",
        "obs-0022",
        "obs-0023",
        "obs-0024",
        "obs-0025",
        "obs-0027"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          16,
          20,
          80
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0015",
        "obs-0020",
        "obs-0021",
        "obs-0022",
        "obs-0023",
        "obs-0024",
        "obs-0025",
        "obs-0027",
        "obs-0044"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0044"
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
      "at": "0x00a980b0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 6,
      "raw": "SUB ESP,0x50",
      "sub": 80
    },
    {
      "at": "0x00a980b0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x50",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00a980b3",
      "count": 10,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00a980b4",
      "count": 12,
      "first_use": 2,
      "first_write_index": 16,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00a980b4",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00a980c0",
      "count": 2,
      "first_use": 5,
      "first_write_index": 5,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ",
      "raw": "XORPS XMM0,XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00a980c0",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "XORPS XMM0,XMM0",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00a980c3",
      "count": 11,
      "first_use": 
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
  "count": 112,
  "instructions": [
    {
      "address": "00a980b0",
      "instruction": "SUB ESP,0x50"
    },
    {
      "address": "00a980b3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00a980b4",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00a980b6",
      "instruction": "CMP byte ptr [EDI + 0x10],0x0"
    },
    {
      "address": "00a980ba",
      "instruction": "JNZ 0x00a981ee"
    },
    {
      "address": "00a980c0",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00a980c3",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00a980c4",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00a980c5",
      "instruction": "MOV byte ptr [EDI + 0x10],0x1"
    },
    {
      "address": "00a980c9",
      "instruction": "MOVSS dword ptr [EDI + 0x14],XMM0"
    },
    {
      "address": "00a980ce",
      "instruction": "CALL 0x00883860"
    },
    {
      "address": "00a980d3",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00a980d5",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00a980d7",
      "instruction": "CMP ESI,EBP"
    },
    {
      "address": "00a980d9",
      "instruction": "JZ 0x00a981ec"
    },
    {
      "address": "00a980df",
      "instruction": "MOV EAX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00a980e2",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a980e5",
      "instruction": "SHR ECX,0x3"
    },
    {
      "address": "00a980e8",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00a980eb",
      "instruction": "JZ 0x00a9816c"
    },
    {
      "address": "00a980ed",
      "instruction": "MOV dword ptr [ESP + 0x54],EBP"
    },
    {
      "address": "00a980f1",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a980f4",
      "instruction": "SHR EDX,0x5"
    },
    {
      "address": "00a980f7",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00a980fa",
      "instruction": "JZ 0x00a98103"
    },
    {
      "address": "00a980fc",
      "instruction": "MOV ECX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00a980ff",
      "instruction": "MOV dword ptr [ESP + 0x1c],ECX"
    },
    {
      "address": "00a98103",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a98106",
      "instruction": "SHR EDX,0x6"
    },
    {
      "address": "00a98109",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00a9810c",
      "instruction": "JZ 0x00a98115"
    },
    {
      "address": "00a9810e",
      "instruction": "MOV ECX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00a98111",
      "instruction": "MOV dword ptr [ESP + 0x24],ECX"
    },
    {
      "address": "00a98115",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a98118",
      "instruction": "SHR EDX,0x7"
    },
    {
      "address": "00a9811b",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00a9811e",
      "instruction": "JZ 0x00a98127"
    },
    {
      "address": "00a98120",
      "instruction": "MOV ECX,dword ptr [EAX + 0x18]"
    },
    {
      "address": "00a98123",
      "instruction": "MOV dword ptr [ESP + 0x2c],ECX"
    },
    {
      "address": "00a98127",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a9812a",
      "instruction": "SHR EDX,0x8"
    },
    {
      "address": "00a9812d",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00a98130",
      "instruction": "JZ 0x00a98139"
    },
    {
      "address": "00a98132",
      "instruction": "MOV ECX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "00a98135",
      "instruction": "MOV dword ptr [ESP + 0x34],ECX"
    },
    {
      "address": "00a98139",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a9813c",
      "instruction": "SHR EDX,0x9"
    },
    {
      "address": "00a9813f",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00a98142",
      "instruction": "JZ 0x00a9814b"
    },
    {
      "address": "00a98144",
      "instruction": "MOV ECX,dword ptr [EAX + 0x20]"
    },
    {
      "address": "00a98147",
      "instruction": "MOV dword ptr [ESP + 0x3c],ECX"
    },
    {
      "address": "00a9814b",
      "instruction": "MOV ECX,dword ptr [EDI + 0x50]"
    },
    {
      "address": "00a9814e",
      "instruction": "MOV dword ptr [ESP + 0x4c],ECX"
    },
    {
      "address": "00a98152",
      "instruction": "LEA EDX,[EDI + 0x18]"
    },
    {
      "address": "00a98155",
      "instruction": "MOV dword ptr [ESP + 0x44],EDX"
    },
    {
      "address": "00a98159",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00a9815b",
      "instruction": "MOV EAX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00a9815e",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00a98161",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00a98162",
      "instruction": "LEA ECX,[ESP + 0x20]"
    },
    {
      "address": "00a98166",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00a98167",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a98168",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00a9816a",
      "instruction": "CALL EDX"
    },
    {
      "address": "00a9816c",
      "instruction": "MOV EAX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00a9816f",
      "instruction": "TEST byte ptr [EAX + 0x8],0x1"
    },
    {
      "address": "00a98173",
      "instruction": "JZ 0x00a98191"
    },
    {
      "address": "00a98175",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00a98177",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00a9817a",
      "instruction": "P
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
  "original_bytes": 8501,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"XMM0\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EDI\",\n      \"EBP\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4 (0x00a981f2, bytes C2 04 00)\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01458788\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 6,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01458788\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00a980ce\",\n        \"direction\": \"out\",\n        \"other\": \"0x00883860\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0339\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00a980b0\",\n  \"normalized_symbol\": \"FUN_00a980b0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w2-00a980b0/sw2_00a980b0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00a980b0/sw2_00a980b0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00a980b0/sw2_00a980b0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w2-00a980b0/00a980b0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Editor\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"editor-core\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00a980b0\",\n    \"name\": \"FUN_00a980b0\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"01458788\"\n      ]\n    },\n    \"queue_state\": \"candidate\",\n    \"rank\": 270\n  },\n  \"types\": [\n    \"void\"\n  ],\n  \"unresolved_questions\": [\n    \"RETURN SEMANTICS, the one place this reconstruction and the machine record disagree, and the disagreement is not resolvable from this evidence: the record names XMM0 as the return register with return_semantics float_or_x87_in_XMM0 and abi.return.void_possible false, while the body produces nothing a caller can read on both paths. The worker's position is that inference RT1 fired on the m
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
  "body_end": "00a981f4",
  "body_span_bytes": 325,
  "body_start": "00a980b0",
  "callees": [
    "FUN_00883860"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00a980b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_40",
      "storage": "Stack[-0x40]:4",
      "type": "undefined4"
    },
    {
      "name": "local_48",
      "storage": "Stack[-0x48]:4",
      "type": "undefined4"
    },
    {
      "name": "local_50",
      "storage": "Stack[-0x50]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 10,
  "mode": "live",
  "name": "FUN_00a980b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6980b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00a980b0(void)",
  "size_bytes": 325,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00a980b0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01458788"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01458790"
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
  "global:PASS"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00a980b0/sw2_00a980b0.cpp",
    "reconstruction/staging/pkg-swarm-w2-00a980b0/sw2_00a980b0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00a980b0/sw2_00a980b0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00a980b0/00a980b0.json"
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
  "vtable:0x01458788"
]
```

## Conflicts

```json
[]
```
