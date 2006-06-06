#include "Field.h"
#include "Heap.h"

Field::Field(byte inputFile [],int * inputPtr,ConstantPool * cp)
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

		/* store only the "ConstantValue Attribute" if any */
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
			/* ConstantValue Attribute */
			if(strcmp(attrName,"ConstantValue")==0 )/*another function*/
			{
			  constantValIndex=(((u2)inputFile[*inputPtr+6])<<8)
			  +inputFile[*inputPtr+7];
			}
			/* advance the input pointer */
			*inputPtr += attrLength+6;
		}
}

Field::~Field()
{
}

void Field::setDefaultValue(void)
{
	char * str = constantPool->getString(descriptorIndex);
	switch(str[0])
	{
		case 'B' : //byte
		{
			size=1;
			staticValue = new byte[1];
			staticValue[0]=0;
		    break;
		}

		case 'C' : //note..note..note..note..char
		{
			size=2;
			staticValue = new byte[2];
			staticValue[0] = staticValue[1] = 0;
			break;
		}
		case 'D' :  //double
		{
			size=8;
			staticValue = new byte[8];
			staticValue[0] = staticValue[1] =
			staticValue[2] = staticValue[3] =
			staticValue[4] = staticValue[5] =
			staticValue[6] = staticValue[7] = 0;
			break;
		}

		case 'F' :  //float
		{
			size=4;
			staticValue = new byte[4];
			staticValue[0] = staticValue[1] =
			staticValue[2] = staticValue[3] = 0;
			break;
		}

		case 'I' :
		{
			size=4;
			staticValue = new byte[4];
			staticValue[0] = staticValue[1] =
			staticValue[2] = staticValue[3] = 0;
			break;
		}

		case 'J' :   //long
		{
			size=8;
			staticValue = new byte[8];
			staticValue[0] = staticValue[1] =
			staticValue[2] = staticValue[3] =
			staticValue[4] = staticValue[5] =
			staticValue[6] = staticValue[7] = 0;
			break;
		}

		case 'L' :   //reference
		{
			size=4;
			staticValue = new byte[4];
			staticValue[0] = staticValue[1] =
			staticValue[2] = staticValue[3] = 0;
			break;
		}

		case 'S' :   //short
		{
			size=2;
			staticValue = new byte[2];
			staticValue[0] = staticValue[1] = 0;
			break;
		}
		case 'Z' :
		{
			size=1;
			staticValue = new byte[1];
			staticValue[0] = 0 ;
			break;
		}

		case '[' :
		{
			size=4;
			staticValue = new byte[4];
			staticValue[0] = staticValue[1] =
			staticValue[2] = staticValue[3] = 0;
			break;
		}
	}
}

u1 Field::getSize(void)
{ return size; }

char * Field:: getName(void)
{ return constantPool->getString(nameIndex); }

char * Field:: getDesc(void)
{ return constantPool->getString(descriptorIndex); }

u4 Field::getOffset(void)
{ return offset; }

void Field:: setOffset(u2 offset)
{ this-> offset = offset; }

void Field::putStaticValue(u4 word1,u4 word2)
{
	/* staticValue[0]=LSB (small indian)*/
	switch(size)
	{
		case 1:
		{
			staticValue[0]= (byte)word1;
			break;
		}

		case 2:
		{
			staticValue[0]= (byte)word1;
			staticValue[1]= (byte)(word1>>8);
			break;
		}

		case 4:
		{
			staticValue[0]= (byte)word1;
			staticValue[1]= (byte)(word1>>8);
			staticValue[2]= (byte)(word1>>16);
			staticValue[3]= (byte)(word1>>24);
			break;
		}

		case 8:
		{
			staticValue[0]= (byte)word1;
			staticValue[1]= (byte)(word1>>8);
			staticValue[2]= (byte)(word1>>16);
			staticValue[3]= (byte)(word1>>24);
			staticValue[4]= (byte)word2;
			staticValue[5]= (byte)(word2>>8);
			staticValue[6]= (byte)(word2>>16);
			staticValue[7]= (byte)(word2>>24);
			break;
		}
	}
}

void Field:: getStaticValue(u4 &word1,u4 &word2)
{
	/* staticValue[0]=LSB (small indian)*/
	switch(size)
	{
		case 1:
		{
			word1 = staticValue[0];
			word2 = 0;
			break;
		}

		case 2:
		{
			word1 = ( ((u2)staticValue[1])<<8 )+ staticValue[0];
			word2 = 0;
			break;
		}

		case 4:
		{
			u4 temp = staticValue[2];
			word1 =( ((u4)staticValue[3])<<24) +(temp << 16) +
			( ((u2)staticValue[1])<<8) + staticValue[0];
			word2 = 0;
			break;
		}

		case 8:
		{
			u4 temp = staticValue[2];
			word1 =( ((u4)staticValue[3])<<24) +(temp << 16) +
			( ((u2)staticValue[1])<<8) + staticValue[0];

			temp = staticValue[6];
			word2 =( ((u4)staticValue[7])<<24) +(temp << 16) + 
			( ((u2)staticValue[5])<<8) + staticValue[4];
			break;
		}	
	}	
}

bool Field::isPublic(void)
{
	if( ( accessFlags & ( (u2)1 ) ) == 0 )
		return false;
	return true;	
}

bool Field::isPrivate(void)
{
	if( ( accessFlags & ( (u2)1 )<<1 ) == 0 )
		return false;
	return true;	
}

bool Field::isProtected(void)
{
	if( ( accessFlags & ( (u2)1 )<<2 ) == 0 )
		return false;
	return true;	
}

bool Field::isStatic(void)
{
	if( ( accessFlags & ( (u2)1 )<<3 ) == 0 )
		return false;
	return true;	
}

bool Field::isFinal(void)
{
	if( ( accessFlags & ( (u2)1 )<<4 ) == 0 )
		return false;
	return true;	
}

bool Field::isVolatile(void)
{
	if( ( accessFlags & ( (u2)1 )<<6 ) == 0 )
		return false;
	return true;	
}

bool Field::isTransient(void)
{
	if( ( accessFlags & ( (u2)1 )<<7 ) == 0 )
		return false;
	return true;	
}	

ClassData * Field:: getOwnerClass(void)
{ return myClass; }
