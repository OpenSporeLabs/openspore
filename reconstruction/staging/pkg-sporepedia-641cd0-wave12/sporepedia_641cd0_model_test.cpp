#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "sporepedia_641cd0.hpp"

namespace recon = openspore::reconstruction::pkg_sporepedia_641cd0_wave12;

using recon::SporepediaAssetData;
using recon::SporepediaGameModeManager;
using recon::SporepediaHandle;
using recon::SporepediaRefCounted;
using recon::kPollenMetadataTag;

static_assert(sizeof(void *) == 4, "0x00641cd0 is an x86-32 reconstruction");
static_assert(sizeof(recon::SporepediaInitBlock) == 16, "block is 16 bytes");
static_assert(kPollenMetadataTag == 0x030bdee3u, "pollen_metadata");

// ---------------------------------------------------------------------------
// Trace
// ---------------------------------------------------------------------------

enum class Step : std::uint8_t {
  manager_get,
  manager_initialize,
  manager_dispose,
  handle_query,
  handle_release,
  ref_add,
  ref_release,
  assign_out_of_line,
};

static Step g_trace[64];
static int g_trace_len = 0;

static void record(Step step) {
  assert(g_trace_len < 64);
  g_trace[g_trace_len++] = step;
}

static void reset_trace() { g_trace_len = 0; }

// The doubles below put the opaque vtable first, so the pointer the
// reconstruction passes around is simply the address of the double.
template <typename Double> static Double *owner_of(void *opaque) {
  return reinterpret_cast<Double *>(opaque);
}

template <typename Double> static void *opaque_of(Double *d) {
  return reinterpret_cast<void *>(d);
}

// ---------------------------------------------------------------------------
// Ref double: the object the +0x0C type query returns
// ---------------------------------------------------------------------------

struct RefDouble {
  recon::SporepediaRefCountedVtable vtable{};
  int adds = 0;
  int releases = 0;
};

static void ref_add_ref(SporepediaRefCounted *self) {
  record(Step::ref_add);
  ++owner_of<RefDouble>(self)->adds;
}

static void ref_release(SporepediaRefCounted *self) {
  record(Step::ref_release);
  ++owner_of<RefDouble>(self)->releases;
}

static void init_ref(RefDouble *d) {
  d->vtable.add_ref = &ref_add_ref;
  d->vtable.release = &ref_release;
  d->adds = 0;
  d->releases = 0;
}

static std::uint32_t ref_word(RefDouble *d) {
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(static_cast<SporepediaRefCounted *>(
          static_cast<void *>(d))));
}

// ---------------------------------------------------------------------------
// Handle double: the object the manager writes into the out parameter
// ---------------------------------------------------------------------------

struct HandleDouble {
  recon::SporepediaHandleVtable vtable{};
  RefDouble *produced = nullptr;
  std::uint32_t produced_tag = 0;
  int queries = 0;
  int releases = 0;
};

static SporepediaRefCounted *handle_query(SporepediaHandle *self,
                                          std::uint32_t tag) {
  record(Step::handle_query);
  HandleDouble *d = owner_of<HandleDouble>(self);
  ++d->queries;
  d->produced_tag = tag;
  return static_cast<SporepediaRefCounted *>(opaque_of(d->produced));
}

static void handle_release(SporepediaHandle *self) {
  record(Step::handle_release);
  ++owner_of<HandleDouble>(self)->releases;
}

static void init_handle(HandleDouble *d, RefDouble *produced) {
  d->vtable.add_ref = nullptr;
  d->vtable.release = &handle_release;
  d->vtable.query_by_type = &handle_query;
  d->produced = produced;
  d->produced_tag = 0;
  d->queries = 0;
  d->releases = 0;
}

// ---------------------------------------------------------------------------
// Manager double
// ---------------------------------------------------------------------------

struct ManagerDouble {
  recon::SporepediaGameModeManagerVtable vtable{};
  bool result = true;
  bool writes_handle = false;
  HandleDouble *handle = nullptr;
  int initializes = 0;
  int disposes = 0;
  // Captured call arguments, copied out of the caller's frame during the call.
  std::uint32_t descriptor[3] = {0, 0, 0};
  std::uint32_t *out_arg = nullptr;
  std::uint32_t *ref70_arg = nullptr;
  std::uint32_t tail[5] = {0, 0, 0, 0, 0};
  int tail_len = 0;
  int arg_count = 0;
};

