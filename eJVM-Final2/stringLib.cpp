#include "stringLib.h"
//------------------------------------------------------
Object* utf8ToArrayOfUnicodeChar (byte* utf8String)
{
	u2 length=0,utf8Loc = 0,temp;
	byte x,y,z;
//**********************************************		
	while(utf8String[utf8Loc] != 0)//Temination condition
	{
		/* the character consists of only one byte */
		x = utf8String[utf8Loc];
		if( x>>7 == 0 )
		{
			length++; 
			utf8Loc++;
		}	
		/* the character consists of two bytes */
		else if( (x&224) ==192  )	
		{
			length++;
			utf8Loc+=2;
		}	
		/* the character consists of two bytes */
		else //if( (x>>4) ==14 )
		{
			length ++;
			utf8Loc+=3;
		}
		
	}
//*****************************************************
//create an object of type array of characters 
//using the length
//then perform a loop to fill the array elements
	Object* Array;
	int lengthes[1];
	lengthes[0] = length;
	ClassData * arrayClass = Loader::getInstance()->getClassData("[C");
	Array =  Heap::getInstance()->createArrayObject(1,lengthes,5,arrayClass,NULL);
	utf8Loc=0;
	int index[1];//to set the array elements
	index[0] = 0;
//*****************************************************
	while(utf8String[utf8Loc] != 0)//Temination condition
	{
		/* the character consists of only one byte "0*******" */
		x = utf8String[utf8Loc];
		if( x>>7 == 0 )
		{
			Array->putElement(index , (u4)x ,(u4)0 );
			length ++;
			utf8Loc++;
		}	
		
		/* the character consists of two bytes 
		 * X = "110 bits(10-6)" , Y =  "10 bits(5-0)" */
		else if( (x&224) ==192  )	
		{
			y = utf8String[utf8Loc+1];
			temp = ( ( (u2)(x & 31) ) << 6) + (y & 63);
			Array->putElement(index , (u4)temp ,(u4)0 );
			length ++ ;
			utf8Loc+=2;
		}	
		
		/* the character consists of two bytes 
		 * X = "1110 bits(15-12)" , Y =  "10 bits(11-6)" 
		 * Z = "10 bits(5-0)" */
		else //if( (x>>4) ==14 )
		{
			y = utf8String[utf8Loc+1];
			z = utf8String[utf8Loc+2];
			temp = ( ( (u2)(x & 15) ) << 12) + ( ( (u2)(y & 63) ) << 6) + (z & 63);
			Array->putElement(index ,(u4)temp  ,(u4)0 );
			length ++;
			utf8Loc+=3;
		}
		index [0]= (index [0]) + 1;
		
	}
//**************************************************
	return Array;
}
//------------------------------------------------------
Object* arrayOfUnicodeCharToString (Object* arrayObject)
{
	ClassData * stringClass = Loader::getInstance()->getClassData("java/lang/String");
	Object* stringObject = (Heap::getInstance())->createObject(stringClass);
	Method* initMethod = stringClass->lookupMethod("<init>","([C)V");
	ExecutionEng * exec =new ExecutionEng();
	exec->executeMethod(stringObject,initMethod,arrayObject);
	return stringObject;
}
//------------------------------------------------------

