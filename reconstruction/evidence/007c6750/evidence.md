# Evidence 0x007c6750

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `98ece8d181aa8775f956d7a2efd6149cd696765b09ef1f40ee2c141845f6100f`

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
    "entry_ESP+0x4"
  ],
  "ordinary_stack_arguments": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_type": "bool",
  "saved_registers": [
    "EBX",
    "ESI",
    "EBP",
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x20",
      "entry_ESP+0x24",
      "entry_ESP+0x28",
      "entry_ESP+0x2c",
      "entry_ESP+0x30",
      "entry_ESP+0x34",
      "entry_ESP+0x5c"
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x28",
        "observed": true,
        "ordinal": 10,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x5c",
        "observed": true,
        "ordinal": 23,
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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x28",
        "observed": true,
        "ordinal": 10,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
     
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
    "va": "0x007c3c20"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8d40",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8d40",
      "0x007d85b0",
      "0x007d8d40",
      "0x01412598",
      "0x007d8c80",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6750"
    ],
    "conflict_id": "app_mode_setter_boundary",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x007c61a0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6eb0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6750",
      "0x007c6750",
      "0x007c6eb0",
      "0x007c6eb0"
    ],
    "conflict_id": "camera_address_conflicts",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
  "count": 360,
  "instructions": [
    {
      "address": "007c6750",
      "instruction": "MOV EAX,FS:[0x0]"
    },
    {
      "address": "007c6756",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "007c6758",
      "instruction": "PUSH 0x12152f8"
    },
    {
      "address": "007c675d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007c675e",
      "instruction": "MOV dword ptr FS:[0x0],ESP"
    },
    {
      "address": "007c6765",
      "instruction": "SUB ESP,0x30"
    },
    {
      "address": "007c6768",
      "instruction": "PUSH EBX"
    },
    {
      "address": "007c6769",
      "instruction": "MOV EBX,dword ptr [ESP + 0x44]"
    },
    {
      "address": "007c676d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007c676e",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "007c6770",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "007c6772",
      "instruction": "CALL 0x00837f30"
    },
    {
      "address": "007c6777",
      "instruction": "CMP EAX,0x1"
    },
    {
      "address": "007c677a",
      "instruction": "JNZ 0x007c67de"
    },
    {
      "address": "007c677c",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "007c677f",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "007c6781",
      "instruction": "MOV EDX,dword ptr [EAX + 0x58]"
    },
    {
      "address": "007c6784",
      "instruction": "CALL EDX"
    },
    {
      "address": "007c6786",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "007c6789",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "007c678b",
      "instruction": "JL 0x007c67b7"
    },
    {
      "address": "007c678d",
      "instruction": "MOV EDX,dword ptr [ECX + 0x98]"
    },
    {
      "address": "007c6793",
      "instruction": "SUB EDX,dword ptr [ECX + 0x94]"
    },
    {
      "address": "007c6799",
      "instruction": "SAR EDX,0x4"
    },
    {
      "address": "007c679c",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "007c679e",
      "instruction": "JGE 0x007c67b7"
    },
    {
      "address": "007c67a0",
      "instruction": "MOV ECX,dword ptr [ECX + 0x94]"
    },
    {
      "address": "007c67a6",
      "instruction": "SHL EAX,0x4"
    },
    {
      "address": "007c67a9",
      "instruction": "MOV EDX,dword ptr [EAX + ECX*0x1]"
    },
    {
      "address": "007c67ac",
      "instruction": "ADD EAX,ECX"
    },
    {
      "address": "007c67ae",
      "instruction": "CMP EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "007c67b1",
      "instruction": "JZ 0x007c67b7"
    },
    {
      "address": "007c67b3",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "007c67b5",
      "instruction": "JMP 0x007c67b9"
    },
    {
      "address": "007c67b7",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "007c67b9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007c67ba",
      "instruction": "MOV EAX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "007c67bd",
      "instruction": "PUSH 0x141067c"
    },
    {
      "address": "007c67c2",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007c67c3",
      "instruction": "CALL 0x00841000"
    },
    {
      "address": "007c67c8",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "007c67cb",
      "instruction": "POP ESI"
    },
    {
      "address": "007c67cc",
      "instruction": "POP EBX"
    },
    {
      "address": "007c67cd",
      "instruction": "MOV ECX,dword ptr [ESP + 0x30]"
    },
    {
      "address": "007c67d1",
      "instruction": "MOV dword ptr FS:[0x0],ECX"
    },
    {
      "address": "007c67d8",
      "instruction": "ADD ESP,0x3c"
    },
    {
      "address": "007c67db",
      "instruction": "RET 0x4"
    },
    {
      "address": "007c67de",
      "instruction": "PUSH EBP"
    },
    {
      "address": "007c67df",
      "instruction": "PUSH EDI"
    },
    {
      "address": "007c67e0",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "007c67e2",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "007c67e4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "007c67e5",
      "instruction": "LEA ECX,[ESP + 0x24]"
    },
    {
      "address": "007c67e9",
      "instruction": "PUSH ECX"
    },
    {
      "address": "007c67ea",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "007c67ec",
      "instruction": "CALL 0x00838020"
    },
    {
      "address": "007c67f1",
      "instruction": "CMP dword ptr [ESP + 0x1c],0x1"
    },
    {
      "address": "007c67f6",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "007c67f8",
      "instruction": "MOV dword ptr [ESP + 0x10],EBP"
    },
    {
      "address": "007c67fc",
      "instruction": "JZ 0x007c681a"
    },
    {
      "address": "007c67fe",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "007c6800",
      "instruction": "PUSH 0x13f2ce4"
    },
    {
      "address": "007c6805",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "007c6807",
      "instruction": "CALL 0x00838330"
    },
    {
      "address": "007c680c",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "007c6810",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "007c6812",
      "instruction": "JZ 0x007c6966"
    },
    {
      "address": "007c6818",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "007c681a",
      "instruction": "MOV EDX,dword ptr [EBP]"
    },
    {
      "address": "007c681d",
      "instruction": "MOVZX EAX,byte ptr [EDX]"
    },
    {
      "address": "007c6820",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007c6821",
      "instruction": "CALL dword ptr [0x013cc4cc]"
    },
    {
      "address": "007c6827",
      "instruction": "ADD E
[TRUNCATED]
```

## external_callees

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "EXT:MSVCR90.DLL::_wcsicmp",
  "EXT:MSVCR90.DLL::isdigit"
]
```

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 10620,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"bool\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EBP\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 8,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 8,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 8,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 8,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 8,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007c3c20\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x007c68e5\",\n        \"direction\": \"out\",\n        \"other\": \"0x0052df30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6b12\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6b52\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6b27\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3c20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6b65\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c3ce0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6a3d\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c65a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6772\",\n        \"direction\": \"out\",\n        \"other\": \"0x00837f30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c67ec\",\n        \"direction\": \"out\",\n        \"other\": \"0x00838020\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c696d\",\n        \"direction\": \"out\",\n        \"other\": \"0x008380b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6807\",\n        \"direction\": \"out\",\n        \"other\": \"0x00838330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6ac9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00838330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6b35\",\n        \"direction\": \"out\",\n        \"other\": \"0x00838330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c67c3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00841000\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6a73\",\n        \"direction\": \"out\",\n        \"other\": \"0x00841000\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6a9c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00841000\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c683d\",\n        
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
  "body_end": "007c6b7e",
  "body_span_bytes": 1071,
  "body_start": "007c6750",
  "callees": [
    "FUN_008380b0",
    "Graphics::IRenderer::Get",
    "FUN_0093c5a0",
    "_CxxThrowException",
    "FUN_00f47380",
    "FUN_007c65a0",
    "_wcsicmp",
    "FUN_00841000",
    "FUN_00838330",
    "stream_printf",
    "FUN_007c3c20",
    "isdigit",
    "FUN_00837f30",
    "FUN_00838020",
    "App::cViewer::EndUpdate"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007c6750",
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
      "name": "local_1c",
      "storage": "Stack[-0x1c]:1",
      "type": "undefined"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_3c",
      "storage": "Stack[-0x3c]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "App::cCameraManager::SetActiveCameraByID",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCameraManager *"
    },
    {
      "name": "cameraID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x3c6750",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cCameraManager::SetActiveCameraByID(cCameraManager * this, uint32_t cameraID)",
  "size_bytes": 1071,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007c6750",
  "vtables": {
    "referenced_by_vtables": [
      "0x014104a4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "014104a4"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__SetActiveCameraByID.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCameraManager__SetActiveCameraByID.c",
    "reconstruction/staging/df2-live-listing/camera_active_by_id_007c6750.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/df2-live-listing/007c6750.json"
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
    "no original-process trace exists in this repository; the static reconstruction of 0x007c6750 is unvalidated at runtime",
    "the committed evidence pack's disassembly is a truncated envelope, so no listing-dependent check could be adjudicated from committed evidence"
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
  "vtable:0x014104a4"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8d40",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8d40",
      "0x007d85b0",
      "0x007d8d40",
      "0x01412598",
      "0x007d8c80",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6750"
    ],
    "conflict_id": "app_mode_setter_boundary",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x007c61a0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6eb0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c61a0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c64c0",
      "0x007c6750",
      "0x007c6750",
      "0x007c6750",
      "0x007c6eb0",
      "0x007c6eb0"
    ],
    "conflict_id": "camera_address_conflicts",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
