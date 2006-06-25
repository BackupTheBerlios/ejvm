#ifndef EXCEPTIONTABLE_H_
#define EXCEPTIONTABLE_H_
#include "typeDefs.h"
//#include "ExceptionTableEntry.h"
class ExceptionTableEntry;

class ExceptionTable
{
private:
	u2 numOfEntries;
	ExceptionTableEntry ** theTable;
public:
	ExceptionTable(const byte inputFile [],int inPtr, u2 numOfEntries);
	virtual ~ExceptionTable();
};

#endif /*EXCEPTIONTABLE_H_*/
