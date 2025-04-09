#pragma once

#include "ivisubscriber.hpp"
#include <type_traits>
#include <cinttypes>
#include <memory>

namespace viasyncworker {

  template<typename T, typename F>
  struct IViDuplexQueue {

    static_assert(std::is_default_constructible_v<T>, "T must be constructable type");
    static_assert(!std::is_pointer_v<T>, "T must not be a pointer type");
    static_assert(!std::is_reference_v<T>, "T must not be a reference type");
    static_assert(is_std_function_v<F>, "F must be a function type");

    virtual uint32_t addSubscriber(std::shared_ptr<IViSubscriber<T, F>> subscriber) = 0;
    virtual void removeSubscriber(uint32_t id) = 0;

    virtual void pushIncoming(const T& s) = 0;
    virtual T popIncoming() = 0;
    virtual void pushOutgoing(const T& s) = 0;
    virtual T popOutgoing() = 0;

    virtual bool hasOutgoing() = 0;
    virtual bool hasIncoming() = 0;

    virtual ~IViDuplexQueue() = default;

  };
  
}