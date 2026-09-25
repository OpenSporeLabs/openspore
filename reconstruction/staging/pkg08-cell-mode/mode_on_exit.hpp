#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-08 reconstruction requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-08 target pointers are 32-bit");
static_assert(sizeof(std::int32_t) == 4, "PKG-08 target words are 32-bit");
static_assert(sizeof(float) == 4, "PKG-08 target floats are 32-bit");

namespace openspore::reconstruction::pkg08_cell_mode {

struct OpaqueMode;
struct OpaqueRecord;
struct OpaqueService;

using OpaqueIterator = std::int32_t;

struct OpaqueGlobalViews {
  std::byte* cell_game_016b3c04 = nullptr;
  const float* source_016b3be0 = nullptr;
  const float* source_016b3be4 = nullptr;
  const float* source_016b3be8 = nullptr;
  const float* source_016b3bec = nullptr;
  const float* source_016b3bf0 = nullptr;
  const std::uint32_t* source_016b3bf4 = nullptr;
  const std::uint32_t* source_016b3bf8 = nullptr;
  const std::uint32_t* source_016b3bfc = nullptr;
  std::uint32_t* destination_01550a84 = nullptr;
  std::uint32_t* destination_01550ad8 = nullptr;
  float* destination_01550adc = nullptr;
  float* destination_01550ae0 = nullptr;
  float* destination_01550ae4 = nullptr;
  float* destination_01550aec = nullptr;
  float* destination_01550af0 = nullptr;
  std::uint32_t* destination_0166c004 = nullptr;
};

using Helper00e53580 = void (*)();
using IteratorBegin00e31100 = OpaqueIterator (*)();
using IteratorAccess00b72230 = OpaqueRecord* (*)(OpaqueMode*, OpaqueIterator*);
using Record00e7e130 = void (*)(OpaqueMode*, OpaqueRecord*, float,
                                std::uint32_t, std::uint32_t);
using IteratorCleanup00b72110 = void (*)(OpaqueMode*);
using ServiceAcquire0067ddd0 = OpaqueService* (*)();
using ServiceVtable0098 = void (*)(OpaqueService*, std::uint32_t,
                                   std::uint32_t);
using Helper00e64a00 = void (*)();
using Helper00e82d40 = void (*)();

struct NativePorts {
  static constexpr char boundary_metadata[] =
      "00e7fc00: ECX entry mode, no ordinary stack arguments, void-like "
      "return, plain RET, Ghidra unknown calling convention; package globals "
      "remove the normalized C++ argument seam; "
      "00e53580: no explicit arguments, ECX ignored; "
      "00e31100: no explicit arguments, EAX iterator; "
      "00b72230: ECX iterator owner, stack iterator address, EAX record, "
      "RET 4; "
      "00e7e130: normalized owner/record/(float zero, zero, one); hidden EDI "
      "record, ECX owner residue, three semantic stack arguments; not an "
      "ordinary native pointer-equivalent signature; void-like; "
      "00b72110: ECX iterator owner, void plain RET; "
      "0067ddd0: no explicit arguments, EAX service; "
      "service vtable +0x98: ECX service, stack seven/zero, void-like; "
      "00e64a00 and 00e82d40: no explicit arguments, void-like";

  Helper00e53580 helper_00e53580 = nullptr;
  IteratorBegin00e31100 iterator_begin_00e31100 = nullptr;
  IteratorAccess00b72230 iterator_access_00b72230 = nullptr;
  Record00e7e130 record_00e7e130 = nullptr;
  IteratorCleanup00b72110 iterator_cleanup_00b72110 = nullptr;
  ServiceAcquire0067ddd0 service_acquire_0067ddd0 = nullptr;
  ServiceVtable0098 service_vtable_0098 = nullptr;
  Helper00e64a00 helper_00e64a00 = nullptr;
  Helper00e82d40 helper_00e82d40 = nullptr;
};

extern OpaqueGlobalViews g_mode_on_exit_globals;
extern NativePorts g_mode_on_exit_ports;

extern "C" void __thiscall cell_mode_on_exit_00e7fc00(OpaqueMode* mode);

}
