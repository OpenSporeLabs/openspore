# Evidence 0x0095fa30

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f435e179d3d83770459b2de12b537146a60b60775f34e557eb085c73c5d14ccd`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "thiscall; the receiver is the ECX hidden argument (the decompiler renders it as `IWindow * this`, and Ghidra warns 'Unknown calling convention')",
    "thiscall"
  ],
  "hidden_receiver": "ECX is the window receiver, the decompiler renders it as IWindow * this",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    "{'address_at_entry': '[ESP+0x4]', 'ghidra_type': 'IWindow * pChildWindow', 'stack_slot': 0, 'use': 'copied verbatim into EAX and then into receiver+0x80; never dereferenced', 'width_bytes': 4}",
    "{'address_at_entry': '[ESP+0x4]', 'ghidra_type': 'IWindow * pChildWindow', 'use': 'copied verbatim into EAX at 0x0095fa30 and stored at receiver+0x80 at 0x0095fa34; never dereferenced, never compared, never tested', 'width_bytes': 4}"
  ],
  "receiver": "ECX, used as the base of the single store `MOV dword ptr [ECX + 0x80],EAX` at 0x0095fa34; never saved to another register and never read from",
  "ret_form": "RET 0x4",
  "return_register": "none; EAX still holds the copied stack word at the RET",
  "return_semantics": [
    "void",
    "void; the body stores the argument and falls through to RET 0x4. No instruction after 0x0095fa30 writes EAX, so the copied argument word survives in EAX at the RET, and no evidence claims that residue as a returned value."
  ],
  "return_type": "void",
  "saved_registers": [],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee"
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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "e9c584d1da1963a9759f0ffa7b724603bc301223f206d30d3300d0ca19ae0c7a",
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
    "persisted_calling_convention": "[\"thiscall; the receiver is the ECX hidden argument (the decompiler renders it as `IWindow * this`, and Ghidra warns 'Unknown calling convention')\", 'thiscall']"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0006"
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
        "obs-0002"
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
        "obs-0004",
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          128
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0006"
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
        "obs-0006"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x0095fa30",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x0095fa30",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0095fa30",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0095fa34",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x80],EAX",
      "reg": "ECX"
    },
    {
      "at": "0x0095fa34",
      "count": 1,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x80],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x0095fa3a",
      "form": "RET 0x4",
      "id": "obs-0006",
      "imm": 4,
      "index": 2,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 3,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 128,
    "offsets": [
      128
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "writte
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
  "count": 3,
  "instructions": [
    {
      "address": "0095fa30",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0095fa34",
      "instruction": "MOV dword ptr [ECX + 0x80],EAX"
    },
    {
      "address": "0095fa3a",
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
  "original_bytes": 12985,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": [\n      \"thiscall; the receiver is the ECX hidden argument (the decompiler renders it as `IWindow * this`, and Ghidra warns 'Unknown calling convention')\",\n      \"thiscall\"\n    ],\n    \"hidden_receiver\": \"ECX is the window receiver, the decompiler renders it as IWindow * this\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": [\n      \"{'address_at_entry': '[ESP+0x4]', 'ghidra_type': 'IWindow * pChildWindow', 'stack_slot': 0, 'use': 'copied verbatim into EAX and then into receiver+0x80; never dereferenced', 'width_bytes': 4}\",\n      \"{'address_at_entry': '[ESP+0x4]', 'ghidra_type': 'IWindow * pChildWindow', 'use': 'copied verbatim into EAX at 0x0095fa30 and stored at receiver+0x80 at 0x0095fa34; never dereferenced, never compared, never tested', 'width_bytes': 4}\"\n    ],\n    \"receiver\": \"ECX, used as the base of the single store `MOV dword ptr [ECX + 0x80],EAX` at 0x0095fa34; never saved to another register and never read from\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"none; EAX still holds the copied stack word at the RET\",\n    \"return_semantics\": [\n      \"void\",\n      \"void; the body stores the argument and falls through to RET 0x4. No instruction after 0x0095fa30 writes EAX, so the copied argument word survives in EAX at the RET, and no evidence claims that residue as a returned value.\"\n    ],\n    \"return_type\": \"void\",\n    \"saved_registers\": [],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb18,vtable:0x01414bc0\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb18,vtable:0x01414bc0\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb18,vtable:0x013fdb6c\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00960050\",\n      \"va\": \"0x00960050\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x01414c14\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_utfwin_layout_wave6_009601e0\",\n      \"va\": \"0x009601e0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x01414c14\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961260\",\n      \"va\": \"0x00961260\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x01414c14\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961300\",\n      \"va\": \"0x00961300\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014431f8\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00962830\",\n      \"va\": \"0x00962830\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01441748\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e20\",\n      \"va\": \"0x00967e20\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0297\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:high\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"UTFWin::Window::IsAncestorOf\",\n  \"normalized_symbol\": \"UTFWin::Window::IsAncestorOf\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"Confirm the containing table base and slot displacement of at least one of the 33 references so the shared-vtable analogue chain can be grounded.\",\n      \"Observe a real virtual call through one of the 33 function words and record the receiver instance state before and after the store at receiver+0x80.\",\n      \"Observe whether any caller consumes AL after the RET 0x4, which would give the EAX residue a real contract the static body cannot prove.\",\n      \"Record the real receiver allocation size, because the 0x84 byte modeled extent is only the prefix through the written slot.\",\n      \"Record the runtime value stored at receiver+0x80 and whether the same word is later consumed as a window pointer, a vtable-adjacent field or a reference count carrier.\",\
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
  "body_end": "0095fa3c",
  "body_span_bytes": 13,
  "body_start": "0095fa30",
  "callees": [],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "0095fa30",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::Window::IsAncestorOf",
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
      "name": "pChildWindow",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "IWindow *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x55fa30",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool UTFWin::Window::IsAncestorOf(IWindow * this, IWindow * pChildWindow)",
  "size_bytes": 13,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0095fa30",
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
  "xref_count": 33,
  "xrefs": [
    {
      "from": "013fdb6c"
    },
    {
      "from": "0140f854"
    },
    {
      "from": "01414c14"
    },
    {
      "from": "01414f04"
    },
    {
      "from": "014151cc"
    },
    {
      "from": "0141876c"
    },
    {
      "from": "01419104"
    },
    {
      "from": "0141933c"
    },
    {
      "from": "014195dc"
    },
    {
      "from": "01419974"
    },
    {
      "from": "01419ba4"
    },
    {
      "from": "0141abc4"
    },
    {
      "from": "01441174"
    },
    {
      "from": "014417c4"
    },
    {
      "from": "01441b4c"
    },
    {
      "from": "01441f0c"
    },
    {
      "from": "01442e44"
    },
    {
      "from": "01443b1c"
    },
    {
      "from": "01444624"
    },
    {
      "from": "01444a9c"
    },
    {
      "from": "01444f94"
    },
    {
      "from": "01445464"
    },
    {
      "from": "014458f4"
    },
    {
      "from": "01445d94"
    },
    {
      "from": "01445fac"
    },
    {
      "from": "014461e4"
    },
    {
      "from": "014464c4"
    },
    {
      "from": "0145d68c"
    },
    {
      "from": "01479314"
    },
    {
      "from": "0147f964"
    },
    {
      "from": "0147fc14"
    },
    {
      "from": "0147f79c"
    },
    {
      "from": "0144324c"
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
  "global:high"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__IsAncestorOf.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__IsAncestorOf.c",
    "reconstruction/staging/pkg-0095fa30-utfwin-isancestorof/utfwin_is_ancestor_of_0095fa30.cpp",
    "reconstruction/staging/pkg-0095fa30-utfwin-isancestorof/utfwin_is_ancestor_of_0095fa30.hpp",
    "reconstruction/staging/pkg-0095fa30-utfwin-isancestorof/utfwin_is_ancestor_of_0095fa30_model_test.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-0095fa30/dogfood_0095fa30.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-0095fa30/dogfood_0095fa30.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-0095fa30/dogfood_0095fa30_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-0095fa30-utfwin-isancestorof/0095fa30.json",
    "reconstruction/metadata/pkg-orchestrate-dogfood-0095fa30/0095fa30.json"
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
    "Confirm the containing table base and slot displacement of at least one of the 33 references so the shared-vtable analogue chain can be grounded.",
    "Observe a real virtual call through one of the 33 function words and record the receiver instance state before and after the store at receiver+0x80.",
    "Observe whether any caller consumes AL after the RET 0x4, which would give the EAX residue a real contract the static body cannot prove.",
    "Record the real receiver allocation size, because the 0x84 byte modeled extent is only the prefix through the written slot.",
    "Record the runtime value stored at receiver+0x80 and whether the same word is later consumed as a window pointer, a vtable-adjacent field or a reference count carrier.",
    "confirm the class identity behind the 33 vtable images; the binary has no MSVC RTTI",
    "observe one real virtual call through a slot +0x00 word and record whether the caller consumes AL, which would settle the void-vs-bool return type",
    "record the receiver allocation size at runtime; the 0x84 byte modelled extent is only the prefix through the written slot",
    "record the value stored at receiver+0x80 and find its consumer, to establish whether the SDK name IsAncestorOf is misassigned"
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
  "DATA",
  "IWindow * pChildWindow",
  "medium (machine says void, SDK label says bool; the machine reading is the one modelled)",
  "openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof::AbiIsAncestorOf0095fa30",
  "openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof::Opaque",
  "openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof::OpaqueWindow",
  "openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof::OpaqueWindowVTable",
  "openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30::Abi0095fa30",
  "openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30::OpaqueWindow",
  "openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30::OpaqueWindowLayout",
  "openspore::reconstruction::pkg_orchestrate_dogfood_0095fa30::TargetPorts",
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
  "vtable:0x0140f854",
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
  "vtable:0x01419ba4"
]
```

## Conflicts

```json
[]
```
