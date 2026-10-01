# Reconstruction context 0x01021090

- Status: `partial`
- Content SHA-256: `e0f4ecb2f629d7ba45cfeadc785c727c483cd54c780cd3e31d568358e2e7662a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01021090",
  "phase": "reconstruction",
  "target": "0x01021090"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_01021090",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x01021090"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "577e26ba54b6a8092af630b15b488319161a062964d6bcfcd60c2f173fff9234",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_01021090(void)

{
  return *(undefined4 *)(Simulator__sSpacePlayerData + 0x18);
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "UNKNOWN, and unknowable from this body. The derived ABI record abstains (`verdict: ABI_UNKNOWN`, `abstained_because: no_discriminator: no stack-argument read and no positive receiver evidence`, `conventions.calling_convention: null`, `confidence: UNKNOWN`). With zero stack-argument slots and no receiver, this body is byte-identical under __cdecl, __stdcall, __thiscall and __fastcall (`inferences.C10`). The reconstruction declares a zero-parameter function, which is what the machine fixes, and asserts no convention beyond that.",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "none. The receiver record reads present=false, register=null, offsets=[], written_through=0, and inference R2 records that ECX is never read in any form.",
  "ret_form": "RET (0x01021098, byte 0xc3, no imm16)",
  "return_note": "32-bit unsigned scalar",
  "return_register": "EAX",
  "return_semantics": "the 32-bit word STORED at [Simulator::sSpacePlayerData + 0x18], copied bit for bit into EAX. The second load is the last write to EAX before the RET, so the returned word is what EAX carries.",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aea3d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aed2c0"
    },
    {
      "name": "FUN_00b1f9d0",
      "reconstructed": false,
      "va": "0x00b1f9d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b68090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb9eb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbcf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcd480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcece0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd9a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdc8a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdff50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be2110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be9b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf2170"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00aea10b",
      "direction": "in",
      "other": "0x00ae9f50",
      "reference_type": "direct-cal
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "32-bit unsigned scalar",
    "SpacePlayerData* (SDK IMPORTED)"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
    "validated": 0
  },
  "semantic": {}
}
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aea3d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aed2c0"
    },
    {
      "name": "FUN_00b1f9d0",
      "reconstructed": false,
      "va": "0x00b1f9d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b68090"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb9eb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbcf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcd480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcece0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd9a80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdc8a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdff50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be2110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be9b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf2170"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfc900"
    },
    {
      "name": null,
    
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 6,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 6,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [],
  "handoffs": [],
  "metadata": []
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "Can any recorded call site reach this entry with a null global? The entry faults in that state by construction; whether it is reachable in practice is unestablished, and it is the one fact that would make this accessor unsafe to call early in startup.",
    "Do the ~100 recorded callers use the returned value as an ID (compare against -1, index a table) or as an address? Not sampled here: the ID reading rests on the export and the lifecycle, not on caller behaviour.",
    "What class is the object at 0x016dda8c? There is no MSVC RTTI in this binary, no instruction in this body names a type, and the pointee is reached only through this one offset from here.",
    "What is the numeric domain of the empire ID - a dense index, a handle, a database key? The -1 sentinel at both allocation and teardown says only 'no empire'.",
    "Which calling convention did the original source declare? The body cannot distinguish __cdecl, __stdcall, __thiscall and __fastcall, and the ABI record abstains. A zero-parameter declaration is used because it is what the machine fixes.",
    "Who else writes +0x18? The committed lifecycle records 0x01021d40 writing -1 at allocation and 0x01022460 resetting to -1 at teardown, but nothing here enumerates every writer in the binary, and no setter-shaped entry is claimed to exist."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
    },
    {
      "mode": "derived",
      "ref": "tools/reconstruction_tooling/abi_infer.py",
      "source_class": "derived"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /decompile_function @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/research/source-reconstruction-manifest.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/triage/queue-f0e310e0-v6.json",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
    "RETURN SEMANTICS",
    "EVIDENCE COVERAGE"
  ]
}
```
