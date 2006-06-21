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

jfieldID GetFieldID(JNIEnv *env, jclass clazz,const char *name, const char *sig){
	//if not initialized , initialise the clazz       
	//if(gExceptionThrower->exceptionOccured())   //check for exception during initialization.
	//	return NULL;
	Field* field = ((ClassData*)clazz)->lookupField(name,sig);
	if(gExceptionThrower->exceptionOccured())   //check for exceptions during searching for the field
		return NULL;
	return (jfieldID)field;
	
		
}
 
 
 
//<NativeType> Get<Type>Field(JNIEnv *env,jobject obj, jfieldID fieldID);
jobject GetObjectField(JNIEnv *env,jobject obj, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Object*)obj)->getField((Field*)fieldID,word1,word2);
	
	return  (jobject)word1;
}

jboolean GetBooleanField(JNIEnv *env,jobject obj, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Object*)obj)->getField((Field*)fieldID,word1,word2);
	
	return (jboolean)word1;
}

jbyte GetByteField(JNIEnv *env,jobject obj, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Object*)obj)->getField((Field*)fieldID,word1,word2);
	
	return (jbyte)word1;
}
 
jchar GetCharField(JNIEnv *env,jobject obj, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Object*)obj)->getField((Field*)fieldID,word1,word2);
	
	return (jchar)word1;
} 

jshort GetShortField(JNIEnv *env,jobject obj, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Object*)obj)->getField((Field*)fieldID,word1,word2);
	
	return (jshort)word1;
}

jint GetIntField(JNIEnv *env,jobject obj, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Object*)obj)->getField((Field*)fieldID,word1,word2);
	
	return (jint)word1;
}

jlong GetLongField(JNIEnv *env,jobject obj, jfieldID fieldID){
	u4 longData[2]; 
	
	((Object*)obj)->getField((Field*)fieldID,longData[0],longData[1]);
	
	
	return *((jlong*)longData);
}  
 
jfloat GetFloatField(JNIEnv *env,jobject obj, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Object*)obj)->getField((Field*)fieldID,word1,word2);
	
	return  *((jfloat*)&word1);
} 

jdouble GetDoubleField(JNIEnv *env,jobject obj, jfieldID fieldID){
	u4 doubleData[2]; 
	
	((Object*)obj)->getField((Field*)fieldID,doubleData[0],doubleData[1]);
	
	
	return *((jdouble*)doubleData);
}

//void Set<Type>Field(JNIEnv *env, jobject obj,jfieldID fieldID, <NativeType> value);


void SetObjectField(JNIEnv *env, jobject obj,jfieldID fieldID, jobject value){
	((Object*)obj)->putField((Field*)fieldID,(u4)value,0);
}

void SetBooleanField(JNIEnv *env, jobject obj,jfieldID fieldID, jboolean value){
	((Object*)obj)->putField((Field*)fieldID,(u4)value,0);
}

void SetByteField(JNIEnv *env, jobject obj,jfieldID fieldID, jbyte value){
	((Object*)obj)->putField((Field*)fieldID,(u4)value,0);
}


void SetCharField(JNIEnv *env, jobject obj,jfieldID fieldID, jchar value){
	((Object*)obj)->putField((Field*)fieldID,(u4)value,0);
}

void SetShortField(JNIEnv *env, jobject obj,jfieldID fieldID, jshort value){
	((Object*)obj)->putField((Field*)fieldID,(u4)value,0);
}

void SetIntField(JNIEnv *env, jobject obj,jfieldID fieldID, jint value){
	((Object*)obj)->putField((Field*)fieldID,(u4)value,0);
}


void SetLongField(JNIEnv *env, jobject obj,jfieldID fieldID, jlong value){
	u4 longData[2];
	*((jlong*)longData) = value;
	
	((Object*)obj)->putField((Field*)fieldID,longData[0],longData[1]);
}

void SetFloatField(JNIEnv *env, jobject obj,jfieldID fieldID, jfloat value){
	u4 word1;
	*((jfloat*)&word1) = value;
	((Object*)obj)->putField((Field*)fieldID,word1,0);
}


void SetDoubleField(JNIEnv *env, jobject obj,jfieldID fieldID, jdouble value){
	u4 doubleData[2];
	*((jdouble*)doubleData) = value;
	
	((Object*)obj)->putField((Field*)fieldID,doubleData[0],doubleData[1]);
}


jfieldID GetStaticFieldID(JNIEnv *env,jclass clazz, const char *name,const char *sig){
	//if not initialized , initialise the clazz       
	//if(gExceptionThrower->exceptionOccured())   //check for exception during initialization.
	//	return NULL;
	Field* field = ((ClassData*)clazz)->lookupField(name,sig);
	if(gExceptionThrower->exceptionOccured())   //check for exceptions during searching for the field
		return NULL;
	return (jfieldID)field;
	
}


