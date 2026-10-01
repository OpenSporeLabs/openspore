#include "parse_uint_008414d0.hpp"

#include <cstdio>
#include <cstring>

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_FORMAT_THIS_CALL __thiscall
#else
#define PKG_ARGSCRIPT_FORMAT_THIS_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_format_008414d0 {

char const* const kObservedFormat = "%s:%d";

namespace {

// 0x00840c2f and 0x00840c39 both name 0x0164f780 and 0x00840c2f pushes the
// observed declared width 0x400. Modelled package-locally; the global is not
// promoted to a global record and stays a runtime gate.
std::array<char, 0x400> g_scratch{};

// 0x00454cb0, observed as an __thiscall member entered with ECX = the
// destination string. Read words: word 0 (begin) and word 1 (end). The
// comparison performed by the original is
//     if ((uint)(dest->end - dest->begin) < (source_end - source)) grow;
//     else { memcpy(dest->begin, source, source_end - source); terminate(); }
// The grow branch calls 0x00455d60 and is NOT modelled.
bool assign_range_00454cb0(OpaqueString* destination, char const* source,
                           char const* source_end) {
  if (destination->begin == nullptr || destination->end == nullptr) {
    return false;
  }
  const std::size_t size = static_cast<std::size_t>(source_end - source);
  const std::size_t room =
      static_cast<std::size_t>(destination->end - destination->begin);
  if (room < size) {
    return false;
  }
  std::memcpy(destination->begin, source, size);
  // 0x0045f080(begin + size, end) terminates at the end of the written range.
  if (room > size) {
    destination->begin[size] = '\0';
  }
  return true;
}

}  // namespace

FormatParserPorts g_argscript_format_ports{&model_copy_formatted_00840c20};

void model_copy_formatted_00840c20(OpaqueString* destination,
                                   char const* format, OpaqueWord first,
                                   OpaqueWord second) {
  if (std::strcmp(format, kObservedFormat) == 0) {
    // The only format literal observed at 0x0141bcb0.
    std::snprintf(
        g_scratch.data(), g_scratch.size(), "%s:%d",
        reinterpret_cast<char const*>(static_cast<std::uintptr_t>(first)),
        static_cast<int>(static_cast<std::int32_t>(second)));
  } else {
    // No other format is reconstructed; the unmodelled path degrades to a
    // verbatim copy of the format text so the model stays total.
    std::memset(g_scratch.data(), 0, g_scratch.size());
    std::strncpy(g_scratch.data(), format, g_scratch.size() - 1);
  }

  // 0x00840c41..0x00840c49 scan the scratch for its NUL, leaving
  // EAX = scratch + strlen(scratch) and EDX = scratch + 1.
  // 0x00840c4f SUB EAX,EDX therefore yields strlen(scratch) - 1, and
  // 0x00840c51 LEA EDX,[EAX + 0x164f780] yields scratch + (strlen - 1).
  const std::size_t length = std::strlen(g_scratch.data());
  const std::size_t size = (length == 0) ? 0u : length - 1u;
  const char* const source_end = g_scratch.data() + size;
  assign_range_00454cb0(destination, g_scratch.data(), source_end);
}

const char* PKG_ARGSCRIPT_FORMAT_THIS_CALL
parse_uint_008414d0(OpaqueFormatParser* parser) {
  const OpaqueWord source = static_cast<OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(parser->field_0e0.begin));
  const OpaqueWord value = static_cast<OpaqueWord>(parser->field_0f0);

  const CopyFormattedToString copy_formatted =
      g_argscript_format_ports.copy_formatted_00840c20;
  if (copy_formatted != nullptr) {
    copy_formatted(&parser->field_0f4, kObservedFormat, source, value);
  }

  // 0x008414f0: MOV EAX,dword ptr [ESI] with ESI = this + 0xf4.
  return parser->field_0f4.begin;
}

}  // namespace openspore::reconstruction::pkg_argscript_format_008414d0

#undef PKG_ARGSCRIPT_FORMAT_THIS_CALL
