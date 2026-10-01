# Reconstruction context 0x00b25f40

- Status: `partial`
- Content SHA-256: `e95e50bde56a2452f83c80aa3dca0d1a04fa747c7a3e65d191781c59414e4611`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b25f40",
  "phase": "reconstruction",
  "target": "0x00b25f40"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b25f40",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b25f40"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "fa248bdf753c73bf31de3d21a6cab79b7e9d5b2305fa11c4a468de9d78a84d4d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b25f40 failed: Decompilation did not complete. Reason: ",
      "mode": "LIVE",
      "status": "unavailable"
    }
  ],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "callee-cleans (RET 0x4). The persisted ABI record names __thiscall and the derived record names __stdcall; both describe callee cleanup and neither is discriminated by the listing, which never reads or writes ECX. The source declares the callee-cleans convention and claims nothing further.",
    "thiscall"
  ],
  "hidden_this_register": "ECX",
  "hidden_this_type": "NounProjection* receiver forwarded to 0x00b21340",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    "{'address_at_entry': 'entry_ESP+0x4', 'listing_reads': '0x00b25f84 `3b 44 24 14` CMP EAX,[ESP+0x14]; at that point ESP is entry_ESP-0x10 after the four register pushes, so [ESP+0x14] is exactly entry_ESP+0x4', 'use': \"compared whole against the identity probe's 32-bit result; never written, never address-taken\", 'width_bytes': 4}",
    "{'entry_offset': 'ESP+0x04', 'name': 'identity', 'position': 1, 'type': 'std::uint32_t', 'width_bytes': 4}"
  ],
  "receiver": "ECX is never read and never written by the body (the derived ABI record states the same absence: 'ECX is never read in any form, so there is no register receiver'). The word is forwarded unchanged to 0x00b21340, which copies ECX to ESI at 0x00b21346 (`8b f1` MOV ESI,ECX). No receiver type is claimed.",
  "return_note": "borrowed candidate pointer or null",
  "return_register": "EAX",
  "return_type": "NounObject*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "call
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    }
  ],
  "callers": [
    {
      "name": "FUN_00b25fb0",
      "reconstructed": false,
      "va": "0x00b25fb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b262c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35b80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b677e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b682a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6baf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b80b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bccf20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcd630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd5ea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdb3b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdd120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdde70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be11f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be1820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be1860"
    }
  ],
  "edge_rows": [
    {
      "call
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:PASS"
  ],
  "types": [
    "NounObject",
    "NounObject* borrowed candidate pointer or null",
    "NounObjectVtable",
    "NounProjection",
    "NounProjection* receiver forwarded to 0x00b21340",
    "NounProjectionLookupPort",
    "NounProjectionVector",
    "std::uint32_t"
  ],
  "vtables": [
    "vtable:0x00000000"
  ]
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "Each candidate pointer and vtable must be readable, and vtable+0x4c must point to a callable identity probe.",
      "Every candidate reached must have a readable function table whose +0x4c word is a callable probe; the body has no guard on any of these.",
      "The container returned by 0x00b21340 must have readable +0x04 and +0x08 words and a span whose arithmetic shift by two yields a usable count.",
      "The five pushed words and 0x00b21340's own behaviour require original-process observation; nothing about them is established statically here.",
      "The fixed callback words and 0x00b21340's map/list behavior require original-process observation.",
      "The hidden receiver word must be valid for whatever 0x00b21340 does with it; this body does not read it, so nothing here constrains it.",
      "The lifetime of a returned candidate is owned by the container and its callees, not by this body, which performs no AddRef, Release, allocation or store.",
      "The ownership and lifetime of returned candidate objects remain external to this function.",
      "The receiver must be valid for the existing 0x00b21340 projection/list layout.",
      "The returned vector must have readable +0x04 and +0x08 words and a valid positive or nonpositive span."
    ],
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
  "callees": [
    {
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "FUN_00b25fb0",
      "reconstructed": false,
      "va": "0x00b25fb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b262c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35b80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b677e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b682a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6baf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b80b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bccf20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bcd630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd5ea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdb3b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdd120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bdde70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be11f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be1820"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be1860"
    },
    {
  
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:NounProjection,NounProjectionVector",
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 9,
    "symbol": "pkg11_sim_core_00b21340",
    "va": "0x00b21340"
  },
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
  "metadata": [
    "reconstruction/metadata/pkg13-c2-tribe-civilization/00b25f40.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x00b21340",
        "0x00b21340",
        "0x00acd9a0",
        "0x00acd9a0",
        "0x00acd9a0",
        "0x00ace2c0",
        "0x00ace2c0",
        "0x00ace2c0",
        "0x00b25f40",
        "0x00b25f40",
        "0x00ba0080",
        "0x00ba0080",
        "0x00ba0080",
        "0x00bf9820",
        "0x00bf9820",
        "0x00ba8420"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:0",
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
        "0x00e63560",
        "0x00e63560",
        "0x00acd9a0",
        "0x00ace2c0",
        "0x00b25f40",
        "0x00ba0080",
        "0x00bf9820",
        "0x00e5c780",
        "0x00551240",
        "0x0067dd90",
        "0x00e66280",
        "0x00e66840",
        "0x00e63560",
        "0x00e5c780",
        "0x00e63560",
        "0x00571f80"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.j
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-c2-tribe-civilization/00b25f40.json', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
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
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg13-c2-tribe-civilization/00b25f40.json",
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
