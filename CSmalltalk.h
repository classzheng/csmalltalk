// CSmalltalk.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pseudo.h"
#include "FMacro.h"
#define $ model->private
#define detect ((short)-1)
typedef struct {
	char* rcode;
	short limit;
	struct {
		short* bracks;
		     int btop;
	} private;
} CSmalltalk;
char*substr(const char*str,int beg,int end) {
	char*sub=(char*)malloc((end-beg+1)*sizeof(char));
	for(unsigned i = 0; i<(end-beg+1); i++) {
		sub[i]=str[i+beg];
	}
	return sub;
}
short i,j,k,h,w,cnt0,cnt1,temp;
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
	for(j=0,cnt0=0; j<$.btop;j++) {
	  if($.bracks[j]<0) {
	  	cnt1=0;
	  	for(i=j; i>=0; i--) {
	  	  if($.bracks[i]>=0) cnt1++;
	  	  if(cnt1==cnt0+1) {
	  	    C57LOG("%s Execute.%s%s",substr(model->rcode,$.bracks[i],-$.bracks[j]),"\r","\n");
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
char beef[128];
char* _Mul(const char* rawcc) {
	strcpy(beef,rawcc);
	return beef;
}
#undef $
