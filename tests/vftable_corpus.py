"""The real SporeApp.exe targets the two new rules are regressed against.

Every listing here is a committed, verbatim ``/disassemble_function`` capture
(``tests/capture_vftable_corpus.py`` re-records it), so every test built on this
table is hermetic and needs no bridge. Nothing is transcribed by hand: the
committed bytes are the provenance, and the table says what each target is here
to *falsify*.

Four groups, and the middle two are the point of the whole exercise:

* ``fires`` -- targets the capability is expected to resolve. If one of them
  stops firing, the capability is broken.
* ``dispatch_receiver`` -- sound vftable membership in the **callee-pop** shape
  whose body reads the ECX the vtable dispatch handed it. ``R1-VFT`` resolves
  these to a register receiver; before the 2026-09-29 extension they were
  refused as a block, which was one claim where there were two.
* ``stack_receiver`` -- sound vftable membership in the same callee-pop shape
  whose receiver really *is* the first popped stack word (the COM /
  ``__stdcall`` interface form). ``0x01053e00`` is the sharpest case in the
  binary: its receiver is provably ``entry_ESP+0x4``, and all five vftables the
  triage index claims for it are unsound. A rule that claimed ``__thiscall``
  for any of these would be fabricating a receiver, and membership alone gets
  all of them wrong -- which is what the group is for.
* ``address_receiver`` -- sound vftable membership in the same callee-pop shape
  whose body takes the **address** of the incoming ECX (``LEA r,[ECX+k]``) and
  never dereferences it. ``R2-VFT`` resolves these. ``0x009817c0`` is the
  witness; ``0x00950eb0`` is in the group as the independent witness *for the
  rule*, because it is the function three of them tail-call into and R1-VFT
  already resolves it to ``__thiscall`` on the strength of a plain ``MOV EAX,ECX``.
* ``not_forwarded`` -- tail-jump bodies that must keep abstaining, each for a
  different, individually checkable reason.

The `hop` field of a forwarding target is the address the thunk jumps to; its own
listing is captured too, so the tail record a test feeds the engine is derived
from a real listing rather than written by hand.
"""
import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORPUS_DIR = os.path.join(ROOT, "tests", "fixtures", "abi", "vftable")

