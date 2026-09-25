#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <deque>
#include <string>
#include <utility>
#include <vector>

#include "editor_support.hpp"

namespace openspore::reconstruction::pkg15_editor_support {

struct RawObject : IRefObject {
  void add_ref() override {}
  void release() override {}

  std::array<std::uint8_t, 0x200> storage{};
};

struct OpaquePaletteEditor : RawObject {};
struct OpaquePalettePage : RawObject {};
struct OpaquePaletteApplication : RawObject {};
struct OpaquePaletteEditorState : RawObject {};
struct OpaquePalettePageState : RawObject {};

namespace {

struct Event {
  std::string name;
  TargetWord first = 0;
  TargetWord second = 0;
  float value = 0.0F;
  OpaqueObject* object = nullptr;
  OpaqueObject* context = nullptr;
  LayoutBounds layout{};
};

class MockServices;

void record_event(MockServices* services, std::string name,
                  TargetWord first = 0, TargetWord second = 0,
                  float value = 0.0F, OpaqueObject* object = nullptr);
void record_layout_event(MockServices* services, std::string name,
                         const LayoutBounds& layout);

class MockController : public IRefObject {
 public:
  explicit MockController(MockServices& services) : services_(&services) {}

  void add_ref() override { record_event(services_, "add_ref:controller"); }
  void release() override { record_event(services_, "release:controller"); }

  std::array<std::uint8_t, 0x200> storage{};

 private:
  MockServices* services_;
};

class MockService : public IEditorService {
 public:
  MockService(MockServices& services, std::string name)
      : services_(&services), name_(std::move(name)) {}

  const std::string& name() const { return name_; }

  void add_ref() override { record_event(services_, "add_ref:" + name_); }
  void release() override { record_event(services_, "release:" + name_); }

  void configure(const ServiceKey& key, OpaqueObject* argument, TargetWord mode,
                 TargetWord source) override {
    record_event(services_, "configure:" + name_, key.first, mode, 0.0F,
                 argument);
    assert(source == 0x5b598fau || source == 0);
  }

  void initialize(TargetWord value) override {
    record_event(services_, "initialize:" + name_, value);
  }

  void set_enabled(TargetWord first, TargetWord second) override {
    record_event(services_, "enabled:" + name_, first, second);
  }

  void set_fade(TargetWord enabled, float duration) override {
    record_event(services_, "fade:" + name_, enabled, 0, duration);
  }

  void set_layout_bounds(const LayoutBounds& bounds) override {
    record_layout_event(services_, "bounds:" + name_, bounds);
  }

  void select_category(TargetWord index) override {
    record_event(services_, "select_category:" + name_, index);
  }

  void set_lighting() override { record_event(services_, "lighting:" + name_); }

  void dispatch_104(OpaqueObject*) override {
    record_event(services_, "dispatch104:" + name_);
  }

  void initialize_application_pair(TargetWord index, OpaqueObject*) override {
    record_event(services_, "app_pair:" + name_, index);
  }

  void set_category_target(TargetWord target, OpaqueObject* owner,
                           TargetWord index) override {
    record_event(services_, "category_target:" + name_, target, index, 0.0F,
                 owner);
  }

  LayoutBounds layout_bounds() const override { return bounds_; }

  void attach_panel(IEditorService* context, TargetWord model_id,
                    TargetWord index, OpaqueObject* owner) override {
    assert(context != nullptr);
    record_event(services_, "attach_panel:" + name_, model_id, index, 0.0F,
                 owner);
  }

  ClassProbe inspect_palette_class(TargetWord key) override {
    record_event(services_, "inspect_class:" + name_, key);
    return probe_;
  }

  LayoutBounds bounds_{1.0F, 2.0F, 3.0F, 4.0F};
  ClassProbe probe_{};
  MockServices* services_;
  std::string name_;
};

class MockCategoryRow : public ICategoryRow {
 public:
  MockCategoryRow(MockServices& services, std::string name)
      : services_(&services), name_(std::move(name)) {}

  void add_ref() override { record_event(services_, "add_ref:" + name_); }
  void release() override { record_event(services_, "release:" + name_); }

  void set_category_visible(TargetWord category, TargetWord visible) override {
    record_event(services_, "row:" + name_, category, visible);
  }

  std::array<std::uint8_t, 0x200> storage{};

 private:
  MockServices* services_;
  std::string name_;
};

class MockOverlay : public IOverlay {
 public:
  MockOverlay(MockServices& services, MockService* template_service,
              MockService* tooltip, MockService* fade)
      : services_(&services),
        template_service_(template_service),
        tooltip_(tooltip),
        fade_(fade) {}

