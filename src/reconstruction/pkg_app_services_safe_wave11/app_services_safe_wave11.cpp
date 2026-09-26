#include "app_services_safe_wave11.hpp"

#if defined(_MSC_VER)
#define PKG_APP_SERVICES_SAFE_WAVE11_CDECL __cdecl
#define PKG_APP_SERVICES_SAFE_WAVE11_THISCALL __thiscall
#define PKG_APP_SERVICES_SAFE_WAVE11_NOINLINE __declspec(noinline)
#define PKG_APP_SERVICES_SAFE_WAVE11_BARRIER() __asm {}
#else
#define PKG_APP_SERVICES_SAFE_WAVE11_CDECL __attribute__((cdecl))
#define PKG_APP_SERVICES_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#define PKG_APP_SERVICES_SAFE_WAVE11_NOINLINE __attribute__((noinline))
#define PKG_APP_SERVICES_SAFE_WAVE11_BARRIER() \
  __asm__ __volatile__("" ::: "memory")
#endif

namespace openspore::reconstruction::pkg_app_services_safe_wave11 {

const OpaqueWord OPAQUE_WIDE_SLASH[] = {0x002fu, 0x0000u};
const OpaqueWord OPAQUE_WIDE_THUMBNAILS[] = {
    0x0054u, 0x0068u, 0x0075u, 0x006du, 0x0062u, 0x006eu,
    0x0061u, 0x0069u, 0x006cu, 0x0073u, 0x002fu, 0x0000u};
const OpaqueWord OPAQUE_WIDE_DEFAULT_FOLDER[] = {
    0x0044u, 0x0065u, 0x0066u, 0x0061u, 0x0075u, 0x006cu, 0x0074u,
    0x0020u, 0x0046u, 0x006fu, 0x006cu, 0x0064u, 0x0065u, 0x0072u,
    0x0020u, 0x0054u, 0x0068u, 0x0075u, 0x006du, 0x0062u, 0x0000u};

static_assert(sizeof(OPAQUE_WIDE_SLASH) == 8, "slash literal");
static_assert(sizeof(OPAQUE_WIDE_THUMBNAILS) == 48, "thumbnails literal");
static_assert(sizeof(OPAQUE_WIDE_DEFAULT_FOLDER) == 84, "default literal");

Ports005f9230* g_ports_005f9230 = nullptr;
Ports005f9310* g_ports_005f9310 = nullptr;
Ports005fa8d0* g_ports_005fa8d0 = nullptr;
Ports005fc330* g_ports_005fc330 = nullptr;
Ports0060ee90* g_ports_0060ee90 = nullptr;

namespace {

inline OpaqueBool low_byte(OpaqueWord value) { return (value & 0xffu) != 0u; }

inline void release_handle(OpaqueWord handle, OpaqueWord slot_offset) {
  if (handle == 0u) {
    return;
  }
  OpaqueHandle* object =
      reinterpret_cast<OpaqueHandle*>(static_cast<std::uintptr_t>(handle));
  if (slot_offset == 0x04u) {
    object->vtable->slot_04(object);
  } else {
    object->vtable->slot_08(object);
  }
  PKG_APP_SERVICES_SAFE_WAVE11_BARRIER();
}

inline void release_owner(OpaqueWord owner) {
  if (owner == 0u) {
    return;
  }
  OpaqueOwner* object =
      reinterpret_cast<OpaqueOwner*>(static_cast<std::uintptr_t>(owner));
  object->vtable->slot_08(object);
  PKG_APP_SERVICES_SAFE_WAVE11_BARRIER();
}

}  // namespace

extern "C" OpaqueBool PKG_APP_SERVICES_SAFE_WAVE11_THISCALL
service_005f9230(OpaqueService* self, OpaqueWord key, OpaqueWide* dst) {
  Ports005f9230& ports = *g_ports_005f9230;
  const OpaqueWideField* field = nullptr;
  switch (key) {
    case OPAQUE_KEY_BUILDINGS:
      ports.assign_0057cb60(dst, &self->path_124);
      return true;
    case OPAQUE_KEY_CITY_MUSIC:
      ports.assign_0057cb60(dst, &self->path_164);
      return true;
    case OPAQUE_KEY_VEHICLES:
      ports.assign_0057cb60(dst, &self->path_144);
      return true;
    case OPAQUE_KEY_CREATURES:
      ports.assign_0057cb60(dst, &self->path_114);
      return true;
    case OPAQUE_KEY_UFOS:
      ports.assign_0057cb60(dst, &self->path_154);
      return true;
    case OPAQUE_KEY_SCENARIOS:
      field = &self->path_174;
      break;
    case OPAQUE_KEY_CELLS:
      field = &self->path_104;
      break;
    case OPAQUE_KEY_PLANTS:
      field = &self->path_134;
      break;
    default:
      return true;
  }
  if (reinterpret_cast<const void*>(field) != static_cast<const void*>(dst)) {
    ports.copy_00423650(dst, field->begin, field->end);
  }
  PKG_APP_SERVICES_SAFE_WAVE11_BARRIER();
  return true;
}

extern "C" OpaqueBool PKG_APP_SERVICES_SAFE_WAVE11_THISCALL
service_005f9310(OpaqueService* self, OpaqueWord instance, OpaqueWide* dst,
                 OpaqueWord table) {
  Ports005f9310& ports = *g_ports_005f9310;
  const OpaqueWord table_id =
      (table == OPAQUE_TABLE_DEFAULT) ? OPAQUE_TABLE_SUBSTITUTE : table;
  OpaqueWide scratch = {nullptr, nullptr};
  ports.resolve_006b5770(&scratch, table_id, instance,
                         OPAQUE_WIDE_DEFAULT_FOLDER);
  ports.prepare_00688830(OPAQUE_PREPARE_00688830_KEY, dst, 0u);
  if (static_cast<OpaqueByte>(self->field_184) == 0u) {
    ports.append_00429580(dst, OPAQUE_WIDE_THUMBNAILS,
                          OPAQUE_WIDE_THUMBNAILS + 11);
  }
  const OpaqueWord* head =
      static_cast<const OpaqueWord*>(ports.emit_006b55c0(&scratch));
  const OpaqueWord* tail = head;
  while (*tail != 0u) {
    ++tail;
  }
  ports.append_00429580(dst, head, tail);
  const OpaqueSigned span =
      static_cast<OpaqueSigned>(reinterpret_cast<std::uintptr_t>(dst->end)) -
      static_cast<OpaqueSigned>(reinterpret_cast<std::uintptr_t>(dst->begin));
  const OpaqueSigned count = span >> 1;
  const OpaqueWord last = dst->begin[static_cast<std::size_t>(count - 1)];
  if (last == OPAQUE_TERMINATOR_0ff0f) {
    ports.truncate_005f8f80(dst, static_cast<OpaqueWord>(count - 1), 1u,
                            OPAQUE_WIDE_SLASH);
  } else if (last != OPAQUE_SEPARATOR_SLASH) {
    const OpaqueWord* stop = OPAQUE_WIDE_SLASH;
    while (*stop != 0u) {
      ++stop;
    }
    ports.append_00429580(dst, OPAQUE_WIDE_SLASH, stop);
  }
  const OpaqueByte status = ports.finalize_00932ae0(dst->begin);
  ports.destroy_006b5240(&scratch);
  PKG_APP_SERVICES_SAFE_WAVE11_BARRIER();
  return status != 0u;
}

extern "C" OpaqueBool PKG_APP_SERVICES_SAFE_WAVE11_THISCALL
service_005fa8d0(OpaqueService* self, void* arg1, void* arg2, void* arg3,
                 OpaqueWord arg4, OpaqueWord arg5) {
  Ports005fa8d0& ports = *g_ports_005fa8d0;
  OpaqueSigned stage = 0;
  OpaqueWord planes = 0u;
  OpaqueWord facets = 0u;
  OpaqueWord depth = 0u;
  OpaqueWord format = 0u;
  OpaqueSigned product = 0;
  OpaqueSigned rounded = 0;
  OpaqueWord buffer = 0u;
  const OpaqueWord* source = nullptr;
  OpaqueWord k0 = 0u;
  OpaqueWord k1 = 0u;
  OpaqueWord k2 = 0u;
  OpaqueWord owner = 0u;
  OpaqueWord pending = 0u;
  OpaqueWord produced = 0u;
  OpaqueWord query = 0u;
  OpaqueWord flag = 0u;
  OpaqueWord tail_word = 0u;
  OpaqueWord emitted = 0u;
  OpaqueWord built = 0u;
  OpaqueWord built_two = 0u;
  OpaqueWord selected = 0u;
  OpaqueWord selected_two = 0u;
  OpaqueWide path_slot = {nullptr, nullptr};
  OpaqueWide state_slot = {nullptr, nullptr};
  OpaqueWide record_slot = {nullptr, nullptr};
  OpaqueWide tag_slot = {nullptr, nullptr};
  OpaqueKey12 current = {0u, 0u, 0u};
  OpaqueKey12 tagged = {0u, 0u, 0u};
  OpaqueKey12 staged = {0u, 0u, 0u};
  OpaqueKey12 descriptor = {0u, 0u, 0u};

  __asm__ volatile(
      "testl %4, %4\n\t"
      "jz 1f\n\t"
      "movzwl 0xc(%4), %0\n\t"
      "movzwl 0xe(%4), %1\n\t"
      "movzbl 0x10(%4), %2\n\t"
      "movl (%4), %3\n\t"
      "1:\n\t"
      : "=r"(planes), "=r"(facets), "=r"(depth), "=r"(format)
      : "r"(arg2)
      : "cc", "memory");
  if (arg2 == nullptr) {
    PKG_APP_SERVICES_SAFE_WAVE11_BARRIER();
    return false;
  }
  buffer = static_cast<OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(ports.prepare_0068e8f0(
          &self->encoder_088, static_cast<OpaqueHalf>(planes),
          static_cast<OpaqueHalf>(facets), static_cast<OpaqueByte>(depth),
          (format == OPAQUE_FORMAT_PNG) ? 1u : 0u)));
  product = static_cast<OpaqueSigned>(depth & 0xffu) *
            static_cast<OpaqueSigned>(facets & 0xffffu) *
            static_cast<OpaqueSigned>(planes & 0xffffu);
  rounded = product;
  rounded += (rounded >> 31) & 7;
  rounded >>= 3;
  flag = ports.fill_011f0440(
             arg2,
             reinterpret_cast<OpaqueWord*>(static_cast<std::uintptr_t>(buffer)),
             static_cast<OpaqueWord>(rounded), 0u)
             ? 1u
             : 0u;
  if (!low_byte(flag)) {
    PKG_APP_SERVICES_SAFE_WAVE11_BARRIER();
    return false;
  }
  source = static_cast<const OpaqueWord*>(arg1);
  k0 = source[2];
  k1 = source[3];
  k2 = source[4];
  self->image_0f8.w0 = k0;
  self->image_0f8.w1 = k1;
  self->image_0f8.w2 = k2;
  current.w0 = k0;
  current.w1 = k1;
  current.w2 = k2;
  tagged.w0 = k0;
  tagged.w1 = OPAQUE_TAG_30bdee3;
  tagged.w2 = k2;
  staged.w0 = k0;
  staged.w1 = k1;
  staged.w2 = k2;
  descriptor.w0 = k0;
  descriptor.w1 = OPAQUE_TAG_2f7d0004;
  descriptor.w2 = k2;
  tag_slot.begin = const_cast<OpaqueWord*>(OPAQUE_WIDE_THUMBNAILS);
  tag_slot.end = const_cast<OpaqueWord*>(OPAQUE_WIDE_THUMBNAILS);
  pending = 0u;
  owner = static_cast<OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(ports.global_0067dcd0()));
  release_handle(pending, 0x04u);
  {
    OpaqueGlobal* global =
        reinterpret_cast<OpaqueGlobal*>(static_cast<std::uintptr_t>(owner));
    flag = global->vtable->slot_0c(global, &tagged, &pending, 0u, 0u, 0u, 0u)
               ? 1u
               : 0u;
  }
  if (!low_byte(flag)) {
    goto fail_early;
  }
  if (pending != 0u) {
    OpaqueHandle* handle =
        reinterpret_cast<OpaqueHandle*>(static_cast<std::uintptr_t>(pending));
    query = handle->vtable->slot_0c(handle, OPAQUE_TAG_30bdee3);
  } else {
    query = 0u;
  }
  flag =
      ports.resolve_005f9920(
          self, query,
          static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(arg1)), arg5)
          ? 1u
          : 0u;
  if (!low_byte(flag)) {
    goto fail_early;
  }
  {
    OpaqueDatabase* database = static_cast<OpaqueDatabase*>(arg3);
    flag = database->vtable->slot_34(database, &descriptor, &produced, 2u, 6u,
                                     1u, 0u)
               ? 1u
               : 0u;
  }
  if (!low_byte(flag)) {
    goto fail_early;
  }
  if (produced != 0u) {
    OpaqueOwner* emitter =
        reinterpret_cast<OpaqueOwner*>(static_cast<std::uintptr_t>(produced));
    emitted = emitter->vtable->slot_18(emitter, 0u);
    ports.emit_0068e1a0(&self->encoder_088, emitted);
    emitter->vtable->slot_24(emitter);
  }
  {
    tail_word =
        *reinterpret_cast<OpaqueWord*>(static_cast<OpaqueByte*>(arg3) + 0x0c);
    built = static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(
        ports.compose_00414e10(tail_word, &tag_slot, &current, arg4, 0u)));
  }
  flag = ports.write_005f97c0(self, &built) ? 1u : 0u;
  if (!low_byte(flag)) {
    stage = 1;
    goto done;
  }
  stage = 2;
  ports.push_00931e10(&state_slot, &tag_slot);
  ports.open_009317b0(&path_slot);
  flag = ports.open_009318f0(&path_slot, 3u, 2u, 1u, 0u) ? 1u : 0u;
  if (!low_byte(flag)) {
    goto done;
  }
  stage = 3;
  ports.emit_pair_0068e1a0(&self->encoder_088, &state_slot, 0u);
  ports.close_00931a70(&path_slot);
  ports.destroy_0056e2d0(&record_slot, &descriptor);
  ports.release_005f7970(&descriptor);
  built = static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(
      ports.build_005f9080(&staged, &current)));
  ports.store_005f8320(&record_slot, &built);
  ports.insert_005fa0a0(&self->block_004, &record_slot, &staged);
  ports.clear_00933960(&descriptor);
  ports.clear_00933960(&current);
  built_two = static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(
      ports.build_005f90c0(&staged, &current)));
  ports.store_005f8390(&record_slot, &built_two);
  ports.insert_005fa0d0(&self->block_024, &record_slot, &staged);
  ports.clear_005f8d80(&descriptor);
  ports.clear_005f8d80(&current);
  selected = static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(
      ports.select_005f7940(&current, &staged, &tagged)));
  ports.record_005f8ed0(&self->block_048, &selected, &tag_slot);
  selected_two = static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(
      ports.select_005f7940(&current, &staged, &tagged)));
  ports.record_005f8f00(&self->block_068, &selected_two, &tag_slot);
  ports.flush_005f8ad0(self);

