#pragma once

#include "property_list_access.hpp"

namespace openspore::reconstruction::wave6_resources {

#if defined(_MSC_VER)
#define WAVE6_VARIANT_THISCALL __thiscall
#else
#define WAVE6_VARIANT_THISCALL __attribute__((thiscall))
#endif

using HasParentLookup = bool(WAVE6_VARIANT_THISCALL*)(PropertyList* list,
                                                      TargetWord property_id);

struct HasParentVtable {
  void* slots_00_18[7];
  HasParentLookup get_at_1c;
};

using ObjectParentLookup = Property*(
    WAVE6_VARIANT_THISCALL*)(PropertyList * list, TargetWord property_id);

struct ObjectParentVtable {
  void* slots_00_24[10];
  ObjectParentLookup get_at_28;
};

bool WAVE6_VARIANT_THISCALL
property_list_has_property_006a2470(PropertyList* list, TargetWord property_id);
Property* WAVE6_VARIANT_THISCALL property_list_get_property_object_006a24d0(
    PropertyList* list, TargetWord property_id);

#undef WAVE6_VARIANT_THISCALL

static_assert(offsetof(HasParentVtable, get_at_1c) == 0x1c,
              "HasProperty parent slot offset");
static_assert(offsetof(ObjectParentVtable, get_at_28) == 0x28,
              "GetPropertyObject parent slot offset");

}
