IDIR=../headers
CC=gcc
CFLAGS=-I$(IDIR) -Wall -Wextra -std=c99 -g

ODIR=obj

LIBS=-lm

#_DEPS = 
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c #$(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
		rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
