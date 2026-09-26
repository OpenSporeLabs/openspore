#include "pkg_advanced_palette_wave11.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_advanced_palette_wave11 {
namespace {

constexpr std::uint32_t kAllocateBytes = 0x17cU;
constexpr std::uint32_t kAllocateTag = 0x0013eb430U;
constexpr std::size_t kItemSlotBase = 0x27bU;
constexpr std::uint32_t kItemIndexBase = 0x3e8U;
constexpr std::uint32_t kItemSlotCount = 5U;
constexpr std::uint32_t kSwatchKey = 0x029da727U;
constexpr std::uint32_t kHostKey = 0x0ee3f516eU;
constexpr std::uint32_t kProbeKey = 0x01cbb2f62U;
constexpr std::uint32_t kScaleKey = 0x005cd5de9U;
constexpr std::uint32_t kCheckA = 0x3e8U;
constexpr std::uint32_t kCheckB = 0x3e9U;
constexpr std::uint32_t kCheckC = 0x3eaU;
constexpr std::uint32_t kLogAccept = 0x0bb58117eU;
constexpr std::uint32_t kLogRetry = 0x0dc91625aU;
constexpr std::uint32_t kLogBusy = 0x04fc39619U;
constexpr std::uint32_t kLogDetach = 0x0e5469985U;
constexpr std::uint32_t kBroadcastTag = 0x06493807U;
constexpr std::uint32_t kNotifyToken = 0x03150c27U;
constexpr std::uint32_t kLaunchToken = 0x0522f9ceU;
constexpr std::uint32_t kAnchorHead = 0x013f7e34U;
constexpr std::uint32_t kAnchorTail = 0x013f7e30U;
constexpr std::uint32_t kWindowA0 = 0x1249ff0fU;
constexpr std::uint32_t kWindowA1 = 0x2f7d0004U;
constexpr std::uint32_t kWindowA2 = 0x100d976eU;
constexpr std::uint32_t kWindowB0 = 0x3cf13a01U;
constexpr std::uint32_t kWindowB1 = 0x2f7d0004U;
constexpr std::uint32_t kWindowB2 = 0x011c0bdeU;
constexpr std::uint32_t kModeAttached = 0x71fa7d3fU;
constexpr std::uint32_t kModeDetached = 0x5e71ab9bU;
constexpr std::uint32_t kModelKey = 0x2399be55U;
constexpr std::uint32_t kTypeRebuildA = 0x7be2440U;
constexpr std::uint32_t kTypeRebuildB = 0x7be2441U;
constexpr std::uint32_t kTypeStampA = 0x7be2444U;
constexpr std::uint32_t kTypeStampB = 0x7be2445U;
constexpr std::uint32_t kTypeTerminal = 0x1cU;
constexpr std::uint32_t kNeutral = 0U;
constexpr std::uint32_t kDetachedMode = 6U;

std::uint32_t bits_of(float value) {
  std::uint32_t out = kNeutral;
  std::memcpy(&out, &value, sizeof(out));
  return out;
}

std::uint32_t bits_of(const void *value) {
  return reinterpret_cast<std::uint32_t>(value);
}

std::uint8_t *item_slot(OpaqueViewer *self, std::uint32_t index) {
  return reinterpret_cast<std::uint8_t *>(self) + index - kItemSlotBase;
}

OpaqueSwatch *resolve_swatch() {
  OpaqueSwatchManager *manager = unresolved_00401020();
  if (manager == nullptr) {
    return nullptr;
  }
  OpaqueSwatchHost *host = unresolved_01137690(manager);
  if (host == nullptr) {
    return nullptr;
  }
  OpaqueRenderer *renderer = host->vtable->slot38(host);
  if (renderer == nullptr) {
    return nullptr;
  }
  return renderer->vtable->slot0c(renderer, kSwatchKey);
}

void post_window(OpaqueSwatchHost *sink, std::uint32_t payload) {
  unresolved_0080d710(sink, payload, kNeutral, 1U);
}

void open_windows(OpaqueViewer *self) {
  OpaqueSwatchManager *manager = unresolved_00401020();
  const std::uint32_t host = unresolved_0113ae10(manager);
  if (host != kNeutral && self->opaque16b != 0) {
    const std::uint32_t fallback =
        self->field17c->field14 != nullptr
            ? reinterpret_cast<std::uint32_t>(self->field17c->field14)
            : host;
    unresolved_005ed6c0(reinterpret_cast<OpaqueSwatchHost *>(fallback));
  }
  const std::uint32_t window = self->vtable->slot34(self, kNeutral, 1U);
  post_window(static_cast<OpaqueSwatchHost *>(unresolved_0067cad0()), window);
  if (self->field194 != nullptr) {
    post_window(static_cast<OpaqueSwatchHost *>(unresolved_0067cad0()),
                reinterpret_cast<std::uint32_t>(self->field194));
  }
}

bool palette_round(std::uint32_t expected) {
  OpaqueManager *first = unresolved_0067caa0();
  first->vtable->slot54(first, 1U);
  OpaqueManager *second = unresolved_0067caa0();
  return second->vtable->slot54(second, 1U) == expected;
}

bool build_window_pair(OpaqueViewer *self) {
  OpaqueKey3 first;
  first.field00 = kWindowA0;
  first.field04 = kWindowA1;
  first.field08 = kWindowA2;
  OpaqueKey3 second;
  second.field00 = kWindowB0;
  second.field04 = kWindowB1;
  second.field08 = kWindowB2;
  OpaqueWindow *made_a = static_cast<OpaqueWindow *>(unresolved_00807880(
      &first, 0.0F, 0.0F, self->field5c->vtable->slot10(self->field5c)));
  unresolved_00b5f950(&self->field1b8, made_a);
  if (self->field1b8 == nullptr) {
    return false;
  }
  OpaqueWindow *made_b = static_cast<OpaqueWindow *>(unresolved_00807880(
      &second, 0.0F, 0.0F, self->field5c->vtable->slot10(self->field5c)));
  unresolved_00b5f950(&self->field1bc, made_b);
  if (self->field1bc == nullptr) {
    return false;
  }
  OpaqueWindow *window_a = self->field1b8;
  OpaqueWindow *window_b = self->field1bc;
  window_a->vtable->slot7c(window_a, 2U, kNeutral);
  window_a->vtable->slot7c(window_a, 0x10U, 1U);
  self->field5c->vtable->slot10(self->field5c)
      ->vtable->slotec(self->field5c->vtable->slot10(self->field5c), window_a);
  window_b->vtable->slot7c(window_b, 2U, kNeutral);
  window_b->vtable->slot7c(window_b, 0x10U, 1U);
  self->field5c->vtable->slot10(self->field5c)
      ->vtable->slotec(self->field5c->vtable->slot10(self->field5c), window_b);
  const float *frame = self->field5c->vtable->slot38(self->field5c);
  OpaqueRect rect;
  rect.field00 = frame[0];
  rect.field04 = frame[1];
  rect.field08 = frame[2];
  rect.field0c = frame[3];
  window_a->vtable->slot6c(window_a, &rect);
  window_b->vtable->slot6c(window_b, &rect);
  unresolved_00804fc0(self, 0.0F);
  unresolved_00804fc0(self, 0.0F);
  self->opaque184 = 1U;
  unresolved_0093a1a0(self->field1a0, 4U);
  return true;
}

void rebuild_palette(OpaqueViewer *self) {
  OpaqueManager *source = unresolved_0067caa0();
  OpaqueManager *sink = unresolved_0067caa0();
  const std::uint32_t token = source->vtable->slot04(source);
  sink->vtable->slot4c(sink, kNeutral, token);
  self->vtable->slot50(self);
}

}

