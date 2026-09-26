#include "creature_wave3.hpp"

#include <cmath>

extern "C" {
float DAT_013ef480 = 0.99F;
float DAT_0146a32c = 3.40282346638528859811704183484516925e+38F;
float DAT_01470f1c = 2.0F;
float DAT_01485720 = 1.0F;
float DAT_0150c900 = 10.0F;
float DAT_0168d910 = 0.0F;
float DAT_0168d914 = 0.0F;
float DAT_0168d918 = 0.0F;
float DAT_0168d964[9] = {0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F};
float DAT_0168d988 = 0.0F;
float DAT_0168d98c = 0.0F;
float DAT_0168d990 = 0.0F;
}

namespace openspore::reconstruction::pkg13_c4_creature_wave3 {

NativePorts g_native_ports{};

float InverseExtendedUnitLength(const Vector3& value) {
  const double x = static_cast<double>(value.x);
  const double y = static_cast<double>(value.y);
  const double z = static_cast<double>(value.z);
  const double sum = (x * x + y * y) + z * z;
  return static_cast<float>(1.0 / std::sqrt(sum));
}

void BuildLocomotionRequest(const Vector3& dst_position,
                            Vector3 perpendicular_unit,
                            float goal_stop_distance,
                            float acceptable_stop_distance,
                            LocomotionRequest* request) {
  request->release_handle = nullptr;
  request->reserved_word_04 = 0U;
  request->reserved_word_08 = 0U;
  request->dst_position = dst_position;
  request->goal_stop_distance = goal_stop_distance;
  request->reserved_word_24 = 0U;
  request->orientation_flag = 0U;
  request->perpendicular_unit = perpendicular_unit;
  request->property_tag_5c = static_cast<std::uint32_t>(kPropertyTagValue);
  request->acceptable_stop_distance = acceptable_stop_distance;
  request->limit_68 = DAT_0146a32c;
  request->residual_6c = 0.0F;
  request->threshold_64 = DAT_013ef480;
  request->reserved_word_70 = 0U;
}

extern "C" void PKG13_C4_THISCALL
Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0(
    OpaqueCreatureState* creature, std::int32_t speed_state,
    const Vector3* dst_position, const Vector3* oriented_vector,
    float goal_stop_distance, float acceptable_stop_distance) {
  const NativePorts& ports = g_native_ports;
  OpaqueLocomotiveObject* locomotive = LocomotiveObjectOf(creature);

  Vector3 perpendicular_unit = *oriented_vector;

  const float* basis = ports.get_locomotive_position(locomotive);

  if (CreatureWord(creature, kProjectionBypassFieldOffset) == 0U) {
    if (basis[0] != DAT_0168d910 || basis[1] != DAT_0168d914 ||
        basis[2] != DAT_0168d918) {
      const float inverse_length = InverseExtendedUnitLength(*dst_position);
      const float unit_x = dst_position->x * inverse_length;
      const float unit_y = dst_position->y * inverse_length;
      const float unit_z = dst_position->z * inverse_length;

      const float projection =
          (oriented_vector->y * unit_y + oriented_vector->x * unit_x) +
          oriented_vector->z * unit_z;

      perpendicular_unit.x = oriented_vector->x - unit_x * projection;
      perpendicular_unit.y = oriented_vector->y - unit_y * projection;
      perpendicular_unit.z = oriented_vector->z - unit_z * projection;

      if (perpendicular_unit.x != DAT_0168d910 ||
          perpendicular_unit.y != DAT_0168d914 ||
          perpendicular_unit.z != DAT_0168d918) {
        const float output_inverse =
            InverseExtendedUnitLength(perpendicular_unit);
        perpendicular_unit.x = output_inverse * perpendicular_unit.x;
        perpendicular_unit.y = perpendicular_unit.y * output_inverse;
        perpendicular_unit.z = perpendicular_unit.z * output_inverse;
      }
    }
  }

  LocomotionRequest request{};
  BuildLocomotionRequest(*dst_position, perpendicular_unit, goal_stop_distance,
                         acceptable_stop_distance, &request);

  ports.submit_locomotion_request(locomotive, &request);

  SetCreatureWord(creature, kSpeedStateFieldOffset,
                  static_cast<std::uint32_t>(speed_state));

  double speed_scalar = 0.0;
  if (CreatureByte(creature, kSpeedModeFlagOffset) != 0U) {
    speed_scalar = ports.lookup_speed_scalar(creature, kStandardSpeedState,
                                             kStandardSpeedMode) +
                   static_cast<double>(DAT_0150c900);
  } else {
    speed_scalar = ports.lookup_speed_scalar(creature, speed_state, 0);
  }

  SetCreatureFloat(creature, kSpeedScalarFieldOffset,
                   static_cast<float>(speed_scalar));
  SetCreatureWord(creature, kTransitResetFieldOffset, 0U);

  ports.commit_container_growth(
      EmbeddedContainerOf(creature),
      CreatureWord(creature, kContainerOffset + kContainerBeginWordOffset),
      CreatureWord(creature, kContainerOffset + kContainerEndWordOffset));

  void* handle = request.release_handle;
  if (handle != nullptr) {
    std::uint32_t header_word = 0;
    std::memcpy(&header_word, static_cast<const std::uint8_t*>(handle) - 4U,
                sizeof(header_word));
    if (header_word != 0U) {
      ports.release_request_handle(handle);
    }
  }
}

extern "C" void PKG13_C4_CDECL
QuaternionToMatrix3_0059c190(Matrix3* destination, const float* quaternion) {
  const float q0 = quaternion[0];
  const float q1 = quaternion[1];
  const float q2 = quaternion[2];
  const float q3 = quaternion[3];
  const float two = DAT_01470f1c;

  const float q0q0 = q0 * q0;
  const float q1q1 = q1 * q1;
  const float q2q2 = q2 * q2;
  const float q0q1 = q0 * q1;
  const float q0q2 = q0 * q2;
  const float q0q3 = q0 * q3;
  const float q1q2 = q1 * q2;
  const float q1q3 = q1 * q3;
  const float q2q3 = q2 * q3;

  destination->m[0] = DAT_01485720 - (q2q2 + q1q1) * two;
  destination->m[1] = (q2q3 + q0q1) * two;
  destination->m[2] = (q0q2 - q1q3) * two;
  destination->m[3] = (q0q1 - q2q3) * two;
  destination->m[4] = DAT_01485720 - (q2q2 + q0q0) * two;
  destination->m[5] = (q0q3 + q1q2) * two;
  destination->m[6] = (q1q3 + q0q2) * two;
  destination->m[7] = (q1q2 - q0q3) * two;
  destination->m[8] = DAT_01485720 - (q1q1 + q0q0) * two;
}

extern "C" void PKG13_C4_THISCALL CopyMatrix3_0041cb40(Matrix3* destination,
                                                       const float* source) {
  std::memcpy(destination->m, source, sizeof(destination->m));
}

extern "C" OpaqueVisualEffect* PKG13_C4_THISCALL
Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460(
    OpaqueCreatureState* creature, std::uint32_t instance_id,
    std::uint32_t pool_key) {
  const NativePorts& ports = g_native_ports;
  OpaqueVisualEffect* handle = nullptr;

  if (handle != nullptr) {
    handle = nullptr;
    ports.effect_release(handle);
  }

  OpaqueEffectsManager* manager = ports.get_effects_manager();

  if (ports.create_visual_effect(manager, instance_id, 0U, &handle)) {
    OpaqueVisualEffect** slot =
        ports.resolve_effect_pool_slot(EffectPool2Of(creature), &pool_key);
    OpaqueVisualEffect* previous = *slot;
    if (handle != previous) {
      if (handle != nullptr) {
        ports.effect_add_ref(handle);
      }
      *slot = handle;
      if (previous != nullptr) {
        ports.effect_release(previous);
      }
    }

    EffectTransformProperties properties{};
    properties.world_position.x = DAT_0168d988;
    properties.world_position.y = DAT_0168d98c;
    properties.world_position.z = DAT_0168d990;
    properties.property_flags = 0U;
    properties.property_count = 0;
    properties.uniform_scale = DAT_01485720;
    CopyMatrix3_0041cb40(&properties.rotation, DAT_0168d964);

    const float* position =
        ports.get_locomotive_position(LocomotiveObjectOf(creature));
    properties.world_position.x = position[0];
    properties.world_position.y = position[1];
    properties.world_position.z = position[2];
    properties.property_flags = static_cast<std::uint16_t>(
        properties.property_flags | kPropertyFlagPosition);
    properties.property_count =
        static_cast<std::int16_t>(properties.property_count + 1);

    Matrix3 rotation{};
    QuaternionToMatrix3_0059c190(&rotation, ports.get_locomotive_quaternion(
                                                LocomotiveObjectOf(creature)));
    std::memcpy(&properties.rotation, rotation.m,
                sizeof(properties.rotation.m));
    properties.property_flags = static_cast<std::uint16_t>(
        properties.property_flags | kPropertyFlagRotation);
    properties.property_count =
        static_cast<std::int16_t>(properties.property_count + 1);

    ports.effect_set_source_transform(handle, &properties);
  }

  if (handle != nullptr) {
    ports.effect_start(handle, 0);
  }
  if (handle != nullptr) {
    ports.effect_release(handle);
  }
  return handle;
}

}
