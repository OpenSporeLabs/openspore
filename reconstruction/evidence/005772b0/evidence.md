# Evidence 0x005772b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `36ccd9ab0bd9ab7b4fc92df00b5cc5d14f36dfcf41eb0ce970dc58bef8f2c055`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX, moved to ESI at 0x005772b1 and held for the whole body",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "There is no MOV EAX/AL and no XOR EAX,EAX in the 36-instruction body. 0x005772ca and 0x00577307 are CALL EAX with the address loaded from a vtable, and the tested precondition is only that the object pointer is non-null.",
  "return_register": "EAX (clobbered, unused)",
  "return_semantics": "no meaningful return; EAX is clobbered by the two indirect calls and is never read by any of the 10 observed call sites",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI",
    "EBX"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "two exits, both a bare RET: 0x005772ed on the decrement path and 0x0057730b on the destroy/early-out path"
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
      "EBX",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "d812044dab089267ea0022cafbfd0edf266fc75adf962605f38aedd436e33d18",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011",
        "obs-0017"
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
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0007"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          240
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0017"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0017"
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
        "obs-0011",
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011",
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
      "at": "0x005772b0",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005772b1",
      "count": 4,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005772b1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x005772b3",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0xf0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005772bd",
      "count": 9,
      "first_use": 5,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x005772bd",
      "definite": true,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EAX]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005772bf",
      "definite": true,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ECX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005772c4",
      "count": 2,
      "first_use": 9,
      "first_write_index": 6,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x16c]",
      "reg": "EDX"
    },
    {
      "at": "0x005772ca",
      "base": "EAX",
      "disp": null,
      "id": "obs-0009",
      "index": 10,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EAX",
      "via": "register"
    },
    {
      "at": "0x005772ec",
      "id": "obs-0010",
      "index": 20,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005772ed",
      "form": "RET",
      "id": "obs-0011",
      "imm": null,
      "index": 21,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x005772f2",
      "count": 2,
      "first_use": 24,
      "first_write_index": 25,
      "id": "obs-0012",
      "index": 24,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x005772f3",
      "definite": true,
    
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
    "va": "0x0057a610"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057e160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057e790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057f6c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": "Editors::cEditor::OnExit",
    "reconstructed": false,
    "va": "0x00587a20"
  },
  {
    "name": "editor_input_00588570",
    "reconstructed": true,
    "va": "0x00588570"
  },
  {
    "name": "editor_input_0058ac10",
    "reconstructed": true,
    "va": "0x0058ac10"
  },
  {
    "name": "editor_input_0058b650",
    "reconstructed": true,
    "va": "0x0058b650"
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
  "count": 36,
  "instructions": [
    {
      "address": "005772b0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005772b1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005772b3",
      "instruction": "MOV EAX,dword ptr [ESI + 0xf0]"
    },
    {
      "address": "005772b9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005772bb",
      "instruction": "JZ 0x0057730a"
    },
    {
      "address": "005772bd",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "005772bf",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "005772c1",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005772c3",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005772c4",
      "instruction": "MOV EAX,dword ptr [EDX + 0x16c]"
    },
    {
      "address": "005772ca",
      "instruction": "CALL EAX"
    },
    {
      "address": "005772cc",
      "instruction": "MOV EAX,dword ptr [ESI + 0xf0]"
    },
    {
      "address": "005772d2",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005772d4",
      "instruction": "JZ 0x0057730a"
    },
    {
      "address": "005772d6",
      "instruction": "MOV dword ptr [ESI + 0xf0],0x0"
    },
    {
      "address": "005772e0",
      "instruction": "MOV ECX,dword ptr [EAX + 0x40]"
    },
    {
      "address": "005772e3",
      "instruction": "CMP ECX,0x1"
    },
    {
      "address": "005772e6",
      "instruction": "JLE 0x005772ee"
    },
    {
      "address": "005772e8",
      "instruction": "DEC ECX"
    },
    {
      "address": "005772e9",
      "instruction": "MOV dword ptr [EAX + 0x40],ECX"
    },
    {
      "address": "005772ec",
      "instruction": "POP ESI"
    },
    {
      "address": "005772ed",
      "instruction": "RET"
    },
    {
      "address": "005772ee",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "005772f0",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "005772f2",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005772f3",
      "instruction": "MOV EBX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "005772f6",
      "instruction": "SHR EBX,0x1f"
    },
    {
      "address": "005772f9",
      "instruction": "AND BL,0x1"
    },
    {
      "address": "005772fc",
      "instruction": "MOVZX ESI,BL"
    },
    {
      "address": "005772ff",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00577300",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00577301",
      "instruction": "MOV EAX,dword ptr [EDX + 0x170]"
    },
    {
      "address": "00577307",
      "instruction": "CALL EAX"
    },
    {
      "address": "00577309",
      "instruction": "POP EBX"
    },
    {
      "address": "0057730a",
      "instruction": "POP ESI"
    },
    {
      "address": "0057730b",
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
  "original_bytes": 9585,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX, moved to ESI at 0x005772b1 and held for the whole body\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"There is no MOV EAX/AL and no XOR EAX,EAX in the 36-instruction body. 0x005772ca and 0x00577307 are CALL EAX with the address loaded from a vtable, and the tested precondition is only that the object pointer is non-null.\",\n    \"return_register\": \"EAX (clobbered, unused)\",\n    \"return_semantics\": \"no meaningful return; EAX is clobbered by the two indirect calls and is never read by any of the 10 observed call sites\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"ESI\",\n      \"EBX\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"two exits, both a bare RET: 0x005772ed on the decrement path and 0x0057730b on the destroy/early-out path\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057a610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057e160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057e790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057f6c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": \"Editors::cEditor::OnExit\",\n        \"reconstructed\": false,\n        \"va\": \"0x00587a20\"\n      },\n      {\n        \"name\": \"editor_input_00588570\",\n        \"reconstructed\": true,\n        \"va\": \"0x00588570\"\n      },\n      {\n        \"name\": \"editor_input_0058ac10\",\n        \"reconstructed\": true,\n        \"va\": \"0x0058ac10\"\n      },\n      {\n        \"name\": \"editor_input_0058b650\",\n        \"reconstructed\": true,\n        \"va\": \"0x0058b650\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0057a621\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057a610\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057e1bc\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057e160\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057e7b7\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057e790\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00580225\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057f6c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005874da\",\n        \"direction\": \"in\",\n        \"other\": \"0x00587270\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00587cca\",\n        \"direction\": \"in\",\n        \"other\": \"0x00587a20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00587d47\",\n        \"direction\": \"in\",\n        \"other\": \"0x00587a20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00589be8\",\n        \"direction\": \"in\",\n        \"other\": \"0x00588570\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsi
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
  "body_end": "0057730b",
  "body_span_bytes": 92,
  "body_start": "005772b0",
  "callees": [],
  "callers": [
    "Editors::cEditor::OnKeyDown",
    "FUN_0057f6c0",
    "Editors::cEditor::SetActiveMode",
    "FUN_0057e790",
    "Editors::cEditor::OnMouseUp",
    "Editors::cEditor::OnExit",
    "Editors::cEditor::OnMouseDown",
    "FUN_0057e160",
    "FUN_0057a610"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "005772b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005772b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1772b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005772b0(void)",
  "size_bytes": 92,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005772b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "005874da"
    },
    {
      "from": "00587cca"
    },
    {
      "from": "00587d47"
    },
    {
      "from": "0058ba34"
    },
    {
      "from": "0057e1bc"
    },
    {
      "from": "0057a621"
    },
    {
      "from": "0057e7b7"
    },
    {
      "from": "00580225"
    },
    {
      "from": "0058b107"
    },
    {
      "from": "00589be8"
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
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b03/005772b0.json"
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
    "A trace must confirm that IModelWorld slot +0x170 does not itself decrement the counter, since this body reaches it with the counter still at 1 (or 0).",
    "A trace with a concrete editor receiver is required before the +0xf0 member and the +0xe9 guard can be given semantic names.",
    "No original-process trace has ever been captured for 0x005772b0, so every claim here is static. A differential trace must confirm that mpWorld is non-null whenever the +0xf0 member is non-null, because both virtual calls dereference model->mpWorld twice with no null check."
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
