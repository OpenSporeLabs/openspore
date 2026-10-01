# Reconstruction context 0x0052e650

- Status: `partial`
- Content SHA-256: `6a84b59c2c4612b67817597d8884bd403ae8e856024b4165688fec7ba47da104`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0052e650",
  "phase": "reconstruction",
  "target": "0x0052e650"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_0052e650",
  "package": null,
  "subsystem": "Editor",
  "va": "0x0052e650"
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
  "content_sha256": "75490d58ea76d142019f7e12fbe6d17858c5c78d639f86c598e07b9d948cd16e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0052e650 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall, callee stack cleanup (one 4-byte word, popped by the callee). The machine-derived ABI record (evidence pack category abi_derived) DETERMINES the convention: conventions.calling_convention = __thiscall, conventions.confidence = INFERRED, conventions.candidate_conventions = [__thiscall], conventions.ambiguities = []. The cleanup is separately OBSERVED and independent of the convention: cleanup.bytes = 4, cleanup.side = callee, cleanup.evidence = \"ret 0x4\". The reconstructed entry is a naked __thiscall member, so the source span carries a __thiscall token and the entry's own `ret $...",
  "ordinary_stack_argument_slots": 1,
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
  "receiver": "ECX, read twice (PUSH ECX at 0x0052e653, MOV dword ptr [EBP + -0x4],ECX at 0x0052e654) and never dereferenced. The record's receiver sub-record now states present = true, register = ECX, provenance = vftable_slot_dispatch, confidence = INFERRED, bounds_only = true, shape = null, distinct_offsets = 0, written_through = 0. What is proven is that ECX carries the receiver and that the receiver is one 4-byte word wide (the width of PUSH ECX). What is NOT proven, and is not claimed, is the receiver's identity: no class, no receiver type, no shape, no object size, no vtable-pointer offset and no f...",
  "recei
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
      "va": "0x0055bfb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0055c3c0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0055c2ca",
      "direction": "in",
      "other": "0x0055bfb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0055c633",
      "direction": "in",
      "other": "0x0055c3c0",
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
    "high - VOID_PROVEN from a complete, fully parsed listing with zero EAX writes, not from a string comparison",
    "openspore::reconstruction::pkg_w2_0052e650::CleanupSide52e650",
    "openspore::reconstruction::pkg_w2_0052e650::ConventionVerdict52e650",
    "openspore::reconstruction::pkg_w2_0052e650::MachineEntry52e650",
    "openspore::reconstruction::pkg_w2_0052e650::MachineExit52e650",
    "openspore::reconstruction::pkg_w2_0052e650::MemoryImage52e650",
    "openspore::reconstruction::pkg_w2_0052e650::ReceiverRegister52e650"
  ],
  "vtables": [
    "vtable:0x013ef620",
    "vtable:0x013ef7f0",
    "vtable:0x013f2194",
    "vtable:0x013f21d8",
    "vtable:0x013f2698",
    "vtable:0x013f276c",
    "vtable:0x013f2d68",
    "vtable:0x013f8be0",
    "vtable:0x013f8cd4",
    "vtable:0x013f9ab8",
    "vtable:0x014123b4",
    "vtable:0x01412454"
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
      "count the distinct classes whose vtable slot resolves to this address, and the slot index each uses. The derived record attributes one table and slot (0x013ef620, slot 5) out of 199 and leaves the other 198 unattributed; the binary has no MSVC RTTI. This is the only remaining blocker to naming a class, and it is the one the vftable_slot_dispatch rule works around rather than answers",
      "observe whether the pushed 4-byte word is read by anything at all, which would place this body in a fold group whose remaining members give the argument a type",
      "observe whether the receiver arriving in ECX is always an adjusted base pointer or whether some call site passes a subobject pointer directly, which would bound how many classes are folded onto this one address"
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
      "va": "0x0055bfb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0055c3c0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0055c2ca",
      "direction": "in",
      "other": "0x0055bfb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0055c633",
      "direction": "in",
      "other": "0x0055c3c0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0052",
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
      "shared_vtable:vtable:0x013f2194,vtable:0x013f21d8"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 10,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f2194,vtable:0x013f21d8"
    ],
    "package": "subobject-forward-0051e380",
    "score": 10,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458024,vtable:0x014599e8"
    ],
    "package": "pkg-swarm-w1-00a85070",
    "score": 10,
    "symbol": "re_00a85070",
    "va": "0x00a85070"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458788"
    ],
    "package": "pkg-swarm-w2-00a980b0",
    "score": 10,
    "symbol": "re_00a980b0",
    "va": "0x00a980b0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458788"
    ],
    "package": "pkg-swarm-w2-00a98200",
    "score": 10,
    "symbol": "re_00a98200",
    "va": "0x00a98200"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 6,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 6,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 6,
    "symbol": "re
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650.cpp",
    "reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650.hpp",
    "reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-0052e650/0052e650.json"
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
    "Does anything read the dead frame local? The listing shows no read inside this body, so a read can only come from outside the frame's lifetime - which no x86 code can do - or from an aliased frame this package cannot see. The store is dead in this body; whether it is a compiler artefact of a larger original statement is not observable from 13 bytes.",
    "What is the pushed 4-byte word for? It is a data address (0x013f4ac0) at one call site and a register (EDX) at the other, and this body never reads it, so its meaning belongs to the fold group this address is part of, not to this body. Under __thiscall the word is an ordinary stack argument of an unnamed type; the callee pops it and never looks at it.",
    "What is the receiver? __thiscall settles that ECX carries it and vftable_slot_dispatch settles why, but nothing settles what it is. The body reads the word, stores it in a dead frame slot and never dereferences it, and the record states bounds_only with shape null, so no type, no object size and no field offset is available from this target. Establishing it needs the class that owns one of the 199 referencing vftables - R1-VFT names 0x013ef620 slot 5 as the evidence but a slot is not a class - and not more analysis of these 13 bytes.",
    "Which classes are folded onto this address? The derived record counts 199 sound vptr-backed vftables holding it and attributes one of them (0x013ef620, slot 5) as its receiver evidence; the remaining 198 are named by neither table nor slot here, the binary has no MSVC RTTI, and 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-0052e650/0052e650.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-w2-0052e650/0052e650.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  
[TRUNCATED]
```
