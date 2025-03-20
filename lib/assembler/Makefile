CC = gcc
CC_FLAGS = -Wall -Werror -std=c99 -fpic -O3

SRCDIR = src
INCDIR = include
BLDDIR = build
BINDIR = bin

TARGET = $(BINDIR)/libassembler.so

SOURCES = $(shell find $(SRCDIR) -type f -name "*.c")
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BLDDIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -shared -o $@ $^

$(BLDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -I$(INCDIR) -c -o $@ $<

clean:
	@find $(BINDIR)/* -type f -not -name ".gitignore" -exec rm -rf {} +
	@find $(BLDDIR)/* -type f -not -name ".gitignore" -exec rm -rf {} +

.PHONY: clean 