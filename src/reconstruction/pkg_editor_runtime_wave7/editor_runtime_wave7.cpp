#include "editor_runtime_wave7.hpp"

#include <cmath>
#include <cstring>

#if defined(_MSC_VER)
#define PKG_W7_THISCALL __thiscall
#define PKG_W7_CDECL __cdecl
#else
#define PKG_W7_THISCALL __attribute__((thiscall))
#define PKG_W7_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_editor_runtime_wave7 {

OpaqueFixedBasis* g_fixed_basis = nullptr;
OpaqueControllerMapPorts* g_controller_map_ports = nullptr;
OpaqueControllerPorts* g_controller_ports = nullptr;

float clamp_offset_length(float length) {
  if (!(kOffsetLimit < length)) {
    return length;
  }
  return kOffsetLimit;
}

float quarter_turn_sign(float wrapped) {
  return wrapped < 0.0f ? kNegativeSign : kPositiveSign;
}

namespace {

std::uint8_t load_u8(const void* base, std::size_t offset) {
  std::uint8_t value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + offset,
              sizeof(value));
  return value;
}

float clamp_blend(float quotient) {
  if (quotient != quotient) {
    return 0.0f;
  }
  const float low = quotient > 0.0f ? quotient : 0.0f;
  return low < kClampCeiling ? low : kClampCeiling;
}

Vector3 limit_offset(Vector3 value) {
  const float length =
      std::sqrt(value.x * value.x + value.y * value.y + value.z * value.z);
  const float limited = clamp_offset_length(length);
  if (limited == length) {
    return value;
  }
  const float scale = (1.0f / length) * kOffsetLimit;
  value.x = value.x * scale;
  value.y = value.y * scale;
  value.z = value.z * scale;
  return value;
}

Vector3 subtract(const Vector3& lhs, const Vector3& rhs) {
  Vector3 result{};
  result.x = lhs.x - rhs.x;
  result.y = lhs.y - rhs.y;
  result.z = lhs.z - rhs.z;
  return result;
}

Vector3 as_vector3(const float* words) {
  Vector3 result{};
  result.x = words[0];
  result.y = words[1];
  result.z = words[2];
  return result;
}

Vector3 negated(Vector3 value) {
  const float sign = 0.0f;
  std::uint32_t mask = 0;
  std::memcpy(&mask, &sign, sizeof(mask));
  std::uint32_t bits = 0;
  std::memcpy(&bits, &value.x, sizeof(bits));
  bits ^= mask;
  std::memcpy(&value.x, &bits, sizeof(bits));
  bits = 0;
  std::memcpy(&bits, &value.y, sizeof(bits));
  bits ^= mask;
  std::memcpy(&value.y, &bits, sizeof(bits));
  bits = 0;
  std::memcpy(&bits, &value.z, sizeof(bits));
  bits ^= mask;
  std::memcpy(&value.z, &bits, sizeof(bits));
  return value;
}

bool component_matches_epsilon(float value, float epsilon) {
  const bool unordered = value != value || epsilon != epsilon;
  return unordered || value == epsilon;
}

bool any_component_matches_epsilon(const Vector3& value, const float* epsilon) {
  return component_matches_epsilon(value.x, epsilon[0]) ||
         component_matches_epsilon(value.y, epsilon[1]) ||
         component_matches_epsilon(value.z, epsilon[2]);
}

Vector3 normalize_or_zero_unchecked(const Vector3& value);

Vector3 normalize_or_zero(const Vector3& value, const float* epsilon) {
  if (!any_component_matches_epsilon(value, epsilon)) {
    return value;
  }
  return normalize_or_zero_unchecked(value);
}

Vector3 normalize_or_zero_unchecked(const Vector3& value) {
  const float length =
      std::sqrt(value.x * value.x + value.y * value.y + value.z * value.z);
  const float inverse = 1.0f / length;
  Vector3 result{};
  result.x = value.x * inverse;
  result.y = value.y * inverse;
  result.z = value.z * inverse;
  return result;
}

OpaqueController* lookup_controller(OpaqueAnimWorld* world,
                                    std::int32_t creature_id) {
  OpaqueControllerMapPorts& ports = *g_controller_map_ports;
  OpaqueControllerMap& map = world->controllers_008;
  OpaqueControllerNode* cursor = nullptr;
  ports.lower_bound_00e5c780(&map, &cursor, &creature_id);
  if (cursor == map.sentinel_004) {
    return nullptr;
  }
  void* slot = ports.find_0059c740(&map, &creature_id);
  return *static_cast<OpaqueController**>(slot);
}