//<NativeType> GetStatic<Type>Field(JNIEnv *env,jclass clazz, jfieldID fieldID);
jobject GetStaticObjectField(JNIEnv *env,jclass clazz, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Field*)fieldID)->getStaticValue(word1,word2);
	
	return  (jobject)word1;
}



jboolean GetStaticBooleanField(JNIEnv *env,jclass clazz, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Field*)fieldID)->getStaticValue(word1,word2);
	
	return  (jboolean)word1;
}


jbyte GetStaticByteField(JNIEnv *env,jclass clazz, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Field*)fieldID)->getStaticValue(word1,word2);
	
	return  (jbyte)word1;
}


jchar GetStaticCharField(JNIEnv *env,jclass clazz, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Field*)fieldID)->getStaticValue(word1,word2);
	
	return  (jchar)word1;
}


jshort GetStaticShortField(JNIEnv *env,jclass clazz, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Field*)fieldID)->getStaticValue(word1,word2);
	
	return  (jshort)word1;
}


jint GetStaticIntField(JNIEnv *env,jclass clazz, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Field*)fieldID)->getStaticValue(word1,word2);
	
	return  (jint)word1;
}


jlong GetStaticLongtField(JNIEnv *env,jclass clazz, jfieldID fieldID){
	u4 longData[2]; 
	
	((Field*)fieldID)->getStaticValue(longData[0],longData[1]);
	
	return *((jlong*)longData);
}


jfloat GetStaticFloatField(JNIEnv *env,jclass clazz, jfieldID fieldID){
	u4 word1 ; //least sig word of the value
	u4 word2 ; //most sig word of the value
	
	((Field*)fieldID)->getStaticValue(word1,word2);
	
	return  *((jfloat*)&word1);
}


jdouble GetStaticDoubleField(JNIEnv *env,jclass clazz, jfieldID fieldID){
	u4 doubleData[2]; 
	
	((Field*)fieldID)->getStaticValue(doubleData[0],doubleData[1]);
	
	return *((jdouble*)doubleData);
}


//void SetStatic<Type>Field(JNIEnv *env,jclass clazz, jfieldID fieldID,<NativeType> value);
void SetStaticObjectField(JNIEnv *env, jclass clazz,jfieldID fieldID, jobject value){
	((Field*)fieldID)->putStaticValue((u4)value,0);
}

void SetStaticBooleanField(JNIEnv *env, jclass clazz,jfieldID fieldID, jboolean value){
	((Field*)fieldID)->putStaticValue((u4)value,0);
}
void SetStaticByteField(JNIEnv *env, jclass clazz,jfieldID fieldID, jbyte value){
	((Field*)fieldID)->putStaticValue((u4)value,0);
}
void SetStaticCharField(JNIEnv *env, jclass clazz,jfieldID fieldID, jchar value){
	((Field*)fieldID)->putStaticValue((u4)value,0);
}
void SetStaticShortField(JNIEnv *env, jclass clazz,jfieldID fieldID, jshort value){
	((Field*)fieldID)->putStaticValue((u4)value,0);
}
void SetStaticIntField(JNIEnv *env, jclass clazz,jfieldID fieldID, jint value){
	((Field*)fieldID)->putStaticValue((u4)value,0);
}
void SetStaticLongField(JNIEnv *env, jclass clazz,jfieldID fieldID, jlong value){
	u4 longData[2];
	*((jlong*)longData) = value;
	((Field*)fieldID)->putStaticValue(longData[0],longData[1]);
}

void SetStaticFloatField(JNIEnv *env, jclass clazz,jfieldID fieldID, jfloat value){
	u4 word1;
	*((jfloat*)&word1) = value;
	((Field*)fieldID)->putStaticValue(word1,0);
}
void SetStaticDoubleField(JNIEnv *env, jclass clazz,jfieldID fieldID, jdouble value){
	u4 doubleData[2];
	*((jdouble*)doubleData) = value;
	((Field*)fieldID)->putStaticValue(doubleData[0],doubleData[1]);
}


jmethodID GetMethodID(JNIEnv *env, jclass clazz,const char *name, const char *sig){
	//if not initialized , initialise the clazz       
	//if(gExceptionThrower->exceptionOccured())   //check for exception during initialization.
	//	return NULL;
	Method* method = ((ClassData*)clazz)->lookupMethod(name,sig);
	if(gExceptionThrower->exceptionOccured())   //check for exceptions during searching for the field
		return NULL;
	return (jmethodID)method;
}


//<NativeType> Call<Type>Method(JNIEnv *env,jobject obj, jmethodID methodID, ...);
//<NativeType> Call<Type>MethodA(JNIEnv *env,jobject obj, jmethodID methodID, jvalue *args);
//<NativeType> Call<Type>MethodV(JNIEnv *env,jobject obj, jmethodID methodID, va_list args);

