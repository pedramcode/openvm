CC = gcc
CC_FLAGS = -Wall -Werror -std=c99 -O3 -L$(BINDIR)

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
	@echo "building assember"
	@cd $(LIBDIR)/assembler && make
	@cp -r $(LIBDIR)/assembler/bin/* $(BINDIR)/

clean:
	@cd $(LIBDIR)/assembler && make clean
	@find $(BINDIR)/* -type f -not -name ".gitignore" -delete
	@find $(BLDDIR)/* -type f -not -name ".gitignore" -delete
	@echo "project cleaned"

run: build_assembler $(TARGET)
	@export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(BINDIR) && ./$(TARGET) $(args)

.PHONY: clean run