# Evidence 0x00bf9820

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e0020591ecc33923c8111f5d0291fd9505381fe6f12f8171f582f3a2f562a845`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall-like",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueCultureSelection* selection",
  "ordinary_stack_arguments": [],
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x8",
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18"
    ],
    "ordinary_stack_arguments": [
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
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
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
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
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
    "flow_not_modelled: the linear ESP walk ends at +56, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched"
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
  "content_sha256": "a01158808dd4c24b1e0c8db6c8c87001866e991c030e8cf6becb2e1542c286db",
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
    "persisted_calling_convention": "thiscall-like"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 14,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0173"
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
        "obs-0035",
        "obs-0036",
        "obs-0039",
        "obs-0040",
        "obs-0042"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 2,
        "observed_slots": 4,
        "total_bytes": 24
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0023",
        "obs-0039",
        "obs-0041",
        "obs-0073",
        "obs-0075",
        "obs-0077",
        "obs-0078",
        "obs-0079",
        "obs-0154"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          137,
          147,
          152,
          156,
          160,
          664,
          1128,
          1196,
          1200
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0023",
        "obs-0039",
        "obs-0041",
        "obs-0073",
        "obs-0075",
        "obs-0077",
        "obs-0078",
        "obs-0079",
        "obs-0154",
        "obs-0173"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0173"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confidence": "APPROXIMATION",
      "id": "S2",
      "value": {
        "present": false
      }
    },

[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "pkg11_sim_core_00b21340",
    "reconstructed": true,
    "va": "0x00b21340"
  },
  {
    "name": "FUN_00b25ca0",
    "reconstructed": false,
    "va": "0x00b25ca0"
  },
  {
    "name": "FUN_00b25fb0",
    "reconstructed": false,
    "va": "0x00b25fb0"
  },
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
  },
  {
    "name": "simulator_game_input_manager_get_00b3d350",
    "reconstructed": true,
    "va": "0x00b3d350"
  },
  {
    "name": "FUN_00b5b800",
    "reconstructed": false,
    "va": "0x00b5b800"
  },
  {
    "name": "FUN_00bd81d0",
    "reconstructed": false,
    "va": "0x00bd81d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd8210"
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
    "va": "0x00bfbbf0"
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
      "0x00b21340",
      "0x00b21340",
      "0x00acd9a0",
      "0x00acd9a0",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00ace2c0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00b25f40",
      "0x00ba0080",
      "0x00ba0080",
      "0x00ba0080",
      "0x00bf9820",
      "0x00bf9820",
      "0x00ba8420"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:0",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e63560",
      "0x00e63560",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00551240",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x00e5c780",
      "0x00e63560",
      "0x00571f80"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:4",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00845310",
      "0x00845310",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x00842d10",
      "0x00844180",
      "0x00843000"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:8",
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
  "count": 480,
  "instructions": [
    {
      "address": "00bf9820",
      "instruction": "SUB ESP,0x20"
    },
    {
      "address": "00bf9823",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bf9824",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bf9825",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bf9826",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00bf9828",
      "instruction": "MOV EAX,dword ptr [ESI + 0xa0]"
    },
    {
      "address": "00bf982e",
      "instruction": "SUB EAX,dword ptr [ESI + 0x9c]"
    },
    {
      "address": "00bf9834",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bf9835",
      "instruction": "TEST EAX,0xfffffffc"
    },
    {
      "address": "00bf983a",
      "instruction": "JZ 0x00bf9e66"
    },
    {
      "address": "00bf9840",
      "instruction": "MOV ECX,dword ptr [ESI + 0x9c]"
    },
    {
      "address": "00bf9846",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00bf9848",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00bf984a",
      "instruction": "MOV dword ptr [ESP + 0x20],EAX"
    },
    {
      "address": "00bf984e",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00bf9850",
      "instruction": "JZ 0x00bf9e66"
    },
    {
      "address": "00bf9856",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00bf985b",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bf985d",
      "instruction": "CALL 0x00b25fb0"
    },
    {
      "address": "00bf9862",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00bf9864",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "00bf9866",
      "instruction": "JZ 0x00bf98bc"
    },
    {
      "address": "00bf9868",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00bf986d",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bf986f",
      "instruction": "CALL 0x00f67d90"
    },
    {
      "address": "00bf9874",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bf9876",
      "instruction": "CALL 0x00c75420"
    },
    {
      "address": "00bf987b",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00bf987d",
      "instruction": "JG 0x00bf98bc"
    },
    {
      "address": "00bf987f",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00bf9881",
      "instruction": "CALL 0x00bf7150"
    },
    {
      "address": "00bf9886",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bf9888",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00bf988a",
      "instruction": "CALL 0x00bf7150"
    },
    {
      "address": "00bf988f",
      "instruction": "CMP EDI,EAX"
    },
    {
      "address": "00bf9891",
      "instruction": "JG 0x00bf98bc"
    },
    {
      "address": "00bf9893",
      "instruction": "MOV ECX,dword ptr [ESI + 0x468]"
    },
    {
      "address": "00bf9899",
      "instruction": "CMP ECX,EBX"
    },
    {
      "address": "00bf989b",
      "instruction": "JZ 0x00bf98aa"
    },
    {
      "address": "00bf989d",
      "instruction": "MOV dword ptr [ESI + 0x468],EBX"
    },
    {
      "address": "00bf98a3",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00bf98a5",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00bf98a8",
      "instruction": "CALL EAX"
    },
    {
      "address": "00bf98aa",
      "instruction": "LEA ECX,[ESI + 0x1c8]"
    },
    {
      "address": "00bf98b0",
      "instruction": "POP EDI"
    },
    {
      "address": "00bf98b1",
      "instruction": "POP ESI"
    },
    {
      "address": "00bf98b2",
      "instruction": "POP EBP"
    },
    {
      "address": "00bf98b3",
      "instruction": "POP EBX"
    },
    {
      "address": "00bf98b4",
      "instruction": "ADD ESP,0x20"
    },
    {
      "address": "00bf98b7",
      "instruction": "JMP 0x00bc3130"
    },
    {
      "address": "00bf98bc",
      "instruction": "MOV ECX,dword ptr [ESI + 0x468]"
    },
    {
      "address": "00bf98c2",
      "instruction": "CMP ECX,EBX"
    },
    {
      "address": "00bf98c4",
      "instruction": "JZ 0x00bf98cf"
    },
    {
      "address": "00bf98c6",
      "instruction": "CALL 0x00bfdf80"
    },
    {
      "address": "00bf98cb",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00bf98cd",
      "instruction": "JNZ 0x00bf98f1"
    },
    {
      "address": "00bf98cf",
      "instruction": "CMP byte ptr [ESI + 0x93],BL"
    },
    {
      "address": "00bf98d5",
      "instruction": "JNZ 0x00bf98f1"
    },
    {
      "address": "00bf98d7",
      "instruction": "LEA ECX,[ESI + 0x1c8]"
    },
    {
      "address": "00bf98dd",
      "instruction": "CALL 0x00bc3190"
    },
    {
      "address": "00bf98e2",
      "instruction": "CMP EDX,EBX"
    },
    {
      "address": "00bf98e4",
      "instruction": "JA 0x00bf98f1"
    },
    {
      "address": "00bf98e6",
      "instruction": "CMP EAX,0x2710"
    },
    {
      "address": "00bf98eb",
      "instruction": "JBE 0x00bf9e66"
    },
    {
      "address": "00bf98f1",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00bf98f4",
      "instruction": "MOV byte ptr [ESI + 0x93],BL"
    },
    {
      "address": "00bf98fa",
      "instruction": "MOV dword ptr [ESP + 0x10],EBX"
    },
    {
      "address": "00bf98fe",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM0"
    },
    {
      "address": "00bf9904",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00bf9909",
      "instruction": "PUSH 0x403df5c"
    },
    {
      "address": "00bf990e",
      "instruction": "PUSH 0xb1e500"
    },
    {
      "address": "00bf9913",
      "instruction": "PUSH 0xae5ea0"
    },
    {
      "address": "00bf9918",
      "instruction": "PUSH 0xd3d420"
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
  "original_bytes": 9217,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall-like\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueCultureSelection* selection\",\n    \"ordinary_stack_arguments\": [],\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"termination\": \"plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-13-C4-CIV-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"city_building_economy_update_00be2440\",\n      \"va\": \"0x00be2440\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 3,\n      \"symbol\": \"pkg11_sim_core_00b21340\",\n      \"va\": \"0x00b21340\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"pkg11_sim_core_00b21340\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b21340\"\n      },\n      {\n        \"name\": \"FUN_00b25ca0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b25ca0\"\n      },\n      {\n        \"name\": \"FUN_00b25fb0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b25fb0\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      },\n      {\n        \"name\": \"simulator_game_input_manager_get_00b3d350\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d350\"\n      },\n      {\n        \"name\": \"FUN_00b5b800\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b5b800\"\n      },\n      {\n        \"name\": \"FUN_00bd81d0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00bd81d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd8210\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bfbbf0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00bfbe95\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bfbbf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9924\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b21340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf99bd\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b25ca0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf985d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b25fb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9856\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9868\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9904\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf99b6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9970\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9a40\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9a50\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9b24\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9baa\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9bc0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9bea\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9bfa\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9cba\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf9cd0\",\n        \"direction\": \
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
  "body_end": "00bf9e6d",
  "body_span_bytes": 1614,
  "body_start": "00bf9820",
  "callees": [
    "FUN_00beff90",
    "FUN_00b21340",
    "FUN_00b7e4d0",
    "FUN_00bfdf80",
    "FUN_00bf00a0",
    "FUN_00bf9700",
    "FUN_00bf2170",
    "FUN_00bf2100",
    "FUN_00bddda0",
    "FUN_00bc3130",
    "FUN_00c9e6d0",
    "FUN_00b88590",
    "FUN_00bd8210",
    "FUN_00bf7150",
    "FUN_00fa0e00",
    "FUN_00bc3190",
    "FUN_00bd81d0",
    "FUN_00b3d300",
    "Simulator::cGameInputManager::Get",
    "FUN_00b25ca0",
    "FUN_00b25fb0",
    "FUN_00bdb930",
    "FUN_00b81470",
    "FUN_00bef710",
    "FUN_00b5b800",
    "FUN_00f67d90",
    "FUN_00c75420",
    "FUN_00bf0c60"
  ],
  "callers": [
    "FUN_00bfbbf0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bf9820",
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
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00bf9820",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7f9820",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bf9820(void)",
  "size_bytes": 1614,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bf9820",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00bfbe95"
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
  "files": [
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.cpp",
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.hpp",
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c4-civ-wave3/00bf9820.json"
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
  "OpaqueCultureSelection* selection",
  "uint16_t",
  "void"
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
      "0x00b21340",
      "0x00b21340",
      "0x00acd9a0",
      "0x00acd9a0",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00ace2c0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00b25f40",
      "0x00ba0080",
      "0x00ba0080",
      "0x00ba0080",
      "0x00bf9820",
      "0x00bf9820",
      "0x00ba8420"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:0",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e63560",
      "0x00e63560",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00551240",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x00e5c780",
      "0x00e63560",
      "0x00571f80"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:4",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00845310",
      "0x00845310",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x00842d10",
      "0x00844180",
      "0x00843000"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:8",
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
