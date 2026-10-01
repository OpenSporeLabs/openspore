# Evidence 0x00f968b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2b70b7ac4c38b2b21b53aed5fb111c8847a7cc34c64c5a7a356deb6a3bda0967`

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
  "hidden_this_register": "ECX",
  "hidden_this_type": "cTerrainSphere *",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4 at 0x00f968f5 (success) and at 0x00f968fd (failure)",
  "return_observation": "EAX is 1 only when the +0x58 slot answered the address of receiver+0x04 for selector id 0x8 AND for selector id 0x7; EAX is 0 on the first mismatch and on the second mismatch",
  "return_register": "EAX",
  "return_type": "bool",
  "return_width_bytes": 4,
  "saved_registers": "EBX, ESI, EDI - pushed at 0x00f968b0, 0x00f968b1 and 0x00f968b4, popped at 0x00f968ed/0x00f968ee and 0x00f968f8/0x00f968f9, with EBX popped last at 0x00f968f4 and 0x00f968fc",
  "stack_arguments": 1,
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "returns to the caller from either RET 0x4; there is no tail call, no exception path and no loop"
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
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path"
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
  "content_sha256": "9a5c1a5c5f35cb295387fba2c27788513df60dfe6f21f274fc6db3d4318b5156",
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
    "ghidra_parameter_count": 2,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020",
        "obs-0024"
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
        "obs-0003"
      ],
      "claim": "ECX carries the receiver: 0x00f968b0 is slot 37 of the vptr-backed vftable at 0x01490be8, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 37,
        "table": "0x01490be8"
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0013",
        "obs-0020",
        "obs-0024"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0024"
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
        "obs-0020",
        "obs-0024"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0024"
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
      "at": "0x00f968b0",
      "count": 5,
      "first_use": 0,
      "first_write_index": 9,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00f968b1",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00f968b2",
      "count": 1,
      "first_use": 2,
      "first_write_index": 13,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00f968b2",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00f968b4",
      "count": 3,
      "first_use": 3,
      "first_write_index": 8,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00f968be",
      "definite": true,
      "id": "obs-0006",
      "index": 8,
      "kind": "REG_WRITE",
   
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
  "count": 39,
  "instructions": [
    {
      "address": "00f968b0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00f968b1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00f968b2",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00f968b4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00f968b5",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00f968b7",
      "instruction": "JZ 0x00f968be"
    },
    {
      "address": "00f968b9",
      "instruction": "LEA EDI,[ESI + 0x4]"
    },
    {
      "address": "00f968bc",
      "instruction": "JMP 0x00f968c0"
    },
    {
      "address": "00f968be",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00f968c0",
      "instruction": "MOV EBX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00f968c4",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00f968c6",
      "instruction": "MOV EDX,dword ptr [EAX + 0x58]"
    },
    {
      "address": "00f968c9",
      "instruction": "PUSH 0x8"
    },
    {
      "address": "00f968cb",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00f968cd",
      "instruction": "CALL EDX"
    },
    {
      "address": "00f968cf",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00f968d1",
      "instruction": "JNZ 0x00f968f8"
    },
    {
      "address": "00f968d3",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00f968d5",
      "instruction": "JZ 0x00f968dc"
    },
    {
      "address": "00f968d7",
      "instruction": "ADD ESI,0x4"
    },
    {
      "address": "00f968da",
      "instruction": "JMP 0x00f968de"
    },
    {
      "address": "00f968dc",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00f968de",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00f968e0",
      "instruction": "MOV EDX,dword ptr [EAX + 0x58]"
    },
    {
      "address": "00f968e3",
      "instruction": "PUSH 0x7"
    },
    {
      "address": "00f968e5",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00f968e7",
      "instruction": "CALL EDX"
    },
    {
      "address": "00f968e9",
      "instruction": "CMP EAX,ESI"
    },
    {
      "address": "00f968eb",
      "instruction": "JNZ 0x00f968f8"
    },
    {
      "address": "00f968ed",
      "instruction": "POP EDI"
    },
    {
      "address": "00f968ee",
      "instruction": "POP ESI"
    },
    {
      "address": "00f968ef",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "00f968f4",
      "instruction": "POP EBX"
    },
    {
      "address": "00f968f5",
      "instruction": "RET 0x4"
    },
    {
      "address": "00f968f8",
      "instruction": "POP EDI"
    },
    {
      "address": "00f968f9",
      "instruction": "POP ESI"
    },
    {
      "address": "00f968fa",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00f968fc",
      "instruction": "POP EBX"
    },
    {
      "address": "00f968fd",
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
  "original_bytes": 10741,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"cTerrainSphere *\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4 at 0x00f968f5 (success) and at 0x00f968fd (failure)\",\n    \"return_observation\": \"EAX is 1 only when the +0x58 slot answered the address of receiver+0x04 for selector id 0x8 AND for selector id 0x7; EAX is 0 on the first mismatch and on the second mismatch\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"bool\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": \"EBX, ESI, EDI - pushed at 0x00f968b0, 0x00f968b1 and 0x00f968b4, popped at 0x00f968ed/0x00f968ee and 0x00f968f8/0x00f968f9, with EBX popped last at 0x00f968f4 and 0x00f968fc\",\n    \"stack_arguments\": 1,\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"returns to the caller from either RET 0x4; there is no tail call, no exception path and no loop\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-00f9b7f0\",\n      \"score\": 12,\n      \"symbol\": \"re_00f9b7f0\",\n      \"va\": \"0x00f9b7f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w2-00f999e0\",\n      \"score\": 6,\n      \"symbol\": \"re_00f999e0\",\n      \"va\": \"0x00f999e0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-fa0d50-atomic-inc\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00fa0d50\",\n      \"va\": \"0x00fa0d50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa5580\",\n      \"score\": 6,\n      \"symbol\": \"re_00fa5580\",\n      \"va\": \"0x00fa5580\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa6ec0\",\n      \"score\": 6,\n      \"symbol\": \"re_00fa6ec0\",\n      \"va\": \"0x00fa6ec0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa73c0\",\n      \"score\": 6,\n      \"symbol\": \"sw1_snap_and_dispatch_00fa73c0\",\n      \"va\": \"0x00fa73c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-0104c110\",\n      \"score\": 6,\n      \"symbol\": \"re_0104c110\",\n      \"va\": \"0x0104c110\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"terrain-world\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0571\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"Terrain::cTerrainSphere::GetSimDataRTT\",\n  \"normalized_symbol\": \"Terrain::cTerrainSphere::GetSimDataRTT\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Terrain__cTerrainSphere__GetSimDataRTT.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/Terrain__cTerrainSphere__GetSimDataRTT.c\",\n      \"reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0.cpp\",\n      \"reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0.hpp\",\n      \"reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-terrain-getsimdatartt-00f968b0/00f968b0.json\"\n    ],\n    \"provenance\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/Terrain__cTerrainSphere__GetSimDataRTT.c (persisted export, superseded: mis-typed receiver, invented unaff_* registers, 'Raster *' return)\",\n      \"ghidra:byte
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
  "body_end": "00f968ff",
  "body_span_bytes": 80,
  "body_start": "00f968b0",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00f968b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Terrain::cTerrainSphere::GetSimDataRTT",
  "namespace": "Terrain",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cTerrainSphere *"
    },
    {
      "name": "quadIndex",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "Raster *",
  "return_type_resolved": true,
  "rva": "0xb968b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "Raster * Terrain::cTerrainSphere::GetSimDataRTT(cTerrainSphere * this, int quadIndex)",
  "size_bytes": 80,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00f968b0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01490be8",
      "0x01490c7c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01490c7c"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Terrain__cTerrainSphere__GetSimDataRTT.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Terrain__cTerrainSphere__GetSimDataRTT.c",
    "reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0.cpp",
    "reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0.hpp",
    "reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-terrain-getsimdatartt-00f968b0/00f968b0.json"
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
  "gates": [],
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
  "runtime_gated": false,
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
  "OpaqueSelectorProvider",
  "OpaqueTerrainSphere",
  "bool",
  "cTerrainSphere *",
  "openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0::OpaqueRttData",
  "openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0::OpaqueSelectorProvider",
  "openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0::OpaqueSelectorProviderVTable",
  "openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0::OpaqueTerrainSphere"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00000058",
  "vtable:0x00f968b0",
  "vtable:0x01490be8",
  "vtable:0x01490c7c"
]
```

## Conflicts

```json
[]
```
