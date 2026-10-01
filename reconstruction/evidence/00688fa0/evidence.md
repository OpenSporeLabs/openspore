# Evidence 0x00688fa0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b5b2b0a7a5cf277b13ef05c2333f66d04a717704400e55b5973a9f149411112b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__cdecl",
  "hidden_receiver": "none",
  "hidden_this_register": "ECX is only ever an explicit thiscall argument, loaded at 0x006890d9, 0x0068912b, 0x00689141, 0x00689150 and 0x0068915c",
  "ordinary_stack_argument_slots": 1,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "0x006891d8: MOV EAX,EBX immediately before the register restores, so the return value is whatever EBX held; 0x00689132 MOV EBX,EAX takes the constructor's result and 0x00689136 XOR EBX,EBX covers the failed-allocation path",
  "return_register": "EAX",
  "return_semantics": "the 0x24-byte object, or null when the second registry allocation failed",
  "return_type": "void*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "frame_offset": "[ESP + 0x5c] at 0x00688fb8 with ESP = entry - 0x58",
      "index": 1,
      "meaning": "a const wchar_t* naming a file; the caller at 0x00de4850 passes the literal 0x0147e040, which ghidra_read_memory shows is the UTF-16LE string \"GGEUserData.dat.tmp\"",
      "width": 4
    }
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single exit at 0x006891e5; no early return exists in the 203-instruction body"
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBP",
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +44, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "e7cfce0c734820a464d265f231257679dc0889a8bc84e1512a284b6c8dd5cf3c",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
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
    "persisted_calling_convention": "__cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0095"
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
        "obs-0014",
        "obs-0015",
        "obs-0023",
        "obs-0026",
        "obs-0035",
        "obs-0048",
        "obs-0051",
        "obs-0055",
        "obs-0081",
        "obs-0086",
        "obs-0089",
        "obs-0094"
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
        "obs-0001",
        "obs-0004",
        "obs-0094"
      ],
      "claim": "an FS:/GS: operand is an SEH or cookie frame, which is not variadic evidence",
      "confidence": "OBSERVED",
      "id": "V2",
      "value": {
        "seh_or_cookie_frame": true
      }
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0015",
        "obs-0023",
        "obs-0026",
        "obs-0035",
        "obs-0048",
        "obs-0051",
        "obs-0055",
        "obs-0081",
        "obs-0086",
        "obs-0089",
        "obs-0094"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0095"
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
        "obs-0095"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0095"
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
      "id": "obs-0001"
    },
    {
      "id": "obs-0002"
    },
    {
      "id": "obs-0003"
    },
    {
      "id": "obs-0004"
    },
    {
      "id": "obs-0005"
    },
    {
      "id": "obs-0006"
    },
    {
      "id": "obs-0007"
    },
    {
      "id": "obs-0008"
    },
    {
      "id": "obs-0009"
    },
    {
      "id": "obs-0010"
    },
    {
      "id": "obs-0011"
    },
    {
      "id": "obs-0012"
    },
    {
      "id": "obs-0013"
    },
    {
      "id": "obs-0014"
    },
    {
      "id": "obs-0015"
    },
    {
      "id": "obs-0016"
    },
    {
      "id": "obs-0017"
    },
    {
      "id": "obs-0018"
    },
    {
      "id": "obs-0019"
    },
    {
      "id": "obs-0020"
    },
    {
      "id": "obs-0021"
    },
    {
      "id": "obs-0022"
    },
    {
      "id": "obs-0023"
    },
    {
      "id": "obs-0024"
    },
    {
      "id": "obs-0025"
    },
    {
      "id": "obs-0026"
    },
    {
      "id": "obs-0027"
    },
    {
      "id": "obs-0028"
    },
    {
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id": "obs-0031"
    },
    {
      "id": "obs-0032"
    },
    {
      "id": "obs-0033"
    },
    {
      "id": "obs-00
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
    "name": "FUN_00580cb0",
    "reconstructed": false,
    "va": "0x00580cb0"
  },
  {
    "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "reconstructed": true,
    "va": "0x00b28ec0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb4ba0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00de4850"
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
  "count": 203,
  "instructions": [
    {
      "address": "00688fa0",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "00688fa2",
      "instruction": "PUSH 0x120c84c"
    },
    {
      "address": "00688fa7",
      "instruction": "MOV EAX,FS:[0x0]"
    },
    {
      "address": "00688fad",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00688fae",
      "instruction": "MOV dword ptr FS:[0x0],ESP"
    },
    {
      "address": "00688fb5",
      "instruction": "SUB ESP,0x4c"
    },
    {
      "address": "00688fb8",
      "instruction": "MOV EAX,dword ptr [ESP + 0x5c]"
    },
    {
      "address": "00688fbc",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00688fbd",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00688fbe",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00688fbf",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00688fc0",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00688fc2",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00688fc3",
      "instruction": "LEA ECX,[ESP + 0x40]"
    },
    {
      "address": "00688fc7",
      "instruction": "MOV dword ptr [ESP + 0x40],EDI"
    },
    {
      "address": "00688fcb",
      "instruction": "MOV dword ptr [ESP + 0x44],EDI"
    },
    {
      "address": "00688fcf",
      "instruction": "MOV dword ptr [ESP + 0x48],EDI"
    },
    {
      "address": "00688fd3",
      "instruction": "CALL 0x00579a90"
    },
    {
      "address": "00688fd8",
      "instruction": "PUSH 0x4729a47"
    },
    {
      "address": "00688fdd",
      "instruction": "MOV dword ptr [ESP + 0x68],EDI"
    },
    {
      "address": "00688fe1",
      "instruction": "CALL 0x006b1f90"
    },
    {
      "address": "00688fe6",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00688fe8",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00688fea",
      "instruction": "MOV EAX,dword ptr [EDX + 0x28]"
    },
    {
      "address": "00688fed",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00688ff0",
      "instruction": "CALL EAX"
    },
    {
      "address": "00688ff2",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00688ff3",
      "instruction": "LEA ECX,[ESP + 0x30]"
    },
    {
      "address": "00688ff7",
      "instruction": "MOV dword ptr [ESP + 0x30],EDI"
    },
    {
      "address": "00688ffb",
      "instruction": "MOV dword ptr [ESP + 0x34],EDI"
    },
    {
      "address": "00688fff",
      "instruction": "MOV dword ptr [ESP + 0x38],EDI"
    },
    {
      "address": "00689003",
      "instruction": "CALL 0x00579a90"
    },
    {
      "address": "00689008",
      "instruction": "MOV ESI,dword ptr [ESP + 0x30]"
    },
    {
      "address": "0068900c",
      "instruction": "MOV EBX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00689010",
      "instruction": "SUB ESI,EBX"
    },
    {
      "address": "00689012",
      "instruction": "SAR ESI,0x1"
    },
    {
      "address": "00689014",
      "instruction": "LEA ECX,[ESI + 0x1]"
    },
    {
      "address": "00689017",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00689018",
      "instruction": "LEA ECX,[ESP + 0x20]"
    },
    {
      "address": "0068901c",
      "instruction": "MOV byte ptr [ESP + 0x68],0x1"
    },
    {
      "address": "00689021",
      "instruction": "MOV dword ptr [ESP + 0x20],EDI"
    },
    {
      "address": "00689025",
      "instruction": "MOV dword ptr [ESP + 0x24],EDI"
    },
    {
      "address": "00689029",
      "instruction": "MOV dword ptr [ESP + 0x28],EDI"
    },
    {
      "address": "0068902d",
      "instruction": "CALL 0x00429760"
    },
    {
      "address": "00689032",
      "instruction": "MOV EBP,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00689036",
      "instruction": "ADD ESI,ESI"
    },
    {
      "address": "00689038",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00689039",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0068903a",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0068903b",
      "instruction": "CALL 0x011e0744"
    },
    {
      "address": "00689040",
      "instruction": "ADD ESI,EBP"
    },
    {
      "address": "00689042",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00689044",
      "instruction": "MOV dword ptr [ESP + 0x2c],ESI"
    },
    {
      "address": "00689048",
      "instruction": "MOV word ptr [ESI],DX"
    },
    {
      "address": "0068904b",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0068904c",
      "instruction": "MOV byte ptr [ESP + 0x74],0x2"
    },
    {
      "address": "00689051",
      "instruction": "CALL 0x00932ae0"
    },
    {
      "address": "00689056",
      "instruction": "LEA EAX,[ESP + 0x4c]"
    },
    {
      "address": "0068905a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0068905b",
      "instruction": "LEA ECX,[ESP + 0x30]"
    },
    {
      "address": "0068905f",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00689060",
      "instruction": "LEA EDX,[ESP + 0x64]"
    },
    {
      "address": "00689064",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00689065",
      "instruction": "CALL 0x00688f00"
    },
    {
      "address": "0068906a",
      "instruction": "ADD ESP,0x1c"
    },
    {
      "address": "0068906d",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "00689071",
      "instruction": "MOV byte ptr [ESP + 0x64],0x3"
    },
    {
      "address": "00689076",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "00689078",
      "instruction": "JZ 0x0068908a"
    },
    {
      "address": "0068907a",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0068907d",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {

[TRUNCATED]
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
  "original_bytes": 11006,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"hidden_receiver\": \"none\",\n    \"hidden_this_register\": \"ECX is only ever an explicit thiscall argument, loaded at 0x006890d9, 0x0068912b, 0x00689141, 0x00689150 and 0x0068915c\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x006891d8: MOV EAX,EBX immediately before the register restores, so the return value is whatever EBX held; 0x00689132 MOV EBX,EAX takes the constructor's result and 0x00689136 XOR EBX,EBX covers the failed-allocation path\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the 0x24-byte object, or null when the second registry allocation failed\",\n    \"return_type\": \"void*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"frame_offset\": \"[ESP + 0x5c] at 0x00688fb8 with ESP = entry - 0x58\",\n        \"index\": 1,\n        \"meaning\": \"a const wchar_t* naming a file; the caller at 0x00de4850 passes the literal 0x0147e040, which ghidra_read_memory shows is the UTF-16LE string \\\"GGEUserData.dat.tmp\\\"\",\n        \"width\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"single exit at 0x006891e5; no early return exists in the 203-instruction body\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n      \"va\": \"0x005c7ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"service_0060ee90\",\n      \"va\": \"0x0060ee90\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00835380\",\n      \"va\": \"0x00835380\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 3,\n      \"symbol\": \"wave6_fixed_pool_allocator_alloc_00926100\",\n      \"va\": \"0x00926100\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"FUN_00580cb0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00580cb0\"\n      },\n      {\n        \"name\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b28ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb4ba0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00de4850\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00580d08\",\n        \"direction\": \"in\",\n        \"other\": \"0x00580cb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b2930b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b28ec0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb4cef\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb4ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00de485f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00de4850\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00689081\",\n        \"direction\": \"out\",\n        \"other\": \"0x00423650\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0068902d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00429760\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00688fd3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00579a90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00689003\",\n        \"direction\": \"out\",\n        \"other\": \"0x00579a90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00689065\",\n        \"direction\": \"out\",\n        \"other\": \"0x00688f00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0068912d\",\n        \"direction\": \"out\",\n        \"oth
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
  "body_end": "006891e5",
  "body_span_bytes": 582,
  "body_start": "00688fa0",
  "callees": [
    "FUN_00926020",
    "FUN_006b1f90",
    "memcpy",
    "FUN_00f47380",
    "FUN_00931fd0",
    "FUN_0069fa60",
    "FUN_00579a90",
    "FUN_00932ae0",
    "FUN_00688f00",
    "FUN_00423650",
    "FUN_00429760",
    "FUN_008d9f80"
  ],
  "callers": [
    "FUN_00de4850",
    "FUN_00b28ec0",
    "FUN_00580cb0",
    "FUN_00bb4ba0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00688fa0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00688fa0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x288fa0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00688fa0(void)",
  "size_bytes": 582,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00688fa0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00b2930b"
    },
    {
      "from": "00bb4cef"
    },
    {
      "from": "00580d08"
    },
    {
      "from": "00de485f"
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
    "reconstruction/staging/wave13-w1-dispatch-b02/b688fa0_gge_user_data_reset.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/b688fa0_gge_user_data_reset.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b02/00688fa0.json"
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
    "A runtime trace is required to confirm the delete actually targets a removable file, since the predicate that would guard it is discarded.",
    "A runtime trace is required to observe what the service locator returns for the key 0x04729a47 and therefore what base directory is actually used.",
    "A runtime trace is required to resolve the four unknown virtual callees and the identity of the Simulator class at runtime.",
    "No original-process trace has ever been captured for 0x00688fa0; every claim here is static. The original Cell stage has never been entered in any recorded run."
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "void*"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01408698",
  "vtable:0x014086e8"
]
```

## Conflicts

```json
[]
```
