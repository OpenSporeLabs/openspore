# Evidence 0x0067e6b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d591fe6114dac04f7213080110838fdb675bdafdfd3343d4fedecb00e45c73b8`

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
  "ordinary_stack_arguments": [
    "{'entry_offset': 'entry_ESP+0x4', 'note': '0x0067e6b8 TEST byte ptr [ESP + 0x8],0x1 addresses entry_ESP+0x4 because PUSH ESI at 0x0067e6b0 is the only outstanding frame change and 0x0067e2b0 pushes nothing and ends in a plain RET at 0x0067e301. The test is on the low BYTE, so only bit 0 of the word is given meaning.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}",
    "{'entry_offset': 'entry_ESP+0x4', 'note': '0x0067e6b8 TEST byte ptr [ESP + 0x8],0x1 addresses entry_ESP+0x4. The only outstanding frame change at that point is the PUSH ESI at 0x0067e6b0, because 0x0067e2b0 is stack-neutral across its own call: it pushes five words at 0x0067e2b0..0x0067e2c6 and drops exactly those five (POP ESI at 0x0067e2f6, ADD ESP,0x10 at 0x0067e2fe) before a bare RET at 0x0067e301. The test is on the low BYTE, so only bit 0 of the word is given meaning; the other 31 are read by the load and not consulted.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}"
  ],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_note": "pointer to the receiver",
  "return_register": "EAX",
  "return_semantics": [
    "0x0067e6c8 MOV EAX,ESI puts the receiver in EAX on the single exit path, taken by both the gated and the ungated path. This CONTRADICTS the persisted SDK/Ghidra signature, which declares 'void App::cCheatManager::func3Ch(cCheatManager * this, int param_2)' and prints the decompiler warning 'Unknown calling convention'. The reconstruction follows the listing and returns the receiver. Whether any consumer reads EAX is unproven: the only inbound reference to the function is its vtable slot, and no call site of that slot is known, so 'returns the receiver' is a statement about the machine, not ...",
    "0x0067e6c8 MOV EAX,ESI is the only write to the return register and it is on the single exit, which both the taken and the untaken branch reach, so EAX holds the receiver on both paths. This CONTRADICTS the persisted SDK/Ghidra prototype, which declares 'void App::cCheatManager::func3Ch(cCheatManager * this, int param_2)'. The reconstruction follows the listing. Whether any consumer reads that word is NOT established: the only inbound reference to this address is the data word of vtable 0x014018b0 at slot 20 (0x01401900), and no call site of that slot is known."
  ],
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4 at 0x0067e6cb"
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
          1
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
          1
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
  "content_sha256": "62793a6040a5c8755be7795b7f95cd3fde85ed4d9d11b6bfcb7d75f0093b475d",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011"
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
        "obs-0006"
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
        "obs-0002"
      ],
      "claim": "ECX carries the receiver: 0x0067e6b0 is slot 20 of the vptr-backed vftable at 0x014018b0, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 20,
        "table": "0x014018b0"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0011"
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
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011"
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
      "at": "0x0067e6b0",
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
      "at": "0x0067e6b1",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0067e6b1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x0067e6b3",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0067e2b0",
      "target": "0x0067e2b0"
    },
    {
      "at": "0x0067e6b8",
      "count": 1,
      "first_use": 3,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "TEST byte ptr [ESP + 0x8],0x1",
      "reg": "ESP"
    },
    {
      "at": "0x0067e6b8",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "TEST byte ptr [ESP + 0x8],0x1",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x0067e6c0",
      "id": "obs-0007",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL
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
  "count": 11,
  "instructions": [
    {
      "address": "0067e6b0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0067e6b1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0067e6b3",
      "instruction": "CALL 0x0067e2b0"
    },
    {
      "address": "0067e6b8",
      "instruction": "TEST byte ptr [ESP + 0x8],0x1"
    },
    {
      "address": "0067e6bd",
      "instruction": "JZ 0x0067e6c8"
    },
    {
      "address": "0067e6bf",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0067e6c0",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "0067e6c5",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0067e6c8",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "0067e6ca",
      "instruction": "POP ESI"
    },
    {
      "address": "0067e6cb",
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
  "original_bytes": 14901,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      \"{'entry_offset': 'entry_ESP+0x4', 'note': '0x0067e6b8 TEST byte ptr [ESP + 0x8],0x1 addresses entry_ESP+0x4 because PUSH ESI at 0x0067e6b0 is the only outstanding frame change and 0x0067e2b0 pushes nothing and ends in a plain RET at 0x0067e301. The test is on the low BYTE, so only bit 0 of the word is given meaning.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}\",\n      \"{'entry_offset': 'entry_ESP+0x4', 'note': '0x0067e6b8 TEST byte ptr [ESP + 0x8],0x1 addresses entry_ESP+0x4. The only outstanding frame change at that point is the PUSH ESI at 0x0067e6b0, because 0x0067e2b0 is stack-neutral across its own call: it pushes five words at 0x0067e2b0..0x0067e2c6 and drops exactly those five (POP ESI at 0x0067e2f6, ADD ESP,0x10 at 0x0067e2fe) before a bare RET at 0x0067e301. The test is on the low BYTE, so only bit 0 of the word is given meaning; the other 31 are read by the load and not consulted.', 'observed': True, 'ordinal': 1, 'read': True, 'width_bytes': 4, 'written': False}\"\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"pointer to the receiver\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": [\n      \"0x0067e6c8 MOV EAX,ESI puts the receiver in EAX on the single exit path, taken by both the gated and the ungated path. This CONTRADICTS the persisted SDK/Ghidra signature, which declares 'void App::cCheatManager::func3Ch(cCheatManager * this, int param_2)' and prints the decompiler warning 'Unknown calling convention'. The reconstruction follows the listing and returns the receiver. Whether any consumer reads EAX is unproven: the only inbound reference to the function is its vtable slot, and no call site of that slot is known, so 'returns the receiver' is a statement about the machine, not ...\",\n      \"0x0067e6c8 MOV EAX,ESI is the only write to the return register and it is on the single exit, which both the taken and the untaken branch reach, so EAX holds the receiver on both paths. This CONTRADICTS the persisted SDK/Ghidra prototype, which declares 'void App::cCheatManager::func3Ch(cCheatManager * this, int param_2)'. The reconstruction follows the listing. Whether any consumer reads that word is NOT established: the only inbound reference to this address is the data word of vtable 0x014018b0 at slot 20 (0x01401900), and no call site of that slot is known.\"\n    ],\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4 at 0x0067e6cb\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-cheat-dispatch-0067e6f0\",\n      \"score\": 8,\n      \"symbol\": \"cCheatManager_func40h_0067e6f0\",\n      \"va\": \"0x0067e6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"cheat-func44h-0067e730\",\n      \"score\": 8,\n      \"symbol\": \"func44h_0067e730\",\n      \"va\": \"0x0067e730\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 8,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-proplist-dispatch-wave14\",\n      \"score\": 8,\n      \"symbol\": \"app_property_list_add_all_properties_from_006a1510\",\n      \"va\": \"0x006a1510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 8,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 8,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-copyfrom-wave14\",\n      \"score\": 8,\n      \"symbol\": \"App_DirectPropertyList_CopyFrom_006a2ad0\",\n      \"va\": \"0x006a2ad0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 8,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0067e6b3\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067e2b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0067e6c0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-
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
  "body_end": "0067e6cd",
  "body_span_bytes": 30,
  "body_start": "0067e6b0",
  "callees": [
    "FUN_0067e2b0",
    "FUN_00f47380"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0067e6b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cCheatManager::func3Ch",
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
  "rva": "0x27e6b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::cCheatManager::func3Ch(cCheatManager * this, int param_2)",
  "size_bytes": 30,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0067e6b0",
  "vtables": {
    "referenced_by_vtables": [
      "0x014018b0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01401900"
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
  "global:PASS",
  "global:g_cheat_func3ch_ports"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func3Ch.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func3Ch.c",
    "reconstruction/staging/pkg-cheat-func3ch-0067e6b0/cheat_func3ch_0067e6b0.cpp",
    "reconstruction/staging/pkg-cheat-func3ch-0067e6b0/cheat_func3ch_0067e6b0.hpp",
    "reconstruction/staging/pkg-cheat-func3ch-0067e6b0/cheat_func3ch_0067e6b0_model_test.cpp",
    "reconstruction/staging/pkg-dfw-0067e6b0/dfw_0067e6b0.cpp",
    "reconstruction/staging/pkg-dfw-0067e6b0/dfw_0067e6b0_model_test.cpp",
    "reconstruction/staging/pkg-dfw-0067e6b0/dfw_0067e6b0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-cheat-func3ch-0067e6b0/0067e6b0.json",
    "reconstruction/metadata/pkg-dfw-0067e6b0/0067e6b0.json"
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
    "The branch is inert unless the gate word has bit 0 set; a differential run that passes an even word will exercise only the teardown path.",
    "The function is only reachable through vtable slot 20, so observing it at all requires a live cCheatManager constructed by 0x0067e100 (which stores 0x014018b0) and a caller that dispatches that slot.",
    "The teardown path requires receiver+0x14 to be non-null before the indirect call at 0x0067e2e1 can happen at all."
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
  "CheatManager* (the receiver), following 0x0067e6c8 MOV EAX,ESI rather than the SDK void",
  "pointer to the receiver",
  "pointer_to_the_receiver, an alias of void*. The alias is named from the persisted ABI record's own abi.return_type string, \"pointer to the receiver\", and no more"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014018b0"
]
```

## Conflicts

```json
[]
```
