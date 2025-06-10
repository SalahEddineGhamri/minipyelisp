# TODO: shall build on windows too.

# compiler and language
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -O2

INC_DIRS = -Isrc -Isrc/backend -Isrc/frontend -Isrc/intermediate -Isrc/utils
TARGET_NAME = minipylisp
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
TARGET = $(BUILD_DIR)/$(TARGET_NAME)

SRCS = $(shell find src -name "*.cpp")

OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(patsubst %.cpp, $(OBJ_DIR)/%.d, $(SRCS))
OBJ_SUBDIRS = $(sort $(dir $(OBJS)))

.PHONY: all clean run rebuild directories
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

VPATH = src:src/backend:src/frontend:src/intermediate:src/utils
-include $(DEPS)

clean:
	@echo "removing artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean done."

run: $(TARGET)
	@echo "starting $(TARGET_NAME)..."
	@./$(TARGET)

rebuild: clean all
