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
//------------------------------------------------------------------------------
Heap * Heap::heapInstance=NULL;
//-------------------------------------------------------------------------------
Heap * Heap::getInstance()
{
	if(heapInstance == NULL)
		heapInstance= new Heap;
	
	if(heapInstance == NULL)
	{
		//cout<<"Heap:GetInstance: NO Sufficient Memory "<<endl;
		exit(1);
	}
	
	return heapInstance;
	
}
//---------------------------------------------------------------------------------
void Heap::deleteHeap()
{
	delete heapInstance;
	heapInstance = NULL;
}
//--------------------------------------------------------------------------------
ClassData * Heap::lookupClassData(const char *className)
{
		map < Path, ClassData * >::iterator p;
		
		p = Hash.find(Path(className));
		
		//Hello.class
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
	
	for(int i=0;i<= objectCount;i++)
		delete object[i];
		
	delete []object;
	//cout<<"Heap destructor"<<endl;
}
//------------------------------------------------------------

ClassData * Heap::createClassData(const char* name, const byte * classFile)//******************************************************************************************u1
{
	ClassData * p = new ClassData(name,classFile);
	//return new ClassData(classFile);
	if(p == NULL)
	{
		//cout<<"Heap:createClassData: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
	
}
//-----------------------------------------------------------------------------
ClassData * Heap::createArrayClassData (const char*name)
{
	ClassData * p = new ClassData(name);
	//return new ClassData(classFile);
	if(p == NULL)
	{
		//cout<<"Heap:createArrayClassData: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}
//----------------------------------------------------------------------
Heap::Heap():
	objectCount(0)
{
	this->object = new Object * [20];
	if(this->object == NULL)
	{
		//cout<<"Heap:Heap: NO Sufficient Memory "<<endl;
		exit(1);
	}
}
//------------------------------------------------------------------------
Object* Heap::createObject(ClassData* classData)
{
	Object *ob = new Object(classData);
	if(ob == NULL)
	{
		//cout<<"Heap:createObject: NO Sufficient Memory "<<endl;
		exit(1);
	}
	object[objectCount] = ob;
	objectCount++;
	return  ob;
}

ConstantPool* Heap:: createCP(const byte inputFile [],int cpCount,int * inputPtr, ClassData * theClass)
{
	ConstantPool * p = new ConstantPool(inputFile,cpCount,inputPtr,theClass);
	if(p == NULL)
	{
		//cout<<"Heap:createCP: NO Sufficient Memory "<<endl;
		exit(1);
	}
//	return new ConstantPool(inputFile,cpCount,inputPtr,theClass);
	return p;
}
ConstantPool* Heap:: createArrayCP(const char* arrayName ,ClassData *  theClass )
{
	ConstantPool * p = new ConstantPool(arrayName,theClass);
	if(p == NULL)
	{
		//cout<<"Heap:createArrayCP: NO Sufficient Memory "<<endl;
		exit(1);
	}
	//return new ConstantPool(arrayName,theClass);
	return p;
}	
u2 * Heap:: createInterfaces(int count)
{
	u2 *p =new u2 [count];
	if(p == NULL)
	{
		//cout<<"Heap:createInterfaces: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}

Field ** Heap:: createFileds(int count)
{
	Field **p =new Field * [count];
	if(p == NULL)
	{
		//cout<<"Heap:createFileds: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}

Field * Heap:: createFieldData(const byte *inputFile , int * inputPtr,
ConstantPool * cp)
{
	Field * p =new Field(inputFile,inputPtr,cp);
	if(p == NULL)
	{
		//cout<<"Heap:createFieldData: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}

Method** Heap:: createMethods(int count)
{
	Method**p =new Method * [count];
	if(p == NULL)
	{
		//cout<<"Heap:createMethods: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}

Method * Heap:: createMethodData(const byte *inputFile, int * inputPtr,
ConstantPool * cp)
{
	Method *p =new Method(inputFile,inputPtr,cp);
	if(p == NULL)
	{
		//cout<<"Heap:createMethodData: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}

byte ** Heap:: createCPTable(int count)
{		
	byte **p =new byte * [count];
	if(p == NULL)
	{
		//cout<<"Heap:createCPTable: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}

byte * Heap:: createCPTableEntry(int count)
{
	byte *p=new byte[count];
	if(p == NULL)
	{
		//cout<<"Heap:createCPTableEntry: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}

byte ** Heap:: createAttrTable(int count)
{
	byte **p = new byte * [count];
	if(p == NULL)
	{
		//cout<<"Heap:createAttrTable: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}
	
void ** Heap:: createPointerTable(int CPCount)
{
	void **p= new void * [CPCount];
	if(p == NULL)
	{
		//cout<<"Heap:createPointerTable: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}
byte * Heap:: createAttrTableEntry(int count)
{
	byte *p= new byte[count];
	if(p == NULL)
	{
		//cout<<"Heap:createAttrTableEntry: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}

byte * Heap:: createByteArray(int length)
{
	byte * p = new byte [length];
	if(p == NULL)
	{
		//cout<<"Heap:createByteArray: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return p;
}
Object *  Heap::createArrayObject(int dims,int* lengths ,int type,ClassData * myClass,ClassData * classType)
{
	Object * ob = new Object(dims,lengths,type,myClass,classType);
	if(ob == NULL)
	{
		//cout<<"Heap:createArrayObject: NO Sufficient Memory "<<endl;
		exit(1);
	}
	return ob;
}
