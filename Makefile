override CFLAGS += -Wall -Wextra -O3

SRCS=$(wildcard src/bsmp/c/*.c) $(wildcard src/bsmp/c/md5/*.c)
DEPS=$(wildcard src/bsmp/c/*.h) $(wildcard src/bsmp/c/md5/*.h) $(wildcard include/bsmp/*.h)
OBJS=$(SRCS:.c=.o)

LN = ln

HDRS = include/bsmp/bsmp.h include/bsmp/server.h include/bsmp/client.h
INSTALL ?= /usr/bin/install
INSTALL_FLAGS = -c -m 644
LDCONFIG ?= /sbin/ldconfig
PREFIX ?= /usr
LDIR = $(PREFIX)/lib
IDIR = $(PREFIX)/include/bsmp
SOVERSION = 1

override CFLAGS += -I include/

.phony: all install clean distclean

all: libbsmp.a libbsmp.so

install: libbsmp.a libbsmp.so $(HDRS)
	$(INSTALL) $(INSTALL_FLAGS) libbsmp.a libbsmp.so.$(SOVERSION) libbsmp.so $(LDIR)
	$(LDCONFIG) -n $(LDIR)
	mkdir -p $(IDIR)
	$(INSTALL) $(INSTALL_FLAGS) $(HDRS) $(IDIR)

libbsmp.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libbsmp.so: $(OBJS)
	$(CC) -shared -Wl,-soname,$@.$(SOVERSION) -o $@.$(SOVERSION) $(OBJS)
	$(LN) -s $@.$(SOVERSION) $@

%.o: %.c $(DEPS)
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)

clean:
	@- $(RM) libbsmp.a libbsmp.so.$(SOVERSION) libbsmp.so $(OBJS)

uninstall:
	$(RM) $(LDIR)/libbsmp.a $(LDIR)/libbsmp.so $(LDIR)/libbsmp.so.$(SOVERSION)
	$(RM) -r $(IDIR)

distclean: clean