std::uint32_t g_table_013f9bb0 = 0x5368d4a5U;
float g_table_01485720 = 1.0F;
std::uint32_t g_table_0151c40c = 0xb37b55b2U;
std::uint32_t g_table_0151c410 = 0xa502dc0bU;
float g_table_013f9d90 = 3.4028234663852886e+38F;
float g_table_013f51ac = -3.4028234663852886e+38F;
float g_table_015f1ce4 = 0.0F;
float g_table_015f1ce8 = 0.0F;
float g_table_015f1cec = 0.0F;
float g_table_013eb1c0 = 1.2F;
float g_table_0151c700 = 1.0F;
float g_table_01471064 = 0.5F;

extern "C" OpaqueItem *PKG_AP_THISCALL
unresolved_005f0ca0(OpaqueItemHostRoot *root, OpaqueItem *supplied) {
  OpaqueItem *item = supplied;
  if (item == nullptr) {
    void *block = unresolved_00f473a0(kAllocateBytes, kAllocateTag, kNeutral,
                                      kNeutral, kNeutral, kNeutral);
    item = block != nullptr
               ? unresolved_005f6bd0(static_cast<OpaqueItem *>(block))
               : nullptr;
  }
  OpaqueIndexNode *live = unresolved_005f0b40(&root->field08, &root->field40);
  OpaqueItem *previous = reinterpret_cast<OpaqueItem *>(live->field14);
  if (item != previous) {
    if (item != nullptr) {
      item->vtable->retain00(item);
    }
    live->field14 = reinterpret_cast<std::uint32_t>(item);
    if (previous != nullptr) {
      previous->vtable->release04(previous);
    }
  }
  if (item == nullptr) {
    return nullptr;
  }
  item->field178 = root->field40;
  root->field40 += 1U;
  item->vtable->retain00(item);
  OpaqueItem *held = item;
  OpaqueIndexNode *tag = unresolved_005f0bc0(&root->field24, &held);
  tag->field14 = g_table_013f9bb0;
  item->vtable->release04(item);
  return item;
}

