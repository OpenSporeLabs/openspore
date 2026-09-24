#include "MessageManager.hpp"

#include <algorithm>
#include <utility>

namespace openspore::message {

RegistrationId MessageManager::nextRegistration() {
  const RegistrationId id = mNextRegistration++;
  if (mNextRegistration == 0) {
    ++mNextRegistration;
  }
  return id;
}

const MessageManager::Registration* MessageManager::findRegistration(
    RegistrationId id) const {
  for (const Registration& registration : mRegistrations) {
    if (registration.id == id) {
      return &registration;
    }
  }
  return nullptr;
}

bool MessageManager::matches(const Registration& registration, MessageId id) {
  return registration.messageId == id;
}

bool MessageManager::dispatchRegistration(const Registration& registration,
                                          MessageId id, const void* payload) {
  if (registration.type == RegistrationType::kListener) {
    if (!registration.listener) {
      return false;
    }
    registration.listener(id, payload);
    return true;
  }
  if (!registration.handler) {
    return false;
  }
  registration.handler(id, payload, registration.context);
  return true;
}

bool MessageManager::dispatchQueued(const QueuedDelivery& delivery) {
  if (delivery.registration.has_value()) {
    return dispatchRegistration(*delivery.registration, delivery.id,
                                delivery.payload.get());
  }
  if (delivery.target.type == MessageTargetType::kHandler &&
      delivery.target.registration == 0) {
    if (!delivery.handler) {
      return false;
    }
    delivery.handler(delivery.id, delivery.payload.get(), delivery.context);
    return true;
  }

  std::vector<Registration> registrations;
  for (const Registration& registration : mRegistrations) {
    if (matches(registration, delivery.id)) {
      registrations.push_back(registration);
    }
  }
  std::sort(registrations.begin(), registrations.end(),
            [](const Registration& left, const Registration& right) {
              if (left.priority != right.priority) {
                return left.priority > right.priority;
              }
              return left.sequence > right.sequence;
            });

  bool delivered = false;
  for (const Registration& registration : registrations) {
    delivered = dispatchRegistration(registration, delivery.id,
                                     delivery.payload.get()) ||
                delivered;
  }
  return delivered;
}

bool MessageManager::queueLess(const QueuedDelivery& left,
                               const QueuedDelivery& right) {
  if (left.orderKey != right.orderKey) {
    return left.orderKey < right.orderKey;
  }
  return left.sequence < right.sequence;
}

bool MessageManager::validTarget(const MessageTarget& target,
                                 RegistrationId* registration) const {
  if (target.type == MessageTargetType::kBroadcast) {
    return true;
  }
  if (target.type != MessageTargetType::kListener &&
      target.type != MessageTargetType::kHandler) {
    return false;
  }
  const Registration* entry = findRegistration(target.registration);
  if (entry == nullptr ||
      (target.type == MessageTargetType::kListener &&
       entry->type != RegistrationType::kListener) ||
      (target.type == MessageTargetType::kHandler &&
       entry->type != RegistrationType::kHandler)) {
    return false;
  }
  if (registration != nullptr) {
    *registration = entry->id;
  }
  return true;
}

RegistrationId MessageManager::registerListener(MessageId id,
                                                MessageListener listener,
                                                int priority) {
  if (!listener) {
    return 0;
  }
  Registration registration;
  registration.id = nextRegistration();
  registration.messageId = id;
  registration.type = RegistrationType::kListener;
  registration.priority = priority;
  registration.sequence = mNextSequence++;
  registration.listener = std::move(listener);
  const RegistrationId result = registration.id;
  mRegistrations.push_back(std::move(registration));
  return result;
}

RegistrationId MessageManager::registerHandler(MessageId id,
                                               MessageHandler handler,
                                               void* context, int priority) {
  if (!handler) {
    return 0;
  }
  Registration registration;
  registration.id = nextRegistration();
  registration.messageId = id;
  registration.type = RegistrationType::kHandler;
  registration.priority = priority;
  registration.sequence = mNextSequence++;
  registration.handler = std::move(handler);
  registration.context = context;
  const RegistrationId result = registration.id;
  mRegistrations.push_back(std::move(registration));
  return result;
}

bool MessageManager::unregister(RegistrationId id) {
  for (auto it = mRegistrations.begin(); it != mRegistrations.end(); ++it) {
    if (it->id == id) {
      mRegistrations.erase(it);
      return true;
    }
  }
  return false;
}

MessageDispatchResult MessageManager::send(MessageId id, const void* payload,
                                           MessageTarget target) {
  if (target.type != MessageTargetType::kBroadcast &&
      target.type != MessageTargetType::kListener &&
      target.type != MessageTargetType::kHandler) {
    return {MessageStatus::kUnsupported, 0};
  }

  std::vector<Registration> registrations;
  if (target.type == MessageTargetType::kBroadcast) {
    for (const Registration& registration : mRegistrations) {
      if (matches(registration, id)) {
        registrations.push_back(registration);
      }
    }
  } else {
    const Registration* registration = findRegistration(target.registration);
    if (registration == nullptr || !matches(*registration, id) ||
        (target.type == MessageTargetType::kListener &&
         registration->type != RegistrationType::kListener) ||
        (target.type == MessageTargetType::kHandler &&
         registration->type != RegistrationType::kHandler)) {
      return {MessageStatus::kInvalidTarget, 0};
    }
    registrations.push_back(*registration);
  }

  if (registrations.empty()) {
    return {MessageStatus::kNoTarget, 0};
  }
  std::sort(registrations.begin(), registrations.end(),
            [](const Registration& left, const Registration& right) {
              if (left.priority != right.priority) {
                return left.priority > right.priority;
              }
              return left.sequence > right.sequence;
            });

  std::size_t delivered = 0;
  for (const Registration& registration : registrations) {
    if (dispatchRegistration(registration, id, payload)) {
      ++delivered;
    }
  }
  return {MessageStatus::kRouted, delivered};
}

MessageDispatchResult MessageManager::post(MessageId id,
                                           std::shared_ptr<const void> payload,
                                           int orderKey, MessageTarget target) {
  RegistrationId targetId = 0;
  if (!validTarget(target, &targetId)) {
    return {MessageStatus::kInvalidTarget, 0};
  }

  QueuedDelivery delivery;
  delivery.id = id;
  delivery.payload = std::move(payload);
  delivery.target = target;
  delivery.orderKey = orderKey;
  delivery.sequence = mNextSequence++;
  if (target.type != MessageTargetType::kBroadcast) {
    const Registration* registration = findRegistration(targetId);
    if (registration == nullptr || !matches(*registration, id)) {
      return {MessageStatus::kInvalidTarget, 0};
    }
    delivery.registration = *registration;
  }
  mQueue.push_back(std::move(delivery));
  return {MessageStatus::kQueued, 0};
}

MessageDispatchResult MessageManager::postFunction(
    MessageId id, std::shared_ptr<const void> payload, int orderKey,
    MessageHandler handler, void* context) {
  if (!handler) {
    return {MessageStatus::kInvalidRegistration, 0};
  }
  QueuedDelivery delivery;
  delivery.id = id;
  delivery.payload = std::move(payload);
  delivery.target = MessageTarget::handler(0);
  delivery.orderKey = orderKey;
  delivery.sequence = mNextSequence++;
  delivery.handler = std::move(handler);
  delivery.context = context;
  mQueue.push_back(std::move(delivery));
  return {MessageStatus::kQueued, 0};
}

std::size_t MessageManager::process(bool drain) {
  std::size_t delivered = 0;
  if (!drain) {
    std::vector<QueuedDelivery> batch;
    batch.swap(mQueue);
    std::sort(batch.begin(), batch.end(), queueLess);
    for (const QueuedDelivery& delivery : batch) {
      if (dispatchQueued(delivery)) {
        ++delivered;
      }
    }
    return delivered;
  }

  while (!mQueue.empty()) {
    auto next = std::min_element(mQueue.begin(), mQueue.end(), queueLess);
    QueuedDelivery delivery = std::move(*next);
    mQueue.erase(next);
    if (dispatchQueued(delivery)) {
      ++delivered;
    }
  }
  return delivered;
}

std::size_t MessageManager::queuedCount() const { return mQueue.size(); }

void MessageManager::clearQueue() { mQueue.clear(); }

void MessageManager::dispose() {
  mQueue.clear();
  mRegistrations.clear();
  mNextRegistration = 1;
  mNextSequence = 1;
}

}  // namespace openspore::message
