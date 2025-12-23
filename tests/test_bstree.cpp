#include <gtest/gtest.h>
#include "bstree.h"
#include <sstream>

TEST(BSTreeBasic, NewTreeEmpty) {
    BSTree t;
    EXPECT_TRUE(t.empty());
    EXPECT_EQ(t.size(), 0u);
    EXPECT_EQ(t.height(), 0);
    EXPECT_EQ(t.min_value(), nullptr);
    EXPECT_EQ(t.max_value(), nullptr);
}

TEST(BSTreeBasic, InsertContainsMinMax) {
    BSTree t;
    EXPECT_TRUE(t.insert("b"));
    EXPECT_TRUE(t.insert("a"));
    EXPECT_TRUE(t.insert("c"));
    EXPECT_FALSE(t.insert("b")); 

    EXPECT_EQ(t.size(), 3u);
    EXPECT_TRUE(t.contains("a"));
    EXPECT_TRUE(t.contains("b"));
    EXPECT_TRUE(t.contains("c"));
    EXPECT_FALSE(t.contains("d"));

    const std::string* mn = t.min_value();
    const std::string* mx = t.max_value();
    ASSERT_NE(mn, nullptr);
    ASSERT_NE(mx, nullptr);
    EXPECT_EQ(*mn, "a");
    EXPECT_EQ(*mx, "c");
    EXPECT_GE(t.height(), 2);
}

TEST(BSTreeBasic, EraseDifferentCases) {
    BSTree t;
    t.insert("b");
    t.insert("a");
    t.insert("c");
    t.insert("d");

    EXPECT_TRUE(t.erase("d"));
    EXPECT_FALSE(t.contains("d"));

    EXPECT_TRUE(t.erase("c"));
    EXPECT_FALSE(t.contains("c"));

    EXPECT_TRUE(t.erase("b"));
    EXPECT_FALSE(t.contains("b"));

    EXPECT_TRUE(t.contains("a"));
    EXPECT_EQ(t.size(), 1u);
}

TEST(BSTreeCopyMove, CopyAndMoveWork) {
    BSTree a;
    a.insert("1");
    a.insert("0");
    a.insert("2");

    BSTree b = a;
    EXPECT_EQ(b.size(), a.size());
    EXPECT_TRUE(b.contains("2"));

    BSTree c;
    c = a;
    EXPECT_EQ(c.size(), a.size());

    BSTree d = std::move(a);
    EXPECT_TRUE(d.contains("1"));
    EXPECT_TRUE(a.empty());

    BSTree e;
    e = std::move(d);
    EXPECT_TRUE(e.contains("1"));
    EXPECT_TRUE(d.empty());
}

TEST(BSTreeIO, SaveAndLoad) {
    BSTree t;
    t.insert("b");
    t.insert("a");
    t.insert("c");
    ASSERT_TRUE(t.save_to_file("test_bst.txt"));

    BSTree other;
    ASSERT_TRUE(other.load_from_file("test_bst.txt"));
    EXPECT_TRUE(other.contains("a"));
    EXPECT_TRUE(other.contains("b"));
    EXPECT_TRUE(other.contains("c"));
}

TEST(BSTreeOps, ClearTree) {
    BSTree t;
    t.insert("a");
    t.insert("b");
    t.insert("c");
    EXPECT_EQ(t.size(), 3u);
    t.clear();
    EXPECT_TRUE(t.empty());
    EXPECT_EQ(t.size(), 0u);
}

TEST(BSTreePrint, PrintInorder) {
    BSTree t;
    t.insert("b");
    t.insert("a");
    t.insert("c");
    std::ostringstream os;
    t.print_inorder(os);
    EXPECT_FALSE(os.str().empty());
}

TEST(BSTreePrint, PrintStructure) {
    BSTree t;
    t.insert("b");
    t.insert("a");
    t.insert("c");
    std::ostringstream os;
    t.print_structure(os);
    EXPECT_FALSE(os.str().empty());
}

TEST(BSTreeIO, BinarySaveLoad) {
    BSTree t;
    t.insert("x");
    t.insert("y");
    t.insert("z");
    ASSERT_TRUE(t.save_to_binary("test_bst.bin"));

    BSTree other;
    ASSERT_TRUE(other.load_from_binary("test_bst.bin"));
    EXPECT_EQ(other.size(), 3u);
    EXPECT_TRUE(other.contains("x"));
    EXPECT_TRUE(other.contains("y"));
    EXPECT_TRUE(other.contains("z"));
}

TEST(BSTreeErase, NodeWithLeftChildOnly) {
    BSTree t;
    t.insert("c");
    t.insert("a");
    t.insert("b");
    EXPECT_TRUE(t.erase("c"));
    EXPECT_FALSE(t.contains("c"));
    EXPECT_TRUE(t.contains("a"));
    EXPECT_TRUE(t.contains("b"));
}

TEST(BSTreeErase, NodeWithTwoChildren) {
    BSTree t;
    t.insert("b");
    t.insert("a");
    t.insert("d");
    t.insert("c");
    t.insert("e");
    EXPECT_TRUE(t.erase("d"));
    EXPECT_FALSE(t.contains("d"));
    EXPECT_TRUE(t.contains("c"));
    EXPECT_TRUE(t.contains("e"));
}
