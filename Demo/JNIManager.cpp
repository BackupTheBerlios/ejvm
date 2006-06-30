#include "JNIManager.h"
#include "Method.h"
#include "ClassData.h"
#include "ExecutionEng.h"
#include <iostream>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
using std::cout;
using std::endl;
extern JNINativeInterface functionTable;
extern const JNINativeInterface * JNI_env;
typedef void (*anyFunction)();




JNIManager * JNIManager::instance = NULL;
JNIManager * JNIManager::getInstance(){
	return (instance==NULL)?(instance=new JNIManager()):instance;
}
JNIManager::JNIManager()
{
	libCount = 0;
	loadLib("libjniNatives.so");
	
}

JNIManager::~JNIManager()
{
}

void JNIManager::callNativeMethod(Method *method, u4 args[],int argsCount){
	//test args values...
	//cout <<endl<<endl<<ExecutionEng::computFloat(args[0])<<endl;
	//cout <<(jint)args[0]<<endl;
	
	//cout <<endl<<endl<<ExecutionEng::computFloat(args[1])<<endl;
	//cout <<(jint)args[1]<<endl;
	
	
	//first version of this funciton: I will assume 
	//		1- The native method has no arguments (so no need to use the ffi functions for now....)
	//		2- The native methods resides in one library called jniNatives
	//		3- No overloaded native methods....
	
	//get name of the method
	const char * name = mangleMethodName(method->getName(),method->getOwnerClassData()->getFQName());
	void * nativeFunctionPtr = searchInLoadedLibs(name);
	
	
	//if using FFI we should do the following:
			//Get the ffi structures required (ffi_cif and the array of values of the arguments (see the example in .../soruces/jni/testFFI.cpp
			//Call the function using the ffi_Call function
	ffi_type ** argsTypes = new ffi_type *[argsCount+2]; //the 2 is for JNIEnv and jobject passed to the native method...		
	ffi_type * retType;
	void ** values = new void*[argsCount+2]; //to hold the values of the arguments
	void * retValue;
	ffi_cif *cif= new ffi_cif;		
	generateFFI_CIF(method,cif,argsCount,argsTypes,retType);
	getValues(method,args,values,retValue,argsCount);
	ffi_call(cif,(anyFunction)nativeFunctionPtr,retValue,values);
	//cout << *((float*)retValue);
	
	//we should here pass the return value to the interpreter....
	
	//For now we will not use the FFI , just call the native function with (JNIEnv*, jobject) parameters....

//	typedef  void(*simpleNativeFunction)(JNIEnv*,jobject);
//	((simpleNativeFunction)nativeFunctionPtr)(&JNI_env,NULL);
	
	
	for(int i =0;i<argsCount+2;i++){
		//cout<<i<<endl;
		delete values[i];
	}
	delete[] values	;
	delete name;
	delete cif;
}


const char * JNIManager::mangleMethodName(char * methodName, char *className){
	char * mangled = new char [6+strlen(methodName)+strlen(className)];
    strcpy(mangled,"Java_");
    strcat(mangled,className);
    strcat(mangled,"_");
    strcat(mangled,methodName);
    int i=0;
    while(mangled[i]!='\0') {
            if(mangled[i]=='/')
                    mangled[i]='_';
            i++;
    }
    return mangled;

}

void * JNIManager::searchInLoadedLibs(const char* name){
	 void * func;
	 for(int i = 0 ;i< libCount;i++)
	 	if((func = dlsym(loadedLibs[i],name)) )return func;
	 return NULL; //not found
}


void JNIManager::loadLib(const char* libName){
	if(libCount > MAX_LIBS-1){
		//cout <<"Exception:Can't load the "<<libName<<"native library"<<endl;
		exit(1);
	}	
	loadedLibs[libCount++] = dlopen(libName,RTLD_LAZY);
}


