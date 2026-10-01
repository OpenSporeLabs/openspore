# Reconstruction context 0x00a98400

- Status: `partial`
- Content SHA-256: `51d31632cc8588ed31f80fca071d99c6f838ce2346ef8fd59f666476d4bca872`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00a98400",
  "phase": "reconstruction",
  "target": "0x00a98400"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00a98400",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00a98400"
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
  "content_sha256": "3d06dda746d820601d36ebdf344e4a909108b992195796b1be717e08d101c1ab",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00a98400 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 2,
  "receiver": "ECX carries the receiver. The machine record states it at INFERRED confidence: receiver {present true, register ECX, provenance vftable_slot_dispatch, bounds_only true, shape null, distinct_offsets 0, offsets [], written_through 0}. In the body itself the receiver is read once -- MOV ESI,ECX at 0x00a98427 -- and aliased into ESI so that it survives all three calls. That alias is used exactly once, and only to form an ADDRESS: LEA ECX,[ESI+0x18] at 0x00a98467 hands receiver+0x18 to 0x00537dc0 as that callee's hidden receiver. There is no load and no store through the receiver in any register...",
  "ret_form": "RET 0x8",
  "return_observation": "The model classifies the return as APPROXIMATION in XMM0 with register_class float_or_x87, and the envelope's own prose is the same. The listing supports a narrower and different statement: the sole return site is 0x00a98473, and no instruction between 0x00a9846a and it writes any register a caller could read a value out of. The C type is void, chosen on that basis; void, float, std::uint32_t and Receiver * are all consistent with the machine width record because there is no width record to contradict them -- the register is written by loads, not by a value placed for the caller.",
  "return_register": "XMM0",
  "return_semantics": "float_or_x87_in_XMM0",
  "return_type": "void",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanu
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00a9844f",
      "direction": "out",
      "other": "0x0041cb40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00a9846a",
      "direction": "out",
      "other": "0x00537dc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00a9845d",
      "direction": "out",
      "other": "0x00537f40",
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
    "openspore::reconstruction::pkg_swarm_w2_00a98400::Receiver",
    "std::size_t",
    "std::uint32_t",
    "void"
  ],
  "vtables": [
    "vtable:0x01458788"
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
  "callees": [],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00a9844f",
      "direction": "out",
      "other": "0x0041cb40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00a9846a",
      "direction": "out",
      "other": "0x00537dc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00a9845d",
      "direction": "out",
      "other": "0x00537f40",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0341",
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
      "shared_vtable:vtable:0x01458788",
      "same_calling_convention"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 12,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458788",
      "same_calling_convention"
    ],
    "package": "subobject-forward-0051e380",
    "score": 12,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458788",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00a980b0",
    "score": 12,
    "symbol": "re_00a980b0",
    "va": "0x00a980b0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458788",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00a98200",
    "score": 12,
    "symbol": "re_00a98200",
    "va": "0x00a98200"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458788"
    ],
    "package": "pkg-w2-0052e640",
    "score": 10,
    "symbol": "reconstruct_0052e640",
    "va": "0x0052e640"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458788"
    ],
    "package": "pkg-w2-0052e650",
    "score": 10,
    "symbol": "reconstruct_0052e650",
    "va": "0x0052e650"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-editor-w1-0057d6f0",
    "score": 8,
    "symbol": "re_0057d6f
[TRUNCATED]
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
    "DECOMPILATION UNAVAILABLE. Both the persisted record and the live bridge report none (the evidence pack's decompilation category reports availability missing and no persisted or live decompilation for this target). Every claim here is from the disassembly listing, the ABI envelope, and bytes and terminators read back out of the image.",
    "THE CLASS THAT OWNS THE TABLE 0x01458788, AND WHETHER IT IS A vptr-BACKED VTABLE AT ALL. R1-VFT calls the table it reasons about a sound vptr-backed vftable, and GhidraMCP /read_memory at 0x01458770 for 48 bytes shows seven consecutive .text words of which this body is the seventh, but this binary carries no MSVC RTTI and no SDK name is recorded for the table. The receiver determination does not need a class and none is claimed. The other six words are transcribed in the staging header as bytes at an address, and nothing is inferred from them beyond their being code addresses.",
    "THE MACHINE RECORD'S STACK-ARGUMENT LIST IS INCOMPLETE, AND THIS PACKAGE COMPLETES IT RATHER THAN COPYING IT. abi_derived.stack_arguments enumerates one slot (entry_ESP+0x8, ordinal 2) with gaps 1 and abstains with \"flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path\". This package reads two stack arguments, at entry_ESP+0x4 and entry_ESP+0x8, on the evidence of the three callees' own RET 0x4 terminators and of the frame arithmetic closing at exactly the entry stack pointer. The reading is stated with its evidence in observed_original_abi.record_incompleteness and the rec
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
