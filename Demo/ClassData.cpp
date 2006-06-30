#include "ClassData.h"
#include "Heap.h"
#include <stdio.h>
#include "ExecutionEng.h"
/* the constructor takes a stream of bytes as a parameter */
ClassData::ClassData(const char *name, const byte inputFile [])
{
		int inputPtr; // pointer to be advanced in the input stream
		u2 i;
		u2 CPCount;
//	////f//printf(stdout,"Let the file parsing BEGIN\n");		
		/* here, there exist magic number, minor and major numbers */

		inputPtr=8;  // initialize inputPtr at the beginning of CPCount

		/* extract constant pool count and advance the input pointer */
		CPCount =( ( (u2)inputFile[inputPtr] )<<8) + inputFile[inputPtr+1];
		inputPtr+=2;
		
//	////f//printf(stdout,"getting the constant pool count => %d entries\n",CPCount-1);
////printf("Ask the heap to create the constant pool\n");
		/* ask the heap to create the constant pool */
		constantPool = Heap::createCP(inputFile,CPCount, &inputPtr,this);
////printf("Getting the acess flags of the class\n");
		/* extract accessFlags, thisClass, superClass and advance the input pointer */
		accessFlags = ( ((u2)inputFile[inputPtr])<<8 ) + inputFile[inputPtr+1];
		inputPtr+=2;

	////f//printf(stdout,"getting the access flags of the class\n");

		thisClass = ( ((u2)inputFile[inputPtr])<<8 ) + inputFile[inputPtr+1];
		inputPtr+=2;

	////f//printf(stdout,"getting the current class index in the constant pool => %d \n",thisClass);
////printf("getting the current class index in the constant pool => %d \n",thisClass);
		superClass = ( ((u2)inputFile[inputPtr])<<8) + inputFile[inputPtr+1];
		inputPtr+=2;
		
	//f//printf(stdout,"getting the super class index in the constant pool => %d \n",superClass);
////printf("getting the super class index in the constant pool => %d \n",superClass);
		/* extract interfacesCount and advance the input pointer */
		interfacesCount =( ((u2)inputFile[inputPtr])<<8 ) + inputFile[inputPtr+1];
		inputPtr+=2;

	//f//printf(stdout,"getting the interfaces count => %d \n",interfacesCount);
////printf("getting the interfaces count => %d \n",interfacesCount);
		/* create the interfaces array and fill it */
////printf("create the interfaces array and fill it\n");
		interfaces = Heap::createInterfaces(interfacesCount);
		for( i=0 ; i < interfacesCount ; i++)
		{
			interfaces[i] = ( ((u2)inputFile[inputPtr])<<8 ) + inputFile[inputPtr+1];
			inputPtr+=2;
		}
		/* extract fieldsCount and advance the input pointer */
		fieldsCount = ( ((u2)inputFile[inputPtr])<<8 ) + inputFile[inputPtr+1];
		inputPtr+=2;

////printf("getting the fields count in this class=> %d \n",fieldsCount);
	//f//printf(stdout,"getting the fields count in this class=> %d \n",fieldsCount);
////printf("create the fields table and fill it\n");
		/* create the fields table and fill it */
		fields = Heap::createFileds(fieldsCount);
		for( i=0 ; i < fieldsCount ; i++)
			fields[i] = Heap::createFieldData(inputFile, &inputPtr,constantPool);

		/* extract methodsCount and advance the input pointer */
		methodsCount =( ((u2)inputFile[inputPtr])<<8 )+ inputFile[inputPtr+1];
		inputPtr+=2;

	//f//printf(stdout,"getting the methods count in this class=> %d \n",methodsCount);
////printf("getting the methods count in this class=> %d \n",methodsCount);
		/* create the methods table and fill it */
////printf("create the methods table and fill it\n");
		methods = Heap::createMethods(methodsCount);
		for(i=0 ; i < methodsCount ; i++)
			methods[i] = Heap::createMethodData(inputFile, &inputPtr,constantPool);

		/* here, there exist the attributes count and attributes table */
		
		/* to load and resolve the super class */
////printf("load and resolve the super class NOW COMMENTED IN CODE\n");
		//if(strcmp(constantPool->getClassName(superClass),"java/lang/Object")!=0)//it is not  the java/lang/Object.class Class
		if(superClass!=0)//dont load superclass if it is java/lang/Object
		{
		  	constantPool-> getClassData(superClass);
	//	}
		/* to load and resolve the superInterfaces */
////printf("load and resolve the super interfaces NOW COMMENTED IN CODE\n");
		for( i=0 ; i < interfacesCount ; i++)
			constantPool-> getClassData(interfaces[i]);
		}
		//call prepare 
		this->prepare();
}
/*****************ARRAY USAGE**********************/
/*****************ARRAY USAGE**********************/
//new constructor specific for arrays 
ClassData::ClassData(const char* arrayName)
{
/*****************ARRAY USAGE**********************/
/*****************ARRAY USAGE**********************/
////printf("Creating the class Data of an array\n");		
////printf("Creating the constant pool of an array\n");
		constantPool = Heap::createArrayCP(arrayName,this );
		accessFlags = 35;//public
		thisClass = 1;
		superClass = 2;
		interfacesCount =0;
		interfaces = NULL;
		fieldsCount = 0;
		fields = NULL;
		methodsCount =0;
		methods = NULL;
	   //	constantPool-> getClassData(superClass);
}

