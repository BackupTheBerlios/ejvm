#include "ExceptionTable.h"
#include "ExceptionTableEntry.h"
#include <iostream>

ExceptionTable::ExceptionTable(const byte inputFile [],
int inPtr, u2 numOfEntries)
{
////printf("Create the Exception Table\n");
	/* create a table with a proper number of entries*/
	this->numOfEntries = numOfEntries;
////printf("create the exception table using new ExceptionTableEntry * [numOfEntries] \n");
	theTable = new ExceptionTableEntry * [numOfEntries];
	/* fill the entries */
////printf("fill the exception table entries\n");
	u2 startPc,endPc,handlerPc,catchType;
	for(u2 i = 0; i<numOfEntries ; i++)
	{
////printf("fill the entry number %d in the exception table\n",i);
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
		if(theTable[i]==NULL)
		{
//printf("------------------------------------------------------>\n");	
//printf("NULL encountered after creating n Exception table entry in the file ExceptionTable.cpp\n");
//printf("------------------------------------------------------>\n");
exit(1);
		}
	}
}	

ExceptionTable::~ExceptionTable()
{
}
