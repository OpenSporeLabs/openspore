# Evidence 0x00b3d350

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a4de232a1cafcde63adfef3e4aa2447c512bff9ea71ad9e73063ad4e67058170`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl",
  "hidden_receiver": "none",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "plain RET",
  "return_register": "EAX",
  "stack_cleanup_bytes": 0
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
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "df632eb575d9a23f64dd72c323595ff5c033b83d6752e7deed0de4082622fd88",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "cdecl"
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
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
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
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00b3d350",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eaf8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d355",
      "form": "RET",
      "id": "obs-0002",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
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
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "pointer_like",
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
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00b3d350"
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac1970"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac1b30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac1dc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac2200"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac2520"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac2a20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac2b40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac2d00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac2e20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac3110"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac3540"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac38d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac5590"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac5c00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac65d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac68e0"
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
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8360",
      "0x007d8360",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30",
      "0x007d8c30",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d8d40"
    ],
    "conflict_id": "Q-INPUT-ROUTING",
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
      "0x00b3d350",
      "0x00b3d400",
      "0x00b3d350",
      "0x00b3d350",
      "0x01485550"
    ],
    "conflict_id": "TB-VT-008",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "separate_entities",
      "preferred_claim": null,
      "preserved_alternatives": true,
      "scope_note": "The interface and object layout are supported; the concrete vtable address is unresolved.",
      "status": "unresolved",
      "taxonomy": "unresolved"
    },
    "resolution_status": "unresolved",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "Simulator::cGameInputManager 27-slot interface and missing concrete vtable base",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  },
  {
    "anchors": [
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360",
      "0x007d8470",
      "0x007d8470",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30"
    ],
    "conflict_id": "U-GAME-INPUT-ROUTER",
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
      "0x005737d0",
      "0x00588570",
      "0x0058ac10",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587a20"
    ],
    "conflict_id": "editor_input_routing",
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
  "count": 2,
  "instructions": [
    {
      "address": "00b3d350",
      "instruction": "MOV EAX,[0x0167eaf8]"
    },
    {
      "address": "00b3d355",
      "instruction": "RET"
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
  "original_bytes": 14590,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl\",\n    \"hidden_receiver\": \"none\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"plain RET\",\n    \"return_register\": \"EAX\",\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"game_input_on_key_down_00697a50\",\n      \"va\": \"0x00697a50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"game_input_on_key_up_00697a80\",\n      \"va\": \"0x00697a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"game_input_mouse_up_00697af0\",\n      \"va\": \"0x00697af0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"cell_mode_strategy_on_mouse_move_00e51010\",\n      \"va\": \"0x00e51010\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"cell_mode_strategy_on_key_down_00e818f0\",\n      \"va\": \"0x00e818f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueGameInput\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac1970\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac1b30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac1dc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac2200\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac2520\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac2a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac2b40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac2d00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac2e20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac3110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac3540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac38d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac5590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac5c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac65d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac68e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac6960\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acebd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acf4c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad0510\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad12a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad2ae0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00adbca0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00adc490\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae49d0\"\
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "original_bytes": 17556,
  "preview": "{\n  \"binary_available\": true,\n  \"binary_sha256\": \"25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e\",\n  \"body_end\": \"00b3d355\",\n  \"body_span_bytes\": 6,\n  \"body_start\": \"00b3d350\",\n  \"callees\": [],\n  \"callers\": [\n    \"FUN_00d3d4f0\",\n    \"FUN_00d40ff0\",\n    \"FUN_00b20e40\",\n    \"FUN_00e10e30\",\n    \"FUN_00cb6a50\",\n    \"FUN_00d63560\",\n    \"FUN_00bdc1a0\",\n    \"FUN_00cb46f0\",\n    \"FUN_00c91250\",\n    \"FUN_00c642e0\",\n    \"FUN_00c979e0\",\n    \"FUN_00ac3110\",\n    \"FUN_00ec2a70\",\n    \"FUN_00ac1dc0\",\n    \"FUN_00b45ca0\",\n    \"FUN_00d824a0\",\n    \"FUN_00d932e0\",\n    \"FUN_00d8d820\",\n    \"FUN_00d39dc0\",\n    \"FUN_00b79e50\",\n    \"FUN_00b80b40\",\n    \"FUN_00ac5c00\",\n    \"FUN_00d7ff20\",\n    \"FUN_00ca72a0\",\n    \"FUN_00bfeb00\",\n    \"FUN_00cb2770\",\n    \"FUN_00d2f940\",\n    \"FUN_00be4c00\",\n    \"FUN_00b783b0\",\n    \"FUN_00d3bf30\",\n    \"FUN_00b08670\",\n    \"FUN_00b9d820\",\n    \"FUN_00c5d140\",\n    \"FUN_00d1c2e0\",\n    \"FUN_00adc490\",\n    \"FUN_00d0bbd0\",\n    \"FUN_00e9ea40\",\n    \"FUN_00cc7240\",\n    \"FUN_00d8a2a0\",\n    \"FUN_00d39670\",\n    \"FUN_00d2dd20\",\n    \"FUN_00c69bc0\",\n    \"FUN_00f32240\",\n    \"FUN_00c099e0\",\n    \"FUN_00d92fb0\",\n    \"FUN_00d2ec50\",\n    \"FUN_00b93ba0\",\n    \"FUN_00bcda00\",\n    \"FUN_00ce1a90\",\n    \"FUN_00c36300\",\n    \"FUN_00b89a30\",\n    \"FUN_00cbb020\",\n    \"FUN_00ad2ae0\",\n    \"FUN_0102acb0\",\n    \"FUN_00c9a8b0\",\n    \"FUN_01006370\",\n    \"FUN_00afdfe0\",\n    \"FUN_00c18740\",\n    \"FUN_00ad12a0\",\n    \"FUN_00b181d0\",\n    \"FUN_00b33030\",\n    \"FUN_00bd40a0\",\n    \"FUN_00c91700\",\n    \"FUN_00ac65d0\",\n    \"FUN_0105b6a0\",\n    \"FUN_00be88d0\",\n    \"FUN_00b49730\",\n    \"FUN_00d23320\",\n    \"FUN_00eef170\",\n    \"FUN_00d99e20\",\n    \"FUN_00f19270\",\n    \"FUN_00d11730\",\n    \"FUN_00b444c0\",\n    \"FUN_00cc22c0\",\n    \"FUN_00c190e0\",\n    \"FUN_00cb6570\",\n    \"FUN_00d124e0\",\n    \"FUN_00b421b0\",\n    \"FUN_00c104d0\",\n    \"FUN_00ac6960\",\n    \"FUN_00bc0180\",\n    \"FUN_00c17de0\",\n    \"FUN_00d56630\",\n    \"FUN_00eec2b0\",\n    \"FUN_01056d30\",\n    \"FUN_00b49a50\",\n    \"FUN_00d73350\",\n    \"FUN_00f316d0\",\n    \"FUN_00cddcf0\",\n    \"FUN_00eba540\",\n    \"FUN_00b57c40\",\n    \"FUN_00bcd970\",\n    \"FUN_00d35190\",\n    \"FUN_00dbb840\",\n    \"FUN_00ad0510\",\n    \"FUN_00daf820\",\n    \"FUN_01060df0\",\n    \"FUN_00c29530\",\n    \"FUN_00cc5850\",\n    \"FUN_00d9aa20\",\n    \"FUN_00ac2e20\",\n    \"FUN_00f011b0\",\n    \"FUN_00c82d50\",\n    \"FUN_00dcc0a0\",\n    \"FUN_00ca0170\",\n    \"FUN_00cd02d0\",\n    \"FUN_00fdc800\",\n    \"FUN_00d51c30\",\n    \"FUN_00b0a0c0\",\n    \"FUN_00d6e910\",\n    \"FUN_00e0de40\",\n    \"FUN_00b969e0\",\n    \"FUN_00bfb020\",\n    \"FUN_00cea1a0\",\n    \"FUN_00fdeac0\",\n    \"FUN_00af3e50\",\n    \"FUN_00ba0080\",\n    \"FUN_00d841a0\",\n    \"FUN_00bddda0\",\n    \"FUN_00c0ca00\",\n    \"FUN_00bda2f0\",\n    \"FUN_00c271d0\",\n    \"Simulator::cDefaultBeamTool::OnMouseDown\",\n    \"FUN_00cc1c30\",\n    \"FUN_00b17c10\",\n    \"FUN_00ceb710\",\n    \"FUN_00dad390\",\n    \"FUN_00b5a750\",\n    \"FUN_00b86a10\",\n    \"FUN_00adbca0\",\n    \"FUN_00c293f0\",\n    \"FUN_00c82f00\",\n    \"FUN_00c9e960\",\n    \"FUN_00f37690\",\n    \"FUN_00e87db0\",\n    \"FUN_00bd8210\",\n    \"FUN_00beff90\",\n    \"FUN_00d15c00\",\n    \"FUN_00ca2210\",\n    \"FUN_00efc930\",\n    \"FUN_00b52690\",\n    \"FUN_00ff5d20\",\n    \"FUN_00b34790\",\n    \"FUN_00e9bb40\",\n    \"FUN_00ac3540\",\n    \"FUN_00d6df70\",\n    \"FUN_00d2aec0\",\n    \"FUN_00ebe3e0\",\n    \"FUN_00cf18b0\",\n    \"FUN_00cbce30\",\n    \"FUN_00d6e3a0\",\n    \"FUN_00b9fa40\",\n    \"FUN_00af6bf0\",\n    \"FUN_00ed59e0\",\n    \"FUN_00c99140\",\n    \"FUN_00b92280\",\n    \"FUN_00afe3a0\",\n    \"FUN_00b7f920\",\n    \"FUN_00c2a190\",\n    \"FUN_00d5ae80\",\n    \"FUN_00d43e30\",\n    \"FUN_00c9f130\",\n    \"FUN_00c6ba20\",\n    \"FUN_00c289b0\",\n    \"FUN_00beabb0\",\n    \"FUN_00d21810\",\n    \"FUN_00c7ce70\",\n    \"FUN_00d10720\",\n    \"FUN_00ac1b30\",\n    \"FUN_00e0e1a0\",\n    \"FUN_00dcd720\",\n    \"FUN_00bbdbf0\",\n    \"FUN_00deb930\",\n    \"FUN_00e0f2c0\",\n    \"FUN_01021740\",\n    \"FUN_00eba0e0\",\n    \"FUN_00f355b0\",\n    \"FUN_00b97720\",\n    \"FUN_00bf8710\",\n    \"FUN_010170e0\",\n    \"FUN_00c6cbf0\",\n    \"FUN_00db7d60\",\n    \"FUN_00db86a0\",\n    \"FUN_00b94420\",\n    \"FUN_00ffb830\",\n    \"FUN_00b76f10\",\n    \"FUN_00bbd730\",\n    \"FUN_00b294c0\",\n    \"FUN_00bc2070\",\n    \"FUN_00cfbc10\",\n    \"FUN_00d739c0\",\n    \"FUN_00fdba50\",\n    \"FUN_00c6b8e0\",\n    \"FUN_00bda200\",\n    \"FUN_00be7bf0\",\n    \"FUN_00c9ff40\",\n    \"FUN_00be3850\",\n    \"FUN_00d858a0\",\n    \"FUN_00b56090\",\n    \"FUN_00ebbfb0\",\n    \"FUN_01003690\",\n    \"FUN_00bf0c60\",\n    \"FUN_00eff590\",\n    \"FUN_010317d0\",\n    \"FUN_00ce3b60\",\n    \"FUN_00f3cf10\",\n    \"FUN_00acf4c0\",\n    \"FUN_00c6a100\",\n    \"FUN_00fe0f40\",\n    \"FUN_00f27d80\",\n    \"FUN_00f015b0\",\n    \"FUN_00cbd620\",\n    \"FUN_00b60110\",\n    \"FUN_00cbf120\",\n    \"FUN_00ff9800\",\n    \"FUN_00d81940\",\n    \"FUN_00bbd0a0\",\n    \"FUN_0105c8d0\",\n    \"FUN_00b7a1d0\",\n    \"FUN_00d4c650\",\n    \"FUN_00ce8f70\",\n    \"FUN_00ca31f0\",\n    \"FUN_00c97b10\",\n    \"FUN_00dad0c0\",\n    \"FUN_00efc9c0\",\n    \"FUN_00f10bd0\",\n    \"FUN_00afdc00\",\n    \"FUN_00dc07d0\",\n    \"FUN_00c9d030\",\n    \"FUN_00b7b070\",\n    \"FUN_00c8e490\",\n    \"FUN_00f20a60\",\n    \"FUN_00ac5590\",\n    \"FUN_00d09f00\",\n    \"FUN_0105ba00\",\n    \"FUN_00be5be0\",\n    \"FUN_010537e0\",\n    \"FUN_00feff80\",\n    \"FUN_00fefbb0\",\n    \"FUN_00c6d7c0\",\n    \"FUN_00f3b9e0\",\n    \"FUN_00bf59d0\",\n    \"FUN_00db0130\",\n    \"FUN_00cf8160\",\n    \"FUN_00d130d0\",\n    \"FUN_0101ed80\",\n    \"FUN_00b9a8
[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x0167eaf8"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave7/00b3d350.json"
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
    "Observe the original global slot and concrete manager lifetime before making ownership claims."
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
  "OpaqueGameInput",
  "OpaqueGameInputManager*",
  "READ"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8360",
      "0x007d8360",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30",
      "0x007d8c30",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d8d40"
    ],
    "conflict_id": "Q-INPUT-ROUTING",
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
      "0x00b3d350",
      "0x00b3d400",
      "0x00b3d350",
      "0x00b3d350",
      "0x01485550"
    ],
    "conflict_id": "TB-VT-008",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "separate_entities",
      "preferred_claim": null,
      "preserved_alternatives": true,
      "scope_note": "The interface and object layout are supported; the concrete vtable address is unresolved.",
      "status": "unresolved",
      "taxonomy": "unresolved"
    },
    "resolution_status": "unresolved",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "Simulator::cGameInputManager 27-slot interface and missing concrete vtable base",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  },
  {
    "anchors": [
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360",
      "0x007d8470",
      "0x007d8470",
      "0x007d85b0",
      "0x007d85b0",
      "0x007d8c30"
    ],
    "conflict_id": "U-GAME-INPUT-ROUTER",
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
      "0x005737d0",
      "0x00588570",
      "0x0058ac10",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587a20"
    ],
    "conflict_id": "editor_input_routing",
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
