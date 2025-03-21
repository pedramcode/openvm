CC = gcc
CC_FLAGS = -Wall -Werror -std=c99 -O3

SRCD = src
INCD = include src
BLDD = build
BIND = bin
TARGET = $(BIND)/openvm

SOURCES = $(shell find $(SRCD) -type f -name "*.c")
OBJECTS = $(patsubst $(SRCD)/%.c,$(BLDD)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -o $@ $^

$(BLDD)/%.o: $(SRCD)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(addprefix -I, $(INCD)) -c -o $@ $<

run: $(TARGET)
	@./$(TARGET)

clean:
	@rm -rf bin
	@rm -rf build

.PHONY: clean run