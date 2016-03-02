SRCDIR = src
IDIR = $(SRCDIR)/headers

CC = gcc
CFLAGS = -I$(IDIR) -Wall -Wextra -std=c99 -g

CHECKERDIR = $(SRCDIR)/Checker
#SOLVERDIR = $(SRCDIR)/Solver

_ODIR = obj
CODIR = $(CHECKERDIR)/$(_ODIR)
#SODIR = $(SOLVERDIR)/$(_ODIR)

LIBS=-lm

_DEPS = KillerSudokuChecker.h SudokuStates.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_CHECKOBJ = KillerSudokuChecker.o gridParser.o ksDataSetup.o solParser.o checkInvalidSol.o checkComplete.o assessInputFiles.o
CHECKOBJ = $(patsubst %,$(CODIR)/%,$(_CHECKOBJ))


%.o: ../%.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

KillerSudokuChecker: $(CHECKOBJ)
		gcc -o KillerSudokuChecker $^ $(CFLAGS) $(LIBS)

clean:
		rm -f $(CODIR)/*.o *~ core $(INCDIR)/*~