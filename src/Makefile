PREFIX ?= /usr
DESTDIR ?=
BINDIR ?= $(PREFIX)/bin

CC ?= cc
CFLAGS ?= -O3
CFLAGS += -std=gnu99 -Wall -Wextra -MMD -MP

TARGET := gennearaccount
SOURCES := main.c gennearaccount.c keypair.c seed.c ge.c fe.c sha512.c
OBJECTS := $(SOURCES:.c=.o)

all: $(TARGET)
.DEFAULT_GOAL := all

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(TARGET) *.o *.d

install: $(TARGET)
	install -d "$(DESTDIR)$(BINDIR)"
	install -m 0755 "$(TARGET)" "$(DESTDIR)$(BINDIR)/$(TARGET)"

.PHONY: all clean install

-include *.d