#: ``(va8, slug)`` of every capture in the corpus.
CORPUS = (
    # -- V1-VFT: a sound vftable slot in register-receiver form ---------------
    {"va8": "00980510", "slug": "vftable_slot_caller_cleanup", "group": "fires",
     "note": "slot 5 of the table at 0x0143d6f0; bare RET, so the callee pops nothing"},
    {"va8": "00b1e4d0", "slug": "vftable_slot_icf_collapsed", "group": "fires",
     "note": "XOR AL,AL; RET, a member of 184 sound tables at once -- membership "
             "yields 'a virtual member of some class' and never a name"},
    {"va8": "00b1fbf0", "slug": "vftable_slot_reconstructed", "group": "fires",
     "note": "already reconstructed; its only remaining blocker was ABI=WARN"},
    {"va8": "00b7e380", "slug": "vftable_slot_three_tables", "group": "fires",
     "note": "three sound memberships; the first sorted one is cited"},
    {"va8": "0051e340", "slug": "vftable_slot_paired_low", "group": "fires",
     "note": "paired with 0x0051e380 at slots 0 and 1 of the same tables"},
    {"va8": "0051e380", "slug": "vftable_slot_paired_high", "group": "fires",
     "note": "the upper half of that pair"},
    {"va8": "006e64f0", "slug": "vftable_slot_many_tables", "group": "fires",
     "note": "46 sound memberships; membership is not a class identity"},
    {"va8": "007f30d0", "slug": "vftable_slot_four_tables", "group": "fires",
     "note": "four sound memberships"},
    {"va8": "00fa0d50", "slug": "vftable_slot_two_tables", "group": "fires",
     "note": "two sound memberships"},

    # -- R1-VFT: sound callee-pop slot, receiver resolved by the dispatch ----
    # The 2026-09-29 extension split this group in two. The previous corpus put
    # all thirteen here under one assertion -- "sound membership plus callee
    # cleanup must change nothing at all" -- and that assertion was too coarse to
    # be true or false: it was really two claims wearing one name, and the
    # second one was wrong. What separates them is a *positive* observation the
    # old rule had no way to read: whether the body reads the ECX the vtable
    # dispatch handed it. See `R1VftReceiverRuleTest`.
    {"va8": "0067dc80", "slug": "message_manager_get_callee_cleanup",
     "group": "dispatch_receiver",
     "note": "App::IMessageManager::Get; slot 0 of a sound table, callee pops. "
             "MOV ESI,ECX then CALL 0x00f47380 with ECX untouched, so the same "
             "object is the receiver of both calls"},
    {"va8": "0067e6b0", "slug": "callee_cleanup_slot20", "group": "dispatch_receiver",
     "note": "slot 20; the same body shape as 0x0067dc80"},
    {"va8": "0052e640", "slug": "callee_cleanup_slot7", "group": "dispatch_receiver",
     "note": "25 sound memberships. Both direct call sites (0x0050a468, "
             "0x0050a5d6) push three words and load ECX from the caller's own "
             "incoming ECX; the callee pops 12"},
    {"va8": "0052e650", "slug": "callee_cleanup_slot10", "group": "dispatch_receiver",
     "note": "199 sound memberships. Corroborated from the other side: 0x0055c633 "
             "is SUB ECX,0x8 immediately before CALL 0x0052e650"},
    {"va8": "0057d6f0", "slug": "callee_cleanup_slot2", "group": "dispatch_receiver",
     "note": "reached only through three this-adjusting thunks (0x0057a5a0/b0/c0, "
             "SUB ECX,0x10/0x14/0x4; JMP here) and by no direct call at all"},
    {"va8": "00642210", "slug": "callee_cleanup_slot0", "group": "dispatch_receiver",
     "note": "two JMP entries, both with a SUB ECX adjustor (0x00642160, 0x00642170)"},
    {"va8": "00a85840", "slug": "callee_cleanup_slot6", "group": "dispatch_receiver",
     "note": "the body adjusts the receiver itself: LEA ECX,[ESI + 0x24] with "
             "ESI = the incoming ECX, then CALL 0x00537dc0"},
    {"va8": "00a98400", "slug": "callee_cleanup_slot6b", "group": "dispatch_receiver",
     "note": "the same shape at offset 0x18; the pair differ in one displacement"},
    {"va8": "00e5cac0", "slug": "identity_getter_ret4", "group": "dispatch_receiver",
     "note": "MOV EAX,ECX; RET 0x4. 0x007fbd90 is ADD ECX,0xc immediately before "
             "CALL here, so the value it forwards is this + 0xc"},
    {"va8": "00f9fef0", "slug": "callee_cleanup_slot35", "group": "dispatch_receiver",
     "note": "MOV EDI,ECX; TEST EDI,EDI; JZ; LEA EBX,[EDI + 0x4] -- null-tested "
             "and then offset, which is the strongest in-body pointer witness "
             "there is. The first popped word is also a pointer here, and it is "
             "an *argument*: ECX is slot 35's receiver because the dispatch "
             "needed it to be"},

    # -- R1-VFT: sound callee-pop slot, receiver is the popped word ----------
    {"va8": "01053e00", "slug": "com_interface_receiver_on_the_stack",
     "group": "stack_receiver",
     "note": "SUB ESP,0x18 + PUSH ESI = 28 bytes, so [ESP+0x20] is entry_ESP+0x4: "
             "the receiver is the first callee-popped word (RET 0x8). The body "
             "never reads its incoming ECX, which is the whole of the guard. Fails "
             "P independently -- all five index-claimed tables are unsound"},
    {"va8": "00fa5040", "slug": "callee_cleanup_slot22", "group": "stack_receiver",
     "note": "sound membership, callee cleanup, and the body already dereferences "
             "no ECX at all: R2's receiver-absent reading, so the record is "
             "unchanged by membership and by this extension"},
    {"va8": "006a2e20", "slug": "callee_cleanup_slot5", "group": "stack_receiver",
     "note": "already __thiscall by C6B before any membership exists -- a real "
             "member that reads its receiver through ECX and pops 8. Kept because "
             "byte-identity covers it too, and because it is the control for "
             "'membership adds nothing once the body has decided'"},

    # -- R2-VFT: sound callee-pop slot, receiver only ever ADDRESS-TAKEN -----
    # The 2026-09-30 extension. These are sound vftable slots in the same
    # callee-pop shape as `dispatch_receiver`, whose body never *dereferences*
    # the incoming ECX: it copies it, offsets it and returns the result. The
    # engine's own reason is `ecx_address_taken_without_memory_access`, which is
    # a different unknown from the one R1-VFT resolves, so they were refused for
    # a reason that has nothing to do with the evidence. See `R2VftReceiverRuleTest`.
    {"va8": "009817c0", "slug": "hash_getter_set_image", "group": "address_receiver",
     "note": "the R2-VFT witness. CMP the hash argument against two immediates, "
             "then TEST ECX,ECX / JZ / LEA EAX,[ECX+0xc] and LEA EAX,[ECX+0x4], "
             "unhandled hashes tail-delegated to 0x00951240 with the hash left in "
             "the first popped word. ECX is never written and never dereferenced"},
    {"va8": "009646d0", "slug": "hash_getter_get_dimensions", "group": "address_receiver",
     "note": "the same shape with three hashes and two tables at 0x0141785c; "
             "LEA EAX,[ECX+0x4] and LEA EAX,[ECX+0xc]"},
    {"va8": "009672d0", "slug": "hash_getter_handle_uimessage", "group": "address_receiver",
     "note": "the one-hash form; LEA EAX,[ECX+0xc], tail-delegated to 0x00950eb0"},
    {"va8": "009804e0", "slug": "hash_getter_single", "group": "address_receiver",
     "note": "the one-hash form again, a different table"},
    {"va8": "00980330", "slug": "hash_getter_forwarded_target", "group": "address_receiver",
     "note": "the hop target of 0x00980480. 0x00980480's only blocker is that "
             "this target's convention abstained, so resolving its receiver is "
             "what T1-FWD needs to forward one"},
    {"va8": "00950eb0", "slug": "hash_getter_delegate", "group": "address_receiver",
     "note": "the delegate all three of the above tail-call into. It is a member "
             "of 17 sound tables and R1-VFT already resolves IT to __thiscall, "
             "because MOV EAX,ECX is a read. So the callee-pop family in which "
             "ECX carries the object is machine-certified today, and the only "
             "difference for the three above is that they offset `this` instead "
             "of copying it. This is the independent witness the rule rests on"},
    {"va8": "00841540", "slug": "lea_receiver_handed_to_call", "group": "address_receiver",
     "note": "a different shape in the same class: LEA ESI,[ECX + 0x4c] and then "
             "three `MOV ECX,ESI; CALL ...` pairs, so the address computed from "
             "the incoming ECX is used as the RECEIVER of three other member "
             "calls. The strongest in-body pointer witness of the group, and it "
             "pops 8"},

    # -- T1-FWD: a resolved single hop --------------------------------------
    {"va8": "0096ff70", "slug": "this_adjustor_thunk", "group": "forwarded",
     "hop": "0096ffd0",
     "note": "SUB ECX,0xc; JMP -- a this-adjustor thunk onto a __thiscall that "
             "pops 4. Corroborated independently: the target writes the vftable "
             "at 0x01442584, and 0x0096ff70 is slot 3 of it"},
    {"va8": "00980470", "slug": "this_adjustor_thunk_c", "group": "forwarded",
     "hop": "00980490", "note": "SUB ECX,0xc; JMP onto a popping __thiscall"},
    {"va8": "005a2320", "slug": "this_adjustor_thunk_b", "group": "forwarded",
     "hop": "005a2ed0", "note": "SUB ECX,0x4; JMP; the pre-fix engine opened a "
                                 "false conflict here (see the cross_validate fix)"},
    {"va8": "00642190", "slug": "forwarding_thunk", "group": "forwarded",
     "hop": "006412a0", "note": "a bare forwarding thunk: one JMP, no frame work"},
    {"va8": "00980480", "slug": "cleanup_only_thunk", "group": "forwarded",
     "hop": "00980330", "note": "the target's convention still abstains, so only "
                               "the cleanup moves: callee, 4 bytes"},
    {"va8": "00c372b0", "slug": "positive_this_adjustor_thunk", "group": "forwarded",
     "hop": "00feba90", "note": "ADD ECX,1976; JMP -- the adjustor is upwards, "
                                "which is what multiple inheritance looks like"},
    {"va8": "00841440", "slug": "two_sites_one_tail_target", "group": "forwarded",
     "hop": "0083c780", "note": "ArgScript::FormatParser::CreateDefinitionSafe: a JZ "
                                "whose two arms each store to [ESP+0x8] and each then "
                                "JMP 0x0083c780. Two exit SITES, one target address, "
                                "so the transfer target is unambiguous and S1 is "
                                "satisfied by the target set rather than the count"},

    # -- T1-FWD: must not forward -------------------------------------------
    {"va8": "007e6100", "slug": "strcmp_loop_interior_jump", "group": "not_forwarded",
     "hop": "007e6130",
     "note": "the one real false positive of a naive rule: a strcmp-shaped loop "
             "whose JMP lands inside its own body (the bridge splits it in two). "
             "Caught by S3 (the target is not an entry), S4 (esp_delta 4) and S6 "
             "(4 bytes of its own arguments against the target's 20)"},
    {"va8": "00847a40", "slug": "canvas_func10_iat_jump", "group": "not_forwarded",
     "note": "a vftable slot at 0x0141ca98 that tail-jumps through the import "
             "address table on both arms: not a direct JMP, and the target is a "
             "__stdcall callee-pop, so no sound rule can forward it"},
    {"va8": "00847a90", "slug": "interior_then_iat_jump", "group": "not_forwarded",
     "note": "two exits, the direct one landing inside its own body: the case "
             "`tail_call.target` gets wrong"},
    {"va8": "01053be0", "slug": "second_wrong_tail_target", "group": "not_forwarded",
     "note": "the other target `tail_call.target` is provably wrong for"},

    # -- hop targets: the listings a forwarding record is derived from -------
    {"va8": "0096ffd0", "slug": "hop_thiscall_pop4", "group": "hop",
     "note": "the target of 0x0096ff70"},
    {"va8": "00980490", "slug": "hop_thiscall_pop4b", "group": "hop",
     "note": "the target of 0x00980470"},
    {"va8": "005a2ed0", "slug": "hop_thiscall_pop4c", "group": "hop",
     "note": "the target of 0x005a2320"},
    {"va8": "006412a0", "slug": "hop_thiscall_caller_cleanup", "group": "hop",
     "note": "the target of 0x00642190: a __thiscall whose cleanup is caller-side"},
    {"va8": "00980330", "slug": "hop_convention_abstains", "group": "hop",
     "note": "the target of 0x00980480: a callee pop of 4 with no convention"},
    {"va8": "00feba90", "slug": "hop_thiscall_caller_cleanup_b", "group": "hop",
     "note": "the target of 0x00c372b0"},
    {"va8": "007e6130", "slug": "hop_interior_not_an_entry", "group": "hop",
     "note": "the function 0x007e6100's JMP lands inside: a bridge capture of the "
             "*containing* function, whose first instruction is not 0x007e6135"},
    {"va8": "0083c780", "slug": "hop_thiscall_pop8", "group": "hop",
     "note": "the target of 0x00841440: RET 0x8 over two popped words, so C6B "
             "decides __thiscall from the target's own body"},
)

def by_group(group):
    return [entry for entry in CORPUS if entry["group"] == group]


def by_va8(va8):
    for entry in CORPUS:
        if entry["va8"] == va8:
            return entry
    return None


def corpus_path(entry):
    return os.path.join(CORPUS_DIR, "%s_%s.json" % (entry["va8"], entry["slug"]))


def load(entry):
    """The committed capture: a bridge response body, forwarded whole."""
    import json
    with open(corpus_path(entry), "r", encoding="utf-8") as handle:
        return json.load(handle)
