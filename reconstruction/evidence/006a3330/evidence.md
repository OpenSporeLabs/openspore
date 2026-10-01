# Evidence 0x006a3330

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3e8d3c8b17b69916169053518661a7a6cf604e7b0354b16fc9540828c4a0ee5d`

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
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x8",
    "entry_ESP+0xc",
    "entry_ESP+0x10",
    "entry_ESP+0x14"
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x10",
  "return_observation": "Only AL is written on either exit, so the upper three bytes of the returned word are whatever the last register-indirect transfer left in EAX. The reconstruction returns a bool, which is the only reading the two exits support; the decompiler's own prototype is bool App__cPropManager__CreateResource(...) and agrees.",
  "return_register": "EAX",
  "return_semantics": "integral_in_EAX, concretised to bool by the two exits: MOV AL,0x1 at 0x006a33c9 on the success path and XOR AL,AL at 0x006a33ec on the failure path. categories.abi.return is {register EAX, register_class integral, type null, void_possible false}, so the record supplies the register and the class and leaves the type open; the two explicit byte writes are what fix it at 1 or 0, and nothing else about the word is claimed.",
  "return_type": "bool",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 16,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x10"
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
      "entry_ESP+0x8",
      "entry_ESP+0xc"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
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
    "ret_form": "RET 0x10",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x10",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "194d14c1d5a8a1d7eb12eeb8a1144606e8b1b013993194dfc169e568786abdf9",
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
    "ghidra_parameter_count": 5,
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
        "obs-0034",
        "obs-0041"
      ],
      "claim": "the callee pops 16 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 16,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0024",
        "obs-0025"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 2,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0011",
        "obs-0016",
        "obs-0024",
        "obs-0032",
        "obs-0033",
        "obs-0036",
        "obs-0040"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0004",
        "obs-0033",
        "obs-0040"
      ],
      "claim": "an FS:/GS: operand is an SEH or cookie frame, which is not variadic evidence",
      "confidence": "OBSERVED",
      "id": "V2",
      "value": {
        "seh_or_cookie_frame": true
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0011",
        "obs-0016",
        "obs-0024",
        "obs-0032",
        "obs-0033",
        "obs-0034",
        "obs-0036",
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
        "obs-0034",
        "obs-0041"
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
        "obs-0034",
        "obs-0041"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0034",
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
      "at": "0x006a3337",
      "id": "obs-0001",
      "index": 2,
      "kind": "SEGMENT_TLS",
      "raw": "MOV EAX,FS:[0x0]",
      "segment": "FS",
      "text": "FS:[0x0]"
    },
    {
      "at": "0x006a3337",
      "definite": true,
      "id": "obs-0002",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,FS:[0x0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a333d",
      "count": 13,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x006a333e",
      "id": "obs-0004",
      "index": 4,
      "kind": "SEGMENT_TLS",
      "raw": "MOV dword ptr FS:[0x0],ESP",
      "segment": "FS",
      "text": "dword
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
  "count": 77,
  "instructions": [
    {
      "address": "006a3330",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "006a3332",
      "instruction": "PUSH 0x120d70a"
    },
    {
      "address": "006a3337",
      "instruction": "MOV EAX,FS:[0x0]"
    },
    {
      "address": "006a333d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a333e",
      "instruction": "MOV dword ptr FS:[0x0],ESP"
    },
    {
      "address": "006a3345",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a3346",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a3347",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a3348",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a3349",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "006a334b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a334c",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a334d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a334e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a334f",
      "instruction": "PUSH 0x1408b44"
    },
    {
      "address": "006a3354",
      "instruction": "PUSH 0x38"
    },
    {
      "address": "006a3356",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "006a3358",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "006a335d",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "006a3360",
      "instruction": "MOV dword ptr [ESP + 0xc],EAX"
    },
    {
      "address": "006a3364",
      "instruction": "MOV dword ptr [ESP + 0x18],ESI"
    },
    {
      "address": "006a3368",
      "instruction": "CMP EAX,ESI"
    },
    {
      "address": "006a336a",
      "instruction": "JZ 0x006a337a"
    },
    {
      "address": "006a336c",
      "instruction": "PUSH 0x1408b34"
    },
    {
      "address": "006a3371",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "006a3373",
      "instruction": "CALL 0x006a1b90"
    },
    {
      "address": "006a3378",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "006a337a",
      "instruction": "MOV EDI,dword ptr [ESP + 0x20]"
    },
    {
      "address": "006a337e",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "006a3380",
      "instruction": "MOV EDX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "006a3383",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "006a3385",
      "instruction": "MOV dword ptr [ESP + 0x18],0xffffffff"
    },
    {
      "address": "006a338d",
      "instruction": "CALL EDX"
    },
    {
      "address": "006a338f",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "006a3391",
      "instruction": "MOV dword ptr [ESI + 0x8],ECX"
    },
    {
      "address": "006a3394",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "006a3397",
      "instruction": "MOV ECX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "006a339b",
      "instruction": "MOV dword ptr [ESI + 0xc],EDX"
    },
    {
      "address": "006a339e",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "006a33a1",
      "instruction": "MOV dword ptr [ESI + 0x10],EAX"
    },
    {
      "address": "006a33a4",
      "instruction": "MOV EAX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "006a33a8",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "006a33aa",
      "instruction": "MOV EDX,dword ptr [EDX + 0x24]"
    },
    {
      "address": "006a33ad",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a33ae",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a33af",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a33b0",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a33b1",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "006a33b3",
      "instruction": "CALL EDX"
    },
    {
      "address": "006a33b5",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "006a33b7",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "006a33b9",
      "instruction": "JZ 0x006a33dd"
    },
    {
      "address": "006a33bb",
      "instruction": "MOV EAX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "006a33bf",
      "instruction": "MOV dword ptr [EAX],ESI"
    },
    {
      "address": "006a33c1",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "006a33c3",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "006a33c5",
      "instruction": "CALL EAX"
    },
    {
      "address": "006a33c7",
      "instruction": "POP EDI"
    },
    {
      "address": "006a33c8",
      "instruction": "POP ESI"
    },
    {
      "address": "006a33c9",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "006a33cb",
      "instruction": "POP EBX"
    },
    {
      "address": "006a33cc",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "006a33d0",
      "instruction": "MOV dword ptr FS:[0x0],ECX"
    },
    {
      "address": "006a33d7",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "006a33da",
      "instruction": "RET 0x10"
    },
    {
      "address": "006a33dd",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "006a33df",
      "instruction": "MOV EAX,dword ptr [EDX + 0x8]"
    },
    {
      "address": "006a33e2",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "006a33e4",
      "instruction": "CALL EAX"
    },
    {
      "address": "006a33e6",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006a33ea",
      "instruction": "POP EDI"
    },
    {
      "address": "006a33eb",
      "instruction": "POP ESI"
    },
    {
      "address": "006a33ec",
  
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
  "original_bytes": 9795,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x8\",\n      \"entry_ESP+0xc\",\n      \"entry_ESP+0x10\",\n      \"entry_ESP+0x14\"\n    ],\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x10\",\n    \"return_observation\": \"Only AL is written on either exit, so the upper three bytes of the returned word are whatever the last register-indirect transfer left in EAX. The reconstruction returns a bool, which is the only reading the two exits support; the decompiler's own prototype is bool App__cPropManager__CreateResource(...) and agrees.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"integral_in_EAX, concretised to bool by the two exits: MOV AL,0x1 at 0x006a33c9 on the success path and XOR AL,AL at 0x006a33ec on the failure path. categories.abi.return is {register EAX, register_class integral, type null, void_possible false}, so the record supplies the register and the class and leaves the type open; the two explicit byte writes are what fix it at 1 or 0, and nothing else about the word is claimed.\",\n    \"return_type\": \"bool\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 16,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x10\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 8,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 8,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 8,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 8,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 8,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014091a0\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 4,\n      \"symbol\": \"app_prop_manager_get_supported_types_006a3400\",\n      \"va\": \"0x006a3400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a3373\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a1b90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a3358\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0224\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"App::cPropManager::CreateResource\",\n  \"normalized_symbol\": \"App::cPropManager::CreateResource\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__CreateResource.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__CreateResource.c\",\n      \"reconstruction/staging/pkg-propmanager-create-wave15/prop_manager_create_resource_006a3330.cpp\",\n      \"reconstruction/staging/pkg-p
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
  "body_end": "006a33fb",
  "body_span_bytes": 204,
  "body_start": "006a3330",
  "callees": [
    "FUN_006a1b90",
    "FUN_00f473a0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a3330",
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
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "App::cPropManager::CreateResource",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 5,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IResourceFactory *"
    },
    {
      "name": "pRecord",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "IRecord *"
    },
    {
      "name": "pDst",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "intrusive_ptr<Resource::ResourceObject> *"
    },
    {
      "name": "param_4",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "void *"
    },
    {
      "name": "nTypeID",
      "ordinal": 4,
      "storage": "Stack[0x14]:4",
      "type": "uint32_t"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x2a3330",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cPropManager::CreateResource(IResourceFactory * this, IRecord * pRecord, intrusive_ptr<Resource::ResourceObject> * pDst, void * param_4, uint32_t nTypeID)",
  "size_bytes": 204,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a3330",
  "vtables": {
    "referenced_by_vtables": [
      "0x014091a0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "014091cc"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__CreateResource.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cPropManager__CreateResource.c",
    "reconstruction/staging/pkg-propmanager-create-wave15/prop_manager_create_resource_006a3330.cpp",
    "reconstruction/staging/pkg-propmanager-create-wave15/prop_manager_create_resource_006a3330.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-propmanager-create-wave15/006a3330.json"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "bool"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014091a0"
]
```

## Conflicts

```json
[]
```