OpaqueController* lookup_controller_guarded(OpaqueAnimWorld* world,
                                            std::int32_t creature_id) {
  if (world->map_enabled_038 == 0) {
    return nullptr;
  }
  return lookup_controller(world, creature_id);
}

void seed_collision_mask(OpaqueRayQuery& query, OpaquePickerWorld* picker) {
  OpaquePickerWorldVTable* vtable = picker->vtable;
  for (std::size_t index = 0; index < 5; ++index) {
    query.collision_mask[index] = 0;
  }
  query.flag_14 = static_cast<std::uint8_t>(kRayQueryFlag);
  query.flag_15 = 0;
  const std::uint32_t collision =
      vtable->set_active_28(picker, kCollisionClassRay_026f3933, false);
  if (collision < kMaskBitBound) {
    const std::size_t word = collision / kMaskBitShift;
    query.collision_mask[word] |= 1u << (collision % kMaskBitShift);
  }
}

Vector3 ray_origin(const OpaqueCreature* creature) {
  Vector3 origin{};
  origin.x = creature->position.x;
  origin.y = creature->position.y;
  origin.z = kRayOriginHeight - kRayOriginDrop;
  return origin;
}

void advance_creep(OpaqueController* controller, float seconds) {
  const float step = controller->creep_rate_080 * seconds;
  if (controller->creep_high_078 > controller->creep_low_074) {
    controller->creep_low_074 = controller->creep_low_074 + step;
    if (controller->creep_low_074 > controller->creep_high_078) {
      controller->creep_low_074 = controller->creep_high_078;
    }
  } else if (controller->creep_low_074 > controller->creep_high_078) {
    controller->creep_low_074 = controller->creep_low_074 - step;
    if (controller->creep_low_074 < controller->creep_high_078) {
      controller->creep_low_074 = controller->creep_high_078;
    }
  }
}

}

extern "C" OpaqueController* PKG_W7_THISCALL
anim_world_get_creature_controller_0059cac0(OpaqueAnimWorld* world,
                                            std::int32_t creature_id) {
  return lookup_controller_guarded(world, creature_id);
}

extern "C" void PKG_W7_THISCALL anim_world_play_animation_0059cb10(
    OpaqueAnimWorld* world, std::int32_t creature_id, OpaqueWord animation_id) {
  OpaqueController* controller = lookup_controller_guarded(world, creature_id);
  if (world->animation_enabled_03c == 0 || controller == nullptr) {
    return;
  }
  OpaqueCreature* creature = controller->creature_008;
  if (creature == nullptr) {
    return;
  }
  OpaqueCreatureVTable* vtable = creature->vtable;
  using Apply = void(PKG_W7_THISCALL*)(void*, OpaqueWord, std::uint32_t);
  Apply apply = reinterpret_cast<Apply>(reinterpret_cast<void**>(vtable)[1]);
  apply(creature, animation_id, 0u);
  g_controller_ports->publish_animation_id_007cd950(controller, animation_id);
}

extern "C" void PKG_W7_THISCALL anim_world_set_target_angle_0059cea0(
    OpaqueAnimWorld* world, std::int32_t creature_id, float angle,
    bool apply_now) {
  OpaqueController* controller = lookup_controller_guarded(world, creature_id);
  if (controller == nullptr) {
    return;
  }
  g_controller_ports->set_target_angle_0059b2f0(controller, angle, apply_now);
}

extern "C" void PKG_W7_THISCALL anim_world_set_target_position_0059cf00(
    OpaqueAnimWorld* world, std::int32_t creature_id, Vector3 position,
    bool apply_now, bool ignore_z) {
  OpaqueController* controller = lookup_controller_guarded(world, creature_id);
  if (controller == nullptr) {
    return;
  }
  g_controller_ports->set_target_position_0059b0f0(controller, &position,
                                                   apply_now, ignore_z);
}