  void add_ref() override { record_event(services_, "add_ref:overlay"); }
  void release() override { record_event(services_, "release:overlay"); }
  void set_category_source(OpaqueObject*) override {
    record_event(services_, "overlay_category");
  }
  IEditorService* resolve_template() override { return template_service_; }
  void attach(IEditorService* service) override {
    record_event(services_, std::string("overlay_attach:") +
                                (service == tooltip_ ? "tooltip" : "fade"));
  }
  void prepare_fade() override {
    record_event(services_, "overlay_prepare_fade");
  }
  IEditorService* tooltip() override { return tooltip_; }
  IEditorService* category_fade() override { return fade_; }

 private:
  MockServices* services_;
  MockService* template_service_;
  MockService* tooltip_;
  MockService* fade_;
};

class MockStandardController : public IStandardController {
 public:
  explicit MockStandardController(MockServices& services)
      : services_(&services) {}

  void add_ref() override { record_event(services_, "add_ref:standard"); }
  void release() override { record_event(services_, "release:standard"); }
  void initialize(OpaqueObject*, IEditorService*,
                  const StandardItemLayout& layout,
                  OpaqueObject* application_context) override {
    record_event(services_, "standard_init", 0, 0, layout.left,
                 application_context);
  }

 private:
  MockServices* services_;
};

class MockAdvancedController : public IAdvancedController {
 public:
  explicit MockAdvancedController(MockServices& services)
      : services_(&services) {}

  void add_ref() override { record_event(services_, "add_ref:advanced"); }
  void release() override { record_event(services_, "release:advanced"); }
  void initialize(OpaqueObject*, IEditorService*, IEditorService*,
                  OpaqueObject*) override {
    record_event(services_, "advanced_init");
  }

 private:
  MockServices* services_;
};

class MockServices final : public IPaletteServices {
 public:
  IRefObject* as_ref(OpaqueObject* object) override {
    return static_cast<IRefObject*>(object);
  }

  IEditorService* create_service(TargetWord key, TargetWord flags) override {
    record("create_service", key, flags);
    return pop(service_queue, "service");
  }

  IEditorService* create_default_service(TargetWord key) override {
    record("create_default", key);
    return pop(default_queue, "default");
  }

  IEditorService* query_service(IEditorService*, TargetWord key,
                                TargetWord flags) override {
    record("query_service", key, flags);
    return pop(query_queue, "query");
  }

  bool key_matches(TargetWord, TargetWord, TargetWord, TargetWord,
                   TargetWord) override {
    return key_match;
  }

  IRefObject* grow_ref_vector(OpaqueObject* owner, std::size_t begin_offset,
                              std::size_t end_offset,
                              std::size_t capacity_offset,
                              IRefObject* item) override {
    record("grow_vector");
    const auto begin = load<TargetWord>(owner, begin_offset);
    const auto end = load<TargetWord>(owner, end_offset);
    const auto count =
        end == 0 ? 0
                 : static_cast<std::size_t>(end - begin) / sizeof(TargetWord);
    auto* grown = new TargetWord[count + 4];
    for (std::size_t index = 0; index < count; ++index) {
      grown[index] = load<TargetWord>(
          reinterpret_cast<OpaqueObject*>(
              begin + static_cast<TargetWord>(index) * sizeof(TargetWord)),
          0);
    }
    grown[count] = reinterpret_cast<TargetWord>(item);
    if (item != nullptr) {
      item->add_ref();
    }
    store(begin_offset, owner, reinterpret_cast<TargetWord>(grown));
    store(end_offset, owner, reinterpret_cast<TargetWord>(grown + count + 1));
    store(capacity_offset, owner,
          reinterpret_cast<TargetWord>(grown + count + 4));
    return item;
  }

  IRefObject* create_palette_controller() override {
    record("create_palette_controller");
    if (!controller_queue.empty()) {
      auto* result = controller_queue.front();
      controller_queue.pop_front();
      return result;
    }
    return new MockController(*this);
  }

  IOverlay* create_overlay(OpaqueObject*, OpaqueObject* owner,
                           TargetWord index) override {
    record("create_overlay", index, 0, 0.0F, owner);
    if (overlay_queue.empty()) {
      return nullptr;
    }
    auto* result = overlay_queue.front();
    overlay_queue.pop_front();
    return result;
  }

  IStandardController* create_standard_controller() override {
    record("create_standard");
    return new_standard();
  }

  IAdvancedController* create_advanced_controller(
      const AdvancedFactoryRequest& request) override {
    record("create_advanced", static_cast<TargetWord>(request.kind),
           request.source_token);
    return new_advanced();
  }

