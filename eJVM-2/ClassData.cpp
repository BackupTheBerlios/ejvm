#include"ClassData.h"
#include"Heap.h"
#include<stdio.h>

/* the constructor takes a stream of bytes as a parameter */
ClassData::ClassData(byte inputFile [])
{
		int inputPtr; // pointer to be advanced in the input stream
		u2 i;
		u2 CPCount;
		
		/* here, there exist magic number, minor and major numbers */

		inputPtr=8;  // initialize inputPtr at the beginning of CPCount

		/* extract constant pool count and advance the input pointer */
		CPCount =( ( (u2)inputFile[inputPtr] )<<8) + inputFile[inputPtr+1];
		inputPtr+=2;
		
		/* ask the heap to create the constant pool */
		constantPool = Heap::createCP(inputFile,CPCount, &inputPtr,this);

		/* extract accessFlags, thisClass, superClass and advance the input pointer */
		accessFlags = ( ((u2)inputFile[inputPtr])<<8 ) + inputFile[inputPtr+1];
		inputPtr+=2;
		thisClass = ( ((u2)inputFile[inputPtr])<<8 ) + inputFile[inputPtr+1];
		inputPtr+=2;
		superClass = ( ((u2)inputFile[inputPtr])<<8) + inputFile[inputPtr+1];
		inputPtr+=2;
		
		/* extract interfacesCount and advance the input pointer */
		interfacesCount =( ((u2)inputFile[inputPtr])<<8 ) + inputFile[inputPtr+1];
		inputPtr+=2;
		/* create the interfaces array and fill it */
		interfaces = Heap::createInterfaces(interfacesCount);
		for( i=0 ; i < interfacesCount ; i++)
		{
			interfaces[i] = ( ((u2)inputFile[inputPtr])<<8 ) + inputFile[inputPtr+1];
			inputPtr+=2;
		}

		/* extract fieldsCount and advance the input pointer */
		fieldsCount = ( ((u2)inputFile[inputPtr])<<8 ) + inputFile[inputPtr+1];
		inputPtr+=2;
		/* create the fields table and fill it */
		fields = Heap::createFileds(fieldsCount);
		for( i=0 ; i < fieldsCount ; i++)
			fields[i] = Heap::createFieldData(inputFile, &inputPtr,constantPool);

		/* extract methodsCount and advance the input pointer */
		methodsCount =( ((u2)inputFile[inputPtr])<<8 )+ inputFile[inputPtr+1];
		inputPtr+=2;
		/* create the methods table and fill it */
		methods = Heap::createMethods(methodsCount);
		for(i=0 ; i < methodsCount ; i++)
			methods[i] = Heap::createMethodData(inputFile, &inputPtr,constantPool);

		/* here, there exist the attributes count and attributes table */
		
		/* to load and resolve the super class */
/////////////////	   	constantPool-> getClassData(superClass);
		/* to load and resolve the superInterfaces */
/////////////////		for( i=0 ; i < interfacesCount ; i++)
/////////////////			constantPool-> getClassData(interfaces[i]);
}

ClassData::~ClassData()
{
}


void ClassData:: prepare(void)
{
	/* get the size of an object of the parent class */
	ClassData * parentClass=constantPool->getClassData(superClass);
	objectSize = parentClass-> getObjectSize();
	for(u2 i=0; i < fieldsCount; i++)
	{
		/* if the field is static, then set it to the default value */
		if(fields[i]-> isStatic())
			fields[i]-> setDefaultValue();
		
		else /* this part is for nonstatic fields only */
		{
			/* set the offset of the field in the cbject image */
			fields[i]-> setOffset(objectSize);
			/* update the value of the object size */
			objectSize += fields[i]-> getSize();
		}
	}
	/* now create the method table */
	///////////////////////createMethodTable();
}

bool ClassData:: isInitialized(void)
{ return initialized; }

void ClassData:: initialize(void)
{
	ClassData * myParent;
	Method * clInit=NULL;
	u2 i;
	
	myParent = constantPool->getClassData(superClass);
	if( !(myParent->isInitialized()) )
		myParent->initialize();
	/* search in this class */
	for(i=0; i<methodsCount ; i++)
	{
		if(strcmp(methods[i]-> getName() ,"()")==0 ) /* another method */
		{
			clInit =  methods[i];
			break;
		}	
	}	
	if(clInit)
	;//execEng->exec(clInit);	
	initialized = true;
}


Field * ClassData:: lookupField(char *name, char*desc)
{ 
	u2 i;
	/* search in this class */
	for(i=0; i<fieldsCount ; i++)
	{
		if(       (strcmp(name , fields[i]-> getName())==0  )
		&&    (strcmp(desc  , fields[i]->getDesc()  )==0)       ) /* another method */
			return fields[i];
	}
	/* search the super interfaces */
	/* what is meant by interface extended by this class */
	ClassData * interface;
	Field * field;
	for(i=0; i<interfacesCount ; i++)
	{
		interface = constantPool-> getClassData(interfaces[i]);
		if( (field = interface->lookupField(name,desc)) != NULL)
			return field;
	}
	/* search in the super class */
	ClassData * myParent=constantPool->getClassData(superClass);
	return myParent->lookupField(name,desc);
}

