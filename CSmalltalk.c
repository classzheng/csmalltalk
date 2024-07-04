// CSmalltalk.C
#include "CSmalltalk.h"
void sgnAbrt(int sgn) {
	THROW(C57Exp,PROGRAM_ABORT);
	return ;
}
int main(FPARAM(_arg,__arg,___arg)) { // Ha
	TRY(C57Exp,exp) {
		C57LOG("[@CSmalltalk launch] CSmalltalk Launch.%s","\r\n");
		CSmalltalk c57vm = {
		  .rcode=_Mul("[[[[Car new] sold] named: 'Didi'] fly]."),
		  .limit=detect,
		},JUST_LIKE_THAT;
		c57vm,parse(&c57vm),flint(&c57vm);
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
