// C57External.h
#define _Obj ObjFile[lmt++]=
void NewObjSyb(Bytecode*ObjFile,char* args) {
	char mark[12];
	sscanf(args,"%s",mark);
	for(k=0; k<strlen(mark); k++) if(mark[k]=='#') break;
	C57Object mrk={
	  .symbol=mark+j+k+1,
	  .rdata="(null)",
	};
	objPool[ptop++]=mrk;
	_Obj IMM _Obj ptop-1;
	return ;
}
void CslPrint(Bytecode*ObjFile,char* args) {
	short strbg=-1;
	for(k=0; k<strlen(args); k++) {
		if(args[k]=='\'') {
			if(strbg==-1) {
				if(k==0) strbg=k;
				else if(args[k-1]!='?') strbg=k;
			} else if(k!=0&&args[k-1]!='?') {
				args[k]=0;
				break;
			}
		}
	}
	sprintf(virtual.mem+virtual.mtop,"%s",args+strbg+1);
	_Obj IMM _Obj virtual.mtop,
	_Obj MOV _Obj AX,_Obj 114,
	_Obj PRTF _Obj AX,
	_Obj BRK,virtual.mtop+=strlen(args)-strbg+2;
	return ;
}
