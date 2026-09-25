#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace openspore::reconstruction::pkg15_editor_support {

using OpaqueObject = void;
using TargetWord = std::uint32_t;

struct OpaquePaletteEditor;
struct OpaquePalettePage;
struct OpaquePaletteApplication;
struct OpaquePaletteEditorState;
struct OpaquePalettePageState;

struct ServiceKey {
  TargetWord first = 0;
  TargetWord second = 0;
  TargetWord third = 0;

  bool operator==(const ServiceKey& other) const {
    return first == other.first && second == other.second &&
           third == other.third;
  }
};

class IEditorService;

struct LayoutBounds {
  float left = 0.0F;
  float top = 0.0F;
  float right = 0.0F;
  float bottom = 0.0F;
};

struct PageMetrics {
  float left = 0.0F;
  float top = 0.0F;
  float right = 0.0F;
  float bottom = 0.0F;
};

struct StandardItemLayout {
  float left = 0.0F;
  float top = 0.0F;
  float right = 0.0F;
  float bottom = 0.0F;
};

struct ModelIdList {
  TargetWord* begin = nullptr;
  TargetWord* end = nullptr;

  std::size_t size() const {
    return begin == nullptr || end == nullptr || end < begin
               ? 0
               : static_cast<std::size_t>(end - begin);
  }
};

struct ClassProbe {
  bool found = false;
  std::uint16_t type = 0;
};

enum class AdvancedKind : std::uint8_t {
  standard,
  token_b4e4f69b,
  token_71fa7d3f,
  token_87e8a1af,
  token_eccc3657,
  automatic,
};

struct AdvancedFactoryRequest {
  AdvancedKind kind = AdvancedKind::standard;
  TargetWord source_token = 0;
  OpaqueObject* template_object = nullptr;
  IEditorService* model = nullptr;
};

class IRefObject {
 public:
  virtual ~IRefObject() = default;
  virtual void add_ref() = 0;
  virtual void release() = 0;
};

class ICategoryRow : public IRefObject {
 public:
  virtual void set_category_visible(TargetWord category,
                                    TargetWord visible) = 0;
};

class IEditorService : public IRefObject {
 public:
  virtual void configure(const ServiceKey& key, OpaqueObject* argument,
                         TargetWord mode, TargetWord source) = 0;
  virtual void initialize(TargetWord value) = 0;
  virtual void set_enabled(TargetWord first, TargetWord second) = 0;
  virtual void set_fade(TargetWord enabled, float duration) = 0;
  virtual void set_layout_bounds(const LayoutBounds& bounds) = 0;
  virtual void select_category(TargetWord index) = 0;
  virtual void set_lighting() = 0;
  virtual void dispatch_104(OpaqueObject* argument) = 0;
  virtual void initialize_application_pair(TargetWord index,
                                           OpaqueObject* argument) = 0;
  virtual void set_category_target(TargetWord target, OpaqueObject* owner,
                                   TargetWord index) = 0;
  virtual LayoutBounds layout_bounds() const = 0;
  virtual void attach_panel(IEditorService* context, TargetWord model_id,
                            TargetWord index, OpaqueObject* owner) = 0;
  virtual ClassProbe inspect_palette_class(TargetWord key) = 0;
};

class IOverlay : public IRefObject {
 public:
  virtual ~IOverlay() = default;
  virtual void set_category_source(OpaqueObject* source) = 0;
  virtual IEditorService* resolve_template() = 0;
  virtual void attach(IEditorService* service) = 0;
  virtual void prepare_fade() = 0;
  virtual IEditorService* tooltip() = 0;
  virtual IEditorService* category_fade() = 0;
};

class IStandardController : public IRefObject {
 public:
  virtual void initialize(OpaqueObject* item, IEditorService* page_service,
                          const StandardItemLayout& layout,
                          OpaqueObject* application_context) = 0;
};

