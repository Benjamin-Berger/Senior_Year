# Compiler
CC = gcc
# Header files (.h) if any
HEADERS = 
# Source files (.c)
SOURCES = sample.c
# Object files (.o)
OBJECTS = sample.o 
# Program name
PROGRAM = sample
#
BINDIR = .
#
EXTRA_DEFINES = 
# C debug flags (-g == debug info, -O == optimize)
CDEBUGFLAGS = -g
#
#

#

DEFINES = $(EXTRA_DEFINES)
INCLUDES = -I. -I/usr/include -I/usr/local/include -I/usr/sfw/include



CFLAGS = $(DEFINES) $(INCLUDES) $(CDEBUGFLAGS)

LDFLAGS =  -L. -L /usr/lib/ -L /usr/local/lib/ -L /opt/local/lib/ /opt/local/lib/libtiff.so -lm 

$(BINDIR)/$(PROGRAM) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(PROGRAM) $(OBJECTS) $(LDFLAGS) 

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
#
#fl:     $(OBJECTS)
#        $(CC) $(CFLAGS) -o $@ $(INCLUDES) $(OBJECTS) $(LDFLAGS)

#
# build objects
#
$(OBJECTS) : $(HEADERS)
#
clean:
	rm -f *.o tok




