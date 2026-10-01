#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "wave6 resource reconstruction requires an x86-32 target"
#endif

namespace openspore::reconstruction::wave6_resource_typename_map {

using TargetWord = std::uint32_t;

// 0x008dff30 compares the type argument against this word (CMP dword ptr
// [ESP+0x28],-0x1 at 0x008dff39) and then walks every bucket of the map
// instead of performing a single lookup.
inline constexpr TargetWord kAllTypesQuery = 0xffffffffu;

// The chained-hash node stores a half-open range of 8-byte entries at +0x04 /
// +0x08; the loop stride at 0x008dffdc and 0x008e0094 is ADD ESI,0x8.
struct TypenameChunkEntry {
  TargetWord value;      // +0x00, the only word this function reads
  TargetWord auxiliary;  // +0x04, never read by this function
};

// Chain node of the map at receiver+0x30. Offsets are taken from
// 0x008dff90 (MOV ECX,[EBP+0x8] / MOV ESI,[EBP+0x4]) and 0x008dfff2
// (MOV EBP,[EBP+0x18]); the callee at 0x00aea1b0 confirms +0x00 is the key and
// +0x18 the chain link (node[6] in its decompilation).
struct TypeChunkNode {
  TargetWord type_id;                // +0x00
  TypenameChunkEntry* chunk_first;   // +0x04
  TypenameChunkEntry* chunk_last;    // +0x08
  std::array<std::uint8_t, 0x0c> opaque_0c_17;
  TypeChunkNode* next;               // +0x18
};

// Map header observed at receiver+0x30: [ESI+4] / [ESI+8] at 0x008e0036 and
// 0x008e0039, and [ECX+0x34] / [ECX+0x38] in the all-types scan. The slot at
// index bucket_count holds the end sentinel; the same 36-byte map shape is
// used by the already reconstructed Resource::cResourceManager::Initialize
// (resource_manager_initialize_008de530, wave6-resources).
struct TypeChunkMap {
  TargetWord opaque_00;
  TypeChunkNode** buckets;
  TargetWord bucket_count;
};

// The thiscall map lookup at 0x00aea1b0 writes this 8-byte pair through its
// second stack argument: [0] is the node, [1] the bucket slot (or
// &buckets[bucket_count] on a miss).
struct TypeChunkIterator {
  TypeChunkNode* node;
  TypeChunkNode** slot;
};

// Destination intrusive list node. Each element costs one 0x0c byte
// allocation (PUSH 0x0c before CALL 0x00f473a0 at 0x008dffba and 0x008e0075)
// and the collected word lands at +0x08 (LEA ECX,[EAX+0x8]).
struct TypeNameListNode {
  TypeNameListNode* next;  // +0x00
  TypeNameListNode* prev;  // +0x04
  TargetWord value;        // +0x08
};

// Receiver carrier: only +0x30 is touched, by the map lookup path
// (LEA ESI,[ECX+0x30] at 0x008e0026) and by the all-types scan.
struct ResourceManagerCarrier {
  std::array<std::uint8_t, 0x30> opaque_00_2f;
  TypeChunkMap type_chunks;  // +0x30
};

// EASTL allocation arguments observed at 0x008dffa0 / 0x008e0060:
// allocate(0x0c, 0x013f2150, 0, 0, 0x013ebb38, 0xd1). The decompiler resolves
// 0x013f2150 as the literal "EASTL" and 0x013ebb38 as the EASTL allocator.h
// include path.
struct TypeNameMapServices {
  TypeNameListNode* (*allocate_node)(TargetWord bytes, TargetWord name,
                                     TargetWord line, TargetWord flags,
                                     TargetWord file, TargetWord file_line);
  void (*lookup_chunk)(TypeChunkMap* map, TypeChunkIterator* out,
                       TargetWord* type_id);
};

#if defined(_MSC_VER)
#define WAVE6_TYPENAME_THISCALL __thiscall
#else
#define WAVE6_TYPENAME_THISCALL __attribute__((thiscall))
#endif

inline constexpr TargetWord kListNodeBytes = 0x0cu;
inline constexpr TargetWord kAllocatorName = 0x013f2150u;
inline constexpr TargetWord kAllocatorFile = 0x013ebb38u;
inline constexpr TargetWord kAllocatorLine = 0xd1u;

TypeNameMapServices& type_name_map_services();
void set_type_name_map_services(const TypeNameMapServices* services);

// Resource::cResourceManager::GetTypenameFromType
//   receiver  ECX   cResourceManager*
//   arg1      ESP+0x04  insertion position (a TypeNameListNode*, typically a
//                        list sentinel)
//   arg2      ESP+0x08  queried type id, or 0xffffffff for every type
//   returns   EAX   number of list nodes appended (full 32-bit counter)
// Both returns are MOV EAX,EDI at 0x008e0016 and 0x008e00a2 and both sites
// close with RET 0x8.
std::uint32_t WAVE6_TYPENAME_THISCALL get_typename_from_type_008dff30(
    ResourceManagerCarrier* manager, TypeNameListNode* position,
    TargetWord type_id);

#undef WAVE6_TYPENAME_THISCALL

static_assert(sizeof(void*) == 4, "wave6 pointers are 32-bit");
static_assert(sizeof(TypenameChunkEntry) == 8, "chunk entry extent");
static_assert(sizeof(TypeNameListNode) == 12, "list node extent");
static_assert(offsetof(TypeNameListNode, value) == 8, "list node value offset");
static_assert(offsetof(TypeChunkNode, chunk_first) == 4,
              "chunk range begin offset");
static_assert(offsetof(TypeChunkNode, chunk_last) == 8,
              "chunk range end offset");
static_assert(offsetof(TypeChunkNode, next) == 0x18, "chain link offset");
static_assert(offsetof(TypeChunkMap, buckets) == 4, "map bucket pointer offset");
static_assert(offsetof(TypeChunkMap, bucket_count) == 8, "map bucket count offset");
static_assert(offsetof(ResourceManagerCarrier, type_chunks) == 0x30,
              "manager map offset");
static_assert(sizeof(TypeChunkMap) == 12, "map header extent");
static_assert(kListNodeBytes == sizeof(TypeNameListNode),
              "allocation size matches the list node");

}