class IAdvancedController : public IRefObject {
 public:
  virtual void initialize(OpaqueObject* item, IEditorService* page_entity,
                          IEditorService* page_service,
                          OpaqueObject* context) = 0;
};

class IPaletteServices {
 public:
  virtual ~IPaletteServices() = default;
  virtual IRefObject* as_ref(OpaqueObject* object) = 0;
  virtual IEditorService* create_service(TargetWord key, TargetWord flags) = 0;
  virtual IEditorService* create_default_service(TargetWord key) = 0;
  virtual IEditorService* query_service(IEditorService* service, TargetWord key,
                                        TargetWord flags) = 0;
  virtual bool key_matches(TargetWord first, TargetWord second,
                           TargetWord third, TargetWord mode,
                           TargetWord source) = 0;
  virtual IRefObject* grow_ref_vector(OpaqueObject* owner,
                                      std::size_t begin_offset,
                                      std::size_t end_offset,
                                      std::size_t capacity_offset,
                                      IRefObject* item) = 0;
  virtual IRefObject* create_palette_controller() = 0;
  virtual IOverlay* create_overlay(OpaqueObject* item, OpaqueObject* owner,
                                   TargetWord index) = 0;
  virtual IStandardController* create_standard_controller() = 0;
  virtual IAdvancedController* create_advanced_controller(
      const AdvancedFactoryRequest& request) = 0;
  virtual IEditorService* create_page_controller() = 0;
  virtual IEditorService* create_query_service() = 0;
  virtual IEditorService* create_panel_service(TargetWord selected_item) = 0;
  virtual IEditorService* create_context_service() = 0;
  virtual IEditorService* create_page_entity(IEditorService* service,
                                             TargetWord key) = 0;
  virtual IEditorService* create_specialized_entity(IEditorService* service,
                                                    TargetWord key) = 0;
  virtual IEditorService* create_palette_model(IEditorService* service) = 0;
  virtual void bind_page_controller(IEditorService* controller,
                                    OpaquePaletteEditor* editor,
                                    TargetWord mode) = 0;
  virtual void apply_base_layout(IEditorService* controller, OpaqueObject* item,
                                 OpaqueObject* owner) = 0;
  virtual void construct_page(OpaquePaletteEditor* editor,
                              OpaqueObject* palette_item,
                              OpaqueObject* application_context) = 0;
  virtual void bind_advanced_application(IEditorService* controller,
                                         OpaqueObject* palette_item,
                                         OpaqueObject* owner) = 0;
  virtual void bind_advanced_controller(
      IEditorService* controller, OpaqueObject* item, IEditorService* palette,
      IEditorService* page_entity, TargetWord model_id, TargetWord page_index,
      TargetWord mode) = 0;
  virtual void bind_layout(IEditorService* layout, IEditorService* controller,
                           OpaqueObject* item, TargetWord selected_model,
                           TargetWord mode) = 0;
  virtual TargetWord selected_model(OpaqueObject* item) = 0;
  virtual bool has_items(OpaqueObject* item) = 0;
  virtual ModelIdList collect_model_ids(IEditorService* service) = 0;
  virtual void free_model_ids(ModelIdList& ids) = 0;
  virtual OpaqueObject* advanced_template(OpaqueObject* page,
                                          TargetWord token) = 0;
  virtual bool is_standard_template(OpaqueObject* object) = 0;
  virtual StandardItemLayout standard_item_layout(OpaquePalettePage* page,
                                                  TargetWord item_index) = 0;
  virtual LayoutBounds advanced_item_layout(OpaquePalettePage* page,
                                            TargetWord item_index) = 0;
  virtual PageMetrics page_metrics() = 0;
  virtual IEditorService* application_system() = 0;
  virtual IEditorService* swatch_manager() = 0;
  virtual void configure_swatch(IEditorService* manager, TargetWord key,
                                IEditorService* palette) = 0;
  virtual void notify_swatch_resource(TargetWord key) = 0;
  virtual void set_swatch_visible(IEditorService* manager,
                                  TargetWord visible) = 0;
  virtual void finish_palette_loop(OpaquePaletteEditorState* state) = 0;
  virtual void transition_category(OpaquePaletteEditorState* state,
                                   TargetWord enabled) = 0;
  virtual void resize_palette(TargetWord category, TargetWord subcategory) = 0;
  virtual void commit_category_selection(OpaquePaletteEditorState* state,
                                         TargetWord enabled) = 0;
  virtual TargetWord toggle_category_mode() = 0;
  virtual TargetWord selected_entry_model(OpaqueObject* entry) = 0;
  virtual TargetWord selected_entry_reachability(TargetWord model) = 0;
  virtual void resize_selected_entry(TargetWord index) = 0;
  virtual bool selected_entry_enabled(OpaquePaletteEditorState* state,
                                      TargetWord index) = 0;
  virtual void set_layout_event(TargetWord key, TargetWord index,
                                float value) = 0;
  virtual void set_category_layout_transaction(TargetWord first_key,
                                               TargetWord second_key,
                                               TargetWord index,
                                               float value) = 0;
};

