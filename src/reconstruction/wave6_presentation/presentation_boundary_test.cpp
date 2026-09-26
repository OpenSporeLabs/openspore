#include "presentation_boundary.hpp"

#include <cstring>

namespace openspore::reconstruction::wave6_presentation {
namespace {

struct DrawIndexedTrace {
  std::uint32_t primitive_type;
  std::uint32_t base_vertex_index;
  std::uint32_t min_index;
  std::uint32_t vertex_count;
  std::uint32_t start_index;
  std::uint32_t primitive_count;
  std::uint32_t calls;
};

struct DrawPrimitiveTrace {
  std::uint32_t primitive_type;
  std::uint32_t start_vertex;
  std::uint32_t primitive_count;
  std::uint32_t calls;
};

struct D3dTrace {
  std::uint32_t flush_calls;
  std::uint32_t prepare_calls;
  std::uint32_t stream_calls;
  std::uint32_t bind_calls;
  std::uint32_t stream[8];
  std::uint32_t source[8];
  std::uint32_t offset[8];
  std::uint32_t stride[8];
  DrawIndexedTrace indexed;
  DrawPrimitiveTrace primitive;
  OpaquePointer bound_buffer;
  Mesh* prepare_mesh;
  std::uint32_t active_state_calls;
  std::int32_t stream_result;
  std::uint32_t stream_limit_update_mask;
  std::uint32_t stream_limit_update[8];
  std::int32_t bind_result;
  std::int32_t prepare_result;
};

D3dTrace g_trace;
GraphicsActiveState* g_test_active_state = nullptr;
std::uint32_t g_calculate_calls = 0;
std::uint32_t g_calculate_last_primitive = 0;
std::uint32_t g_calculate_receiver_primitive = 0;
std::uint32_t g_offset_calls = 0;
const Vector3* g_offset_vector = nullptr;
const Matrix3* g_offset_matrix = nullptr;
std::uint32_t g_rotation_calls = 0;
const Matrix3* g_rotation_first = nullptr;
const Matrix3* g_rotation_second = nullptr;

std::uint32_t WAVE6_THISCALL
calculate_index_count(Mesh* receiver, std::uint32_t primitive_type) {
  ++g_calculate_calls;
  g_calculate_last_primitive = primitive_type;
  g_calculate_receiver_primitive = receiver->primitiveType;
  return primitive_type + 2U;
}

Vector3* offset_transform(Vector3* destination, const Vector3* vector,
                          const Matrix3* matrix) {
  ++g_offset_calls;
  g_offset_vector = vector;
  g_offset_matrix = matrix;
  destination->x = vector->x;
  destination->y = vector->y;
  destination->z = vector->z;
  return destination;
}

Matrix3* rotation_transform(Matrix3* destination, const Matrix3* first,
                            const Matrix3* second) {
  ++g_rotation_calls;
  g_rotation_first = first;
  g_rotation_second = second;
  for (std::uint32_t row = 0; row < 3U; ++row) {
    for (std::uint32_t column = 0; column < 3U; ++column) {
      destination->m[row][column] =
          first->m[row][column] + static_cast<float>(row + column);
    }
  }
  return destination;
}

void WAVE6_CDECL flush_render_state() { ++g_trace.flush_calls; }

std::int32_t WAVE6_CDECL prepare_mesh(Mesh* mesh) {
  ++g_trace.prepare_calls;
  g_trace.prepare_mesh = mesh;
  return g_trace.prepare_result;
}

OpaquePointer WAVE6_CDECL get_active_state() {
  ++g_trace.active_state_calls;
  return g_test_active_state;
}

std::int32_t WAVE6_STDCALL set_stream_source(OpaquePointer device,
                                             std::uint32_t stream,
                                             OpaquePointer source,
                                             std::uint32_t offset,
                                             std::uint32_t stride) {
  (void)device;
  const std::uint32_t index = g_trace.stream_calls++;
  g_trace.stream[index] = stream;
  g_trace.source[index] =
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(source));
  g_trace.offset[index] = offset;
  g_trace.stride[index] = stride;
  if ((g_trace.stream_limit_update_mask & (1U << index)) != 0U) {
    g_stream_limit_015d0934 = g_trace.stream_limit_update[index];
  }
  return g_trace.stream_result;
}

std::int32_t WAVE6_STDCALL bind_index_buffer(OpaquePointer device,
                                             OpaquePointer buffer) {
  (void)device;
  ++g_trace.bind_calls;
  g_trace.bound_buffer = buffer;
  return g_trace.bind_result;
}

std::int32_t WAVE6_STDCALL draw_primitive(OpaquePointer device,
                                          std::uint32_t primitive_type,
                                          std::uint32_t start_vertex,
                                          std::uint32_t primitive_count) {
  (void)device;
  g_trace.primitive.primitive_type = primitive_type;
  g_trace.primitive.start_vertex = start_vertex;
  g_trace.primitive.primitive_count = primitive_count;
  ++g_trace.primitive.calls;
  return 0;
}

std::int32_t WAVE6_STDCALL draw_indexed(OpaquePointer device,
                                        std::uint32_t primitive_type,
                                        std::uint32_t base_vertex_index,
                                        std::uint32_t min_index,
                                        std::uint32_t vertex_count,
                                        std::uint32_t start_index,
                                        std::uint32_t primitive_count) {
  (void)device;
  g_trace.indexed.primitive_type = primitive_type;
  g_trace.indexed.base_vertex_index = base_vertex_index;
  g_trace.indexed.min_index = min_index;
  g_trace.indexed.vertex_count = vertex_count;
  g_trace.indexed.start_index = start_index;
  g_trace.indexed.primitive_count = primitive_count;
  ++g_trace.indexed.calls;
  return 0;
}

bool equal_float(float left, float right) { return left == right; }

bool test_set_transform() {
  Matrix4 input{};
  for (std::uint32_t row = 0; row < 4U; ++row) {
    for (std::uint32_t column = 0; column < 4U; ++column) {
      input.m[row][column] = static_cast<float>(row * 4U + column + 1U);
    }
  }
  g_transform_dirty_016f9528 = 0x80U;
  g_transform_type_016f96a0 = 0;
  g_transform_slot_016fa380 = nullptr;
  graphics_global_state_set_transform_005291f0(&input, 0x12345678U);
  if (g_transform_dirty_016f9528 != 0x81U ||
      g_transform_type_016f96a0 != 0x12345678U ||
      g_transform_slot_016fa380 != &g_transform_storage_016fa4f0 ||
      std::memcmp(&g_transform_storage_016fa4f0, &input, sizeof(input)) != 0) {
    return false;
  }
  return true;
}

bool test_pre_transform() {
  Transform receiver{};
  receiver.mnFlags = 1;
  receiver.mnTransformCount = 4;
  receiver.mOffset = {1.0F, 2.0F, 3.0F};
  receiver.mfScale = 2.0F;
  Transform other{};
  other.mnFlags = 8;
  other.mOffset = {10.0F, 20.0F, 30.0F};
  other.mfScale = 3.0F;
  other.mRotation.m[0][0] = 1.0F;
  other.mRotation.m[1][1] = 2.0F;
  other.mRotation.m[2][2] = 3.0F;

  g_offset_calls = 0;
  g_offset_vector = nullptr;
  g_offset_matrix = nullptr;
  g_rotation_calls = 0;
  g_rotation_first = nullptr;
  g_rotation_second = nullptr;
  g_transform_boundary_ports.offset_transform = offset_transform;
  g_transform_boundary_ports.rotation_transform = rotation_transform;
  Transform* result = transform_pre_transform_by_0040ccb0(&receiver, &other);
  if (result != &receiver || g_offset_calls != 1U || g_rotation_calls != 1U ||
      g_offset_vector == nullptr || !equal_float(g_offset_vector->x, 20.0F) ||
      !equal_float(g_offset_vector->y, 40.0F) ||
      !equal_float(g_offset_vector->z, 60.0F) ||
      g_offset_matrix != &receiver.mRotation ||
      g_rotation_first != &other.mRotation ||
      g_rotation_second != &receiver.mRotation ||
      !equal_float(receiver.mOffset.x, 21.0F) ||
      !equal_float(receiver.mOffset.y, 42.0F) ||
      !equal_float(receiver.mOffset.z, 63.0F) ||
      !equal_float(receiver.mfScale, 6.0F) || receiver.mnFlags != 9 ||
      receiver.mnTransformCount != 5 ||
      !equal_float(receiver.mRotation.m[0][0], 1.0F) ||
      !equal_float(receiver.mRotation.m[1][1], 4.0F) ||
      !equal_float(receiver.mRotation.m[2][2], 7.0F)) {
    return false;
  }
  return true;
}

bool test_set_indices_count() {
  Mesh mesh{};
  IndexBuffer index_buffer{};
  index_buffer.primitiveType = 6U;
  g_mesh_boundary_ports.calculate_index_count = calculate_index_count;
  g_calculate_calls = 0;

  renderware_mesh_set_indices_count_011f96e0(&mesh, &index_buffer);
  if (mesh.pIndexBuffer != &index_buffer || mesh.primitiveType != 6U ||
      mesh.triangleCount != 8U || g_calculate_calls != 1U ||
      g_calculate_last_primitive != 6U ||
      g_calculate_receiver_primitive != 6U) {
    return false;
  }

  renderware_mesh_set_indices_count_011f96e0(&mesh, nullptr);
  if (mesh.pIndexBuffer != nullptr || mesh.primitiveType != 6U ||
      mesh.triangleCount != 8U || g_calculate_calls != 2U ||
      g_calculate_last_primitive != 6U) {
    return false;
  }
  return true;
}

bool test_set_index_buffer() {
  GraphicsActiveState active_state{};
  active_state.flags = 1U;
  g_test_active_state = &active_state;
  g_trace = D3dTrace{};
  g_trace.prepare_result = 1;
  g_trace.stream_result = 0;
  g_trace.bind_result = 0;
  g_d3d_boundary_ports.flush_render_state = flush_render_state;
  g_d3d_boundary_ports.prepare_mesh = prepare_mesh;
  g_d3d_boundary_ports.get_active_state = get_active_state;
  g_d3d_boundary_ports.set_stream_source = set_stream_source;
  g_d3d_boundary_ports.bind_index_buffer = bind_index_buffer;
  g_d3d_boundary_ports.draw_primitive = draw_primitive;
  g_d3d_boundary_ports.draw_indexed = draw_indexed;
  g_device_016f89d0 =
      reinterpret_cast<OpaquePointer>(static_cast<std::uintptr_t>(0x1000U));
  g_active_state_016f6568 =
      reinterpret_cast<OpaquePointer>(static_cast<std::uintptr_t>(0x5678U));
  g_current_primitive_016f85a8 = 5U;
  g_stream_limit_015d0934 = 3U;
  for (std::uint32_t index = 0; index < 12U; ++index) {
    g_stream_cache_016f9138[index] = 0xaaaaaaaaU;
  }
  g_cached_index_buffer_016f8afc = nullptr;

  std::uint8_t first_description[16]{};
  std::uint8_t second_description[16]{};
  first_description[0x0f] = 4U;
  second_description[0x0f] = 2U;
  VertexBuffer vertex_buffers[2]{};
  vertex_buffers[0].pVertexDescription = first_description;
  vertex_buffers[0].pDXBuffer =
      reinterpret_cast<OpaquePointer>(static_cast<std::uintptr_t>(0x2000U));
  vertex_buffers[0].baseVertexIndex = 3U;
  vertex_buffers[1].pVertexDescription = second_description;
  vertex_buffers[1].pDXBuffer =
      reinterpret_cast<OpaquePointer>(static_cast<std::uintptr_t>(0x4000U));
  vertex_buffers[1].baseVertexIndex = 5U;
  VertexBuffer* vertex_buffer_ptrs[2] = {&vertex_buffers[0],
                                         &vertex_buffers[1]};

  IndexBuffer index_buffer{};
  index_buffer.pDXBuffer =
      reinterpret_cast<OpaquePointer>(static_cast<std::uintptr_t>(0x3000U));
  index_buffer.startIndex = 5U;
  Mesh mesh{};
  mesh.primitiveType = 4U;
  mesh.pIndexBuffer = &index_buffer;
  mesh.triangleCount = 9U;
  mesh.vertexBuffersCount = 2U;
  mesh.firstIndex = 11U;
  mesh.firstVertex = 13U;
  mesh.vertexCount = 17U;
  mesh.pVertexBuffers = vertex_buffer_ptrs;

  renderware_mesh_set_index_buffer_011f9710(&mesh);
  if (g_trace.flush_calls != 1U || g_trace.prepare_calls != 1U ||
      g_trace.prepare_mesh != &mesh || g_trace.active_state_calls != 2U ||
      g_trace.stream_calls != 3U || g_trace.bind_calls != 1U ||
      g_trace.bound_buffer != index_buffer.pDXBuffer ||
      g_trace.stream[0] != 0U || g_trace.source[0] != 0x2000U ||
      g_trace.offset[0] != 12U || g_trace.stride[0] != 4U ||
      g_trace.stream[1] != 1U || g_trace.source[1] != 0x4000U ||
      g_trace.offset[1] != 10U || g_trace.stride[1] != 2U ||
      g_trace.stream[2] != 2U || g_trace.source[2] != 0U ||
      g_stream_cache_016f9138[0] != 0x2000U ||
      g_stream_cache_016f9138[1] != 12U || g_stream_cache_016f9138[2] != 4U ||
      g_stream_cache_016f9138[3] != 0x4000U ||
      g_stream_cache_016f9138[4] != 10U || g_stream_cache_016f9138[5] != 2U ||
      g_stream_cache_016f9138[6] != 0U || g_stream_cache_016f9138[7] != 0U ||
      g_stream_cache_016f9138[8] != 0U || g_stream_limit_015d0934 != 2U ||
      g_state_01718610 != 7U || g_state_01718614 != 0U ||
      g_trace.indexed.calls != 1U || g_trace.indexed.primitive_type != 5U ||
      g_trace.indexed.base_vertex_index != 0U ||
      g_trace.indexed.min_index != 13U || g_trace.indexed.vertex_count != 17U ||
      g_trace.indexed.start_index != 16U ||
      g_trace.indexed.primitive_count != 7U) {
    return false;
  }

  mesh.vertexBuffersCount = 0U;
  mesh.pIndexBuffer = nullptr;
  g_stream_limit_015d0934 = 0U;
  g_state_01718618 = 0x1234U;
  renderware_mesh_set_index_buffer_011f9710(&mesh);
  if (g_trace.primitive.calls != 1U || g_trace.primitive.primitive_type != 5U ||
      g_trace.primitive.start_vertex != 0x1234U ||
      g_trace.primitive.primitive_count != 7U || g_trace.indexed.calls != 1U) {
    return false;
  }

  mesh.vertexBuffersCount = 1U;
  mesh.pVertexBuffers = vertex_buffer_ptrs;
  g_stream_limit_015d0934 = 0;
  g_stream_cache_016f9138[0] = 0U;
  g_stream_cache_016f9138[1] = 0U;
  g_stream_cache_016f9138[2] = 0U;
  active_state.flags = 0U;
  g_state_01718614 = 0U;
  g_trace.stream_result = -1;
  g_trace.indexed.calls = 0U;
  g_trace.primitive.calls = 0U;
  renderware_mesh_set_index_buffer_011f9710(&mesh);
  if (g_trace.stream_calls != 4U || g_state_01718614 != 3U ||
      g_state_01718618 != 3U || g_trace.source[3] != 0x2000U ||
      g_trace.offset[3] != 0U || g_trace.stride[3] != 4U ||
      g_trace.indexed.calls != 0U || g_trace.primitive.calls != 0U) {
    return false;
  }

  mesh.vertexBuffersCount = 2U;
  vertex_buffer_ptrs[0] = nullptr;
  g_stream_limit_015d0934 = 0;
  g_trace.active_state_calls = 0;
  g_trace.stream_calls = 0;
  g_trace.stream_result = 0;
  renderware_mesh_set_index_buffer_011f9710(&mesh);
  if (g_trace.active_state_calls != 1U || g_trace.stream_calls != 1U ||
      g_trace.stream[0] != 1U || g_trace.source[0] != 0x4000U ||
      g_trace.offset[0] != 0U || g_trace.stride[0] != 2U ||
      g_stream_limit_015d0934 != 0U) {
    return false;
  }

  mesh.vertexBuffersCount = 0U;
  mesh.pIndexBuffer = nullptr;
  g_stream_limit_015d0934 = 1U;
  g_trace.stream_calls = 0U;
  g_trace.stream_limit_update_mask = 0x3U;
  g_trace.stream_limit_update[0] = 2U;
  g_trace.stream_limit_update[1] = 3U;
  renderware_mesh_set_index_buffer_011f9710(&mesh);
  if (g_trace.stream_calls != 3U || g_trace.stream[0] != 0U ||
      g_trace.stream[1] != 1U || g_trace.stream[2] != 2U ||
      g_trace.source[0] != 0U || g_trace.source[1] != 0U ||
      g_trace.source[2] != 0U || g_trace.offset[0] != 0U ||
      g_trace.offset[1] != 0U || g_trace.offset[2] != 0U ||
      g_trace.stride[0] != 0U || g_trace.stride[1] != 0U ||
      g_trace.stride[2] != 0U || g_stream_cache_016f9138[0] != 0U ||
      g_stream_cache_016f9138[1] != 0U || g_stream_cache_016f9138[2] != 0U ||
      g_stream_cache_016f9138[3] != 0U || g_stream_cache_016f9138[4] != 0U ||
      g_stream_cache_016f9138[5] != 0U || g_stream_cache_016f9138[6] != 0U ||
      g_stream_cache_016f9138[7] != 0U || g_stream_cache_016f9138[8] != 0U ||
      g_stream_limit_015d0934 != 0U) {
    return false;
  }
  return true;
}

}

}

int main() {
  namespace package = openspore::reconstruction::wave6_presentation;
  const bool passed =
      package::test_set_transform() && package::test_pre_transform() &&
      package::test_set_indices_count() && package::test_set_index_buffer();
  return passed ? 0 : 1;
}
