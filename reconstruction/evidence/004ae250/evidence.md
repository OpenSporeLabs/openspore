# Evidence 0x004ae250

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b8b31ec81d0dcaff08802952947481e76180d41b5c50ad617bf4448f1453c745`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "return_type": "void",
  "stack_arguments": [
    {
      "adapter_use": "ignored",
      "entry_offset": "ESP+4",
      "name": "index",
      "signed": true,
      "type": "int",
      "width_bytes": 4
    },
    {
      "adapter_use": "ignored",
      "entry_offset": "ESP+8",
      "fields": [
        {
          "keys": [
            "name",
            "offset",
            "type",
            "width_bytes"
          ]
        },
        {
          "keys": [
            "name",
            "offset",
            "type",
            "width_bytes"
          ]
        },
        {
          "keys": [
            "name",
            "offset",
            "type",
            "width_bytes"
          ]
        }
      ],
      "name": "color",
      "type": "EditorModelColor / ColorRGB",
      "width_bytes": 12
    }
  ],
  "stack_cleanup_bytes": 16
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX;void_possible",
    "saved_registers": [
      "EBP"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_read_without_deref"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [
    {
      "field": "stack_cleanup_bytes",
      "inferred": 0,
      "kind": "inferred_vs_persisted",
      "persisted": 16,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "b4ed9dae646bd197c0fb7dca80eef07d229fe93395e02725d736ecaf8ef06840",
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
    "ghidra_parameter_count": 3,
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
        "obs-0009"
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
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0009"
      ],
      "claim": "calling convention is __thiscall: 0x004ae250 is slot 5 of the vptr-backed vftable at 0x013ef110, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 11,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 5,
        "table": "0x013ef110"
      }
    },
    {
      "based_on": [
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    },
    {
      "based_on": [
        "obs-0009"
      ],
      "claim": "EAX is never written and no call can clobber it, so a void return is possible; this is a flag, never a type",
      "confidence": "APPROXIMATION",
      "id": "RT3",
      "value": {
        "void_possible": true
      }
    }
  ],
  "observations": [
    {
      "at": "0x004ae250",
      "count": 3,
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
      "at": "0x004ae250",
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
      "at": "0x004ae251",
      "count": 1,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004ae251",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004ae253",
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
      "at": "0x004ae254",
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
      "at": "0x004ae257",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ESP,EBP",
      "reg": "ESP",
      "write_kind": "reg"
    },
    {
      "at": "0x004ae259",
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_RESTORE",
      "raw": "POP EBP",
      "reg": "EBP"
    },
    {
      "at": "0x004ae25a",
      "form": "RET",
      "id": "obs-0009",
      "imm": null,
      "index": 6,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 7,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "
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
    "va": "0x00441440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0044d8f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0044e720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00451400"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00453dc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00453e20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00454dc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00455fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00456cb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0047fcb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004928d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004942b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0049b460"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004b2f80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004b7660"
  },
  {
    "name": "editor_input_00588570",
    "reconstructed": true,
    "va": "0x00588570"
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
  "count": 7,
  "instructions": [
    {
      "address": "004ae250",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004ae251",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004ae253",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004ae254",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "004ae257",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004ae259",
      "instruction": "POP EBP"
    },
    {
      "address": "004ae25a",
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
  "original_bytes": 12754,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"adapter_use\": \"ignored\",\n        \"entry_offset\": \"ESP+4\",\n        \"name\": \"index\",\n        \"signed\": true,\n        \"type\": \"int\",\n        \"width_bytes\": 4\n      },\n      {\n        \"adapter_use\": \"ignored\",\n        \"entry_offset\": \"ESP+8\",\n        \"fields\": [\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\",\n              \"type\",\n              \"width_bytes\"\n            ]\n          },\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\",\n              \"type\",\n              \"width_bytes\"\n            ]\n          },\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\",\n              \"type\",\n              \"width_bytes\"\n            ]\n          }\n        ],\n        \"name\": \"color\",\n        \"type\": \"EditorModelColor / ColorRGB\",\n        \"width_bytes\": 12\n      }\n    ],\n    \"stack_cleanup_bytes\": 16\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 10,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 10,\n      \"symbol\": \"Editors_EditorUI_HandleMessage_005e0000\",\n      \"va\": \"0x005e0000\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"editor_query_service_005ca960\",\n      \"va\": \"0x005ca960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"editor_query_reset_005dd750\",\n      \"va\": \"0x005dd750\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"editor_query_clear_flags_0093db80\",\n      \"va\": \"0x0093db80\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01458024,vtable:0x01458788\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The SDK formal signature and raw ECX-only executable entry disagree on explicit argument presence, so the package keeps a formal no-op adapter separate from the exact raw body without claiming setter semantics.\",\n    \"The executable body supports only a no-op contract; it contains no evidence for color assignment, bounds checks, sentinels, or errors.\",\n    \"The ten data pointer slots are unnamed and untyped in live Ghidra, so concrete owner and interface semantics remain unresolved.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEditorModel\",\n  \"cluster\": \"editor-core\",\n  \"confidence\": 0.98,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00441440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0044d8f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0044e720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00451400\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00453dc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00453e20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00454dc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00455fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00456cb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0047fcb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004928d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004942b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0049b460\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004b2f80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004b7660\"\n      },\n      {\n        \"name\": \"editor_input_00588570\",\n        \"reconstructed\": true,\n        \"va\": \"0x00588570\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x004414f4\",\n
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
  "body_end": "004ae25a",
  "body_span_bytes": 11,
  "body_start": "004ae250",
  "callees": [],
  "callers": [
    "FUN_004b7660",
    "FUN_00451400",
    "FUN_00456cb0",
    "FUN_00453dc0",
    "FUN_00453e20",
    "FUN_004942b0",
    "FUN_0049b460",
    "FUN_00454dc0",
    "FUN_00455fa0",
    "FUN_0044e720",
    "FUN_0044d8f0",
    "FUN_00441440",
    "FUN_0047fcb0",
    "FUN_004b2f80",
    "FUN_004928d0",
    "Editors::cEditor::OnMouseDown"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "004ae250",
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
  "name": "Editors::EditorModel::SetColor",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "EditorModel *"
    },
    {
      "name": "index",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "color",
      "ordinal": 2,
      "storage": "Stack[0xc]:12",
      "type": "ColorRGB"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0xae250",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Editors::EditorModel::SetColor(EditorModel * this, int index, ColorRGB color)",
  "size_bytes": 11,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004ae250",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f2194",
      "0x01458024",
      "0x01458788",
      "0x013f21d8",
      "0x013f276c",
      "0x013f2d68",
      "0x013ef110",
      "0x01453998",
      "0x01453254",
      "0x014599e8",
      "0x01459a88"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 31,
  "xrefs": [
    {
      "from": "00451d31"
    },
    {
      "from": "004414f4"
    },
    {
      "from": "00453e7d"
    },
    {
      "from": "00454e42"
    },
    {
      "from": "004561b3"
    },
    {
      "from": "00456d3d"
    },
    {
      "from": "00492dd2"
    },
    {
      "from": "0044d951"
    },
    {
      "from": "00494668"
    },
    {
      "from": "0049b87f"
    },
    {
      "from": "0044e7a7"
    },
    {
      "from": "004b7669"
    },
    {
      "from": "004b76b5"
    },
    {
      "from": "00453df0"
    },
    {
      "from": "0047fcd5"
    },
    {
      "from": "004b3119"
    },
    {
      "from": "004b3167"
    },
    {
      "from": "013ef124"
    },
    {
      "from": "013f21d8"
    },
    {
      "from": "013f219c"
    },
    {
      "from": "013f2770"
    },
    {
      "from": "013f2d70"
    },
    {
      "from": "01453258"
    },
    {
      "from": "014599f0"
    },
    {
      "from": "0145399c"
    },
    {
      "from": "00588791"
    },
    {
      "from": "005887d5"
    },
    {
      "from": "005d8454"
    },
    {
      "from": "01458028"
    },
    {
      "from": "0145878c"
    },
    {
      "from": "01459a8c"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorModel__SetColor.c",
  "file": "src/reconstruction/pkg10_editor_dispatch/editor_model_set_color.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorModel__SetColor.c",
    "src/reconstruction/pkg10_editor_dispatch/editor_model_set_color.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/004ae250.json"
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
    "gate-editor-model-setcolor-symbol-mapping"
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
  "EditorModelColor",
  "EditorModelColor / ColorRGB",
  "OpaqueEditorModel",
  "float",
  "int",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013ef110",
  "vtable:0x013f2194",
  "vtable:0x013f21d8",
  "vtable:0x013f276c",
  "vtable:0x013f2d68",
  "vtable:0x01453254",
  "vtable:0x01453998",
  "vtable:0x01458024",
  "vtable:0x01458788",
  "vtable:0x014599e8",
  "vtable:0x01459a88"
]
```

## Conflicts

```json
[]
```
