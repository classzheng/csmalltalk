// CSmalltalk.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
/** CSmalltalk基础对象
 * Pussy -   定义对象符号
 * symbol -  Pussy子对象
 **/
void flint(CSmalltalk* model) {
	objPool=(C57Object*)malloc(sizeof(C57Object)*2);
  	C57Object psy={
  	  .symbol="Pussy",
  	  .rdata="(pussy)"
  	},syb={
      .symbol="symbol",
      .rdata="(lambda)",
  	  .path="Pussy>"
  	}; // The SIMPLEST C57OBJECT!!!
    objPool[0]=psy;
    objPool[1]=syb;
    ptop=2;
	return ;
}
short top;
Bytecode* compile(CSmalltalk* model) { // Still writing...
	Bytecode* ObjFile=(Bytecode*)malloc(sizeof(Bytecode)*1024);
	for(i=0; i<$.etop; i++) {
		for(j=0; j<strlen($.excgo[i]); j++) {
			if($.excgo[i][j]=='[') break;
		}
		char obj[64],method[64];
		sscanf($.excgo+i+j+1,"%s%s",obj,method);
		if(method[strlen(method)-1]==':') {
			
		}
		if((!strcmp(obj,"Pussy"))&&(!strcmp(method,"symbol"))) {
			
		}
		if(obj[0]='/') { // Function-return
			
		}
	}
	return ObjFile;
}
char beef[128];
char* _Mul(const char* rawcc) {
	strcpy(beef,rawcc);
	return beef;
}
#undef $
