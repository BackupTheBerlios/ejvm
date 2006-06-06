#include "ConstantPool.h"
#include "ClassData.h"
#include "Heap.h"
#include "Loader.h"
#include <stdio.h>

ConstantPool::ConstantPool(byte inputFile [],int CPCount,
int * inputPtr, ClassData * myClass)
{
		u1 tag;  			/* the tag is the first byte of each entry */
		int infoCount;  	/* the length ( in bytes) of the actual entry data */

		this-> myClass= myClass;
		this-> CPCount = CPCount;
		this-> myClass = myClass;
		/* create the entry table and pointer table */
		entryTable = Heap:: createCPTable(CPCount);
		pointerTable = Heap:: createPointerTable(CPCount);
		
		/* fill the constant pool entries */
		for(int i=1 ; i < CPCount ; i++)
		{
			/* initialize the pointer table to NULL
		 	* as indication of not being resolved */
			pointerTable[i] = NULL;

			tag = inputFile[*inputPtr];
			/* determine the type of constant pool entry */
			switch(tag)
			{
				case 7:  infoCount = 2; break;  /* CONSTANT_Class  */
				/*
				 * CONSTANT_Class_info {u1 tag;	u2 name_index;}
				 * */
				case 9:	 infoCount = 4; break;  /* CONSTANT_Fieldref  */
				/*
				 * CONSTANT_Fieldref_info {
    			 *		u1 tag;
				 *  	u2 class_index;
				 *   	u2 name_and_type_index;
    			 *	}
				 * */
				case 10: infoCount = 4; break;  /* CONSTANT_Methodref  */
				/*
				 * CONSTANT_Methodref_info {
    			 * 		u1 tag;
				 *   	u2 class_index;
				 *   	u2 name_and_type_index;
				 *   }	
				 **/
				case 11: infoCount = 4; break;  /* CONSTANT_InterfaceMethodref  */
				/**CONSTANT_InterfaceMethodref_info {
    			*		u1 tag;
    			*		u2 class_index;
    			*		u2 name_and_type_index;
    			*	}
				**/
				case 8:  infoCount = 2; break;  /* CONSTANT_String  */
				/** CONSTANT_String_info {
    			 *		u1 tag;
    			 *		u2 string_index;
    			 *	}
				 * */
				case 3:	 infoCount = 4; break;  /* CONSTANT_Integer  */
				/**
				 * CONSTANT_Integer_info {u1 tag; u4 bytes; }
				    CONSTANT_Float_info {u1 tag;  u4 bytes; }
				 * 
				 * */
				case 4:  infoCount = 4; break;  /* CONSTANT_Float  */
				case 5:	 infoCount = 8; break;  /* CONSTANT_Long  */
				/*
				 *  CONSTANT_Long_info {u1 tag;	u4 high_bytes;u4 low_bytes; }
			    	CONSTANT_Double_info {u1 tag;u4 high_bytes;u4 low_bytes;}
			    	**/
				case 6:	 infoCount = 8; break;  /* CONSTANT_Double  */
				
				case 12: infoCount = 4; break;  /* CONSTANT_NameAndType  */
	/*
	 *  CONSTANT_NameAndType_info {	u1 tag;u2 name_index;u2 descriptor_index;}
	 */
				case 1: 						/* CONSTANT_Utf8 */
				{
				   infoCount = 2 + (((u2)inputFile[*inputPtr+1])<<8) + inputFile[*inputPtr+2];
				   break;
				}
			}

			/* create the current entry */
			entryTable[i] = Heap:: createCPTableEntry(infoCount+1);
			/* fill the current entry with tag and data */
			for(int j=0 ; j <= infoCount ; j++)
				entryTable[i][j] = inputFile[ (*inputPtr)+j ];
			/* advance the input pointer */
			(*inputPtr) += infoCount+1;
		}
}

ConstantPool::~ConstantPool()
{
}


char * ConstantPool::getString(u2 UTF8Index)
{
	/* if the entry is not of the type UTF-8 */
	if(entryTable[UTF8Index][0] != 1)
	//exception();
	;
	/* if the entry is resolved, then return the pointer directly*/	
	if( pointerTable[UTF8Index] != NULL )
		return (char *)pointerTable[UTF8Index];
	/* here, the entry is not resolved */
	char * str; /* small indian */
	u2 entryLength,entryPtr,i,temp;
	byte x,y,z;
	/* get the length of the UTF8 in bytes */
	entryLength=(((u2)entryTable[UTF8Index][1])<<8)+entryTable[UTF8Index][2];
	str = new char [entryLength+1];
	/* initialize the string */
	for(i=0; i<=entryLength ;i++)
		str[i] = '\0';	
	/* fill str from the UTF8 */
	entryPtr=3;
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
	/* if the entry is not of the type "ClassInfo"  */
	if( entryTable [index][0] != (byte)7 )
		//exception();
		;
	/* if the entry is resolved, then return the pointer directly*/	
	if( pointerTable[index] != NULL )
		return (ClassData *)pointerTable[index];
	/* here, the entry is not resolved */
	ClassData * theClass;
	char * className;
	u2 classNameIndex;
	
	classNameIndex = ( ((u2)entryTable[index][1]) <<8 ) + entryTable[index][2];
	className = getString(classNameIndex);
	Loader * loader = Loader::getInstance();
	theClass = loader-> getClassData(className);
	/* access permission goes here */
	accessPermissionClass(theClass);
	//theClass -> prepare();
	/* the verification goes here */
	theClass -> initialize();
	/* the resoution goes here */
	pointerTable[index] = theClass;
	return theClass;
}


