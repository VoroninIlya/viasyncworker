#pragma once

#include <functional>
#include <future>

namespace viasyncworker {

  template<typename R, typename C>
  struct IViAsyncWorker {
    virtual void startWork(std::function<void(std::future<std::function<R(C)>>)> f) = 0;
    virtual ~IViAsyncWorker() = default;
  };

  template<typename R, typename C>
  struct IViAsyncWorker<R, C*> {
    virtual void startWork(std::function<void(std::future<std::function<R(C*)>>)> f) = 0;
    virtual ~IViAsyncWorker() = default;
  };

  template<typename R>
  struct IViAsyncWorker<R,void> {
    virtual void startWork(std::function<void(std::future<std::function<R()>>)> f) = 0;
    virtual ~IViAsyncWorker() = default;
  };

}