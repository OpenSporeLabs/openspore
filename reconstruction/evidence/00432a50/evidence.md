# Evidence 0x00432a50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b4ae9b77e5d6d01418e9afe7494810c908ef45ca88cf1536954c4996f0617e15`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "receiver_register": "ECX",
  "return_register": "EAX",
  "return_type": "std::uint32_t",
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "termination": "RET"
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
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBP"
    ],
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
  "content_sha256": "f4a74022a9c91276a46083b24f7a9d7258b63b9f0a48d0c977cc99f3a6b9fab3",
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
    "ghidra_parameter_count": 1,
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
        "obs-0014"
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
        "obs-0005",
        "obs-0006",
        "obs-0009",
        "obs-0010",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0014"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0014"
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
        "obs-0014"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0014"
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
      "at": "0x00432a50",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00432a50",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00432a51",
      "count": 1,
      "first_use": 1,
      "first_write_index": 10,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x00432a51",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x00432a53",
      "count": 4,
      "first_use": 2,
      "first_write_index": 6,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00432a54",
      "base": "EBP",
      "disp": -4,
      "id": "obs-0006",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x4],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00432a57",
      "base": "EBP",
      "disp": -4,
      "id": "obs-0007",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + -0x4]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00432a57",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + -0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00432a5d",
      "definite": true,
      "id": "obs-0009",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,0x1",
      "reg": "ECX",
      "write_kind": "imm"
    },
    {
      "at": "0x00432a62",
      "count": 1,
      "first_use": 7,
      "first_write_index": 4,
      "id": "obs-0010",
      "index": 7,
      "kind": "REG_READ",
      "raw": "XADD.LOCK dword ptr [EAX],ECX",
      "reg": "EAX"
    },
    {
      "at": "0x00432a62",
      "clobbers": [
        "EAX",
        "ECX"
      ],
      "form": "XADD.LOCK",
      "id": "obs-0011",
      "index": 7,
      "kind": "STRING_OP",
      "raw": "XADD.LOCK dword ptr [EAX],ECX",
      "rep": false,
      "string_base": false
    },
    {
      "at": "0x00432a69",
      "def
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
    "va": "0x00404660"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040f4a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040f820"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040fc00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005598b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057a710"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057f6c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005a5960"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005a9200"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dfbb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006145d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0061b9a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00628230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00628340"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00633560"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00640ee0"
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
  "count": 13,
  "instructions": [
    {
      "address": "00432a50",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00432a51",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "00432a53",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00432a54",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "00432a57",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "00432a5a",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "00432a5d",
      "instruction": "MOV ECX,0x1"
    },
    {
      "address": "00432a62",
      "instruction": "XADD.LOCK dword ptr [EAX],ECX"
    },
    {
      "address": "00432a66",
      "instruction": "INC ECX"
    },
    {
      "address": "00432a67",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "00432a69",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "00432a6b",
      "instruction": "POP EBP"
    },
    {
      "address": "00432a6c",
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
  "original_bytes": 17112,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"receiver_register\": \"ECX\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"std::uint32_t\",\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 14,\n      \"symbol\": \"wave6_fixed_pool_allocator_alloc_00926100\",\n      \"va\": \"0x00926100\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 14,\n      \"symbol\": \"wave6_fixed_pool_allocator_free_00926140\",\n      \"va\": \"0x00926140\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014186c4\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01409bec,vtable:0x014186c4\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff508\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00801ac0\",\n      \"va\": \"0x00801ac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 2,\n      \"symbol\": \"transform_pre_transform_by_0040ccb0\",\n      \"va\": \"0x0040ccb0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-RESOURCE-ADAPTER\",\n      \"score\": 2,\n      \"symbol\": \"TexturePtr_Set\",\n      \"va\": \"0x00576650\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The signed 32-bit count offset, locked increment, return value, wraparound, and no-direct-callee contract are exact; concrete owner and runtime concurrency remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"No original-process runtime trace is available for concurrent callers.\",\n    \"The package model exposes only the observed four-byte count prefix and does not synthesize a complete ResourceManager type.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"Wave6ReferenceCounted\",\n  \"cluster\": \"unknown-vtable-impl\",\n  \"confidence\": 0.98,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00404660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040f4a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040f820\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040fc00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005598b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057a710\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057f6c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005a5960\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005a9200\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dfbb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006145d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0061b9a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00628230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00628340\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00633560\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00640ee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006af260\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006b6d10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006e3100\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006e4210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076bc91\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076c210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076ce50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076dee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b7ac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00
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
  "body_end": "00432a6c",
  "body_span_bytes": 29,
  "body_start": "00432a50",
  "callees": [],
  "callers": [
    "FUN_00d0e170",
    "FUN_00fa9790",
    "FUN_00adb700",
    "FUN_00ada360",
    "FUN_00cf1f50",
    "FUN_005a5960",
    "FUN_00ade1d0",
    "FUN_0076bc91",
    "FUN_007c8940",
    "FUN_0057a710",
    "FUN_00bff2d0",
    "FUN_00adcd10",
    "FUN_00628230",
    "FUN_00813e70",
    "FUN_0061b9a0",
    "FUN_007bbde0",
    "FUN_0081e230",
    "FUN_007bbf80",
    "FUN_00e20860",
    "FUN_00add060",
    "FUN_00eea260",
    "FUN_0040fc00",
    "FUN_00404660",
    "FUN_00eb1dc0",
    "FUN_00fa9b50",
    "FUN_00b50f40",
    "FUN_007b7ac0",
    "FUN_00fe5a20",
    "FUN_00ad9a30",
    "FUN_00d3c6a0",
    "FUN_006e4210",
    "FUN_007bea00",
    "FUN_007bfee0",
    "FUN_00e248b0",
    "FUN_007bced0",
    "FUN_007c1c10",
    "FUN_0040f4a0",
    "FUN_00633560",
    "FUN_0057f6c0",
    "FUN_007be430",
    "FUN_00c34320",
    "FUN_007bf720",
    "FUN_00628340",
    "FUN_005a9200",
    "FUN_00a25090",
    "FUN_00adac70",
    "FUN_00ada7e0",
    "FUN_00adcfc0",
    "FUN_00a417b0",
    "FUN_007bb670",
    "FUN_0076c210",
    "FUN_00adbaa0",
    "FUN_005dfbb0",
    "UTFWin::cCursorManager::ShowDropCursorIcon",
    "FUN_006145d0",
    "FUN_00adb8d0",
    "FUN_00a31170",
    "FUN_00ea2a60",
    "FUN_007c0780",
    "FUN_00adaad0",
    "FUN_00fa0560",
    "FUN_006af260",
    "FUN_00ad95c0",
    "FUN_0076ce50",
    "FUN_00deb840",
    "FUN_00ada250",
    "FUN_00ada4b0",
    "FUN_00640ee0",
    "FUN_007bedb0",
    "FUN_00e24700",
    "FUN_00ada110",
    "FUN_00ccaff0",
    "FUN_006b6d10",
    "FUN_00ccef10",
    "FUN_00ad9860",
    "FUN_00ad9ff0",
    "FUN_0076dee0",
    "FUN_00e4b730",
    "FUN_006e3100",
    "FUN_0040f820",
    "FUN_00ada880",
    "FUN_005598b0",
    "FUN_00e629a0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00432a50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "informative",
  "ghidra_has_calling_convention": true,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "Reference",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "ECX:4 (auto)",
      "type": "ResourceManager *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "uint",
  "return_type_resolved": true,
  "rva": "0x32a50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "uint Reference(ResourceManager * this)",
  "size_bytes": 29,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00432a50",
  "vtables": {
    "referenced_by_vtables": [
      "0x014186c4",
      "0x013ff508",
      "0x0140944c",
      "0x014529fc",
      "0x014626b8",
      "0x0140e09c",
      "0x01465fd0",
      "0x013ebca4",
      "0x013eff40",
      "0x013f3d44",
      "0x01409bec",
      "0x014158f8",
      "0x014527b8",
      "0x01452b00",
      "0x0148b040",
      "0x013eb90c",
      "0x013f3d84",
      "0x013fc06c",
      "0x013fe50c",
      "0x014095cc"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00adb919"
    },
    {
      "from": "0061ba6f"
    },
    {
      "from": "00adbae9"
    },
    {
      "from": "007bbf1b"
    },
    {
      "from": "007bccd4"
    },
    {
      "from": "007bbc40"
    },
    {
      "from": "007bbc76"
    },
    {
      "from": "00adb749"
    },
    {
      "from": "00ada8c1"
    },
    {
      "from": "00adab1a"
    },
    {
      "from": "00adacb1"
    },
    {
      "from": "00ada15e"
    },
    {
      "from": "00ada2a7"
    },
    {
      "from": "00ada4fa"
    },
    {
      "from": "00ada82a"
    },
    {
      "from": "0057a787"
    },
    {
      "from": "0057a833"
    },
    {
      "from": "0057a8de"
    },
    {
      "from": "00ad98ac"
    },
    {
      "from": "00559cbc"
    },
    {
      "from": "00ad9bc0"
    },
    {
      "from": "00ad9601"
    },
    {
      "from": "007c0618"
    },
    {
      "from": "00bff673"
    },
    {
      "from": "0058015e"
    },
    {
      "from": "007becdb"
    },
    {
      "from": "007bf223"
    },
    {
      "from": "00ade344"
    },
    {
      "from": "0081e27a"
    },
    {
      "from": "007be901"
    },
    {
      "from": "00adcd69"
    },
    {
      "from": "007bd387"
    },
    {
      "from": "00add010"
    },
    {
      "from": "00d3c91a"
    },
    {
      "from": "00813f3e"
    },
    {
      "from": "006336c3"
    },
    {
      "from": "00eb1e34"
    },
    {
      "from": "00cf1fb1"
    },
    {
      "from": "00a3125f"
    },
    {
      "from": "00b50f8e"
    },
    {
      "from": "00b50fb9"
    },
    {
      "from": "007b7b4b"
    },
    {
      "from": "006b6db6"
    },
    {
      "from": "00c34397"
    },
    {
      "from": "00614632"
    },
    {
      "from": "00deb8ca"
    },
    {
      "from": "0076c126"
    },
    {
      "from": "00e4b7e1"
    },
    {
      "from": "00ccb086"
    },
    {
      "from": "00eea2af"
    },
    {
      "from": "00fa9cb1"
    },
    {
      "from": "005a92c3"
    },
    {
      "from": "00fa97e1"
    },
    {
      "from": "007c8a70"
    },
    {
      "from": "0040f8ad"
    },
    {
      "from": "0040fcf2"
    },
    {
      "from": "006af3d3"
    },
    {
      "from": "0040f6d4"
    },
    {
      "from": "00ccef74"
    },
    {
      "from": "00d0fc79"
    },
    {
      "from": "0076dfa0"
    },
    {
      
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
  "file": "src/reconstruction/wave6_containers_memory/containers_memory.cpp",
  "files": [
    "reconstruction/staging/wave6-containers-memory/containers_memory.cpp",
    "reconstruction/staging/wave6-containers-memory/containers_memory.hpp",
    "reconstruction/staging/wave6-containers-memory/containers_memory_model_test.cpp",
    "src/reconstruction/wave6_containers_memory/containers_memory.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-containers-memory/00432a50.json"
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
    "gate-reference-count-concurrency-and-lifetime"
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
  "Wave6ReferenceCounted",
  "std::uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013eb90c",
  "vtable:0x013ebca4",
  "vtable:0x013eff40",
  "vtable:0x013f3d44",
  "vtable:0x013f3d84",
  "vtable:0x013fc06c",
  "vtable:0x013fe50c",
  "vtable:0x013ff508",
  "vtable:0x0140944c",
  "vtable:0x014095cc",
  "vtable:0x01409bec",
  "vtable:0x0140a278",
  "vtable:0x0140c60c",
  "vtable:0x0140e09c",
  "vtable:0x01414a1c",
  "vtable:0x014158f8"
]
```

## Conflicts

```json
[]
```
