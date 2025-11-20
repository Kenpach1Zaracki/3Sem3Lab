#include <gtest/gtest.h>
#include "hash.h"

TEST(HashMapBasic, NewMapEmpty) {
    HashMap m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0u);
    EXPECT_GT(m.bucket_count(), 0u);
}

TEST(HashMapBasic, SetGetContainsErase) {
    HashMap m;
    m.set("a", "1");
    m.set("b", "2");
    m.set("a", "3"); 

    EXPECT_TRUE(m.contains("a"));
    EXPECT_TRUE(m.contains("b"));
    EXPECT_FALSE(m.contains("c"));

    std::string val;
    EXPECT_TRUE(m.get("a", val));
    EXPECT_EQ(val, "3");
    EXPECT_TRUE(m.get("b", val));
    EXPECT_EQ(val, "2");
    EXPECT_FALSE(m.get("c", val));

    EXPECT_TRUE(m.erase("a"));
    EXPECT_FALSE(m.contains("a"));
    EXPECT_FALSE(m.erase("a"));
}

TEST(HashMapBasic, ClearAndCopyMove) {
    HashMap m;
    m.set("x", "10");
    m.set("y", "20");

    HashMap copy = m;
    EXPECT_EQ(copy.size(), m.size());
    EXPECT_TRUE(copy.contains("x"));

    HashMap assigned;
    assigned = m;
    EXPECT_EQ(assigned.size(), m.size());

    HashMap moved = std::move(m);
    EXPECT_TRUE(moved.contains("x"));
    EXPECT_TRUE(moved.contains("y"));

    moved.clear();
    EXPECT_TRUE(moved.empty());
}

TEST(HashMapIO, SaveAndLoad) {
    HashMap m;
    m.set("k1", "v1");
    m.set("k2", "v2");
    ASSERT_TRUE(m.save_to_file("test_hashmap.txt"));

    HashMap other;
    ASSERT_TRUE(other.load_from_file("test_hashmap.txt"));
    std::string val;
    EXPECT_TRUE(other.get("k1", val));
    EXPECT_EQ(val, "v1");
    EXPECT_TRUE(other.get("k2", val));
    EXPECT_EQ(val, "v2");
}
