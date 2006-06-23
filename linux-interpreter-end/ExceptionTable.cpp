#include "ExceptionTable.h"
#include "ExceptionTableEntry.h"

ExceptionTable::ExceptionTable(byte inputFile [],
int inPtr, u2 numOfEntries)
{
	/* create a table with a proper number of entries*/
	this->numOfEntries = numOfEntries;
	theTable = new ExceptionTableEntry * [numOfEntries];
	/* fill the entries */
	u2 startPc,endPc,handlerPc,catchType;
	for(u2 i = 0; i<numOfEntries ; i++)
	{
		startPc = inputFile[inPtr] + inputFile[inPtr+1];
		inPtr+=2;
		endPc = inputFile[inPtr] + inputFile[inPtr+1];
		inPtr+=2;
		handlerPc = inputFile[inPtr] + inputFile[inPtr+1];
		inPtr+=2;
		catchType = inputFile[inPtr] + inputFile[inPtr+1];
		inPtr+=2;
		theTable[i] = new ExceptionTableEntry(startPc,endPc,
		handlerPc,catchType);
	}
}	

ExceptionTable::~ExceptionTable()
{
}
