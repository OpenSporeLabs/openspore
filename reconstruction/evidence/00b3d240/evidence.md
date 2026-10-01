# Evidence 0x00b3d240

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `63f8656d4e4fbbbc81bea9232144e249cf173d6622f66caa6ec805eadecbddcb`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": false,
  "ordinary_stack_argument_slots": [],
  "ordinary_stack_arguments": [],
  "receiver": false,
  "receiver_register": null,
  "ret_form": "RET",
  "return_register": [
    "EAX",
    "AL"
  ],
  "return_semantics": "The 4-byte word stored at the absolute address 0x0167eac4, returned whole in EAX. All 32 bits are meaningful: the load at 0x00b3d240 writes the full register, so no narrower or sign-extended return is consistent with the bytes.",
  "return_type": "uint32",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "none",
  "termination": "RET at 0x00b3d245, five bytes after the entry at 0x00b3d240; it is the second and last instruction of the body."
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
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "6f944fdbda4daa0a32ac379921ce5b4971b86029750f864c8a5fce48d5a6dc13",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0002"
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
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0002"
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
      "at": "0x00b3d240",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eac4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d245",
      "form": "RET",
      "id": "obs-0002",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
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
    "present": false,
    "register": null,
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "pointer_like",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00b3d240"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_UNKNOWN"
}
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
    "va": "0x00ae00d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b08670"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b0a6f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b19290"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b19440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b195f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b197b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b19810"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b303e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b30550"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b307e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b31030"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32b20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32ce0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b32e80"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nundefined4 FUN_00b3d240(void)\n\n{\n  return DAT_0167eac4;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 2,
  "instructions": [
    {
      "address": "00b3d240",
      "instruction": "MOV EAX,[0x0167eac4]"
    },
    {
      "address": "00b3d245",
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
  "original_bytes": 18338,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": null,\n    \"hidden_this\": false,\n    \"ordinary_stack_argument_slots\": [],\n    \"ordinary_stack_arguments\": [],\n    \"receiver\": false,\n    \"receiver_register\": null,\n    \"ret_form\": \"RET\",\n    \"return_register\": [\n      \"EAX\",\n      \"AL\"\n    ],\n    \"return_semantics\": \"The 4-byte word stored at the absolute address 0x0167eac4, returned whole in EAX. All 32 bits are meaningful: the load at 0x00b3d240 writes the full register, so no narrower or sign-extended return is consistent with the bytes.\",\n    \"return_type\": \"uint32\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"none\",\n    \"termination\": \"RET at 0x00b3d245, five bytes after the entry at 0x00b3d240; it is the second and last instruction of the body.\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae00d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b08670\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b0a6f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b19290\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b19440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b195f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b197b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b19810\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b303e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b30550\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b307e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b31030\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32ce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32e80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32f60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b330e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b334e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b335d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33970\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b36030\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b37210\"\n      },\n      {\n        \"name\": null,\
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
  "body_end": "00b3d245",
  "body_span_bytes": 6,
  "body_start": "00b3d240",
  "callees": [],
  "callers": [
    "FUN_00c36ae0",
    "FUN_00d28300",
    "PTRREF_00B18EF0",
    "FUN_00b32dd0",
    "FUN_00db4370",
    "FUN_00cd9da0",
    "FUN_00db4a60",
    "FUN_00d311b0",
    "FUN_01003690",
    "FUN_00dc8f30",
    "FUN_00cb9bd0",
    "FUN_00d0c170",
    "FUN_00dc6530",
    "FUN_00fdb330",
    "FUN_00b307e0",
    "FUN_00bda0a0",
    "FUN_00b334e0",
    "FUN_00d8e8d0",
    "FUN_00c20230",
    "FUN_00b32ce0",
    "FUN_00b32f60",
    "FUN_00d11730",
    "FUN_0107c4b0",
    "FUN_00d33ec0",
    "FUN_00b36030",
    "FUN_00b19810",
    "FUN_00cfe160",
    "FUN_00f10bd0",
    "FUN_00b197b0",
    "FUN_00b335d0",
    "FUN_00cf2520",
    "FUN_00f10670",
    "FUN_00fddba0",
    "FUN_00e98500",
    "FUN_00f22070",
    "FUN_00b19440",
    "FUN_00e97bf0",
    "FUN_00bdbc20",
    "FUN_00b33350",
    "FUN_00c17de0",
    "FUN_00eda130",
    "FUN_00f09fc0",
    "FUN_00bd9060",
    "FUN_00cd68d0",
    "FUN_00f19e70",
    "FUN_00ba3860",
    "FUN_00d299f0",
    "FUN_00c1a3c0",
    "FUN_00d0ae50",
    "FUN_00d124e0",
    "FUN_00d1cdf0",
    "FUN_00eff790",
    "FUN_00d29610",
    "FUN_00ce3b60",
    "FUN_00cb9810",
    "FUN_00db4f60",
    "Simulator::cDefaultAoETool::OnMouseDown",
    "FUN_00f23220",
    "FUN_00b7cc60",
    "FUN_00d342d0",
    "FUN_00f24752",
    "FUN_00cb6570",
    "FUN_00d10f90",
    "FUN_00bdca30",
    "FUN_00caa610",
    "FUN_00e07540",
    "FUN_00f039a0",
    "FUN_00b330e0",
    "FUN_00b7a880",
    "FUN_00e35370",
    "FUN_00b33540",
    "FUN_00cc22c0",
    "FUN_00ef10c0",
    "FUN_00bcece0",
    "FUN_00ef0ee0",
    "FUN_00ae00d0",
    "FUN_00bd9dd0",
    "FUN_010053c0",
    "FUN_00ce3560",
    "FUN_00d22300",
    "FUN_00d4cb70",
    "FUN_00b33970",
    "FUN_00bd9140",
    "FUN_00d1c400",
    "FUN_00b5d430",
    "FUN_00cf2b70",
    "FUN_00c14cb0",
    "FUN_00be6f90",
    "FUN_00f00850",
    "FUN_00b32e80",
    "FUN_00d09770",
    "FUN_00dc57a0",
    "FUN_00f0ac40",
    "FUN_00c21bf0",
    "FUN_00b08670",
    "FUN_00d0a040",
    "FUN_00cba560",
    "FUN_00f03440",
    "FUN_00d9aa20",
    "FUN_00cb6500",
    "FUN_00db4140",
    "FUN_00d10840",
    "FUN_00fddfa0",
    "FUN_00bcbc80",
    "FUN_00be3ad0",
    "FUN_00d178a0",
    "FUN_01052f00",
    "FUN_00cbbdc0",
    "FUN_00d099c0",
    "FUN_00b31030",
    "FUN_00cea1a0",
    "FUN_00dca100",
    "FUN_00f1ae10",
    "FUN_00b0a6f0",
    "FUN_00cbf120",
    "FUN_01030fd0",
    "FUN_01053980",
    "FUN_00d31a70",
    "FUN_00b37210",
    "FUN_00e97350",
    "FUN_00cba690",
    "FUN_00ccefb0",
    "j_cSpaceGfx_Initialize_",
    "FUN_00b19290",
    "FUN_00d2dd20",
    "FUN_00d07ab0",
    "FUN_00b303e0",
    "FUN_00d9a4a0",
    "FUN_00d130d0",
    "FUN_00cd02d0",
    "FUN_00d29780",
    "FUN_00cd4d50",
    "FUN_00ccff40",
    "FUN_00f19940",
    "FUN_00cdbd20",
    "FUN_00cf2d60",
    "FUN_00b195f0",
    "FUN_00d1afe0",
    "FUN_00d2d7d0",
    "FUN_00c42350",
    "FUN_00cba050",
    "FUN_00efd970",
    "FUN_00c2f690",
    "FUN_00d35190",
    "FUN_00bdc8a0",
    "FUN_00bdb0b0",
    "FUN_00cf18b0",
    "FUN_00b30550",
    "FUN_00cf1630",
    "FUN_00cf28f0",
    "FUN_00deb5d0",
    "FUN_00c86aa0",
    "FUN_00c7d240",
    "FUN_00eb6760",
    "FUN_01058020",
    "FUN_010743a0",
    "FUN_00b32b20",
    "FUN_00d98140",
    "FUN_00c8a550"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d240",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b3d240",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d240",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3d240(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d240",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00c21d55"
    },
    {
      "from": "00f1aef6"
    },
    {
      "from": "00f19967"
    },
    {
      "from": "00f199c9"
    },
    {
      "from": "00ae03ed"
    },
    {
      "from": "00bdc944"
    },
    {
      "from": "00be3c40"
    },
    {
      "from": "00be3d04"
    },
    {
      "from": "00bd90ea"
    },
    {
      "from": "00bdb1ca"
    },
    {
      "from": "00bd9ddc"
    },
    {
      "from": "00bda0ac"
    },
    {
      "from": "00bdcc88"
    },
    {
      "from": "00caa71e"
    },
    {
      "from": "00caa82f"
    },
    {
      "from": "00b1929d"
    },
    {
      "from": "00b193cf"
    },
    {
      "from": "00b1944e"
    },
    {
      "from": "00b1945e"
    },
    {
      "from": "00b195f9"
    },
    {
      "from": "00b1962e"
    },
    {
      "from": "00b197b8"
    },
    {
      "from": "00b197c8"
    },
    {
      "from": "00b1981f"
    },
    {
      "from": "00b19832"
    },
    {
      "from": "00b19842"
    },
    {
      "from": "00b304c9"
    },
    {
      "from": "00b30556"
    },
    {
      "from": "00b30880"
    },
    {
      "from": "00b31215"
    },
    {
      "from": "00b3385f"
    },
    {
      "from": "00b32b88"
    },
    {
      "from": "00b32d28"
    },
    {
      "from": "00b32eb4"
    },
    {
      "from": "00b3356b"
    },
    {
      "from": "00c86ac2"
    },
    {
      "from": "00b33b1e"
    },
    {
      "from": 
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
  "files": [
    "reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240.cpp",
    "reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240.hpp",
    "reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00b3d240/00b3d240.json"
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
    "Any differential run against the original must arrange for 0x0167eac4 to hold a known word first: the image carries no initializer for it, and a run that reads it as zero observes the loader's zero-fill rather than the game's state.",
    "No original-process trace exists for this target (evidence.json categories.runtime is MISSING), so nothing here is runtime-validated."
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
  "std::uint32_t",
  "uint32"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
