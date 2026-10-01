# Evidence 0x009817c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `dc9919649603e2784a0d4ac7f9803b427e11a44140ca286d605ee2919bbb6358`

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
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x4"
  ],
  "ordinary_stack_arguments": [
    "{'entry_offset': 'entry_ESP+0x4', 'local_spelling': 'key', 'name': 'hash', 'observed': True, 'ordinal': 1, 'role': \"32-bit comparison key, tested against four CMP immediates across this body and its tail-call target, and never masked, widened or used as an index. The name and the type are the record's; this package adds nothing to them. Nothing establishes that the value is a hash of anything, and the model does not claim that.\", 'sizes': [4], 'type': 'uint32_t'}",
    "{'entry_offset': 'entry_ESP+0x4', 'name': 'hash', 'observed': True, 'ordinal': 1, 'role': '32-bit comparison key, tested against four CMP immediates and never masked, widened or used as an index', 'size_inferred': False, 'sizes': [4], 'type': 'uint32_t'}"
  ],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_observation": "EAX is written on every path. The three null exits materialise it with XOR EAX,EAX, the two local offset exits with LEA EAX,[ECX+0x4] and LEA EAX,[ECX+0xc], and the delegated paths by the tail-called 0x00951240, whose own exits are ADD EAX,0x4 and XOR EAX,EAX. So the returned value is always a deliberate pointer result, not a residual register.",
  "return_register": "EAX",
  "return_semantics": "Returns the address of the member selected by the hash argument relative to the receiver: receiver + 0x04 for hash 0xeec58382, receiver + 0x0c for hash 0xeef3af8c, receiver + 0x04 for hash 0xee3f516e, the bare receiver for hash 0x6ec581fd, and null for any other hash. Both locally handled offsets and the delegated 0x04 offset are null-guarded; the bare-receiver 0x6ec581fd case is NOT null-guarded and returns the receiver verbatim even when it is null.",
  "return_type": "void*",
  "return_width_bytes": 4,
  "saved_registers": [
    "none; the body pushes no register at all",
    "none; no register is pushed"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
    "return_semantics": "integral_in_EAX",
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
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "e6fc5016d092a195a10af1333b810ab562b66b435d6a0494a4e71868868bc7ff",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
        "obs-0008",
        "obs-0009",
        "obs-0010"
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
        "obs-0002",
        "obs-0005"
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
        "obs-0007"
      ],
      "claim": "ECX carries the receiver: 0x009817c0 is slot 9 of the vptr-backed vftable at 0x01441a2c, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body takes the address of its incoming ECX (LEA at 0x009817df, 0x009817e9) and never touches memory through it, after a null test of it, and a body that computes an address from a register the vtable dispatch delivered computes it from the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form has no register parameter and never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R2-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_null_test": true,
        "incoming_ecx_reads": 1,
        "incoming_member_leas": 2,
        "member_lea_displacements": [
          12,
          4
        ],
        "member_lea_sites": [
          "0x009817df",
          "0x009817e9"
        ],
        "membership_count": 2,
        "receiver_provenance": "vftable_slot_address",
        "receiver_register": "ECX",
        "slot_index": 9,
        "table": "0x01441a2c"
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010"
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
        "obs-0006",
        "obs-0008",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed",
      "confidence": "UNKNOWN",
      "id": "T2",
      "value": {
        "form": "epilogue_then_jmp"
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010"
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
      "at": "0x009817c0",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x009817c0",
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
      "at": "0x009817c0",
      "definite": true,
   
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

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\n/* WARNING: Unknown calling convention */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n\nvoid UTFWin__ScrollbarDrawable__SetImage(IScrollbarDrawable *this,int index,Image *pImage)\n\n{\n  int in_ECX;\n  \n  if (this == (IScrollbarDrawable *)0xeec58382) {\n    if (in_ECX != 0) {\n      return;\n    }\n  }\n  else {\n    if (this != (IScrollbarDrawable *)0xeef3af8c) {\n      FUN_00951240();\n      return;\n    }\n    if (in_ECX != 0) {\n      return;\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 17,
  "instructions": [
    {
      "address": "009817c0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "009817c4",
      "instruction": "CMP EAX,0xeec58382"
    },
    {
      "address": "009817c9",
      "instruction": "JZ 0x009817e5"
    },
    {
      "address": "009817cb",
      "instruction": "CMP EAX,0xeef3af8c"
    },
    {
      "address": "009817d0",
      "instruction": "JZ 0x009817db"
    },
    {
      "address": "009817d2",
      "instruction": "MOV dword ptr [ESP + 0x4],EAX"
    },
    {
      "address": "009817d6",
      "instruction": "JMP 0x00951240"
    },
    {
      "address": "009817db",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "009817dd",
      "instruction": "JZ 0x009817ef"
    },
    {
      "address": "009817df",
      "instruction": "LEA EAX,[ECX + 0xc]"
    },
    {
      "address": "009817e2",
      "instruction": "RET 0x4"
    },
    {
      "address": "009817e5",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "009817e7",
      "instruction": "JZ 0x009817ef"
    },
    {
      "address": "009817e9",
      "instruction": "LEA EAX,[ECX + 0x4]"
    },
    {
      "address": "009817ec",
      "instruction": "RET 0x4"
    },
    {
      "address": "009817ef",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "009817f1",
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
  "original_bytes": 12289,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      \"{'entry_offset': 'entry_ESP+0x4', 'local_spelling': 'key', 'name': 'hash', 'observed': True, 'ordinal': 1, 'role': \\\"32-bit comparison key, tested against four CMP immediates across this body and its tail-call target, and never masked, widened or used as an index. The name and the type are the record's; this package adds nothing to them. Nothing establishes that the value is a hash of anything, and the model does not claim that.\\\", 'sizes': [4], 'type': 'uint32_t'}\",\n      \"{'entry_offset': 'entry_ESP+0x4', 'name': 'hash', 'observed': True, 'ordinal': 1, 'role': '32-bit comparison key, tested against four CMP immediates and never masked, widened or used as an index', 'size_inferred': False, 'sizes': [4], 'type': 'uint32_t'}\"\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_observation\": \"EAX is written on every path. The three null exits materialise it with XOR EAX,EAX, the two local offset exits with LEA EAX,[ECX+0x4] and LEA EAX,[ECX+0xc], and the delegated paths by the tail-called 0x00951240, whose own exits are ADD EAX,0x4 and XOR EAX,EAX. So the returned value is always a deliberate pointer result, not a residual register.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"Returns the address of the member selected by the hash argument relative to the receiver: receiver + 0x04 for hash 0xeec58382, receiver + 0x0c for hash 0xeef3af8c, receiver + 0x04 for hash 0xee3f516e, the bare receiver for hash 0x6ec581fd, and null for any other hash. Both locally handled offsets and the delegated 0x04 offset are null-guarded; the bare-receiver 0x6ec581fd case is NOT null-guarded and returns the receiver verbatim even when it is null.\",\n    \"return_type\": \"void*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"none; the body pushes no register at all\",\n      \"none; no register is pushed\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-00980510\",\n      \"score\": 8,\n      \"symbol\": \"dfw_get_proxy_id_00980510\",\n      \"va\": \"0x00980510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-utfwin-slot7-wave12\",\n      \"score\": 8,\n      \"symbol\": \"re_00fc7e10_UTFWin_ImageDrawable_GetTiling\",\n      \"va\": \"0x00fc7e10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-utfwin-settiling-wave13\",\n      \"score\": 8,\n      \"symbol\": \"set_tiling_00fd9460\",\n      \"va\": \"0x00fd9460\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-0095fa30-utfwin-isancestorof\",\n      \"score\": 6,\n      \"symbol\": \"is_ancestor_of_0095fa30\",\n      \"va\": \"0x0095fa30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-utfwin-func35-wave12\",\n      \"score\": 6,\n      \"symbol\": \"func35_0095fd60\",\n      \"va\": \"0x0095fd60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-dfw-0096ff70\",\n      \"score\": 6,\n      \"symbol\": \"dfw_func88h_0096ff70\",\n      \"va\": \"0x0096ff70\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-dfw-00980c50\",\n      \"score\": 6,\n      \"symbol\": \"dfw_00980c50_func88h\",\n      \"va\": \"0x00980c50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x009817d6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00951240\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0327\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"UTFWin::ScrollbarDrawable::SetImage\",\n  \"normalized_symbol\": \"UTFWin::ScrollbarDrawable::SetImage\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n
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
  "body_end": "009817f3",
  "body_span_bytes": 52,
  "body_start": "009817c0",
  "callees": [
    "FUN_00951240"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "009817c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "in_ECX",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "this",
      "storage": "Stack[0x4]:4",
      "type": "IScrollbarDrawable *"
    },
    {
      "name": "pImage",
      "storage": "Stack[0xc]:4",
      "type": "Image *"
    },
    {
      "name": "index",
      "storage": "Stack[0x8]:4",
      "type": "int"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "UTFWin::ScrollbarDrawable::SetImage",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IScrollbarDrawable *"
    },
    {
      "name": "index",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "pImage",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Image *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x5817c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void UTFWin::ScrollbarDrawable::SetImage(IScrollbarDrawable * this, int index, Image * pImage)",
  "size_bytes": 52,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x009817c0",
  "vtables": {
    "referenced_by_vtables": [
      "0x014447f8",
      "0x01441a2c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "01441a50"
    },
    {
      "from": "01444880"
    },
    {
      "from": "00969b43"
    },
    {
      "from": "00969b53"
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
  "global:PASS"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ScrollbarDrawable__SetImage.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ScrollbarDrawable__SetImage.c",
    "reconstruction/staging/pkg-utfwin-hash-offset-009817c0/.clang-format",
    "reconstruction/staging/pkg-utfwin-hash-offset-009817c0/utfwin_hash_offset_009817c0.cpp",
    "reconstruction/staging/pkg-utfwin-hash-offset-009817c0/utfwin_hash_offset_009817c0.hpp",
    "reconstruction/staging/pkg-utfwin-hash-offset-009817c0/utfwin_hash_offset_009817c0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-009817c0/009817c0.json",
    "reconstruction/metadata/pkg-utfwin-hash-offset-009817c0/009817c0.json"
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
    "No original-process invocation and no indirect-caller trace was captured, so no concrete caller and no real key value are known. The key-to-offset table is proven from the two bodies but the values a real caller passes, and therefore which members these offsets name, cannot be observed without a trace.",
    "The member names and declared types behind offsets +0x00, +0x04 and +0x0c are not established; only the offsets themselves are proven.",
    "The owning C++ class name and the interface identity of the target's vtable slot are not established, because SporeApp.exe carries no MSVC RTTI.",
    "The provenance of the four comparison constants is not established, so it cannot be checked whether another translation unit contributes further keys to the same table that are unreachable from this entry point."
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
  "uint32_t",
  "void*"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x009838e0",
  "vtable:0x01441a2c",
  "vtable:0x014447f8"
]
```

## Conflicts

```json
[]
```
