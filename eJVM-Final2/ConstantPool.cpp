#include "ConstantPool.h"
#include "ClassData.h"
#include "Heap.h"
#include "Loader.h"
#include <stdio.h>

ConstantPool::ConstantPool(const byte inputFile [],int CPCount,
int * inputPtr, ClassData * myClass)
{
printf("inside the constructor of the constant pool\n");
		u1 tag;  			/* the tag is the first byte of each entry */
		int infoCount;  	/* the length ( in bytes) of the actual entry data */

		this-> myClass= myClass;
		this-> CPCount = CPCount;
		this-> myClass = myClass;
		/* create the entry table and pointer table */
printf("creating the constant pool table in the constant pool constructor\n");
		entryTable = Heap:: createCPTable(CPCount);
printf("creating the pointer table in the constant pool constructor\n");
		pointerTable = Heap:: createPointerTable(CPCount);

fprintf(stdout,"fill the constant pool entries\n");

		/* fill the constant pool entries */
		for(int i=1 ; i < CPCount ; i++)
		{
			/* initialize the pointer table to NULL
		 	* as indication of not being resolved */
printf("initialize the pointer table to NULL  as indication of not being resolved \n");
			pointerTable[i] = NULL;

			tag = inputFile[*inputPtr];
			/* determine the type of constant pool entry */
			switch(tag)
			{
				case 7:  infoCount = 2; 
fprintf(stdout,"entry no. %d in the constant pool is a CONSTANT_Class\n",i);
					break;  /* CONSTANT_Class  */
				/*
				 * CONSTANT_Class_info {u1 tag;	u2 name_index;}
				 * */
				case 9:	 infoCount = 4; 
fprintf(stdout,"entry no. %d in the constant pool is a CONSTANT_Fieldref_info\n",i);
					break;  /* CONSTANT_Fieldref  */
				/*
				 * CONSTANT_Fieldref_info {
    			 *		u1 tag;
				 *  	u2 class_index;
				 *   	u2 name_and_type_index;
    			 *	}
				 * */
				case 10: infoCount = 4; 
fprintf(stdout,"entry no. %d in the constant pool is a CONSTANT_Methodref_info\n",i);
					break;  /* CONSTANT_Methodref  */
				/*
				 * CONSTANT_Methodref_info {
    			 * 		u1 tag;
				 *   	u2 class_index;
				 *   	u2 name_and_type_index;
				 *   }	
				 **/
				case 11: infoCount = 4;
fprintf(stdout,"entry no. %d in the constant pool is a CONSTANT_InterfaceMethodref_info\n",i);
				 break;  /* CONSTANT_InterfaceMethodref  */
				/**CONSTANT_InterfaceMethodref_info {
    			*		u1 tag;
    			*		u2 class_index;
    			*		u2 name_and_type_index;
    			*	}
				**/
				case 8:  infoCount = 2; 
fprintf(stdout,"entry no. %d in the constant pool is a CONSTANT_String_info\n",i);						
				break;  /* CONSTANT_String  */
				/** CONSTANT_String_info {
    			 *		u1 tag;
    			 *		u2 string_index;
    			 *	}
				 * */
				case 3:	 infoCount = 4; 
fprintf(stdout,"entry no. %d in the constant pool is a CONSTANT_Integer_info\n",i);
					break;  /* CONSTANT_Integer  */
				/**
				 * CONSTANT_Integer_info {u1 tag; u4 bytes; }
				    CONSTANT_Float_info {u1 tag;  u4 bytes; }
				 * 
				 * */
				case 4:  infoCount = 4; 
fprintf(stdout,"entry no. %d in the constant pool is a CONSTANT_Float_info\n",i);								
				break;  /* CONSTANT_Float  */
				case 5:	 infoCount = 8;
fprintf(stdout,"entry no. %d in the constant pool is a CONSTANT_Long_info\n",i);
					 break;  /* CONSTANT_Long  */
				/*
				 *  CONSTANT_Long_info {u1 tag;	u4 high_bytes;u4 low_bytes; }
			    	CONSTANT_Double_info {u1 tag;u4 high_bytes;u4 low_bytes;}
			    	**/
				case 6:	 infoCount = 8; 
fprintf(stdout,"entry no. %d in the constant pool is a CONSTANT_Double_info\n",i);
					break;  /* CONSTANT_Double  */
				
				case 12: infoCount = 4; 
fprintf(stdout,"entry no. %d in the constant pool is a CONSTANT_NameAndType_info\n",i);
					break;  /* CONSTANT_NameAndType  */
	/*
	 *  CONSTANT_NameAndType_info {	u1 tag;u2 name_index;u2 descriptor_index;}
	 */
				case 1: 						/* CONSTANT_Utf8 */
				{
				   infoCount = 2 + (((u2)inputFile[*inputPtr+1])<<8) + inputFile[*inputPtr+2];
fprintf(stdout,"entry no. %d in the constant pool is a CONSTANT_utf8_info\n",i);
				   break;
				}
			}

			/* create the current entry */
printf("create the entry number %d in the constant pool\n",i);
			entryTable[i] = Heap:: createCPTableEntry(infoCount+1);
			/* fill the current entry with tag and data */
printf("fill the current entry  %d in the constant pool with tag and data\n",i);
			for(int j=0 ; j <= infoCount ; j++)
				entryTable[i][j] = inputFile[ (*inputPtr)+j ];
			/* advance the input pointer */
			(*inputPtr) += infoCount+1;
			if(tag==5 || tag == 6)
				i++;
		}
}
/*****************************************/
ConstantPool::ConstantPool(const char * arrayName, ClassData * myClass)
{
		this-> CPCount =5;
		this-> myClass = myClass;
		/* create the entry table and pointer table */
printf("create the entry table and pointer table in the constant pool constructor for arays\n");
		entryTable = Heap:: createCPTable(CPCount);
		pointerTable = Heap:: createPointerTable(CPCount);
printf("initialize the pointer table to NULL  as indication of not being resolved \n");
		for(int i=1 ; i < CPCount ; i++)
			/* initialize the pointer table to NULL  as indication of not being resolved */
			pointerTable[i] = NULL;	
		char * name= new char [ strlen(arrayName)+1 ];
if(name == NULL)
{
	printf("NULL encountered when creating a new array of characters");
	printf(" in the constant pool of the array\n");
	exit(1);
}
		strcpy(name,arrayName);
printf("put the class Object's Fully Qualified name in an char * obj\n");
		char * obj ="java/lang/Object ";
		pointerTable[1] = myClass;
		pointerTable[3] = name;
		pointerTable[4] = obj;
printf("ask heap to create CPTableEntry number 1 in the constructor of constant pool of arrays\n");			
		entryTable[1] = Heap:: createCPTableEntry(3);
		entryTable[1][0]=(u1)7;
		entryTable[1][1]=(u1)0;
		entryTable[1][2]=(u1)3;
printf("ask heap to create CPTableEntry number 2 in the constructor of constant pool of arrays\n");		
		entryTable[2] = Heap:: createCPTableEntry(3);
		entryTable[1][0]=(u1)7;
		entryTable[1][1]=(u1)0;
		entryTable[1][2]=(u1)4;
printf("ask heap to create CPTableEntry number 3 in the constructor of constant pool of arrays\n");
		entryTable[3] = Heap:: createCPTableEntry(1);
		entryTable[3][0] = 1;
printf("ask heap to create CPTableEntry number 4 in the constructor of constant pool of arrays\n");
		entryTable[4] = Heap:: createCPTableEntry(1);
		entryTable[4][0] = 1;
}

