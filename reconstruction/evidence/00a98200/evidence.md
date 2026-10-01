# Evidence 0x00a98200

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `da46022a7f12512b163a7147fdff596fc32ca9687a6b5d569e898c2de934ade4`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_note": "DECLARED void BECAUSE THE BYTES PRODUCE NOTHING, and the canonical machine record disagrees in a way that is recorded rather than papered over. The three exits are 0x00a98332 (latch already zero -- EAX untouched by this body, so whatever the caller had), 0x00a98330 (service null -- EAX holds the service word the null test just read) and the fall-through (EAX holds the last indirect callee's return, which the body never reads). No path loads EAX with a value meant for the caller, and the epilogue does not move it. Ghidra's independent decompilation of the same listing agrees: it opens `void ...",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EBP",
    "EDI",
    "ESI"
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
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EDI",
      "ESI"
    ],
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +48, so the listing is not one path"
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
  "content_sha256": "358ee9e36c3cfd04edb7d653bbeed2794c05a245417715a93dc9f14f896df8c3",
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
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0042"
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
        "obs-0042"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0017",
        "obs-0030",
        "obs-0031",
        "obs-0032",
        "obs-0033",
        "obs-0034",
        "obs-0035",
        "obs-0037"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          16,
          80
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0017",
        "obs-0030",
        "obs-0031",
        "obs-0032",
        "obs-0033",
        "obs-0034",
        "obs-0035",
        "obs-0037",
        "obs-0042"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0042"
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
        "obs-0042"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0042"
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
      "at": "0x00a98200",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 5,
      "raw": "SUB ESP,0x50",
      "sub": 80
    },
    {
      "at": "0x00a98200",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x50",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00a98203",
      "count": 9,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00a98204",
      "count": 12,
      "first_use": 2,
      "first_write_index": 22,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00a98204",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00a98210",
      "count": 12,
      "first_use": 5,
      "first_write_index": 10,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00a98211",
      "count": 9,
      "first_use": 6,
      "first_write_index": 
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
  "count": 110,
  "instructions": [
    {
      "address": "00a98200",
      "instruction": "SUB ESP,0x50"
    },
    {
      "address": "00a98203",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00a98204",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00a98206",
      "instruction": "CMP byte ptr [EDI + 0x10],0x0"
    },
    {
      "address": "00a9820a",
      "instruction": "JZ 0x00a98332"
    },
    {
      "address": "00a98210",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00a98211",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00a98212",
      "instruction": "MOV byte ptr [EDI + 0x10],0x0"
    },
    {
      "address": "00a98216",
      "instruction": "CALL 0x00883860"
    },
    {
      "address": "00a9821b",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00a9821d",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00a9821f",
      "instruction": "CMP ESI,EBP"
    },
    {
      "address": "00a98221",
      "instruction": "JZ 0x00a98330"
    },
    {
      "address": "00a98227",
      "instruction": "MOV EAX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00a9822a",
      "instruction": "TEST byte ptr [EAX + 0x8],0x1"
    },
    {
      "address": "00a9822e",
      "instruction": "JZ 0x00a9824c"
    },
    {
      "address": "00a98230",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00a98232",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00a98235",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00a98236",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00a9823a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a9823b",
      "instruction": "PUSH 0xe7a8472"
    },
    {
      "address": "00a98240",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00a98242",
      "instruction": "MOV dword ptr [ESP + 0x20],EBP"
    },
    {
      "address": "00a98246",
      "instruction": "MOV dword ptr [ESP + 0x18],EBP"
    },
    {
      "address": "00a9824a",
      "instruction": "CALL EDX"
    },
    {
      "address": "00a9824c",
      "instruction": "MOV EAX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00a9824f",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a98252",
      "instruction": "SHR ECX,0x1"
    },
    {
      "address": "00a98254",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00a98257",
      "instruction": "JZ 0x00a98279"
    },
    {
      "address": "00a98259",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00a9825b",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00a9825e",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00a9825f",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00a98263",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a98264",
      "instruction": "PUSH 0xe7a8472"
    },
    {
      "address": "00a98269",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00a9826b",
      "instruction": "MOV dword ptr [ESP + 0x20],EBP"
    },
    {
      "address": "00a9826f",
      "instruction": "MOV dword ptr [ESP + 0x18],0x1"
    },
    {
      "address": "00a98277",
      "instruction": "CALL EDX"
    },
    {
      "address": "00a98279",
      "instruction": "MOV EAX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00a9827c",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a9827f",
      "instruction": "SHR ECX,0x2"
    },
    {
      "address": "00a98282",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00a98285",
      "instruction": "JZ 0x00a982a3"
    },
    {
      "address": "00a98287",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00a98289",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00a9828c",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00a9828d",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00a98291",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a98292",
      "instruction": "PUSH 0xe7a8474"
    },
    {
      "address": "00a98297",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00a98299",
      "instruction": "MOV dword ptr [ESP + 0x20],EBP"
    },
    {
      "address": "00a9829d",
      "instruction": "MOV dword ptr [ESP + 0x18],EBP"
    },
    {
      "address": "00a982a1",
      "instruction": "CALL EDX"
    },
    {
      "address": "00a982a3",
      "instruction": "MOV EAX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00a982a6",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a982a9",
      "instruction": "SHR ECX,0x4"
    },
    {
      "address": "00a982ac",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00a982af",
      "instruction": "JZ 0x00a98330"
    },
    {
      "address": "00a982b1",
      "instruction": "MOV dword ptr [ESP + 0x54],EBP"
    },
    {
      "address": "00a982b5",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a982b8",
      "instruction": "SHR EDX,0x5"
    },
    {
      "address": "00a982bb",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00a982be",
      "instruction": "JZ 0x00a982c7"
    },
    {
      "address": "00a982c0",
      "instruction": "MOV ECX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00a982c3",
      "instruction": "MOV dword ptr [ESP + 0x1c],ECX"
    },
    {
      "address": "00a982c7",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a982ca",
      "instruction": "SHR EDX,0x6"
    },
    {
      "address": "00a982cd",
      "instruction": "TEST DL,0x1"
   
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
  "original_bytes": 9300,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"DECLARED void BECAUSE THE BYTES PRODUCE NOTHING, and the canonical machine record disagrees in a way that is recorded rather than papered over. The three exits are 0x00a98332 (latch already zero -- EAX untouched by this body, so whatever the caller had), 0x00a98330 (service null -- EAX holds the service word the null test just read) and the fall-through (EAX holds the last indirect callee's return, which the body never reads). No path loads EAX with a value meant for the caller, and the epilogue does not move it. Ghidra's independent decompilation of the same listing agrees: it opens `void ...\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01458788\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 6,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01458788\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00a98216\",\n        \"direction\": \"out\",\n        \"other\": \"0x00883860\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0340\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00a98200\",\n  \"normalized_symbol\": \"FUN_00a98200\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w2-00a98200/00a98200.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Editor\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"editor-core\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00a98200\",\n    \"name\": \"FUN_00a98200\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54
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
  "body_end": "00a98338",
  "body_span_bytes": 313,
  "body_start": "00a98200",
  "callees": [
    "FUN_00883860"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00a98200",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_48",
      "storage": "Stack[-0x48]:4",
      "type": "undefined4"
    },
    {
      "name": "local_50",
      "storage": "Stack[-0x50]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00a98200",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x698200",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00a98200(void)",
  "size_bytes": 313,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00a98200",
  "vtables": {
    "referenced_by_vtables": [
      "0x01458788"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01458794"
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
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200.cpp",
    "reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00a98200/00a98200.json"
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01458788"
]
```

## Conflicts

```json
[]
```
