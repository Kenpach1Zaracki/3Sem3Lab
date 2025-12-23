#include <gtest/gtest.h>
#include "hash.h"
#include <sstream>

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

TEST(HashMapIO, BinarySaveLoad) {
    HashMap m;
    m.set("key1", "value1");
    m.set("key2", "value2");
    m.set("key3", "value3");
    ASSERT_TRUE(m.save_to_binary("test_hashmap.bin"));

    HashMap loaded;
    ASSERT_TRUE(loaded.load_from_binary("test_hashmap.bin"));
    EXPECT_EQ(loaded.size(), 3u);
    std::string val;
    EXPECT_TRUE(loaded.get("key1", val));
    EXPECT_EQ(val, "value1");
    EXPECT_TRUE(loaded.get("key2", val));
    EXPECT_EQ(val, "value2");
    EXPECT_TRUE(loaded.get("key3", val));
    EXPECT_EQ(val, "value3");
}

TEST(HashMapIO, PrintToStream) {
    HashMap m;
    m.set("a", "1");
    m.set("b", "2");
    std::ostringstream oss;
    m.print(oss);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(HashMapOps, MoveAssignment) {
    HashMap m1;
    m1.set("x", "10");
    m1.set("y", "20");

    HashMap m2;
    m2.set("z", "30");
    m2 = std::move(m1);

    EXPECT_TRUE(m2.contains("x"));
    EXPECT_TRUE(m2.contains("y"));
    std::string val;
    EXPECT_TRUE(m2.get("x", val));
    EXPECT_EQ(val, "10");
}

TEST(HashMapOps, SelfMoveAssignment) {
    HashMap m;
    m.set("a", "1");
    HashMap* ptr = &m;
    m = std::move(*ptr);
    EXPECT_TRUE(m.contains("a"));
}

TEST(HashMapOps, SelfCopyAssignment) {
    HashMap m;
    m.set("a", "1");
    m = m;
    EXPECT_TRUE(m.contains("a"));
}

TEST(HashMapOps, HashCollisions) {
    HashMap m(2);

    m.set("a", "1");
    m.set("b", "2");
    m.set("c", "3");
    m.set("d", "4");

    EXPECT_TRUE(m.contains("a"));
    EXPECT_TRUE(m.contains("b"));
    EXPECT_TRUE(m.contains("c"));
    EXPECT_TRUE(m.contains("d"));

    std::string val;
    EXPECT_TRUE(m.get("a", val));
    EXPECT_EQ(val, "1");
    EXPECT_TRUE(m.get("c", val));
    EXPECT_EQ(val, "3");

    EXPECT_TRUE(m.erase("b"));
    EXPECT_FALSE(m.contains("b"));
    EXPECT_TRUE(m.contains("a"));
    EXPECT_TRUE(m.contains("c"));
    EXPECT_TRUE(m.contains("d"));

    EXPECT_TRUE(m.erase("d"));
    EXPECT_FALSE(m.contains("d"));
}

TEST(HashMapOps, EraseFromMiddleOfChain) {
    HashMap m(2);

    m.set("key1", "val1");
    m.set("key2", "val2");
    m.set("key3", "val3");

    EXPECT_TRUE(m.erase("key2"));
    EXPECT_FALSE(m.contains("key2"));
    EXPECT_TRUE(m.contains("key1"));
    EXPECT_TRUE(m.contains("key3"));
}

TEST(HashMapOps, ClearWithZeroBuckets) {
    HashMap m(1024);
    m.set("a", "1");
    m.clear();
    EXPECT_TRUE(m.empty());
    EXPECT_GT(m.bucket_count(), 0u);
}
