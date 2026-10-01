# Evidence 0x00b5b960

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a434dd6f5ccc99ae53c84f2984bd0281c77990ac7a7333d1e5804df5e1ebca9f`

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
  "content_sha256": "2f77c74349a776d086d14a98709712b54ced1385364c9d3a3ee5cace601ec157",
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
        "obs-0007"
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
        "obs-0002",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4,
          8,
          12,
          16,
          20,
          24
        ],
        "register": "ECX",
        "written_through": 8
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0006",
        "obs-0007"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0007"
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
        "obs-0007"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0007"
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
      "at": "0x00b5b960",
      "count": 4,
      "first_use": 0,
      "first_write_index": 4,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b5b960",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ECX",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b5b962",
      "count": 8,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EAX + 0x4],0x13ef094",
      "reg": "EAX"
    },
    {
      "at": "0x00b5b969",
      "count": 3,
      "first_use": 2,
      "first_write_index": 2,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "XOR EDX,EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00b5b969",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "XOR EDX,EDX",
      "reg": "EDX",
      "write_kind": "zero"
    },
    {
      "at": "0x00b5b96e",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "OR ECX,0xffffffff",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x00b5b98a",
      "form": "RET",
      "id": "obs-0007",
      "imm": null,
      "index": 11,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 12,
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
    "confidence": "SUPPORTED",
    "distinct_offsets": 7,
    "max_offset": 24,
    "offsets": [
      0,
      4,
      8,
      12,
      16,
      20,
      24
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-ALIAS",
    "written_through": 8
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
    "eax_holds_slot0_at_ret": nu
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
    "va": "0x00ac0c70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac4c20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac6b90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ac78a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00acf230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00adf420"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae7f00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aebde0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b0bdb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b0d8d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b1c2c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b1d870"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b232b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b26e10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2d480"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b31ea0"
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
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b5b960",
      "0x00b1d870",
      "0x00b1d870",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b267f0",
      "0x00b267f0",
      "0x00b5b840",
      "0x00b5b840",
      "0x00b5b880"
    ],
    "conflict_id": "game_mode_identifier_domain",
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
      "0x00b1db60",
      "0x00b5b880",
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b1db60",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021960",
      "0x01021960",
      "0x01021d40"
    ],
    "conflict_id": "simulator_mode_identifier_mapping",
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
  "count": 12,
  "instructions": [
    {
      "address": "00b5b960",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "00b5b962",
      "instruction": "MOV dword ptr [EAX + 0x4],0x13ef094"
    },
    {
      "address": "00b5b969",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00b5b96b",
      "instruction": "MOV dword ptr [EAX + 0x8],EDX"
    },
    {
      "address": "00b5b96e",
      "instruction": "OR ECX,0xffffffff"
    },
    {
      "address": "00b5b971",
      "instruction": "MOV dword ptr [EAX],0x1461580"
    },
    {
      "address": "00b5b977",
      "instruction": "MOV dword ptr [EAX + 0x4],0x1461578"
    },
    {
      "address": "00b5b97e",
      "instruction": "MOV dword ptr [EAX + 0xc],ECX"
    },
    {
      "address": "00b5b981",
      "instruction": "MOV dword ptr [EAX + 0x10],ECX"
    },
    {
      "address": "00b5b984",
      "instruction": "MOV dword ptr [EAX + 0x14],ECX"
    },
    {
      "address": "00b5b987",
      "instruction": "MOV dword ptr [EAX + 0x18],EDX"
    },
    {
      "address": "00b5b98a",
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
  "original_bytes": 16356,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"fastcall-compatible one-argument ECX function\",\n    \"hidden_receiver\": \"ECX is the receiver pointer\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"RET\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H3-HELPER-WAVE2\",\n      \"score\": 10,\n      \"symbol\": \"embedded_object_first_word_init_00743b50\",\n      \"va\": \"0x00743b50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-H3-HELPER-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"noun_manager_logical_destroy_00b225d0\",\n      \"va\": \"0x00b225d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 2,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 2,\n      \"symbol\": \"context_word_read_00ce6950\",\n      \"va\": \"0x00ce6950\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueStrategyBaseWire\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac0c70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac4c20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac6b90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac78a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acf230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00adf420\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae7f00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebde0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b0bdb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b0d8d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b1c2c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b1d870\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b232b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b26e10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2d480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b31ea0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b379f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b4d220\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5e260\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b60d80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b71dc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b79740\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b7df80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b863e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b8ff90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba2250\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba3ef0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bae490\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbf1f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bc7380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd7010\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd9a10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf98b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cfecc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d1c150\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d3b9b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false
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
  "body_end": "00b5b98a",
  "body_span_bytes": 43,
  "body_start": "00b5b960",
  "callees": [],
  "callers": [
    "FUN_00b5e260",
    "FUN_00ae7f00",
    "FUN_00ba2250",
    "FUN_00b0d8d0",
    "FUN_00bae490",
    "FUN_00b31ea0",
    "FUN_00cd9a10",
    "FUN_00b60d80",
    "FUN_00fdca00",
    "FUN_00e30c60",
    "FUN_00b232b0",
    "FUN_00b2d480",
    "FUN_00b8ff90",
    "FUN_00dd7020",
    "FUN_00b79740",
    "FUN_00ac0c70",
    "FUN_00d1c150",
    "FUN_00b1c2c0",
    "FUN_0104f960",
    "FUN_00b863e0",
    "FUN_00ba3ef0",
    "FUN_00bbf1f0",
    "FUN_00ac6b90",
    "FUN_00adf420",
    "FUN_00aebde0",
    "FUN_00b1d870",
    "FUN_00e19680",
    "FUN_00d3b9b0",
    "FUN_00b0bdb0",
    "FUN_00b71dc0",
    "FUN_00cf98b0",
    "FUN_00b379f0",
    "FUN_00bc7380",
    "FUN_00bd7010",
    "FUN_00e43830",
    "FUN_010378f0",
    "FUN_00b4d220",
    "FUN_0103b690",
    "FUN_00ac4c20",
    "FUN_00b26e10",
    "FUN_00acf230",
    "FUN_00b7df80",
    "FUN_00cfecc0",
    "FUN_00e173d0",
    "FUN_00f39df0",
    "FUN_00ac78a0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00b5b960",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b5b960",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x75b960",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b5b960(void)",
  "size_bytes": 43,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b5b960",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 46,
  "xrefs": [
    {
      "from": "00ac0c73"
    },
    {
      "from": "00ac4c2f"
    },
    {
      "from": "00ac6b93"
    },
    {
      "from": "00ac78a3"
    },
    {
      "from": "00acf234"
    },
    {
      "from": "00adf430"
    },
    {
      "from": "00ae7f03"
    },
    {
      "from": "00aebde3"
    },
    {
      "from": "00b0bdc0"
    },
    {
      "from": "00b0d8e3"
    },
    {
      "from": "00b1c2df"
    },
    {
      "from": "00b1d873"
    },
    {
      "from": "00b232bf"
    },
    {
      "from": "00b26e1f"
    },
    {
      "from": "00b2d48f"
    },
    {
      "from": "00b31ea3"
    },
    {
      "from": "00b37a06"
    },
    {
      "from": "00b5e263"
    },
    {
      "from": "00b622cb"
    },
    {
      "from": "00b4d231"
    },
    {
      "from": "00b71dc3"
    },
    {
      "from": "00b79750"
    },
    {
      "from": "00b7df91"
    },
    {
      "from": "00b863f0"
    },
    {
      "from": "00b8ff93"
    },
    {
      "from": "00ba2253"
    },
    {
      "from": "00ba3eff"
    },
    {
      "from": "00bae494"
    },
    {
      "from": "00bbf1f3"
    },
    {
      "from": "00bc7389"
    },
    {
      "from": "00bd701f"
    },
    {
      "from": "00cfecc3"
    },
    {
      "from": "00dd7031"
    },
    {
      "from": "00e173d3"
    },
    {
      "from": "00e19692"
    },
    {
      "from": "00e30c64"
    },
    {
      "from": "00e43849"
    },
    {
      "from": "00f39df3"
    },
    {
      "from": "010378f4"
    },
    {
      "from": "0103b693"
    },
    {
      "from": "0104f966"
    },
    {
      "from": "00cf98c0"
    },
    {
      "from": "00d1c166"
    },
    {
      "from": "00d3b9c7"
    },
    {
      "from": "00fdca17"
    },
    {
      "from": "00cd9a2f"
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
    "reconstruction/metadata/pkg11-h3-helper-wave2/00b5b960.json"
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
    "gate-strategy-base-constructor-00b5b960",
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
  "OpaqueStrategyBaseWire",
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
    "anchors": [
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b5b960",
      "0x00b1d870",
      "0x00b1d870",
      "0x00b1db60",
      "0x00b1db60",
      "0x00b1dbd0",
      "0x00b1dbd0",
      "0x00b267f0",
      "0x00b267f0",
      "0x00b5b840",
      "0x00b5b840",
      "0x00b5b880"
    ],
    "conflict_id": "game_mode_identifier_domain",
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
      "0x00b1db60",
      "0x00b5b880",
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b1db60",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021960",
      "0x01021960",
      "0x01021d40"
    ],
    "conflict_id": "simulator_mode_identifier_mapping",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "derived": "__thiscall",
    "field": "calling_convention",
    "kind": "derived_vs_persisted",
    "persisted": "fastcall-compatible one-argument ECX function",
    "resolution_status": "unresolved"
  }
]
```