/*****************************************/

ConstantPool::~ConstantPool()
{
}


char * ConstantPool::getString(u2 UTF8Index)
{
printf("the ConstantPool -- getString\n");
	/* if the entry is not of the type UTF-8 */
	if(entryTable[UTF8Index][0] != 1)
	//exception();
	;
	/* if the entry is resolved, then return the pointer directly*/	
printf("if the entry is resolved, then return the pointer directly\n");
	if( pointerTable[UTF8Index] != NULL )
		return (char *)pointerTable[UTF8Index];
	/* here, the entry is not resolved */
	char * str; /* small indian */
	u2 entryLength,entryPtr,i,temp;
	byte x,y,z;
	/* get the length of the UTF8 in bytes */
printf("get the length of the UTF8 in bytes\n");
	entryLength=(((u2)entryTable[UTF8Index][1])<<8)+entryTable[UTF8Index][2];
	str = new char [entryLength+1];
if(str == NULL)
{
	printf("NULL encountered when creating a new array of characters");
	printf(" in the constant pool ::getString \n");
	exit(1);
}
printf("initialize the string to NULLs\n");
	/* initialize the string */
	for(i=0; i<=entryLength ;i++)
		str[i] = '\0';	
	/* fill str from the UTF8 */
	entryPtr=3;
printf("fill the string from the UTF8 string got\n");
	while(entryPtr<entryLength+3)
	{
		/* the character consists of only one byte "0*******" */
		x = entryTable[UTF8Index][entryPtr];
		if( x>>7 == 0 )
		{
			str[entryPtr-3] = x;
			entryPtr++;
		}	
		
		/* the character consists of two bytes 
		 * X = "110 bits(10-6)" , Y =  "10 bits(5-0)" */
		else if( (x>>5) ==6 )	
		{
			y = entryTable[UTF8Index][entryPtr+1];
			temp = ( ( (u2)(x & 31) ) << 6) + (y & 63);
			str[entryPtr-3] = (char)temp;
			str[entryPtr-2] =(char)(temp>>8);
			entryPtr+=2;
		}	
		
		/* the character consists of two bytes 
		 * X = "1110 bits(15-12)" , Y =  "10 bits(11-6)" 
		 * Z = "10 bits(5-0)" */
		else //if( (x>>4) ==14 )
		{
			y = entryTable[UTF8Index][entryPtr+1];
			z = entryTable[UTF8Index][entryPtr+2];
			temp = ( ( (u2)(x & 15) ) << 12) + 
			( ( (u2)(y & 63) ) << 6) + (z & 63);
			str[entryPtr-3] = (char)temp;
			str[entryPtr-2] =(char)(temp>>8);
			entryPtr+=3;
		}
	}
	pointerTable[UTF8Index] = str;
	return str;
}



