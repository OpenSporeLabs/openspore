# Evidence 0x00642230

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6876609c3230f877ec8566a8cf110624555e9f6068d64d6333da640d85a34561`

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
      "machine_type": "OpaqueLookupSource*",
      "native_reads": [
        "MOV ESI,[ESP+0x48] at 0x00642263",
        "CMP ESI,EBP / JZ 0x00642375"
      ],
      "normalized_name": "source",
      "note": "a null source skips both lookup branches and still zeroes max_6c and runs the gate scan",
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
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
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
        "size_inferred": true,
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
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
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0x14; everything above it belongs to the caller's frame",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0x14 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "a743bd2174013895e4eb9b11339098b129ae7619aec0ba37458ffeb1d1940f44",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "indirect_calls": 7,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
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
        "obs-0015",
        "obs-0046",
        "obs-0050",
        "obs-0051",
        "obs-0055",
        "obs-0056",
        "obs-0060",
        "obs-0061",
        "obs-0063",
        "obs-0064",
        "obs-0065",
        "obs-0066",
        "obs-0068",
        "obs-0069",
        "obs-0071",
        "obs-0072"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 5,
        "total_bytes": 20
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0018",
        "obs-0026",
        "obs-0028",
        "obs-0037",
        "obs-0045",
        "obs-0048",
        "obs-0050",
        "obs-0053",
        "obs-0055",
        "obs-0058",
        "obs-0060",
        "obs-0068",
        "obs-0069",
        "obs-0072",
        "obs-0076",
        "obs-0078"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to i
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
  "count": 257,
  "instructions": [
    {
      "address": "00642230",
      "instruction": "SUB ESP,0x28"
    },
    {
      "address": "00642233",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00642234",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00642235",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00642236",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00642237",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00642239",
      "instruction": "MOV dword ptr [EBX + 0x2c],0x2"
    },
    {
      "address": "00642240",
      "instruction": "MOV ESI,dword ptr [EBX + 0x44]"
    },
    {
      "address": "00642243",
      "instruction": "MOV EBP,dword ptr [EBX + 0x40]"
    },
    {
      "address": "00642246",
      "instruction": "LEA EDI,[EBX + 0x40]"
    },
    {
      "address": "00642249",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "0064224b",
      "instruction": "SUB EAX,ESI"
    },
    {
      "address": "0064224d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0064224e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0064224f",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00642250",
      "instruction": "CALL 0x011e0744"
    },
    {
      "address": "00642255",
      "instruction": "SUB ESI,EBP"
    },
    {
      "address": "00642257",
      "instruction": "SAR ESI,0x2"
    },
    {
      "address": "0064225a",
      "instruction": "NEG ESI"
    },
    {
      "address": "0064225c",
      "instruction": "ADD ESI,ESI"
    },
    {
      "address": "0064225e",
      "instruction": "ADD ESI,ESI"
    },
    {
      "address": "00642260",
      "instruction": "ADD dword ptr [EDI + 0x4],ESI"
    },
    {
      "address": "00642263",
      "instruction": "MOV ESI,dword ptr [ESP + 0x48]"
    },
    {
      "address": "00642267",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00642269",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "0064226c",
      "instruction": "CMP ESI,EBP"
    },
    {
      "address": "0064226e",
      "instruction": "JZ 0x00642375"
    },
    {
      "address": "00642274",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00642276",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00642279",
      "instruction": "PUSH 0x670da17"
    },
    {
      "address": "0064227e",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00642280",
      "instruction": "CALL EAX"
    },
    {
      "address": "00642282",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00642286",
      "instruction": "CMP EAX,EBP"
    },
    {
      "address": "00642288",
      "instruction": "JZ 0x00642292"
    },
    {
      "address": "0064228a",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0064228c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0064228e",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "00642290",
      "instruction": "CALL EAX"
    },
    {
      "address": "00642292",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00642294",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00642297",
      "instruction": "PUSH 0x3c609f8"
    },
    {
      "address": "0064229c",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0064229e",
      "instruction": "CALL EAX"
    },
    {
      "address": "006422a0",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "006422a2",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "006422a4",
      "instruction": "MOV dword ptr [ESP + 0x3c],EBP"
    },
    {
      "address": "006422a8",
      "instruction": "CMP EBP,ESI"
    },
    {
      "address": "006422aa",
      "instruction": "JZ 0x006422b5"
    },
    {
      "address": "006422ac",
      "instruction": "MOV EDX,dword ptr [EBP]"
    },
    {
      "address": "006422af",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "006422b1",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "006422b3",
      "instruction": "CALL EAX"
    },
    {
      "address": "006422b5",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006422b9",
      "instruction": "CMP ECX,ESI"
    },
    {
      "address": "006422bb",
      "instruction": "JZ 0x0064237e"
    },
    {
      "address": "006422c1",
      "instruction": "CALL 0x005507a0"
    },
    {
      "address": "006422c6",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006422ca",
      "instruction": "MOV ESI,dword ptr [EAX]"
    },
    {
      "address": "006422cc",
      "instruction": "CALL 0x005507a0"
    },
    {
      "address": "006422d1",
      "instruction": "MOV EBP,dword ptr [EAX + 0x4]"
    },
    {
      "address": "006422d4",
      "instruction": "CMP ESI,EBP"
    },
    {
      "address": "006422d6",
      "instruction": "JZ 0x006422f4"
    },
    {
      "address": "006422d8",
      "instruction": "JMP 0x006422e0"
    },
    {
      "address": "006422e0",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "006422e2",
      "instruction": "MOV EAX,dword ptr [EDX + 0xb4]"
    },
    {
      "address": "006422e8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006422e9",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "006422eb",
      "instruction": "CALL EAX"
    },
    {
      "address": "006422ed",
      "instruction": "ADD ESI,0xc"
    },
    {
      "address": "006422f0",
      "instruction": "CMP ESI,EBP"
    },
    {
      "address": "006422f2",
      "instruction": "JNZ 0x006422e0"
    },
    {
      "address": "006422f4",
      "instruction": "MOV EBP,dword ptr [ES
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
  "original_bytes": 12139,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with callee stack cleanup\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"machine_type\": \"OpaqueLookupSource*\",\n        \"native_reads\": [\n          \"MOV ESI,[ESP+0x48] at 0x00642263\",\n          \"CMP ESI,EBP / JZ 0x00642375\"\n        ],\n        \"normalized_name\": \"source\",\n        \"note\": \"a null source skips both lookup branches and still zeroes max_6c and runs the gate scan\",\n        \"position\": 1,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueAssetRef,OpaqueInlineWordVector,OpaqueSporepediaAsset,OpaqueSporepediaAsset*\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-SAFE-WAVE10\",\n      \"score\": 28,\n      \"symbol\": \"sporepedia_asset_destroy_00642190\",\n      \"va\": \"0x00642190\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"cursor_buffer_emit_0041e8b0\",\n      \"va\": \"0x0041e8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"skin_painter_state_setup_00506590\",\n      \"va\": \"0x00506590\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE8\",\n      \"score\": 2,\n      \"symbol\": \"editor_creature_walk_controller_set_target_angle_0059b2f0\",\n      \"va\": \"0x0059b2f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"editor_row_publish_005a2010\",\n      \"va\": \"0x005a2010\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"page_visible_slots_refresh_005c0a60\",\n      \"va\": \"0x005c0a60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UI-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"image_archive_scalar_deleting_destructor_00635700\",\n      \"va\": \"0x00635700\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RESOURCE-STATE-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"record_write_get_state_00e310c0\",\n      \"va\": \"0x00e310c0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueSporepediaAsset\",\n  \"cluster\": null,\n  \"confidence\": 0.85,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00642395\",\n        \"direction\": \"out\",\n        \"other\": \"0x004babe0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006423e2\",\n        \"direction\": \"out\",\n        \"other\": \"0x004f3d60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642432\",\n        \"direction\": \"out\",\n        \"other\": \"0x004f3d60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642482\",\n        \"direction\": \"out\",\n        \"other\": \"0x004f3d60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0064249c\",\n        \"direction\": \"out\",\n        \"other\": \"0x004f5720\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006422c1\",\n        \"direction\": \"out\",\n        \"other\": \"0x005507a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006422cc\",\n        \"direction\": \"out\",\n        \"other\": \"0x005507a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006424f3\",\n        \"direction\": \"out\",\n        \"other\": \"0x0060a600\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006424b6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00642070\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642301\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dea0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642321\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dea0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642328\",\n        \"direction\": \"out\",\n        \"other\": \"0x007db5e0\",\n        \"reference_type
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
  "body_end": "0064252f",
  "body_span_bytes": 768,
  "body_start": "00642230",
  "callees": [
    "FUN_004f3d60",
    "FUN_00f47380",
    "FUN_0067dea0",
    "FUN_007db5e0",
    "memcpy",
    "FUN_005507a0",
    "FUN_0060a600",
    "FUN_004f5720",
    "FUN_004babe0",
    "FUN_00642070"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00642230",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00642230",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x242230",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00642230(void)",
  "size_bytes": 768,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00642230",
  "vtables": {
    "referenced_by_vtables": [
      "0x0147ca30",
      "0x0147ca70",
      "0x0147caf8",
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
      "from": "013ff6f8"
    },
    {
      "from": "01462808"
    },
    {
      "from": "0147caa8"
    },
    {
      "from": "0147cb70"
    },
    {
      "from": "0147cc60"
    },
    {
      "from": "01489140"
    },
    {
      "from": "01489460"
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
  "file": "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.cpp",
    "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.hpp",
    "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-sporepedia-safe-wave10/00642230.json"
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
    "Ten callees are modelled as opaque ports and none is promoted to a function record.",
    "The asset apply property vtable slot owner at +0xb4 is unattributed in the live database.",
    "The clear port count argument is computed as last minus last, which is statically zero; the runtime meaning of a zero count is unverified.",
    "The entry vector rewind arithmetic and the inline marker invariant are static only.",
    "The selectors 0x0670da17 and 0x03c609f8 and the three tag globals at 0x015da8e0, 0x015dab18 and 0x015da80c are undecoded.",
    "The signed maximum comparison depends on runtime supplied entry values.",
    "gate-sporepedia-asset-load-runtime-selectors-and-tag-globals",
    "runtime validation not performed; static decompilation and disassembly only",
    "ten callees are modelled as opaque ports and none is promoted to a function record",
    "the asset apply property vtable slot owner at +0xb4 is unattributed in the live database",
    "the clear port count argument is computed as last minus last, which is statically zero; the runtime meaning of a zero count is unverified",
    "the entry vector rewind arithmetic and the inline marker invariant are static only",
    "the selectors 0x0670da17 and 0x03c609f8 and the three tag globals are undecoded",
    "the signed maximum comparison against max_6c depends on the entry values, which are runtime supplied"
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
  "OpaqueAssetRef",
  "OpaqueGlobalRecord",
  "OpaqueGlobalRecordRange",
  "OpaqueInlineWordVector",
  "OpaqueKey16",
  "OpaqueKeyedSet",
  "OpaqueLookup",
  "OpaqueLookupEntry",
  "OpaqueLookupSource",
  "OpaqueLookupSource*",
  "OpaqueSporepediaAsset",
  "OpaqueSporepediaAsset*",
  "OpaqueWordVector",
  "SporepediaSafeBindings",
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
