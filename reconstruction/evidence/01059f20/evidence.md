# Evidence 0x01059f20

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2629d06da8316d8deb63b2556ef887032b1e2839f904f4e17c52369223af355f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_receiver": true,
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueToolStrategy*",
  "receiver_register": "ECX",
  "ret_form": "ret 0xc",
  "return_register": "AL",
  "return_type": "bool",
  "return_width_bytes": 1,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04 at function entry",
      "load_site": "0x01059f2d, `mov ebp, dword ptr [esp + 0x1c]` after `push ebp`",
      "observed_use": "The SDK structure cSpaceToolData (size 0x2a0) supplies every field the body touches: +0x114 mpToolOwner, +0x120 mpArea, +0x124 mpBeam and +0x174 mFlags. The callee 0x010568b0 reads the same +0x114 and +0x120 words and the callee 0x01059170 reads the same three, so one object type is proven across three functions.",
      "position": 1,
      "register": "EBP",
      "type": "cSpaceToolData*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08 at function entry",
      "load_site": "0x01059f28, `mov ebx, dword ptr [esp + 0x1c]` after `push ebx`",
      "observed_use": "Read as three consecutive floats at +0, +4 and +8 by `movss` at 0x01059f6e, 0x01059f7e and 0x01059f89, copied into a 12-byte stack local, and re-materialised by `flds`/`fstps` at 0x0105a00f-0x0105a022 for the call to 0x01059170. A by-value Vector3 would need four stack words at the call site; the direct caller at 0x0105aa5c-0x0105aa6e pushes exactly three dwords, so the argument is a pointer.",
      "position": 2,
      "register": "EBX",
      "type": "Vector3*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0c at function entry",
      "load_site": "0x01059f23, `mov eax, dword ptr [esp + 0x1c]` after `sub esp, 0x10`",
      "observed_use": "Pushed as the last argument to 0x010568b0 at 0x01059f33 and never read again, so it is forwarded unchanged and otherwise unused. The SDK spells the fourth parameter of every sibling virtual `int param_4`.",
      "position": 3,
      "register": "EAX",
      "type": "int",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 12,
  "stack_cleanup_owner": "callee",
  "termination": "Single return instruction at 0x0105a043, `C2 0C 00`."
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
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
      }
    ],
    "ret_form": "RET 0xc",
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
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +28, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "0ec903a6ad62a6413af97f6af89f2f3d70e6747890f5dd691f6d04d19969bbba",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 7,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0050"
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
        "obs-0004",
        "obs-0007",
        "obs-0010"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0016",
        "obs-0018",
        "obs-0019",
        "obs-0020",
        "obs-0033",
        "obs-0039"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0016",
        "obs-0018",
        "obs-0019",
        "obs-0020",
        "obs-0033",
        "obs-0039"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0050"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x01059f20",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 4,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x01059f20",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x01059f23",
      "count": 12,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
  
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
  "count": 106,
  "instructions": [
    {
      "address": "01059f20",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "01059f23",
      "instruction": "MOV EAX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "01059f27",
      "instruction": "PUSH EBX"
    },
    {
      "address": "01059f28",
      "instruction": "MOV EBX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "01059f2c",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01059f2d",
      "instruction": "MOV EBP,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "01059f31",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01059f32",
      "instruction": "PUSH EDI"
    },
    {
      "address": "01059f33",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01059f34",
      "instruction": "PUSH EBX"
    },
    {
      "address": "01059f35",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01059f36",
      "instruction": "MOV dword ptr [ESP + 0x1c],ECX"
    },
    {
      "address": "01059f3a",
      "instruction": "CALL 0x010568b0"
    },
    {
      "address": "01059f3f",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "01059f41",
      "instruction": "JZ 0x0105a03a"
    },
    {
      "address": "01059f47",
      "instruction": "MOV ECX,dword ptr [EBP + 0x114]"
    },
    {
      "address": "01059f4d",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01059f4f",
      "instruction": "JZ 0x01059f62"
    },
    {
      "address": "01059f51",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "01059f53",
      "instruction": "MOV EAX,dword ptr [EDX + 0xb8]"
    },
    {
      "address": "01059f59",
      "instruction": "PUSH 0x13f94d4"
    },
    {
      "address": "01059f5e",
      "instruction": "CALL EAX"
    },
    {
      "address": "01059f60",
      "instruction": "JMP 0x01059f64"
    },
    {
      "address": "01059f62",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "01059f64",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "01059f66",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "01059f68",
      "instruction": "JZ 0x0105a03a"
    },
    {
      "address": "01059f6e",
      "instruction": "MOVSS XMM0,dword ptr [EBX]"
    },
    {
      "address": "01059f72",
      "instruction": "MOV EDI,dword ptr [EBP + 0x124]"
    },
    {
      "address": "01059f78",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM0"
    },
    {
      "address": "01059f7e",
      "instruction": "MOVSS XMM0,dword ptr [EBX + 0x4]"
    },
    {
      "address": "01059f83",
      "instruction": "MOVSS dword ptr [ESP + 0x18],XMM0"
    },
    {
      "address": "01059f89",
      "instruction": "MOVSS XMM0,dword ptr [EBX + 0x8]"
    },
    {
      "address": "01059f8e",
      "instruction": "MOVSS dword ptr [ESP + 0x1c],XMM0"
    },
    {
      "address": "01059f94",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "01059f96",
      "instruction": "JZ 0x01059faf"
    },
    {
      "address": "01059f98",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "01059f9a",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "01059f9c",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "01059f9e",
      "instruction": "CALL EAX"
    },
    {
      "address": "01059fa0",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "01059fa2",
      "instruction": "MOV EAX,dword ptr [EDX + 0x2c]"
    },
    {
      "address": "01059fa5",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "01059fa7",
      "instruction": "MOV ESI,EDI"
    },
    {
      "address": "01059fa9",
      "instruction": "CALL EAX"
    },
    {
      "address": "01059fab",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "01059fad",
      "instruction": "JZ 0x0105a004"
    },
    {
      "address": "01059faf",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "01059fb3",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "01059fb5",
      "instruction": "MOV EDX,dword ptr [EDX + 0x48]"
    },
    {
      "address": "01059fb8",
      "instruction": "LEA EAX,[ESP + 0x14]"
    },
    {
      "address": "01059fbc",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01059fbd",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01059fbe",
      "instruction": "CALL EDX"
    },
    {
      "address": "01059fc0",
      "instruction": "MOV EDI,dword ptr [EBP + 0x124]"
    },
    {
      "address": "01059fc6",
      "instruction": "CMP EDI,ESI"
    },
    {
      "address": "01059fc8",
      "instruction": "JZ 0x01059feb"
    },
    {
      "address": "01059fca",
      "instruction": "MOV dword ptr [ESP + 0x2c],ESI"
    },
    {
      "address": "01059fce",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "01059fd0",
      "instruction": "JZ 0x01059fda"
    },
    {
      "address": "01059fd2",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "01059fd4",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "01059fd6",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "01059fd8",
      "instruction": "CALL EDX"
    },
    {
      "address": "01059fda",
      "instruction": "MOV ECX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "01059fde",
      "instruction": "MOV ESI,EDI"
    },
    {
      "address": "01059fe0",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01059fe2",
      "instruction": "JZ 0x01059feb"
    },
    {
      "address": "01059fe4",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01059fe6",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01059fe9",
      "instruction": "CALL EDX"
    },
    {
      "a
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
  "original_bytes": 11556,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_receiver\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueToolStrategy*\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"ret 0xc\",\n    \"return_register\": \"AL\",\n    \"return_type\": \"bool\",\n    \"return_width_bytes\": 1,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04 at function entry\",\n        \"load_site\": \"0x01059f2d, `mov ebp, dword ptr [esp + 0x1c]` after `push ebp`\",\n        \"observed_use\": \"The SDK structure cSpaceToolData (size 0x2a0) supplies every field the body touches: +0x114 mpToolOwner, +0x120 mpArea, +0x124 mpBeam and +0x174 mFlags. The callee 0x010568b0 reads the same +0x114 and +0x120 words and the callee 0x01059170 reads the same three, so one object type is proven across three functions.\",\n        \"position\": 1,\n        \"register\": \"EBP\",\n        \"type\": \"cSpaceToolData*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08 at function entry\",\n        \"load_site\": \"0x01059f28, `mov ebx, dword ptr [esp + 0x1c]` after `push ebx`\",\n        \"observed_use\": \"Read as three consecutive floats at +0, +4 and +8 by `movss` at 0x01059f6e, 0x01059f7e and 0x01059f89, copied into a 12-byte stack local, and re-materialised by `flds`/`fstps` at 0x0105a00f-0x0105a022 for the call to 0x01059170. A by-value Vector3 would need four stack words at the call site; the direct caller at 0x0105aa5c-0x0105aa6e pushes exactly three dwords, so the argument is a pointer.\",\n        \"position\": 2,\n        \"register\": \"EBX\",\n        \"type\": \"Vector3*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0c at function entry\",\n        \"load_site\": \"0x01059f23, `mov eax, dword ptr [esp + 0x1c]` after `sub esp, 0x10`\",\n        \"observed_use\": \"Pushed as the last argument to 0x010568b0 at 0x01059f33 and never read again, so it is forwarded unchanged and otherwise unused. The SDK spells the fourth parameter of every sibling virtual `int param_4`.\",\n        \"position\": 3,\n        \"register\": \"EAX\",\n        \"type\": \"int\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 12,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"Single return instruction at 0x0105a043, `C2 0C 00`.\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No differential runtime corpus is available for this virtual, so the beam rebalance ordering and the relationship stamp are static-only evidence.\",\n    \"The SDK address table is provably wrong immediately around this function, which blocks using it to align the vtable and therefore blocks naming the overridden method.\",\n    \"The owning class and the interface slot of this virtual are unresolved, so the function cannot be tied to a named SDK override even though its argument shape matches the cToolStrategy family.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x01059ff8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d3c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01059fff\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b7c160\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01059fed\",\n        \"direction\": \"out\",\n        \"other\": \"0x0104cd50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n       
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
  "body_end": "0105a045",
  "body_span_bytes": 294,
  "body_start": "01059f20",
  "callees": [
    "FUN_00b7c160",
    "FUN_0104cd50",
    "FUN_01059170",
    "FUN_010568b0",
    "Simulator::cRelationshipManager::Get"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01059f20",
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
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_01059f20",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc59f20",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01059f20(void)",
  "size_bytes": 294,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01059f20",
  "vtables": {
    "referenced_by_vtables": [
      "0x0149b8b4",
      "0x0149b810"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "0149b80c"
    },
    {
      "from": "0149b8ac"
    },
    {
      "from": "0149b8fc"
    },
    {
      "from": "0149ba2c"
    },
    {
      "from": "0105aa6f"
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
    "reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20.cpp",
    "reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20.hpp",
    "reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-sim-toolstrategy-01059f20/01059f20.json"
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
  "OpaqueToolStrategy*",
  "Simulator::cSpaceToolData::SpaceToolFlags",
  "Vector3",
  "Vector3*",
  "bool",
  "cGameData__vftable*",
  "cSpaceToolData*",
  "float",
  "int",
  "intrusive_ptr<Simulator::cDefaultAoEArea>",
  "intrusive_ptr<Simulator::cDefaultBeamProjectile>",
  "intrusive_ptr<Simulator::cSpaceToolData>",
  "intrusive_ptr<Simulator::cSpatialObject>",
  "map<pair<unsigned int, unsigned int>, Simulator::cRelationshipData>",
  "uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0149b810",
  "vtable:0x0149b8b4"
]
```

## Conflicts

```json
[]
```
