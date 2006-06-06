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
	ClassData * getClassData(char * className);
	/**
	 * if success return pointer to the loaded classData
	 * if failed return NULL
	 */
	 
private:

		~Loader(){cout<<"Loader destructor"<<endl;}
		Loader();
		byte * makeArrayInCPP(char * fileName);
		static Loader * loaderInstance;
};

#endif /*LOADER_H_*/
