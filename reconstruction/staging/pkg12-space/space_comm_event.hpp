#pragma once

#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-12 Space communication events require an x86-32 target"
#endif

namespace openspore::reconstruction::pkg12_space {

struct cCommEvent;
struct cCommManager;

using OpaquePayloadWord = std::uint32_t;

extern "C" __thiscall __attribute__((naked)) void
pkg12_space_comm_event_00aeb720(cCommManager* manager,
                                OpaquePayloadWord payload0,
                                OpaquePayloadWord payload1,
                                OpaquePayloadWord payload2,
                                OpaquePayloadWord payload3,
                                OpaquePayloadWord payload4,
                                OpaquePayloadWord payload5);

}
