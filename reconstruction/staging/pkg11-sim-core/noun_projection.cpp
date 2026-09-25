#include "noun_projection.hpp"

namespace openspore::reconstruction::pkg11_sim_core {

#if defined(_MSC_VER)
#define PKG11_THISCALL __thiscall
#else
#define PKG11_THISCALL __attribute__((thiscall))
#endif

NounProjectionVector* PKG11_THISCALL pkg11_sim_core_00b21340(
    NounProjection* projection, NounCreateCallback create_callback,
    NounClearCallback clear_callback, NounAddCallback add_callback,
    NounFilterCallback filter_callback, TargetWord noun_id) {
  OrderedMapEntry* result = nullptr;
  pkg20_gameglobal::pkg20_gameglobal_00e5c780(&projection->noun_map, &result,
                                              &noun_id);

  NounProjectionVector* value = nullptr;
  if (result ==
      reinterpret_cast<OrderedMapEntry*>(&projection->noun_map.anchor)) {
    value = create_callback();
    const NounMapPair pair{noun_id, value};
    NounMapInsertResult insertion{};
    (void)noun_projection_insert_00ba8420(&projection->noun_map, &insertion,
                                          &pair, nullptr);
  } else {
    value = reinterpret_cast<NounMapEntry*>(result)->value;
  }

  if (value->needs_update != 0) {
    clear_callback(value);

    NounListNode* node =
        reinterpret_cast<NounListNode*>(projection->list_sentinel.next_link);
    if (node != nullptr) {
      node = reinterpret_cast<NounListNode*>(
          reinterpret_cast<unsigned char*>(node) - 0x0c);
    }
    NounListNode* const end = &projection->list_sentinel;
    while (node != end) {
      if (filter_callback(node, noun_id) != 0) {
        add_callback(value, node);
      }
      void* const next_link = node->next_link;
      if (next_link != nullptr) {
        node = reinterpret_cast<NounListNode*>(
            reinterpret_cast<unsigned char*>(next_link) - 0x0c);
      } else {
        node = nullptr;
      }
    }
    value->needs_update = 0;
  }

  return value;
}

#undef PKG11_THISCALL

}
