#include <gtest/gtest.h>
#include "onel.h"

TEST(LinkedListBasic, NewListIsEmpty) {
    LinkedList list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
    EXPECT_EQ(list.front(), nullptr);
    EXPECT_EQ(list.back(), nullptr);
}

TEST(LinkedListBasic, PushFrontBack) {
    LinkedList list;
    list.push_back("b");
    list.push_front("a");
    list.push_back("c");

    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 3u);
    ASSERT_NE(list.front(), nullptr);
    ASSERT_NE(list.back(), nullptr);
    EXPECT_EQ(*list.front(), "a");
    EXPECT_EQ(*list.back(), "c");
    EXPECT_EQ(*list.at(1), "b");
    EXPECT_EQ(list.at(10), nullptr); 
}

TEST(LinkedListBasic, PopFrontBack) {
    LinkedList list;
    list.push_back("a");
    list.push_back("b");
    list.push_back("c");

    EXPECT_TRUE(list.pop_front());
    EXPECT_EQ(list.size(), 2u);
    ASSERT_NE(list.front(), nullptr);
    EXPECT_EQ(*list.front(), "b");

    EXPECT_TRUE(list.pop_back());
    EXPECT_EQ(list.size(), 1u);
    ASSERT_NE(list.back(), nullptr);
    EXPECT_EQ(*list.back(), "b");

    EXPECT_TRUE(list.pop_back());
    EXPECT_TRUE(list.empty());
    EXPECT_FALSE(list.pop_back());
    EXPECT_FALSE(list.pop_front());
}

TEST(LinkedListOps, InsertAndEraseByIndex) {
    LinkedList list;
    list.push_back("a");
    list.push_back("c"); 

    EXPECT_TRUE(list.insert_after(0, "b")); 
    EXPECT_EQ(*list.at(1), "b");

    EXPECT_TRUE(list.insert_before(0, "start")); 
    EXPECT_EQ(*list.at(0), "start");

    EXPECT_FALSE(list.insert_after(100, "x"));
    EXPECT_FALSE(list.insert_before(100, "y"));

    EXPECT_TRUE(list.erase_after(0)); 
    EXPECT_EQ(*list.at(1), "b");

    EXPECT_TRUE(list.erase_before_tail()); 
    EXPECT_EQ(list.size(), 2u);
    EXPECT_EQ(*list.at(0), "start");
    EXPECT_EQ(*list.at(1), "c");
}

TEST(LinkedListOps, EraseByValue) {
    LinkedList list;
    list.push_back("x");
    list.push_back("y");
    list.push_back("x");
    list.push_back("z");
    list.push_back("x");

    EXPECT_EQ(list.index_of("y"), 1);
    EXPECT_EQ(list.index_of("no"), -1);

    EXPECT_TRUE(list.erase_first("x"));
    EXPECT_EQ(*list.front(), "y");

    int removed = list.erase_all("x");
    EXPECT_EQ(removed, 2);
    EXPECT_EQ(list.index_of("x"), -1);
}

TEST(LinkedListCopyMove, CopyAndMoveWork) {
    LinkedList a;
    a.push_back("1");
    a.push_back("2");

    LinkedList b = a;         
    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(*b.front(), "1");
    EXPECT_EQ(*b.back(), "2");

    LinkedList c;
    c.push_back("x");
    c = a;                   
    EXPECT_EQ(c.size(), 2u);
    EXPECT_EQ(*c.front(), "1");

    LinkedList d = std::move(a); 
    EXPECT_EQ(d.size(), 2u);
    EXPECT_TRUE(a.empty());

    LinkedList e;
    e = std::move(d);          
    EXPECT_EQ(e.size(), 2u);
    EXPECT_TRUE(d.empty());
}

TEST(LinkedListIO, SaveAndLoad) {
    LinkedList list;
    list.push_back("alpha");
    list.push_back("beta");
    ASSERT_TRUE(list.save_to_file("test_list.txt"));

    LinkedList loaded;
    ASSERT_TRUE(loaded.load_from_file("test_list.txt"));
    EXPECT_EQ(loaded.size(), 2u);
    EXPECT_EQ(*loaded.at(0), "alpha");
    EXPECT_EQ(*loaded.at(1), "beta");
}
