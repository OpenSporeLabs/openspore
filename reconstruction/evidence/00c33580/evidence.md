# Evidence 0x00c33580

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `28fc305fc27d0023a5b468d10ee75695b66a9199a111dfd2c6252b952acacf44`

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
  "return_note": "DECLARED void, AND THE DISAGREEMENT WITH THE MACHINE RECORD IS RECORDED RATHER THAN PAPERED OVER. abi.return_semantics is the machine-vocabulary phrase unclassified_in_EAX and abi_derived.return reports register EAX, register_class aggregate_unknown, void_possible false -- so no C++ return type can agree with the canonical claim and the dimension is a WARN whatever is declared. Option (b) of the wave-1 guidance was taken because the bytes genuinely produce nothing: the single RET is reached with EAX holding, per exit, the lookup's null result, record word 2, the handle sentinel 0xffffffff, ...",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +32, so the listing is not one path"
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
  "content_sha256": "77f64cd11f9c1ae58eb34e91c66111ac3508dea66b61f49520263571b574a0ad",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0041"
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
        "obs-0009",
        "obs-0022",
        "obs-0031"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          176
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0009",
        "obs-0022",
        "obs-0031",
        "obs-0041"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
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
        "obs-0041"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0041"
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
      "at": "0x00c33580",
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
      "raw": "SUB ESP,0x24",
      "sub": 36
    },
    {
      "at": "0x00c33580",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x24",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c33583",
      "count": 7,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c33584",
      "count": 9,
      "first_use": 2,
      "first_write_index": 8,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c33584",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c33586",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0xb0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c33595",
      "count": 19,
      "first_use": 6,
      "first_write_index": 3,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00c33596",
      "id": "obs-0008",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00c3359b",
      "definite": true,
      "id": "obs-0009",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c3359d",
      "id": "obs-0010",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ba6d80",
      "target": "0x00ba6d80"
    },
    {
      "at": "0x00c335ac",
      "id": "obs-0011",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bb9b80",
      "target": "0x00bb9b80"
    },
    {
      "at": "0x00c335b3",
      "definite": true,
      "id": "obs-0012",
      "index": 15,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x4]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c335b9",
      "count": 13,
      "first_use": 17,
      "fir
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": "EmpirePoliticalColor_00c32cd0",
    "reconstructed": true,
    "va": "0x00c32cd0"
  },
  {
    "name": "map_int_whatever_find",
    "reconstructed": true,
    "va": "0x00e5c780"
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
    "va": "0x00ba7dc0"
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
  "count": 79,
  "instructions": [
    {
      "address": "00c33580",
      "instruction": "SUB ESP,0x24"
    },
    {
      "address": "00c33583",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c33584",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c33586",
      "instruction": "MOV EAX,dword ptr [ESI + 0xb0]"
    },
    {
      "address": "00c3358c",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00c3358f",
      "instruction": "JZ 0x00c33681"
    },
    {
      "address": "00c33595",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c33596",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00c3359b",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c3359d",
      "instruction": "CALL 0x00ba6d80"
    },
    {
      "address": "00c335a2",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c335a4",
      "instruction": "JZ 0x00c33681"
    },
    {
      "address": "00c335aa",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c335ac",
      "instruction": "CALL 0x00bb9b80"
    },
    {
      "address": "00c335b1",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "00c335b3",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00c335b6",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00c335b9",
      "instruction": "MOV dword ptr [ESP + 0x10],EDX"
    },
    {
      "address": "00c335bd",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "00c335c1",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c335c3",
      "instruction": "JZ 0x00c33681"
    },
    {
      "address": "00c335c9",
      "instruction": "MOV EAX,dword ptr [ESI + 0xb0]"
    },
    {
      "address": "00c335cf",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00c335d2",
      "instruction": "JZ 0x00c33681"
    },
    {
      "address": "00c335d8",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c335d9",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00c335de",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c335e0",
      "instruction": "CALL 0x00ba6d80"
    },
    {
      "address": "00c335e5",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c335e7",
      "instruction": "JZ 0x00c33681"
    },
    {
      "address": "00c335ed",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c335ee",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c335f0",
      "instruction": "CALL 0x00bba500"
    },
    {
      "address": "00c335f5",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00c335f7",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00c335f9",
      "instruction": "JZ 0x00c33680"
    },
    {
      "address": "00c335ff",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "00c33603",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c33604",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c33606",
      "instruction": "CALL 0x00c32cd0"
    },
    {
      "address": "00c3360b",
      "instruction": "MOV EAX,0x1667bac"
    },
    {
      "address": "00c33610",
      "instruction": "LEA EDX,[ESP + 0x1c]"
    },
    {
      "address": "00c33614",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c33615",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c33617",
      "instruction": "MOV dword ptr [ESP + 0x20],EAX"
    },
    {
      "address": "00c3361b",
      "instruction": "MOV dword ptr [ESP + 0x24],EAX"
    },
    {
      "address": "00c3361f",
      "instruction": "MOV dword ptr [ESP + 0x28],0x1667bae"
    },
    {
      "address": "00c33627",
      "instruction": "CALL 0x004da330"
    },
    {
      "address": "00c3362c",
      "instruction": "LEA EAX,[ESP + 0x1c]"
    },
    {
      "address": "00c33630",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c33631",
      "instruction": "LEA ECX,[ESI + 0xc]"
    },
    {
      "address": "00c33634",
      "instruction": "CALL 0x00b6f380"
    },
    {
      "address": "00c33639",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00c3363d",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c3363e",
      "instruction": "LEA EDX,[ESP + 0x10]"
    },
    {
      "address": "00c33642",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c33643",
      "instruction": "LEA ECX,[ESI + 0x14]"
    },
    {
      "address": "00c33646",
      "instruction": "MOV dword ptr [ESP + 0x10],0x2"
    },
    {
      "address": "00c3364e",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "00c33653",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00c33655",
      "instruction": "MOV ECX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00c33658",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c33659",
      "instruction": "LEA ECX,[ESI + 0x3c]"
    },
    {
      "address": "00c3365c",
      "instruction": "CALL 0x005c3d90"
    },
    {
      "address": "00c33661",
      "instruction": "MOV EDX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00c33665",
      "instruction": "MOV EAX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00c33669",
      "instruction": "SUB EDX,EAX"
    },
    {
      "address": "00c3366b",
      "instruction": "AND EDX,0xfffffffe"
    },
    {
      "address": "00c3366e",
      "instruction": "CMP EDX,0x2"
    },
    {
      "address": "00c33671",
      "instruction": "JLE 0x00c33680"
    },
    {
      "address": "00c33673",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c33675",
      "instruction": "JZ 0x00c33680"
    },
    {
      "address":
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
  "original_bytes": 11742,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_note\": \"DECLARED void, AND THE DISAGREEMENT WITH THE MACHINE RECORD IS RECORDED RATHER THAN PAPERED OVER. abi.return_semantics is the machine-vocabulary phrase unclassified_in_EAX and abi_derived.return reports register EAX, register_class aggregate_unknown, void_possible false -- so no C++ return type can agree with the canonical claim and the dimension is a WARN whatever is declared. Option (b) of the wave-1 guidance was taken because the bytes genuinely produce nothing: the single RET is reached with EAX holding, per exit, the lookup's null result, record word 2, the handle sentinel 0xffffffff, ...\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 9,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 9,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"EmpirePoliticalColor_00c32cd0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00c32cd0\"\n      },\n      {\n        \"name\": \"map_int_whatever_find\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c780\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba7dc0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00ba7e23\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba7dc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c33627\",\n        \"direction\": \"out\",\n        \"other\": \"0x004da330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c3365c\",\n        \"direction\": \"out\",\n        \"other\": \"0x005c3d90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c33596\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c335d9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c33634\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b6f380\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c3359d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ba6d80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c335e0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ba6d80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c335ac\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bb9b80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c335f0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bba500\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c33606\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c32cd0\",\n        \"reference_type\": \"dire
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
  "body_end": "00c33685",
  "body_span_bytes": 262,
  "body_start": "00c33580",
  "callees": [
    "FUN_00bb9b80",
    "FUN_00f47380",
    "FUN_00ba6d80",
    "FUN_00c32cd0",
    "FUN_00bba500",
    "FUN_004da330",
    "FUN_00b3d2a0",
    "FUN_00b6f380",
    "FUN_005c3d90",
    "map_int_whatever_find"
  ],
  "callers": [
    "FUN_00ba7dc0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c33580",
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
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:1",
      "type": "undefined"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:1",
      "type": "undefined"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 8,
  "mode": "live",
  "name": "FUN_00c33580",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x833580",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c33580(void)",
  "size_bytes": 262,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c33580",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00ba7e23"
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
  "global:evidence ceiling, not a source defect (see unresolved_questions)."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580.cpp",
    "reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00c33580/sw2_00c33580_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00c33580/00c33580.json"
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
