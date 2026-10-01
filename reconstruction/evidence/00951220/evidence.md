# Evidence 0x00951220

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `32e5998f69d6cb84c656ed3ddbb64f574f1fc4564d204a8102c31c9afe400b08`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 stdcall with five caller arguments and callee cleanup",
  "return_semantics": "null pointer in EAX",
  "return_type": "void*",
  "stack_cleanup_bytes": 20,
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
    "calling_convention": "__stdcall",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": false,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": false,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": false,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": false,
    "ret_form": "RET 0x14",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": false,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": false,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": false,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "stack_cleanup_bytes": 20,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x14"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 20,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x14",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "85c1bfbbed71b113298898e0f293a900350a009f6a6122798ff850b1a3a66651",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 stdcall with five caller arguments and callee cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the callee pops 20 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 20,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 5,
        "total_bytes": 20
      }
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "calling convention is __stdcall: a callee that pops stack arguments with no register receiver",
      "confidence": "INFERRED",
      "id": "C6",
      "value": "__stdcall"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
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
      "at": "0x00951220",
      "count": 1,
      "first_use": 0,
      "first_write_
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
  "count": 2,
  "instructions": [
    {
      "address": "00951220",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00951222",
      "instruction": "RET 0x14"
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
  "original_bytes": 10288,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 stdcall with five caller arguments and callee cleanup\",\n    \"return_semantics\": \"null pointer in EAX\",\n    \"return_type\": \"void*\",\n    \"stack_cleanup_bytes\": 20,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x013fa72c,vtable:0x013fa794\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00801ac0\",\n      \"va\": \"0x00801ac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00835380\",\n      \"va\": \"0x00835380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00957510\",\n      \"va\": \"0x00957510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_0095f960\",\n      \"va\": \"0x0095f960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_0095f990\",\n      \"va\": \"0x0095f990\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_0095f9a0\",\n      \"va\": \"0x0095f9a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0291\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"UTFWin::GetAllocator\",\n  \"normalized_symbol\": \"re_00951220\",\n  \"observed_mechanics\": [\n    \"Returns null for all five opaque input words without dereferencing them.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-UTFWIN-CORE-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n     
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
  "body_end": "00951224",
  "body_span_bytes": 5,
  "body_start": "00951220",
  "callees": [],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00951220",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::GetAllocator",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "ICoreAllocator *",
  "return_type_resolved": true,
  "rva": "0x551220",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "ICoreAllocator * UTFWin::GetAllocator(void)",
  "size_bytes": 5,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00951220",
  "vtables": {
    "referenced_by_vtables": [
      "0x013fa8f0",
      "0x013fcc08",
      "0x014805b8",
      "0x01480bf0",
      "0x013fa72c",
      "0x013fa8b0",
      "0x013fb2b8",
      "0x013fb408",
      "0x013fef58",
      "0x014184e4",
      "0x01419fd0",
      "0x0141a538",
      "0x0141a57c",
      "0x0141a5c0",
      "0x014422a4",
      "0x01442584",
      "0x0144347c",
      "0x01444220",
      "0x01444314",
      "0x0147e9d0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "013fa840"
    },
    {
      "from": "013fa844"
    },
    {
      "from": "013fa84c"
    },
    {
      "from": "013fa8e0"
    },
    {
      "from": "013fa8e4"
    },
    {
      "from": "013fa8ec"
    },
    {
      "from": "013fa978"
    },
    {
      "from": "013fa97c"
    },
    {
      "from": "013fa984"
    },
    {
      "from": "013fb2e8"
    },
    {
      "from": "013fb2ec"
    },
    {
      "from": "013fb2f4"
    },
    {
      "from": "013fb438"
    },
    {
      "from": "013fb43c"
    },
    {
      "from": "013fb444"
    },
    {
      "from": "013fcc38"
    },
    {
      "from": "013fcc3c"
    },
    {
      "from": "013fcc44"
    },
    {
      "from": "013fefa0"
    },
    {
      "from": "013fefa4"
    },
    {
      "from": "013fefac"
    },
    {
      "from": "014179e8"
    },
    {
      "from": "014179ec"
    },
    {
      "from": "014179f4"
    },
    {
      "from": "01417a98"
    },
    {
      "from": "01417a9c"
    },
    {
      "from": "01417aa4"
    },
    {
      "from": "01418d30"
    },
    {
      "from": "01418d34"
    },
    {
      "from": "01418d3c"
    },
    {
      "from": "01418f30"
    },
    {
      "from": "01418f34"
    },
    {
      "from": "01418f3c"
    },
    {
      "from": "01419798"
    },
    {
      "from": "0141979c"
    },
    {
      "from": "014197a4"
    },
    {
      "from": "0141a028"
    },
    {
      "from": "0141a02c"
    },
    {
      "from": "0141a034"
    },
    {
      "from": "0141a580"
    },
    {
      "from": "0141a584"
    },
    {
      "from": "0141a58c"
    },
    {
      "from": "0141a618"
    },
    {
      "from": "0141a61c"
    },
    {
      "from": "0141a624"
    },
    {
      "from": "0141a9c8"
    },
    {
      "from": "0141a9cc"
    },
    {
      "from": "0141a9d4"
    },
    {
      "from": "0141af38"
    },
    {
      "from": "0141af3c"
    },
    {
      "from": "0141af44"
    },
    {
      "from": "01440db8"
    },
    {
      "from": "01440dbc"
    },
    {
      "from": "01440dc4"
    },
    {
      "from": "01442328"
    },
    {
      "from": "0144232c"
    },
    {
      "from": "01442334"
    },
    {
      "from": "01442608"
    },
    {
      "from": "0144260c"
    },
    {
      "from": "01442614"
    },
    {
      "from": "01443500"
    },
    {
      "from": "01443504"
    },
    {
      "from": "0144350c"
    },
    {
      "from": "01443dc0"
    },
    {
      "from": "01443dc4"
    },
    {
      "from": "01443dcc"
    },
    {
      "from": "01444398"
    },
    {
      "from": "0144439c"
    },
    {
      "from": "014443a4"
    },
    {
      "from": "0147eaa0"
    },
    {
      "from": "0147eaa4"
    },
    {
      "from": "0147eaac"
    },
    {
      "from": "0147ea00"
    },
    {
      "from": "0147ea04"
    },
    {
      "from": "0147ea0c"
    },
    {
      "from": "014805f4"
    },
    {
      "from": "014806e8"
    },
    {
      "from": "014806f4"
    },
    {
      "from": "014807ec"
    },
    {
      "from": "014808fc"
    },
    {
      "from": "01480a0c"
    },
    {
      "from": "01480b1c"
    },
    {
      "from": "01480c2c"
    },
    {
      "from": "01480d3c"
    },
    {
      "from": "01480e4c"
    },
    {
      "from": "014819e0"
    },
    {
      "from": "014819e4"
    },
    {
      "from": "014819ec"
    },
    {
      "from": "013fa798"
    },
    {
      "from": "013fa79c"
    },
    {
      "from": "013fa7a4"
    },
    {
      "from": "01489784"
    },
    {
      "from": "0148978c"
    },
    {
      "from": "01489990"
    },
    {
      "from": "01489994"
    },
    {
      "from": "0148999c"
    },
    {
      "from": "01489dac"
    },
    {
      "from": "01417bf0"
    },
    {
      "from": "01417bf4"
    },
    {
      "from": "01417bfc"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GetAllocator.c",
  "file": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__GetAllocator.c",
    "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-core-wave6/00951220.json"
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
    "allocation/serialization boundary and runtime caller contract remain gated",
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
  "openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager",
  "openspore::reconstruction::pkg_utfwin_core_wave6::Drawable",
  "openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject",
  "openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory",
  "openspore::reconstruction::pkg_utfwin_core_wave6::TooltipCore",
  "openspore::reconstruction::pkg_utfwin_core_wave6::WindowCore",
  "void*"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013fa72c",
  "vtable:0x013fa794",
  "vtable:0x013fa810",
  "vtable:0x013fa8b0",
  "vtable:0x013fa8f0",
  "vtable:0x013fa974",
  "vtable:0x013fb2b8",
  "vtable:0x013fb408",
  "vtable:0x013fcc08",
  "vtable:0x013fef58",
  "vtable:0x013fef9c",
  "vtable:0x014179b8",
  "vtable:0x01417a68",
  "vtable:0x01417bc0",
  "vtable:0x014184e4",
  "vtable:0x01418544"
]
```

## Conflicts

```json
[]
```
