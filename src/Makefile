IDIR=../headers
CC=gcc
CFLAGS=-I$(IDIR) -Wall -Wextra -std=c99 -g

ODIR=obj

LIBS=-lm

_DEPS = ../headers
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = KSChecker.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

KillerSudokuChecker: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
		rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
