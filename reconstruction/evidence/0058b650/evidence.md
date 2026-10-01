# Evidence 0x0058b650

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1787913b272cb8016413f441fe608495c09d9983a4a3decbdd163871965fbe14`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup",
  "return_semantics": "bool in AL; selection mouse-up result or false",
  "return_type": "bool",
  "stack_cleanup_bytes": 16,
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
      "entry_ESP+0x28",
      "entry_ESP+0x2c",
      "entry_ESP+0x30",
      "entry_ESP+0x34",
      "entry_ESP+0x38"
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
        "entry_offset": "entry_ESP+0x28",
        "observed": true,
        "ordinal": 10,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
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
    "ret_form": "RET 0x10",
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
        "entry_offset": "entry_ESP+0x28",
        "observed": true,
        "ordinal": 10,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +32, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x10 pops less than the highest read slot 0x38; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x10 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x10 but entry slot 0x38 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "9f29b08e288746da5135ad674091d36d177c3d0d871c410b3901cd1a419f4d91",
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
    "ghidra_parameter_count": 5,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 9,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0014",
        "obs-0029",
        "obs-0087",
        "obs-0095"
      ],
      "claim": "the callee pops 16 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 16,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0029",
        "obs-0087",
        "obs-0095"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 16,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0017",
        "obs-0019",
        "obs-0023",
        "obs-0039",
        "obs-0040",
        "obs-0042",
        "obs-0045"
      ],
      "claim": "entr
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
    "va": "0x004a88d0"
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
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
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
      "0x00587270",
      "0x0058b650",
      "0x013f57f8",
      "0x0058b650",
      "0x0057f3e0",
      "0x013f57f8",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "ceditor_vtable_tail",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x00588570",
      "0x0058b650",
      "0x00588570",
      "0x0057f3e0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570"
    ],
    "conflict_id": "manipulator_types",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
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
  "count": 332,
  "instructions": [
    {
      "address": "0058b650",
      "instruction": "SUB ESP,0x1c"
    },
    {
      "address": "0058b653",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0058b654",
      "instruction": "MOV EBX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "0058b658",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0058b659",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0058b65b",
      "instruction": "CMP EBX,dword ptr [ESI + 0x34]"
    },
    {
      "address": "0058b65e",
      "instruction": "JZ 0x0058b66a"
    },
    {
      "address": "0058b660",
      "instruction": "POP ESI"
    },
    {
      "address": "0058b661",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0058b663",
      "instruction": "POP EBX"
    },
    {
      "address": "0058b664",
      "instruction": "ADD ESP,0x1c"
    },
    {
      "address": "0058b667",
      "instruction": "RET 0x10"
    },
    {
      "address": "0058b66a",
      "instruction": "MOV EAX,dword ptr [ESI + 0x31c]"
    },
    {
      "address": "0058b670",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0058b671",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "0058b673",
      "instruction": "SUB EAX,EDI"
    },
    {
      "address": "0058b675",
      "instruction": "MOV dword ptr [ESI + 0x34],EDI"
    },
    {
      "address": "0058b678",
      "instruction": "JZ 0x0058b6b0"
    },
    {
      "address": "0058b67a",
      "instruction": "SUB EAX,0x2"
    },
    {
      "address": "0058b67d",
      "instruction": "JNZ 0x0058ba4a"
    },
    {
      "address": "0058b683",
      "instruction": "MOV EDX,dword ptr [ESP + 0x38]"
    },
    {
      "address": "0058b687",
      "instruction": "FLD float ptr [ESP + 0x34]"
    },
    {
      "address": "0058b68b",
      "instruction": "MOV ECX,dword ptr [ESI + 0x7c]"
    },
    {
      "address": "0058b68e",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0058b690",
      "instruction": "MOV EAX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "0058b693",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0058b694",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "0058b697",
      "instruction": "FSTP float ptr [ESP + 0x4]"
    },
    {
      "address": "0058b69b",
      "instruction": "FLD float ptr [ESP + 0x3c]"
    },
    {
      "address": "0058b69f",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "0058b6a2",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0058b6a3",
      "instruction": "CALL EAX"
    },
    {
      "address": "0058b6a5",
      "instruction": "POP EDI"
    },
    {
      "address": "0058b6a6",
      "instruction": "POP ESI"
    },
    {
      "address": "0058b6a7",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0058b6a9",
      "instruction": "POP EBX"
    },
    {
      "address": "0058b6aa",
      "instruction": "ADD ESP,0x1c"
    },
    {
      "address": "0058b6ad",
      "instruction": "RET 0x10"
    },
    {
      "address": "0058b6b0",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "0058b6b5",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0058b6b7",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0058b6b8",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0058b6b9",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0058b6bb",
      "instruction": "MOV EAX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "0058b6be",
      "instruction": "PUSH 0x48e5912"
    },
    {
      "address": "0058b6c3",
      "instruction": "CALL EAX"
    },
    {
      "address": "0058b6c5",
      "instruction": "CMP EBX,0x3e9"
    },
    {
      "address": "0058b6cb",
      "instruction": "JZ 0x0058ba0b"
    },
    {
      "address": "0058b6d1",
      "instruction": "CMP EBX,0x3e8"
    },
    {
      "address": "0058b6d7",
      "instruction": "JNZ 0x0058b6e5"
    },
    {
      "address": "0058b6d9",
      "instruction": "CMP dword ptr [ESI + 0x148],EDI"
    },
    {
      "address": "0058b6df",
      "instruction": "JZ 0x0058ba0b"
    },
    {
      "address": "0058b6e5",
      "instruction": "MOV EAX,EBX"
    },
    {
      "address": "0058b6e7",
      "instruction": "SUB EAX,0x3e8"
    },
    {
      "address": "0058b6ec",
      "instruction": "JZ 0x0058b6f7"
    },
    {
      "address": "0058b6ee",
      "instruction": "SUB EAX,0x2"
    },
    {
      "address": "0058b6f1",
      "instruction": "JNZ 0x0058ba4a"
    },
    {
      "address": "0058b6f7",
      "instruction": "CMP dword ptr [ESI + 0x148],EDI"
    },
    {
      "address": "0058b6fd",
      "instruction": "JZ 0x0058ba4a"
    },
    {
      "address": "0058b703",
      "instruction": "MOV EAX,dword ptr [ESI + 0xd0]"
    },
    {
      "address": "0058b709",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "0058b70b",
      "instruction": "JZ 0x0058b71e"
    },
    {
      "address": "0058b70d",
      "instruction": "CMP dword ptr [EAX + 0x3ec],EDI"
    },
    {
      "address": "0058b713",
      "instruction": "JZ 0x0058b71e"
    },
    {
      "address": "0058b715",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0058b716",
      "instruction": "CALL 0x004a5e10"
    },
    {
      "address": "0058b71b",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0058b71e",
      "instruction": "MOV ECX,dword ptr [ESI + 0x98]"
    },
    {
      "address": "0058b724",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0058b725",
      "instruction": "CALL 0x004accf0"
    },
    {
      "address": "0058b72a",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "0058b72c",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "0058b72e",
      "instruction": "JLE 0x0058b74a"
    },
    {
      "address":
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
  "original_bytes": 12855,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"bool in AL; selection mouse-up result or false\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 16,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573d70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005772b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0058b83d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00438a40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058b740\",\n        \"direction\": \"out\",\n        \"other\": \"0x0044e980\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058b859\",\n        \"direction\": \"out\",\n        \"other\": \"0x0044efb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058b91c\",\n        \"direction\": \"out\",\n        \"other\": \"0x0047e6c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058b940\",\n        \"direction\": \"out\",\n        \"other\": \"0x0047e6c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058b8a8\",\n        \"direction\": \"out\",\n        \"other\": \"0x0048fde0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058b7b8\",\n        \"direction\": \"out\",\n        \"other\": \"0x004a1020\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058b716\",\n        \
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
  "body_end": "0058ba54",
  "body_span_bytes": 1029,
  "body_start": "0058b650",
  "callees": [
    "FUN_004a88d0",
    "FUN_00577520",
    "FUN_004a1020",
    "FUN_0048fde0",
    "FUN_004a6310",
    "FUN_00573d70",
    "FUN_0067cab0",
    "FUN_004a5e10",
    "FUN_00438a40",
    "FUN_0044efb0",
    "FUN_008013d0",
    "FUN_004a6120",
    "App::IAppSystem::Get",
    "FUN_004a6640",
    "FUN_004accf0",
    "FUN_0044e980",
    "FUN_0057e790",
    "FUN_004accb0",
    "Editors::cEditor::Undo",
    "FUN_005772b0",
    "FUN_0057e160",
    "FUN_00573c00",
    "Editors::cEditor::CommitEditHistory",
    "FUN_0047e6c0",
    "FUN_004a7f30",
    "FUN_0057af00",
    "FUN_004aa030"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0058b650",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "Editors::cEditor::OnMouseUp",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 5,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cEditor *"
    },
    {
      "name": "mouseButton",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "MouseButton"
    },
    {
      "name": "mouseX",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "float"
    },
    {
      "name": "mouseY",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "float"
    },
    {
      "name": "mouseState",
      "ordinal": 4,
      "storage": "Stack[0x14]:4",
      "type": "MouseState"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x18b650",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Editors::cEditor::OnMouseUp(cEditor * this, MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)",
  "size_bytes": 1029,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0058b650",
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
      "from": "013f5828"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseUp.c",
  "file": "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseUp.c",
    "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-input-wave6/0058b650.json"
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
    "runtime validation not run",
    "selection vtable, release ownership, and runtime button state remain gated"
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
      "0x00587270",
      "0x0058b650",
      "0x013f57f8",
      "0x0058b650",
      "0x0057f3e0",
      "0x013f57f8",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "ceditor_vtable_tail",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x00588570",
      "0x0058b650",
      "0x00588570",
      "0x0057f3e0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570"
    ],
    "conflict_id": "manipulator_types",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
