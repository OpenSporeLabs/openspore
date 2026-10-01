# Evidence 0x00960050

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1c35e16253687c41b3adec2feb8a4423cadbe7566d388192b28b2e7c3fcbac98`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit window receiver in ECX and caller cleanup",
  "return_semantics": "window drawable pointer in EAX",
  "return_type": "Drawable*",
  "stack_cleanup_bytes": 4,
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
      "EBX",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "cfe2ced24cbc52fd3e1224fc7b6b0c8633ea54eeb2e7159e5f26b98e7a7ca1b8",
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
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit window receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0021"
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
        "obs-0006",
        "obs-0007",
        "obs-0013"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          484
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0021"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0021"
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
        "obs-0021"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0021"
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
      "at": "0x00960050",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00960051",
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
      "at": "0x00960051",
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
      "at": "0x00960051",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00960055",
      "count": 6,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00960056",
      "count": 1,
      "first_use": 3,
      "first_write_index": 14,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00960056",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00960060",
      "count": 3,
      "first_use": 6,
      "first_write_index": 7,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00960061",
      "definite": true,
      "id": "obs-0009",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [EDI + 0x1e4]",
      "reg": "EBX",
      "write_kin
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

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960050",
      "0x00960050",
      "0x00960250",
      "0x00960250"
    ],
    "conflict_id": "U-SCREEN-STATE-BITS",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x00809e60",
      "0x00809e60",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960050",
      "0x00960050",
      "0x00960250",
      "0x00960250",
      "0x00960310",
      "0x00960310",
      "0x00961300",
      "0x00961300",
      "0x00961980",
      "0x00961980"
    ],
    "conflict_id": "U-UTFWIN-DISPATCH",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
  "count": 31,
  "instructions": [
    {
      "address": "00960050",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00960051",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00960055",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00960056",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00960058",
      "instruction": "CMP ESI,dword ptr [EDI + 0x1e4]"
    },
    {
      "address": "0096005e",
      "instruction": "JZ 0x00960097"
    },
    {
      "address": "00960060",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00960061",
      "instruction": "MOV EBX,dword ptr [EDI + 0x1e4]"
    },
    {
      "address": "00960067",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "00960069",
      "instruction": "JZ 0x0096008a"
    },
    {
      "address": "0096006b",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "0096006d",
      "instruction": "JZ 0x00960077"
    },
    {
      "address": "0096006f",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00960071",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00960073",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00960075",
      "instruction": "CALL EDX"
    },
    {
      "address": "00960077",
      "instruction": "MOV dword ptr [EDI + 0x1e4],ESI"
    },
    {
      "address": "0096007d",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "0096007f",
      "instruction": "JZ 0x0096008a"
    },
    {
      "address": "00960081",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00960083",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00960086",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00960088",
      "instruction": "CALL EDX"
    },
    {
      "address": "0096008a",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "0096008c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x90]"
    },
    {
      "address": "00960092",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00960094",
      "instruction": "CALL EDX"
    },
    {
      "address": "00960096",
      "instruction": "POP EBX"
    },
    {
      "address": "00960097",
      "instruction": "POP EDI"
    },
    {
      "address": "00960098",
      "instruction": "POP ESI"
    },
    {
      "address": "00960099",
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
  "original_bytes": 10644,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit window receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"window drawable pointer in EAX\",\n    \"return_type\": \"Drawable*\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x013fdb18,vtable:0x01414bc0\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"re_0095f960\",\n      \"va\": \"0x0095f960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"re_0095f990\",\n      \"va\": \"0x0095f990\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 25,\n      \"symbol\": \"re_0095f9a0\",\n      \"va\": \"0x0095f9a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00801ac0\",\n      \"va\": \"0x00801ac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00835380\",\n      \"va\": \"0x00835380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0299\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"UTFWin::Window::GetDrawable\",\n  \"normalized_symbol\": \"re_00960050\",\n  \"observed_mechanics\": [\n    \"Returns the old drawable unchanged for pointer equality.\",\n    \"Otherwi
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
  "body_end": "0096009b",
  "body_span_bytes": 76,
  "body_start": "00960050",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00960050",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::Window::GetDrawable",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IWindow *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "IDrawable *",
  "return_type_resolved": true,
  "rva": "0x560050",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "IDrawable * UTFWin::Window::GetDrawable(IWindow * this)",
  "size_bytes": 76,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00960050",
  "vtables": {
    "referenced_by_vtables": [
      "0x01414ed4",
      "0x0141873c",
      "0x014190d4",
      "0x0141930c",
      "0x014195ac",
      "0x0141ab94",
      "0x01441144",
      "0x01441794",
      "0x01441edc",
      "0x01443aec",
      "0x014458c4",
      "0x0147f76c",
      "0x0147fbe4",
      "0x013fdb18",
      "0x013fdb6c",
      "0x01414bc0",
      "0x01414c14",
      "0x01415178",
      "0x014151cc",
      "0x01419920"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 32,
  "xrefs": [
    {
      "from": "013fdba0"
    },
    {
      "from": "01414c48"
    },
    {
      "from": "01414f38"
    },
    {
      "from": "01415200"
    },
    {
      "from": "01443280"
    },
    {
      "from": "014187a0"
    },
    {
      "from": "01419138"
    },
    {
      "from": "01419370"
    },
    {
      "from": "01419610"
    },
    {
      "from": "014199a8"
    },
    {
      "from": "01419bd8"
    },
    {
      "from": "0141abf8"
    },
    {
      "from": "014411a8"
    },
    {
      "from": "014417f8"
    },
    {
      "from": "01441b80"
    },
    {
      "from": "01441f40"
    },
    {
      "from": "01442e78"
    },
    {
      "from": "01443b50"
    },
    {
      "from": "01444658"
    },
    {
      "from": "01444ad0"
    },
    {
      "from": "01444fc8"
    },
    {
      "from": "01445498"
    },
    {
      "from": "01445928"
    },
    {
      "from": "01445dc8"
    },
    {
      "from": "01445fe0"
    },
    {
      "from": "01446218"
    },
    {
      "from": "014464f8"
    },
    {
      "from": "0145d6c0"
    },
    {
      "from": "01479348"
    },
    {
      "from": "0147f998"
    },
    {
      "from": "0147fc48"
    },
    {
      "from": "0147f7d0"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__GetDrawable.c",
  "file": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__GetDrawable.c",
    "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-core-wave6/00960050.json"
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
    "drawable reference ownership, window vtable, and returned pointer lifetime remain gated",
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
  "Drawable*",
  "openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager",
  "openspore::reconstruction::pkg_utfwin_core_wave6::Drawable",
  "openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject",
  "openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory",
  "openspore::reconstruction::pkg_utfwin_core_wave6::TooltipCore",
  "openspore::reconstruction::pkg_utfwin_core_wave6::WindowCore"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013fdb18",
  "vtable:0x013fdb6c",
  "vtable:0x01414bc0",
  "vtable:0x01414c14",
  "vtable:0x01414ed4",
  "vtable:0x01414f38",
  "vtable:0x01415178",
  "vtable:0x014151cc",
  "vtable:0x0141873c",
  "vtable:0x014187a0",
  "vtable:0x014190d4",
  "vtable:0x01419138",
  "vtable:0x0141930c",
  "vtable:0x01419370",
  "vtable:0x014195ac",
  "vtable:0x01419610"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960050",
      "0x00960050",
      "0x00960250",
      "0x00960250"
    ],
    "conflict_id": "U-SCREEN-STATE-BITS",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x00809e60",
      "0x00809e60",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960050",
      "0x00960050",
      "0x00960250",
      "0x00960250",
      "0x00960310",
      "0x00960310",
      "0x00961300",
      "0x00961300",
      "0x00961980",
      "0x00961980"
    ],
    "conflict_id": "U-UTFWIN-DISPATCH",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
