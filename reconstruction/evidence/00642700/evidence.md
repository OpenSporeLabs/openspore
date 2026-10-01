# Evidence 0x00642700

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d1c819729714e0d6ce4b877b59e960b75d60dcb74a9262cc5e107096cbab8fcc`

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
  "return_register": "EAX",
  "return_type": "bool",
  "saved_registers": [
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "4e67dfa07e8fc62856e16da052b7a483b253d6866ff56c9c2167cfcd247d9f26",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0033",
        "obs-0039",
        "obs-0041"
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
        "obs-0006"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0008",
        "obs-0012",
        "obs-0032",
        "obs-0038",
        "obs-0040"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          8
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0008",
        "obs-0012",
        "obs-0032",
        "obs-0033",
        "obs-0038",
        "obs-0039",
        "obs-0040",
        "obs-0041"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0033",
        "obs-0039",
        "obs-0041"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0033",
        "obs-0039",
        "obs-0041"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0033",
        "obs-0039",
        "obs-0041"
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
      "at": "0x00642700",
      "count": 18,
      "first_use": 0,
      "first_write_index": 10,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0064270e",
      "count": 21,
      "first_use": 3,
      "first_write_index": 9,
      "id": "obs-0002",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0064270f",
      "count": 7,
      "first_use": 4,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00642719",
      "id": "obs-0004",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00556140",
      "target": "0x00556140"
    },
    {
      "at": "0x0064271e",
      "count": 11,
      "first_use": 9,
      "first_write_index": 11,
      "id": "obs-0005",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x18]",
      "reg": "ESP"
    },
    {
      "at": "0x0064271e",
      "base": "ESP",
      "disp": 24,
      "id": "obs-0006",
      "index": 9,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "r
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
  "count": 114,
  "instructions": [
    {
      "address": "00642700",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00642701",
      "instruction": "CMP dword ptr [ECX + 0x8],0x2b978c46"
    },
    {
      "address": "00642708",
      "instruction": "JNZ 0x0064282e"
    },
    {
      "address": "0064270e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0064270f",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00642710",
      "instruction": "LEA EDI,[ECX + 0x4]"
    },
    {
      "address": "00642713",
      "instruction": "PUSH 0xa426730b"
    },
    {
      "address": "00642718",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00642719",
      "instruction": "CALL 0x00556140"
    },
    {
      "address": "0064271e",
      "instruction": "MOV ESI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00642722",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00642725",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00642728",
      "instruction": "MOV dword ptr [ESP + 0x8],EAX"
    },
    {
      "address": "0064272c",
      "instruction": "CMP ECX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "0064272f",
      "instruction": "JNC 0x0064273f"
    },
    {
      "address": "00642731",
      "instruction": "LEA EDX,[ECX + 0x4]"
    },
    {
      "address": "00642734",
      "instruction": "MOV dword ptr [ESI + 0x4],EDX"
    },
    {
      "address": "00642737",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00642739",
      "instruction": "JZ 0x0064274c"
    },
    {
      "address": "0064273b",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "0064273d",
      "instruction": "JMP 0x0064274c"
    },
    {
      "address": "0064273f",
      "instruction": "LEA EAX,[ESP + 0x8]"
    },
    {
      "address": "00642743",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00642744",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00642745",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00642747",
      "instruction": "CALL 0x004558a0"
    },
    {
      "address": "0064274c",
      "instruction": "PUSH 0xad56080c"
    },
    {
      "address": "00642751",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00642752",
      "instruction": "CALL 0x00556140"
    },
    {
      "address": "00642757",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "0064275a",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "0064275d",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00642761",
      "instruction": "CMP ECX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "00642764",
      "instruction": "JNC 0x00642774"
    },
    {
      "address": "00642766",
      "instruction": "LEA EDX,[ECX + 0x4]"
    },
    {
      "address": "00642769",
      "instruction": "MOV dword ptr [ESI + 0x4],EDX"
    },
    {
      "address": "0064276c",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0064276e",
      "instruction": "JZ 0x00642781"
    },
    {
      "address": "00642770",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "00642772",
      "instruction": "JMP 0x00642781"
    },
    {
      "address": "00642774",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00642778",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00642779",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0064277a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0064277c",
      "instruction": "CALL 0x004558a0"
    },
    {
      "address": "00642781",
      "instruction": "PUSH 0xf71fa311"
    },
    {
      "address": "00642786",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00642787",
      "instruction": "CALL 0x00556140"
    },
    {
      "address": "0064278c",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "0064278f",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00642792",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00642796",
      "instruction": "CMP ECX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "00642799",
      "instruction": "JNC 0x006427a9"
    },
    {
      "address": "0064279b",
      "instruction": "LEA EDX,[ECX + 0x4]"
    },
    {
      "address": "0064279e",
      "instruction": "MOV dword ptr [ESI + 0x4],EDX"
    },
    {
      "address": "006427a1",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006427a3",
      "instruction": "JZ 0x006427b6"
    },
    {
      "address": "006427a5",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "006427a7",
      "instruction": "JMP 0x006427b6"
    },
    {
      "address": "006427a9",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "006427ad",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006427ae",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006427af",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "006427b1",
      "instruction": "CALL 0x004558a0"
    },
    {
      "address": "006427b6",
      "instruction": "PUSH 0xbeb528cb"
    },
    {
      "address": "006427bb",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006427bc",
      "instruction": "CALL 0x00556140"
    },
    {
      "address": "006427c1",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "006427c4",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "006427c7",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "006427cb",
      "instruction": "CMP ECX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "006427ce",
      "instruc
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
  "original_bytes": 12652,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"bool\",\n    \"saved_registers\": [\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:Word\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n      \"va\": \"0x006417c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_name_00641810\",\n      \"va\": \"0x00641810\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_id_00641820\",\n      \"va\": \"0x00641820\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00642747\",\n        \"direction\": \"out\",\n        \"other\": \"0x004558a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0064277c\",\n        \"direction\": \"out\",\n        \"other\": \"0x004558a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006427b1\",\n        \"direction\": \"out\",\n        \"other\": \"0x004558a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006427e6\",\n        \"direction\": \"out\",\n        \"other\": \"0x004558a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642821\",\n        \"direction\": \"out\",\n        \"other\": \"0x004558a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642719\",\n        \"direction\": \"out\",\n        \"other\": \"0x00556140\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642752\",\n        \"direction\": \"out\",\n        \"other\": \"0x00556140\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642787\",\n        \"direction\": \"out\",\n        \"other\": \"0x00556140\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006427bc\",\n        \"direction\": \"out\",\n        \"other\": \"0x00556140\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006427f1\",\n        \"direction\": \"out\",\n        \"other\": \"0x00556140\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0172\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00642700\",\n  \"normalized_symbol\": \"FUN_00642700\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n
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
  "body_end": "00642833",
  "body_span_bytes": 308,
  "body_start": "00642700",
  "callees": [
    "FUN_004558a0",
    "FUN_00556140"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00642700",
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
  "name": "FUN_00642700",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x242700",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00642700(void)",
  "size_bytes": 308,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00642700",
  "vtables": {
    "referenced_by_vtables": [
      "0x013ff648",
      "0x01462764",
      "0x0147c9e8",
      "0x0147ca30",
      "0x0147ca70",
      "0x0147caf8",
      "0x01489090",
      "0x014893b0",
      "0x013ff6ac",
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
      "from": "013ff6d4"
    },
    {
      "from": "014627e4"
    },
    {
      "from": "0147ca84"
    },
    {
      "from": "0147cb4c"
    },
    {
      "from": "0148911c"
    },
    {
      "from": "0148943c"
    },
    {
      "from": "00dd1209"
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
    "reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700.cpp",
    "reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00642700/00642700.json"
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
  "SporepediaTypeDescriptor",
  "SporepediaTypeKeySource",
  "SporepediaTypeKeyVector",
  "Word",
  "bool"
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
  "vtable:0x0147c9e8",
  "vtable:0x0147ca30",
  "vtable:0x0147ca70",
  "vtable:0x0147caf8",
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
