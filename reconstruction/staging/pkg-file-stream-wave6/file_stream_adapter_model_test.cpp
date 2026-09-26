#include <array>
#include <cassert>
#include <cstring>

#include "file_stream_adapter.hpp"

namespace openspore::reconstruction::pkg_file_stream_wave6 {
namespace {

struct ModelStream : OpaqueStream {
  std::uint32_t position = 0;
  std::uint32_t capacity = 0;
};

template <typename Vtable, typename Function>
void set_slot(Vtable* vtable, std::size_t offset, Function function) {
  static_assert(sizeof(Function) == sizeof(Opaque),
                "target function pointer width");
  Opaque word = 0;
  std::memcpy(&word, &function, sizeof(word));
  std::memcpy(&vtable->slots[offset / sizeof(Opaque)], &word, sizeof(word));
}

XmlWriter xml_writer{};
XmlWriterVtable xml_vtable{};
const char16_t* observed_instruction_name = nullptr;
std::size_t observed_instruction_length = 0;
bool write_text_result = true;
std::uint32_t write_text_calls = 0;

bool PKG_FILE_STREAM_WAVE6_THISCALL write_text(XmlWriter* writer,
                                               const char16_t* instruction_name,
                                               std::size_t instruction_length) {
  assert(writer == &xml_writer);
  observed_instruction_name = instruction_name;
  observed_instruction_length = instruction_length;
  ++write_text_calls;
  return write_text_result;
}

std::uint32_t conversion_calls = 0;
std::uint32_t conversion_codepage = 0;
std::uint32_t conversion_flags = 0;
const char* conversion_source = nullptr;
std::int32_t conversion_source_length = 0;
char16_t* conversion_destination = nullptr;
std::int32_t conversion_capacity = 0;
bool conversion_writes = true;
std::int32_t conversion_result = 0;

extern "C" std::int32_t PKG_FILE_STREAM_WAVE6_STDCALL
pkg_file_stream_wave6_multi_byte_to_wide_char(
    std::uint32_t codepage, std::uint32_t flags, const char* source,
    std::int32_t source_length, char16_t* destination,
    std::int32_t destination_capacity) {
  ++conversion_calls;
  conversion_codepage = codepage;
  conversion_flags = flags;
  conversion_source = source;
  conversion_source_length = source_length;
  conversion_destination = destination;
  conversion_capacity = destination_capacity;
  if (!conversion_writes) {
    return conversion_result;
  }
  std::int32_t index = 0;
  while (index < destination_capacity && source[index] != '\0') {
    destination[index] =
        static_cast<char16_t>(static_cast<unsigned char>(source[index]));
    ++index;
  }
  if (index < destination_capacity) {
    destination[index] = u'\0';
  }
  return index;
}

char16_t* copy_destination = nullptr;
const char16_t* copy_source = nullptr;
std::size_t copy_count = 0;
std::uint32_t copy_calls = 0;

extern "C" char16_t* PKG_FILE_STREAM_WAVE6_CDECL
pkg_file_stream_wave6_copy_wide_path(char16_t* destination,
                                     const char16_t* source,
                                     std::size_t count) {
  ++copy_calls;
  copy_destination = destination;
  copy_source = source;
  copy_count = count;
  for (std::size_t index = 0; index < count; ++index) {
    destination[index] = source[index];
    if (source[index] == u'\0') {
      for (std::size_t clear = index + 1; clear < count; ++clear) {
        destination[clear] = u'\0';
      }
      break;
    }
  }
  return destination;
}

OpaqueStreamVtable parent_vtable{};
ModelStream parent_stream{};
std::int32_t delegated_result = 0;
std::uint32_t delegated_calls = 0;

std::int32_t PKG_FILE_STREAM_WAVE6_THISCALL
delegated_stream(OpaqueStream* stream) {
  assert(stream == &parent_stream);
  assert(parent_stream.position == 37u);
  assert(parent_stream.capacity == 91u);
  ++delegated_calls;
  return delegated_result;
}

void reset_conversion() {
  conversion_calls = 0;
  conversion_codepage = 0;
  conversion_flags = 0;
  conversion_source = nullptr;
  conversion_source_length = 0;
  conversion_destination = nullptr;
  conversion_capacity = 0;
  conversion_writes = true;
  conversion_result = 0;
}

void reset_copy() {
  copy_destination = nullptr;
  copy_source = nullptr;
  copy_count = 0;
  copy_calls = 0;
}

void test_xml_processing_instruction() {
  set_slot(&xml_vtable, 0x30, write_text);
  xml_writer.vtable = &xml_vtable;
  write_text_result = true;
  write_text_calls = 0;
  const char16_t instruction[] = u"target";

  assert(pkg_file_stream_wave6_xml_writer_begin_processing_instruction_00901930(
      &xml_writer, instruction));
  assert(write_text_calls == 1u);
  assert(observed_instruction_name == instruction);
  assert(observed_instruction_length == 6u);

  write_text_result = false;
  assert(
      !pkg_file_stream_wave6_xml_writer_begin_processing_instruction_00901930(
          &xml_writer, instruction));
  assert(write_text_calls == 2u);

  write_text_result = true;
  const char16_t empty[] = u"";
  assert(pkg_file_stream_wave6_xml_writer_begin_processing_instruction_00901930(
      &xml_writer, empty));
  assert(observed_instruction_length == 0u);
}

void test_file_stream_reference_counter() {
  FileStream stream{};
  stream.ref_count = 0x7ffffffe;
  stream.path[0] = u'p';
  assert(pkg_file_stream_wave6_file_stream_increment_ref_009317b0(&stream) ==
         0x7fffffff);
  assert(stream.ref_count == 0x7fffffff);
  assert(stream.path[0] == u'p');
  assert(pkg_file_stream_wave6_file_stream_increment_ref_009317b0(&stream) ==
         static_cast<std::int32_t>(0x80000000u));
  assert(stream.ref_count == static_cast<std::int32_t>(0x80000000u));
}

void test_utf8_path() {
  FileStream stream{};
  stream.handle = -1;
  stream.path[0] = u'x';
  const char source[] = "abc";
  reset_conversion();

  pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0(&stream, source);
  assert(conversion_calls == 1u);
  assert(conversion_codepage == 0xFDE9u);
  assert(conversion_flags == 0u);
  assert(conversion_source == source);
  assert(conversion_source_length == -1);
  assert(conversion_destination == stream.path);
  assert(conversion_capacity == 260);
  assert(stream.path[0] == u'a');
  assert(stream.path[1] == u'b');
  assert(stream.path[2] == u'c');
  assert(stream.path[3] == u'\0');
  assert(source[0] == 'a');

  const std::uint32_t calls_after_success = conversion_calls;
  stream.handle = 0;
  pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0(&stream, source);
  assert(conversion_calls == calls_after_success);
  assert(stream.path[0] == u'a');

  stream.handle = -1;
  pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0(&stream, nullptr);
  assert(conversion_calls == calls_after_success);

  stream.path[0] = u'z';
  conversion_writes = false;
  conversion_result = 0;
  pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0(&stream, source);
  assert(conversion_calls == calls_after_success + 1u);
  assert(stream.path[0] == u'z');
}

void test_wide_path() {
  FileStream stream{};
  stream.handle = -1;
  const char16_t source[] = u"wide";
  reset_copy();

  pkg_file_stream_wave6_file_stream_set_wide_path_00931810(&stream, source);
  assert(copy_calls == 1u);
  assert(copy_destination == stream.path);
  assert(copy_source == source);
  assert(copy_count == 260u);
  assert(stream.path[0] == u'w');
  assert(stream.path[1] == u'i');
  assert(stream.path[2] == u'd');
  assert(stream.path[3] == u'e');
  assert(stream.path[4] == u'\0');
  assert(source[0] == u'w');

  std::array<char16_t, 260> full_path{};
  full_path.fill(u'q');
  pkg_file_stream_wave6_file_stream_set_wide_path_00931810(&stream,
                                                           full_path.data());
  assert(copy_count == 260u);
  assert(stream.path[0] == u'q');
  assert(stream.path[259] == u'q');

  const std::uint32_t calls_after_success = copy_calls;
  stream.handle = 0;
  pkg_file_stream_wave6_file_stream_set_wide_path_00931810(&stream, source);
  pkg_file_stream_wave6_file_stream_set_wide_path_00931810(&stream, nullptr);
  assert(copy_calls == calls_after_success);
}

void test_stream_delegates() {
  set_slot(&parent_vtable, 0x14, delegated_stream);
  parent_stream.vtable = &parent_vtable;
  parent_stream.position = 37u;
  parent_stream.capacity = 91u;
  delegated_result = 123;
  delegated_calls = 0;

  StreamBuffer buffer{};
  buffer.stream = &parent_stream;
  buffer.position_external = 4u;
  buffer.position_internal = 8u;
  buffer.read_buffer_size = 16u;
  buffer.read_buffer_used = 5u;
  buffer.write_buffer_size = 32u;
  buffer.write_buffer_used = 9u;
  assert(pkg_file_stream_wave6_stream_buffer_delegate_0093ae60(&buffer) == 123);
  assert(delegated_calls == 1u);
  assert(buffer.position_external == 4u);
  assert(buffer.position_internal == 8u);
  assert(buffer.read_buffer_size == 16u);
  assert(buffer.read_buffer_used == 5u);
  assert(buffer.write_buffer_size == 32u);
  assert(buffer.write_buffer_used == 9u);
  assert(parent_stream.position == 37u);
  assert(parent_stream.capacity == 91u);

  buffer.stream = nullptr;
  assert(pkg_file_stream_wave6_stream_buffer_delegate_0093ae60(&buffer) == 0);
  assert(delegated_calls == 1u);

  StreamChild child{};
  child.parent = &parent_stream;
  child.position = 6u;
  child.size = 22u;
  assert(pkg_file_stream_wave6_stream_child_delegate_0093b6d0(&child) == 123);
  assert(delegated_calls == 2u);
  assert(child.position == 6u);
  assert(child.size == 22u);
  assert(parent_stream.position == 37u);
  assert(parent_stream.capacity == 91u);

  child.parent = nullptr;
  assert(pkg_file_stream_wave6_stream_child_delegate_0093b6d0(&child) == 0);
  assert(delegated_calls == 2u);
}

}

int run_model_tests() {
  test_xml_processing_instruction();
  test_file_stream_reference_counter();
  test_utf8_path();
  test_wide_path();
  test_stream_delegates();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_file_stream_wave6::run_model_tests();
}