ClassData::~ClassData()
{
}


void ClassData:: prepare(void)
{
////printf("the preparation phase of the class\n");
	/* get the size of an object of the parent class */
//	if(strcmp(constantPool->getClassName(superClass),"java/lang/Object")==0)
	if(superClass==0)//the object size of the Class java/lang/Object = 0
		objectSize=0;
	else
	{
		ClassData * parentClass=constantPool->getClassData(superClass);
		objectSize = parentClass-> getObjectSize();
	}
	//objectSize=0;
	for(u2 i=0; i < fieldsCount; i++)
	{
		/* if the field is static, then set it to the default value */
		if(fields[i]-> isStatic())
		{
			fields[i]-> setDefaultValue();
////printf("setting the default value for a static feild\n");
		}
		else /* this part is for nonstatic fields only */
		{
////printf("Non static feild--->set the offset of the field in the cbject image\n");
			/* set the offset of the field in the cbject image */
			fields[i]->setInstanceVariableSize();
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
////printf("initializing the class--> commented now \n");
////printf("\tso it does only a loop to get the method clinit from the methods array\n");
	ClassData * myParent;
	Method * clInit=NULL;
	u2 i;
//	if(strcmp(constantPool->getClassName(superClass),"java/lang/Object")!=0)
	if(superClass!=0)
	{
		myParent = constantPool->getClassData(superClass);
		if( !(myParent->isInitialized()) )
			myParent->initialize();
	}
	/* search in this class */
	for(i=0; i<methodsCount ; i++)
	{
		if(strcmp(methods[i]-> getName() ,"<clinit>")==0 ) /* another method */
		{
			clInit =  methods[i];
			break;
		}	
	}
	initialized = true;	
	if(clInit)
	{
		ExecutionEng * exec=ExecutionEng::getInstance();
		exec->executeMethod(NULL,clInit);
		//;//execEng->exec(clInit);	
	}
	//initialized = true;
}


Field * ClassData:: lookupField(const char *name,const  char*desc)
{ 
////printf("return the Field block using its name and descriptor\n");
	u2 i;
	/* search in this class */
	for(i=0; i<fieldsCount ; i++)
	{
		if(       (strcmp(name , fields[i]-> getName())==0  )
		&&    (strcmp(desc  , fields[i]->getDesc()  )==0)       ) /* another method */
			return fields[i];
	}
////printf("searching the super interfaces for this field\n");	
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
////printf("searching the super class for this field\n");	
	ClassData * myParent=constantPool->getClassData(superClass);
	return myParent->lookupField(name,desc);
}

Method * ClassData:: lookupMethod(const char *name, const char*desc)
{
////printf("return the Method block using its name and descriptor\n");
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
////printf("searching the super class for this Method\n");	
	/* search in the super class */
	Method * method;
	ClassData * myParent=constantPool->getClassData(superClass);
	if( (method=myParent->lookupMethod(name,desc)) != NULL)
		return method;
	/* search the super interfaces */
	/* what is meant by sueprinterface of interfaces 
	 * directly implemented by this class */
////printf("searching the super interfaces for this Method\n");	
	ClassData * interface;
	for(i=0; i<interfacesCount ; i++)
	{
		interface = constantPool-> getClassData(interfaces[i]);
		if( (method = interface->lookupMethod(name,desc)) != NULL)
			return method;
	}
	return NULL;
}

Method* ClassData:: lookupInterfaceMethod(const char *name,const char *desc)
{
////printf("look up interface method\n");
	if(! (this->isInterface()) )
	;////////////////////////
	u2 i;
	/* search in this interface */
////printf("search in this interface\n");
	for(i=0; i<methodsCount ; i++)
	{
		if(   (strcmp(name ,methods[i]-> getName())==0)
		&& (strcmp(desc , methods[i]->getDesc() )==0)  ) /* another method */
			return methods[i];
	}
////printf("search in this super interfaces\n");
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
////printf("Create the method table\n");
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
////printf("check the validation of casting this class to another given class\n");
	/* if this class is a class */
	if( ! isInterface() )
	{
////printf("This class is of type class not interface\n");		
		/* the other class is a class */
		if( !(classData->isInterface()) )
		{
////printf("the class to be casted to is of type class\n");
////printf("check if this class is a descendent of the given class\n");
			if(isDescendentOf(classData)||this==classData)
				return true;
		}
		else /* the other class is an interface */
		{
////printf("the class to be casted to is of type interface\n");
////printf("check if this class implements the given interface\n");
			if(isImplement(classData))
				return true;
		}
	}
	/* this class is an interface */
	else
	{
////printf("This class is of type class not interface\n");		
		/* the other class is a class */
		if( !(classData->isInterface()) )
		{
////printf("the class to be casted to is of type class\n");
////printf("check if the class to be casted to is the Object class\n");
			if(classData->getFQName()=="Object")//another function
				return true;
		}
		else /* the other class is an interface */
		{
////printf("the class to be casted to is of type interface\n");
////printf("check if this class is a descendent of the given interface\n");
			///////what is meant by superinterfaces
			if(this==classData||isDescendentOf(classData))
				return true;
		}
	}
	return false;
}

bool ClassData:: isImplement(ClassData * theInterface)
{
////printf("searches the interfaces array for the given interface");
////printf(" to check if this class implements this given interface\n");
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
////printf("Check the access flags of the class to check if it is public\n");
	if( ( accessFlags & ( ( (u2)1 ) ) ) ==0 )
		return false;
	return true;	
}
 
bool ClassData:: isFinal(void)
{
////printf("Check the access flags of the class to check if it is final\n");
	if( ( accessFlags & ( ( (u2)1 )<<1 ) ) ==0 )
		return false;
	return true;	
} 

bool ClassData:: treatSuperMethodsSpecially()
{
////printf("Check the access flags of the class to check if it treats the super class methods specially\n");
	if( ( accessFlags & ( ( (u2)1 )<< 5 ) ) ==0 )
		return false;
	return true;
}

bool ClassData:: isInterface(void)
{
////printf("Check the access flags of the class to check if it is an interface\n");
	if( ( accessFlags & ( ( (u2)1 )<< 9 ) ) ==0 )
		return false;
	return true;	
}

bool ClassData:: isAbstract(void)
{
////printf("Check the access flags of the class to check if it is abstract class\n");
	if( ( accessFlags & ( ( (u2)1 )<< 10 ) ) ==0 )
		return false;
	return true;	
}

Method * ClassData:: getActualMethod(Method* nonActualMethod)
{
////printf("Get actual method--> it returns NULL so far\n");
////printf("--------------->if U reached here the error is a call to getActualMethod\n");
return NULL;
}

bool ClassData:: isDescendentOf(ClassData* classData)
{
////printf("Check if this class is a descendent of the given class\n");
	ClassData * myParent=constantPool->getClassData(superClass);
	if( classData == myParent )
		return true;
	return 	myParent->isDescendentOf(classData);
}

ClassData* ClassData::getSuperClassData()
{
////printf("Get super class data --> it returns NULL so far\n");
////printf("--------------->if U reached here the error is a call to getSuperClassData\n");
	//if(strcmp(constantPool->getClassName(superClass),"java/lang/Object") ==0)
	if(superClass!=0)
		return NULL;
	else
	{
	ClassData * myParent = constantPool->getClassData(superClass);
	return myParent;}
	//return NULL;
}

