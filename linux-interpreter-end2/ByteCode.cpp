#include "ByteCode.h"
#include "ExceptionTable.h"
#include<stdio.h>

ByteCode::ByteCode(byte inputFile[], int inPtr,
	u2 nameIndex, u4 length)
{
	this->nameIndex = nameIndex;
	this->length = length;
	maxStack = ( ((u2)inputFile[inPtr])<<8) + inputFile[inPtr+1];
    printf("maxStack = %d",maxStack);
    inPtr+=2;
	maxLocals = ( ((u2)inputFile[inPtr])<<8) + inputFile[inPtr+1];
    printf("maxLoc = %d",maxLocals);
	inPtr+=2;
    int x;
    scanf("%d",&x);
	u2 temp = inputFile[inPtr+1];
	codeLength = (((u4)inputFile[inPtr])<<24) + (temp << 16) + 	
				(((u2)inputFile[inPtr+2])<<8)+ inputFile[inPtr+3];
	/* advance the pointer */			
	inPtr+=4;
	/* create the array of code and fill it*/
	code = new byte [codeLength];
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
