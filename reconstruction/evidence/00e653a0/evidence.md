# Evidence 0x00e653a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9f9905c2ee01efe92b7d0a36650c72a60216dee25159ef3d9cf10d434b066d78`

## abi

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
        "size_inferred": true,
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
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
  "content_sha256": "43d77a3a5ef8728a01cd4adf81d6e1cfe38a9bcb0d9eba2056870f6eddd31dd8",
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
    "ghidra_parameter_count": 2,
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
        "obs-0015",
        "obs-0017"
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
        "obs-0002",
        "obs-0005",
        "obs-0011"
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
        "obs-0006",
        "obs-0007",
        "obs-0014"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4,
          8
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0015",
        "obs-0017"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0015",
        "obs-0017"
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
        "obs-0015",
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0017"
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
      "at": "0x00e653a0",
      "count": 4,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00e653a0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e653a0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e653a4",
      "count": 12,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP + 0x4],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00e653a4",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0005",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP + 0x4],EAX",
      "resolved": true,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00e653af",
      "count": 5,
      "first_use": 5,
      "first_write_index": 26,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ"
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
        "size_inferred": true,
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
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
  "content_sha256": "43d77a3a5ef8728a01cd4adf81d6e1cfe38a9bcb0d9eba2056870f6eddd31dd8",
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
    "ghidra_parameter_count": 2,
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
        "obs-0015",
        "obs-0017"
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
        "obs-0002",
        "obs-0005",
        "obs-0011"
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
        "obs-0006",
        "obs-0007",
        "obs-0014"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4,
          8
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0015",
        "obs-0017"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0015",
        "obs-0017"
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
        "obs-0015",
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0017"
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
      "at": "0x00e653a0",
      "count": 4,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00e653a0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e653a0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e653a4",
      "count": 12,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP + 0x4],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00e653a4",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0005",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP + 0x4],EAX",
      "resolved": true,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00e653af",
      "count": 5,
      "first_use": 5,
      "first_write_index": 26,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ"
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
    "name": "Simulator::Cell::cCellGFX::AddPreloadedModel",
    "reconstructed": false,
    "va": "0x00e65410"
  },
  {
    "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
    "reconstructed": false,
    "va": "0x00e66280"
  },
  {
    "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
    "reconstructed": false,
    "va": "0x00e663b0"
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
  "count": 43,
  "instructions": [
    {
      "address": "00e653a0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e653a4",
      "instruction": "MOV dword ptr [ESP + 0x4],EAX"
    },
    {
      "address": "00e653a8",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e653aa",
      "instruction": "JZ 0x00e653af"
    },
    {
      "address": "00e653ac",
      "instruction": "INC dword ptr [EAX + 0x40]"
    },
    {
      "address": "00e653af",
      "instruction": "MOV EDX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00e653b2",
      "instruction": "CMP EDX,dword ptr [ECX + 0x8]"
    },
    {
      "address": "00e653b5",
      "instruction": "JNC 0x00e653ce"
    },
    {
      "address": "00e653b7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e653b8",
      "instruction": "LEA ESI,[EDX + 0x4]"
    },
    {
      "address": "00e653bb",
      "instruction": "MOV dword ptr [ECX + 0x4],ESI"
    },
    {
      "address": "00e653be",
      "instruction": "POP ESI"
    },
    {
      "address": "00e653bf",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "00e653c1",
      "instruction": "JZ 0x00e653dd"
    },
    {
      "address": "00e653c3",
      "instruction": "MOV dword ptr [EDX],EAX"
    },
    {
      "address": "00e653c5",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e653c7",
      "instruction": "JZ 0x00e6540a"
    },
    {
      "address": "00e653c9",
      "instruction": "INC dword ptr [EAX + 0x40]"
    },
    {
      "address": "00e653cc",
      "instruction": "JMP 0x00e653dd"
    },
    {
      "address": "00e653ce",
      "instruction": "LEA EAX,[ESP + 0x4]"
    },
    {
      "address": "00e653d2",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e653d3",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e653d4",
      "instruction": "CALL 0x00423c40"
    },
    {
      "address": "00e653d9",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e653dd",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e653df",
      "instruction": "JZ 0x00e6540a"
    },
    {
      "address": "00e653e1",
      "instruction": "MOV ECX,dword ptr [EAX + 0x40]"
    },
    {
      "address": "00e653e4",
      "instruction": "CMP ECX,0x1"
    },
    {
      "address": "00e653e7",
      "instruction": "JLE 0x00e653f0"
    },
    {
      "address": "00e653e9",
      "instruction": "DEC ECX"
    },
    {
      "address": "00e653ea",
      "instruction": "MOV dword ptr [EAX + 0x40],ECX"
    },
    {
      "address": "00e653ed",
      "instruction": "RET 0x4"
    },
    {
      "address": "00e653f0",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00e653f3",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "00e653f5",
      "instruction": "SHR EDX,0x1f"
    },
    {
      "address": "00e653f8",
      "instruction": "AND DL,0x1"
    },
    {
      "address": "00e653fb",
      "instruction": "MOVZX EDX,DL"
    },
    {
      "address": "00e653fe",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e653ff",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00e65401",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e65402",
      "instruction": "MOV EAX,dword ptr [EDX + 0x170]"
    },
    {
      "address": "00e65408",
      "instruction": "CALL EAX"
    },
    {
      "address": "00e6540a",
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
  "abi": {},
  "analogues": [
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-11-H4-HELPER-WAVE3",
      "score": 6,
      "symbol": "address_window_offset_005c65e0",
      "va": "0x005c65e0"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-SIMULATOR-SAFE-WAVE11",
      "score": 6,
      "symbol": "dispatch_key_00628450",
      "va": "0x00628450"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-SIMULATOR-SAFE-WAVE11",
      "score": 6,
      "symbol": "cycle_key_006286a0",
      "va": "0x006286a0"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-SIMULATOR-SAFE-WAVE11",
      "score": 6,
      "symbol": "release_child_0062c910",
      "va": "0x0062c910"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-01-SHARED-STATE-ROOTS",
      "score": 6,
      "symbol": "FUN_00b3d2a0",
      "va": "0x00b3d2a0"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-01-SHARED-STATE-ROOTS",
      "score": 6,
      "symbol": "FUN_00b3d300",
      "va": "0x00b3d300"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-01-SHARED-STATE-ROOTS",
      "score": 6,
      "symbol": "Simulator_GetUIMissionLogManager",
      "va": "0x00b3d4f0"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-13-E4-EMPIRE-WAVE3",
      "score": 6,
      "symbol": "EmpirePoliticalColor_00c32cd0",
      "va": "0x00c32cd0"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [],
  "body_status": null,
  "class_type": null,
  "cluster": "sim-cell",
  "confidence": null,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [
      {
        "name": "Simulator::Cell::cCellGFX::AddPreloadedModel",
        "reconstructed": false,
        "va": "0x00e65410"
      },
      {
        "name": "Simulator::Cell::cCellGFX::AddPreloadedEffect",
        "reconstructed": false,
        "va": "0x00e66280"
      },
      {
        "name": "Simulator::Cell::cCellGFX::PreloadCellResource",
        "reconstructed": false,
        "va": "0x00e663b0"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x00e65439",
        "direction": "in",
        "other": "0x00e65410",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00e6635e",
        "direction": "in",
        "other": "0x00e66280",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00e6649f",
        "direction": "in",
        "other": "0x00e663b0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00e653d4",
        "direction": "out",
        "other": "0x00423c40",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 3,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0535",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "CONFIRMED",
  "globals": [],
  "integration_status": null,
  "name": "Simulator::Cell::cCellGFX::AddPreloadedModel2",
  "normalized_symbol": "Simulator::Cell::cCellGFX::AddPreloadedModel2",
  "observed_mechanics": [],
  "ownership": {
    "claimability": "queue_candidate",
    "handoff_packages": [],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": null,
    "queue_state": "implemented"
  },
  "package": null,
  "reconstructed": false,
  "review_status": null,
  "runtime": {
    "blocking_reason": null,
    "gates": [],
    "validated": 0
  },
  "runtime_gated": false,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": null,
  "services": [],
  "source": {
    "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedModel2.c",
    "file": null,
    "files": [
      ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedModel2.c"
    ],
    "handoffs": [],
    "metadata": [],
    "provenance": []
  },
  "status": "implemented",
  "subsystem": "Simulator",
  "triage": {
    "category": "GAMEPLAY_LOGIC",
    "cluster": "sim-cell",
    "db_triage_status": "DONE",
    "decomp_path": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedModel2.c",
    "dependencies": [
      "resource-io",
      "app-lifecycle",
      "utfwin-framework",
      "graphics-render"
    ],
    "evidence": "CONFIRMED",
    "kg_node_id": "fun:00e653a0",
    "name": "Simulator::Cell::cCellGFX::AddPreloadedModel2",
    "priority": "P3",
    "provenance": {
      "classifier": "triage-v4",
      "generated_at": "2026-09-23T10:12:09Z",
      "generator": "subagent-7-sequential-triage",
      "sdk_name": "Simulator::Cell::cCellGFX::AddPreloadedModel2",
      "snapshot": "2540f2ca",
      "snapshot_sha256": "2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8",
      "vtable_addrs": []
    },
    "queue_state": "implemented",
    "rank": 189
  },
  "types": [],
  "unresolved_questions": [],
  "va": "0x00e653a0",
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
  "body_end": "00e6540c",
  "body_span_bytes": 109,
  "body_start": "00e653a0",
  "callees": [
    "FUN_00423c40"
  ],
  "callers": [
    "Simulator::Cell::cCellGFX::PreloadCellResource",
    "Simulator::Cell::cCellGFX::AddPreloadedEffect",
    "Simulator::Cell::cCellGFX::AddPreloadedModel"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e653a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::Cell::cCellGFX::AddPreloadedModel2",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCellGFX *"
    },
    {
      "name": "model",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "Model *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0xa653a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Simulator::Cell::cCellGFX::AddPreloadedModel2(cCellGFX * this, Model * model)",
  "size_bytes": 109,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e653a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00e6649f"
    },
    {
      "from": "00e6635e"
    },
    {
      "from": "00e65439"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedModel2.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__AddPreloadedModel2.c"
  ],
  "handoffs": [],
  "metadata": []
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
  "gates": [],
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
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "implemented"
}
```

## types

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
