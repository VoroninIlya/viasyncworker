#pragma once

#include <functional>
#include <type_traits>

namespace viasyncworker {

  template <typename T>
  constexpr bool is_std_function_v = false;

  template <typename R, typename... Args>
  constexpr bool is_std_function_v<std::function<R(Args...)>> = true;

  template  <typename T, typename F>
  struct IViSubscriber {
    static_assert(std::is_default_constructible_v<T>, "T must be constructable type");
    static_assert(!std::is_pointer_v<T>, "T must not be a pointer type");
    static_assert(!std::is_reference_v<T>, "T must not be a reference type");
    static_assert(is_std_function_v<F>, "F must be a function type");

    virtual void call(const T&) = 0;
    virtual void assign(F val) = 0;

    virtual  ~IViSubscriber() =  default;
  };
  
}