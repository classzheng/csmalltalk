// CSmalltalk.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PseuCmd
#include "Pseudo.h"
#include "FMacro.h"
char*substr(const char*str,int beg,int end) {
	char*sub=(char*)malloc((end-beg+1)*sizeof(char));
	for(unsigned i = 0; i<(end-beg+1); i++) {
		sub[i]=str[i+beg];
	}
	return sub;
}
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
void flint(CSmalltalk* model) {
	objPool=(C57Object*)malloc(sizeof(C57Object)*16),ptop=0;
  	Bytecode prtl[]={        // immt=string address
	  MOV AX,1,
	  ADD AX  ,   // immt=string addr+1 (pass \')
	  MOV AX,114, // While \0 end
	  PRTF AX,
	  MOV AX,0,
	  EXT AX,
	}; // PrintLambda
  	C57Object prt={
      .symbol="print:",
      .rdata="(lambda)", // Pseudo Lambda
  	  .path="Console",
  	  .mlt=15,
  	  .mth=prtl,
  	}; // Console Objects
    objPool[ptop++]=prt;
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
		if((!strcmp(obj,"Pussy"))&&(!strcmp(method,"symbol:"))) { // Program External
			char mark[12];
			sscanf(args,"%s",mark);
			C57Object mrk={
			  .symbol=mark+j+1,
			  .rdata="(null)",
			};
			objPool=(C57Object*)malloc(sizeof(C57Object)*(++ptop));
			objPool[ptop-1]=mrk;
			ObjFile[lmt++]=IMM;
			ObjFile[lmt++]=ptop-1;
			C57LOG("%s\n",args);
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
				for(k=0; k<ret; k++) {
					ObjFile[lmt++]=ret[k];
				}
			}
		}
		for(j=0; j<ptop; j++) {
			if((!strcmp(objPool[j].symbol,method))&&(!strcmp(objPool[j].path,obj))) {
				sprintf(virtual.mem+virtual.mtop,"%s",args);
				ObjFile[lmt++]=IMM;
				ObjFile[lmt++]=virtual.mtop,virtual.mtop+=strlen(args);
				for(k=0; k<objPool[j].mlt; k++) {
					ObjFile[lmt++]=objPool[j].mth[k];
				}
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
