#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG app wave10 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_app_wave10 {

using TargetWord = std::uint32_t;
using TargetSignedWord = std::int32_t;
using TargetByte = std::uint8_t;
using TargetHalf = std::uint16_t;
using TargetFloat = float;

#if defined(_MSC_VER)
#define PKG_APP_WAVE10_THISCALL __thiscall
#else
#define PKG_APP_WAVE10_THISCALL __attribute__((thiscall))
#endif

struct OpaqueVector3 {
  TargetFloat x;
  TargetFloat y;
  TargetFloat z;
};

struct OpaquePropertyValueSlot {
  std::array<TargetByte, 0x10> data;
  TargetHalf flags;
  TargetHalf kind;
};

struct OpaqueCursorBuffer {
  TargetWord opaque_00;
  TargetWord cursor;
  TargetWord limit;
};

struct OpaqueModelQuery {
  TargetWord first;
  TargetWord second;
};

struct OpaqueTriple {
  TargetWord slots[3];
};

struct OpaqueJobDescriptor {
  TargetWord owner;
  TargetWord tag;
  TargetWord packed;
};

struct OpaquePairTable {
  OpaqueModelQuery* begin;
  TargetWord extra;
};

struct OpaqueFieldRun {
  std::array<TargetByte, 0x08> opaque_00_07;
  TargetWord head;
  std::array<TargetByte, 0x0c> opaque_0c_17;
  TargetWord cells[6];
  std::array<TargetByte, 0x08> opaque_30_37;
  std::array<TargetByte, 0x04> opaque_38_3b;
  OpaquePairTable* table;
  std::array<TargetByte, 0x10> opaque_40_4f;
  TargetByte tail;
  std::array<TargetByte, 0x03> opaque_51_53;
};

using QuerySlotB4 = void(PKG_APP_WAVE10_THISCALL*)(void*, OpaqueModelQuery*);
using QuerySlotB8 = void(PKG_APP_WAVE10_THISCALL*)(void*, OpaqueModelQuery*);
using QuerySlotBC = void(PKG_APP_WAVE10_THISCALL*)(void*, OpaqueModelQuery*);
using QuerySlotEC = void(PKG_APP_WAVE10_THISCALL*)(void*, TargetWord,
                                                   OpaqueTriple*);
using FactorySlot1C = TargetWord(PKG_APP_WAVE10_THISCALL*)(void*, TargetWord,
                                                           TargetWord);

struct OpaqueModelServiceVtable {
  std::array<void*, 45> slots_00_b3;
  QuerySlotB4 query_b4;
  QuerySlotB8 query_b8;
  QuerySlotBC query_bc;
  std::array<void*, 11> slots_c0_e8;
  QuerySlotEC query_ec;
  std::array<void*, 12> slots_f0_11c;
};

struct OpaqueModelService {
  OpaqueModelServiceVtable* vtable;
};

struct OpaqueFactoryServiceVtable {
  std::array<void*, 7> slots_00_1b;
  FactorySlot1C resolve_1c;
  std::array<void*, 16> slots_20_5f;
};

struct OpaqueFactoryService {
  OpaqueFactoryServiceVtable* vtable;
};

using RenderSlot54 = void(PKG_APP_WAVE10_THISCALL*)(void*, TargetWord,
                                                    TargetWord);
using RenderSlot5C = void(PKG_APP_WAVE10_THISCALL*)(void*, TargetWord,
                                                    TargetWord, TargetWord,
                                                    TargetWord);

struct OpaqueRenderServiceVtable {
  std::array<void*, 21> slots_00_53;
  RenderSlot54 adopt_54;
  std::array<void*, 1> slot_58;
  RenderSlot5C submit_5c;
  std::array<void*, 24> slots_60_bf;
};

struct OpaqueRenderService {
  OpaqueRenderServiceVtable* vtable;
};

using AppSlot14 = void(PKG_APP_WAVE10_THISCALL*)(void*, TargetWord, TargetWord,
                                                 TargetWord);

struct OpaqueAppServiceVtable {
  std::array<void*, 5> slots_00_13;
  AppSlot14 dispatch_14;
  std::array<void*, 56> slots_18_f7;
};