  IEditorService* create_page_controller() override {
    record("create_page_controller");
    return pop(page_controller_queue, "page_controller");
  }

  IEditorService* create_query_service() override {
    record("create_query_service");
    return new_service("query_service");
  }

  IEditorService* create_panel_service(TargetWord selected_item) override {
    record("create_panel", selected_item);
    return new_service("panel");
  }

  IEditorService* create_context_service() override {
    record("create_context");
    return new_service("context");
  }

  IEditorService* create_page_entity(IEditorService*, TargetWord key) override {
    record("create_page_entity", key);
    return new_service("page_entity");
  }

  IEditorService* create_specialized_entity(IEditorService*,
                                            TargetWord key) override {
    record("create_specialized", key);
    return new_service("specialized");
  }

  IEditorService* create_palette_model(IEditorService*) override {
    record("create_palette_model");
    return new_service("palette_model");
  }

  void bind_page_controller(IEditorService* controller, OpaquePaletteEditor*,
                            TargetWord mode) override {
    assert(controller != nullptr);
    record("bind_page_controller", mode);
  }

  void apply_base_layout(IEditorService*, OpaqueObject*,
                         OpaqueObject* owner) override {
    record("apply_base_layout", 0, 0, 0.0F, owner);
  }

  void construct_page(OpaquePaletteEditor* editor, OpaqueObject*,
                      OpaqueObject* application_context) override {
    record("construct_page", 0, 0, 0.0F, editor);
    events.back().context = application_context;
  }

  void bind_advanced_application(IEditorService*, OpaqueObject* palette_item,
                                 OpaqueObject* owner) override {
    record("bind_advanced_application", 0, 0, 0.0F, palette_item);
    assert(owner != nullptr);
  }

  void bind_advanced_controller(IEditorService*, OpaqueObject*, IEditorService*,
                                IEditorService*, TargetWord, TargetWord,
                                TargetWord mode) override {
    record("bind_advanced_controller", mode);
  }

  void bind_layout(IEditorService*, IEditorService*, OpaqueObject*,
                   TargetWord selected_model, TargetWord mode) override {
    record("bind_layout", selected_model, mode);
  }

  TargetWord selected_model(OpaqueObject*) override { return 0x33u; }

  bool has_items(OpaqueObject*) override { return has_items_value; }

  ModelIdList collect_model_ids(IEditorService*) override {
    record("collect_model_ids", static_cast<TargetWord>(model_ids.size()));
    if (model_ids.empty()) {
      return {};
    }
    auto* storage = new TargetWord[model_ids.size()];
    std::copy(model_ids.begin(), model_ids.end(), storage);
    return {storage, storage + model_ids.size()};
  }

  void free_model_ids(ModelIdList& ids) override {
    record("free_model_ids", static_cast<TargetWord>(ids.size()));
    delete[] ids.begin;
    ids = {};
  }

  OpaqueObject* advanced_template(OpaqueObject*, TargetWord token) override {
    record("advanced_template", token);
    return template_enabled ? reinterpret_cast<OpaqueObject*>(this) : nullptr;
  }

  bool is_standard_template(OpaqueObject*) override { return true; }

  StandardItemLayout standard_item_layout(OpaquePalettePage*,
                                          TargetWord index) override {
    record("standard_item_layout", index);
    return {static_cast<float>(index) + 10.0F, 2.0F, 3.0F, 4.0F};
  }

  LayoutBounds advanced_item_layout(OpaquePalettePage*,
                                    TargetWord index) override {
    record("advanced_item_layout", index);
    return {static_cast<float>(index) + 100.0F, 2.0F, 3.0F, 4.0F};
  }

  PageMetrics page_metrics() override {
    record("page_metrics");
    return {0.0F, 10.0F, 800.0F, 610.0F};
  }

  IEditorService* application_system() override { return app_system; }

  IEditorService* swatch_manager() override { return swatch; }

  void configure_swatch(IEditorService*, TargetWord key,
                        IEditorService*) override {
    record("configure_swatch", key);
  }

  void notify_swatch_resource(TargetWord key) override {
    record("notify_swatch", key);
  }

  void set_swatch_visible(IEditorService*, TargetWord visible) override {
    record("swatch_visible", visible);
  }

  void finish_palette_loop(OpaquePaletteEditorState*) override {
    record("finish_palette_loop");
  }

  void transition_category(OpaquePaletteEditorState*,
                           TargetWord enabled) override {
    record("transition", enabled);
  }