extern "C" std::uint32_t PKG_AP_THISCALL
unresolved_005f2350(OpaqueRect *self, const OpaqueRect *probe) {
  const bool inside =
      probe->field00 >= self->field00 && probe->field04 >= self->field04 &&
      self->field08 > probe->field00 && self->field0c > probe->field04;
  return inside ? 1U : kNeutral;
}

extern "C" bool PKG_AP_THISCALL unresolved_005f27c0(OpaqueViewer *self,
                                                    std::uint32_t expected,
                                                    OpaqueEvent *event) {
  if (self->field16c != 0) {
    OpaqueSwatch *swatch = resolve_swatch();
    if (swatch != nullptr) {
      switch (event->field08) {
        case 1U:
          return swatch->vtable->slot28(swatch, bits_of(event->field10),
                                        bits_of(event->field14)) != 0;
        case 2U:
          return swatch->vtable->slot2c(swatch, bits_of(event->field14),
                                        bits_of(event->field10)) != 0;
        case 6U: {
          if (!swatch->vtable->slot30(swatch, event->field0c, event->field10,
                                      bits_of(event->field14))) {
            return false;
          }
          OpaqueManager *busy = unresolved_0067caa0();
          busy->vtable->slot58(busy, 1U, bits_of(self->field5c));
          item_slot(self, event->field18)[0] = 1U;
          return true;
        }
        case 7U: {
          if (item_slot(self, event->field18)[0] != 0) {
            item_slot(self, event->field18)[0] = 0U;
            std::uint32_t live = kNeutral;
            while (live < kItemSlotCount && self->field16d[live] == 0) {
              live += 1U;
            }
            if (live == kItemSlotCount) {
              OpaqueManager *idle = unresolved_0067caa0();
              idle->vtable->slot5c(idle, 1U, bits_of(self->field5c));
            }
          }
          return swatch->vtable->slot34(swatch, event->field18, event->field0c,
                                        event->field10,
                                        bits_of(event->field14)) != 0;
        }
        case 8U:
          return swatch->vtable->slot38(swatch, event->field0c, event->field10,
                                        bits_of(event->field14)) != 0;
        case 9U:
          return swatch->vtable->slot3c(swatch, event->field18, event->field0c,
                                        event->field10,
                                        bits_of(event->field14)) != 0;
        case 10U: {
          swatch->vtable->slot24(
              swatch, event->field18 == bits_of(self->field5c) ? 1U : kNeutral);
          return false;
        }
        default:
          return false;
      }
    }
  }
  switch (event->field08) {
    case 1U:
    case 2U:
    case 5U:
      return palette_round(expected);
    case 3U:
    case 4U:
    case 7U:
    case 8U:
    case 9U:
    case 10U:
    case 11U:
    case 12U:
    case 13U:
    case 14U:
    case 15U:
    case 16U:
    case 17U:
    case 18U:
    case 19U:
    case 20U:
    case 21U:
    case 22U:
    case 23U:
    case 24U:
    case 25U:
    case 26U:
    case 27U: {
      if (self->vtable->slot44(self)) {
        return false;
      }
      if (bits_of(event->field0c) != 1U) {
        return false;
      }
      if (event->field18 != bits_of(self->field5c)) {
        return false;
      }
      self->fieldec = 1U;
      const std::uint8_t head = unresolved_008d2fb0(kCheckA);
      const std::uint8_t middle = unresolved_008d2fb0(kCheckB);
      const std::uint8_t tail = unresolved_008d2fb0(kCheckC);
      if (head != 0U || middle != head || tail != 0U) {
        return false;
      }
      unresolved_00435ed0(kLogAccept, unresolved_00435e90());
      self->vtable->slot48(self);
      return false;
    }
    case 6U:
      if (event->field18 != kItemIndexBase) {
        return false;
      }
      rebuild_palette(self);
      return true;
    case kTypeRebuildA:
      rebuild_palette(self);
      return true;
    case kTypeRebuildB:
      self->vtable->slot40(self);
      self->vtable->slot4c(self);
      return true;
    case kTypeStampA:
    case kTypeStampB:
      *reinterpret_cast<std::uint32_t *>(event->field18 + 0x18U) =
          kBroadcastTag;
      return true;
    case kTypeTerminal:
      if (self->vtable->slot44(self)) {
        return false;
      }
      if (bits_of(event->field0c) != 1U) {
        return false;
      }
      if (event->field18 != bits_of(self->field5c)) {
        return false;
      }
      self->fieldec = 0U;
      self->vtable->slot4c(self);
      return false;
    default:
      return false;
  }
  return false;
}

