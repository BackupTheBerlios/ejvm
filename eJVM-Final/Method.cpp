#include "Method.h"
#include "ByteCode.h"
#include "Heap.h"
#include <stdio.h>

Method::Method(const byte inputFile [],int * inputPtr,ConstantPool * cp)
{
printf("inside tha Method Constructor\n");
		constantPool = cp;
printf("get the owner class of this method\n");
		myClass = constantPool->getOwnerClassData();
printf("get the access flags of the method\n");
		accessFlags = ( ((u2)inputFile[*inputPtr]) <<8) +
		inputFile[*inputPtr+1];
printf("get the name index of this method\n");
		nameIndex = ( ((u2)inputFile[*inputPtr+2]) <<8) +
		inputFile[*inputPtr+3];
printf("get the descriptor index of this method\n");
		descriptorIndex=( ((u2)inputFile[*inputPtr+4]) <<8)+
		inputFile[*inputPtr+5];
		/* get the number of attributes */
printf("get the number of attributes of this method\n");
		u2 attributesCount=( ((u2)inputFile[*inputPtr+6]) <<8) +
		inputFile[*inputPtr+7];
		/* advance the input pointer */
		*inputPtr += 8;
		cout<<"Method Name:"<<this->getName()<<"\tDescriptor: "<<this->getDesc()<<endl;
//********************************************************************************
		/* store only the "Code Attribute" if any */
		u2 attrNameIndex,attrLength;
		u4 temp;
		char * attrName;
printf("a loop to fine the code attribute\n");
		for(u2 i=0; i<attributesCount; i++)
		{
printf("get the attribute's name index\n");
			attrNameIndex = ( ((u2)inputFile[*inputPtr]) <<8)+
			inputFile[*inputPtr+1];
			temp = inputFile[*inputPtr+3];
printf("get the attribute's length\n");
			attrLength =( ((u4)inputFile[*inputPtr+2])<<24) +
			(temp << 16) + ( ((u2)inputFile[*inputPtr+4])<<8)+
			inputFile[*inputPtr+5];
printf("get the attribute's name \n");
			attrName = constantPool->getString(attrNameIndex);
			/* Code Attribute */
			if(strcmp(attrName,"Code") == 0 ) /*another function*/
			{
printf("the Code attribute is reached\n");
			  byteCode = new ByteCode(inputFile,*inputPtr+6,  attrNameIndex,attrLength);
	if(byteCode == NULL)
	{
		printf("NULL pointer encountered when trying to create a new byte code\n");
		exit(1);
	}
			}
			/* Exceptions Attribute */
			else if(strcmp(attrName,"Exceptions") == 0 ) /*another function*/
			{
   				u2 numOfExceptions=( ((u2)inputFile[*inputPtr+6]) <<8)+
   				inputFile[*inputPtr+7];
  				exceptionIndexTable = new u2 [numOfExceptions];
//   				exceptionIndexTable = Heap:: createU2Array(numOfExceptions);
   				u2 in = *inputPtr+8;
   				for(u2 i=0 ;i<numOfExceptions ;i++)
   				{
   					exceptionIndexTable[i] = ( ((u2)inputFile[in+i]) <<8)+
					inputFile[in+i+1];
			  		in+=2;
			   	}		
			}
			/* advance the input pointer */
			*inputPtr += attrLength+6;
	}
}

Method::~Method()
{
}

ClassData * Method:: getOwnerClassData(void)
{ return myClass; }

bool Method::isInit(void)
{
printf("inside Method::isInit\n");
	if(strcmp(constantPool->getString(nameIndex),"<init>") == 0)/*another function*/
		return true;
	else
		return false;
}

ByteCode * Method:: getByteCode(void)
{ return this->byteCode; }

char * Method:: getName(void)
{ return constantPool->getString(nameIndex); }

char * Method:: getDesc(void)
{ return constantPool->getString(descriptorIndex); }


bool Method:: isPublic(void)
{
printf("inside Method::isPublic\n");
	if( ( accessFlags & ( (u2)1 ) ) == 0 )
		return false;
	return true;
}

bool Method:: isPrivate(void)
{
printf("inside Method::isPrivate\n");
	if( ( accessFlags & ( (u2)1 )<<1 ) == 0 )
		return false;
	return true;
}

bool Method:: isProtected(void)
{
printf("inside Method::isProtected\n");
	if( ( accessFlags & ( (u2)1 )<<2 ) == 0 )
		return false;
	return true;
}

bool Method:: isStatic(void)
{
printf("inside Method::isStatic\n");
	if( ( accessFlags & ( (u2)1 )<<3 ) == 0 )
		return false;
	return true;
}

bool Method:: isFinal(void)
{
printf("inside Method::isFinal\n");
	if( ( accessFlags & ( (u2)1 )<<4 ) == 0 )
		return false;
	return true;
}

bool Method:: isSynchronized(void)
{
printf("inside Method::isSynchronized\n");
	if( ( accessFlags & ( (u2)1 )<<5 ) == 0 )
		return false;
	return true;
}

bool Method:: isNative(void)
{
printf("inside Method::isNative\n");
	if( ( accessFlags & ( (u2)1 )<<8 ) == 0 )
		return false;
	return true;
}

bool Method:: isAbstract(void)
{
printf("inside Method::isAbstract\n");
	if( ( accessFlags & ( (u2)1 )<<10 ) == 0 )
		return false;
	return true;
}

bool Method:: isStrict(void)
{
printf("inside Method::isStrict\n");
	if( ( accessFlags & ( (u2)1 )<<11 ) == 0 )
		return false;
	return true;
}

u2 Method::getMaxLoacals()
{
printf("inside Method::getMaxLoacals\n");
	 return		byteCode->getMaxLocals();
}

u2 Method::getMaxStack()
{
printf("inside Method::getMaxStack\n");
	 return   byteCode->getMaxStack();
}