  void resize_palette(TargetWord category, TargetWord subcategory) override {
    record("resize", category, subcategory);
  }

  void commit_category_selection(OpaquePaletteEditorState*,
                                 TargetWord enabled) override {
    record("commit_category", enabled);
  }

  TargetWord toggle_category_mode() override {
    category_mode = category_mode == 0 ? 1 : 0;
    record("toggle_category_mode", category_mode);
    return category_mode;
  }

  TargetWord selected_entry_model(OpaqueObject* entry) override {
    record("selected_entry_model", 0, 0, 0.0F, entry);
    return 0x44u;
  }

  TargetWord selected_entry_reachability(TargetWord model) override {
    record("entry_reachability", model);
    return 2;
  }

  void resize_selected_entry(TargetWord index) override {
    record("resize_entry", index);
  }

  bool selected_entry_enabled(OpaquePaletteEditorState*,
                              TargetWord index) override {
    record("entry_enabled", index);
    return true;
  }

  void set_layout_event(TargetWord key, TargetWord index,
                        float value) override {
    record("layout_event", key, index, value);
  }

  void set_category_layout_transaction(TargetWord first_key,
                                       TargetWord second_key, TargetWord index,
                                       float value) override {
    (void)index;
    record("category_layout_transaction", first_key, second_key, value);
  }

  void record(std::string name, TargetWord first = 0, TargetWord second = 0,
              float value = 0.0F, OpaqueObject* object = nullptr) {
    events.push_back({std::move(name), first, second, value, object});
  }

  bool contains(const std::string& value) const {
    for (const auto& event : events) {
      if (event.name == value) {
        return true;
      }
    }
    return false;
  }

  std::size_t count(const std::string& value) const {
    std::size_t result = 0;
    for (const auto& event : events) {
      result += event.name == value ? 1 : 0;
    }
    return result;
  }

  std::size_t last(const std::string& value) const {
    std::size_t result = 0;
    bool found = false;
    for (std::size_t index = 0; index < events.size(); ++index) {
      if (events[index].name == value) {
        result = index;
        found = true;
      }
    }
    assert(found);
    return result;
  }

  template <typename T>
  static T load(OpaqueObject* object, std::size_t offset) {
    T value{};
    std::memcpy(&value, static_cast<unsigned char*>(object) + offset,
                sizeof(value));
    return value;
  }

  template <typename T>
  static void store(std::size_t offset, OpaqueObject* object, T value) {
    std::memcpy(static_cast<unsigned char*>(object) + offset, &value,
                sizeof(value));
  }

  MockService* new_service(const std::string& name) {
    return new MockService(*this, name);
  }

  MockStandardController* new_standard() {
    if (!standard_queue.empty()) {
      auto* result = standard_queue.front();
      standard_queue.pop_front();
      return result;
    }
    return new MockStandardController(*this);
  }

  MockAdvancedController* new_advanced() {
    if (!advanced_queue.empty()) {
      auto* result = advanced_queue.front();
      advanced_queue.pop_front();
      return result;
    }
    return new MockAdvancedController(*this);
  }

  template <typename Queue>
  MockService* pop(Queue& queue, const std::string& fallback) {
    if (!queue.empty()) {
      auto* result = queue.front();
      queue.pop_front();
      return result;
    }
    return new MockService(*this, fallback);
  }