// The slot signature carries the opaque manager type, so the double is
// recovered from a file-scope pointer.
static ManagerDouble *g_active_manager = nullptr;

static std::uint8_t manager_initialize(SporepediaGameModeManager *,
                                       const std::uint32_t *block_w0,
                                       std::uint32_t *out, std::uint32_t a3,
                                       std::uint32_t a4, std::uint32_t a5,
                                       std::uint32_t a6) {
  record(Step::manager_initialize);
  ManagerDouble *d = g_active_manager;
  ++d->initializes;
  d->arg_count = 6;
  d->descriptor[0] = block_w0[0];
  d->descriptor[1] = block_w0[1];
  d->descriptor[2] = block_w0[2];
  d->out_arg = out;
  d->ref70_arg = nullptr;
  d->tail[0] = a3;
  d->tail[1] = a4;
  d->tail[2] = a5;
  d->tail[3] = a6;
  d->tail_len = 4;
  if (d->writes_handle) {
    *out = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(opaque_of(d->handle)));
  }
  return d->result ? 1u : 0u;
}

static std::uint8_t manager_dispose(SporepediaGameModeManager *,
                                    const std::uint32_t *block_w0,
                                    std::uint32_t *ref70, std::uint32_t *out,
                                    std::uint32_t a4, std::uint32_t a5,
                                    std::uint32_t a6, std::uint32_t a7,
                                    std::uint32_t a8) {
  record(Step::manager_dispose);
  ManagerDouble *d = g_active_manager;
  ++d->disposes;
  d->arg_count = 8;
  d->descriptor[0] = block_w0[0];
  d->descriptor[1] = block_w0[1];
  d->descriptor[2] = block_w0[2];
  d->ref70_arg = ref70;
  d->out_arg = out;
  d->tail[0] = a4;
  d->tail[1] = a5;
  d->tail[2] = a6;
  d->tail[3] = a7;
  d->tail[4] = a8;
  d->tail_len = 5;
  if (d->writes_handle) {
    *out = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(opaque_of(d->handle)));
  }
  return d->result ? 1u : 0u;
}

static void init_manager(ManagerDouble *d, bool result, bool writes_handle,
                         HandleDouble *handle) {
  d->vtable.slot_00 = nullptr;
  d->vtable.release = nullptr;
  d->vtable.slot_08 = nullptr;
  d->vtable.initialize = &manager_initialize;
  d->vtable.dispose = &manager_dispose;
  d->result = result;
  d->writes_handle = writes_handle;
  d->handle = handle;
  d->initializes = 0;
  d->disposes = 0;
  d->descriptor[0] = 0;
  d->descriptor[1] = 0;
  d->descriptor[2] = 0;
  d->out_arg = nullptr;
  d->ref70_arg = nullptr;
  d->tail[0] = 0;
  d->tail[1] = 0;
  d->tail[2] = 0;
  d->tail[3] = 0;
  d->tail[4] = 0;
  d->tail_len = 0;
  d->arg_count = 0;
}

static SporepediaGameModeManager *as_manager(ManagerDouble *d) {
  return static_cast<SporepediaGameModeManager *>(opaque_of(d));
}

// ---------------------------------------------------------------------------
// Ports: faithful bodies of the two direct callees
// ---------------------------------------------------------------------------

// 0x00b5f950, transcribed from its Ghidra decompilation. The target also
// inlines this sequence at 0x00641dd0..0x00641df1, which is what confirms it.
extern "C" std::uint32_t *sporepedia_00b5f950_intrusive_ptr_assign(
    std::uint32_t *slot, std::uint32_t value) {
  record(Step::assign_out_of_line);
  std::uint32_t old = *slot;
  if (value != old) {
    if (value != 0) {
      ref_add_ref(
          static_cast<SporepediaRefCounted *>(static_cast<void *>(
              reinterpret_cast<RefDouble *>(
                  reinterpret_cast<std::uintptr_t>(value)))));
    }
    *slot = value;
    if (old != 0) {
      ref_release(
          static_cast<SporepediaRefCounted *>(static_cast<void *>(
              reinterpret_cast<RefDouble *>(
                  reinterpret_cast<std::uintptr_t>(old)))));
    }
  }
  return slot;
}

