# Evidence 0x00642190

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `11c0aab85dc03f4b2388c159d2a8ff612814412a1b452233b1e5bd86e6c1b9ea`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall, receiver only, no stack arguments",
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_width_bytes": 0,
  "stack_arguments": [],
  "stack_cleanup_bytes": 0
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/abi_infer.py#tail_target=0x006412a0`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller"
  },
  "abstained_because": [
    "no_terminal_ret: the only exit observed is a tail jump"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "forwarded_from_tail_target",
    "evidence": "forwarded from the tail target 0x006412a0: ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "4b5c60c52a54bdf496ab990b34045a35c0f9c508bf9d1b8857fd97905b413507",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall, receiver only, no stack arguments"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          16,
          20,
          28,
          32,
          60,
          64,
          80,
          112,
          116
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0017"
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
        "obs-0017"
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
        "obs-0017"
      ],
      "claim": "calling convention is __thiscall, forwarded from the tail target 0x006412a0: this listing is a single ESP-neutral direct jump, inherits its caller's frame and never runs its own RET, so the two calls are one call (resolved from live listing for 0x006412a0)",
      "confidence": "INFERRED",
      "id": "T1-FWD",
      "value": "__thiscall"
    }
  ],
  "observations": [
    {
      "at": "0x00642190",
      "count": 12,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00642191",
      "count": 6,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00642191",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x006421a7",
      "definite": true,
      "id": "obs-0004",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x74]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006421ae",
      "definite": true,
      "id": "obs-0005",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006421b0",
      "count": 6,
      "first_use": 9,
      "first_write_index": 8,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x4]",
      "reg": "EAX"
    },
    {
      "at": "0x006421b0",
      "definite": true,
      "id": "obs-0007",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x4]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006421b3",
      "count": 5,
      "first_use": 10,
      "first_write_index": 9,
      "id": "obs-0008",
      "index": 10,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x006421b3",
      "base": "EDX",
      "disp": null,
      "id": "obs-0009",
      "index": 10,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x006421c1",
      "base": "EDX",
      "disp": null,
      "id": "obs-0010",
      "index": 16,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x006421d0",
      "id": "obs-0011",
      "index": 23,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f47380",
      "target": "0x00f47380"
    },
    {
      "at": "0x006421d5",
      "definite": true,
      "id": "obs-0012",
      "index": 24,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x4",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x006421e4",
      "base": "EDX",
      "disp": null,
      "id": "obs-0013",
      "index": 30,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x006421f2",
      "base": "EDX",
      "disp": null,
      "id": "obs-0014",
      "index": 36
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
    "name": "FUN_00642210",
    "reconstructed": false,
    "va": "0x00642210"
  },
  {
    "name": "FUN_00dd0bc0",
    "reconstructed": false,
    "va": "0x00dd0bc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00dd0cf0"
  },
  {
    "name": "FUN_00ec4280",
    "reconstructed": false,
    "va": "0x00ec4280"
  },
  {
    "name": "FUN_00ecc620",
    "reconstructed": false,
    "va": "0x00ecc620"
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
  "count": 46,
  "instructions": [
    {
      "address": "00642190",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00642191",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00642193",
      "instruction": "MOV dword ptr [ESI],0x13ff648"
    },
    {
      "address": "00642199",
      "instruction": "MOV dword ptr [ESI + 0x10],0x1462748"
    },
    {
      "address": "006421a0",
      "instruction": "MOV dword ptr [ESI + 0x14],0x1462738"
    },
    {
      "address": "006421a7",
      "instruction": "MOV ECX,dword ptr [ESI + 0x74]"
    },
    {
      "address": "006421aa",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006421ac",
      "instruction": "JZ 0x006421b5"
    },
    {
      "address": "006421ae",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "006421b0",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "006421b3",
      "instruction": "CALL EDX"
    },
    {
      "address": "006421b5",
      "instruction": "MOV ECX,dword ptr [ESI + 0x70]"
    },
    {
      "address": "006421b8",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006421ba",
      "instruction": "JZ 0x006421c3"
    },
    {
      "address": "006421bc",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "006421be",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "006421c1",
      "instruction": "CALL EDX"
    },
    {
      "address": "006421c3",
      "instruction": "MOV EAX,dword ptr [ESI + 0x40]"
    },
    {
      "address": "006421c6",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "006421c8",
      "instruction": "JZ 0x006421d8"
    },
    {
      "address": "006421ca",
      "instruction": "CMP EAX,dword ptr [ESI + 0x50]"
    },
    {
      "address": "006421cd",
      "instruction": "JZ 0x006421d8"
    },
    {
      "address": "006421cf",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006421d0",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "006421d5",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "006421d8",
      "instruction": "MOV ECX,dword ptr [ESI + 0x3c]"
    },
    {
      "address": "006421db",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006421dd",
      "instruction": "JZ 0x006421e6"
    },
    {
      "address": "006421df",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "006421e1",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "006421e4",
      "instruction": "CALL EDX"
    },
    {
      "address": "006421e6",
      "instruction": "MOV ECX,dword ptr [ESI + 0x20]"
    },
    {
      "address": "006421e9",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006421eb",
      "instruction": "JZ 0x006421f4"
    },
    {
      "address": "006421ed",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "006421ef",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "006421f2",
      "instruction": "CALL EDX"
    },
    {
      "address": "006421f4",
      "instruction": "MOV ECX,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006421f7",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006421f9",
      "instruction": "JZ 0x00642202"
    },
    {
      "address": "006421fb",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "006421fd",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00642200",
      "instruction": "CALL EDX"
    },
    {
      "address": "00642202",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00642204",
      "instruction": "POP ESI"
    },
    {
      "address": "00642205",
      "instruction": "JMP 0x006412a0"
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
  "original_bytes": 8702,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall, receiver only, no stack arguments\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueAssetRef,OpaqueInlineWordVector,OpaqueSporepediaAsset,OpaqueSporepediaAsset*\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-SAFE-WAVE10\",\n      \"score\": 28,\n      \"symbol\": \"sporepedia_asset_load_00642230\",\n      \"va\": \"0x00642230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"property_value_resolve_0041e920\",\n      \"va\": \"0x0041e920\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"palette_row_layout_005c3000\",\n      \"va\": \"0x005c3000\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueSporepediaAsset\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"FUN_00642210\",\n        \"reconstructed\": false,\n        \"va\": \"0x00642210\"\n      },\n      {\n        \"name\": \"FUN_00dd0bc0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00dd0bc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd0cf0\"\n      },\n      {\n        \"name\": \"FUN_00ec4280\",\n        \"reconstructed\": false,\n        \"va\": \"0x00ec4280\"\n      },\n      {\n        \"name\": \"FUN_00ecc620\",\n        \"reconstructed\": false,\n        \"va\": \"0x00ecc620\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00642213\",\n        \"direction\": \"in\",\n        \"other\": \"0x00642210\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0bd7\",\n        \"direction\": \"in\",\n        \"other\": \"0x00dd0bc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0d28\",\n        \"direction\": \"in\",\n        \"other\": \"0x00dd0cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ec4297\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ec4280\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ecc65c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ecc620\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642205\",\n        \"direction\": \"out\",\n        \"other\": \"0x006412a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006421d0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 5,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00f47380\",\n      \"0x006412a0\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0169\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 3\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"sporepedia_asset_destroy_00642190\",\n  \"normalized_symbol\": \"sporepedia_asset_destroy_00642190\",\n  \"observed_mechanics\": [\n    \"Write the derived vtable triple 0x013ff648 at +0x00, 0x01462748 at +0x10 and 0x01462738 at +0x14.\",\n    \"Release the handle at +0x74 through vtable slot +0x04 when it is non null.\",\n    \"Release the handles at +0x70, then +0x3c, then +0x20, then +0x1c, each null guarded.\",\n    \"Read the inline entry vector first word at +0x40 and skip the free when it is null.\",\n    \"Skip the free when the vector first word equals the inline marker word at +0x50.\",\n    \"Otherwise free the entry vector through the cdecl port 0x00f47380.\",\n    \"No receiver field outside the three vtable slots is written and no released pointer is reused.\",\n    \"End with POP ESI followed by JMP 0x006412a0, a tail transfer into the base destructor.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-SPOREPEDIA-SAFE-WAVE10\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-SPOREPEDIA-SAFE-WAVE10\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG
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
  "body_end": "00642209",
  "body_span_bytes": 122,
  "body_start": "00642190",
  "callees": [
    "FUN_006412a0",
    "FUN_00f47380"
  ],
  "callers": [
    "FUN_00ecc620",
    "FUN_00dd0bc0",
    "FUN_00642210",
    "FUN_00ec4280",
    "FUN_00dd0cf0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00642190",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00642190",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x242190",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00642190(void)",
  "size_bytes": 122,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00642190",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00642213"
    },
    {
      "from": "00dd0bd7"
    },
    {
      "from": "00dd0d28"
    },
    {
      "from": "00ec4297"
    },
    {
      "from": "00ecc65c"
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
  "file": "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.cpp",
    "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.hpp",
    "src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-sporepedia-safe-wave10/00642190.json"
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
    "The base destructor 0x006412a0 is a tail-transfer target and is not promoted; only its three vtable stores are modelled.",
    "The free port 0x00f47380 is shared across the campaign and is not promoted here.",
    "The handle release slots at asset-ref vtable +0x04 are opaque seams and are not promoted.",
    "The invariant that keeps an inline vector from being freed is unverified at runtime.",
    "The six vtable words are literal image addresses with no class attribution in the live database.",
    "gate-sporepedia-asset-destroy-runtime-vtable-owners",
    "runtime validation not performed; static decompilation and disassembly only",
    "the base destructor 0x006412a0 is a tail-transfer target and is not promoted; only its three vtable stores are modelled in the default port",
    "the free port 0x00f47380 is shared across the campaign and is not promoted here",
    "the handle release slots at asset-ref vtable +0x04 are opaque seams and are not promoted",
    "the inline marker comparison uses the word at +0x50 against the vector first word at +0x40; the invariant that keeps an inline vector from being freed is unverified at runtime",
    "the six vtable words are literal image addresses with no class attribution in the live database"
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
  "OpaqueAssetRef",
  "OpaqueAssetRefVtable",
  "OpaqueInlineWordVector",
  "OpaqueSporepediaAsset",
  "OpaqueSporepediaAsset*",
  "SporepediaSafeBindings",
  "void"
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
