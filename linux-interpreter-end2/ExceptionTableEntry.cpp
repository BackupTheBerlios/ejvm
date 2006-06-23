#include "ExceptionTableEntry.h"

ExceptionTableEntry::ExceptionTableEntry(u2 startPc,u2 endPc,
		u2 handlerPc,u2 catchType)
{
	this->startPc = startPc;
	this->endPc = endPc;
	this->handlerPc = handlerPc;
	this->catchType = catchType;
}

ExceptionTableEntry::~ExceptionTableEntry()
{
}
