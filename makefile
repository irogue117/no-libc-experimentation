.PHONY: all app test clean lint

CC       := musl-gcc
CFLAGS   := -Wall -Wextra -ffreestanding -nostdlib -nostartfiles -fstack-protector-all
SRCDIR   := src
BUILDDIR := build

rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SOURCES := $(call rwildcard,$(SRCDIR)/,*.c)

OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

all: app

app: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(BUILDDIR)/app

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $@

# test: app
# 	./$(BUILDDIR)/app --test

lint:
	cppcheck $(SRCDIR)/

clean:
	rm -rf $(BUILDDIR)
