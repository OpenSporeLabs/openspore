# Evidence 0x01021230

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5027f103e4bd679152b8253ec25165658614101c35cb23af29b042872ddd9ba6`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl-compatible no-argument accessor",
  "return_note": "opaque 32-bit active-star pointer word",
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
  "content_sha256": "468967391582be8539da8d664a7f2776656c8de34a73e64af35c354f25986c73",
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
        "obs-0003"
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
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
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
      "at": "0x01021230",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016dda8c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01021235",
      "count": 1,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x8]",
      "reg": "EAX"
    },
    {
      "at": "0x01021238",
      "form": "RET",
      "id": "obs-0003",
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
    "instructions": 3,
    "syntax": "intel",
    "va": "0x01021230"
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
    "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "reconstructed": true,
    "va": "0x00b28ec0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bae130"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bba4b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bcece0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c474b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5f530"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd5f70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cfa410"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d43e30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e1a040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ea5510"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fd9d30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fd9d90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fda5e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fda9f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fdc240"
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
      "address": "01021230",
      "instruction": "MOV EAX,[0x016dda8c]"
    },
    {
      "address": "01021235",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "01021238",
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
  "original_bytes": 16157,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"return_note\": \"opaque 32-bit active-star pointer word\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 24,\n      \"symbol\": \"FUN_01021080\",\n      \"va\": \"0x01021080\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 19,\n      \"symbol\": \"FUN_01021260\",\n      \"va\": \"0x01021260\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 19,\n      \"symbol\": \"FUN_010212a0\",\n      \"va\": \"0x010212a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d400\",\n      \"va\": \"0x00b3d400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cSpaceTrading_Get\",\n      \"va\": \"0x00b3d4d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Direct +0x08 active-star word read with no null guard and no AddRef/Release; concrete star subtype and replacement lifetime remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"SpacePlayerDataAccessPrefix\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b28ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bae130\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bba4b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bcece0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c474b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5f530\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd5f70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cfa410\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d43e30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e1a040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ea5510\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fd9d30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fd9d90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fda5e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fda9f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdc240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdc710\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdc800\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdd200\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdd390\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdd5a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fde3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdeac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdf5f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdfbc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe0160\"\n      },\n      {\n        \"name\": null,\n        \"reconstruc
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
  "body_end": "01021238",
  "body_span_bytes": 9,
  "body_start": "01021230",
  "callees": [],
  "callers": [
    "FUN_00d43e30",
    "FUN_00b28ec0",
    "FUN_01023be0",
    "FUN_00fe0160",
    "FUN_00c5f530",
    "FUN_0100a960",
    "FUN_00bcece0",
    "FUN_00fdc800",
    "FUN_00fde3e0",
    "FUN_00ff9800",
    "FUN_00fe3b30",
    "FUN_0101b160",
    "FUN_00fdfbc0",
    "FUN_0102d1b0",
    "FUN_00fd9d30",
    "FUN_00cd5f70",
    "FUN_01056160",
    "FUN_01008270",
    "FUN_00fda9f0",
    "FUN_00fdeac0",
    "FUN_00fe6bc0",
    "FUN_010021a0",
    "FUN_00fdd390",
    "FUN_00fda5e0",
    "FUN_00ea5510",
    "FUN_01036830",
    "FUN_00fdf5f0",
    "FUN_00ff5930",
    "FUN_00feb770",
    "FUN_0105e290",
    "FUN_0105f2d0",
    "FUN_00e1a040",
    "FUN_0102df20",
    "FUN_01003a50",
    "FUN_00bae130",
    "FUN_01058c90",
    "FUN_010362e0",
    "FUN_010091d0",
    "FUN_01004e50",
    "FUN_0100d0d0",
    "FUN_00fe0c60",
    "FUN_00cfa410",
    "FUN_00ffcab0",
    "FUN_00fe0e10",
    "FUN_01003690",
    "FUN_00fdd5a0",
    "FUN_010361c0",
    "FUN_010077e0",
    "FUN_00fea510",
    "FUN_010393a0",
    "FUN_010053c0",
    "FUN_0106a4e0",
    "FUN_00bba4b0",
    "FUN_010027b0",
    "FUN_00fdd200",
    "FUN_01011120",
    "FUN_00fdc710",
    "FUN_010175b0",
    "FUN_00c474b0",
    "FUN_00fdc240",
    "FUN_01008e60",
    "FUN_00fd9d90"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "01021230",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_01021230",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc21230",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01021230(void)",
  "size_bytes": 9,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01021230",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 80,
  "xrefs": [
    {
      "from": "00b28fa0"
    },
    {
      "from": "00fe3b62"
    },
    {
      "from": "0102e13e"
    },
    {
      "from": "0102e491"
    },
    {
      "from": "010029a3"
    },
    {
      "from": "0102d392"
    },
    {
      "from": "0103947e"
    },
    {
      "from": "00fde42c"
    },
    {
      "from": "01003a54"
    },
    {
      "from": "0100ac94"
    },
    {
      "from": "0106a57e"
    },
    {
      "from": "010362b4"
    },
    {
      "from": "0103637a"
    },
    {
      "from": "00bae245"
    },
    {
      "from": "00fdd203"
    },
    {
      "from": "00fdd3ea"
    },
    {
      "from": "00fdd40d"
    },
    {
      "from": "00fdd5c2"
    },
    {
      "from": "00fe0e2b"
    },
    {
      "from": "00ff9922"
    },
    {
      "from": "00ff593f"
    },
    {
      "from": "0100377a"
    },
    {
      "from": "01007a2a"
    },
    {
      "from": "010368cc"
    },
    {
      "from": "00c474e7"
    },
    {
      "from": "00c5f53c"
    },
    {
      "from": "00cd5f8a"
    },
    {
      "from": "00e1a0c3"
    },
    {
      "from": "010175db"
    },
    {
      "from": "00fda64d"
    },
    {
      "from": "00fe6c17"
    },
    {
      "from": "00fdc247"
    },
    {
      "from": "00fdc724"
    },
    {
      "from": "00fdc829"
    },
    {
      "from": "00fdf225"
    },
    {
      "from": "00fdf731"
    },
    {
      "from": "00fdf847"
    },
    {
      "from": "00fdfbfd"
    },
    {
      "from": "00fe0379"
    },
    {
      "from": "00fe0d2d"
    },
    {
      "from": "00ffcadf"
    },
    {
      "from": "00fea76e"
    },
    {
      "from": "00feb83e"
    },
    {
      "from": "01004edb"
    },
    {
      "from": "01005495"
    },
    {
      "from": "010054df"
    },
    {
      "from": "01008ea5"
    },
    {
      "from": "01009208"
    },
    {
      "from": "0100d151"
    },
    {
      "from": "0101117e"
    },
    {
      "from": "0101b204"
    },
    {
      "from": "01023bfb"
    },
    {
      "from": "00bba4c8"
    },
    {
      "from": "0105640c"
    },
    {
      "from": "01058cb0"
    },
    {
      "from": "0105f3a8"
    },
    {
      "from": "0105e50f"
    },
    {
      "from": "00fdaa32"
    },
    {
      "from": "00cfa470"
    },
    {
      "from": "010084d3"
    },
    {
      "from": "00d440af"
    },
    {
      "from": "00bcf2bd"
    },
    {
      "from": "00bcfe2a"
    },
    {
      "from": "00c4e1c6"
    },
    {
      "from": "00c77dac"
    },
    {
      "from": "00c77f88"
    },
    {
      "from": "00ea553a"
    },
    {
      "from": "0100231f"
    },
    {
      "from": "00fd9d48"
    },
    {
      "from": "00fd9da7"
    },
    {
      "from": "00fd9dba"
    },
    {
      "from": "0101c4ac"
    },
    {
      "from": "0101c5a7"
    },
    {
      "from": "010258e9"
    },
    {
      "from": "01025a46"
    },
    {
      "from": "01025ece"
    },
    {
      "from": "0102644d"
    },
    {
      "from": "01027c79"
    },
    {
      "from": "01028b78"
    },
    {
      "from": "01058b80"
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
  "global:Simulator::sSpacePlayerData at 0x016dda8c"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg01_roots/space_player_data_accessors.cpp",
  "files": [
    "src/reconstruction/pkg01_roots/space_player_data_accessors.cpp",
    "src/reconstruction/pkg01_roots/space_player_data_accessors.hpp",
    "src/reconstruction/pkg01_roots/space_player_data_accessors_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg01-roots/01021230.json"
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
    "No trace establishes when the published global is valid during initialization or teardown.",
    "Separate static writers and cleanup routines can replace or release the +0x08 slot; use-after-clear or stale-pointer windows remain runtime questions.",
    "The concrete returned object and its lifetime are not established by this accessor.",
    "gate-space-player-data-publication"
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
  "OpaqueActiveStar",
  "SpacePlayerDataAccessPrefix",
  "opaque 32-bit active-star pointer word"
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
