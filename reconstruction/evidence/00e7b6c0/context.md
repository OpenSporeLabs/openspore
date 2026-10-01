# Reconstruction context 0x00e7b6c0

- Status: `complete`
- Content SHA-256: `7407e49988aa0210e1a9868ff17d3cdf63d3d20a1c4ae19b0872b1fef2da282e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e7b6c0",
  "phase": "reconstruction",
  "target": "0x00e7b6c0"
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
  "subsystem": "Simulator",
  "va": "0x00e7b6c0"
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
  "content_sha256": "824938b17aec7864cd546469a45d1fc6320b4dbdfd2735b7e74d031ef8ca7873",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

/* WARNING: Enum "Names": Some values do not have unique names */
/* WARNING: Enum "ObjectTYPE": Some values do not have unique names */

void FUN_00e7b630(undefined4 *param_1)

{
  undefined4 uVar1;
  cCellObjectData *cell;
  undefined4 uVar2;
  int iVar3;
  undefined4 *unaff_ESI;
  float10 extraout_ST0;
  undefined1 local_8 [4];
  float local_4;
  
  if ((((*(char *)((int)unaff_ESI + 0x112) != '\x01') &&
       (*(char *)((int)unaff_ESI + 0x113) != '\x01')) && (*(char *)(unaff_ESI + 0x5e) == '\0')) &&
     ((*(char *)((int)unaff_ESI + 0x17f) == '\0' && (*(char *)((int)param_1 + 0x17b) == '\0')))) {
    cell = (cCellObjectData *)FUN_00b72210(*unaff_ESI);
    Simulator__Cell__PlayAnimation
              (cell,(cCellObjectData *)0x0,kAnimIndexCellEatMandNpcBig,cell->mCurrentAnimation);
    local_4 = (float)extraout_ST0;
    uVar1 = *unaff_ESI;
    uVar2 = FUN_00b72160();
    iVar3 = FUN_00b72210(uVar2);
    *(float *)(iVar3 + 0x1c) = local_4;
    *(float *)(iVar3 + 0x20) = local_4;
    *(undefined4 *)(iVar3 + 0x24) = 0x20;
    *(undefined4 *)(iVar3 + 0x28) = uVar1;
    *(undefined4 *)(iVar3 + 0x2c) = 0;
    *(undefined4 *)(iVar3 + 0x30) = 0xffffffff;
    *(undefined4 *)(iVar3 + 0x34) = 0xffffffff;
    *(undefined4 *)(iVar3 + 0x38) = 0;
    *(undefined4 *)(iVar3 + 0x3c) = 0;
    *(undefined4 *)(iVar3 + 0x40) = 0;
    *(undefined4 *)(iVar3 + 0x44) = 0;
    *(undefined4 *)(iVar3 + 0x48) = DAT_016b3c28;
    *(undefined4 *)(iVar3 + 0x4c) = DAT_016b3c2c;
    *(undefined4 *)(iVar3 + 0x50) = DAT_016b3c30;
    *(undefined4 *)(iVar3 + 0x54) = DAT_016b3c28;
    *(undefined4 *)(iVar3 +
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": false,
  "hidden_this_register": null,
  "ordinary_stack_argument_slots": 1,
  "receiver": "NONE. Undetermined with reason ecx_read_without_deref. ECX is read at 0x00e7b68b as a LOAD out of memory (MOV ECX,[EAX+0x1b0]) and immediately PUSHed at 0x00e7b691 as the first of 0x00e6d200's four ordinary stack arguments. It is read and written seventeen times across the body and dereferenced nowhere. The body works through EAX, EBX, EDX, EDI, EBP and ESI.",
  "ret_form": "RET",
  "return_register": "ST0",
  "return_semantics": "float_or_x87_in_ST0",
  "return_type": "void",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:WARN"
  ],
  "types": [
    "openspore::reconstruction::pkg_w2_00e7b6c0::CalleeTerminator00e7b6c0",
    "openspore::reconstruction::pkg_w2_00e7b6c0::RecordValueSource00e7b6c0",
    "openspore::reconstruction::pkg_w2_00e7b6c0::RecordWrite00e7b6c0",
    "std::size_t",
    "std::uint32_t",
    "std::uint8_t",
    "void",
    "void, and that is a reading of the listing rather than a recovered fact. No instruction places a value in a return register at the single return site. EAX's last write is 0x00e7b79b, whose only consumer is the call that follows it; XMM0's last write is the XORPS at 0x00e7b6c5, consumed by the two MOVSS at 0x00e7b6ea and 0x00e7b6ef. The machine record's return_register ST0 with return_semantics float_or_x87_in_ST0 is at confidence APPROXIMATION under rule RT1, whose stated basis is that an x87 or SSE instruction appears in the body; it is carried in the header as data and is NOT adopted. The x87 balance is a fact of the listing and it points the same way: the body pushes twice and pops three times, so whatever ST0 held on entry is consumed and nothing is left."
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0552",
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
  "files": [
    "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_entry.cpp",
    "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_model_test.cpp",
    "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00e7b6c0/00e7b6c0.json"
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
    "How many x87 registers does 0x00e6d200 leave, and with what values? The FSTP at 0x00e7b69b pops one this body never pushed, so its value is whatever ST0 held on entry. The model test therefore takes the ST0 content as a PARAMETER and pins only the ORDER of the two stores, which are the same value because FST does not pop.",
    "Is the machine record's ST0/float_or_x87_in_ST0 return claim wrong, or does this body leave a value in ST0 that the listing does not show? The body pops three x87 registers and pushes two, which is the opposite of leaving a return value, and this package adopts void on the listing's own evidence. The divergence is recorded, not resolved.",
    "What is 0x00e6d200's ECX, held in the callee's hidden register, and what does it do? Its own body WAS decompiled (Simulator::Cell::PlayAnimation) but this package claims nothing about it beyond the four stack words the listing pushes and the stack discipline the listing shows.",
    "What is 0x016b3c04, and what are 0x016b3c28, 0x016b3c2c, 0x016b3c30, 0x015a7c4c, 0x015a7c50, 0x015a7c54 and 0x015a7c58? Thirteen loads and no store; the model test plants words in both pages and checks each reaches the record, but nothing names them.",
    "What is at the base EAX, and what do the twenty-six written displacements mean? Offsets 0x04..0x78 are located, two of the writes are single-byte, and the run 0x0c..0x1b is untouched -- but no type, member, size or layout is claimed, because the base is 0x00b72210's result and nothing in evidence describes it.",
    "What i
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-00e7b6c0/00e7b6c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_entry.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_types.hpp', 'source_class': 'committed_artifact'}`

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
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-w2-00e7b6c0/00e7b6c0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_entry.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_ty
[TRUNCATED]
```
