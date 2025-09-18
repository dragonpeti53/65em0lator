CC = g++
FLAGS = -Wall -Wpedantic -Werror -O2
SRC_DIR = src
TEST_DIR = test
TEST_SOURCES = $(SRC_DIR)/cpu.cpp $(SRC_DIR)/memory.cpp $(SRC_DIR)/test.cpp
BUILD_DIR = build
BUILD_SOURCES = $(SRC_DIR)/cpu.cpp $(SRC_DIR)/memory.cpp $(SRC_DIR)/video.cpp

test: $(TEST_SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(TEST_SOURCES) -o $(BUILD_DIR)/test

build: $(BUILD_SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(BUILD_SOURCES) -o $(BUILD_DIR)/main

clean:
	rm -rf $(BUILD_DIR)