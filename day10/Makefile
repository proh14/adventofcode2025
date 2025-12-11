CXX := g++
CXXFLAGS := -Wall -Wextra -MMD -MP -std=c++17 -g
SRC_DIR := ./src
BUILD_DIR := ./build
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/src/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)
EXES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%, $(SRCS))

all: $(EXES)

$(shell mkdir -p $(BUILD_DIR)/src)

$(BUILD_DIR)/%: $(BUILD_DIR)/src/%.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lz3

$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
