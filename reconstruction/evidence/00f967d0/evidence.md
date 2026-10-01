# Evidence 0x00f967d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ad0e9bf260b971ee4e00119e9256c99b36952b388dc721357c1c39e902f74a79`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x04",
    "entry_ESP+0x08",
    "entry_ESP+0x0c"
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0xc",
  "return_note": "The machine-derived ABI record for this VA (briefing.abi) reports return_register ST0 and return_semantics 'float_or_x87_in_ST0'. That is a reading of the x87 PAIR the body executes, not of an outgoing value: 0x00f967dc's FLD result is consumed by the FMUL at 0x00f967e1 and committed to memory by the FSTP at 0x00f967e7, so the x87 stack is EMPTY from 0x00f967e8 onward and no instruction on any path writes ST0 after that. EAX is equally dead: its last writer is the store at 0x00f9682a, two instructions before the terminator, and it is not copied anywhere. The declared return type is void and...",
  "return_type": "void",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 12,
  "stack_cleanup_owner": "callee",
  "termination": "0x00f96830, bytes C2 0C 00. The callee owns all twelve argument bytes: the epilogue's POP ESI (0x00f9682c) and ADD ESP,0x10 (0x00f9682d) land ESP back on its entry value, and 0x62 is the offset from the first instruction to the terminator."
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
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
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
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "2262f3994744692ba4d448a75eec7426795fb0c2067b158d76f1b433fb86b07c",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0024"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0016",
        "obs-0018",
        "obs-0022"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0015",
        "obs-0016",
        "obs-0022"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          524
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0015",
        "obs-0016",
        "obs-0022",
        "obs-0024"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0016"
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
        "obs-0024"
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
      "at": "0x00f967d0",
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
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00f967d0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00f967d3",
      "count": 4,
      "first_use": 1,
      "first_write_index": 2,
      "
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
  "count": 27,
  "instructions": [
    {
      "address": "00f967d0",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00f967d3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00f967d4",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00f967d6",
      "instruction": "MOV ECX,dword ptr [ESI + 0x20c]"
    },
    {
      "address": "00f967dc",
      "instruction": "CALL 0x0097ef00"
    },
    {
      "address": "00f967e1",
      "instruction": "FMUL float ptr [0x0140f334]"
    },
    {
      "address": "00f967e7",
      "instruction": "FSTP float ptr [ESP + 0x4]"
    },
    {
      "address": "00f967eb",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00f967f1",
      "instruction": "CVTSS2SI EAX,XMM0"
    },
    {
      "address": "00f967f5",
      "instruction": "CVTSI2SS XMM1,EAX"
    },
    {
      "address": "00f967f9",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00f967fb",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00f967fe",
      "instruction": "UCOMISS XMM0,XMM1"
    },
    {
      "address": "00f96801",
      "instruction": "CMOVC EAX,ECX"
    },
    {
      "address": "00f96804",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00f96808",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "00f9680a",
      "instruction": "MOV ECX,dword ptr [ESI + 0x20c]"
    },
    {
      "address": "00f96810",
      "instruction": "CALL 0x00fb7bb0"
    },
    {
      "address": "00f96815",
      "instruction": "MOV EDX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00f96819",
      "instruction": "MOV dword ptr [EDX],EAX"
    },
    {
      "address": "00f9681b",
      "instruction": "MOV ECX,dword ptr [ESI + 0x20c]"
    },
    {
      "address": "00f96821",
      "instruction": "CALL 0x00fb7bc0"
    },
    {
      "address": "00f96826",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00f9682a",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "00f9682c",
      "instruction": "POP ESI"
    },
    {
      "address": "00f9682d",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00f96830",
      "instruction": "RET 0xc"
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
  "original_bytes": 9237,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x04\",\n      \"entry_ESP+0x08\",\n      \"entry_ESP+0x0c\"\n    ],\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0xc\",\n    \"return_note\": \"The machine-derived ABI record for this VA (briefing.abi) reports return_register ST0 and return_semantics 'float_or_x87_in_ST0'. That is a reading of the x87 PAIR the body executes, not of an outgoing value: 0x00f967dc's FLD result is consumed by the FMUL at 0x00f967e1 and committed to memory by the FSTP at 0x00f967e7, so the x87 stack is EMPTY from 0x00f967e8 onward and no instruction on any path writes ST0 after that. EAX is equally dead: its last writer is the store at 0x00f9682a, two instructions before the terminator, and it is not copied anywhere. The declared return type is void and...\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 12,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"0x00f96830, bytes C2 0C 00. The callee owns all twelve argument bytes: the epilogue's POP ESI (0x00f9682c) and ADD ESP,0x10 (0x00f9682d) land ESP back on its entry value, and 0x62 is the offset from the first instruction to the terminator.\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"RUNTIME validation is gated at 0\",\n    \"The briefing's abi block disagrees with the listing about the return register (ST0)\",\n    \"The receiver's class is unnamed\",\n    \"The three direct callees' semantics are unknown beyond their own two instructions\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00f967dc\",\n        \"direction\": \"out\",\n        \"other\": \"0x0097ef00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f96810\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fb7bb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f96821\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fb7bc0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0568\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:0x0140f334\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00f967d0\",\n  \"normalized_symbol\": \"FUN_00f967d0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"Conditions are listed in full under runtime_gate.conditions; the shortest form is that a live receiver of this vtable's class, with a non-null word at +0x20c, must be driven through both floor arms and through a NaN, and the three callee returns plus the three out-pointer addresses must be captured at the call sites.\",\n      
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
  "body_end": "00f96832",
  "body_span_bytes": 99,
  "body_start": "00f967d0",
  "callees": [
    "FUN_0097ef00",
    "FUN_00fb7bc0",
    "FUN_00fb7bb0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00f967d0",
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
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00f967d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xb967d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00f967d0(void)",
  "size_bytes": 99,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00f967d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01490be8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01490c60"
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
  "global:0x0140f334"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00f967d0/00f967d0.json"
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
    "Conditions are listed in full under runtime_gate.conditions; the shortest form is that a live receiver of this vtable's class, with a non-null word at +0x20c, must be driven through both floor arms and through a NaN, and the three callee returns plus the three out-pointer addresses must be captured at the call sites.",
    "RUNTIME is required and gated at 0: no trace was run and no differential evidence was gathered for this VA."
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
  "OpaquePointee",
  "OpaqueReceiver",
  "PKG_SW1_00F967D0_THISCALL",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01490be8"
]
```

## Conflicts

```json
[]
```
