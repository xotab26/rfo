OS = Linux

VERSION = 0.1.0
CC      = g++
CFLAGS  = -g3 -Wall -Werror -pedantic -Wextra -Wno-unknown-pragmas -D_DEBUG -DUNIX_BUILD -DMYSQLPP_MYSQL_HEADERS_BURIED -DMYSQLPP_NO_DLL -DVERSION=\"$(VERSION)\" -std=c++11
CXXFLAGS= 
LDFLAGS = -lpthread -ldl -lmysqlclient -lnsl -lz -lm -I/usr/include/cppconn -I/usr/include -L/usr/lib -I/usr/include/mysql -L/usr/lib/mysql

BUILDDIR  = .
SOURCEDIR = source
HEADERDIR = source

SOURCES := $(shell find $(SOURCEDIR) -name '*.c')
SOURCES2 := $(shell find $(SOURCEDIR) -name '*.cpp')
COBJ := $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%.o))
CPPOBJ := $(addprefix $(BUILDDIR)/,$(SOURCES2:%.cpp=%.o))

OBJECTS = $(CPPOBJ) $(COBJ)

NAME = rfoemu
BINARY = rfoemu

ECHO = echo
RM = rm -rf
MKDIR = mkdir
INSTALL = install

.PHONY: all clean setup

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BINARY) $(LDFLAGS)

$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(dir $<) -c $< -o $@ $(LDFLAGS)
	
$(BUILDDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(dir $<) -c $< -o $@ $(CXXFLAGS) $(LDFLAGS)

setup:
	$(MKDIR) -p $(BUILDDIR)

install:
	$(INSTALL) -m 755 -o 0 -g 0 -d $(DESTDIR)/usr/local/bin/
	$(INSTALL) -m 755 -o 0 -g 0 $(BINARY) $(DESTDIR)/usr/local/bin/$(BINARY)

remove:
	$(RM) -f $(BINARY) $(DESTDIR)/usr/local/bin/$(BINARY)

clean:
	$(RM) $(BINARY) $(OBJECTS)

distclean: clean


help:
	@$(ECHO) "Targets:"
	@$(ECHO) "all     - build/compile what is necessary"
	@$(ECHO) "clean   - cleanup old .o and .bin"
	@$(ECHO) "install - not yet fully supported"
	@$(ECHO) "remove  - not yet fully supported"