ClassData * ConstantPool:: getClassData(u2 index)
{
printf("ConstantPool-- getClassData\n");
	/* if the entry is not of the type "ClassInfo"  */
	if( entryTable [index][0] != (byte)7 )
		//exception();
		;
printf("if the entry is resolved, then return the pointer directly \n");
	/* if the entry is resolved, then return the pointer directly*/	
	if( pointerTable[index] != NULL )
		return (ClassData *)pointerTable[index];
	/* here, the entry is not resolved */
	ClassData * theClass;
	char * className;
	u2 classNameIndex;
printf("the entry is not resolved\n");	
	classNameIndex = ( ((u2)entryTable[index][1]) <<8 ) + entryTable[index][2];
	className = getString(classNameIndex);
	Loader * loader = Loader::getInstance();
printf("Loader * loader = Loader::getInstance\n");
	theClass = loader-> getClassData(className);
	/* access permission goes here */
	accessPermissionClass(theClass);
	//theClass -> prepare();
	/* the verification goes here */
printf("initialize the class if it is not initialized\n");
	if(!theClass->isInitialized())
		theClass -> initialize();
	/* the resoution goes here */
printf("the entry of the pointer table corresponding to this class is set to a pointer to the loaded class data \n");
	pointerTable[index] = theClass;
	return theClass;
}