extern "C" void PKG_AP_THISCALL unresolved_005f2e00(OpaqueViewer *self) {
  bool armed = false;
  if (self->fieldeb != 0) {
    armed =
        self->opaque166 != 0 && self->opaque160 != 0 && self->opaque163 != 0;
  } else {
    armed = self->opaque166 != 0 && self->opaque160 != 0;
  }
  if (armed) {
    if (self->field60 != nullptr) {
      self->fieldc0 = 0.0F;
    }
    if (self->field118 != nullptr) {
      self->fieldd8 = g_table_01485720;
    }
    if (self->field14 != nullptr) {
      unresolved_0080d7c0(self->field14, 1U);
    }
    if (self->field3c != nullptr) {
      self->field34->vtable->slot88(self->field34,
                                    unresolved_0080d610(self->field3c));
    }
    self->field10 = 1U;
  }
  if (self->fieldf0 != nullptr) {
    reinterpret_cast<std::uint8_t *>(self->fieldf0)[0x64] = 1U;
  }
}

extern "C" void PKG_AP_THISCALL unresolved_005f2ee0(OpaqueViewer *self) {
  if (self->field118 == nullptr) {
    return;
  }
  OpaqueTransform *transform = self->field118;
  const std::uint32_t name =
      self->field50 == kModelKey ? g_table_0151c410 : g_table_0151c40c;
  const std::int32_t count =
      transform->vtable->slot64(transform, kNeutral, kNeutral, name);
  for (std::int32_t index = 0; index < count; index += 1) {
    transform->vtable->slot70(transform, name, kNeutral, 0.0F,
                              static_cast<std::uint32_t>(index));
  }
}

