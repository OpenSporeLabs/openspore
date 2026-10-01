#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "this package reconstructs x86-32 code and has no 64-bit fallback"
#endif

#if defined(_MSC_VER)
#define PKG_ASR_CDECL __cdecl
#else
#define PKG_ASR_CDECL __attribute__((cdecl))
#endif

using TargetWord = std::uint32_t;

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void *) == sizeof(TargetWord),
              "target pointers are 32-bit");

// Absolute word the entry instruction reads before any field is reached. The
// Ghidra label on it is Simulator::sSpacePlayerData; nothing else about the
// container is claimed here.
inline constexpr TargetWord kContainerWord = 0x016dda8c;

// The two displacements the eight-instruction body states, and no others. Each
// is a local fact of one instruction; neither identifies a member by name.
inline constexpr std::size_t kActiveStarDisplacement = 0x8;
inline constexpr std::size_t kStarRecordDisplacement = 0x48;

// Container prefix reaching exactly the displacement the body loads. The words
// below it are padding for the layout, not observed fields.
struct SpacePlayerDataStarPrefix {
  TargetWord leading_words[2];
  TargetWord active_star_word;
};

// The active-star object is reached through one word and is read at exactly one
// displacement, so an opaque run up to and including that word is the whole of
// what the body shows.
struct OpaqueActiveStarWindow {
  std::uint8_t bytes[kStarRecordDisplacement + sizeof(TargetWord)];
};

// The accessor hands back the word stored at the star displacement. The body
// never dereferences it, so nothing is claimed about what that word addresses.

static_assert(offsetof(SpacePlayerDataStarPrefix, active_star_word) ==
              kActiveStarDisplacement);
static_assert(sizeof(OpaqueActiveStarWindow) ==
              kStarRecordDisplacement + sizeof(TargetWord));

extern "C" {
extern SpacePlayerDataStarPrefix *Simulator__sSpacePlayerData;

std::uint32_t PKG_ASR_CDECL FUN_01021240();
}