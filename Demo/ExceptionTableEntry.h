#ifndef EXCEPTIONTABLEENTRY_H_
#define EXCEPTIONTABLEENTRY_H_

#include "typeDefs.h"

class ExceptionTableEntry
{
private:
	u2 startPc;
	u2 endPc;
	u2 handlerPc;
	u2 catchType;	
	
public:
	ExceptionTableEntry(u2 startPc,u2 endPc,
		u2 handlerPc,u2 catchType);
		
	~ExceptionTableEntry();	
};

#endif /*EXCEPTIONTABLEENTRY_H_*/
