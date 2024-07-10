// C57External.h
#define _Obj ObjFile[lmt++]=
void NewObjSyb(Bytecode*ObjFile,char* args,short) {
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
void CslPrint(Bytecode*ObjFile,char* args,short) {
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
	_Obj RET _Obj 0,virtual.mtop+=strlen(args)-strbg+2;
	return ;
}
void CslScanf(Bytecode*ObjFile,char* args,short) {
	short strbg=-1;
	for(k=0; k<strlen(args); k++) {
		if(args[k]=='\'') {
			if(strbg==-1) {
				if(k==0) strbg=k;
				else if(args[k-1]!='#') strbg=k;
			} else if(k!=0&&args[k-1]!='#') {
				args[k]=0;
				break;
			}
		}
	}
	sprintf(virtual.mem+virtual.mtop,"%s",args+strbg+1);
	_Obj IMM _Obj virtual.mtop,
	_Obj SCNF,
	_Obj RET _Obj 0,virtual.mtop+=strlen(args)-strbg+2;
	return ;
}
void NewObjPro(Bytecode*ObjFile,char* args,short pnt) {
	short u=0,v,w;
	char temp[114];
	Bool st;
	k=0;
	while(True)
		if(sscanf(args+k,"%s ",temp)!=1) break;
		else                             {
			st=False;
			for(v=0; v < strlen(temp); v++) if(temp[v]=='\'') {
				st=True;
				break;
			}
			if(st) for(w=strlen(temp)-1; True; w--) if(temp[w]=='\''&&temp[w-1]!='#') break;
			if(st) temp[w]=0;
			if(st) sprintf(virtual.mem+virtual.mtop,"%s",temp+v+1),_Obj IMM _Obj virtual.mtop,virtual.mtop+=strlen(temp);
			if(!st) for(w=0; w<ptop; w++) if(!strcmp(temp,objPool[w].symbol)) {
				sprintf(virtual.mem+virtual.mtop,"%s",objPool[w]),_Obj IMM _Obj virtual.mtop,virtual.mtop+=strlen(temp);
			}
		}
	for(u=0; True; u++)
		_Obj objPool[pnt].mth[u];
	return ;
}