extern "C" void PKG_AP_THISCALL unresolved_005f30b0(OpaqueViewer *self) {
  open_windows(self);
  self->opaque169 = 0U;
  OpaqueViewer *anchor = self;
  OpaqueApp *app = unresolved_0067dcc0();
  app->vtable->slot14(app, kLaunchToken, &anchor, kNeutral);
}

extern "C" void PKG_AP_THISCALL unresolved_005f3cf0(OpaqueViewer *self) {
  if (self->field16c != 0) {
    self->opaque160 = 1U;
    return;
  }
  OpaqueViewer *context = nullptr;
  std::uint32_t model = kNeutral;
  if (self->field14 != nullptr) {
    context = self->field14;
    model = unresolved_0093b6c0(context);
  } else if (self->field3c != nullptr) {
    context = self->field3c;
    model = unresolved_0080d5f0(context);
  } else {
    return;
  }
  if (model == kNeutral) {
    return;
  }
  OpaqueTransform *transform = self->field118;
  OpaqueBounds box;
  box.field00 = g_table_013f9d90;
  box.field04 = g_table_013f9d90;
  box.field08 = g_table_013f9d90;
  box.field0c = g_table_013f51ac;
  box.field10 = g_table_013f51ac;
  box.field14 = g_table_013f51ac;
  OpaqueFeature *feature = transform->vtable == nullptr ? nullptr
                           : transform->vtable->slot24 == nullptr
                               ? nullptr
                               : transform->field90;
  if (feature != nullptr && feature->vtable->slot1c(feature, kProbeKey)) {
    OpaqueFeature *resolved = static_cast<OpaqueFeature *>(
        feature->vtable->slot28(feature, kProbeKey));
    OpaqueBounds seed{};
    unresolved_00571d60(
        &box, unresolved_00511140(&seed, unresolved_005f2320(resolved)));
  } else {
    const float *extent = transform->vtable->slot24(transform, self->field118);
    box.field00 = extent[0];
    box.field04 = extent[1];
    box.field08 = extent[2];
    box.field0c = extent[3];
    box.field10 = extent[4];
    box.field14 = extent[5];
  }
  const bool attached = self->fieldf0 != nullptr;
  OpaqueBounds centre;
  centre.field00 = g_table_015f1ce4;
  centre.field04 = g_table_015f1ce8;
  centre.field08 = g_table_015f1cec;
  if (!attached) {
    OpaqueLocalXf frame;
    unresolved_00409930(&frame);
    frame.field04 = static_cast<std::uint16_t>(frame.field04 | 4U);
    frame.field06 = static_cast<std::uint16_t>(frame.field06 + 1U);
    frame.field08 = -((box.field0c + box.field00) * g_table_01471064);
    frame.field0c = -((box.field10 + box.field04) * g_table_01471064);
    frame.field10 = -((box.field14 + box.field08) * g_table_01471064);
    unresolved_00409dd0(&box, &frame);
    centre.field00 = frame.field08;
    centre.field04 = frame.field0c;
    centre.field08 = frame.field10;
  }
  float scale = g_table_013eb1c0;
  OpaqueProperty *resolved_slot = nullptr;
  OpaqueService *service = unresolved_0067de30();
  if (resolved_slot != nullptr) {
    resolved_slot->vtable->slot04(resolved_slot);
    resolved_slot = nullptr;
  }
  bool scaled = false;
  if (service->vtable->slot2c(service, self->field4c, self->field54,
                              &resolved_slot) &&
      resolved_slot->vtable->slot1c(resolved_slot, kScaleKey)) {
    unresolved_0040cf10(resolved_slot, kScaleKey, &scale);
    scaled = true;
  }
  if (!scaled && self->fieldf0 != nullptr) {
    scale = g_table_0151c700;
  }
  OpaqueItemHost *host = self->field60;
  const float *span = host->vtable->slot38(host);
  const float aspect = (span[2] - span[0]) / (span[3] - span[1]);
  OpaqueViewer *model_context = nullptr;
  std::uint32_t second = kNeutral;
  if (self->field14 != nullptr) {
    model_context = self->field14;
    second = unresolved_0093b6c0(model_context);
  } else if (self->field3c != nullptr) {
    model_context = self->field3c;
    second = unresolved_0080d5f0(model_context);
  } else {
    second = kNeutral;
  }
  const std::uint32_t mode = attached ? kNeutral : kDetachedMode;
  unresolved_0067ddb0()->vtable->slot14(unresolved_0067ddb0(), &box, second,
                                        self->field174, scale, mode, aspect);
  if (!attached) {
    transform->field08 = static_cast<std::uint16_t>(transform->field08 | 4U);
    transform->field0a = static_cast<std::uint16_t>(transform->field0a + 1U);
    transform->field0c = centre.field00;
    transform->field10 = centre.field04;
    transform->field14 = centre.field08;
  }
  self->opaque160 = 1U;
  if (resolved_slot != nullptr) {
    resolved_slot->vtable->slot04(resolved_slot);
  }
  (void)context;
  (void)model;
  (void)model_context;
}