done:
  if (stage == 3) {
    ports.clear_00933960(&path_slot);
    ports.clear_00931e70(&state_slot);
    ports.clear_00933960(&tag_slot);
    release_owner(produced);
    release_handle(pending, 0x04u);
    PKG_APP_SERVICES_SAFE_WAVE11_BARRIER();
    return true;
  }
  if (stage == 2) {
    ports.clear_00931e70(&state_slot);
  }
  if (stage >= 1) {
    ports.clear_00933960(&tag_slot);
  }
  release_handle(pending, 0x04u);
  PKG_APP_SERVICES_SAFE_WAVE11_BARRIER();
  return false;

fail_early:
  stage = 0;
  goto done;
}

extern "C" OpaqueBool PKG_APP_SERVICES_SAFE_WAVE11_THISCALL service_005fc330(
    OpaqueService* self, const OpaqueWord* arg1, OpaqueKey12* arg2) {
  Ports005fc330& ports = *g_ports_005fc330;
  OpaqueSigned stage = 0;
  OpaqueWord flag = 0u;
  OpaqueWord allocator = 0u;
  OpaqueWord manager = 0u;
  OpaqueWord node = 0u;
  OpaqueWord built = 0u;
  OpaqueWord side = 0u;
  OpaqueWord gate = 0u;
  OpaqueWord gate_out = 0u;
  OpaqueWord owner_size = 0u;
  OpaqueWord cast = 0u;
  OpaqueWord lift = 0u;
  OpaqueWord gate_handle = 0u;
  OpaqueWord node_two = 0u;
  OpaqueWord node_owner = 0u;
  OpaqueWord built_node = 0u;
  OpaqueWord pending = 0u;
  OpaqueWord head_owner = 0u;
  OpaqueWord found = 0u;
  OpaqueWord probe_head = 0u;
  OpaqueWord probe_tail = 0u;
  const OpaqueWord* first = nullptr;
  const OpaqueWord* limit = nullptr;
  OpaqueWide path_slot = {nullptr, nullptr};
  OpaqueWide state_slot = {nullptr, nullptr};
  OpaqueKey12 scratch = {0u, 0u, 0u};
  OpaqueKey12 located = {0u, 0u, 0u};
  OpaqueKey12 candidate = {0u, 0u, 0u};
  OpaqueKey12 descriptor = {0u, 0u, 0u};
  OpaqueKey12 emitted = {0u, 0u, 0u};
  OpaqueKey12 written = {0u, 0u, 0u};
  OpaqueKey12 resolved = {0u, 0u, 0u};
  OpaqueWord words[16] = {0u};

  arg2->w0 = OPAQUE_KEY12_INVALID;
  arg2->w1 = OPAQUE_KEY12_INVALID;
  arg2->w2 = OPAQUE_KEY12_INVALID;
  ports.push_00931e10(&path_slot, const_cast<OpaqueWord*>(arg1));
  ports.state_009317b0(&state_slot);
  flag = ports.query_009318f0(&state_slot, 1u, 3u, 1u, 0u) ? 1u : 0u;
  if (!low_byte(flag)) {
    stage = 0;
    goto epilogue;
  }
  allocator = static_cast<OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(ports.get_0067cb30()));
  emitted.w0 = OPAQUE_TWO_BYTE_01667bac;
  written.w0 = OPAQUE_ONE_BYTE_01667bae;
  flag = ports.probe_005fbb00(self, &emitted, &written, &scratch) ? 1u : 0u;
  flag = low_byte(flag) ? 1u : 0u;
  ports.close_00931a70(&state_slot);
  resolved.w0 = scratch.w1;
  resolved.w1 = scratch.w2;
  resolved.w2 = scratch.w0;
  ports.reset_005f8050(&self->block_048, &found, &resolved);
  if (found != 0u) {
    const OpaqueWord* entry =
        reinterpret_cast<const OpaqueWord*>(static_cast<std::uintptr_t>(found));
    arg2->w0 = entry[3];
    arg2->w1 = entry[4];
    arg2->w2 = entry[5];
    release_handle(head_owner, 0x08u);
    stage = 1;
    goto epilogue;
  }
  manager = *reinterpret_cast<OpaqueWord*>(
      static_cast<std::uintptr_t>(allocator) + 0x58u);
  cast = ports.resolve_0054e460(
             reinterpret_cast<void*>(static_cast<std::uintptr_t>(manager)),
             probe_head, probe_tail, &located)
             ? 1u
             : 0u;
  if (low_byte(cast)) {
    OpaqueFactory* factory =
        reinterpret_cast<OpaqueFactory*>(static_cast<std::uintptr_t>(manager));
    cast = factory->vtable->slot_58(factory, &located) ? 1u : 0u;
    if (low_byte(cast)) {
      arg2->w0 = located.w0;
      arg2->w1 = located.w1;
      arg2->w2 = located.w2;
      release_handle(candidate.w0, 0x08u);
      stage = 1;
      goto epilogue;
    }
  }
  if (!low_byte(flag)) {
    stage = 3;
    goto epilogue;
  }
  side = static_cast<OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(ports.side_0067de60()));
  {
    OpaqueSide* gate_side =
        reinterpret_cast<OpaqueSide*>(static_cast<std::uintptr_t>(side));
    gate_side->vtable->slot_08(gate_side, &resolved, &descriptor, 0u);
  }
  node = static_cast<OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(ports.factory_00f473a0(
          OPAQUE_CLASS_0058, OPAQUE_NAME_013fa0a8, 0u, 0u, 0u, 0u)));
  built = 0u;
  if (node != 0u) {
    built = static_cast<OpaqueWord>(
        reinterpret_cast<std::uintptr_t>(ports.build_00550450(&node)));
    if (built != 0u) {
      OpaqueOwner* owner =
          reinterpret_cast<OpaqueOwner*>(static_cast<std::uintptr_t>(built));
      owner->vtable->slot_00(owner);
    }
  }
  ports.meta_00551620(&built, &scratch, &located, &candidate, &descriptor,
                      &emitted, &written, &path_slot, &state_slot, words[9],
                      words[8], words[7], OPAQUE_NAME_013f9f38, 1u);
  ports.seal_00551b60(&built, words[6], words[5]);
  if (words[4] == self->field_044) {
    ports.flag_00550990(&built, 1u);
  }
  first = reinterpret_cast<const OpaqueWord*>(
      static_cast<std::uintptr_t>(words[3]));
  limit = reinterpret_cast<const OpaqueWord*>(
      static_cast<std::uintptr_t>(words[2]));
  while (first != limit) {
    ports.drop_00550b00(&built, *first);
    ++first;
  }
  gate = static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(
      ports.build_006b1f90(OPAQUE_RESOURCE_11ac19d)));
  {
    OpaqueGlobal* global =
        reinterpret_cast<OpaqueGlobal*>(ports.global_0067dcd0());
    gate_out = 0u;
    (void)global->vtable->slot_48(global, &gate_out, OPAQUE_KEY12_INVALID);
    gate_handle = gate_out;
  }
  if (gate_handle == 0u) {
    flag = 0u;
    stage = 2;
    goto tail;
  }
  node_two = static_cast<OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(ports.node_00926020(
          OPAQUE_CLASS_0024, OPAQUE_NAME_013fa0a8, 0u, 0u, 0u, 0u)));
  built_node = 0u;
  if (node_two != 0u) {
    built_node = static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(
        ports.node_008e2380(&node_two, 0u, 0u, &emitted, 0u)));
    if (built_node != 0u) {
      OpaqueHandle* handle = reinterpret_cast<OpaqueHandle*>(
          static_cast<std::uintptr_t>(built_node));
      handle->vtable->slot_04(handle);
    }
  }
  release_handle(pending, 0x04u);
  {
    OpaqueGate* gate_object =
        reinterpret_cast<OpaqueGate*>(static_cast<std::uintptr_t>(gate_handle));
    flag = gate_object->vtable->slot_1c(gate_object, built_node, &located, 0u,
                                        &node_owner)
               ? 1u
               : 0u;
  }
  if (!low_byte(flag)) {
    flag = 0u;
    goto release_pair;
  }
  {
    OpaqueWord* target =
        reinterpret_cast<OpaqueWord*>(static_cast<std::uintptr_t>(built_node));
    target[2] = located.w0;
    target[3] = located.w1;
    target[4] = located.w2;
  }
  {
    OpaqueWord handle = built_node;
    ports.toggle_006ad010(&handle);
  }
  {
    OpaqueGlobal* global =
        reinterpret_cast<OpaqueGlobal*>(ports.global_0067dcd0());
    flag = global->vtable->slot_20(global, 0u, 0u, gate, 0u, pending) ? 1u : 0u;
  }
  {
    OpaqueWord handle = pending;
    ports.toggle_006ac0a0(&handle, 2u);
  }
  {
    OpaqueWord handle = node_two;
    ports.toggle_006ad010(&handle);
  }
  if (low_byte(flag)) {
    OpaqueGlobal* global =
        reinterpret_cast<OpaqueGlobal*>(ports.global_0067dcd0());
    (void)global->vtable->slot_20(global, 0u, 0u, gate, 0u, pending);
    flag = 1u;
    if (!low_byte(flag)) {
      flag = 0u;
    }
  }
  {
    OpaqueWord handle = built;
    ports.toggle_006ac0a0(&handle, 2u);
  }
  descriptor.w0 = OPAQUE_TAG_2f7d0004;
  descriptor.w1 = words[0];
  descriptor.w2 = words[1];
  if (!low_byte(flag)) {
    goto release_pair;
  }
  release_handle(node_owner, 0x08u);
  {
    OpaqueGate* gate_object =
        reinterpret_cast<OpaqueGate*>(static_cast<std::uintptr_t>(gate_handle));
    flag = gate_object->vtable->slot_34(gate_object, &head_owner, &descriptor,
                                        2u, 6u, 1u, 0u)
               ? 1u
               : 0u;
  }
  if (!low_byte(flag)) {
    flag = 0u;
    goto release_pair;
  }
  if (node_owner != 0u) {
    OpaqueOwner* record =
        reinterpret_cast<OpaqueOwner*>(static_cast<std::uintptr_t>(node_owner));
    owner_size = record->vtable->slot_18(record, 0u);
    ports.emit_0068e1a0(&self->encoder_088, owner_size);
    record->vtable->slot_24(record);
  }

