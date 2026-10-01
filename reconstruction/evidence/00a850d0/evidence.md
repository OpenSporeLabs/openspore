# Evidence 0x00a850d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `07322b6b3027bf90502d1e926720bf29f90b76ea8ef1f83a7fce3343defc6679`

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
  "return_note": "machine record carries abi.return.type = null and abi.return.void_possible = false, confidence APPROXIMATION, register XMM0, register_class float_or_x87",
  "return_register": "XMM0",
  "saved_registers": [
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "0x00a85189 and 0x00a851bf are both RET 0x4"
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
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path"
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
  "content_sha256": "a6c32c2146aed3cbf431e9a70277c8cef75b50c90570ffc589d60c914ee1899a",
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
        "obs-0020",
        "obs-0024"
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
        "obs-0020",
        "obs-0024"
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
        "obs-0002",
        "obs-0003",
        "obs-0004"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          16,
          20,
          24,
          28,
          32,
          104
        ],
        "register": "ECX",
        "written_through": 7
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0020",
        "obs-0024"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0024"
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
        "obs-0024"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00a850d0",
      "count": 18,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00a850d1",
      "count": 8,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00a850d1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00a850dd",
      "definite": true,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x10]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00a850e0",
      "count": 5,
      "first_use": 5,
      "first_write_index": 42,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00a850e9",
      "definite": true,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0xc]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00a850ec",
      "count": 16,
      "first_use": 10,
      "first_write_index": 9,
      "id": "obs-0007",
      "index": 10,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x8]",
      "reg": "EAX"
    },
    {
      "at": "0x00a850ec",
      "definite": true,
      "id": "obs-0008",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x8]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00a850ef",
      "count": 9,
      "first_use": 11,
      "first_write_index":
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
  "count": 81,
  "instructions": [
    {
      "address": "00a850d0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00a850d1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00a850d3",
      "instruction": "CMP byte ptr [ESI + 0x14],0x0"
    },
    {
      "address": "00a850d7",
      "instruction": "JNZ 0x00a85188"
    },
    {
      "address": "00a850dd",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "00a850e0",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00a850e1",
      "instruction": "MOV byte ptr [ESI + 0x14],0x1"
    },
    {
      "address": "00a850e5",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00a850e7",
      "instruction": "JZ 0x00a8515c"
    },
    {
      "address": "00a850e9",
      "instruction": "MOV EAX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "00a850ec",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a850ef",
      "instruction": "SHR EDX,0x2"
    },
    {
      "address": "00a850f2",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00a850f5",
      "instruction": "JZ 0x00a850fe"
    },
    {
      "address": "00a850f7",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00a850f9",
      "instruction": "MOV EDX,dword ptr [EAX + 0x18]"
    },
    {
      "address": "00a850fc",
      "instruction": "CALL EDX"
    },
    {
      "address": "00a850fe",
      "instruction": "MOV EAX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "00a85101",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a85104",
      "instruction": "MOV EDX,ECX"
    },
    {
      "address": "00a85106",
      "instruction": "SHR EDX,0x4"
    },
    {
      "address": "00a85109",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00a8510c",
      "instruction": "JZ 0x00a85130"
    },
    {
      "address": "00a8510e",
      "instruction": "MOVZX EAX,word ptr [EAX + 0xa8]"
    },
    {
      "address": "00a85115",
      "instruction": "SHR ECX,0x6"
    },
    {
      "address": "00a85118",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00a8511b",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "00a8511e",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00a85120",
      "instruction": "MOV EDX,dword ptr [EDX + 0x1c]"
    },
    {
      "address": "00a85123",
      "instruction": "JZ 0x00a8512b"
    },
    {
      "address": "00a85125",
      "instruction": "LEA EDI,[ESI + 0x28]"
    },
    {
      "address": "00a85128",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00a85129",
      "instruction": "JMP 0x00a8512d"
    },
    {
      "address": "00a8512b",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00a8512d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a8512e",
      "instruction": "CALL EDX"
    },
    {
      "address": "00a85130",
      "instruction": "MOV EAX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "00a85133",
      "instruction": "MOV dword ptr [ESI + 0x68],0xffffffff"
    },
    {
      "address": "00a8513a",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a8513d",
      "instruction": "SHR ECX,0x1"
    },
    {
      "address": "00a8513f",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00a85142",
      "instruction": "JZ 0x00a8518c"
    },
    {
      "address": "00a85144",
      "instruction": "MOV EDI,dword ptr [EAX + 0xa4]"
    },
    {
      "address": "00a8514a",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "00a8514d",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00a8514f",
      "instruction": "MOV EAX,dword ptr [EAX + 0xa0]"
    },
    {
      "address": "00a85155",
      "instruction": "MOV EDX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00a85158",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00a85159",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a8515a",
      "instruction": "CALL EDX"
    },
    {
      "address": "00a8515c",
      "instruction": "XORPS XMM1,XMM1"
    },
    {
      "address": "00a8515f",
      "instruction": "MOV EAX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "00a85162",
      "instruction": "MOVSS dword ptr [ESI + 0x1c],XMM1"
    },
    {
      "address": "00a85167",
      "instruction": "MOVSS dword ptr [ESI + 0x20],XMM1"
    },
    {
      "address": "00a8516c",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00a85171",
      "instruction": "COMISS XMM0,XMM1"
    },
    {
      "address": "00a85174",
      "instruction": "JBE 0x00a85182"
    },
    {
      "address": "00a85176",
      "instruction": "MOVSS XMM1,dword ptr [0x01485720]"
    },
    {
      "address": "00a8517e",
      "instruction": "DIVSS XMM1,XMM0"
    },
    {
      "address": "00a85182",
      "instruction": "MOVSS dword ptr [ESI + 0x18],XMM1"
    },
    {
      "address": "00a85187",
      "instruction": "POP EDI"
    },
    {
      "address": "00a85188",
      "instruction": "POP ESI"
    },
    {
      "address": "00a85189",
      "instruction": "RET 0x4"
    },
    {
      "address": "00a8518c",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00a85191",
      "instruction": "COMISS XMM0,dword ptr [0x01485378]"
    },
    {
      "address": "00a85198",
      "instruction": "JBE 0x00a8515c"
    },
    {
      "address": "00a8519a",
      "instruction": "MOV EDI,dword ptr [EAX + 0xa4]"
    },
    {
      "address": "00a851a0",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "00a851a3",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00a851a5",
      "instr
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
  "original_bytes": 9995,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"machine record carries abi.return.type = null and abi.return.void_possible = false, confidence APPROXIMATION, register XMM0, register_class float_or_x87\",\n    \"return_register\": \"XMM0\",\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"0x00a85189 and 0x00a851bf are both RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01458024\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 6,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01458024\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"GLOBALS cannot reach PASS while the xref export carries no data-reference edge type and the listing genuinely names two .rdata addresses. Both constants are declared with their addresses and their image-transcribed values, and the body is not truncated to hide them.\",\n    \"RETURN SEMANTICS cannot reach PASS from the source side while the canonical record's return token is the machine phrase float_or_x87_in_XMM0. Writing a typedef named after that phrase would win the string comparison and would be a validator hack, so it was not done; the disagreement is recorded instead.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0336\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:WARN\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00a850d0\",\n  \"normalized_symbol\": \"FUN_00a850d0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w2-00a850d0/sw2_00a850d0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00a850d0/sw2_00a850d0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00a850d0/sw2_00a850d0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w2-00a850d0/00a850d0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Editor\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"editor-core\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00a850d0\",\n    \"name\": \"FUN_00a850d0\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \
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
  "body_end": "00a851c1",
  "body_span_bytes": 242,
  "body_start": "00a850d0",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00a850d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00a850d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6850d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00a850d0(void)",
  "size_bytes": 242,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00a850d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01458024"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0145802c"
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
    "reconstruction/staging/pkg-swarm-w2-00a850d0/sw2_00a850d0.cpp",
    "reconstruction/staging/pkg-swarm-w2-00a850d0/sw2_00a850d0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00a850d0/sw2_00a850d0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00a850d0/00a850d0.json"
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
  "float",
  "machine record carries abi.return.type = null and abi.return.void_possible = false, confidence APPROXIMATION, register XMM0, register_class float_or_x87"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01458024"
]
```

## Conflicts

```json
[]
```