struct OpaqueAppService {
  OpaqueAppServiceVtable* vtable;
};

using ReleaseSlot04 = void(PKG_APP_WAVE10_THISCALL*)(void*);

struct OpaqueHolderVtable {
  std::array<void*, 1> slot_00;
  ReleaseSlot04 release_04;
};

struct OpaqueHolder {
  OpaqueHolderVtable* vtable;
};

using ReleaseEntry = void(PKG_APP_WAVE10_THISCALL*)(void*);
using ResolveEnum = void (*)(TargetWord, TargetWord, TargetWord*);
using ResolveBool = bool(PKG_APP_WAVE10_THISCALL*)(void*, TargetWord);
using AcquireToken = TargetWord (*)(TargetWord, TargetWord);
using SubmitResolve = void (*)(TargetWord, TargetWord, TargetWord, TargetWord*);
using SubmitGraphicsJob = TargetByte (*)(TargetWord, OpaqueJobDescriptor*,
                                         TargetWord);
using ModelServiceGet = OpaqueModelService* (*)();
using FactoryServiceGet = OpaqueFactoryService* (*)();
using RenderServiceGet = OpaqueRenderService* (*)();
using AppServiceGet = OpaqueAppService* (*)();

struct RenderRuntime {
  ReleaseEntry release_entry;
  ResolveEnum resolve_enum;
  ResolveBool resolve_bool;
  AcquireToken acquire_token;
  SubmitResolve submit_resolve;
  SubmitGraphicsJob submit_graphics_job;
  ModelServiceGet model_service;
  FactoryServiceGet factory_service;
  RenderServiceGet render_service;
  AppServiceGet app_service;
};

struct OpaqueSelection {
  std::array<TargetByte, 0x10> opaque_00_0f;
  TargetWord index;
  std::array<TargetByte, 0x03> opaque_14_16;
};

struct OpaqueRenderHost {
  std::array<TargetByte, 0x08> opaque_00_07;
  TargetWord source_handle;
  std::array<TargetByte, 0x21c> opaque_0c_227;
  TargetWord owner;
  std::array<TargetByte, 0x04> opaque_22c_22f;
  TargetWord stamp;
  std::array<TargetByte, 0x18> opaque_234_24b;
  TargetWord resolver;
  std::array<TargetByte, 0xf2c> opaque_250_117b;
  OpaqueHolder* holder;
  std::array<TargetByte, 0x03> opaque_1180_1182;
};

using SourceSlot30 = void(PKG_APP_WAVE10_THISCALL*)(void*, void*, TargetWord);

struct OpaqueSourceServiceVtable {
  std::array<void*, 12> slots_00_2f;
  SourceSlot30 reserve_30;
  std::array<void*, 12> slots_34_63;
};

struct OpaqueSourceService {
  OpaqueSourceServiceVtable* vtable;
};

using ReadField = void (*)(void*, TargetWord*, TargetWord, TargetWord);
using ReadFlag = void (*)(void*, TargetByte*);
using PrepareSource = void (*)(void*, void*);
using BindPairTable = void(PKG_APP_WAVE10_THISCALL*)(OpaquePairTable*,
                                                     OpaqueModelQuery*,
                                                     TargetWord);
using ReservePairSlots = void(PKG_APP_WAVE10_THISCALL*)(OpaquePairTable*,
                                                        TargetWord);

struct RecordRuntime {
  ReadField read_field;
  ReadFlag read_flag;
  PrepareSource prepare_source;
  BindPairTable bind_pair_table;
  ReservePairSlots reserve_pair_slots;
};

using EmitElement = TargetWord(PKG_APP_WAVE10_THISCALL*)(void*, TargetWord);
using GrowAndEmit = void(PKG_APP_WAVE10_THISCALL*)(OpaqueCursorBuffer*,
                                                   TargetWord, TargetWord);

struct CursorRuntime {
  EmitElement emit_element;
  GrowAndEmit grow_and_emit;
};

RenderRuntime& render_runtime();
RecordRuntime& record_runtime();
CursorRuntime& cursor_runtime();

const TargetByte* property_value_sentinel();

