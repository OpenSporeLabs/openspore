# Evidence 0x00b3d480

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `684ee707f935d6d27ad04c1af7a40293c06383b617e54817f5df9a17d7efd86e`

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
  "return_note": "opaque 32-bit game-time-manager pointer",
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
  "content_sha256": "f853608a16fcfde5047c916fab283f9b1952e62001a377378a8fb26645bf53ba",
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
      "at": "0x00b3d480",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb3c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d485",
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
    "va": "0x00b3d480"
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
    "va": "0x00b32b20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32ce0"
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
    "va": "0x00b33130"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bcd690"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd7e40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd7ea0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd7f30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd9060"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bdff50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be1150"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be11f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be6f60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be6f90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be88d0"
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
      "0x00b3d480",
      "0x00b3d480",
      "0x00b31da0",
      "0x00b321e0",
      "0x005c7d00",
      "0x005c7cb0",
      "0x005c7f10",
      "0x005c7f70",
      "0x00b32330",
      "0x00b32560",
      "0x00b63980",
      "0x00b32390",
      "0x00b32330",
      "0x00b32560",
      "0x00e63560",
      "0x005c7d00"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:2",
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
      "address": "00b3d480",
      "instruction": "MOV EAX,[0x0167eb3c]"
    },
    {
      "address": "00b3d485",
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
  "original_bytes": 14882,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"hidden_receiver\": null,\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"RET\",\n    \"return_note\": \"opaque 32-bit game-time-manager pointer\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-WAVE6-MISC-ENGINE\",\n      \"score\": 8,\n      \"symbol\": \"message_manager_get_queue_0098f4d0\",\n      \"va\": \"0x0098f4d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-WAVE6-MISC-ENGINE\",\n      \"score\": 8,\n      \"symbol\": \"destructible_lifecycle_thunk_00b63980\",\n      \"va\": \"0x00b63980\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"app_cheat_manager_get_0067dde0\",\n      \"va\": \"0x0067dde0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"app_id_generator_get_007c79e0\",\n      \"va\": \"0x007c79e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 2,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 2,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 2,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 2,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The absolute slot read and unchanged pointer return are exact; concrete manager, publisher, clock state, and pointer lifetime remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueGameTimeManager\",\n  \"cluster\": null,\n  \"confidence\": 0.96,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32ce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32f60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33130\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bcd690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd7e40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd7ea0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd7f30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd9060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdff50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be1150\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be11f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be6f60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be6f90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00beb090\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c099e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c09fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4ccd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4d050\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c504a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c56000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c737a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c830f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c95ee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cc22c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cde660\"\n   
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
  "body_end": "00b3d485",
  "body_span_bytes": 6,
  "body_start": "00b3d480",
  "callees": [],
  "callers": [
    "FUN_00c95ee0",
    "FUN_00c737a0",
    "FUN_00cc22c0",
    "FUN_00d5cfd0",
    "FUN_00d695a0",
    "FUN_01030fd0",
    "FUN_00d5c720",
    "FUN_00be11f0",
    "FUN_00feff80",
    "FUN_00fefbb0",
    "FUN_00d57940",
    "FUN_00bd9060",
    "FUN_00be6f60",
    "FUN_00d5fb60",
    "FUN_00c56000",
    "FUN_00d5bfa0",
    "FUN_00bdff50",
    "FUN_00db7050",
    "FUN_00d5b8d0",
    "FUN_00d9c6f0",
    "FUN_00b32f60",
    "FUN_00d697a0",
    "FUN_00c504a0",
    "FUN_00b33130",
    "FUN_00d60f00",
    "FUN_00c4ccd0",
    "FUN_00cfbc10",
    "FUN_00d51c30",
    "FUN_00e3ede0",
    "FUN_00be1150",
    "FUN_00ffa2c0",
    "FUN_00c09fa0",
    "FUN_00c099e0",
    "FUN_00d4ee20",
    "FUN_00ff5720",
    "FUN_01043fd0",
    "FUN_00d50a40",
    "FUN_01003690",
    "FUN_00bd7e40",
    "FUN_00bd7ea0",
    "FUN_00bcd690",
    "FUN_00beb090",
    "FUN_00d51540",
    "FUN_00b32ce0",
    "FUN_00c4d050",
    "FUN_00b32b20",
    "FUN_00b32dd0",
    "FUN_00d50ef0",
    "FUN_00d9e250",
    "FUN_00ff9800",
    "FUN_00ff5b50",
    "FUN_00fe2ab0",
    "FUN_0100a960",
    "FUN_00c830f0",
    "FUN_0105a110",
    "FUN_00be88d0",
    "FUN_00be6f90",
    "FUN_00bd7f30",
    "FUN_00e43710",
    "FUN_00cde660",
    "FUN_00d43e30"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d480",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::cGameTimeManager::Get",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "cGameTimeManager *",
  "return_type_resolved": true,
  "rva": "0x73d480",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "cGameTimeManager * Simulator::cGameTimeManager::Get(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d480",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00c738f6"
    },
    {
      "from": "00d60f48"
    },
    {
      "from": "00d610b4"
    },
    {
      "from": "00d57980"
    },
    {
      "from": "00d5b8ea"
    },
    {
      "from": "00d5b960"
    },
    {
      "from": "00d5c018"
    },
    {
      "from": "00d5c736"
    },
    {
      "from": "00d6083e"
    },
    {
      "from": "00c09fca"
    },
    {
      "from": "00c0a1be"
    },
    {
      "from": "00c09a11"
    },
    {
      "from": "00be12fd"
    },
    {
      "from": "00beb1a6"
    },
    {
      "from": "00be8e0f"
    },
    {
      "from": "00be8e89"
    },
    {
      "from": "00bd9097"
    },
    {
      "from": "00be11bb"
    },
    {
      "from": "00b32b56"
    },
    {
      "from": "00b32b62"
    },
    {
      "from": "00b32cf6"
    },
    {
      "from": "00b32d02"
    },
    {
      "from": "0100adf5"
    },
    {
      "from": "00ffa3ec"
    },
    {
      "from": "00ffa3f8"
    },
    {
      "from": "00b32e02"
    },
    {
      "from": "00b32fa8"
    },
    {
      "from": "00bd7e6c"
    },
    {
      "from": "00bd7eb8"
    },
    {
      "from": "00bdff56"
    },
    {
      "from": "00be6f76"
    },
    {
      "from": "00be6fb4"
    },
    {
      "from": "00ff9cf0"
    },
    {
      "from": "00ff9e17"
    },
    {
      "from": "00ff9f79"
    },
    {
      "from": "010037c7"
    },
    {
      "from": "01044059"
    },
    {
      "from": "00c4cdd4"
    },
    {
      "from": "00feff97"
    },
    {
      "from": "00c4d100"
    },
    {
      "from": "00fefbb3"
    },
    {
      "from": "00c50555"
    },
    {
      "from": "00c5607e"
    },
    {
      "from": "00c837ae"
    },
    {
      "from": "00c95fa8"
    },
    {
      "from": "00cc2621"
    },
    {
      "from": "00bd7f31"
    },
    {
      "from": "00d4efce"
    },
    {
      "from": "00d50ab8"
    },
    {
      "from": "00d5118d"
    },
    {
      "from": "00d515b0"
    },
    {
      "from": "00d520e8"
    },
    {
      "from": "00d521cc"
    },
    {
      "from": "00d522a2"
    },
    {
      "from": "00d5cfd9"
    },
    {
      "from": "00d6967a"
    },
    {
      "from": "00d69c10"
    },
    {
      "from": "00d69c27"
    },
    {
      "from": "00d9c766"
    },
    {
      "from": "00d9e401"
    },
    {
      "from": "00db7160"
    },
    {
      "from": "00fe2b63"
    },
    {
      "from": "00fe2d25"
    },
    {
      "from": "00ff57fe"
    },
    {
      "from": "00ff5b50"
    },
    {
      "from": "0103174b"
    },
    {
      "from": "0105a31c"
    },
    {
      "from": "00cfc996"
    },
    {
      "from": "00cfccb3"
    },
    {
      "from": "00b331ac"
    },
    {
      "from": "00b331f9"
    },
    {
      "from": "00b33245"
    },
    {
      "from": "00b33252"
    },
    {
      "from": "00b33293"
    },
    {
      "from": "00b332a0"
    },
    {
      "from": "00d450b8"
    },
    {
      "from": "00cde941"
    },
    {
      "from": "00e3edef"
    },
    {
      "from": "00e43723"
    },
    {
      "from": "00d78684"
    },
    {
      "from": "00b24502"
    },
    {
      "from": "00bcd85d"
    },
    {
      "from": "00bd0b4c"
    },
    {
      "from": "00c03140"
    },
    {
      "from": "00c235a9"
    },
    {
      "from": "00cabc83"
    },
    {
      "from": "00cdf2ba"
    },
    {
      "from": "00cdf589"
    
[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:MOV EAX,[0x0167eb3c]",
  "global:get_xrefs_to(0x0167eb3c); one read xref from this function"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_misc_engine/misc_engine.cpp",
  "files": [
    "reconstruction/staging/wave6-misc-engine/misc_engine.cpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine.hpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp",
    "src/reconstruction/wave6_misc_engine/misc_engine.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-misc-engine/00b3d480.json"
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
    "gate-game-time-manager-slot-publication"
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
  "OpaqueGameTimeManager",
  "opaque 32-bit game-time-manager pointer"
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
      "0x00b3d480",
      "0x00b3d480",
      "0x00b31da0",
      "0x00b321e0",
      "0x005c7d00",
      "0x005c7cb0",
      "0x005c7f10",
      "0x005c7f70",
      "0x00b32330",
      "0x00b32560",
      "0x00b63980",
      "0x00b32390",
      "0x00b32330",
      "0x00b32560",
      "0x00e63560",
      "0x005c7d00"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:2",
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
