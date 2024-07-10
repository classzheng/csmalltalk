// CSmalltalk.C
#include "CSmalltalk.h"
char* str1Line(void) {
	char* str=(char*)malloc(128);
	int c,msz=128;
	int len = 0;
	while((c = getchar())!=EOF&&len<msz) {
		str[len++] = c;
		if('\n' == c||'\r'==c)
			break;
	}
	str[len] = '\0';
	return str;
}
int main(FPARAM(ac,av,nv)) {
	TRY(C57Exp,exp) {
		C57LOG("[@CSmalltalk launch] CSmalltalk Launch.%s","\r\n");
		CSmalltalk c57vm = {
		  .rcode=_Mul("[Console print: 'CSmalltalk v0.9 CoffeeRain release\n']."),
		  .limit=detect,
		},JUST_LIKE_THAT;
		Bool dumpMode=False;
		short b=0,maxl1=0,maxl2=0;
		virtual.mem=(unsigned char*)malloc(4096);
		while(True) {
			if(!strcmp(c57vm.rcode,"-dump\n")) {
				dumpMode=!dumpMode,ftop=0,lmt=0;
				C57LOG("CSmalltalk> "),c57vm=JUST_LIKE_THAT,c57vm.rcode=str1Line();
				continue;
			} else if(!strcmp(c57vm.rcode,"-swim\n")) {
				C57LOG("Object: ");
				for(b=0;b<ptop; b++) {
					C57LOG("%12s",objPool[b].symbol);
				}
				C57LOG("\nPath:   ");
				for(b=0; b<ptop; b++) {
					C57LOG("%12s",objPool[b].path);
				}
				C57LOG("\n"),ftop=0,lmt=0;
				C57LOG("CSmalltalk> "),c57vm=JUST_LIKE_THAT,c57vm.rcode=str1Line();
				continue;
			}
			c57vm,parse(&c57vm),flint();
			Bytecode* dumpData=compile(&c57vm);
			NeutralInt(dumpData,lmt);
			if(dumpMode) dumpPseu(dumpData,lmt);
			free(dumpData),ftop=0,lmt=0;
			C57LOG("CSmalltalk> "),c57vm=JUST_LIKE_THAT,c57vm.rcode=str1Line();
		}
		C57LOG("[@CSmalltalk logout] EXIT 0.%s","\r\n");
		return 0;
	} CATCH(exp,ENOUGH_MEM) {
		C57LOG("[@CSmalltalk logout] Enough memory.%s","\r\n");
	} CATCH(exp,UNKNOWN) {
		C57LOG("[@CSmalltalk logout] Unkown reason.%s","\r\n");
	} CATCH(exp,PROGRAM_ABORT) {
		C57LOG("[@CSmalltalk logout] Program abort.%s","\r\n");
	} FINALLY() {
		C57LOG("[@CSmalltalk logout] EXIT -1.%s","\r\n");
	}
	return -1;
}
