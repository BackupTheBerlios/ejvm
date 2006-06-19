#include "jni.h" //this is the GNU classpath implementation of the jni.h
#include "Loader.h"
#include "ClassData.h"
#include "Heap.h"
#include "ExceptionThrower.h"
#include "JNIManager.h"
#include "Method.h"
#include "Field.h"
#include "ExecutionEng.h"
#include "typeDefs.h"


#include <iostream>
#include <stdarg.h>
using std::cout;
using std::endl;


static Loader* gLoader = Loader::getInstance();
static Heap*		gHeap = Heap::getInstance();
static ExceptionThrower *gExceptionThrower = ExceptionThrower::getInstance();
static JNIManager * gJNIManager = JNIManager::getInstance();
static ExecutionEng * gExecutionEng = ExecutionEng::geInstance();

#define JNI_VERSION JNI_VERSION_1_1


jint GetVersion(JNIEnv *env){
	return JNI_VERSION;
}

/**
 * This function returns the java.lang.Class instance of a class defined as an array of bytes.
 * The JVM does no check to see if the required class was already loaded by the given loader.
 */
jclass DefineClass(JNIEnv *env, const char *name,jobject loader, const jbyte *buf,jsize bufLen)
 {
 	cout << "JNI Function: DefineClass" << endl;
 	//this method should be modified to return NULL if and only if in case an exception occured during the function
	ClassData * newClass =gLoader->getClassData(name,(byte*)buf);
	//check here if an exception occured. If so delete the newClass and return NULL
	return (jclass)newClass->getClassInstance();
	
 }
 
 
 jclass FindClass(JNIEnv *env, const char *name){
 	cout << "JNI function FindClass" << endl;
	//this method should be modified to return NULL if and only if in case an exception occured during the function
	ClassData * newClass =gLoader->getClassData(name);
	//check here if an exception occured. If so delete the newClass and return NULL
	
	//from JNIspecs: The class returned should be initialized...
	return (jclass)newClass->getClassInstance();
 }
 
 
 
 jclass GetSuperclass(JNIEnv *env, jclass clazz){
	 	cout << "JNI function GetSuperClass" << endl;
 		//Note till now the getSuperClassData method returns NULL.
 		return (jclass)((ClassData*)clazz)->getSuperClassData();
 }
 
 
 
jboolean IsAssignableFrom(JNIEnv *env,jclass clazz1, jclass clazz2){
		return (jboolean)((ClassData*)clazz1)->canCastedTo((ClassData*)clazz2);
}


jint Throw(JNIEnv *env, jthrowable obj){
//	ExceptionThrower
	gExceptionThrower->throwException((Object*)obj);
	//check here if any exception occured during the above line if any , return -1
	return 0;
}

jint ThrowNew(JNIEnv *env, jclass clazz,const char *message){
	gExceptionThrower->throwException((ClassData*)clazz,message);
	//check here if any exception occured during the above line if any , return -1
	return 0;
}

jthrowable ExceptionOccurred(JNIEnv *env){
	return (jthrowable)gExceptionThrower->exceptionOccured();
}

void ExceptionDescribe(JNIEnv *env){
	gExceptionThrower->printPendingException();
} 


void ExceptionClear(JNIEnv *env){
	gExceptionThrower->clearPendingException();
}
 
void FatalError(JNIEnv *env, const char *msg){
	fprintf(stderr,msg);
	//this function should then exit the virtual machine 
	//so we should implement a mechanism to clearly exit the VM..
	
	//exitVM();
}

jobject NewGlobalRef(JNIEnv *env, jobject obj){
	//The implementation of this function may change if a need to save the global reference appeard
	//The new implementation should check if OutOfMemory exception occured , and then return NULL.	
	return obj;
}

void DeleteGlobalRef(JNIEnv *env, jobject gref){
	//The implementation of this function may chane if a need to save the global references appesrd
	//for now this function do nothing....
}
 
 
 
void DeleteLocalRef(JNIEnv *env, jobject lref){
	gJNIManager->deleteLocalRef((Object*)lref);
} 


 
jobject AllocObject(JNIEnv *env, jclass clazz){
	return (jobject)gJNIManager->addJNILocalRef(gHeap->createObject((ClassData*)clazz));
}

 
jobject NewObject(JNIEnv *env, jclass clazz,jmethodID methodID, ...){
	Object* newObject = gHeap->createObject((ClassData*)clazz);
	if(gExceptionThrower->exceptionOccured())
		return NULL;
	//call constructor...	
	va_list args ;
	va_start(args,methodID);
	gExecutionEng->executeMethod(newObject,(Method*)methodID,args);
	va_end(args);
	if(gExceptionThrower->exceptionOccured())
		return NULL;
		
	return (jobject)gJNIManager->addJNILocalRef(newObject);
}
 
 
 
jclass GetObjectClass(JNIEnv *env, jobject obj){
	return (jclass)((Object*)obj)->getClassData();
} 
 
 
 
jboolean IsInstanceOf(JNIEnv *env, jobject obj,jclass clazz){
	if(obj == NULL)
		return JNI_TRUE;
	if( ((ClassData*)clazz)->canCastedTo(((Object*)obj)->getClassData()))
		return JNI_TRUE;
	return JNI_FALSE;	
}

jboolean IsSameObject(JNIEnv *env, jobject ref1,jobject ref2){
	if(ref1 == ref2)
		return JNI_TRUE;
	else
		return JNI_FALSE;
}


 
 
 
 
 
 
 
 
/**
 * @This global variable is the function table of the JNI.
 * It is used only by the JNIManager class
 */
JNINativeInterface functionTable = {
/*0*/	NULL,
/*1*/	NULL,
/*2*/	NULL,
/*3*/	NULL,
/*4*/	GetVersion,
/*5*/	DefineClass,
/*6*/	FindClass,
/*7*/	NULL,
/*8*/	NULL,
/*9*/	NULL,
/*10*/	GetSuperclass,
/*11*/	IsAssignableFrom	,
/*12*/	NULL,
/*13*/	Throw,
/*14*/	ThrowNew,
/*15*/	ExceptionOccurred,
/*16*/	ExceptionDescribe,
/*17*/  ExceptionClear,
/*18*/  FatalError,
/*19*/  NULL,
/*20*/  NULL,
/*21*/  NewGlobalRef,
/*22*/  DeleteGlobalRef,
/*23*/  DeleteLocalRef,
/*24*/  IsSameObject,
/*25*/  NULL,
/*26*/  NULL,
/*27*/  AllocObject,
/*28*/  NewObject,
/*29*/  NULL,
/*30*/  NULL,
/*31*/  GetObjectClass,
/*32*/  IsInstanceOf













	
};
const JNINativeInterface * env = &functionTable;





/**
 * @brief This function tests the functionality of the jni functions
 */
 void testJNI(){
 	cout<<"GetVersion():" << env->GetVersion(&env)<< endl;
 }
 
 
 
 
 