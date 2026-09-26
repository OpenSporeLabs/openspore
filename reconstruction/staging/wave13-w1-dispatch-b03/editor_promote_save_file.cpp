#include "editor_promote_save_file.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

// The literal u".old" lives at 0x01403204; read live as
// 2e 00 6f 00 6c 00 64 00 00 00.
extern const char16_t kOldSuffix[] = u".old";

namespace {

using unresolved_ports::delete_file;
using unresolved_ports::delete_path_recursive;
using unresolved_ports::eastl_deallocate;
using unresolved_ports::file_exists;
using unresolved_ports::lookup_save_area_by_id;
using unresolved_ports::memcpy;
using unresolved_ports::move_file;
using unresolved_ports::string16_assign;
using unresolved_ports::string16_concat;
using unresolved_ports::string16_reserve;

// Resource::SaveAreaID::GamesGame0 = 0x4729A47, i.e.
// "%APPDATA%/Spore/Games/Game0". The immediate is at 0x0068920c.
constexpr unsigned int kGamesGame0SaveAreaId = 0x4729a47u;

// 0x00689216 MOV EDX,[EAX] / 0x0068921a MOV EAX,[EDX + 0x28] / 0x00689220
// CALL EAX - virtual slot +0x28 of the looked-up save area, returning the
// directory path. Unresolved: no concrete table was located for this site.
const char16_t* base_directory_path() {
  void* const save_area = lookup_save_area_by_id(kGamesGame0SaveAreaId);
  auto* const vtable = *static_cast<void* const*>(save_area);
  using PathSlot = const char16_t*(__thiscall*)(void*);
  PathSlot slot = nullptr;
  const auto* const address =
      reinterpret_cast<const unsigned char*>(vtable) + 0x28;
  __builtin_memcpy(&slot, address, sizeof(slot));
  return slot(save_area);
}

// 0x00689235 assigns a NUL-terminated wide string into a zeroed local; the
// three dwords are written first at 0x00689229/0x0068922d/0x00689231.
void assign_string(OpaqueString16* dst, const char16_t* src) {
  dst->begin = nullptr;
  dst->end = nullptr;
  dst->capacity = nullptr;
  string16_assign(dst, src);
}

// 0x00689246 LEA ECX,[ESI+0x1] / 0x0068925e CALL 0x00429760 / 0x0068926c
// memcpy / 0x0068927a MOV word ptr [EAX],DX - an inlined deep copy of a string
// object, reserving length + 1 and NUL-terminating.
OpaqueString16 copy_string(const OpaqueString16& src) {
  // 0x00689242 SUB ESI,EBX / 0x00689244 SAR ESI,0x1: the subtraction is on
  // byte addresses and the shift is arithmetic, so a span of 0 also yields 0.
  const auto byte_span = static_cast<int>(reinterpret_cast<const char*>(src.end) -
                                         reinterpret_cast<const char*>(src.begin));
  const auto length = static_cast<unsigned int>(byte_span >> 1);
  OpaqueString16 dst;
  dst.begin = nullptr;
  dst.end = nullptr;
  dst.capacity = nullptr;
  string16_reserve(&dst, length + 1u);
  const auto byte_length = length << 1;
  memcpy(dst.begin, src.begin, byte_length);
  dst.end = dst.begin + (byte_length >> 1);
  *dst.end = u'\0';
  return dst;
}

// The repeated tail guard: CMP ECX,0x2 / JLE skip / CMP ptr,0 / JZ skip /
// PUSH ptr / CALL 0x00f47380, e.g. 0x0068942d..0x00689445. ECX is
// (end - begin) & 0xfffffffe, so a buffer is freed only when it spans more than
// one char16_t and is non-null.
void free_string(const OpaqueString16& s) {
  const auto span = static_cast<unsigned int>(
      reinterpret_cast<const unsigned char*>(s.end) -
      reinterpret_cast<const unsigned char*>(s.begin));
  if (static_cast<int>(span & 0xfffffffeu) > 2 && s.begin != nullptr) {
    eastl_deallocate(const_cast<char16_t*>(s.begin));
  }
}

}  // namespace

// Reconstructed body of 0x006891f0 (731 bytes, 239 instructions, image base
// 0x00400000). See
// reconstruction/metadata/wave13-w1-dispatch-b03/006891f0.json.
//
// Operation, in the order the disassembly performs it:
//   1. resolve the GamesGame0 save area and read its directory path
//   2. deep-copy that path into a local string
//   3. delete-tree the copy (result discarded)
//   4. dest = base + dest_name
//   5. src  = base + source_name
//   6. bak  = dest + ".old"
//   7. if file_exists(dest) move dest -> bak
//   8. move src -> dest, result discarded
//   9. if file_exists(bak) delete_file(bak)
//  10. release all six string buffers and tear down the SEH frame
void __cdecl editor_promote_save_file_006891f0(const char16_t* source_name,
                                               const char16_t* dest_name) {
  OpaqueString16 base = {};
  assign_string(&base, base_directory_path());

  // 0x0068924a..0x0068927a: reserve length + 1, memcpy, NUL-terminate.
  OpaqueString16 base_copy = copy_string(base);

  // 0x0068927d PUSH EBP / 0x00689286 CALL 0x00932ae0. EBP is the freshly
  // NUL-terminated copy of the base path, so the argument is that path.
  delete_path_recursive(base_copy.begin);

  OpaqueString16 dest = {};
  OpaqueString16 dest_name_string = {};
  assign_string(&dest_name_string, dest_name);
  string16_concat(&dest, &base, &dest_name_string);

  OpaqueString16 src = {};
  OpaqueString16 source_name_string = {};
  assign_string(&source_name_string, source_name);
  string16_concat(&src, &base, &source_name_string);

  OpaqueString16 backup = {};
  OpaqueString16 old_suffix_string = {};
  assign_string(&old_suffix_string, kOldSuffix);
  string16_concat(&backup, &dest, &old_suffix_string);

  // 0x006893e1 CALL 0x00931fa0 / 0x006893ea TEST AL,AL / 0x006893ec JZ
  if (file_exists(dest.begin) != 0) {
    // 0x006893f2 PUSH 0x1 / 0x006893f4..0x006893f6 CALL 0x00931ff0
    move_file(dest.begin, backup.begin, 1);
  }

  // 0x00689402..0x00689406: the promotion itself; the return value is dropped.
  move_file(src.begin, dest.begin, 1);

  // 0x0068940f CALL 0x00931fa0 / 0x00689418 TEST AL,AL / 0x0068941a JZ
  if (file_exists(backup.begin) != 0) {
    // 0x00689420 PUSH EDX / 0x00689421 CALL 0x00931fd0
    delete_file(backup.begin);
  }

  // Tail: 0x00689429..0x006894b5, the same guarded release applied in reverse
  // order to backup, src, dest, base_copy, base and the two name temporaries.
  free_string(backup);
  free_string(src);
  free_string(dest);
  free_string(base_copy);
  free_string(base);
  free_string(old_suffix_string);
  free_string(dest_name_string);
  free_string(source_name_string);

  // 0x006894c0 MOV dword ptr FS:[0x0],ECX / 0x006894c7 ADD ESP,0x6c / RET.
  // 0x6c is 0x60 frame + 4 saved registers + 8 bytes of arguments, so the
  // callee drops its own arguments and the caller owns no cleanup.
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
