# Evidence 0x00641fd0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `af445398eff5c5adfde5079a89d326a38e81fa5fb4d934bd1aa4090ce1103373`

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
  "return_note": "a source-side choice: the machine fixes a 32-bit word in EAX and nothing fixes a C type. See return_semantics and unresolved_questions.",
  "return_register": "EAX",
  "return_type": "void*",
  "saved_registers": [
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "callee",
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
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
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
  "content_sha256": "bc66f802250bb49a447097c485ea9b8b4c6c2b288cc98e079c26567c91467a19",
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
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0029",
        "obs-0033"
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
        "obs-0013",
        "obs-0014",
        "obs-0022",
        "obs-0025"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          8,
          60
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0013",
        "obs-0014",
        "obs-0022",
        "obs-0025",
        "obs-0029",
        "obs-0033"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0029",
        "obs-0033"
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
        "obs-0029",
        "obs-0033"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0029",
        "obs-0033"
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
      "at": "0x00641fd0",
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
      "raw": "SUB ESP,0xc",
      "sub": 12
    },
    {
      "at": "0x00641fd0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0xc",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00641fd3",
      "count": 6,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00641fd4",
      "count": 8,
      "first_use": 2,
      "first_write_index": 14,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00641fd4",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00641fd6",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x3c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00641fe4",
      "count": 3,
      "first_use": 7,
      "first_write_index": 19,
      "id": "obs-0007",
      "index": 7,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00641fe5",
      "count": 8,
      "first_use": 8,
      "first_write_index": 0,
      "id": "obs-0008",
      "index": 8,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP + 0xc],EAX",
      "reg": "ESP"
    },
    {
      "at": "0x00641fe5",
      "count": 9,
      "first_use": 8,
      "first_write_index": 3,
      "id": "obs-0009",
      "index": 8,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP + 0xc],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00641fe5",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0010",
      "index": 8,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP + 0xc],EAX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00641fe9",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0011",
      
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
  "count": 62,
  "instructions": [
    {
      "address": "00641fd0",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "00641fd3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00641fd4",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00641fd6",
      "instruction": "MOV EAX,dword ptr [ESI + 0x3c]"
    },
    {
      "address": "00641fd9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00641fdb",
      "instruction": "JNZ 0x00642068"
    },
    {
      "address": "00641fe1",
      "instruction": "OR EAX,0xffffffff"
    },
    {
      "address": "00641fe4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00641fe5",
      "instruction": "MOV dword ptr [ESP + 0xc],EAX"
    },
    {
      "address": "00641fe9",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00641fed",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00641fef",
      "instruction": "MOV EDX,dword ptr [EAX + 0x90]"
    },
    {
      "address": "00641ff5",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "00641ff9",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00641ffa",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00641ffc",
      "instruction": "CALL EDX"
    },
    {
      "address": "00641ffe",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00642000",
      "instruction": "JZ 0x00642065"
    },
    {
      "address": "00642002",
      "instruction": "CALL 0x0067cb30"
    },
    {
      "address": "00642007",
      "instruction": "MOV EDI,dword ptr [EAX + 0x5c]"
    },
    {
      "address": "0064200a",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "0064200c",
      "instruction": "JZ 0x00642065"
    },
    {
      "address": "0064200e",
      "instruction": "MOV EAX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "00642011",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00642012",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00642014",
      "instruction": "CALL 0x00613860"
    },
    {
      "address": "00642019",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0064201b",
      "instruction": "JZ 0x00642065"
    },
    {
      "address": "0064201d",
      "instruction": "MOV EDX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00642021",
      "instruction": "MOV EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00642025",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00642027",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "0064202b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0064202c",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0064202d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0064202e",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00642030",
      "instruction": "MOV dword ptr [ESP + 0x18],0x0"
    },
    {
      "address": "00642038",
      "instruction": "CALL 0x00612f50"
    },
    {
      "address": "0064203d",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00642041",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00642043",
      "instruction": "JZ 0x0064205a"
    },
    {
      "address": "00642045",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00642047",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00642049",
      "instruction": "JZ 0x00642052"
    },
    {
      "address": "0064204b",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "0064204d",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00642050",
      "instruction": "CALL EAX"
    },
    {
      "address": "00642052",
      "instruction": "POP EDI"
    },
    {
      "address": "00642053",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00642055",
      "instruction": "POP ESI"
    },
    {
      "address": "00642056",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00642059",
      "instruction": "RET"
    },
    {
      "address": "0064205a",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0064205c",
      "instruction": "JZ 0x00642065"
    },
    {
      "address": "0064205e",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00642060",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00642063",
      "instruction": "CALL EAX"
    },
    {
      "address": "00642065",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00642067",
      "instruction": "POP EDI"
    },
    {
      "address": "00642068",
      "instruction": "POP ESI"
    },
    {
      "address": "00642069",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "0064206c",
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
  "original_bytes": 10953,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_note\": \"a source-side choice: the machine fixes a 32-bit word in EAX and nothing fixes a C type. See return_semantics and unresolved_questions.\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void*\",\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n      \"va\": \"0x005c7ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_0060ee90\",\n      \"va\": \"0x0060ee90\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 5,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00642038\",\n        \"direction\": \"out\",\n        \"other\": \"0x00612f50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642014\",\n        \"direction\": \"out\",\n        \"other\": \"0x00613860\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642002\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067cb30\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0168\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00641fd0\",\n  \"normalized_symbol\": \"FUN_00641fd0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-00641fd0/00641fd0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00641fd0\",\n    \"name\": \"FUN_00641fd0\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n 
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
  "body_end": "0064206c",
  "body_span_bytes": 157,
  "body_start": "00641fd0",
  "callees": [
    "FUN_00612f50",
    "FUN_00613860",
    "FUN_0067cb30"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00641fd0",
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
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00641fd0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x241fd0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00641fd0(void)",
  "size_bytes": 157,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00641fd0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013ff648",
      "0x01462764",
      "0x0147ca30",
      "0x0147ca70",
      "0x0147caf8",
      "0x0147cbbc",
      "0x01489090",
      "0x014893b0",
      "0x013ff6ac",
      "0x0147cc14",
      "0x014890f4",
      "0x01489414",
      "0x014627bc"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "013ff6e4"
    },
    {
      "from": "014627f4"
    },
    {
      "from": "0147ca94"
    },
    {
      "from": "0147cb5c"
    },
    {
      "from": "0147cc4c"
    },
    {
      "from": "0148912c"
    },
    {
      "from": "0148944c"
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
    "reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00641fd0/00641fd0.json"
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
  "AcquireSlot04",
  "Acquired",
  "HandlePair",
  "ResolveSlot90",
  "Service",
  "ServiceRoot",
  "SporepediaAssetDataOtdb",
  "void*"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013ff648",
  "vtable:0x013ff6ac",
  "vtable:0x01462764",
  "vtable:0x014627bc",
  "vtable:0x0147ca30",
  "vtable:0x0147ca70",
  "vtable:0x0147caf8",
  "vtable:0x0147cbbc",
  "vtable:0x0147cc14",
  "vtable:0x01489090",
  "vtable:0x014890f4",
  "vtable:0x014893b0",
  "vtable:0x01489414"
]
```

## Conflicts

```json
[]
```
