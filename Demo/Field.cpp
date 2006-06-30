#include "Field.h"
#include "Heap.h"

Field::Field(const byte inputFile [],int * inputPtr,ConstantPool * cp)
{
////printf("inside the Field constructor\n");
		constantPool = cp;
////printf("get the owner class from the constant pool\n");
		myClass = constantPool->getOwnerClassData();
////printf("extract the acess flags\n");
		accessFlags = ( ((u2)inputFile[*inputPtr]) <<8) +
		inputFile[*inputPtr+1];
////printf("extract the filed name index\n");
		nameIndex = ( ((u2)inputFile[*inputPtr+2]) <<8) +
		inputFile[*inputPtr+3];
////printf("extract the filed descriptor index\n");
		descriptorIndex=( ((u2)inputFile[*inputPtr+4]) <<8)+
		inputFile[*inputPtr+5];
		/* get the number of attributes */
		u2 attributesCount=( ((u2)inputFile[*inputPtr+6]) <<8) +
		inputFile[*inputPtr+7];
		/* advance the input pointer */
		*inputPtr += 8;
////printf("store tha constant value attribute if any\n");
		/* store only the "ConstantValue Attribute" if any */
		u2 attrNameIndex,attrLength;
		u4 temp;
		char * attrName;
////printf("perform a loop to check all attributes\n");
		for(u2 i=0; i<attributesCount; i++)
		{
////printf("get tha attribute's name index\n");
			attrNameIndex = ( ((u2)inputFile[*inputPtr]) <<8)+
			inputFile[*inputPtr+1];
			temp = inputFile[*inputPtr+3];
////printf("get the attribute's length\n");
			attrLength =( ((u4)inputFile[*inputPtr+2])<<24) +
			(temp << 16) + ( ((u2)inputFile[*inputPtr+4])<<8)+
			inputFile[*inputPtr+5];
////printf("get the attribute name from the constant pool using its index\n");
			attrName = constantPool->getString(attrNameIndex);
			/* ConstantValue Attribute */
			if(strcmp(attrName,"ConstantValue")==0 )/*another function*/
			{
////printf("the attribute has a ConstantValue --> store it\n");
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
////printf("inside Field::setDefaultValue\n");
////printf("get the descriptor of this field\n");
	char * str = constantPool->getString(descriptorIndex);
	switch(str[0])
	{
		case 'B' : //byte
		{
			size=1;
			staticValue = new byte[1];
if(staticValue == NULL)
{
	//printf("NULL pointer encountered in Field::setDefaultValue\n");
	exit(1);
}
			staticValue[0]=0;
		    break;
		}

		case 'C' : //note..note..note..note..char
		{
			size=2;
			staticValue = new byte[2];
if(staticValue == NULL)
{
	//printf("NULL pointer encountered in Field::setDefaultValue\n");
	exit(1);
}

			staticValue[0] = staticValue[1] = 0;
			break;
		}
		case 'D' :  //double
		{
			size=8;
			staticValue = new byte[8];
if(staticValue == NULL)
{
	//printf("NULL pointer encountered in Field::setDefaultValue\n");
	exit(1);
}

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
if(staticValue == NULL)
{
	//printf("NULL pointer encountered in Field::setDefaultValue\n");
	exit(1);
}

			staticValue[0] = staticValue[1] =
			staticValue[2] = staticValue[3] = 0;
			break;
		}

		case 'I' :
		{
			size=4;
			staticValue = new byte[4];
if(staticValue == NULL)
{
	//printf("NULL pointer encountered in Field::setDefaultValue\n");
	exit(1);
}

			staticValue[0] = staticValue[1] =
			staticValue[2] = staticValue[3] = 0;
			break;
		}

		case 'J' :   //long
		{
			size=8;
			staticValue = new byte[8];
if(staticValue == NULL)
{
	//printf("NULL pointer encountered in Field::setDefaultValue\n");
	exit(1);
}

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
if(staticValue == NULL)
{
	//printf("NULL pointer encountered in Field::setDefaultValue\n");
	exit(1);
}

			staticValue[0] = staticValue[1] =
			staticValue[2] = staticValue[3] = 0;
			break;
		}

		case 'S' :   //short
		{
			size=2;
			staticValue = new byte[2];
if(staticValue == NULL)
{
	//printf("NULL pointer encountered in Field::setDefaultValue\n");
	exit(1);
}

			staticValue[0] = staticValue[1] = 0;
			break;
		}
		case 'Z' :
		{
			size=1;
			staticValue = new byte[1];
if(staticValue == NULL)
{
	//printf("NULL pointer encountered in Field::setDefaultValue\n");
	exit(1);
}

			staticValue[0] = 0 ;
			break;
		}

		case '[' :
		{
			size=4;
			staticValue = new byte[4];
if(staticValue == NULL)
{
	//printf("NULL pointer encountered in Field::setDefaultValue\n");
	exit(1);
}

			staticValue[0] = staticValue[1] =
			staticValue[2] = staticValue[3] = 0;
			break;
		}
	}
}

void Field::setInstanceVariableSize()
{
////printf("inside Field::setInstanceVariableSize\n");
////printf("get the descriptor of this field\n");
	char * str = constantPool->getString(descriptorIndex);
	switch(str[0])
	{
		case 'B' : //byte
		{
			size=1;
		    break;
		}

		case 'C' : //note..note..note..note..char
		{
			size=2;
			break;
		}
		case 'D' :  //double
		{
			size=8;
			break;
		}

		case 'F' :  //float
		{
			size=4;
			break;
		}

		case 'I' :
		{
			size=4;
			break;
		}

		case 'J' :   //long
		{
			size=8;
			break;
		}

		case 'L' :   //reference
		{
			size=4;
			break;
		}

		case 'S' :   //short
		{
			size=2;
			break;
		}
		case 'Z' :
		{
			size=1;
			break;
		}

		case '[' :
		{
			size=4;
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
////printf("inside Field::putStaticValue\n");
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
////printf("inside Field:: getStaticValue\n");
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
////printf("inside Field::isPublic\n");
	if( ( accessFlags & ( (u2)1 ) ) == 0 )
		return false;
	return true;	
}

bool Field::isPrivate(void)
{
////printf("inside Field::isPrivate\n");
	if( ( accessFlags & ( (u2)1 )<<1 ) == 0 )
		return false;
	return true;	
}

bool Field::isProtected(void)
{
////printf("inside Field::isProtected\n");
	if( ( accessFlags & ( (u2)1 )<<2 ) == 0 )
		return false;
	return true;	
}

bool Field::isStatic(void)
{
////printf("inside Field::isStatic\n");
	if( ( accessFlags & ( (u2)1 )<<3 ) == 0 )
		return false;
	return true;	
}

bool Field::isFinal(void)
{
////printf("inside Field::isFinal\n");
	if( ( accessFlags & ( (u2)1 )<<4 ) == 0 )
		return false;
	return true;	
}

bool Field::isVolatile(void)
{
////printf("inside Field::isVolatile\n");
	if( ( accessFlags & ( (u2)1 )<<6 ) == 0 )
		return false;
	return true;	
}

bool Field::isTransient(void)
{
////printf("inside Field::isTransient\n");
	if( ( accessFlags & ( (u2)1 )<<7 ) == 0 )
		return false;
	return true;	
}	

ClassData * Field:: getOwnerClass(void)
{ return myClass; }
