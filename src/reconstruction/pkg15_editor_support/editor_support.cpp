#include "editor_support.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <limits>

namespace openspore::reconstruction::pkg15_editor_support {

namespace {

constexpr std::size_t kEditorPageBegin = 0x34;
constexpr std::size_t kEditorPageEnd = 0x38;
constexpr std::size_t kEditorPageCapacity = 0x3c;
constexpr std::size_t kEditorRowBegin = 0x48;
constexpr std::size_t kEditorRowEnd = 0x4c;
constexpr std::size_t kEditorRowCapacity = 0x50;
constexpr std::size_t kEditorSelectedCategory = 0x64;
constexpr std::size_t kEditorSelectionBegin = 0x88;
constexpr std::size_t kEditorSelectionEnd = 0x8c;
constexpr std::size_t kEditorItemBegin = 0xe8;
constexpr std::size_t kEditorItemEnd = 0xec;
constexpr std::size_t kEditorItemCapacity = 0xf0;

template <typename Value>
Value load(OpaqueObject* object, std::size_t offset) {
  Value value{};
  const auto* source = static_cast<unsigned char*>(object) + offset;
  auto* destination = reinterpret_cast<unsigned char*>(&value);
  for (std::size_t index = 0; index < sizeof(value); ++index) {
    destination[index] = source[index];
  }
  return value;
}

template <typename Value>
Value load(const OpaqueObject* object, std::size_t offset) {
  Value value{};
  const auto* source = static_cast<const unsigned char*>(object) + offset;
  auto* destination = reinterpret_cast<unsigned char*>(&value);
  for (std::size_t index = 0; index < sizeof(value); ++index) {
    destination[index] = source[index];
  }
  return value;
}

template <typename Value>
void store(OpaqueObject* object, std::size_t offset, Value value) {
  auto* destination = static_cast<unsigned char*>(object) + offset;
  const auto* source = reinterpret_cast<const unsigned char*>(&value);
  for (std::size_t index = 0; index < sizeof(value); ++index) {
    destination[index] = source[index];
  }
}

std::size_t vector_size(OpaqueObject* object, std::size_t begin_offset,
                        std::size_t end_offset, std::size_t element_size) {
  const auto begin = load<TargetWord>(object, begin_offset);
  const auto end = load<TargetWord>(object, end_offset);
  return end >= begin ? (end - begin) / element_size : 0;
}

OpaqueObject* vector_at(OpaqueObject* object, std::size_t begin_offset,
                        std::size_t index,
                        std::size_t element_size = sizeof(TargetWord)) {
  const auto begin = load<TargetWord>(object, begin_offset);
  return reinterpret_cast<OpaqueObject*>(*reinterpret_cast<const TargetWord*>(
      begin +
      static_cast<TargetWord>(index) * static_cast<TargetWord>(element_size)));
}

ServiceKey service_key(TargetWord first, TargetWord second = 0,
                       TargetWord third = 0) {
  return ServiceKey{first, second, third};
}

AdvancedKind classify_advanced(TargetWord token, bool* recognized) {
  *recognized = true;
  switch (token) {
    case 0x81c74dbcu:
    case 0x0142462au:
    case 0x8bfac054u:
      return AdvancedKind::token_87e8a1af;
    case 0x42bf8c1du:
      return AdvancedKind::token_b4e4f69b;
    case 0x71fa7d3fu:
      return AdvancedKind::token_71fa7d3f;
    case 0x17d37d90u:
    case 0xdee3d8a8u:
    case 0xbd110a25u:
      return AdvancedKind::token_eccc3657;
    default:
      break;
  }
  *recognized = false;
  return AdvancedKind::standard;
}

}
void __thiscall palette_editor_construct_loop_005cb5a0(
    OpaquePaletteEditor* editor, OpaqueObject* category_source,
    IEditorService* application, TargetWord context_key, OpaqueObject* owner) {
  (void)context_key;
  auto& services = palette_support_services();
  RefLifecycleAdapter lifecycle(services);
  auto* state = reinterpret_cast<OpaquePaletteEditorState*>(editor);

  auto* source_ref = services.as_ref(category_source);
  auto* owner_ref = services.as_ref(owner);
  lifecycle.assign(editor, 0x2c, source_ref);
  lifecycle.assign(editor, 0x30, owner_ref);

  auto* common = services.create_service(0x13eb430u, 0);
  lifecycle.assign(editor, 0x0c, common);

  if (services.key_matches(load<TargetWord>(category_source, 0x20), 0x510a95bu,
                           0x40464100u, 1, 0x5b598fau)) {
    common->configure(service_key(load<TargetWord>(category_source, 0x20),
                                  0x510a95bu, 0x40464100u),
                      application, 1, 0x5b598fau);
    auto* default_service = services.create_default_service(0xffffffffu);
    store<IEditorService*>(editor, 0x28, default_service);
    if (default_service != nullptr) {
      default_service->initialize(1);
    }
    auto* palette_service = services.query_service(common, 0x49afe6a1u, 1);
    if (palette_service != nullptr) {
      palette_service->set_enabled(1, 0);
    }
    store<IEditorService*>(editor, 0x20,
                           services.query_service(common, 0xba83c461u, 1));
    store<IEditorService*>(editor, 0x14,
                           services.query_service(common, 0x90d4aadcu, 1));
    store<IEditorService*>(editor, 0x18,
                           services.query_service(common, 0x05aeff7fu, 1));
    store<IEditorService*>(editor, 0x1c,
                           services.query_service(common, 0x72df4ceeu, 1));
    store<IEditorService*>(editor, 0x24,
                           services.query_service(common, 0x93019dbcu, 1));
  }

  for (const TargetWord key : {0x5aec4b8u, 0x5aec4b9u, 0x7bce6e8u}) {
    if (auto* service = services.query_service(common, key, 1);
        service != nullptr) {
      service->dispatch_104(editor);
    }
  }

  const auto category_count =
      vector_size(category_source, 0x0c, 0x10, sizeof(TargetWord));
  for (std::size_t index = 0; index < category_count; ++index) {
    auto* item = vector_at(category_source, 0x0c, index);
    auto* controller = services.create_palette_controller();
    if (controller != nullptr) {
      controller->add_ref();
    }
    auto* application_service = load<IEditorService*>(editor, 0x24);
    palette_application_setup_005c53c0(
        reinterpret_cast<OpaquePaletteEditor*>(controller), item,
        application_service, owner);
    lifecycle.push(editor, kEditorPageBegin, kEditorPageEnd,
                   kEditorPageCapacity, controller);

    const auto* category_panel = load<IEditorService*>(editor, 0x10);
    if (category_panel != nullptr && category_count > 1) {
      auto* overlay =
          services.create_overlay(item, owner, static_cast<TargetWord>(index));
      if (overlay != nullptr) {
        overlay->set_category_source(category_source);
        auto* overlay_template = overlay->resolve_template();
        if (overlay_template != nullptr) {
          overlay_template->dispatch_104(editor);
        }
        auto* tooltip = overlay->tooltip();
        if (tooltip != nullptr) {
          tooltip->add_ref();
        }
        if (overlay_template != nullptr) {
          overlay_template->dispatch_104(tooltip);
        }
        auto* fade = overlay->category_fade();
        if (fade != nullptr) {
          fade->add_ref();
          fade->set_enabled(1, 0);
          fade->set_fade(1, 0.3F);
        }
        if (overlay_template != nullptr) {
          overlay_template->dispatch_104(fade);
        }
        overlay->add_ref();
        lifecycle.push(editor, kEditorRowBegin, kEditorRowEnd,
                       kEditorRowCapacity, overlay);
        overlay->release();
        if (fade != nullptr) {
          fade->release();
        }
        if (tooltip != nullptr) {
          tooltip->release();
        }
      }
    }
    if (controller != nullptr) {
      controller->release();
    }
  }

  services.finish_palette_loop(state);
  store<TargetWord>(editor, 0x60, 0);
  const auto selected = load<TargetWord>(category_source, 0x38);
  palette_select_category_005cb240(
      editor, selected == static_cast<TargetWord>(-1) ? 0 : selected);
  if (load<IRefObject*>(editor, kEditorSelectedCategory) != nullptr) {
    services.transition_category(state, 1);
  }
}

void __thiscall palette_select_category_005cb240(OpaquePaletteEditor* editor,
                                                 TargetWord category) {
  const auto category_count =
      vector_size(editor, 0x34, 0x38, sizeof(TargetWord));
  if (static_cast<std::int32_t>(category) < 0 || category >= category_count) {
    return;
  }

  auto& services = palette_support_services();
  auto* state = reinterpret_cast<OpaquePaletteEditorState*>(editor);
  const auto row_count =
      vector_size(editor, kEditorRowBegin, kEditorRowEnd, sizeof(TargetWord));
  auto* old_category = load<IRefObject*>(editor, kEditorSelectedCategory);
  if (old_category != nullptr) {
    if (row_count != 0) {
      for (std::size_t index = 0; index < category_count; ++index) {
        if (vector_at(editor, kEditorPageBegin, index) == old_category) {
          auto* old_row = vector_at(editor, kEditorRowBegin, index);
          static_cast<ICategoryRow*>(services.as_ref(old_row))
              ->set_category_visible(4, 0);
          break;
        }
      }
    }
    services.transition_category(state, 0);
  }

  auto* selected = vector_at(editor, kEditorPageBegin, category);
  store<IRefObject*>(editor, kEditorSelectedCategory,
                     services.as_ref(selected));
  services.transition_category(state, 1);
  if (row_count != 0) {
    auto* selected_row = vector_at(editor, kEditorRowBegin, category);
    static_cast<ICategoryRow*>(services.as_ref(selected_row))
        ->set_category_visible(4, 1);
    if (auto* service = load<IEditorService*>(editor, 0x20);
        service != nullptr) {
      service->set_lighting();
    }
  }

  services.resize_palette(category, category / 9u);
  services.set_layout_event(0x38eb66f8u, 0, 0.0F);
  services.set_category_layout_transaction(0x1d6253c0u, 0x3597e2dau, 0,
                                           static_cast<float>(category));
  if (auto* application_system = services.application_system();
      application_system != nullptr) {
    application_system->set_category_target(0x44ef2b8u, editor, 0);
  }
  const auto category_mode = services.toggle_category_mode();
  services.set_layout_event(0x6ca71431u, 0, static_cast<float>(category_mode));
  services.commit_category_selection(state, 1);
}

void __thiscall palette_application_setup_005c53c0(OpaquePaletteEditor* editor,
                                                   OpaqueObject* palette_item,
                                                   IEditorService* application,
                                                   OpaqueObject* owner) {
  auto& services = palette_support_services();
  RefLifecycleAdapter lifecycle(services);
  auto* state = reinterpret_cast<OpaquePaletteEditorState*>(editor);

  auto* common = services.create_service(0x13eb430u, 0);
  lifecycle.assign(editor, 0x10, common);

  if (services.key_matches(load<TargetWord>(palette_item, 0x48), 0x510a95bu,
                           0x40464100u, 1, 0x5b598fau)) {
    common->configure(service_key(load<TargetWord>(palette_item, 0x48),
                                  0x510a95bu, 0x40464100u),
                      application, 1, 0x5b598fau);
    auto* default_service = services.create_default_service(0xffffffffu);
    if (default_service != nullptr) {
      default_service->initialize(1);
    }
    lifecycle.assign(editor, 0x18,
                     services.query_service(common, 0x52df67afu, 1));
    lifecycle.assign(editor, 0x1c,
                     services.query_service(common, 0x92df6fd8u, 1));
    lifecycle.assign(editor, 0x20,
                     services.query_service(common, 0x5d122c0u, 1));
    lifecycle.assign(editor, 0x28,
                     services.query_service(common, 0x5d1754bu, 1));
    lifecycle.assign(editor, 0x2c,
                     services.query_service(common, 0x5d17546u, 1));
    lifecycle.assign(editor, 0x24,
                     services.query_service(common, 0x5d3f56bu, 1));
  }

  services.apply_base_layout(common, palette_item, owner);
  lifecycle.assign(editor, 0x6c, services.as_ref(palette_item));
  services.construct_page(editor, palette_item, owner);
  if (common == nullptr) {
    return;
  }

  auto* base_service = services.query_service(common, 0x92df6fd8u, 1);
  if (base_service != nullptr) {
    auto* page_controller = services.create_page_controller();
    lifecycle.assign(editor, 0x70, page_controller);
    if (page_controller != nullptr) {
      services.bind_page_controller(page_controller, editor, 1);
      page_controller->initialize(1);
    }

    const auto selected_model = services.selected_model(palette_item);
    if (auto* layout_resource = services.create_service(0x3304221bu, 1);
        layout_resource != nullptr) {
      auto* layout = services.create_page_controller();
      lifecycle.assign(editor, 0x30, layout);
      if (layout != nullptr) {
        services.bind_layout(layout, layout_resource, palette_item,
                             selected_model, 0);
        layout->initialize(1);
        const auto bounds = layout->layout_bounds();
        store<float>(editor, 0x38, bounds.left);
        store<float>(editor, 0x3c, bounds.top);
        store<float>(editor, 0x40, bounds.right);
        store<float>(editor, 0x44, bounds.bottom);
        store<float>(editor, 0x48, bounds.left);
        store<float>(editor, 0x4c, bounds.top);
        store<float>(editor, 0x50, bounds.right);
        store<float>(editor, 0x54, bounds.bottom);
      }
    }
    if (auto* layout_resource = services.create_service(0x3304221cu, 1);
        layout_resource != nullptr) {
      auto* layout = services.create_page_controller();
      lifecycle.assign(editor, 0x34, layout);
      if (layout != nullptr) {
        services.bind_layout(layout, layout_resource, palette_item,
                             selected_model, 0);
        layout->initialize(1);
        const auto bounds = layout->layout_bounds();
        store<float>(editor, 0x48, bounds.left);
        store<float>(editor, 0x4c, bounds.top);
        store<float>(editor, 0x50, bounds.right);
        store<float>(editor, 0x54, bounds.bottom);
      }
    }
    store<float>(editor, 0x58, load<float>(editor, 0x38));
    store<float>(editor, 0x5c, load<float>(editor, 0x3c));
    store<float>(editor, 0x60, load<float>(editor, 0x40));
    store<float>(editor, 0x64, load<float>(editor, 0x44));
    store<float>(editor, 0x64, load<float>(editor, 0x54));

    auto ids = services.collect_model_ids(common);
    const auto id_count = ids.size();
    for (std::size_t index = 0; index < id_count; ++index) {
      const TargetWord model_id = *ids.begin + index;
      const auto selected_item =
          static_cast<std::int32_t>(load<TargetWord>(palette_item, 0x10) -
                                    load<TargetWord>(palette_item, 0x0c)) > 0
              ? services.selected_model(palette_item)
              : static_cast<TargetWord>(-1);
      auto* panel = services.create_panel_service(selected_item);
      if (panel != nullptr) {
        panel->add_ref();
      }
      auto* context = services.create_context_service();
      if (context != nullptr) {
        context->add_ref();
        context->configure(service_key(0x32f652adu, 0, 0x406a0200u), nullptr, 0,
                           0);
      }
      if (panel != nullptr) {
        panel->attach_panel(context, model_id, 0, owner);
      }
      auto* stored_panel = static_cast<IEditorService*>(
          lifecycle.push(editor, kEditorItemBegin, kEditorItemEnd,
                         kEditorItemCapacity, panel));
      if (stored_panel != panel) {
        if (panel != nullptr) {
          panel->release();
        }
        panel = stored_panel;
      }
      if (context != nullptr) {
        context->release();
      }
      if (panel != nullptr) {
        panel->release();
      }
    }
    services.free_model_ids(ids);

    if (auto* swatch_resource = services.create_service(0x530c27bcu, 1);
        swatch_resource != nullptr) {
      auto* swatch = services.swatch_manager();
      lifecycle.assign(editor, 0x68, swatch);
      if (swatch != nullptr) {
        services.configure_swatch(swatch, 0xef4519ffu, swatch_resource);
        services.notify_swatch_resource(0x2d03ced2u);
        services.set_swatch_visible(swatch, 0);
      }
    }

    auto* application_system = services.application_system();
    store<IEditorService*>(editor, 0xb4, application_system);
    store<OpaquePaletteEditor*>(editor, 0xb8, editor);
    store<OpaqueObject*>(editor, 0xbc,
                         reinterpret_cast<OpaqueObject*>(0x013f7f6cu));
    store<TargetWord>(editor, 0xc0, 2);
    store<TargetWord>(editor, 0xc4, 0);
    if (application_system != nullptr) {
      application_system->initialize_application_pair(
          0, load<OpaqueObject*>(editor, 0xbc));
      application_system->initialize_application_pair(
          1, load<OpaqueObject*>(editor, 0xbc));
    }

    if (auto* advanced_resource = services.create_service(0x1357f0c2u, 1);
        advanced_resource != nullptr && services.has_items(palette_item)) {
      auto* advanced_application = services.create_page_controller();
      lifecycle.assign(editor, 0x9c, advanced_application);
      if (advanced_application != nullptr) {
        services.bind_advanced_application(advanced_application, palette_item,
                                           owner);
        advanced_application->initialize(1);
      }
    }
  }

  const auto selection_count =
      vector_size(editor, kEditorSelectionBegin, kEditorSelectionEnd, 8);
  if (selection_count != 0) {
    const auto current = load<TargetWord>(editor, 0xa0);
    auto* entry = vector_at(editor, kEditorSelectionBegin, current, 8);
    const auto model = services.selected_entry_model(entry);
    const auto reachable = services.selected_entry_reachability(model);
    services.resize_selected_entry(reachable / load<TargetWord>(editor, 0xb0));
    if (static_cast<std::int32_t>(current) >= 0 && current < selection_count &&
        services.selected_entry_enabled(state, current)) {
      store<TargetWord>(editor, 0xa0, current);
    }
  }

  if (auto* service = load<IEditorService*>(editor, 0x18); service != nullptr) {
    service->set_enabled(1, 0);
  }
  if (auto* swatch = load<IEditorService*>(editor, 0x68); swatch != nullptr) {
    services.set_swatch_visible(swatch, 0);
  }
  if (auto* service = load<IEditorService*>(editor, 0x20); service != nullptr) {
    service->set_enabled(1, 0);
  }
}

OpaqueObject* __thiscall palette_page_construct_005c9230(
    OpaquePalettePage* page, OpaqueObject* page_definition,
    IEditorService* application, OpaqueObject* application_context,
    TargetWord page_index, TargetWord mode_flag) {
  auto& services = palette_support_services();
  RefLifecycleAdapter lifecycle(services);

  lifecycle.assign(page, 0x14, services.as_ref(page_definition));
  if (application_context == nullptr ||
      load<float>(application_context, 0x28) == -1.0F) {
    const auto metrics = services.page_metrics();
    store<float>(page, 0x18, (metrics.right - metrics.left) * 0.00125F);
    store<float>(page, 0x1c, (metrics.bottom - metrics.top) * 0.0016666667F);
  } else {
    store<float>(page, 0x18, load<float>(application_context, 0x24));
    store<float>(page, 0x1c, load<float>(application_context, 0x28));
  }

  auto* service = services.create_service(0x13eb430u, 0);
  lifecycle.assign(page, 0x0c, service);
  if (!services.key_matches(load<TargetWord>(page_definition, 0x0c), 0x510a95bu,
                            0x40464100u, 1, 0x5b598fau)) {
    return nullptr;
  }

  service->configure(service_key(load<TargetWord>(page_definition, 0x0c),
                                 0x510a95bu, 0x40464100u),
                     application, 1, 0x5b598fau);
  auto* default_service = services.create_default_service(0xffffffffu);
  if (default_service != nullptr) {
    default_service->initialize(1);
  }
  auto* page_service = services.query_service(service, 0x12df7465u, 1);
  store<IEditorService*>(page, 0x10, page_service);

  const auto item_count =
      vector_size(page_definition, 0x70, 0x74, sizeof(TargetWord));
  for (std::size_t index = 0; index < item_count; ++index) {
    auto* item = vector_at(page_definition, 0x70, index);
    if (item == nullptr) {
      continue;
    }

    auto* automatic_template = static_cast<OpaqueObject*>(nullptr);
    auto* query = services.create_query_service();
    if (query != nullptr && load<TargetWord>(page_definition, 0x10) == 0) {
      const auto probe = query->inspect_palette_class(0x811c9dc5u);
      if (probe.found && probe.type == 10) {
        automatic_template = services.advanced_template(page_definition, 0);
      }
    }

    const auto source_token = load<TargetWord>(item, 0x24);
    bool token_known = false;
    auto advanced_kind = classify_advanced(source_token, &token_known);
    const bool advanced_branch = automatic_template != nullptr || token_known;

    if (!advanced_branch) {
      auto* controller = services.create_standard_controller();
      if (controller != nullptr) {
        controller->add_ref();
        const auto layout =
            services.standard_item_layout(page, static_cast<TargetWord>(index));
        controller->initialize(item, page_service, layout, application_context);
        lifecycle.push(page, 0x24, 0x28, 0x2c, controller);
        controller->release();
      }
    } else if (advanced_branch) {
      IAdvancedController* advanced = nullptr;
      if (automatic_template != nullptr) {
        AdvancedFactoryRequest request;
        request.kind = AdvancedKind::automatic;
        request.template_object = automatic_template;
        advanced = services.create_advanced_controller(request);
      } else if (token_known) {
        AdvancedFactoryRequest request;
        request.kind = advanced_kind;
        request.source_token = source_token;
        request.template_object =
            advanced_kind == AdvancedKind::token_eccc3657
                ? load<OpaqueObject*>(page_definition, 0x60)
                : nullptr;
        advanced = services.create_advanced_controller(request);
      }
      if (advanced != nullptr) {
        if (auto* entity = services.create_page_entity(page_service, 0);
            entity != nullptr) {
          entity->set_layout_bounds(services.advanced_item_layout(
              page, static_cast<TargetWord>(index)));
          advanced->initialize(item, entity, page_service, application_context);
          lifecycle.push(page, 0x34, 0x38, 0x3c, advanced);
        }
        advanced->release();
      }
    }
  }

  if (page_service != nullptr) {
    page_service->set_enabled(1, 0);
  }
  (void)page_index;
  (void)mode_flag;
  return nullptr;
}

}