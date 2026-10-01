# Evidence 0x00c32cd0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e8f1ffd0e83fe67a5735f83642104c59a028cabf09512e05bd7298c6a0910c90`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueRecord*",
  "return_type": "OpaqueFloatColor*",
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "output",
      "position": 1,
      "type": "OpaqueFloatColor*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4 on every return path"
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8"
    ],
    "ordinary_stack_argument_slots_bounded": {
      "kept": 2,
      "omitted": 22
    },
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ordinary_stack_arguments_bounded": {
      "kept": 2,
      "omitted": 22
    },
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_arguments_bounded": {
      "kept": 2,
      "omitted": 22
    },
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -404, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0x198; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0x198 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "7dfc6d62d5492634c9e84eda16563af4c756b304a86550981ab33afae40cc3f3",
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020",
        "obs-0114",
        "obs-0123",
        "obs-0183"
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
        "obs-0020",
        "obs-0114",
        "obs-0123",
        "obs-0183"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 4,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0032",
        "obs-0038",
        "obs-0039",
        "obs-0040",
        "obs-0043",
        "obs-0044",
        "obs-0045",
        "obs-0046",
        "obs-0047",
        "obs-0048",
        "obs-0049",
        "obs-0050",
        "obs-0051",
        "obs-0062",
        "obs-0063",
        "obs-0064",
        "obs-0065",
        "obs-0066",
        "obs-0067",
        "obs-0079",
        "obs-0081",
        "obs-0082",
        "obs-0084",
        "obs-0089",
        "obs-0091",
        "obs-0092",
        "obs-0093",
        "obs-0094",
        "obs-0095",
        "obs-0096",
        "obs-0097",
        "obs-0098",
        "obs-0099",
        "obs-0100",
        "obs-0101",
        "obs-0102",
        "obs-0106",
        "obs-0107",
        "obs-0108",
        "obs-0109",
        "obs-0118",
        "obs-0127",
        "obs-0129",
        "obs-0130",
        "obs-0131",
        "obs-0132",
        "obs-0133",
        "obs-0134",
        "obs-0135",
        "obs-0136",
        "obs-0137",
        "obs-0138",
        "obs-0141",
        "obs-0142",
        "obs-0146",
        "obs-0148",
        "obs-0149",
        "obs-0150",
        "obs-0164",
        "obs-0165",
        "obs-0166",
        "obs-0167",
        "obs-0168",
        "obs-0169",
        "obs-0170",
        "obs-0173",
        "obs-0174",
        "obs-0175",
        "obs-0177"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 70,
        "observed_slots": 32,
        "total_bytes": 408
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0009",
        "obs-0013",
        "obs-0014",
        "obs-0015",
        "obs-0049",
        "obs-0054",
        "obs-0063",
        "obs-0068",
        "obs-0071",
        "obs-0089",
        "obs-0095",
        "obs-0100",
        "obs-0104",
      
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "address_window_offset_005c65e0",
    "reconstructed": true,
    "va": "0x005c65e0"
  },
  {
    "name": "pkg13_creature_accessor_00b1fdb0",
    "reconstructed": true,
    "va": "0x00b1fdb0"
  },
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": "Simulator_LookupEmpireByPoliticalId",
    "reconstructed": true,
    "va": "0x00ba9370"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c30c80"
  },
  {
    "name": "pkg12_space_01021300",
    "reconstructed": true,
    "va": "0x01021300"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aebe90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b677e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6d3c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba0080"
  },
  {
    "name": "FUN_00c33580",
    "reconstructed": false,
    "va": "0x00c33580"
  },
  {
    "name": "ProfileSetter_00c33690",
    "reconstructed": true,
    "va": "0x00c33690"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c737a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cc22c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00dd4b20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e06d90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e91060"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e9a940"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00feb510"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01005180"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01042080"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x010421c0"
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
  "count": 404,
  "instructions": [
    {
      "address": "00c32cd0",
      "instruction": "SUB ESP,0x84"
    },
    {
      "address": "00c32cd6",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c32cd7",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c32cd8",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00c32cda",
      "instruction": "MOV EAX,dword ptr [EBP + 0x10]"
    },
    {
      "address": "00c32cdd",
      "instruction": "LEA ECX,[EAX + 0xfac2430d]"
    },
    {
      "address": "00c32ce3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c32ce4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c32ce5",
      "instruction": "CMP ECX,0xb"
    },
    {
      "address": "00c32ce8",
      "instruction": "JA 0x00c32d19"
    },
    {
      "address": "00c32cea",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c32ceb",
      "instruction": "CALL 0x00b6f0c0"
    },
    {
      "address": "00c32cf0",
      "instruction": "FLD float ptr [EAX]"
    },
    {
      "address": "00c32cf2",
      "instruction": "MOV ECX,dword ptr [ESP + 0x9c]"
    },
    {
      "address": "00c32cf9",
      "instruction": "FSTP float ptr [ECX]"
    },
    {
      "address": "00c32cfb",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00c32cfe",
      "instruction": "FLD float ptr [EAX + 0x4]"
    },
    {
      "address": "00c32d01",
      "instruction": "FSTP float ptr [ECX + 0x4]"
    },
    {
      "address": "00c32d04",
      "instruction": "FLD float ptr [EAX + 0x8]"
    },
    {
      "address": "00c32d07",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "00c32d09",
      "instruction": "FSTP float ptr [ECX + 0x8]"
    },
    {
      "address": "00c32d0c",
      "instruction": "POP EDI"
    },
    {
      "address": "00c32d0d",
      "instruction": "POP ESI"
    },
    {
      "address": "00c32d0e",
      "instruction": "POP EBP"
    },
    {
      "address": "00c32d0f",
      "instruction": "POP EBX"
    },
    {
      "address": "00c32d10",
      "instruction": "ADD ESP,0x84"
    },
    {
      "address": "00c32d16",
      "instruction": "RET 0x4"
    },
    {
      "address": "00c32d19",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00c32d1e",
      "instruction": "CMP EBP,EAX"
    },
    {
      "address": "00c32d20",
      "instruction": "JNZ 0x00c32e95"
    },
    {
      "address": "00c32d26",
      "instruction": "MOV EAX,dword ptr [EBP + 0x10]"
    },
    {
      "address": "00c32d29",
      "instruction": "CMP EAX,0x53dbcf1"
    },
    {
      "address": "00c32d2e",
      "instruction": "JZ 0x00c32e15"
    },
    {
      "address": "00c32d34",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00c32d39",
      "instruction": "MOV EAX,dword ptr [EAX + 0xb0]"
    },
    {
      "address": "00c32d3f",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00c32d42",
      "instruction": "JZ 0x00c32d5e"
    },
    {
      "address": "00c32d44",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c32d45",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00c32d4a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c32d4c",
      "instruction": "CALL 0x00ba6d80"
    },
    {
      "address": "00c32d51",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c32d53",
      "instruction": "JZ 0x00c32d5e"
    },
    {
      "address": "00c32d55",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c32d57",
      "instruction": "CALL 0x00bba500"
    },
    {
      "address": "00c32d5c",
      "instruction": "JMP 0x00c32d60"
    },
    {
      "address": "00c32d5e",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00c32d60",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x4ec]"
    },
    {
      "address": "00c32d68",
      "instruction": "FLD float ptr [0x01471064]"
    },
    {
      "address": "00c32d6e",
      "instruction": "MOVSS XMM1,dword ptr [EAX + 0x4f0]"
    },
    {
      "address": "00c32d76",
      "instruction": "MOVSS XMM2,dword ptr [EAX + 0x4f4]"
    },
    {
      "address": "00c32d7e",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "00c32d81",
      "instruction": "MOV EAX,ESP"
    },
    {
      "address": "00c32d83",
      "instruction": "FST float ptr [ESP + 0x10]"
    },
    {
      "address": "00c32d87",
      "instruction": "LEA EDX,[ESP + 0x24]"
    },
    {
      "address": "00c32d8b",
      "instruction": "FSTP float ptr [ESP + 0xc]"
    },
    {
      "address": "00c32d8f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c32d90",
      "instruction": "MOVSS dword ptr [EAX],XMM0"
    },
    {
      "address": "00c32d94",
      "instruction": "MOVSS dword ptr [EAX + 0x4],XMM1"
    },
    {
      "address": "00c32d99",
      "instruction": "MOVSS dword ptr [EAX + 0x8],XMM2"
    },
    {
      "address": "00c32d9e",
      "instruction": "CALL 0x00b6e4b0"
    },
    {
      "address": "00c32da3",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00c32da9",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00c32dac",
      "instruction": "MOV EAX,ESP"
    },
    {
      "address": "00c32dae",
      "instruction": "MOVSS dword ptr [EAX],XMM0"
    },
    {
      "address": "00c32db2",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00c32db8",
      "instruction": "MOVSS dword ptr [EAX + 0x4],XMM0"
    },
    {
      "address": "00c32dbd",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00c32dc3",
      "instruction": "MOVSS dword ptr [EAX + 0x8],XMM0"
    },
    {
      "address": "00c32dc8",
      "instruction": "CALL 0x00b6f140"
    },
    {
      "address": "00c32dcd",
      "instruction": "ADD ESP,0xc"
    },
    {
    
[TRUNCATED]
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
  "original_bytes": 13404,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueRecord*\",\n    \"return_type\": \"OpaqueFloatColor*\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"output\",\n        \"position\": 1,\n        \"type\": \"OpaqueFloatColor*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4 on every return path\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"shared_types:OpaqueRecord*\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 11,\n      \"symbol\": \"PoliticalOwnershipScan_00c8d060\",\n      \"va\": \"0x00c8d060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 9,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 9,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"address_window_offset_005c65e0\",\n        \"reconstructed\": true,\n        \"va\": \"0x005c65e0\"\n      },\n      {\n        \"name\": \"pkg13_creature_accessor_00b1fdb0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b1fdb0\"\n      },\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"Simulator_LookupEmpireByPoliticalId\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ba9370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c30c80\"\n      },\n      {\n        \"name\": \"pkg12_space_01021300\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b677e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6d3c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba0080\"\n      },\n      {\n        \"name\": \"FUN_00c33580\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c33580\"\n      },\n      {\n        \"name\": \"ProfileSetter_00c33690\",\n        \"reconstructed\": true,\n        \"va\": \"0x00c33690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c737a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cc22c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd4b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e06d90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e91060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e9a940\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00feb510\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01005180\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01042080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010421c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01047000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01047300\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01047850\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010488e0\"\n      },
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
  "body_end": "00c33290",
  "body_span_bytes": 1473,
  "body_start": "00c32cd0",
  "callees": [
    "FUN_00b6f180",
    "FUN_005c65e0",
    "FUN_00f47380",
    "FUN_004232c0",
    "FUN_01021300",
    "FUN_00b6f0c0",
    "FUN_00b6e4b0",
    "FUN_00b3d2a0",
    "FUN_00b6e1e0",
    "FUN_00b6f140",
    "FUN_00c30c80",
    "FUN_00bb1080",
    "FUN_00ba9370",
    "FUN_00ba6d80",
    "FUN_00bba500",
    "FUN_00bb9ae0",
    "FUN_00b1fdb0",
    "FUN_00885c90"
  ],
  "callers": [
    "FUN_00e91060",
    "FUN_01047000",
    "FUN_00ba0080",
    "FUN_00b6d3c0",
    "FUN_00cc22c0",
    "FUN_00feb510",
    "FUN_00c33690",
    "FUN_01005180",
    "FUN_010727e0",
    "FUN_0106a7b0",
    "FUN_00c33580",
    "FUN_00c737a0",
    "FUN_00e9a940",
    "FUN_010488e0",
    "FUN_01042080",
    "FUN_00b677e0",
    "FUN_00aebe90",
    "FUN_00dd4b20",
    "FUN_0106ba00",
    "FUN_0106cc70",
    "FUN_01047300",
    "FUN_010421c0",
    "FUN_00e06d90",
    "FUN_01047850"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c32cd0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_3c",
      "storage": "Stack[-0x3c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_40",
      "storage": "Stack[-0x40]:4",
      "type": "undefined4"
    },
    {
      "name": "local_44",
      "storage": "Stack[-0x44]:4",
      "type": "undefined4"
    },
    {
      "name": "local_48",
      "storage": "Stack[-0x48]:4",
      "type": "undefined4"
    },
    {
      "name": "local_4c",
      "storage": "Stack[-0x4c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_58",
      "storage": "Stack[-0x58]:4",
      "type": "undefined4"
    },
    {
      "name": "local_5c",
      "storage": "Stack[-0x5c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_60",
      "storage": "Stack[-0x60]:4",
      "type": "undefined4"
    },
    {
      "name": "local_64",
      "storage": "Stack[-0x64]:4",
      "type": "undefined4"
    },
    {
      "name": "local_68",
      "storage": "Stack[-0x68]:4",
      "type": "undefined4"
    },
    {
      "name": "local_6c",
      "storage": "Stack[-0x6c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_70",
      "storage": "Stack[-0x70]:4",
      "type": "undefined4"
    },
    {
      "name": "local_74",
      "storage": "Stack[-0x74]:4",
      "type": "undefined4"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "undefined4"
    },
    {
      "name": "local_7c",
      "storage": "Stack[-0x7c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_80",
      "storage": "Stack[-0x80]:4",
      "type": "undefined4"
    },
    {
      "name": "local_84",
      "storage": "Stack[-0x84]:4",
      "type": "undefined4"
    },
    {
      "name": "local_98",
      "storage": "Stack[-0x98]:4",
      "type": "undefined4"
    },
    {
      "name": "local_9c",
      "storage": "Stack[-0x9c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a0",
      "storage": "Stack[-0xa0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a4",
      "storage": "Stack[-0xa4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a8",
      "storage": "Stack[-0xa8]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 25,
  "mode": "live",
  "name": "FUN_00c32cd0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x832cd0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c32cd0(void)",
  "size_bytes": 1473,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c32cd0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 35,
  "xrefs": [
    {
      "from": "00c33769"
    },
    {
      "from": "00c7383e"
    },
    {
      "from": "00c738c6"
    },
    {
      "from": "00aec240"
    },
    {
      "from": "00aec27e"
    },
    {
      "from": "00aec2f0"
    },
    {
      "from": "00aec346"
    },
    {
      "from": "00dd4c41"
    },
    {
      "from": "00dd4d48"
    },
    {
      "from": "01005253"
    },
    {
      "from": "01047281"
    },
    {
      "from": "0104211b"
    },
    {
      "from": "00c33606"
    },
    {
      "from": "0106bc27"
    },
    {
      "from": "0106d1a5"
    },
    {
      "from": "00b679e3"
    },
    {
      "from": "00ba019d"
    },
    {
      "from": "01042247"
    },
    {
      "from": "00cc2561"
    },
    {
      "from": "00e06dfc"
    },
    {
      "from": "00e06e21"
    },
    {
      "from": "00e06e48"
    },
    {
      "from": "00e071bf"
    },
    {
      "from": "00e91166"
    },
    {
      "from": "00e9ac82"
    },
    {
      "from": "01072d04"
    },
    {
      "from": "0104796e"
    },
    {
      "from": "01047f46"
    },
    {
      "from": "01047f69"
    },
    {
      "from": "0106a8d0"
    },
    {
      "from": "00feb69a"
    },
    {
      "from": "010473d6"
    },
    {
      "from": "01048a71"
    },
    {
      "fro
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
  "files": [
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3.cpp",
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3.hpp",
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3_boundary_test.sh",
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3_model_test.cpp",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3.cpp",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3.hpp",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3_boundary_test.sh",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-e4-empire-wave3/00c32cd0.json"
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
  "OpaqueFloatColor*",
  "OpaqueRecord*"
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
