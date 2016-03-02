SRCDIR = src
IDIR = $(SRCDIR)/headers

CC = gcc
CFLAGS = -I$(IDIR) -Wall -Wextra -std=c99 -g

CHECKERDIR = $(SRCDIR)/Checker
SOLVERDIR = $(SRCDIR)/Solver

_ODIR = obj
CODIR = $(CHECKERDIR)/$(_ODIR)
SODIR = $(SOLVERDIR)/$(_ODIR)

LIBS=-lm

_DEPS = KillerSudoku.h SudokuStates.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_CHECKOBJ = KillerSudokuChecker.o
CHECKOBJ = $(patsubst %,$(CODIR)/%,$(_CHECKOBJ))

_CHECKOBJ' = gridParser.o ksDataSetup.o solParser.o checkInvalidSol.o checkComplete.o assessInputFiles.o
CHECKOBJ' = $(patsubst %,$(CODIR)/%,$(_CHECKOBJ'))

_SOLVEOBJ = KillerSudokuSolver.o sudokuOperations.o solveSudoku.o
SOLVEOBJ = $(patsubst %,$(SODIR)/%,$(_SOLVEOBJ)) $(CHECKOBJ')

%.o: ../%.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)
		
all: KillerSudokuChecker KillerSudokuSolver

KillerSudokuChecker: $(CHECKOBJ) $(CHECKOBJ')
		gcc -o $@ $^ $(CFLAGS) $(LIBS)
		
KillerSudokuSolver: $(SOLVEOBJ)
		gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
		rm -f $(CODIR)/*.o *~ core $(INCDIR)/*~