CXX      = g++
CXXFLAGS = -std=c++17
LDFLAGS  =

SRC_DIR   = src
TEST_DIR  = tests
BENCH_DIR = bench


GTEST_ROOT  = /opt/homebrew/opt/googletest
BENCH_ROOT  = /opt/homebrew/opt/google-benchmark

CXXFLAGS += -I$(SRC_DIR) -I$(GTEST_ROOT)/include -I$(BENCH_ROOT)/include
LDFLAGS  += -L$(GTEST_ROOT)/lib -L$(BENCH_ROOT)/lib


SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/onelinkedclass.cpp \
       $(SRC_DIR)/twolinkedclass.cpp \
       $(SRC_DIR)/queueclass.cpp \
       $(SRC_DIR)/stackclass.cpp \
       $(SRC_DIR)/massiveclass.cpp \
       $(SRC_DIR)/hashclass.cpp \
       $(SRC_DIR)/bstree.cpp

OBJS   = $(SRCS:.cpp=.o)
TARGET = app


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

TEST_SRCS = $(TEST_DIR)/test_main.cpp \
            $(TEST_DIR)/test_linkedlist.cpp \
            $(TEST_DIR)/test_dlinkedlist.cpp \
            $(TEST_DIR)/test_queue.cpp \
            $(TEST_DIR)/test_stack.cpp \
            $(TEST_DIR)/test_hashset.cpp \
            $(TEST_DIR)/test_hashmap.cpp \
            $(TEST_DIR)/test_bstree.cpp

TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_BIN  = tests_bin

GTEST_LIBS = -lgtest -lpthread

tests: CXXFLAGS += --coverage -O0
tests: LDFLAGS  += --coverage
tests: $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS) $(filter-out $(SRC_DIR)/main.o,$(OBJS))
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIBS) $(LDFLAGS)

run_tests: tests
	./$(TEST_BIN)

coverage: run_tests
	gcovr --root . --html-details -o coverage.html --filter $(SRC_DIR)/ --gcov-ignore-errors=no_working_dir_found

BENCH_SRCS = $(BENCH_DIR)/bench_main.cpp \
             $(BENCH_DIR)/bench_linkedlist.cpp \
             $(BENCH_DIR)/bench_dlinkedlist.cpp \
             $(BENCH_DIR)/bench_queue.cpp \
             $(BENCH_DIR)/bench_stack.cpp \
             $(BENCH_DIR)/bench_hashset.cpp \
             $(BENCH_DIR)/bench_hashmap.cpp \
             $(BENCH_DIR)/bench_bstree.cpp

BENCH_OBJS = $(BENCH_SRCS:.cpp=.o)
BENCH_BIN  = bench_bin
BENCH_LIBS = -lbenchmark -lpthread

bench: $(BENCH_BIN)

$(BENCH_BIN): $(BENCH_OBJS) $(filter-out $(SRC_DIR)/main.o,$(OBJS))
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BENCH_LIBS) $(LDFLAGS)

run_bench: bench
	./$(BENCH_BIN)

clean:
	rm -f $(OBJS) $(TARGET) \
	      $(TEST_OBJS) $(TEST_BIN) \
	      $(BENCH_OBJS) $(BENCH_BIN)

	find . \( -name '*.html' -o -name '*.css' -o -name '*.txt' -o -name '*.o' -o -name '*.gcda' -o -name '*.gcno' \) -type f -delete || true

