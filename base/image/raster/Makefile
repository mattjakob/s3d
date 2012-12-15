ROOT = ../..
LIBDIR = $(ROOT)/lib
INCLUDE =$(ROOT)/include

CC = gcc
CFLAGS = -g -I$(INCLUDE)

HEADERS = image.h rasterfile.h
OBJECTS = image.o sunras.o
LIBNAME = libimg.a


$(LIBNAME): $(HEADERS) $(OBJECTS)
	ar ruv $(LIBNAME) $(OBJECTS)
	ranlib $(LIBNAME)

install: $(LIBNAME)
	mv $(LIBNAME) $(LIBDIR)
	cp $(HEADERS) $(INCLUDE)

clean:
	rm -f *.o *~ $(LIBNAME)

