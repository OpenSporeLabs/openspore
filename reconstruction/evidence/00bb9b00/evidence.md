# Evidence 0x00bb9b00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `40670a2c1f497ad9bfad569304fdf3c06158f4d67e311a4c58e786e574d934a6`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall with two callee-popped stack words",
  "hidden_this_register": "ECX, read at 0x00bb9b0b and 0x00bb9b17, never written",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8 on both paths",
  "return_register": "none",
  "return_semantics": "no value; the function's only effect is the read-modify-write of the receiver's +0x5c dword",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [
    {
      "slot": "[ESP+0x4]",
      "use": "the 32-bit mask, used whole in the OR path and after a NOT in the AND path"
    },
    {
      "slot": "[ESP+0x8]",
      "use": "the set/clear selector, read as a byte and compared against 0",
      "width": 1
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "0x00bb9b0e and 0x00bb9b1a"
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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "f98dbd50997174395b7016cb20bc7b863d1fbddaf535e1968aca6df2b3c6a67d",
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
    "persisted_calling_convention": "__thiscall with two callee-popped stack words"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0007",
        "obs-0011"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0008"
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
        "obs-0005",
        "obs-0006",
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          92
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0011"
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
        "obs-0007",
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0011"
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
      "at": "0x00bb9b00",
      "count": 3,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP byte ptr [ESP + 0x8],0x0",
      "reg": "ESP"
    },
    {
      "at": "0x00bb9b00",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "CMP byte ptr [ESP + 0x8],0x0",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x00bb9b07",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0003",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bb9b07",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bb9b0b",
      "count": 2,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "OR dword ptr [ECX + 0x5c],EAX",
      "reg": "ECX"
    },
    {
      "at": "0x00bb9b0b",
      "count": 1,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "OR dword ptr [ECX + 0x5c],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00bb9b0e",
      "form": "RET 0x8",
      "id": "o
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
    "va": "0x00b294c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba6cf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba7dc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba8830"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00baac30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bad940"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00baf630"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb21b0"
  },
  {
    "name": "star_regenerate_00bb4af0",
    "reconstructed": true,
    "va": "0x00bb4af0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb4ba0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb4f30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb5640"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb5d80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb6040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb80f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5b660"
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
  "count": 9,
  "instructions": [
    {
      "address": "00bb9b00",
      "instruction": "CMP byte ptr [ESP + 0x8],0x0"
    },
    {
      "address": "00bb9b05",
      "instruction": "JZ 0x00bb9b11"
    },
    {
      "address": "00bb9b07",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00bb9b0b",
      "instruction": "OR dword ptr [ECX + 0x5c],EAX"
    },
    {
      "address": "00bb9b0e",
      "instruction": "RET 0x8"
    },
    {
      "address": "00bb9b11",
      "instruction": "MOV EDX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00bb9b15",
      "instruction": "NOT EDX"
    },
    {
      "address": "00bb9b17",
      "instruction": "AND dword ptr [ECX + 0x5c],EDX"
    },
    {
      "address": "00bb9b1a",
      "instruction": "RET 0x8"
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
  "original_bytes": 12504,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall with two callee-popped stack words\",\n    \"hidden_this_register\": \"ECX, read at 0x00bb9b0b and 0x00bb9b17, never written\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x8 on both paths\",\n    \"return_register\": \"none\",\n    \"return_semantics\": \"no value; the function's only effect is the read-modify-write of the receiver's +0x5c dword\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [],\n    \"stack_arguments\": [\n      {\n        \"slot\": \"[ESP+0x4]\",\n        \"use\": \"the 32-bit mask, used whole in the OR path and after a NOT in the AND path\"\n      },\n      {\n        \"slot\": \"[ESP+0x8]\",\n        \"use\": \"the set/clear selector, read as a byte and compared against 0\",\n        \"width\": 1\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"0x00bb9b0e and 0x00bb9b1a\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\",\n      \"score\": 3,\n      \"symbol\": \"star_regenerate_00bb4af0\",\n      \"va\": \"0x00bb4af0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b294c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba6cf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba7dc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba8830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00baac30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bad940\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00baf630\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb21b0\"\n      },\n      {\n        \"name\": \"star_regenerate_00bb4af0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00bb4af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb4ba0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb4f30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb5640\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb5d80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb6040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb80f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5b660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5c470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5f5f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5f770\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c7a160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8c2a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe9580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0100a160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0100aec0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b296d3\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b294c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b296de\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b294c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba6d5c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba6cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba7fb0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba7dc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba8872\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba8830\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00baacb5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00baac30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00baacce\",\n        \"direction\": \"in\",\n        \"other\": \"0x00baac30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00baacee\",\n        \"direction\": \"in\",\n        \"other\": \"0x00baac30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bad9c9\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bad940\",\n        \"reference_typ
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
  "body_end": "00bb9b1c",
  "body_span_bytes": 29,
  "body_start": "00bb9b00",
  "callees": [],
  "callers": [
    "FUN_00bb5d80",
    "FUN_00bad940",
    "FUN_00c5f5f0",
    "FUN_00b294c0",
    "FUN_00ba8830",
    "FUN_00ba7dc0",
    "FUN_00c7a160",
    "FUN_0100aec0",
    "FUN_0100a160",
    "FUN_00c5b660",
    "FUN_00c5c470",
    "FUN_00ba6cf0",
    "FUN_00baf630",
    "FUN_00bb21b0",
    "FUN_00bb5640",
    "FUN_00c5f770",
    "FUN_00bb4af0",
    "FUN_00bb4f30",
    "FUN_00bb4ba0",
    "FUN_00c8c2a0",
    "FUN_00fe9580",
    "FUN_00bb6040",
    "FUN_00bb80f0",
    "FUN_00baac30"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00bb9b00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00bb9b00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b9b00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb9b00(void)",
  "size_bytes": 29,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb9b00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 44,
  "xrefs": [
    {
      "from": "00b296de"
    },
    {
      "from": "00baf677"
    },
    {
      "from": "00baf699"
    },
    {
      "from": "00bb4c81"
    },
    {
      "from": "00bb6202"
    },
    {
      "from": "00ba8872"
    },
    {
      "from": "00bb2323"
    },
    {
      "from": "00ba6d5c"
    },
    {
      "from": "00baacb5"
    },
    {
      "from": "00baacce"
    },
    {
      "from": "00baacee"
    },
    {
      "from": "00bb86b1"
    },
    {
      "from": "00bb88ab"
    },
    {
      "from": "00bb4b7c"
    },
    {
      "from": "00fe973e"
    },
    {
      "from": "00fe9c8e"
    },
    {
      "from": "00c8c2c3"
    },
    {
      "from": "00bb5690"
    },
    {
      "from": "00bb569f"
    },
    {
      "from": "00bb56aa"
    },
    {
      "from": "00bb56b5"
    },
    {
      "from": "00bb56c3"
    },
    {
      "from": "00ba7fb0"
    },
    {
      "from": "00c7a1c2"
    },
    {
      "from": "00c7a1e1"
    },
    {
      "from": "00bb5eb8"
    },
    {
      "from": "00c5b67c"
    },
    {
      "from": "00c5c6f9"
    },
    {
      "from": "00c5f624"
    },
    {
      "from": "00c5fa12"
    },
    {
      "from": "00c5fb56"
    },
    {
      "from": "00c5fb6b"
    },
    {
      "from": "0100a5c9"
    },
    {
      "from": "0100b031"
    },
    {
      "from": "00b296d3"
    },
    {
      "from": "00bad9c9"
    },
    {
      "from": "00b29c25"
    },
    {
      "from": "00b29fca"
    },
    {
      "from": "00b29c1a"
    },
    {
      "from": "00b29fbf"
    },
    {
      "from": "00bb4fb0"
    },
    {
      "from": "00bb5086"
    },
    {
      "from": "00bb5149"
    },
    {
      "from": "00bb5562"
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
    "reconstruction/staging/wave13-pilot-core-b01/bb9b00_star_record_set_flags.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-core-b01/00bb9b00.json"
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
    "A runtime trace would be needed to observe the actual flag word of a real star record before and after a state transition, and to confirm that no other code path writes +0x5c outside this function and the two siblings that read it.",
    "No original-process trace exists for 0x00bb9b00; every claim is static.",
    "The undocumented bit meanings can only be resolved by correlating runtime flag values with game events, which no recorded run provides."
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
