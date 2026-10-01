# Evidence 0x0096fec0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `af95890264020fb8a9736d447a72b7a0c6d2106b5988a1346612a5beb18321bf`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit opaque word in ECX and caller cleanup",
  "return_semantics": "object pointer in EAX or null",
  "return_type": "Opaque*",
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
    "calling_convention": "__stdcall",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
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
    "receiver": false,
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_arguments": [
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
  "content_sha256": "24940c6bec093a730c505a28bc202820f4052ad1f202be1277af61c926eecb6f",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__stdcall",
    "candidate_conventions": [
      "__stdcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit opaque word in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0010",
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
        "obs-0002"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0011"
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
        "obs-0010",
        "obs-0011"
      ],
      "claim": "calling convention is __stdcall: a callee that pops stack arguments with no register receiver",
      "confidence": "INFERRED",
      "id": "C6",
      "value": "__stdcall"
    },
    {
      "based_on": [
        "obs-0010",
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
        "obs-0010",
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x0096fec0",
      "count": 1,
      "first_use": 0,
      "first_write_index": 9,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x0096fec0",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0096fec0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0096fec8",
      "id": "obs-0004",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x009512c0",
      "target": "0x009512c0"
    },
    {
      "at": "0x0096fecd",
      "count": 3,
      "first_use": 4,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x0096fed7",
      "id": "obs-0006",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x009512d0",
      "target": "0x009512d0"
    },
    {
      "at": "0x0096fedc",
      "definite": true,
      "id": "obs-0007",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0096fee3",
      "definite": true,
      "id": "obs-0008",
      "index": 12,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x0096fee5",
      "id": "obs-0009",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0096fe30",
      "target": "0x0096fe30"
    },
    {
      "at": "0x0096feea",
      "form": "RET 0x8",
      "id": "obs-0010",
      "imm": 8,
      "index": 14,
      "kind": "RET",
      "raw": "RET 0x8"
    },
    {
      "at": "0x0096feef",
      "form": "RET 0x8",
      "id": "obs-0011",
      "imm": 8,
      "index": 16,
      "kind": "RET",
      "raw": "RET 0x8"
    }
  ],
  "parse": {
    "declared_count": 17,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": 
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
  "count": 17,
  "instructions": [
    {
      "address": "0096fec0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0096fec4",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0096fec6",
      "instruction": "JNZ 0x0096fecd"
    },
    {
      "address": "0096fec8",
      "instruction": "CALL 0x009512c0"
    },
    {
      "address": "0096fecd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0096fece",
      "instruction": "PUSH 0x14424f4"
    },
    {
      "address": "0096fed3",
      "instruction": "PUSH 0x4"
    },
    {
      "address": "0096fed5",
      "instruction": "PUSH 0x60"
    },
    {
      "address": "0096fed7",
      "instruction": "CALL 0x009512d0"
    },
    {
      "address": "0096fedc",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "0096fedf",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0096fee1",
      "instruction": "JZ 0x0096feed"
    },
    {
      "address": "0096fee3",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0096fee5",
      "instruction": "CALL 0x0096fe30"
    },
    {
      "address": "0096feea",
      "instruction": "RET 0x8"
    },
    {
      "address": "0096feed",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "0096feef",
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
  "original_bytes": 9354,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit opaque word in ECX and caller cleanup\",\n    \"return_semantics\": \"object pointer in EAX or null\",\n    \"return_type\": \"Opaque*\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"utfwin_0096ffc0\",\n      \"va\": \"0x0096ffc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:Opaque*,openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"utfwin_0097e440\",\n      \"va\": \"0x0097e440\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"utfwin_0097e890\",\n      \"va\": \"0x0097e890\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"utfwin_00980200\",\n      \"va\": \"0x00980200\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_0097e550\",\n      \"va\": \"0x0097e550\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_0097e990\",\n      \"va\": \"0x0097e990\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_0097ea50\",\n      \"va\": \"0x0097ea50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout,openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"utfwin_00980120\",\n      \"va\": \"0x00980120\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0096fec8\",\n        \"direction\": \"out\",\n        \"other\": \"0x009512c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0096fed7\",\n        \"direction\": \"out\",\n        \"other\": \"0x009512d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0096fee5\",\n        \"direction\": \"out\",\n        \"other\": \"0x0096fe30\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_tru
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
  "body_end": "0096fef1",
  "body_span_bytes": 50,
  "body_start": "0096fec0",
  "callees": [
    "FUN_009512c0",
    "FUN_0096fe30",
    "FUN_009512d0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0096fec0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::GlideEffect::GetProxyID",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "ILayoutElement *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "uint32_t",
  "return_type_resolved": true,
  "rva": "0x56fec0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "uint32_t UTFWin::GlideEffect::GetProxyID(ILayoutElement * this)",
  "size_bytes": 50,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0096fec0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01442490"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "014424a4"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__GetProxyID.c",
  "file": "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GlideEffect__GetProxyID.c",
    "src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-effects-wave6/0096fec0.json"
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
    "allocator, type name, constructor, and returned object ownership remain gated",
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
  "Opaque*",
  "openspore::reconstruction::pkg_utfwin_effects_wave6::FloatRect",
  "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueColorTarget",
  "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueLayout",
  "openspore::reconstruction::pkg_utfwin_effects_wave6::OpaqueModulateEffect"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01442490"
]
```

## Conflicts

```json
[
  {
    "derived": "__stdcall",
    "field": "calling_convention",
    "kind": "derived_vs_persisted",
    "persisted": "x86-32 thiscall with first explicit opaque word in ECX and caller cleanup",
    "resolution_status": "unresolved"
  }
]
```
