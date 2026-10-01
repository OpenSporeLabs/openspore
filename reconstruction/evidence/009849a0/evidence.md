# Evidence 0x009849a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2692020e8d4eaeba1cc18bf06af36cf99bf6b6c4ba4849e12da5c8ff8dc15b17`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04 (read after PUSH ESI, i.e. the incoming ESP+0x08 slot)",
      "name": "target",
      "type": "drawable header *",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x4",
  "return_register": "none",
  "return_type": "void",
  "stack_cleanup_bytes": 4
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
      "entry_ESP+0x4"
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
        "size_inferred": false,
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
  "content_sha256": "780bc951396095a602d965e58e4289cf4e625b79422e4bbf459f50dfd10dc6f7",
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
    "ghidra_parameter_count": 4,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0012"
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
        "obs-0003"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          20
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0012"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012"
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
      "at": "0x009849a0",
      "count": 5,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x009849a1",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x009849a1",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x009849a1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x009849a5",
      "count": 4,
      "first_use": 2,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ECX + -0x4]",
      "reg": "EAX"
    },
    {
      "at": "0x009849a5",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ECX + -0x4]",
      "reg": "ECX"
    },
    {
      "at": "0x009849b8",
      "definite": true,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ECX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {

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
  "count": 12,
  "instructions": [
    {
      "address": "009849a0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "009849a1",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "009849a5",
      "instruction": "LEA EAX,[ECX + -0x4]"
    },
    {
      "address": "009849a8",
      "instruction": "MOV dword ptr [ESI + 0x4],EAX"
    },
    {
      "address": "009849ab",
      "instruction": "MOV dword ptr [ESI],0x1444c24"
    },
    {
      "address": "009849b1",
      "instruction": "MOV dword ptr [ESI + 0x8],0x1"
    },
    {
      "address": "009849b8",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "009849ba",
      "instruction": "MOV EAX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "009849bd",
      "instruction": "CALL EAX"
    },
    {
      "address": "009849bf",
      "instruction": "MOV dword ptr [ESI + 0xc],EAX"
    },
    {
      "address": "009849c2",
      "instruction": "POP ESI"
    },
    {
      "address": "009849c3",
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
  "original_bytes": 7532,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04 (read after PUSH ESI, i.e. the incoming ESP+0x08 slot)\",\n        \"name\": \"target\",\n        \"type\": \"drawable header *\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"none\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:drawable header *\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-DRAWABLE-WAVE9\",\n      \"score\": 19,\n      \"symbol\": \"re_00987ae0\",\n      \"va\": \"0x00987ae0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-UTFWIN-DRAWABLE-WAVE9\",\n      \"score\": 14,\n      \"symbol\": \"re_00985ce0\",\n      \"va\": \"0x00985ce0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-DRAWABLE-WAVE9\",\n      \"score\": 10,\n      \"symbol\": \"re_00b267d0\",\n      \"va\": \"0x00b267d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, offsets, constants, strides, and slot indices were read from the live Ghidra disassembly; imported signatures are candidate labels only. Concrete vtable and port owners, runtime values, and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"SpinnerDrawable\",\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0328\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"UTFWin::SpinnerDrawable::Paint\",\n  \"normalized_symbol\": \"re_009849a0\",\n  \"observed_mechanics\": [\n    \"Push ESI and read the target pointer from the incoming ESP+0x08 slot into ESI.\",\n    \"Form this-4 in EAX with LEA and store it at target+0x4.\",\n    \"Store the constant 0x1444c24 at target+0x0.\",\n    \"Store the constant 1 at target+0x8.\",\n    \"Load this->vtable into EDX, load vtable slot +0x14 into EAX, and call it with ECX still holding this and no pushed argument.\",\n    \"Store the returned word at target+0xc.\",\n    \"Restore ESI and return with RET 0x4.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-UTFWIN-DRAWABLE-WAVE9\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-UTFWIN-DRAWABLE-WAVE9\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-UTFWIN-DRAWABLE-WAVE9\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process invocation or indirect-caller trace was captured.\",\n      \"The 0x1444c24 tag is treated as an opaque published constant, not a decoded type id.\",\n      \"The concrete vtable owner and meaning of slot +0x14 are unresolved; the result is only stored.\",\n      \"gate-utfwin-drawable-slot-14-and-tag-decoding\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_drawable_header_publication_with_back_pointer_bias_and_vtable_derived_slot_observed\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SpinnerDrawable__Paint.c\",\n    \"file\": \"src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SpinnerDrawable__Paint.c\",\n      \"src/reconstruction/pkg_utfwin_drawable_wave9\",\n      \"src/reconstruction/pkg_utfwin_drawable_wave
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
  "body_end": "009849c5",
  "body_span_bytes": 38,
  "body_start": "009849a0",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "009849a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::SpinnerDrawable::Paint",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 4,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "SpinnerDrawable *"
    },
    {
      "name": "pRenderer",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "UIRenderer *"
    },
    {
      "name": "area",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Rectangle *"
    },
    {
      "name": "params",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "RenderParams *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x5849a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::SpinnerDrawable::Paint(SpinnerDrawable * this, UIRenderer * pRenderer, Rectangle * area, RenderParams * params)",
  "size_bytes": 38,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x009849a0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01444c60"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01444c88"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SpinnerDrawable__Paint.c",
  "file": "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__SpinnerDrawable__Paint.c",
    "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp",
    "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.hpp",
    "src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-drawable-wave9/009849a0.json"
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
    "No original-process invocation or indirect-caller trace was captured.",
    "The 0x1444c24 tag is treated as an opaque published constant, not a decoded type id.",
    "The concrete vtable owner and meaning of slot +0x14 are unresolved; the result is only stored.",
    "gate-utfwin-drawable-slot-14-and-tag-decoding"
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
  "SpinnerDrawable",
  "drawable header *",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01444c60"
]
```

## Conflicts

```json
[]
```
