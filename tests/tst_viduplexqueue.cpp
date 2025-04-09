#include "viduplexqueue.hpp"
#include "visubscribermock.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace viasyncworker;

template <typename T>
class ViDuplexQueueTest : public ::testing::Test {};

using ViDuplexQueueTypes = ::testing::Types<
  std::pair<int, std::function<void(const int&)>>
  >;

TYPED_TEST_SUITE(ViDuplexQueueTest, ViDuplexQueueTypes);

TYPED_TEST(ViDuplexQueueTest, FullTest) {
  using T = typename TypeParam::first_type;
  using U = typename TypeParam::second_type;

  auto subscr1 = std::make_shared<VisubscriberMock<T, U>>();
  auto subscr2 = std::make_shared<VisubscriberMock<T, U>>();

  ViDuplexQueue<T, U> queue;

  ASSERT_FALSE(queue.hasIncoming());
  ASSERT_FALSE(queue.hasOutgoing());

  auto id1 = queue.addSubscriber(subscr1);
  queue.addSubscriber(subscr2);

  T test1 = T{static_cast<T>(1)};
  T test2 = T{static_cast<T>(2)};

  EXPECT_CALL(*subscr1, call(test1)).Times(1);
  EXPECT_CALL(*subscr2, call(test1)).Times(1);

  queue.pushIncoming(test1);

  queue.removeSubscriber(id1);

  EXPECT_CALL(*subscr1, call(test2)).Times(0);
  EXPECT_CALL(*subscr2, call(test2)).Times(1);

  queue.pushIncoming(test2);

  ASSERT_TRUE(queue.hasIncoming());

  ASSERT_EQ(test1, queue.popIncoming());
  ASSERT_EQ(test2, queue.popIncoming());
  ASSERT_EQ(T(), queue.popIncoming());

  queue.pushOutgoing(test1);
  queue.pushOutgoing(test2);

  ASSERT_TRUE(queue.hasOutgoing());

  ASSERT_EQ(test1, queue.popOutgoing());
  ASSERT_EQ(test2, queue.popOutgoing());
  ASSERT_EQ(T(), queue.popOutgoing());

}

