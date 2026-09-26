# Evidence 0x00fc7e10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `df4dc2c136bac6df623b4a2bf4994bc236fbc5cb9c24f66b640884d0038bcb9b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x4",
    "entry_ESP+0x8"
  ],
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "name": "first_word",
      "observed": true,
      "ordinal": 1,
      "size_inferred": false,
      "sizes": [
        4
      ],
      "type": "opaque 32-bit word"
    },
    {
      "entry_offset": "entry_ESP+0x8",
      "name": "second_word",
      "observed": true,
      "ordinal": 2,
      "size_inferred": false,
      "sizes": [
        4
      ],
      "type": "opaque 32-bit word"
    }
  ],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_observation": "EAX exits holding the first stack word. No instruction produces a result in EAX, so the machine level fact is a 4-byte value in EAX whose value equals the first argument; whether the original source produced it deliberately is NOT established by this evidence.",
  "return_register": "EAX",
  "return_semantics": "opaque 32-bit word in EAX, equal to the first stack argument; intended-return semantics unresolved",
  "return_type": "OpaqueWord",
  "return_width_bytes": 4,
  "saved_registers": "none; no register is pushed and no callee-saved register is written",
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8"
}
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

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\n/* WARNING: Unknown calling convention */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n\nImageTiling UTFWin__ImageDrawable__GetTiling(IImageDrawable *this)\n\n{\n  int in_ECX;\n  undefined4 in_stack_00000008;\n  \n  *(IImageDrawable **)(in_ECX + 8) = this;\n  *(undefined4 *)(in_ECX + 0x10) = in_stack_00000008;\n  return (ImageTiling)this;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 5,
  "instructions": [
    {
      "address": "00fc7e10",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00fc7e14",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00fc7e18",
      "instruction": "MOV dword ptr [ECX + 0x8],EAX"
    },
    {
      "address": "00fc7e1b",
      "instruction": "MOV dword ptr [ECX + 0x10],EDX"
    },
    {
      "address": "00fc7e1e",
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
  "original_bytes": 9061,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0x8\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"name\": \"first_word\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"type\": \"opaque 32-bit word\"\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"name\": \"second_word\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"type\": \"opaque 32-bit word\"\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_observation\": \"EAX exits holding the first stack word. No instruction produces a result in EAX, so the machine level fact is a 4-byte value in EAX whose value equals the first argument; whether the original source produced it deliberately is NOT established by this evidence.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"opaque 32-bit word in EAX, equal to the first stack argument; intended-return semantics unresolved\",\n    \"return_type\": \"OpaqueWord\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": \"none; no register is pushed and no callee-saved register is written\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005f9230\",\n      \"va\": \"0x005f9230\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005f9310\",\n      \"va\": \"0x005f9310\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005fc330\",\n      \"va\": \"0x005fc330\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 5,\n      \"symbol\": \"FUN_00aeb160\",\n      \"va\": \"0x00aeb160\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01492140\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"app_canvas_00847a40\",\n      \"va\": \"0x00847a40\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0511\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"UTFWin::ImageDrawable::GetTiling\",\n  \"normalized_symbol\": \"UTFWin::ImageDrawable::GetTiling\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process invocation or indirect-caller trace was captured, so no concrete caller is known and the argument values a real caller passes cannot be observed.\",\n      \"The declared types of the words at receiver +0x08 and +0x10 are not established. Their observed uses are a CALL target and a call argument respectively, which constrains but does not prove them.\",\n      \"The owning C++ class name and the interface identity of slot +0x1c are not established. SporeApp.exe carries no MSVC RTTI, so class identity cannot be read from the binary; the 0x01493990 class is known only to derive from the 0x01491730 class because its constructor calls the latter's constructor.\",\n      \"Whether the +
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
  "body_end": "00fc7e20",
  "body_span_bytes": 17,
  "body_start": "00fc7e10",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00fc7e10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "in_stack_00000008",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "in_ECX",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "this",
      "storage": "Stack[0x4]:4",
      "type": "IImageDrawable *"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "UTFWin::ImageDrawable::GetTiling",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IImageDrawable *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "ImageTiling",
  "return_type_resolved": true,
  "rva": "0xbc7e10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "ImageTiling UTFWin::ImageDrawable::GetTiling(IImageDrawable * this)",
  "size_bytes": 17,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00fc7e10",
  "vtables": {
    "referenced_by_vtables": [
      "0x01492140",
      "0x01491730",
      "0x01493990"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "0149174c"
    },
    {
      "from": "0149215c"
    },
    {
      "from": "014939ac"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__GetTiling.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__GetTiling.c",
    "reconstruction/staging/pkg-utfwin-slot7-wave12/.clang-format",
    "reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12.cpp",
    "reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12.hpp",
    "reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-slot7-wave12/00fc7e10.json"
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
    "No original-process invocation or indirect-caller trace was captured, so no concrete caller is known and the argument values a real caller passes cannot be observed.",
    "The declared types of the words at receiver +0x08 and +0x10 are not established. Their observed uses are a CALL target and a call argument respectively, which constrains but does not prove them.",
    "The owning C++ class name and the interface identity of slot +0x1c are not established. SporeApp.exe carries no MSVC RTTI, so class identity cannot be read from the binary; the 0x01493990 class is known only to derive from the 0x01491730 class because its constructor calls the latter's constructor.",
    "Whether the +0x10 and +0x14 words belong to the same sub-object as the constructor-initialised words is unresolved; none of the three constructors initialises them."
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueWord",
  "opaque 32-bit word"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01491730",
  "vtable:0x01492140",
  "vtable:0x01493990"
]
```

## Conflicts

```json
[]
```
