# Evidence 0x004ad330

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `43e63eefb29947cc370cc21b3824e6b66385e6a0e24312330d80191c70a18b5e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__fastcall (register argument in ECX, no stack arguments)",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is spilled to [EBP - 0xc] at 0x004ad336 and reloaded twice, at 0x004ad339 for the 0x004ad280 call and at 0x004ad341 for the field_30 read; it is also pushed at 0x004ad35c as 0x004b9570's second argument",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "the last write to EAX is 0x004ad353 MOV EAX,dword ptr [EDX + 0x30], a reload of the member that is immediately stored to [EBP - 0x8]; nothing survives to the epilogue",
  "return_register": "none",
  "return_semantics": "no value; EAX is never written on any path",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "callee",
  "termination": "two paths, both through 0x004ad365: the JZ at 0x004ad34e and the fall-through after 0x004b9570"
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
    "return_semantics": "unclassified_in_EAX",
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
  "content_sha256": "99655e3302b171ac342ccc3b1492c12d6e7b2c42b5e58b7706d3d3e0712b8ffb",
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
    "persisted_calling_convention": "__fastcall (register argument in ECX, no stack arguments)"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0024"
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
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0013",
        "obs-0014",
        "obs-0020",
        "obs-0021"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          48
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0013",
        "obs-0014",
        "obs-0020",
        "obs-0021",
        "obs-0024"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0024"
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
        "obs-0024"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0024"
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
      "at": "0x004ad330",
      "count": 11,
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
      "at": "0x004ad330",
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
      "sub": 12
    },
    {
      "at": "0x004ad331",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004ad331",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004ad333",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0xc",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x004ad336",
      "count": 3,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0xc],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x004ad336",
      "base": "EBP",
      "disp": -12,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0xc],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x004ad339",
      "base": "EBP",
      "disp": -12,
      "id": "obs-0008",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [EBP + -0xc]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x004ad339",
      "definite": true,
      "id": "obs-0009",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EBP + -0xc]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x004ad33c",
      "id": "obs-0010",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x004ad280",
      "target": "0x004ad280"
    },
    {
      "at": "0x004ad341",
      "base": "EBP",
      "disp": -12,
      "id": "obs-0011",
      "index": 6,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword 
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
    "va": "0x0040d2d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0046d840"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004aba00"
  },
  {
    "name": "Editors::cEditor::Dispose",
    "reconstructed": false,
    "va": "0x00576c50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057d710"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057f6c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00585c10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00586b00"
  },
  {
    "name": "Editors::cEditor::OnExit",
    "reconstructed": false,
    "va": "0x00587a20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005f40b0"
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
  "count": 21,
  "instructions": [
    {
      "address": "004ad330",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004ad331",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004ad333",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "004ad336",
      "instruction": "MOV dword ptr [EBP + -0xc],ECX"
    },
    {
      "address": "004ad339",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004ad33c",
      "instruction": "CALL 0x004ad280"
    },
    {
      "address": "004ad341",
      "instruction": "MOV EAX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004ad344",
      "instruction": "MOV ECX,dword ptr [EAX + 0x30]"
    },
    {
      "address": "004ad347",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "004ad34a",
      "instruction": "CMP dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "004ad34e",
      "instruction": "JZ 0x004ad365"
    },
    {
      "address": "004ad350",
      "instruction": "MOV EDX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004ad353",
      "instruction": "MOV EAX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "004ad356",
      "instruction": "MOV dword ptr [EBP + -0x8],EAX"
    },
    {
      "address": "004ad359",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004ad35c",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004ad35d",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004ad360",
      "instruction": "CALL 0x004b9570"
    },
    {
      "address": "004ad365",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004ad367",
      "instruction": "POP EBP"
    },
    {
      "address": "004ad368",
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
  "original_bytes": 7991,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__fastcall (register argument in ECX, no stack arguments)\",\n    \"hidden_receiver\": \"ECX\",\n    \"hidden_this_register\": \"ECX is spilled to [EBP - 0xc] at 0x004ad336 and reloaded twice, at 0x004ad339 for the 0x004ad280 call and at 0x004ad341 for the field_30 read; it is also pushed at 0x004ad35c as 0x004b9570's second argument\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"the last write to EAX is 0x004ad353 MOV EAX,dword ptr [EDX + 0x30], a reload of the member that is immediately stored to [EBP - 0x8]; nothing survives to the epilogue\",\n    \"return_register\": \"none\",\n    \"return_semantics\": \"no value; EAX is never written on any path\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"two paths, both through 0x004ad365: the JZ at 0x004ad34e and the fall-through after 0x004b9570\"\n  },\n  \"analogues\": [],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040d2d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0046d840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004aba00\"\n      },\n      {\n        \"name\": \"Editors::cEditor::Dispose\",\n        \"reconstructed\": false,\n        \"va\": \"0x00576c50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057d710\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057f6c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00585c10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00586b00\"\n      },\n      {\n        \"name\": \"Editors::cEditor::OnExit\",\n        \"reconstructed\": false,\n        \"va\": \"0x00587a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005f40b0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0040d3b5\",\n        \"direction\": \"in\",\n        \"other\": \"0x0040d2d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0040e58e\",\n        \"direction\": \"in\",\n        \"other\": \"0x0040d2d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0046da80\",\n        \"direction\": \"in\",\n        \"other\": \"0x0046d840\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004aba1f\",\n        \"direction\": \"in\",\n        \"other\": \"0x004aba00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576d38\",\n        \"direction\": \"in\",\n        \"other\": \"0x00576c50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576d74\",\n        \"direction\": \"in\",\n        \"other\": \"0x00576c50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057df35\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057d710\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057f6dd\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057f6c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00585c40\",\n        \"direction\": \"in\",\n        \"other\": \"0x00585c10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00586bf7\",\n        \"direction\": \"in\",\n        \"other\": \"0x00586b00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00587e15\",\n        \"direction\": \"in\",\n        \"other\": \"0x00587a20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00587e57\",\n        \"direction\": \"in\",\n        \"other\": \"0x00587a20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005f422e\",\n        \"direction\": \"in\",\n        \"other\": \"0x005f40b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004ad33c\",\n        \"direction\": \"out\",\n        \"other\": \"0x004ad280\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004ad360\",\n        \"direction\": \"out\",\n        \"other\": \"0x004b9570\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 10,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0021\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": null,\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": null,\n  \"normalized_symbol\": null,\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n  
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
  "body_end": "004ad368",
  "body_span_bytes": 57,
  "body_start": "004ad330",
  "callees": [
    "FUN_004ad280",
    "FUN_004b9570"
  ],
  "callers": [
    "Editors::cEditor::Dispose",
    "FUN_0057f6c0",
    "FUN_00585c10",
    "FUN_005f40b0",
    "FUN_0040d2d0",
    "Editors::cEditor::OnExit",
    "FUN_004aba00",
    "FUN_0046d840",
    "FUN_0057d710",
    "Editors::cEditor::SetEditorModel"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "004ad330",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_004ad330",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xad330",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004ad330(void)",
  "size_bytes": 57,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004ad330",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 13,
  "xrefs": [
    {
      "from": "0046da80"
    },
    {
      "from": "0040d3b5"
    },
    {
      "from": "0040e58e"
    },
    {
      "from": "004aba1f"
    },
    {
      "from": "00585c40"
    },
    {
      "from": "00586bf7"
    },
    {
      "from": "00587e15"
    },
    {
      "from": "00587e57"
    },
    {
      "from": "005f422e"
    },
    {
      "from": "0057f6dd"
    },
    {
      "from": "00576d38"
    },
    {
      "from": "00576d74"
    },
    {
      "from": "0057df35"
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
    "reconstruction/staging/wave13-w1-dispatch-b02/b4ad330_teardown_004ad330.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/b4ad330_teardown_004ad330.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b02/004ad330.json"
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
    "A runtime trace is required to determine whether the double base pass in OnExit is benign in the shipping build.",
    "A runtime trace is required to observe the two virtual calls in 0x004ad280 and thereby resolve the receiver's class.",
    "No original-process trace has ever been captured for 0x004ad330; every claim here is static. The original Cell stage has never been entered in any recorded run."
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
[
  {
    "derived": "__thiscall",
    "field": "calling_convention",
    "kind": "derived_vs_persisted",
    "persisted": "__fastcall (register argument in ECX, no stack arguments)",
    "resolution_status": "unresolved"
  }
]
```
