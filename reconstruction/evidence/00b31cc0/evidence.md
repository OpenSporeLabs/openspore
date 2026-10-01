# Evidence 0x00b31cc0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e82496dcc0cdf4ef73104c18576bad96ebf0fcd85c8c45aadbfa5ad421a95843`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall with one ordinary stack word",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "pointer-sized context word",
      "normalized_name": "first_stack_word",
      "position": 1,
      "width_bytes": 4
    }
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_width_bytes": 0,
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
        "size_inferred": true,
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
    "flow_not_modelled: the linear ESP walk ends at +52, so the listing is not one path",
    "unparsed_lines_present: 2 line(s) matched no grammar rule"
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
  "content_sha256": "18ff4ee40c298c11c50bb55ea1cab2ee999eca60bf45df377184a8ec951a0aa8",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall with one ordinary stack word"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0074"
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
        "obs-0005",
        "obs-0010"
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
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0019",
        "obs-0037",
        "obs-0043",
        "obs-0048",
        "obs-0051",
        "obs-0054",
        "obs-0060"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0019",
        "obs-0037",
        "obs-0043",
        "obs-0048",
        "obs-0051",
        "obs-0054",
        "obs-0060",
        "obs-0074"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0074"
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
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00b31cc0",
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
      "sub": 96
    },
    {
      "at": "0x00b31cc0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00b31cc3",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "reg": "EBX"
    },
    {
      "at": "0x00b31cc4",
      "count": 31,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "reg": "ESP"
    },
    {
      "at": "0x00b31cc4",
      "base": "ESP",
      "disp": 104,
      "id": "obs-0005",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00b31cc4",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b31cc8",
      "count": 2,
      "first_use": 3,
      "first_write_index": 12,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "reg": "ESI"
    },
    {
      "at": "0x00b31cc9",
      "count": 3,
      "first_use": 4,
      "first_write_index": 8,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_READ",
      "reg": "EDI"
    },
    {
      "at": "0x00b31cce",
      "count": 26,
      "first_use": 7,
      "first_write_index": 16,
      "id": "obs-0009",
      "index": 
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "pkg13_creature_accessor_00b1fdb0",
    "reconstructed": true,
    "va": "0x00b1fdb0"
  },
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
  },
  {
    "name": "FUN_01021260",
    "reconstructed": true,
    "va": "0x01021260"
  }
]
```

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
  "count": 128,
  "instructions": [
    {
      "address": "00b31cc0",
      "instruction": "SUB ESP,0x60"
    },
    {
      "address": "00b31cc3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b31cc4",
      "instruction": "MOV EBX,dword ptr [ESP + 0x68]"
    },
    {
      "address": "00b31cc8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b31cc9",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b31cca",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00b31ccc",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00b31cce",
      "instruction": "LEA EAX,[ESP + 0x78]"
    },
    {
      "address": "00b31cd2",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00b31cd4",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b31cd5",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00b31cd7",
      "instruction": "CALL 0x00838020"
    },
    {
      "address": "00b31cdc",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00b31cde",
      "instruction": "CALL 0x00bc30b0"
    },
    {
      "address": "00b31ce3",
      "instruction": "CMP dword ptr [ESP + 0x70],0x0"
    },
    {
      "address": "00b31ce8",
      "instruction": "JLE 0x00b31e41"
    },
    {
      "address": "00b31cee",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00b31cf0",
      "instruction": "MOV ECX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "00b31cf3",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00b31cf5",
      "instruction": "MOV EDX,dword ptr [EDX + 0xa4]"
    },
    {
      "address": "00b31cfb",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b31cfc",
      "instruction": "LEA EAX,[ESP + 0x14]"
    },
    {
      "address": "00b31d00",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b31d01",
      "instruction": "CALL EDX"
    },
    {
      "address": "00b31d03",
      "instruction": "MOVSS XMM1,dword ptr [EAX]"
    },
    {
      "address": "00b31d07",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00b31d0c",
      "instruction": "MULSS XMM0,dword ptr [0x01460388]"
    },
    {
      "address": "00b31d14",
      "instruction": "MULSS XMM1,dword ptr [0x0140ebc0]"
    },
    {
      "address": "00b31d1c",
      "instruction": "ADDSS XMM0,XMM1"
    },
    {
      "address": "00b31d20",
      "instruction": "MOVSS dword ptr [ESP + 0x24],XMM0"
    },
    {
      "address": "00b31d26",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00b31d29",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM0"
    },
    {
      "address": "00b31d2f",
      "instruction": "MOVSS XMM0,dword ptr [0x01485720]"
    },
    {
      "address": "00b31d37",
      "instruction": "MOVSS dword ptr [ESP + 0xc],XMM0"
    },
    {
      "address": "00b31d3d",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00b31d43",
      "instruction": "MAXSS XMM0,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00b31d49",
      "instruction": "MINSS XMM0,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00b31d4f",
      "instruction": "MOVSS dword ptr [ESP + 0x24],XMM0"
    },
    {
      "address": "00b31d55",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00b31d5a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b31d5c",
      "instruction": "CALL 0x00b1fdb0"
    },
    {
      "address": "00b31d61",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b31d63",
      "instruction": "JZ 0x00b31d87"
    },
    {
      "address": "00b31d65",
      "instruction": "LEA ECX,[EAX + 0xc0]"
    },
    {
      "address": "00b31d6b",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00b31d6d",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "00b31d70",
      "instruction": "CALL EDX"
    },
    {
      "address": "00b31d72",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "00b31d74",
      "instruction": "MOV dword ptr [ESP + 0x18],ECX"
    },
    {
      "address": "00b31d78",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00b31d7b",
      "instruction": "MOV dword ptr [ESP + 0x1c],EDX"
    },
    {
      "address": "00b31d7f",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00b31d82",
      "instruction": "JMP 0x00b31e09"
    },
    {
      "address": "00b31d87",
      "instruction": "MOVSS XMM0,dword ptr [0x0167e8b0]"
    },
    {
      "address": "00b31d8f",
      "instruction": "MOVSS dword ptr [ESP + 0x38],XMM0"
    },
    {
      "address": "00b31d95",
      "instruction": "MOVSS XMM0,dword ptr [0x0167e8b4]"
    },
    {
      "address": "00b31d9d",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00b31d9f",
      "instruction": "MOVSS dword ptr [ESP + 0x3c],XMM0"
    },
    {
      "address": "00b31da5",
      "instruction": "MOVSS XMM0,dword ptr [0x0167e8b8]"
    },
    {
      "address": "00b31dad",
      "instruction": "MOV word ptr [ESP + 0x34],CX"
    },
    {
      "address": "00b31db2",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00b31db4",
      "instruction": "MOVSS dword ptr [ESP + 0x40],XMM0"
    },
    {
      "address": "00b31dba",
      "instruction": "MOVSS XMM0,dword ptr [0x01485720]"
    },
    {
      "address": "00b31dc2",
      "instruction": "PUSH 0x167e8e0"
    },
    {
      "address": "00b31dc7",
      "instruction": "LEA ECX,[ESP + 0x4c]"
    },
    {
      "address": "00b31dcb",
      "instruction": "MOV word ptr [ESP + 0x3a],DX"
    },
    {
      "address": "00b31dd0",
      "instruction": "MOVSS dword ptr [ESP + 0x48],XMM0"
    },
    {
      "address": "00b31dd6",
      "instruction": "CALL 0x0041cb40"
    },
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
  "original_bytes": 7905,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with one ordinary stack word\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"machine_type\": \"pointer-sized context word\",\n        \"normalized_name\": \"first_stack_word\",\n        \"position\": 1,\n        \"width_bytes\": 4\n      }\n    ],\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 0,\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCellUpdateBody\"\n      ],\n      \"package\": \"PKG-FRAME-RUNTIME-WAVE8\",\n      \"score\": 22,\n      \"symbol\": \"cell_update_body_00e806b0\",\n      \"va\": \"0x00e806b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-FRAME-RUNTIME-WAVE7\",\n      \"score\": 9,\n      \"symbol\": \"cell_mode_update_00e80980\",\n      \"va\": \"0x00e80980\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-FRAME-RUNTIME-WAVE7\",\n      \"score\": 6,\n      \"symbol\": \"app_frame_update_00f47930\",\n      \"va\": \"0x00f47930\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 3,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0100\",\n      \"va\": \"0x005c0100\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 3,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCellUpdateBody\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"pkg13_creature_accessor_00b1fdb0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b1fdb0\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      },\n      {\n        \"name\": \"FUN_01021260\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021260\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b31dd6\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041cb40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31ddb\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31df0\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c40f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31cd7\",\n        \"direction\": \"out\",\n        \"other\": \"0x00838020\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31e4a\",\n        \"direction\": \"out\",\n        \"other\": \"0x00838330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31d5c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b1fdb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31d55\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31e8b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bc28c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31e3c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bc2f00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31cde\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bc30b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31e16\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bc30b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31e35\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bc30b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31e84\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bc30b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b31e0d\",\n        \"direction\": \"out\",\n        \"other\": \"0x01021260\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_
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
  "body_end": "00b31e98",
  "body_span_bytes": 473,
  "body_start": "00b31cc0",
  "callees": [
    "FUN_00bc30b0",
    "FUN_00b1fdb0",
    "Graphics::IRenderer::Get",
    "FUN_00bc2f00",
    "FUN_0041cb40",
    "FUN_01021260",
    "FUN_007c40f0",
    "FUN_00b3d300",
    "FUN_00838020",
    "FUN_00838330",
    "FUN_00bc28c0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b31cc0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_5c",
      "storage": "Stack[-0x5c]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00b31cc0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x731cc0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b31cc0(void)",
  "size_bytes": 473,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b31cc0",
  "vtables": {
    "referenced_by_vtables": [
      "0x014602a0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "014602a0"
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
  "global:timing_root_00b3d300 is called before the runtime accessor."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.cpp",
  "files": [
    "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.cpp",
    "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.hpp",
    "src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-frame-runtime-wave8/00b31cc0.json"
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
    "required"
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
  "DATA",
  "OpaqueCellUpdateBody",
  "OpaqueTimingOwner*"
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
