# TODO: shall build on windows too.

# compiler and compile flags
# instructions on installing latest gcc compiler can be found here
# https://medium.com/@xersendo/moving-to-c-26-how-to-build-and-set-up-gcc-15-1-on-ubuntu-f52cc9173fa0
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -O2 -pthread

INC_DIRS = -Isrc -Isrc/backend -Isrc/frontend -Isrc/frontend/parser -Isrc/frontend/ast -Isrc/intermediate -Isrc/utils
TARGET_NAME = minipylisp
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
TARGET = $(BUILD_DIR)/$(TARGET_NAME)

# find sources using shell command
SRCS = $(shell find src -name "*.cpp")

# mirror src for the objects
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(patsubst %.cpp, $(OBJ_DIR)/%.d, $(SRCS))
OBJ_SUBDIRS = $(sort $(dir $(OBJS)))

.PHONY: all clean test run rebuild directories

# the default target
all: directories $(TARGET)

# build
$(BUILD_DIR):
	@echo "creating build directory: $@"
	@mkdir -p $@

# build/obj
$(OBJ_DIR):
	@echo "creating object directory: $@"
	@mkdir -p $@

# all sub directories
$(OBJ_SUBDIRS):
	@echo "creating object subdirectory: $@"
	@mkdir -p $@

directories: $(BUILD_DIR) $(OBJ_DIR) $(OBJ_SUBDIRS)

# link
$(TARGET): $(OBJS)
	@echo "Linking $(TARGET_NAME)..."
	$(CXX) $(OBJS) $(CXXFLAGS) -o $@
	@echo "Build complete! Executable located at: $@"

# compile 
$(OBJ_DIR)/src/%.o: src/%.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c $< -o $@ -MMD -MP

VPATH = src:src/backend:src/frontend:src/frontend/parser:src/frontend/ast:src/intermediate:src/utils
-include $(DEPS)

# Gtest sources
GTEST_DIR := lib/googletest
GTEST_SRC := $(GTEST_DIR)/src/gtest-all.cc
GTEST_OBJ := $(BUILD_DIR)/gtest-all.o
GTEST_INC := -I$(GTEST_DIR) -I$(GTEST_DIR)/include

#  build gtest as object file 
$(GTEST_OBJ): $(GTEST_SRC)
	@echo "Building Google Test ..."
	$(CXX) $(CXXFLAGS) $(GTEST_INC) -c $< -o $@

# Test sources
TEST_SRC := $(wildcard tests/*.cpp)
TEST_OBJ := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(TEST_SRC)))

# compile test files
$(BUILD_DIR)/%.o: tests/%.cpp
	@echo "Compiling test: $<"
	$(CXX) $(CXXFLAGS) $(GTEST_INC) $(INC_DIRS) -c $< -o $@

# link gtest
TEST_BIN := test_runner

# only one main
APP_OBJS_NO_MAIN := $(filter-out $(OBJ_DIR)/src/main.o, $(OBJS))
$(TEST_BIN): $(TEST_OBJ) $(APP_OBJS_NO_MAIN) $(GTEST_OBJ)
	@echo "Linking test runner..."
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test: $(TEST_BIN)
	@echo "Running tests..."
	./$(TEST_BIN)

clean:
	@echo "removing artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean done."

run: $(TARGET)
	@echo "starting $(TARGET_NAME)..."
	@./$(TARGET)

rebuild: clean all
