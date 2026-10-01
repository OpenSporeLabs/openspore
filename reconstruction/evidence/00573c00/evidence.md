# Evidence 0x00573c00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e24f97e2807336f8f07f06e4058f94c070dd91a4d5800f39d996fce38e64d8c6`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, copied to ESI at 0x00573c02; EBX is then set to the ADDRESS of the receiver's +0xcc field at 0x00573c0e (LEA EBX,[ESI + 0xcc]) and used as a first-class pointer for the rest of the body",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "the only store of a computed value is 0x00573d5a..0x00573d61: CMP dword ptr [EBX],0x0 / POP EDI / SETNZ CL / MOV byte ptr [ESI + 0x398],CL. Nothing is returned in a register.",
  "return_register": "none (EAX is scratch throughout; the last value in it is discarded at 0x00573d69)",
  "return_semantics": "no register result. The single observable outcome is the byte written to receiver + 0x398, which is the boolean 'the +0xcc slot is non-null' and is refreshed on every path including both early exits.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "offset_in_callee": "[ESP + 0x10] with ESP lowered 12",
      "read_by": "0x00573c15: MOV EDI,dword ptr [ESP + 0x10]",
      "role": "the incoming rigblock pointer, stored in EDI and tested at 0x00573c19, 0x00573c80, 0x00573cc1",
      "slot": 1,
      "width_bytes": 4
    },
    {
      "offset_in_callee": "[ESP + 0x10] with ESP lowered 8",
      "read_by": "0x00573c0a: MOV ECX,dword ptr [ESP + 0x10]",
      "role": "the paint-region value, stored in ECX and latched into +0x3b0 and +0x3b4 at 0x00573c31/0x00573c37",
      "slot": 2,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8"
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
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "6cabac94c4a51a0283cc6c4f557418f98ac01f7c7e344b03a8fd321273aecab7",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0033"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0010"
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
        "obs-0003",
        "obs-0004",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0018"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          60,
          204,
          228,
          796,
          920,
          944,
          948,
          964,
          1176
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0018",
        "obs-0033"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
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
        "obs-0033"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0033"
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
      "at": "0x00573c00",
      "count": 12,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00573c01",
      "count": 15,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00573c02",
      "count": 7,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00573c02",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00573c04",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0xcc]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00573c0a",
      "count": 2,
      "first_use": 4,
      "first_write_index": 24,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
  
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
    "va": "0x004a88d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004b09b0"
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
    "va": "0x00573d70"
  },
  {
    "name": "FUN_005774f0",
    "reconstructed": false,
    "va": "0x005774f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00577520"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057f6c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005858f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": "Editors::cEditor::OnExit",
    "reconstructed": false,
    "va": "0x00587a20"
  },
  {
    "name": "editor_input_00588570",
    "reconstructed": true,
    "va": "0x00588570"
  },
  {
    "name": "editor_input_0058ac10",
    "reconstructed": true,
    "va": "0x0058ac10"
  },
  {
    "name": "editor_input_0058b650",
    "reconstructed": true,
    "va": "0x0058b650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0058ba60"
  },
  {
    "name": "Editors::cEditor::HandleMessage",
    "reconstructed": false,
    "va": "0x00591fa0"
  },
  {
    "name": "Editors_EditorUI_HandleMessage_005e0000",
    "reconstructed": true,
    "va": "0x005e0000"
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
  "count": 115,
  "instructions": [
    {
      "address": "00573c00",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00573c01",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00573c02",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00573c04",
      "instruction": "MOV EAX,dword ptr [ESI + 0xcc]"
    },
    {
      "address": "00573c0a",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00573c0e",
      "instruction": "LEA EBX,[ESI + 0xcc]"
    },
    {
      "address": "00573c14",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00573c15",
      "instruction": "MOV EDI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00573c19",
      "instruction": "CMP EDI,EAX"
    },
    {
      "address": "00573c1b",
      "instruction": "JNZ 0x00573c31"
    },
    {
      "address": "00573c1d",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00573c1f",
      "instruction": "JZ 0x00573d5a"
    },
    {
      "address": "00573c25",
      "instruction": "CMP ECX,dword ptr [ESI + 0x3b0]"
    },
    {
      "address": "00573c2b",
      "instruction": "JZ 0x00573d5a"
    },
    {
      "address": "00573c31",
      "instruction": "MOV dword ptr [ESI + 0x3b0],ECX"
    },
    {
      "address": "00573c37",
      "instruction": "MOV dword ptr [ESI + 0x3b4],ECX"
    },
    {
      "address": "00573c3d",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00573c3f",
      "instruction": "JZ 0x00573d5a"
    },
    {
      "address": "00573c45",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00573c47",
      "instruction": "JZ 0x00573c80"
    },
    {
      "address": "00573c49",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00573c4a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00573c4b",
      "instruction": "CALL 0x004a60a0"
    },
    {
      "address": "00573c50",
      "instruction": "MOV ECX,dword ptr [ESI + 0xe4]"
    },
    {
      "address": "00573c56",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00573c59",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00573c5b",
      "instruction": "SETZ AL"
    },
    {
      "address": "00573c5e",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00573c60",
      "instruction": "JZ 0x00573c77"
    },
    {
      "address": "00573c62",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00573c64",
      "instruction": "JZ 0x00573c77"
    },
    {
      "address": "00573c66",
      "instruction": "CALL 0x0047e6c0"
    },
    {
      "address": "00573c6b",
      "instruction": "MOV ECX,dword ptr [EBX]"
    },
    {
      "address": "00573c6d",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00573c6e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00573c6f",
      "instruction": "CALL 0x004a60a0"
    },
    {
      "address": "00573c74",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00573c77",
      "instruction": "MOV ECX,dword ptr [EBX]"
    },
    {
      "address": "00573c79",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00573c7b",
      "instruction": "CALL 0x0043a830"
    },
    {
      "address": "00573c80",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00573c82",
      "instruction": "JNZ 0x00573cc1"
    },
    {
      "address": "00573c84",
      "instruction": "MOV ECX,dword ptr [EBX]"
    },
    {
      "address": "00573c86",
      "instruction": "MOV EDX,dword ptr [ECX + 0xdc8]"
    },
    {
      "address": "00573c8c",
      "instruction": "SHR EDX,0x3"
    },
    {
      "address": "00573c8f",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00573c92",
      "instruction": "JZ 0x00573c99"
    },
    {
      "address": "00573c94",
      "instruction": "CALL 0x0043e2b0"
    },
    {
      "address": "00573c99",
      "instruction": "MOV ECX,dword ptr [EBX]"
    },
    {
      "address": "00573c9b",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00573c9d",
      "instruction": "JZ 0x00573cac"
    },
    {
      "address": "00573c9f",
      "instruction": "MOV dword ptr [EBX],0x0"
    },
    {
      "address": "00573ca5",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00573ca7",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00573caa",
      "instruction": "CALL EDX"
    },
    {
      "address": "00573cac",
      "instruction": "MOV ECX,dword ptr [ESI + 0x498]"
    },
    {
      "address": "00573cb2",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00573cb4",
      "instruction": "JZ 0x00573d3e"
    },
    {
      "address": "00573cba",
      "instruction": "CALL 0x005cc690"
    },
    {
      "address": "00573cbf",
      "instruction": "JMP 0x00573d3e"
    },
    {
      "address": "00573cc1",
      "instruction": "MOV EAX,dword ptr [EDI + 0xdc8]"
    },
    {
      "address": "00573cc7",
      "instruction": "SHR EAX,0x1"
    },
    {
      "address": "00573cc9",
      "instruction": "TEST AL,0x1"
    },
    {
      "address": "00573ccb",
      "instruction": "JNZ 0x00573d3e"
    },
    {
      "address": "00573ccd",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00573cce",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00573cd0",
      "instruction": "CALL 0x004b09b0"
    },
    {
      "address": "00573cd5",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00573cd6",
      "instruction": "CALL 0x004a2060"
    },
    {
      "address": "00573cdb",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00573cde",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00573ce0",
      "instruction": "JNZ 0x00573cf1"
    },
    {
      "address": "00573ce2",
      "instruction": "MOV ECX,dword ptr [ESI + 0x498]"
  
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
  "original_bytes": 14618,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX, copied to ESI at 0x00573c02; EBX is then set to the ADDRESS of the receiver's +0xcc field at 0x00573c0e (LEA EBX,[ESI + 0xcc]) and used as a first-class pointer for the rest of the body\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x8\",\n    \"return_observation\": \"the only store of a computed value is 0x00573d5a..0x00573d61: CMP dword ptr [EBX],0x0 / POP EDI / SETNZ CL / MOV byte ptr [ESI + 0x398],CL. Nothing is returned in a register.\",\n    \"return_register\": \"none (EAX is scratch throughout; the last value in it is discarded at 0x00573d69)\",\n    \"return_semantics\": \"no register result. The single observable outcome is the byte written to receiver + 0x398, which is the boolean 'the +0xcc slot is non-null' and is refreshed on every path including both early exits.\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"offset_in_callee\": \"[ESP + 0x10] with ESP lowered 12\",\n        \"read_by\": \"0x00573c15: MOV EDI,dword ptr [ESP + 0x10]\",\n        \"role\": \"the incoming rigblock pointer, stored in EDI and tested at 0x00573c19, 0x00573c80, 0x00573cc1\",\n        \"slot\": 1,\n        \"width_bytes\": 4\n      },\n      {\n        \"offset_in_callee\": \"[ESP + 0x10] with ESP lowered 8\",\n        \"read_by\": \"0x00573c0a: MOV ECX,dword ptr [ESP + 0x10]\",\n        \"role\": \"the paint-region value, stored in ECX and latched into +0x3b0 and +0x3b4 at 0x00573c31/0x00573c37\",\n        \"slot\": 2,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 5,\n      \"symbol\": \"Editors_EditorUI_HandleMessage_005e0000\",\n      \"va\": \"0x005e0000\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004b09b0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573d70\"\n      },\n      {\n        \"name\": \"FUN_005774f0\",\n        \"reconstructed\": false,\n        \"va\": \"0x005774f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00577520\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057f6c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005858f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": \"Editors::cEditor::OnExit\",\n        \"reconstructed\": false,\n        \"va\": \"0x00587a20\"\n      },\n      {\n        \"name\": \"editor_input_00588570\",\n        \"reconstructed\": true,\n        \"va\": \"0x00588570\"\n      },\n      {\n        \"name\": \"editor_input_0058ac10\",\n        \"reconstructed\": true,\n        \"va\": \"0x0058ac10\"\n      },\n      {\n        \"name\": \"editor_input_0058b650\",\n        \"reconstructed\": true,\n        \"va\": \"0x0058b650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0058ba60\"\n      },\n      {\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"reconstructed\": false,\n        \"va\": \"0x00591fa0\"\n      },\n      {\n        \"name\": \"Edit
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
  "body_end": "00573d6b",
  "body_span_bytes": 364,
  "body_start": "00573c00",
  "callees": [
    "FUN_0047e6c0",
    "FUN_004a88d0",
    "FUN_005ca920",
    "FUN_005cc690",
    "FUN_004a60a0",
    "FUN_0043e2b0",
    "FUN_00573520",
    "FUN_004b09b0",
    "FUN_004a2060",
    "FUN_0043a830"
  ],
  "callers": [
    "FUN_0057f6c0",
    "FUN_005774f0",
    "FUN_00577520",
    "Editors::cEditor::OnMouseUp",
    "FUN_005858f0",
    "FUN_00573d70",
    "Editors::cEditor::OnKeyDown",
    "Editors::cEditor::SetActiveMode",
    "Editors::cEditor::OnExit",
    "Editors::cEditor::OnMouseDown",
    "FUN_0058ba60",
    "Editors::cEditor::HandleMessage",
    "FUN_005e0000"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00573c00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00573c00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x173c00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00573c00(void)",
  "size_bytes": 364,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00573c00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 17,
  "xrefs": [
    {
      "from": "0057753d"
    },
    {
      "from": "00573ea3"
    },
    {
      "from": "00587465"
    },
    {
      "from": "00585bcd"
    },
    {
      "from": "00587cd4"
    },
    {
      "from": "0058b99b"
    },
    {
      "from": "0058bc51"
    },
    {
      "from": "0058bc77"
    },
    {
      "from": "0058bd42"
    },
    {
      "from": "005e0353"
    },
    {
      "from": "0058028e"
    },
    {
      "from": "0058aec3"
    },
    {
      "from": "0057750e"
    },
    {
      "from": "00588f8f"
    },
    {
      "from": "00589ca5"
    },
    {
      "from": "0059228a"
    },
    {
      "from": "0059303e"
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
    "reconstruction/staging/wave13-w1-dispatch-b00/editor_00573c00.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b00/editor_00573c00.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b00/00573c00.json"
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
    "12 of the 13 recorded callsites were not disassembled. A full callsite sweep is static work and is listed in unresolved_questions rather than as a runtime gate.",
    "No original-process trace exists for 0x00573c00; every claim is static and the Cell stage has never been entered in any recorded run.",
    "The +0xdc8 bit semantics are the single largest gap and only a run can close it: each bit must be observed being set on a real rigblock together with the behaviour it gates.",
    "The vtable slot +0x8 callee, and the concrete types of the +0x498 and +0x3c4 receivers, require a run with a real editor session.",
    "Whether the discarded comparison at 0x00573c6f matters for its callee's side effects can only be settled by instrumenting 0x004a60a0 at runtime."
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
  "bitflags",
  "bool",
  "handle pointer (nullable)",
  "int",
  "mode enumerator",
  "pointer (nullable)",
  "rigblock pointer (nullable)",
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
