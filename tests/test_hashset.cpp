#include <gtest/gtest.h>
#include "massive.h"
#include <sstream>

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

TEST(HashSetIO, BinarySaveLoad) {
    HashSet s;
    s.insert("alpha");
    s.insert("beta");
    s.insert("gamma");
    ASSERT_TRUE(s.save_to_binary("test_hashset.bin"));

    HashSet loaded;
    ASSERT_TRUE(loaded.load_from_binary("test_hashset.bin"));
    EXPECT_EQ(loaded.size(), 3u);
    EXPECT_TRUE(loaded.contains("alpha"));
    EXPECT_TRUE(loaded.contains("beta"));
    EXPECT_TRUE(loaded.contains("gamma"));
}

TEST(HashSetIO, PrintToStream) {
    HashSet s;
    s.insert("x");
    s.insert("y");
    std::ostringstream oss;
    s.print(oss);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(HashSetIO, PrintEmpty) {
    HashSet s;
    std::ostringstream oss;
    s.print(oss);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(HashSetOps, MoveAssignment) {
    HashSet s1;
    s1.insert("foo");
    s1.insert("bar");

    HashSet s2;
    s2.insert("baz");
    s2 = std::move(s1);

    EXPECT_TRUE(s2.contains("foo"));
    EXPECT_TRUE(s2.contains("bar"));
}

TEST(HashSetOps, SelfMoveAssignment) {
    HashSet s;
    s.insert("test");
    HashSet* ptr = &s;
    s = std::move(*ptr);
    EXPECT_TRUE(s.contains("test"));
}

TEST(HashSetOps, SelfCopyAssignment) {
    HashSet s;
    s.insert("test");
    s = s;
    EXPECT_TRUE(s.contains("test"));
}

TEST(HashSetOps, HashCollisions) {
    HashSet s(2);

    s.insert("a");
    s.insert("b");
    s.insert("c");
    s.insert("d");

    EXPECT_TRUE(s.contains("a"));
    EXPECT_TRUE(s.contains("b"));
    EXPECT_TRUE(s.contains("c"));
    EXPECT_TRUE(s.contains("d"));

    EXPECT_TRUE(s.erase("b"));
    EXPECT_FALSE(s.contains("b"));
    EXPECT_TRUE(s.contains("a"));
    EXPECT_TRUE(s.contains("c"));
    EXPECT_TRUE(s.contains("d"));

    EXPECT_TRUE(s.erase("d"));
    EXPECT_FALSE(s.contains("d"));
}

TEST(HashSetOps, EraseFromMiddleOfChain) {
    HashSet s(2);

    s.insert("item1");
    s.insert("item2");
    s.insert("item3");

    EXPECT_TRUE(s.erase("item2"));
    EXPECT_FALSE(s.contains("item2"));
    EXPECT_TRUE(s.contains("item1"));
    EXPECT_TRUE(s.contains("item3"));
}

TEST(HashSetOps, ClearWithZeroSize) {
    HashSet s(1009);
    s.insert("a");
    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_GT(s.table_size(), 0u);
}
