#pragma once

#include "ividuplexqueue.hpp"
#include <type_traits>
#include <memory>
#include <map>
#include <deque>
#include <mutex>

namespace viasyncworker {

  template<typename T, typename F>
  class ViDuplexQueue : public IViDuplexQueue<T, F> {
    static_assert(std::is_default_constructible_v<T>, "T must be constructable type");
    static_assert(!std::is_pointer_v<T>, "T must not be a pointer type");
    static_assert(!std::is_reference_v<T>, "T must not be a reference type");
    static_assert(is_std_function_v<F>, "F must be a function type");

    static uint32_t m_nextSubscriberId;

    std::deque<T> m_incoming;
    std::deque<T> m_outgoing;
    std::mutex m_incomingMutex;
    std::mutex m_outgoingMutex;

    std::map<uint32_t, std::shared_ptr<IViSubscriber<T, F>>> m_subscribers;

  public:
    ViDuplexQueue();
    virtual ~ViDuplexQueue() override = default;

    virtual uint32_t addSubscriber(std::shared_ptr<IViSubscriber<T, F>> subscriber) override;
    virtual void removeSubscriber(uint32_t id) override;

    virtual void pushIncoming(const T& s) override;
    virtual T popIncoming() override;
    virtual void pushOutgoing(const T& s) override;
    virtual T popOutgoing() override;

    virtual bool hasOutgoing() override;
    virtual bool hasIncoming() override;

  };

}

#include "../viduplexqueue.cpp"