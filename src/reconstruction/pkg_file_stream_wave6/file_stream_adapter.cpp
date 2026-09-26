#include "file_stream_adapter.hpp"

namespace openspore::reconstruction::pkg_file_stream_wave6 {
namespace {

using WriteText = bool(PKG_FILE_STREAM_WAVE6_THISCALL*)(XmlWriter*,
                                                        const char16_t*,
                                                        std::size_t);
using DelegatedStreamCall =
    std::int32_t(PKG_FILE_STREAM_WAVE6_THISCALL*)(OpaqueStream*);

WriteText write_text_slot(XmlWriter* writer) {
  return reinterpret_cast<WriteText>(
      writer->vtable->slots[0x30 / sizeof(Opaque)]);
}

DelegatedStreamCall delegated_stream_slot(OpaqueStream* stream) {
  return reinterpret_cast<DelegatedStreamCall>(
      stream->vtable->slots[0x14 / sizeof(Opaque)]);
}

}

bool PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_xml_writer_begin_processing_instruction_00901930(
    XmlWriter* writer, const char16_t* instruction_name) {
  const char16_t* cursor = instruction_name;
  while (*cursor != u'\0') {
    ++cursor;
  }
  const std::size_t length =
      static_cast<std::size_t>(cursor - instruction_name);
  return write_text_slot(writer)(writer, instruction_name, length);
}

std::int32_t PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_file_stream_increment_ref_009317b0(FileStream* stream) {
  const std::int32_t next = static_cast<std::int32_t>(
      static_cast<std::uint32_t>(stream->ref_count) + 1u);
  stream->ref_count = next;
  return next;
}

void PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0(FileStream* stream,
                                                         const char* path) {
  if (stream->handle == -1 && path != nullptr) {
    static_cast<void>(pkg_file_stream_wave6_multi_byte_to_wide_char(
        0xFDE9u, 0u, path, -1, stream->path, 260));
  }
}

void PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_file_stream_set_wide_path_00931810(FileStream* stream,
                                                         const char16_t* path) {
  if (stream->handle == -1 && path != nullptr) {
    static_cast<void>(
        pkg_file_stream_wave6_copy_wide_path(stream->path, path, 260));
  }
}

std::int32_t PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_stream_buffer_delegate_0093ae60(StreamBuffer* buffer) {
  if (buffer->stream == nullptr) {
    return 0;
  }
  return delegated_stream_slot(buffer->stream)(buffer->stream);
}

std::int32_t PKG_FILE_STREAM_WAVE6_THISCALL
pkg_file_stream_wave6_stream_child_delegate_0093b6d0(StreamChild* child) {
  if (child->parent == nullptr) {
    return 0;
  }
  return delegated_stream_slot(child->parent)(child->parent);
}

}
