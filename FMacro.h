// FMacro.h
#pragma once
#include <setjmp.h>
#define True  1
#define False 0
#define C57P_MCRO (True)
#define TRYP_MCRO (True)

#if C57P_MCRO // CSmalltalk-parse Macro
# define regsgH(mt)   \
(                     \
  signal(SIGABRT,mt), \
  signal(SIGFPE,mt),  \
  signal(SIGILL,mt),  \
  signal(SIGINT,mt),  \
  signal(SIGSEGV,mt), \
  signal(SIGTERM,mt), \
  True                \
)
# define nil (NULL)
# ifdef NDEBUG
#  define C57LOG(...) return 0
# else
#  define C57LOG(...) fprintf(stdout,__VA_ARGS__)
# endif
#endif

#if TRYP_MCRO // Try-pack Macro
# define TRINT(EXP) jmp_buf EXP; typedef enum
# define TRY(EXP,JBRN) int JBRN=setjmp(EXP);if(!JBRN)
# define CATCH(JBRN,VAL) else if(JBRN==VAL)
# define THROW(EXP,VAL) (longjmp(EXP,VAL))
# define FINALLY() if(True)
#endif

#undef True
#undef False
#define FPARAM(argc,argv,env) signed argc,const char* argv[], const char* env[]
#define THBLOCK(...) if(True)
#define PARAM 0 +
#define C57Pair(type1,type2) \
struct {                    \
  type1 first;              \
  type2 second;             \
} 

typedef enum {
	False,
	True,
} Bool; // Bool Type

TRINT(C57Exp) {
	NORMAL, PROGRAM_ABORT,
	UNKNOWN, ENOUGH_MEM
} EXCEPT_VAL;

#define $ model->private
#define pc(n)     struct {n;}
#define detect ((short)-1)
typedef char* string;
typedef struct {
	char* rcode;
	short limit;
	string*sybl;
	Bool  next;
	struct {
		short* bracks;
		     int btop;
		string* excgo;
			 int etop;
	} private;
} CSmalltalk;
typedef struct {
	string   path;
	Bytecode*mth;
	short    mlt;
	string   rdata;
	string   symbol;
	void(*argsplit)(Bytecode*,char*,short);
} C57Object;
C57Object objPool[128];
