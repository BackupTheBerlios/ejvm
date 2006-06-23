#ifndef BYTECODE_H_
#define BYTECODE_H_
#include "typeDefs.h"
//#include "ExceptionTable.h"
class ExceptionTable;

class ByteCode
{
public:	
	u2 nameIndex;
    u4 length;
    u2 maxStack;
    u2 maxLocals;
    u4 codeLength;
    u1 * code;
    ExceptionTable * exceptionTable;
	
public:
	ByteCode(){};	
	ByteCode(byte inputFile [],int inPtr,u2 nameIndex, u4 length);
	virtual ~ByteCode();
};

#endif /*BYTECODE_H_*/
