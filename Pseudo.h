#include <stdio.h>
struct {
  unsigned char* mem;
  		  short mtop;
  unsigned char* stac;
  		   short stop;
  unsigned char* regy;
  unsigned char  immt;
} virtual;
typedef enum {
	NOP=0,XOR,ADD,MUL,DIV,MOV,IMM,
	PRTF,EXT,SWP,
	AX,BX,CX,DX,SP,BP,SI,DI,IP,CS,DS,SS,ES,
	IMMT=-1
} Bytecode;
void swap_str(char*a,char*b) {
    char*temp=a;
    strcpy(a,b);
    strcpy(b,temp);
    return ;
}
short i,j,k,h,w,cnt0,cnt1,temp;
void NeutralInt(Bytecode* method,short limit) {  // Wait for me
	virtual.stac=(unsigned char*)malloc(128);
	virtual.regy=(unsigned char*)malloc(16);
	for(i=0; i<limit; i++) {
#       define _case(n) if(method[i]==n)
		  _case(XOR) 
		  	virtual.immt=virtual.immt^virtual.regy[method[i+1]-AX],i++;
		  else _case(ADD) 
		  	virtual.immt=virtual.immt+virtual.regy[method[i+1]-AX],i++;
		  else _case(MUL) 
  		  	virtual.immt=virtual.immt*virtual.regy[method[i+1]-AX],i++;
  		  else _case(DIV) 
  		  	virtual.immt=virtual.immt/virtual.regy[method[i+1]-AX],i++;
  		  else _case(MOV) 
  		  	virtual.regy[method[i+1]-AX]=(method[i+2]==-1?virtual.immt:method[i+2]),i+=2;
  		  else _case(IMM) 
  		  	virtual.immt=method[i+1],i++;
  		  else _case(PRTF)
  		  	printf("%s",virtual.mem+virtual.immt,0,virtual.regy[method[i+1]-AX]);
  		  else _case(EXT)
  		  	if(virtual.regy[method[i+1]-AX]) i=virtual.immt;
  		  else _case(SWP)
  		    swap_str(virtual.regy[method[i+1]-AX],virtual.immt);
  		  else _case(NOP); // You should do nothing...
	}
	return ;
}
#define XOR XOR,
#define ADD ADD,
#define MUL MUL,
#define DIV DIV,
#define MOV MOV,
#define IMM IMM,
#define EXT EXT,
#define SWP SWP,
#define PRTF PRTF,
int main(void) {
    Bytecode area[]={
    // #define Line(n) Line##n
//   Line0:
      MOV AX,5 , // AX=5;
      IMM 6    , // (immt)=6;
      ADD AX   , // immt+=AX;                 (immt=11,AX=5)
      MOV AX,12, // AX=12;
      PRTF AX  , // printf("%s",memory+immt);
      MOV AX,0 , // AX=0;
      EXT AX   , // if(AX) goto Line(immt);
    }; // Pseudo-AsSeMbly
    char memory[64]="classzheng\0Hello,world!\0";
	virtual.mem=(unsigned char*)malloc(64);
	virtual.mem=memory;
    NeutralInt(area,13);
    return 0;
}