// Wave-13 worker batch b02 -- target 0x00688fa0
// Reconstructed from the live disassembly of 0x00688fa0..0x006891e5
// (203 instructions). Every statement is anchored to an instruction address;
// see reconstruction/metadata/wave13-w1-dispatch-b02/00688fa0.json.
//
// A note on the reconstruction's scope: the four length-guarded frees at
// 0x006890a5, 0x0068918a, 0x006891a9 and 0x006891c8 are reproduced with their
// exact guard, but which of the four intermediate string headers each one frees
// is not resolved here. The disassembly's ESP-relative slots shift by four
// between the guard and the free, and the decompiler's local names for them are
// not reliable. The four guards are the same test -- (end - begin) & ~1 > 2
// with a non-null begin -- so the reconstruction frees the four headers it
// tracks in construction order and records the ambiguity.

#include "b688fa0_gge_user_data_reset.hpp"

namespace openspore::wave13::b02 {
namespace {

// The four frees share one guard. 0x00689094 AND ECX,0xfffffffe with
// 0x00689097 CMP ECX,0x2 / 0x0068909f JLE, then 0x006890a1 CMP EAX,EDI with
// EDI zero, then the free. The identical four-instruction sequence appears at
// 0x0068917e..0x0068918b, 0x0068919d..0x006891aa and 0x006891bc..0x006891c9.
void free_string_header(String16Header* header) {
    if (header == nullptr) {
        return;
    }
    const auto bytes = reinterpret_cast<const std::uint8_t*>(header->end) -
                       reinterpret_cast<const std::uint8_t*>(header->begin);
    if ((static_cast<std::uint32_t>(bytes) & 0xfffffffeu) <= 2u) {
        return;
    }
    heap_free_port(header->begin);
}

}  // namespace

// 0x00688fa0, __cdecl, one wide-string pointer argument, returns the 0x24-byte
// object or null.
void* FUN_00688fa0_reconstruct(const wchar_t* name) {
    // 0x00688fa0..0x00688fae: the MSVC SEH prologue. PUSH -1 is the state slot
    // that the body overwrites with 1..6 as it acquires and releases
    // temporaries; 0x0120c84c is the 8-byte scope record
    // {MOV EAX,0x014f9e98; JMP <back into the function>}.
    // 0x00688fb5/0x00688fbc..0x00688fbf: a 0x4c-byte frame and four saved
    // registers.
    // 0x00688fb8/0x00688fc2: the single argument, the wide string.

    // 0x00688fc3..0x00688fcf: the first header is zeroed, then
    // 0x00688fd3 assigns the argument into it. 0x00579a90 pops its own argument.
    String16Header from_argument{};
    string16_assign_port(&from_argument, name);

    // 0x00688fd8/0x00688fe1: the service locator is asked for 0x04729a47.
    // 0x00688fe6..0x00688ff0: virtual slot +0x28 on the result, no arguments.
    // 0x00688fed: ADD ESP,0x4 pops the key.
    ServiceEntryPort* const service = service_locator_find_port(kServiceKey);
    const wchar_t* base_path = nullptr;
    {
        using Fn = const wchar_t* (*)(ServiceEntryPort*);
        void** const vtable = *reinterpret_cast<void***>(service);
        base_path = reinterpret_cast<Fn>(vtable[0x28 / 4])(service);
    }

    // 0x00688ff2..0x00688fff: a second header is zeroed, then
    // 0x00689003 assigns the base path into it. 0x00579a90 pops its argument.
    String16Header base{};
    string16_assign_port(&base, base_path);

    // 0x00689008..0x00689014: the element count of the base string, in 16-bit
    // units, and count + 1.
    const std::uint32_t count = static_cast<std::uint32_t>(
        (reinterpret_cast<const std::uint8_t*>(base.end) -
         reinterpret_cast<const std::uint8_t*>(base.begin)) >> 1);

    // 0x00689018..0x00689029: a third header is zeroed.
    String16Header working{};
    // 0x00689017/0x0068902d: capacity count + 1 elements.
    string16_reserve_port(&working, count + 1u);
    // 0x00689032..0x0068903b: the base string is memcpy'd into it, size
    // (end - begin) >> 1 * 2 bytes. 0x0068903b is 0x011e0744.
    // 0x00689040/0x00689048: end = begin + size, and a 16-bit NUL is written
    // at the new end.
    {
        const std::size_t bytes = static_cast<std::size_t>(count) * 2u;
        for (std::size_t i = 0; i < bytes / sizeof(wchar_t); ++i) {
            working.begin[i] = base.begin[i];
        }
        working.end = working.begin + (bytes / sizeof(wchar_t));
        *reinterpret_cast<wchar_t*>(working.end) = L'\0';
    }

    // 0x0068904b/0x00689051: the first path test. 0x00932ae0's body is
    // GetFileAttributesW plus a DIRECTORY-bit test, with a fallback to
    // 0x00932960, and 0x00932960 was not read. The result is not tested here.
    (void)path_is_directory_port(*working.begin);

    // 0x00689056..0x00689065: a fourth header receives the concatenation of the
    // working copy and the argument. 0x00688f00's body appends its second
    // parameter before its third, so the order is working then argument.
    String16Header joined{};
    (void)string16_concat_port(&joined, &working, &from_argument);

    // 0x0068906a: seven words of caller cleanup for 0x00688f00's three
    // arguments and the three words pushed before it.
    // 0x00689071/0x00689076/0x00689078: if the returned pointer differs from the
    // output header, 0x0068907a..0x00689086 assigns through it and reloads the
    // working pointer.
    // 0x006890a1..0x006890ab: the first guarded free, on the joined header.
    free_string_header(&joined);

    // 0x006890ae/0x006890af: DeleteFileW on the working copy's buffer. Its
    // result is discarded.
    (void)path_delete_file_port(*working.begin);

    // 0x006890b4..0x006890c2: the first registry allocation, 0x388 = 904 bytes,
    // under the class name at 0x013f09b4, which ghidra_read_memory shows is
    // the NUL-terminated ASCII "Simulator".
    void* const big = registry_allocate_port(0x388, g_simulator_class_name_013f09b4, 0, 0, 0, 0);

    // 0x006890ca: the result is kept.
    // 0x006890d3/0x006890d5: a null big is not dereferenced; the code simply
    // skips the constructor and keeps null.
    void* big_object = nullptr;
    if (big != nullptr) {
        // 0x006890d7..0x006890db: the constructor, with two zero arguments and
        // ECX = the new object. 0x006890e0/0x006890e2: its result is kept.
        big_object = construct_big_object_port(big, 0, 0);
    }

    // 0x006890f3..0x00689103: if big_object is non-null, virtual slot +0x00 of
    // the sub-object at big_object + 4 is called with ECX = big_object + 4.
    if (big_object != nullptr) {
        auto** const vtable = *reinterpret_cast<void***>(static_cast<std::uint8_t*>(big_object) + 4);
        using Fn = void (*)(void*);
        reinterpret_cast<Fn>(vtable[0])(static_cast<std::uint8_t*>(big_object) + 4);
    }

    // 0x00689105..0x00689115: the second registry allocation, 0x24 = 36 bytes,
    // under the same "Simulator" name.
    void* const small_raw = registry_allocate_port(0x24, g_simulator_class_name_013f09b4, 0, 0, 0, 0);

    // 0x00689121/0x00689126/0x00689136: a failed allocation yields a null
    // result; the code does not branch around the following virtual calls, so
    // the null case is carried into them.
    void* small = nullptr;
    if (small_raw != nullptr) {
        // 0x0068912a..0x0068912d: the constructor, with ECX = the new 0x24-byte
        // object and the 0x388-byte object pushed as its argument. 0x00689132
        // keeps its return value.
        small = construct_small_object_port(small_raw, big_object);
    }

    // 0x00689138..0x00689148: virtual slot +0x04 of the sub-object at small + 4.
    {
        // 0x00689138: MOV EDX,dword ptr [EBX + 0x4] loads the sub-object's
        // vtable pointer; 0x0068913e LEA ESI,[EBX + 0x4] forms the receiver.
        auto** const vtable = *reinterpret_cast<void***>(static_cast<std::uint8_t*>(small) + 4);
        using Fn = void (*)(void*);
        reinterpret_cast<Fn>(vtable[4 / 4])(static_cast<std::uint8_t*>(small) + 4);
    }
    // 0x0068914a..0x00689152: virtual slot +0x2c of the same sub-object, with
    // the working copy's buffer pushed as the single argument.
    {
        auto** const vtable = *reinterpret_cast<void***>(static_cast<std::uint8_t*>(small) + 4);
        using Fn = void (*)(void*, void*);
        reinterpret_cast<Fn>(vtable[0x2c / 4])(static_cast<std::uint8_t*>(small) + 4, *working.begin);
    }
    // 0x00689154..0x0068915e: virtual slot +0x3c of the vtable at small + 0,
    // with the arguments 0 and 1.
    {
        auto** const vtable = *reinterpret_cast<void***>(small);
        using Fn = void (*)(void*, std::uint32_t, std::uint32_t);
        reinterpret_cast<Fn>(vtable[0x3c / 4])(small, 0, 1);
    }

    // 0x00689160..0x00689176: if big_object is non-null, virtual slot +0x04 of
    // the sub-object at big_object + 4 is called again. The 0x388 object
    // therefore receives two calls at the same slot, before and after the
    // 0x24 object's three.
    if (big_object != nullptr) {
        using Fn = void (*)(void*);
        auto** const vtable = *reinterpret_cast<void***>(static_cast<std::uint8_t*>(big_object) + 4);
        reinterpret_cast<Fn>(vtable[4 / 4])(static_cast<std::uint8_t*>(big_object) + 4);
    }

    // 0x00689178..0x006891d1: three more guarded frees with the identical
    // (end - begin) & ~1 > 2 and non-null-begin test.
    free_string_header(&working);
    free_string_header(&base);
    free_string_header(&from_argument);

    // 0x006891d5..0x006891da: the saved registers are restored and EAX takes
    // the 0x24-byte object, so a failed second allocation returns null.
    // 0x006891db: MOV dword ptr FS:[0x0],ECX unlinks the SEH frame, using the
    // value saved at 0x00688fc7's predecessor in the prologue chain.
    // 0x006891e2/0x006891e5: the frame is dropped and a bare RET returns to the
    // caller, which cleans the one argument itself.
    return small;
}

}  // namespace openspore::wave13::b02
