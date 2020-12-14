# Usefuls dirs
IDIR	= .
ODIR	= build
LDIR	=

# Target name
TARGET = dungeon

# Files to compile
_DEPS =
_OBJ = main.o

# External lib dependencies
LIBS=-lSDL2_image

# Compiler and compiler params
CC		= gcc
CFLAGS	= -I$(IDIR) -fstack-protector `sdl2-config --libs --cflags`

# Dark magic
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Building specified .o file
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Build all, yay !
all: $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS) $(LIBS)

# Makeing sure that we can still clean even if a file named clean exist
.PHONY: clean

# Cleanin our shit
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
