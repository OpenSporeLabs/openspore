#pragma once

// PKG-APP-PROPERTY-GET-WAVE15
// Reconstruction of App::PropertyList::GetProperty at VA 0x006a2530
// (SporeApp.exe 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// LAYOUT PROVENANCE (attempt 2). Every field name and offset below is read out
// of the Spore ModAPI SDK structures that the live Ghidra type database holds
// for SporeApp.exe, dumped through the bridge at 127.0.0.1:8089 on 2026-09-26:
//
//   /Spore/App/PropertyList                                 len 0x38
//   /Spore/App/PropertyList/PropertyMap                     len 0x18, a typedef
//        of /Spore/eastl/vector_map<unsigned int, App::Property>
//   /Spore/eastl/vector_map<unsigned int, App::Property>    len 0x18
//   /Spore/eastl/pair<uint, App::Property>                  len 0x18
//   /Spore/App/Property                                     len 4
//   /Spore/App/PropertyList/PropertyList__vftable           len 0x4c (19 slots)
//   /Spore/App/PropertyList/GetProperty                     function definition:
//        bool (PropertyList *this, uint32_t propertyID, Property **result)
//
// The same database also carries the prototype Ghidra already applies to the
// body: `bool App::PropertyList::GetProperty(PropertyList *this, uint32_t
// propertyID, Property **result)`, with the calling-convention field still
// `unknown`. Nothing here is inferred from a sibling body.
//
// Independently of the SDK, every offset below is re-derived from the
// 47-instruction listing of 0x006a2530 and the 33-instruction listing of its one
// direct callee 0x00612db0. The two sources agree exactly; the comments cite
// both where they meet.

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-APP-PROPERTY-GET-WAVE15 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG15_THISCALL __thiscall
#define PKG15_CDECL __cdecl
#else
#define PKG15_THISCALL __attribute__((thiscall))
#define PKG15_CDECL
#endif

namespace openspore::reconstruction::pkg_app_property_get_wave15 {

struct PropertyList;
struct PropertyListVtable;

// /Spore/App/Property, 4 bytes. SDK fields mnFlags and mnType.
// mnType is declared by the SDK as the 2-byte enum PropertyType; the
// enumerators were not recovered, so it is modelled as the raw 16-bit word and
// no property type is named here.
struct Property {
  std::int16_t mnFlags;  // +0x00
  std::uint16_t mnType;  // +0x02
};

// One element of PropertyList::mProperties: eastl::pair<uint, App::Property>,
// 0x18 bytes, so the binary's element stride is the pair's own size.
// The key half is `first` in the SDK; the value half is `second`, the 4-byte
// Property. 0x006a2530 compares only `first` (indirectly, through 0x00612db0)
// and publishes the ADDRESS of `second` to the caller.
struct PropertyEntry {
  std::uint32_t first;       // +0x00, the property id, compared against propertyID
  Property second;           // +0x04, the value; 0x006a256b forms its address
  std::uint8_t unnamed[0x10];  // +0x08..+0x17, unnamed in the SDK, never read here
};

// /Spore/eastl/vector_map<unsigned int, App::Property>, which the SDK typedef
// PropertyList::PropertyMap resolves to. It sits at receiver+0x18, so the
// receiver offsets the body uses are this type's offsets biased by 0x18.
struct PropertyMap {
  PropertyEntry* mpBegin;      // receiver+0x18, MOV EDX at 0x006a2537
  PropertyEntry* mpEnd;        // receiver+0x1c, MOV EDI at 0x006a253b
  PropertyEntry* mpCapacity;   // receiver+0x20, never read by this body
  std::uint8_t mAllocator[4];  // receiver+0x24, never read by this body
  std::int32_t garbage;        // receiver+0x28, never read by this body
  std::int32_t mValueCompare;  // receiver+0x2c; 0x006a2533 reads its LOW BYTE
                               // only (MOVZX) and pushes it
};

// /Spore/App/PropertyList, 0x38 bytes.
struct PropertyList {
  const PropertyListVtable* _vftable0;  // +0x00
  std::int32_t mnRefCount;             // +0x04
  std::uint8_t mNameKey[12];           // +0x08..+0x13, SDK ResourceKey
  void* mpFinalReleaseCallback;        // +0x14, SDK cIReleaseCallback*
  PropertyMap mProperties;             // +0x18..+0x2f, SDK PropertyMap
  PropertyList* mpParent;              // +0x30, MOV ECX at 0x006a2577. The SDK
                                       // type is intrusive_ptr<App::PropertyList>,
                                       // itself a one-word struct, so the word
                                       // at +0x30 is the parent pointer.
  std::int32_t mnOperationsDone;       // +0x34, never touched by this body
};

// The port the miss path dispatches through, in the shape the SDK declares for
// /Spore/App/PropertyList/GetProperty. The base PropertyList vtable at
// 0x01408820 stores 0x006A2530 in this slot, so a base-typed parent re-enters
// this very body.
using GetPropertyPort = bool(PKG15_THISCALL*)(PropertyList* list,
                                              std::uint32_t propertyID,
                                              Property** result);

// /Spore/App/PropertyList/PropertyList__vftable, 0x4c bytes, 19 slots. Only
// GetProperty (+0x24) is read by 0x006a2530; the remaining eighteen are named
// as the SDK names them and are otherwise untouched. All nineteen were read
// directly out of the table at 0x01408820 and each agrees with the SDK slot
// name (see the metadata sidecar's vtable_evidence).
struct PropertyListVtable {
  void* AddRef;                // +0x00
  void* Release;               // +0x04
  void* virtual_dtor;          // +0x08, SDK field `_virtual_dtor`
  void* Cast;                  // +0x0c
  void* GetReferenceCount;     // +0x10
  void* SetProperty;           // +0x14
  void* RemoveProperty;        // +0x18
  void* HasProperty;           // +0x1c
  void* GetPropertyAlt;        // +0x20
  GetPropertyPort GetProperty; // +0x24, the escalation port
  void* GetPropertyObject;     // +0x28
  void* CopyFrom;              // +0x2c
  void* AddPropertiesFrom;     // +0x30
  void* CopyAllPropertiesFrom; // +0x34
  void* AddAllPropertiesFrom;  // +0x38
  void* Read;                  // +0x3c
  void* Write;                 // +0x40
  void* GetPropertyIDs;        // +0x44
  void* Clear;                 // +0x48
};

// The one direct callee (0x00612db0, callsite 0x006a2546), a lower_bound over
// the pair array.
//
// 0x006a2530 pushes four dwords: mpBegin, mpEnd, &propertyID, and the low byte
// of mValueCompare. The live 33-instruction body of 0x00612db0 reads only
// [ESP+0x08] (mpEnd), [ESP+0x04] (mpBegin, reached through the PUSH ESI at
// 0x00612db4) and [ESP+0x10] (&propertyID), and ends in a bare RET at
// 0x00612dfc. It never touches [ESP+0x14], so the fourth dword is forwarded and
// ignored; it is modelled here as an explicit, ignored parameter instead of
// being dropped silently. The bare RET also proves the callee pops nothing, so
// the helper is cdecl.
extern "C" PropertyEntry* PKG15_CDECL property_list_lower_bound_00612db0(
    PropertyEntry* mpBegin, PropertyEntry* mpEnd,
    const std::uint32_t* propertyID, std::uint32_t ignored_mValueCompare_byte);

// 0x006a2530. Receiver in ECX (aliased to ESI at 0x006a2531), two ordinary
// stack dwords, bool in AL, RET 0x8 at 0x006a2574 / 0x006a258d / 0x006a2594.
extern "C" bool PKG15_THISCALL property_list_get_property_006a2530(
    PropertyList* list, std::uint32_t propertyID, Property** result);

// Layout constants, restated as compile-time facts about the model above. Each
// is the offset the 47-instruction listing shows the body using.
inline constexpr std::uint32_t kEntryStride = 0x18;
inline constexpr std::uint32_t kEntryValueOffset = 0x04;
inline constexpr std::uint32_t kMapBeginOffset = 0x18;
inline constexpr std::uint32_t kMapEndOffset = 0x1c;
inline constexpr std::uint32_t kValueCompareOffset = 0x2c;
inline constexpr std::uint32_t kParentOffset = 0x30;
inline constexpr std::uint32_t kGetPropertySlotOffset = 0x24;

}  // namespace openspore::reconstruction::pkg_app_property_get_wave15

