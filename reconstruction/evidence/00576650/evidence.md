# Evidence 0x00576650

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9ffe937bafcd3cb4e2819500f3ce30325a8bb40ecfe20074c5c763f389b6c87a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "TexturePtr*",
  "return_register": null,
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "rhs",
      "observed_use": "Compares against the current slot, increments rhs+0x08 when non-null, and publishes rhs to the slot.",
      "position": 1,
      "type": "OpaqueTexture*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "dc89558998df12339884eba44c5465dad231e358ae8c18b9cdb663310ffa7fec",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
    "persisted_calling_convention": "__thiscall observed"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0019",
        "obs-0022"
      ],
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0015",
        "obs-0016",
        "obs-0017",
        "obs-0020"
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
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0015",
        "obs-0016",
        "obs-0017",
        "obs-0019",
        "obs-0020",
        "obs-0022"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0022"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0022"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0022"
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
      "at": "0x00576650",
      "count": 9,
      "first_use": 0,
      "first_write_index": 2,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00576650",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ECX",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x00576652",
      "count": 2,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x00576652",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00576654",
      "count": 1,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00576
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
    "va": "0x00580700"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00585d40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005fdca0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00646370"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00659270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006ebb80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006ef9e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f0fb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f44c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f4500"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006fbed0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0070ec80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00713070"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007679f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076e110"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076edf0"
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
  "count": 33,
  "instructions": [
    {
      "address": "00576650",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "00576652",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00576654",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00576658",
      "instruction": "CMP ECX,EDX"
    },
    {
      "address": "0057665a",
      "instruction": "JZ 0x005766a2"
    },
    {
      "address": "0057665c",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0057665d",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0057665f",
      "instruction": "JZ 0x0057666f"
    },
    {
      "address": "00576661",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00576662",
      "instruction": "LEA ESI,[ECX + 0x8]"
    },
    {
      "address": "00576665",
      "instruction": "MOV EDI,0x1"
    },
    {
      "address": "0057666a",
      "instruction": "XADD.LOCK dword ptr [ESI],EDI"
    },
    {
      "address": "0057666e",
      "instruction": "POP EDI"
    },
    {
      "address": "0057666f",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00576671",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "00576673",
      "instruction": "JZ 0x005766a1"
    },
    {
      "address": "00576675",
      "instruction": "ADD EDX,0x8"
    },
    {
      "address": "00576678",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "0057667a",
      "instruction": "OR ESI,0xffffffff"
    },
    {
      "address": "0057667d",
      "instruction": "XADD.LOCK dword ptr [ECX],ESI"
    },
    {
      "address": "00576681",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00576683",
      "instruction": "MOV ESI,EDX"
    },
    {
      "address": "00576685",
      "instruction": "XADD.LOCK dword ptr [ESI],ECX"
    },
    {
      "address": "00576689",
      "instruction": "CMP ECX,0x1"
    },
    {
      "address": "0057668c",
      "instruction": "JGE 0x0057669b"
    },
    {
      "address": "0057668e",
      "instruction": "MOV ECX,0x1"
    },
    {
      "address": "00576693",
      "instruction": "XADD.LOCK dword ptr [EDX],ECX"
    },
    {
      "address": "00576697",
      "instruction": "POP ESI"
    },
    {
      "address": "00576698",
      "instruction": "RET 0x4"
    },
    {
      "address": "0057669b",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "0057669d",
      "instruction": "XADD.LOCK dword ptr [EDX],ECX"
    },
    {
      "address": "005766a1",
      "instruction": "POP ESI"
    },
    {
      "address": "005766a2",
      "instruction": "RET 0x4"
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
  "original_bytes": 22791,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"TexturePtr*\",\n    \"return_register\": null,\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"rhs\",\n        \"observed_use\": \"Compares against the current slot, increments rhs+0x08 when non-null, and publishes rhs to the slot.\",\n        \"position\": 1,\n        \"type\": \"OpaqueTexture*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 2,\n      \"symbol\": \"transform_pre_transform_by_0040ccb0\",\n      \"va\": \"0x0040ccb0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 2,\n      \"symbol\": \"wave6_reference_00432a50\",\n      \"va\": \"0x00432a50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"editor_query_reset_005dd750\",\n      \"va\": \"0x005dd750\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 2,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 2,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"editor_query_clear_flags_0093db80\",\n      \"va\": \"0x0093db80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 2,\n      \"symbol\": \"pkg11_sim_core_00b21340\",\n      \"va\": \"0x00b21340\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"Caller slot layouts and Texture producer semantics remain opaque.\",\n    \"Concrete Texture ownership and destruction remain outside this body.\",\n    \"No runtime trace is available for refcount, allocator, or concurrency behavior.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"TexturePtr\",\n  \"cluster\": \"gameglobal-misc\",\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00580700\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00585d40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005fdca0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00646370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00659270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006ebb80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006ef9e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f0fb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f44c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f4500\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006fbed0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0070ec80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00713070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007679f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076e110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076edf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00777290\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007773c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0077cb10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00780270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007a52f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007a5370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007a5410\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007a54b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007a5530\"\n      },\n      {\n
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
  "body_end": "005766a4",
  "body_span_bytes": 85,
  "body_start": "00576650",
  "callees": [],
  "callers": [
    "FUN_006f44c0",
    "FUN_00713070",
    "FUN_00f9e280",
    "FUN_007a5990",
    "FUN_00e49f80",
    "FUN_00777290",
    "FUN_007cfcd0",
    "FUN_00fa6480",
    "FUN_007a9f30",
    "FUN_00f4bcb0",
    "FUN_00fa3c10",
    "FUN_01006370",
    "FUN_00659270",
    "FUN_0076e110",
    "FUN_007a5900",
    "FUN_00f46630",
    "FUN_007773c0",
    "FUN_007a57d0",
    "FUN_00faec70",
    "FUN_00fa01e0",
    "FUN_007a56b0",
    "FUN_0082eb80",
    "FUN_007a52f0",
    "FUN_007a5370",
    "FUN_007bea00",
    "FUN_00f4b870",
    "FUN_00fba330",
    "FUN_007a5530",
    "FUN_00f4baa0",
    "FUN_00fd9750",
    "FUN_00f9e120",
    "FUN_007a5630",
    "FUN_00f6b330",
    "FUN_007a5410",
    "FUN_007a5730",
    "FUN_00580700",
    "FUN_007a5860",
    "FUN_00f3d210",
    "FUN_00c2fc10",
    "FUN_00f9c010",
    "FUN_00fa1650",
    "FUN_006ebb80",
    "FUN_00ae4610",
    "FUN_007a54b0",
    "FUN_00f9d5c0",
    "FUN_007679f0",
    "FUN_0070ec80",
    "FUN_0077cb10",
    "FUN_00780270",
    "FUN_00fbdb10",
    "FUN_00f44fe0",
    "FUN_00fba2f0",
    "FUN_005fdca0",
    "FUN_00646370",
    "FUN_007a5a20",
    "FUN_006fbed0",
    "FUN_00ae42f0",
    "FUN_007cf760",
    "FUN_007a55b0",
    "FUN_00ae4430",
    "FUN_00e834d0",
    "FUN_006ef9e0",
    "FUN_006f0fb0",
    "FUN_00fbce30",
    "FUN_00585d40",
    "FUN_006f4500",
    "FUN_0076edf0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00576650",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "TexturePtr_Set",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x176650",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined TexturePtr_Set(void)",
  "size_bytes": 85,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00576650",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "0077cb2a"
    },
    {
      "from": "00586058"
    },
    {
      "from": "0058623b"
    },
    {
      "from": "00580858"
    },
    {
      "from": "006592c6"
    },
    {
      "from": "00659310"
    },
    {
      "from": "005fddb1"
    },
    {
      "from": "00777455"
    },
    {
      "from": "006f44e3"
    },
    {
      "from": "007772e9"
    },
    {
      "from": "006ebba3"
    },
    {
      "from": "006ebbaf"
    },
    {
      "from": "006ef9eb"
    },
    {
      "from": "006f106d"
    },
    {
      "from": "006f1086"
    },
    {
      "from": "006f10f1"
    },
    {
      "from": "006f1144"
    },
    {
      "from": "006f1166"
    },
    {
      "from": "006f1193"
    },
    {
      "from": "006f11b5"
    },
    {
      "from": "006f1294"
    },
    {
      "from": "006f12a1"
    },
    {
      "from": "006f451e"
    },
    {
      "from": "006f4542"
    },
    {
      "from": "006f4566"
    },
    {
      "from": "006fbf33"
    },
    {
      "from": "0070ee3c"
    },
    {
      "from": "00713314"
    },
    {
      "from": "00767c1b"
    },
    {
      "from": "0076e19d"
    },
    {
      "from": "0076ee97"
    },
    {
      "from": "0078038c"
    },
    {
      "from": "007a5348"
    },
    {
      "from": "007a53e6"
    },
    {
      "from": "007a5486"
    },
    {
      "from": "007a550b"
    },
    {
      "from": "007a5608"
    },
    {
      "from": "007a5688"
    },
    {
      "from": "007a570a"
    },
    {
      "from": "007a583a"
    },
    {
      "from": "007a5967"
    },
    {
      "from": "007a59f4"
    },
    {
      "from": "007a5a76"
    },
    {
      "from": "007a5588"
    },
    {
      "from": "007a579f"
    },
    {
      "from": "007a58cf"
    },
    {
      "from": "007a9fc9"
    },
    {
      "from": "007aa057"
    },
    {
      "from": "007bebe6"
    },
    {
      "from": "007cf7ca"
    },
    {
      "from": "007cffa3"
    },
    {
      "from": "00ae4506"
    },
    {
      "from": "00ae469f"
    },
    {
      "from": "00ae46af"
    },
    {
      "from": "00fa3db3"
    },
    {
      "from": "00f9d5ea"
    },
    {
      "from": "00f6b33b"
    },
    {
      "from": "00fa0207"
    },
    {
      "from": "00faec87"
    },
    {
      "from": "00c2fc6f"
    },
    {
      "from": "0082eb95"
    },
    {
      "from": "0064678f"
    },
    {
      "from": "00f454b6"
    },
    {
      "from": "00f3d245"
    },
    {
      "from": "00f3d253"
    },
    {
      "from": "00f46726"
    },
    {
      "from": "00f4b8b4"
    },
    {
      "from": "00f4be15"
    },
    {
      "from": "00fbdb58"
    },
    {
      "from": "00fbce3e"
    },
    {
      "from": "00fbce4a"
    },
    {
      "from": "00fbce56"
    },
    {
      "from": "00fbce62"
    },
    {
      "from": "00fbce6e"
    },
    {
      "from": "00fbce7a"
    },
    {
      "from": "00fbce86"
    },
    {
      "from": "00fbce92"
    },
    {
      "from": "00fbce9e"
    },
    {
      "from": "00fbceaa"
    },
    {
      "from": "00fbceb6"
    },
    {
      "from": "00fbcec2"
    },
    {
      "from": "00fbcece"
    },
    {
      "from": "00fbceda"
    },
    {
      "from": "00f9c052"
    },
    {
      "from": "00f9c088"
    },
    {
      "from": "00f9c0bf"
    },
    {
      "from": "00f9e157"
  
[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:No direct global data reference is present in the target body."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg20_resource_adapter/texture_ptr.cpp",
  "files": [
    "reconstruction/staging/pkg20-resource-adapter/texture_ptr.cpp",
    "reconstruction/staging/pkg20-resource-adapter/texture_ptr.hpp",
    "reconstruction/staging/pkg20-resource-adapter/texture_ptr_model_test.cpp",
    "src/reconstruction/pkg20_resource_adapter/texture_ptr.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-resource-adapter/00576650.json"
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
    "gate-texture-ptr-refcount"
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 6367,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"STRONG_SEMANTIC\",\n  \"confidence\": {\n    \"identity\": 0.95,\n    \"mechanics\": 0.99,\n    \"ownership\": 0.9\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 67,\n  \"evidence\": [\n    {\n      \"kind\": \"disassembly\",\n      \"source\": \"ghidra://SporeApp.exe@0x00576650\",\n      \"statement\": \"The target compares old/rhs, uses LOCK XADD for rhs+8 and old+8, stores rhs into the slot, and restores a below-one old count to one.\"\n    },\n    {\n      \"kind\": \"decompilation\",\n      \"source\": \"ghidra://SporeApp.exe@0x00576650\",\n      \"statement\": \"Pseudocode independently shows the same add-new, publish, release-old sequence.\"\n    },\n    {\n      \"kind\": \"sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x005766b0\",\n      \"statement\": \"The adjacent clear/reset path also clears the slot and clamps the reference count without deletion.\"\n    },\n    {\n      \"kind\": \"SDK\",\n      \"source\": \"/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Graphics/Texture.h:26-30,45-75,84-97\",\n      \"statement\": \"TexturePtr is eastl::intrusive_ptr<Graphics::Texture>; Texture stores mnRefCount at +0x08 and Release restores a below-one count to one without deleting itself.\"\n    },\n    {\n      \"kind\": \"repository\",\n      \"source\": \"docs/analysis/reconstruction-research-queue.md:128\",\n      \"statement\": \"The committed queue records TexturePtr_Set as a 67-fan-in GameGlobal resource-content candidate with no callees.\"\n    }\n  ],\n  \"family\": \"eastl::intrusive_ptr<Graphics::Texture>::operator=\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": {\n      \"count\": 0,\n      \"items\": [],\n      \"status\": \"leaf\"\n    },\n    \"direct_callers\": {\n      \"canonical\": {\n        \"direct_call_references\": 118,\n        \"fan_out_external\": 0,\n        \"fan_out_internal\": 0,\n        \"gameplay_fan_in\": 0,\n        \"global_fan_in\": 2,\n        \"unique_direct_caller_functions\": 67\n      },\n      \"read_only_ghidra\": {\n        \"direct_call_xrefs\": 124,\n        \"unique_direct_caller_functions\": 67\n      },\n      \"representative\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        }\n      ]\n    },\n    \"globals\": [],\n    \"structures\": [\n      {\n        \"field\": \"single Texture pointer\",\n        \"name\": \"eastl::intrusive_ptr<Graphics::Texture>\",\n        \"size\": \"0x04\"\n      },\n      {\n        \"fields\": [\n          \"Raster* +0x00\",\n          \"flags +0x04\",\n          \"mnRefCount +0x08\",\n          \"field_0C +0x0c\",\n          \"ResourceKey +0x10\",\n          \"resource pointer +0x1c\"\n        ],\n        \"name\": \"Graphics::Texture\",\n        \"size\": \"0x20\"\n      }\n    ],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [\n        {\n          \"keys\": [\n            \"meaning\",\n            \"name\",\n            \"ordinal\",\n            \"storage\",\n            \"type\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"meaning\",\n            \"name\",\n            \"ordinal\",\n            \"storage\",\n            \"type\"\n          ]\n        }\n      ],\n      \"ordering\": [],\n      \"outputs\": [],\n      \"postconditions\": [\n        \"If rhs equals the old pointer, the function is a complete no-op.\",\n        \"If rhs is non-null, rhs->mnRefCount is atomically incremented before publication.\",\n        \"The slot is assigned rhs.\",\n        \"If the old pointer is non-null, old->mnRefCount is atomically decremented.\",\n        \"If the old post-decrement count is below 1, it is restored to 1; the function does not delete the Texture.\"\n      ],\n      \"preconditions\": [\n        \"this points to a writable intrusive pointer slot.\",\n        \"rhs is null or a live Graphics::Texture whose reference count is at +0x08.\",\n        \"The slot is not concurrently assigned without the same external synchronization assumptions as the original intrusive_ptr.\"\n      ],\n      \"purpose\": \"eastl::intrusive_ptr<Graphics::Texture>::operator=\",\n      \"return\": {\n        \"type\": \"void\",\n        \"value\": \"The caller's slot is updated; no ownership is transferred to the caller separately.\"\n      },\n      \"side_effects\": {\n        \"concurrency\": \"Reference counts are atomic; pointer publication and equality are ordinary instructions in the observed body.\",\n        \"items\": [\n          \"Reference-count update is performed with LOCK XADD.\",\n          \"Old pointer is released after the new pointer is published.\",\n          \"No callee, virtual call, allocation, or deletion occurs.\"\n        ]\n      },\n      \"status\": \"STATIC_CONTRACT\",\n      \"unresolved\": []\n    }\n  },\n  \"invariants\": {\n    \"failure_semantics\": [],\n    \"invariants\": [\n      {\n        \"observed\": [\n          \"Equal pointers are not released twice.\",\n          \"Reference counts never remain below one in the observed release path.\"\n        ],\n        \"semantic_status\": \"static_supported\"\n      }\n    ],\n    \"invariants_status\": \"reported\"\n  },\n  \"name\": \"eastl::intrusive_ptr<Graphics::Texture
[TRUNCATED]
```

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
  "OpaqueTexture",
  "OpaqueTexture*",
  "TexturePtr",
  "TexturePtr*",
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
