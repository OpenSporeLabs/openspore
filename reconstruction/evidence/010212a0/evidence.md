# Evidence 0x010212a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f950a1005174188b52abe700fb27ab0672da1c5b9ba29809bd339516192a2dee`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl-compatible no-argument accessor",
  "return_note": "opaque 32-bit word loaded from active-planet+0x13c",
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
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
  "content_sha256": "fbb6ba53852b543561d776fbe103fd7ed8e1163a3d055744910abdc9158e2d0a",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017",
        "obs-0020"
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
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0016",
        "obs-0019"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0020"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0020"
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
        "obs-0017",
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0020"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x010212a0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 6,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x010212a1",
      "count": 3,
      "first_use": 1,
      "first_write_index": 1,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "XOR EDX,EDX",
      "reg": "EDX"
    },
    {
      "at": "0x010212a1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "XOR EDX,EDX",
      "reg": "EDX",
      "write_kind": "zero"
    },
    {
      "at": "0x010212a3",
      "count": 4,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP],EDX",
      "reg": "ESP"
    },
    {
      "at": "0x010212a3",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0005",
      "index": 2,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP],EDX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x010212a6",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016dda8c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x010212af",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0007",
      "index": 6,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x010212af",
      "definite": true,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x010212be",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0009",
      "index": 11,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x010212c1",
      "count": 4,
      "first_use": 12,
      "first_write_index": 3,
      "id": "obs-0010",
      "index": 12,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP]",
      "reg": "EAX"
    },
    {
      "at": "0x010212c1",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0011",
      "index": 12,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA EAX,[ESP]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x010212c4",
      "count": 2,
      "first_use": 13,
      "first_write_ind
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
    "va": "0x00ae5840"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba0770"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba57f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba58f3"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5a60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbc670"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbc6a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbc870"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbc950"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbcda0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbce00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbce40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbe370"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbe5f0"
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
  "count": 32,
  "instructions": [
    {
      "address": "010212a0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "010212a1",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "010212a3",
      "instruction": "MOV dword ptr [ESP],EDX"
    },
    {
      "address": "010212a6",
      "instruction": "MOV EAX,[0x016dda8c]"
    },
    {
      "address": "010212ab",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "010212ad",
      "instruction": "JZ 0x010212b7"
    },
    {
      "address": "010212af",
      "instruction": "MOV ECX,dword ptr [ESP]"
    },
    {
      "address": "010212b2",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "010212b5",
      "instruction": "JMP 0x010212c4"
    },
    {
      "address": "010212b7",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "010212b9",
      "instruction": "MOV EDX,0x1"
    },
    {
      "address": "010212be",
      "instruction": "MOV dword ptr [ESP],ECX"
    },
    {
      "address": "010212c1",
      "instruction": "LEA EAX,[ESP]"
    },
    {
      "address": "010212c4",
      "instruction": "PUSH ESI"
    },
    {
      "address": "010212c5",
      "instruction": "MOV ESI,dword ptr [EAX]"
    },
    {
      "address": "010212c7",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "010212ca",
      "instruction": "JZ 0x010212da"
    },
    {
      "address": "010212cc",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "010212ce",
      "instruction": "JZ 0x010212da"
    },
    {
      "address": "010212d0",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "010212d2",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc0]"
    },
    {
      "address": "010212d8",
      "instruction": "CALL EDX"
    },
    {
      "address": "010212da",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "010212dc",
      "instruction": "JZ 0x010212e7"
    },
    {
      "address": "010212de",
      "instruction": "MOV EAX,dword ptr [ESI + 0x13c]"
    },
    {
      "address": "010212e4",
      "instruction": "POP ESI"
    },
    {
      "address": "010212e5",
      "instruction": "POP ECX"
    },
    {
      "address": "010212e6",
      "instruction": "RET"
    },
    {
      "address": "010212e7",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "010212e9",
      "instruction": "POP ESI"
    },
    {
      "address": "010212ea",
      "instruction": "POP ECX"
    },
    {
      "address": "010212eb",
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
  "original_bytes": 16275,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"return_note\": \"opaque 32-bit word loaded from active-planet+0x13c\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:ActivePlanetAccessWindow,SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 22,\n      \"symbol\": \"FUN_01021260\",\n      \"va\": \"0x01021260\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 19,\n      \"symbol\": \"FUN_01021080\",\n      \"va\": \"0x01021080\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 19,\n      \"symbol\": \"FUN_01021230\",\n      \"va\": \"0x01021230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d400\",\n      \"va\": \"0x00b3d400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cSpaceTrading_Get\",\n      \"va\": \"0x00b3d4d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Null-guarded +0x04 active-planet chain followed by opaque +0x13c word read; concrete pointee type and ownership remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueActivePlanetField13c\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae5840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba0770\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba57f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba58f3\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5a60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbc670\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbc6a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbc870\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbc950\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbcda0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbce00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbce40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbe370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbe5f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbe850\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbecc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbee30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbf2b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbf860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bc0180\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bc1450\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bcece0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd8a00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd8aa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd8b10\"\n   
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
  "body_end": "010212eb",
  "body_span_bytes": 76,
  "body_start": "010212a0",
  "callees": [],
  "callers": [
    "FUN_00ba0770",
    "FUN_00ee7cb0",
    "FUN_00c8cb20",
    "FUN_00ffa900",
    "FUN_00c830f0",
    "FUN_00c4dd10",
    "FUN_00bbe5f0",
    "FUN_00ee9840",
    "FUN_00ae5840",
    "FUN_00c51bb0",
    "FUN_00bbee30",
    "FUN_00bcece0",
    "FUN_0103fc10",
    "FUN_01030fd0",
    "FUN_00c382e0",
    "FUN_00bc1450",
    "FUN_00ff6380",
    "FUN_00ff65f0",
    "FUN_01056160",
    "FUN_00ee8d80",
    "FUN_00bbcda0",
    "FUN_00fdf5b0",
    "FUN_00ff6200",
    "FUN_00bbf2b0",
    "FUN_00fdeac0",
    "FUN_00c4ea70",
    "FUN_00f37690",
    "FUN_00be5dd0",
    "FUN_00fdf5f0",
    "FUN_00c4c3f0",
    "FUN_0103eff0",
    "FUN_0105b350",
    "FUN_01058c90",
    "FUN_00d06a50",
    "FUN_00c8c9d0",
    "FUN_0106fc90",
    "FUN_01004e50",
    "FUN_00bbf860",
    "FUN_00c53720",
    "FUN_0102ba30",
    "FUN_00bd8a00",
    "FUN_00c774b0",
    "FUN_00ebd420",
    "FUN_00bbce00",
    "FUN_00bc0180",
    "FUN_01071d70",
    "FUN_00bf4370",
    "FUN_00c00b00",
    "FUN_00ee95a0",
    "FUN_00ff7530",
    "FUN_00bbc670",
    "FUN_00fdf8e0",
    "FUN_01024630",
    "FUN_01060150",
    "FUN_00fef140",
    "FUN_00bbe850",
    "FUN_0102f820",
    "FUN_00bbc6a0",
    "FUN_00f32d10",
    "FUN_00c737a0",
    "FUN_01009df0",
    "FUN_00f32030",
    "FUN_00fde3e0",
    "FUN_010593e0",
    "FUN_00fdfbc0",
    "FUN_00f35c80",
    "FUN_00d056c0",
    "FUN_00bbe370",
    "FUN_01004fc0",
    "FUN_00bbecc0",
    "FUN_00ba5650",
    "FUN_00ee9690",
    "FUN_00ba57f0",
    "FUN_00c61070",
    "FUN_00ba58f3",
    "FUN_00fe7e60",
    "FUN_00f31f80",
    "FUN_00dbfad0",
    "FUN_00ff63e0",
    "FUN_00aeb3e0",
    "FUN_00d05730",
    "FUN_00f37f20",
    "FUN_00bd8aa0",
    "FUN_00e9c7f0",
    "FUN_00ffa690",
    "FUN_00dc40a0",
    "FUN_0106ba00",
    "FUN_00d01ab0",
    "FUN_00ebcc80",
    "FUN_01000520",
    "FUN_00ba5a60",
    "FUN_01067fb0",
    "FUN_00ebb8b0",
    "FUN_00c8d060",
    "FUN_01072d40",
    "FUN_00bbc950",
    "FUN_0106a4e0",
    "FUN_00ffaf20",
    "FUN_00bbc870",
    "FUN_00bd8b10",
    "FUN_00bbce40",
    "FUN_00e07e70",
    "FUN_00c8ce40"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "010212a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_010212a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc212a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_010212a0(void)",
  "size_bytes": 76,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x010212a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00bbc678"
    },
    {
      "from": "00c73854"
    },
    {
      "from": "00aeb461"
    },
    {
      "from": "00d01ac6"
    },
    {
      "from": "00d0575b"
    },
    {
      "from": "00ae5874"
    },
    {
      "from": "00be607f"
    },
    {
      "from": "00bd8b2e"
    },
    {
      "from": "00bbe5fd"
    },
    {
      "from": "00bbce4b"
    },
    {
      "from": "00bbce58"
    },
    {
      "from": "00bbce8a"
    },
    {
      "from": "00bd8ab7"
    },
    {
      "from": "00bf45a5"
    },
    {
      "from": "00ba5b47"
    },
    {
      "from": "00c00d8d"
    },
    {
      "from": "00c8ca16"
    },
    {
      "from": "00c8cf57"
    },
    {
      "from": "00c8cb5e"
    },
    {
      "from": "0102f83a"
    },
    {
      "from": "0103fd5a"
    },
    {
      "from": "00bbf8bf"
    },
    {
      "from": "00bbc885"
    },
    {
      "from": "00bbc961"
    },
    {
      "from": "00bc033f"
    },
    {
      "from": "00bbf2e1"
    },
    {
      "from": "00bbf335"
    },
    {
      "from": "00bbf33e"
    },
    {
      "from": "00fdf944"
    },
    {
      "from": "00fdea49"
    },
    {
      "from": "00ffa931"
    },
    {
      "from": "0102ba37"
    },
    {
      "from": "01068041"
    },
    {
      "from": "0106c667"
    },
    {
      "from": "0106a52f"
    },
    {
      "from": "00bd8a3e"
    },
    {
      "from": "00ba0f0f"
    },
    {
      "from": "00ba571c"
    },
    {
      "from": "00ba588a"
    },
    {
      "from": "00ba59bc"
    },
    {
      "from": "00bbe380"
    },
    {
      "from": "00bbe38d"
    },
    {
      "from": "00bbe85d"
    },
    {
      "from": "00bbcda8"
    },
    {
      "from": "00bbee43"
    },
    {
      "from": "00bbee50"
    },
    {
      "from": "00bbc6a8"
    },
    {
      "from": "00bbc6b1"
    },
    {
      "from": "00bc1477"
    },
    {
      "from": "00ebcc93"
    },
    {
      "from": "00c38427"
    },
    {
      "from": "00c4c3ff"
    },
    {
      "from": "00c4eab2"
    },
    {
      "from": "00c4eb54"
    },
    {
      "from": "00c51e19"
    },
    {
      "from": "00c5379e"
    },
    {
      "from": "00c8d1c7"
    },
    {
      "from": "00c8d1fa"
    },
    {
      "from": "00c8d232"
    },
    {
      "from": "00c77528"
    },
    {
      "from": "00c8355e"
    },
    {
      "from": "00dbfc46"
    },
    {
      "from": "00dc415d"
    },
    {
      "from": "00e09037"
    },
    {
      "from": "00e9c857"
    },
    {
      "f
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
    "reconstruction/metadata/pkg01-roots/010212a0.json"
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
    "The concrete +0x13c pointee, reference policy, and lifetime remain unresolved.",
    "The planet can be replaced or released by separate static lifecycle paths; validity of the two-level read and returned pointee remains runtime-gated.",
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
  "ActivePlanetAccessWindow",
  "OpaqueActivePlanetField13c",
  "SpacePlayerDataAccessPrefix",
  "opaque 32-bit word loaded from active-planet+0x13c"
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
