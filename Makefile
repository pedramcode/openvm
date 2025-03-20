CC = gcc
CC_FLAGS = -Wall -Werror -std=c99 -O3 -L$(BINDIR)
MAKEFLAGS += --no-print-directory

SRCDIR = src
INCDIR = include
LIBDIR = lib
BLDDIR = build
BINDIR = bin

CC_LIB_FLAGS = -L$(BINDIR) -lassembler -I$(LIBDIR)/assembler/include

TARGET = $(BINDIR)/vm.out

SOURCES = $(shell find $(SRCDIR) -type f -name "*.c")
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BLDDIR)/%.o, $(SOURCES))

all: build_assembler $(TARGET) 

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -o $@ $^ $(CC_LIB_FLAGS)

$(BLDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(CC_LIB_FLAGS) -I$(INCDIR) -c -o $@ $<

build_assembler:
	$(MAKE) -C $(LIBDIR)/assembler
	@cp -r $(LIBDIR)/assembler/bin/* $(BINDIR)/

clean:
	@$(MAKE) clean -C $(LIBDIR)/assembler
	@find $(BINDIR)/* -type f -not -name ".gitignore" -exec rm -rf {} +
	@find $(BLDDIR)/* -type f -not -name ".gitignore" -exec rm -rf {} +
	@echo "project cleaned"

install:
	@$(MAKE) install -C $(LIBDIR)/assembler
	@cp $(TARGET) /usr/local/bin/$(notdir $(TARGET))

uninstall:
	@$(MAKE) uninstall -C $(LIBDIR)/assembler
	@rm -rf /usr/local/bin/$(notdir $(TARGET))

run: build_assembler $(TARGET)
	@export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(BINDIR) && ./$(TARGET) $(args)

.PHONY: clean run install uninstall build_assembler