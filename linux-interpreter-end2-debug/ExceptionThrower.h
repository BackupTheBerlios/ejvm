#ifndef EXCEPTIONTHROWER_H_
#define EXCEPTIONTHROWER_H_
#include <stdio.h>

class Object;
class ClassData;
//This class shoulod be singlton
class ExceptionThrower
{
	static ExceptionThrower* exceptionThrowerInstance;
	static Object* exceptionObject;
	ExceptionThrower();
public:

	
	
	static ExceptionThrower *getInstance();
	void throwException(const char * exceptionClassName, const char * message);
	void throwException(Object * throwableObj);
	void throwException(ClassData* exceptionClassData, const char * message);
	Object* exceptionOccured();
	void printPendingException();
	void clearPendingException();
	virtual ~ExceptionThrower();
};

#endif /*EXCEPTIONTHROWER_H_*/

