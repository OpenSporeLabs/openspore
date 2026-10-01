# Evidence 0x0043eed0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `de6eab32bf5408adb66d4ac46b4cfedba5ad29217da782455e5c1ffbb2cf992c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (receiver in ECX), no stack arguments",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is read only by the spill at 0x0043eed4",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x0043eeda is FLD dword ptr [EAX+0x1D4] and is the only floating-point instruction in the body. There is no FSTP, FADD, FMUL or memory store, so the loaded value is still on the x87 stack when the frame is torn down and the caller reads ST(0) directly. The caller confirms this: 0x0043f4c6 is FLD1, the matching push of the 1.0f the caller substitutes when it has no child to ask.",
  "return_register": "ST(0) - the x87 stack top, NOT an XMM register",
  "return_semantics": "the float32 stored at receiver+0x1D4, unmodified",
  "return_type": "float",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single RET at 0x0043eee3"
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
  "content_sha256": "39fb8ad4ea6a16304b9152aab6754da11df9a46841f3faf78cd610f4002a9b3f",
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
    "persisted_calling_convention": "__thiscall (receiver in ECX), no stack arguments"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0012"
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
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          468
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0012"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0012"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x0043eed0",
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
      "at": "0x0043eed0",
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
      "at": "0x0043eed1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x0043eed1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0043eed3",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0043eed4",
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
      "at": "0x0043eed7",
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
      "at": "0x0043eed7",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + -0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0043eeda",
      "count": 1,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_READ",
      "raw": "FLD float ptr [EAX + 0x1d4]",
      "reg": "EAX"
    },
    {
      "at": "0x0043eee0",
      "definite": true,
      "id": "obs-0010",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ESP,EBP",
      "reg": "ESP",
      "write_kind": "reg"
    },
    {
      "at": "0x0043eee2",
      "id": "obs-0011",
      "index": 7,
      "kind": "REG_RESTORE",
      "raw": "POP EBP",
      "reg": "EBP"
    },
    {
      "at": "0x0043eee3",
      "form": "RET",
      "id": "obs-0012",
      "imm": null,
      "index": 8,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 9,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": true,
      "fp": true,
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
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
    "va": "0x0043ecb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043f3a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043f3f0"
  },
  {
    "name": "FUN_0044ae00",
    "reconstructed": false,
    "va": "0x0044ae00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004860b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0048b370"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0049cfd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a0bf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a1070"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a29a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004c73f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00582250"
  },
  {
    "name": "editor_input_0058ac10",
    "reconstructed": true,
    "va": "0x0058ac10"
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
      "address": "0043eed0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0043eed1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0043eed3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0043eed4",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "0043eed7",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "0043eeda",
      "instruction": "FLD float ptr [EAX + 0x1d4]"
    },
    {
      "address": "0043eee0",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0043eee2",
      "instruction": "POP EBP"
    },
    {
      "address": "0043eee3",
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
  "original_bytes": 9727,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall (receiver in ECX), no stack arguments\",\n    \"hidden_receiver\": \"ECX\",\n    \"hidden_this_register\": \"ECX is read only by the spill at 0x0043eed4\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x0043eeda is FLD dword ptr [EAX+0x1D4] and is the only floating-point instruction in the body. There is no FSTP, FADD, FMUL or memory store, so the loaded value is still on the x87 stack when the frame is torn down and the caller reads ST(0) directly. The caller confirms this: 0x0043f4c6 is FLD1, the matching push of the 1.0f the caller substitutes when it has no child to ask.\",\n    \"return_register\": \"ST(0) - the x87 stack top, NOT an XMM register\",\n    \"return_semantics\": \"the float32 stored at receiver+0x1D4, unmodified\",\n    \"return_type\": \"float\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"single RET at 0x0043eee3\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043ecb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043f3a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043f3f0\"\n      },\n      {\n        \"name\": \"FUN_0044ae00\",\n        \"reconstructed\": false,\n        \"va\": \"0x0044ae00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004860b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0048b370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0049cfd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a0bf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a1070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a29a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004c73f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00582250\"\n      },\n      {\n        \"name\": \"editor_input_0058ac10\",\n        \"reconstructed\": true,\n        \"va\": \"0x0058ac10\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0043ed5d\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043ecb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043ed68\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043ecb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043eda4\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043ecb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043f3be\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043f3a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043f4ba\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043f3f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0044afb9\",\n        \"direction\": \"in\",\n        \"other\": \"0x0044ae00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00486159\",\n        \"direction\": \"in\",\n        \"other\": \"0x004860b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00486164\",\n        \"direction\": \"in\",\n        \"other\": \"0x004860b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0048b6b8\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048b370\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0048b6c3\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048b370\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0048b77e\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048b370\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0048b819\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048b370\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0048b9c9\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048b370\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0049d1ad\",\n        \"direction\": \"in\",\n        \"other\": \"0x0049cfd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004a0fc4\",\n        \"direction\": \"in\",\n        \"other\": \"0x004a0bf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00
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
  "body_end": "0043eee3",
  "body_span_bytes": 20,
  "body_start": "0043eed0",
  "callees": [],
  "callers": [
    "FUN_004860b0",
    "FUN_004a1070",
    "FUN_0048b370",
    "FUN_0044ae00",
    "Editors::cEditor::OnKeyDown",
    "FUN_004a0bf0",
    "FUN_0043f3f0",
    "Editors::cEditor::sub_581F70",
    "FUN_0043f3a0",
    "FUN_004a29a0",
    "FUN_004c73f0",
    "FUN_0049cfd0",
    "FUN_0043ecb0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0043eed0",
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
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_0043eed0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3eed0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0043eed0(void)",
  "size_bytes": 20,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0043eed0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 22,
  "xrefs": [
    {
      "from": "0044afb9"
    },
    {
      "from": "0043f4ba"
    },
    {
      "from": "0043ed5d"
    },
    {
      "from": "0043ed68"
    },
    {
      "from": "0043eda4"
    },
    {
      "from": "004c9086"
    },
    {
      "from": "0043f3be"
    },
    {
      "from": "00486159"
    },
    {
      "from": "00486164"
    },
    {
      "from": "0048b6b8"
    },
    {
      "from": "0048b6c3"
    },
    {
      "from": "0048b77e"
    },
    {
      "from": "0048b819"
    },
    {
      "from": "0048b9c9"
    },
    {
      "from": "0049d1ad"
    },
    {
      "from": "004a15e2"
    },
    {
      "from": "004a2ab0"
    },
    {
      "from": "004a2ec1"
    },
    {
      "from": "004a0fc4"
    },
    {
      "from": "00582b81"
    },
    {
      "from": "00582ba8"
    },
    {
      "from": "0058af90"
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
  "global:The body contains no absolute address operand, so it reads and writes no global."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b04/0043eed0_editor_part_blend_getter.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/0043eed0_editor_part_blend_getter.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/0043eed0.json"
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
    "No original-process trace has been captured. The value actually stored at +0x1D4 in the shipping build, and its range, are runtime facts that static analysis cannot supply.",
    "Whether the getter is ever reached through a pointer stored in a table, which would explain its out-of-line form, needs a reference scan beyond the 29 direct calls."
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
  "Editors::EditorRigblock (SDK candidate, two-offset match)",
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
