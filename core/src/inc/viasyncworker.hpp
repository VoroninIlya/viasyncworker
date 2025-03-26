#pragma once

#include "iviasyncworker.hpp"

#include <thread>
#include <future>

namespace viasyncworker {

  template<typename R, typename C>
  class ViAsyncWorker : public IViAsyncWorker<R, C> {
    std::function<R(C)> m_callback;
  public:
    ViAsyncWorker() = delete;
    ViAsyncWorker(std::function<R(C)> cb) : m_callback(cb) {}
    virtual void startWork(std::function<void(std::future<std::function<R(C)>>)> f) override {
      std::promise<std::function<R(C)>> prom;
      std::future<std::function<R(C)>> fut = prom.get_future();

      std::thread t(f, std::move(fut));

      prom.set_value(m_callback);

      t.detach();
    }
  };

  template<typename R, typename C>
  class ViAsyncWorker<R, C*> : public IViAsyncWorker<R, C*> {
    std::function<R(C*)> m_callback;
  public:
    ViAsyncWorker() = delete;
    ViAsyncWorker(std::function<R(C*)> cb) : m_callback(cb) {}
    virtual void startWork(std::function<void(std::future<std::function<R(C*)>>)> f) override {
      std::promise<std::function<R(C*)>> prom;
      std::future<std::function<R(C*)>> fut = prom.get_future();

      std::thread t(f, std::move(fut));

      prom.set_value(m_callback);

      t.detach();
    }
  };

  template<typename R>
  class ViAsyncWorker<R, void> : public IViAsyncWorker<R, void> {
    std::function<R()> m_callback;
  public:
    ViAsyncWorker() = delete;
    ViAsyncWorker(std::function<R()> cb) : m_callback(cb) {}
    virtual void startWork(std::function<void(std::future<std::function<R()>>)> f) override {
      std::promise<std::function<R()>> prom;
      std::future<std::function<R()>> fut = prom.get_future();

      std::thread t(f, std::move(fut));

      prom.set_value(m_callback);

      t.detach();
    }
  };

}