extern "C" void PKG_W7_THISCALL controller_set_target_position_0059b0f0(
    OpaqueController* controller, const Vector3* position, bool apply_now,
    bool ignore_z) {
  OpaqueControllerPorts& ports = *g_controller_ports;
  controller->position_020 = *position;
  controller->offset_02c = *position;
  controller->offset_02c = limit_offset(controller->offset_02c);
  if (ignore_z) {
    controller->offset_02c.z = 0.0f;
  }
  if (!apply_now) {
    return;
  }
  OpaqueCreature* creature = controller->creature_008;
  creature->position = controller->offset_02c;
  controller->current_038 = controller->offset_02c;
  if (!ignore_z) {
    OpaquePickerWorld* picker = ports.picker_world_0067dd80();
    OpaqueRayQuery query{};
    seed_collision_mask(query, picker);
    Vector3 origin = ray_origin(creature);
    OpaqueRaycastOut hit{};
    OpaqueRaycastOut aux{};
    OpaqueShadowWorldVTable* shadow_vtable = controller->shadow_00c->vtable;
    const std::uint32_t found = shadow_vtable->raycast_24(
        controller->shadow_00c, &hit, &origin, kNullWord, &query, kNullWord,
        &aux, kNullWord, kNullWord);
    if (found != 0u) {
      creature->position.z = hit.x;
      (void)(aux.x == aux.x);
    }
  }
  ports.notify_00a047d0(creature, 1u);
}