extern "C" void PKG_AP_THISCALL unresolved_005f4310(
    OpaqueViewer *self, const OpaqueKey3 *name, std::uint32_t unused_word,
    OpaqueAddRef *window, std::uint32_t message, OpaqueItemHost *entry,
    OpaqueSource *source, std::uint8_t flag) {
  void *spawned = unresolved_005f3b20(name, name, kNeutral, kNeutral, kNeutral,
                                      1U, name, 1U);
  (void)spawned;
  self->field40 = name->field00;
  self->field44 = name->field04;
  self->field48 = name->field08;
  if (name->field00 != kNeutral) {
    self->vtable->slot24(self, name);
  }
  OpaqueAddRef *held = self->field18c;
  if (window != held) {
    if (window != nullptr) {
      window->vtable->retain00(window);
    }
    self->field18c = window;
    if (held != nullptr) {
      held->vtable->release04(held);
    }
  }
  OpaqueViewer *viewer = nullptr;
  std::uint32_t ready = kNeutral;
  if (self->field14 != nullptr) {
    viewer = self->field14;
    ready = unresolved_0093b6c0(viewer);
  } else if (self->field3c != nullptr) {
    viewer = self->field3c;
    ready = unresolved_0080d5f0(viewer);
  } else {
    ready = kNeutral;
  }
  if (ready != kNeutral) {
    unresolved_005f2390(viewer, kNeutral, self->field60, self->field84,
                        self->field88, self->field64);
  }
  self->field190 = message;
  OpaqueItemHost *previous = self->field180;
  if (entry != previous) {
    if (entry != nullptr) {
      entry->vtable->retain04(entry);
    }
    self->field180 = entry;
    if (previous != nullptr) {
      previous->vtable->release08(previous);
    }
  }
  self->field199 = flag;
  OpaqueSource *held_source = self->field17c;
  if (source != held_source) {
    if (source != nullptr) {
      source->vtable->retain04(source);
    }
    self->field17c = source;
    if (held_source != nullptr) {
      held_source->vtable->release08(held_source);
    }
  }
  OpaqueSource *live = self->field17c;
  if (live != nullptr) {
    self->fieldea = live->field30;
    if (live->field1c != kNeutral) {
      self->field174 = live->field1c;
      self->opaque160 = 0U;
    }
    bool usable = false;
    if (live->field10 != nullptr) {
      usable = unresolved_005c6670(entry, live->field10);
    }
    live = self->field17c;
    if (live->field08 != nullptr) {
      usable = usable ||
               live->field08->vtable->slot05(live->field08, &entry->field0c);
    }
    if (entry != nullptr && usable && self->field5c != nullptr) {
      build_window_pair(self);
    }
  }
  unresolved_005f3400(self);
  unresolved_005f3600(self);
  OpaqueApp *app = unresolved_0067dcc0();
  if (app != nullptr) {
    app->vtable->slot24(app, &self->field0c, kNotifyToken);
  }
  (void)unused_word;
}

