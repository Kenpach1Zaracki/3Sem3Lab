#include <gtest/gtest.h>
#include "onel.h"
#include <sstream>

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

TEST(LinkedListIO, BinarySaveLoad) {
    LinkedList list;
    list.push_back("item1");
    list.push_back("item2");
    list.push_back("item3");
    ASSERT_TRUE(list.save_to_binary("test_list.bin"));

    LinkedList loaded;
    ASSERT_TRUE(loaded.load_from_binary("test_list.bin"));
    EXPECT_EQ(loaded.size(), 3u);
    EXPECT_EQ(*loaded.at(0), "item1");
    EXPECT_EQ(*loaded.at(1), "item2");
    EXPECT_EQ(*loaded.at(2), "item3");
}

TEST(LinkedListIO, PrintToStream) {
    LinkedList list;
    list.push_back("a");
    list.push_back("b");
    list.push_back("c");
    std::ostringstream oss;
    list.print(oss);
    std::string output = oss.str();
    EXPECT_EQ(output, "a b c");
}

TEST(LinkedListOps, ConstAccessorsReturnNull) {
    const LinkedList emptyList;
    EXPECT_EQ(emptyList.front(), nullptr);
    EXPECT_EQ(emptyList.back(), nullptr);
    EXPECT_EQ(emptyList.at(0), nullptr);
}

TEST(LinkedListOps, MutableAccessors) {
    LinkedList list;
    list.push_back("test");

    std::string* frontPtr = list.front();
    ASSERT_NE(frontPtr, nullptr);
    *frontPtr = "modified";
    EXPECT_EQ(*list.front(), "modified");
}

TEST(LinkedListOps, InsertAfterTail) {
    LinkedList list;
    list.push_back("a");
    list.push_back("b");

    EXPECT_TRUE(list.insert_after(1, "c"));
    EXPECT_EQ(*list.back(), "c");
    EXPECT_EQ(list.size(), 3u);
}

TEST(LinkedListOps, InsertBeforeTail) {
    LinkedList list;
    list.push_back("a");
    list.push_back("c");

    EXPECT_TRUE(list.insert_before(1, "b"));
    EXPECT_EQ(*list.at(1), "b");
    EXPECT_EQ(list.size(), 3u);
}

TEST(LinkedListOps, EraseAfterUpdatingTail) {
    LinkedList list;
    list.push_back("a");
    list.push_back("b");

    EXPECT_TRUE(list.erase_after(0));
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(*list.back(), "a");
    EXPECT_EQ(list.front(), list.back());
}

TEST(LinkedListOps, EraseBeforeTailWithTwoElements) {
    LinkedList list;
    list.push_back("a");
    list.push_back("b");

    EXPECT_TRUE(list.erase_before_tail());
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(*list.front(), "b");
}

TEST(LinkedListOps, EraseBeforeTailWithMultipleElements) {
    LinkedList list;
    list.push_back("a");
    list.push_back("b");
    list.push_back("c");
    list.push_back("d");

    EXPECT_TRUE(list.erase_before_tail());
    EXPECT_EQ(list.size(), 3u);
    EXPECT_EQ(*list.at(2), "d");
    EXPECT_FALSE(list.index_of("c") >= 0);
}

TEST(LinkedListOps, EraseBeforeTailEmpty) {
    LinkedList list;
    EXPECT_FALSE(list.erase_before_tail());

    list.push_back("a");
    EXPECT_FALSE(list.erase_before_tail());
}

TEST(LinkedListOps, EraseFirstUpdatingTail) {
    LinkedList list;
    list.push_back("a");
    list.push_back("b");

    EXPECT_TRUE(list.erase_first("b"));
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(*list.back(), "a");
    EXPECT_EQ(list.front(), list.back());
}

TEST(LinkedListOps, EraseFirstNotFound) {
    LinkedList list;
    list.push_back("a");
    list.push_back("b");

    EXPECT_FALSE(list.erase_first("x"));
    EXPECT_EQ(list.size(), 2u);
}

TEST(LinkedListOps, EraseAllUpdatingTail) {
    LinkedList list;
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

TEST(LinkedListOps, EraseAllFromHead) {
    LinkedList list;
    list.push_back("x");
    list.push_back("x");
    list.push_back("a");

    int removed = list.erase_all("x");
    EXPECT_EQ(removed, 2);
    EXPECT_EQ(*list.front(), "a");
}

TEST(LinkedListOps, SelfCopyAssignment) {
    LinkedList list;
    list.push_back("a");
    list = list;
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(*list.front(), "a");
}

TEST(LinkedListOps, SelfMoveAssignment) {
    LinkedList list;
    list.push_back("a");
    LinkedList* ptr = &list;
    list = std::move(*ptr);
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(*list.front(), "a");
}

TEST(LinkedListOps, PushBackToEmptyList) {
    LinkedList list;
    list.push_back("first");
    EXPECT_EQ(*list.front(), "first");
    EXPECT_EQ(*list.back(), "first");
    EXPECT_EQ(list.size(), 1u);
}

TEST(LinkedListOps, PopFrontMakesEmpty) {
    LinkedList list;
    list.push_back("a");
    EXPECT_TRUE(list.pop_front());
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.front(), nullptr);
    EXPECT_EQ(list.back(), nullptr);
}
