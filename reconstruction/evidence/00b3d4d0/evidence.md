# Evidence 0x00b3d4d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2c93b93ed5d0e0829c53f03f20d3affafec9f26000430ee61dea53e6e140504f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__cdecl",
  "return_register": "EAX",
  "return_type": "OpaqueSpaceTradingService*",
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
  "content_sha256": "5c2292a0fc374d8e37e193d94fd8d578b0a808ea04150d83cb085577b6fdc642",
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
      "at": "0x00b3d4d0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb50]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d4d5",
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
    "va": "0x00b3d4d0"
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
    "va": "0x00ace5a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ad2650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ad2ae0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ad6f40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae3b30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae6240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae9f50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b19290"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b5e9a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b69990"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b69aa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6dbd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b7b070"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b998a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd7e40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd9060"
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
  "count": 2,
  "instructions": [
    {
      "address": "00b3d4d0",
      "instruction": "MOV EAX,[0x0167eb50]"
    },
    {
      "address": "00b3d4d5",
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
  "original_bytes": 15528,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__cdecl\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"OpaqueSpaceTradingService*\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 10,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 10,\n      \"symbol\": \"FUN_00b3d400\",\n      \"va\": \"0x00b3d400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00ff3f00\",\n      \"va\": \"0x00ff3f00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_01021080\",\n      \"va\": \"0x01021080\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_01021230\",\n      \"va\": \"0x01021230\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Unconditional read of the cSpaceTrading service slot 0x0167eb50; no trading operation, ownership operation, or runtime publication claim.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueSpaceTradingService\",\n  \"cluster\": null,\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ace5a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad2650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad2ae0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad6f40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae3b30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae6240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9f50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b19290\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5e9a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b69990\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b69aa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6dbd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b7b070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b998a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd7e40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd9060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be92e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c00b00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c02cb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1a3c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c28b40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c2f690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c2f7e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c3ae70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c3c520\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5ff50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c60120\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c6d7c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c82d50\"\n      },\n      {\n        \"name\": null,\n        \"rec
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
  "body_end": "00b3d4d5",
  "body_span_bytes": 6,
  "body_start": "00b3d4d0",
  "callees": [],
  "callers": [
    "FUN_00d40ff0",
    "FUN_00dec020",
    "FUN_00e73f60",
    "FUN_00e53c20",
    "FUN_00ad2650",
    "FUN_0100a7c0",
    "FUN_00d41560",
    "FUN_00e806b0",
    "FUN_01008910",
    "FUN_00e18dd0",
    "FUN_01016e50",
    "FUN_0106b630",
    "FUN_00e50f30",
    "FUN_00bd9060",
    "FUN_00c3c520",
    "FUN_00deb930",
    "FUN_00b69990",
    "FUN_00b6dbd0",
    "FUN_00f0e520",
    "FUN_00c3ae70",
    "FUN_00cf93b0",
    "FUN_00d40e70",
    "FUN_00de4720",
    "FUN_0105c5d0",
    "FUN_00d522c0",
    "FUN_00d4cb70",
    "FUN_00ffe860",
    "FUN_00c28b40",
    "FUN_00cfbc10",
    "FUN_00fdba50",
    "FUN_00e01390",
    "FUN_00e78de0",
    "FUN_00e64a00",
    "FUN_00cdab10",
    "FUN_00e7cbb0",
    "FUN_00cdcf70",
    "FUN_0106cc70",
    "FUN_00c5ff50",
    "FUN_01003df0",
    "FUN_01041c50",
    "FUN_00ae3b30",
    "FUN_00cc6910",
    "FUN_00ef25a0",
    "FUN_00bd7e40",
    "FUN_00de44f0",
    "FUN_0106a7b0",
    "FUN_00ad2ae0",
    "FUN_01002f30",
    "FUN_0105c3d0",
    "FUN_00e794f0",
    "FUN_00ff62d0",
    "FUN_010691e0",
    "FUN_00cd4280",
    "FUN_00fdfbc0",
    "FUN_00e72ac0",
    "FUN_00cf9ba0",
    "FUN_00fe0f40",
    "FUN_00e62500",
    "FUN_00d389d0",
    "FUN_01044640",
    "FUN_00fe5a20",
    "FUN_00e600a0",
    "FUN_00cdbd20",
    "FUN_00c00b00",
    "FUN_00ae6240",
    "FUN_00d3fcf0",
    "FUN_00be88d0",
    "FUN_00eb6760",
    "FUN_00ae9f50",
    "FUN_00fe6490",
    "FUN_00f10bd0",
    "FUN_00fe8990",
    "FUN_00be92e0",
    "FUN_00d7a3e0",
    "FUN_00b5e9a0",
    "FUN_00e07e70",
    "FUN_00ebb8b0",
    "FUN_00ff74f0",
    "FUN_00e79720",
    "FUN_01053d50",
    "FUN_00e6e8c0",
    "FUN_00efa1b0",
    "FUN_00b998a0",
    "FUN_00d5b0c0",
    "FUN_00b7b070",
    "FUN_010743a0",
    "FUN_0105f2d0",
    "FUN_00c6d7c0",
    "FUN_00e6eb60",
    "FUN_00e77930",
    "FUN_00d5fb60",
    "FUN_00ff6200",
    "FUN_00d4e4a0",
    "FUN_00cf8160",
    "FUN_0106ba00",
    "FUN_00d6ce10",
    "FUN_00fff6a0",
    "FUN_00e35370",
    "FUN_00fdade0",
    "FUN_00fff8e0",
    "FUN_00f1f180",
    "FUN_00fdda10",
    "FUN_00e50940",
    "FUN_00ffcab0",
    "FUN_00d35190",
    "FUN_00e6ecb0",
    "FUN_00b19290",
    "FUN_00cf7a90",
    "FUN_01060df0",
    "FUN_00c82d50",
    "FUN_00ad6f40",
    "FUN_00e50400",
    "FUN_00cda370",
    "FUN_00e62440",
    "FUN_00ce48f0",
    "FUN_00ff5ee0",
    "FUN_00e4f660",
    "FUN_00fdabf0",
    "FUN_00b69aa0",
    "FUN_0102df20",
    "FUN_00ef2fe0",
    "FUN_00f0a1e0",
    "FUN_00d3cdc0",
    "FUN_00ceb710",
    "FUN_00d40230",
    "FUN_00d2b720",
    "FUN_0101b670",
    "FUN_0102d1b0",
    "UTFWin::Window::GetCommandID",
    "FUN_00ace5a0",
    "FUN_00f05b00",
    "FUN_00f1a120",
    "FUN_00e72060",
    "FUN_00e7d880",
    "FUN_00f0a440",
    "FUN_01044360",
    "FUN_00c60120",
    "FUN_00d30830",
    "FUN_00e510f0",
    "FUN_01000520",
    "FUN_00d9cf70",
    "FUN_00e72200",
    "FUN_0100a960",
    "FUN_00c1a3c0",
    "FUN_00d400e0",
    "FUN_00fe3d30",
    "FUN_00e7b410",
    "FUN_00d5ef80",
    "FUN_00f1faa0",
    "FUN_00e7f5a0",
    "FUN_00d38e60",
    "FUN_00e34e00",
    "FUN_00ccefb0",
    "FUN_00c02cb0",
    "FUN_00c2f690",
    "FUN_00d43e30"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d4d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::cSpaceTrading::Get",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "cSpaceTrading *",
  "return_type_resolved": true,
  "rva": "0x73d4d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "cSpaceTrading * Simulator::cSpaceTrading::Get(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d4d0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00fe8993"
    },
    {
      "from": "00d5fc05"
    },
    {
      "from": "00d5b35c"
    },
    {
      "from": "00d5b39e"
    },
    {
      "from": "00cf7a90"
    },
    {
      "from": "00cf7aa2"
    },
    {
      "from": "00cf7ab3"
    },
    {
      "from": "00d5efa1"
    },
    {
      "from": "00ace842"
    },
    {
      "from": "00ad6f6c"
    },
    {
      "from": "00ad6fad"
    },
    {
      "from": "00ad6fee"
    },
    {
      "from": "00ad702f"
    },
    {
      "from": "00ad7070"
    },
    {
      "from": "00ad70b1"
    },
    {
      "from": "00ad70f5"
    },
    {
      "from": "00ad7136"
    },
    {
      "from": "00ae3d03"
    },
    {
      "from": "00ae63f1"
    },
    {
      "from": "00be95c2"
    },
    {
      "from": "00be960f"
    },
    {
      "from": "00be978f"
    },
    {
      "from": "00be97b6"
    },
    {
      "from": "00be8e76"
    },
    {
      "from": "00bd9084"
    },
    {
      "from": "00aea139"
    },
    {
      "from": "00c00d48"
    },
    {
      "from": "00c00d5f"
    },
    {
      "from": "00cf9d98"
    },
    {
      "from": "00cf9db3"
    },
    {
      "from": "0102e61e"
    },
    {
      "from": "0102e639"
    },
    {
      "from": "0102e675"
    },
    {
      "from": "0102d50a"
    },
    {
      "from": "01041c5a"
    },
    {
      "from": "01041ca7"
    },
    {
      "from": "010448fa"
    },
    {
      "from": "00b19378"

[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x0167eb50"
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
    "reconstruction/metadata/pkg01-roots/00b3d4d0.json"
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
    "No runtime trace establishes value equality with another root or service slot; physical separation does not establish inequality of values.",
    "No runtime trace establishes when DAT_0167eb50 is published, replaced, invalidated, cleared, or unpublished.",
    "The borrowed return has no accessor-side generation, liveness, or teardown guarantee.",
    "This getter does not validate or implement trading operations; trade requests, offers, acceptance, inventory, commodity, and economy boundaries remain unvalidated.",
    "gate-space-trading-lifecycle"
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
  "OpaqueSpaceTradingService",
  "OpaqueSpaceTradingService*"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
