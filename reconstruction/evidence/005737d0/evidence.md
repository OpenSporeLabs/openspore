# Evidence 0x005737d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7a2f2835e74864a91caac0c2cbe19dff38b55e4db496bdffcd7184d0b02ae1f4`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup",
  "return_semantics": "bool in AL; editor mouse-move state transition result",
  "return_type": "bool",
  "stack_cleanup_bytes": 12,
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10"
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
    "ret_form": "RET 0xc",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBX",
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0xc pops less than the highest read slot 0x10; everything above it belongs to the caller's frame",
    "no_discriminator: the callee pop of 0xc is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0xc but entry slot 0x10 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "627d652641501ac96a00330399196851615fd7e83210c6668826857f08c3bc1e",
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
    "ghidra_parameter_count": 4,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017",
        "obs-0029",
        "obs-0037",
        "obs-0048",
        "obs-0053",
        "obs-0056"
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
        "obs-0017",
        "obs-0029",
        "obs-0037",
        "obs-0048",
        "obs-0053",
        "obs-0056"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 12,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0009",
        "obs-0012",
        "obs-0019",
        "obs-0024",
        "obs-0030",
        "obs-0032",
        "obs-0038",
        "obs-0040"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 4,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0018"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          40,
          44,
          48,
          52,
          56,
          124,
          152,
          192,
          196,
          328,
          691,
          692,
          796,
          919
        ],
        "register": "ECX",
        "written_through": 7
      }
    },
    {
      "based_on": [
        "obs-0056"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0029",
        "obs-0037",
        "obs-0048",
        "obs-0053",
        "obs-0056"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confidence": "APPROXIMATION",
      "id": "S2",
      "value": {
        "present": false
      }

[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004b09b0"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 12798,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-001-mission-transitions\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"resolution_status\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00d2e4a0\",\n      \"0x00d2e4a0\",\n      \"0x00aeb7b0\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\",\n      \"0x00588570\",\n      \"0x00588570\",\n      \"0x0058a5a0\"\n    ],\n    \"conflict_id\": \"U-002-tribe-plans\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00aeb160\",\n      \"0x00aeb7b0\",\n      \"0x00aebe90\",\n      \"0x00aeb160\",\n      \"0x00aebe90\",\n      \"0x00aeb7b0\",\n      \"0x00aeb7b0\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\"\n    ],\n    \"conflict_id\": \"U-007-communication-completion\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"resolution_status\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-008-runtime-validation\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00587270\",\n      \"0x0058b650\",\n      \"0x013f57f8\",\n      \"0x0058b650\",\n      \"0x0057f3e0\",\n      \"0x013f57f8\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x0057ce80\",\n      \"0x0057ce80\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"ceditor_vtable_tail\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.\",\n    \"resolution_status\": \"The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x005737d0\",\n      \"0x00588570\",\n      \"0x0058ac10\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x0057ce80\",\n      \"0x0057ce80\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00587a20\"\n    ],\n    \"conflict_id\": \"editor_input_routing\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The input/UI surface is structurally presen
[TRUNCATED]
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
  "count": 117,
  "instructions": [
    {
      "address": "005737d0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005737d1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005737d2",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005737d4",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "005737d6",
      "instruction": "CMP byte ptr [ESI + 0x397],BL"
    },
    {
      "address": "005737dc",
      "instruction": "JNZ 0x0057393e"
    },
    {
      "address": "005737e2",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0xc]"
    },
    {
      "address": "005737e8",
      "instruction": "MOV EDX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "005737ec",
      "instruction": "MOVSS dword ptr [ESI + 0x28],XMM0"
    },
    {
      "address": "005737f1",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x10]"
    },
    {
      "address": "005737f7",
      "instruction": "MOVSS dword ptr [ESI + 0x2c],XMM0"
    },
    {
      "address": "005737fc",
      "instruction": "MOV dword ptr [ESI + 0x30],EDX"
    },
    {
      "address": "005737ff",
      "instruction": "MOV byte ptr [ESI + 0x38],0x1"
    },
    {
      "address": "00573803",
      "instruction": "CMP byte ptr [ESI + 0x2b3],BL"
    },
    {
      "address": "00573809",
      "instruction": "JZ 0x00573818"
    },
    {
      "address": "0057380b",
      "instruction": "MOV byte ptr [ESI + 0x2b3],BL"
    },
    {
      "address": "00573811",
      "instruction": "POP ESI"
    },
    {
      "address": "00573812",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00573814",
      "instruction": "POP EBX"
    },
    {
      "address": "00573815",
      "instruction": "RET 0xc"
    },
    {
      "address": "00573818",
      "instruction": "MOV EAX,dword ptr [ESI + 0x31c]"
    },
    {
      "address": "0057381e",
      "instruction": "CMP EAX,0x2"
    },
    {
      "address": "00573821",
      "instruction": "JNZ 0x0057384c"
    },
    {
      "address": "00573823",
      "instruction": "TEST DL,0x38"
    },
    {
      "address": "00573826",
      "instruction": "JZ 0x0057384c"
    },
    {
      "address": "00573828",
      "instruction": "MOV ECX,dword ptr [ESI + 0x7c]"
    },
    {
      "address": "0057382b",
      "instruction": "FLD float ptr [ESP + 0x10]"
    },
    {
      "address": "0057382f",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00573831",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00573832",
      "instruction": "MOV EDX,dword ptr [EAX + 0x18]"
    },
    {
      "address": "00573835",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00573838",
      "instruction": "FSTP float ptr [ESP + 0x4]"
    },
    {
      "address": "0057383c",
      "instruction": "FLD float ptr [ESP + 0x18]"
    },
    {
      "address": "00573840",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00573843",
      "instruction": "CALL EDX"
    },
    {
      "address": "00573845",
      "instruction": "POP ESI"
    },
    {
      "address": "00573846",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00573848",
      "instruction": "POP EBX"
    },
    {
      "address": "00573849",
      "instruction": "RET 0xc"
    },
    {
      "address": "0057384c",
      "instruction": "MOV ECX,dword ptr [ESI + 0x34]"
    },
    {
      "address": "0057384f",
      "instruction": "CMP ECX,0x3e9"
    },
    {
      "address": "00573855",
      "instruction": "JZ 0x005738ff"
    },
    {
      "address": "0057385b",
      "instruction": "CMP ECX,0x3ea"
    },
    {
      "address": "00573861",
      "instruction": "JZ 0x005738ff"
    },
    {
      "address": "00573867",
      "instruction": "CMP ECX,0x3e8"
    },
    {
      "address": "0057386d",
      "instruction": "JNZ 0x0057387b"
    },
    {
      "address": "0057386f",
      "instruction": "CMP dword ptr [ESI + 0x148],EBX"
    },
    {
      "address": "00573875",
      "instruction": "JZ 0x005738ff"
    },
    {
      "address": "0057387b",
      "instruction": "SUB EAX,EBX"
    },
    {
      "address": "0057387d",
      "instruction": "JZ 0x005738a8"
    },
    {
      "address": "0057387f",
      "instruction": "SUB EAX,0x2"
    },
    {
      "address": "00573882",
      "instruction": "JNZ 0x00573811"
    },
    {
      "address": "00573884",
      "instruction": "MOV ECX,dword ptr [ESI + 0x7c]"
    },
    {
      "address": "00573887",
      "instruction": "FLD float ptr [ESP + 0x10]"
    },
    {
      "address": "0057388b",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0057388d",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0057388e",
      "instruction": "MOV EDX,dword ptr [EAX + 0x18]"
    },
    {
      "address": "00573891",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00573894",
      "instruction": "FSTP float ptr [ESP + 0x4]"
    },
    {
      "address": "00573898",
      "instruction": "FLD float ptr [ESP + 0x18]"
    },
    {
      "address": "0057389c",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "0057389f",
      "instruction": "CALL EDX"
    },
    {
      "address": "005738a1",
      "instruction": "POP ESI"
    },
    {
      "address": "005738a2",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "005738a4",
      "instruction": "POP EBX"
    },
    {
      "address": "005738a5",
      "instruction": "RET 0xc"
    },
    {
      "address": "005738a8",
      "instruction": "MOV ECX,dword ptr [ESI + 0x148]"
    },
    {
      "address": "005738ae",
      "instruction": "CMP ECX,EBX"
    },
    {
      "address": "005738b0",
      "instruction": "JZ 0x00573811"
    },
    {
      "address": "005738b6",
      "instruction": "FLD float ptr [ESP + 0x10]"
    },
    {
      "address": "005738ba",
      "instruction": "MOV EAX,dword ptr [ECX]"
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
  "original_bytes": 8354,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"bool in AL; editor mouse-move state transition result\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 12,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004b09b0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005738f3\",\n        \"direction\": \"out\",\n        \"other\": \"0x004adfc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005738e6\",\n        \"direction\": \"out\",\n        \"other\": \"0x004b09b0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0054\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Editors::cEditor::OnMouseMove\",\n  \"normalized_symbol\": \"editor_input_005737d0\",\n  \"observed_mechanics\": [\n    \"Reads editor+0x397 and returns false when nonzero.\",\n    \"Publishes x, y, state, and pending byte at offsets 0x28, 0x2c, 0x30, and 0x38.\",\n    \"Applies pending-clear, mode-2, near-button distance, and selection gates in source order.\",\n    \"Calls mode mouse-move for mode 2 or selection move plus query and side-effect hook for mode 0 with selection.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-EDITOR-INPUT-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\":
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
  "body_end": "00573944",
  "body_span_bytes": 373,
  "body_start": "005737d0",
  "callees": [
    "FUN_004adfc0",
    "FUN_004b09b0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005737d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "Editors::cEditor::OnMouseMove",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 4,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cEditor *"
    },
    {
      "name": "mouseX",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "float"
    },
    {
      "name": "mouseY",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "float"
    },
    {
      "name": "mouseState",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "MouseState"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x1737d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Editors::cEditor::OnMouseMove(cEditor * this, float mouseX, float mouseY, MouseState mouseState)",
  "size_bytes": 373,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005737d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f57f8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "013f582c"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseMove.c",
  "file": "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseMove.c",
    "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-input-wave6/005737d0.json"
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
    "editor runtime hooks, mode/selection vtable ownership, and mouse coordinate interpretation remain runtime-gated",
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
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor",
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks",
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget",
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget",
  "openspore::reconstruction::pkg_editor_input_wave6::TargetWord"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f57f8"
]
```

## Conflicts

```json
{
  "original_bytes": 12798,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-001-mission-transitions\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"resolution_status\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00d2e4a0\",\n      \"0x00d2e4a0\",\n      \"0x00aeb7b0\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\",\n      \"0x00588570\",\n      \"0x00588570\",\n      \"0x0058a5a0\"\n    ],\n    \"conflict_id\": \"U-002-tribe-plans\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00aeb160\",\n      \"0x00aeb7b0\",\n      \"0x00aebe90\",\n      \"0x00aeb160\",\n      \"0x00aebe90\",\n      \"0x00aeb7b0\",\n      \"0x00aeb7b0\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\"\n    ],\n    \"conflict_id\": \"U-007-communication-completion\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"resolution_status\": \"Creation appends to cCommManager+0x20 and ShowCommEvent stores +0x1c before processing. Removal/clear and completion ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-008-runtime-validation\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00587270\",\n      \"0x0058b650\",\n      \"0x013f57f8\",\n      \"0x0058b650\",\n      \"0x0057f3e0\",\n      \"0x013f57f8\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x0057ce80\",\n      \"0x0057ce80\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"ceditor_vtable_tail\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed b
[TRUNCATED]
```
