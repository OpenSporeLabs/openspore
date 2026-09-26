#pragma once

#include <cstddef>

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

// Spore/MathUtils.h:554 declares
//   struct BoundingBox { /* 00h */ Vector3 lower; /* 0Ch */ Vector3 upper; };
// i.e. exactly six consecutive floats. That is proven independently by
// 0x00409c00, which writes 0x7f7fffff three times then 0xff7fffff three times,
// and by 0x0043f050, which pairs element 0 with 3, 1 with 4 and 2 with 5.
struct BoundingBox {
  float lower[3];  // +0x00 .. +0x08, initialised to +FLT_MAX
  float upper[3];  // +0x0c .. +0x14, initialised to -FLT_MAX
};

// The receiver. Only the vector this body reads is declared.
// Spore/Editors/EditorModel.h: /* 18h */ eastl::vector<EditorRigblockPtr>
// mRigblocks; - and the elements are EditorRigblockPtr, one intrusive pointer.
struct OpaqueRigblockVector {
  unsigned char* begin;     // +0x18
  unsigned char* end;       // +0x1c
  unsigned char* capacity;  // +0x20
};

struct OpaqueEditorModel {
  unsigned char pad_000_018[0x18];
  mutable OpaqueRigblockVector mRigblocks;  // +0x18
};

// The vector element. The body only ever passes the pointer to the bounds port
// and to the filter port, so the type stays opaque; the class is not claimed
// because no vtable was located.
struct EditorRigblockPort;

// One vector element as the body reads it: the eastl::vector holds
// EditorRigblockPtr, an intrusive_ptr, so one pointer per element.
struct EditorRigblockPtrSlot {
  EditorRigblockPort* ptr;
};

// Opaque ports. Each is declared with the call shape the disassembly proves and
// with the operation established from that callee's own decompiled body.
namespace unresolved_ports {

// 0x00409c00(BoundingBox*). Stores +FLT_MAX into lower and -FLT_MAX into upper.
// This is Math::BoundingBox's empty/inverted sentinel, not a zero box.
extern void __fastcall bounding_box_make_empty(BoundingBox*);

// 0x0044ae00(EditorRigblock* this, BoundingBox* out, int mode, char a, char b)
// -> BoundingBox*. Computes the rigblock's own bounds and, when the last
// argument is non-zero, additionally unions the bounds of the child rigblocks
// in the vector at rigblock+0x340. Returns `out`.
extern BoundingBox* __thiscall rigblock_get_bounds(EditorRigblockPort*,
                                                   BoundingBox*, int, char,
                                                   char);

// 0x0043f050(BoundingBox* acc, const BoundingBox* b) -> void.
// Union: if acc.lower[0] > acc.upper[0] (acc is the empty sentinel) acc is
// overwritten by b, otherwise acc is expanded componentwise to contain b.
extern void __thiscall bounding_box_union_in_place(BoundingBox*,
                                                    const BoundingBox*);

// 0x00511140(void* dst, const void* src) -> void*. Copies six dwords.
extern void* __thiscall copy_six_dwords(void*, const void*);

// 0x00435d40(EditorRigblock* this) -> byte. Walks the parent chain through
// rigblock+0x33c for at most 100 levels looking for flag bits 0x80 or 0x100 at
// +0xdc8 or bit 0x8 at +0xdcc; returns 1 if any level matches, else 0.
extern unsigned char __fastcall rigblock_is_hidden_or_filtered(
    EditorRigblockPort*);

}  // namespace unresolved_ports

static_assert(sizeof(void*) == 4, "the target is x86-32");
static_assert(sizeof(BoundingBox) == 24,
              "Spore/MathUtils.h declares BoundingBox as two Vector3, and "
              "0x00409c00 writes exactly six dwords");
static_assert(offsetof(OpaqueEditorModel, mRigblocks) == 0x18,
              "the receiver's +0x18 and +0x1c are the vector's begin and end");
static_assert(offsetof(OpaqueRigblockVector, end) == 0x04,
              "the count is ((end - begin) >> 2), i.e. four bytes per element");
static_assert(sizeof(EditorRigblockPtrSlot) == 4,
              "the shift by 2 at 0x004ad58f proves a four-byte element");

// 0x004ad550. __thiscall, ECX receiver, two callee-cleaned stack arguments
// (RET 0x8): a BoundingBox* out parameter and a one-byte filter flag. Returns
// the out parameter in EAX.
BoundingBox* __thiscall editor_model_union_bounds_004ad550(
    OpaqueEditorModel* model, BoundingBox* out_bounds, char filter_hidden);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
