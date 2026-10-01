# Evidence 0x00b25f40

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `fa248bdf753c73bf31de3d21a6cab79b7e9d5b2305fa11c4a468de9d78a84d4d`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "NounProjection* receiver forwarded to 0x00b21340",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "identity",
      "position": 1,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "return_note": "borrowed candidate pointer or null",
  "return_register": "EAX",
  "return_type": "NounObject*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4"
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
    "calling_convention": "__stdcall",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": false,
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "SUPPORTED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [
    {
      "field": "calling_convention",
      "inferred": "__stdcall",
      "kind": "inferred_vs_persisted",
      "persisted": "__thiscall",
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "c0e1fb57765598588f63a2dbbb64600b1272fb4e7ec5bab4323743fb120699e3",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__stdcall",
    "candidate_conventions": [
      "__stdcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "disagrees",
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
        "obs-0023",
        "obs-0028"
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
        "obs-0023",
        "obs-0028"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0028"
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
        "obs-0023",
        "obs-0028"
      ],
      "claim": "calling convention is __stdcall: a callee that pops stack arguments with no register receiver",
      "confidence": "INFERRED",
      "id": "C6",
      "value": "__stdcall"
    },
    {
      "based_on": [
        "obs-0023",
        "obs-0028"
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
        "obs-0023",
        "obs-0028"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0023",
        "obs-0028"
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
      "at": "0x00b25f40",
      "count": 4,
      "first_use": 0,
      "first_write_index": 19,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00b25f41",
      "count": 3,
      "first_use": 1,
      "first_write_index": 15,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00b25f41",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00b25f42",
      "count": 2,
      "first_use": 2,
      "first_write_index": 11,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b25f43",
      "count": 4,
      "first_use": 3,
      "first_write_index": 10,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b25f5d",
      "id": "obs-0006",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b21340",
      "target": "0x00b21340"
    },
    {
      "at": "0x00b25f62",
      "count": 4,
      "first_use": 10,
      "first_write_index": 18,
      "id": "obs-0007",
      "index": 10,
      "kind
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
    "name": "FUN_00b25fb0",
    "reconstructed": false,
    "va": "0x00b25fb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b262c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b35b80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b677e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b682a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6baf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b80b40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bccf20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bcd630"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd5ea0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bdb3b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bdd120"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bdde70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be11f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be1820"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be1860"
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
  "count": 41,
  "instructions": [
    {
      "address": "00b25f40",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b25f41",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00b25f42",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b25f43",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b25f44",
      "instruction": "PUSH 0x18c816a"
    },
    {
      "address": "00b25f49",
      "instruction": "PUSH 0xb1e500"
    },
    {
      "address": "00b25f4e",
      "instruction": "PUSH 0xb236c0"
    },
    {
      "address": "00b25f53",
      "instruction": "PUSH 0xd3d420"
    },
    {
      "address": "00b25f58",
      "instruction": "PUSH 0xb21080"
    },
    {
      "address": "00b25f5d",
      "instruction": "CALL 0x00b21340"
    },
    {
      "address": "00b25f62",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00b25f64",
      "instruction": "MOV ESI,dword ptr [EDI + 0x8]"
    },
    {
      "address": "00b25f67",
      "instruction": "SUB ESI,dword ptr [EDI + 0x4]"
    },
    {
      "address": "00b25f6a",
      "instruction": "ADD EDI,0x4"
    },
    {
      "address": "00b25f6d",
      "instruction": "SAR ESI,0x2"
    },
    {
      "address": "00b25f70",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00b25f72",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00b25f74",
      "instruction": "JLE 0x00b25f8f"
    },
    {
      "address": "00b25f76",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00b25f78",
      "instruction": "MOV EBX,dword ptr [EAX + EBP*0x4]"
    },
    {
      "address": "00b25f7b",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "00b25f7d",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4c]"
    },
    {
      "address": "00b25f80",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00b25f82",
      "instruction": "CALL EAX"
    },
    {
      "address": "00b25f84",
      "instruction": "CMP EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00b25f88",
      "instruction": "JZ 0x00b25f98"
    },
    {
      "address": "00b25f8a",
      "instruction": "INC EBP"
    },
    {
      "address": "00b25f8b",
      "instruction": "CMP EBP,ESI"
    },
    {
      "address": "00b25f8d",
      "instruction": "JL 0x00b25f76"
    },
    {
      "address": "00b25f8f",
      "instruction": "POP EDI"
    },
    {
      "address": "00b25f90",
      "instruction": "POP ESI"
    },
    {
      "address": "00b25f91",
      "instruction": "POP EBP"
    },
    {
      "address": "00b25f92",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00b25f94",
      "instruction": "POP EBX"
    },
    {
      "address": "00b25f95",
      "instruction": "RET 0x4"
    },
    {
      "address": "00b25f98",
      "instruction": "POP EDI"
    },
    {
      "address": "00b25f99",
      "instruction": "POP ESI"
    },
    {
      "address": "00b25f9a",
      "instruction": "POP EBP"
    },
    {
      "address": "00b25f9b",
      "instruction": "MOV EAX,EBX"
    },
    {
      "address": "00b25f9d",
      "instruction": "POP EBX"
    },
    {
      "address": "00b25f9e",
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
  "original_bytes": 15548,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"NounProjection* receiver forwarded to 0x00b21340\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"identity\",\n        \"position\": 1,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"return_note\": \"borrowed candidate pointer or null\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"NounObject*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:NounProjection,NounProjectionVector\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 9,\n      \"symbol\": \"pkg11_sim_core_00b21340\",\n      \"va\": \"0x00b21340\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"pkg11_sim_core_00b21340\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b21340\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"FUN_00b25fb0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b25fb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b262c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b35b80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b677e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b682a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6baf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b80b40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bccf20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bcd630\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd5ea0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdb3b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdd120\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdde70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be11f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be1820\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be1860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be2110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be45b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be92e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be9850\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be9980\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00beaa30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf02b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        
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
  "body_end": "00b25fa0",
  "body_span_bytes": 97,
  "body_start": "00b25f40",
  "callees": [
    "FUN_00b21340"
  ],
  "callers": [
    "FUN_00be9850",
    "FUN_00c737a0",
    "FUN_00dd2820",
    "FUN_00d5cfd0",
    "FUN_00dcd720",
    "FUN_00bcd630",
    "FUN_00be11f0",
    "FUN_00e10220",
    "FUN_00be2110",
    "FUN_00cb91d0",
    "FUN_00be9980",
    "FUN_00be1820",
    "FUN_00e0f2c0",
    "FUN_00b80b40",
    "FUN_00ca72a0",
    "FUN_00bfe0c0",
    "FUN_00b682a0",
    "FUN_00bff7a0",
    "FUN_00cfbc10",
    "FUN_00d05d90",
    "FUN_00b677e0",
    "FUN_00cc3140",
    "FUN_00bf02b0",
    "FUN_00dce4d0",
    "FUN_00c9f650",
    "FUN_00ca3f20",
    "FUN_00bfdf80",
    "FUN_00e2d6a0",
    "FUN_00b25fb0",
    "FUN_00cc3000",
    "FUN_00c74550",
    "FUN_00b35b80",
    "FUN_00bdde70",
    "FUN_00dcc440",
    "FUN_00bff2d0",
    "FUN_00bccf20",
    "FUN_00cc3380",
    "FUN_00c9e7c0",
    "FUN_00b262c0",
    "FUN_00bdd120",
    "FUN_00be45b0",
    "FUN_00bd5ea0",
    "FUN_00beaa30",
    "FUN_00c00b00",
    "FUN_00e06d90",
    "FUN_00cba690",
    "FUN_00d84ec0",
    "FUN_00caa610",
    "FUN_0100a960",
    "FUN_00be88d0",
    "FUN_00b6baf0",
    "FUN_00be1860",
    "FUN_00ce87c0",
    "FUN_00dca100",
    "FUN_00dce330",
    "FUN_00dc57a0",
    "FUN_00d5d880",
    "FUN_00ce8f70",
    "FUN_00bdb3b0",
    "FUN_00ff6a50",
    "FUN_00cacc60",
    "FUN_00d07770",
    "FUN_00d05a20",
    "FUN_00be92e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b25f40",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b25f40",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x725f40",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b25f40(void)",
  "size_bytes": 97,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b25f40",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 94,
  "xrefs": [
    {
      "from": "00c7387b"
    },
    {
      "from": "00c7389d"
    },
    {
      "from": "00d05a86"
    },
    {
      "from": "00d05a99"
    },
    {
      "from": "00b25fc6"
    },
    {
      "from": "00d05fb8"
    },
    {
      "from": "00d05fc7"
    },
    {
      "from": "00d5da1b"
    },
    {
      "from": "00bfdf97"
    },
    {
      "from": "00be226b"
    },
    {
      "from": "00be22a4"
    },
    {
      "from": "00be22d9"
    },
    {
      "from": "00be1297"
    },
    {
      "from": "00beaad3"
    },
    {
      "from": "00be9330"
    },
    {
      "from": "00be47b3"
    },
    {
      "from": "00be48cd"
    },
    {
      "from": "00be8903"
    },
    {
      "from": "00be9876"
    },
    {
      "from": "00bff9f0"
    },
    {
      "from": "00bffa46"
    },
    {
      "from": "00bffa94"
    },
    {
      "from": "00c00c14"
    },
    {
      "from": "00c7456f"
    },
    {
      "from": "00ca7459"
    },
    {
      "from": "00caa628"
    },
    {
      "from": "00caa8c6"
    },
    {
      "from": "00c9e829"
    },
    {
      "from": "00dd2899"
    },
    {
      "from": "00b262d6"
    },
    {
      "from": "00bff377"
    },
    {
      "from": "00ce8ff4"
    },
    {
      "from": "0100aa3f"
    },
    {
      "from": "00b6bf30"
    },
    {
      "from": "00b67b49"
    },
    {
      "from": "00b684bb"
    },
    {
      "from": "00b80bf2"
    },
    {
      "from": "00bccf6b"
    },
    {
      "from": "00bcd688"
    },
    {
      "from": "00bf02c1"
    },
    {
      "from": "00bd5f0b"
    },
    {
      "from": "00bdd165"
    },
    {
      "from": "00bddeb7"
    },
    {
      "from": "00ff6a9e"
    },
    {
      "from": "00be99cb"
    },
    {
      "from": "00ca4077"
    },
    {
      "from": "00cacc9b"
    },
    {
      "from": "00cb940e"
    },
    {
      "from": "00cc30b8"
    },
    {
      "from": "00cc31cc"
    },
    {
      "from": "00cc3434"
    },
    {
      "from": "00ce8897"
    },
    {
      "from": "00c9f65f"
    },
    {
      "from": "00be182f"
    },
    {
      "from": "00d07788"
    },
    {
      "from": "00d5d032"
    },
    {
      "from": "00d84fce"
    },
    {
      "from": "00dc58bd"
    },
    {
      "from": "00dca218"
    },
    {
      "from": "00dca3d4"
    },
    {
      "from": "00dca59f"
    },
    {
      "from": "00bdb44e"
    },
    {
      "from": "00dcc46c"
    },
    {
      "from": "00dcd789"
    },
    {
      "from": "00dcd8b7"
    },
    {
      "from": "00dce35d"
    },
    {
      "from": "00e2d702"
    },
    {
      "from": "00e0f360"
    },
    {
      "from": "00e10479"
    },
    {
      "from": "00cfbefd"
    },
    {
      "from": "00bff89a"
    },
    {
      "from": "00bfe0d7"
    },
    {
      "from": "00dce7d7"
    },
    {
      "from": "00be1abf"
    },
    {
      "from": "00e06f89"
    },
    {
      "from": "00e0702b"
    },
    {
      "from": "00e070aa"
    },
    {
      "from": "00e07136"
    },
    {
      "from": "00b35b8c"
    },
    {
      "from": "00bfe60c"
    },
    {
      "from": "00cab6ed"
    },
    {
      "from": "00cab705"
    },
    {
      "from": "00cba787"
    },
    {
      "from": "00cbf0f8"
    },
    {
      "from": "00cc3811"
    },
    {
      "from": "00dc7fd0"
    },
    {
      "from": "00dc8124"
    },
    {
      "from": "00e8b15f"
    }
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
  "files": [],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg13-c2-tribe-civilization/00b25f40.json"
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
    "Each candidate pointer and vtable must be readable, and vtable+0x4c must point to a callable identity probe.",
    "The fixed callback words and 0x00b21340's map/list behavior require original-process observation.",
    "The ownership and lifetime of returned candidate objects remain external to this function.",
    "The receiver must be valid for the existing 0x00b21340 projection/list layout.",
    "The returned vector must have readable +0x04 and +0x08 words and a valid positive or nonpositive span."
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "NounObject",
  "NounObject* borrowed candidate pointer or null",
  "NounObjectVtable",
  "NounProjection",
  "NounProjection* receiver forwarded to 0x00b21340",
  "NounProjectionLookupPort",
  "NounProjectionVector",
  "std::uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00000000"
]
```

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
  },
  {
    "derived": "__stdcall",
    "field": "calling_convention",
    "kind": "derived_vs_persisted",
    "persisted": "thiscall",
    "resolution_status": "unresolved"
  }
]
```
