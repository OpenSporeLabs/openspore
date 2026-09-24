#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <vector>

namespace openspore::message {

using MessageId = std::uint32_t;
using RegistrationId = std::uint64_t;
inline constexpr RegistrationId kInvalidRegistration = 0;
using MessageListener = std::function<void(MessageId, const void*)>;
using MessageHandler = std::function<void(MessageId, const void*, void*)>;

enum class MessageTargetType : std::uint8_t {
  kBroadcast,
  kListener,
  kHandler,
};

struct MessageTarget {
  MessageTargetType type = MessageTargetType::kBroadcast;
  RegistrationId registration = 0;
  void* context = nullptr;

  static MessageTarget broadcast() { return {}; }
  static MessageTarget listener(RegistrationId id) {
    return {MessageTargetType::kListener, id, nullptr};
  }
  static MessageTarget handler(RegistrationId id) {
    return {MessageTargetType::kHandler, id, nullptr};
  }
};

enum class MessageStatus : std::uint8_t {
  kRouted,
  kQueued,
  kNoTarget,
  kInvalidTarget,
  kInvalidRegistration,
  kUnsupported,
};

struct MessageDispatchResult {
  MessageStatus status = MessageStatus::kUnsupported;
  std::size_t delivered = 0;

  bool ok() const {
    return status == MessageStatus::kRouted || status == MessageStatus::kQueued;
  }
};

class IMessageManager {
 public:
  virtual ~IMessageManager() = default;

  virtual RegistrationId registerListener(MessageId id,
                                          MessageListener listener,
                                          int priority = 0) = 0;
  virtual RegistrationId registerHandler(MessageId id, MessageHandler handler,
                                         void* context = nullptr,
                                         int priority = 0) = 0;
  virtual bool unregister(RegistrationId registration) = 0;
  virtual MessageDispatchResult send(MessageId id,
                                     const void* payload = nullptr,
                                     MessageTarget target = {}) = 0;
  virtual MessageDispatchResult post(MessageId id,
                                     std::shared_ptr<const void> payload = {},
                                     int orderKey = 0,
                                     MessageTarget target = {}) = 0;
  virtual MessageDispatchResult postFunction(
      MessageId id, std::shared_ptr<const void> payload, int orderKey,
      MessageHandler handler, void* context = nullptr) = 0;
  virtual std::size_t process(bool drain = false) = 0;
  virtual std::size_t queuedCount() const = 0;
  virtual void clearQueue() = 0;
  virtual void dispose() = 0;
};

class MessageManager final : public IMessageManager {
 public:
  RegistrationId registerListener(MessageId id, MessageListener listener,
                                  int priority = 0) override;
  RegistrationId registerHandler(MessageId id, MessageHandler handler,
                                 void* context = nullptr,
                                 int priority = 0) override;
  bool unregister(RegistrationId registration) override;
  MessageDispatchResult send(MessageId id, const void* payload = nullptr,
                             MessageTarget target = {}) override;
  MessageDispatchResult post(MessageId id,
                             std::shared_ptr<const void> payload = {},
                             int orderKey = 0,
                             MessageTarget target = {}) override;
  MessageDispatchResult postFunction(MessageId id,
                                     std::shared_ptr<const void> payload,
                                     int orderKey, MessageHandler handler,
                                     void* context = nullptr) override;
  std::size_t process(bool drain = false) override;
  std::size_t queuedCount() const override;
  void clearQueue() override;
  void dispose() override;

 private:
  enum class RegistrationType : std::uint8_t {
    kListener,
    kHandler,
  };

  struct Registration {
    RegistrationId id = 0;
    MessageId messageId = 0;
    RegistrationType type = RegistrationType::kListener;
    int priority = 0;
    std::uint64_t sequence = 0;
    MessageListener listener;
    MessageHandler handler;
    void* context = nullptr;
  };

  struct QueuedDelivery {
    MessageId id = 0;
    std::shared_ptr<const void> payload;
    MessageTarget target;
    int orderKey = 0;
    std::uint64_t sequence = 0;
    std::optional<Registration> registration;
    MessageHandler handler;
    void* context = nullptr;
  };

  RegistrationId nextRegistration();
  const Registration* findRegistration(RegistrationId id) const;
  static bool matches(const Registration& registration, MessageId id);
  static bool dispatchRegistration(const Registration& registration,
                                   MessageId id, const void* payload);
  bool dispatchQueued(const QueuedDelivery& delivery);
  static bool queueLess(const QueuedDelivery& left,
                        const QueuedDelivery& right);
  bool validTarget(const MessageTarget& target,
                   RegistrationId* registration) const;

  std::vector<Registration> mRegistrations;
  std::vector<QueuedDelivery> mQueue;
  RegistrationId mNextRegistration = 1;
  std::uint64_t mNextSequence = 1;
};

}  // namespace openspore::message

namespace openspore::gamemode {
using message::IMessageManager;
using message::MessageDispatchResult;
using message::MessageHandler;
using message::MessageId;
using message::MessageListener;
using message::MessageManager;
using message::MessageStatus;
using message::MessageTarget;
using message::MessageTargetType;
using message::RegistrationId;
}  // namespace openspore::gamemode
