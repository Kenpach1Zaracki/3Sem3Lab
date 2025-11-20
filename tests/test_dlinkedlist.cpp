#include <gtest/gtest.h>
#include "twolink.h"

TEST(DLinkedListBasic, NewListEmpty) {
    DLinkedList list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
    EXPECT_EQ(list.front(), nullptr);
    EXPECT_EQ(list.back(), nullptr);
}

TEST(DLinkedListBasic, PushPopFrontBack) {
    DLinkedList list;
    list.push_back("b");
    list.push_front("a");
    list.push_back("c");

    EXPECT_EQ(list.size(), 3u);
    ASSERT_NE(list.front(), nullptr);
    ASSERT_NE(list.back(), nullptr);
    EXPECT_EQ(*list.front(), "a");
    EXPECT_EQ(*list.back(), "c");

    EXPECT_TRUE(list.pop_front());
    EXPECT_TRUE(list.pop_back());
    EXPECT_EQ(list.size(), 1u);
}

TEST(DLinkedListOps, InsertEraseByIndex) {
    DLinkedList list;
    list.push_back("a"); 
    list.push_back("c"); 

    EXPECT_TRUE(list.insert_after(0, "b"));  
    EXPECT_EQ(*list.at(1), "b");

    EXPECT_TRUE(list.insert_before(0, "start")); 
    EXPECT_EQ(*list.at(0), "start");

    EXPECT_TRUE(list.erase_after(0)); 
    EXPECT_EQ(*list.at(1), "b");

    EXPECT_TRUE(list.erase_before(2)); 
    EXPECT_EQ(list.size(), 2u);
}

TEST(DLinkedListOps, EraseByValue) {
    DLinkedList list;
    list.push_back("x");
    list.push_back("y");
    list.push_back("x");

    EXPECT_EQ(list.index_of("y"), 1);
    EXPECT_TRUE(list.erase_first("x"));
    EXPECT_EQ(list.index_of("x"), 1);

    int removed = list.erase_all("x");
    EXPECT_EQ(removed, 1);
    EXPECT_EQ(list.index_of("x"), -1);
}

TEST(DLinkedListCopyMove, CopyAndMoveWork) {
    DLinkedList a;
    a.push_back("1");
    a.push_back("2");

    DLinkedList b = a;
    EXPECT_EQ(b.size(), 2u);

    DLinkedList c;
    c = a;
    EXPECT_EQ(c.size(), 2u);

    DLinkedList d = std::move(a);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_TRUE(a.empty());

    DLinkedList e;
    e = std::move(d);
    EXPECT_EQ(e.size(), 2u);
    EXPECT_TRUE(d.empty());
}

TEST(DLinkedListIO, SaveAndLoad) {
    DLinkedList list;
    list.push_back("aa");
    list.push_back("bb");
    ASSERT_TRUE(list.save_to_file("test_dlist.txt"));

    DLinkedList other;
    ASSERT_TRUE(other.load_from_file("test_dlist.txt"));
    EXPECT_EQ(other.size(), 2u);
    EXPECT_EQ(*other.at(0), "aa");
    EXPECT_EQ(*other.at(1), "bb");
}
