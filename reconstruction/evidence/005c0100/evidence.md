# Evidence 0x005c0100

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `af95489d02e66f9c73e36605a18070e360edac2f9ebabb71ffd643c3e38fa5f8`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "receiver": {
    "register": "ECX",
    "type": "opaque UI shell",
    "width_bytes": 4
  },
  "return_observation": "AL is one for handled message shapes and zero for unmatched shapes.",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "unused",
      "position": 1,
      "type": "opaque uint32",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "message",
      "position": 2,
      "type": "opaque UI message pointer",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
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
      "entry_ESP+0x8"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -76, so the listing is not one path"
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
  "content_sha256": "b80248d55d45863cf7a521e207dfafcd05e74f576088017da20d7d349019d26c",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 9,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0027",
        "obs-0031",
        "obs-0038",
        "obs-0045",
        "obs-0051",
        "obs-0057",
        "obs-0063",
        "obs-0066"
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
        "obs-0002"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0022"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          24,
          32
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0022",
        "obs-0027",
        "obs-0031",
        "obs-0038",
        "obs-0045",
        "obs-0051",
        "obs-0057",
        "obs-0063",
        "obs-0066"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0027",
        "obs-0031",
        "obs-0038",
        "obs-0045",
        "obs-0051",
        "obs-0057",
        "obs-0063",
        "obs-0066"
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
        "obs-0027",
        "obs-0031",
        "obs-0038",
        "obs-0045",
        "obs-0051",
        "obs-0057",
        "obs-0063",
        "obs-0066"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0027",
        "obs-0031",
        "obs-0038",
        "obs-0045",
        "obs-0051",
        "obs-0057",
        "obs-0063",
        "obs-0066"
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
      "at": "0x005c0100",
      "count": 5,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x005c0100",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x005c0100",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "and_esp": null,
      "at": "0x005c0104",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0004",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x005c0104",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "r
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
    "va": "0x00edb750"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360"
    ],
    "conflict_id": "U-DIALOG-BEHAVIOR",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960050",
      "0x00960050",
      "0x00960250",
      "0x00960250"
    ],
    "conflict_id": "U-SCREEN-STATE-BITS",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
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
  "count": 192,
  "instructions": [
    {
      "address": "005c0100",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "005c0104",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "005c0107",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005c0108",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005c010a",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "005c010d",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "005c0110",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005c0111",
      "instruction": "JZ 0x005c01cc"
    },
    {
      "address": "005c0117",
      "instruction": "SUB ECX,0x17"
    },
    {
      "address": "005c011a",
      "instruction": "JZ 0x005c01a4"
    },
    {
      "address": "005c0120",
      "instruction": "SUB ECX,0x287259de"
    },
    {
      "address": "005c0126",
      "instruction": "JNZ 0x005c0312"
    },
    {
      "address": "005c012c",
      "instruction": "CMP dword ptr [EAX + 0xc],0x2"
    },
    {
      "address": "005c0130",
      "instruction": "JNZ 0x005c0312"
    },
    {
      "address": "005c0136",
      "instruction": "CALL 0x00a206f0"
    },
    {
      "address": "005c013b",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005c013d",
      "instruction": "JZ 0x005c014a"
    },
    {
      "address": "005c013f",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005c0141",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005c0143",
      "instruction": "MOV EAX,dword ptr [EDX + 0x20]"
    },
    {
      "address": "005c0146",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c0148",
      "instruction": "JMP 0x005c014c"
    },
    {
      "address": "005c014a",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "005c014c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005c014d",
      "instruction": "PUSH 0xa03e74b2"
    },
    {
      "address": "005c0152",
      "instruction": "CALL 0x00435ed0"
    },
    {
      "address": "005c0157",
      "instruction": "MOV ECX,dword ptr [ESI + 0x20]"
    },
    {
      "address": "005c015a",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "005c015d",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005c015e",
      "instruction": "LEA EDX,[ESP + 0xc]"
    },
    {
      "address": "005c0162",
      "instruction": "PUSH EDX"
    },
    {
      "address": "005c0163",
      "instruction": "CALL 0x004010a0"
    },
    {
      "address": "005c0168",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005c016a",
      "instruction": "CALL 0x005ecf80"
    },
    {
      "address": "005c016f",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "005c0173",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005c0174",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005c0176",
      "instruction": "CALL 0x005bf950"
    },
    {
      "address": "005c017b",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "005c017f",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "005c0183",
      "instruction": "SUB ECX,EAX"
    },
    {
      "address": "005c0185",
      "instruction": "AND ECX,0xfffffffe"
    },
    {
      "address": "005c0188",
      "instruction": "CMP ECX,0x2"
    },
    {
      "address": "005c018b",
      "instruction": "JLE 0x005c019a"
    },
    {
      "address": "005c018d",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005c018f",
      "instruction": "JZ 0x005c019a"
    },
    {
      "address": "005c0191",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005c0192",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "005c0197",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "005c019a",
      "instruction": "POP EDI"
    },
    {
      "address": "005c019b",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "005c019d",
      "instruction": "POP ESI"
    },
    {
      "address": "005c019e",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "005c01a1",
      "instruction": "RET 0x8"
    },
    {
      "address": "005c01a4",
      "instruction": "CMP dword ptr [EAX + 0xc],0x1"
    },
    {
      "address": "005c01a8",
      "instruction": "JNZ 0x005c0312"
    },
    {
      "address": "005c01ae",
      "instruction": "CMP dword ptr [EAX + 0x14],0x1"
    },
    {
      "address": "005c01b2",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "005c01b4",
      "instruction": "MOV EDX,dword ptr [EDX + 0x1c]"
    },
    {
      "address": "005c01b7",
      "instruction": "SETZ AL"
    },
    {
      "address": "005c01ba",
      "instruction": "MOVZX ECX,AL"
    },
    {
      "address": "005c01bd",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005c01be",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005c01c0",
      "instruction": "CALL EDX"
    },
    {
      "address": "005c01c2",
      "instruction": "POP EDI"
    },
    {
      "address": "005c01c3",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "005c01c5",
      "instruction": "POP ESI"
    },
    {
      "address": "005c01c6",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "005c01c9",
      "instruction": "RET 0x8"
    },
    {
      "address": "005c01cc",
      "instruction": "MOV ECX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "005c01cf",
      "instruction": "CMP ECX,0xd"
    },
    {
      "address": "005c01d2",
      "instruction": "JZ 0x005c02dd"
    },
    {
      "address": "005c01d8",
      "instruction": "CMP ECX,0x1b"
    },
    {
      "address": "005c01db",
      "instruction": "JZ 0x005c02dd"

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
  "original_bytes": 8689,
  "preview": "{\n  \"abi\": {\n    \"receiver\": {\n      \"register\": \"ECX\",\n      \"type\": \"opaque UI shell\",\n      \"width_bytes\": 4\n    },\n    \"return_observation\": \"AL is one for handled message shapes and zero for unmatched shapes.\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"unused\",\n        \"position\": 1,\n        \"type\": \"opaque uint32\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"message\",\n        \"position\": 2,\n        \"type\": \"opaque UI message pointer\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueUiMessage,OpaqueUiObject,OpaqueUiShell\",\n        \"shared_vtable:vtable:0x013f7b70\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 32,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueUiObject,OpaqueUiShell,UNCONDITIONAL_CALL\",\n        \"shared_vtable:vtable:0x013f7b70\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 32,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 6,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 6,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 3,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueUiMessage\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"Editors_EditorUI_HandleMessage_005e0000\",\n      \"va\": \"0x005e0000\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 3,\n      \"symbol\": \"app_system_service_gate_dispatch_007e5f30\",\n      \"va\": \"0x007e5f30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"app_capp_system_hook_windows_007e6080\",\n      \"va\": \"0x007e6080\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueUiShell\",\n  \"cluster\": null,\n  \"confidence\": 0.88,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00edb750\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00edb94c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00edb750\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0163\",\n        \"direction\": \"out\",\n        \"other\": \"0x004010a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0152\",\n        \"direction\": \"out\",\n        \"other\": \"0x00435ed0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0176\",\n        \"direction\": \"out\",\n        \"other\": \"0x005bf950\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c016a\",\n        \"direction\": \"out\",\n        \"other\": \"0x005ecf80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0220\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067caa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0257\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067caa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c028b\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067caa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c02c2\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067caa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c02f4\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067caa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0211\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c024c\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c027c\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c02b7\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"
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
  "body_end": "005c031b",
  "body_span_bytes": 540,
  "body_start": "005c0100",
  "callees": [
    "FUN_00f47380",
    "FUN_00435ed0",
    "FUN_008105b0",
    "FUN_0067caa0",
    "Simulator::cSpaceNames::Get",
    "FUN_005ecf80",
    "FUN_00a206f0",
    "FUN_005bf950"
  ],
  "callers": [
    "FUN_00edb750"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005c0100",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005c0100",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1c0100",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005c0100(void)",
  "size_bytes": 540,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005c0100",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f7b54"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "013f7ba8"
    },
    {
      "from": "00edb94c"
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
  "file": "src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp",
  "files": [
    "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.cpp",
    "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.hpp",
    "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions_model_test.cpp",
    "src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg18-ui-scripting/005c0100.json"
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
    "gate-ui-scripting-message-routes"
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
  "OpaqueUiMessage",
  "OpaqueUiObject",
  "OpaqueUiShell",
  "UNCONDITIONAL_CALL",
  "opaque UI message pointer",
  "opaque UI shell",
  "opaque uint32"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f7b70"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360"
    ],
    "conflict_id": "U-DIALOG-BEHAVIOR",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960050",
      "0x00960050",
      "0x00960250",
      "0x00960250"
    ],
    "conflict_id": "U-SCREEN-STATE-BITS",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
