#include "viasyncworker.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace viasyncworker;

template <typename T>
class ViAsyncWorkerTest : public ::testing::Test {};

using ViAsyncWorkerTypes = ::testing::Types<
  std::pair<std::monostate, int>,
  std::pair<std::monostate, std::monostate>,
  std::pair<int, std::monostate>,
  std::pair<void*, void*>>;

TYPED_TEST_SUITE(ViAsyncWorkerTest, ViAsyncWorkerTypes);

TYPED_TEST(ViAsyncWorkerTest, FullTest) {
  using T1 = std::conditional_t<std::is_same_v<typename TypeParam::first_type, std::monostate>, void, typename TypeParam::first_type>;
  using T2 = std::conditional_t<std::is_same_v<typename TypeParam::second_type, std::monostate>, void, typename TypeParam::second_type>;;

  if constexpr (std::is_void_v<T2>) {

    auto worker = std::make_unique<ViAsyncWorker<T1,T2>>([&](){
      if constexpr (!std::is_void_v<T1>) {
        return (T1)1000;
      }
    });

    if constexpr (!std::is_void_v<T1>) {
      worker->startWork([&](std::future<std::function<T1()>> f) {
        if(auto cb = f.get()) {
          ASSERT_EQ((T1)1000, cb());
        }
      });
    } else {
      worker->startWork([&](std::future<std::function<T1()>> f) {
        if(auto cb = f.get())
            cb();
      });
    }

  } else {

    auto worker = std::make_unique<ViAsyncWorker<T1,T2>>([&](T2 p) {
      if constexpr (!std::is_void_v<T1>) {
        ASSERT_EQ((T2)3000, p), (T1)2000;
        return (T1)2000;
      } else {
        ASSERT_EQ((T2)3000, p);
      }

    });

    if constexpr (!std::is_void_v<T1>) {
      worker->startWork([&](std::future<std::function<T1(T2 p)>> f) {
        if(auto cb = f.get()) {
          ASSERT_EQ((T1)2000, cb((T2)3000));
        }
      });

    } else {
      worker->startWork([&](std::future<std::function<T1(T2 p)>> f) {
        if(auto cb = f.get())
          cb((T2)3000);
      });
    }
  }
}