# Evidence 0x007b86e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `545a4d10d907946f14c6e267eee3397c222b3a78c14f7265361c23bc1c64064d`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (receiver in ECX), no stack arguments",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is the receiver; 0x007b86e3 ADD ECX,4 biases it to the embedded sub-object and it stays biased for the indirect call at 0x007b86fb",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x007b86e6 ADD EAX,-1 leaves the new count in EAX and 0x007b86ec JNZ branches to 0x007b86ff (RET) with EAX untouched, so the non-zero path returns the decremented count. The zero path ends at 0x007b86fd XOR EAX,EAX, so it returns exactly 0. Both paths write the full 32-bit register.",
  "return_register": "EAX",
  "return_semantics": "the decremented reference count, or 0 when the zero arm ran and the object was destroyed",
  "return_type": "std::int32_t",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single RET at 0x007b86ff; the JNZ at 0x007b86ec targets it directly"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "466f0671a17c1ea7c1ad110ad3c99fe54e23fbbd077b1bdb4b6a36003820c2db",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
    "persisted_calling_convention": "__thiscall (receiver in ECX), no stack arguments"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0008"
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
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          8
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008"
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
        "obs-0008"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008"
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
      "at": "0x007b86e0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x8]",
      "reg": "ECX"
    },
    {
      "at": "0x007b86e0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007b86e3",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "ADD ECX,0x4",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x007b86e9",
      "count": 3,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x4],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x007b86f7",
      "definite": true,
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007b86fb",
      "count": 1,
      "first_use": 9,
      "first_write_index": 7,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x007b86fb",
      "base": "EDX",
      "disp": null,
      "id": "obs-0007",
      "index": 9,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x007b86ff",
      "form": "RET",
      "id": "obs-0008",
      "imm": null,
      "index": 11,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 12,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
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
    "max_offset": 8,
    "offsets": [
      8
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "integral",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 
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
    "va": "0x00650190"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00658c70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0065e110"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076dee0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00782660"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007bb670"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007bced0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007c1c10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00801230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b60d80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e642a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ed8a30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f33bf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fffdd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01070290"
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
  "count": 12,
  "instructions": [
    {
      "address": "007b86e0",
      "instruction": "MOV EAX,dword ptr [ECX + 0x8]"
    },
    {
      "address": "007b86e3",
      "instruction": "ADD ECX,0x4"
    },
    {
      "address": "007b86e6",
      "instruction": "ADD EAX,-0x1"
    },
    {
      "address": "007b86e9",
      "instruction": "MOV dword ptr [ECX + 0x4],EAX"
    },
    {
      "address": "007b86ec",
      "instruction": "JNZ 0x007b86ff"
    },
    {
      "address": "007b86ee",
      "instruction": "MOV dword ptr [ECX + 0x4],0x1"
    },
    {
      "address": "007b86f5",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "007b86f7",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "007b86f9",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "007b86fb",
      "instruction": "CALL EDX"
    },
    {
      "address": "007b86fd",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "007b86ff",
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
  "original_bytes": 21137,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall (receiver in ECX), no stack arguments\",\n    \"hidden_receiver\": \"ECX\",\n    \"hidden_this_register\": \"ECX is the receiver; 0x007b86e3 ADD ECX,4 biases it to the embedded sub-object and it stays biased for the indirect call at 0x007b86fb\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x007b86e6 ADD EAX,-1 leaves the new count in EAX and 0x007b86ec JNZ branches to 0x007b86ff (RET) with EAX untouched, so the non-zero path returns the decremented count. The zero path ends at 0x007b86fd XOR EAX,EAX, so it returns exactly 0. Both paths write the full 32-bit register.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the decremented reference count, or 0 when the zero arm ran and the object was destroyed\",\n    \"return_type\": \"std::int32_t\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"single RET at 0x007b86ff; the JNZ at 0x007b86ec targets it directly\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014542e8,vtable:0x014626b8\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 4,\n      \"symbol\": \"wave6_reference_00432a50\",\n      \"va\": \"0x00432a50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147c9e8,vtable:0x0147cc14\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00650190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00658c70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0065e110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076dee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00782660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bb670\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bced0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007c1c10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00801230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b60d80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e642a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ed8a30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f33bf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fffdd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01070290\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00650349\",\n        \"direction\": \"in\",\n        \"other\": \"0x00650190\",\n        \"reference_type\": \"computed-call\"\n      },\n      {\n        \"callsite\": \"0x00658de3\",\n        \"direction\": \"in\",\n        \"other\": \"0x00658c70\",\n        \"reference_type\": \"computed-call\"\n      },\n      {\n        \"callsite\": \"0x0065e1ee\",\n        \"direction\": \"in\",\n        \"other\": \"0x0065e110\",\n        \"reference_type\": \"compute
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
  "body_end": "007b86ff",
  "body_span_bytes": 32,
  "body_start": "007b86e0",
  "callees": [],
  "callers": [
    "FUN_00e642a0",
    "FUN_00ed8a30",
    "FUN_00fffdd0",
    "FUN_007c1c10",
    "FUN_00650190",
    "thunk_FUN_007b86e0",
    "FUN_0065e110",
    "FUN_007bced0",
    "FUN_0076dee0",
    "FUN_00aeb3e0",
    "FUN_00782660",
    "FUN_01070290",
    "FUN_00658c70",
    "FUN_007bb670",
    "FUN_00f33bf0",
    "FUN_00b60d80"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "007b86e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_007b86e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3b86e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_007b86e0(void)",
  "size_bytes": 32,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007b86e0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01418838",
      "0x0147c9e8",
      "0x0149b4d8",
      "0x0149b8b4",
      "0x014625d0",
      "0x0149b498",
      "0x0149b900",
      "0x013f8100",
      "0x01462610",
      "0x01485550",
      "0x0149b810",
      "0x0149ba30",
      "0x013f57f8",
      "0x013f7cc0",
      "0x013f8be0",
      "0x0140f7b0",
      "0x0140fdac",
      "0x0141a750",
      "0x01455a2c",
      "0x014575e8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "007bbdba"
    },
    {
      "from": "00ed8da4"
    },
    {
      "from": "00658de3"
    },
    {
      "from": "00ffffe3"
    },
    {
      "from": "0065e55a"
    },
    {
      "from": "007bd496"
    },
    {
      "from": "00f33d46"
    },
    {
      "from": "00650349"
    },
    {
      "from": "010707b1"
    },
    {
      "from": "00aeb5a2"
    },
    {
      "from": "0076e025"
    },
    {
      "from": "007c2075"
    },
    {
      "from": "007c23a1"
    },
    {
      "from": "00b6233e"
    },
    {
      "from": "013f6270"
    },
    {
      "from": "013f6378"
    },
    {
      "from": "013f68ec"
    },
    {
      "from": "013f691c"
    },
    {
      "from": "013f6af4"
    },
    {
      "from": "013f6d00"
    },
    {
      "from": "013f6d70"
    },
    {
      "from": "0149baec"
    },
    {
      "from": "0149bb34"
    },
    {
      "from": "013f6df8"
    },
    {
      "from": "013f6f28"
    },
    {
      "from": "013f7b58"
    },
    {
      "from": "013f7ca4"
    },
    {
      "from": "013f7d28"
    },
    {
      "from": "013f7dc4"
    },
    {
      "from": "013f8140"
    },
    {
      "from": "013f8310"
    },
    {
      "from": "013f845c"
    },
    {
      "from": "013f8640"
    },
    {
      "from": "013f8c00"
    },
    {
      "from": "013f926c"
    },
    {
      "from": "013f9288"
    },
    {
      "from": "013f938c"
    },
    {
      "from": "013f93f8"
    },
    {
      "from": "013f94ac"
    },
    {
      "from": "013f9568"
    },
    {
      "from": "013f963c"
    },
    {
      "from": "013f96e0"
    },
    {
      "from": "013f9858"
    },
    {
      "from": "013f98e0"
    },
    {
      "from": "013f9a14"
    },
    {
      "from": "013f9c24"
    },
    {
      "from": "013f9e24"
    },
    {
      "from": "013f9ebc"
    },
    {
      "from": "0148959c"
    },
    {
      "from": "013fa238"
    },
    {
      "from": "013fa2bc"
    },
    {
      "from": "013fa568"
    },
    {
      "from": "013fa610"
    },
    {
      "from": "013fdcdc"
    },
    {
      "from": "013fe72c"
    },
    {
      "from": "0146274c"
    },
    {
      "from": "013ffa00"
    },
    {
      "from": "013ff808"
    },
    {
      "from": "013ffcdc"
    },
    {
      "from": "013fff5c"
    },
    {
      "from": "01400948"
    },
    {
      "from": "0140117c"
    },
    {
      "from": "01401340"
    },
    {
      "from": "01401ad8"
    },
    {
      "from": "01401b7c"
    },
    {
      "from": "014032ec"
    },
    {
      "from": "01403314"
    },
    {
      "from": "01403358"
    },
    {
      "from": "0140b77c"
    },
    {
      "from": "0140c764"
    },
    {
      "from": "0140c90c"
    },
    {
      "from": "0140cca8"
    },
    {
      "from": "0140d5dc"
    },
    {
      "from": "0140d624"
    },
    {
      "from": "0140d5f4"
    },
    {
      "from": "0140d60c"
    },
    {
      "from": "0140d724"
    },
    {
      "from": "0140dcec"
    },
    {
      "from": "0140ddf8"
    },
    {
      "from": "0140e258"
    },
    {
      "from": "0140e27c"
    },
    {
      "from": "0140e364"
    },
    {
      "from": "0140e958"
    },
    {
      "from": "0140e944"
    },
    {
      "from": "0140f7c4"
    },
    {
      "from": "0140fad4"
    },
    {
      "from": "0140fc30"
    },
    {
      "from": "0140fdd8"
    },
    {
      "from": "0140fdfc"
    },
    {
      "from": "0140fe20"
    },
    {
      "from": "0140fe44"
    },
    {
      "from": "0140fe68"
    },
    {
      "from": "0140fe8c"
    },
    {
      "from": "0140feb0"
    },
    {
      "from": "0140ffa0"
    },
    {
      "from": "01410004"
    },
    {
      "from": "01410028"
    },
    {
      "from": "0140ffe4"
    },
    {
      "from": "01410198"
    },
    {
      "from": "014106b4"
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
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b04/007b86e0_object_release.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/007b86e0_object_release.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/007b86e0.json"
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
    "No original-process trace has been captured for 0x007b86e0. A differential run must confirm that the decrement, the restore-to-1 and the destructor call happen in that order on a real receiver, and that no runtime patch retargets the address.",
    "The 417 vtable slots need at least one resolved concrete receiver before any owning class can be named.",
    "The zero arm has never been observed executing. Whether the delete-on-zero path is reachable in the shipping build, and what the caller does with the 0 return, needs a trace."
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "std::int32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f56a8",
  "vtable:0x013f57f8",
  "vtable:0x013f625c",
  "vtable:0x013f6364",
  "vtable:0x013f68c4",
  "vtable:0x013f6ae0",
  "vtable:0x013f6cec",
  "vtable:0x013f6d6c",
  "vtable:0x013f6de4",
  "vtable:0x013f6f14",
  "vtable:0x013f6fc0",
  "vtable:0x013f7b54",
  "vtable:0x013f7c90",
  "vtable:0x013f7cc0",
  "vtable:0x013f7de0",
  "vtable:0x013f8100"
]
```

## Conflicts

```json
[]
```
