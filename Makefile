CXX      = g++
CXXFLAGS = -std=c++17
LDFLAGS  =

SRC_DIR   = src
TEST_DIR  = tests
BENCH_DIR = bench
BUILD_DIR = build
OBJ_DIR   = $(BUILD_DIR)/obj
BIN_DIR   = $(BUILD_DIR)/bin
COV_DIR   = $(BUILD_DIR)/coverage


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

OBJS   = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/app


all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR) $(COV_DIR):
	mkdir -p $@

TEST_SRCS = $(TEST_DIR)/test_main.cpp \
            $(TEST_DIR)/test_linkedlist.cpp \
            $(TEST_DIR)/test_dlinkedlist.cpp \
            $(TEST_DIR)/test_queue.cpp \
            $(TEST_DIR)/test_stack.cpp \
            $(TEST_DIR)/test_hashset.cpp \
            $(TEST_DIR)/test_hashmap.cpp \
            $(TEST_DIR)/test_bstree.cpp

TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/test_%.o,$(TEST_SRCS))
TEST_COV_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/cov_%.o,$(filter-out $(SRC_DIR)/main.cpp,$(SRCS)))
TEST_BIN  = $(BIN_DIR)/tests_bin

GTEST_LIBS = -lgtest -lpthread

tests: $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS) $(TEST_COV_OBJS) | $(BIN_DIR)
	$(CXX) -std=c++17 --coverage -I$(SRC_DIR) -o $@ $^ $(GTEST_LIBS) -L$(GTEST_ROOT)/lib --coverage

$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -std=c++17 --coverage -O0 -I$(SRC_DIR) -I$(GTEST_ROOT)/include -c $< -o $@

$(OBJ_DIR)/cov_%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -std=c++17 --coverage -O0 -I$(SRC_DIR) -c $< -o $@

run_tests: tests
	./$(TEST_BIN)

coverage: tests | $(COV_DIR)
	-./$(TEST_BIN)
	gcovr --root . --html-details -o $(COV_DIR)/coverage.html --filter $(SRC_DIR)/ --gcov-ignore-errors=no_working_dir_found
	@echo "Coverage report generated: $(COV_DIR)/coverage.html"

BENCH_SRCS = $(BENCH_DIR)/bench_main.cpp \
             $(BENCH_DIR)/bench_linkedlist.cpp \
             $(BENCH_DIR)/bench_dlinkedlist.cpp \
             $(BENCH_DIR)/bench_queue.cpp \
             $(BENCH_DIR)/bench_stack.cpp \
             $(BENCH_DIR)/bench_hashset.cpp \
             $(BENCH_DIR)/bench_hashmap.cpp \
             $(BENCH_DIR)/bench_bstree.cpp

BENCH_OBJS = $(patsubst $(BENCH_DIR)/%.cpp,$(OBJ_DIR)/bench_%.o,$(BENCH_SRCS))
BENCH_BIN  = $(BIN_DIR)/bench_bin
BENCH_LIBS = -lbenchmark -lpthread

bench: $(BENCH_BIN)

$(BENCH_BIN): $(BENCH_OBJS) $(filter-out $(OBJ_DIR)/main.o,$(OBJS)) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BENCH_LIBS) $(LDFLAGS)

$(OBJ_DIR)/bench_%.o: $(BENCH_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run_bench: bench
	./$(BENCH_BIN)

clean:
	rm -rf $(BUILD_DIR)
	find . \( -name '*.gcda' -o -name '*.gcno' -o -name '*.gcov' \) -type f -delete || true

.PHONY: all tests run_tests coverage bench run_bench clean

