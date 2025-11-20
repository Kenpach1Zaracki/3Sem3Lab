#include <gtest/gtest.h>
#include "massive.h"

TEST(HashSetBasic, NewSetEmpty) {
    HashSet s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
    EXPECT_GT(s.table_size(), 0u);
}

TEST(HashSetBasic, InsertContainsErase) {
    HashSet s;
    EXPECT_TRUE(s.insert("a"));
    EXPECT_TRUE(s.insert("b"));
    EXPECT_FALSE(s.insert("a"));

    EXPECT_TRUE(s.contains("a"));
    EXPECT_TRUE(s.contains("b"));
    EXPECT_FALSE(s.contains("c"));

    EXPECT_TRUE(s.erase("a"));
    EXPECT_FALSE(s.contains("a"));
    EXPECT_FALSE(s.erase("a"));
}

TEST(HashSetBasic, ClearAndCopyMove) {
    HashSet s;
    s.insert("x");
    s.insert("y");

    HashSet copy = s;
    EXPECT_EQ(copy.size(), s.size());
    EXPECT_TRUE(copy.contains("x"));

    HashSet assigned;
    assigned = s;
    EXPECT_EQ(assigned.size(), s.size());

    HashSet moved = std::move(s);
    EXPECT_TRUE(moved.contains("x"));
    EXPECT_TRUE(moved.contains("y"));

    moved.clear();
    EXPECT_TRUE(moved.empty());
}

TEST(HashSetIO, SaveAndLoad) {
    HashSet s;
    s.insert("one");
    s.insert("two");
    ASSERT_TRUE(s.save_to_file("test_hashset.txt"));

    HashSet other;
    ASSERT_TRUE(other.load_from_file("test_hashset.txt"));
    EXPECT_TRUE(other.contains("one"));
    EXPECT_TRUE(other.contains("two"));
}
