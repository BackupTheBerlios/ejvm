#ifndef EXCEPTIONTHROWER_H_
#define EXCEPTIONTHROWER_H_

class ExceptionThrower
{
public:
	ExceptionThrower();
	/**
	 * @brief save the exception occured by any module. This excepion
	 * should be checked latter by any other module wants to catch this
	 * exception...
	 */
	void throwException(char * exceptionClass);
	bool exceptionOccured();
	virtual ~ExceptionThrower();
};

#endif /*EXCEPTIONTHROWER_H_*/
