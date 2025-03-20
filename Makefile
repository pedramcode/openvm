CC = gcc
CC_FLAGS = -Wall -Werror -std=c99 -O3

SRCDIR = src
INCDIR = include
LIBDIR = libs
BLDDIR = build
BINDIR = bin

TARGET = $(BINDIR)/vm.out

SOURCES = $(shell find $(SRCDIR) -type f -name "*.c")
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BLDDIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -o $@ $^

$(BLDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -I$(INCDIR) -c -o $@ $<

clean:
	@rm -rf $(BLDDIR)/*
	@rm -rf $(BINDIR)/*
	@echo "project cleaned"

run: $(TARGET)
	@./$(TARGET) $(args)

.PHONY: clean run