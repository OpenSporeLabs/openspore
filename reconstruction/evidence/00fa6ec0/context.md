# Reconstruction context 0x00fa6ec0

- Status: `partial`
- Content SHA-256: `9112dd162388cf525d1ebd8289a3e9c3ea006b4860cd41db2c807369bb9babf8`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00fa6ec0",
  "phase": "reconstruction",
  "target": "0x00fa6ec0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00fa6ec0",
  "package": "pkg-swarm-w1-00fa6ec0",
  "subsystem": "Sporepedia",
  "va": "0x00fa6ec0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "da20f200fcca794b2aa295b7de718e432cc11cfd761a75a176990cf173ecc7d1",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00fa6ec0 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_note": "The WIDTH and the bit pattern are machine-fixed: the LAST write to EAX in the whole body is 0x00fa6f13 IMUL EDI, the low 32 bits of the second block's 64-bit signed product, so the value comes back in EAX and is 32 bits wide, and no 64-bit or floating claim is compatible with those bytes. The C SPELLING is a source-side choice: Word is one of several C++ types of that width (std::uint32_t, unsigned int, unsigned long, or a 32-bit typedef of the original source's own vocabulary) and the listing does not choose between them -- which is precisely why abi_derived can classify the register but n...",
  "return_register": "EAX",
  "return_type": "Word",
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "callee",
  "termination": "RET (0x00fa6f37, one byte C3, no immediate)"
}
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
      "callsite": "0x00fa6ed4",
      "direction": "out",
      "other": "0x00f9f770",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa6f07",
      "direction": "out",
      "other": "0x00f9f770",
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
  "globals": [
    "global:PASS"
  ],
  "types": [
    "Word",
    "Word (uint32_t)",
    "openspore::reconstruction::pkg_swarm_w1_00fa6ec0::Element",
    "openspore::reconstruction::pkg_swarm_w1_00fa6ec0::ElementVector",
    "openspore::reconstruction::pkg_swarm_w1_00fa6ec0::Owner",
    "openspore::reconstruction::pkg_swarm_w1_00fa6ec0::Word"
  ],
  "vtables": [
    "vtable:0x01490be8"
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
      "callsite": "0x00fa6ed4",
      "direction": "out",
      "other": "0x00f9f770",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa6f07",
      "direction": "out",
      "other": "0x00f9f770",
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
    "id": "scc-0580",
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
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00f999e0",
    "score": 12,
    "symbol": "re_00f999e0",
    "va": "0x00f999e0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-fa0d50-atomic-inc",
    "score": 12,
    "symbol": "FUN_00fa0d50",
    "va": "0x00fa0d50"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa5580",
    "score": 12,
    "symbol": "re_00fa5580",
    "va": "0x00fa5580"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa73c0",
    "score": 12,
    "symbol": "sw1_snap_and_dispatch_00fa73c0",
    "va": "0x00fa73c0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-0104c110",
    "score": 12,
    "symbol": "re_0104c110",
    "va": "0x0104c110"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:Word",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 11,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:Word",
      "same_calling_convention"
    ],
    "package": "pkg
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00fa6ec0/00fa6ec0.json"
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
    "The class name, the method name and the meaning of every receiver word. The binary has no MSVC RTTI, the SDK XML carries no symbol at this address, and the only association available is the transitive vtable classification. Nothing in this package names the class or the method, and the reconstruction names neither.",
    "What the 0x814 counter counts. 0x00fa7220 increments both 0x814 and 0x818 and 0x00fa5040 increments the ranges' last words, so the two counters at 0x814/0x818 are related, but no listing in this set says what either measures.",
    "What the body MEANT. The arithmetic is fixed (last += -(span/0xAC)*0xAC) and its two consequences are fixed (a whole-element range ends with last == first; a drifted one keeps only the residue), but nothing in 40 instructions or in the image says whether the original expression was intended as a truncate-to-boundary, a clear, a shrink, or a mistake. The two sibling methods of the same table bound the idiom without deciding it: 0x00fa7220 does copy(begin+0xAC, last, begin); last -= 0xAC (erase(0)) and 0x00fa5040 does copy(begin+i+1, last, begin+i); last -= 0xAC (erase(i)), and neither is this expression.",
    "What the element's dword at +0xA8 names. It is a 4-byte value the class's search methods compare against a 32-bit argument (0x00fa5080) and 0x00fa7220 reads the dword four bytes below a range's last pointer, which suggests an identifier, but nothing here fixes it. The element's opaque head (0x00..0x37) is likewise untouched by anything in this set -- 0x00f9f620 hands i
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00fa6ec0/00fa6ec0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00fa6ec0/00fa6ec0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
