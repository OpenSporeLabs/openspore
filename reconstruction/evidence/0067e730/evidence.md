# Evidence 0x0067e730

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `cbbf502298789e89dce51bbadf02210388735877617df66d2a892cb9a7b31b75`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "convention": "__thiscall with two callee-cleaned stack words",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x4"
  ],
  "ordinary_stack_arguments": [
    "{'entry_offset': 'entry_ESP+0x4', 'note': '0x0067e73d MOV EBX,dword ptr [ESP + 0x10] addresses entry_ESP+0x4 because PUSH ESI (0x0067e730), PUSH EDI (0x0067e734) and PUSH EBX (0x0067e73c) have moved ESP from entry_ESP to entry_ESP-0xC. It is read exactly once, before the loop head at 0x0067e741, and the back edge at 0x0067e75b targets the head, so the word is hoisted out of the loop.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}",
    "{'entry_offset': 'entry_ESP+0x4', 'note': 'Read once, hoisted out of the loop. After PUSH ESI/EDI/EBX the frame is entry_ESP-0xC, so 0x0067e73d MOV EBX,[ESP+0x10] addresses entry_ESP+0x4.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}"
  ],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_semantics": [
    "EAX carries no defined value on any exit path; the only writes to EAX are the vtable load at 0x0067e744 and the 0x00921580 result consumed into ESI at 0x0067e754. The function is a procedure, not a value producer.",
    "EAX carries no defined value on any exit path; the only writes to EAX are the vtable load and the 0x00921580 result, and both are consumed by the loop. The function is a procedure, not a value producer."
  ],
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_arguments": 2,
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": [
    "RET 0x4 at 0x0067e760",
    "RET 0x4"
  ]
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
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
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
  "content_sha256": "e4577ef22e2f8763d63df621e6776ad587b2572401ef2008d86aa14fddce1025",
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
    "ghidra_parameter_count": 2,
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
        "obs-0007"
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
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          80,
          96
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0010",
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
      "at": "0x0067e730",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0067e731",
      "count": 3,
      "first_use": 1,
      "first_write_index": 8,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ECX + 0x50]",
      "reg": "ECX"
    },
    {
      "at": "0x0067e731",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ECX + 0x50]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0067e734",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x0067e73c",
      "count": 2,
      "first_use": 6,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x0067e73d",
      "count": 1,
      "first_use": 7,
      "first_write_index": 17,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x0067e73d",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0007",
      "index": 7,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0067e73d",
      "definite": true,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESP + 0x10]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0067e741",
      "definite": true,
      "id": "obs-0009",
      "index": 8,

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
  "count": 24,
  "instructions": [
    {
      "address": "0067e730",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0067e731",
      "instruction": "MOV ESI,dword ptr [ECX + 0x50]"
    },
    {
      "address": "0067e734",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0067e735",
      "instruction": "LEA EDI,[ECX + 0x4c]"
    },
    {
      "address": "0067e738",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "0067e73a",
      "instruction": "JZ 0x0067e75e"
    },
    {
      "address": "0067e73c",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0067e73d",
      "instruction": "MOV EBX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "0067e741",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "0067e744",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0067e746",
      "instruction": "MOV EDX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "0067e749",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0067e74a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0067e74c",
      "instruction": "CALL EDX"
    },
    {
      "address": "0067e74e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0067e74f",
      "instruction": "CALL 0x00921580"
    },
    {
      "address": "0067e754",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "0067e756",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0067e759",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "0067e75b",
      "instruction": "JNZ 0x0067e741"
    },
    {
      "address": "0067e75d",
      "instruction": "POP EBX"
    },
    {
      "address": "0067e75e",
      "instruction": "POP EDI"
    },
    {
      "address": "0067e75f",
      "instruction": "POP ESI"
    },
    {
      "address": "0067e760",
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
  "original_bytes": 12512,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"convention\": \"__thiscall with two callee-cleaned stack words\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      \"{'entry_offset': 'entry_ESP+0x4', 'note': '0x0067e73d MOV EBX,dword ptr [ESP + 0x10] addresses entry_ESP+0x4 because PUSH ESI (0x0067e730), PUSH EDI (0x0067e734) and PUSH EBX (0x0067e73c) have moved ESP from entry_ESP to entry_ESP-0xC. It is read exactly once, before the loop head at 0x0067e741, and the back edge at 0x0067e75b targets the head, so the word is hoisted out of the loop.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}\",\n      \"{'entry_offset': 'entry_ESP+0x4', 'note': 'Read once, hoisted out of the loop. After PUSH ESI/EDI/EBX the frame is entry_ESP-0xC, so 0x0067e73d MOV EBX,[ESP+0x10] addresses entry_ESP+0x4.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}\"\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": [\n      \"EAX carries no defined value on any exit path; the only writes to EAX are the vtable load at 0x0067e744 and the 0x00921580 result consumed into ESI at 0x0067e754. The function is a procedure, not a value producer.\",\n      \"EAX carries no defined value on any exit path; the only writes to EAX are the vtable load and the 0x00921580 result, and both are consumed by the loop. The function is a procedure, not a value producer.\"\n    ],\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": 2,\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": [\n      \"RET 0x4 at 0x0067e760\",\n      \"RET 0x4\"\n    ]\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 8,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 8,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 8,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 8,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 8,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0067e74f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00921580\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0190\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:g_cheat_func44h_ports\",\n    \"global:g_dispatch_ports\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"App::cCheatManager::func44h\",\n  \"normalized_symbol\": \"App::cCheatManager::func44h\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"A live cCheatManager with a populated observer chain is required to observe the dispatch a
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
  "body_end": "0067e762",
  "body_span_bytes": 51,
  "body_start": "0067e730",
  "callees": [
    "FUN_00921580"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0067e730",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cCheatManager::func44h",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCheatManager *"
    },
    {
      "name": "param_2",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x27e730",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::cCheatManager::func44h(cCheatManager * this, int param_2)",
  "size_bytes": 51,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0067e730",
  "vtables": {
    "referenced_by_vtables": [
      "0x01401b74"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01401bb8"
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
  "global:g_cheat_func44h_ports",
  "global:g_dispatch_ports"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func44h.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func44h.c",
    "reconstruction/staging/cheat-func44h-0067e730/cheat_dispatch_func44h_0067e730.cpp",
    "reconstruction/staging/cheat-func44h-0067e730/cheat_dispatch_func44h_0067e730.hpp",
    "reconstruction/staging/cheat-func44h-0067e730/cheat_dispatch_func44h_0067e730_model_test.cpp",
    "reconstruction/staging/dogfood-after-02-0067e730/cheat_dispatch_0067e730.cpp",
    "reconstruction/staging/dogfood-after-02-0067e730/cheat_dispatch_0067e730.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/cheat-func44h-0067e730/0067e730.json",
    "reconstruction/metadata/dogfood-after-02-0067e730/0067e730.json"
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
    "A live cCheatManager with a populated observer chain is required to observe the dispatch at all; the chain head at +0x50 must differ from the embedded terminator at +0x4c, or the body exits at 0x0067e73a without making any call.",
    "A live cCheatManager with a populated observer chain is required to observe the dispatch at all; the chain head at +0x50 must differ from the embedded terminator at +0x4c.",
    "The concrete receiver type must be identified before the +0x1c entry can be attributed a meaning, and before a stub with the right stack discipline can be confirmed.",
    "The concrete receiver type must be identified before the +0x1c entry can be attributed a meaning.",
    "The function is reachable only through vtable 0x01401b74 slot 17, so a differential run must construct that exact table and dispatch the slot."
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
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01401b74"
]
```

## Conflicts

```json
[]
```
