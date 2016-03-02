#ifndef KS_STATES_H
#define KS_STATES_H

typedef enum {
	VALID,
	INVALIDSYNTAX,
	INVALIDPROBLEM,
	INVALIDSOL,
	INCOMPLETE,
	SOLVED
} KSState;

static inline char *stringFromState(KSState s)
{
    static char *strings[] = {
    	"VALID",
    	"INVALIDSYNTAX",
    	"INVALIDPROBLEM",
    	"INVALIDSOL",
    	"INCOMPLETE",
    	"SOLVED"
    };

    return strings[s];
}

#endif
