// Pseudo.h
#include <stdio.h>
#include <string.h>
struct {
  unsigned char* mem;
  		  short mtop;
  unsigned char* regy;
  unsigned char  immt;
} virtual;
typedef enum {
    NOP=128,XOR,ADD,MUL,DIV,MOV,IMM,NOT,SUB,
	PRTF,EXT,CPY,
	AX,BX,CX,DX,SP,BP,SI,DI,IP,CS,DS,SS,ES,
	IMMT=-1
} Bytecode;
short i,j,k,h,w,cnt0,cnt1,temp,ptop=0,lmt,ftop;
void NeutralInt(Bytecode* method,short limit) {
	virtual.regy=(unsigned char*)malloc(16);
	for(i=0; i<limit; i++) {
#       define _case(n) if(method[i]==n)
		  _case(XOR) 
		  	virtual.immt=virtual.immt^virtual.regy[method[i+1]-AX],i++;
		  else _case(ADD) 
		  	virtual.immt=virtual.immt+virtual.regy[method[i+1]-AX],i++;
		  else _case(SUB) 
		  	virtual.immt=virtual.immt+virtual.regy[method[i+1]-AX],i++;
		  else _case(NOT) 
		  	virtual.immt=(!virtual.regy[method[i+1]-AX]),i++;
		  else _case(MUL) 
  		  	virtual.immt=virtual.immt*virtual.regy[method[i+1]-AX],i++;
  		  else _case(DIV) 
  		  	virtual.immt=virtual.immt/virtual.regy[method[i+1]-AX],i++;
  		  else _case(MOV) 
  		  	virtual.regy[method[i+1]-AX]=(method[i+2]==IMMT?virtual.immt:method[i+2]),i+=2;
  		  else _case(IMM) 
  		  	virtual.immt=method[i+1],i++;
  		  else _case(PRTF)
  		  	printf("%s",virtual.mem+virtual.immt,0,virtual.regy[method[i+1]-AX]);
  		  else _case(EXT)
  		  	if(virtual.regy[method[i+1]-AX]) i=virtual.immt;
  		  else _case(CPY)
  		    strcpy(virtual.mem+virtual.regy[method[i+1]-AX],virtual.mem+virtual.regy[method[i+2]-AX]),i+=2;
  		  else _case(NOP); // You should do nothing..
	}
	return ;
}
void dumpPseu(Bytecode* area,short limit) {
	for(i=0; i<limit; i++) {
		if(area[i]==NOP) printf(" - NOP ");
		else if(area[i]==XOR) printf(" - XOR ");
		else if(area[i]==ADD) printf(" - ADD ");
		else if(area[i]==MUL) printf(" - MUL ");
		else if(area[i]==DIV) printf(" - DIV ");
		else if(area[i]==MOV) printf(" - MOV ");
		else if(area[i]==IMM) printf(" - IMM ");
		else if(area[i]==NOT) printf(" - NOT ");
		else if(area[i]==SUB) printf(" - SUB ");
		else if(area[i]==PRTF) printf(" - PRTF ");
		else if(area[i]==EXT) printf(" - EXT ");
		else if(area[i]==CPY) printf(" - CPY ");
		else if(area[i]==AX) printf("AX ");
		else if(area[i]==BX) printf("BX ");
		else if(area[i]==CX) printf("CX ");
		else if(area[i]==DX) printf("DX ");
		else if(area[i]==SP) printf("SP ");
		else if(area[i]==BP) printf("BP ");
		else if(area[i]==SI) printf("SI ");
		else if(area[i]==DI) printf("DI ");
		else if(area[i]==IP) printf("IP ");
		else if(area[i]==CS) printf("CS ");
		else if(area[i]==DS) printf("DS ");
		else if(area[i]==SS) printf("SS ");
		else if(area[i]==ES) printf("ES ");
		else if(area[i]==IMMT) printf("IMMT ");
		else {
		    if(area[i+1]<=NOP) printf("%d",area[i]-24);
		}
		if(area[i+1]<=NOP) puts("");
	}
	return ;
}
#define PseuCmd
#ifdef PseuCmd
# define XOR XOR,
# define NOT NOT,
# define ADD ADD,
# define SUB SUB,
# define MUL MUL,
# define DIV DIV,
# define MOV MOV,
# define IMM IMM,
# define EXT EXT,
# define CPY CPY,
# define PRTF PRTF,
#endif
/*****************************************
* for Example                            *
*  @classzheng 2024.7.4                  *
int main(void) {
    printf("\033c"); // Clear Screen
    Bytecode area[]={
    // #define Line(n) Line##n
//   Line0:
      MOV AX,N 5 , // AX=5;
      IMM N 6    , // (immt)=6;
      ADD AX     , // immt+=AX;                 (immt=11,AX=5)
      MOV AX,N 11, // AX=11;
      PRTF AX    , // printf("%s",memory+immt);
      MOV AX,N 0 , // AX=0;
      EXT AX     , // if(AX) goto Line(immt);
    }; // Pseudo-AsSeMbly
    char memory[64]="classzheng\0Hello,world!\n\0";
	virtual.mem=(unsigned char*)malloc(64);
	virtual.mem=memory;
    NeutralInt(area,17);
    dumpPseu(area);
    return 0;
}
*                                         *
*******************************************/