//=====================================CallVoidMethod(A|V| )=============================
void CallVoidMethod(JNIEnv *env,jobject obj, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
}
void CallVoidMethodA(JNIEnv *env,jobject obj, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
}
void CallVoidMethodV(JNIEnv *env,jobject obj, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
}
//==========================================================================================



//=====================================CallObjectMethod(A|V| )=============================
jobject CallObjectMethod(JNIEnv *env,jobject obj, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jobject)retWord1;
	
}
jobject CallObjectMethodA(JNIEnv *env,jobject obj, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jobject)retWord1;
	
}
jobject CallObjectMethodV(JNIEnv *env,jobject obj, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jobject)retWord1;
}
//===========================================================================================


//=====================================CallBooleanMethod(A|V| )=============================
jboolean CallBooleanMethod(JNIEnv *env,jobject obj, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jboolean)retWord1;
	
}
jboolean CallBooleanMethodA(JNIEnv *env,jobject obj, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jboolean)retWord1;
	
}
jboolean CallBooleanMethodV(JNIEnv *env,jobject obj, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jboolean)retWord1;
}
//==========================================================================================


//=====================================CallByteMethod(A|V| )=============================
jbyte CallByteMethod(JNIEnv *env,jobject obj, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jbyte)retWord1;
	
}
jbyte CallByteMethodA(JNIEnv *env,jobject obj, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jbyte)retWord1;
	
}
jbyte CallByteMethodV(JNIEnv *env,jobject obj, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jbyte)retWord1;
}
//==========================================================================================

//=====================================CallCharMethod(A|V| )=============================
jchar CallCharMethod(JNIEnv *env,jobject obj, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jchar)retWord1;
	
}
jchar CallCharMethodA(JNIEnv *env,jobject obj, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jchar)retWord1;
	
}
jchar CallCharMethodV(JNIEnv *env,jobject obj, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jchar)retWord1;
}
//==========================================================================================

//=====================================CallShortMethod(A|V| )=============================
jshort CallShortMethod(JNIEnv *env,jobject obj, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jshort)retWord1;
	
}
jshort CallShortMethodA(JNIEnv *env,jobject obj, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jshort)retWord1;
	
}
jshort CallShortMethodV(JNIEnv *env,jobject obj, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jshort)retWord1;
}
//==========================================================================================


//=====================================CallIntMethod(A|V| )=============================
jint CallIntMethod(JNIEnv *env,jobject obj, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jint)retWord1;
	
}
jint CallIntMethodA(JNIEnv *env,jobject obj, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jint)retWord1;
	
}
jint CallIntMethodV(JNIEnv *env,jobject obj, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jint)retWord1;
}
//==========================================================================================


//=====================================CallLongMethod(A|V| )=============================
jlong CallLongMethod(JNIEnv *env,jobject obj, jmethodID methodID, ...){
	u4 longData[2];
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,longData[0],longData[1],args);
	va_end(args);
	return *((jlong*)longData);
}
jlong CallLongMethodA(JNIEnv *env,jobject obj, jmethodID methodID, jvalue *args){
	u4 longData[2];
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,longData[0],longData[1],args);
	return *((jlong*)longData);
	
}
jlong CallLongMethodV(JNIEnv *env,jobject obj, jmethodID methodID, va_list args){
	u4 longData[2];
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,longData[0],longData[1],args);
	return *((jlong*)longData);
}
//==========================================================================================


//=====================================CallFloatMethod(A|V| )=============================
jfloat CallFloatMethod(JNIEnv *env,jobject obj, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return *((jfloat*)&retWord1);
	
}
jfloat CallFloatMethodA(JNIEnv *env,jobject obj, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return *((jfloat*)&retWord1);
	
}
jfloat CallFloatMethodV(JNIEnv *env,jobject obj, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return *((jfloat*)&retWord1);
}
//==========================================================================================

