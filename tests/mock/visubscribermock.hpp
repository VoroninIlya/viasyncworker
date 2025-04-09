#pragma once

#include <gmock/gmock.h>
#include "ivisubscriber.hpp"

using namespace viasyncworker;

template <typename T, typename F>
class VisubscriberMock : public IViSubscriber<T, F> {
public:
  MOCK_METHOD(void, call, (const T&), (override));
  MOCK_METHOD(void, assign, (F val), (override));
};

