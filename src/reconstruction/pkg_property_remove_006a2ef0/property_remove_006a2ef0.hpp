// Clean-room reconstruction of App::PropertyList::RemoveProperty @ 0x006a2ef0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// Every statement below is a reading of the 9-instruction x86-32 body at
// 0x006a2ef0..0x006a2f06. Types are opaque: the binary carries no MSVC RTTI and
// nothing in the machine record establishes a field layout, so no member of any
// receiver is named anywhere in this package.

#ifndef OPENSPORE_RECONSTRUCTION_PKG_PROPERTY_REMOVE_006A2EF0_HPP
#define OPENSPORE_RECONSTRUCTION_PKG_PROPERTY_REMOVE_006A2EF0_HPP

#include <cstdint>

#if defined(_MSC_VER)
#define PKG_PROPERTY_REMOVE_006A2EF0_THISCALL __thiscall
#else
#define PKG_PROPERTY_REMOVE_006A2EF0_THISCALL __attribute__((thiscall))
#endif

namespace openspore {
namespace reconstruction {
namespace pkg_property_remove_006a2ef0 {

// Receiver of 0x006a2ef0. Left incomplete: the body establishes only that a
// 32-bit word is read-modify-written through it, never what the object is made
// of.
struct OpaquePropertyList;

// Receiver the removal port is invoked on (ECX at the call site, formed as
// this + 0x18). Also incomplete; the port's own body is not reconstructed here.
struct OpaquePropertyMap;

// Runtime-gated port, 0x006a2cb0.
//
// Observed call shape, read off the single call site 0x006a2efb:
//   ECX = receiver, one 4-byte stack argument, EAX carries the result.
// The stack argument is the address of the caller's property-id word, not the
// word itself: the body only ever forms its address (0x006a2ef3) and pushes it
// (0x006a2ef7). The port's own listing confirms it from the other side -- it
// loads the pushed word (006a2cb1: MOV EBX,[ESP + 0x8]), dereferences it
// (006a2cd2: MOV EDX,[EBX]) to compare against a candidate entry, and both of
// its exits are RET 0x4 (006a2d16, 006a2d1e), so the port pops the pointer this
// body hands it and 0x006a2ef0 must not clean it up again.
// The port returns 1 from one exit and 0 from the other; the result is passed
// back to RemoveProperty's caller unchanged, because 0x006a2ef0 writes no
// register of its own after the call.
//
// Declared, not defined: this package reconstructs 0x006a2ef0 only, so the
// symbol stays an unresolved external until the port is reconstructed.
int PKG_PROPERTY_REMOVE_006A2EF0_THISCALL property_list_map_remove_006a2cb0(
    OpaquePropertyMap* receiver, const std::uint32_t* property_id);

// App::PropertyList::RemoveProperty(uint32 propertyID) @ 0x006a2ef0.
//
// One ordinary stack argument (entry ESP+0x4, 4 bytes) which the callee pops:
// the body ends in RET 0x4. The receiver arrives in ECX. The result of
// 0x006a2cb0 is returned in EAX.
int PKG_PROPERTY_REMOVE_006A2EF0_THISCALL property_list_remove_property_006a2ef0(
    OpaquePropertyList* self, std::uint32_t property_id);

}  // namespace pkg_property_remove_006a2ef0
}  // namespace reconstruction
}  // namespace openspore

#endif  // OPENSPORE_RECONSTRUCTION_PKG_PROPERTY_REMOVE_006A2EF0_HPP
