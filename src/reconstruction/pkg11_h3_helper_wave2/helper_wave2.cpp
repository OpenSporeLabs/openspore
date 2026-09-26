#include "helper_wave2.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg11_h3_helper_wave2 {

PendingGrowthPorts g_pending_growth_ports_00aea5d0 = {nullptr, nullptr};

namespace {

std::uintptr_t address(OpaqueNoun** pointer) {
  return reinterpret_cast<std::uintptr_t>(pointer);
}

std::size_t byte_distance(OpaqueNoun** first, OpaqueNoun** last) {
  return static_cast<std::size_t>(address(last) - address(first));
}

std::uint32_t preceding_marker(OpaqueNoun** entries) {
  std::uint32_t marker = 0;
  std::memcpy(&marker,
              reinterpret_cast<const std::uint8_t*>(entries) - sizeof(marker),
              sizeof(marker));
  return marker;
}

void retain(OpaqueNoun* noun) {
  if (noun != nullptr) {
    noun->vtable->add_ref(noun);
  }
}

void release(OpaqueNoun* noun) {
  if (noun != nullptr) {
    noun->vtable->release(noun);
  }
}

}

extern "C" void __attribute__((thiscall)) pending_vector_insert_00aea5d0(
    PendingVectorWire* pending, OpaqueNoun** position, OpaqueNoun** source) {
  OpaqueNoun** end = pending->end;
  OpaqueNoun** begin = pending->begin;
  if (address(end) != address(pending->capacity)) {
    OpaqueNoun** adjusted_source = source;
    if (address(position) <= address(source) &&
        address(source) < address(end)) {
      ++adjusted_source;
    }
    if (address(position) == address(end)) {
      OpaqueNoun* inserted = *adjusted_source;
      *position = inserted;
      retain(inserted);
      pending->end = end + 1;
      return;
    }
    if (address(position) < address(end) && begin != nullptr) {
      OpaqueNoun* previous = end[-1];
      *end = previous;
      retain(previous);
      OpaqueNoun** first = position;
      OpaqueNoun** last = end - 1;
      OpaqueNoun** result = end;
      if (last != first) {
        do {
          OpaqueNoun* shifted = last[-1];
          OpaqueNoun* replaced = result[-1];
          --last;
          --result;
          if (shifted != replaced) {
            retain(shifted);
            *result = shifted;
            release(replaced);
          }
        } while (last != first);
      }
    }
    OpaqueNoun* inserted = *adjusted_source;
    OpaqueNoun* replaced = *position;
    if (inserted != replaced) {
      retain(inserted);
      *position = inserted;
      release(replaced);
    }
    pending->end = end + 1;
    return;
  }

  const std::uint32_t old_count =
      static_cast<std::uint32_t>((address(end) - address(begin)) >> 2U);
  const std::uint32_t new_count = old_count == 0U ? 1U : old_count * 2U;
  OpaqueNoun** new_begin = nullptr;
  if (new_count != 0U) {
    new_begin = g_pending_growth_ports_00aea5d0.allocate(
        static_cast<std::size_t>(new_count) * sizeof(OpaqueNoun*));
  }

  const std::size_t prefix_bytes = byte_distance(begin, position);
  if (prefix_bytes != 0U) {
    std::memcpy(new_begin, begin, prefix_bytes);
  }
  OpaqueNoun** inserted_position =
      new_begin + prefix_bytes / sizeof(OpaqueNoun*);
  OpaqueNoun* inserted = *source;
  *inserted_position = inserted;
  retain(inserted);
  const std::size_t suffix_bytes = byte_distance(position, end);
  if (suffix_bytes != 0U) {
    std::memcpy(inserted_position + 1, position, suffix_bytes);
  }
  if (begin != nullptr && preceding_marker(begin) != 0U) {
    g_pending_growth_ports_00aea5d0.deallocate(begin);
  }

  pending->end = inserted_position + 1 + suffix_bytes / sizeof(OpaqueNoun*);
  pending->begin = new_begin;
  pending->capacity = new_begin + new_count;
}

extern "C" void __attribute__((naked)) noun_manager_logical_destroy_00b225d0(
    OpaqueNounManager*, OpaqueNoun*) {
  __asm__ volatile(
      "pushl %ebx\n\t"
      "pushl %esi\n\t"
      "movl 0xc(%esp), %esi\n\t"
      "movb $0x1, 0x20(%esi)\n\t"
      "movl (%esi), %eax\n\t"
      "movl (%eax), %edx\n\t"
      "pushl %edi\n\t"
      "movl %ecx, %edi\n\t"
      "movl %esi, %ebx\n\t"
      "movl %esi, %ecx\n\t"
      "movl %ebx, 0x10(%esp)\n\t"
      "call *%edx\n\t"
      "movl 0x84(%edi), %eax\n\t"
      "cmpl 0x88(%edi), %eax\n\t"
      "leal 0x80(%edi), %ecx\n\t"
      "jnc 1f\n\t"
      "leal 0x4(%eax), %edx\n\t"
      "movl %edx, 0x4(%ecx)\n\t"
      "testl %eax, %eax\n\t"
      "jz 2f\n\t"
      "movl %esi, (%eax)\n\t"
      "movl (%esi), %eax\n\t"
      "movl (%eax), %edx\n\t"
      "movl %esi, %ecx\n\t"
      "call *%edx\n\t"
      "jmp 2f\n\t"
      "1:\n\t"
      "leal 0x10(%esp), %edx\n\t"
      "pushl %edx\n\t"
      "pushl %eax\n\t"
      "call pending_vector_insert_00aea5d0\n\t"
      "movl 0x10(%esp), %ebx\n\t"
      "2:\n\t"
      "testl %ebx, %ebx\n\t"
      "jz 3f\n\t"
      "movl (%ebx), %eax\n\t"
      "movl 0x4(%eax), %edx\n\t"
      "movl %ebx, %ecx\n\t"
      "call *%edx\n\t"
      "3:\n\t"
      "pushl %esi\n\t"
      "movl %edi, %ecx\n\t"
      "call noun_manager_teardown_00b20d30\n\t"
      "pushl %esi\n\t"
      "movl %edi, %ecx\n\t"
      "call noun_manager_dependencies_00b201a0\n\t"
      "popl %edi\n\t"
      "popl %esi\n\t"
      "popl %ebx\n\t"
      "ret $0x4\n\t");
}

extern "C" void __attribute__((naked)) embedded_object_first_word_init_00743b50(
    OpaqueEmbeddedObject*) {
  __asm__ volatile(
      "movl %ecx, %eax\n\t"
      "movl $0x0, (%eax)\n\t"
      "ret\n\t");
}

extern "C" void __attribute__((naked)) strategy_base_constructor_00b5b960(
    OpaqueStrategyBaseWire*) {
  __asm__ volatile(
      "movl %ecx, %eax\n\t"
      "movl $0x013ef094, 0x4(%eax)\n\t"
      "xorl %edx, %edx\n\t"
      "movl %edx, 0x8(%eax)\n\t"
      "orl $-1, %ecx\n\t"
      "movl $0x01461580, (%eax)\n\t"
      "movl $0x01461578, 0x4(%eax)\n\t"
      "movl %ecx, 0xc(%eax)\n\t"
      "movl %ecx, 0x10(%eax)\n\t"
      "movl %ecx, 0x14(%eax)\n\t"
      "movl %edx, 0x18(%eax)\n\t"
      "ret\n\t");
}

}
