// Reconstruction of App::PropertyList::Read @ 0x006a2f60.
//
// Every statement below is annotated with the instruction block it comes from.
// Addresses are VA in the GOG digital build 3.1.0.22
// (sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// Structure of the original, in address order:
//
//   0x006a2f60  SUB ESP,0x10 / PUSH EBX,EBP,ESI,EDI   (callee-saved frame)
//   0x006a2f65  MOV EBP,[ESP+0x1c]                     arg1 = pInputStream
//   0x006a2f6d  one 32-bit big-endian header word      -> 0x0093a780
//   0x006a2f86  TEST BL,BL / JZ                        bail to the record loop
//   0x006a2f8a  TEST EAX,EAX / JNS                     bail if sign bit clear
//   0x006a2f8e  zero 12 bytes, read 3 BE words         -> 0x0093a780
//   0x006a2fb2  release the previous parent            vtable +0x04
//   0x006a2fad  svc = *DAT_015fd8a8                    -> 0x0067de30
//   0x006a2fd5  svc->vftable[0x2c](blk[0], blk[2], &this->parent)
//   0x006a2fe9  resize(this->properties, blk[1] & 0x7fffffff)  -> 0x006a2b80
//   0x006a2ff9  count = (properties.entries_end - entries_begin) / 0x18
//   0x006a3020  per record: 0x0093a780(entry->key, 1) then 0x00694440(entry+4)
//   0x006a3057  next record: byte offset += 0x18
//   0x006a3064  MOV AL,BL / RET 0x4                    return the accumulated flag
//
// The record format is fixed independently by App::PropertyList::Write @
// 0x006a1540, which emits the same 0x0093a780-counted 32-bit key word per entry
// (0x006a15a7 MOV EAX,[EDI+EDX] -> 0x006a15b8) and the same 0x18 stride
// (0x006a15e2 ADD EDI,0x18).

#include "property_list_read_006a2f60.hpp"

namespace openspore::reconstruction::pkg_app_proplist_read_wave17 {

namespace {

// 0x006a2b8e-0x006a300d: signed 32-bit division of the byte span by 0x18
// (IMUL 0x2AAAAAAB / SAR EDX,2 / MOV EAX,EDX / SHR EAX,0x1f / ADD EAX,EDX).
// Signed, so a corrupt span smaller than the start yields a negative count and
// the JLE at 0x006a3011 skips the loop entirely.
std::int32_t RecordCount(const PropertyMap& map) {
  const std::int32_t byte_span = static_cast<std::int32_t>(
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
          map.entries_end)) -
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
          map.entries_begin)));
  return byte_span / static_cast<std::int32_t>(kPropertyMapEntryStride);
}

}  // namespace

HelperPorts g_helpers;

bool OPENSPORE_THISCALL read_006a2f60(DirectPropertyList* list,
                                      IStream* pInputStream) {
  // 0x006a2f6d-0x006a2f7d: read one 32-bit word; the helper's element count is
  // in DWORDS (0x0093a780 reads count*4 bytes), and the result lands in AL.
  std::uint32_t header_word = 0;
  bool ok = g_helpers.read_dwords_be(pInputStream, &header_word, 1, 0);

  // 0x006a2f86 TEST BL,BL / 0x006a2f8a TEST EAX,EAX / JNS 0x006a2fe9.
  // The extended header is present only when the word read succeeded AND its
  // sign bit is set.
  if (ok && static_cast<std::int32_t>(header_word) < 0) {
    // 0x006a2f97-0x006a2f9f: three dwords are cleared before the read.
    std::uint32_t block[3] = {0u, 0u, 0u};

    // 0x006a2f8f PUSH 3 -> LEA ECX,[ESP+0x1c] -> 0x006a2fa3 CALL 0x0093a780.
    // NOTE: the result of THIS read replaces `ok` (0x006a2fab MOV BL,AL) and is
    // the value the record loop starts from; the first word's result is
    // discarded.  That is why the loop below starts from `ok`, not from a
    // separate variable.
    ok = g_helpers.read_dwords_be(pInputStream, block, 3, 0);

    // 0x006a2fb2-0x006a2fcb: drop the previous parent.  The field is nulled
    // first, then vtable slot +0x04 (index 1) is invoked on the old pointer --
    // a release, matching the `(**(code **)(*piVar1 + 4))()` shape in the
    // persisted decompilation and the Release() tail-call idiom used for
    // PropertyList objects in 0x006866f0.
    if (list->parent != nullptr) {
      DirectPropertyList* previous = list->parent;
      list->parent = nullptr;
      reinterpret_cast<void (*)()>(previous->vftable->release)();
    }

    // 0x006a2fad CALL 0x0067de30 -- the trivial getter that returns the
    // runtime-filled service pointer DAT_015fd8a8 (zero in the static image).
    // 0x006a2fd1-0x006a2fd7: ECX = service, EDX = service->vftable[0x2c].
    // 0x006a2fda/0x006a2fe0: pushed &this->parent (0x30) then block[0], so the
    // port is (block[0], block[2], DirectPropertyList**).
    PropertyListService* service = g_helpers.get_service();
    service->resolve(block[0], block[2], &list->parent);

    // 0x006a2fe5 MOV EAX,[ESP+0x24] (block[1]) / 0x006a2fe9 AND EAX,0x7fffffff
    // / 0x006a2fee LEA ESI,[EDI+0x18] / 0x006a2ff4 CALL 0x006a2b80.
    // 0x006a2b80 sets the entry count exactly: it appends default-constructed
    // entries when the map is short and erases the tail when it is long.
    g_helpers.resize_map(&list->properties, block[1] & 0x7fffffffu);
  }

  // 0x006a2fee-0x006a3011: the loop bound comes from the receiver's map, not
  // from the stream.  This is the single structural difference from
  // PropertyList::Write @ 0x006a1540, which writes the count first and never
  // emits a header word.
  const std::int32_t count = RecordCount(list->properties);

  // 0x006a3013-0x006a305f: byte-offset accumulator, stride 0x18.
  for (std::int32_t offset = 0; offset < count; offset += 1) {
    // The original re-loads entries_begin every iteration (0x006a3024); caching
    // it is behaviourally identical because resize_map already ran.
    PropertyMapEntry* entry = list->properties.entries_begin + offset;

    // 0x006a3020 TEST BL,BL / 0x006a3055 XOR BL,BL: once the flag is clear the
    // remaining records are skipped without touching the stream, and the loop
    // still runs to completion.
    if (!ok) {
      ok = false;
    } else {
      // 0x006a3024-0x006a302e: MOV EAX,[ESI] / ADD EAX,EDI / PUSH 0 / PUSH 1 /
      // PUSH EAX / PUSH EBP -- one 32-bit big-endian word into entry->key.
      ok = g_helpers.read_dwords_be(pInputStream, &entry->key, 1, 0);

      // 0x006a303a-0x006a3045: same entry, +0x04, third argument 0.
      if (ok) {
        ok = g_helpers.read_property_value(pInputStream, &entry->property, 0);
      }
    }
  }

  // 0x006a3064 MOV AL,BL -- only AL is defined; the upper three bytes of EAX
  // are residual.  0x006a306a RET 0x4 -- one stack word, callee-cleaned.
  return ok;
}

}  // namespace openspore::reconstruction::pkg_app_proplist_read_wave17
