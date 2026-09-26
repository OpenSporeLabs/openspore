#include "sporepedia_641cd0.hpp"

namespace openspore::reconstruction::pkg_sporepedia_641cd0_wave12 {

namespace {

inline SporepediaRefCounted *as_ref(std::uint32_t word) {
  return reinterpret_cast<SporepediaRefCounted *>(
      static_cast<std::uintptr_t>(word));
}

inline std::uint32_t as_word(void *pointer) {
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(pointer));
}

// The sequence inlined at 0x00641dd0..0x00641df1, which is the body of
// 0x00b5f950: add-ref the new value, store it, release the displaced one.
void assign_ref_inlined(std::uint32_t *slot, std::uint32_t value) {
  SporepediaRefCounted *previous = as_ref(*slot);
  SporepediaRefCounted *fresh = as_ref(value);
  if (value == *slot) {
    return;
  }
  if (fresh != nullptr) {
    fresh->vtable->add_ref(fresh);
  }
  *slot = value;
  if (previous != nullptr) {
    previous->vtable->release(previous);
  }
}

} // namespace

// ---------------------------------------------------------------------------
// Recovered semantics
// ---------------------------------------------------------------------------
//
// Order of operations, matching the body instruction for instruction:
//
//   block.out_handle = 0
//   block.w0         = self->field_04
//   block.w1         = 0x030bdee3          (overwrites the self->field_08
//   block.w2         = self->field_0c      store made at 0x00641ce0)
//   manager          = App::IGameModeManager::Get()
//   if (flag != 0) {                      (0x00641d02, JZ to 0x00641d82)
//     if (block.out_handle) { ... }       provably dead: still zero here
//     if (self->ref_70) { self->ref_70 = 0; release(old); }
//     if (manager->dispose(&block.w0, &self->ref_70, &block.out_handle,
//                          0, 0, 0, 0, 0)) {
//       if (block.out_handle) {
//         self->ref_1c = manager assign of
//             block.out_handle->query_by_type(0x030bdee3)
//       }
//     }
//   } else {
//     if (block.out_handle) { ... }       provably dead: still zero here
//     if (manager->initialize(&block.w0, &block.out_handle, 0, 0, 0, 0)) {
//       fresh = block.out_handle
//                   ? block.out_handle->query_by_type(0x030bdee3)
//                   : 0;
//       assign_ref_inlined(&self->ref_1c, fresh);
//     }
//   }
//   if (block.out_handle) release(block.out_handle);
//   return;                               (RET 0x4)
//
// The two blocks guarded by `if (block.out_handle)` that sit before either
// manager call are unreachable: 0x00641cf5 is the only write to that word up
// to those tests, and it stores zero.
void Sporepedia_00641cd0_model(SporepediaAssetData *self, std::uint8_t flag,
                               const Sporepedia641cd0Ports &ports) {
  SporepediaInitBlock block;
  block.out_handle = 0;
  block.w0 = self->field_04;
  block.w1 = kPollenMetadataTag;
  block.w2 = self->field_0c;

  SporepediaGameModeManager *manager = ports.get_manager_0067dcd0();

  if (flag != 0) {
    if (block.out_handle != 0) {
      SporepediaHandle *stale =
          reinterpret_cast<SporepediaHandle *>(as_word(&block.out_handle));
      block.out_handle = 0;
      stale->vtable->release(stale);
    }
    if (self->ref_70 != 0) {
      SporepediaRefCounted *stale = as_ref(self->ref_70);
      self->ref_70 = 0;
      stale->vtable->release(stale);
    }
    if (manager->vtable->dispose(manager, &block.w0, &self->ref_70,
                                 &block.out_handle, 0, 0, 0, 0, 0) != 0) {
      if (block.out_handle != 0) {
        SporepediaHandle *handle = reinterpret_cast<SporepediaHandle *>(
            as_word(&block.out_handle));
        std::uint32_t fresh =
            as_word(handle->vtable->query_by_type(handle, kPollenMetadataTag));
        ports.assign_ref_00b5f950(&self->ref_1c, fresh);
      }
    }
  } else {
    if (block.out_handle != 0) {
      SporepediaHandle *stale =
          reinterpret_cast<SporepediaHandle *>(as_word(&block.out_handle));
      block.out_handle = 0;
      stale->vtable->release(stale);
    }
    if (manager->vtable->initialize(manager, &block.w0, &block.out_handle, 0,
                                    0, 0, 0) != 0) {
      std::uint32_t fresh = 0;
      if (block.out_handle != 0) {
        SporepediaHandle *handle = reinterpret_cast<SporepediaHandle *>(
            as_word(&block.out_handle));
        fresh =
            as_word(handle->vtable->query_by_type(handle, kPollenMetadataTag));
      }
      assign_ref_inlined(&self->ref_1c, fresh);
    }
  }

  if (block.out_handle != 0) {
    SporepediaHandle *handle =
        reinterpret_cast<SporepediaHandle *>(as_word(&block.out_handle));
    handle->vtable->release(handle);
  }
}

