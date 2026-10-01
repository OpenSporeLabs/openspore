# Evidence 0x00848020

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1f437f003f5d77997de52764091e0112f1be70397e53d297fe62fc2581f1369f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit canvas receiver in ECX and caller cleanup",
  "return_semantics": "bool in AL; true on reviewed cleanup paths",
  "return_type": "bool",
  "stack_cleanup_bytes": 0,
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +60, so the listing is not one path"
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
  "content_sha256": "48606c3be358a7d3742a5ebca693c878a22dd26fdf2dd2416a81922b816aebe3",
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
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit canvas receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 8,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0032",
        "obs-0035"
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
        "obs-0006",
        "obs-0017"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          77,
          78,
          79,
          112,
          116,
          128,
          140,
          144,
          148
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0017",
        "obs-0032",
        "obs-0035"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0032",
        "obs-0035"
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
        "obs-0032",
        "obs-0035"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0032",
        "obs-0035"
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
      "and_esp": null,
      "at": "0x00848020",
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
      "raw": "SUB ESP,0xc",
      "sub": 12
    },
    {
      "at": "0x00848020",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0xc",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00848023",
      "count": 14,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00848024",
      "count": 17,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00848025",
      "count": 5,
      "first_use": 3,
      "first_write_index": 19,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00848025",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00848027",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "XOR EBX,EBX",
      "reg": "EBX",
      "write_kind": "zero"
    },
    {
      "at": "0x00848032",
      "count": 8,
      "first_use": 7,
      "first_write_index": 13,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0x8]",
      "reg": "EAX"
    },
    {
      "at": "0x00848032",
      "count": 4,
      "first_use": 7,
      "first_write_index": 0,
      "id": "obs-0009",
      "index": 7,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00848032",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0010",
      "index": 7,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA EAX,[ESP + 0x8]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00848037",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0011",
      "index": 9,
     
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
    "va": "0x00849da0"
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
  "count": 78,
  "instructions": [
    {
      "address": "00848020",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "00848023",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00848024",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00848025",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00848027",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00848029",
      "instruction": "CMP dword ptr [ESI + 0x74],EBX"
    },
    {
      "address": "0084802c",
      "instruction": "JZ 0x008480f3"
    },
    {
      "address": "00848032",
      "instruction": "LEA EAX,[ESP + 0x8]"
    },
    {
      "address": "00848036",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00848037",
      "instruction": "MOV dword ptr [ESP + 0xc],0x1ee1005"
    },
    {
      "address": "0084803f",
      "instruction": "MOV dword ptr [ESP + 0x10],ESI"
    },
    {
      "address": "00848043",
      "instruction": "MOV dword ptr [ESP + 0x14],EBX"
    },
    {
      "address": "00848047",
      "instruction": "CALL 0x00847e70"
    },
    {
      "address": "0084804c",
      "instruction": "MOV EAX,dword ptr [ESI + 0x74]"
    },
    {
      "address": "0084804f",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00848051",
      "instruction": "JZ 0x00848071"
    },
    {
      "address": "00848053",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00848054",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00848055",
      "instruction": "CALL dword ptr [0x013cc638]"
    },
    {
      "address": "0084805b",
      "instruction": "MOV ECX,dword ptr [0x01650388]"
    },
    {
      "address": "00848061",
      "instruction": "MOV dword ptr [ECX + 0x10],EBX"
    },
    {
      "address": "00848064",
      "instruction": "MOV EDX,dword ptr [ESI + 0x74]"
    },
    {
      "address": "00848067",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00848068",
      "instruction": "CALL dword ptr [0x013cc5a0]"
    },
    {
      "address": "0084806e",
      "instruction": "MOV dword ptr [ESI + 0x74],EBX"
    },
    {
      "address": "00848071",
      "instruction": "CMP word ptr [ESI + 0x70],BX"
    },
    {
      "address": "00848075",
      "instruction": "JZ 0x00848090"
    },
    {
      "address": "00848077",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00848078",
      "instruction": "CALL dword ptr [0x013cc0c0]"
    },
    {
      "address": "0084807e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0084807f",
      "instruction": "MOVZX EAX,word ptr [ESI + 0x70]"
    },
    {
      "address": "00848083",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00848084",
      "instruction": "CALL dword ptr [0x013cc63c]"
    },
    {
      "address": "0084808a",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "0084808c",
      "instruction": "MOV word ptr [ESI + 0x70],CX"
    },
    {
      "address": "00848090",
      "instruction": "MOV EAX,dword ptr [ESI + 0x80]"
    },
    {
      "address": "00848096",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00848098",
      "instruction": "JZ 0x008480a7"
    },
    {
      "address": "0084809a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0084809b",
      "instruction": "CALL dword ptr [0x013cc04c]"
    },
    {
      "address": "008480a1",
      "instruction": "MOV dword ptr [ESI + 0x80],EBX"
    },
    {
      "address": "008480a7",
      "instruction": "PUSH EDI"
    },
    {
      "address": "008480a8",
      "instruction": "MOV EDI,dword ptr [0x013cc6c8]"
    },
    {
      "address": "008480ae",
      "instruction": "CMP byte ptr [ESI + 0x4d],BL"
    },
    {
      "address": "008480b1",
      "instruction": "JZ 0x008480c3"
    },
    {
      "address": "008480b3",
      "instruction": "MOV EDX,dword ptr [ESI + 0x8c]"
    },
    {
      "address": "008480b9",
      "instruction": "PUSH EBX"
    },
    {
      "address": "008480ba",
      "instruction": "PUSH EDX"
    },
    {
      "address": "008480bb",
      "instruction": "PUSH EBX"
    },
    {
      "address": "008480bc",
      "instruction": "PUSH 0x101b"
    },
    {
      "address": "008480c1",
      "instruction": "CALL EDI"
    },
    {
      "address": "008480c3",
      "instruction": "CMP byte ptr [ESI + 0x4e],BL"
    },
    {
      "address": "008480c6",
      "instruction": "JZ 0x008480d5"
    },
    {
      "address": "008480c8",
      "instruction": "MOV EAX,dword ptr [ESI + 0x90]"
    },
    {
      "address": "008480ce",
      "instruction": "PUSH EBX"
    },
    {
      "address": "008480cf",
      "instruction": "PUSH EBX"
    },
    {
      "address": "008480d0",
      "instruction": "PUSH EAX"
    },
    {
      "address": "008480d1",
      "instruction": "PUSH 0x5d"
    },
    {
      "address": "008480d3",
      "instruction": "CALL EDI"
    },
    {
      "address": "008480d5",
      "instruction": "CMP byte ptr [ESI + 0x4f],BL"
    },
    {
      "address": "008480d8",
      "instruction": "JZ 0x008480ea"
    },
    {
      "address": "008480da",
      "instruction": "MOV ECX,dword ptr [ESI + 0x94]"
    },
    {
      "address": "008480e0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "008480e1",
      "instruction": "PUSH ECX"
    },
    {
      "address": "008480e2",
      "instruction": "PUSH EBX"
    },
    {
      "address": "008480e3",
      "instruction": "PUSH 0x101d"
    },
    {
      "address": "008480e8",
      "instruction": "CALL EDI"
    },
    {
      "address": "008480ea",
      "instruction": "POP EDI"
    },
    {
      "address": "008480eb",
      "instruction": "POP ESI"
    },
    {
      "address": "008480ec",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "008480ee",
      "instruction": "POP EBX"
    },
    {
      "address": "008480ef",
      "instruction": "ADD ESP,0xc"
    },
  
[TRUNCATED]
```

## external_callees

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "EXT:GDI32.DLL::DeleteObject",
  "EXT:KERNEL32.DLL::GetModuleHandleA",
  "EXT:USER32.DLL::DestroyWindow",
  "EXT:USER32.DLL::KillTimer",
  "EXT:USER32.DLL::SystemParametersInfoA",
  "EXT:USER32.DLL::UnregisterClassA"
]
```

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 9716,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit canvas receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"bool in AL; true on reviewed cleanup paths\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00847a40\",\n      \"va\": \"0x00847a40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00847a90\",\n      \"va\": \"0x00847a90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00847b10\",\n      \"va\": \"0x00847b10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00847b40\",\n      \"va\": \"0x00847b40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00848100\",\n      \"va\": \"0x00848100\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00849da0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00849da9\",\n        \"direction\": \"in\",\n        \"other\": \"0x00849da0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00848047\",\n        \"direction\": \"out\",\n        \"other\": \"0x00847e70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0084809b\",\n        \"direction\": \"out\",\n        \"other\": \"EXT:GDI32.DLL::DeleteObject\",\n        \"reference_type\": \"external\"\n      },\n      {\n        \"callsite\": \"0x00848078\",\n        \"direction\": \"out\",\n        \"other\": \"EXT:KERNEL32.DLL::GetModuleHandleA\",\n        \"reference_type\": \"external\"\n      },\n      {\n        \"callsite\": \"0x00848068\",\n        \"direction\": \"out\",\n        \"other\": \"EXT:USER32.DLL::DestroyWindow\",\n        \"reference_type\": \"external\"\n      },\n      {\n        \"callsite\": \"0x00848055\",\n        \"direction\": \"out\",\n        \"other\": \"EXT:USER32.DLL::KillTimer\",\n        \"reference_type\": \"external\"\n      },\n      {\n        \"callsite\": \"0x008480c1\",\n        \"direction\": \"out\",\n        \"other\": \"EXT:USER32.DLL::SystemParametersInfoA\",\n        \"reference_type\": \"external\"\n      },\n      {\n        \"callsite\": \"0x008480d3\",\n        \"direction\": \"out\",\n        \"other\": \"EXT:USER32.DLL::SystemParametersInfoA\",\n        \"reference_type\": \"external\"\n      },\n      {\n        \"callsite\": \"0x008480e8\",\n        \"direction\": \"out\",\n        \"other\": \"EXT:USER32.DLL::SystemParametersInfoA\",\n        \"reference_type\": \"external\"\n      },\n      {\n        \"callsite\": \"0x00848084\",\n        \
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
  "body_end": "008480fa",
  "body_span_bytes": 219,
  "body_start": "00848020",
  "callees": [
    "UnregisterClassA",
    "GetModuleHandleA",
    "KillTimer",
    "SystemParametersInfoA",
    "DestroyWindow",
    "DeleteObject",
    "FUN_00847e70"
  ],
  "callers": [
    "FUN_00849da0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00848020",
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
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "App::Canvas::func80h",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "Canvas *"
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
  "rva": "0x448020",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::Canvas::func80h(Canvas * this, int param_2)",
  "size_bytes": 219,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00848020",
  "vtables": {
    "referenced_by_vtables": [
      "0x0141ca70"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "00849da9"
    },
    {
      "from": "0141ca78"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__func80h.c",
  "file": "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__func80h.c",
    "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-canvas-wave6/00848020.json"
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
    "platform handles, dispatch records, global state, and teardown ownership remain gated",
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
  "bool",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueOwnerManager"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0141ca70"
]
```

## Conflicts

```json
[]
```
