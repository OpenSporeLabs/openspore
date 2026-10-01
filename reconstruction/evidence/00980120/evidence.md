# Evidence 0x00980120

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0b7758e0f67917308c222f97cf0a53059f7bc4e9a50090ee58b19bfc38b23f43`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit effect receiver in ECX and caller cleanup",
  "return_semantics": "void",
  "return_type": "void",
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "caller"
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
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EDI",
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "d1f9179de7ad652e39709db1596fd41c3ee309d007beeb6ecd70b60d22f6c921",
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
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit effect receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020"
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
        "obs-0004",
        "obs-0006"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          100,
          104
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0010",
        "obs-0020"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020"
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
        "obs-0020"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00980120",
      "count": 4,
      "first_use": 0,
      "first_write_index": 7,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x68]",
      "reg": "ECX"
    },
    {
      "at": "0x00980120",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x68]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00980123",
      "count": 3,
      "first_use": 1,
      "first_write_index": 13,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "FLD float ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00980123",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0004",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "FLD float ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00980127",
      "count": 3,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00980128",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00980128",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESI",
      "write_kind": "mem_load"
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
  "count": 20,
  "instructions": [
    {
      "address": "00980120",
      "instruction": "MOV EAX,dword ptr [ECX + 0x68]"
    },
    {
      "address": "00980123",
      "instruction": "FLD float ptr [ESP + 0x8]"
    },
    {
      "address": "00980127",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00980128",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0098012c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0098012d",
      "instruction": "MOV EDI,dword ptr [ESI]"
    },
    {
      "address": "0098012f",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00980130",
      "instruction": "MOV ECX,dword ptr [ECX + 0x64]"
    },
    {
      "address": "00980133",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00980136",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00980137",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00980138",
      "instruction": "CALL 0x007f5eb0"
    },
    {
      "address": "0098013d",
      "instruction": "MOV EDX,dword ptr [EDI + 0x5c]"
    },
    {
      "address": "00980140",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00980143",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00980144",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00980146",
      "instruction": "CALL EDX"
    },
    {
      "address": "00980148",
      "instruction": "POP EDI"
    },
    {
      "address": "00980149",
      "instruction": "POP ESI"
    },
    {
      "address": "0098014a",
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
  "original_bytes": 8863,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit effect receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_0096fec0\",\n      \"va\": \"0x0096fec0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_0096ffc0\",\n      \"va\": \"0x0096ffc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_0097e440\",\n      \"va\": \"0x0097e440\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_0097e550\",\n      \"va\": \"0x0097e550\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_0097e890\",\n      \"va\": \"0x0097e890\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_0097e990\",\n      \"va\": \"0x0097e990\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_0097ea50\",\n      \"va\": \"0x0097ea50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_00980200\",\n      \"va\": \"0x00980200\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00980138\",\n        \"direction\": \"out\",\n        \"other\": \"0x007f5eb0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0320\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"UTFWin::ModulateEffect::SetColors\",\n 
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
  "body_end": "0098014c",
  "body_span_bytes": 45,
  "body_start": "00980120",
  "callees": [
    "FUN_007f5eb0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00980120",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "UTFWin::ModulateEffect::SetColors",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IModulateEffect *"
    },
    {
      "name": "color1",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "Color"
    },
    {
      "name": "color2",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Color"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x580120",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::ModulateEffect::SetColors(IModulateEffect * this, Color color1, Color color2)",
  "size_bytes": 45,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00980120",
  "vtables": {
    "referenced_by_vtables": [
      "0x01443d90"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01443e14"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ModulateEffect__SetColors.c",
  "file": "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ModulateEffect__SetColors.c",
    "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-effects-wave6/00980120.json"
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
    "blend helper, color vtable, and target/color ownership remain gated",
    "runtime validation not run"
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
  "openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect",
  "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget",
  "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout",
  "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01443d90"
]
```

## Conflicts

```json
[]
```