namespace openspore::reconstruction::pkg_app_property_get_wave15 {

// App::Property
static_assert(sizeof(Property) == 4, "App::Property is 4 bytes");
static_assert(offsetof(Property, mnFlags) == 0x00, "mnFlags at +0x00");
static_assert(offsetof(Property, mnType) == 0x02, "mnType at +0x02");

// eastl::pair<uint, App::Property>: the stride and the value offset
static_assert(sizeof(PropertyEntry) == kEntryStride, "entry stride 0x18");
static_assert(offsetof(PropertyEntry, first) == 0x00, "first at entry+0x00");
static_assert(offsetof(PropertyEntry, second) == kEntryValueOffset,
              "second at entry+0x04");

// eastl::vector_map<uint, App::Property>, the type PropertyMap resolves to
static_assert(sizeof(PropertyMap) == 0x18, "vector_map is 0x18 bytes");
static_assert(offsetof(PropertyMap, mpBegin) == 0x00, "mpBegin at map+0x00");
static_assert(offsetof(PropertyMap, mpEnd) == 0x04, "mpEnd at map+0x04");
static_assert(offsetof(PropertyMap, mValueCompare) == 0x14,
              "mValueCompare at map+0x14");

// App::PropertyList
static_assert(offsetof(PropertyList, _vftable0) == 0x00, "vtable at +0x00");
static_assert(offsetof(PropertyList, mProperties) == kMapBeginOffset,
              "mProperties at +0x18");
static_assert(offsetof(PropertyList, mpParent) == kParentOffset,
              "mpParent at +0x30");
static_assert(offsetof(PropertyList, mnOperationsDone) == 0x34,
              "mnOperationsDone at +0x34");
static_assert(sizeof(PropertyList) == 0x38, "receiver extent 0x38");

// PropertyList__vftable
static_assert(offsetof(PropertyListVtable, GetProperty) == kGetPropertySlotOffset,
              "GetProperty port at vtable+0x24");
static_assert(offsetof(PropertyListVtable, Clear) == 0x48, "Clear at vtable+0x48");
static_assert(sizeof(PropertyListVtable) == 0x4c, "vtable extent 0x4c (19 slots)");

}  // namespace openspore::reconstruction::pkg_app_property_get_wave15
