#pragma once

#include <functional>
#include <future>

namespace viasyncworker {

  template<typename R, typename C>
  struct IViAsyncWorker {
    IViAsyncWorker() = delete;
    IViAsyncWorker(std::function<R(C)> cb) : m_callback(cb) {}
    virtual void startWork(std::function<void(std::future<std::function<R(C)>>)> f) = 0;
    virtual ~IViAsyncWorker() = default;

  protected:
    std::function<R(C)> m_callback;
  };

}