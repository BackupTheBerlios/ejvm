#ifndef LOADER_H_
#define LOADER_H_
#include "typeDefs.h"
#include <iostream>

#include <cstring>
#include <fstream>
using namespace std;
class ClassData;
class Object;


class Loader
{
public:
	static Loader * getInstance();//finished
	static void deleteLoader();
	/**
	 * psudoCode:
	 * if(!(classData=lookupdClassData(className)))
	 * 		u1[] classFile = classFiel2bytes(className);
	 * 		classData = Heap->createClassData(classFile);
	 * return classData;
	 */
	ClassData * getClassData(const char * className);
	/**
	 * if success return pointer to the loaded classData
	 * if failed return NULL
	 */
	 
	 /**
	  * This function searches for the className, if found return pointer to the ClassData, if not found create the classData
	  * by the given array instead of opening any files....
	  */ 
	ClassData * getClassData(const char * className, const byte classFile[]){
		//This function should be implemented, for now it will return NULL;
		return NULL;
	}
	 
private:

		~Loader(){/*cout<<"Loader destructor"<<endl;*/;}
		Loader();
		byte * makeArrayInCPP(char * fileName);
		static Loader * loaderInstance;
};

#endif /*LOADER_H_*/
