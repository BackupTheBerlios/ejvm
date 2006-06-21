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






//=====================================CallNonvirtualVoidMethod(A|V| )=============================
void CallNonvirtualVoidMethod(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
}
void CallNonvirtualVoidMethodA(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
}
void CallNonvirtualVoidMethodV(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
}
//==========================================================================================


//=====================================CallNonvirtualObjectMethod(A|V| )=============================
jobject CallNonvirtualObjectMethod(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jobject)retWord1;
	
}
jobject CallNonvirtualObjectMethodA(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jobject)retWord1;
	
}
jobject CallNonvirtualObjectMethodV(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jobject)retWord1;
}
//===========================================================================================


//=====================================CallNonvirtualBooleanMethod(A|V| )=============================
jboolean CallNonvirtualBooleanMethod(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jboolean)retWord1;
	
}
jboolean CallNonvirtualBooleanMethodA(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jboolean)retWord1;
	
}
jboolean CallNonvirtualBooleanMethodV(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jboolean)retWord1;
}
//==========================================================================================


//=====================================CallNonvirtualByteMethod(A|V| )=============================
jbyte CallNonvirtualByteMethod(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jbyte)retWord1;
	
}
jbyte CallNonvirtualByteMethodA(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jbyte)retWord1;
	
}
jbyte CallNonvirtualByteMethodV(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jbyte)retWord1;
}
//==========================================================================================

//=====================================CallNonvirtualCharMethod(A|V| )=============================
jchar CallNonvirtualCharMethod(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jchar)retWord1;
	
}
jchar CallNonvirtualCharMethodA(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jchar)retWord1;
	
}
jchar CallNonvirtualCharMethodV(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jchar)retWord1;
}
//==========================================================================================

//=====================================CallNonvirtualShortMethod(A|V| )=============================
jshort CallNonvirtualShortMethod(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jshort)retWord1;
	
}
jshort CallNonvirtualShortMethodA(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jshort)retWord1;
	
}
jshort CallNonvirtualShortMethodV(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jshort)retWord1;
}
//==========================================================================================


//=====================================CallNonvirtualIntMethod(A|V| )=============================
jint CallNonvirtualIntMethod(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jint)retWord1;
	
}
jint CallNonvirtualIntMethodA(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jint)retWord1;
	
}
jint CallNonvirtualIntMethodV(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jint)retWord1;
}
//==========================================================================================


//=====================================CallNonvirtualLongMethod(A|V| )=============================
jlong CallNonvirtualLongMethod(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, ...){
	u4 longData[2];
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,longData[0],longData[1],args);
	va_end(args);
	return *((jlong*)longData);
}
jlong CallNonvirtualLongMethodA(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, jvalue *args){
	u4 longData[2];
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,longData[0],longData[1],args);
	return *((jlong*)longData);
	
}
jlong CallNonvirtualLongMethodV(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, va_list args){
	u4 longData[2];
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,longData[0],longData[1],args);
	return *((jlong*)longData);
}
//==========================================================================================


//=====================================CallNonvirtualFloatMethod(A|V| )=============================
jfloat CallNonvirtualFloatMethod(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return *((jfloat*)&retWord1);
	
}
jfloat CallNonvirtualFloatMethodA(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return *((jfloat*)&retWord1);
	
}
jfloat CallNonvirtualFloatMethodV(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return *((jfloat*)&retWord1);
}
//==========================================================================================

//=====================================CallNonvirtualDoubleMethod(A|V| )=============================
jdouble CallNonvirtualDoubleMethod(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, ...){
	u4 doubleData[2];
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,doubleData[0],doubleData[1],args);
	va_end(args);
	return *((jdouble*)doubleData);
}
jdouble CallNonvirtualDoubleMethodA(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, jvalue *args){
	u4 doubleData[2];
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,doubleData[0],doubleData[1],args);
	return *((jdouble*)doubleData);
	
}
jdouble CallNonvirtualDoubleMethodV(JNIEnv *env,jobject obj,jclass clazz, jmethodID methodID, va_list args){
	u4 doubleData[2];
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,doubleData[0],doubleData[1],args);
	return *((jdouble*)doubleData);
}
//==========================================================================================


