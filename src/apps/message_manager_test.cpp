#include <cstdio>
#include <memory>
#include <string>
#include <vector>

#include "MessageManager.hpp"

namespace {

int g_failures = 0;

void check(bool condition, const char* label) {
  std::printf("%s: %s\n", condition ? "ok" : "FAIL", label);
  if (!condition) {
    ++g_failures;
  }
}

std::shared_ptr<const void> payload(int value) {
  return std::make_shared<int>(value);
}

}  // namespace

int main() {
  using openspore::message::kInvalidRegistration;
  using openspore::message::MessageManager;
  using openspore::message::MessageStatus;
  using openspore::message::MessageTarget;

  MessageManager manager;
  std::vector<std::string> order;
  const auto low = manager.registerListener(
      1, [&order](auto, const void*) { order.push_back("low"); }, 0);
  const auto newer = manager.registerListener(
      1, [&order](auto, const void*) { order.push_back("newer"); }, 0);
  const auto high = manager.registerListener(
      1, [&order](auto, const void*) { order.push_back("high"); }, 10);
  check(manager.registerListener(1, {}) == kInvalidRegistration &&
            manager.registerHandler(1, {}) == kInvalidRegistration,
        "empty registration has an explicit failure result");

  int value = 7;
  const auto immediate = manager.send(1, &value);
  check(immediate.status == MessageStatus::kRouted && immediate.ok() &&
            immediate.delivered == 3,
        "immediate transport reports every matching target");
  check(order.size() == 3 && order[0] == "high" && order[1] == "newer" &&
            order[2] == "low",
        "immediate order is priority descending and newest first");

  order.clear();
  const auto targeted = manager.send(1, &value, MessageTarget::listener(newer));
  check(targeted.status == MessageStatus::kRouted && targeted.delivered == 1 &&
            order.size() == 1 && order[0] == "newer",
        "immediate transport can target one registration");
  check(manager.send(99, &value).status == MessageStatus::kNoTarget,
        "unmatched immediate message reports no target");
  check(manager.send(1, &value, MessageTarget::listener(9999)).status ==
            MessageStatus::kInvalidTarget,
        "invalid immediate target is rejected");
  const auto unsupported = manager.send(
      1, &value,
      {static_cast<openspore::message::MessageTargetType>(255), 0, nullptr});
  check(unsupported.status == MessageStatus::kUnsupported,
        "unknown target kind is rejected as unsupported");

  int handlerContext = 0;
  bool handlerCalled = false;
  const auto handlerRegistration = manager.registerHandler(
      1,
      [&handlerCalled, &handlerContext](auto, const void*, void* context) {
        handlerCalled = context == &handlerContext;
      },
      &handlerContext);
  check(manager.send(1, &value, MessageTarget::handler(handlerRegistration))
                .status == MessageStatus::kRouted,
        "registered handler target is routed immediately");
  check(handlerCalled, "registered handler receives its context");

  manager.clearQueue();
  std::vector<int> deferredValues;
  const auto deferred =
      manager.registerListener(2, [&deferredValues](auto, const void* data) {
        deferredValues.push_back(*static_cast<const int*>(data));
      });
  check(manager.post(2, payload(20), 2).status == MessageStatus::kQueued,
        "deferred post is accepted");
  check(manager.post(2, payload(10), 1).status == MessageStatus::kQueued,
        "second deferred post is accepted");
  check(manager.queuedCount() == 2, "deferred transport retains queue records");
  check(manager.process(false) == 2 && deferredValues.size() == 2 &&
            deferredValues[0] == 10 && deferredValues[1] == 20,
        "deferred order key is explicit and ascending");

  order.clear();
  const auto snapshot = manager.registerListener(
      3, [&order](auto, const void*) { order.push_back("snapshot"); });
  check(manager.post(3, payload(1), 0, MessageTarget::listener(snapshot))
                .status == MessageStatus::kQueued,
        "targeted deferred post is accepted");
  check(manager.unregister(snapshot), "registration can be removed");
  check(manager.process(false) == 1 && order.size() == 1 &&
            order[0] == "snapshot",
        "registration removal does not cancel a queued target snapshot");

  int functionContext = 4;
  const auto handlerPayload = manager.postFunction(
      4, payload(8), 0,
      [&handlerCalled](auto, const void* data, void* ctx) {
        handlerCalled = *static_cast<const int*>(data) == 8 && ctx != nullptr;
      },
      &functionContext);
  check(handlerPayload.status == MessageStatus::kQueued,
        "deferred function target is accepted");
  check(manager.process(false) == 1 && handlerCalled,
        "deferred function target receives its context");

  const auto nested = manager.post(5, payload(11));
  check(nested.status == MessageStatus::kQueued, "nested post setup succeeds");
  bool postedNested = false;
  const auto nestedProducer =
      manager.registerListener(5, [&manager, &postedNested](auto, const void*) {
        if (!postedNested) {
          postedNested = true;
          manager.post(5, payload(12));
        }
      });
  check(nestedProducer != 0, "nested producer registration succeeds");
  check(manager.process(false) == 1 && manager.queuedCount() == 1,
        "snapshot processing leaves callback-created posts queued");
  check(manager.process(true) == 1 && manager.queuedCount() == 0,
        "drain processing includes callback-created posts");
  check(manager.unregister(deferred) && manager.unregister(newer) &&
            manager.unregister(high) && manager.unregister(low),
        "registrations can be removed");
  manager.dispose();
  check(manager.queuedCount() == 0, "dispose clears transport state");

  std::printf("message_manager_test: %s\n",
              g_failures == 0 ? "ALL PASS" : "FAIL");
  return g_failures == 0 ? 0 : 1;
}
