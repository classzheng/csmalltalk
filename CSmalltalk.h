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
  	C57Object nwo={
      .symbol="NewObject",
      .rdata="(object)",
  	},syb={
  	  .symbol="symbol:",
  	  .rdata="(lambda)",
  	  .path="NewObject",
  	  .mth=(Bytecode*){BRK},
  	  .mlt=1,
  	  .argsplit=NewObjSyb,
  	}; // NewObject System
    objPool[ptop++]=nwo,sizeof(nwo),objPool[ptop++]=syb,sizeof(syb);
    C57Object csl={
      .symbol="Console",
      .rdata="(object)",  	}; // Console Objects
  	objPool[ptop++]=csl,sizeof(csl);
  	C57Object prt={
      .symbol="print:",
      .rdata="(lambda)", // Pseudo Lambda
  	  .path="Console",
  	  .mth=(Bytecode*){BRK},
  	  .mlt=1,
  	  .argsplit=CslPrint,
  	}; // Console Objects
    objPool[ptop++]=prt,sizeof(prt);
  	C57Object scn={
      .symbol="scanf:",
      .rdata="(lambda)", // Pseudo Lambda
  	  .path="Console",
  	  .mth=(Bytecode*){BRK},
  	  .mlt=1,
  	  .argsplit=CslScanf,
  	}; // Console Objects
    objPool[ptop++]=scn,sizeof(scn);
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
# undef RET RET,
# undef TRV TRV,
# undef CPY CPY,
# undef PRTF PRTF,
#endif
Bytecode* compile(CSmalltalk* model) { // Still writing...
	Bytecode* ObjFile=(Bytecode*)malloc(sizeof(Bytecode)*1024);
	for(i=0,ftop=0,lmt=0; i<$.etop; i++) {
		for(j=0; j<strlen($.excgo[i]); j++) {
			if($.excgo[i][j]=='['&&$.excgo[i][j+1]!='[') break;
		}
		char obj[64],method[64],args[128];
		sscanf($.excgo[i]+j+1,"%s%s",obj,method);
		if(!strcmp(obj,"bytecode:")) {
			char btcode[1145],tp=j+strlen(obj)+1;
			while(True) {
				sscanf($.excgo[i]+tp,"%s",btcode);
				if(!strcmp("NOP",btcode)) _Obj NOP;
				if(!strcmp("XOR",btcode)) _Obj XOR;
				if(!strcmp("ADD",btcode)) _Obj ADD;
				if(!strcmp("MUL",btcode)) _Obj MUL;
				if(!strcmp("DIV",btcode)) _Obj DIV;
				if(!strcmp("MOV",btcode)) _Obj MOV;
				if(!strcmp("IMM",btcode)) _Obj IMM;
				if(!strcmp("NOT",btcode)) _Obj NOT;
				if(!strcmp("SUB",btcode)) _Obj SUB;
				if(!strcmp("PRTF",btcode)) _Obj PRTF;
				if(!strcmp("EXT",btcode)) _Obj EXT;
				if(!strcmp("CPY",btcode)) _Obj CPY;
				if(!strcmp("TRV",btcode)) _Obj TRV;
				if(!strcmp("SCNF",btcode)) _Obj SCNF;
				if(!strcmp("AX",btcode)) _Obj AX;
				if(!strcmp("BX",btcode)) _Obj BX;
				if(!strcmp("CX",btcode)) _Obj CX;
				if(!strcmp("DX",btcode)) _Obj DX;
				if(!strcmp("SP",btcode)) _Obj SP;
				if(!strcmp("BP",btcode)) _Obj BP;
				if(!strcmp("SI",btcode)) _Obj SI;
				if(!strcmp("DI",btcode)) _Obj DI;
				if(!strcmp("IP",btcode)) _Obj IP;
				if(!strcmp("CS",btcode)) _Obj CS;
				if(!strcmp("DS",btcode)) _Obj DS;
				if(!strcmp("SS",btcode)) _Obj SS;
				if(!strcmp("ES",btcode)) _Obj ES;
				if(!strcmp("BRK",btcode)) { _Obj BRK; break;}
				if(!strcmp("IMMT",btcode)) _Obj IMMT;
			}
			continue;
		} else if(method[strlen(method)-1]==':') {
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
			NewObjSyb(ObjFile,args,-1);
			continue;
		}
		if(obj[0]=='/'||args[0]=='[') { // Function-return
			if(obj[0]=='/') {
				for(j=0; j<= ptop; j++)	if(!strcmp(objPool[j].symbol,method)) break;
				sprintf(virtual.mem+virtual.mtop,"%s",args);
				ObjFile[lmt++]=IMM;
				ObjFile[lmt++]=virtual.mtop,virtual.mtop+=strlen(args);
				objPool[j].argsplit(ObjFile,args,j);
				continue;
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
				objPool[j].argsplit(ObjFile,args,j);
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
