#include <gtest/gtest.h>
#include "queue.h"

TEST(QueueBasic, NewQueueEmpty) {
    Queue q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
    EXPECT_EQ(q.front(), nullptr);
    EXPECT_EQ(q.back(), nullptr);
}

TEST(QueueBasic, PushPopFIFO) {
    Queue q;
    q.push("a");
    q.push("b");
    q.push("c");

    EXPECT_EQ(q.size(), 3u);
    ASSERT_NE(q.front(), nullptr);
    EXPECT_EQ(*q.front(), "a");
    ASSERT_NE(q.back(), nullptr);
    EXPECT_EQ(*q.back(), "c");

    std::string out;
    ASSERT_TRUE(q.pop(&out));
    EXPECT_EQ(out, "a");
    ASSERT_TRUE(q.pop(&out));
    EXPECT_EQ(out, "b");
    ASSERT_TRUE(q.pop(&out));
    EXPECT_EQ(out, "c");
    EXPECT_TRUE(q.empty());
}

TEST(QueueCopyMove, CopyAndMoveWork) {
    Queue a;
    a.push("x");
    a.push("y");

    Queue b = a;
    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(*b.front(), "x");

    Queue c;
    c = a;
    EXPECT_EQ(c.size(), 2u);

    Queue d = std::move(a);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_TRUE(a.empty());

    Queue e;
    e = std::move(d);
    EXPECT_EQ(e.size(), 2u);
    EXPECT_TRUE(d.empty());
}

TEST(QueueIO, SaveAndLoad) {
    Queue q;
    q.push("1");
    q.push("2");
    ASSERT_TRUE(q.save_to_file("test_queue.txt"));

    Queue other;
    ASSERT_TRUE(other.load_from_file("test_queue.txt"));
    EXPECT_EQ(other.size(), 2u);

    std::string out;
    ASSERT_TRUE(other.pop(&out));
    EXPECT_EQ(out, "1");
    ASSERT_TRUE(other.pop(&out));
    EXPECT_EQ(out, "2");
}
