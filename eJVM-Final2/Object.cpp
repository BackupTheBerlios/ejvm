#include "Object.h"
#include "Field.h"
#include "ClassData.h"
#include "Heap.h"

Object::Object(ClassData * myClass)
{
//printf("inside tha constructor of Object\n");
	this->myClass = myClass;
	u2 size = this->myClass->getObjectSize();
//printf("ask the heap to create the associated byte array of the object\n");
	data = Heap:: createByteArray(size);
}

Object::~Object()
{
}

void Object:: putField(Field * field, u4 word1, u4 word2)
{
//printf("inside Object:: putField\n");
	u4 offset = field->getOffset();
	u1 size = field->getSize();
//printf("put the fields value due to its size\n");	
	/* data[0]=LSB (little endian)*/
	switch(size)
	{
		case 1:
		{
			data[offset]= (byte)word1;
			break;
		}

		case 2:
		{
			data[offset]= (byte)word1;
			data[offset+1]= (byte)(word1>>8);
			break;
		}

		case 4:
		{
			data[offset]= (byte)word1;
			data[offset+1]= (byte)(word1>>8);
			data[offset+2]= (byte)(word1>>16);
			data[offset+3]= (byte)(word1>>24);
			break;
		}

		case 8:
		{
			data[offset]= (byte)word1;
			data[offset+1]= (byte)(word1>>8);
			data[offset+2]= (byte)(word1>>16);
			data[offset+3]= (byte)(word1>>24);
			data[offset+4]= (byte)word2;
			data[offset+5]= (byte)(word2>>8);
			data[offset+6]= (byte)(word2>>16);
			data[offset+7]= (byte)(word2>>24);
			break;
		}
	}	
}

void Object:: getField(Field * field, u4 &word1, u4 &word2)
{
//printf("inside Object:: getField\n");
	u4 offset = field->getOffset();
	u1 size = field->getSize();
//printf("set the fields value due to its size\n");		
	/* data[0]=LSB (little endian)*/
	switch(size)
	{
		case 1:
		{
			word1 = data[offset];
			word2 = 0;
			break;
		}

		case 2:
		{
			word1 = ( ((u2)data[offset+1])<<8 )+ data[offset];
			word2 = 0;
			break;
		}

		case 4:
		{
			u4 temp = data[offset+2];
			word1 =( ((u4)data[offset+3])<<24) +(temp << 16) +
			( ((u2)data[offset+1])<<8) + data[offset];
			word2 = 0;
			break;
		}

		case 8:
		{
			u4 temp = data[offset+2];
			word1 =( ((u4)data[offset+3])<<24) +(temp << 16) +
			( ((u2)data[offset+1])<<8) + data[offset];

			temp = data[offset+6];
			word2 =( ((u4)data[offset+7])<<24) +(temp << 16) + 
			( ((u2)data[offset+5])<<8) + data[offset+4];
			break;
		}	
	}	
}

ClassData * Object:: getClassData()
{ return myClass; }


Object :: Object(int dims,int lengths [],int type,ClassData * myClass,ClassData * classType)
{
//printf("inside the constructor of Object specified to Arrays\n");	
numOfDims = dims;
	length = lengths[0];
	this->type = type;
	this->myClass = myClass;
	this->classType = classType;



  if(classType==NULL)
  {	
//printf("array of primitive types\n");
	if(dims==1)
	{
//printf("one dimensional array\n");
//printf("switch the array's type\n");
		switch(type)
		{
			case 4:   //T_BOOLEAN
			  entrySize = 1;
			  break;  
			case 5:   //T_CHAR  
			  entrySize = 2;
			  break;  
			case 6:   //T_FLOAT
			  entrySize = 4;
			  break;  
			case 7:   //T_DOUBLE
			  entrySize = 8;
			  break;  
			case 8:   //T_BYTE
			  entrySize = 1;
			  break;  
			case 9:   //T_SHORT
			  entrySize = 2;
			  break;  
			case 10:  //T_INT
			  entrySize = 4;
			  break;  
			case 11:  //T_LONG  
			  entrySize = 8;
			  break;  
		}
//printf("ask the heap to create the byte array that contains the array's elements\n");
		data = Heap:: createByteArray(length*entrySize);
		/* initialize to default value */
//printf("initialize the array to its default values\n");
		for(int i=0; i<length*entrySize ;i++)
			data[i]=0;
	}
	
	else
	{
//printf("Multi dimentional Array\n");
		entrySize = 4;
//printf("ask the heap to create the byte array that contains the array's elements that are arrays of lower dimentionality\n");
		data = Heap:: createByteArray(length*entrySize);
		Object * arr;
		int arrInt;
		lengths++;
		for(int i = 0; i<length*entrySize ;i+=entrySize)
		{
//printf("initialize the array's entry number %d  to an array of dim = %d\n",i,dims-1);			
			arr = Heap:: createArrayObject(dims-1,lengths,type,myClass,classType);
			arrInt = (int)arr;
			data[i]   = (byte)arrInt;
			data[i+1] = (byte)(arrInt>>8);
			data[i+2] = (byte)(arrInt>>16);
			data[i+3] = (byte)(arrInt>>24);
		}
	}
  }

  else
  {
//printf("array of references\n");
	if(dims==1)
	{
//printf("array of one dimension\n");
		entrySize = 4;
//printf("ask the heap to create the byte array containing the array's elements\n");
		data = Heap:: createByteArray(length*entrySize);
//printf("set the array elements to NULL\n");
		for(int i = 0; i<length*entrySize ;i++)
		   data[i] = 0;		
	}

	else
	{

//printf("Multi dimensional Array\n");
		entrySize = 4;
//printf("ask the heap to create the byte array that contains the array's elements that are arrays of lower dimensionality\n");
		data = Heap:: createByteArray(length*entrySize);
		Object * arr;
		int arrInt;
		for(int i = 0; i<length*entrySize ;i+=entrySize)
		{
//printf("initialize the array's entry number %d  to an array of dim = %d\n",i,dims-1);			
			arr = Heap:: createArrayObject(dims-1,++lengths,type,myClass,classType);
			arrInt = (int)arr;
			data[i]   = (byte)arrInt;
			data[i+1] = (byte)(arrInt>>8);
			data[i+2] = (byte)(arrInt>>16);
			data[i+3] = (byte)(arrInt>>24);
		}
	}
  	
  }	

}

