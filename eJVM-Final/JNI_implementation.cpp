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
/*33*/  NULL,
/*34*/  NULL,
/*35*/  NULL,
/*36*/  NULL,
/*37*/  NULL,
/*38*/  NULL,
/*39*/  NULL,
/*40*/  NULL,
/*41*/  NULL,
/*42*/  NULL,
/*43*/  NULL,
/*44*/  NULL,
/*45*/  NULL,
/*46*/  NULL,
/*47*/  NULL,
/*48*/  NULL,
/*49*/  NULL,
/*50*/  NULL,
/*51*/  NULL,
/*52*/  NULL,
/*53*/  NULL,
/*54*/  NULL,
/*55*/  NULL,
/*56*/  NULL,
/*57*/  NULL,
/*58*/  NULL,
/*59*/  NULL,
/*60*/  NULL,
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











	
};
const JNINativeInterface * env = &functionTable;





/**
 * @brief This function tests the functionality of the jni functions
 */
 void testJNI(){
 	cout<<"GetVersion():" << env->GetVersion(&env)<< endl;
 }
 
 
 
 
 