# Validation 0x00f99980

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00f99980/sw2_00f99980.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 25-instruction listing name the same 3 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x00f99980; the source span names 3 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 25-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 25-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x894, 0x8a4), all of which the record accounts for or the listing is the better witness on; the 25-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=25, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x894, 0x8a4) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x894, 0x8a4), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (25 of 25 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 25-instruction listing lie inside the recovered body span 0x00f99980..0x00f999d7, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 25-instruction body names 1 indirect transfer(s): 0x00f9999f dispatches slot 0x7c through the table word in EDX; the machine parse consumed 25 of 25 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x7c, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `94ad50daa3e7e61d863c2d6cfd6a099c0d4d4a7eccb197d090aad60eb46e0697`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `cd826f507d21c024f42a3737aee17c120e75aacac93acf2264512860f25bf9da`
- Pack digest quoted by the briefing: `94ad50daa3e7e61d863c2d6cfd6a099c0d4d4a7eccb197d090aad60eb46e0697`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- ABI is WARN, and it is fixed rather than fixable from this package: the derived record's verdict is ABI_UNKNOWN because the inference's linear ESP walk ended at +4 on a listing that is not one path, and the record states that reason itself. The model here supplies the per-path frame the walker could not (mechanics.frame_resolution), and the model test measures the frame with two ESP-sampling trampolines, but the verdict is read out of the committed record and no source edit can move it.
- The canonical ABI record cannot be reconciled with any C++ return type, and this package does not try. abi_derived.abi.return_semantics is the machine phrase 'unclassified_in_EAX' and the validator compares the declared return type against it as a string, so RETURN SEMANTICS is a WARN whatever is written. The choice made here is (b) of the wave-1 lesson -- declare void -- and the argument for it is in implementation.return_type_note: no instruction in the 25 has EAX as a destination and all three calls' return words are discarded. The alternative (a), a 32-bit integral return, would be a positive claim that this body produces a value, which the bytes refute. The record's void_possible false is not a counter-argument: abi_infer.py sets that flag only when EAX is never written AND the body contains no call, so it is unset for every body with a call in it, whatever the body returns. No typedef named after the phrase exists in this package.
- The model's emitted code for the transfer at 0x00f999d1 is call+ret rather than the machine's jmp, because no C++ spelling forces the jump and this function needs a frame for the position-independent thunk. Nothing outside the body can distinguish the two shapes -- the callee's return reaches the body's caller either way, and no memory of the body is touched after the transfer -- so case T of the model test asserts the observable consequences (a balanced frame, and the callee receiving the word read before the clear) and the machine's JMP is recorded here rather than claimed. See validation.mutation_checking for the mutation that survives for this reason.
- The unconditional clear of +0x8a4 at 0x00f999a7 cannot be distinguished from a conditional one, and this is provable rather than a gap in the test: on the only path where the two differ the field already holds 0xffffffff, so storing 0xffffffff over it changes no byte. The model test asserts the stronger observable instead (case A: with the sentinel already in place, not one byte of the receiver changes). The mutation that makes the clear conditional survives, and no input can kill it.
- What 0x00692330 is, and what 0x00690120 does after its branch at 0x00690137, were not read. The first is the notify's target and the second is the arm taken when the count does not reach zero. Both are outside this body, and the model asserts nothing about either.
- What the literal 1 pushed at 0x00f999b5 means is not established. 0x00692400 reads it as its own first stack word and forwards it to 0x00692330, whose body was not read for this package. It is passed as 1 because that is what the PUSH carries, and nothing more is claimed.
- What the two receiver words ARE is not established. The +0x8a4 word is compared against 0xffffffff, passed by value to a lighting-manager method and then overwritten with 0xffffffff; the +0x894 word is null-tested, used as an ECX receiver by a thunk that adjusts it by -8 and dispatches through its table at +0x30, and finally cleared and handed to 0x00690120. That is what the bytes do, and nothing here says what either word is for: no record in this repository names them, no caller of this body exists in the xref export, and a sibling listing in the same class was not read for this package. Naming them is deliberately left to the integrator.
- Whether the +0x8a4 word is an owning reference, a borrowed one, or an index is unknown. The body stores 0xffffffff over it and hands its value to a method that this body never sees inside, so the ownership question cannot be settled from here. The one fact that leans on it is 0x00690120's own `LOCK XADD [EAX],ESI` with ESI = -1, and that is about the OTHER word.
- Whether the slot at 0x7c is a real slot INDEX in any class is not established. 0x7c is 31 whole dwords, which is what a dword-indexed table looks like on x86-32, and the machine's own classifier reads the site as VTABLE_SLOT -- but no record names the class, no record names the method, and the decompiler's `_vftable0[2].GetLightingWorld` is a structure it applied itself, not evidence. The model states the displacement and the receiver and the argument and nothing more.
