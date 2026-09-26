// reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp
//
// Opaque / partially-known receiver types for OpenSpore wave-13 batch b07
// (package wave13-w1-core-b07, binary SPORE/SporeBin/SporeApp.exe 3.1.0.22,
// image base 0x00400000,
// sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// Every offset in this header is proved by a named instruction in the
// original binary; the instruction address is quoted in the comment.
// Unobserved bytes are declared as explicit padding, never invented.
//
// Addresses are modelled as 32-bit words so the model stays host
// independent; the original is x86-32 and every pointer there is 4 bytes.

#ifndef OPENSPORE_B07_OPAQUE_TYPES_HPP
#define OPENSPORE_B07_OPAQUE_TYPES_HPP

#include <cstddef>
#include <cstdint>

namespace openspore {
namespace b07 {

using Word = std::uint32_t;

inline constexpr Word kInvalidWord = 0xffffffffu;

// Pointer <-> 32-bit-word conversion. On the x86-32 target this is lossless;
// the model is only meaningful for 32-bit receivers, which is what the
// original is.
template <typename T>
inline Word word_of(T* pointer) {
    return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

template <typename T>
inline T* pointer_at(Word word) {
    return reinterpret_cast<T*>(static_cast<std::uintptr_t>(word));
}

// ---------------------------------------------------------------------------
// 0x00643a40 -- rbtree node, 0x18 bytes (0x00579b50 asserts an allocation
// size of 0x18, and EASTL's rbtree_node_base is 13 bytes padded to 16 with
// the value at +0x10).
//
// ~/apps/Spore-ModAPI/EASTL-3.02.01/include/EASTL/internal/red_black_tree.h
// declares rbtree_node_base { mpNodeRight; mpNodeLeft; mpNodeParent;
// char mColor; } followed by rbtree_node::mValue, which is exactly this
// layout.
struct MapNode {
    Word mpNodeRight;   // +0x00  0x00643a64 MOV EAX,dword ptr [EAX]
    Word mpNodeLeft;    // +0x04  0x00643a5f MOV EAX,dword ptr [EAX + 0x4]
    Word mpNodeParent;  // +0x08  unobserved in this body
    Word mColorAndPad;  // +0x0C  char mColor + 3 unobserved bytes
    Word key;           // +0x10  0x00643a58 CMP dword ptr [EAX + 0x10],EBX
    Word mapped;        // +0x14  returned as the mapped-slot address
};

static_assert(sizeof(MapNode) == 0x18,
              "0x00579b50 asserts node size 0x18");

// ---------------------------------------------------------------------------
// 0x00643a40 -- the ordered-map receiver, 0x1C bytes.
//
// Identity is EASTL: 0x00579b50 carries the assert string
// "c:\BuildAgent\max-spore001-spore\CMBuild\SporeEP1_RL\Core\UTFKernel\"
// "EASTL\include\EASTL/allocator.h". The anchor (rbtree_node_base, 13 bytes
// padded to 16) starts at +0x04:
//   0x00643a48 LEA ESI,[ECX + 0x4]           -> anchor address == end()
//   0x00643a40 MOV EAX,dword ptr [ECX + 0xc] -> anchor.mpNodeParent == root
//   0x00579b50 *(int *)(param_1 + 0x14)++    -> +0x14 is the node counter
// The 0x1C byte stride between the two maps reached by 0x00644510 (this+0x10)
// and 0x00644530 (this+0x2c) matches this total size.
struct OrderedMap {
    Word baseWord;      // +0x00  unobserved rb_base head word
    Word anchorRight;   // +0x04  anchor.mpNodeRight  (rbegin)
    Word anchorLeft;    // +0x08  anchor.mpNodeLeft   (begin)
    Word anchorParent;  // +0x0C  anchor.mpNodeParent (root)
    Word anchorColor;   // +0x10  char mColor + 3 unobserved pad bytes
    Word nodeCount;     // +0x14  mnSize, incremented by 0x00579b50
    Word allocator;     // +0x18  mAllocator
};

static_assert(sizeof(OrderedMap) == 0x1c,
              "anchor at +0x04 padded to 16 puts mnSize at +0x14");

// ---------------------------------------------------------------------------
// 0x00b8dec0 -- contiguous 4-byte element block.
//   0x00b8dec0 MOV EDX,dword ptr [ECX + 0x160]
//   0x00b8dec6 SUB EDX,dword ptr [ECX + 0x15c]
//   0x00b8ded0 SAR EDX,0x2                    -> 4-byte elements
// The element type is unestablished (caller 0x00c5c860 uses the returned word
// as an object pointer), so an element is a raw word.
struct ElementBlock {
    Word head[0x15c / 4];  // +0x000 unobserved receiver head
    Word begin;            // +0x15c  first element
    Word end;              // +0x160  one past the last element
};

static_assert(sizeof(ElementBlock) == 0x164, "begin/end sit at +0x15c/+0x160");

// ---------------------------------------------------------------------------
// 0x00bca0c0 -- fixed table of eight 0x44-byte records; the first record
// starts at this+0x20.
//   0x00bca0cf LEA EAX,[ECX + 0x28]   -> EAX walks record field +0x04
//   0x00bca105 MOVZX EAX,word ptr [EAX + -0x8]  -> 16-bit id at record+0x00
//   0x00bca0f4 ADD EAX,0x44           -> 0x44 stride
//   0x00bca0f7 CMP EDX,0x8            -> at most eight slots
struct TableRecord {
    std::uint16_t id;       // +0x00  0x00bca105 MOVZX EAX,word ptr [EAX-0x8]
    std::uint16_t idPad;    // +0x02  unobserved
    Word key1;              // +0x04  0x00bca0d8 CMP dword ptr [EAX-0x4],EBX
    Word key2;              // +0x08  0x00bca0dd CMP dword ptr [EAX],EDI
    Word body[4];           // +0x0C  unobserved
    Word key3;              // +0x1C  0x00bca0e5 CMP dword ptr [EAX+0x14],ESI
    Word key4;              // +0x20  0x00bca0ee CMP dword ptr [EAX+0x18],ECX
    Word tail[8];           // +0x24  unobserved, record ends at +0x44
};

static_assert(sizeof(TableRecord) == 0x44, "0x00bca0c0 uses a 0x44 stride");

struct RecordTable {
    Word head[0x20 / 4];  // +0x00 unobserved receiver head
    TableRecord slots[8];
};

// ---------------------------------------------------------------------------
// 0x00c04750 -- 0x4e0-stride record objects.
//   0x00c04779 IMUL EAX,EAX,0x4e0
//   0x00c0477f ADD EAX,dword ptr [ESI + 0x70]
// build a pointer into a 0x4e0-stride block. Callers then read +0x4a8
// (0x00c047bc), +0x4ec (0x00c32f2f) and +0x504 (0x00bba531) inside a record.
inline constexpr Word kRecordStride = 0x4e0;

// ---------------------------------------------------------------------------
// 0x0060d860 -- receiver; only one field is observed in this body.
//   0x0060d863 CMP dword ptr [ECX + 0x58],0x0
struct ModeOwner {
    Word pad58;  // +0x58 guard: the entire body is skipped when it is zero
};

// ---------------------------------------------------------------------------
// 0x0060d860 -- 0x14-byte key/param descriptor built in the caller's frame at
// frame+0x0c, plus the two halves of the 8-byte key it is filled from.
//   0x0060d8d4 LEA ECX,[ESP + 0x14]              -> descriptor address
//   0x0060d8d8 MOV word ptr [ESP + 0x24],AX      -> zero flags  (+0x10)
//   0x0060d8ce MOV word ptr [ESP + 0x22],CX      -> zero kind   (+0x12)
//   0x0060cfa0 writes head[0] = key[0], head[1] = key[1]
//   0x0060d8f3 TEST byte ptr [ESP + 0x20],0x4    -> flags bit 0x4
struct KeyDescriptor {
    Word head[4];         // +0x00 .. +0x0F  written by 0x0060cfa0
    std::uint16_t flags;  // +0x10
    std::uint16_t kind;   // +0x12
};

static_assert(sizeof(KeyDescriptor) == 0x14,
              "the descriptor ends at frame+0x20 in the 0x20-byte frame");

// ---------------------------------------------------------------------------
// 0x0060d860 -- objects reached through 0x00552450. Only the vtable word is
// observed (0x0060d90e MOV EDX,dword ptr [ECX] then 0x0060d910 MOV EAX,
// dword ptr [EDX + 0x4] and 0x0060d913 CALL EAX), so the layout stops there.
// 0x005507a0 returns object+0x18, which is where the 8-byte key pair lives.
struct ResolvedObject {
    Word vtable;  // +0x00 slot +0x4 is the release/slot-1 entry
};

// ---------------------------------------------------------------------------
// 0x0060d860 -- the mode descriptor passed as the second argument.
// 0x00552450 reads word 0 as a vtable pointer and word 2, and copies
// {word0, 0, 0x30bdee3} into a local IGameModeManager-shaped object.
struct ModeDescriptor {
    Word vtable;  // +0x00
    Word word4;   // +0x04 unobserved
    Word word8;   // +0x08 read by 0x00552450
};

// ---------------------------------------------------------------------------
// 0x00c30c80 -- receiver; the only observed field is the 32-bit record id.
//   0x00c30c80 MOV EAX,dword ptr [ECX + 0xb0]
//   0x00c30c86 CMP EAX,-0x1   -> -1 is the "unset" sentinel
struct RecordIdOwner {
    Word head[0xb0 / 4];  // +0x000 unobserved receiver head
    Word fieldB0;         // +0x0b0 record id, -1 when unset
};

// ---------------------------------------------------------------------------
// 0x00c04750 -- receiver of the record-pointer computation.
//   0x00b18530 reads [this + 0x1c] and returns 0 when it is -1, so the field is
//   an id with -1 as its unset value.
struct LevelOwner {
    Word head[0x1c / 4];  // +0x00 unobserved
    Word field1c;          // +0x1c id, -1 when unset
};

// ---------------------------------------------------------------------------
// Opaque ports. Declared only; no body is invented for any of them.
//
// Where the original pushes the *address* of a local as a 4-byte stack word
// (0x00643a89 LEA EAX,[ESP + 0x10], 0x0060d872 LEA EAX,[ESP + 0x4], ...), the
// model passes a real pointer: on the 32-bit original the two are identical.
using InsertWithHintFn = void (*)(Word container, Word* keySlot, Word candidateHint,
                                 const Word* valuePair, Word unusedFlag);
using GlobalHandleTableFn = Word (*)(void);
using ResolveHandleFn = Word (*)(Word handleTable, Word handle);
using RecordAccessorFn = Word (*)(Word recordOwner);
using CreateFromModeDescriptorFn = Word (*)(const ModeDescriptor* modeDescriptor, Word* outObject);
using KeyPairAddrFn = Word (*)(Word object);
using JobManagerFn = Word (*)(void);
using MakeKeyDescriptorFn = void (*)(KeyDescriptor* keyDescriptor, const Word* keyPair);
using SubmitJobFn = Word (*)(Word jobManager, Word arg1, const KeyDescriptor* keyDescriptor);
using ReportKeyFlagsFn = void (*)(KeyDescriptor* keyDescriptor, Word clearFlags);
using VirtualReleaseFn = void (*)(Word object);

// Ports specific to 0x00c04750, declared next to the function that uses them.
using CurrentModeFn = Word (*)(void);
using ResolveSubObjectFn = Word (*)(Word self);
using CurrentIndexFn = Word (*)(void);

}  // namespace b07
}  // namespace openspore

#endif  // OPENSPORE_B07_OPAQUE_TYPES_HPP
