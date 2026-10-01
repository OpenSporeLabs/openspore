# Reconstruction context 0x00642210

- Status: `partial`
- Content SHA-256: `6b0acce8ad5b68315fb33ace506d8a8319e030b32cc926f46a3afe4eb8d25647`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00642210",
  "phase": "reconstruction",
  "target": "0x00642210"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00642210",
  "package": null,
  "subsystem": "Sporepedia",
  "va": "0x00642210"
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
  "content_sha256": "d0b37290fe61bf35cb5f4e3f6853e810445887c73b210048c741aae281c77fb2",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00642210 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver": "ECX carries the receiver. The machine record states it at INFERRED confidence: receiver {present true, register ECX, provenance vftable_slot_dispatch, bounds_only true, shape null, distinct_offsets 0, offsets [], written_through 0}. In the body itself the receiver is read once -- MOV ESI,ECX at 0x00642211 -- and aliased into ESI so that it survives both calls, because a full call at 0x00642213 whose result lands in EAX would otherwise lose it. That is the same VALUE that goes to 0x00642190 in ECX (unchanged) and to 0x00f47380 on the stack (unchanged), and what MOV EAX,ESI at 0x00642228 writ...",
  "ret_form": "RET 0x4",
  "return_observation": "The record classifies the last write to EAX as aggregate_unknown (RT2) and the envelope as unclassified_in_EAX. The listing says more than that and this package reads only the listing: the single write to EAX is MOV EAX,ESI at 0x00642228, a register-to-register move of the value ESI has held since 0x00642211, so the returned value is the incoming receiver verbatim and 32 bits wide. Both paths to the single reachable RET pass through 0x00642228, so the must-analysis has no uninitialised path. The C type is Receiver *, the width-computable spelling of a 4-byte value the machine shows to be th...",
  "return_register": "EAX",
  "return_semantics": "unclassified_in_EAX",
  "return_type": "Receiver *",
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI"
  ]
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "sporepedia_asset_destroy_00642190",
      "reconstructed": true,
      "va": "0x00642190"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00642213",
      "direction": "out",
      "other": "0x00642190",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642220",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "Receiver *",
    "openspore::reconstruction::pkg_w2_00642210::OptionWord",
    "openspore::reconstruction::pkg_w2_00642210::Receiver",
    "std::size_t",
    "std::uint32_t"
  ],
  "vtables": [
    "vtable:0x013ff648"
  ]
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
  "callees": [
    {
      "name": "sporepedia_asset_destroy_00642190",
      "reconstructed": true,
      "va": "0x00642190"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00642213",
      "direction": "out",
      "other": "0x00642190",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00642220",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x00642190"
  ],
  "scc": {
    "id": "scc-0170",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 12,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 12,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641410",
    "score": 12,
    "symbol": "re_00641410",
    "va": "0x00641410"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641780",
    "score": 12,
    "symbol": "re_00641780",
    "va": "0x00641780"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006417d0",
    "score": 12,
    "symbol": "re_006417d0",
    "va": "0x006417d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641fa0",
    "score": 12,
    "symbol": "sporepedia_predicate_00641fa0",
    "va": "0x00641fa0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648",
      "same_calling_convention"

[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-w2-00642210/w2_00642210.cpp",
    "reconstruction/staging/pkg-w2-00642210/w2_00642210_model_test.cpp",
    "reconstruction/staging/pkg-w2-00642210/w2_00642210_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00642210/00642210.json"
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
    "DECOMPILATION UNAVAILABLE. Both the persisted record and the live bridge report none (04_decompilation state: missing; live attempt ghidra_rest_error, \"Decompilation did not complete\"). Every claim here is from the disassembly listing, the ABI envelope and bytes read back out of the image.",
    "THE CLASS THAT OWNS THE TABLE 0x013ff648, AND WHETHER IT IS A vptr-BACKED VTABLE AT ALL. R1-VFT calls the table it reasons about a sound vptr-backed vftable, and GhidraMCP /read_memory at 0x013ff640 for 24 bytes shows a table whose first slot is this body, but this binary carries no MSVC RTTI and no SDK name is recorded for the table. The receiver determination does not need a class and none is claimed.",
    "THE RECEIVER'S IDENTITY. __thiscall says the receiver arrives in ECX; it does not say what the receiver IS. This body never dereferences it and never adjusts it, and the two entry stubs adjust ECX by 0x10 and 0x14 before arriving, so at least two different base relationships reach 0x00642210. No class, no vtable identity, no receiver type, no object size, no vtable-pointer offset and no field are claimed, and the base relationships are not guessed.",
    "THE RETURNED VALUE'S C TYPE. The machine fixes the WIDTH (4 bytes; MOV EAX,ESI at 0x00642228 is the last write before the sole return on both paths) and the FACT that the value is the receiver. It does not fix the type: Receiver *, uint32_t or any other four-byte spelling are all consistent with it. Receiver * is the declared source-side choice, not a recovered fact.",

[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-00642210/00642210.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00642210/w2_00642210.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00642210/w2_00642210_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00642210/w2_00642210_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-w2-00642210/00642210.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00642210/w2_00642210.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00642210/w2_00642210_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00642210/w2_00642210_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_catego
[TRUNCATED]
```
