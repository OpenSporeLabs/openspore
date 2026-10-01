# Evidence 0x005c0a60

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `99c29edbdac9e03a785251f96fcff5748b09ce821d175af30e64b7dda836162d`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall with callee stack cleanup",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "std::uint32_t",
      "native_reads": [],
      "normalized_name": "argument",
      "note": "the entry accepts one stack word but never reads it; the body only tests byte ptr [ESP+0x8],0x1 against the deleting-destructor idiom position, so the argument is an unused formal",
      "position": 1,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      },
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
      },
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
      }
    ],
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0x8; everything above it belongs to the caller's frame",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0x8 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "7cfdbba31848501192728098479453585e99ba3a314f9aa6742c125306cc4fb6",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall with callee stack cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0026",
        "obs-0043"
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
        "obs-0026",
        "obs-0043"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 4,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0031",
        "obs-0032",
        "obs-0036"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0016",
        "obs-0036"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          20,
          24,
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0043"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0026",
        "obs-0043"
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
        "obs-0026",
        "obs-0043"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0026",
        "obs-0043"
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
      "at": "0x005c0a60",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 10,
      "raw": "SUB ESP,0x14",
      "sub": 20
    },
    {
      "at": "0x005c0a60",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x14",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x005c0a63",
      "count": 4,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x005c0a64",
      "count": 14,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
     
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
    "va": "0x005c28b0"
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
  "count": 100,
  "instructions": [
    {
      "address": "005c0a60",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "005c0a63",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005c0a64",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005c0a65",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "005c0a67",
      "instruction": "MOV EAX,dword ptr [EDI + 0x14]"
    },
    {
      "address": "005c0a6a",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "005c0a6c",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "005c0a6e",
      "instruction": "JZ 0x005c0b6e"
    },
    {
      "address": "005c0a74",
      "instruction": "CMP dword ptr [EDI + 0x18],EBX"
    },
    {
      "address": "005c0a77",
      "instruction": "JZ 0x005c0b6e"
    },
    {
      "address": "005c0a7d",
      "instruction": "PUSH EBP"
    },
    {
      "address": "005c0a7e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005c0a7f",
      "instruction": "MOV ESI,dword ptr [EAX + 0x8c]"
    },
    {
      "address": "005c0a85",
      "instruction": "SUB ESI,dword ptr [EAX + 0x88]"
    },
    {
      "address": "005c0a8b",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "005c0a8d",
      "instruction": "SAR ESI,0x3"
    },
    {
      "address": "005c0a90",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "005c0a92",
      "instruction": "MOV dword ptr [ESP + 0x10],EBX"
    },
    {
      "address": "005c0a96",
      "instruction": "JLE 0x005c0ac7"
    },
    {
      "address": "005c0a98",
      "instruction": "JMP 0x005c0aa0"
    },
    {
      "address": "005c0aa0",
      "instruction": "MOV ECX,dword ptr [EDI + 0x14]"
    },
    {
      "address": "005c0aa3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005c0aa4",
      "instruction": "CALL 0x005c29c0"
    },
    {
      "address": "005c0aa9",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "005c0aab",
      "instruction": "JZ 0x005c0abd"
    },
    {
      "address": "005c0aad",
      "instruction": "MOV EAX,dword ptr [EDI + 0x14]"
    },
    {
      "address": "005c0ab0",
      "instruction": "CMP EBX,dword ptr [EAX + 0xa0]"
    },
    {
      "address": "005c0ab6",
      "instruction": "JNZ 0x005c0abc"
    },
    {
      "address": "005c0ab8",
      "instruction": "MOV dword ptr [ESP + 0x10],EBP"
    },
    {
      "address": "005c0abc",
      "instruction": "INC EBP"
    },
    {
      "address": "005c0abd",
      "instruction": "INC EBX"
    },
    {
      "address": "005c0abe",
      "instruction": "CMP EBX,ESI"
    },
    {
      "address": "005c0ac0",
      "instruction": "JL 0x005c0aa0"
    },
    {
      "address": "005c0ac2",
      "instruction": "CMP EBP,0x2"
    },
    {
      "address": "005c0ac5",
      "instruction": "JGE 0x005c0ae9"
    },
    {
      "address": "005c0ac7",
      "instruction": "MOV EDI,dword ptr [EDI + 0x1c]"
    },
    {
      "address": "005c0aca",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "005c0acc",
      "instruction": "JZ 0x005c0b6c"
    },
    {
      "address": "005c0ad2",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "005c0ad4",
      "instruction": "MOV EAX,dword ptr [EDX + 0x7c]"
    },
    {
      "address": "005c0ad7",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005c0ad9",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005c0adb",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "005c0add",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c0adf",
      "instruction": "POP ESI"
    },
    {
      "address": "005c0ae0",
      "instruction": "POP EBP"
    },
    {
      "address": "005c0ae1",
      "instruction": "POP EDI"
    },
    {
      "address": "005c0ae2",
      "instruction": "POP EBX"
    },
    {
      "address": "005c0ae3",
      "instruction": "ADD ESP,0x14"
    },
    {
      "address": "005c0ae6",
      "instruction": "RET 0x4"
    },
    {
      "address": "005c0ae9",
      "instruction": "MOV ECX,dword ptr [EDI + 0x1c]"
    },
    {
      "address": "005c0aec",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "005c0aee",
      "instruction": "JZ 0x005c0afb"
    },
    {
      "address": "005c0af0",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "005c0af2",
      "instruction": "MOV EAX,dword ptr [EDX + 0x7c]"
    },
    {
      "address": "005c0af5",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005c0af7",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005c0af9",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c0afb",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "005c0aff",
      "instruction": "CMP dword ptr [EDI + 0x20],ESI"
    },
    {
      "address": "005c0b02",
      "instruction": "JNZ 0x005c0b09"
    },
    {
      "address": "005c0b04",
      "instruction": "CMP dword ptr [EDI + 0x24],EBP"
    },
    {
      "address": "005c0b07",
      "instruction": "JZ 0x005c0b6c"
    },
    {
      "address": "005c0b09",
      "instruction": "PUSH EBP"
    },
    {
      "address": "005c0b0a",
      "instruction": "LEA ECX,[ESI + 0x1]"
    },
    {
      "address": "005c0b0d",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005c0b0e",
      "instruction": "MOV EAX,0x1667bac"
    },
    {
      "address": "005c0b13",
      "instruction": "LEA EDX,[ESP + 0x1c]"
    },
    {
      "address": "005c0b17",
      "instruction": "PUSH 0x13f7c30"
    },
    {
      "address": "005c0b1c",
      "instruction": "PUSH EDX"
    },
    {
      "address": "005c0b1d",
      "instruction": "MOV dword ptr [ESP + 0x24],EAX"
    },
    {
      "address": "005c0b21",
      "instruction": "MOV dword ptr [ESP + 0x28],EAX"
    },
    {
      "address": "005c0b25",
      "instruction": "MOV
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
  "original_bytes": 9312,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with callee stack cleanup\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"machine_type\": \"std::uint32_t\",\n        \"native_reads\": [],\n        \"normalized_name\": \"argument\",\n        \"note\": \"the entry accepts one stack word but never reads it; the body only tests byte ptr [ESP+0x8],0x1 against the deleting-destructor idiom position, so the argument is an unused formal\",\n        \"position\": 1,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:OpaqueRect\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE10\",\n      \"score\": 17,\n      \"symbol\": \"palette_row_layout_005c3000\",\n      \"va\": \"0x005c3000\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"cursor_buffer_emit_0041e8b0\",\n      \"va\": \"0x0041e8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"skin_painter_state_setup_00506590\",\n      \"va\": \"0x00506590\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"editor_row_publish_005a2010\",\n      \"va\": \"0x005a2010\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UI-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"image_archive_scalar_deleting_destructor_00635700\",\n      \"va\": \"0x00635700\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaquePage\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005c28b0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005c28dc\",\n        \"direction\": \"in\",\n        \"other\": \"0x005c28b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0b2d\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041e050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0aa4\",\n        \"direction\": \"out\",\n        \"other\": \"0x005c29c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0b64\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x005c29c0\",\n      \"0x0041e050\",\n      \"0x00f47380\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0112\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 1\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"page_visible_slots_refresh_005c0a60\",\n  \"normalized_symbol\": \"page_visible_slots_refresh_005c0a60\",\n  \"observed_mechanics\": [\n    \"Return untouched when the category at +0x14 is null.\",\n    \"Return untouched when the text object at +0x18 is null.\",\n    \"Derive the slot count as ((end_8c - begin_88) >> 3), the eight byte category slot stride.\",\n    \"Reload the category pointer from EDI+0x14 on every loop iteration and call the visibility port 0x005c29c0 once per slot.\",\n    \"Record selected as the running visible count when index == current_a0, and increment total for every visible slot.\",\n    \"When total < 2 call the nav vtable slot +0x7c with (1, 0) and return.\",\n    \"When total >= 2 cal
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
  "body_end": "005c0b75",
  "body_span_bytes": 278,
  "body_start": "005c0a60",
  "callees": [
    "FUN_00f47380",
    "FUN_0041e050",
    "FUN_005c29c0"
  ],
  "callers": [
    "FUN_005c28b0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005c0a60",
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
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_005c0a60",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1c0a60",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005c0a60(void)",
  "size_bytes": 278,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005c0a60",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "005c28dc"
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
    "reconstruction/metadata/pkg-palette-safe-wave10/005c0a60.json"
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
    "The decoded meaning of the format literal at 0x013f7c30 is inferred as '<n>/<total>' and is unconfirmed by any runtime render.",
    "The formatter 0x0041e050 and the release port 0x00f47380 remain dependency-only.",
    "The nav and text vtable owners are unattributed in the live database.",
    "The unused formal argument is kept only to preserve the RET 0x4 cleanup width.",
    "The visibility port 0x005c29c0 is an opaque bool seam and is not promoted.",
    "gate-page-visible-slots-runtime-visibility-and-format-literal",
    "runtime validation not performed; static decompilation and disassembly only",
    "the decoded meaning of the format literal at 0x013f7c30 is inferred as '<n>/<total>' and is not confirmed by a runtime render",
    "the nav and text vtable owners at slot +0x7c and +0x80 are unattributed in the live database",
    "the text formatter 0x0041e050 and the release port 0x00f47380 remain dependency-only",
    "the unused formal argument is retained in the signature to keep the RET 0x4 cleanup width exact",
    "the visibility port 0x005c29c0 is modelled as an opaque bool seam and is not promoted"
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
  "OpaquePage",
  "OpaquePage*",
  "OpaquePageCategory",
  "OpaqueRect",
  "OpaqueTextBuffer",
  "unsigned int",
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
