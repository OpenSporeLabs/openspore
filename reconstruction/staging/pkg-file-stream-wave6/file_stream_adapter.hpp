#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-file-stream-wave6 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_FILE_STREAM_WAVE6_THISCALL __thiscall
#define PKG_FILE_STREAM_WAVE6_STDCALL __stdcall
#define PKG_FILE_STREAM_WAVE6_CDECL __cdecl
#else
#define PKG_FILE_STREAM_WAVE6_THISCALL __attribute__((thiscall))
#define PKG_FILE_STREAM_WAVE6_STDCALL __attribute__((stdcall))
#define PKG_FILE_STREAM_WAVE6_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_file_stream_wave6 {

using Opaque = std::uint32_t;

static_assert(sizeof(Opaque) == 4, "pkg-file-stream-wave6 words are 32-bit");
static_assert(sizeof(void*) == 4, "pkg-file-stream-wave6 pointers are 32-bit");
static_assert(sizeof(std::size_t) == 4,
              "pkg-file-stream-wave6 sizes are 32-bit");

struct XmlWriterVtable;

struct XmlWriter {
  XmlWriterVtable* vtable = nullptr;
  std::array<std::uint8_t, 0x1c> opaque{};
};

struct XmlWriterVtable {
  using Slot = Opaque;
  std::array<Slot, 0x31> slots{};
};

struct FileStreamVtable;

struct FileStream {
  FileStreamVtable* vtable = nullptr;
  std::int32_t handle = -1;
  char16_t path[260]{};
  std::int32_t ref_count = 0;
  std::int32_t access_flags = 0;
  std::int32_t creation_disposition = 0;
  std::int32_t sharing = 0;
  std::int32_t usage_hints = 0;
  std::int32_t last_error = 0;
  std::int32_t cached_size = -1;
};

struct FileStreamVtable {
  using Slot = Opaque;
  std::array<Slot, 0x13> slots{};
};

struct OpaqueStreamVtable;

struct OpaqueStream {
  OpaqueStreamVtable* vtable = nullptr;
};

struct OpaqueStreamVtable {
  using Slot = Opaque;
  std::array<Slot, 0x0d> slots{};
};

struct StreamBuffer {
  OpaqueStreamVtable* vtable = nullptr;
  OpaqueStream* stream = nullptr;
  std::uint32_t ref_count = 0;
  std::uint32_t position_external = 0;
  std::uint32_t position_internal = 0;
  char* read_buffer = nullptr;
  std::uint32_t read_buffer_size = 0;
  std::uint32_t read_buffer_start_position = 0;
  std::uint32_t read_buffer_used = 0;
  char* write_buffer = nullptr;
  std::uint32_t write_buffer_size = 0;
  std::uint32_t write_buffer_start_position = 0;
  std::uint32_t write_buffer_used = 0;
};

struct StreamChild {
  OpaqueStreamVtable* vtable = nullptr;
  std::int32_t ref_count = 0;
  std::int32_t access_flags = 0;
  OpaqueStream* parent = nullptr;
  std::uint32_t parent_position = 0;
  std::uint32_t position = 0;
  std::uint32_t size = 0;
};

static_assert(sizeof(XmlWriter) == 0x20, "XmlWriter target extent");
static_assert(sizeof(FileStream) == 0x22c, "FileStream target extent");
static_assert(sizeof(StreamBuffer) == 0x34, "StreamBuffer target extent");
static_assert(sizeof(StreamChild) == 0x1c, "StreamChild target extent");

using MultiByteToWideCharBoundary = std::int32_t(
    PKG_FILE_STREAM_WAVE6_STDCALL*)(std::uint32_t, std::uint32_t, const char*,
                                    std::int32_t, char16_t*, std::int32_t);
using WideCopyBoundary = char16_t*(
    PKG_FILE_STREAM_WAVE6_CDECL*)(char16_t*, const char16_t*, std::size_t);

extern "C" std::int32_t PKG_FILE_STREAM_WAVE6_STDCALL
pkg_file_stream_wave6_multi_byte_to_wide_char(
    std::uint32_t codepage, std::uint32_t flags, const char* source,
    std::int32_t source_length, char16_t* destination,
    std::int32_t destination_capacity);

extern "C" char16_t* PKG_FILE_STREAM_WAVE6_CDECL
pkg_file_stream_wave6_copy_wide_path(char16_t* destination,
                                     const char16_t* source, std::size_t count);

bool PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_xml_writer_begin_processing_instruction_00901930(
    XmlWriter* writer, const char16_t* instruction_name);

std::int32_t PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_file_stream_increment_ref_009317b0(FileStream* stream);

void PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0(FileStream* stream,
                                                         const char* path);

void PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_file_stream_set_wide_path_00931810(FileStream* stream,
                                                         const char16_t* path);

std::int32_t PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_stream_buffer_delegate_0093ae60(StreamBuffer* buffer);

std::int32_t PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_stream_child_delegate_0093b6d0(StreamChild* child);

}