void Object:: putElement(int index [], u4 word1, u4 word2)
//word2 is the most significant bytes
{
//printf("inside Object:: putElement for arrays' elements\n");
	int offset = index[0]*entrySize;

//	if(numOfDims == 1)
//	{
		switch(entrySize)
		{
			case 1:
			{
				data[offset] = (byte)word1;
				break;
			}

			case 2:
			{
				data[offset]= (byte)word1;
				data[offset+1]= (byte)(word1>>8);
				break;
			}

			case 4:
			{
				data[offset]=   (byte)word1;
				data[offset+1]= (byte)(word1>>8);
				data[offset+2]= (byte)(word1>>16);
				data[offset+3]= (byte)(word1>>24);
				break;
			}

			case 8:
			{
				data[offset]=   (byte)word1;
				data[offset+1]= (byte)(word1>>8);
				data[offset+2]= (byte)(word1>>16);
				data[offset+3]= (byte)(word1>>24);
				data[offset+4]= (byte)word2;
				data[offset+5]= (byte)(word2>>8);
				data[offset+6]= (byte)(word2>>16);
				data[offset+7]= (byte)(word2>>24);
				break;
			}	
		
		}
//	}
	
	/*else   //here entrySize = 4
	{
		Object * obj;
		u4 temp = data[offset+2];
		obj =(Object *)( ((u4)data[offset+3])<<24) +(temp << 16) +
		( ((u2)data[offset+1])<<8) + data[offset];
		
		obj->putElement(++index,word1,word2);

	}*/
}

void Object:: getElement(int index [], u4 & word1, u4 & word2)
{
//printf("inside Object:: getElement for arrays' elements\n");
	int offset = index[0]*entrySize;

	
	//if(numOfDims == 1)
	//{
		switch(entrySize)
		{
			case 1:
			{
				word1 = data[offset];
				word2 = 0;
				break;
			}

			case 2:
			{
				word1 = ( ((u2)data[offset+1])<<8 )+ data[offset];
				word2 = 0;
				break;
			}

			case 4:
			{
				u4 temp = data[offset+2];
				word1 =( ((u4)data[offset+3])<<24) +(temp << 16) +
				( ((u2)data[offset+1])<<8) + data[offset];
				word2 = 0;
				break;
			}

			case 8:
			{
				u4 temp = data[offset+2];
				word1 =( ((u4)data[offset+3])<<24) +(temp << 16) +
				( ((u2)data[offset+1])<<8) + data[offset];
	
				temp = data[offset+6];
				word2 =( ((u4)data[offset+7])<<24) +(temp << 16) + 
				( ((u2)data[offset+5])<<8) + data[offset+4];
				break;
			}	
		}
	//}
	
	/*else  //here entrySize = 4
	{
		Object * obj;
		u4 temp = data[offset+2];
		obj =(Object *)( ((u4)data[offset+3])<<24) +(temp << 16) +
		( ((u2)data[offset+1])<<8) + data[offset];
		
		obj->getElement(++index,word1,word2);
	}	*/
}

int Object::getArrayLength(void)
{ return length; }