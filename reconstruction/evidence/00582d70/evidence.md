# Evidence 0x00582d70

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c80e2c0326a5e625b8a626ee065852c25de312a311a990335db2a9dac5f2c5a1`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is copied to ESI at 0x00582d74 and read only as [ESI + disp]; the function passes it on to 0x0057ef50 and 0x009c69f0 as ECX after loading LEA EBP,[ESI + 0x36c] at 0x00582e5b and 0x00582ef6, so the vector helpers take the address of the begin field as their receiver",
  "ordinary_stack_argument_slots": 3,
  "receiver": true,
  "ret_form": "RET 0xc",
  "return_observation": "EAX is used only as scratch: the divide-by-0x30 sign correction at 0x00582db7 and the element-address computation at 0x00582df0 overwrite it before every call, and the last write before the epilogue is 0x00582ea1 LEA EDI,... / 0x00582ea8 SHL EDI,0x4",
  "return_register": "none",
  "return_semantics": "no value; the body never writes EAX on any exit path and all six exits share the same four-instruction epilogue",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    {
      "frame_offset": "[ESP + 0x18] at 0x00582d87",
      "index": 1,
      "meaning": "mode selector; compared against 1 at 0x00582d8b, against 0 at 0x00582f72 and against 2 at 0x00582fb3",
      "width": 4
    },
    {
      "frame_offset": "[ESP + 0x1c] at 0x00582d94",
      "index": 2,
      "meaning": "remove_last, read as a BYTE; any non-zero byte selects the remove-last path, so only bit 0 of the pushed dword matters",
      "width": 1
    },
    {
      "frame_offset": "[ESP + 0x28] at 0x00582e61 after PUSH EBX; PUSH EBP",
      "index": 3,
      "meaning": "handle, compared against element dword 0 in the linear search at 0x00582e88 and tested against zero at 0x00582e61 to choose between clear-all and remove-by-handle",
      "width": 4
    }
  ],
  "stack_cleanup_bytes": 12,
  "stack_cleanup_owner": "callee",
  "termination": "six exits, all through the same epilogue: 0x00582e96 (null anim world, empty array, or an unrecognised mode), 0x00582e56 (mode 1 remove-last), 0x00582e9b (mode 1 not found), 0x00582ef3 (mode 1 remove-by-handle), 0x00582f6f (mode 1 clear-all), 0x00582fb0 (mode 0), 0x00582fdb (mode 2)"
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
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
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
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -20, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_width_ambiguous: one entry slot is read at more than one width"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "368dccfeac9229847d13938e6a82bed8892d408c305da594747e3dfdec2a13ec",
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
        "obs-0024",
        "obs-0037",
        "obs-0052",
        "obs-0070",
        "obs-0075",
        "obs-0079"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0012",
        "obs-0027",
        "obs-0031",
        "obs-0039",
        "obs-0041",
        "obs-0056",
        "obs-0058"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0012",
        "obs-0027",
        "obs-0031",
        "obs-0039",
        "obs-0041",
        "obs-0056",
        "obs-0058"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0018",
        "obs-0041",
        "obs-0046",
        "obs-0053",
        "obs-0054"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          864,
          868,
          872,
          876,
          880,
          901
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0018",
        "obs-0024",
        "obs-0037",
        "obs-0041",
        "obs-0046",
        "obs-0052",
        "obs-0053",
        "obs-0054",
        "obs-0070",
        "obs-0075",
        "obs-0079"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0024",
        "obs-0037",
        "obs-0052",
        "obs-0070",
        "obs-0075",
        "obs-0079"
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
        "obs
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059d110"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062ba10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062c340"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062c990"
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
  "count": 199,
  "instructions": [
    {
      "address": "00582d70",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "00582d73",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00582d74",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00582d76",
      "instruction": "MOV ECX,dword ptr [ESI + 0x360]"
    },
    {
      "address": "00582d7c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00582d7d",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00582d7f",
      "instruction": "CMP ECX,EDI"
    },
    {
      "address": "00582d81",
      "instruction": "JZ 0x00582e96"
    },
    {
      "address": "00582d87",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00582d8b",
      "instruction": "CMP EAX,0x1"
    },
    {
      "address": "00582d8e",
      "instruction": "JNZ 0x00582f72"
    },
    {
      "address": "00582d94",
      "instruction": "CMP byte ptr [ESP + 0x1c],0x0"
    },
    {
      "address": "00582d99",
      "instruction": "MOV EAX,0x2aaaaaab"
    },
    {
      "address": "00582d9e",
      "instruction": "JZ 0x00582e59"
    },
    {
      "address": "00582da4",
      "instruction": "MOV EDX,dword ptr [ESI + 0x370]"
    },
    {
      "address": "00582daa",
      "instruction": "SUB EDX,dword ptr [ESI + 0x36c]"
    },
    {
      "address": "00582db0",
      "instruction": "IMUL EDX"
    },
    {
      "address": "00582db2",
      "instruction": "SAR EDX,0x3"
    },
    {
      "address": "00582db5",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00582db7",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "00582dba",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "00582dbc",
      "instruction": "JZ 0x00582e96"
    },
    {
      "address": "00582dc2",
      "instruction": "LEA EDX,[ESP + 0x8]"
    },
    {
      "address": "00582dc6",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00582dc7",
      "instruction": "MOV EDX,dword ptr [ESI + 0x370]"
    },
    {
      "address": "00582dcd",
      "instruction": "SUB EDX,dword ptr [ESI + 0x36c]"
    },
    {
      "address": "00582dd3",
      "instruction": "MOV EAX,0x2aaaaaab"
    },
    {
      "address": "00582dd8",
      "instruction": "IMUL EDX"
    },
    {
      "address": "00582dda",
      "instruction": "SAR EDX,0x3"
    },
    {
      "address": "00582ddd",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00582ddf",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "00582de2",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "00582de4",
      "instruction": "MOV EDX,dword ptr [ESI + 0x36c]"
    },
    {
      "address": "00582dea",
      "instruction": "LEA EAX,[EAX + EAX*0x2]"
    },
    {
      "address": "00582ded",
      "instruction": "SHL EAX,0x4"
    },
    {
      "address": "00582df0",
      "instruction": "MOV EAX,dword ptr [EAX + EDX*0x1 + -0x30]"
    },
    {
      "address": "00582df4",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00582df5",
      "instruction": "CALL 0x0059d110"
    },
    {
      "address": "00582dfa",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00582dfe",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00582dff",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00582e00",
      "instruction": "PUSH 0x3f1bf57"
    },
    {
      "address": "00582e05",
      "instruction": "CALL 0x00401050"
    },
    {
      "address": "00582e0a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00582e0c",
      "instruction": "CALL 0x0045af60"
    },
    {
      "address": "00582e11",
      "instruction": "MOV ECX,dword ptr [ESI + 0x370]"
    },
    {
      "address": "00582e17",
      "instruction": "SUB ECX,dword ptr [ESI + 0x36c]"
    },
    {
      "address": "00582e1d",
      "instruction": "MOV EAX,0x2aaaaaab"
    },
    {
      "address": "00582e22",
      "instruction": "IMUL ECX"
    },
    {
      "address": "00582e24",
      "instruction": "SAR EDX,0x3"
    },
    {
      "address": "00582e27",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00582e29",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "00582e2c",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "00582e2e",
      "instruction": "LEA EDX,[EAX + EAX*0x2]"
    },
    {
      "address": "00582e31",
      "instruction": "MOV EAX,dword ptr [ESI + 0x36c]"
    },
    {
      "address": "00582e37",
      "instruction": "SHL EDX,0x4"
    },
    {
      "address": "00582e3a",
      "instruction": "MOV ECX,dword ptr [EDX + EAX*0x1 + -0x30]"
    },
    {
      "address": "00582e3e",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00582e3f",
      "instruction": "MOV ECX,dword ptr [ESI + 0x360]"
    },
    {
      "address": "00582e45",
      "instruction": "CALL 0x0059c6e0"
    },
    {
      "address": "00582e4a",
      "instruction": "ADD dword ptr [ESI + 0x370],-0x30"
    },
    {
      "address": "00582e51",
      "instruction": "POP EDI"
    },
    {
      "address": "00582e52",
      "instruction": "POP ESI"
    },
    {
      "address": "00582e53",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00582e56",
      "instruction": "RET 0xc"
    },
    {
      "address": "00582e59",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00582e5a",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00582e5b",
      "instruction": "LEA EBP,[ESI + 0x36c]"
    },
    {
      "address": "00582e61",
      "instruction": "CMP dword ptr [ESP + 0x28],EDI"
    },
    {
      "address": "00582e65",
      "instruction": "JZ 0x00582ef6"
    },
    {
      "address": "00582e6b",
      "instruction": "MOV EDX,dword ptr [EBP + 0x4]"
    },
    {
      "address": "00582e6e",
      "instruction": "SUB EDX,dword ptr [EBP]"
 
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
  "original_bytes": 12085,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX\",\n    \"hidden_this_register\": \"ECX is copied to ESI at 0x00582d74 and read only as [ESI + disp]; the function passes it on to 0x0057ef50 and 0x009c69f0 as ECX after loading LEA EBP,[ESI + 0x36c] at 0x00582e5b and 0x00582ef6, so the vector helpers take the address of the begin field as their receiver\",\n    \"ordinary_stack_argument_slots\": 3,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0xc\",\n    \"return_observation\": \"EAX is used only as scratch: the divide-by-0x30 sign correction at 0x00582db7 and the element-address computation at 0x00582df0 overwrite it before every call, and the last write before the epilogue is 0x00582ea1 LEA EDI,... / 0x00582ea8 SHL EDI,0x4\",\n    \"return_register\": \"none\",\n    \"return_semantics\": \"no value; the body never writes EAX on any exit path and all six exits share the same four-instruction epilogue\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"frame_offset\": \"[ESP + 0x18] at 0x00582d87\",\n        \"index\": 1,\n        \"meaning\": \"mode selector; compared against 1 at 0x00582d8b, against 0 at 0x00582f72 and against 2 at 0x00582fb3\",\n        \"width\": 4\n      },\n      {\n        \"frame_offset\": \"[ESP + 0x1c] at 0x00582d94\",\n        \"index\": 2,\n        \"meaning\": \"remove_last, read as a BYTE; any non-zero byte selects the remove-last path, so only bit 0 of the pushed dword matters\",\n        \"width\": 1\n      },\n      {\n        \"frame_offset\": \"[ESP + 0x28] at 0x00582e61 after PUSH EBX; PUSH EBP\",\n        \"index\": 3,\n        \"meaning\": \"handle, compared against element dword 0 in the linear search at 0x00582e88 and tested against zero at 0x00582e61 to choose between clear-all and remove-by-handle\",\n        \"width\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 12,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"six exits, all through the same epilogue: 0x00582e96 (null anim world, empty array, or an unrecognised mode), 0x00582e56 (mode 1 remove-last), 0x00582e9b (mode 1 not found), 0x00582ef3 (mode 1 remove-by-handle), 0x00582f6f (mode 1 clear-all), 0x00582fb0 (mode 0), 0x00582fdb (mode 2)\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d110\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062ba10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062c340\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062c990\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0062ba5e\",\n        \"direction\": \"in\",\n        \"other\": \"0x0062ba10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0062ba7f\",\n        \"direction\": \"in\",\n        \"other\": \"0x0062ba10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0062c3de\",\n        \"direction\": \"in\",\n        \"other\": \"0x0062c340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0062ca18\",\n        \"direction\": \"in\",\n        \"other\": \"0x0062c990\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"call
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
  "body_end": "00582fdd",
  "body_span_bytes": 622,
  "body_start": "00582d70",
  "callees": [
    "FUN_0057e340",
    "Editors::cEditorAnimWorld::DestroyCreature",
    "FUN_00401050",
    "FUN_0059d110",
    "FUN_0045af60",
    "FUN_009c69f0",
    "FUN_0057ef50"
  ],
  "callers": [
    "FUN_0062ba10",
    "FUN_0062c340",
    "FUN_0062c990"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00582d70",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00582d70",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x182d70",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00582d70(void)",
  "size_bytes": 622,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00582d70",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "0062c3de"
    },
    {
      "from": "0062ba5e"
    },
    {
      "from": "0062ba7f"
    },
    {
      "from": "0062ca18"
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
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b02/b582d70_editor_remove_creature.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/b582d70_editor_remove_creature.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b02/00582d70.json"
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
    "A runtime trace is required to confirm modes 0 and 2 are never taken, since no static reference to them exists.",
    "A runtime trace is required to confirm no entry destructor is needed, i.e. that the removed 0x30-byte entries leak or are owned elsewhere by design.",
    "A runtime trace is required to observe the 0x03f1bf57 notification reaching a listener, which is the only way to learn what the detach protocol announces.",
    "No original-process trace has ever been captured for 0x00582d70; every claim here is static. The original Cell stage has never been entered in any recorded run."
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
  "status": "unresolved"
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
