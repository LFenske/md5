# $Header$

BINDIR = /usr/local/bin
LIBDIR = /usr/local/lib
INCDIR = /usr/local/include
MANDIR = /usr/local/man/iemtools
MANDIRPRG = $(MANDIR)/cat1
MANDIRLIB = $(MANDIR)/cat3
LIB    = $(LIBDIR)/libiem.a

all:		libmd5.a md5

libmd5.a:	md5.o
		ar r libmd5.a md5.o

md5:		libmd5.a main.o
		$(CC) $(CFLAGS) -o md5 main.o -L. -lmd5

md5.o:		md5.c md5.h
main.o:		main.c md5.h

install:	md5.o md5 md5.1 md5.3
		if [ ! -d $(LIBDIR) ]; then mkdir $(LIBDIR); fi;
		if [ ! -d $(BINDIR) ]; then mkdir $(BINDIR); fi;
		if [ ! -d $(INCDIR) ]; then mkdir $(INCDIR); fi;
		if [ ! -d $(MANDIR) ]; then mkdir $(MANDIR); fi;
		if [ ! -d $(MANDIR)/cat1 ]; then mkdir $(MANDIR)/cat1; fi;
		if [ ! -d $(MANDIR)/cat3 ]; then mkdir $(MANDIR)/cat3; fi;
		ar r $(LIB) md5.o
		cp -p md5   $(BINDIR)/md5
		cp -p md5.h $(INCDIR)/md5.h
		cp -p md5.1 $(MANDIR)/cat1/md5.1
		cp -p md5.3 $(MANDIR)/cat3/md5.3

files:
		@echo md5.c md5.h main.c Makefile md5.1 md5.3 | tr " " "\012"

clean:
		rm -f *.o core

clobber:	clean
		rm -f md5 libmd5.a

