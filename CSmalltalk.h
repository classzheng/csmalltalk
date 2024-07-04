// CSmalltalk.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PseuCmd
#include "Pseudo.h"
#include "FMacro.h"
#define $ model->private
#define detect ((short)-1)
#define pc(n)     struct {n;}
typedef char* string;
typedef struct {
	char* rcode;
	short limit;
	string*sybl;
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
} C57Object;
char*substr(const char*str,int beg,int end) {
	char*sub=(char*)malloc((end-beg+1)*sizeof(char));
	for(unsigned i = 0; i<(end-beg+1); i++) {
		sub[i]=str[i+beg];
	}
	return sub;
}
short i,j,k,h,w,cnt0,cnt1,temp,ptop=0;
C57Object* objPool;
Bool parse(CSmalltalk* model) {
	if(model->limit==detect) model->limit=strlen(model->rcode);
	$.bracks=(short*)malloc(model->limit*sizeof(short));
	$.btop=0;
	for(i=0; i<(model->limit); i++) {
		if(model->rcode[i]=='[') 
		 $.bracks[$.btop++]= +i;
		if(model->rcode[i]==']')
		 $.bracks[$.btop++]= -i;
	}
	$.excgo=(string*)malloc($.btop*sizeof(string)/2);
	$.etop=0;
	for(j=0,cnt0=0; j<$.btop;j++) {
	  if($.bracks[j]<0) {
	  	cnt1=0;
	  	for(i=j; i>=0; i--) {
	  	  if($.bracks[i]>=0) cnt1++;
	  	  if(cnt1==cnt0+1) {
	  	    $.excgo[$.etop++]=substr(model->rcode,$.bracks[i],-$.bracks[j]);
	  	    for(k=$.bracks[i];k<=-$.bracks[j];k++) {
	  	    	model->rcode[k]='/';
	  	    }
			break;
	  	  }
	  	}
	  	cnt0++;
	  }
	}
	for(j=0; j<$.btop;j++) {
		C57LOG(" - %d\n",$.bracks[j]);
	}
	return True;
}
void flint(CSmalltalk* model) {
	objPool=(C57Object*)malloc(sizeof(C57Object)*2);
  	C57Object psy={
  	  .symbol="Pussy",
  	  .rdata="(pussy)"
  	},syb={
      .symbol="symbol",
      .rdata="(lambda)", // Pseudo Lambda
  	  .path="Pussy>"
  	}; // The SIMPLEST C57OBJECT!!!
    objPool[0]=psy;
    objPool[1]=syb;
    ptop=2;
	return ;
}
short top,lmt;
Bytecode* compile(CSmalltalk* model) { // Still writing...
	Bytecode* ObjFile=(Bytecode*)malloc(sizeof(Bytecode)*1024);
	for(i=0,lmt=0; i<$.etop; i++) {
		for(j=0; j<strlen($.excgo[i]); j++) {
			if($.excgo[i][j]=='[') break;
		}
		char obj[64],method[64],args[128];
		sscanf($.excgo+i+j+1,"%s%s",obj,method);
		if(method[strlen(method)-1]==':') {
			for(k=0; k<strlen($.excgo)-i-j; k++) {
				if(!strcmp(substr($.excgo,k,k+strlen(method)),method)) break;
			}
			k+=strlen(method);
			strcpy(args,substr($.excgo,k,strlen($.excgo)-1)); // Split ARGS
		}
		if((!strcmp(obj,"Pussy"))&&(!strcmp(method,"symbol"))) { // Program External
			char mark[12];
			sscanf(args,"%s",mark);
			C57Object mrk={
			  .symbol=mark,
			  .rdata="(null)",
			};
			objPool=(C57Object*)malloc(sizeof(C57Object)*(++ptop));
			objPool[ptop-1]=mrk;
			Bytecode ret[]={
#			ifdef PseuCmd
			  IMM ptop-1,
#			else
			  IMM,ptop-1,
#			endif
			}; // Set return val
			NeutralInt(ret,2);
			lmt+=2;
			continue;
		}
		if(obj[0]='/') { // Function-return
			
		}
	}
	return ObjFile;
}
#ifdef PseuCmd
# undef XOR XOR,
# undef NOT NOT,
# undef ADD ADD,
# undef SUB SUB,
# undef MUL MUL,
# undef DIV DIV,
# undef MOV MOV,
# undef IMM IMM,
# undef EXT EXT,
# undef CPY CPY,
# undef PRTF PRTF,
#endif
void dumpPseu(Bytecode* area) {
	return ;
}
char beef[128];
char* _Mul(const char* rawcc) {
	strcpy(beef,rawcc);
	return beef;
}
#undef $
