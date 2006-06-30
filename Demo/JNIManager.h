#ifndef JNIMANAGER_H_
#define JNIMANAGER_H_
#include "jni.h"
#include "typeDefs.h"
#include <ffi.h>

class Object;
class Method;




class JNIManager
{
public:

	static JNIManager * getInstance();

	
	/**This method adds the given obj to the data structure saving the local 
	 * objects referenced by a native function.
	 * this data structure will be used to adjust the state of the objects referenced
	 * after the return of the native method.
	 */
    Object * addJNILocalRef(Object* obj){
     	//This method should be imnplemented , for now it is empty..
     	return NULL;
    }
    
    /**
     * This method deletes a local reference from the local reference generated by the top native call
     */
    void deleteLocalRef(Object *obj){
    		//this method should be implemented , for now it is empty...
    }
	
	
	/**
	 * This method is called by the interpreter to execute a native method given the method data in arg method and the arguments in the 
	 * array args, this array is in the same format of the local variables before the calling of a java methods...
	 */
	void callNativeMethod(Method * method,u4 args[],int argsCount);
	void loadLib(const char * libName);
	
	
	
	virtual ~JNIManager();
private:
	static const int MAX_LIBS = 10;
	void *loadedLibs[MAX_LIBS] ;
	int libCount ;
	static JNIManager * instance;
	JNIManager(); 
	const char * mangleMethodName(char* name,char * className);
	void * searchInLoadedLibs(const char* name);
	void  generateFFI_CIF(Method * method, ffi_cif * cif,int argsCount,ffi_type** argsTypes,ffi_type *&rType);
	void getValues(Method * method, u4 args[],void ** values,void *& retValue,int argsCount); //put the arguments from args to values...
	
	
	
};

#endif /*JNIMANAGER_H_*/