void JNIManager::generateFFI_CIF(Method * method, ffi_cif * cif,int argsCount,ffi_type** argsTypes,ffi_type *&rType){
	//ffi_type *rType;
	//ffi_type ** argsTypes = new ffi_type *[argsCount+2]; //the 2 is for JNIEnv and jobject passed to the native method...
	
	char * p=method->getDesc();
	
	argsTypes[0] = &ffi_type_pointer;
	argsTypes[1] = &ffi_type_pointer;
	int i=2;
	p++;     /* skip start ( */	
	while(*p != ')')
	{               

		//getting the arguments...    
		switch (*p){
			case 'B':
				argsTypes[i] = &ffi_type_schar;
				i++; p++;
				break;
			case 'C':
				argsTypes[i] = &ffi_type_ushort;
				i++; p++;
				break;	
			case 'D':
				argsTypes[i] = &ffi_type_double;
				i++; p++;
				break;
			case 'F':
				argsTypes[i] = &ffi_type_float;
				i++; p++;
				break;	
			case 'I':
				argsTypes[i] = &ffi_type_sint;
				i++; p++;
				break;	
			case 'J':
				argsTypes[i] = &ffi_type_slong;
				i++; p++;
				break;	
			case 'L':
				argsTypes[i] = &ffi_type_pointer;
				i++;
				while(*(p++) != ';');              
				break;	
			case 'S':
				argsTypes[i] = &ffi_type_sshort;
				i++; p++;
				break;
			case 'Z':
				argsTypes[i] = &ffi_type_uchar;
				i++; p++;
				break;	
			case '[':
				argsTypes[i] = &ffi_type_pointer;
				i++;
				while(*(p++)=='[');
				if(*p == 'L')
					while(*(p++) != ';');
				else
					p++;	              
				break;		
		}  
	 }   
	p++; //skip ')'
	 	//getting the return type...
	switch (*p){
		case 'B':
			rType = &ffi_type_schar;
			break;
		case 'C':
			rType = &ffi_type_ushort;
			break;	
		case 'D':
			rType = &ffi_type_double;
			break;
		case 'F':
			rType = &ffi_type_float;
			break;	
		case 'I':
			rType = &ffi_type_sint;
			break;	
		case 'J':
			rType = &ffi_type_slong;
			break;	
		case 'L': case '[':
			rType = &ffi_type_pointer;
			i++;
			while(*(p++) != ';');              
			break;	
		case 'S':
			rType = &ffi_type_sshort;
			break;
		case 'Z':
			rType = &ffi_type_uchar;
			break;	
				
	}                                                                  
	//getting the ffi_cif
	
	 if(!(ffi_prep_cif(cif,FFI_DEFAULT_ABI,argsCount+2,rType,argsTypes)==FFI_OK))
	 ;	////cout <<"error in ffi_cif generation"<<endl;	
 	
}

//void JNIManager::getValues(Method* method,u4 args[],void ** values,void *&retValue,int argsCount){
//	char * p=method->getDesc();
//	
//	
//	p++;     /* skip start ( */	
//	values[0] = new jobject;
//	*((JNIEnv **)values[0]) = &JNI_env;
//	values[1] = new jobject;
//	*((jobject*)values[1]) = NULL;
//	//p: iterates on the desc
//	//i: iterates on the values
//	//j: iterates on the args
//	
//	int i=2;  //number of values = argCount+2
//	int j=0;
//	while(*p != ')')
//	{               
//	//getting the arguments...    
//		switch (*p){
//			case 'B':
//				values[i] = new jbyte;
//				*((jbyte*)values[i]) = (jbyte)args[j];
//				i++; p++;j++;
//				break;
//			case 'C':
//				values[i] = new jchar;
//				*((jchar*)values[i]) = (jchar)args[j];
//				i++; p++;j++;
//				break;
//			case 'D':
//				values[i] = new jdouble;
//				*((jdouble*)values[i]) = ExecutionEng::computDouble(args[j],args[j+1]);
//				i++; p++;j+=2;
//				break;
//			case 'F':
//				values[i] = new jfloat;
//				*((jfloat*)values[i]) =  ExecutionEng::computFloat(args[j]);;
//				i++; p++;j++;
//				break;;	
//			case 'I':
//				values[i] = new jint;
//				*((jint*)values[i]) = (jint)args[j];
//				i++; p++;j++;
//				break;
//			case 'J':
//				values[i] = new jlong;
//				*((jlong*)values[i]) = *((jlong*)(args+j));
//				i++; p++;j+=2;
//				break;	
//			case 'L':
//				values[i] = new jobject;
//				*((jobject*)values[i]) = (jobject)args[j];
//				i++;j++;
//				while(*(p++) != ';');              
//				break;
//			case 'S':
//				values[i] = new jshort;
//				*((jshort*)values[i]) = (jshort)args[j];
//				i++; p++;j++;
//				break;
//			case 'Z':
//				values[i] = new jboolean;
//				*((jboolean*)values[i]) = (jboolean)args[j];
//				i++; p++;j++;
//				break;
//			case '[':
//				values[i] = new jobject;
//				*((jobject*)values[i]) = (jobject)args[j];
//				i++;j++;
//				while(*(p++)=='[');
//				if(*p == 'L')
//					while(*(p++) != ';');
//				else
//					p++;	              
//				break;		
//		}  
//	 }   
//	 
//	 
//	 p++; //skip ')'
//	 //allocate the return value...
//	 switch (*p){
//			case 'B':
//				retValue = new jbyte;
//				break;
//			case 'C':
//				retValue = new jchar;
//				break;
//			case 'D':
//				retValue = new jdouble;
//				break;
//			case 'F':
//				retValue = new jfloat;
//				break;;	
//			case 'I':
//				retValue = new jint;
//				break;
//			case 'J':
//				retValue = new jlong;
//				break;	
//			case 'L':
//				retValue = new jobject;
//				break;
//			case 'S':
//				retValue = new jshort;
//				break;
//			case 'Z':
//				retValue = new jboolean;
//				break;
//			case '[':
//				retValue = new jobject;
//				break;		
//		}  
//	 
//	
//}