extern "C" void PKG_AP_THISCALL unresolved_005f49f0(OpaqueViewer *self) {
  if (self->opaque184 != 0) {
    return;
  }
  if (self->field4c == kNeutral && self->field118 == nullptr) {
    return;
  }
  std::uint32_t *selector =
      self->field4c != kNeutral ? &self->field4c : &self->field40;
  OpaqueSource *source = self->field17c;
  if (source != nullptr && source->field08 != nullptr) {
    const std::uint32_t state =
        source->field08->vtable->slot04(source->field08, selector, kNeutral);
    if (state == 2U) {
      if (self->field198 == 0U) {
        return;
      }
      if (self->opaque184 != 0) {
        return;
      }
      unresolved_00435ed0(kLogBusy, unresolved_00435e90());
      return;
    }
    if (state == 3U) {
      unresolved_00435ed0(kLogRetry, unresolved_00435e90());
      return;
    }
    if (state != 1U) {
      return;
    }
  }
  unresolved_005f2fd0(self);
  if (self->field198 != 0 && self->field100 == kModeAttached) {
    OpaquePeer *peer = unresolved_00a206f0();
    const std::uint32_t value =
        peer != nullptr ? peer->vtable->slot20(peer) : kNeutral;
    unresolved_00435ed0(kLogDetach, value);
    unresolved_005f3600(self);
    OpaqueFloatPair pair;
    pair.field00 = 0.0F;
    pair.field04 = 0.0F;
    OpaqueManager *probe = unresolved_0067caa0();
    probe->vtable->slot3c(probe, &pair);
    self->field1c0 = pair.field00;
    self->field1c4 = pair.field04;
    open_windows(self);
    return;
  }
  if (self->field100 == kModeDetached) {
    self->vtable->slot60(self);
  }
}

extern "C" void PKG_AP_THISCALL unresolved_005f4b80(OpaqueViewer *self) {
  OpaqueAddRef *host = unresolved_00804500();
  if (unresolved_006c1100(host)) {
    const std::uint32_t live =
        self != nullptr ? self->vtable->slot0c(self, kHostKey) : kNeutral;
    if (live == unresolved_006c10e0(host)) {
      unresolved_00803bd0(unresolved_00804500(), kNeutral);
    }
  }
  OpaqueAnchor anchor;
  anchor.field00 = kAnchorHead;
  anchor.field04 = kAnchorTail;
  anchor.field08 = kNeutral;
  anchor.field0c = self->field4c;
  anchor.field10 = kNeutral;
  anchor.field14 = self->field50;
  anchor.field18 = self->field54;
  anchor.field1c = self->field190;
  anchor.field20 = kNeutral;
  anchor.field24 = nullptr;
  if (self->field180 != nullptr) {
    OpaqueItemHost *held = self->field180;
    held->vtable->retain04(held);
    anchor.field20 = reinterpret_cast<std::uint32_t>(held);
  }
  OpaqueApp *app = unresolved_0067dcc0();
  app->vtable->slot14(app, anchor.field0c, &anchor, kNeutral);
  OpaqueItemHost *item = self->field60;
  self->opaque169 = 0U;
  const float *frame = item->vtable->slot38(item);
  OpaqueFloatPair half;
  half.field00 = (frame[2] - frame[0]) * g_table_01471064;
  half.field04 = (frame[3] - frame[1]) * g_table_01471064;
  OpaqueFloatPair out;
  out.field00 = 0.0F;
  out.field04 = 0.0F;
  item->vtable->slotc0(item, &out, half.field00, half.field04);
  self->field88 = out.field00;
  self->field84 = out.field04;
  self->field8c = out.field04;
  self->field90 = out.field00;
  if (anchor.field24 != nullptr) {
    anchor.field24->vtable->release04(anchor.field24);
  }
  if (anchor.field20 != kNeutral) {
    OpaqueItemHost *tail = reinterpret_cast<OpaqueItemHost *>(anchor.field20);
    tail->vtable->release08(tail);
  }
}

}
