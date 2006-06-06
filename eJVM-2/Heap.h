#ifndef HEAP_H_
#define HEAP_H_
#include "typeDefs.h"
#include "ConstantPool.h"
#include "Field.h"
#include "Method.h"

#include <iostream>
#include <map>
#include <cstring>
#include <fstream>

using namespace std;

class Object;
class ClassData;
//class ConstantPool;
//class Field;
//class Method;

//***************************************************************************************************
class Path
{
	private:
		char str[80];
		
	public:
		Path() { strcpy (str, "") ;}
		Path(char * s){ strcpy(str,s);}
		
		char * get(){ return str;}
};
//***********************************************************************************

class Heap
{
	public:
		static Heap * getInstance();//Finished
		static void deleteHeap();
		ClassData * lookupClassData(char *className);
		ClassData * addToHash(ClassData * cptr);
		int HashSize();
		ClassData * createClassData (byte classFile[]);
		
		
		Object* createObject(ClassData* classData);
		
	
		static ConstantPool* createCP(byte inputFile [],int cpCount,int * inputPtr, ClassData * theClass);
		static u2 * createInterfaces(int);
		static Field ** createFileds(int);
		static Field * createFieldData(byte * , int *,ConstantPool *);
		static Method ** createMethods(int);
		static Method * createMethodData(byte *, int *,ConstantPool *);
		static byte ** createCPTable(int);
		static byte * createCPTableEntry(int CPCount);
		static void ** createPointerTable(int CPCount);
		static byte ** createAttrTable(int);
		static byte * createAttrTableEntry(int);
		
	
private:
	~Heap();
	Heap();	
	map < Path, ClassData * >  Hash;
	static Heap * heapInstance;
};

#endif /*HEAP_H_*/