Field * ConstantPool:: getFieldData(u2 index)
{
	/* if the entry is not of the type "FieldInfo"  */
	if( entryTable [index][0] != (byte)9 )
	/* exception()*/ ;
	/* if the entry is resolved, then return the pointer directly*/	
	if( pointerTable[index] != NULL )
		return (Field *)pointerTable[index];
	/* here, the entry is not resolved */
	/* name and descriptor of the field*/
	char * fieldName, *fieldDesc; 
	/* the two parts of the fieldInfo entry */
	u2 classIndex , nameTypeIndex;
	/* the class that contains the desired field */
	ClassData * theClass;
	/* get the classIndex part of the entry */
	classIndex = ( ((u2)entryTable[index][1] )<<8 ) + entryTable[index][2];
	/* resolve the class that contains the desired field */
	theClass = getClassData(classIndex);
	/* get the nameAndType part of the entry */
	nameTypeIndex = ( ((u2)entryTable[index][3] )<<8 ) + entryTable[index][4];
	fieldName = getNameAndType(nameTypeIndex,0);
	fieldDesc = getNameAndType(nameTypeIndex,1);
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
	/* if the entry is not of the type "MethodInfo"  */
	if( entryTable [index][0] != (byte)10 && 
	entryTable [index][0] != (byte)11)
	//exception();
	;
	/* if the entry is resolved, then return the pointer directly*/	
	if( pointerTable[index] != NULL )
		return (Method *)pointerTable[index];
	/* here, the entry is not resolved */
	/* get the classIndex part of the entry */
	/* name and descriptor of the method*/
	char * methodName, *methodDesc; 
	/* the two parts of the methodInfo entry */
	u2 classIndex , nameTypeIndex;
	/* the class that contains the desired method */
	ClassData * theClass;
	
	classIndex = ( ((u2)entryTable[index][1] )<<8 ) + entryTable[index][2];
	/* resolve the class that contains the desired method */
	theClass = getClassData(classIndex);
	
	//
	// check if theClass is a class and not an interface 
	//if( theClass->isInterface() )
	//	//exception();
	//;
	//	
	
	/* get the nameAndType part of the entry */
	nameTypeIndex = ( ((u2)entryTable[index][3] )<<8 ) + entryTable[index][4];
	methodName = getNameAndType(nameTypeIndex,0);
	methodDesc = getNameAndType(nameTypeIndex,1);
	
	/* check the type of the cp entry */
	if(entryTable [index][0] != (byte)10)
		pointerTable[index] = theClass-> lookupMethod(methodName,methodDesc);
	else
		pointerTable[index] = theClass-> lookupMethod(methodName,methodDesc);
	
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
	char * str;
	u2 index;
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
	
	str = getString(index);	
	return str;
}

void ConstantPool::accessPermissionClass(ClassData * theClass)
{
	if( !(theClass->isPublic()) )
	/* exception() */ ;
	//the two classes are members of the same runtime package
}

void ConstantPool::accessPermissionField(Field * theField)
{
	/* what is the declaring class */
	bool pub = theField->isPublic();
	if(!pub)
	{
		bool prot = theField->isProtected();
		ClassData * currentClass, * declaringClass; 
		currentClass = this->getOwnerClassData();
		declaringClass = theField->getOwnerClass();
	
		bool cond1=(currentClass->isDescendentOf(declaringClass)) 
		|| (currentClass==declaringClass) ;
		if( !(cond1&&prot))
		{
			bool priv = theField->isPrivate(); 
			bool pkpriv = (!pub && !prot && !priv);
			bool samerunpk;
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
/* what is the declaring class */
	bool pub = theMethod->isPublic();
	if(!pub)
	{
		bool prot = theMethod->isProtected();
		ClassData * currentClass, * declaringClass; 
		currentClass = this->getOwnerClassData();
		declaringClass = theMethod->getOwnerClassData();
	
		bool cond1=(currentClass->isDescendentOf(declaringClass)) 
		|| (currentClass==declaringClass) ;
		if( !(cond1&&prot))
		{
			bool priv = theMethod->isPrivate(); 
			bool pkpriv = (!pub && !prot && !priv);
			bool samerunpk;
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
	/* CONSTANT_Integer_info */
	if(entryTable[index][0]!=3)
	/* exception(); */ ;
	u4 temp = entryTable[index][2];
	word = ( ((u4)entryTable[index][1])<<24) +
			(temp << 16) + ( ((u2)entryTable[index][3])<<8)+
			entryTable[index][4];	
}

void ConstantPool:: get2Words(u2 index,u4 &word1,u4 &word2)
{
	/* CONSTANT_Long_info */
	if(entryTable[index][0]!=5)
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
	/* we will not check here if the
	 * entry is of type "CONSTAVT_CLASS"*/
	u2 utf8Index = ( ((u2)entryTable[classIndex][1])<<8) +
	entryTable[classIndex][2];
	return this->getString(utf8Index);
}