release_pair:
  release_handle(built_node, 0x08u);
  release_handle(pending, 0x04u);
  if (!low_byte(flag)) {
    stage = 2;
    goto tail;
  }
  arg2->w0 = located.w0;
  arg2->w1 = located.w1;
  arg2->w2 = located.w2;
  self->image_0f8.w0 = located.w0;
  self->image_0f8.w1 = located.w1;
  self->image_0f8.w2 = located.w2;
  if ((words[10] & words[11]) != 0xffffffffu) {
    OpaqueWord holder = *reinterpret_cast<OpaqueWord*>(
        static_cast<std::uintptr_t>(allocator) + 0x58u);
    lift = ports.resolve_0054e460(
               reinterpret_cast<void*>(static_cast<std::uintptr_t>(holder)),
               words[11], words[10], &located)
               ? 1u
               : 0u;
    if (low_byte(lift)) {
      ports.mark_0054ed50(
          reinterpret_cast<void*>(static_cast<std::uintptr_t>(holder)), 1u,
          words[11], words[10]);
    }
    ports.lift_0054e250(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(holder)), words[11],
        &descriptor, &located);
  }
  resolved.w0 = words[12];
  resolved.w1 = arg2->w0;
  resolved.w2 = arg2->w1;
  candidate.w0 = words[13];
  candidate.w1 = arg2->w2;
  candidate.w2 = words[14];
  ports.record_005f8170(&self->block_048, 0u, &resolved, &head_owner);
  resolved.w0 = arg2->w0;
  resolved.w1 = arg2->w1;
  resolved.w2 = arg2->w2;
  candidate.w0 = words[12];
  candidate.w1 = words[13];
  candidate.w2 = words[14];
  ports.record_005f8240(&self->block_068, 0u, &candidate, &head_owner);
  {
    OpaqueGlobal* global =
        reinterpret_cast<OpaqueGlobal*>(ports.global_0067dcc0());
    global->vtable->slot_14(
        global, OPAQUE_MARSHAL_5132ed1,
        static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(&head_owner)));
  }
  stage = 2;

