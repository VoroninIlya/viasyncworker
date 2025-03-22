#pragma once

#include "iviasyncworker.hpp"

#include <thread>
#include <future>
#include <queue>
#include <mutex>
#include <chrono>

namespace viasyncworker {

  template<typename R, typename C>
  class ViAsyncWorker : public IViAsyncWorker<R, C> {
  public:
    ViAsyncWorker() = delete;
    ViAsyncWorker(std::function<R(C)> cb) : IViAsyncWorker<R, C>(cb) {}
    virtual void startWork(std::function<void(std::future<std::function<R(C)>>)> f) override {
      std::promise<std::function<R(C)>> prom;
      std::future<std::function<R(C)>> fut = prom.get_future();

      std::thread t(f, std::move(fut));

      prom.set_value(IViAsyncWorker<R, C>::m_callback);

      t.detach();
    }
  };
}