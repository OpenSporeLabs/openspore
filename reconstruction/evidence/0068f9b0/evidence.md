# Evidence 0x0068f9b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `89ca8e7dc1788db36f54ce50c660a8c451ec4cbbb740bc41ab023a0de425c15c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "convention": "__thiscall with no stack argument",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "evidence": "0x0068f9b2 8B 74 24 0C MOV ESI,DWORD PTR [ESP+0x0C]. ESP arithmetic: on entry [ESP+0x0] holds the return address, so entry_ESP+0x4 is the first stack argument slot; PUSH EBX at 0x0068f9b0 moves ESP to entry_ESP-0x4 and PUSH ESI at 0x0068f9b1 moves it to entry_ESP-0x8, making [ESP+0x0C] == entry_ESP+0x4. The displacement is 0x0C and not 0x10 precisely because the load sits between the second and third pushes (PUSH EDI at 0x0068f9b8 comes after it).",
      "observed": true,
      "ordinal": 1,
      "read": true,
      "read_once": "Loaded exactly once at 0x0068f9b2 into ESI and never re-read from the stack; the captured value is reused by 0x0068f9bc (compare), 0x0068f9c0 (null test), 0x0068f9c8 (dispatch receiver), 0x0068f9cc (stored value). The function never writes to its own argument slot.",
      "type": "opaque 4-byte pointer; no pointee type is established by the bytes",
      "width_bytes": 4,
      "written": false
    }
  ],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_semantics": "Nothing is propagated. No path writes EAX with a result: the only EAX writes are the two object-pointer loads at 0x0068f9c4 and 0x0068f9d3, both consumed by the immediately following slot loads at 0x0068f9c6 and 0x0068f9d5. The identity exit at 0x0068f9be returns with EAX never written by this body at all. EAX is undefined on return on every path.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": 0,
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4 at 0x0068f9df (bytes C2 04 00, the last three bytes of the body)"
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
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "1dc5098fe4a59280b98ae7e97204e7885a56d6de286b3f5312fe94d8901e3b68",
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
    "ghidra_parameter_count": 3,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020"
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
        "obs-0004"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0013"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          8
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0020"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020"
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
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020"
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
      "at": "0x0068f9b0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x0068f9b1",
      "count": 4,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0068f9b2",
      "count": 1,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x0068f9b2",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0068f9b2",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0068f9b6",
      "count": 1,
      "first_use": 3,
      "first_write_index": 12,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EBX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0068f9b6",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,ECX",
      "reg": "EBX",
      "write_kind": "reg"
    },
    {
      "at": "0x0068f9b8",
      "count": 3,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x0068f9b9",
      "definite": true,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [EBX + 0x8]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0068f9c4",
      "definite": true,
      "id"
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
    "va": "0x004103c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004186c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0042ffb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00467a20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00560d60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00560f20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00615870"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00616d60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0061fdb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0061fee0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00633ac0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006411b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0068f1d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006af260"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006b4490"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006b4610"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\n/* WARNING: Unknown calling convention */\n\nvoid App__cJob__Continuation(cJob *this,cJobVoidCallback callback,void *data)\n\n{\n  cJob *pcVar1;\n  int in_ECX;\n  \n  pcVar1 = *(cJob **)(in_ECX + 8);\n  if (this != pcVar1) {\n    if (this != (cJob *)0x0) {\n      (**(code **)this->mCallback)();\n    }\n    *(cJob **)(in_ECX + 8) = this;\n    if (pcVar1 != (cJob *)0x0) {\n      (**(code **)(pcVar1->mCallback + 4))();\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 25,
  "instructions": [
    {
      "address": "0068f9b0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0068f9b1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0068f9b2",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0068f9b6",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "0068f9b8",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0068f9b9",
      "instruction": "MOV EDI,dword ptr [EBX + 0x8]"
    },
    {
      "address": "0068f9bc",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "0068f9be",
      "instruction": "JZ 0x0068f9dc"
    },
    {
      "address": "0068f9c0",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "0068f9c2",
      "instruction": "JZ 0x0068f9cc"
    },
    {
      "address": "0068f9c4",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "0068f9c6",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0068f9c8",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0068f9ca",
      "instruction": "CALL EDX"
    },
    {
      "address": "0068f9cc",
      "instruction": "MOV dword ptr [EBX + 0x8],ESI"
    },
    {
      "address": "0068f9cf",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "0068f9d1",
      "instruction": "JZ 0x0068f9dc"
    },
    {
      "address": "0068f9d3",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "0068f9d5",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0068f9d8",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0068f9da",
      "instruction": "CALL EDX"
    },
    {
      "address": "0068f9dc",
      "instruction": "POP EDI"
    },
    {
      "address": "0068f9dd",
      "instruction": "POP ESI"
    },
    {
      "address": "0068f9de",
      "instruction": "POP EBX"
    },
    {
      "address": "0068f9df",
      "instruction": "RET 0x4"
    }
  ]
}
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
  "original_bytes": 18608,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"convention\": \"__thiscall with no stack argument\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"evidence\": \"0x0068f9b2 8B 74 24 0C MOV ESI,DWORD PTR [ESP+0x0C]. ESP arithmetic: on entry [ESP+0x0] holds the return address, so entry_ESP+0x4 is the first stack argument slot; PUSH EBX at 0x0068f9b0 moves ESP to entry_ESP-0x4 and PUSH ESI at 0x0068f9b1 moves it to entry_ESP-0x8, making [ESP+0x0C] == entry_ESP+0x4. The displacement is 0x0C and not 0x10 precisely because the load sits between the second and third pushes (PUSH EDI at 0x0068f9b8 comes after it).\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": true,\n        \"read_once\": \"Loaded exactly once at 0x0068f9b2 into ESI and never re-read from the stack; the captured value is reused by 0x0068f9bc (compare), 0x0068f9c0 (null test), 0x0068f9c8 (dispatch receiver), 0x0068f9cc (stored value). The function never writes to its own argument slot.\",\n        \"type\": \"opaque 4-byte pointer; no pointee type is established by the bytes\",\n        \"width_bytes\": 4,\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"Nothing is propagated. No path writes EAX with a result: the only EAX writes are the two object-pointer loads at 0x0068f9c4 and 0x0068f9d3, both consumed by the immediately following slot loads at 0x0068f9c6 and 0x0068f9d5. The identity exit at 0x0068f9be returns with EAX never written by this body at all. EAX is undefined on return on every path.\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": 0,\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4 at 0x0068f9df (bytes C2 04 00, the last three bytes of the body)\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x014018b0\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-cheat-func3ch-0067e6b0\",\n      \"score\": 12,\n      \"symbol\": \"func3_ch_0067e6b0\",\n      \"va\": \"0x0067e6b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-cheat-dispatch-0067e6f0\",\n      \"score\": 8,\n      \"symbol\": \"cCheatManager_func40h_0067e6f0\",\n      \"va\": \"0x0067e6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"cheat-func44h-0067e730\",\n      \"score\": 8,\n      \"symbol\": \"func44h_0067e730\",\n      \"va\": \"0x0067e730\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 8,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-proplist-dispatch-wave14\",\n      \"score\": 8,\n      \"symbol\": \"app_property_list_add_all_properties_from_006a1510\",\n      \"va\": \"0x006a1510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 8,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 8,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-copyfrom-wave14\",\n      \"score\": 8,\n      \"symbol\": \"App_DirectPropertyList_CopyFrom_006a2ad0\",\n      \"va\": \"0x006a2ad0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004103c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004186c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0042ffb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00467a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00560d60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00560f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00615870\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00616d60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0061fdb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0061f
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
  "body_end": "0068f9e1",
  "body_span_bytes": 50,
  "body_start": "0068f9b0",
  "callees": [],
  "callers": [
    "FUN_0061fdb0",
    "FUN_00616d60",
    "FUN_007564b0",
    "FUN_006411b0",
    "FUN_00769f20",
    "FUN_006b4610",
    "FUN_006b4a10",
    "FUN_0068f1d0",
    "FUN_00faacd0",
    "FUN_00756650",
    "FUN_00729300",
    "FUN_0076ce50",
    "FUN_0061fee0",
    "FUN_007677c0",
    "FUN_00560f20",
    "FUN_007b13b0",
    "FUN_00615870",
    "FUN_004103c0",
    "FUN_007652c0",
    "FUN_006b4490",
    "FUN_0042ffb0",
    "FUN_00765b30",
    "FUN_0076a400",
    "FUN_007573a0",
    "FUN_00633ac0",
    "FUN_0076a4d0",
    "FUN_007b0430",
    "FUN_004186c0",
    "FUN_006af260",
    "FUN_0076a720",
    "FUN_00467a20",
    "FUN_00560d60",
    "FUN_007b10d0",
    "FUN_00767590",
    "FUN_00765d30"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0068f9b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "this",
      "storage": "Stack[0x4]:4",
      "type": "cJob *"
    },
    {
      "name": "data",
      "storage": "Stack[0xc]:4",
      "type": "void *"
    },
    {
      "name": "callback",
      "storage": "Stack[0x8]:4",
      "type": "cJobVoidCallback"
    },
    {
      "name": "pcVar1",
      "storage": "unique:00017200:4",
      "type": "cJob *"
    },
    {
      "name": "in_ECX",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "App::cJob::Continuation",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cJob *"
    },
    {
      "name": "callback",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "cJobVoidCallback"
    },
    {
      "name": "data",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "void *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x28f9b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::cJob::Continuation(cJob * this, cJobVoidCallback callback, void * data)",
  "size_bytes": 50,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0068f9b0",
  "vtables": {
    "referenced_by_vtables": [
      "0x0143dcc4",
      "0x014018b0",
      "0x0143ddf4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 57,
  "xrefs": [
    {
      "from": "0061fe56"
    },
    {
      "from": "007b061e"
    },
    {
      "from": "007b166a"
    },
    {
      "from": "00418823"
    },
    {
      "from": "004106a5"
    },
    {
      "from": "00410959"
    },
    {
      "from": "0043015d"
    },
    {
      "from": "007293ba"
    },
    {
      "from": "0075781d"
    },
    {
      "from": "0075784e"
    },
    {
      "from": "00757896"
    },
    {
      "from": "00757920"
    },
    {
      "from": "007579dd"
    },
    {
      "from": "00757a63"
    },
    {
      "from": "00757b0c"
    },
    {
      "from": "00757b90"
    },
    {
      "from": "00467e6d"
    },
    {
      "from": "0056101f"
    },
    {
      "from": "00560ed3"
    },
    {
      "from": "0061ff90"
    },
    {
      "from": "0061589a"
    },
    {
      "from": "00616df8"
    },
    {
      "from": "00633c37"
    },
    {
      "from": "00641119"
    },
    {
      "from": "0068f255"
    },
    {
      "from": "006af455"
    },
    {
      "from": "006b45f0"
    },
    {
      "from": "006b4b11"
    },
    {
      "from": "00756551"
    },
    {
      "from": "00756707"
    },
    {
      "from": "007676ac"
    },
    {
      "from": "0076a0fe"
    },
    {
      "from": "0076a129"
    },
    {
      "from": "0076a175"
    },
    {
      "from": "0076a1ae"
    },
    {
      "from": "0076a4a1"
    },
    {
      "from": "0076a62a"
    },
    {
      "from": "0076a663"
    },
    {
      "from": "0076a8e2"
    },
    {
      "from": "0076545c"
    },
    {
      "from": "00765487"
    },
    {
      "from": "00765ca0"
    },
    {
      "from": "00765ccb"
    },
    {
      "from": "00765eb7"
    },
    {
      "from": "0076795d"
    },
    {
      "from": "00767988"
    },
    {
      "from": "0076d471"
    },
    {
      "from": "00faad46"
    },
    {
      "from": "007b12ec"
    },
    {
      "from": "014018e4"
    },
    {
      "from": "0143dcfc"
    },
    {
      "from": "0143ddf4"
    },
    {
      "from": "0143de30"
    },
    {
      "from": "006b4e58"
    },
    {
      "from": "006b4e88"
    },
    {
      "from": "006b4ecc"
    },
    {
      "from": "006b46f9"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cJob__Continuation.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cJob__Continuation.c",
    "reconstruction/staging/pkg-job-continuation-0068f9b0/job_continuation_0068f9b0.cpp",
    "reconstruction/staging/pkg-job-continuation-0068f9b0/job_continuation_0068f9b0.hpp",
    "reconstruction/staging/pkg-job-continuation-0068f9b0/job_continuation_0068f9b0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-job-continuation-0068f9b0/0068f9b0.json"
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
    "A live receiver whose +0x8 field differs from the incoming pointer is required for any dispatch to be observed; when they are equal (0x0068f9be) the body is a total no-op.",
    "Both dispatched objects must carry a table with at least two dword slots before slot 0 can be entered; the machine test dereferences [obj] and then [table+0] and [table+0x4] unconditionally on the non-null path.",
    "The two slot targets must be real thiscall functions taking only an ECX pointer; a differential run needs the concrete receiver type and the concrete slot implementations identified first, which the bytes do not establish."
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
  "opaque 4-byte pointer; no pointee type is established by the bytes",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014018b0",
  "vtable:0x0143dcc4",
  "vtable:0x0143ddf4"
]
```

## Conflicts

```json
[]
```