tail:
  release_handle(built_node, 0x08u);
  release_handle(pending, 0x04u);
  release_handle(head_owner, 0x08u);

epilogue:
  if (stage == 1) {
    ports.close_005f8e40(&path_slot);
    ports.close_00931e70(&state_slot);
    PKG_APP_SERVICES_SAFE_WAVE11_BARRIER();
    return false;
  }
  if (stage == 2 || stage == 3) {
    ports.close_005f8e40(&path_slot);
  }
  ports.close_00931e70(&state_slot);
  PKG_APP_SERVICES_SAFE_WAVE11_BARRIER();
  return low_byte(flag);
}

extern "C" void PKG_APP_SERVICES_SAFE_WAVE11_THISCALL
service_0060ee90(OpaqueOwner60ee90* self, void* arg1, void* arg2, void* arg3) {
  Ports0060ee90& ports = *g_ports_0060ee90;
  OpaqueWord pending = 0u;
  OpaqueWord owner = 0u;
  OpaqueWord handle_word = 0u;
  OpaqueWord allocated = 0u;
  OpaqueWord node = 0u;
  OpaqueWord* slot = &handle_word;
  OpaqueKey12 request = {0u, 0u, 0u};
  const OpaqueWord* key = static_cast<const OpaqueWord*>(arg1);
  const OpaqueWord* pair = nullptr;
  (void)arg2;
  (void)arg3;

  request.w0 = key[0];
  request.w1 = OPAQUE_TAG_30bdee3;
  request.w2 = key[2];
  owner = static_cast<OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(ports.global_0067dcd0()));
  release_handle(pending, 0x04u);
  (void)ports.global_0c(
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(owner)), &request,
      slot, 0u, 0u, 0u, 0u);
  if (pending != 0u) {
    OpaqueHandle* released =
        reinterpret_cast<OpaqueHandle*>(static_cast<std::uintptr_t>(pending));
    handle_word = released->vtable->slot_0c(released, OPAQUE_TAG_30bdee3);
  } else {
    handle_word = 0u;
  }
  pair = ports.probe_005507a0(
      reinterpret_cast<OpaqueWord*>(static_cast<std::uintptr_t>(handle_word)));
  if ((pair[0] & pair[1]) == 0xffffffffu) {
    ports.drop_00551af0(
        reinterpret_cast<OpaqueWord*>(static_cast<std::uintptr_t>(handle_word)),
        self->slot_060, self->slot_064);
    {
      void* global = ports.global_0067dcd0();
      (void)ports.global_20(global, 0u, 0u, 0u);
      (void)ports.global_6c(global, 1u, 0u);
    }
    handle_word = static_cast<OpaqueWord>(
        reinterpret_cast<std::uintptr_t>(ports.owner_005f7930(arg1)));
    (void)ports.compose_005fb430(reinterpret_cast<OpaqueWord*>(
        static_cast<std::uintptr_t>(handle_word)));
  }
  self->slot_060 = OPAQUE_KEY12_INVALID;
  self->slot_064 = OPAQUE_KEY12_INVALID;
  allocated = static_cast<OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(ports.factory_00615810(0x30u)));
  if (allocated != 0u) {
    node = static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(
        ports.build_00615d30(reinterpret_cast<OpaqueWord*>(
                                 static_cast<std::uintptr_t>(allocated)),
                             handle_word, self->tag_058, request.w0, 0u, 0u)));
  } else {
    node = 0u;
  }
  if (node != 0u) {
    OpaqueOwner* built =
        reinterpret_cast<OpaqueOwner*>(static_cast<std::uintptr_t>(node));
    built->vtable->slot_04(built);
    if (self->end_010 == self->capacity_014) {
      OpaqueWord value = node;
      ports.grow_0060db40(self->base_008, &value);
    } else {
      OpaqueWord* pushed = self->end_010 - 1;
      self->end_010 = pushed;
      if (pushed != nullptr) {
        *pushed = node;
        built->vtable->slot_04(built);
      }
    }
    built->vtable->slot_08(built);
  }
  ports.place_0060cf30(self, arg1);
  release_handle(pending, 0x04u);
  PKG_APP_SERVICES_SAFE_WAVE11_BARRIER();
}

}

#undef PKG_APP_SERVICES_SAFE_WAVE11_BARRIER
#undef PKG_APP_SERVICES_SAFE_WAVE11_CDECL
#undef PKG_APP_SERVICES_SAFE_WAVE11_THISCALL
#undef PKG_APP_SERVICES_SAFE_WAVE11_NOINLINE
