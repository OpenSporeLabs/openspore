// Wave-13 worker batch b02 -- target 0x00b9aa10
// Clean-room reconstruction from SporeApp.exe 3.1.0.22.
//
// Observed shape: a 4-argument __cdecl void routine that walks an array of
// 32-bit ids, resolves each id through Editors::cSpeciesManager, derives a
// placement count and a bitmask from the resolved record, finds free cells on
// a cube map for each placement, commits the placement, paints three radius
// flag bits, optionally recurses into two child lists, and frees one
// heap block. It recurses into itself.
//
//   0x00b9aa10..0x00b9b088, 430 instructions, frame 0xdc bytes + 3 pushes.
//
// The class that owns the per-id record (read at +0x10, +0x2d4..+0x310, +0x334,
// +0x39c/+0x3a0, +0x3b0/+0x3b4, +0x43c) is NOT identified, and neither is the
// record's 0x19a8-byte stride observed at the caller 0x00b9c830. Those stay
// unnamed. See reconstruction/metadata/wave13-w1-dispatch-b02/00b9aa10.json.

#pragma once

#include <cstdint>

namespace openspore::wave13::b02 {

// Spore/Graphics/cCubeMapCoord.h: float mU; float mV; int mFace; size 0x0C.
// 0x00b90ea0 indexes a flat array of these with ((N*u + v)*N + w) * 0x0C and
// tests (first_dword & 7) == 0 before writing, so the low three bits of mU's
// bit pattern are in use as occupancy flags.
struct CubeMapCoord {
    float u;
    float v;
    std::int32_t face;
};
static_assert(sizeof(CubeMapCoord) == 0x0c, "cCubeMapCoord is 12 bytes");

// The per-id record reached through Editors::cSpeciesManager. Layout is
// PARTIAL: only the offsets this function reads are named.
struct SpeciesPlacementRecord {
    void* field_00;
    void* field_04;
    void* field_08;
    void* field_0c;
    std::uint32_t field_14;  // 0x00b9ae78 MOV EDI,dword ptr [EAX + 0x14]
    std::uint8_t pad18[0x2d4 - 0x18];
    float f_2d4;  // 0x00b9ae27
    float f_2d8;  // 0x00b9ae1d
    float f_2dc;  // 0x00b9ae13
    float f_2e0;  // 0x00b9ac9a, offset by the input-manager delta
    float f_2e4;  // 0x00b9acc3, offset by the input-manager delta
    float f_2e8;  // 0x00b9adf3
    float f_2ec;  // 0x00b9ade2
    float f_2f0;  // 0x00b9af72, first end of a discarded random lerp
    float f_2f4;  // 0x00b9af65, second end of that discarded random lerp
    float f_300;  // 0x00b9ab0c, low end of the count lerp
    float f_304;  // 0x00b9ab1b, high end of the count lerp
    float f_308;  // 0x00b9afc2, radius A
    float f_30c;  // 0x00b9afb3, radius B
    float f_310;  // 0x00b9afa2, radius C
    std::uint8_t pad314[0x334 - 0x314];
    std::uint8_t u8_334;  // 0x00b9adbe, widened with MOVZX and passed to the search
    std::uint8_t pad335[0x39c - 0x335];
    float* ring_begin;    // +0x39c
    float* ring_end;      // +0x3a0
    std::uint8_t pad3a4[0x3b0 - 0x3a4];
    std::uint32_t* child_ids;  // +0x3b0
    std::uint32_t* child_ids_end;  // +0x3b4
    std::uint8_t pad3b8[0x43c - 0x3b8];
    void* prop_list;  // +0x43c, an App::PropertyList*
    std::uint8_t pad440[4];
    void* field_10;  // +0x10, reached as [record + 0x10]
};

// ---------------------------------------------------------------------------
// Opaque ports. Declared, never implemented: no original body is claimed for
// any of these, and none is inlined from the target.
// ---------------------------------------------------------------------------

// 0x00b3d300 -- returns [0x0167eae0]; the target discards the result.
void* global_0167eae0_get_port();
// 0x00b3d350 -- Ghidra SDK symbol Simulator::cGameInputManager::Get(), returns
// [0x0167eaf8].
struct GameInputManagerPort;
GameInputManagerPort* game_input_manager_get_port();
// 0x00b5b800 -- returns 0xffffffff when 0x00b3d320() is zero, otherwise the
// value of 0x00a42730(). Its result is compared against 0x01654c01.
std::uint32_t current_calling_mode_id_port();
// 0x00401090 -- Ghidra SDK symbol Editors::cSpeciesManager::Get().
struct SpeciesManagerPort;
SpeciesManagerPort* species_manager_get_port();
// 0x004df420 -- calls 0x004df550(param_1 + 0xa4) on the species manager.
void species_manager_prepare_0a4_port(SpeciesManagerPort* manager);
// 0x004cd3c0 -- grows a dword vector to at least `count` elements.
void reserve_dword_vector_port(std::uint32_t* begin, std::uint32_t* end, std::uint32_t count);
// 0x00b7e390 -- __fastcall, argument in EAX. Virtual slot +0xc on
// [*[arg+0x24]] then (float)[+0x3c] * (float)[+0x38] + (float)[+0x34].
float input_manager_delta_port(GameInputManagerPort* manager);
// 0x0067cb40 -- returns [0x015fcc74]; the whole body is skipped when it is zero.
void* global_015fcc74_get_port();

// 0x004e0050 -- __thiscall(manager, id, flag). Returns 0 or a record pointer,
// optionally advanced by +4 and by one indexed step through [+0x3b4]/[+0x3c8].
SpeciesPlacementRecord* species_manager_resolve_port(SpeciesManagerPort* manager, std::uint32_t id,
                                                      std::uint32_t flag);
// 0x004dfff0 -- __thiscall, five arguments plus an out-context pointer.
std::int32_t species_manager_select_port(SpeciesManagerPort* manager, SpeciesPlacementRecord* record,
                                         void* out_context, std::uint32_t a3, std::uint32_t a4,
                                         std::uint32_t a5);
// 0x004e1c70 -- (prop_list, key, default_float) -> float.
float property_get_float_port(void* prop_list, std::uint32_t key, float default_value);
// 0x00b938d0 -- (out_vec3, prop_list, key, dx, dy, dz) -> Vector3, falling back
// to (dx,dy,dz) when the key is absent or not a 3-vector.
struct Vector3 {
    float x;
    float y;
    float z;
};
Vector3* property_get_vector3_port(Vector3* out, void* prop_list, std::uint32_t key, float dx, float dy,
                                  float dz);
// 0x00407190 -- Ghidra SDK symbol App::Property::GetBool().
bool property_get_bool_port(void* prop_list, std::uint32_t key, bool* out_value);
// 0x006a0840 -- Ghidra SDK symbol App::Property::GetArrayUInt32().
bool property_get_array_u32_port(void* prop_list, std::uint32_t key, std::uint32_t* out_count,
                                 std::uint32_t** out_data);
// 0x009360d0 -- __fastcall, state pointer in ECX. A 0x278dde6d LCG seeded from
// rdtsc on first use, returning a value in [0,1) with 1.0 folded back to 0.
float lcg_random_unit_port(std::uint32_t* state);
// 0x00b97720 -- 17-argument cube-map free-cell search. Returns 1 and writes a
// direction into `out` when a suitable cell is found, 0 otherwise.
bool cube_map_find_free_direction_port(Vector3* out, const Vector3* up, std::uint8_t selector,
                                       float radius_a, float radius_b, float r2d4, float r2d8,
                                       float r2dc, float offset_2e0, float offset_2e4, float r2e8,
                                       float r2ec, std::uint32_t ring_index, std::uint32_t flag_mask,
                                       void* out_context, std::uint32_t a15, std::uint32_t a16);
// 0x00b93f40 -- (out_pos, record, id, serial, extra): creates and commits one
// placed instance through a factory reached from 0x00b20c60(0x036be27e).
void commit_placement_port(Vector3* out_pos, SpeciesPlacementRecord* record, std::uint32_t id,
                           std::uint32_t serial, std::uint32_t extra);
// 0x00b90ea0 -- __thiscall(out_pos, radius_a, radius_b, radius_c): paints flag
// bits 0x10/0x20/0x40 into the 12-byte cube-map cells of *(this+0x24) around
// the direction in *out_pos.
void cube_map_paint_flags_port(Vector3* out_pos, float radius_a, float radius_b, float radius_c);
// 0x00b906a0 -- (a, b): computes a uniform random in [a,b] and returns nothing
// observable. The target discards it.
void random_lerp_port(float a, float b);
// 0x00b96220 -- lower_bound over a sorted array of 16-byte records keyed by the
// first two dwords; writes {lower, upper} to the out pair.
void sorted_range_lower_bound_port(std::uint32_t* out_range, std::uint32_t table_begin,
                                   std::uint32_t table_end, const std::uint32_t* key,
                                   std::uint8_t compare_mode);
// 0x00b970c0 -- __thiscall(out_range_ptr, key_ptr): element count in the range.
std::int32_t sorted_range_count_port(const std::uint32_t* range);
// 0x00b965d0 -- __thiscall(out_ptr, range_ptr): advances to the range's first element.
void sorted_range_begin_port(std::uint32_t* out_ptr, const std::uint32_t* range);
// 0x00b98230 -- __thiscall(out_key, range_ptr): advances to the range's end and
// writes {value, 1} to the out pair.
void sorted_range_end_port(std::uint32_t* out_key, const std::uint32_t* range);
// 0x00a68fb0 -- __thiscall(uint* state, uint range): a 0x41c64e6d LCG step
// returning a value in [0, range).
std::uint32_t lcg_bounded_port(std::uint32_t* state, std::uint32_t range);
// 0x00b9b090 -- sibling: places every id of a uint32 array through its own
// property path and returns a success count. It also recurses into the target.
std::int32_t place_from_property_array_port(Vector3* out_pos, const std::uint32_t* ids,
                                            std::uint32_t count, std::uint32_t extra,
                                            std::uint32_t a5);
// 0x00f47380 -- free if non-null, via 0x009276c0.
void heap_free_port(void* block);

// ---------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------

// 0x016895a4 -- a monotonically increasing dword serial, incremented once per
// accepted id. Zero in the file image.
extern std::uint32_t g_placement_serial_016895a4;
// 0x0156c060 -- a component selector indexing the Vector3s read from properties.
// Zero in the file image.
extern std::uint32_t g_vector_component_index_0156c060;
// 0x0156bfc4, 0x0156bfc8, 0x0156bfcc -- the (1.0f, 1.0f, 1.0f) default for
// property 0x1ee4cafd. Read live: 0000803f four times.
extern const float g_default_vector_1ee4cafd[4];
// 0x01688890, 0x01688894, 0x01688898 -- the default for property 0x6b152f47.
// All zero in the file image.
extern float g_default_vector_6b152f47[3];
// 0x0168890c, 0x01688910 -- the begin and end of a sorted 16-byte-record table.
// Both zero in the file image, i.e. the table starts empty.
extern std::uint32_t g_sorted_table_begin_0168890c;
extern std::uint32_t g_sorted_table_end_01688910;
// 0x01688920 -- the comparison mode byte passed to the sorted-table helpers.
extern std::uint8_t g_sorted_table_mode_01688920;
// 0x013ec4d0 -- 100.0f, the first fallback of the ring pair.
extern const float g_ring_fallback_a_013ec4d0;
// 0x013ec5b4 -- 1000.0f, the second fallback of the ring pair.
extern const float g_ring_fallback_b_013ec5b4;
// 0x0168_88e8 / 0x0168890c / 0x0156c060 are LCG state / table pointers passed
// as immediate ECX values; modelled as opaque state cells.
extern std::uint32_t g_lcg_state_a;
extern std::uint32_t g_lcg_state_b;
extern std::uint32_t g_lcg_state_c;

}  // namespace openspore::wave13::b02
