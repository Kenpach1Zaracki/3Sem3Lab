#include <gtest/gtest.h>
#include "stack.h"
#include <sstream>

TEST(StackBasic, NewStackEmpty) {
    Stack st;
    EXPECT_TRUE(st.empty());
    EXPECT_EQ(st.size(), 0u);
    EXPECT_EQ(st.peek(), nullptr);
}

TEST(StackBasic, PushPopLIFO) {
    Stack st;
    st.push("a");
    st.push("b");
    st.push("c");

    EXPECT_EQ(st.size(), 3u);
    ASSERT_NE(st.peek(), nullptr);
    EXPECT_EQ(*st.peek(), "c");

    std::string out;
    ASSERT_TRUE(st.pop(&out));
    EXPECT_EQ(out, "c");
    ASSERT_TRUE(st.pop(&out));
    EXPECT_EQ(out, "b");
    ASSERT_TRUE(st.pop(&out));
    EXPECT_EQ(out, "a");
    EXPECT_TRUE(st.empty());
    EXPECT_FALSE(st.pop(&out));
}

TEST(StackCopyMove, CopyAndMoveWork) {
    Stack a;
    a.push("1");
    a.push("2");

    Stack b = a;
    EXPECT_EQ(b.size(), 2u);

    Stack c;
    c = a;
    EXPECT_EQ(c.size(), 2u);

    Stack d = std::move(a);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_TRUE(a.empty());

    Stack e;
    e = std::move(d);
    EXPECT_EQ(e.size(), 2u);
    EXPECT_TRUE(d.empty());
}

TEST(StackIO, SaveAndLoad) {
    Stack st;
    st.push("low");
    st.push("high");
    ASSERT_TRUE(st.save_to_file("test_stack.txt"));

    Stack other;
    ASSERT_TRUE(other.load_from_file("test_stack.txt"));
    EXPECT_EQ(other.size(), 2u);
    ASSERT_NE(other.peek(), nullptr);
    EXPECT_EQ(*other.peek(), "high");
}

TEST(StackOps, PeekConstVersion) {
    Stack st;
    st.push("test");
    const Stack& cst = st;
    ASSERT_NE(cst.peek(), nullptr);
    EXPECT_EQ(*cst.peek(), "test");
}

TEST(StackOps, ClearStack) {
    Stack st;
    st.push("a");
    st.push("b");
    st.push("c");
    EXPECT_EQ(st.size(), 3u);
    st.clear();
    EXPECT_TRUE(st.empty());
    EXPECT_EQ(st.size(), 0u);
}

TEST(StackIO, PrintToStream) {
    Stack st;
    st.push("a");
    st.push("b");
    std::ostringstream os;
    st.print(os);
    EXPECT_FALSE(os.str().empty());
}

TEST(StackIO, BinarySaveLoad) {
    Stack st;
    st.push("x");
    st.push("y");
    st.push("z");
    ASSERT_TRUE(st.save_to_binary("test_stack.bin"));

    Stack other;
    ASSERT_TRUE(other.load_from_binary("test_stack.bin"));
    EXPECT_EQ(other.size(), 3u);
    ASSERT_NE(other.peek(), nullptr);
    EXPECT_EQ(*other.peek(), "z");
}
