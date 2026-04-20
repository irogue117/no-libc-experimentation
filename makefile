.PHONY: all app debug test clean lint

CC       := musl-gcc
INCLUDES = -Iinclude
CFLAGS   := -Wall -Wextra -ffreestanding -nostdlib -nostartfiles -fstack-protector-all $(INCLUDES)
DEBUGFLAGS := -g3 -O0 -DDEBUG
SRCDIR   := src
BUILDDIR := build
DEBUGDIR := build/debug

rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SOURCES := $(call rwildcard,$(SRCDIR)/,*.c)

OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
DEBUG_OBJECTS := $(patsubst $(SRCDIR)/%.c,$(DEBUGDIR)/%.o,$(SOURCES))

all: app

app: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(BUILDDIR)/app

debug: $(DEBUG_OBJECTS)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $^ -o $(DEBUGDIR)/app

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEBUGDIR)/%.o: $(SRCDIR)/%.c | $(DEBUGDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $@

$(DEBUGDIR):
	mkdir -p $@

# test: app
# 	./$(BUILDDIR)/app --test

lint:
	cppcheck $(SRCDIR)/

clean:
	rm -rf $(BUILDDIR)
