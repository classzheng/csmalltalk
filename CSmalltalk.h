// CSmalltalk.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PseuCmd
#include "Pseudo.h"
#include "FMacro.h"
#include "C57External.h"
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
	return True;
}
void flint(void) {
	ptop=0;
  	C57Object prt={
      .symbol="print:",
      .rdata="(lambda)", // Pseudo Lambda
  	  .path="Console",
  	  .mth=(Bytecode*){BRK},
  	  .mlt=9,
  	  .argsplit=CslPrint,
  	}; // Console Objects
    objPool[ptop++]=prt,sizeof(prt);
	return ;
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
# undef TRV TRV,
# undef CPY CPY,
# undef PRTF PRTF,
#endif
Bytecode* compile(CSmalltalk* model) { // Still writing...
	Bytecode* ObjFile=(Bytecode*)malloc(sizeof(Bytecode)*1024);
	for(i=0,ftop=0,lmt=0; i<$.etop; i++) {
		for(j=0; j<strlen($.excgo[i]); j++) {
			if($.excgo[i][j]=='[') break;
		}
		char obj[64],method[64],args[128];
		sscanf($.excgo[i]+j+1,"%s%s",obj,method);
		if(method[strlen(method)-1]==':') {
			for(k=0; k<strlen($.excgo[i]); k++) {
				if($.excgo[i][k]==':') break;
			}
			strcpy(args,substr($.excgo[i]+j+1,k,strlen($.excgo[i])));
			for(k=0; k<strlen(args); k++) {
				if(args[k]==':') {
					for(j=0; j<strlen(args); j++) 
						if(args[j]!=' ') break;
					break;
				}
			}
			for(k=strlen(args)-1; k>=0; k--) if(args[k]==']') {
				args[k]=0;
				break;
			}
		}
		if((!strcmp(obj,"NewObject"))&&(!strcmp(method,"symbol:"))) { // Program External
			NewObjSyb(ObjFile,args);
			continue;
		}
		if(obj[0]=='/'||args[0]=='[') { // Function-return
			if(obj[0]=='/') {
				j=ptop-1;
				sprintf(virtual.mem+virtual.mtop,"%s",args);
				ObjFile[lmt++]=IMM;
				ObjFile[lmt++]=virtual.mtop,virtual.mtop+=strlen(args);
				for(k=0; k<objPool[j].mlt; k++) {
					ObjFile[lmt++]=objPool[j].mth[k];
				}
			} else {
				parse(model);
				Bytecode* ret=compile(model);
				for(k=0; ; k++) {
					if(ret[k]==BRK) break;
					ObjFile[lmt++]=ret[k];
				}
			}
		}
		for(j=0; j<ptop; j++) {
			if((!strcmp(objPool[j].symbol,method))&&(!strcmp(objPool[j].path,obj))) {
				objPool[j].argsplit(ObjFile,args);
				break;
			}
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
