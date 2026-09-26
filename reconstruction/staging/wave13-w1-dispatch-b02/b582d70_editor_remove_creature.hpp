// Wave-13 worker batch b02 -- target 0x00582d70
// Clean-room reconstruction from SporeApp.exe 3.1.0.22.
//
// Observed shape: an instance method on Editors::cEditor with three stack
// arguments, __thiscall, void return, RET 0xC. It removes animated creatures
// from the editor.
//
//   mode (arg1) : 0 -> clear the handle at this+0x364 and drop it
//                 1 -> operate on the 0x30-byte element vector at +0x36c
//                      arg2 != 0 : remove the last element
//                      arg2 == 0 : arg3 == 0 removes all, otherwise removes
//                                  the element whose dword 0 equals arg3
//                 2 -> clear the handle at this+0x368 and drop it
//                 other -> do nothing
//
// Every removal follows the same three-step protocol, visible twice in the
// listing and mirrored in Editors::cEditor::AddCreature at 0x00582fe0:
//   1. Editors::cEditorAnimWorld lookup of the element's dword 0 into a
//      12-byte out block (0x0059d110),
//   2. a notification on the singleton returned by 0x00401050 with the key
//      0x03f1bf57 and that block (0x0045af60),
//   3. Editors::cEditorAnimWorld::DestroyCreature(dword 0) (0x0059c6e0).
// The element is then unlinked with end -= 0x30; no element destructor runs.
//
// The owning class is INFERRED, not OBSERVED: this binary carries no MSVC RTTI
// and no cEditor vtable was located. See
// reconstruction/metadata/wave13-w1-dispatch-b02/00582d70.json.

#pragma once

#include <cstdint>

namespace openspore::wave13::b02 {

// The three selection values of arg1, read from the CMP chain at
// 0x00582d8b / 0x00582f72 / 0x00582fb3.
enum class CreatureSlot : std::uint32_t {
    Primary = 0,     // this + 0x364
    Array = 1,       // the 0x30-byte element vector at this + 0x36c
    Secondary = 2,   // this + 0x368
};

// One element of the vector at +0x36c. The stride is 0x30, proved by
// 0x00582dea (LEA EAX,[EAX + EAX*0x2]; SHL EAX,0x4) and by the -0x30 in
// 0x00582e4a, and independently by 0x0057ef50 and 0x009c69f0, which both
// memmove 0xc dwords per element.
//
// Only dword 0 is read by the target. It holds the Editors::cEditorAnimWorld
// handle: Editors::cEditor::AddCreature at 0x00582fe0 stores the anim-world
// pointer into element+0x00 and writes the other eleven dwords at +0x0c, +0x10,
// +0x14, +0x18, +0x19, +0x1a, +0x1b, +0x1c, +0x20, +0x24, +0x28 and +0x2c.
struct EditorCreatureEntry {
    std::uint32_t anim_world;  // +0x00, the only field this function reads
    std::uint8_t pad04[8];
    float f_0c;
    float f_10;
    float f_14;
    std::uint8_t u8_18;
    std::uint8_t u8_19;
    std::uint8_t u8_1a;
    std::uint8_t u8_1b;
    std::uint8_t u8_1c;
    std::uint8_t pad1d[3];
    std::uint32_t dword_20;
    std::uint32_t dword_24;
    std::uint32_t dword_28;
    std::uint32_t dword_2c;
};
static_assert(sizeof(EditorCreatureEntry) == 0x30, "the element stride is 0x30");

// The 12-byte payload 0x0059d110 writes, forwarded verbatim to 0x0045af60.
struct CreatureTransform {
    std::uint32_t a;
    std::uint32_t b;
    std::uint32_t c;
};

// Partial view of Editors::cEditor. Only the members this function touches are
// named; the two gaps are padding so the offsets stay byte-exact.
struct EditorPartial {
    std::uint8_t pad000[0x360];
    void* mpAnimWorld;             // +0x360, the receiver of 0x0059c6e0 and 0x0059d110
    std::uint32_t primary_world;   // +0x364, destroyed in mode 0
    std::uint32_t secondary_world; // +0x368, destroyed in mode 2
    EditorCreatureEntry* begin;    // +0x36c
    EditorCreatureEntry* end;      // +0x370
    EditorCreatureEntry* capacity; // +0x374, named for AddCreature's growth test
    std::uint8_t pad378[0x385 - 0x378];
    std::uint8_t attach_flag;      // +0x385, the setter is 0x0057e340
};

// ---------------------------------------------------------------------------
// Opaque ports. Declared, never implemented: no original body is claimed for
// any of these and none is inlined from the target.
// ---------------------------------------------------------------------------

// 0x0059c6e0 -- Ghidra SDK symbol Editors::cEditorAnimWorld::DestroyCreature.
// A map lookup on the anim world; on a hit it calls slot +0x3c of
// [*(this+0x38)] with (*(node+0x14) + 8) and then 0x0059ae60 and 0x0059c460.
void editor_anim_world_destroy_creature_port(void* anim_world, std::uint32_t creature_handle);

// 0x0059d110 -- __thiscall, one stack argument. Returns a byte: 1 when a node
// was found whose controller's +8 block is non-null, in which case the three
// dwords at +4, +8 and +0xc of that block are written to the out pointer.
std::uint8_t editor_anim_world_get_transform_port(void* anim_world, std::uint32_t creature_handle,
                                                  CreatureTransform* out);

// 0x00401050 -- a bare singleton getter returning [0x015d0c14]. Its RET has no
// immediate, so the three words pushed before it are consumed by the following
// call.
void* global_015d0c14_get_port();
// 0x0045af60 -- __thiscall, three stack arguments. Builds a 16-byte descriptor
// from the 12-byte payload, bumps two fields of it, and calls 0x0045ac20.
void notify_creature_detached_port(void* singleton, std::uint32_t key, std::uint32_t selector,
                                   const CreatureTransform* payload);

// 0x0057e340 -- __thiscall, one stack argument. Writes this+0x385, walks the
// model's list of the AnimatedCreature at this+0x364 calling slot +0xc4 on
// each, walks the array at this+0x98 calling slots +4, +0xc4 and +8, and
// finally calls 0x0057ae10.
void set_attach_flag_port(EditorPartial* editor, std::uint8_t value);

// 0x0057ef50 -- __thiscall(begin_field_ptr, element_ptr). The vector erase:
// shifts every following element down by 0x30 bytes and does end -= 0x30.
void editor_vector_erase_port(EditorCreatureEntry** begin_field, EditorCreatureEntry* element);
// 0x009c69f0 -- __thiscall(begin_field_ptr, begin, end). The vector clear:
// zeroes every element and sets end = begin.
void editor_vector_clear_port(EditorCreatureEntry** begin_field, EditorCreatureEntry* begin,
                              EditorCreatureEntry* end);

}  // namespace openspore::wave13::b02