class RefLifecycleAdapter {
 public:
  explicit RefLifecycleAdapter(IPaletteServices& services)
      : services_(services) {}

  void assign(OpaqueObject* owner, std::size_t offset,
              IRefObject* replacement) {
    auto* old =
        static_cast<IRefObject*>(load_field<OpaqueObject*>(owner, offset));
    if (old == replacement) {
      return;
    }
    if (replacement != nullptr) {
      replacement->add_ref();
    }
    store_field(owner, offset, replacement);
    if (old != nullptr) {
      old->release();
    }
  }

  IRefObject* push(OpaqueObject* owner, std::size_t begin_offset,
                   std::size_t end_offset, std::size_t capacity_offset,
                   IRefObject* item, bool retain_in_capacity = true) {
    const auto end = load_field<TargetWord>(owner, end_offset);
    const auto capacity = load_field<TargetWord>(owner, capacity_offset);
    if (end < capacity) {
      store_field<TargetWord>(
          owner, end_offset, end + static_cast<TargetWord>(sizeof(TargetWord)));
      if (end != 0) {
        store_field<TargetWord>(reinterpret_cast<OpaqueObject*>(end), 0,
                                reinterpret_cast<TargetWord>(item));
        if (retain_in_capacity && item != nullptr) {
          item->add_ref();
        }
      }
      return item;
    }
    return services_.grow_ref_vector(owner, begin_offset, end_offset,
                                     capacity_offset, item);
  }

 private:
  template <typename Value>
  static void store_field(OpaqueObject* owner, std::size_t offset,
                          Value value) {
    __builtin_memcpy(static_cast<unsigned char*>(owner) + offset, &value,
                     sizeof(value));
  }

  template <typename Value>
  static Value load_field(const OpaqueObject* owner, std::size_t offset) {
    Value value{};
    __builtin_memcpy(&value, static_cast<const unsigned char*>(owner) + offset,
                     sizeof(value));
    return value;
  }

  IPaletteServices& services_;
};

IPaletteServices& palette_support_services();

void __thiscall palette_editor_construct_loop_005cb5a0(
    OpaquePaletteEditor*, OpaqueObject* category_source,
    IEditorService* application, TargetWord context_key, OpaqueObject* owner);

void __thiscall palette_select_category_005cb240(OpaquePaletteEditor*,
                                                 TargetWord category);

void __thiscall palette_application_setup_005c53c0(OpaquePaletteEditor*,
                                                   OpaqueObject* palette_item,
                                                   IEditorService* application,
                                                   OpaqueObject* owner);

OpaqueObject* __thiscall palette_page_construct_005c9230(
    OpaquePalettePage*, OpaqueObject* page_definition,
    IEditorService* application, OpaqueObject* application_context,
    TargetWord page_index, TargetWord mode_flag);

}
