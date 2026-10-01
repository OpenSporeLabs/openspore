# Evidence 0x007d9410

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b1f792d20c11922aace3a8ba0b2bdf070d7d7df3b93efd01bfdf3aecc1492769`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX holds a pointer to the subobject that carries the OnKeyDown virtual; the entry rewinds it to the cMouseCamera start",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": [
    "none in this body - the entry tail-jumps; the callee at 0x007d9bb0 ends with `POP ESI` / `RET 0x4`",
    "none in this body (tail transfer)"
  ],
  "return_note": "unclassified in this model; the persisted record and the SDK/Ghidra prototype both say bool at the declaration site",
  "return_register": [
    "EAX",
    "EAX per the persisted ABI record; the derived record names none (return.register null, register_class unknown, confidence UNKNOWN)"
  ],
  "return_type": "bool",
  "saved_registers": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "the tail target: the body pushes nothing and pops nothing, and the persisted record describes 0x007d9bb0 as ending in POP ESI / RET 0x4, which is what drops the caller's one word and returns to this body's caller",
  "termination": "JMP 0x007d9bb0 at 0x007d9413"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/abi_infer.py#tail_target=0x007d9bb0`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "receiver": false,
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee"
  },
  "abstained_because": [
    "no_terminal_ret: the only exit observed is a tail jump"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "SUPPORTED",
    "corroboration": "forwarded_from_tail_target",
    "evidence": "forwarded from the tail target 0x007d9bb0: ret 0x4",
    "side": "callee"
  },
  "completeness": "EMPTY",
  "conflicts": [
    {
      "field": "stack_cleanup_bytes",
      "inferred": 4,
      "kind": "inferred_vs_persisted",
      "persisted": 0,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "8c6c422e90a086301d804d50fdb1cd44ca1c7e46a6426471e8d8c1dae31e011a",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "forwarded_from_tail_target"
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "this listing is a tail transfer: it inherits its caller's frame and never runs its own RET",
      "confidence": "UNKNOWN",
      "id": "T1",
      "value": {
        "form": "jmp"
      }
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "calling convention is __thiscall, forwarded from the tail target 0x007d9bb0: this listing is a single ESP-neutral direct jump, inherits its caller's frame and never runs its own RET, so the two calls are one call (resolved from live listing for 0x007d9bb0)",
      "confidence": "INFERRED",
      "id": "T1-FWD",
      "value": "__thiscall"
    }
  ],
  "observations": [
    {
      "at": "0x007d9410",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ECX,0x4",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x007d9413",
      "id": "obs-0002",
      "index": 1,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x007d9bb0",
      "target": "0x007d9bb0"
    }
  ],
  "parse": {
    "declared_count": 2,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "adjustor_delta": -4,
    "bounds_only": true,
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "register": null,
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "UNKNOWN",
    "register": null,
    "register_class": "unknown",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": "jmp",
    "present": true,
    "target": "0x007d9bb0"
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x007d9410"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_UNKNOWN"
}
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

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\n/* WARNING: Unknown calling convention */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nbool App__cMouseCamera__OnKeyDown(cMouseCamera *this,int virtualKey,KeyModifiers modifiers)\n\n{\n  bool bVar1;\n  \n  bVar1 = (bool)FUN_007d9bb0();\n  return bVar1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 2,
  "instructions": [
    {
      "address": "007d9410",
      "instruction": "SUB ECX,0x4"
    },
    {
      "address": "007d9413",
      "instruction": "JMP 0x007d9bb0"
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
  "original_bytes": 10528,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX holds a pointer to the subobject that carries the OnKeyDown virtual; the entry rewinds it to the cMouseCamera start\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": [\n      \"none in this body - the entry tail-jumps; the callee at 0x007d9bb0 ends with `POP ESI` / `RET 0x4`\",\n      \"none in this body (tail transfer)\"\n    ],\n    \"return_note\": \"unclassified in this model; the persisted record and the SDK/Ghidra prototype both say bool at the declaration site\",\n    \"return_register\": [\n      \"EAX\",\n      \"EAX per the persisted ABI record; the derived record names none (return.register null, register_class unknown, confidence UNKNOWN)\"\n    ],\n    \"return_type\": \"bool\",\n    \"saved_registers\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"the tail target: the body pushes nothing and pops nothing, and the persisted record describes 0x007d9bb0 as ending in POP ESI / RET 0x4, which is what drops the caller's one word and returns to this body's caller\",\n    \"termination\": \"JMP 0x007d9bb0 at 0x007d9413\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"pkg-app-imessage-manager-dtor\",\n      \"score\": 9,\n      \"symbol\": \"get_0067dc80\",\n      \"va\": \"0x0067dc80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-cheat-func3ch-0067e6b0\",\n      \"score\": 8,\n      \"symbol\": \"func3_ch_0067e6b0\",\n      \"va\": \"0x0067e6b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-cheat-dispatch-0067e6f0\",\n      \"score\": 8,\n      \"symbol\": \"cCheatManager_func40h_0067e6f0\",\n      \"va\": \"0x0067e6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"cheat-func44h-0067e730\",\n      \"score\": 8,\n      \"symbol\": \"func44h_0067e730\",\n      \"va\": \"0x0067e730\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 8,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-proplist-dispatch-wave14\",\n      \"score\": 8,\n      \"symbol\": \"app_property_list_add_all_properties_from_006a1510\",\n      \"va\": \"0x006a1510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 8,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 8,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x007d9413\",\n        \"direction\": \"out\",\n        \"other\": \"0x007d9bb0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0248\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\",\n    \"global:none: the complete two-instruction listing names no data-segment address\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"App::cMouseCamera::OnKeyDown\",\n  \"normalized_symbol\": \"App::cMouseCamera::OnKeyDown\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__cMouseCamera__OnKeyDown.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/App__cMouseCamera__OnKeyDown.c\",\n      \"reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410.cpp\",\n      \"reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410.hpp\",\n      \"reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410_model_test.cpp\",\n      \"reconstruction/staging/pkg-dfw-007d9410/dfw_007d9410.
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
  "body_end": "007d9417",
  "body_span_bytes": 8,
  "body_start": "007d9410",
  "callees": [
    "FUN_007d9bb0"
  ],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "007d9410",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "bVar1",
      "storage": "register:00000000:1",
      "type": "bool"
    },
    {
      "name": "this",
      "storage": "Stack[0x4]:4",
      "type": "cMouseCamera *"
    },
    {
      "name": "modifiers",
      "storage": "Stack[0xc]:4",
      "type": "KeyModifiers"
    },
    {
      "name": "virtualKey",
      "storage": "Stack[0x8]:4",
      "type": "int"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "App::cMouseCamera::OnKeyDown",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cMouseCamera *"
    },
    {
      "name": "virtualKey",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "modifiers",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "KeyModifiers"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x3d9410",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cMouseCamera::OnKeyDown(cMouseCamera * this, int virtualKey, KeyModifiers modifiers)",
  "size_bytes": 8,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007d9410",
  "vtables": {
    "referenced_by_vtables": [
      "0x01412890"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01412894"
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
  "global:none: the complete two-instruction listing names no data-segment address"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cMouseCamera__OnKeyDown.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cMouseCamera__OnKeyDown.c",
    "reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410.cpp",
    "reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410.hpp",
    "reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410_model_test.cpp",
    "reconstruction/staging/pkg-dfw-007d9410/dfw_007d9410.cpp",
    "reconstruction/staging/pkg-dfw-007d9410/dfw_007d9410_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-mouse-camera-keydown/007d9410.json",
    "reconstruction/metadata/pkg-dfw-007d9410/007d9410.json"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "DATA",
  "bool",
  "unclassified in this model; the persisted record and the SDK/Ghidra prototype both say bool at the declaration site",
  "unclassified_in_EAX (a std::uint32_t alias)"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x007d93a0",
  "vtable:0x01412890",
  "vtable:0x01412894"
]
```

## Conflicts

```json
[]
```
