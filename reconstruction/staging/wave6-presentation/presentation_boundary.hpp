#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "wave6-presentation reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define WAVE6_CDECL __cdecl
#define WAVE6_STDCALL __stdcall
#define WAVE6_THISCALL __thiscall
#else
#define WAVE6_CDECL __attribute__((cdecl))
#define WAVE6_STDCALL __attribute__((stdcall))
#define WAVE6_THISCALL __attribute__((thiscall))
#endif

static_assert(sizeof(void*) == 4, "wave6-presentation pointers are 32-bit");
static_assert(sizeof(float) == 4, "wave6-presentation floats are 32-bit");
static_assert(sizeof(std::int16_t) == 2, "wave6-presentation words are 16-bit");
static_assert(sizeof(std::int32_t) == 4,
              "wave6-presentation dwords are 32-bit");

namespace openspore::reconstruction::wave6_presentation {

using MatrixType = std::uint32_t;
using OpaquePointer = void*;

struct Matrix4 {
  float m[4][4];
};

struct Vector3 {
  float x;
  float y;
  float z;
};

struct Matrix3 {
  float m[3][3];
};

struct Transform {
  std::int16_t mnFlags;
  std::int16_t mnTransformCount;
  Vector3 mOffset;
  float mfScale;
  Matrix3 mRotation;
};

struct IndexBuffer {
  OpaquePointer pDXBuffer;
  std::uint32_t startIndex;
  std::uint32_t indicesCount;
  std::uint32_t usage;
  std::uint32_t format;
  std::uint32_t primitiveType;
  OpaquePointer pIndexData;
};

struct VertexBuffer {
  OpaquePointer pVertexDescription;
  OpaquePointer pDXBuffer;
  std::uint32_t baseVertexIndex;
  std::uint32_t vertexCount;
  std::uint32_t usage;
  std::uint8_t stride;
  std::uint8_t lockFlags;
  std::uint16_t reserved;
  OpaquePointer pVertexData;
};

struct Mesh {
  std::uint32_t instancedSize;
  std::uint32_t primitiveType;
  IndexBuffer* pIndexBuffer;
  std::uint32_t triangleCount;
  std::uint32_t vertexBuffersCount;
  std::uint32_t firstIndex;
  std::uint32_t indicesCount;
  std::uint32_t firstVertex;
  std::uint32_t vertexCount;
  VertexBuffer** pVertexBuffers;
};

struct GraphicsActiveState {
  std::uint8_t bytes[0xd4];
  std::uint8_t flags;
};

static_assert(sizeof(Matrix4) == 64, "Matrix4 must remain 64 bytes");
static_assert(sizeof(Matrix3) == 36, "Matrix3 must remain 36 bytes");
static_assert(sizeof(Transform) == 56, "Transform must remain 56 bytes");
static_assert(offsetof(Transform, mnFlags) == 0x00, "Transform flags offset");
static_assert(offsetof(Transform, mnTransformCount) == 0x02,
              "Transform count offset");
static_assert(offsetof(Transform, mOffset) == 0x04, "Transform offset field");
static_assert(offsetof(Transform, mfScale) == 0x10, "Transform scale offset");
static_assert(offsetof(Transform, mRotation) == 0x14,
              "Transform rotation offset");
static_assert(sizeof(IndexBuffer) == 28, "IndexBuffer must remain 28 bytes");
static_assert(offsetof(IndexBuffer, primitiveType) == 0x14,
              "IndexBuffer primitive type offset");
static_assert(sizeof(VertexBuffer) == 28, "VertexBuffer must remain 28 bytes");
static_assert(offsetof(VertexBuffer, baseVertexIndex) == 0x08,
              "VertexBuffer base vertex offset");
static_assert(sizeof(Mesh) == 40, "Mesh must remain 40 bytes");
static_assert(offsetof(Mesh, primitiveType) == 0x04, "Mesh primitive type");
static_assert(offsetof(Mesh, pIndexBuffer) == 0x08, "Mesh index buffer");
static_assert(offsetof(Mesh, triangleCount) == 0x0c, "Mesh triangle count");
static_assert(offsetof(Mesh, vertexBuffersCount) == 0x10,
              "Mesh vertex buffer count");
static_assert(offsetof(Mesh, firstIndex) == 0x14, "Mesh first index");
static_assert(offsetof(Mesh, indicesCount) == 0x18, "Mesh index count");
static_assert(offsetof(Mesh, firstVertex) == 0x1c, "Mesh first vertex");
static_assert(offsetof(Mesh, vertexCount) == 0x20, "Mesh vertex count");
static_assert(offsetof(Mesh, pVertexBuffers) == 0x24, "Mesh vertex buffers");
static_assert(offsetof(GraphicsActiveState, flags) == 0xd4,
              "Graphics active-state flag offset");

struct TransformBoundaryPorts {
  using OffsetTransform = Vector3*(WAVE6_CDECL*)(Vector3*, const Vector3*,
                                                 const Matrix3*);
  using RotationTransform = Matrix3*(WAVE6_CDECL*)(Matrix3*, const Matrix3*,
                                                   const Matrix3*);