extern "C" void PKG_W7_THISCALL
controller_update_0059b4b0(OpaqueController* controller, std::int32_t dt) {
  OpaqueControllerPorts& ports = *g_controller_ports;
  OpaqueFixedBasis& basis = *g_fixed_basis;
  OpaqueCreature* creature = controller->creature_008;
  if (creature == nullptr || controller->shadow_00c == nullptr) {
    return;
  }
  const float seconds =
      static_cast<float>(static_cast<std::uint32_t>(dt)) * kTimeScale;
  Vector4 weight{};
  weight.w = kClampCeiling;
  float blend_interval = kClampCeiling;
  float interval_scale = kClampCeiling;
  float blend_speed = 0.0f;
  void* handle = nullptr;
  void* handle_extra = nullptr;
  creature->vtable->get_bounds_58(creature, &handle, 0u, 0u, &handle_extra);
  void* manager = ports.manager_get_0067cb20();
  void* owner = ports.manager_slot_40(manager, handle);
  if (owner != nullptr && load_u8(owner, 0x1d) == 0) {
    blend_interval = 0.0f;
    interval_scale = 0.0f;
    blend_speed = 0.0f;
    ports.publish_animation_id_007cd950(controller, 0u);
  }
  if (ports.manager_query_00a02710(handle)) {
    weight.w = 0.0f;
    float blend = 0.0f;
    if (creature->vtable->get_blend_5c(creature, handle, &blend, &weight)) {
      blend_speed = clamp_blend(blend / blend_interval);
      weight.w = blend_speed;
    } else {
      blend_speed = 0.0f;
      weight.w = kClampCeiling;
    }
  }
  const float position_scalar =
      controller->position_rate_04c * blend_speed * seconds;
  const Vector3* moved =
      ports.lerp_vector_00699600(&weight, &controller->current_038,
                                 &controller->offset_02c, position_scalar);
  controller->current_038 = limit_offset(*moved);
  const float angle_step =
      controller->angle_rate_050 * blend_speed * interval_scale * seconds;
  controller->angle_048 = ports.lerp_angle_0069b840(
      controller->target_angle_044, controller->angle_048, angle_step);
  const Vector3 look = normalize_or_zero(
      subtract(controller->previous_058, controller->current_038),
      basis.normalize_epsilon);
  const Vector3 target = normalize_or_zero(
      subtract(controller->world_064, controller->current_038),
      basis.normalize_epsilon);
  const Vector3 orientation_basis = as_vector3(basis.orientation);
  const Vector3 projection_basis = as_vector3(basis.projection);
  const Vector3 negated_projection_basis = negated(projection_basis);
  if (controller->angle_limited_084 != 0) {
    const float look_projection =
        ports.project_0069b760(&look, &orientation_basis, &projection_basis);
    const float target_projection =
        ports.project_0069b760(&target, &projection_basis, &orientation_basis);
    const float sweep = ports.lerp_angle_0069b840(
        look_projection, target_projection, kSweepFactor * interval_scale);
    const float sine = std::sin(sweep);
    const float cosine = std::cos(sweep);
    controller->world_064.x = controller->current_038.x + sine * kTargetLead;
    controller->world_064.y = controller->current_038.y + cosine * kTargetLead;
    controller->world_064.z = controller->current_038.z + kTargetLead * 0.0f;
  } else {
    const Vector3* mixed = ports.lerp_vector_00699600(
        &weight, &target, &look, kDirectionStep * blend_speed * seconds);
    controller->world_064.x =
        controller->current_038.x + mixed->x * kTargetLead;
    controller->world_064.y =
        controller->current_038.y + mixed->y * kTargetLead;
    controller->world_064.z =
        controller->current_038.z + mixed->z * kTargetLead;
  }
  if (controller->snap_when_facing_055 != 0) {
    const float projection = ports.project_0069b760(
        &target, &negated_projection_basis, &orientation_basis);
    const float wrapped = ports.wrap_angle_0059ac00(controller->angle_048) -
                          ports.wrap_angle_0059ac00(-projection);
    if (kFacingQuarterTurn < std::fabs(wrapped)) {
      const float adjustment =
          wrapped - quarter_turn_sign(wrapped) * kFacingQuarterTurn;
      Vector3 rotated{};
      ports.rotate_00576b00(&rotated, &target, adjustment);
      const float blend_half = kReconcileHalf;
      const float blend_full = kReconcileFull;
      const float bias = kReconcileBias;
      controller->world_064.x = creature->position.x + rotated.x * blend_full +
                                basis.projection[0] * blend_half -
                                basis.orientation[1] * bias;
      controller->world_064.y = creature->position.y - rotated.y * blend_full +
                                basis.orientation[2] * blend_half;
      controller->world_064.z = creature->position.z + rotated.z * blend_full -
                                basis.projection[2] * bias;
    }
  }
  creature->position = controller->current_038;
  const float half = controller->angle_048 * kHalfAngle;
  const float sine = std::sin(half);
  const float cosine = std::cos(half);
  Vector4 row{};
  row.x = sine * basis.orientation[0];
  row.y = sine * basis.orientation[1];
  row.z = sine * basis.orientation[2];
  row.w = cosine;
  creature->orientation = row;
  if (ports.manager_query_00a027a0(handle) && creature->model_17c != nullptr &&
      creature->model_17c->smoothing_enabled_2d4 != 0) {
    if (controller->angle_limited_084 != 0) {
      creature->smoothing = controller->world_064;
    } else {
      Vector3 toward{};
      toward.x = controller->position_020.x - controller->current_038.x;
      toward.y = controller->position_020.y - controller->current_038.y;
      Vector3 steer{};
      if (std::sqrt(toward.x * toward.x + toward.y * toward.y) <= kLookRadius) {
        steer = *ports.look_direction_0059aed0(&negated_projection_basis,
                                               &toward, &creature->orientation);
        if (ports.look_blocked_0059ab70(&steer)) {
          steer = negated_projection_basis;
        }
      } else {
        steer = *ports.cross_00436ce0(&weight, &toward);
      }
      const float lead_take = kSmoothingTake;
      creature->smoothing.x =
          creature->smoothing.x * kSmoothingRetain +
          (controller->current_038.x + steer.x * kTargetLead) * lead_take;
      creature->smoothing.y =
          creature->smoothing.y * kSmoothingRetain +
          (controller->current_038.y + steer.y * kTargetLead) * lead_take;
      creature->smoothing.z =
          creature->smoothing.z * kSmoothingRetain +
          (controller->current_038.z + steer.z * kTargetLead) * lead_take;
      if (std::fabs(creature->smoothing.z) < kSnapThreshold) {
        creature->smoothing.z = 0.0f;
      }
      controller->world_064 = creature->smoothing;
      controller->previous_058 = creature->smoothing;
    }
  } else {
    creature->smoothing = controller->world_064;
  }
  if (controller->follow_ground_054 != 0) {
    return;
  }
  OpaquePickerWorld* picker = ports.picker_world_0067dd80();
  OpaqueRayQuery query{};
  seed_collision_mask(query, picker);
  Vector3 origin = ray_origin(creature);
  OpaqueRaycastOut hit{};
  OpaqueRaycastOut aux{};
  OpaqueShadowWorldVTable* shadow_vtable = controller->shadow_00c->vtable;
  const std::uint32_t found = shadow_vtable->raycast_24(
      controller->shadow_00c, &hit, &origin, kNullWord, &query, kNullWord, &aux,
      kNullWord, kNullWord);
  if (found == 0u) {
    return;
  }
  (void)(aux.x == aux.x);
  if (0.0f < controller->creep_remaining_07c) {
    controller->creep_remaining_07c = controller->creep_remaining_07c - seconds;
    return;
  }
  creature->position.z = hit.x + controller->creep_low_074;
  advance_creep(controller, seconds);
}

}

#undef PKG_W7_CDECL
#undef PKG_W7_THISCALL
