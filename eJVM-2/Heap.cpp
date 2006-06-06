#include "Heap.h"
//#include "Field.h"
//#include "Method.h"
#include <stdio.h>
#include "ClassData.h"

//***************************************************************************************************
bool operator<(Path a, Path b)
{
	return strcmp(a.get(),b.get()) < 0;
}
//***************************************************************************************************
//---------------------------------------------------------------------
Heap * Heap::heapInstance=NULL;
//----------------------------------------------------------------------
Heap * Heap::getInstance()
{
	if(heapInstance == NULL)
		heapInstance= new Heap;
	
	return heapInstance;
	
}
//--------------------------------------------------------------------
void Heap::deleteHeap()
{
	delete heapInstance;
	heapInstance = NULL;
}
//-----------------------------------------------------------------------
ClassData * Heap::lookupClassData(char *className)
{
		map < Path, ClassData * >::iterator p;
		
		p = Hash.find(Path(className));
		
		if ( p != Hash.end())
			return p->second;
		else 
			return NULL;
	
}
//-------------------------------------------------------------------------------
ClassData * Heap::addToHash(ClassData * cptr)
{
	Hash.insert(pair<Path, ClassData  *>(Path(cptr->getFQName()),cptr));
	return cptr;
}
//-------------------------------------------------------------------

int Heap::HashSize()
{
	return (this->Hash).size();
}
//-----------------------------------------------------------
Heap::~Heap()
{
	map < Path, ClassData * >::iterator pos;
	for (pos = Hash.begin(); pos != Hash.end(); ++pos) {
			delete pos->second;
			pos->second = NULL;
	}
	cout<<"Heap destructor"<<endl;
}
//------------------------------------------------------------

ClassData * Heap::createClassData(byte * classFile)//******************************************************************************************u1
{
	return new ClassData(classFile);
	
}
//---------------------------------------------------------------------------
Heap::Heap()
{
}


ConstantPool* Heap:: createCP(byte inputFile [],int cpCount,int * inputPtr, ClassData * theClass)
{
	return new ConstantPool(inputFile,cpCount,inputPtr,theClass);
}
	
u2 * Heap:: createInterfaces(int count)
{
	u2 *p =new u2 [count];
	return p;
}

Field ** Heap:: createFileds(int count)
{
	Field **p =new Field * [count];
	return p;
}

Field * Heap:: createFieldData(byte *inputFile , int * inputPtr,
ConstantPool * cp)
{
	Field * p =new Field(inputFile,inputPtr,cp);
	return p;
}

Method** Heap:: createMethods(int count)
{
	Method**p =new Method * [count];
	return p;
}

Method * Heap:: createMethodData(byte *inputFile, int * inputPtr,
ConstantPool * cp)
{
	Method *p =new Method(inputFile,inputPtr,cp);
	return p;
}

byte ** Heap:: createCPTable(int count)
{		
	byte **p =new byte * [count];
	return p;
}

byte * Heap:: createCPTableEntry(int count)
{
	byte *p=new byte[count];
	return p;
}

byte ** Heap:: createAttrTable(int count)
{
	byte **p = new byte * [count];
	return p;
}
	
void ** Heap:: createPointerTable(int CPCount)
{
	void **p= new void * [CPCount];
	return p;
}
byte * Heap:: createAttrTableEntry(int count)
{
	byte *p= new byte[count];
	return p;
}
