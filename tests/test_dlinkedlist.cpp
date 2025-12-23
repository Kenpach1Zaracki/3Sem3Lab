#include <gtest/gtest.h>
#include "twolink.h"
#include <sstream>

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

TEST(DLinkedListIO, BinarySaveLoad) {
    DLinkedList list;
    list.push_back("data1");
    list.push_back("data2");
    list.push_back("data3");
    ASSERT_TRUE(list.save_to_binary("test_dlist.bin"));

    DLinkedList loaded;
    ASSERT_TRUE(loaded.load_from_binary("test_dlist.bin"));
    EXPECT_EQ(loaded.size(), 3u);
    EXPECT_EQ(*loaded.at(0), "data1");
    EXPECT_EQ(*loaded.at(1), "data2");
    EXPECT_EQ(*loaded.at(2), "data3");
}

TEST(DLinkedListIO, PrintToStream) {
    DLinkedList list;
    list.push_back("x");
    list.push_back("y");
    list.push_back("z");
    std::ostringstream oss;
    list.print(oss);
    std::string output = oss.str();
    EXPECT_EQ(output, "x y z");
}

TEST(DLinkedListOps, ConstAccessorsReturnNull) {
    const DLinkedList emptyList;
    EXPECT_EQ(emptyList.front(), nullptr);
    EXPECT_EQ(emptyList.back(), nullptr);
    EXPECT_EQ(emptyList.at(0), nullptr);
}

TEST(DLinkedListOps, MutableAccessors) {
    DLinkedList list;
    list.push_back("test");

    std::string* frontPtr = list.front();
    ASSERT_NE(frontPtr, nullptr);
    *frontPtr = "changed";
    EXPECT_EQ(*list.front(), "changed");
}

TEST(DLinkedListOps, InsertAfterTail) {
    DLinkedList list;
    list.push_back("a");
    list.push_back("b");

    EXPECT_TRUE(list.insert_after(1, "c"));
    EXPECT_EQ(*list.back(), "c");
    EXPECT_EQ(list.size(), 3u);
}

TEST(DLinkedListOps, InsertBeforeTail) {
    DLinkedList list;
    list.push_back("a");
    list.push_back("c");

    EXPECT_TRUE(list.insert_before(1, "b"));
    EXPECT_EQ(*list.at(1), "b");
    EXPECT_EQ(list.size(), 3u);
}

TEST(DLinkedListOps, EraseAfterUpdatingTail) {
    DLinkedList list;
    list.push_back("a");
    list.push_back("b");

    EXPECT_TRUE(list.erase_after(0));
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(*list.back(), "a");
}

TEST(DLinkedListOps, EraseBeforeUpdatingHead) {
    DLinkedList list;
    list.push_back("a");
    list.push_back("b");

    EXPECT_TRUE(list.erase_before(1));
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(*list.front(), "b");
}

TEST(DLinkedListOps, EraseBeforeInvalid) {
    DLinkedList list;
    EXPECT_FALSE(list.erase_before(0));

    list.push_back("a");
    EXPECT_FALSE(list.erase_before(0));
    EXPECT_FALSE(list.erase_before(5));
}

TEST(DLinkedListOps, EraseFirstUpdatingTail) {
    DLinkedList list;
    list.push_back("a");
    list.push_back("b");

    EXPECT_TRUE(list.erase_first("b"));
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(*list.back(), "a");
}

TEST(DLinkedListOps, EraseFirstNotFound) {
    DLinkedList list;
    list.push_back("a");
    list.push_back("b");

    EXPECT_FALSE(list.erase_first("x"));
    EXPECT_EQ(list.size(), 2u);
}

TEST(DLinkedListOps, EraseAllUpdatingTail) {
    DLinkedList list;
    list.push_back("x");
    list.push_back("a");
    list.push_back("x");
    list.push_back("x");

    int removed = list.erase_all("x");
    EXPECT_EQ(removed, 3);
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(*list.front(), "a");
    EXPECT_EQ(*list.back(), "a");
}

TEST(DLinkedListOps, EraseAllFromHead) {
    DLinkedList list;
    list.push_back("x");
    list.push_back("x");
    list.push_back("a");

    int removed = list.erase_all("x");
    EXPECT_EQ(removed, 2);
    EXPECT_EQ(*list.front(), "a");
}

TEST(DLinkedListOps, SelfCopyAssignment) {
    DLinkedList list;
    list.push_back("a");
    list = list;
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(*list.front(), "a");
}

TEST(DLinkedListOps, SelfMoveAssignment) {
    DLinkedList list;
    list.push_back("a");
    DLinkedList* ptr = &list;
    list = std::move(*ptr);
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(*list.front(), "a");
}

TEST(DLinkedListOps, PushBackToEmptyList) {
    DLinkedList list;
    list.push_back("first");
    EXPECT_EQ(*list.front(), "first");
    EXPECT_EQ(*list.back(), "first");
    EXPECT_EQ(list.size(), 1u);
}

TEST(DLinkedListOps, PopFrontMakesEmpty) {
    DLinkedList list;
    list.push_back("a");
    EXPECT_TRUE(list.pop_front());
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.front(), nullptr);
    EXPECT_EQ(list.back(), nullptr);
}

TEST(DLinkedListOps, PopBackMakesEmpty) {
    DLinkedList list;
    list.push_back("a");
    EXPECT_TRUE(list.pop_back());
    EXPECT_TRUE(list.empty());
}

TEST(DLinkedListOps, IndexOfNotFound) {
    DLinkedList list;
    list.push_back("a");
    list.push_back("b");
    EXPECT_EQ(list.index_of("c"), -1);
}
