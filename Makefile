# @(#)$Header$

BASEDIR= /usr/ih
BINDIR = $(BASEDIR)/bin
LIBDIR = $(BASEDIR)/lib
INCDIR = $(BASEDIR)/include
MANDIR = $(BASEDIR)/man
MANDIRPRG = $(MANDIR)/cat1
MANDIRLIB = $(MANDIR)/cat3
LIB    = $(LIBDIR)/libocal.a

CFLAGS = -O
MKDIR  = mkdir -p
CP     = cp -p
AR     = ar r

all:		libmd5.a md5

libmd5.a:	md5.o
		ar r libmd5.a md5.o

md5:		libmd5.a main.o
		$(CC) $(CFLAGS) -o md5 main.o -L. -lmd5

md5.o:		md5.c md5.h
main.o:		main.c md5.h

install:	md5.o md5 md5.1 md5.3
		if [ ! -d $(LIBDIR) ]; then $(MKDIR) $(LIBDIR); fi;
		if [ ! -d $(BINDIR) ]; then $(MKDIR) $(BINDIR); fi;
		if [ ! -d $(INCDIR) ]; then $(MKDIR) $(INCDIR); fi;
		if [ ! -d $(MANDIR) ]; then $(MKDIR) $(MANDIR); fi;
		if [ ! -d $(MANDIR)/cat1 ]; then $(MKDIR) $(MANDIR)/cat1; fi;
		if [ ! -d $(MANDIR)/cat3 ]; then $(MKDIR) $(MANDIR)/cat3; fi;
		$(AR) $(LIB) md5.o
		$(CP) md5   $(BINDIR)/md5
		$(CP) md5.h $(INCDIR)/md5.h
		$(CP) md5.1 $(MANDIR)/cat1/md5.1
		$(CP) md5.3 $(MANDIR)/cat3/md5.3

files:
		@echo md5.c md5.h main.c Makefile md5.1 md5.3 | tr " " "\012"

clean:
		rm -f *.o core

clobber:	clean
		rm -f md5 libmd5.a