//=====================================CallDoubleMethod(A|V| )=============================
jdouble CallDoubleMethod(JNIEnv *env,jobject obj, jmethodID methodID, ...){
	u4 doubleData[2];
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,doubleData[0],doubleData[1],args);
	va_end(args);
	return *((jdouble*)doubleData);
}
jdouble CallDoubleMethodA(JNIEnv *env,jobject obj, jmethodID methodID, jvalue *args){
	u4 doubleData[2];
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,doubleData[0],doubleData[1],args);
	return *((jdouble*)doubleData);
	
}
jdouble CallDoubleMethodV(JNIEnv *env,jobject obj, jmethodID methodID, va_list args){
	u4 doubleData[2];
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,doubleData[0],doubleData[1],args);
	return *((jdouble*)doubleData);
}
//==========================================================================================





 
 
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
/*32*/  IsInstanceOf,
/*33*/  GetMethodID,
/*34*/  CallObjectMethod,
/*35*/  CallObjectMethodV,
/*36*/  CallObjectMethodA,
/*37*/  CallBooleanMethod,
/*38*/  CallBooleanMethodV,
/*39*/  CallBooleanMethodA,
/*40*/  CallByteMethod,
/*41*/  CallByteMethodV,
/*42*/  CallByteMethodA,
/*43*/  CallCharMethod,
/*44*/  CallCharMethodV,
/*45*/  CallCharMethodA,
/*46*/  CallShortMethod,
/*47*/  CallShortMethodV,
/*48*/  CallShortMethodA,
/*49*/  CallIntMethod,
/*50*/  CallIntMethodV,
/*51*/  CallIntMethodA,
/*52*/  CallLongMethod,
/*53*/  CallLongMethodV,
/*54*/  CallLongMethodA,
/*55*/  CallFloatMethod,
/*56*/  CallFloatMethodV,
/*57*/  CallFloatMethodA,
/*58*/  CallDoubleMethod,
/*59*/  CallDoubleMethodV,
/*60*/  CallDoubleMethodA,
/*61*/  NULL,
/*62*/  NULL,
/*63*/  NULL,
/*64*/  NULL,
/*65*/  NULL,
/*66*/  NULL,
/*67*/  NULL,
/*68*/  NULL,
/*69*/  NULL,
/*70*/  NULL,
/*71*/  NULL,
/*72*/  NULL,
/*73*/  NULL,
/*74*/  NULL,
/*75*/  NULL,
/*76*/  NULL,
/*77*/  NULL,
/*78*/  NULL,
/*79*/  NULL,
/*80*/  NULL,
/*81*/  NULL,
/*82*/  NULL,
/*83*/  NULL,
/*84*/  NULL,
/*85*/  NULL,
/*86*/  NULL,
/*87*/  NULL,
/*88*/  NULL,
/*89*/  NULL,
/*90*/  NULL,
/*91*/  NULL,
/*92*/  NULL,
/*93*/  NULL,
/*94*/  GetFieldID,
/*95*/  GetObjectField,
/*96*/  GetBooleanField,
/*97*/  GetByteField,
/*98*/  GetCharField,
/*99*/  GetShortField,
/*100*/  GetIntField,
/*101*/  GetLongField,
/*102*/  GetFloatField,
/*103*/  GetDoubleField,
/*104*/  SetObjectField,
/*105*/  SetBooleanField,
/*106*/  SetByteField,
/*107*/  SetCharField,
/*108*/  SetShortField,
/*109*/  SetIntField,
/*110*/  SetLongField,
/*111*/  SetFloatField,
/*112*/  SetDoubleField,
/*113*/  NULL,
/*114*/  NULL,
/*115*/  NULL,
/*116*/  NULL,
/*117*/  NULL,
/*118*/  NULL,
/*119*/  NULL,
/*120*/  NULL,
/*121*/  NULL,
/*122*/  NULL,
/*123*/  NULL,
/*124*/  NULL,
/*125*/  NULL,
/*126*/  NULL,
/*127*/  NULL,
/*128*/  NULL,
/*129*/  NULL,
/*130*/  NULL,
/*131*/  NULL,
/*132*/  NULL,
/*133*/  NULL,
/*134*/  NULL,
/*135*/  NULL,
/*136*/  NULL,
/*137*/  NULL,
/*138*/  NULL,
/*139*/  NULL,
/*140*/  NULL,
/*141*/  NULL,
/*142*/  NULL,
/*143*/  NULL,
/*144*/  GetStaticFieldID,
/*145*/  GetStaticObjectField,
/*146*/  GetStaticBooleanField,
/*147*/  GetStaticByteField,
/*148*/  GetStaticCharField,
/*149*/  GetStaticShortField,
/*150*/  GetStaticIntField,
/*151*/  GetStaticLongtField,
/*152*/  GetStaticFloatField,
/*153*/  GetStaticDoubleField,
/*154*/  SetStaticObjectField,
/*155*/  SetStaticBooleanField,
/*156*/  SetStaticByteField,
/*157*/  SetStaticCharField,
/*158*/  SetStaticShortField,
/*159*/  SetStaticIntField,
/*160*/  SetStaticLongField,
/*161*/  SetStaticFloatField,
/*162*/  SetStaticDoubleField,











	
};
const JNINativeInterface * env = &functionTable;





/**
 * @brief This function tests the functionality of the jni functions
 */
 void testJNI(){
 	cout<<"GetVersion():" << env->GetVersion(&env)<< endl;
 }
 
 
 
 
 