#include "presentation_boundary.hpp"

#include <cstring>

namespace openspore::reconstruction::wave6_presentation {

TransformBoundaryPorts g_transform_boundary_ports;
MeshBoundaryPorts g_mesh_boundary_ports;
D3dBoundaryPorts g_d3d_boundary_ports;

std::uint32_t g_transform_dirty_016f9528 = 0;
MatrixType g_transform_type_016f96a0 = 0;
const Matrix4* g_transform_slot_016fa380 = nullptr;
Matrix4 g_transform_storage_016fa4f0{};
OpaquePointer g_device_016f89d0 = nullptr;
OpaquePointer g_active_state_016f6568 = nullptr;
std::uint32_t g_state_016f9110 = 0;
std::uint32_t g_state_01718610 = 0;
std::uint32_t g_state_01718614 = 0;
std::uint32_t g_state_01718618 = 0;
std::uint32_t g_stream_cache_016f913c[96]{};
std::uint32_t g_stream_limit_015d0934 = 0;
std::uint32_t g_current_primitive_016f85a8 = 0;
OpaquePointer g_cached_index_buffer_016f8afc = nullptr;

namespace {

std::uint8_t load_u8(const void* address) {
  std::uint8_t value;
  std::memcpy(&value, address, sizeof(value));
  return value;
}

std::uint32_t pointer_word(OpaquePointer pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

void multiply_components(Vector3* destination, const Vector3* source,
                         float scale) {
  destination->x = source->x * scale;
  destination->y = source->y * scale;
  destination->z = source->z * scale;
}

void add_vectors(Vector3* destination, const Vector3* source) {
  destination->x += source->x;
  destination->y += source->y;
  destination->z += source->z;
}

}

extern "C" void WAVE6_CDECL graphics_global_state_set_transform_005291f0(
    const Matrix4* matrix, MatrixType type) {
  g_transform_dirty_016f9528 |= 1U;
  g_transform_type_016f96a0 = type;
  g_transform_slot_016fa380 = &g_transform_storage_016fa4f0;
  g_transform_storage_016fa4f0 = *matrix;
}

extern "C" Transform* WAVE6_THISCALL
transform_pre_transform_by_0040ccb0(Transform* receiver, Transform* other) {
  Vector3 scaled_offset{};
  multiply_components(&scaled_offset, &other->mOffset, receiver->mfScale);

  Vector3 transformed_offset{};
  Vector3* offset_result = g_transform_boundary_ports.offset_transform(
      &transformed_offset, &scaled_offset, receiver, other);
  add_vectors(&receiver->mOffset, offset_result);

  Matrix3 transformed_rotation{};
  Matrix3* rotation_result = g_transform_boundary_ports.rotation_transform(
      &transformed_rotation, other);
  receiver->mRotation = *rotation_result;
  receiver->mfScale *= other->mfScale;
  receiver->mnFlags =
      static_cast<std::int16_t>(receiver->mnFlags | other->mnFlags);
  receiver->mnTransformCount =
      static_cast<std::int16_t>(receiver->mnTransformCount + 1);
  return receiver;
}

extern "C" void WAVE6_THISCALL renderware_mesh_set_indices_count_011f96e0(
    Mesh* receiver, IndexBuffer* index_buffer) {
  receiver->pIndexBuffer = index_buffer;
  if (index_buffer != nullptr) {
    receiver->primitiveType = index_buffer->primitiveType;
  }
  receiver->triangleCount = g_mesh_boundary_ports.calculate_index_count(
      receiver, receiver->primitiveType);
}

extern "C" void WAVE6_THISCALL
renderware_mesh_set_index_buffer_011f9710(Mesh* receiver) {
  g_d3d_boundary_ports.flush_render_state();
  if (g_d3d_boundary_ports.prepare_mesh(g_active_state_016f6568, receiver) ==
      0) {
    return;
  }

  g_state_016f9110 = 0;
  const std::uint32_t vertex_buffer_count = receiver->vertexBuffersCount;
  if (vertex_buffer_count == 1) {
    const VertexBuffer* vertex_buffer = receiver->pVertexBuffers;
    g_state_01718614 = vertex_buffer->baseVertexIndex;
    g_state_01718618 = g_state_01718614;
  }

  std::uint32_t stream = 0;
  if (vertex_buffer_count != 0) {
    for (; stream < vertex_buffer_count; ++stream) {
      const VertexBuffer* vertex_buffer = receiver->pVertexBuffers + stream;
      const std::uint32_t source = pointer_word(vertex_buffer->pDXBuffer);
      const std::uint8_t description_stride = load_u8(
          static_cast<const std::uint8_t*>(vertex_buffer->pVertexDescription) +
          0x0f);
      const GraphicsActiveState* active_state =
          static_cast<const GraphicsActiveState*>(
              g_d3d_boundary_ports.get_active_state());
      std::uint32_t stream_offset = 0;
      if ((load_u8(reinterpret_cast<const std::uint8_t*>(active_state) + 0xd4) &
           1U) != 0) {
        stream_offset = vertex_buffer->baseVertexIndex * description_stride;
        g_state_01718614 = 0;
        g_state_01718618 = 0;
      }

      const std::size_t cache_index = static_cast<std::size_t>(stream) * 3U;
      if (g_stream_cache_016f913c[cache_index] != source ||
          g_stream_cache_016f913c[cache_index + 1U] != stream_offset ||
          g_stream_cache_016f913c[cache_index + 2U] != description_stride) {
        if (g_d3d_boundary_ports.set_stream_source(g_device_016f89d0, stream,
                                                   source, stream_offset,
                                                   description_stride) < 0) {
          return;
        }
        g_stream_cache_016f913c[cache_index] = source;
        g_stream_cache_016f913c[cache_index + 1U] = stream_offset;
        g_stream_cache_016f913c[cache_index + 2U] = description_stride;
      }
    }
  }

  const std::uint32_t old_stream_limit = g_stream_limit_015d0934;
  for (; stream < old_stream_limit; ++stream) {
    if (g_d3d_boundary_ports.set_stream_source(g_device_016f89d0, stream, 0, 0,
                                               0) < 0) {
      return;
    }
    const std::size_t cache_index = static_cast<std::size_t>(stream) * 3U;
    g_stream_cache_016f913c[cache_index] = 0;
    g_stream_cache_016f913c[cache_index + 1U] = 0;
    g_stream_cache_016f913c[cache_index + 2U] = 0;
  }
  g_stream_limit_015d0934 = vertex_buffer_count;

  const std::uint32_t current_primitive = g_current_primitive_016f85a8;
  const std::uint32_t primitive_count =
      receiver->primitiveType == current_primitive
          ? receiver->triangleCount
          : g_mesh_boundary_ports.calculate_index_count(receiver,
                                                        current_primitive);
  g_state_01718610 = primitive_count;

  if (receiver->pIndexBuffer == nullptr) {
    g_d3d_boundary_ports.draw_primitive(g_device_016f89d0,
                                        receiver->primitiveType,
                                        g_state_01718618, primitive_count);
    return;
  }

  OpaquePointer native_buffer = receiver->pIndexBuffer->pDXBuffer;
  if (native_buffer != g_cached_index_buffer_016f8afc) {
    if (g_d3d_boundary_ports.bind_index_buffer(g_device_016f89d0,
                                               native_buffer) < 0) {
      return;
    }
    g_cached_index_buffer_016f8afc = native_buffer;
  }

  g_d3d_boundary_ports.draw_indexed(
      g_device_016f89d0, receiver->primitiveType, g_state_01718614,
      receiver->firstVertex, receiver->vertexCount,
      receiver->pIndexBuffer->startIndex + receiver->firstIndex,
      primitive_count);
}

}