Method * ClassData:: lookupMethod(char *name, char*desc)
{
	if(this->isInterface())
	;/////////exception();
	u2 i;
	/* search in this class */
	for(i=0; i<methodsCount ; i++)
	{
		if(              (strcmp(name , methods[i]-> getName() )==0)
		&&           (strcmp(desc  , methods[i]->getDesc()   )==0) ) /* another method */
			return methods[i];
	}
	/* search in the super class */
	Method * method;
	ClassData * myParent=constantPool->getClassData(superClass);
	if( (method=myParent->lookupMethod(name,desc)) != NULL)
		return method;
	/* search the super interfaces */
	/* what is meant by sueprinterface of interfaces 
	 * directly implemented by this class */
	ClassData * interface;
	for(i=0; i<interfacesCount ; i++)
	{
		interface = constantPool-> getClassData(interfaces[i]);
		if( (method = interface->lookupMethod(name,desc)) != NULL)
			return method;
	}
	return NULL;
}

Method* ClassData:: lookupInterfaceMethod(char *name,char *desc)
{
	if(! (this->isInterface()) )
	;////////////////////////
	u2 i;
	/* search in this interface */
	for(i=0; i<methodsCount ; i++)
	{
		if(   (strcmp(name ,methods[i]-> getName())==0)
		&& (strcmp(desc , methods[i]->getDesc() )==0)  ) /* another method */
			return methods[i];
	}
	/* search the super interfaces */
	/* what is meant by sueprinterface of interfaces 
	 * directly implemented by this class */
	ClassData * interface;
	Method * method;
	for(i=0; i<interfacesCount ; i++)
	{
		interface = constantPool-> getClassData(interfaces[i]);
		if( (method = interface->lookupInterfaceMethod(name,desc)) != NULL)
			return method;
	}
	/* search in class Object */
	return NULL;
}

u2 ClassData:: getObjectSize(void)
{ return objectSize; }

/* till now assume that there is no method 
 * overriding for simpilicity */
void ClassData::createMethodTable(void)
{
	u2 count,i;
	ClassData * parentClass=constantPool->getClassData(superClass); 
	Method ** tempTable = parentClass->getMethodTable();
	count = parentClass->methodTableEntriesCount;
	methodTableEntriesCount = count + methodsCount;
	methodTable = new Method * [methodTableEntriesCount];
	for(i=0 ;i<count ;i++)
		methodTable[i] = tempTable[i];
	for(i=0 ;i<methodsCount ;i++)
		methodTable[i+count] = methods[i];		
}

Method ** ClassData::getMethodTable(void)
{ return methodTable; }

bool ClassData:: canCastedTo(ClassData *classData)
{
	/* if this class is a class */
	if( ! isInterface() )
	{
		/* the other class is a class */
		if( !(classData->isInterface()) )
		{
			if(isDescendentOf(classData)||this==classData)
				return true;
		}
		else /* the other class is an interface */
		{
			if(isImplement(classData))
				return true;
		}
	}
	/* this class is an interface */
	else
	{
		/* the other class is a class */
		if( !(classData->isInterface()) )
		{
			if(classData->getFQName()=="Object")//another function
				return true;
		}
		else /* the other class is an interface */
		{
			///////what is meant by superinterfaces
			if(this==classData||isDescendentOf(classData))
				return true;
		}
	}
	return false;
}

bool ClassData:: isImplement(ClassData * theInterface)
{
	for(u2 i=0; i<interfacesCount; i++)
	{
		if(theInterface==constantPool->getClassData(i))
			return true;
	}
	return false;
}

char * ClassData :: getFQName(void)
{ return constantPool->getClassName(thisClass); }

bool ClassData:: isPublic(void)
{
	if( ( accessFlags & ( ( (u2)1 ) ) ) ==0 )
		return false;
	return true;	
}
 
bool ClassData:: isFinal(void)
{
	if( ( accessFlags & ( ( (u2)1 )<<1 ) ) ==0 )
		return false;
	return true;	
} 

bool ClassData:: treatSuperMethodsSpecially()
{
	if( ( accessFlags & ( ( (u2)1 )<< 5 ) ) ==0 )
		return false;
	return true;
}

bool ClassData:: isInterface(void)
{
	if( ( accessFlags & ( ( (u2)1 )<< 9 ) ) ==0 )
		return false;
	return true;	
}

bool ClassData:: isAbstract(void)
{
	if( ( accessFlags & ( ( (u2)1 )<< 10 ) ) ==0 )
		return false;
	return true;	
}

Method * ClassData:: getActualMethod(Method* nonActualMethod)
{
return NULL;
}

bool ClassData:: isDescendentOf(ClassData* classData)
{
	ClassData * myParent=constantPool->getClassData(superClass);
	if( classData == myParent )
		return true;
	return 	myParent->isDescendentOf(classData);
}

