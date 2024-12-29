// CSmalltalk.C
#include "CSmalltalk.h"
int main(int argc, const char**argv) {
	TRY(C57Exp,exp) {
		C57LOG("[@CSmalltalk launch] CSmalltalk Launch.%s","\r\n");
		CSmalltalk c57vm = {
		  .rcode=malloc_string("\
 (Car flyWith: (Wing constructBy: 'furry\\'s fur)AWESOME!!!\\' \\'\\')-_-b)~' Length: '17cm*') toBe: (Bird class)).\
 (Console log:'Hello, world!'), (StdIn load: var1 | var2)."),
		  .limit=detect,
		};
		if(argc>1&&!strcmp(argv[1], "feeding~")) {
			printf("      /\\ __/\\\n");
			printf("    / _   _   \\\n");
			printf("(_)|____W_____(_)\n");
			printf("    CSmalltalk     \n\n");
		}
		0xC0FFEE57>flint();
		0xC0FFEE57>split(&c57vm);
		0xC0FFEE57>NeutralInt(&c57vm);
		C57LOG("\r\n");
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