jmethodID GetStaticMethodID(JNIEnv *env,jclass clazz, const char *name,const char *sig){
	//if not initialized , initialise the clazz       
	//if(gExceptionThrower->exceptionOccured())   //check for exception during initialization.
	//	return NULL;
	Method* method = ((ClassData*)clazz)->lookupMethod(name,sig);
	if(gExceptionThrower->exceptionOccured())   //check for exceptions during searching for the method
			return NULL;
	return (jmethodID)method;
}


//=====================================CallStaticVoidMethod(A|V| )=============================
void CallStaticVoidMethod(JNIEnv *env,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
}
void CallStaticVoidMethodA(JNIEnv *env,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
}
void CallStaticVoidMethodV(JNIEnv *env,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
}
//==========================================================================================



//=====================================CallStaticObjectMethod(A|V| )=============================
jobject CallStaticObjectMethod(JNIEnv *env,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jobject)retWord1;
	
}
jobject CallStaticObjectMethodA(JNIEnv *env,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jobject)retWord1;
	
}
jobject CallStaticObjectMethodV(JNIEnv *env,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jobject)retWord1;
}
//===========================================================================================


//=====================================CallStaticBooleanMethod(A|V| )=============================
jboolean CallStaticBooleanMethod(JNIEnv *env,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jboolean)retWord1;
	
}
jboolean CallStaticBooleanMethodA(JNIEnv *env,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jboolean)retWord1;
	
}
jboolean CallStaticBooleanMethodV(JNIEnv *env,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jboolean)retWord1;
}
//==========================================================================================


//=====================================CallStaticByteMethod(A|V| )=============================
jbyte CallStaticByteMethod(JNIEnv *env,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jbyte)retWord1;
	
}
jbyte CallStaticByteMethodA(JNIEnv *env,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jbyte)retWord1;
	
}
jbyte CallStaticByteMethodV(JNIEnv *env,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jbyte)retWord1;
}
//==========================================================================================

//=====================================CallStaticCharMethod(A|V| )=============================
jchar CallStaticCharMethod(JNIEnv *env,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jchar)retWord1;
	
}
jchar CallStaticCharMethodA(JNIEnv *env,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jchar)retWord1;
	
}
jchar CallStaticCharMethodV(JNIEnv *env,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jchar)retWord1;
}
//==========================================================================================

//=====================================CallStaticShortMethod(A|V| )=============================
jshort CallStaticShortMethod(JNIEnv *env,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jshort)retWord1;
	
}
jshort CallStaticShortMethodA(JNIEnv *env,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jshort)retWord1;
	
}
jshort CallStaticShortMethodV(JNIEnv *env,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jshort)retWord1;
}
//==========================================================================================


//=====================================CallStaticIntMethod(A|V| )=============================
jint CallStaticIntMethod(JNIEnv *env,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return (jint)retWord1;
	
}
jint CallStaticIntMethodA(JNIEnv *env,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jint)retWord1;
	
}
jint CallStaticIntMethodV(JNIEnv *env,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return (jint)retWord1;
}
//==========================================================================================


//=====================================CallStaticLongMethod(A|V| )=============================
jlong CallStaticLongMethod(JNIEnv *env,jclass clazz, jmethodID methodID, ...){
	u4 longData[2];
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,longData[0],longData[1],args);
	va_end(args);
	return *((jlong*)longData);
}
jlong CallStaticLongMethodA(JNIEnv *env,jclass clazz, jmethodID methodID, jvalue *args){
	u4 longData[2];
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,longData[0],longData[1],args);
	return *((jlong*)longData);
	
}
jlong CallStaticLongMethodV(JNIEnv *env,jclass clazz, jmethodID methodID, va_list args){
	u4 longData[2];
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,longData[0],longData[1],args);
	return *((jlong*)longData);
}
//==========================================================================================


//=====================================CallStaticFloatMethod(A|V| )=============================
jfloat CallStaticFloatMethod(JNIEnv *env,jclass clazz, jmethodID methodID, ...){
	u4 retWord1,retWord2;
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	va_end(args);
	return *((jfloat*)&retWord1);
	
}
jfloat CallStaticFloatMethodA(JNIEnv *env,jclass clazz, jmethodID methodID, jvalue *args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return *((jfloat*)&retWord1);
	
}
jfloat CallStaticFloatMethodV(JNIEnv *env,jclass clazz, jmethodID methodID, va_list args){
	u4 retWord1,retWord2;
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,retWord1,retWord2,args);
	return *((jfloat*)&retWord1);
}
//==========================================================================================

