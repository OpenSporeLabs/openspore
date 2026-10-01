# Evidence 0x00be2440

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a86e1e473bbefc677e19b988d58849bf82d22dd0fe4631ecc3913e743311976d`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl",
  "hidden_this_register": null,
  "ordinary_stack_arguments": [
    {
      "name": "city",
      "offset": 4,
      "type": "OpaqueCity*",
      "width_bytes": 4
    },
    {
      "name": "live_state",
      "offset": 8,
      "type": "OpaqueLiveStateContext*",
      "width_bytes": 4
    },
    {
      "name": "update_word",
      "offset": 12,
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "termination": "plain RET"
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
    "ret_form": "RET",
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
        "size_inferred": false,
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "unparsed_lines_present: 2 line(s) matched no grammar rule",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "9b9ef901b93ddcc910a93b14ae7aa308da8dfbb80ef6f20021f0314da08e2ce7",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "persisted_calling_convention": "cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0193"
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
        "obs-0086",
        "obs-0088"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0086",
        "obs-0087",
        "obs-0090",
        "obs-0091",
        "obs-0096",
        "obs-0114",
        "obs-0116",
        "obs-0131",
        "obs-0132",
        "obs-0133",
        "obs-0134",
        "obs-0135",
        "obs-0137",
        "obs-0144",
        "obs-0145",
        "obs-0169",
        "obs-0173",
        "obs-0178",
        "obs-0179",
        "obs-0185"
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
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0193"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "id": "obs-0001"
    },
    {
      "id": "obs-0002"
    },
    {
      "id": "obs-0003"
    },
    {
      "id": "obs-0004"
    },
    {
      "id": "obs-0005"
    },
    {
      "id": "obs-0006"
    },
    {
      "id": "obs-0007"
    },
    {
      "id": "obs-0008"
    },
    {
      "id": "obs-0009"
    },
    {
      "id": "obs-0010"
    },
    {
      "id": "obs-0011"
    },
    {
      "id": "obs-0012"
    },
    {
      "id": "obs-0013"
    },
    {
      "id": "obs-0014"
    },
    {
      "id": "obs-0015"
    },
    {
      "id": "obs-0016"
    },
    {
      "id": "obs-0017"
    },
    {
      "id": "obs-0018"
    },
    {
      "id": "obs-0019"
    },
    {
      "id": "obs-0020"
    },
    {
      "id": "obs-0021"
    },
    {
      "id": "obs-0022"
    },
    {
      "id": "obs-0023"
    },
    {
      "id": "obs-0024"
    },
    {
      "id": "obs-0025"
    },
    {
      "id": "obs-0026"
    },
    {
      "id": "obs-0027"
    },
    {
      "id": "obs-0028"
    },
    {
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id"
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
    "va": "0x00bcc760"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bcece0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be3350"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be3500"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be3de0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be5180"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be5dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be92e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d0e170"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d10840"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d10f90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ff1da0"
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
  "count": 428,
  "instructions": [
    {
      "address": "00be2440",
      "instruction": "SUB ESP,0x210"
    },
    {
      "address": "00be2446",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00be2448",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00be2449",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00be244a",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00be244b",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00be244c",
      "instruction": "PUSH 0xc4"
    },
    {
      "address": "00be2451",
      "instruction": "MOV dword ptr [ESP + 0xb8],EAX"
    },
    {
      "address": "00be2458",
      "instruction": "MOV dword ptr [ESP + 0xbc],EAX"
    },
    {
      "address": "00be245f",
      "instruction": "MOV dword ptr [ESP + 0xc0],EAX"
    },
    {
      "address": "00be2466",
      "instruction": "MOV dword ptr [ESP + 0xc4],EAX"
    },
    {
      "address": "00be246d",
      "instruction": "MOV dword ptr [ESP + 0xc8],EAX"
    },
    {
      "address": "00be2474",
      "instruction": "MOV dword ptr [ESP + 0xcc],EAX"
    },
    {
      "address": "00be247b",
      "instruction": "MOV dword ptr [ESP + 0xd0],EAX"
    },
    {
      "address": "00be2482",
      "instruction": "MOV dword ptr [ESP + 0xd4],EAX"
    },
    {
      "address": "00be2489",
      "instruction": "MOV dword ptr [ESP + 0xd8],EAX"
    },
    {
      "address": "00be2490",
      "instruction": "MOV dword ptr [ESP + 0xdc],EAX"
    },
    {
      "address": "00be2497",
      "instruction": "MOV dword ptr [ESP + 0xe0],EAX"
    },
    {
      "address": "00be249e",
      "instruction": "MOV dword ptr [ESP + 0xe4],EAX"
    },
    {
      "address": "00be24a5",
      "instruction": "MOV dword ptr [ESP + 0xe8],EAX"
    },
    {
      "address": "00be24ac",
      "instruction": "MOV dword ptr [ESP + 0xec],EAX"
    },
    {
      "address": "00be24b3",
      "instruction": "MOV dword ptr [ESP + 0x80],EAX"
    },
    {
      "address": "00be24ba",
      "instruction": "MOV dword ptr [ESP + 0x84],EAX"
    },
    {
      "address": "00be24c1",
      "instruction": "MOV dword ptr [ESP + 0x88],EAX"
    },
    {
      "address": "00be24c8",
      "instruction": "MOV dword ptr [ESP + 0x8c],EAX"
    },
    {
      "address": "00be24cf",
      "instruction": "MOV dword ptr [ESP + 0x90],EAX"
    },
    {
      "address": "00be24d6",
      "instruction": "MOV dword ptr [ESP + 0x94],EAX"
    },
    {
      "address": "00be24dd",
      "instruction": "MOV dword ptr [ESP + 0x98],EAX"
    },
    {
      "address": "00be24e4",
      "instruction": "MOV dword ptr [ESP + 0x9c],EAX"
    },
    {
      "address": "00be24eb",
      "instruction": "MOV dword ptr [ESP + 0xa0],EAX"
    },
    {
      "address": "00be24f2",
      "instruction": "MOV dword ptr [ESP + 0xa4],EAX"
    },
    {
      "address": "00be24f9",
      "instruction": "MOV dword ptr [ESP + 0xa8],EAX"
    },
    {
      "address": "00be2500",
      "instruction": "MOV dword ptr [ESP + 0xac],EAX"
    },
    {
      "address": "00be2507",
      "instruction": "MOV dword ptr [ESP + 0xb0],EAX"
    },
    {
      "address": "00be250e",
      "instruction": "MOV dword ptr [ESP + 0xb4],EAX"
    },
    {
      "address": "00be2515",
      "instruction": "MOV dword ptr [ESP + 0xf0],EAX"
    },
    {
      "address": "00be251c",
      "instruction": "MOV dword ptr [ESP + 0xf4],EAX"
    },
    {
      "address": "00be2523",
      "instruction": "MOV dword ptr [ESP + 0xf8],EAX"
    },
    {
      "address": "00be252a",
      "instruction": "MOV dword ptr [ESP + 0xfc],EAX"
    },
    {
      "address": "00be2531",
      "instruction": "MOV dword ptr [ESP + 0x100],EAX"
    },
    {
      "address": "00be2538",
      "instruction": "MOV dword ptr [ESP + 0x104],EAX"
    },
    {
      "address": "00be253f",
      "instruction": "MOV dword ptr [ESP + 0x108],EAX"
    },
    {
      "address": "00be2546",
      "instruction": "MOV dword ptr [ESP + 0x10c],EAX"
    },
    {
      "address": "00be254d",
      "instruction": "MOV dword ptr [ESP + 0x110],EAX"
    },
    {
      "address": "00be2554",
      "instruction": "MOV dword ptr [ESP + 0x114],EAX"
    },
    {
      "address": "00be255b",
      "instruction": "MOV dword ptr [ESP + 0x118],EAX"
    },
    {
      "address": "00be2562",
      "instruction": "MOV dword ptr [ESP + 0x11c],EAX"
    },
    {
      "address": "00be2569",
      "instruction": "MOV dword ptr [ESP + 0x120],EAX"
    },
    {
      "address": "00be2570",
      "instruction": "MOV dword ptr [ESP + 0x124],EAX"
    },
    {
      "address": "00be2577",
      "instruction": "MOV dword ptr [ESP + 0x128],EAX"
    },
    {
      "address": "00be257e",
      "instruction": "MOV dword ptr [ESP + 0x12c],EAX"
    },
    {
      "address": "00be2585",
      "instruction": "MOV dword ptr [ESP + 0x130],EAX"
    },
    {
      "address": "00be258c",
      "instruction": "MOV dword ptr [ESP + 0x134],EAX"
    },
    {
      "address": "00be2593",
      "instruction": "MOV dword ptr [ESP + 0x138],EAX"
    },
    {
      "address": "00be259a",
      "instruction": "MOV dword ptr [ESP + 0x13c],EAX"
    },
    {
      "address": "00be25a1",
      "instruction": "MOV dword ptr [ESP + 0x140],EAX"
    },
    {
      "address": "00be25a8",
      "instruction": "MOV dword ptr [ESP + 0x144],EAX"
    },
    {
      "address": "00be25af",
      "instruction": "MOV dword ptr [ESP + 0x148],EAX"
    },
    {
      "address": "00be25b6",
      "instruction": "MOV dword ptr [ESP + 0x14c],EAX"
    },
    {
      "address": "00be25bd",
      "instruction": "MOV dword ptr [ESP + 0x150],EAX"
    },
    {
      "address": "00be25c4",
      "instruction": "MOV dword ptr [ESP + 0x154],EAX"
    },
    {
      "address": "00be25cb",
      "instruction": "MOV dword ptr [ESP + 0x158],EAX"
    },
    {
      "address": "00be25d2",
      "instruction": "MOV dword ptr [ESP + 0x15c],EAX"
    },
    {
      "address": "00be25d9",

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
  "original_bytes": 9963,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl\",\n    \"hidden_this_register\": null,\n    \"ordinary_stack_arguments\": [\n      {\n        \"name\": \"city\",\n        \"offset\": 4,\n        \"type\": \"OpaqueCity*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"name\": \"live_state\",\n        \"offset\": 8,\n        \"type\": \"OpaqueLiveStateContext*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"name\": \"update_word\",\n        \"offset\": 12,\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"termination\": \"plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-13-C4-CIV-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"culture_selection_00bf9820\",\n      \"va\": \"0x00bf9820\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-14-A3-WORLD-WAVE3\",\n      \"score\": 2,\n      \"symbol\": \"sphere_draw_direction_00b7e560\",\n      \"va\": \"0x00b7e560\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 2,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 2,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 2,\n      \"symbol\": \"PoliticalOwnershipScan_00c8d060\",\n      \"va\": \"0x00c8d060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 2,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"cell_mode_constructor_00e616c0\",\n      \"va\": \"0x00e616c0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bcc760\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bcece0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be3350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be3500\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be3de0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be5180\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be5dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be92e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d0e170\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d10840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d10f90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ff1da0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00bcc7c4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bcc760\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bced59\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bcece0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bcf465\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bcece0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be33c4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be3350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be36ec\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be3500\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be3e7e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be3de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be526c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be5180\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be605b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be5dd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be954d\",\n    
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
  "body_end": "00be2b0b",
  "body_span_bytes": 1740,
  "body_start": "00be2440",
  "callees": [
    "memset",
    "FUN_00be0020",
    "FUN_00fcc210",
    "FUN_00bfc600",
    "FUN_00ff0330",
    "FUN_00af9ff0",
    "FUN_00ff07a0",
    "FUN_00ff08b0",
    "FUN_008e7f80",
    "FUN_00bcc6e0"
  ],
  "callers": [
    "FUN_00be3350",
    "FUN_00be5dd0",
    "FUN_00d0e170",
    "FUN_00bcece0",
    "FUN_00be3de0",
    "FUN_00be92e0",
    "FUN_00d10840",
    "FUN_00bcc760",
    "FUN_00d10f90",
    "FUN_00be3500",
    "FUN_00ff1da0",
    "FUN_00be5180"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00be2440",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c4",
      "storage": "Stack[-0xc4]:1",
      "type": "undefined"
    },
    {
      "name": "local_c8",
      "storage": "Stack[-0xc8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_cc",
      "storage": "Stack[-0xcc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_d0",
      "storage": "Stack[-0xd0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_d4",
      "storage": "Stack[-0xd4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_d8",
      "storage": "Stack[-0xd8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_dc",
      "storage": "Stack[-0xdc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_e0",
      "storage": "Stack[-0xe0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_e4",
      "storage": "Stack[-0xe4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_e8",
      "storage": "Stack[-0xe8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_ec",
      "storage": "Stack[-0xec]:4",
      "type": "undefined4"
    },
    {
      "name": "local_f0",
      "storage": "Stack[-0xf0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_f4",
      "storage": "Stack[-0xf4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_f8",
      "storage": "Stack[-0xf8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_fc",
      "storage": "Stack[-0xfc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_100",
      "storage": "Stack[-0x100]:4",
      "type": "undefined4"
    },
    {
      "name": "local_104",
      "storage": "Stack[-0x104]:4",
      "type": "undefined4"
    },
    {
      "name": "local_108",
      "storage": "Stack[-0x108]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10c",
      "storage": "Stack[-0x10c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_110",
      "storage": "Stack[-0x110]:4",
      "type": "undefined4"
    },
    {
      "name": "local_114",
      "storage": "Stack[-0x114]:4",
      "type": "undefined4"
    },
    {
      "name": "local_118",
      "storage": "Stack[-0x118]:4",
      "type": "undefined4"
    },
    {
      "name": "local_11c",
      "storage": "Stack[-0x11c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_120",
      "storage": "Stack[-0x120]:4",
      "type": "undefined4"
    },
    {
      "name": "local_124",
      "storage": "Stack[-0x124]:4",
      "type": "undefined4"
    },
    {
      "name": "local_128",
      "storage": "Stack[-0x128]:4",
      "type": "undefined4"
    },
    {
      "name": "local_12c",
      "storage": "Stack[-0x12c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_130",
      "storage": "Stack[-0x130]:4",
      "type": "undefined4"
    },
    {
      "name": "local_134",
      "storage": "Stack[-0x134]:4",
      "type": "undefined4"
    },
    {
      "name": "local_138",
      "storage": "Stack[-0x138]:4",
      "type": "undefined4"
    },
    {
      "name": "local_13c",
      "storage": "Stack[-0x13c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_140",
      "storage": "Stack[-0x140]:4",
      "type": "undefined4"
    },
    {
      "name": "local_144",
      "storage": "Stack[-0x144]:4",
      "type": "undefined4"
    },
    {
      "name": "local_148",
      "storage": "Stack[-0x148]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14c",
      "storage": "Stack[-0x14c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_150",
      "storage": "Stack[-0x150]:4",
      "type": "undefined4"
    },
    {
      "name": "local_154",
      "storage": "Stack[-0x154]:4",
      "type": "undefined4"
    },
    {
      "name": "local_158",
      "storage": "Stack[-0x158]:4",
      "type": "undefined4"
    },
    {
      "name": "local_15c",
      "storage": "Stack[-0x15c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_160",
      "storage": "Stack[-0x160]:4",
      "type": "undefined4"
    },
    {
      "name": "local_164",
      "storage": "Stack[-0x164]:4",
      "type": "undefined4"
    },
    {
      "name": "local_168",
      "storage": "Stack[-0x168]:4",
      "type": "undefined4"
    },
    {
      "name": "local_16c",
      "storage": "Stack[-0x16c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_170",
      "storage": "Stack[-0x170]:4",
      "type": "undefined4"
    },
    {
      "name": "local_174",
      "storage": "Stack[-0x174]:4",
      "type": "undefined4"
    },
    {
      "name": "local_178",
      "storage": "Stack[-0x178]:4",
      "type": "undefined4"
    },
    {
      "name": "local_17c",
      "storage": "Stack[-0x17c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_180",
      "storage": "Stack[-0x180]:4",
      "type": "undefined4"
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
  "files": [
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.cpp",
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.hpp",
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c4-civ-wave3/00be2440.json"
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
  "OpaqueCity*",
  "OpaqueLiveStateContext*",
  "uint32_t",
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
