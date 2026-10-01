# Evidence 0x00743b50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `14ef9f4011f4c41a0bc9c265d59b375a395be0cd6690d556812cc70c4e41c111`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "fastcall-compatible one-argument ECX function",
  "hidden_receiver": "ECX is the receiver pointer",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "RET",
  "return_type": "void",
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "a5422953c931452af97126188c1b13a99225b4d65c655d9a86f6464a09abed39",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
    "persisted_calling_convention": "fastcall-compatible one-argument ECX function"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0004"
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
        "obs-0001",
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0004"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0004"
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
        "obs-0004"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0004"
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
      "at": "0x00743b50",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00743b50",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ECX",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x00743b52",
      "count": 1,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EAX],0x0",
      "reg": "EAX"
    },
    {
      "at": "0x00743b58",
      "form": "RET",
      "id": "obs-0004",
      "imm": null,
      "index": 2,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 3,
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
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 0,
    "offsets": [
      0
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-ALIAS",
    "written_through": 1
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
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
    "instructions": 3,
    "syntax": "intel",
    "va": "0x00743b50"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_INFERRED"
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
    "va": "0x0068f600"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0092f960"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00943a30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00946540"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00a33600"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b46ff0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6a530"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4c8c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4f040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4f100"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4f330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4f860"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4f9d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4fc20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4fca0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4ff10"
  }
]
```

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
  "count": 3,
  "instructions": [
    {
      "address": "00743b50",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "00743b52",
      "instruction": "MOV dword ptr [EAX],0x0"
    },
    {
      "address": "00743b58",
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
  "original_bytes": 16381,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"fastcall-compatible one-argument ECX function\",\n    \"hidden_receiver\": \"ECX is the receiver pointer\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"RET\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H3-HELPER-WAVE2\",\n      \"score\": 10,\n      \"symbol\": \"strategy_base_constructor_00b5b960\",\n      \"va\": \"0x00b5b960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-H3-HELPER-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"noun_manager_logical_destroy_00b225d0\",\n      \"va\": \"0x00b225d0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"cell_move_player_to_mouse_position_00e5b790\",\n      \"va\": \"0x00e5b790\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 3,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00e780a0\",\n      \"va\": \"0x00e780a0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00e7a4a0\",\n      \"va\": \"0x00e7a4a0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00e7a7c0\",\n      \"va\": \"0x00e7a7c0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00e7fd00\",\n      \"va\": \"0x00e7fd00\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEmbeddedObject\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0068f600\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0092f960\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00943a30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00946540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a33600\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b46ff0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6a530\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4c8c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4f040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4f100\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4f330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4f860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4f9d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4fc20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4fca0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4ff10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4ffe0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e50020\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e50060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e503a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e50680\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e50810\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e50990\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e50af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e52060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e52960\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e52b70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e52d80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\":
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
  "body_end": "00743b58",
  "body_span_bytes": 9,
  "body_start": "00743b50",
  "callees": [],
  "callers": [
    "Simulator::Cell::GetCurrentAdvectInfo",
    "FUN_00e4fca0",
    "Simulator::Cell::cCellGame::Initialize",
    "FUN_00e4f9d0",
    "FUN_00e67610",
    "FUN_00a33600",
    "FUN_00e71520",
    "Simulator::Cell::GetNextAdvectID",
    "FUN_00e6fbb0",
    "FUN_00e6d8f0",
    "FUN_00e707d0",
    "App::cCellModeStrategy::OnMouseDown",
    "FUN_00e7add0",
    "FUN_00e78fc0",
    "FUN_00e55080",
    "Simulator::Cell::cCellGFX::LoadEffectMap",
    "FUN_00b46ff0",
    "Simulator::Cell::ShouldNotAttack",
    "FUN_00e5ce90",
    "FUN_00e5ec70",
    "FUN_00e7b5d0",
    "FUN_00e6c330",
    "FUN_00e50020",
    "FUN_00e52d80",
    "FUN_00e819b0",
    "FUN_00e78d10",
    "FUN_00e6b500",
    "Simulator::Cell::cCellGFX::PreloadResources",
    "FUN_00e50060",
    "FUN_00e7b630",
    "FUN_00e64a00",
    "FUN_00e56b50",
    "FUN_00e7a7c0",
    "FUN_00e7c6c0",
    "FUN_00e7cbb0",
    "FUN_00e576f0",
    "Simulator::Cell::cCellGFX::PreloadPopulateResource",
    "FUN_00e6fce0",
    "FUN_00e549b0",
    "FUN_00e62120",
    "FUN_00e771d0",
    "FUN_00e7d760",
    "FUN_00e71ce0",
    "FUN_00e4f330",
    "FUN_00e52060",
    "FUN_00e5a1a0",
    "FUN_00e50af0",
    "Simulator::Cell::CreateCellObject",
    "FUN_00e68470",
    "FUN_00e56e50",
    "FUN_00e611b0",
    "FUN_00e4c8c0",
    "FUN_00e79320",
    "FUN_00943a30",
    "FUN_00e647d0",
    "FUN_00e4f040",
    "FUN_00e61aa0",
    "FUN_00e7c500",
    "FUN_00e777a0",
    "FUN_00e65ad0",
    "FUN_00e6eec0",
    "FUN_00e61d90",
    "FUN_00e575f0",
    "FUN_00e5d2b0",
    "FUN_00e50680",
    "FUN_00e57560",
    "FUN_0068f600",
    "FUN_00e6e8c0",
    "FUN_00e7c8c0",
    "FUN_00e70650",
    "FUN_00e75900",
    "FUN_00e4ff10",
    "FUN_00e4f100",
    "FUN_00e7a4a0",
    "FUN_00e780a0",
    "FUN_00e67330",
    "FUN_00e6b180",
    "FUN_00e52960",
    "FUN_00e50990",
    "FUN_00e56dc0",
    "FUN_00e78830",
    "FUN_00e4fc20",
    "FUN_0113df10",
    "FUN_00e5c250",
    "FUN_00e7fd00",
    "Simulator::Cell::cCellGFX::PreloadCellResource",
    "FUN_00e61630",
    "Simulator::Cell::GetModelKeyForCellResource",
    "FUN_00e7ce10",
    "FUN_00e7b7c0",
    "FUN_00e4ffe0",
    "FUN_00e503a0",
    "FUN_00e5c9d0",
    "FUN_00e54d30",
    "FUN_00e7f140",
    "FUN_00e6fd70",
    "FUN_00e4f860",
    "FUN_00e62b80",
    "FUN_00e750c0",
    "FUN_00e7d880",
    "FUN_00e6a3f0",
    "FUN_00e646d0",
    "FUN_00e5d7b0",
    "FUN_00e56200",
    "FUN_00b6a530",
    "FUN_00e56300",
    "FUN_00946540",
    "FUN_00e7d070",
    "FUN_00e5ae80",
    "FUN_00e52b70",
    "FUN_00e71f00",
    "FUN_00e6f990",
    "FUN_0092f960",
    "FUN_00f20fe0",
    "FUN_00e53460",
    "FUN_00e57e10",
    "FUN_00e59d90",
    "FUN_00e57910",
    "FUN_00e760f0",
    "FUN_00ebf160",
    "FUN_00e50810",
    "FUN_00e792b0",
    "FUN_00e5a430",
    "Simulator::Cell::MovePlayerToMousePosition",
    "FUN_00e67890"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00743b50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00743b50",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x343b50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00743b50(void)",
  "size_bytes": 9,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00743b50",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00a33656"
    },
    {
      "from": "0094659a"
    },
    {
      "from": "0068f655"
    },
    {
      "from": "0092f991"
    },
    {
      "from": "00943a3c"
    },
    {
      "from": "00b46ff7"
    },
    {
      "from": "00b4700a"
    },
    {
      "from": "00b6a553"
    },
    {
      "from": "00e4f10c"
    },
    {
      "from": "00e4f33c"
    },
    {
      "from": "00e4f9d8"
    },
    {
      "from": "00e4f9f5"
    },
    {
      "from": "00e4ffe6"
    },
    {
      "from": "00e50066"
    },
    {
      "from": "00e5087b"
    },
    {
      "from": "00e549b6"
    },
    {
      "from": "00e54d3f"
    },
    {
      "from": "00e55086"
    },
    {
      "from": "00e56255"
    },
    {
      "from": "00e5629e"
    },
    {
      "from": "00e563a6"
    },
    {
      "from": "00e503a4"
    },
    {
      "from": "00e57e7d"
    },
    {
      "from": "00e50689"
    },
    {
      "from": "00e506dd"
    },
    {
      "from": "00e58f01"
    },
    {
      "from": "00e5a211"
    },
    {
      "from": "00e5a230"
    },
    {
      "from": "00e5aeaf"
    },
    {
      "from": "00e5c260"
    },
    {
      "from": "00e5c9fe"
    },
    {
      "from": "00e5d2b6"
    },
    {
      "from": "00e58e3a"
    },
    {
      "from": "00e611b8"
    },
    {
      "from": "00e6163f"
    },
    {
      "from": "00e61ac2"
    },
    {
      "from": "00e61d9b"
    },
    {
      "from": "00e61dba"
    },
    {
      "from": "00e646db"
    },
    {
      "from": "00e646e3"
    },
    {
      "from": "00e646eb"
    },
    {
      "from": "00e64718"
    },
    {
      "from": "00e64723"
    },
    {
      "from": "00e6472e"
    },
    {
      "from": "00e64bd6"
    },
    {
      "from": "00e64bee"
    },
    {
      "from": "00e65649"
    },
    {
      "from": "00e65666"
   
[TRUNCATED]
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
  "file": "src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.cpp",
    "reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.hpp",
    "reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2_model_test.cpp",
    "src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.cpp",
    "src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.hpp",
    "src/reconstruction/pkg11_h3_helper_wave2/helper_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-h3-helper-wave2/00743b50.json"
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
    "gate-embedded-first-word-00743b50",
    "runtime validation not run"
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
  "OpaqueEmbeddedObject",
  "void"
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
    "derived": "__thiscall",
    "field": "calling_convention",
    "kind": "derived_vs_persisted",
    "persisted": "fastcall-compatible one-argument ECX function",
    "resolution_status": "unresolved"
  }
]
```
