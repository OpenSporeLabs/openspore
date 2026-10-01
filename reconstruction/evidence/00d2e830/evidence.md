# Evidence 0x00d2e830

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a85ad59f17219a57b4fd74b820271ff28fff1fb63026804e0794a8b28428f0e5`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "receiver": false,
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
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
  "content_sha256": "c7f2e29d9f83275d449d8aadea5b58d1d3097c4f98ed1c72b6a0f1ca4eccfac8",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0021",
        "obs-0023"
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
        "obs-0023"
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
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0021",
        "obs-0023"
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
      "and_esp": null,
      "at": "0x00d2e830",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00d2e830",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00d2e833",
      "count": 4,
      "first_use": 1,
      "first_write_index": 9,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00d2e834",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d300",
      "target": "0x00b3d300"
    },
    {
      "at": "0x00d2e839",
      "count": 2,
      "first_use": 3,
      "first_write_index": 24,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00d2e839",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00d2e83b",
      "id": "obs-0007",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f67d90",
      "target": "0x00f67d90"
    },
    {
      "at": "0x00d2e840",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [EAX + 0x10f0]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00d2e848",
      "count": 7,
      "first_use": 6,
      "first_write_index": 0,
      "id": "obs-0009",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [ESP + 0x8],XMM0",
      "reg": "ESP"
    },
    {
      "at": "0x00d2e848",
      "count": 3,
      "first_use": 6,
      "first_write_index": 5,
      "id": "obs-0010",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [ESP + 0x8],XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00d2e848",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0011",
      "index": 6,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOVSS dword ptr [ESP + 0x8],XMM0",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00d2e851",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0012",
      "index": 8,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOVSS dword ptr [ESP + 0x4],XMM0",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00d2e857",
      "definite": true,
      "id": "obs-0013",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "XOR ESI,ESI",
      "reg": "ESI",
      "write_kind": "zero"
    },
    {
      "at": "0x00d2e859",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0014",
      "index": 10,
      "key": null,
      "ki
[TRUNCATED]
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
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
  "content_sha256": "c7f2e29d9f83275d449d8aadea5b58d1d3097c4f98ed1c72b6a0f1ca4eccfac8",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0021",
        "obs-0023"
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
        "obs-0023"
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
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0021",
        "obs-0023"
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
      "and_esp": null,
      "at": "0x00d2e830",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00d2e830",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00d2e833",
      "count": 4,
      "first_use": 1,
      "first_write_index": 9,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00d2e834",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d300",
      "target": "0x00b3d300"
    },
    {
      "at": "0x00d2e839",
      "count": 2,
      "first_use": 3,
      "first_write_index": 24,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00d2e839",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00d2e83b",
      "id": "obs-0007",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f67d90",
      "target": "0x00f67d90"
    },
    {
      "at": "0x00d2e840",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [EAX + 0x10f0]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00d2e848",
      "count": 7,
      "first_use": 6,
      "first_write_index": 0,
      "id": "obs-0009",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [ESP + 0x8],XMM0",
      "reg": "ESP"
    },
    {
      "at": "0x00d2e848",
      "count": 3,
      "first_use": 6,
      "first_write_index": 5,
      "id": "obs-0010",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [ESP + 0x8],XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00d2e848",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0011",
      "index": 6,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOVSS dword ptr [ESP + 0x8],XMM0",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00d2e851",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0012",
      "index": 8,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOVSS dword ptr [ESP + 0x4],XMM0",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00d2e857",
      "definite": true,
      "id": "obs-0013",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "XOR ESI,ESI",
      "reg": "ESI",
      "write_kind": "zero"
    },
    {
      "at": "0x00d2e859",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0014",
      "index": 10,
      "key": null,
      "ki
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
  },
  {
    "name": "Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel",
    "reconstructed": true,
    "va": "0x00d2e380"
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
    "va": "0x00d3fcf0"
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
      "address": "00d2e830",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00d2e833",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d2e834",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00d2e839",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d2e83b",
      "instruction": "CALL 0x00f67d90"
    },
    {
      "address": "00d2e840",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x10f0]"
    },
    {
      "address": "00d2e848",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM0"
    },
    {
      "address": "00d2e84e",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00d2e851",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "00d2e857",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00d2e859",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "00d2e860",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d2e861",
      "instruction": "CALL 0x00d2e380"
    },
    {
      "address": "00d2e866",
      "instruction": "FADD float ptr [ESP + 0x8]"
    },
    {
      "address": "00d2e86a",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00d2e86d",
      "instruction": "FST float ptr [ESP + 0x4]"
    },
    {
      "address": "00d2e871",
      "instruction": "FLD float ptr [ESP + 0x8]"
    },
    {
      "address": "00d2e875",
      "instruction": "FXCH"
    },
    {
      "address": "00d2e877",
      "instruction": "FCOMIP ST0,ST1"
    },
    {
      "address": "00d2e879",
      "instruction": "FSTP ST0"
    },
    {
      "address": "00d2e87b",
      "instruction": "JA 0x00d2e88d"
    },
    {
      "address": "00d2e87d",
      "instruction": "INC ESI"
    },
    {
      "address": "00d2e87e",
      "instruction": "CMP ESI,0x4"
    },
    {
      "address": "00d2e881",
      "instruction": "JL 0x00d2e860"
    },
    {
      "address": "00d2e883",
      "instruction": "MOV EAX,0x4"
    },
    {
      "address": "00d2e888",
      "instruction": "POP ESI"
    },
    {
      "address": "00d2e889",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00d2e88c",
      "instruction": "RET"
    },
    {
      "address": "00d2e88d",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00d2e88f",
      "instruction": "POP ESI"
    },
    {
      "address": "00d2e890",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00d2e893",
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
  "abi": {},
  "analogues": [
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "PKG-18-UI-SCRIPTING",
      "score": 3,
      "symbol": "FUN_005bf9d0",
      "va": "0x005bf9d0"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "PKG-18-UI-SCRIPTING",
      "score": 3,
      "symbol": "FUN_005c0100",
      "va": "0x005c0100"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "PKG-18-UI-SCRIPTING",
      "score": 3,
      "symbol": "FUN_005c0380",
      "va": "0x005c0380"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "wave6-resources",
      "score": 3,
      "symbol": "property_list_has_property_006a2470",
      "va": "0x006a2470"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "wave6-resources",
      "score": 3,
      "symbol": "property_list_get_property_object_006a24d0",
      "va": "0x006a24d0"
    },
    {
      "match_basis": [
        "direct_xref_neighbor"
      ],
      "package": "PKG-01-SHARED-STATE-ROOTS",
      "score": 3,
      "symbol": "FUN_00b3d300",
      "va": "0x00b3d300"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "PKG-13-C4-CREATURE-WAVE3",
      "score": 3,
      "symbol": "Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460",
      "va": "0x00c1d460"
    },
    {
      "match_basis": [
        "shared_types:UNCONDITIONAL_CALL"
      ],
      "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
      "score": 3,
      "symbol": "Simulator_cCreatureGameData_Get_00d2e340",
      "va": "0x00d2e340"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [
    "Runtime object validity, field meaning, threshold values, and selector reachability remain gated."
  ],
  "body_status": null,
  "class_type": null,
  "cluster": null,
  "confidence": null,
  "dependencies": {
    "callees": [
      {
        "name": "FUN_00b3d300",
        "reconstructed": true,
        "va": "0x00b3d300"
      },
      {
        "name": "Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel",
        "reconstructed": true,
        "va": "0x00d2e380"
      }
    ],
    "callees_truncated": false,
    "callers": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x00d3fcf0"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x00d3fd2f",
        "direction": "in",
        "other": "0x00d3fcf0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00d2e834",
        "direction": "out",
        "other": "0x00b3d300",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00d2e861",
        "direction": "out",
        "other": "0x00d2e380",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00d2e83b",
        "direction": "out",
        "other": "0x00f67d90",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 1,
    "fan_out": 2,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [
      "0x00b3d300",
      "0x00d2e380"
    ],
    "scc": {
      "id": "scc-0502",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": null,
  "globals": [],
  "integration_status": null,
  "name": null,
  "normalized_symbol": null,
  "observed_mechanics": [],
  "ownership": {
    "claimability": "runtime_gated_requires_explicit_gate",
    "handoff_packages": [],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": null,
    "queue_state": null
  },
  "package": null,
  "reconstructed": false,
  "review_status": null,
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "No original-process level-selection trace has been run.",
      "Observe 0x0167eae0, the +0x74 returned object, the +0x10f0 float, and the four threshold globals in an original process.",
      "Resolve concrete progression-player and noun-manager ownership and threshold writers."
    ],
    "validated": 0
  },
  "runtime_gated": true,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": null,
  "services": [],
  "source": {
    "decomp": null,
    "file": null,
    "files": [
      "reconstruction/staging/pkg13-c1-creature-progression/creature_progression.cpp",
      "reconstruction/staging/pkg13-c1-creature-progression/creature_progression.hpp",
      "reconstruction/staging/pkg13-c1-creature-progression/creature_progression_model_test.cpp"
    ],
    "handoffs": [],
    "metadata": [
      "reconstruction/metadata/pkg13-c1-creature-progression/00d2e830.json"
    ],
    "provenance": []
  },
  "status": "unresolved",
  "subsystem": null,
  "triage": null,
  "types": [
    "UNCONDITIONAL_CALL",
    "float"
  ],
  "unresolved_questions": [
    "The SDK semantic name for this selector is unresolved; the normalized symbol remains opaque.",
    "The later virtual action selected by the caller after sentinel 4 is outside this target.",
    "The runtime relationship between the progression-player +0x10f0 field and DAT_0169e398 is not established by this body."
  ],
  "va": "0x00d2e830",
  "vtables": []
}
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00d2e893",
  "body_span_bytes": 100,
  "body_start": "00d2e830",
  "callees": [
    "Simulator::cCreatureGameData::GetEvoPointsToNextBrainLevel",
    "FUN_00f67d90",
    "FUN_00b3d300"
  ],
  "callers": [
    "FUN_00d3fcf0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d2e830",
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
      "name": "local_c",
      "storage": "Stack[-0xc]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00d2e830",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x92e830",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d2e830(void)",
  "size_bytes": 100,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d2e830",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00d3fd2f"
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
    "reconstruction/staging/pkg13-c1-creature-progression/creature_progression.cpp",
    "reconstruction/staging/pkg13-c1-creature-progression/creature_progression.hpp",
    "reconstruction/staging/pkg13-c1-creature-progression/creature_progression_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg13-c1-creature-progression/00d2e830.json"
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
    "No original-process level-selection trace has been run.",
    "Observe 0x0167eae0, the +0x74 returned object, the +0x10f0 float, and the four threshold globals in an original process.",
    "Resolve concrete progression-player and noun-manager ownership and threshold writers."
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "UNCONDITIONAL_CALL",
  "float"
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