void JNIManager::getValues(Method* method,u4 args[],void ** values,void *&retValue,int argsCount){
	char * p=method->getDesc();
	
	
	p++;     /* skip start ( */	
	values[0] = new jobject;
	*((JNIEnv **)values[0]) = &JNI_env;
	values[1] = new jobject;
	*((jobject*)values[1]) = NULL;
	//p: iterates on the desc
	//i: iterates on the values
	//j: iterates on the args
	
	int i=2;  //number of values = argCount+2
	int j=0;
	while(*p != ')')
	{               
	//getting the arguments...    
		switch (*p){
			case 'B':
				values[i] = new jbyte;
				*((jbyte*)values[i]) = (jbyte)args[j];
				i++; p++;j++;
				break;
			case 'C':
				values[i] = new jchar;
				*((jchar*)values[i]) = (jchar)args[j];
				i++; p++;j++;
				break;
			case 'D':
				values[i] = new jdouble;
				*((jdouble*)values[i]) = ExecutionEng::computDouble(args[j],args[j+1]);
				i++; p++;j+=2;
				break;
			case 'F':
				values[i] = new jfloat;
				*((jfloat*)values[i]) =  ExecutionEng::computFloat(args[j]);;
				i++; p++;j++;
				break;;	
			case 'I':
				values[i] = new jint;
				*((jint*)values[i]) = (jint)args[j];
				i++; p++;j++;
				break;
			case 'J':
				values[i] = new jlong;
				*((jlong*)values[i]) = *((jlong*)(args+j));
				i++; p++;j+=2;
				break;	
			case 'L':
				values[i] = new jobject;
				*((jobject*)values[i]) = (jobject)args[j];
				i++;j++;
				while(*(p++) != ';');              
				break;
			case 'S':
				values[i] = new jshort;
				*((jshort*)values[i]) = (jshort)args[j];
				i++; p++;j++;
				break;
			case 'Z':
				values[i] = new jboolean;
				*((jboolean*)values[i]) = (jboolean)args[j];
				i++; p++;j++;
				break;
			case '[':
				values[i] = new jobject;
				*((jobject*)values[i]) = (jobject)args[j];
				i++;j++;
				while(*(p++)=='[');
				if(*p == 'L')
					while(*(p++) != ';');
				else
					p++;	              
				break;		
		}  
	 }   
	 
	 
	 p++; //skip ')'
	 //allocate the return value...
	 switch (*p){
			case 'B':
				retValue = new jbyte;
				break;
			case 'C':
				retValue = new jchar;
				break;
			case 'D':
				retValue = new jdouble;
				break;
			case 'F':
				retValue = new jfloat;
				break;;	
			case 'I':
				retValue = new jint;
				break;
			case 'J':
				retValue = new jlong;
				break;	
			case 'L':
				retValue = new jobject;
				break;
			case 'S':
				retValue = new jshort;
				break;
			case 'Z':
				retValue = new jboolean;
				break;
			case '[':
				retValue = new jobject;
				break;		
		}  
	 
	
}

