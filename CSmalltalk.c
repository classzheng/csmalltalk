// CSmalltalk.C
#include "CSmalltalk.h"
int main(FPARAM(ac,av,nv)) {
	TRY(C57Exp,exp) {
		C57LOG("[@CSmalltalk launch] CSmalltalk Launch.%s","\r\n");
		CSmalltalk c57vm = {
		  .rcode=_Mul("[Console print: 'Hello,world!']."),
		  .limit=detect,
		},JUST_LIKE_THAT;
		virtual.mem=(unsigned char*)malloc(4096);
		c57vm,parse(&c57vm),flint();
		Bytecode* dumpData=compile(&c57vm);
		NeutralInt(dumpData,lmt),dumpPseu(dumpData,lmt);
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
