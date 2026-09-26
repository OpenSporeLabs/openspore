// Wave-13 worker batch b02 -- target 0x00582d70
// Reconstructed from the live disassembly of 0x00582d70..0x00582fdb
// (199 instructions). Every statement is anchored to an instruction address;
// see reconstruction/metadata/wave13-w1-dispatch-b02/00582d70.json.

#include "b582d70_editor_remove_creature.hpp"

namespace openspore::wave13::b02 {
namespace {

// The divide-by-0x30 idiom that appears six times: IMUL EDX by 0x2aaaaaab,
// SAR EDX,3, then add the sign correction. 0x2aaaaaab * 2^3 / 2^32 == 1/48, so
// the result is (end - begin) / 48 for a non-negative byte count.
std::uint32_t entry_count(const EditorCreatureEntry* begin, const EditorCreatureEntry* end) {
    const std::uint32_t bytes = static_cast<std::uint32_t>(
        reinterpret_cast<const std::uint8_t*>(end) - reinterpret_cast<const std::uint8_t*>(begin));
    return (bytes * 0x2aaaaaabu) >> 3;
}

// The three-step detach protocol, identical at 0x00582df5/0x00582e05/0x00582e45,
// 0x00582eb0/0x00582ec1/0x00582eda and 0x00582f22/0x00582f33/0x00582f4c.
void detach_one(void* anim_world, std::uint32_t handle) {
    CreatureTransform payload{};
    (void)editor_anim_world_get_transform_port(anim_world, handle, &payload);
    // 0x00582dff/0x00582e00: the selector is 0 on the first and third sites and
    // 0 on the second as well; the key is always 0x03f1bf57. The three words
    // are pushed before 0x00401050, which does not pop them.
    notify_creature_detached_port(global_015d0c14_get_port(), 0x03f1bf57u, 0u, &payload);
    editor_anim_world_destroy_creature_port(anim_world, handle);
}

}  // namespace

// 0x00582d70, __thiscall, three stack arguments (RET 0xC), void return.
void FUN_00582d70_reconstruct(EditorPartial* editor, std::uint32_t mode, std::uint32_t remove_last,
                              std::uint32_t handle) {
    // 0x00582d76/0x00582d7f/0x00582d81: a null anim world aborts every mode.
    void* const anim_world = editor->mpAnimWorld;
    if (anim_world == nullptr) {
        return;
    }

    if (mode == 1) {
        // 0x00582d94: arg2 is tested as a BYTE, not as a dword.
        if (static_cast<std::uint8_t>(remove_last) == 0) {
            // 0x00582e59..0x00582ef3: remove by handle, or remove all.
            EditorCreatureEntry* const begin = editor->begin;

            if (handle == 0) {
                // 0x00582ef6: the clear-all loop. 0x00582f0c fixes the trip
                // count in EBX, 0x00582f51 advances EDI by 0x30 and
                // 0x00582f57 JNZ runs the body exactly `count` times.
                const std::uint32_t count = entry_count(begin, editor->end);
                if (count == 0) {
                    // 0x00582f0a JLE 0x00582f59 falls through to the clear.
                } else {
                    for (std::uint32_t i = 0; i < count; ++i) {
                        detach_one(anim_world, begin[i].anim_world);
                    }
                }
                // 0x00582f59..0x00582f63: zero every element and set end = begin.
                editor_vector_clear_port(&editor->begin, begin, editor->end);
                return;
            }

            // 0x00582e6b..0x00582e7f: the count, and an empty-vector early exit
            // at 0x00582e7f JLE 0x00582e94.
            const std::uint32_t count = entry_count(begin, editor->end);
            if (count == 0) {
                return;
            }

            // 0x00582e81..0x00582e92: a linear search for handle, comparing
            // element.dword0 only, with the 0x30 stride applied by
            // 0x00582e8d ADD EDX,0x30 and the bound at 0x00582e90 JL.
            for (std::uint32_t i = 0; i < count; ++i) {
                if (begin[i].anim_world == handle) {
                    // 0x00582e9e..0x00582ed3: the found index is turned back
                    // into a byte offset, 0x00582ea1 LEA EDI,[EDI + EDI*0x2]
                    // then 0x00582ea8 SHL EDI,0x4, and the handle is re-read
                    // from the element a second time.
                    const std::size_t offset = i * sizeof(EditorCreatureEntry);
                    detach_one(anim_world, *reinterpret_cast<const std::uint32_t*>(
                                                reinterpret_cast<const std::uint8_t*>(begin) + offset));
                    // 0x00582edf..0x00582ee7: the erase, with ECX = the address
                    // of the begin field and the argument = the element address.
                    editor_vector_erase_port(&editor->begin,
                                             reinterpret_cast<EditorCreatureEntry*>(
                                                 reinterpret_cast<std::uint8_t*>(begin) + offset));
                    return;
                }
            }
            // 0x00582e94: falling out of the search without a match returns
            // without touching the vector.
            return;
        }

        // 0x00582da4..0x00582e56: remove the LAST element.
        const std::uint32_t count = entry_count(editor->begin, editor->end);
        if (count == 0) {
            return;  // 0x00582dbc JZ 0x00582e96
        }
        // 0x00582de4..0x00582df0: begin + (count - 1) * 0x30, formed as
        // 3 * count * 16 - 0x30 + begin.
        {
            EditorCreatureEntry* const last = editor->begin + (count - 1);
            detach_one(anim_world, last->anim_world);
        }
        // 0x00582e4a: the unlink. The element's own destructor does not run.
        editor->end -= 1;
        return;
    }

    if (mode == 0) {
        // 0x00582f76/0x00582f7c: nothing to do when the handle is already null.
        if (editor->primary_world == 0) {
            return;
        }
        // 0x00582f82..0x00582f8e: the attach flag is cleared first, and only
        // when it is currently set. 0x0057e340 writes editor+0x385 itself.
        if (editor->attach_flag != 0) {
            set_attach_flag_port(editor, 0);
        }
        // 0x00582f93..0x00582fa0: destroy the handle, then clear the field.
        editor_anim_world_destroy_creature_port(anim_world, editor->primary_world);
        editor->primary_world = 0;
        return;
    }

    if (mode == 2) {
        // 0x00582fbc/0x00582fc4: the same guard on the second handle.
        if (editor->secondary_world == 0) {
            return;
        }
        editor_anim_world_destroy_creature_port(anim_world, editor->secondary_world);
        editor->secondary_world = 0;
        return;
    }

    // 0x00582fb6 JNZ 0x00582e96: any other mode value is a no-op. The three
    // values the CMP chain accepts are 0, 1 and 2, and every recorded callsite
    // in the binary passes 1.
}

}  // namespace openspore::wave13::b02
