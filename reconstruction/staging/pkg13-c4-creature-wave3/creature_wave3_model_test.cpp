#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>

#include "creature_wave3.hpp"

#if defined(_MSC_VER)
#define PKG13_C4_TEST_THISCALL __thiscall
#define PKG13_C4_TEST_CDECL __cdecl
#else
#define PKG13_C4_TEST_THISCALL __attribute__((thiscall))
#define PKG13_C4_TEST_CDECL __attribute__((cdecl))
#endif

namespace {

using namespace openspore::reconstruction::pkg13_c4_creature_wave3;

enum class CallKind : std::uint8_t {
  kGetLocomotivePosition,
  kSubmitLocomotionRequest,
  kLookupSpeedScalar,
  kReleaseRequestHandle,
  kCommitContainerGrowth,
  kGetEffectsManager,
  kCreateVisualEffect,
  kResolveEffectPoolSlot,
  kEffectAddRef,
  kEffectRelease,
  kEffectStart,
  kEffectSetSourceTransform,
  kGetLocomotiveQuaternion,
};

struct TraceEntry {
  CallKind kind;
  const void* receiver = nullptr;
  std::int32_t key = 0;
  std::int32_t mode = 0;
  std::uint32_t instance_id = 0;
  std::uint32_t group_id = 0;
  std::uint32_t pool_key = 0;
  std::int32_t hard_start = 0;
  const void* argument = nullptr;
};

struct WriteSpan {
  std::size_t offset;
  std::size_t length;
};

int failures = 0;

void Expect(bool condition) {
  if (!condition) {
    ++failures;
  }
}

std::uint32_t FloatBits(float value) {
  std::uint32_t bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  return bits;
}

bool SameFloatBits(float left, float right) {
  return FloatBits(left) == FloatBits(right);
}

std::vector<TraceEntry> trace;

void Trace(CallKind kind, const void* receiver = nullptr, std::int32_t key = 0,
           std::int32_t mode = 0, std::uint32_t instance_id = 0,
           std::uint32_t group_id = 0, std::uint32_t pool_key = 0,
           std::int32_t hard_start = 0, const void* argument = nullptr) {
  trace.push_back({kind, receiver, key, mode, instance_id, group_id, pool_key,
                   hard_start, argument});
}

void ExpectKinds(const CallKind* expected, std::size_t count) {
  Expect(trace.size() == count);
  const std::size_t checked = trace.size() < count ? trace.size() : count;
  for (std::size_t index = 0; index < checked; ++index) {
    Expect(trace[index].kind == expected[index]);
  }
}

constexpr float kNaN = std::numeric_limits<float>::quiet_NaN();
constexpr float kMaxFloat = 3.40282346638528859811704183484516925e+38F;

OpaqueCreatureState creature;
OpaqueLocomotiveObject* locomotive = LocomotiveObjectOf(&creature);
OpaqueEffectPool* effect_pool = EffectPool2Of(&creature);
OpaqueEmbeddedContainer* embedded_container = EmbeddedContainerOf(&creature);
OpaqueEffectsManager manager;
OpaqueVisualEffect first_effect;
OpaqueVisualEffect second_effect;
Vector3 world_position{3.0F, 4.0F, 5.0F};
float quaternion[4] = {0.0F, 0.0F, 0.0F, 1.0F};

const float* position_result = &world_position.x;
const float* quaternion_result = quaternion;

LocomotionRequest captured_request{};
const LocomotionRequest* captured_request_address = nullptr;

std::uint8_t handle_block[64]{};
enum class CreateOutcome : std::uint8_t {
  kSucceedWithHandle,
  kSucceedWithNull,
  kFailWithNull,
  kFailWithHandle,
};

void* created_handle = nullptr;
CreateOutcome create_outcome = CreateOutcome::kSucceedWithHandle;
OpaqueVisualEffect** create_destination = nullptr;

EffectTransformProperties captured_properties{};
const EffectTransformProperties* captured_properties_address = nullptr;

OpaqueVisualEffect** pool_slot = nullptr;
OpaqueVisualEffect* pool_previous = nullptr;

double speed_scalar_result = 0.0;
const void* released_handle = nullptr;
OpaqueVisualEffect* release_first = nullptr;
OpaqueVisualEffect* release_second = nullptr;
std::int32_t release_call_count = 0;
std::uint32_t container_begin_word = 0U;
std::uint32_t container_end_word = 0U;
const OpaqueEmbeddedContainer* container_receiver = nullptr;
std::int32_t position_call_count = 0;
std::int32_t start_call_count = 0;

const float* PKG13_C4_TEST_THISCALL
GetLocomotivePosition(OpaqueLocomotiveObject* receiver) {
  Trace(CallKind::kGetLocomotivePosition, receiver);
  ++position_call_count;
  Expect(receiver == locomotive);
  return position_result;
}

void PKG13_C4_TEST_THISCALL SubmitLocomotionRequest(
    OpaqueLocomotiveObject* receiver, LocomotionRequest* request) {
  Trace(CallKind::kSubmitLocomotionRequest, receiver, 0, 0, 0, 0, 0, 0,
        request);
  Expect(receiver == locomotive);
  request->release_handle = created_handle;
  captured_request = *request;
  captured_request_address = request;
}

double PKG13_C4_TEST_THISCALL LookupSpeedScalar(OpaqueCreatureState* receiver,
                                                std::int32_t key,
                                                std::int32_t mode) {
  Trace(CallKind::kLookupSpeedScalar, receiver, key, mode);
  Expect(receiver == &creature);
  return speed_scalar_result;
}

void PKG13_C4_TEST_CDECL ReleaseRequestHandle(void* handle) {
  Trace(CallKind::kReleaseRequestHandle, handle);
  released_handle = handle;
}

void PKG13_C4_TEST_THISCALL
CommitContainerGrowth(OpaqueEmbeddedContainer* container,
                      std::uint32_t begin_word, std::uint32_t end_word) {
  Trace(CallKind::kCommitContainerGrowth, container);
  Expect(container == embedded_container);
  container_receiver = container;
  container_begin_word = begin_word;
  container_end_word = end_word;
}

OpaqueEffectsManager* PKG13_C4_TEST_CDECL GetEffectsManager() {
  Trace(CallKind::kGetEffectsManager);
  return &manager;
}

bool PKG13_C4_TEST_THISCALL
CreateVisualEffect(OpaqueEffectsManager* receiver, std::uint32_t instance_id,
                   std::uint32_t group_id, OpaqueVisualEffect** destination) {
  Trace(CallKind::kCreateVisualEffect, receiver, 0, 0, instance_id, group_id);
  Expect(receiver == &manager);
  Expect(group_id == 0U);
  create_destination = destination;
  const bool succeeded = create_outcome == CreateOutcome::kSucceedWithHandle ||
                         create_outcome == CreateOutcome::kSucceedWithNull;
  const bool delivers = create_outcome == CreateOutcome::kSucceedWithHandle ||
                        create_outcome == CreateOutcome::kFailWithHandle;
  *destination =
      delivers ? static_cast<OpaqueVisualEffect*>(created_handle) : nullptr;
  return succeeded;
}

OpaqueVisualEffect** PKG13_C4_TEST_THISCALL
ResolveEffectPoolSlot(OpaqueEffectPool* receiver, const std::uint32_t* key) {
  Trace(CallKind::kResolveEffectPoolSlot, receiver, 0, 0, 0, 0, *key);
  Expect(receiver == effect_pool);
  return pool_slot;
}

std::int32_t PKG13_C4_TEST_THISCALL EffectAddRef(OpaqueVisualEffect* effect) {
  Trace(CallKind::kEffectAddRef, effect);
  return 1;
}

std::int32_t PKG13_C4_TEST_THISCALL EffectRelease(OpaqueVisualEffect* effect) {
  Trace(CallKind::kEffectRelease, effect);
  ++release_call_count;
  if (release_call_count == 1) {
    release_first = effect;
  } else if (release_call_count == 2) {
    release_second = effect;
  }
  return 0;
}

void PKG13_C4_TEST_THISCALL EffectStart(OpaqueVisualEffect* effect,
                                        std::int32_t hard_start) {
  Trace(CallKind::kEffectStart, effect, 0, 0, 0, 0, 0, hard_start);
  ++start_call_count;
}

void PKG13_C4_TEST_THISCALL EffectSetSourceTransform(
    OpaqueVisualEffect* effect, const EffectTransformProperties* properties) {
  Trace(CallKind::kEffectSetSourceTransform, effect, 0, 0, 0, 0, 0, 0,
        properties);
  captured_properties = *properties;
  captured_properties_address = properties;
}

const float* PKG13_C4_TEST_THISCALL
GetLocomotiveQuaternion(OpaqueLocomotiveObject* receiver) {
  Trace(CallKind::kGetLocomotiveQuaternion, receiver);
  Expect(receiver == locomotive);
  return quaternion_result;
}

void InstallPorts() {
  g_native_ports = NativePorts{GetLocomotivePosition,
                               SubmitLocomotionRequest,
                               LookupSpeedScalar,
                               ReleaseRequestHandle,
                               CommitContainerGrowth,
                               GetEffectsManager,
                               CreateVisualEffect,
                               ResolveEffectPoolSlot,
                               EffectAddRef,
                               EffectRelease,
                               EffectStart,
                               EffectSetSourceTransform,
                               GetLocomotiveQuaternion,
                               &CopyMatrix3_0041cb40,
                               &QuaternionToMatrix3_0059c190};
}

void ResetFixture() {
  std::memset(&creature, 0, sizeof(creature));
  std::memset(&first_effect, 0, sizeof(first_effect));
  std::memset(&second_effect, 0, sizeof(second_effect));
  std::memset(handle_block, 0, sizeof(handle_block));
  DAT_013ef480 = 0.99F;
  DAT_0146a32c = kMaxFloat;
  DAT_01470f1c = 2.0F;
  DAT_01485720 = 1.0F;
  DAT_0150c900 = 10.0F;
  DAT_0168d910 = 0.0F;
  DAT_0168d914 = 0.0F;
  DAT_0168d918 = 0.0F;
  DAT_0168d988 = 0.0F;
  DAT_0168d98c = 0.0F;
  DAT_0168d990 = 0.0F;
  for (std::size_t index = 0; index < 9U; ++index) {
    DAT_0168d964[index] = 0.0F;
  }
  world_position = Vector3{3.0F, 4.0F, 5.0F};
  quaternion[0] = 0.0F;
  quaternion[1] = 0.0F;
  quaternion[2] = 0.0F;
  quaternion[3] = 1.0F;
  position_result = &world_position.x;
  quaternion_result = quaternion;
  captured_request = LocomotionRequest{};
  captured_request_address = nullptr;
  created_handle = handle_block + 8;
  const std::uint32_t header_word = 1U;
  std::memcpy(handle_block + 4, &header_word, sizeof(header_word));
  create_outcome = CreateOutcome::kSucceedWithHandle;
  create_destination = nullptr;
  captured_properties = EffectTransformProperties{};
  captured_properties_address = nullptr;
  pool_slot = reinterpret_cast<OpaqueVisualEffect**>(&pool_previous);
  pool_previous = nullptr;
  speed_scalar_result = 0.0;
  released_handle = nullptr;
  release_first = nullptr;
  release_second = nullptr;
  release_call_count = 0;
  container_begin_word = 0U;
  container_end_word = 0U;
  container_receiver = nullptr;
  position_call_count = 0;
  start_call_count = 0;
  trace.clear();
}

void RunWalkTo(std::int32_t speed_state, const Vector3& dst,
               const Vector3& oriented, float goal, float acceptable) {
  Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0(
      &creature, speed_state, &dst, &oriented, goal, acceptable);
}

OpaqueVisualEffect* RunPool2Effect(std::uint32_t instance_id,
                                   std::uint32_t pool_key) {
  return Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460(
      &creature, instance_id, pool_key);
}

void TestGlobalConstants() {
  Expect(FloatBits(DAT_0168d910) == 0x00000000U);
  Expect(FloatBits(DAT_0168d914) == 0x00000000U);
  Expect(FloatBits(DAT_0168d918) == 0x00000000U);
  Expect(FloatBits(DAT_013ef480) == 0x3F7D70A4U);
  Expect(FloatBits(DAT_0146a32c) == 0x7F7FFFFFU);
  Expect(FloatBits(DAT_01470f1c) == 0x40000000U);
  Expect(FloatBits(DAT_01485720) == 0x3F800000U);
  Expect(FloatBits(DAT_0150c900) == 0x41200000U);
  Expect(FloatBits(DAT_0168d988) == 0x00000000U);
  Expect(FloatBits(DAT_0168d98c) == 0x00000000U);
  Expect(FloatBits(DAT_0168d990) == 0x00000000U);
  for (std::size_t index = 0; index < 9U; ++index) {
    Expect(FloatBits(DAT_0168d964[index]) == 0x00000000U);
  }
}

void TestRequestWriteSet() {
  const WriteSpan written[] = {
      {0x00U, 4U}, {0x04U, 4U}, {0x08U, 4U}, {0x14U, 4U}, {0x18U, 4U},
      {0x1CU, 4U}, {0x20U, 4U}, {0x24U, 4U}, {0x4CU, 1U}, {0x50U, 4U},
      {0x54U, 4U}, {0x58U, 4U}, {0x5CU, 4U}, {0x60U, 4U}, {0x64U, 4U},
      {0x68U, 4U}, {0x6CU, 4U}, {0x70U, 4U}};

  LocomotionRequest request;
  std::memset(&request, 0xA5, sizeof(request));
  const Vector3 dst{0.0F, 0.0F, 2.0F};
  const Vector3 unit{1.0F, 0.0F, 0.0F};
  BuildLocomotionRequest(dst, unit, 1.25F, 2.5F, &request);

  const std::uint8_t* raw = reinterpret_cast<const std::uint8_t*>(&request);
  for (std::size_t index = 0; index < sizeof(request); ++index) {
    bool expected_write = false;
    for (const WriteSpan& span : written) {
      if (index >= span.offset && index < span.offset + span.length) {
        expected_write = true;
      }
    }
    if (expected_write) {
      Expect(raw[index] != 0xA5U);
    } else {
      Expect(raw[index] == 0xA5U);
    }
  }

  Expect(request.release_handle == nullptr);
  Expect(request.reserved_word_04 == 0U);
  Expect(request.reserved_word_08 == 0U);
  Expect(request.reserved_word_24 == 0U);
  Expect(request.reserved_word_70 == 0U);
  Expect(request.orientation_flag == 0U);
  Expect(request.property_tag_5c == 3U);
  Expect(SameFloatBits(request.goal_stop_distance, 1.25F));
  Expect(SameFloatBits(request.acceptable_stop_distance, 2.5F));
  Expect(SameFloatBits(request.threshold_64, 0.99F));
  Expect(FloatBits(request.limit_68) == 0x7F7FFFFFU);
  Expect(FloatBits(request.residual_6c) == 0x00000000U);
  Expect(SameFloatBits(request.dst_position.x, dst.x));
  Expect(SameFloatBits(request.dst_position.z, dst.z));
  Expect(SameFloatBits(request.perpendicular_unit.y, unit.y));
  Expect(SameFloatBits(request.perpendicular_unit.z, unit.z));
}

void TestPerpendicularProjection() {
  ResetFixture();
  const Vector3 dst{0.0F, 0.0F, 5.0F};
  const Vector3 oriented{0.0F, 3.0F, 4.0F};
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(SameFloatBits(captured_request.perpendicular_unit.x, 0.0F));
  Expect(SameFloatBits(captured_request.perpendicular_unit.y, 1.0F));
  Expect(SameFloatBits(captured_request.perpendicular_unit.z, 0.0F));
  Expect(SameFloatBits(captured_request.dst_position.z, 5.0F));
  Expect(SameFloatBits(captured_request.goal_stop_distance, 1.0F));
  Expect(SameFloatBits(captured_request.acceptable_stop_distance, 2.0F));
  Expect(captured_request.property_tag_5c == 3U);
  Expect(captured_request.release_handle == created_handle);
  Expect(captured_request_address != nullptr);
  const CallKind expected_calls[] = {
      CallKind::kGetLocomotivePosition, CallKind::kSubmitLocomotionRequest,
      CallKind::kLookupSpeedScalar, CallKind::kCommitContainerGrowth,
      CallKind::kReleaseRequestHandle};
  ExpectKinds(expected_calls,
              sizeof(expected_calls) / sizeof(expected_calls[0]));
  Expect(trace[0].receiver == locomotive);
  Expect(trace[1].receiver == locomotive);
  Expect(trace[2].receiver == &creature);
  Expect(trace[2].key == kStandardSpeedState);
  Expect(trace[2].mode == 0);
  Expect(trace[3].receiver == embedded_container);
  Expect(trace[4].receiver == created_handle);
}

void TestZeroVectorSkipsMath() {
  ResetFixture();
  world_position = Vector3{0.0F, 0.0F, 0.0F};
  const Vector3 dst{0.0F, 0.0F, 5.0F};
  const Vector3 oriented{0.0F, 3.0F, 4.0F};
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(SameFloatBits(captured_request.perpendicular_unit.y, 3.0F));
  Expect(SameFloatBits(captured_request.perpendicular_unit.z, 4.0F));
  Expect(trace[0].kind == CallKind::kGetLocomotivePosition);
  Expect(trace[1].kind == CallKind::kSubmitLocomotionRequest);
}

void TestNegativeZeroBasisTreatedAsZero() {
  ResetFixture();
  world_position = Vector3{-0.0F, -0.0F, -0.0F};
  const Vector3 dst{0.0F, 0.0F, 5.0F};
  const Vector3 oriented{0.0F, 3.0F, 4.0F};
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(FloatBits(captured_request.perpendicular_unit.y) == 0x40400000U);
  Expect(SameFloatBits(captured_request.perpendicular_unit.z, 4.0F));
}

void TestNaNBasisEntersMath() {
  ResetFixture();
  world_position = Vector3{kNaN, 0.0F, 0.0F};
  const Vector3 dst{0.0F, 0.0F, 5.0F};
  const Vector3 oriented{0.0F, 3.0F, 4.0F};
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(SameFloatBits(captured_request.perpendicular_unit.x, 0.0F));
  Expect(SameFloatBits(captured_request.perpendicular_unit.y, 1.0F));
  Expect(SameFloatBits(captured_request.perpendicular_unit.z, 0.0F));
}

void TestProjectionBypassField() {
  ResetFixture();
  SetCreatureWord(&creature, kProjectionBypassFieldOffset, 1U);
  const Vector3 dst{0.0F, 0.0F, 5.0F};
  const Vector3 oriented{0.0F, 3.0F, 4.0F};
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(SameFloatBits(captured_request.perpendicular_unit.y, 3.0F));
  Expect(SameFloatBits(captured_request.perpendicular_unit.z, 4.0F));
  const CallKind expected_calls[] = {
      CallKind::kGetLocomotivePosition, CallKind::kSubmitLocomotionRequest,
      CallKind::kLookupSpeedScalar, CallKind::kCommitContainerGrowth,
      CallKind::kReleaseRequestHandle};
  ExpectKinds(expected_calls,
              sizeof(expected_calls) / sizeof(expected_calls[0]));
  Expect(trace[0].receiver == locomotive);
  Expect(trace[1].receiver == locomotive);
  Expect(position_call_count == 1);
}

void TestBypassStillCallsPositionCallback() {
  ResetFixture();
  const Vector3 dst{0.0F, 0.0F, 5.0F};
  const Vector3 oriented{0.0F, 3.0F, 4.0F};

  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(position_call_count == 1);
  Expect(trace[0].kind == CallKind::kGetLocomotivePosition);

  const std::uint32_t bypass_values[] = {1U, 0x00010000U, 0xFFFFFFFFU};
  for (const std::uint32_t bypass : bypass_values) {
    ResetFixture();
    SetCreatureWord(&creature, kProjectionBypassFieldOffset, bypass);
    RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
    Expect(position_call_count == 1);
    Expect(trace[0].kind == CallKind::kGetLocomotivePosition);
    Expect(trace[1].kind == CallKind::kSubmitLocomotionRequest);
    Expect(trace[0].receiver == locomotive);
    Expect(trace[0].receiver != reinterpret_cast<const void*>(&creature));
    Expect(SameFloatBits(captured_request.perpendicular_unit.y, 3.0F));
    Expect(SameFloatBits(captured_request.perpendicular_unit.z, 4.0F));
  }

  ResetFixture();
  SetCreatureWord(&creature, kProjectionBypassFieldOffset, 0xFFFFFFFFU);
  position_result = &world_position.x;
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(position_call_count == 1);
  Expect(trace[0].kind == CallKind::kGetLocomotivePosition);
  Expect(SameFloatBits(captured_request.perpendicular_unit.y, 3.0F));
  Expect(SameFloatBits(captured_request.perpendicular_unit.z, 4.0F));
}

void TestEmbeddedContainerReceiver() {
  ResetFixture();
  SetCreatureWord(&creature, kContainerOffset + kContainerBeginWordOffset,
                  0x0BADF00DU);
  SetCreatureWord(&creature, kContainerOffset + kContainerEndWordOffset,
                  0x00C0FFEEU);
  const Vector3 dst{0.0F, 0.0F, 5.0F};
  const Vector3 oriented{0.0F, 3.0F, 4.0F};
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(container_receiver == embedded_container);
  Expect(container_receiver == reinterpret_cast<const OpaqueEmbeddedContainer*>(
                                   creature.bytes + kContainerOffset));
  Expect(container_receiver !=
         reinterpret_cast<const OpaqueEmbeddedContainer*>(&creature));
  Expect(container_begin_word == 0x0BADF00DU);
  Expect(container_end_word == 0x00C0FFEEU);
  Expect(trace[3].receiver == container_receiver);
  Expect(trace[3].receiver != reinterpret_cast<const void*>(&creature));

  ResetFixture();
  SetCreatureWord(&creature, kContainerOffset + kContainerBeginWordOffset, 0U);
  SetCreatureWord(&creature, kContainerOffset + kContainerEndWordOffset, 0U);
  SetCreatureWord(&creature, 0x00000000U, 0x11111111U);
  SetCreatureWord(&creature, 0x00000004U, 0x22222222U);
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(container_begin_word == 0U);
  Expect(container_end_word == 0U);
  Expect(container_receiver == embedded_container);
}

void TestDegenerateBasisLengthProducesNan() {
  ResetFixture();
  const Vector3 dst{0.0F, 0.0F, 0.0F};
  const Vector3 oriented{0.0F, 3.0F, 4.0F};
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(std::isnan(captured_request.perpendicular_unit.x));
  Expect(std::isnan(captured_request.perpendicular_unit.y));
  Expect(std::isnan(captured_request.perpendicular_unit.z));
  Expect(trace[0].kind == CallKind::kGetLocomotivePosition);
}

void TestZeroProjectionSkipsRenormalization() {
  ResetFixture();
  const Vector3 dst{0.0F, 0.0F, 1.0F};
  const Vector3 oriented{0.0F, 0.0F, 1.0F};
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(FloatBits(captured_request.perpendicular_unit.x) == 0x00000000U);
  Expect(FloatBits(captured_request.perpendicular_unit.y) == 0x00000000U);
  Expect(FloatBits(captured_request.perpendicular_unit.z) == 0x00000000U);
}

void TestParallelDirectionProjectsToZero() {
  ResetFixture();
  const Vector3 dst{0.0F, 0.0F, 5.0F};
  const Vector3 oriented{0.0F, 0.0F, 7.0F};
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(FloatBits(captured_request.perpendicular_unit.x) == 0x00000000U);
  Expect(FloatBits(captured_request.perpendicular_unit.y) == 0x00000000U);
  Expect(FloatBits(captured_request.perpendicular_unit.z) == 0x00000000U);
}

void TestGeneralProjectionIsUnitLength() {
  ResetFixture();
  const Vector3 dst{3.0F, 0.0F, 4.0F};
  const Vector3 oriented{-2.0F, 5.0F, 1.0F};
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  const Vector3& unit = captured_request.perpendicular_unit;
  const double length = std::sqrt(static_cast<double>(unit.x) * unit.x +
                                  static_cast<double>(unit.y) * unit.y +
                                  static_cast<double>(unit.z) * unit.z);
  Expect(std::fabs(length - 1.0) < 1e-6);
  const double dot = static_cast<double>(dst.x) * unit.x +
                     static_cast<double>(dst.y) * unit.y +
                     static_cast<double>(dst.z) * unit.z;
  Expect(std::fabs(dot) < 1e-5);
}

void TestSpeedStateAndSpeedModeFlag() {
  ResetFixture();
  speed_scalar_result = 1.5;
  const Vector3 dst{0.0F, 0.0F, 5.0F};
  const Vector3 oriented{0.0F, 3.0F, 4.0F};
  RunWalkTo(7, dst, oriented, 1.0F, 2.0F);
  Expect(CreatureWord(&creature, kSpeedStateFieldOffset) == 7U);
  Expect(
      SameFloatBits(CreatureFloat(&creature, kSpeedScalarFieldOffset), 1.5F));
  Expect(CreatureWord(&creature, kTransitResetFieldOffset) == 0U);
  Expect(trace[2].key == 7);
  Expect(trace[2].mode == 0);

  ResetFixture();
  SetCreatureByte(&creature, kSpeedModeFlagOffset, 1U);
  SetCreatureWord(&creature, kTransitResetFieldOffset, 0x5A5A5A5AU);
  speed_scalar_result = 0.25;
  RunWalkTo(9, dst, oriented, 1.0F, 2.0F);
  Expect(trace[2].key == kStandardSpeedState);
  Expect(trace[2].mode == kStandardSpeedMode);
  Expect(
      SameFloatBits(CreatureFloat(&creature, kSpeedScalarFieldOffset), 10.25F));
  Expect(CreatureWord(&creature, kSpeedStateFieldOffset) == 9U);
  Expect(CreatureWord(&creature, kTransitResetFieldOffset) == 0U);
}

void TestContainerGrowthArgumentOrder() {
  ResetFixture();
  SetCreatureWord(&creature, kContainerOffset + kContainerBeginWordOffset,
                  0x11112222U);
  SetCreatureWord(&creature, kContainerOffset + kContainerEndWordOffset,
                  0x33334444U);
  const Vector3 dst{0.0F, 0.0F, 5.0F};
  const Vector3 oriented{0.0F, 3.0F, 4.0F};
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(container_begin_word == 0x11112222U);
  Expect(container_end_word == 0x33334444U);
  Expect(trace[3].receiver == embedded_container);
}

void TestHandleReleaseGuards() {
  ResetFixture();
  const Vector3 dst{0.0F, 0.0F, 5.0F};
  const Vector3 oriented{0.0F, 3.0F, 4.0F};

  std::memset(handle_block + 4, 0, 4);
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(captured_request.release_handle == created_handle);
  Expect(released_handle == nullptr);
  Expect(trace.size() == 4U);

  ResetFixture();
  created_handle = nullptr;
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(captured_request.release_handle == nullptr);
  Expect(released_handle == nullptr);
  Expect(trace.size() == 4U);

  ResetFixture();
  const std::uint32_t live_header = 0x7F7F7F7FU;
  std::memcpy(handle_block + 4, &live_header, sizeof(live_header));
  RunWalkTo(kStandardSpeedState, dst, oriented, 1.0F, 2.0F);
  Expect(released_handle == created_handle);
  Expect(trace.size() == 5U);
}

void TestQuaternionToMatrixExact() {
  struct QuaternionCase {
    float quaternion[4];
    float expected[9];
  };

  const QuaternionCase cases[] = {
      {{0.0F, 0.0F, 0.0F, 1.0F},
       {1.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 1.0F}},
      {{1.0F, 0.0F, 0.0F, 0.0F},
       {1.0F, 0.0F, 0.0F, 0.0F, -1.0F, 0.0F, 0.0F, 0.0F, -1.0F}},
      {{0.0F, 1.0F, 0.0F, 0.0F},
       {-1.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, -1.0F}},
      {{0.0F, 0.0F, 1.0F, 0.0F},
       {-1.0F, 0.0F, 0.0F, 0.0F, -1.0F, 0.0F, 0.0F, 0.0F, 1.0F}},
      {{0.0F, 0.0F, 1.0F, 1.0F},
       {-1.0F, 2.0F, 0.0F, -2.0F, -1.0F, 0.0F, 0.0F, 0.0F, 1.0F}},
      {{0.0F, 1.0F, 1.0F, 0.0F},
       {-3.0F, 0.0F, 0.0F, 0.0F, -1.0F, 2.0F, 0.0F, 2.0F, -1.0F}},
  };

  for (const QuaternionCase& item : cases) {
    Matrix3 matrix{};
    QuaternionToMatrix3_0059c190(&matrix, item.quaternion);
    for (std::size_t index = 0; index < 9U; ++index) {
      Expect(SameFloatBits(matrix.m[index], item.expected[index]));
    }
  }
}

void TestPoolEffectSuccessPath() {
  ResetFixture();
  created_handle = reinterpret_cast<void*>(&first_effect);
  OpaqueVisualEffect* result = RunPool2Effect(0xABCD1234U, 9U);
  Expect(result == &first_effect);
  const CallKind expected_calls[] = {CallKind::kGetEffectsManager,
                                     CallKind::kCreateVisualEffect,
                                     CallKind::kResolveEffectPoolSlot,
                                     CallKind::kEffectAddRef,
                                     CallKind::kGetLocomotivePosition,
                                     CallKind::kGetLocomotiveQuaternion,
                                     CallKind::kEffectSetSourceTransform,
                                     CallKind::kEffectStart,
                                     CallKind::kEffectRelease};
  ExpectKinds(expected_calls,
              sizeof(expected_calls) / sizeof(expected_calls[0]));
  Expect(trace[1].instance_id == 0xABCD1234U);
  Expect(trace[1].group_id == 0U);
  Expect(trace[1].receiver == &manager);
  Expect(create_destination != nullptr);
  Expect(trace[2].pool_key == 9U);
  Expect(trace[2].receiver == effect_pool);
  Expect(trace[3].receiver == &first_effect);
  Expect(pool_previous == &first_effect);
  Expect(release_call_count == 1);
  Expect(release_first == &first_effect);
  Expect(release_second == nullptr);
  Expect(trace[4].receiver == locomotive);
  Expect(trace[5].receiver == locomotive);
  Expect(trace[6].receiver == &first_effect);
  Expect(trace[7].receiver == &first_effect);
  Expect(trace[7].hard_start == 0);
  Expect(trace[8].receiver == &first_effect);
  Expect(start_call_count == 1);
}

void TestPoolEffectReplacesPrevious() {
  ResetFixture();
  created_handle = reinterpret_cast<void*>(&first_effect);
  pool_previous = &second_effect;
  OpaqueVisualEffect* result = RunPool2Effect(1U, 2U);
  Expect(result == &first_effect);
  const CallKind expected_calls[] = {CallKind::kGetEffectsManager,
                                     CallKind::kCreateVisualEffect,
                                     CallKind::kResolveEffectPoolSlot,
                                     CallKind::kEffectAddRef,
                                     CallKind::kEffectRelease,
                                     CallKind::kGetLocomotivePosition,
                                     CallKind::kGetLocomotiveQuaternion,
                                     CallKind::kEffectSetSourceTransform,
                                     CallKind::kEffectStart,
                                     CallKind::kEffectRelease};
  ExpectKinds(expected_calls,
              sizeof(expected_calls) / sizeof(expected_calls[0]));
  Expect(trace[3].receiver == &first_effect);
  Expect(trace[4].receiver == &second_effect);
  Expect(pool_previous == &first_effect);
  Expect(release_call_count == 2);
  Expect(release_first == &second_effect);
  Expect(release_second == &first_effect);
  Expect(trace[9].receiver == &first_effect);
}

void TestPoolEffectSameHandleSkipsRefcount() {
  ResetFixture();
  created_handle = reinterpret_cast<void*>(&first_effect);
  pool_previous = &first_effect;
  OpaqueVisualEffect* result = RunPool2Effect(1U, 2U);
  Expect(result == &first_effect);
  const CallKind expected_calls[] = {CallKind::kGetEffectsManager,
                                     CallKind::kCreateVisualEffect,
                                     CallKind::kResolveEffectPoolSlot,
                                     CallKind::kGetLocomotivePosition,
                                     CallKind::kGetLocomotiveQuaternion,
                                     CallKind::kEffectSetSourceTransform,
                                     CallKind::kEffectStart,
                                     CallKind::kEffectRelease};
  ExpectKinds(expected_calls,
              sizeof(expected_calls) / sizeof(expected_calls[0]));
  Expect(pool_previous == &first_effect);
  Expect(release_call_count == 1);
  Expect(release_first == &first_effect);
  Expect(start_call_count == 1);
}

void TestPoolEffectNullCreatedReleasesPrevious() {
  ResetFixture();
  create_outcome = CreateOutcome::kSucceedWithNull;
  pool_previous = &second_effect;
  OpaqueVisualEffect* result = RunPool2Effect(1U, 2U);
  Expect(result == nullptr);
  const CallKind expected_calls[] = {
      CallKind::kGetEffectsManager,       CallKind::kCreateVisualEffect,
      CallKind::kResolveEffectPoolSlot,   CallKind::kEffectRelease,
      CallKind::kGetLocomotivePosition,   CallKind::kGetLocomotiveQuaternion,
      CallKind::kEffectSetSourceTransform};
  ExpectKinds(expected_calls,
              sizeof(expected_calls) / sizeof(expected_calls[0]));
  Expect(trace[3].receiver == &second_effect);
  Expect(pool_previous == nullptr);
  Expect(release_call_count == 1);
  Expect(release_first == &second_effect);
  Expect(release_second == nullptr);
  Expect(start_call_count == 0);
  Expect(trace[6].receiver == nullptr);
}

void TestPoolEffectServiceFailure() {
  ResetFixture();
  created_handle = reinterpret_cast<void*>(&first_effect);
  create_outcome = CreateOutcome::kFailWithNull;
  OpaqueVisualEffect* result = RunPool2Effect(5U, 6U);
  Expect(result == nullptr);
  const CallKind expected_calls[] = {CallKind::kGetEffectsManager,
                                     CallKind::kCreateVisualEffect};
  ExpectKinds(expected_calls,
              sizeof(expected_calls) / sizeof(expected_calls[0]));
  Expect(trace[1].instance_id == 5U);
  Expect(trace[1].group_id == 0U);
  Expect(start_call_count == 0);
  Expect(create_destination != nullptr);
}

void TestPoolEffectTransformProperties() {
  ResetFixture();
  created_handle = reinterpret_cast<void*>(&first_effect);
  RunPool2Effect(1U, 2U);
  Expect(trace[6].argument != nullptr);
  Expect(captured_properties_address ==
         static_cast<const EffectTransformProperties*>(trace[6].argument));
  const EffectTransformProperties* properties = &captured_properties;
  Expect(properties->property_flags == 6U);
  Expect(properties->property_count == 2);
  Expect(SameFloatBits(properties->world_position.x, 3.0F));
  Expect(SameFloatBits(properties->world_position.y, 4.0F));
  Expect(SameFloatBits(properties->world_position.z, 5.0F));
  Expect(SameFloatBits(properties->uniform_scale, 1.0F));
  const float expected_identity[9] = {1.0F, 0.0F, 0.0F, 0.0F, 1.0F,
                                      0.0F, 0.0F, 0.0F, 1.0F};
  for (std::size_t index = 0; index < 9U; ++index) {
    Expect(
        SameFloatBits(properties->rotation.m[index], expected_identity[index]));
  }
  Expect(reinterpret_cast<std::uintptr_t>(captured_properties_address) % 4U ==
         0U);
}

void TestPoolEffectRotationUsesQuaternion() {
  ResetFixture();
  created_handle = reinterpret_cast<void*>(&first_effect);
  const float half_about_y[4] = {0.0F, 0.0F, 1.0F, 0.0F};
  std::memcpy(quaternion, half_about_y, sizeof(half_about_y));
  quaternion_result = quaternion;
  RunPool2Effect(1U, 2U);
  Expect(captured_properties_address ==
         static_cast<const EffectTransformProperties*>(trace[6].argument));
  const EffectTransformProperties* properties = &captured_properties;
  const float expected_about_y[9] = {-1.0F, 0.0F, 0.0F, 0.0F, -1.0F,
                                     0.0F,  0.0F, 0.0F, 1.0F};
  for (std::size_t index = 0; index < 9U; ++index) {
    Expect(
        SameFloatBits(properties->rotation.m[index], expected_about_y[index]));
  }
  Expect(properties->property_flags == 6U);
  Expect(properties->property_count == 2);
}

}

int main() {
  InstallPorts();
  TestGlobalConstants();
  TestRequestWriteSet();
  TestPerpendicularProjection();
  TestZeroVectorSkipsMath();
  TestNegativeZeroBasisTreatedAsZero();
  TestNaNBasisEntersMath();
  TestProjectionBypassField();
  TestBypassStillCallsPositionCallback();
  TestEmbeddedContainerReceiver();
  TestDegenerateBasisLengthProducesNan();
  TestZeroProjectionSkipsRenormalization();
  TestParallelDirectionProjectsToZero();
  TestGeneralProjectionIsUnitLength();
  TestSpeedStateAndSpeedModeFlag();
  TestContainerGrowthArgumentOrder();
  TestHandleReleaseGuards();
  TestQuaternionToMatrixExact();
  TestPoolEffectSuccessPath();
  TestPoolEffectReplacesPrevious();
  TestPoolEffectSameHandleSkipsRefcount();
  TestPoolEffectNullCreatedReleasesPrevious();
  TestPoolEffectServiceFailure();
  TestPoolEffectTransformProperties();
  TestPoolEffectRotationUsesQuaternion();
  return failures == 0 ? 0 : 1;
}
