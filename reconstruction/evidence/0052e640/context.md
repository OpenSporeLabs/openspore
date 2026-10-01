# Reconstruction context 0x0052e640

- Status: `partial`
- Content SHA-256: `68c56c2d77a5bbd9e2efec4d8a8779f921bccbb1761eef7887569cb8361920e7`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0052e640",
  "phase": "reconstruction",
  "target": "0x0052e640"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_0052e640",
  "package": null,
  "subsystem": "Editor",
  "va": "0x0052e640"
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
  "content_sha256": "18c11d67b1844222f8536ddec6cf9c95eeb068c14a8cd874a74eb5dfe69d5bf6",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0052e640 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall, with callee stack cleanup: THREE 4-byte stack words, 12 bytes in all, popped by the callee. The machine-derived ABI record (evidence pack reconstruction/evidence/0052e640/evidence.json, category abi_derived) DETERMINES the convention rather than abstaining: conventions.calling_convention = __thiscall, conventions.confidence = INFERRED, conventions.candidate_conventions = [__thiscall], conventions.ambiguities = []. It does so in two steps it records separately. R1-VFT (INFERRED) puts the receiver in ECX: 0x0052e640 is slot 8 of the sound vptr-backed vftable at 0x013f2194, one of ...",
  "ordinary_stack_argument_slots": 3,
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
    },
    {
      "entry_offset": "entry_ESP+0x8",
      "observed": false,
      "ordinal": 2,
      "read": false,
      "size_inferred": false,
      "sizes": [
        4
      ],
      "source": "ret_immediate",
      "written": false
    },
    {
      "entry_offset": "entry_ESP+0xc",
      "observed": false,
      "ordinal": 3,
      "read": false,
      "size_inferred": false,
      "sizes": [
        4
      ],
      "source": "ret_immediate",
      "written": false
    }
  ],
  "receiver": "ECX carries the receiver, at INFERRED confidence, with the machine's own label for how it determined that: receiver.provenance = vfta
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
      "va": "0x0050a0a0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0050a468",
      "direction": "in",
      "other": "0x0050a0a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0050a5d6",
      "direction": "in",
      "other": "0x0050a0a0",
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
  "types": [],
  "vtables": [
    "vtable:0x013f2194",
    "vtable:0x013f21d8",
    "vtable:0x013f2698",
    "vtable:0x013f276c",
    "vtable:0x013f2d68",
    "vtable:0x01412454",
    "vtable:0x01413048",
    "vtable:0x01414614",
    "vtable:0x01414918",
    "vtable:0x01453254",
    "vtable:0x01453998",
    "vtable:0x01458024"
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
      "No original-process trace exists in this repository for 0x0052e640, so every claim in this record is static. A differential run under Wine must confirm the answer is still 0 in the shipping build and that no runtime patch retargets the address.",
      "One of the .rdata slots that point here must be observed being called with a concrete receiver before any owning class or slot offset can be named. The __thiscall determination does not satisfy this gate: it fixes the register the receiver arrives in, not the object behind it.",
      "The INFERRED confidence of the convention and of the receiver register must not be reported as OBSERVED without a runtime observation of one of these vftable slots being called with a concrete receiver, which is the evidence the R1-VFT rule names as its own basis and the evidence a trace would supply directly."
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
      "va": "0x0050a0a0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0050a468",
      "direction": "in",
      "other": "0x0050a0a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0050a5d6",
      "direction": "in",
      "other": "0x0050a0a0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0051",
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
    "reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero.cpp",
    "reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero.hpp",
    "reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-0052e640/0052e640.json"
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
    "Are the three popped dwords really three parameters? The derived record marks all three observed=false and the caller corroborates the count by pushing three, but the body reads none of them, so the count is the popped area rather than a read parameter count. The reconstruction keeps three because `ret 0xc` pops three, not because three parameters were proven.",
    "Does the JNZ that follows each call site ever get a live value? Both are statically dead in this build, so no differential trace of the original process exists that could show the answer being used.",
    "Is the C return type bool, unsigned char or std::uint8_t? The machine fixes only the width (one byte of EAX, upper 24 bits undefined) and the value (0). The reconstruction uses std::uint8_t; the choice is source-side and is not verified.",
    "Is the address a compiler-folded COMDAT shared by several unrelated 'return false' defaults, or one class's default emitted once? Both fit every observation, including the two adjacent equal slots and the 25-table membership count.",
    "No original-process trace exists in this repository for 0x0052e640, so every claim in this record is static. A differential run under Wine must confirm the answer is still 0 in the shipping build and that no runtime patch retargets the address.",
    "One of the .rdata slots that point here must be observed being called with a concrete receiver before any owning class or slot offset can be named. The __thiscall determination does not satisfy this gate: it fixes the register the rec
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-0052e640/0052e640.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-w2-0052e640/0052e640.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "req
[TRUNCATED]
```
