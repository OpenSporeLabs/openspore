# Evidence 0x00e7a190

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `571109c7c062cb6ffade3be590535c737bc318cbf1bf8ed96876192098e0796e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "convention": "custom register-and-stack convention; no standard Ghidra prototype is assigned",
  "return": "void-like; all visible exits use RET without a target-specific return-value contract",
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
      "entry_ESP+0x4",
      "entry_ESP+0xc"
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
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
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -476, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [
    {
      "field": "stack_cleanup_bytes",
      "inferred": 0,
      "kind": "inferred_vs_persisted",
      "persisted": 4,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "782fd7d5b6d5e3986b259977e8ce8a09ba18e54393844f56433d7bf481671b28",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0018",
        "obs-0038",
        "obs-0045",
        "obs-0052",
        "obs-0061",
        "obs-0068",
        "obs-0075",
        "obs-0082",
        "obs-0089",
        "obs-0096",
        "obs-0103",
        "obs-0110",
        "obs-0117",
        "obs-0124",
        "obs-0131",
        "obs-0138"
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
        "obs-0013",
        "obs-0025",
        "obs-0030",
        "obs-0032",
        "obs-0039",
        "obs-0040",
        "obs-0046",
        "obs-0047",
        "obs-0055",
        "obs-0056",
        "obs-0062",
        "obs-0063",
        "obs-0069",
        "obs-0070",
        "obs-0076",
        "obs-0077",
        "obs-0083",
        "obs-0084",
        "obs-0090",
        "obs-0091",
        "obs-0097",
        "obs-0098",
        "obs-0104",
        "obs-0105",
        "obs-0111",
        "obs-0112",
        "obs-0118",
        "obs-0119",
        "obs-0125",
        "obs-0126",
        "obs-0132",
        "obs-0133"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 89,
        "observed_slots": 31,
        "total_bytes": 480
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0010",
        "obs-0023"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          274,
          364,
          396
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0010",
        "obs-0018",
        "obs-0023",
        "obs-0038",
        "obs-0045",
        "obs-0052",
        "obs-0061",
        "obs-0068",
        "obs-0075",
        "obs-0082",
        "obs-0089",
        "obs-0096",
        "obs-0103",
        "obs-0110",
        "obs-0117",
        "obs-0124",
        "obs-0131",
        "obs-0138"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0038",
        "obs-0045",
        "obs-0052",
        "obs-0061",
        "obs-0068",
        "obs-0075",
        "obs-0082",
        "obs-0089",
        "obs-0096",
        "obs-0103",
        "obs-0110",
        "obs-0117",
       
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "cell_ai_select_profile_00e52910",
    "reconstructed": true,
    "va": "0x00e52910"
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
    "va": "0x00e7c8c0"
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
  "count": 265,
  "instructions": [
    {
      "address": "00e7a190",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "00e7a193",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7a194",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00e7a196",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7a19c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a19d",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00e7a19f",
      "instruction": "MOV EAX,dword ptr [ECX + 0x5190]"
    },
    {
      "address": "00e7a1a5",
      "instruction": "MOV EAX,dword ptr [EAX + 0x7c]"
    },
    {
      "address": "00e7a1a8",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "00e7a1ab",
      "instruction": "JZ 0x00e7a1bf"
    },
    {
      "address": "00e7a1ad",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00e7a1b0",
      "instruction": "JZ 0x00e7a1ca"
    },
    {
      "address": "00e7a1b2",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00e7a1b5",
      "instruction": "JNZ 0x00e7a1ca"
    },
    {
      "address": "00e7a1b7",
      "instruction": "LEA EAX,[EDI + 0x194]"
    },
    {
      "address": "00e7a1bd",
      "instruction": "JMP 0x00e7a1c5"
    },
    {
      "address": "00e7a1bf",
      "instruction": "LEA EAX,[EDI + 0x248]"
    },
    {
      "address": "00e7a1c5",
      "instruction": "CMP dword ptr [EAX],-0x1"
    },
    {
      "address": "00e7a1c8",
      "instruction": "JNZ 0x00e7a1d0"
    },
    {
      "address": "00e7a1ca",
      "instruction": "LEA EAX,[EDI + 0xe0]"
    },
    {
      "address": "00e7a1d0",
      "instruction": "CMP dword ptr [EAX],0x0"
    },
    {
      "address": "00e7a1d3",
      "instruction": "JNZ 0x00e7a1e3"
    },
    {
      "address": "00e7a1d5",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00e7a1d7",
      "instruction": "CMP EDX,dword ptr [ECX + 0x411c]"
    },
    {
      "address": "00e7a1dd",
      "instruction": "JNZ 0x00e7a456"
    },
    {
      "address": "00e7a1e3",
      "instruction": "FLD float ptr [ESP + 0x20]"
    },
    {
      "address": "00e7a1e7",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7a1e8",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7a1eb",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a1ec",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00e7a1ee",
      "instruction": "CALL 0x00e76a80"
    },
    {
      "address": "00e7a1f3",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e7a1f6",
      "instruction": "CMP byte ptr [ESI + 0x112],0x0"
    },
    {
      "address": "00e7a1fd",
      "instruction": "JZ 0x00e7a218"
    },
    {
      "address": "00e7a1ff",
      "instruction": "CMP dword ptr [ESI + 0x18c],0x8"
    },
    {
      "address": "00e7a206",
      "instruction": "JZ 0x00e7a218"
    },
    {
      "address": "00e7a208",
      "instruction": "POP EDI"
    },
    {
      "address": "00e7a209",
      "instruction": "MOV dword ptr [ESI + 0x18c],0xa"
    },
    {
      "address": "00e7a213",
      "instruction": "POP ESI"
    },
    {
      "address": "00e7a214",
      "instruction": "ADD ESP,0x14"
    },
    {
      "address": "00e7a217",
      "instruction": "RET"
    },
    {
      "address": "00e7a218",
      "instruction": "CMP byte ptr [ESI + 0x16c],0x0"
    },
    {
      "address": "00e7a21f",
      "instruction": "JNZ 0x00e7a456"
    },
    {
      "address": "00e7a225",
      "instruction": "MOV EDX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7a22b",
      "instruction": "CMP byte ptr [EDX + 0x51db],0x1"
    },
    {
      "address": "00e7a232",
      "instruction": "JNZ 0x00e7a242"
    },
    {
      "address": "00e7a234",
      "instruction": "MOV EAX,dword ptr [EDX + 0x411c]"
    },
    {
      "address": "00e7a23a",
      "instruction": "CMP EAX,dword ptr [ESI]"
    },
    {
      "address": "00e7a23c",
      "instruction": "JZ 0x00e7a456"
    },
    {
      "address": "00e7a242",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e7a243",
      "instruction": "MOV EBX,dword ptr [ESI]"
    },
    {
      "address": "00e7a245",
      "instruction": "CMP EBX,dword ptr [EDX + 0x51b0]"
    },
    {
      "address": "00e7a24b",
      "instruction": "JNZ 0x00e7a2d8"
    },
    {
      "address": "00e7a251",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a252",
      "instruction": "CALL 0x00e52910"
    },
    {
      "address": "00e7a257",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e7a259",
      "instruction": "MOVSS XMM0,dword ptr [ECX + 0x1c]"
    },
    {
      "address": "00e7a25e",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7a261",
      "instruction": "UCOMISS XMM0,dword ptr [0x01485378]"
    },
    {
      "address": "00e7a268",
      "instruction": "LAHF"
    },
    {
      "address": "00e7a269",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00e7a26c",
      "instruction": "JP 0x00e7a273"
    },
    {
      "address": "00e7a26e",
      "instruction": "MOVSS XMM0,dword ptr [ECX + 0x18]"
    },
    {
      "address": "00e7a273",
      "instruction": "CMP dword ptr [EDX + 0x51b4],0x3"
    },
    {
      "address": "00e7a27a",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM0"
    },
    {
      "address": "00e7a280",
      "instruction": "JNZ 0x00e7a2d8"
    },
    {
      "address": "00e7a282",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7a283",
      "instruction": "CALL 0x00e52910"
    },
    {
      "address": "00e7a288",
      "instruction": "MOVZX ECX,byte ptr [EAX + 0x44]"
    },
    {
      "address": "00e7a28c",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7a28f",
      "instruction": "PUSH ECX"
    },
    
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
  "original_bytes": 13045,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"convention\": \"custom register-and-stack convention; no standard Ghidra prototype is assigned\",\n    \"return\": \"void-like; all visible exits use RET without a target-specific return-value contract\",\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None,ObservedCellCellResource\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-06A-CELL-AI-SELECTION\",\n      \"score\": 14,\n      \"symbol\": \"cell_ai_select_profile_00e52910\",\n      \"va\": \"0x00e52910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_IsNotStarOrBinaryStar\",\n      \"va\": \"0x00c8b6b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The custom EAX-resource, ECX-object, ESP+4-float, caller-cleanup ABI, inline initial profile selection, five early gates, game-global reloads, NaN-sensitive special path, and 14-entry dispatch mapping are observed; canonical type promotion, 17 native ABI ports, handler semantics, and runtime branch outcomes remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_type_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"cell_ai_select_profile_00e52910\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e52910\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7c8c0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e7ca47\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7c8c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a252\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e52910\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a283\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e52910\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a29e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e52910\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a31b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e52910\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a294\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e67c40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a30b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e6f5b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a2c9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e6f800\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a3a7\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e6f990\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a3ef\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e6fbb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a41f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e6fce0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a407\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e6fd70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a376\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e702d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7a35d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e704b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n    
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
  "body_end": "00e7a45b",
  "body_span_bytes": 716,
  "body_start": "00e7a190",
  "callees": [
    "FUN_00e78fc0",
    "FUN_00e6fce0",
    "FUN_00e7a0d0",
    "FUN_00e6fd70",
    "FUN_00e70650",
    "FUN_00e6fbb0",
    "FUN_00e67c40",
    "FUN_00e707d0",
    "FUN_00e6f990",
    "FUN_00e6f800",
    "FUN_00e6f5b0",
    "FUN_00e704b0",
    "FUN_00e702d0",
    "FUN_00e76a80",
    "FUN_00e52910",
    "FUN_00e71300",
    "FUN_00e71c00",
    "FUN_00e7a0a0"
  ],
  "callers": [
    "FUN_00e7c8c0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e7a190",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
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
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_00e7a190",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa7a190",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e7a190(void)",
  "size_bytes": 716,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e7a190",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00e7ca47"
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
  "global:0x00e7a225",
  "global:0x00e7a2a6",
  "global:0x016b3c04"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg06c_cell_behavior_dispatch/cell_behavior_dispatch.cpp",
  "files": [
    "reconstruction/staging/pkg06c-cell-behavior-dispatch/cell_behavior_dispatch.cpp",
    "reconstruction/staging/pkg06c-cell-behavior-dispatch/cell_behavior_dispatch.hpp",
    "reconstruction/staging/pkg06c-cell-behavior-dispatch/cell_behavior_dispatch_model_test.cpp",
    "src/reconstruction/pkg06c_cell_behavior_dispatch/cell_behavior_dispatch.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg06c-cell-behavior-dispatch/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg06c-cell-behavior-dispatch/00e7a190.json"
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
    "gate-cell-behavior-dispatch"
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
  "NativeCallContext",
  "NativePorts&",
  "None",
  "ObservedCellCellResource",
  "ObservedCellCellResource*",
  "ObservedCellObjectData",
  "ObservedCellObjectData*",
  "PKG-06C-CELL-BEHAVIOR-DISPATCH::NativePorts",
  "float"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00e7a45c"
]
```

## Conflicts

```json
[]
```
