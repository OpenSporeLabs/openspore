# Evidence 0x0067dcd0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `cee05250f32cceeb84853d9c45f0011e32264abb3830b0e192f5a0dff7141683`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__cdecl",
  "ordinary_stack_argument_slots": 0,
  "return_note": "borrowed pointer word",
  "return_register": "EAX",
  "return_width_bytes": 4,
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
  "content_sha256": "6b43359bdab69f3b7c3e66e532e8d1fb9cbd6fb1be2eed24be1aa2977f0414c3",
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
    "persisted_calling_convention": "__cdecl"
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
      "at": "0x0067dcd0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x015fd894]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0067dcd5",
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
    "va": "0x0067dcd0"
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
    "va": "0x004021a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00402cc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00403af0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00404660"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00407280"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00411e50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00415730"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004157d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00417210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00417600"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00418500"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0041a0c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00430e70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00466690"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0046c900"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004ae3b0"
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
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d39360",
      "0x045ab96e",
      "0x00d2e480",
      "0x00aebe90",
      "0x045ab96e",
      "0x0067dcd0",
      "0x0067dcd0",
      "0x007d8420",
      "0x007d8420",
      "0x007d8cf0",
      "0x007d8cf0",
      "0x007d8d40",
      "0x007d8d40"
    ],
    "conflict_id": "U-005-evolution-level-promotion",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "resolution_status": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00594b10",
      "0x00594b10",
      "0x00596da0",
      "0x00596da0",
      "0x00597390",
      "0x00597390",
      "0x00597400",
      "0x00597400",
      "0x00598db0",
      "0x00598db0",
      "0x00598e90",
      "0x00598e90",
      "0x00599440",
      "0x00599440",
      "0x0067dcd0",
      "0x0067dcd0"
    ],
    "conflict_id": "baby_growth_transition",
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
  "count": 2,
  "instructions": [
    {
      "address": "0067dcd0",
      "instruction": "MOV EAX,[0x015fd894]"
    },
    {
      "address": "0067dcd5",
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
  "original_bytes": 13852,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"return_note\": \"borrowed pointer word\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:READ,WRITE,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 11,\n      \"symbol\": \"App_IStateManager_Get_0067dce0\",\n      \"va\": \"0x0067dce0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:READ,WRITE,undefined4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 11,\n      \"symbol\": \"App_IPropManager_Get_0067ddf0\",\n      \"va\": \"0x0067ddf0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:READ,WRITE\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"ui_layer_manager_get_0067ca90\",\n      \"va\": \"0x0067ca90\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:READ,WRITE\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"anim_manager_get_0067cae0\",\n      \"va\": \"0x0067cae0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:READ,WRITE\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"app_locale_manager_get_0067de00\",\n      \"va\": \"0x0067de00\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n      \"va\": \"0x005c7ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"service_005fc330\",\n      \"va\": \"0x005fc330\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004021a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00402cc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00403af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00404660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00407280\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00411e50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00415730\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004157d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00417210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00417600\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00418500\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0041a0c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00430e70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00466690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0046c900\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ae3b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004badd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004bafc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004bc080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004d15c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004d5020\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004da3a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004db6e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004dc660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004e5410\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004e9950\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ea920\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004eb270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004f3c50\"\n      },\n      {\n        \"name\": null,\n        \"recons
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
  "body_end": "0067dcd5",
  "body_span_bytes": 6,
  "body_start": "0067dcd0",
  "callees": [],
  "callers": [
    "FUN_0055ec70",
    "Editors::cEditor::HandleMessage",
    "FUN_0046c900",
    "FUN_0082cd30",
    "FUN_006b3240",
    "FUN_00bba640",
    "FUN_01007430",
    "FUN_00617f10",
    "FUN_00ec5e80",
    "FUN_00646370",
    "FUN_00ef4bd0",
    "FUN_006419f0",
    "FUN_00f3d3e0",
    "FUN_0106b860",
    "FUN_00e4a9f0",
    "FUN_01002ee0",
    "FUN_00e84510",
    "FUN_00f135b0",
    "FUN_004e9950",
    "FUN_007e7115",
    "FUN_00aeee50",
    "FUN_00402cc0",
    "FUN_005fa8d0",
    "FUN_00755c80",
    "FUN_00de9600",
    "FUN_00556e30",
    "FUN_00615870",
    "FUN_00f47ed0",
    "FUN_0055fc10",
    "FUN_00d18df0",
    "FUN_00552450",
    "FUN_0070aed0",
    "FUN_00e83910",
    "FUN_00e4ced0",
    "FUN_00a08a20",
    "FUN_004bafc0",
    "FUN_005582a0",
    "FUN_00b19f70",
    "FUN_007a6b40",
    "FUN_00411e50",
    "FUN_00826960",
    "FUN_004dc660",
    "FUN_0066f150",
    "FUN_00686490",
    "FUN_00711780",
    "FUN_004e5410",
    "FUN_00a0a120",
    "FUN_00ec6820",
    "FUN_00404660",
    "FUN_00f3c330",
    "FUN_00775760",
    "FUN_006b4b60",
    "FUN_005c7ff0",
    "FUN_00516ca0",
    "FUN_004f3c50",
    "FUN_00bb8b20",
    "FUN_004ae3b0",
    "FUN_005fb430",
    "FUN_006b6920",
    "FUN_00ec5340",
    "FUN_0055cd90",
    "FUN_00aeef00",
    "FUN_00c75460",
    "FUN_00a0f080",
    "FUN_00bbaa80",
    "FUN_006b4010",
    "FUN_00edabf0",
    "FUN_007ca1c0",
    "FUN_00552300",
    "FUN_007559a0",
    "FUN_00f2c470",
    "FUN_005567e0",
    "FUN_004157d0",
    "FUN_00ea23e0",
    "FUN_00417600",
    "FUN_00eb19e0",
    "FUN_00577b20",
    "FUN_009feb30",
    "FUN_00f93c40",
    "FUN_00d1cb00",
    "FUN_00ef6700",
    "FUN_00f662c0",
    "FUN_00f2b790",
    "FUN_00caa980",
    "FUN_00585d40",
    "FUN_004f3de0",
    "FUN_005f5f20",
    "FUN_005bf120",
    "FUN_00430e70",
    "FUN_0061b620",
    "FUN_006b27f0",
    "FUN_00e4d920",
    "FUN_006f1860",
    "FUN_0068d840",
    "FUN_00c87cc0",
    "FUN_00ba7c20",
    "FUN_00552580",
    "FUN_00c30bd0",
    "FUN_007f2240",
    "FUN_0074d2c0",
    "FUN_006c1ae0",
    "FUN_007e9a00",
    "FUN_0060ee90",
    "FUN_00f42a50",
    "FUN_00766b30",
    "FUN_00755240",
    "FUN_00e000a0",
    "FUN_00f3cb60",
    "FUN_00813b20",
    "FUN_004db6e0",
    "FUN_0068d290",
    "FUN_00555cf0",
    "FUN_00e0e840",
    "FUN_00bac3a0",
    "FUN_00614050",
    "FUN_00617130",
    "FUN_00813760",
    "FUN_00668c80",
    "FUN_00641900",
    "FUN_0068d0d0",
    "FUN_00a09280",
    "FUN_00613a10",
    "FUN_00e0eab0",
    "FUN_00fef9f0",
    "FUN_00ec5a60",
    "FUN_00a088e0",
    "FUN_00e82140",
    "FUN_00f93790",
    "FUN_00614280",
    "FUN_00466690",
    "FUN_00aeeda0",
    "FUN_006708d0",
    "FUN_00f43420",
    "Editor_Save",
    "FUN_00696c80",
    "FUN_00f318e0",
    "FUN_00713070",
    "FUN_00edad00",
    "FUN_00f37f20",
    "FUN_00615ed0",
    "FUN_006a9b60",
    "FUN_006b2000",
    "FUN_00e4c9e0",
    "FUN_004d15c0",
    "FUN_007ac850",
    "FUN_00ee40f0",
    "FUN_005fc330",
    "FUN_0055f7a0",
    "FUN_006b1d50",
    "FUN_006145d0",
    "FUN_006b6d10",
    "FUN_00815dd0",
    "FUN_0063f740",
    "FUN_0055aa00",
    "FUN_005a8f80",
    "FUN_00407280",
    "FUN_004ea920",
    "FUN_00741210",
    "FUN_005c1570",
    "FUN_0055cff0",
    "FUN_00aeec90",
    "FUN_0041a0c0",
    "FUN_00f3d260",
    "FUN_00561340",
    "FUN_00bb6a30",
    "FUN_004eb270",
    "FUN_0059db40",
    "FUN_005a8ed0",
    "FUN_006177b0",
    "FUN_00eef810",
    "FUN_00a0d570",
    "FUN_007b8cb0",
    "FUN_00668d90",
    "FUN_00712670",
    "FUN_00e3f010",
    "FUN_00e3ce60",
    "FUN_008138e0",
    "FUN_00deb930",
    "FUN_004bc080",
    "FUN_006a8610",
    "FUN_00f355b0",
    "FUN_005e0930",
    "FUN_007655f0",
    "FUN_00415730",
    "FUN_006b10a0",
    "FUN_00e4b730",
    "FUN_00e9a940",
    "FUN_00e3e350",
    "FUN_0055e190",
    "FUN_00641e40",
    "FUN_007aa200",
    "FUN_00f27990",
    "FUN_0055dce0",
    "FUN_00765d30",
    "FUN_00eeebd0",
    "FUN_00f44fe0",
    "FUN_008124a0",
    "FUN_00595a90",
    "FUN_00754960",
    "FUN_00e47930",
    "FUN_005f9920",
    "FUN_00e4b170",
    "FUN_006b2b30",
    "FUN_00755fe0",
    "FUN_004d5020",
    "FUN_00eeea50",
    "FUN_00b60d80",
    "FUN_005562a0",
    "FUN_006b3050",
    "FUN_0074c670",
    "FUN_00bb7940",
    "FUN_00e4b910",
    "FUN_005598b0",
    "FUN_01036940",
    "FUN_00552080",
    "FUN_00558bf0",
    "FUN_00f372b0",
    "FUN_00a42220",
    "FUN_0066ce00",
    "FUN_006ae880",
    "FUN_006a7e40",
    "FUN_00deb770",
    "FUN_0061c880",
    "FUN_0068d5a0",
    "FUN_004f5c60",
    "FUN_00e5d500",
    "FUN_0055a580",
    "FUN_00bd5ea0",
    "FUN_00f2ac30",
    "FUN_007a7d50",
    "FUN_006b2dc0",
    "FUN_005dec10",
    "FUN_007acbb0",
    "FUN_0072fff0",
    "FUN_01006ef0",
    "FUN_00768650",
    "FUN_00eaa9a0",
    "FUN_00417210",
    "FUN_00670370",
    "FUN_00f3d5d0",
    "FUN_00eecba0",
    "FUN_00418500",
    "FUN_00aeefc0",
    "FUN_007cfcd0",
    "FUN_00f938b0",
    "FUN_00e821d0",
    "FUN_006b2090",
    "FUN_005f3930",
    "FUN_006175c0",
    "FUN_006b22f0",
    "FUN_007db650",
    "FUN_00697754",
    "FUN_004badd0",
    "FUN_00d1c610",
    "FUN_00e4cc50",
    "FUN_007ac750",
    "FUN_00b1b410",
    "FUN_00aeebe0",
    "FUN_00ea2790",
    "FUN_00e4ccf0",
    "FUN_0066daf0",
    "FUN_00d130d0",
    "FUN_0055aac0",
    "FUN_00e3cf60",
    "FUN_00b95500",
    "FUN_00fba330",
    "FUN_00755d40",
    "FUN_00555f70",
    "FUN_00613c60",
    "FUN_010727e0",
    "FUN_005634e0",
    "FUN_00687610",
    "FUN_00d1a2b0",
    "FUN_0057f6c0",
    "FUN_00563ac0",
    "FUN_008137f0",
    "FUN_007ab860",
    "FUN_00e4d840",
    "FUN_00bb6390",
    "FUN_0054df60",
    "FUN_006866f0",
    "FUN_006aa7c0",
    "FUN_0057ea30",
    "FUN_006b2620",
    "FUN_00bd3750",
    "FUN_00756a20",
    "FUN_006960f0",
    "FUN_00dffd
[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x015fd894",
  "global:g_wave6_app_manager_globals.app_game_mode_manager_015fd894"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave6-app-managers/app_managers_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave6-app-managers/0067dcd0.json"
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueAppGameModeManager*",
  "READ",
  "WRITE",
  "borrowed pointer word",
  "undefined4"
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
      "0x00d2e380",
      "0x00d2e480",
      "0x00d2e8a0",
      "0x00d39360",
      "0x045ab96e",
      "0x00d2e480",
      "0x00aebe90",
      "0x045ab96e",
      "0x0067dcd0",
      "0x0067dcd0",
      "0x007d8420",
      "0x007d8420",
      "0x007d8cf0",
      "0x007d8cf0",
      "0x007d8d40",
      "0x007d8d40"
    ],
    "conflict_id": "U-005-evolution-level-promotion",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "resolution_status": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00594b10",
      "0x00594b10",
      "0x00596da0",
      "0x00596da0",
      "0x00597390",
      "0x00597390",
      "0x00597400",
      "0x00597400",
      "0x00598db0",
      "0x00598db0",
      "0x00598e90",
      "0x00598e90",
      "0x00599440",
      "0x00599440",
      "0x0067dcd0",
      "0x0067dcd0"
    ],
    "conflict_id": "baby_growth_transition",
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
