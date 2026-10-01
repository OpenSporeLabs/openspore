# Evidence 0x00980480

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ee7894d03ba772093098709cade4c4c954cb4ec4b28a2663e3d728157cf5d52f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "__thiscall",
    "x86-32 thiscall with the receiver in ECX and one 4-byte stack word, popped by the tail callee"
  ],
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "none in this body; the callee of the tail transfer ends in RET 0x4 at 0x0098034b and 0x00980350",
  "return_register": "EAX",
  "return_semantics": "delegated result in EAX, forwarded verbatim from 0x00980330",
  "return_type": "Opaque*",
  "saved_registers": [],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": [
    "tail transfer (JMP) to 0x00980330",
    "the body does not return; control leaves through the tail transfer at 0x00980483"
  ]
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/abi_infer.py#tail_target=0x00980330`

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
    "confidence": "OBSERVED",
    "corroboration": "forwarded_from_tail_target",
    "evidence": "forwarded from the tail target 0x00980330: ret 0x4",
    "side": "callee"
  },
  "completeness": "EMPTY",
  "conflicts": [],
  "content_sha256": "5adcc0ff6c4068014d586ecbb7515ab1ed9f89f68f5167df335f8ea400284827",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "forwarded_from_tail_target"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "['__thiscall', 'x86-32 thiscall with the receiver in ECX and one 4-byte stack word, popped by the tail callee']"
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
      "claim": "calling convention is __thiscall, forwarded from the tail target 0x00980330: this listing is a single ESP-neutral direct jump, inherits its caller's frame and never runs its own RET, so the two calls are one call (resolved from live listing for 0x00980330)",
      "confidence": "INFERRED",
      "id": "T1-FWD",
      "value": "__thiscall"
    }
  ],
  "observations": [
    {
      "at": "0x00980480",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ECX,0x4",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x00980483",
      "id": "obs-0002",
      "index": 1,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x00980330",
      "target": "0x00980330"
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
    "target": "0x00980330"
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00980480"
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
"\n/* WARNING: Unknown calling convention */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n\nbool UTFWin__PerspectiveEffect__HandleUIMessage\n               (PerspectiveEffect *this,IWindow *pWindow,Message *message)\n\n{\n  bool bVar1;\n  \n  bVar1 = (bool)FUN_00980330();\n  return bVar1;\n}\n\n"
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
      "address": "00980480",
      "instruction": "SUB ECX,0x4"
    },
    {
      "address": "00980483",
      "instruction": "JMP 0x00980330"
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
  "original_bytes": 10475,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": [\n      \"__thiscall\",\n      \"x86-32 thiscall with the receiver in ECX and one 4-byte stack word, popped by the tail callee\"\n    ],\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"none in this body; the callee of the tail transfer ends in RET 0x4 at 0x0098034b and 0x00980350\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"delegated result in EAX, forwarded verbatim from 0x00980330\",\n    \"return_type\": \"Opaque*\",\n    \"saved_registers\": [],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": [\n      \"tail transfer (JMP) to 0x00980330\",\n      \"the body does not return; control leaves through the tail transfer at 0x00980483\"\n    ]\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-0095fa30-utfwin-isancestorof\",\n      \"score\": 6,\n      \"symbol\": \"is_ancestor_of_0095fa30\",\n      \"va\": \"0x0095fa30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-utfwin-func35-wave12\",\n      \"score\": 6,\n      \"symbol\": \"func35_0095fd60\",\n      \"va\": \"0x0095fd60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-dfw-0096ff70\",\n      \"score\": 6,\n      \"symbol\": \"dfw_func88h_0096ff70\",\n      \"va\": \"0x0096ff70\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-dfw-00980510\",\n      \"score\": 6,\n      \"symbol\": \"dfw_get_proxy_id_00980510\",\n      \"va\": \"0x00980510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-dfw-00980c50\",\n      \"score\": 6,\n      \"symbol\": \"dfw_00980c50_func88h\",\n      \"va\": \"0x00980c50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-utfwin-slot7-wave12\",\n      \"score\": 6,\n      \"symbol\": \"re_00fc7e10_UTFWin_ImageDrawable_GetTiling\",\n      \"va\": \"0x00fc7e10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-utfwin-settiling-wave13\",\n      \"score\": 6,\n      \"symbol\": \"set_tiling_00fd9460\",\n      \"va\": \"0x00fd9460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01443f2c\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"utfwin_00980470\",\n      \"va\": \"0x00980470\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00980483\",\n        \"direction\": \"out\",\n        \"other\": \"0x00980330\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0323\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\",\n    \"global:PASS (expected)\",\n    \"global:PASS / complete\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"UTFWin::PerspectiveEffect::HandleUIMessage\",\n  \"normalized_symbol\": \"UTFWin::PerspectiveEffect::HandleUIMessage\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__HandleUIMessage.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__HandleUIMessage.c\",\n      \"reconstruction/staging/pkg-dfw-00980480/dfw_00980480.cpp\",\n      \"reconstruction/staging/pkg-dfw-00980480/dfw_00980480_types.hpp\",\n      \"reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12.cpp\",\n      \"reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12.hpp\",\n      \"reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-dfw-00980480/00980480.json\",\n      \"reconstruction/metadata/pkg-utfwin-perspective-wave12/00980480.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"UTFWin\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"utfwin-framework\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__HandleUIMessage.c\",\n    \"dependencies\": [\n      \"app-lifecycle\",\n      \"resource-io\"\n    ],\n    
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
  "body_end": "00980487",
  "body_span_bytes": 8,
  "body_start": "00980480",
  "callees": [
    "FUN_00980330"
  ],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00980480",
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
      "name": "pWindow",
      "storage": "Stack[0x8]:4",
      "type": "IWindow *"
    },
    {
      "name": "this",
      "storage": "Stack[0x4]:4",
      "type": "PerspectiveEffect *"
    },
    {
      "name": "message",
      "storage": "Stack[0xc]:4",
      "type": "Message *"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "UTFWin::PerspectiveEffect::HandleUIMessage",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "PerspectiveEffect *"
    },
    {
      "name": "pWindow",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "IWindow *"
    },
    {
      "name": "message",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Message *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x580480",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool UTFWin::PerspectiveEffect::HandleUIMessage(PerspectiveEffect * this, IWindow * pWindow, Message * message)",
  "size_bytes": 8,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00980480",
  "vtables": {
    "referenced_by_vtables": [
      "0x01443f2c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01443f68"
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
  "global:PASS (expected)",
  "global:PASS / complete"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__HandleUIMessage.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__PerspectiveEffect__HandleUIMessage.c",
    "reconstruction/staging/pkg-dfw-00980480/dfw_00980480.cpp",
    "reconstruction/staging/pkg-dfw-00980480/dfw_00980480_types.hpp",
    "reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12.cpp",
    "reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12.hpp",
    "reconstruction/staging/pkg-utfwin-perspective-wave12/utfwin_perspective_wave12_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-00980480/00980480.json",
    "reconstruction/metadata/pkg-utfwin-perspective-wave12/00980480.json"
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
  "ILayoutElement__vftable*",
  "IPerspectiveEffect__vftable*",
  "Opaque*",
  "PerspectiveEffect__vftable*",
  "float",
  "int",
  "openspore::reconstruction::pkg_utfwin_perspective_wave12::MessageSlot",
  "openspore::reconstruction::pkg_utfwin_perspective_wave12::Opaque"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01443f2c"
]
```

## Conflicts

```json
[]
```
