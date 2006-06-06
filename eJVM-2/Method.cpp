#include "Method.h"
#include "ByteCode.h"
#include "Heap.h"
#include <stdio.h>

Method::Method(byte inputFile [],int * inputPtr,ConstantPool * cp)
{
		constantPool = cp;
		myClass = constantPool->getOwnerClassData();
		accessFlags = ( ((u2)inputFile[*inputPtr]) <<8) +
		inputFile[*inputPtr+1];
		nameIndex = ( ((u2)inputFile[*inputPtr+2]) <<8) +
		inputFile[*inputPtr+3];
		descriptorIndex=( ((u2)inputFile[*inputPtr+4]) <<8)+
		inputFile[*inputPtr+5];
		/* get the number of attributes */
		u2 attributesCount=( ((u2)inputFile[*inputPtr+6]) <<8) +
		inputFile[*inputPtr+7];
		/* advance the input pointer */
		*inputPtr += 8;

		/* store only the "Code Attribute" if any */
		u2 attrNameIndex,attrLength;
		u4 temp;
		char * attrName;
		for(u2 i=0; i<attributesCount; i++)
		{
			attrNameIndex = ( ((u2)inputFile[*inputPtr]) <<8)+
			inputFile[*inputPtr+1];
			temp = inputFile[*inputPtr+3];
			attrLength =( ((u4)inputFile[*inputPtr+2])<<24) +
			(temp << 16) + ( ((u2)inputFile[*inputPtr+4])<<8)+
			inputFile[*inputPtr+5];

			attrName = constantPool->getString(attrNameIndex);
			/* Code Attribute */
			if(strcmp(attrName,"Code") == 0 ) /*another function*/
			  byteCode = new ByteCode(inputFile,*inputPtr+6,
			  attrNameIndex,attrLength);
			/* Exceptions Attribute */
			else if(strcmp(attrName,"Exceptions") == 0 ) /*another function*/
			{
				;
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
	if(strcmp(constantPool->getString(nameIndex),"<init>") == 0)/*another function*/
		return true;
	else
		return false;
}

ByteCode * Method:: getByteCode(void)
{ return byteCode; }

char * Method:: getName(void)
{ return constantPool->getString(nameIndex); }

char * Method:: getDesc(void)
{ return constantPool->getString(descriptorIndex); }


bool Method:: isPublic(void)
{
	if( ( accessFlags & ( (u2)1 ) ) == 0 )
		return false;
	return true;
}

bool Method:: isPrivate(void)
{
	if( ( accessFlags & ( (u2)1 )<<1 ) == 0 )
		return false;
	return true;
}

bool Method:: isProtected(void)
{
	if( ( accessFlags & ( (u2)1 )<<2 ) == 0 )
		return false;
	return true;
}

bool Method:: isStatic(void)
{
	if( ( accessFlags & ( (u2)1 )<<3 ) == 0 )
		return false;
	return true;
}

bool Method:: isFinal(void)
{
	if( ( accessFlags & ( (u2)1 )<<4 ) == 0 )
		return false;
	return true;
}

bool Method:: isSynchronized(void)
{
	if( ( accessFlags & ( (u2)1 )<<5 ) == 0 )
		return false;
	return true;
}

bool Method:: isNative(void)
{
	if( ( accessFlags & ( (u2)1 )<<8 ) == 0 )
		return false;
	return true;
}

bool Method:: isAbstract(void)
{
	if( ( accessFlags & ( (u2)1 )<<10 ) == 0 )
		return false;
	return true;
}

bool Method:: isStrict(void)
{
	if( ( accessFlags & ( (u2)1 )<<11 ) == 0 )
		return false;
	return true;
}

