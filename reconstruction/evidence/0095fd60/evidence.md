# Evidence 0x0095fd60

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7518932e28a63ee615c86e2fcfc1cc6f4be9a3a82b5dcfd65717d022bd4835f0`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall; receiver in ECX (MOV ESI,ECX at 0x0095fd64)",
  "receiver": "ECX, saved to ESI at 0x0095fd64, used as the base for [ESI+0xa8], [ESI+0x1dc] and both vtable loads",
  "return_semantics": "void",
  "return_type": "void",
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
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
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
  "content_sha256": "f6c5dce1a1fd6d19bb0fadb2eacdb7a2a144bcf7c2d76811693302dfb9a5fb79",
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
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall; receiver in ECX (MOV ESI,ECX at 0x0095fd64)"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020"
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
        "obs-0008"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0014"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          168,
          476
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0014",
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
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020"
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
      "and_esp": null,
      "at": "0x0095fd60",
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
      "raw": "SUB ESP,0x1c",
      "sub": 28
    },
    {
      "at": "0x0095fd60",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x1c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0095fd63",
      "count": 8,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0095fd64",
      "count": 5,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0095fd64",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x0095fd66",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0xa8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0095fd6c",
      "count": 5,
      "first_use": 4,
      "first_write_index": 0,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x24]",
      "reg": "ESP"
    },
    {
      "at": "0x0095fd6c",
      "base": "ESP",
      "disp": 36,
      "id": "obs-0008",
      "index": 4,

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
  "count": 26,
  "instructions": [
    {
      "address": "0095fd60",
      "instruction": "SUB ESP,0x1c"
    },
    {
      "address": "0095fd63",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0095fd64",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0095fd66",
      "instruction": "MOV EAX,dword ptr [ESI + 0xa8]"
    },
    {
      "address": "0095fd6c",
      "instruction": "MOV ECX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "0095fd70",
      "instruction": "CMP ECX,EAX"
    },
    {
      "address": "0095fd72",
      "instruction": "JZ 0x0095fdb0"
    },
    {
      "address": "0095fd74",
      "instruction": "MOV dword ptr [ESI + 0xa8],ECX"
    },
    {
      "address": "0095fd7a",
      "instruction": "MOV dword ptr [ESP + 0x10],ECX"
    },
    {
      "address": "0095fd7e",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "0095fd82",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "0095fd84",
      "instruction": "MOV EDX,dword ptr [EAX + 0x114]"
    },
    {
      "address": "0095fd8a",
      "instruction": "LEA ECX,[ESP + 0x4]"
    },
    {
      "address": "0095fd8e",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0095fd8f",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0095fd91",
      "instruction": "MOV dword ptr [ESP + 0x10],0x13"
    },
    {
      "address": "0095fd99",
      "instruction": "CALL EDX"
    },
    {
      "address": "0095fd9b",
      "instruction": "CMP dword ptr [ESI + 0x1dc],0x0"
    },
    {
      "address": "0095fda2",
      "instruction": "JZ 0x0095fdb0"
    },
    {
      "address": "0095fda4",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "0095fda6",
      "instruction": "MOV EDX,dword ptr [EAX + 0x90]"
    },
    {
      "address": "0095fdac",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0095fdae",
      "instruction": "CALL EDX"
    },
    {
      "address": "0095fdb0",
      "instruction": "POP ESI"
    },
    {
      "address": "0095fdb1",
      "instruction": "ADD ESP,0x1c"
    },
    {
      "address": "0095fdb4",
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
  "original_bytes": 8486,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall; receiver in ECX (MOV ESI,ECX at 0x0095fd64)\",\n    \"receiver\": \"ECX, saved to ESI at 0x0095fd64, used as the base for [ESI+0xa8], [ESI+0x1dc] and both vtable loads\",\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb18,vtable:0x01414bc0\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb18,vtable:0x01414bc0\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb18,vtable:0x013fdb6c\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00960050\",\n      \"va\": \"0x00960050\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x01414c14\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_utfwin_layout_wave6_009601e0\",\n      \"va\": \"0x009601e0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x01414c14\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961260\",\n      \"va\": \"0x00961260\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x01414c14\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961300\",\n      \"va\": \"0x00961300\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014431f8\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00962830\",\n      \"va\": \"0x00962830\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01441748\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e20\",\n      \"va\": \"0x00967e20\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0298\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"UTFWin::Window::func35\",\n  \"normalized_symbol\": \"UTFWin::Window::func35\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"ownership and lifetime of the word stored at +0xa8 unresolved\",\n      \"producer of the +0x1dc gate unresolved\",\n      \"record consumer semantics (vtable slot 0x114) unresolved\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__func35.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__func35.c\",\n      \"reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60.cpp\",\n      \"reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60.hpp\",\n      \"reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-utfwin-func35-wave12/0095fd60.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"UTFWin\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"utfwin-framework\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__func35.c\",\n    \"dependencies\": [\n      \"app-lifecycle\",\n      \"resource-io\"\n    ],\n    \"evidence\": \"CONFIRMED\",\n    \"kg_node_id\": \"fun:0095fd60\",\n    \"name\": \"UTFWin::Window::func35\",\n    \"priority\": \"P0\",\n    \"provenance\": {\n      \"classifier\": \"triage-v4\",\n      \"generated_at\": \"2026-09-23T10:12:09Z\",\n      \"generator\": \"subagent-7-sequential-triage\",\n      \"sdk_name\": \"UTFWin::Window::func35\",\n      \"snapshot\": \"2540f2ca\",\n      \"snapshot_sha256\": \"2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8\",\n      \"vtable_addrs\": [\n        \"013fdb18\",\n        \"013fdb6c\",\n        \"01414bc0\",\n        \"01414c14\",\n        \"01414ed
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
  "body_end": "0095fdb6",
  "body_span_bytes": 87,
  "body_start": "0095fd60",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0095fd60",
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
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "UTFWin::Window::func35",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IWindow *"
    },
    {
      "name": "param_2",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x55fd60",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::Window::func35(IWindow * this, int param_2)",
  "size_bytes": 87,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0095fd60",
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
      "from": "013fdb70"
    },
    {
      "from": "01414c18"
    },
    {
      "from": "01414f08"
    },
    {
      "from": "014151d0"
    },
    {
      "from": "01418770"
    },
    {
      "from": "01419108"
    },
    {
      "from": "01419340"
    },
    {
      "from": "014195e0"
    },
    {
      "from": "01419978"
    },
    {
      "from": "01419ba8"
    },
    {
      "from": "0141abc8"
    },
    {
      "from": "01441178"
    },
    {
      "from": "014417c8"
    },
    {
      "from": "01441b50"
    },
    {
      "from": "01441f10"
    },
    {
      "from": "01442e48"
    },
    {
      "from": "01443b20"
    },
    {
      "from": "01444628"
    },
    {
      "from": "01444aa0"
    },
    {
      "from": "01444f98"
    },
    {
      "from": "01445468"
    },
    {
      "from": "014458f8"
    },
    {
      "from": "01445d98"
    },
    {
      "from": "01445fb0"
    },
    {
      "from": "014461e8"
    },
    {
      "from": "014464c8"
    },
    {
      "from": "0145d690"
    },
    {
      "from": "01479318"
    },
    {
      "from": "0147f968"
    },
    {
      "from": "0147fc18"
    },
    {
      "from": "0147f7a0"
    },
    {
      "from": "01443250"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__func35.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__func35.c",
    "reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60.cpp",
    "reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60.hpp",
    "reconstruction/staging/pkg-utfwin-func35-wave12/utfwin_func35_0095fd60_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-func35-wave12/0095fd60.json"
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
    "ownership and lifetime of the word stored at +0xa8 unresolved",
    "producer of the +0x1dc gate unresolved",
    "record consumer semantics (vtable slot 0x114) unresolved"
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
  "openspore::reconstruction::pkg_utfwin_func35_wave12::OpaquePendingQueue",
  "openspore::reconstruction::pkg_utfwin_func35_wave12::OpaqueStateMessage",
  "openspore::reconstruction::pkg_utfwin_func35_wave12::OpaqueWindow",
  "openspore::reconstruction::pkg_utfwin_func35_wave12::OpaqueWindowVTable",
  "void"
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
  "vtable:0x01415178",
  "vtable:0x014151cc",
  "vtable:0x0141873c",
  "vtable:0x014190d4",
  "vtable:0x0141930c",
  "vtable:0x014195ac",
  "vtable:0x01419920",
  "vtable:0x01419974",
  "vtable:0x01419b50",
  "vtable:0x01419ba4",
  "vtable:0x0141ab34"
]
```

## Conflicts

```json
[]
```