#if defined(__i386__) && (defined(__GNUC__) || defined(__clang__))
// Byte-exact transcription of the 315 bytes at 0x00641cd0..0x00641e0a. The
// frame offsets are the original ones: the body reserves 0x10 (SUB ESP,0x10)
// and pushes EBP, ESI, EDI, so the block sits at entry_ESP-0x10 and the flag
// at entry_ESP+4. Nothing is elided, including the dead store of
// self->field_08 into block+0x08 at 0x00641ce0 that 0x00641ced overwrites.
extern "C" __attribute__((naked)) void
Sporepedia_00641cd0_raw(SporepediaAssetData *, std::uint32_t) {
  __asm__("subl $0x10, %esp\n\t"                    // 0x00641cd0
          "pushl %ebp\n\t"                           // 0x00641cd3
          "movl %ecx, %ebp\n\t"                      // 0x00641cd4
          "movl 0x8(%ebp), %ecx\n\t"                 // 0x00641cd6
          "movl 0x4(%ebp), %eax\n\t"                 // 0x00641cd9
          "movl 0xc(%ebp), %edx\n\t"                 // 0x00641cdc
          "pushl %esi\n\t"                           // 0x00641cdf
          "movl %ecx, 0x10(%esp)\n\t"                // 0x00641ce0 dead store
          "pushl %edi\n\t"                           // 0x00641ce4
          "movl %eax, 0x10(%esp)\n\t"                // 0x00641ce5 block.w0
          "movl %edx, 0x18(%esp)\n\t"                // 0x00641ce9 block.w2
          "movl $0x30bdee3, 0x14(%esp)\n\t"          // 0x00641ced block.w1
          "movl $0, 0xc(%esp)\n\t"                   // 0x00641cf5 out_handle
          "call sporepedia_0067dcd0_app_igamemodemanager_get\n\t" // 0x00641cfd
          "cmpb $0, 0x20(%esp)\n\t"                  // 0x00641d02 the flag
          "movl 0xc(%esp), %ecx\n\t"                 // 0x00641d07 out_handle
          "jz 4f\n\t"                                // 0x00641d0b
          "movl %eax, %edi\n\t"                      // 0x00641d0d manager
          "testl %ecx, %ecx\n\t"                     // 0x00641d0f
          "jz 2f\n\t"                                // 0x00641d11 always taken
          "movl $0, 0xc(%esp)\n\t"                   // 0x00641d13
          "movl (%ecx), %eax\n\t"                    // 0x00641d1b
          "movl 0x4(%eax), %edx\n\t"                 // 0x00641d1d
          "call *%edx\n\t"                           // 0x00641d20
          "2:\n\t"                                   // 0x00641d22
          "movl 0x70(%ebp), %ecx\n\t"                // 0x00641d22 self->ref_70
          "leal 0x70(%ebp), %esi\n\t"                // 0x00641d25
          "testl %ecx, %ecx\n\t"                     // 0x00641d28
          "jz 3f\n\t"                                // 0x00641d2a
          "movl $0, (%esi)\n\t"                      // 0x00641d2c
          "movl (%ecx), %eax\n\t"                    // 0x00641d32
          "movl 0x4(%eax), %edx\n\t"                 // 0x00641d34
          "call *%edx\n\t"                           // 0x00641d37
          "3:\n\t"                                   // 0x00641d39
          "movl (%edi), %eax\n\t"                    // 0x00641d39
          "movl 0x10(%eax), %eax\n\t"                // 0x00641d3b vtable+0x10
          "pushl $0\n\t"                             // 0x00641d3e
          "pushl $0\n\t"                             // 0x00641d40
          "pushl $0\n\t"                             // 0x00641d42
          "pushl $0\n\t"                             // 0x00641d44
          "pushl $0\n\t"                             // 0x00641d46
          "leal 0x20(%esp), %ecx\n\t"                // 0x00641d48 &out_handle
          "pushl %ecx\n\t"                           // 0x00641d4c
          "pushl %esi\n\t"                           // 0x00641d4d &self->ref_70
          "leal 0x2c(%esp), %edx\n\t"                // 0x00641d4e &block.w0
          "pushl %edx\n\t"                           // 0x00641d52
          "movl %edi, %ecx\n\t"                      // 0x00641d53
          "call *%eax\n\t"                           // 0x00641d55 dispose
          "testb %al, %al\n\t"                       // 0x00641d57
          "jz 6f\n\t"                                // 0x00641d59
          "movl 0xc(%esp), %ecx\n\t"                 // 0x00641d5f out_handle
          "testl %ecx, %ecx\n\t"                     // 0x00641d63
          "jz 5f\n\t"                                // 0x00641d65 -> epilogue
          "movl (%ecx), %edx\n\t"                    // 0x00641d6b
          "movl 0xc(%edx), %eax\n\t"                 // 0x00641d6d vtable+0x0C
          "pushl $0x30bdee3\n\t"                     // 0x00641d70
          "call *%eax\n\t"                           // 0x00641d75
          "pushl %eax\n\t"                           // 0x00641d77
          "leal 0x1c(%ebp), %ecx\n\t"                // 0x00641d78 &self->ref_1c
          "call sporepedia_00b5f950_intrusive_ptr_assign\n\t" // 0x00641d7b
          "jmp 6f\n\t"                               // 0x00641d80
          "4:\n\t"                                   // 0x00641d82
          "movl %eax, %esi\n\t"                      // 0x00641d82 manager
          "testl %ecx, %ecx\n\t"                     // 0x00641d84
          "jz 7f\n\t"                                // 0x00641d86 always taken
          "movl $0, 0xc(%esp)\n\t"                   // 0x00641d88
          "movl (%ecx), %edx\n\t"                    // 0x00641d90
          "movl 0x4(%edx), %eax\n\t"                 // 0x00641d92
          "call *%eax\n\t"                           // 0x00641d95
          "7:\n\t"                                   // 0x00641d97
          "movl (%esi), %edx\n\t"                    // 0x00641d97
          "movl 0xc(%edx), %edx\n\t"                 // 0x00641d99 vtable+0x0C
          "pushl $0\n\t"                             // 0x00641d9c
          "pushl $0\n\t"                             // 0x00641d9e
          "pushl $0\n\t"                             // 0x00641da0
          "pushl $0\n\t"                             // 0x00641da2
          "leal 0x1c(%esp), %eax\n\t"                // 0x00641da4 &out_handle
          "pushl %eax\n\t"                           // 0x00641da8
          "leal 0x24(%esp), %ecx\n\t"                // 0x00641da9 &block.w0
          "pushl %ecx\n\t"                           // 0x00641dad
          "movl %esi, %ecx\n\t"                      // 0x00641dae
          "call *%edx\n\t"                           // 0x00641db0 initialize
          "testb %al, %al\n\t"                       // 0x00641db2
          "jz 6f\n\t"                                // 0x00641db4
          "movl 0xc(%esp), %ecx\n\t"                 // 0x00641db6 out_handle
          "testl %ecx, %ecx\n\t"                     // 0x00641dba
          "jz 8f\n\t"                                // 0x00641dbc
          "movl (%ecx), %eax\n\t"                    // 0x00641dbe
          "movl 0xc(%eax), %edx\n\t"                 // 0x00641dc0 vtable+0x0C
          "pushl $0x30bdee3\n\t"                     // 0x00641dc3
          "call *%edx\n\t"                           // 0x00641dc8
          "movl %eax, %esi\n\t"                      // 0x00641dca
          "jmp 9f\n\t"                               // 0x00641dcc
          "8:\n\t"                                   // 0x00641dce
          "xorl %esi, %esi\n\t"                      // 0x00641dce
          "9:\n\t"                                   // 0x00641dd0
          "movl 0x1c(%ebp), %edi\n\t"                // 0x00641dd0 self->ref_1c
          "cmpl %esi, %edi\n\t"                      // 0x00641dd3
          "jz 6f\n\t"                                // 0x00641dd5
          "testl %esi, %esi\n\t"                     // 0x00641dd7
          "jz 10f\n\t"                               // 0x00641dd9
          "movl (%esi), %eax\n\t"                    // 0x00641ddb
          "movl (%eax), %edx\n\t"                    // 0x00641ddd vtable+0x00
          "movl %esi, %ecx\n\t"                      // 0x00641ddf
          "call *%edx\n\t"                           // 0x00641de1 add ref
          "10:\n\t"                                  // 0x00641de3
          "movl %esi, 0x1c(%ebp)\n\t"                // 0x00641de3
          "testl %edi, %edi\n\t"                     // 0x00641de6
          "jz 6f\n\t"                                // 0x00641de8
          "movl (%edi), %eax\n\t"                    // 0x00641dea
          "movl 0x4(%eax), %edx\n\t"                 // 0x00641dec vtable+0x04
          "movl %edi, %ecx\n\t"                      // 0x00641def
          "call *%edx\n\t"                           // 0x00641df1 release
          "6:\n\t"                                   // 0x00641df3
          "movl 0xc(%esp), %ecx\n\t"                 // 0x00641df3 out_handle
          "testl %ecx, %ecx\n\t"                     // 0x00641df7
          "jz 5f\n\t"                                // 0x00641df9 -> epilogue
          "movl (%ecx), %eax\n\t"                    // 0x00641dfb
          "movl 0x4(%eax), %edx\n\t"                 // 0x00641dfd
          "call *%edx\n\t"                           // 0x00641e00
          "5:\n\t"                                   // 0x00641e02
          "popl %edi\n\t"                            // 0x00641e02
          "popl %esi\n\t"                            // 0x00641e03
          "popl %ebp\n\t"                            // 0x00641e04
          "addl $0x10, %esp\n\t"                     // 0x00641e05
          "ret $4\n\t");                             // 0x00641e08
}
#else
extern "C" void Sporepedia_00641cd0_raw(SporepediaAssetData *,
                                        std::uint32_t) {}
