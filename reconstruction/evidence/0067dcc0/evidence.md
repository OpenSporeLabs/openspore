# Evidence 0x0067dcc0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9a1c92e69d129c73be81dbfc669608b761523646dc3ab870697d696c8fdc709e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl-compatible no-argument accessor",
  "hidden_receiver": null,
  "ordinary_stack_argument_slots": 0,
  "ret_form": "RET",
  "return_note": "opaque 32-bit application-system pointer",
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
  "content_sha256": "f592bb39af8fa86067bedfe879e9cd5c3575db59b543fb89cd31ebf458fffc73",
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
    "persisted_calling_convention": "cdecl-compatible no-argument accessor"
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
      "at": "0x0067dcc0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x015fd890]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0067dcc5",
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
    "va": "0x0067dcc0"
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
    "va": "0x0040a590"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040e5b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040eab0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040eb70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040f820"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040fc00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040fe00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00410d70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00410dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004111e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00411890"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004157d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004165a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00416990"
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
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x0067dcc0",
      "0x00b3d330",
      "0x00e7fc00",
      "0x00e20860"
    ],
    "conflict_id": "U01",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e81cf0",
      "0x00e81cf0",
      "0x0067dcc0",
      "0x00b3d330",
      "0x00e552f0"
    ],
    "conflict_id": "U04",
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
      "0x00b5e160",
      "0x00b5e160",
      "0x0067dcc0"
    ],
    "conflict_id": "U05",
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
      "0x0067dcc0",
      "0x0067deb0",
      "0x00b3d330",
      "0x00b3d4e0",
      "0x015fd890",
      "0x0167eaf0",
      "0x0167eb60",
      "0x0067dcc0",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9590",
      "0x00ae9930",
      "0x00ae9c90",
      "0x00ae9f50",
      "0x00aeb3e0"
    ],
    "conflict_id": "global_service_publication",
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
      "address": "0067dcc0",
      "instruction": "MOV EAX,[0x015fd890]"
    },
    {
      "address": "0067dcc5",
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
  "original_bytes": 14212,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"hidden_receiver\": null,\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"RET\",\n    \"return_note\": \"opaque 32-bit application-system pointer\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"editor_anim_event_message_send_0059d8b0\",\n      \"va\": \"0x0059d8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 3,\n      \"symbol\": \"palette_application_setup_005c53c0\",\n      \"va\": \"0x005c53c0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 3,\n      \"symbol\": \"palette_select_category_005cb240\",\n      \"va\": \"0x005cb240\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00403af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00404660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040a590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040e5b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040eab0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040eb70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040f820\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040fc00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040fe00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00410d70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00410dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004111e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00411890\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004157d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004165a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00416990\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0041a0c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00428450\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004284d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0042ff30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00430320\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00430e70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00457af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004581d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a1070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a2350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a29a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a6f10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004add60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n       
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "original_bytes": 19387,
  "preview": "{\n  \"binary_available\": true,\n  \"binary_sha256\": \"25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e\",\n  \"body_end\": \"0067dcc5\",\n  \"body_span_bytes\": 6,\n  \"body_start\": \"0067dcc0\",\n  \"callees\": [],\n  \"callers\": [\n    \"Editors::cEditor::HandleMessage\",\n    \"FUN_00d9ff00\",\n    \"FUN_00ee3e40\",\n    \"FUN_0066c490\",\n    \"FUN_00650190\",\n    \"FUN_00c34ee0\",\n    \"FUN_00e02580\",\n    \"FUN_00ea5650\",\n    \"FUN_00fde180\",\n    \"FUN_00adf840\",\n    \"FUN_006073a0\",\n    \"FUN_00b148c0\",\n    \"FUN_00ec5e80\",\n    \"FUN_005fae40\",\n    \"FUN_006074b0\",\n    \"FUN_00b30d70\",\n    \"FUN_005f4b80\",\n    \"Editors::cEditor::OnKeyDown\",\n    \"FUN_00ef2370\",\n    \"FUN_00f00790\",\n    \"FUN_0057c2f0\",\n    \"FUN_00fd90c0\",\n    \"FUN_00e538b0\",\n    \"FUN_00642860\",\n    \"FUN_007e7115\",\n    \"FUN_007c8940\",\n    \"FUN_00b451f0\",\n    \"FUN_00be4c00\",\n    \"FUN_00bf2270\",\n    \"FUN_007664e0\",\n    \"FUN_00c20230\",\n    \"FUN_00f16580\",\n    \"FUN_00f47700\",\n    \"FUN_00d1c2e0\",\n    \"FUN_00d45530\",\n    \"FUN_006a9790\",\n    \"FUN_0061dfe0\",\n    \"FUN_00600ab0\",\n    \"FUN_00c18370\",\n    \"FUN_0060bae0\",\n    \"FUN_00ea6b20\",\n    \"FUN_00aed0e0\",\n    \"FUN_00e02900\",\n    \"FUN_00b1dee0\",\n    \"FUN_0103eff0\",\n    \"FUN_005fe050\",\n    \"FUN_00cf1ad0\",\n    \"FUN_004a1070\",\n    \"FUN_00e033d0\",\n    \"FUN_005ff4e0\",\n    \"FUN_00eeba40\",\n    \"FUN_00ed1880\",\n    \"FUN_00ec64b0\",\n    \"FUN_0060b800\",\n    \"FUN_00e02a20\",\n    \"FUN_00e53f20\",\n    \"FUN_010021a0\",\n    \"FUN_00adffd0\",\n    \"FUN_00d2cea0\",\n    \"FUN_004a6f10\",\n    \"FUN_00ed7a10\",\n    \"FUN_00f44dd0\",\n    \"FUN_0064c8e0\",\n    \"FUN_00bf8170\",\n    \"FUN_00eb0ea0\",\n    \"FUN_010393a0\",\n    \"FUN_00e248b0\",\n    \"FUN_00f05c40\",\n    \"FUN_00f96d20\",\n    \"FUN_0060b290\",\n    \"FUN_00f17870\",\n    \"FUN_0076f210\",\n    \"FUN_01023be0\",\n    \"FUN_00c30c10\",\n    \"FUN_00e02950\",\n    \"FUN_00632fe0\",\n    \"FUN_00d3fcf0\",\n    \"FUN_00667b00\",\n    \"FUN_00be88d0\",\n    \"FUN_00606d80\",\n    \"FUN_005ff640\",\n    \"FUN_00aea210\",\n    \"FUN_00608a10\",\n    \"FUN_0065b6b0\",\n    \"FUN_006a58a0\",\n    \"FUN_00edcd30\",\n    \"FUN_00630f20\",\n    \"FUN_008130c0\",\n    \"FUN_00672040\",\n    \"FUN_00e34a00\",\n    \"FUN_007bd4c0\",\n    \"FUN_00b1cc00\",\n    \"FUN_005ff850\",\n    \"FUN_007e72d0\",\n    \"FUN_00f69a30\",\n    \"FUN_007e9d00\",\n    \"App::Canvas::func6Ch\",\n    \"FUN_0060cec0\",\n    \"FUN_00ffe3a0\",\n    \"FUN_00fd7800\",\n    \"FUN_0063d9e0\",\n    \"FUN_00dd4260\",\n    \"FUN_00585d40\",\n    \"FUN_0064a990\",\n    \"FUN_00b22960\",\n    \"App::cAppSystem::Unpause\",\n    \"FUN_00ad8f20\",\n    \"FUN_00430e70\",\n    \"FUN_00d0e170\",\n    \"FUN_00fa9b50\",\n    \"FUN_010593e0\",\n    \"FUN_00b18960\",\n    \"FUN_00813e70\",\n    \"FUN_007b7ac0\",\n    \"FUN_0063d2f0\",\n    \"FUN_00d35190\",\n    \"FUN_0040a590\",\n    \"FUN_00dd1aa0\",\n    \"FUN_005dc380\",\n    \"FUN_00f3cd60\",\n    \"FUN_01020fc0\",\n    \"FUN_00aeb7b0\",\n    \"FUN_00b19180\",\n    \"FUN_0076cd30\",\n    \"FUN_00fdc800\",\n    \"FUN_007094c0\",\n    \"FUN_00f3ce80\",\n    \"FUN_00ea7ab0\",\n    \"FUN_005c6f40\",\n    \"FUN_00ffa2c0\",\n    \"FUN_00fdeac0\",\n    \"FUN_005dfd00\",\n    \"FUN_00603260\",\n    \"FUN_00644910\",\n    \"FUN_00777060\",\n    \"Editors::cEditor::SetActiveMode\",\n    \"FUN_00ad7d60\",\n    \"FUN_006f9cf0\",\n    \"FUN_00ee68b0\",\n    \"FUN_00c15dc0\",\n    \"FUN_00c267e0\",\n    \"FUN_0063ced0\",\n    \"FUN_00ea8ad0\",\n    \"FUN_00de0890\",\n    \"FUN_00f37690\",\n    \"FUN_0063cf90\",\n    \"FUN_00aebe90\",\n    \"FUN_00c316c0\",\n    \"FUN_00636560\",\n    \"FUN_00e2fe10\",\n    \"FUN_00fd7610\",\n    \"FUN_006a9b60\",\n    \"FUN_0057c440\",\n    \"FUN_00d3c6a0\",\n    \"FUN_00c37180\",\n    \"FUN_00edfb30\",\n    \"FUN_0105b350\",\n    \"App::cAppSystem::func7Ch\",\n    \"FUN_00601f00\",\n    \"FUN_00de00e0\",\n    \"FUN_00dea420\",\n    \"FUN_00deac20\",\n    \"FUN_00ea6ae0\",\n    \"FUN_00de81b0\",\n    \"FUN_00edbd30\",\n    \"FUN_01078120\",\n    \"FUN_007afe10\",\n    \"FUN_005fc330\",\n    \"FUN_0040eb70\",\n    \"FUN_00adf690\",\n    \"FUN_01064560\",\n    \"FUN_004df310\",\n    \"FUN_006111c0\",\n    \"FUN_00ea56a0\",\n    \"FUN_00ff4470\",\n    \"FUN_00573fb0\",\n    \"FUN_00f1e620\",\n    \"FUN_00e7f630\",\n    \"FUN_0041a0c0\",\n    \"FUN_007771f0\",\n    \"FUN_00561340\",\n    \"FUN_00e010c0\",\n    \"FUN_01073700\",\n    \"FUN_00bf45f0\",\n    \"FUN_004165a0\",\n    \"FUN_00e03620\",\n    \"FUN_006f69c0\",\n    \"FUN_00deb930\",\n    \"FUN_00debec0\",\n    \"FUN_0103fba0\",\n    \"FUN_00620ef0\",\n    \"FUN_01041090\",\n    \"FUN_00ed57e0\",\n    \"FUN_00befc40\",\n    \"FUN_00eb05a0\",\n    \"FUN_00f38930\",\n    \"FUN_00c490e0\",\n    \"FUN_00627ca0\",\n    \"FUN_00e277b0\",\n    \"FUN_00c7e280\",\n    \"FUN_00e22370\",\n    \"FUN_0061faf0\",\n    \"FUN_00f44fe0\",\n    \"FUN_00b294c0\",\n    \"FUN_00ed49a0\",\n    \"FUN_004a29a0\",\n    \"FUN_00e45760\",\n    \"FUN_00df5d90\",\n    \"FUN_006f0890\",\n    \"FUN_00e15a10\",\n    \"FUN_00d2cb10\",\n    \"FUN_00f0cad0\",\n    \"FUN_00688d50\",\n    \"FUN_00ac14e0\",\n    \"FUN_005c0380\",\n    \"FUN_005f16d0\",\n    \"FUN_00e20860\",\n    \"FUN_005ef850\",\n    \"FUN_0105a890\",\n    \"FUN_006448e0\",\n    \"FUN_00b2fbe0\",\n    \"FUN_01065900\",\n    \"FUN_00ef2c70\",\n    \"FUN_00ff48d0\",\n    \"FUN_00a428a0\",\n    \"FUN_00e44200\",\n    \"FUN_005f4310\",\n    \"FUN_007bbde0\",\n    \"FUN_00410dd0\",\n    \"FUN_007b77a0\",\n    \"FUN_00d7c3e0\",\n    \"FUN_005c14f0\",\n    \"FUN_00eea260\",\n    \"FUN_00d09d30\",\n    \"FUN_0060b050\",\n    \"FUN_01078820\",\n    \"FUN_00eeaf00\",\n    \"FUN_00754ca0\",\n    \"FUN_00aeb600\",\n    \"FUN_00f17b00\",\n    \"FUN_00f18660\",\n    \"FUN_00b5dbb0\",\n    \"FUN_00ff9800\",\n    \"FUN_00f22710\",\n    \
[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:MOV EAX,[0x015fd890]",
  "global:get_function_globals audit reports one undefined4 read at 0x015fd890"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave6-misc-engine/misc_engine.cpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine.hpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave6-misc-engine/0067dcc0.json"
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
  "opaque 32-bit application-system pointer"
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
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x00e20860",
      "0x0067dcc0",
      "0x00b3d330",
      "0x00e7fc00",
      "0x00e20860"
    ],
    "conflict_id": "U01",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e81cf0",
      "0x00e81cf0",
      "0x0067dcc0",
      "0x00b3d330",
      "0x00e552f0"
    ],
    "conflict_id": "U04",
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
      "0x00b5e160",
      "0x00b5e160",
      "0x0067dcc0"
    ],
    "conflict_id": "U05",
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
      "0x0067dcc0",
      "0x0067deb0",
      "0x00b3d330",
      "0x00b3d4e0",
      "0x015fd890",
      "0x0167eaf0",
      "0x0167eb60",
      "0x0067dcc0",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9590",
      "0x00ae9930",
      "0x00ae9c90",
      "0x00ae9f50",
      "0x00aeb3e0"
    ],
    "conflict_id": "global_service_publication",
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