OpaqueVector3* vector3_add(OpaqueVector3* destination,
                           const OpaqueVector3* left,
                           const OpaqueVector3* right);

void PKG_APP_WAVE10_THISCALL cursor_buffer_emit(OpaqueCursorBuffer* buffer,
                                                TargetWord argument);

const TargetByte* PKG_APP_WAVE10_THISCALL
property_value_resolve(const OpaquePropertyValueSlot* slot);

void record_field_run_load(OpaqueSourceService* source, OpaqueFieldRun* run,
                           TargetSignedWord shape);

TargetByte PKG_APP_WAVE10_THISCALL
render_host_select(OpaqueRenderHost* host, const OpaqueSelection* selection);

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueVector3) == 0x0c, "opaque vector size");
static_assert(sizeof(OpaquePropertyValueSlot) == 0x14,
              "opaque property value slot size");
static_assert(offsetof(OpaquePropertyValueSlot, flags) == 0x10,
              "opaque property value slot flags offset");
static_assert(offsetof(OpaquePropertyValueSlot, kind) == 0x12,
              "opaque property value slot kind offset");
static_assert(offsetof(OpaqueCursorBuffer, cursor) == 0x04,
              "opaque cursor buffer cursor offset");
static_assert(offsetof(OpaqueCursorBuffer, limit) == 0x08,
              "opaque cursor buffer limit offset");
static_assert(offsetof(OpaqueFieldRun, head) == 0x08,
              "opaque field run head offset");
static_assert(offsetof(OpaqueFieldRun, cells) == 0x18,
              "opaque field run cells offset");
static_assert(offsetof(OpaqueFieldRun, table) == 0x3c,
              "opaque field run table offset");
static_assert(offsetof(OpaqueFieldRun, tail) == 0x50,
              "opaque field run tail offset");
static_assert(sizeof(OpaqueFieldRun) == 0x54, "opaque field run size");
static_assert(offsetof(OpaquePairTable, begin) == 0x00,
              "opaque pair table begin offset");
static_assert(offsetof(OpaquePairTable, extra) == 0x04,
              "opaque pair table extra offset");
static_assert(sizeof(OpaqueJobDescriptor) == 0x0c,
              "opaque job descriptor size");
static_assert(offsetof(OpaqueSelection, index) == 0x10,
              "opaque selection index offset");
static_assert(offsetof(OpaqueRenderHost, source_handle) == 0x08,
              "opaque render host source handle offset");
static_assert(offsetof(OpaqueRenderHost, owner) == 0x228,
              "opaque render host owner offset");
static_assert(offsetof(OpaqueRenderHost, stamp) == 0x230,
              "opaque render host stamp offset");
static_assert(offsetof(OpaqueRenderHost, resolver) == 0x24c,
              "opaque render host resolver offset");
static_assert(offsetof(OpaqueRenderHost, holder) == 0x117c,
              "opaque render host holder offset");
static_assert(offsetof(OpaqueModelServiceVtable, query_b4) == 0xb4,
              "model service query b4 slot offset");
static_assert(offsetof(OpaqueModelServiceVtable, query_b8) == 0xb8,
              "model service query b8 slot offset");
static_assert(offsetof(OpaqueModelServiceVtable, query_bc) == 0xbc,
              "model service query bc slot offset");
static_assert(offsetof(OpaqueModelServiceVtable, query_ec) == 0xec,
              "model service query ec slot offset");
static_assert(offsetof(OpaqueFactoryServiceVtable, resolve_1c) == 0x1c,
              "factory service resolve slot offset");
static_assert(offsetof(OpaqueRenderServiceVtable, adopt_54) == 0x54,
              "render service adopt slot offset");
static_assert(offsetof(OpaqueRenderServiceVtable, submit_5c) == 0x5c,
              "render service submit slot offset");
static_assert(offsetof(OpaqueAppServiceVtable, dispatch_14) == 0x14,
              "app service dispatch slot offset");
static_assert(offsetof(OpaqueHolderVtable, release_04) == 0x04,
              "holder release slot offset");
static_assert(offsetof(OpaqueSourceServiceVtable, reserve_30) == 0x30,
              "source service reserve slot offset");

}