  OffsetTransform offset_transform = nullptr;
  RotationTransform rotation_transform = nullptr;
};

struct MeshBoundaryPorts {
  using IndexCount = std::uint32_t(WAVE6_THISCALL*)(Mesh*, std::uint32_t);

  IndexCount calculate_index_count = nullptr;
};

struct D3dBoundaryPorts {
  using FlushRenderState = void(WAVE6_CDECL*)();
  using PrepareMesh = std::int32_t(WAVE6_CDECL*)(GraphicsActiveState*, Mesh*);
  using GetActiveState = OpaquePointer(WAVE6_CDECL*)();
  using SetStreamSource = std::int32_t(WAVE6_STDCALL*)(OpaquePointer,
                                                       std::uint32_t,
                                                       OpaquePointer,
                                                       std::uint32_t,
                                                       std::uint32_t);
  using BindIndexBuffer = std::int32_t(WAVE6_STDCALL*)(OpaquePointer,
                                                       OpaquePointer);
  using DrawPrimitive = std::int32_t(WAVE6_STDCALL*)(OpaquePointer,
                                                     std::uint32_t,
                                                     std::uint32_t,
                                                     std::uint32_t);
  using DrawIndexed = std::int32_t(WAVE6_STDCALL*)(OpaquePointer, std::uint32_t,
                                                   std::uint32_t, std::uint32_t,
                                                   std::uint32_t, std::uint32_t,
                                                   std::uint32_t);

  FlushRenderState flush_render_state = nullptr;
  PrepareMesh prepare_mesh = nullptr;
  GetActiveState get_active_state = nullptr;
  SetStreamSource set_stream_source = nullptr;
  BindIndexBuffer bind_index_buffer = nullptr;
  DrawPrimitive draw_primitive = nullptr;
  DrawIndexed draw_indexed = nullptr;
};

extern TransformBoundaryPorts g_transform_boundary_ports;
extern MeshBoundaryPorts g_mesh_boundary_ports;
extern D3dBoundaryPorts g_d3d_boundary_ports;

extern std::uint32_t g_transform_dirty_016f9528;
extern MatrixType g_transform_type_016f96a0;
extern const Matrix4* g_transform_slot_016fa380;
extern Matrix4 g_transform_storage_016fa4f0;
extern OpaquePointer g_device_016f89d0;
extern GraphicsActiveState* g_active_state_016f6568;
extern std::uint32_t g_state_016f9110;
extern std::uint32_t g_state_01718610;
extern std::uint32_t g_state_01718614;
extern std::uint32_t g_state_01718618;
extern std::uint32_t g_stream_cache_016f9138[12];
extern std::uint32_t g_stream_limit_015d0934;
extern std::uint32_t g_current_primitive_016f85a8;
extern OpaquePointer g_cached_index_buffer_016f8afc;

extern "C" void WAVE6_CDECL graphics_global_state_set_transform_005291f0(
    const Matrix4* matrix, MatrixType type);
extern "C" Transform* WAVE6_THISCALL
transform_pre_transform_by_0040ccb0(Transform* receiver, Transform* other);
extern "C" void WAVE6_THISCALL renderware_mesh_set_indices_count_011f96e0(
    Mesh* receiver, IndexBuffer* index_buffer);
extern "C" void WAVE6_THISCALL
renderware_mesh_set_index_buffer_011f9710(Mesh* receiver);

}
