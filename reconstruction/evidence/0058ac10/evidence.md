# Evidence 0x0058ac10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a381a0649ce1de8057627b4aa501cd387fdce07b30a1271ffc3ac8d985b3f256`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup",
  "return_semantics": "bool in AL from the selected key-down path",
  "return_type": "bool",
  "stack_cleanup_bytes": 8,
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
      "entry_ESP+0x8"
    ],
    "ordinary_stack_argument_slots_bounded": {
      "kept": 2,
      "omitted": 22
    },
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
      }
    ],
    "ordinary_stack_arguments_bounded": {
      "kept": 2,
      "omitted": 22
    },
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
      }
    ],
    "stack_arguments_bounded": {
      "kept": 2,
      "omitted": 22
    },
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -1932, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x8 pops less than the highest read slot 0x740; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x8 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x8 but entry slot 0x740 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "50363fdeb8456336f3cd26a1eb06c88bec822697b7dd7050ac4e4b33c0b2c3dd",
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
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 12,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0023",
        "obs-0041",
        "obs-0049",
        "obs-0057",
        "obs-0064",
        "obs-0071",
        "obs-0078",
        "obs-0087",
        "obs-0094",
        "obs-0157",
        "obs-0165",
        "obs-0172",
        "obs-0180",
        "obs-0195",
        "obs-0209",
        "obs-0216",
        "obs-0223",
        "obs-0229",
        "obs-0237",
        "obs-0245",
        "obs-0254",
        "obs-0260",
        "obs-0266",
        "obs-0279",
        "obs-0286"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0023",
        "obs-0041",
        "obs-0049",
        "obs-0057",
        "obs-0064",
        "obs-0071",
        "obs-0078",
        "obs-0087",
        "obs-0094",
        "obs-0157",
        "obs-0165",
        "obs-0172",
        "obs-0180",
        "obs-0195",
        "obs-0209",
        "obs-0216",
        "obs-0223",
        "obs-0229",
        "obs-0237",
        "obs-0245",
        "obs-0254",
        "obs-0260",
        "obs-0266",
        "obs-0279",
        "obs-0286"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 8,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0009",
        "obs-0031",
        "obs-0034",
        "obs-0035",
        "obs-0042",
        "obs-0043",
        "obs-0050",
        "obs-0051",
        "obs-0095",
        "obs-0101",
        "obs-0106",
        "obs-0118",
        "obs-0122",
        "obs-0123",
        "obs-0124",
        "obs-0125",
        "obs-0128",
        "obs-0129",
        "obs-0130",
        "obs-0131",
        "obs-0132",
        "obs-0133",
        "obs-0134",
        "obs-0137",
        "obs-0138",
        "obs-0139",
        "obs-0141",
        "obs-0143",
        "obs-0144",
        "obs-0145",
        "obs-0149",
        "obs-0158",
        "obs-0173",
        "obs-0183",
        "obs-0185",
        "obs-0187",
        "obs-0203",
        "obs-0269"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 432,
        "observed_slots": 32,
        "total_bytes": 1856
      }
    },
    {
      "based_on": [
        "ob
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
    "va": "0x00438700"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043eed0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004adaa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573c00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573d70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005772b0"
  },
  {
    "name": "editor_query_dispatch_005dfd00",
    "reconstructed": true,
    "va": "0x005dfd00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  },
  {
    "name": "game_input_on_key_down_00697a50",
    "reconstructed": true,
    "va": "0x00697a50"
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
[
  {
    "anchors": [
      "0x005737d0",
      "0x00588570",
      "0x0058ac10",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587a20"
    ],
    "conflict_id": "editor_input_routing",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x0058ac10",
      "0x0058ac10"
    ],
    "conflict_id": "editor_runtime_validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  },
  {
    "anchors": [
      "0x005e0000",
      "0x70218642",
      "0xb006ef6e",
      "0xf006efa5",
      "0xf019c2e7",
      "0xf019c2f3",
      "0x005e0000",
      "0x004af260",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058ac10"
    ],
    "conflict_id": "editor_ui_command_names",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00574080",
      "0x00586410",
      "0x0058ac10",
      "0x0058ac10",
      "0x004af260",
      "0x00574080",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00586410",
      "0x00587a20",
      "0x00587a20",
      "0x0058be50"
    ],
    "conflict_id": "history_budget_semantics",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
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
  "count": 774,
  "instructions": [
    {
      "address": "0058ac10",
      "instruction": "SUB ESP,0x50"
    },
    {
      "address": "0058ac13",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0058ac14",
      "instruction": "MOV EBX,dword ptr [ESP + 0x5c]"
    },
    {
      "address": "0058ac18",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0058ac19",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0058ac1a",
      "instruction": "MOV EDI,dword ptr [ESP + 0x60]"
    },
    {
      "address": "0058ac1e",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0058ac20",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0058ac21",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0058ac22",
      "instruction": "LEA ECX,[ESI + 0xf8]"
    },
    {
      "address": "0058ac28",
      "instruction": "MOV byte ptr [ESP + 0x14],0x0"
    },
    {
      "address": "0058ac2d",
      "instruction": "CALL 0x00697a50"
    },
    {
      "address": "0058ac32",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0058ac34",
      "instruction": "CALL 0x005855b0"
    },
    {
      "address": "0058ac39",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0058ac3b",
      "instruction": "CALL 0x005855b0"
    },
    {
      "address": "0058ac40",
      "instruction": "CMP byte ptr [ESI + 0x397],0x0"
    },
    {
      "address": "0058ac47",
      "instruction": "JZ 0x0058ac54"
    },
    {
      "address": "0058ac49",
      "instruction": "POP EDI"
    },
    {
      "address": "0058ac4a",
      "instruction": "POP ESI"
    },
    {
      "address": "0058ac4b",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0058ac4d",
      "instruction": "POP EBX"
    },
    {
      "address": "0058ac4e",
      "instruction": "ADD ESP,0x50"
    },
    {
      "address": "0058ac51",
      "instruction": "RET 0x8"
    },
    {
      "address": "0058ac54",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0058ac55",
      "instruction": "CALL 0x0067caa0"
    },
    {
      "address": "0058ac5a",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0058ac5c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0058ac5e",
      "instruction": "MOV EAX,dword ptr [EDX + 0x84]"
    },
    {
      "address": "0058ac64",
      "instruction": "CALL EAX"
    },
    {
      "address": "0058ac66",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "0058ac68",
      "instruction": "CALL 0x00401030"
    },
    {
      "address": "0058ac6d",
      "instruction": "CMP dword ptr [ESI + 0x31c],0x2"
    },
    {
      "address": "0058ac74",
      "instruction": "MOV AL,byte ptr [EAX + 0x1c]"
    },
    {
      "address": "0058ac77",
      "instruction": "MOV byte ptr [ESP + 0x68],AL"
    },
    {
      "address": "0058ac7b",
      "instruction": "JNZ 0x0058ac99"
    },
    {
      "address": "0058ac7d",
      "instruction": "MOV ECX,dword ptr [ESI + 0x7c]"
    },
    {
      "address": "0058ac80",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "0058ac82",
      "instruction": "MOV EAX,dword ptr [EDX + 0x1c]"
    },
    {
      "address": "0058ac85",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0058ac86",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0058ac87",
      "instruction": "CALL EAX"
    },
    {
      "address": "0058ac89",
      "instruction": "MOV byte ptr [ESP + 0x10],AL"
    },
    {
      "address": "0058ac8d",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0058ac8f",
      "instruction": "JNZ 0x0058b14b"
    },
    {
      "address": "0058ac95",
      "instruction": "MOV AL,byte ptr [ESP + 0x68]"
    },
    {
      "address": "0058ac99",
      "instruction": "MOV EDI,EBX"
    },
    {
      "address": "0058ac9b",
      "instruction": "AND EDI,0x7"
    },
    {
      "address": "0058ac9e",
      "instruction": "TEST BL,0x40"
    },
    {
      "address": "0058aca1",
      "instruction": "JNZ 0x0058b531"
    },
    {
      "address": "0058aca7",
      "instruction": "MOV ECX,dword ptr [ESP + 0x64]"
    },
    {
      "address": "0058acab",
      "instruction": "ADD ECX,-0x8"
    },
    {
      "address": "0058acae",
      "instruction": "CMP ECX,0xb7"
    },
    {
      "address": "0058acb4",
      "instruction": "JA 0x0058b531"
    },
    {
      "address": "0058acba",
      "instruction": "MOVZX ECX,byte ptr [ECX + 0x58b594]"
    },
    {
      "address": "0058acc1",
      "instruction": "JMP dword ptr [ECX*0x4 + 0x58b540]"
    },
    {
      "address": "0058acc8",
      "instruction": "POP EBP"
    },
    {
      "address": "0058acc9",
      "instruction": "POP EDI"
    },
    {
      "address": "0058acca",
      "instruction": "MOV dword ptr [ESI + 0x30],EBX"
    },
    {
      "address": "0058accd",
      "instruction": "POP ESI"
    },
    {
      "address": "0058acce",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0058acd0",
      "instruction": "POP EBX"
    },
    {
      "address": "0058acd1",
      "instruction": "ADD ESP,0x50"
    },
    {
      "address": "0058acd4",
      "instruction": "RET 0x8"
    },
    {
      "address": "0058acd7",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "0058acd9",
      "instruction": "JNZ 0x0058b531"
    },
    {
      "address": "0058acdf",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0058ace1",
      "instruction": "JNZ 0x0058b531"
    },
    {
      "address": "0058ace7",
      "instruction": "MOV EDX,dword ptr [ESI + 0x30]"
    },
    {
      "address": "0058acea",
      "instruction": "FLD float ptr [ESI + 0x2c]"
    },
    {
      "address": "0058aced",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "0058acef",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0058acf0",
      "instruction": "SUB ESP,0x8"
    },
 
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
  "original_bytes": 13840,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"bool in AL from the selected key-down path\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"game_input_on_key_down_00697a50\",\n      \"va\": \"0x00697a50\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00438700\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043eed0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004adaa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573d70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005772b0\"\n      },\n      {\n        \"name\": \"editor_query_dispatch_005dfd00\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dfd00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": \"game_input_on_key_down_00697a50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00697a50\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0058ac68\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401030\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058b25e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401040\"
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
  "body_end": "0058b53c",
  "body_span_bytes": 2349,
  "body_start": "0058ac10",
  "callees": [
    "FUN_006288c0",
    "FUN_00572260",
    "FUN_005dc300",
    "FUN_0057c530",
    "FUN_00573d70",
    "FUN_0043eed0",
    "FUN_006284a0",
    "FUN_005dd070",
    "FUN_00453eb0",
    "FUN_00438f20",
    "FUN_0067dd00",
    "FUN_0057e790",
    "FUN_00628930",
    "FUN_0067cb10",
    "FUN_005857c0",
    "FUN_00575eb0",
    "Editors::cEditor::Undo",
    "FUN_005858f0",
    "FUN_0067c830",
    "FUN_0044f420",
    "FUN_0044e830",
    "FUN_004511d0",
    "FUN_00573480",
    "App::DirectPropertyList::SetBool",
    "FUN_005725d0",
    "Sporepedia::cAssetViewManager::Get",
    "FUN_00401040",
    "FUN_00439110",
    "FUN_00435a10",
    "FUN_00448e90",
    "FUN_005dfb40",
    "FUN_004a0b70",
    "Editors::cEditor::Redo",
    "FUN_005dfd00",
    "FUN_00449420",
    "FUN_0067cac0",
    "App::IAppSystem::Get",
    "FUN_0067caa0",
    "FUN_005ca920",
    "FUN_0048c790",
    "FUN_005dc2d0",
    "FUN_00572520",
    "FUN_005855b0",
    "FUN_004adaa0",
    "FUN_005772b0",
    "FUN_005dc2e0",
    "FUN_00573c00",
    "FUN_0043eb50",
    "Editors::cEditor::CommitEditHistory",
    "FUN_005dd050",
    "FUN_004a6f10",
    "FUN_00438700",
    "FUN_004abaf0",
    "FUN_004a7f30",
    "FUN_0049dd20",
    "GameInput::OnKeyDown"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0058ac10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_50",
      "storage": "Stack[-0x50]:1",
      "type": "undefined1"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "Editors::cEditor::OnKeyDown",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cEditor *"
    },
    {
      "name": "virtualKey",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "modifiers",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "KeyModifiers"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x18ac10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Editors::cEditor::OnKeyDown(cEditor * this, int virtualKey, KeyModifiers modifiers)",
  "size_bytes": 2349,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0058ac10",
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
      "from": "013f581c"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnKeyDown.c",
  "file": "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnKeyDown.c",
    "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-input-wave6/0058ac10.json"
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
    "input command domains, external paths, wheel handling, and runtime object/vtable ownership remain gated",
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
[
  {
    "anchors": [
      "0x005737d0",
      "0x00588570",
      "0x0058ac10",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587a20"
    ],
    "conflict_id": "editor_input_routing",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x0058ac10",
      "0x0058ac10"
    ],
    "conflict_id": "editor_runtime_validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  },
  {
    "anchors": [
      "0x005e0000",
      "0x70218642",
      "0xb006ef6e",
      "0xf006efa5",
      "0xf019c2e7",
      "0xf019c2f3",
      "0x005e0000",
      "0x004af260",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058ac10"
    ],
    "conflict_id": "editor_ui_command_names",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00574080",
      "0x00586410",
      "0x0058ac10",
      "0x0058ac10",
      "0x004af260",
      "0x00574080",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00586410",
      "0x00587a20",
      "0x00587a20",
      "0x0058be50"
    ],
    "conflict_id": "history_budget_semantics",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