//=====================================CallStaticDoubleMethod(A|V| )=============================
jdouble CallStaticDoubleMethod(JNIEnv *env,jclass clazz, jmethodID methodID, ...){
	u4 doubleData[2];
	va_list args;
	va_start(args,methodID);
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,doubleData[0],doubleData[1],args);
	va_end(args);
	return *((jdouble*)doubleData);
}
jdouble CallStaticDoubleMethodA(JNIEnv *env,jclass clazz, jmethodID methodID, jvalue *args){
	u4 doubleData[2];
	//gExecutionEng->executeMethod((Object*)obj,(Method*)jmethodID,doubleData[0],doubleData[1],args);
	return *((jdouble*)doubleData);
	
}
jdouble CallStaticDoubleMethodV(JNIEnv *env,jclass clazz, jmethodID methodID, va_list args){
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
/*61*/  CallVoidMethod,
/*62*/  CallVoidMethodV,
/*63*/  CallVoidMethodA,
/*64*/  CallNonvirtualObjectMethod,
/*65*/  CallNonvirtualObjectMethodV,
/*66*/  CallNonvirtualObjectMethodA,
/*67*/  CallNonvirtualBooleanMethod,
/*68*/  CallNonvirtualBooleanMethodV,
/*69*/  CallNonvirtualBooleanMethodA,
/*70*/  CallNonvirtualByteMethod,
/*71*/  CallNonvirtualByteMethodV,
/*72*/  CallNonvirtualByteMethodA,
/*73*/  CallNonvirtualCharMethod,
/*74*/  CallNonvirtualCharMethodV,
/*75*/  CallNonvirtualCharMethodA,
/*76*/  CallNonvirtualShortMethod,
/*77*/  CallNonvirtualShortMethodV,
/*78*/  CallNonvirtualShortMethodA,
/*79*/  CallNonvirtualIntMethod,
/*80*/  CallNonvirtualIntMethodV,
/*81*/  CallNonvirtualIntMethodA,
/*82*/  CallNonvirtualLongMethod,
/*83*/  CallNonvirtualLongMethodV,
/*84*/  CallNonvirtualLongMethodA,
/*85*/  CallNonvirtualFloatMethod,
/*86*/  CallNonvirtualFloatMethodV,
/*87*/  CallNonvirtualFloatMethodA,
/*88*/  CallNonvirtualDoubleMethod,
/*89*/  CallNonvirtualDoubleMethodV,
/*90*/  CallNonvirtualDoubleMethodA,
/*91*/  CallNonvirtualVoidMethod,
/*92*/  CallNonvirtualVoidMethodV,
/*93*/  CallNonvirtualVoidMethodA,
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
/*113*/  GetStaticMethodID,
/*114*/  CallStaticObjectMethod,
/*115*/  CallStaticObjectMethodV,
/*116*/  CallStaticObjectMethodA,
/*117*/  CallStaticBooleanMethod,
/*118*/  CallStaticBooleanMethodV,
/*119*/  CallStaticBooleanMethodA,
/*120*/  CallStaticByteMethod,
/*121*/  CallStaticByteMethodV,
/*122*/  CallStaticByteMethodA,
/*123*/  CallStaticCharMethod,
/*124*/  CallStaticCharMethodV,
/*125*/  CallStaticCharMethodA,
/*126*/  CallStaticShortMethod,
/*127*/  CallStaticShortMethodV,
/*128*/  CallStaticShortMethodA,
/*129*/  CallStaticIntMethod,
/*130*/  CallStaticIntMethodV,
/*131*/  CallStaticIntMethodA,
/*132*/  CallStaticLongMethod,
/*133*/  CallStaticLongMethodV,
/*134*/  CallStaticLongMethodA,
/*135*/  CallStaticFloatMethod,
/*136*/  CallStaticFloatMethodV,
/*137*/  CallStaticFloatMethodA,
/*138*/  CallStaticDoubleMethod,
/*139*/  CallStaticDoubleMethodV,
/*140*/  CallStaticDoubleMethodA,
/*141*/  CallStaticVoidMethod,
/*142*/  CallStaticVoidMethodV,
/*143*/  CallStaticVoidMethodA,
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
 
 
 
 
 