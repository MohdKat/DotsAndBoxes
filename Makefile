CC        := gcc
CFLAGS    := -std=c99 -Wall -Wextra -Wpedantic -g -Iinclude
SRC_DIR   := src
BUILD_DIR := build
LOG_DIR   := docs/debugging
TARGET    := dots_and_boxes

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all run valgrind debug clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	mkdir -p $(LOG_DIR)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$(LOG_DIR)/valgrind_$(or $(USER),$(shell whoami))_$(shell date +%Y%m%d_%H%M%S).log ./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)