  std::vector<Event> events;
  std::deque<MockService*> service_queue;
  std::deque<MockService*> default_queue;
  std::deque<MockService*> query_queue;
  std::deque<MockService*> page_controller_queue;
  std::deque<IRefObject*> controller_queue;
  std::deque<MockOverlay*> overlay_queue;
  std::deque<MockStandardController*> standard_queue;
  std::deque<MockAdvancedController*> advanced_queue;
  std::vector<TargetWord> model_ids;
  MockService* app_system = nullptr;
  MockService* swatch = nullptr;
  bool key_match = true;
  bool has_items_value = false;
  bool template_enabled = false;
  TargetWord category_mode = 0;
};

void record_event(MockServices* services, std::string name, TargetWord first,
                  TargetWord second, float value, OpaqueObject* object) {
  services->record(std::move(name), first, second, value, object);
}

void record_layout_event(MockServices* services, std::string name,
                         const LayoutBounds& layout) {
  services->record(std::move(name), 0, 0, layout.left);
  services->events.back().layout = layout;
}

MockServices services;

template <typename T>
T load(OpaqueObject* object, std::size_t offset) {
  return MockServices::load<T>(object, offset);
}

template <typename T>
void store(OpaqueObject* object, std::size_t offset, T value) {
  MockServices::store(offset, object, value);
}

void set_vector(OpaqueObject* object, std::size_t begin_offset,
                std::size_t end_offset, std::size_t capacity_offset,
                OpaqueObject* const* values, std::size_t count,
                std::size_t capacity) {
  store<TargetWord>(object, begin_offset, reinterpret_cast<TargetWord>(values));
  store<TargetWord>(object, end_offset,
                    reinterpret_cast<TargetWord>(values + count));
  store<TargetWord>(object, capacity_offset,
                    reinterpret_cast<TargetWord>(values + capacity));
}

void reset_services() {
  services.events.clear();
  services.service_queue.clear();
  services.default_queue.clear();
  services.query_queue.clear();
  services.page_controller_queue.clear();
  services.controller_queue.clear();
  services.overlay_queue.clear();
  services.standard_queue.clear();
  services.advanced_queue.clear();
  services.model_ids.clear();
  services.app_system = new MockService(services, "application_system");
  services.swatch = new MockService(services, "swatch");
  services.key_match = true;
  services.has_items_value = false;
  services.template_enabled = false;
  services.category_mode = 0;
}

void test_category_validation_and_selection() {
  reset_services();
  OpaquePaletteEditor editor;
  RawObject categories[2];
  std::array<OpaqueObject*, 2> category_pointers{&categories[0],
                                                 &categories[1]};
  set_vector(&editor, 0x34, 0x38, 0x3c, category_pointers.data(), 2, 2);

  palette_select_category_005cb240(&editor, 2);
  assert(services.events.empty());

  palette_select_category_005cb240(&editor, 1);
  assert(services.count("transition") == 1);
  assert(services.events[0].name == "transition" &&
         services.events[0].first == 1);
  assert(services.contains("resize"));
  assert(services.contains("commit_category"));
  assert(load<IRefObject*>(&editor, 0x64) ==
         static_cast<IRefObject*>(category_pointers[1]));

  reset_services();
  OpaquePaletteEditor row_editor;
  auto* row0 = new MockCategoryRow(services, "row0");
  auto* row1 = new MockCategoryRow(services, "row1");
  OpaqueObject* row_values[2] = {row0, row1};
  set_vector(&row_editor, 0x34, 0x38, 0x3c, row_values, 2, 2);
  set_vector(&row_editor, 0x48, 0x4c, 0x50, row_values, 2, 2);
  store<IRefObject*>(&row_editor, 0x64, row0);
  auto* lighting = new MockService(services, "lighting");
  store<IEditorService*>(&row_editor, 0x20, lighting);

  palette_select_category_005cb240(&row_editor, 1);
  assert(services.events[0].name == "row:row0" &&
         services.events[0].first == 4 && services.events[0].second == 0);
  assert(services.events[1].name == "transition" &&
         services.events[1].first == 0);
  assert(services.events[2].name == "transition" &&
         services.events[2].first == 1);
  assert(services.events[3].name == "row:row1" &&
         services.events[3].first == 4 && services.events[3].second == 1);
  assert(services.events[4].name == "lighting:lighting");
  assert(load<IRefObject*>(&row_editor, 0x64) == row1);
  assert(services.contains("category_target:application_system"));
  assert(services.contains("toggle_category_mode"));
  const auto mode_event = services.last("layout_event");
  assert(services.events[mode_event].first == 0x6ca71431u);
  assert(services.events[mode_event].value == 1.0F);
  assert(services.last("category_target:application_system") <
         services.last("toggle_category_mode"));
  assert(services.last("toggle_category_mode") <
         services.last("commit_category"));
  assert(services.count("layout_event") == 2);
  assert(services.count("category_layout_transaction") == 1);
  const auto transaction = services.last("category_layout_transaction");
  assert(services.events[transaction].first == 0x1d6253c0u);
  assert(services.events[transaction].second == 0x3597e2dau);
  assert(services.events[transaction].value == 1.0F);
}

void test_palette_setup_selection_and_teardown() {
  reset_services();
  OpaquePaletteEditor editor;
  auto* palette_item = new MockCategoryRow(services, "palette_item");
  auto* owner = new MockCategoryRow(services, "owner");
  auto* application_service = new MockService(services, "application");
  auto* common = new MockService(services, "common");
  auto* assigned = new MockService(services, "assigned");
  auto* base = new MockService(services, "base");
  auto* page = new MockService(services, "page");
  auto* layout1 = new MockService(services, "layout1");
  auto* layout2 = new MockService(services, "layout2");
  layout2->bounds_ = {5.0F, 6.0F, 7.0F, 8.0F};
  services.service_queue = {common, layout1, layout2, services.swatch, nullptr};
  services.query_queue = {assigned, base};
  services.default_queue = {new MockService(services, "default")};
  services.page_controller_queue = {page, layout1, layout2};
  services.model_ids = {0x44u, 0x45u};

  store<TargetWord>(&palette_item, 0x48, 0x1234u);
  OpaqueObject* palette_vectors[1] = {&palette_item};
  store(&palette_item, 0x0c, static_cast<OpaqueObject*>(palette_vectors));
  store(&palette_item, 0x10, static_cast<OpaqueObject*>(palette_vectors + 1));
  std::array<std::uint8_t, 16> selections{};
  store(&editor, 0x88, static_cast<OpaqueObject*>(selections.data()));
  store(&editor, 0x8c, static_cast<OpaqueObject*>(selections.data() + 8));
  store<TargetWord>(&editor, 0xa0, 0);
  store<TargetWord>(&editor, 0xb0, 3);

  palette_application_setup_005c53c0(&editor, palette_item, application_service,
                                     owner);
  assert(services.count("apply_base_layout") == 1);
  assert(services.events[services.last("apply_base_layout")].object == owner);
  assert(services.count("construct_page") == 1);
  const auto construct_page = services.last("construct_page");
  assert(services.events[construct_page].object == &editor);
  assert(services.events[construct_page].context == owner);
  assert(load<OpaqueObject*>(&editor, 0x6c) == palette_item);
  assert(services.count("create_panel") == 2);
  assert(services.count("free_model_ids") == 1);
  assert(services.count("selected_entry_model") == 1);
  assert(services.count("entry_reachability") == 1);
  assert(services.count("resize_entry") == 1);
  assert(!services.contains("select_current"));
  assert(!services.contains("select_entry"));
  assert(services.last("selected_entry_model") <
         services.last("entry_reachability"));
  assert(services.last("entry_reachability") < services.last("resize_entry"));
  assert(load<TargetWord>(&editor, 0xa0) == 0);
  assert(load<float>(&editor, 0x38) == 1.0F);
  assert(load<float>(&editor, 0x5c) == 2.0F);
  assert(load<float>(&editor, 0x60) == 3.0F);
  assert(load<float>(&editor, 0x64) == 8.0F);
  const auto item_end = load<TargetWord>(&editor, 0xec);
  const auto item_begin = load<TargetWord>(&editor, 0xe8);
  assert((item_end - item_begin) / sizeof(TargetWord) == 2);
  assert(services.count("add_ref:assigned") == 1);
  assert(services.count("release:assigned") == 0);
  assert(services.count("add_ref:base") == 1);
  assert(services.count("release:base") == 0);
  const auto swatch_hide = services.last("swatch_visible");
  const auto final_enabled = services.last("enabled:query");
  assert(swatch_hide < final_enabled);
}

void test_keyed_service_replacement_lifecycle() {
  reset_services();
  OpaquePaletteEditor editor;
  RawObject palette_item;
  RawObject owner;
  auto* common = new MockService(services, "common");
  auto* replacement_52 = new MockService(services, "keyed_52");
  auto* replacement_92 = new MockService(services, "keyed_92");
  auto* replacement_5d122 = new MockService(services, "keyed_5d122");
  auto* replacement_5d1754b = new MockService(services, "keyed_5d1754b");
  auto* replacement_5d17546 = new MockService(services, "keyed_5d17546");
  auto* replacement_5d3f56b = new MockService(services, "keyed_5d3f56b");
  auto* base_service = new MockService(services, "base_service");
  auto* old_52 = new MockService(services, "old_52");
  auto* old_92 = new MockService(services, "old_92");
  auto* old_5d122 = new MockService(services, "old_5d122");
  auto* old_5d1754b = new MockService(services, "old_5d1754b");
  auto* old_5d17546 = new MockService(services, "old_5d17546");
  auto* old_5d3f56b = new MockService(services, "old_5d3f56b");
  services.service_queue = {common};
  services.query_queue = {replacement_52,      replacement_92,
                          replacement_5d122,   replacement_5d1754b,
                          replacement_5d17546, replacement_5d3f56b,
                          base_service};
  const std::array<std::size_t, 6> offsets{0x18, 0x1c, 0x20, 0x28, 0x2c, 0x24};
  const std::array<MockService*, 6> old_services{
      old_52, old_92, old_5d122, old_5d1754b, old_5d17546, old_5d3f56b};
  const std::array<MockService*, 6> replacements{
      replacement_52,      replacement_92,      replacement_5d122,
      replacement_5d1754b, replacement_5d17546, replacement_5d3f56b};
  for (std::size_t index = 0; index < offsets.size(); ++index) {
    store(&editor, offsets[index], old_services[index]);
  }
  store<TargetWord>(&palette_item, 0x48, 0x1234u);

  palette_application_setup_005c53c0(
      &editor, &palette_item, new MockService(services, "application"), &owner);

  for (std::size_t index = 0; index < offsets.size(); ++index) {
    assert(load<IEditorService*>(&editor, offsets[index]) ==
           replacements[index]);
    assert(services.count("add_ref:" +
                          std::string(replacements[index]->name())) == 1);
    assert(services.count("release:" +
                          std::string(old_services[index]->name())) == 1);
  }
}

void test_page_standard_and_advanced_branches() {
  reset_services();
  OpaquePalettePage page;
  RawObject application_context;
  RawObject page_definition;
  RawObject standard_item;
  RawObject advanced_item;
  RawObject distinct_item;
  auto* common = new MockService(services, "page_common");
  auto* page_service = new MockService(services, "page_service");
  services.service_queue = {common};
  services.query_queue = {page_service};
  auto* standard = new MockStandardController(services);
  auto* advanced = new MockAdvancedController(services);
  services.standard_queue = {standard};
  services.advanced_queue = {advanced};
  store<TargetWord>(&page_definition, 0x0c, 0x9876u);
  OpaqueObject* items[3] = {&standard_item, &advanced_item, &distinct_item};
  set_vector(&page_definition, 0x70, 0x74, 0x78, items, 3, 3);
  store<TargetWord>(&standard_item, 0x24, 0x12345678u);
  store<TargetWord>(&advanced_item, 0x24, 0x42bf8c1du);
  store<TargetWord>(&distinct_item, 0x24, 0x71fa7d3fu);
  store<float>(&application_context, 0x24, 2.5F);
  store<float>(&application_context, 0x28, 3.5F);
  auto* application = new MockService(services, "page_application");

  assert(palette_page_construct_005c9230(&page, &page_definition, application,
                                         &application_context, 1,
                                         0) == nullptr);
  assert(load<float>(&page, 0x18) == 2.5F);
  assert(load<float>(&page, 0x1c) == 3.5F);
  const auto configure_event = services.last("configure:page_common");
  assert(services.events[configure_event].object == application);
  assert(services.contains("standard_init"));
  assert(services.contains("advanced_init"));
  const auto standard_event = services.last("standard_init");
  assert(services.events[standard_event].object == &application_context);
  assert(services.events[standard_event].value == 10.0F);
  assert(services.count("create_advanced") == 2);
  bool has_distinct_factory = false;
  for (const auto& event : services.events) {
    has_distinct_factory =
        has_distinct_factory ||
        (event.name == "create_advanced" &&
         event.first == static_cast<TargetWord>(AdvancedKind::token_71fa7d3f) &&
         event.second == 0x71fa7d3fu);
  }
  assert(has_distinct_factory);
  assert(services.count("advanced_item_layout") == 2);
  assert(services.count("bounds:page_entity") == 2);
  const auto advanced_layout = services.last("bounds:page_entity");
  assert(services.events[advanced_layout].layout.left == 102.0F);
  assert(services.events[advanced_layout].layout.top == 2.0F);
  assert(services.events[advanced_layout].layout.right == 3.0F);
  assert(services.events[advanced_layout].layout.bottom == 4.0F);
  assert(!services.contains("layout_value:page_entity"));
  const auto standard_end = load<TargetWord>(&page, 0x28);
  const auto standard_begin = load<TargetWord>(&page, 0x24);
  const auto advanced_end = load<TargetWord>(&page, 0x38);
  const auto advanced_begin = load<TargetWord>(&page, 0x34);
  assert(standard_end - standard_begin == sizeof(TargetWord));
  assert(advanced_end - advanced_begin == 2 * sizeof(TargetWord));
  assert(services.count("add_ref:query_service") == 0);
  assert(services.count("release:query_service") == 0);
  assert(services.count("add_ref:page_service") == 0);
  assert(services.count("release:page_service") == 0);
  assert(services.count("add_ref:advanced") == 2);
  assert(services.count("release:advanced") == 2);

  reset_services();
  OpaquePalettePage invalid_page;
  RawObject invalid_context;
  RawObject invalid_definition;
  store<float>(&invalid_context, 0x28, -1.0F);
  store<TargetWord>(&invalid_definition, 0x0c, 0x111u);
  services.key_match = false;
  auto* invalid_application = new MockService(services, "invalid");
  assert(palette_page_construct_005c9230(&invalid_page, &invalid_definition,
                                         invalid_application, &invalid_context,
                                         0, 0) == nullptr);
  assert(services.contains("page_metrics"));
  assert(!services.contains("standard_init"));
  assert(!services.contains("advanced_init"));

  reset_services();
  OpaquePalettePage zero_index_page;
  RawObject zero_index_definition;
  RawObject nondefault_context;
  auto* zero_index_application = new MockService(services, "zero_index_app");
  auto* zero_index_common = new MockService(services, "zero_index_common");
  auto* zero_index_service = new MockService(services, "zero_index_service");
  services.service_queue = {zero_index_common};
  services.query_queue = {zero_index_service};
  store<float>(&nondefault_context, 0x24, 4.5F);
  store<float>(&nondefault_context, 0x28, 5.5F);
  assert(palette_page_construct_005c9230(
             &zero_index_page, &zero_index_definition, zero_index_application,
             &nondefault_context, 0, 0) == nullptr);
  assert(load<float>(&zero_index_page, 0x18) == 4.5F);
  assert(load<float>(&zero_index_page, 0x1c) == 5.5F);
  assert(!services.contains("page_metrics"));
}

void test_construct_loop() {
  reset_services();
  OpaquePaletteEditor editor;
  RawObject category_source;
  RawObject first_item;
  RawObject second_item;
  RawObject categories[2];
  OpaqueObject* source_items[2] = {&first_item, &second_item};
  OpaqueObject* category_values[2] = {&categories[0], &categories[1]};
  set_vector(&category_source, 0x0c, 0x10, 0x14, source_items, 2, 2);
  store<TargetWord>(&category_source, 0x38, 1);
  set_vector(&editor, 0x34, 0x38, 0x3c, category_values, 0, 2);
  services.key_match = false;
  auto* category_panel = new MockService(services, "category_panel");
  auto* overlay_template = new MockService(services, "overlay_template");
  auto* tooltip = new MockService(services, "tooltip");
  auto* fade = new MockService(services, "fade");
  auto* first_overlay =
      new MockOverlay(services, overlay_template, tooltip, fade);
  auto* second_overlay =
      new MockOverlay(services, overlay_template, tooltip, fade);
  services.overlay_queue = {first_overlay, second_overlay};
  store<IEditorService*>(&editor, 0x10, category_panel);
  auto* application = new MockService(services, "loop_application");
  auto* owner = new MockCategoryRow(services, "owner");
  store<IEditorService*>(&editor, 0x24, application);

  palette_editor_construct_loop_005cb5a0(&editor, &category_source, application,
                                         0x99u, owner);
  assert(services.count("apply_base_layout") == 2);
  for (const auto& event : services.events) {
    if (event.name == "apply_base_layout") {
      assert(event.object == owner);
    }
  }
  assert(services.count("create_overlay") == 2);
  for (const auto& event : services.events) {
    if (event.name == "create_overlay") {
      assert(event.object == owner);
    }
  }
  assert(services.count("add_ref:overlay") == 4);
  assert(services.count("release:overlay") == 2);
  assert(services.count("add_ref:tooltip") == 2);
  assert(services.count("release:tooltip") == 2);
  assert(services.count("add_ref:fade") == 2);
  assert(services.count("release:fade") == 2);
  assert(services.count("add_ref:controller") == 4);
  assert(services.count("release:controller") == 2);
  assert(services.last("add_ref:overlay") < services.last("release:overlay"));
  assert(services.last("release:overlay") < services.last("release:fade"));
  assert(services.last("release:fade") < services.last("release:tooltip"));
  assert(services.count("add_ref:loop_application") == 0);
  assert(services.count("release:loop_application") == 0);
  assert(services.count("finish_palette_loop") == 1);
  const auto end = load<TargetWord>(&editor, 0x38);
  const auto begin = load<TargetWord>(&editor, 0x34);
  assert(end - begin == 2 * sizeof(TargetWord));
  assert(load<TargetWord>(&editor, 0x60) == 0);
  const auto selected = load<TargetWord>(reinterpret_cast<OpaqueObject*>(begin),
                                         sizeof(TargetWord));
  assert(load<TargetWord>(&editor, 0x64) == selected);
}

}
IPaletteServices& palette_support_services() { return services; }

}
int main() {
  using namespace openspore::reconstruction::pkg15_editor_support;
  test_category_validation_and_selection();
  test_palette_setup_selection_and_teardown();
  test_keyed_service_replacement_lifecycle();
  test_page_standard_and_advanced_branches();
  test_construct_loop();
}
