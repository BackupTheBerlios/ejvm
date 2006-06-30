#include "ExceptionThrower.h"
#include "Loader.h"
#include "Object.h"
#include "ClassData.h"

ExceptionThrower* ExceptionThrower::exceptionThrowerInstance = NULL;
Object* ExceptionThrower::exceptionObject = NULL;

ExceptionThrower::ExceptionThrower()
{
}

ExceptionThrower::~ExceptionThrower()
{
}

ExceptionThrower* ExceptionThrower::getInstance()
{
//This method should be implemented , for now it returns NULL.
	if(exceptionThrowerInstance==NULL)
		exceptionThrowerInstance = new ExceptionThrower();
	return exceptionThrowerInstance;
}
	
	/**
	 * @brief save the exception occured by any module. This excepion
	 * should be checked latter by any other module wants to catch this
	 * exception...
	 */
	 //obj = new object
void ExceptionThrower::throwException(const char * exceptionClassName, const char * message)
{
	//This method should be implemented , for now it will be empty..
	Loader * loadclass = Loader::getInstance();
	ClassData* exceptionClassData = loadclass->getClassData(exceptionClassName);
	exceptionObject = new Object(exceptionClassData);
}
	
	/**
	 * This method takes an object of type java.lang.Throwable and throw it....
	 */
void ExceptionThrower::throwException(Object * throwableObj)
{
		//This method should be implemented , for now it will be empty..
		exceptionObject = throwableObj;
} 
	
	/**
	 * This method takes a pointer to the class data of the exception class and instantiate an object of this class.
	 * using the message to call the constructor of the Throwable object.
	 */
void ExceptionThrower::throwException(ClassData* exceptionClassData, const char * message)
{
		//This method should be implemented , for now it will be empty..
		exceptionObject = new Object(exceptionClassData);
			
}
	
	
	/**
	 * This method returns The Exception Object describes the pending exception.
	 * returns NULL if no pending exceptions.
	 */
Object* ExceptionThrower::exceptionOccured()
{
		//This method should be implemented , for now it will return NULL.
	return exceptionObject;
}
	
	
	/**This method should call the printStackTrace method to the pending Excetion Object
	 *Till we support the GNU classpath, this method will print 
	 *print the Class name of the pending Exception if any.
	 *After the printing , this method should clear the pending exception.
	 */
void ExceptionThrower::printPendingException()
{
//print the class name of the pending exception if any, for now	
	if(exceptionObject==NULL)
		;//printf("No pending Exception\n");
	else
	{
			//printf("Exception of type: ");
			//printf((exceptionObject->getClassData())->getFQName());
			//printf("is pending\n");
			;
	}
	exceptionObject=NULL;
}
		
	/** This method clears any pending exception.
	 */
void ExceptionThrower::clearPendingException()
{
		//this method should be implemented , for now it is empty...
		exceptionObject=NULL;
}
	
