# Evidence 0x00951230

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ed9fe46fa1d8233073d38a397739d400711493c3122961cd13dfd31161db6576`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 stdcall with three caller arguments and callee cleanup",
  "return_semantics": "null pointer in EAX",
  "return_type": "void*",
  "stack_cleanup_bytes": 12,
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
      "entry_ESP+0xc"
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
      }
    ],
    "receiver": false,
    "ret_form": "RET 0xc",
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
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "57453f2f4019f6c2c43ddd8be4cc4aad317bfffda89ccd7205b0ecc9b6ae559c",
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
    "ghidra_parameter_count": 4,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 stdcall with three caller arguments and callee cleanup"
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
        "obs-0003"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 3,
        "total_bytes": 12
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
      "at": "0x00951230",
      "count": 1,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "XOR AL,AL",
      "reg": "EAX"
    },
    {
      "at": "0x00951230",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "XOR AL,AL",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x00951232",
      "form": "RET 0xc",
      "id": "obs-0003",
      "imm": 12,
      "index": 1,
      "kind": "RET",
      "raw": "RET 0xc"
    }
  ],
  "parse": {
    "declared_count": 2,
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
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
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

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x013fa974",
      "0x01419794",
      "0x013fa974",
      "0x01419794",
      "0x013fa974",
      "0x01419794",
      "0x013fa974",
      "0x01419794",
      "0x00951230",
      "0x006f2f20",
      "0x00dde980",
      "0x01419794",
      "0x013fa974",
      "0x013fef9c",
      "0x0141a024",
      "0x01442324"
    ],
    "conflict_id": "VT-003",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "CONFLICT_REMAINS",
    "resolution_status": "CONFLICT_REMAINS",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x013FA974 and 0x01419794 UTFWin 21-slot base candidates",
    "unresolved_reason": "There is no constructor, destructor, complete-table boundary, RTTI, or independent owner evidence to choose between byte-identical arrays."
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
  "count": 2,
  "instructions": [
    {
      "address": "00951230",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00951232",
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
  "original_bytes": 12959,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 stdcall with three caller arguments and callee cleanup\",\n    \"return_semantics\": \"null pointer in EAX\",\n    \"return_type\": \"void*\",\n    \"stack_cleanup_bytes\": 12,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x013fa72c,vtable:0x013fa794\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x01414b10,vtable:0x01418838\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"re_0095f960\",\n      \"va\": \"0x0095f960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x01414b10,vtable:0x01414ce0\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"re_0095f990\",\n      \"va\": \"0x0095f990\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\",\n        \"shared_vtable:vtable:0x01414b10,vtable:0x01414ce0\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"re_0095f9a0\",\n      \"va\": \"0x0095f9a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00801ac0\",\n      \"va\": \"0x00801ac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00835380\",\n      \"va\": \"0x00835380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_core_wave6::CursorManager,openspore::reconstruction::pkg_utfwin_core_wave6::Drawable,openspore::reconstruction::pkg_utfwin_core_wave6::DropIconObject,openspore::reconstruction::pkg_utfwin_core_wave6::ResourceFactory\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"re_00957510\",\n      \"va\": \"0x00957510\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0292\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"UTFWin::UTFWinObject::new_\",\n  \"normalized_symbol\": \"re_00951230\",\n  \"observed_mechanics\": [\n    \"Returns null for all three opaque input words without dereferenci
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
  "body_end": "00951234",
  "body_span_bytes": 5,
  "body_start": "00951230",
  "callees": [],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00951230",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::UTFWinObject::new_",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 4,
  "parameters": [
    {
      "name": "n",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "size_t"
    },
    {
      "name": "align",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "size_t"
    },
    {
      "name": "pName",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "char *"
    },
    {
      "name": "pAllocator",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "ICoreAllocator *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "UTFWinObject *",
  "return_type_resolved": true,
  "rva": "0x551230",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "UTFWinObject * UTFWin::UTFWinObject::new_(size_t n, size_t align, char * pName, ICoreAllocator * pAllocator)",
  "size_bytes": 5,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00951230",
  "vtables": {
    "referenced_by_vtables": [
      "0x013fa8f0",
      "0x013fcc08",
      "0x01418838",
      "0x014191d0",
      "0x01441240",
      "0x01441c18",
      "0x01441fd8",
      "0x01443318",
      "0x01443be8",
      "0x014446f0",
      "0x01444b68",
      "0x01445060",
      "0x014793e0",
      "0x0147f868",
      "0x014805b8",
      "0x01480bf0",
      "0x013fa72c",
      "0x013fa8b0",
      "0x013fb2b8",
      "0x013fb408"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "013fa83c"
    },
    {
      "from": "013fa850"
    },
    {
      "from": "013fa854"
    },
    {
      "from": "013fa878"
    },
    {
      "from": "013fa880"
    },
    {
      "from": "013fa884"
    },
    {
      "from": "013fa888"
    },
    {
      "from": "013fa88c"
    },
    {
      "from": "013fa8dc"
    },
    {
      "from": "013fa8f0"
    },
    {
      "from": "013fa8f4"
    },
    {
      "from": "013fa918"
    },
    {
      "from": "013fa920"
    },
    {
      "from": "013fa924"
    },
    {
      "from": "013fa928"
    },
    {
      "from": "013fa92c"
    },
    {
      "from": "013fa974"
    },
    {
      "from": "013fa988"
    },
    {
      "from": "013fa98c"
    },
    {
      "from": "013fa9b0"
    },
    {
      "from": "013fa9b8"
    },
    {
      "from": "013fa9bc"
    },
    {
      "from": "013fa9c0"
    },
    {
      "from": "013fa9c4"
    },
    {
      "from": "013fb2e4"
    },
    {
      "from": "013fb2f8"
    },
    {
      "from": "013fb2fc"
    },
    {
      "from": "013fb320"
    },
    {
      "from": "013fb328"
    },
    {
      "from": "013fb32c"
    },
    {
      "from": "013fb330"
    },
    {
      "from": "013fb334"
    },
    {
      "from": "013fb434"
    },
    {
      "from": "013fb448"
    },
    {
      "from": "013fb44c"
    },
    {
      "from": "013fb470"
    },
    {
      "from": "013fb478"
    },
    {
      "from": "013fb47c"
    },
    {
      "from": "013fb480"
    },
    {
      "from": "013fb484"
    },
    {
      "from": "013fcc34"
    },
    {
      "from": "013fcc48"
    },
    {
      "from": "013fcc4c"
    },
    {
      "from": "013fcc70"
    },
    {
      "from": "013fcc78"
    },
    {
      "from": "013fcc7c"
    },
    {
      "from": "013fcc80"
    },
    {
      "from": "013fcc84"
    },
    {
      "from": "013fdc60"
    },
    {
      "from": "013fdc64"
    },
    {
      "from": "013fdc9c"
    },
    {
      "from": "013fec60"
    },
    {
      "from": "013fef9c"
    },
    {
      "from": "013fefb0"
    },
    {
      "from": "013fefb4"
    },
    {
      "from": "013fefd8"
    },
    {
      "from": "013fefe0"
    },
    {
      "from": "013fefe4"
    },
    {
      "from": "013fefe8"
    },
    {
      "from": "013fefec"
    },
    {
      "from": "013ff08c"
    },
    {
      "from": "013ff550"
    },
    {
      "from": "0140b608"
    },
    {
      "from": "0140b624"
    },
    {
      "from": "0140b674"
    },
    {
      "from": "014105f8"
    },
    {
      "from": "01412be8"
    },
    {
      "from": "01414634"
    },
    {
      "from": "01414b38"
    },
    {
      "from": "01414b3c"
    },
    {
      "from": "01414b40"
    },
    {
      "from": "01414b44"
    },
    {
      "from": "01414b54"
    },
    {
      "from": "01414b74"
    },
    {
      "from": "01414b84"
    },
    {
      "from": "01414d08"
    },
    {
      "from": "01414d0c"
    },
    {
      "from": "01414d10"
    },
    {
      "from": "01414d14"
    },
    {
      "from": "01414d24"
    },
    {
      "from": "01414d44"
    },
    {
      "from": "01414d54"
    },
    {
      "from": "01414ff8"
    },
    {
      "from": "01414ffc"
    },
    {
      "from": "01415034"
    },
    {
      "from": "01415044"
    },
    {
      "from": "014152c0"
    },
    {
      "from": "014152c4"
    },
    {
      "from": "014152c8"
    },
    {
      "from": "014152cc"
    },
    {
      "from": "014152dc"
    },
    {
      "from": "014152fc"
    },
    {
      "from": "0141530c"
    },
    {
      "from": "014179e4"
    },
    {
      "from": "014179f8"
    },
    {
      "from": "014179fc"
    },
    {
     
[TRUNCATED]
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__UTFWinObject__new_.c",
  "file": "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__UTFWinObject__new_.c",
    "src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-core-wave6/00951230.json"
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
  "vtable:0x013fa7d8",
  "vtable:0x013fa810",
  "vtable:0x013fa8b0",
  "vtable:0x013fa8f0",
  "vtable:0x013fa974",
  "vtable:0x013fb2b8",
  "vtable:0x013fb2f8",
  "vtable:0x013fb408",
  "vtable:0x013fb448",
  "vtable:0x013fcc08",
  "vtable:0x013fcc48",
  "vtable:0x013fdc38",
  "vtable:0x013fdc9c",
  "vtable:0x013fec40"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x013fa974",
      "0x01419794",
      "0x013fa974",
      "0x01419794",
      "0x013fa974",
      "0x01419794",
      "0x013fa974",
      "0x01419794",
      "0x00951230",
      "0x006f2f20",
      "0x00dde980",
      "0x01419794",
      "0x013fa974",
      "0x013fef9c",
      "0x0141a024",
      "0x01442324"
    ],
    "conflict_id": "VT-003",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "CONFLICT_REMAINS",
    "resolution_status": "CONFLICT_REMAINS",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x013FA974 and 0x01419794 UTFWin 21-slot base candidates",
    "unresolved_reason": "There is no constructor, destructor, complete-table boundary, RTTI, or independent owner evidence to choose between byte-identical arrays."
  }
]
```