static SporepediaGameModeManager *g_manager_ptr = nullptr;

extern "C" SporepediaGameModeManager *
sporepedia_0067dcd0_app_igamemodemanager_get() {
  record(Step::manager_get);
  return g_manager_ptr;
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static void expect_trace(const Step *expected, int len) {
  assert(len == g_trace_len);
  for (int i = 0; i < len; ++i) {
    assert(g_trace[i] == expected[i]);
  }
}

static SporepediaAssetData make_asset(std::uint32_t ref1c,
                                      std::uint32_t ref70) {
  SporepediaAssetData data;
  std::memset(&data, 0, sizeof(data));
  data.field_04 = 0x11112222u;
  data.field_08 = 0x33334444u;
  data.field_0c = 0x55556666u;
  data.ref_1c = ref1c;
  data.ref_70 = ref70;
  return data;
}

static void run() {
  // -- flag == 0 takes the vtable+0x0C branch, six stack arguments ----------
  {
    RefDouble old_ref{};
    RefDouble fresh{};
    HandleDouble handle{};
    ManagerDouble manager{};
    init_ref(&old_ref);
    init_ref(&fresh);
    init_handle(&handle, &fresh);
    init_manager(&manager, true, true, &handle);
    g_manager_ptr = as_manager(&manager);
    g_active_manager = &manager;

    SporepediaAssetData data = make_asset(ref_word(&old_ref), 0);
    reset_trace();
    recon::Sporepedia_00641cd0(&data, 0);

    const Step expected[] = {Step::manager_get, Step::manager_initialize,
                             Step::handle_query, Step::ref_add,
                             Step::ref_release, Step::handle_release};
    expect_trace(expected, 6);

    // Descriptor words: self->field_04, the constant, self->field_0c.
    assert(manager.descriptor[0] == 0x11112222u);
    assert(manager.descriptor[1] == 0x030bdee3u);
    assert(manager.descriptor[2] == 0x55556666u);
    // Six stack arguments and no ref_70 pointer on this branch.
    assert(manager.arg_count == 6);
    assert(manager.ref70_arg == nullptr);
    assert(manager.out_arg != nullptr);
    assert(manager.tail_len == 4);
    for (int i = 0; i < 4; ++i) {
      assert(manager.tail[i] == 0u);
    }
    // The +0x0C type query always carries pollen_metadata.
    assert(handle.produced_tag == 0x030bdee3u);
    assert(handle.queries == 1);
    // The assign is inlined on this branch, never called out of line.
    assert(fresh.adds == 1);
    assert(old_ref.releases == 1);
    assert(data.ref_1c == ref_word(&fresh));
    // The out handle is released once on the way out.
    assert(handle.releases == 1);
    // field_08 is loaded into ECX but reaches neither the descriptor nor the
    // manager: the value survives untouched.
    assert(data.field_08 == 0x33334444u);
  }

  // -- flag != 0 takes the vtable+0x10 branch, eight stack arguments --------
  {
    RefDouble old_ref{};
    RefDouble fresh{};
    RefDouble pending70{};
    HandleDouble handle{};
    ManagerDouble manager{};
    init_ref(&old_ref);
    init_ref(&fresh);
    init_ref(&pending70);
    init_handle(&handle, &fresh);
    init_manager(&manager, true, true, &handle);
    g_manager_ptr = as_manager(&manager);
    g_active_manager = &manager;

    SporepediaAssetData data =
        make_asset(ref_word(&old_ref), ref_word(&pending70));
    reset_trace();
    recon::Sporepedia_00641cd0(&data, 1);

    const Step expected[] = {Step::manager_get,         Step::ref_release,
                             Step::manager_dispose,     Step::handle_query,
                             Step::assign_out_of_line,  Step::ref_add,
                             Step::ref_release,         Step::handle_release};
    expect_trace(expected, 8);

    // This branch drops self+0x70 before dispatching.
    assert(data.ref_70 == 0u);
    assert(pending70.releases == 1);
    // Eight stack arguments, the second being &self+0x70.
    assert(manager.arg_count == 8);
    assert(manager.ref70_arg == &data.ref_70);
    assert(manager.out_arg != nullptr);
    assert(manager.tail_len == 5);
    for (int i = 0; i < 5; ++i) {
      assert(manager.tail[i] == 0u);
    }
    assert(manager.descriptor[1] == 0x030bdee3u);
    // This branch reaches the assign out of line at 0x00641d7b.
    assert(fresh.adds == 1);
    assert(old_ref.releases == 1);
    assert(data.ref_1c == ref_word(&fresh));
    assert(handle.releases == 1);
  }

  // -- a false return leaves self+0x1C alone -------------------------------
  {
    RefDouble old_ref{};
    RefDouble pending70{};
    HandleDouble handle{};
    ManagerDouble manager{};
    init_ref(&old_ref);
    init_ref(&pending70);
    init_handle(&handle, nullptr);
    init_manager(&manager, false, true, &handle);
    g_manager_ptr = as_manager(&manager);
    g_active_manager = &manager;

    SporepediaAssetData data =
        make_asset(ref_word(&old_ref), ref_word(&pending70));
    reset_trace();
    recon::Sporepedia_00641cd0(&data, 1);

    // The drop of self+0x70 happens before the dispatch so it survives the
    // false return; the type query and the assign never run.
    const Step expected[] = {Step::manager_get, Step::ref_release,
                             Step::manager_dispose, Step::handle_release};
    expect_trace(expected, 4);
    assert(data.ref_70 == 0u);
    assert(data.ref_1c == ref_word(&old_ref));
    assert(old_ref.adds == 0);
    assert(old_ref.releases == 0);
  }

  // -- a null out handle collapses the refresh ------------------------------
  {
    RefDouble old_ref{};
    ManagerDouble manager{};
    init_ref(&old_ref);
    init_manager(&manager, true, false, nullptr);
    g_manager_ptr = as_manager(&manager);
    g_active_manager = &manager;

    SporepediaAssetData data = make_asset(ref_word(&old_ref), 0);
    reset_trace();
    recon::Sporepedia_00641cd0(&data, 0);

    // With no handle the inline assign is reached with a null value, so the
    // old reference is dropped and the field cleared.
    const Step expected[] = {Step::manager_get, Step::manager_initialize,
                             Step::ref_release};
    expect_trace(expected, 3);
    assert(data.ref_1c == 0u);
    assert(old_ref.releases == 1);
  }

  // -- an unchanged value short-circuits -----------------------------------
  {
    RefDouble same{};
    HandleDouble handle{};
    ManagerDouble manager{};
    init_ref(&same);
    init_handle(&handle, &same);
    init_manager(&manager, true, true, &handle);
    g_manager_ptr = as_manager(&manager);
    g_active_manager = &manager;

    SporepediaAssetData data = make_asset(ref_word(&same), 0);
    reset_trace();
    recon::Sporepedia_00641cd0(&data, 0);

    // The CMP at 0x00641dd3 short-circuits: no add-ref, no release.
    const Step expected[] = {Step::manager_get, Step::manager_initialize,
                             Step::handle_query, Step::handle_release};
    expect_trace(expected, 4);
    assert(same.adds == 0);
    assert(same.releases == 0);
    assert(data.ref_1c == ref_word(&same));
  }

  // -- the manager is dereferenced with no null check -----------------------
  // 0x00641d39 reads [EDI] unguarded, so a null manager faults. That is the
  // runtime gate on DAT_015fd894, the global 0x0067dcd0 returns.
  {
    g_manager_ptr = nullptr;
    SporepediaAssetData data = make_asset(0, 0);
    pid_t pid = fork();
    assert(pid >= 0);
    if (pid == 0) {
      recon::Sporepedia_00641cd0(&data, 0);
      _exit(0);
    }
    int status = 0;
    assert(waitpid(pid, &status, 0) == pid);
    assert(WIFSIGNALED(status));
    assert(WTERMSIG(status) == SIGSEGV);
  }
}

int main() { run(); }