#endif

#if defined(__i386__) && (defined(__GNUC__) || defined(__clang__))
// Entry: [esp]=return address, [esp+4]=receiver, [esp+8]=flag. Rebuilds the
// original __thiscall frame and transfers into the body above. The body's own
// RET 4 pops the staged argument and returns to this bridge's caller, so
// control never comes back through this epilogue.
extern "C" __attribute__((naked)) void
Sporepedia_00641cd0_host_bridge(SporepediaAssetData *, std::uint32_t) {
  __asm__("movl 4(%esp), %ecx\n\t"  // receiver into ECX
          "subl $4, %esp\n\t"
          "movl 8(%esp), %eax\n\t"   // flag
          "movl %eax, 4(%esp)\n\t"   // [esp+4] := flag
          "jmp Sporepedia_00641cd0_raw\n\t");
}
#else
extern "C" void Sporepedia_00641cd0_host_bridge(SporepediaAssetData *,
                                                std::uint32_t) {}
#endif

void Sporepedia_00641cd0(SporepediaAssetData *self, std::uint8_t flag) {
#if defined(__i386__) && (defined(__GNUC__) || defined(__clang__))
  Sporepedia_00641cd0_host_bridge(self, static_cast<std::uint32_t>(flag));
#else
  Sporepedia641cd0Ports ports;
  ports.get_manager_0067dcd0 = &sporepedia_0067dcd0_app_igamemodemanager_get;
  ports.assign_ref_00b5f950 = &sporepedia_00b5f950_intrusive_ptr_assign;
  Sporepedia_00641cd0_model(self, flag, ports);
#endif
}

} // namespace openspore::reconstruction::pkg_sporepedia_641cd0_wave12
