#ifndef BYTECODE_H_
#define BYTECODE_H_
#include "typeDefs.h"
//#include "ExceptionTable.h"
class ExceptionTable;

class ByteCode
{
private:	
//public:
	u2 nameIndex;
    u4 length;
    u2 maxStack;
    u2 maxLocals;
    u4 codeLength;
    u1 * code;
    ExceptionTable * exceptionTable;
	
public:
	u2 getMaxLocals(){return maxLocals;}
	u2 getMaxStack(){return maxStack;}
	ByteCode(const byte inputFile [],int inPtr,	u2 nameIndex, u4 length);
	~ByteCode();
	u1 * getCode(){return code;}
};

#endif /*BYTECODE_H_*/
