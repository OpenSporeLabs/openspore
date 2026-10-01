# Evidence 0x006a3180

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `537b615e936c5d4851871ffb6bc25c4d86411513912a5c41af7413f49e547dd7`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit list receiver in ECX and caller cleanup",
  "return_semantics": "void",
  "return_type": "void",
  "stack_cleanup_bytes": 4,
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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
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
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
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
  "content_sha256": "96d988fb64f73e12d128fe58dce3750e871661708a7f6b6e8e0fb01736074991",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
    "persisted_calling_convention": "x86-32 thiscall with first explicit list receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
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
        "obs-0006",
        "obs-0018"
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
        "obs-0013",
        "obs-0014",
        "obs-0022",
        "obs-0031"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          24,
          28,
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0014",
        "obs-0022",
        "obs-0031",
        "obs-0044"
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
        "obs-0044"
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
        "obs-0044"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0044"
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
      "at": "0x006a3180",
      "count": 9,
      "first_use": 0,
      "first_write_index": 4,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x006a3181",
      "count": 8,
      "first_use": 1,
      "first_write_index": 12,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x006a3181",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x006a3182",
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
      "at": "0x006a3183",
      "count": 9,
      
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
  "count": 110,
  "instructions": [
    {
      "address": "006a3180",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a3181",
      "instruction": "PUSH EBP"
    },
    {
      "address": "006a3182",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a3183",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006a3187",
      "instruction": "MOV EBX,dword ptr [ESI]"
    },
    {
      "address": "006a3189",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a318a",
      "instruction": "MOV EDI,dword ptr [ESI + 0x4]"
    },
    {
      "address": "006a318d",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "006a318f",
      "instruction": "SUB EAX,EDI"
    },
    {
      "address": "006a3191",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a3192",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a3193",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a3194",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "006a3196",
      "instruction": "CALL 0x011e0744"
    },
    {
      "address": "006a319b",
      "instruction": "SUB EDI,EBX"
    },
    {
      "address": "006a319d",
      "instruction": "SAR EDI,0x2"
    },
    {
      "address": "006a31a0",
      "instruction": "NEG EDI"
    },
    {
      "address": "006a31a2",
      "instruction": "ADD EDI,EDI"
    },
    {
      "address": "006a31a4",
      "instruction": "ADD EDI,EDI"
    },
    {
      "address": "006a31a6",
      "instruction": "ADD dword ptr [ESI + 0x4],EDI"
    },
    {
      "address": "006a31a9",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "006a31ac",
      "instruction": "CALL 0x0067de30"
    },
    {
      "address": "006a31b1",
      "instruction": "MOV EDI,0x1"
    },
    {
      "address": "006a31b6",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "006a31b8",
      "instruction": "MOV dword ptr [ESP + 0x14],EDI"
    },
    {
      "address": "006a31bc",
      "instruction": "CMP dword ptr [EBP + 0x38],EDI"
    },
    {
      "address": "006a31bf",
      "instruction": "JBE 0x006a3203"
    },
    {
      "address": "006a31c1",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "006a31c3",
      "instruction": "MOV EAX,dword ptr [EDX + 0x50]"
    },
    {
      "address": "006a31c6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a31c7",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "006a31c9",
      "instruction": "CALL EAX"
    },
    {
      "address": "006a31cb",
      "instruction": "CMP word ptr [EAX + 0x12],0x0"
    },
    {
      "address": "006a31d0",
      "instruction": "JZ 0x006a31f9"
    },
    {
      "address": "006a31d2",
      "instruction": "MOV EAX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "006a31d5",
      "instruction": "CMP EAX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "006a31d8",
      "instruction": "JNC 0x006a31e8"
    },
    {
      "address": "006a31da",
      "instruction": "LEA ECX,[EAX + 0x4]"
    },
    {
      "address": "006a31dd",
      "instruction": "MOV dword ptr [ESI + 0x4],ECX"
    },
    {
      "address": "006a31e0",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "006a31e2",
      "instruction": "JZ 0x006a31f9"
    },
    {
      "address": "006a31e4",
      "instruction": "MOV dword ptr [EAX],EDI"
    },
    {
      "address": "006a31e6",
      "instruction": "JMP 0x006a31f9"
    },
    {
      "address": "006a31e8",
      "instruction": "LEA EDX,[ESP + 0x14]"
    },
    {
      "address": "006a31ec",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a31ed",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a31ee",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "006a31f0",
      "instruction": "CALL 0x004558a0"
    },
    {
      "address": "006a31f5",
      "instruction": "MOV EDI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "006a31f9",
      "instruction": "INC EDI"
    },
    {
      "address": "006a31fa",
      "instruction": "MOV dword ptr [ESP + 0x14],EDI"
    },
    {
      "address": "006a31fe",
      "instruction": "CMP EDI,dword ptr [EBP + 0x38]"
    },
    {
      "address": "006a3201",
      "instruction": "JC 0x006a31c1"
    },
    {
      "address": "006a3203",
      "instruction": "MOV EDX,dword ptr [EBP + 0x1c]"
    },
    {
      "address": "006a3206",
      "instruction": "SUB EDX,dword ptr [EBP + 0x18]"
    },
    {
      "address": "006a3209",
      "instruction": "MOV EDI,dword ptr [ESI + 0x4]"
    },
    {
      "address": "006a320c",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "006a320e",
      "instruction": "MOV EAX,0x2aaaaaab"
    },
    {
      "address": "006a3213",
      "instruction": "IMUL EDX"
    },
    {
      "address": "006a3215",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "006a3218",
      "instruction": "MOV EBX,EDI"
    },
    {
      "address": "006a321a",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "006a321c",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "006a321f",
      "instruction": "SUB EBX,ECX"
    },
    {
      "address": "006a3221",
      "instruction": "SAR EBX,0x2"
    },
    {
      "address": "006a3224",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "006a3226",
      "instruction": "ADD EAX,EBX"
    },
    {
      "address": "006a3228",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "006a322a",
      "instruction": "JBE 0x006a3246"
    },
    {
      "address": "006a322c",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "006a3230",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a3231",
      "instruction": "SUB EAX,EBX"
    },
    {
      "address": "006a3233",
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
  "original_bytes": 9067,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit list receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_has_property_006a27d0\",\n      \"va\": \"0x006a27d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_get_property_object_006a2800\",\n      \"va\": \"0x006a2800\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_get_property_006a28c0\",\n      \"va\": \"0x006a28c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject,openspore::reconstruction::pkg_direct_property_wave6::OpaqueList,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap,openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"opaque_list_set_property_006a30c0\",\n      \"va\": \"0x006a30c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 4,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 4,\n      \"symbol\": \"direct_property_list_add_properties_from_006a1600\",\n      \"va\": \"0x006a1600\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 4,\n      \"symbol\": \"direct_property_list_get_property_alt_006a1e50\",\n      \"va\": \"0x006a1e50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408870\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 4,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a31f0\",\n        \"direction\": \"out\",\n        \"other\": \"0x004558a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a323f\",\n        \"direction\": \"out\",\n        \"other\": \"0x004cea40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a31ac\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a3196\",\n        \"direction\": \"out\",\n        \"other\": \"0x011e0744\",\n        \"reference_type\": \"thunk\"\n      },\n      {\n        \"callsite\": \"0x006a3254\",\n        \"direction\": \"out\",\n        \"other\": \"0x011e0744\",\n        \"reference_type\": \"thunk\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0221\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::DirectPropertyList::GetPropertyIDs\",\n  \"normalized_symbol\": \"opaque_list_get_property_ids_0
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
  "body_end": "006a3298",
  "body_span_bytes": 281,
  "body_start": "006a3180",
  "callees": [
    "FUN_004558a0",
    "memcpy",
    "FUN_0067de30",
    "FUN_004cea40"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a3180",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::DirectPropertyList::GetPropertyIDs",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "DirectPropertyList *"
    },
    {
      "name": "dst",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "vector<unsigned int> *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x2a3180",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::DirectPropertyList::GetPropertyIDs(DirectPropertyList * this, vector<unsigned int> * dst)",
  "size_bytes": 281,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a3180",
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
      "from": "014088b4"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyIDs.c",
  "file": "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyIDs.c",
    "src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-direct-property-wave6/006a3180.json"
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
    "runtime validation not run",
    "vector allocation, service metadata, map lifetime, and destination ownership remain gated"
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
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueBaseObject",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueList",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueMap",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueMapEntry",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueProperty",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaquePropertyService",
  "openspore::reconstruction::pkg_direct_property_wave6::OpaqueWordVector",
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