Field * ConstantPool:: getFieldData(u2 index)
{
printf("ConstantPool-- getFieldData\n");
	/* if the entry is not of the type "FieldInfo"  */
	if( entryTable [index][0] != (byte)9 )
	/* exception()*/ ;
printf("if the entry is resolved, then return the pointer directly \n");
	/* if the entry is resolved, then return the pointer directly*/	
	if( pointerTable[index] != NULL )
		return (Field *)pointerTable[index];
	/* here, the entry is not resolved */
printf("the entry is not resolved\n");
	/* name and descriptor of the field*/
	char * fieldName, *fieldDesc; 
	/* the two parts of the fieldInfo entry */
	u2 classIndex , nameTypeIndex;
	/* the class that contains the desired field */
	ClassData * theClass;
	/* get the classIndex part of the entry */
printf("get the classIndex part of the entry\n");
	classIndex = ( ((u2)entryTable[index][1] )<<8 ) + entryTable[index][2];
	/* resolve the class that contains the desired field */
printf("resolve the class that contains the desired field \n");
	theClass = getClassData(classIndex);
	/* get the nameAndType part of the entry */
	nameTypeIndex = ( ((u2)entryTable[index][3] )<<8 ) + entryTable[index][4];
printf("call to get name and type twice to get the name and descriptor of the feild\n");
	fieldName = getNameAndType(nameTypeIndex,0);
	fieldDesc = getNameAndType(nameTypeIndex,1);
printf("call look up field on the class containing this field\n");
	pointerTable[index] = theClass-> lookupField(fieldName,fieldDesc);
	/* if the lookup failed */
	if(pointerTable[index] == NULL)
		//exception();
			;
	/* check access permission. 
	 * If fialed, then throw exception*/	
	accessPermissionField((Field *)pointerTable[index]);
	return (Field*)pointerTable[index];	
}


Method * ConstantPool:: getMethodData(u2 index)
{
printf("inside ConstantPool-- getMethodData\n");
	/* if the entry is not of the type "MethodInfo"  */
	if( entryTable [index][0] != (byte)10 && 
	entryTable [index][0] != (byte)11)
	//exception();
	;
printf("if the entry is resolved, then return the pointer directly \n");
	/* if the entry is resolved, then return the pointer directly*/	
	if( pointerTable[index] != NULL )
		return (Method *)pointerTable[index];
	/* here, the entry is not resolved */
printf("the entry is not resolved\n");
	/* get the classIndex part of the entry */
	/* name and descriptor of the method*/
	char * methodName, *methodDesc; 
	/* the two parts of the methodInfo entry */
	u2 classIndex , nameTypeIndex;
	/* the class that contains the desired method */
	ClassData * theClass;
printf("get the classIndex part of the entry\n");		
	classIndex = ( ((u2)entryTable[index][1] )<<8 ) + entryTable[index][2];
	/* resolve the class that contains the desired method */
printf("resolve the class that contains the desired Method \n");
	theClass = getClassData(classIndex);
	
	//
	// check if theClass is a class and not an interface 
	//if( theClass->isInterface() )
	//	//exception();
	//;
	//	
printf("call to get name and type twice to get the name and descriptor of the feild\n");	
	/* get the nameAndType part of the entry */
	nameTypeIndex = ( ((u2)entryTable[index][3] )<<8 ) + entryTable[index][4];
	methodName = getNameAndType(nameTypeIndex,0);
	methodDesc = getNameAndType(nameTypeIndex,1);
printf("check if this is a member method of an class or an interface\n");		
	/* check the type of the cp entry */
	if(entryTable [index][0] == (byte)10)
		pointerTable[index] = theClass-> lookupMethod(methodName,methodDesc);
	else
		pointerTable[index] = theClass-> lookupInterfaceMethod(methodName,methodDesc);
	
	/* if the lookup failed */
	if(pointerTable[index] == NULL)
	//exception();
	;
	
	if( ((Method*)pointerTable[index])->isAbstract() &&
	! theClass->isAbstract() ) //theClass only or its supertypes
	;////exception(); 
	
	/* check access permission. 
	 * If fialed, then throw exception*/	
	accessPermissionMethod((Method *)pointerTable[index]);
	return (Method*)pointerTable[index];	
}


char * ConstantPool:: getNameAndType(u2 nameTypeIndex,int option)
{
printf("inside ConstantPool-- getNameAndType\n");
	char * str;
	u2 index;
printf("check if the entry is not of type NameAndType \n");
	/* if the entry is not of the type "NameAndType" */
	if(entryTable[nameTypeIndex][0] != 12)
	//exception();
		;
	/* if the name is desired */	
	if(option == 0)
		index = (( (u2)entryTable[nameTypeIndex][1] ) <<8) + 
		entryTable[nameTypeIndex][2];
	/* if the type is desired */
	else
		index = (( (u2)entryTable[nameTypeIndex][3] ) <<8) + 
		entryTable[nameTypeIndex][4];
printf("Call To get String\n");	
	str = getString(index);	
	return str;
}

