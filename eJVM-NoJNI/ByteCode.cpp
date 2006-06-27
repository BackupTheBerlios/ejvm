#include "ByteCode.h"
#include "ExceptionTable.h"
#include <stdio.h>
#include <stdlib.h>

ByteCode::ByteCode(const byte inputFile[], int inPtr,
	u2 nameIndex, u4 length)
{
	this->nameIndex = nameIndex;
	this->length = length;
	maxStack = ( ((u2)inputFile[inPtr])<<8) + inputFile[inPtr+1];
    //printf("maxStack = %d\n",maxStack);
    inPtr+=2;
	maxLocals = ( ((u2)inputFile[inPtr])<<8) + inputFile[inPtr+1];
    //printf("maxLoc = %d\n",maxLocals);
	inPtr+=2;
    //int x;
    //scanf("%d",&x);
	u2 temp = inputFile[inPtr+1];
	codeLength = (((u4)inputFile[inPtr])<<24) + (temp << 16) + 	
				(((u2)inputFile[inPtr+2])<<8)+ inputFile[inPtr+3];
	/* advance the pointer */			
	inPtr+=4;
	/* create the array of code and fill it*/
	code = NULL;	
	code = new u1 [codeLength];
	if(code == NULL){
		//printf("Null in allocating code[]\n\r");
		exit(1);
	}
	for(u4 i=0; i<codeLength; i++)
		code[i] = inputFile[inPtr+i];	
	/* advance the pointer */			
	inPtr+=codeLength;	
	/* create the exception table and fill it */
	u2 exceptionTableLength=(((u2)inputFile[inPtr])<<8)+
	inputFile[inPtr+1];	
	/* advance the pointer */			
	inPtr+=2;
	exceptionTable = new ExceptionTable(inputFile,
	inPtr,exceptionTableLength);
}

ByteCode::~ByteCode()
{
}
