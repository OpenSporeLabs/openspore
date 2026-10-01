# Reconstruction context 0x005c8480

- Status: `partial`
- Content SHA-256: `28ecde727320b1d6e33f7f75d374be2e4e2767984a4bfd043e46ef5c831006c3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005c8480",
  "phase": "reconstruction",
  "target": "0x005c8480"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x005c8480"
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
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "18db9dded0e9b27eaa5071257a74198e842498ca3711cd167c51f051dd0b6b01",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005c8480 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, copied to EDI at 0x005c8487; every receiver access in the body is [EDI + disp]",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "no MOV to EAX in either epilogue; the last EAX written on the grow arm is the biased cursor at 0x005c8597, which is immediately stored to [EDI + 4] at 0x005c85bd rather than returned.",
  "return_register": "none (EAX carries the allocator result and the running memcpy cursor but is not returned as a value)",
  "return_semantics": "no register result. The observable effects are the rewritten receiver triple and, on the in-capacity arm, an overwrite of the caller's *second argument* through the pointer it holds.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "offset_in_callee": "[ESP + 0x1c] with ESP lowered 0x18",
      "read_by": "0x005c8495: MOV EBP,dword ptr [ESP + 0x1c] (grow arm re-read at 0x005c8550)",
      "role": "the append/insert position, a slot address; both inspected callers pass the receiver's own `last` pointer",
      "slot": 1,
      "width_bytes": 4
    },
    {
      "offset_in_callee": "[ESP + 0x20] with ESP lowered 0x18",
      "read_by": "0x005c8491: MOV ECX,dword ptr [ESP + 0x20] (grow arm re-read at 0x005c8571)",
      "role": "a pointer to a value slot; both inspected callers pass the address of a caller stack slot holding the new value",
      "slot": 2,
   
[TRUNCATED]
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
      "va": "0x00586410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cb80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c21d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c22b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c2390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c5f00"
    },
    {
      "name": "palette_safe_wave11_load_page_state_005c85d0",
      "reconstructed": true,
      "va": "0x005c85d0"
    },
    {
      "name": "palette_page_construct_005c9230",
      "reconstructed": true,
      "va": "0x005c9230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005e04d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062bb40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062ce00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062ec90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062efb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f9f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00631df0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006338a0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00586510",
      "direction": "in",
     
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "allocator cookie / size",
    "payload pointer",
    "pointer to the first slot (nullable)",
    "pointer to the slot one past the capacity",
    "pointer to the slot one past the last used slot (nullable)",
    "void"
  ],
  "vtables": []
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
      "No original-process trace exists for 0x005c8480; every claim is static and the Cell stage has never been entered in any recorded run.",
      "The capacity*16 allocation size and the null-block overflow path can only be confirmed as intentional or as defects by a run that exercises them.",
      "The payload's vtable and therefore the meanings of slots +0x4 and +0x8 require a run with a live editor or palette session.",
      "Whether the in-capacity arm is ever reached with an interior position can only be settled by instrumenting the 19 uninspected callsites or by a run; the two inspected ones never reach it."
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cb80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c21d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c22b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c2390"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005c5f00"
    },
    {
      "name": "palette_safe_wave11_load_page_state_005c85d0",
      "reconstructed": true,
      "va": "0x005c85d0"
    },
    {
      "name": "palette_page_construct_005c9230",
      "reconstructed": true,
      "va": "0x005c9230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005e04d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062bb40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062ce00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062ec90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062efb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f9f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00631df0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006338a0"
    },
    {
      "name": null,
      "reconstructed": false,
   
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE11",
    "score": 5,
    "symbol": "palette_safe_wave11_load_page_state_005c85d0",
    "va": "0x005c85d0"
  },
  {
    "match_basis": [
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-15-EDITOR-SUPPORT",
    "score": 5,
    "symbol": "palette_page_construct_005c9230",
    "va": "0x005c9230"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_scalar_00428060",
    "va": "0x00428060"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_paint_commit_0043ac40",
    "va": "0x0043ac40"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "model_parts_apply_properties_00447150",
    "va": "0x00447150"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "pair_vector_insert_004786e0",
    "va": "0x004786e0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "edit
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b00/slot_vector_005c8480.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b00/slot_vector_005c8480.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b00/005c8480.json"
  ]
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
    "Is the container an eastl::vector? The +0x160 field correspondence says a vector of pointers, but the spare slot and the cookie-guarded release are not standard vector behaviour, so the SDK type is a candidate and not an identification.",
    "Is the in-capacity arm reachable with a position strictly inside the array by any caller? Both inspected callers pass `last` and take the grow arm. If some of the other 19 callers pass an interior position, the argument-bound mismatch between 0x005c1dc0's loop and the hole position becomes live, and the arm's element algebra must be re-derived.",
    "No original-process trace exists for 0x005c8480; every claim is static and the Cell stage has never been entered in any recorded run.",
    "The 19 uninspected callers include four in the 0x005c2xxx range that the briefing attributes to ENGINE_IMPLEMENTATION. Their argument shapes, and therefore whether any of them uses the in-capacity arm, are not established.",
    "The capacity*16 allocation size and the null-block overflow path can only be confirmed as intentional or as defects by a run that exercises them.",
    "The payload's vtable and therefore the meanings of slots +0x4 and +0x8 require a run with a live editor or palette session.",
    "What are the two NULL arguments at 0x005c851c and 0x005c851e to 0x00f473a0? The shim reorders six parameters and the underlying 0x009289f0 signature was not read, so their positions are unknown.",
    "What do vtable slots +0x4 and +0x8 actually do -- reference counting, slot-change notificat
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b00/005c8480.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b00/slot_vector_005c8480.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b00/slot_vector_005c8480.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b00/005c8480.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b00/slot_vector_005c8480.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b00/slot_vector_005c8480.hpp",
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
 
[TRUNCATED]
```