void ConstantPool::accessPermissionClass(ClassData * theClass)
{
printf("inside ConstantPool--accessPermissionClass\n");
	if( !(theClass->isPublic()) )
	/* exception() */ ;
	//the two classes are members of the same runtime package
}

void ConstantPool::accessPermissionField(Field * theField)
{
printf("ConstantPool--accessPermissionField\n");
	/* what is the declaring class */
	bool pub = theField->isPublic();
	if(!pub)
	{
		bool prot = theField->isProtected();
		ClassData * currentClass, * declaringClass; 
printf("get the class data of the current class that uses this field\n");
		currentClass = this->getOwnerClassData();
printf("get the class data of the class that owns this field\n");
		declaringClass = theField->getOwnerClass();
	
		bool cond1=(currentClass->isDescendentOf(declaringClass)) 
		|| (currentClass==declaringClass) ;
		if( !(cond1&&prot))
		{
			bool priv = theField->isPrivate(); 
			bool pkpriv = (!pub && !prot && !priv);
			bool samerunpk=true;
			if( !((prot||pkpriv) && samerunpk) ) 
			{
				if( !( priv&&(currentClass==declaringClass) ) )
				/* exception() */;
			}
		}
	}
}

void ConstantPool::accessPermissionMethod(Method * theMethod)
{
printf("ConstantPool--accessPermissionMethod\n");
/* what is the declaring class */
	bool pub = theMethod->isPublic();
	if(!pub)
	{
		bool prot = theMethod->isProtected();
		ClassData * currentClass, * declaringClass; 
		currentClass = this->getOwnerClassData();
printf("get the class data of the current class that uses this method\n");
		declaringClass = theMethod->getOwnerClassData();
printf("get the class data of the class that owns this method\n");	
		bool cond1=(currentClass->isDescendentOf(declaringClass)) 
		|| (currentClass==declaringClass) ;
		if( !(cond1&&prot))
		{
			bool priv = theMethod->isPrivate(); 
			bool pkpriv = (!pub && !prot && !priv);
			bool samerunpk=true;
			if( !((prot||pkpriv) && samerunpk) ) 
			{
				if( !( priv&&(currentClass==declaringClass) ) )
				/* exception() */;
			}
		}
	}
}


ClassData * ConstantPool:: getOwnerClassData(void)
{ return myClass; }

void ConstantPool:: getWord(u2 index,u4 &word)
{
printf("inside ConstantPool-- getWord\n");
	/* CONSTANT_Integer_info */
	if(entryTable[index][0]!=3&&entryTable[index][0]!=4)
	/* exception(); */ ;
	u4 temp = entryTable[index][2];
	word = ( ((u4)entryTable[index][1])<<24) +
			(temp << 16) + ( ((u2)entryTable[index][3])<<8)+
			entryTable[index][4];	
}

void ConstantPool:: get2Words(u2 index,u4 &word1,u4 &word2)
{
printf("inside ConstantPool-- get2Words\n");
	/* CONSTANT_Long_info */
	if(entryTable[index][0]!=5&&entryTable[index][0]!=6)
	/* exception(); */ ;
	u4 temp = entryTable[index][2];
	word2 = ( ((u4)entryTable[index][1])<<24) +
			(temp << 16) + ( ((u2)entryTable[index][3])<<8)+
			entryTable[index][4];
			
	temp = entryTable[index][6];
	word1 = ( ((u4)entryTable[index][5])<<24) +
			(temp << 16) + ( ((u2)entryTable[index][7])<<8)+
			entryTable[index][8];			
}

char * ConstantPool:: getClassName(u2 classIndex)
{
printf("inside ConstantPool-- getClassName\n");
	/* we will not check here if the
	 * entry is of type "CONSTAVT_CLASS"*/
	u2 utf8Index = ( ((u2)entryTable[classIndex][1])<<8) +
	entryTable[classIndex][2];
	return this->getString(utf8Index);
}
