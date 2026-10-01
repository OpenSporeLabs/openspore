# Evidence 0x00b3d400

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `8fcbcd4fa56c90c48c3e70960f6179c42e73e323f66306bb4b97487eb1a1405a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__cdecl",
  "return_register": "EAX",
  "return_type": "OpaqueCanonicalNounManager*",
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
  "content_sha256": "b839cd275d5f1049aab71890ef6e1b13fc99101a950ec6b687ae0240d9dbace9",
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
      "at": "0x00b3d400",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb60]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d405",
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
    "va": "0x00b3d400"
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
    "va": "0x00ae9f50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aebe90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32aa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32c60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32f60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b330e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b33350"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b335d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b33970"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6f650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6f760"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6f820"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ccec20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd3610"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd3bf0"
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
      "0x00b3d300",
      "0x00b3d400",
      "0x00b3d2a0",
      "0x00b3d3a0",
      "0x00b5b800",
      "0xffffffff",
      "0x00b3d300",
      "0x00b3d2a0",
      "0x00b3d400",
      "0x00b3d3a0",
      "0x00b5b800"
    ],
    "conflict_id": "CF-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-f-cross-domain-impact.json",
    "subject": null,
    "unresolved_reason": {
      "missing_evidence": [
        "Direct or indirect publisher and teardown evidence for both alternate/canonical manager slot pairs.",
        "Pointer-equality checks across mode and service lifecycle boundaries.",
        "The concrete receiver class and physical storage type behind DAT_0167eaec and forwarded_object+0x20."
      ],
      "status": "blocked"
    }
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
      "address": "00b3d400",
      "instruction": "MOV EAX,[0x0167eb60]"
    },
    {
      "address": "00b3d405",
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
  "original_bytes": 14684,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__cdecl\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"OpaqueCanonicalNounManager*\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 10,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 10,\n      \"symbol\": \"Simulator_cSpaceTrading_Get\",\n      \"va\": \"0x00b3d4d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00ff3f00\",\n      \"va\": \"0x00ff3f00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_01021080\",\n      \"va\": \"0x01021080\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_01021230\",\n      \"va\": \"0x01021230\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Unconditional read of the canonical noun slot 0x0167eb60; no fallback, ownership operation, or runtime publication/equality claim.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCanonicalNounManager\",\n  \"cluster\": null,\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9f50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32aa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32c60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32f60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b330e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b335d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33970\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6f650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6f760\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6f820\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ccec20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd3610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd3bf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ce8ee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d0e170\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d100b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d37ea0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d37f10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d38150\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd2e80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd30d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e16090\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e168d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e17570\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e1d7a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4fe90\"\n      },\n      {\n        \"name\": \"App::cCellModeStrategy::OnEnter\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e552f0\"\n      },\n      
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
  "body_end": "00b3d405",
  "body_span_bytes": 6,
  "body_start": "00b3d400",
  "callees": [],
  "callers": [
    "FUN_00cd3610",
    "Simulator::Cell::cCellGame::Initialize",
    "FUN_00d100b0",
    "FUN_00ccec20",
    "FUN_00d37f10",
    "FUN_01007430",
    "FUN_00e75b80",
    "FUN_00cd3bf0",
    "FUN_00e1d7a0",
    "FUN_00b6f820",
    "FUN_00e16090",
    "FUN_00fe3cc0",
    "FUN_00d37ea0",
    "FUN_00e17570",
    "FUN_00b33970",
    "FUN_00b33350",
    "FUN_00d0e170",
    "FUN_00b330e0",
    "App::cCellModeStrategy::OnEnter",
    "FUN_00b335d0",
    "FUN_00e5d7b0",
    "FUN_00aebe90",
    "FUN_00dd30d0",
    "FUN_00b6f650",
    "FUN_00fe5a20",
    "FUN_00b32f60",
    "FUN_00b32c60",
    "FUN_00b32dd0",
    "FUN_00e6c9f0",
    "FUN_00e4fe90",
    "FUN_00e168d0",
    "FUN_00dd2e80",
    "FUN_00b32aa0",
    "FUN_00ef10c0",
    "FUN_01003230",
    "FUN_00ae9f50",
    "FUN_00b6f760",
    "FUN_00d38150",
    "FUN_01003160",
    "FUN_00e64a00",
    "FUN_00fe6490",
    "FUN_00fe5430",
    "FUN_00ce8ee0"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d400",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::cGameNounManager::Get",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "cGameNounManager *",
  "return_type_resolved": true,
  "rva": "0x73d400",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "cGameNounManager * Simulator::cGameNounManager::Get(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d400",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 63,
  "xrefs": [
    {
      "from": "00fe548b"
    },
    {
      "from": "00aece75"
    },
    {
      "from": "00aea0e4"
    },
    {
      "from": "00dd2f7f"
    },
    {
      "from": "00dd2f89"
    },
    {
      "from": "00dd3108"
    },
    {
      "from": "00dd3113"
    },
    {
      "from": "00b3379c"
    },
    {
      "from": "0100336d"
    },
    {
      "from": "00e169e6"
    },
    {
      "from": "00b33b2c"
    },
    {
      "from": "00b32af6"
    },
    {
      "from": "00b32cc5"
    },
    {
      "from": "00b32e0f"
    },
    {
      "from": "00b32fe9"
    },
    {
      "from": "00b33120"
    },
    {
      "from": "00b333b2"
    },
    {
      "from": "00d10393"
    },
    {
      "from": "00d1039e"
    },
    {
      "from": "00b6f659"
    },
    {
      "from": "00b6f773"
    },
    {
      "from": "00ccec48"
    },
    {
      "from": "00ccec52"
    },
    {
      "from": "00cd3619"
    },
    {
      "from": "00cd3bf7"
    },
    {
      "from": "00ce8f52"
    },
    {
      "from": "00ce8f5d"
    },
    {
      "from": "00d0e75b"
    },
    {
      "from": "00d0e766"
    },
    {
      "from": "00d37ea8"
    },
    {
      "from": "00d38159"
    },
    {
      "from": "00d37f41"
    },
    {
      "from": "00e1628b"
    },
    {
      "from": "00e1d83e"
    },
    {
      "from": "00e64b83"
    },
    {
      "from": "00e5d985"
    },
    {
      "from": "00e5d9d8"
    },
    {
      "from": "00e5d9e1"
    },
    {
      "from": "00e6ca9e"
    },
    {
      "from": "00e4feb8"
    },
    {
      "from": "00e4fec9"
    },
    {
      "from": "00e4fed9"
    },
    {
      "from": "00e4fef8"
    },
    {
      "from": "00e810f0"
    },
    {
      "from": "00e810ff"
    },
    {
      "from": "00ef10e7"
    },
    {
      "from": "010031e3"
    },
    {
      "from": "010031ee"
    },
    {
      "from": "00fe6651"
    },
    {
      "from": "00fe5b0a"
    },
    {
      "from": "00fe3cd1"
    },
    {
      "from": "010076de"
    },
    {
      "from": "00e17a64"
    },
    {
      "from": "00e75be7"
    },
    {
      "from": "00e75bf2"
    },
    {
      "from": "00b6f82c"
    },
    {
      "from": "00b6f839"
    },
    {
      "from": "00cd3683"
    },
    {
      "from": "00cd3690"
    },
    {
      "from": "0100d00e"
    },
    {
      "from": "0100d019"
    },
    {
      "from": "00e55380"
    },
    {
      "from": "00e5538b"
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
  "global:0x0167eb60"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg01_roots/canonical_roots.cpp",
  "files": [
    "src/reconstruction/pkg01_roots/canonical_roots.cpp",
    "src/reconstruction/pkg01_roots/canonical_roots.hpp",
    "src/reconstruction/pkg01_roots/canonical_roots_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg01-roots/00b3d400.json"
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
    "No runtime trace establishes value equality with DAT_0167eae0 across the lifecycle; physical separation does not establish inequality of values.",
    "No runtime trace establishes when DAT_0167eb60 is published, replaced, invalidated, cleared, or unpublished.",
    "The borrowed return has no accessor-side generation, liveness, or teardown guarantee.",
    "gate-space-root-publication"
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
  "OpaqueCanonicalNounManager",
  "OpaqueCanonicalNounManager*"
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
      "0x00b3d300",
      "0x00b3d400",
      "0x00b3d2a0",
      "0x00b3d3a0",
      "0x00b5b800",
      "0xffffffff",
      "0x00b3d300",
      "0x00b3d2a0",
      "0x00b3d400",
      "0x00b3d3a0",
      "0x00b5b800"
    ],
    "conflict_id": "CF-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-f-cross-domain-impact.json",
    "subject": null,
    "unresolved_reason": {
      "missing_evidence": [
        "Direct or indirect publisher and teardown evidence for both alternate/canonical manager slot pairs.",
        "Pointer-equality checks across mode and service lifecycle boundaries.",
        "The concrete receiver class and physical storage type behind DAT_0167eaec and forwarded_object+0x20."
      ],
      "status": "blocked"
    }
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
  }
]
```
