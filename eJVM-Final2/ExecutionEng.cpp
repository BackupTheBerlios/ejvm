#include "ExecutionEng.h"
#include "JNIManager.h"
#include "stringLib.h"
using std::cout;  
using std::endl;
//-------------------------------------------------------------------------------------------------
ExecutionEng::ExecutionEng()
{
	this->mainThread = new Thread();
	if(mainThread == NULL)
	{
		cout<<"ExecutionEng: ExecutionEng: no suffiecinet memory"<<endl;
		exit(1);
	}
}
//------------------------------------------------------------------------------------------------
ExecutionEng::~ExecutionEng()
{
	delete mainThread;
	cout<<"ExecutionEngine Destructor"<<endl;
}
//--------------------------------------------------------------------------------------------------
ExecutionEng * ExecutionEng::execInstance=NULL;

ExecutionEng * ExecutionEng::getInstance()
{
	if(execInstance == NULL)
		execInstance= new ExecutionEng;
	
	return execInstance;
}
//---------------------------------------------------------------------------------------------
void ExecutionEng::deleteExec()
{
	delete execInstance;
	execInstance=NULL;
}
//---------------------------------------------------------------------------------------------------
void ExecutionEng::executeMethod(Object *object,Method * method,...)
{
	//1- get the current stack (with single thread, we only have the stack of mainThread).
	Stack * stack = mainThread->getStack();
	//Create the first frame in the invokation
	//2- push dummy frame in the stack to mark the beginning of execution
	//3- from the given method, get max_locals and max_operandStack
//	Frame * f =new Frame(method->getMaxLoacals(), method->getMaxStack(),true,method);
	Frame * f =new Frame(true,method);
	if(f == NULL)
	{
		cout<<"ExecutionEng: executeMethod: no suffiecinet memory"<<endl;
		exit(1);
	}
	//5- get the signature of the given method (function name and its arguments)
	char * desc = method->getDesc();
	cout<<"method desc: "<<desc<<endl;
	
	//Put the function parameters in the local variables
	//6- use the signature and the given va_list to put the arguments into local variables
	va_list ap; /* points to each unnamed arg in turn */
	char *p;
	u4 arg;
	u4 * vPtr = &arg;
	int index=0;//index to locals variables
	if(object)//if this the <init> method
	{
		*vPtr=(u4)object;
		f->setAtIndex(index,arg);//put in the local variables array at index index
		index++;
	}
	
	
	va_start(ap, method); //make ap point to first unamed argument
	p = desc; 
	cout<<*p;
	p++;     /* skip start ( */    
	while(*p != ')')
	{                         
       if((*p == 'J') || (*p == 'D'))
       {         
           //Insert Long and Double values in the Local Variables      
           *vPtr = va_arg(ap,u4);
           f->setAtIndex(index,arg);
           index++;
           *vPtr = va_arg(ap,u4);
           f->setAtIndex(index,arg);      
           index++ ;                      
           p++;                                  
       }
       else 
       {                                 
           if(*p == 'L' || *p == '[')//if the pareamete is a refrence (e.g. refrence to object or refrece to array object)
           {
          		*vPtr = va_arg(ap,u4); 
           }		
           else if(*p == 'F')
           {
           		*(float *)vPtr = va_arg(ap,double);
           }
           else
           {
           		*vPtr = va_arg(ap,u4);
           }
          f->setAtIndex(index,arg);
          index++; 
                                              
           if(*p == '[') 
           {
               for(p++; *p == '['; p++);         
               //to skip the type of array element, the following two lines if else will do that
               //so if the type of the array element is refrence, the if will skip it
               //if the type of the primitive type also it wil be skipped
           }
           
           if(*p == 'L')                         
               while(*p++ != ';');              
           else                                 
               p++;                              
       }                                         
    }                                            
    cout<<*p;
    p++;               /* skip end ) */
	cout<<*p<<endl<<endl;
	va_end(ap); /* clean up when done */	
	
	
	
	//4- push new frame 
	stack->push(f);
	//8- call interpret
	interpret(mainThread);
}
//-------------------------------------------------------------------------
void ExecutionEng::executeMethod(Object *object,Method * method,va_list ap)
{
	Stack * stack = mainThread->getStack();
	Frame * f =new Frame(true,method);
	if(f == NULL)
	{
		cout<<"ExecutionEng: executeMethod: no suffiecinet memory"<<endl;
		exit(1);
	}
	char * desc = method->getDesc();
	cout<<"method desc: "<<desc<<endl;
	
	char *p;
	u4 arg;
	u4 * vPtr = &arg;
	int index=0;//index to locals variables
	if(object)//if this the <init> method
	{
		*vPtr=(u4)object;
		f->setAtIndex(index,arg);//put in the local variables array at index index
		index++;
	}
	
	p = desc; 
	cout<<*p;
	p++;     /* skip start ( */    
	while(*p != ')')
	{                         
       if((*p == 'J') || (*p == 'D'))
       {         
           //Insert Long and Double values in the Local Variables                                    
           p++;                                  
       }
       else 
       {                                 
           if(*p == 'L' || *p == '[')//if the pareamete is a refrence (e.g. refrence to object or refrece to array object)
           {
          		*vPtr = va_arg(ap,u4); 
           }		
           else if(*p == 'F')
           {
           		*(float *)vPtr = va_arg(ap,double);
           }
           else
           {
           		*vPtr = va_arg(ap,u4);
           }
          f->setAtIndex(index,arg);
          index++; 
                                              
           if(*p == '[') 
               for(p++; *p == '['; p++);         
           if(*p == 'L')                         
               while(*p++ != ';');              
           else                                 
               p++;                              
       }                                         
    }                                            
    cout<<*p;
    p++;               /* skip end ) */
	cout<<*p<<endl<<endl;
	
	stack->push(f);
	interpret(mainThread);	
}
//--------------------------------------------------------------------------------------------
void ExecutionEng::executeMethod(Object *object,Method * method,jvalue * args)
{
	Stack * stack = mainThread->getStack();
	Frame * f =new Frame(true,method);
	if(f == NULL)
	{
		cout<<"ExecutionEng: executeMethod: no suffiecinet memory"<<endl;
		exit(1);
	}
	char * desc = method->getDesc();
	cout<<"method desc: "<<desc<<endl;
	
	char *p;
	u4 arg;
	u4 * vPtr = &arg;
	int index=0;//index to locals variables
	if(object)//if this the <init> method
	{
		*vPtr=(u4)object;
		f->setAtIndex(index,arg);//put in the local variables array at index index
		index++;
	}
	
	p = desc; 
	cout<<*p;
	p++;     /* skip start ( */    
	int argIndex=0;
	while(*p != ')')
	{                         
       if((*p == 'J') || (*p == 'D'))
       {         
           //Insert Long and Double values in the Local Variables                                    
           p++;                                  
       }
       else 
       {                                 
           if(*p == 'L' || *p == '[')//if the pareamete is a refrence (e.g. refrence to object or refrece to array object)
           {
          		*vPtr = args[argIndex].i; 
           }		
           else if(*p == 'F')
           {
           		*(float *)vPtr =  args[argIndex].f;
           }
           else
           {
           		*vPtr =  args[argIndex].i;
           }
          f->setAtIndex(index,arg);
          index++; 
          argIndex++;        
           if(*p == '[') 
               for(p++; *p == '['; p++);         
           if(*p == 'L')                         
               while(*p++ != ';');              
           else                                 
               p++;                              
       }                                         
    }                                            
    cout<<*p;
    p++;               /* skip end ) */
	cout<<*p<<endl<<endl;
	
	stack->push(f);
	interpret(mainThread);	
}
//--------------------------------------------------------------------------------------------
void ExecutionEng::interpret(Thread * thread)
{
	unsigned char* pc=NULL;
	Frame * currentFrame = mainThread->getStack()->getTopFrame();
	Method * method = currentFrame->getMethod();
	ByteCode * byteCode = method->getByteCode();
	ConstantPool * constantPool = method->getConstantPool();
	u1 * code = byteCode->getCode();
//	u4 temp,temp2;
	pc = code;
	
	
	while(true)
	{
		switch(*pc) {
			case NOP:
				pc++;
				break;
			case ACONST_NULL:
			currentFrame->push((u4)NULL);
			pc++;
			break;
			//Push the int constant <i> (-1, 0, 1, 2, 3, 4 or 5) onto the operand stack.
			case ICONST_M1:
			case ICONST_0:  
			case ICONST_1:
			case ICONST_2:	
			case ICONST_3:
			case ICONST_4:
			case ICONST_5:
				currentFrame->push((*pc -ICONST_0));
				cout<<"ICONST_"<<(*pc -ICONST_0)<<" : TopOfTheOperandStack= "<<currentFrame->getTopOpStack()<<endl;
				pc++;	
				break;         
			case LCONST_0:
			case LCONST_1:
				{
					u4 Long[2] ; 
					Long[0]=0;
					Long[1]=0;
					*(long long *)Long=(*pc -LCONST_0);
					//operandStack: ...=> ...,word1,word2
					currentFrame->push(Long[0]);
					currentFrame->push(Long[1]);
					cout<<"LCONST_"<<(*pc -LCONST_0)<<" : TopOfTheOperandStack= "<<*(long long *)Long<<endl;
				}
				pc++;
				break;
			case FCONST_0:
			case FCONST_1:      
			case FCONST_2:
				{
					u4 u4num ;
					u4 * ptr =&u4num;
					float fnum=(float)*pc - (float)FCONST_0;
					*(float * )ptr = fnum;
					currentFrame->push(*ptr);
					cout<<"FCONST_"<<(*pc -FCONST_0)<<" : TopOfTheOperandStack= "<<*(float *)ptr<<endl;
				}
				pc++;
				break;
			case DCONST_0:
			case DCONST_1:
				{
					u4 Double[2];
					*(double *)Double =(double) (*pc -DCONST_0);
					currentFrame->push(Double[0]);
					currentFrame->push(Double[1]);
					cout<<"DCONST_"<<(*pc -DCONST_0)<<" : TopOfTheOperandStack= ";
					printf("%.1f\n",*(double *)Double);
				}
				pc++;
				break;
			case BIPUSH:
				{
					int value = *(pc+1);
					currentFrame->push(value);
					cout<<"BIPUSH: theVlaue="<<currentFrame->getTopOpStack()<<endl;
				}
				pc+=2;
				break;
			case SIPUSH:
				{
					u1 	byte1 = *(pc+1);
					u1  byte2 = *(pc+2);
					int value = (byte1 << 8) | byte2;
					currentFrame->push(value);
					cout<<"SIPUSH: The Value="<<currentFrame->getTopOpStack()<<endl;
				}
				pc+=3;
				break;
			case LDC:
				{
					u1 index= *(pc+1);
					u4 word;
					constantPool->getWord(index,word);
					currentFrame->push(word);
					cout<<"LDC: Ivalue="<<word<<endl;
					printf("Fvalue=%.1f\n",computFloat(word));
				}
				pc+=2;
				break;
			case LDC_W:
				{
					u1 indexbyte1 = *(pc+1);
					u1 indexbyte2 = *(pc+2);
					u4 word;
					constantPool->getWord(((indexbyte1 << 8) | indexbyte2),word);
					currentFrame->push(word);
					cout<<"LDC_W: Ivalue="<<word<<endl;
					printf("Fvalue=%.1f\n",computFloat(word));
				}
				pc+=3;
				break;
			case LDC2_W:
				{
					u1 indexbyte1 = *(pc+1);
					u1 indexbyte2 = *(pc+2);
					u4 word1, word2;
					constantPool->get2Words(((indexbyte1 << 8) | indexbyte2),word1,word2);
					u4 longOrDouble[2] ; 
					longOrDouble[0]=word1;
					longOrDouble[1]=word2;
					//push the least significant bits first, where word1 is the least significant bit,then push the most significant bits
					//operandStack: ...=> ...,word1,word2
					currentFrame->push(word1);
					//operandStack: ...=> ...,word1
					currentFrame->push(word2);
					//operandStack: ...=> ...,word1,word2
					cout<<"LDC2_W: value="<<*(long long *)longOrDouble<<endl;
					printf("%.1lf\n",computDouble(word1,word2));
				}
				pc+=3;
				break;
			case ILOAD:
				{
					u1 index = *(pc+1);
					u4 word = currentFrame->getAtIndex(index);
					currentFrame->push(word);
					cout<<"ILOAD: theIndex="<<(int)index<<"  theValueAtTheTopOfTheStack="<<(int)currentFrame->getTopOpStack()<<endl;
				}
				pc+=2;
				break;
			case LLOAD:
				{
					u1 index = *(pc+1);
					u4 word1 = currentFrame->getAtIndex(index);
					u4 word2 = currentFrame->getAtIndex(index+1);
					u4 longValue[2];
					longValue[0]=word1;
					longValue[1]=word2;
					//push the least significant bits first, where word1 is the least significant bit,then push the most significant bits
					//operandStack: ...=> ...,word1,word2
					currentFrame->push(word1);
					//operandStack: ...,word1
					currentFrame->push(word2);
					//operandStack: ..,word1,word2
					cout<<"LLOAD: theIndex="<<(int)index<<"  theLongValueAtTopOfStack="<<*(long long *)longValue<<endl;
				}
				pc+=2;
				break;
			case FLOAD:
				{
					u1 index = *(pc+1);
					u4 word = currentFrame->getAtIndex(index);
					currentFrame->push(word);
					printf("FLOAD: theIndex=%d  theValueAtTheTopOfTheStack=%.1f\n",index,computFloat(word));
				}
				pc+=2;
				break;
			case DLOAD:
				{
					u1 index = *(pc+1);
					u4 word1 = currentFrame->getAtIndex(index);
					u4 word2 = currentFrame->getAtIndex(index+1);
					//operandStack: ...=> ...,word1,word2
					currentFrame->push(word1);
					//operandStack: ...=> ...,word1
					currentFrame->push(word2);
					//operandStack: ..,word1,word2
					cout<<"DLOAD: theIndex="<<(int)index<<"  theDoubleValueAtTopOfStack=";
					printf("%.1lf\n",computDouble(word1,word2));
				}				
				pc+=2;
				break;
			case ALOAD:
				{
					u1 index = *(pc+1);
					u4 word = currentFrame->getAtIndex(index);
					currentFrame->push(word);
					cout<<"ALOAD: theIndex="<<(int)index<<"  theValueAtTheTopOfTheStack="<<(Object *)word<<endl;
				}
				pc+=2;
				break;
			case ILOAD_0 :  
			case ILOAD_1 :  
			case ILOAD_2 :
			case ILOAD_3 :
				{
					u4 temp=currentFrame->getAtIndex(*pc - ILOAD_0);
					currentFrame->push(temp);
					cout<<"ILOAD_"<<(*pc - ILOAD_0)<<": value at index"<<(*pc - ILOAD_0)<<"="<<(int)temp<<"  value at the top of the stack="<<(int)currentFrame->getTopOpStack()<<endl;
				}
				pc++;	
				break;   
			case LLOAD_0:
			case LLOAD_1:
			case LLOAD_2:
			case LLOAD_3:
				{
					u4 word1 = currentFrame->getAtIndex(*pc - LLOAD_0);
					u4 word2 = currentFrame->getAtIndex((*pc - LLOAD_0)+1);
					u4 longValue[2];
					longValue[0]=word1;
					longValue[1]=word2;
					currentFrame->push(word1);
					currentFrame->push(word2);
					cout<<"LLOAD_"<<(*pc - LLOAD_0)<<": theLongValue="<<*(long long *)longValue<<endl;
				}
				pc++;
				break;
			case FLOAD_0:             
			case FLOAD_1:
			case FLOAD_2:
			case FLOAD_3:
				{
					u4 temp=currentFrame->getAtIndex(*pc - FLOAD_0);
					currentFrame->push(temp);
					u4 * ptr=& temp;
					cout<<"FLOAD_"<<(*pc - FLOAD_0)<<": value at the top of the Stack=";
					printf("%.1f\n",computFloat(temp));
				}
				pc++;
				break;
			case DLOAD_0:
			case DLOAD_1:
			case DLOAD_2:
			case DLOAD_3:
				{
					u4 word1 = currentFrame->getAtIndex(*pc - DLOAD_0);
					u4 word2 = currentFrame->getAtIndex((*pc - DLOAD_0)+1);
					currentFrame->push(word1);
					currentFrame->push(word2);
					cout<<"DLOAD_"<<(*pc - DLOAD_0)<<": theDoubleValue=";
					printf("%.1lf\n",computDouble(word1,word2));
				}
				pc++;
				break;
			case ALOAD_0 :
			case ALOAD_1 :
			case ALOAD_2 :
			case ALOAD_3 :
				{
					u4 temp=currentFrame->getAtIndex(*pc - ALOAD_0);
					currentFrame->push(temp);
					cout<<"ALOAD_"<<(*pc - ALOAD_0)<<": value at index"<<(*pc - ALOAD_0)<<"="<<(Object *)temp<<"  value at the top of the stack="<<(Object *)currentFrame->getTopOpStack()<<endl;
				}
				pc++;
				break;    
			case IALOAD:
				{
					int index[1];
					index[0]=currentFrame->pop();
					Object * arrayref=(Object *)currentFrame->pop();
					u4 value;
					u4 temp;
					arrayref->getElement(index,value,temp);
					currentFrame->push(value);
					cout<<"IALOAD: theIndex="<<index[0]<<" theValue="<<value<<endl;
				}
				pc++;
				break;
			case AALOAD:
				{
					int index[1];
					index[0]=currentFrame->pop();
					Object * arrayref=(Object *)currentFrame->pop();
					u4 value;
					u4 temp;
					arrayref->getElement(index,value,temp);
					currentFrame->push(value);
					cout<<"AALOAD: theIndex="<<index[0]<<" theValue="<<(Object *)value<<endl;
				}
				pc++;
				break;
			case ISTORE:
				{
					u1 index = *(pc+1);
					u4 word = currentFrame->pop();
					currentFrame->setAtIndex(index,word);
					cout<<"ISTORE: theIndex="<<(int)index<<" theValue="<<word<<endl;
				}
				pc+=2;
				break; 
			case LSTORE:
				{
					u1 index = *(pc+1);
					//operandStack: ...,word1,word2=>...
					u4 word2= currentFrame->pop();
					//operandStack: ...,word1
					u4 word1= currentFrame->pop();
					//operandStack: ...
					u4 longValue[2] ; 
					longValue[0]=word1;
					longValue[1]=word2;
					//we will put at index  the least significant bit(word1) then we will put at index+1 the most significant bits (word2)
					//localVariable[index]=word1
					//localVariable[index+1]=word2
					currentFrame->setAtIndex(index,word1);
					currentFrame->setAtIndex(index+1,word2);
					cout<<"LSTORE: theIndex="<<(int)index<<" theLongValue="<<*(long long *)longValue<<endl;
				}
				pc+=2;
				break;     
			case FSTORE:
				{
					u1 index = *(pc+1);
					u4 word = currentFrame->pop();
					currentFrame->setAtIndex(index,word);
					printf("FSTORE: theIndex=%d  theValueAtTheTopOfTheStack=%.1f\n",index,computFloat(word));
				}
				pc+=2;
				break;      
			case DSTORE:
				{
					u1 index = *(pc+1);
					//operandStack: ...,word1,word2=>...
					u4 word2= currentFrame->pop();
					//operandStack: ...,word1
					u4 word1= currentFrame->pop();
					//operandStack: ...
					//localVariable[index]=word1
					//localVariable[index+1]=word2
					currentFrame->setAtIndex(index,word1);
					currentFrame->setAtIndex(index+1,word2);
					cout<<"DSTORE: theIndex="<<(int)index<<" theDoubleValue=";
					printf("%.1lf\n",computDouble(word1,word2));
				}
				pc+=2;
				break;
			case ASTORE:
				{
					u1 index = *(pc+1);
					u4 word = currentFrame->pop();
					currentFrame->setAtIndex(index,word);
					cout<<"FSTORE: theIndex="<<(int)index<<" theObject="<<(Object *)word<<endl;
				}
				pc+=2;
				break; 
			case ISTORE_0:  
			case ISTORE_1:
			case ISTORE_2: 
			case ISTORE_3:
				{
					u4 temp = currentFrame->pop();
					currentFrame->setAtIndex((*pc - ISTORE_0 ),temp);
					cout<<"ISTORE_"<<(*pc - ISTORE_0 )<<": "<<"value Poped="<<(int)temp<<" value at index "<<(*pc - ISTORE_0 )<<"="<<(int)currentFrame->getAtIndex((*pc - ISTORE_0 ))<<endl;
				}
				pc++;	
				break;    
			case LSTORE_0:
			case LSTORE_1:
			case LSTORE_2:
			case LSTORE_3:
				{
					//operandStack: ...,word1,word2=>...
					u4 word2= currentFrame->pop();
					//operandStack: ...,word1
					u4 word1= currentFrame->pop();
					//operandStack: ...
					u4 longValue[2] ; 
					longValue[0]=word1;
					longValue[1]=word2;
					//we will put at index  the least significant bit(word1) then we will put at index+1 the most significant bits (word2)
					//localVariable[index]=word1
					//localVariable[index+1]=word2
					currentFrame->setAtIndex((*pc - LSTORE_0 ),word1);
					currentFrame->setAtIndex(((*pc - LSTORE_0)+1),word2);
					cout<<"LSTORE_"<<(*pc - LSTORE_0 )<<": theLongValue="<<*(long long *)longValue<<endl;
				}
				pc++;
				break;
			case FSTORE_0:    
			case FSTORE_1:
			case FSTORE_2:
			case FSTORE_3:
				{
					u4 u4num=currentFrame->pop();
					u4 * ptr = & u4num;
					currentFrame->setAtIndex((*pc - FSTORE_0 ),u4num);
					cout<<"FSTORE_"<<(*pc - FSTORE_0 )<<": value Poped=";
					printf("%.1f\n",computFloat(u4num));
				}
				pc++;
				break;
			case DSTORE_0:
			case DSTORE_1:
			case DSTORE_2:
			case DSTORE_3:
				{
					//operandStack: ...,word1,word2=>...
					u4 word2= currentFrame->pop();
					//operandStack: ...,word1
					u4 word1= currentFrame->pop();
					//operandStack: ...
					currentFrame->setAtIndex((*pc - DSTORE_0 ),word1);
					currentFrame->setAtIndex(((*pc - DSTORE_0)+1),word2);
					cout<<"DSTORE_"<<(*pc - DSTORE_0 )<<": theDoubleValue=";
					printf("%.1lf\n",computDouble(word1,word2));
				}
				pc++;
				break;
			case ASTORE_0:
			case ASTORE_1:        
			case ASTORE_2:
			case ASTORE_3:
				{
					u4 temp = currentFrame->pop();
					currentFrame->setAtIndex((*pc - ASTORE_0 ),temp);
					cout<<"ASTORE_"<<(*pc - ASTORE_0 )<<": "<<"value Poped="<<(Object *)temp<<" value at index "<<(*pc - ASTORE_0 )<<"="<<(Object *)currentFrame->getAtIndex((*pc - ASTORE_0 ))<<endl;
				}
				pc++;
				break;
			case IASTORE:
				{
					int value= currentFrame->pop();
					int index[1];
					index[0]= currentFrame->pop();
					Object * arrayref=(Object *)currentFrame->pop();
					arrayref->putElement(index,value);
					cout<<"IASTORE: theIndex"<<index[0]<<" theValue="<<value<<endl;
				}
				pc++;
				break;
			case POP:
				{
					u4 temp = currentFrame->pop();
					cout<<"POP: ValuePoped"<<temp<<endl;
				}
				pc++;
				break;
			case POP2:
				{
					u4 value1=currentFrame->pop();
					u4 value2=currentFrame->pop();
					cout<<"POP2: Value1="<<value1<<" value2="<<value2<<endl;
				}
				pc++;
				break;
			case DUP:
				{
					u4 temp=currentFrame->getTopOpStack();
					currentFrame->push(temp);
					cout<<"DUP: "<<"TopOfStack="<<currentFrame->getTopOpStack()<<endl;
				}
				pc++;
				break;
			case DUP_X1:
				{
					u4 value1=currentFrame->pop();
					u4 value2=currentFrame->pop();
					currentFrame->push(value1);
					currentFrame->push(value2);
					currentFrame->push(value1);
					cout<<"DUP_X1: "<<"TopOfStack="<<currentFrame->getTopOpStack()<<endl;
				}
				pc++;
				break;
			case DUP_X2:
				{
					u4 value1=currentFrame->pop();
					u4 value2=currentFrame->pop();
					u4 value3=currentFrame->pop();
					currentFrame->push(value1);
					currentFrame->push(value3);
					currentFrame->push(value2);
					currentFrame->push(value1);
					cout<<"DUP_X2: "<<"TopOfStack="<<currentFrame->getTopOpStack()<<endl;
				}
				pc++;
				break;
			case DUP2:
				{
					u4 value1=currentFrame->pop();
					u4 value2=currentFrame->pop();
					currentFrame->push(value2); currentFrame->push(value1);
					currentFrame->push(value2); currentFrame->push(value1);
					cout<<"DUP2: Value1="<<value1<<" Value2="<<value2<<endl;
				}
				pc++;
				break;
			case SWAP:
				{
					cout<<"SWAP: ";
					u4 t1 = currentFrame->pop();
					cout<<"Value1 Poped="<<t1;
					u4 t2 = currentFrame->pop();
					cout<<"\tValue2 Poped="<<t2;
					currentFrame->push(t1);
					cout<<"\tValueOnTopOfTheStack="<<currentFrame->getTopOpStack();
					currentFrame->push(t2);
					cout<<"\tValueOnTopOfTheStack="<<currentFrame->getTopOpStack()<<endl;
				}
				pc++;
				break;
			case IADD:
				{
					u4 value2=currentFrame->pop();
					u4 value1=currentFrame->pop();
					currentFrame->push((int)value1+(int)value2);                
					cout<<"IADD: Value1="<<(int)value1<<" Value2="<<(int)value2<<" Result="<<(int)currentFrame->getTopOpStack()<<endl;
				}
				pc++;	
				break;
			case LADD:
				{
					u4 word2=currentFrame->pop();
					u4 word1=currentFrame->pop();
					u4 value2[2];
					value2[0]=word1;
					value2[1]=word2;
					word2=currentFrame->pop();
					word1=currentFrame->pop();
					u4 value1[2];
					value1[0]=word1;
					value1[1]=word2;
					u4 result[2];
					*(long long *)result=(*(long long *)value1) + (*(long long *)value2);
					word1=result[0];
					word2=result[1];
					currentFrame->push(word1);
					currentFrame->push(word2);
					cout<<"LADD: Value1="<<*(long long *)value1<<" Value2="<<*(long long *)value2<<" Result="<<*(long long *)result<<endl;
				}
				pc++;
				break;
			case FADD:
				{
					float value2 = computFloat(currentFrame->pop());
					float value1 = computFloat(currentFrame->pop());
					float fresult = value1 + value2;
					u4 result;
					u4 * ptr=&result;
					*(float *)ptr= fresult;
					currentFrame->push(*ptr);
					printf("FADD: Value1=%.1f Value2=%.1f  Result=%.1f\n",value1,value2,*(float *)ptr);
				}
				pc++;
				break;
			case DADD:
				{
					u4 word2=currentFrame->pop();
					u4 word1=currentFrame->pop();
					double value2=computDouble(word1,word2);
					word2=currentFrame->pop();
					word1=currentFrame->pop();
					double value1=computDouble(word1,word2);
					u4 result[2];
					*(double *)result = value1 + value2;
					word1=result[0];
					word2=result[1];
					currentFrame->push(word1);
					currentFrame->push(word2);
//					cout<<"DADD: Value1="<<(double)value1<<" Value2="<<(double)value2<<" Result="<<*(double *)result<<endl;
					printf("DADD: Value1=%.1lf Value2=%.1lf Result=%.1lf\n",value1,value2,*(double *)result);
				}
				pc++;
				break;
			case ISUB:
				{
					u4 value2=currentFrame->pop();
					u4 value1=currentFrame->pop();
					int result = (int) value1 - (int) value2;
					currentFrame->push(result);
					cout<<"ISUB: Value1="<<(int)value1<<" Value2="<<(int)value2<<" Result="<<(int)currentFrame->getTopOpStack()<<endl;
				}
				pc++;
				break;
			case LSUB:
				{
					u4 word2=currentFrame->pop();
					u4 word1=currentFrame->pop();
					u4 value2[2];
					value2[0]=word1;
					value2[1]=word2;
					word2=currentFrame->pop();
					word1=currentFrame->pop();
					u4 value1[2];
					value1[0]=word1;
					value1[1]=word2;
					u4 result[2];
					*(long long *)result=(*(long long *)value1) - (*(long long *)value2);
					word1=result[0];
					word2=result[1];
					currentFrame->push(word1);
					currentFrame->push(word2);
					cout<<"LSUB: Value1="<<*(long long *)value1<<" Value2="<<*(long long *)value2<<" Result="<<*(long long *)result<<endl;
				}
				pc++;
				break;
			case FSUB:
				{
					u4 value2=currentFrame->pop();
					float fValue2=computFloat(value2);
					u4 value1=currentFrame->pop();
					float fValue1=computFloat(value1);
					float fresult=fValue1 - fValue2; 
					u4 result;
					u4 * pResult = &result;
					*(float *)pResult = fresult;
					currentFrame->push(*pResult);
					printf("FSUB: Value1=%.1f Value2=%.1f  Result=%.1f\n",fValue1,fValue2,*(float *)pResult);
				}
				pc++;
				break;
			case DSUB:
				{
					u4 word2=currentFrame->pop();
					u4 word1=currentFrame->pop();
					double value2=computDouble(word1,word2);
					word2=currentFrame->pop();
					word1=currentFrame->pop();
					double value1=computDouble(word1,word2);
					u4 result[2];
					*(double *)result = value1 - value2;
					word1=result[0];
					word2=result[1];
					currentFrame->push(word1);
					currentFrame->push(word2);
					printf("DSUB: Value1=%.1lf Value2=%.1lf Result=%.1lf\n",value1,value2,*(double *)result);
				}
				pc++;
				break;
			case IMUL:
				{
					u4 value2=currentFrame->pop();
					u4 value1=currentFrame->pop();
					int result = (int) value1 * (int) value2;
					currentFrame->push(result);
					cout<<"IMUL: Value1="<<(int)value1<<" Value2="<<(int)value2<<" Result="<<(int)currentFrame->getTopOpStack()<<endl;
				}
				pc++;
				break;
			case LMUL:
				{
					u4 word2=currentFrame->pop();
					u4 word1=currentFrame->pop();
					u4 value2[2];
					value2[0]=word1;
					value2[1]=word2;
					word2=currentFrame->pop();
					word1=currentFrame->pop();
					u4 value1[2];
					value1[0]=word1;
					value1[1]=word2;
					u4 result[2];
					*(long long *)result=(*(long long *)value1) * (*(long long *)value2);
					word1=result[0];
					word2=result[1];
					currentFrame->push(word1);
					currentFrame->push(word2);
					cout<<"LMUL: Value1="<<*(long long *)value1<<" Value2="<<*(long long *)value2<<" Result="<<*(long long *)result<<endl;
				}
				pc++;
				break;
			case FMUL:
				{
					u4 value2=currentFrame->pop();
					float fValue2=computFloat(value2);
					u4 value1=currentFrame->pop();
					float fValue1=computFloat(value1);
					float fresult=fValue1 * fValue2; 
					u4 result;
					u4 * pResult = &result;
					*(float *)pResult = fresult;
					currentFrame->push(*pResult);
					printf("FMUL: Value1=%.1f Value2=%.1f  Result=%.1f\n",fValue1,fValue2,*(float *)pResult);
				}
				pc++;
				break;
			case DMUL:
				{
					u4 word2=currentFrame->pop();
					u4 word1=currentFrame->pop();
					double value2=computDouble(word1,word2);
					word2=currentFrame->pop();
					word1=currentFrame->pop();
					double value1=computDouble(word1,word2);
					u4 result[2];
					*(double *)result = value1 * value2;
					word1=result[0];
					word2=result[1];
					currentFrame->push(word1);
					currentFrame->push(word2);
					printf("DMUL: Value1=%.1lf Value2=%.1lf Result=%.1lf\n",value1,value2,*(double *)result);
				}
				pc++;
				break;
			case IDIV:
				{
					u4 value2=currentFrame->pop();
					u4 value1=currentFrame->pop();
					currentFrame->push((int)value1/(int)value2);     //note temp2/temp not the reverse order temp/temp2     
					cout<<"IDIV: Value1="<<(int)value1<<" Value2="<<(int)value2<<" Result="<<(int)currentFrame->getTopOpStack()<<endl;
				}
				pc++;
				break;
			case LDIV:
				{
					u4 word2=currentFrame->pop();
					u4 word1=currentFrame->pop();
					u4 value2[2];
					value2[0]=word1;
					value2[1]=word2;
					word2=currentFrame->pop();
					word1=currentFrame->pop();
					u4 value1[2];
					value1[0]=word1;
					value1[1]=word2;
					u4 result[2];
					*(long long *)result=(*(long long *)value1) / (*(long long *)value2);
					word1=result[0];
					word2=result[1];
					currentFrame->push(word1);
					currentFrame->push(word2);
					cout<<"LDIV: Value1="<<*(long long *)value1<<" Value2="<<*(long long *)value2<<" Result="<<*(long long *)result<<endl;
				}
				pc++;
				break;
			case FDIV:
				{
					u4 value2=currentFrame->pop();
				//	u4 * pValue2 = &value2;
					float fValue2=computFloat(value2);
					u4 value1=currentFrame->pop();
					//u4 * pValue1 = &value1;
					float fValue1=computFloat(value1);
					//float fresult = *(float *)pValue1 / *(float *)pValue2;
					float fresult=fValue1/fValue2; 
					u4 result;
					u4 * pResult = &result;
					*(float *)pResult = fresult;
					currentFrame->push(*pResult);
					//cout<<"FDIV: Value1="<<*(float *)pValue1<<" Value2="<<*(float *)pValue2<<" Result="<<*(float *)pResult<<endl;
					//cout<<"REsult in u4="<<*pResult<<endl;
					printf("FDIV: Value1=%.1f Value2=%.1f  Result=%.1f\n",fValue1,fValue2,*(float *)pResult);
				}
				pc++;
				break;
			case DDIV:
				{
					u4 word2=currentFrame->pop();
					u4 word1=currentFrame->pop();
					double value2=computDouble(word1,word2);
					word2=currentFrame->pop();
					word1=currentFrame->pop();
					double value1=computDouble(word1,word2);
					u4 result[2];
					*(double *)result = value1 / value2;
					word1=result[0];
					word2=result[1];
					currentFrame->push(word1);
					currentFrame->push(word2);
					printf("DDIVs: Value1=%.1lf Value2=%.1lf Result=%.1lf\n",value1,value2,*(double *)result);
				}
				pc++;
				break;
			case IREM:
				{
					int value2=currentFrame->pop();
					int value1=currentFrame->pop();
					int result = value1 - (value1 / value2) * value2;
					currentFrame->push(result);
					cout<<"IREM: value1="<<value1<<" value2="<<value2<<" result="<<result<<endl;
				}
				pc++;
				break;
			case IINC:
				{
					u1 index= *(pc+1);
					signed char Const= (signed char)*(pc+2);
					int value= currentFrame->getAtIndex((int)index);
					cout<<"IINC: index="<<(int)index<<" valueBefore="<<value<<" const="<<(int)Const;
					value+=(int)Const;
					currentFrame->setAtIndex((int)index,value);
					cout<<" newValeue="<<value<<endl;
				}
				pc+=3;
				break;
			case IFEQ:
			case IFNE:
			case IFLT:
			case IFGE:
			case IFGT:
			case IFLE:
			case IF_ICMPEQ:	
			case IF_ICMPNE:
			case IF_ICMPLT:
			case IF_ICMPGE:
			case IF_ICMPGT:
			case IF_ICMPLE:
				{
					u4 value2;
					if(IFEQ<=*pc && *pc<=IFLE)
						value2=0;
					else
						value2 = currentFrame->pop();
					u4 value1 = currentFrame->pop();
					if(compare((int) value1,(int) value2,*pc))
					{//succeed 
						u1 branchbyte1 = *(pc+1);
						u1 branchbyte2 = *(pc+2);
						short int offset =(short int ) (branchbyte1 << 8) | branchbyte2;
						pc =pc+offset;
						cout<<"offset="<<offset<<endl;
					}
					else
					{ 
						cout<<"execution proceed noramlly"<<endl;
						pc+=3;
					}
				}
				break;
			case GOTO:
				{
					u1 branchbyte1 = *(pc+1);
					u1 branchbyte2 = *(pc+2);
					short int offset =(short int ) (branchbyte1 << 8) | branchbyte2;
					pc = pc+offset;
					cout<<"GOTO: offset="<<offset<<endl;
				}
				break;
			case IRETURN:
				{
					//pop the current frame from the stack,the current frame is held in the currentfarme variable
					mainThread->getStack()->pop();
					Frame * invokingFrame = mainThread->getStack()->getTopFrame();
					
					//pop the return valus from the operand stack of the invoked method 
					//and push it in the operand stack of the invoking method
					invokingFrame->push(currentFrame->pop());
					
					//free up the memory occupied by the invoked method 
					delete currentFrame;
					
					currentFrame = invokingFrame;
					method = currentFrame->getMethod();
					byteCode = method->getByteCode();
					constantPool = method->getConstantPool();
					code = byteCode->getCode();
					pc = currentFrame->PC;
					
					cout<<"IRETURN: return Int="<<currentFrame->getTopOpStack()<<endl<<endl;
					cout<<"continue: "<<method->getName()<<"\t"<<method->getDesc()<<endl;
				}
				break;
			case LRETURN:
				{
					//pop the current frame from the stack,the current frame is held in the currentfarme variable
					mainThread->getStack()->pop();
					Frame * invokingFrame = mainThread->getStack()->getTopFrame();
					//pop the return valus from the operand stack of the invoked method 
					//and push it in the operand stack of the invoking method
					u4 word2=currentFrame->pop();
					u4 word1=currentFrame->pop();
					invokingFrame->push(word1);
					invokingFrame->push(word2);
					u4 result[2];
					result[0]=word1;
					result[1]=word2;
					
					delete currentFrame;
					currentFrame = invokingFrame;
					method = currentFrame->getMethod();
					byteCode = method->getByteCode();
					constantPool = method->getConstantPool();
					code = byteCode->getCode();
					pc = currentFrame->PC;
					cout<<"LRETURN: return long="<<*(long long *)result<<endl<<endl;
					cout<<"continue: "<<method->getName()<<"\t"<<method->getDesc()<<endl;
				}
				break;
			case FRETURN:
				{
					//pop the current frame from the stack,the current frame is held in the currentfarme variable
					mainThread->getStack()->pop();
					Frame * invokingFrame = mainThread->getStack()->getTopFrame();
					//pop the return valus from the operand stack of the invoked method 
					//and push it in the operand stack of the invoking method
					invokingFrame->push(currentFrame->pop());
					//free up the memory occupied by the invoked method 
					delete currentFrame;
					
					currentFrame = invokingFrame;
					method = currentFrame->getMethod();
					byteCode = method->getByteCode();
					constantPool = method->getConstantPool();
					code = byteCode->getCode();
					pc = currentFrame->PC;
					printf("FRETURN: return float=%.1f\n\n",computFloat(currentFrame->getTopOpStack()));
					cout<<"continue: "<<method->getName()<<"\t"<<method->getDesc()<<endl;
				}
				break;
			case DRETURN:
				{
					//pop the current frame from the stack,the current frame is held in the currentfarme variable
					mainThread->getStack()->pop();
					Frame * invokingFrame = mainThread->getStack()->getTopFrame();
					//pop the return valus from the operand stack of the invoked method 
					//and push it in the operand stack of the invoking method
					u4 word2=currentFrame->pop();
					u4 word1=currentFrame->pop();
					invokingFrame->push(word1);
					invokingFrame->push(word2);
					
					
					delete currentFrame;
					currentFrame = invokingFrame;
					method = currentFrame->getMethod();
					byteCode = method->getByteCode();
					constantPool = method->getConstantPool();
					code = byteCode->getCode();
					pc = currentFrame->PC;
					printf("DRETURN: return Double=%.1lf\n\n",computDouble(word1,word2));
					cout<<"continue: "<<method->getName()<<"\t"<<method->getDesc()<<endl;
				}
				break;
			case ARETURN:
				{
					//pop the current frame from the stack,the current frame is held in the currentfarme variable
					mainThread->getStack()->pop();
					Frame * invokingFrame = mainThread->getStack()->getTopFrame();
					
					//pop the return valus from the operand stack of the invoked method 
					//and push it in the operand stack of the invoking method
					invokingFrame->push(currentFrame->pop());
					
					//free up the memory occupied by the invoked method 
					delete currentFrame;
					
					currentFrame = invokingFrame;
					method = currentFrame->getMethod();
					byteCode = method->getByteCode();
					constantPool = method->getConstantPool();
					code = byteCode->getCode();
					pc = currentFrame->PC;
					
					cout<<"ARETURN: returnRefrence="<<(Object *)currentFrame->getTopOpStack()<<endl<<endl;
					cout<<"continue: "<<method->getName()<<"\t"<<method->getDesc()<<endl;
				}
				break;
			case RETURN:
				{
					if(currentFrame->isTopOfJavaInvoc())
					{//This is the top of Java invocation. so we must return from 
						//we must pop this frame from the thread stack and delete it to free location
						delete mainThread->getStack()->pop();
						cout<<"RETURN: return void"<<endl;
						return;
					}
					mainThread->getStack()->pop();
					Frame * invokingFrame = mainThread->getStack()->getTopFrame();
					delete currentFrame;
					currentFrame = invokingFrame;
					method = currentFrame->getMethod();
					byteCode = method->getByteCode();
					constantPool = method->getConstantPool();
					code = byteCode->getCode();
					pc = currentFrame->PC;
					
					cout<<"RETURN: return void"<<endl<<endl;
					cout<<"continue: "<<method->getName()<<"\t"<<method->getDesc()<<endl;
				}
				break;
			case GETSTATIC:
				{
					u1 indexbyte1 = *(pc+1);
					u1 indexbyte2 = *(pc+2);
					u4 word1,word2;
					Field * field = constantPool->getFieldData((indexbyte1 << 8) | indexbyte2);
					char * p = field->getDesc();
					ClassData * cl = field->getOwnerClass();
					if(!cl->isInitialized())
						cl->initialize();
						
					field->getStaticValue(word1,word2);
					if((*p == 'J') || (*p == 'D'))//double or long will occupy 2 entries(words)in OperandStack
					{
						//push word1 and word 2 in operand stack
					}
					else//any other type will occupy only one word (entry)in OPerandStack
					{
						//push word1 only in the operand stack
						currentFrame->push(word1);
					}
					
					cout<<field->getName()<<"\t"<<field->getDesc()<<endl;
					cout<<"GETSTATIC: theValue="<<word1<<endl;
				}
				pc+=3;
				break;
			case PUTSTATIC:
				{
					u1 indexbyte1 = *(pc+1);
					u1 indexbyte2 = *(pc+2);
					u4 word1,word2;
					Field * field = constantPool->getFieldData((indexbyte1 << 8) | indexbyte2);
					char * p = field->getDesc();
					ClassData * cl = field->getOwnerClass();
					if(!cl->isInitialized())
						cl->initialize();
					
					if((*p == 'J') || (*p == 'D'))//double or long will occupy 2 entries(words)in OperandStack
					{
						//put in word1 and word 2
					}
					else//any other type will occupy only one word (entry)in OPerandStack
					{
						word1= currentFrame->pop();
					}
					
					field->putStaticValue(word1,word2);
					cout<<field->getName()<<"\t"<<field->getDesc()<<endl;
					cout<<"PUTSTATIC: theValue="<<word1<<endl;
				}
				pc+=3;
				break;
			case GETFIELD:
				{
					u1 indexbyte1 = *(pc+1);
					u1 indexbyte2 = *(pc+2);
					u4 word1,word2;
					Field * field = constantPool->getFieldData((indexbyte1 << 8) | indexbyte2);
					char * p = field->getDesc();
					Object * object = (Object *) currentFrame->pop();
					object->getField(field,word1,word2);
					if((*p == 'J') || (*p == 'D'))//double or long will occupy 2 entries(words)in OperandStack
					{
						//push word1 and word 2 in operand stack
					}
					else//any other type will occupy only one word (entry)in OPerandStack
					{
						//push word1 only in the operand stack
						currentFrame->push(word1);
					}
					cout<<field->getName()<<"\t"<<field->getDesc()<<endl;
					cout<<"GETFIELD: theValue="<<word1<<endl;
				}
				
				pc+=3;
				break;
			case PUTFIELD:
				{
					u1 indexbyte1 = *(pc+1);
					u1 indexbyte2 = *(pc+2);
					u4 word1,word2;
					Field * field = constantPool->getFieldData((indexbyte1 << 8) | indexbyte2);
					char * p = field->getDesc();
					if((*p == 'J') || (*p == 'D'))//double or long will occupy 2 entries(words)in OperandStack
					{
						//put in word1 and word 2
					}
					else//any other type will occupy only one word (entry)in OPerandStack
					{
						word1= currentFrame->pop();
					}
					Object * object = (Object *) currentFrame->pop();
					object->putField(field,word1,word2);
					cout<<field->getName()<<"\t"<<field->getDesc()<<endl;
					cout<<"PUTFIELD: theValue="<<word1<<endl;
				}
				
				pc+=3;
				break;
			case INVOKEVIRTUAL:
				{
					u1 indexbyte1 = *(pc+1);
					u1 indexbyte2 = *(pc+2);
					Method * actualMethod=NULL;
					Method * nonActualMethod = constantPool->getMethodData((indexbyte1 << 8) | indexbyte2);
					//get the index of the object refrence
					unsigned int index;
					index = getRefrenceIndex(nonActualMethod->getDesc());
					//cast the pointer to the object
					Object * object =(Object *) currentFrame->getAtIndexInOpStack(index);
					ClassData * CLASS = object->getClassData();
//					actualMethod = CLASS->getActualMethod(nonActualMethod);
//					actualMethod=nonActualMethod;
					actualMethod = CLASS->lookupMethod(nonActualMethod->getName(),nonActualMethod->getDesc());
					
					cout<<"INVOKEVIRTUAL: "<<actualMethod->getName()<<"\t"<<actualMethod->getDesc()<<"\t"<<actualMethod->getOwnerClassData()->getFQName()<<endl<<endl;

					Frame * newFrame = new Frame(false,actualMethod);
					if(newFrame == NULL)
					{
						cout<<"ExecutionEng: intrepret:INVOKEVIRTUAL:no sufficient memory "<<endl;
						exit(1);
					}
					putArgInLocalVariables(currentFrame,newFrame,object);
					
					currentFrame->PC=pc+3;					
					currentFrame = newFrame;
					method = currentFrame->getMethod();
					byteCode = method->getByteCode();
					constantPool = method->getConstantPool();
					code = byteCode->getCode();
					pc = code;
					//push the new frame in the stack	
					mainThread->getStack()->push(currentFrame);	
					
				}
				break;
			case INVOKESPECIAL :
				{
					u1 indexbyte1 = *(pc+1);
					u1 indexbyte2 = *(pc+2);
					Method * actualMethod=NULL;
					/*if(((indexbyte1 << 8) | indexbyte2) == 12)
					{
						currentFrame->pop();
						cout<<"INVOKESPECIAL: OBJECT"<<endl;
						pc+=3;
						break;
					}*/
					Method * nonActualMethod = constantPool->getMethodData((indexbyte1 << 8) | indexbyte2);
					ClassData * nonActualMethodClass = nonActualMethod->getOwnerClassData();
					/*if(strcmp(nonActualMethod->getName(),"<init>")==0//check if this the <init> of the object
						&& nonActualMethodClass->getSuperClassData()==NULL)
					{
						cout<<"INVOKESPECIAL: "<<nonActualMethod->getName()<<"\t"<<nonActualMethod->getDesc()<<endl<<endl;
						currentFrame->pop();
						pc+=3;
						break;
					}*/
					ClassData * currentClass = method->getOwnerClassData();
					
					/*if(currentClass->treatSuperMethodsSpecially()&&
						(currentClass->isDescendentOf(nonActualMethodClass))&&
						(!nonActualMethod->isInit()))
					{
						ClassData * superClass = currentClass->getSuperClassData();
						actualMethod = superClass->getActualMethod(nonActualMethod);
					}
					else*/
						actualMethod = nonActualMethod;

					cout<<"INVOKESPECIAL: "<<actualMethod->getName()<<"\t"<<actualMethod->getDesc()<<"\t"<<nonActualMethodClass->getFQName()<<endl<<endl;
					Frame * newFrame = new Frame(false,actualMethod);
					if(newFrame == NULL)
					{
						cout<<"ExecutionEng: interpret:INVOKESPECIAL:no sufficient memory "<<endl;
						exit(1);
					}
					unsigned int index;
					index = getRefrenceIndex(nonActualMethod->getDesc());
					//cast the pointer to the object
					Object * object =(Object *) currentFrame->getAtIndexInOpStack(index);
					cout<<object<<endl<<endl;
					putArgInLocalVariables(currentFrame,newFrame,object);
					
					currentFrame->PC=pc+3;					
					currentFrame = newFrame;
					method = currentFrame->getMethod();
					byteCode = method->getByteCode();
					constantPool = method->getConstantPool();
					code = byteCode->getCode();
					pc = code;
					//push the new frame in the stack	
					mainThread->getStack()->push(currentFrame);		
				}
				break;
			case INVOKESTATIC:
				{
					u1 indexbyte1 = *(pc+1);
					u1 indexbyte2 = *(pc+2);
					
					//Get a refrence to method from the constant pool of the current frame pointed to 
					//by the index in the instruction operand 
					Method * m = constantPool->getMethodData((indexbyte1 << 8) | indexbyte2);
					cout<<"INVOKESTATIC: "<<m->getName()<<"\t"<<m->getDesc()<<endl<<endl;
					//-------------------check if native
					JNIManager *jniMngr = JNIManager::getInstance();
					//u4* jniArgs = currentFrame->getOperandStack();
					//cout<< computFloat(jniArgs[0]);
					//cout<< computFloat(jniArgs[1]);
					if(m->getAccesFlags() & ACC_NATIVE){
						jniMngr->callNativeMethod(m,currentFrame->getOperandStack(),2);
						pc+=3;
					}
					else
					{
						ClassData * cd = m->getOwnerClassData();
						if(strcmp(cd->getFQName(),"OurAPI") == 0)//check if this the OurAPI class
						{
							if(strcmp(m->getName(),"readInt")==0)
							{
								int i;
								cout<<"enter int:";
								cin>>i;
								currentFrame->push(i);
								cout<<"The integer Value read="<<currentFrame->getTopOpStack()<<endl;
							}
							else if (strcmp(m->getName(),"readChar")==0)
							{
								char c;
								cout<<"enter char:";
								cin>>c;
								currentFrame->push(c);
								cout<<"The char is:"<<(char)currentFrame->getTopOpStack()<<endl;
							}
							else if(strcmp(m->getName(),"writeInt")==0)
							{
								int i = currentFrame->pop();
								//cout<<i<<endl;
								cout<<"the int to be printed="<<i<<endl;
							}
							else if(strcmp(m->getName(),"writeChar")==0)
							{
								char c = (char)currentFrame->pop();
								//cout<<c<<endl;
								cout<<"the char to be printed="<<c<<endl;
							}
							else if(strcmp(m->getName(),"writeString")==0)
							{
								Object * string =(Object *) currentFrame->pop();
								char * str=stringObjectToArrayOfCChars(string);
								cout<<"The string to be printed:"<<str<<endl;
							}
							else if(strcmp(m->getName(),"isDigit")==0)
							{
								char c =(char)currentFrame->pop();
								if(isdigit(c))
									currentFrame->push(1);
								else
									currentFrame->push(0);
								cout<<"the test is:"<<currentFrame->getTopOpStack()<<endl;
							}
							pc+=3;
						}
					    else{
					
						//create a new frame for the invoked method and put the resolved method in it
						//and put false to indicate that this frame is not in the top of java invocation
						Frame * newFrame = new Frame(false,m);
						if(newFrame == NULL)
						{
							cout<<"ExecutionEng: interpret:INVOKESTATIC:no sufficient memory "<<endl;
							exit(1);
						}
						//put the arg in the operand stack in the current frame
						//in the local variables of the new frame, taken care with the order ====> very important
						putArgInLocalVariables(currentFrame,newFrame,NULL);
						
						//adjust the execution of the new frame
						//stroe the pc, pc point to the instruction that follow the invoke instruction
						currentFrame->PC=pc+3;
						//make the new frame is the current frame
						currentFrame = newFrame;
						method = currentFrame->getMethod();
						byteCode = method->getByteCode();
						constantPool = method->getConstantPool();
						code = byteCode->getCode();
						pc = code;
						//push the new frame in the stack	
						mainThread->getStack()->push(currentFrame);}
					}
				}
				break;
			case NEW:
				{
					u1 indexbyte1 = *(pc+1);
					u1 indexbyte2 = *(pc+2);
					ClassData * cl = constantPool->getClassData((indexbyte1 << 8) | indexbyte2);
					Heap * heap = Heap::getInstance();				
					Object * object = heap->createObject(cl);
					cout<<"NEW :"<<"ClassName:"<<cl->getFQName()<<"\t &Object:"<<object<<endl;
					currentFrame->push((u4)object);
				}
				pc+=3;
				break;
			case NEWARRAY:
				{
					int count[1];
					//get the count :number of elements of array to create 
					count[0]= currentFrame->pop();
					u1 atype= *(pc+1);
					//form the descriptor of the array
					char desc[3];
					desc[0]='[';
					desc[1]=getType(atype);
					desc[2]='\0';
					Loader * loader= Loader::getInstance();
					//get the Class instance of the array
					ClassData * arrayCData=loader->getClassData(desc);
					//create the array object
					Object * arrayref= new Object(1,count,(int)atype,arrayCData,NULL);
					//push the arrayref in the operand stack
					currentFrame->push((u4)arrayref);
					cout<<"NEWARRAY: Array of:"<<int(atype)<<" theLengthOfTheArray="<<arrayref->getArrayLength()<<endl;
				}
				pc+=2;
				break; 
			case MULTIANEWARRAY:
				{
					u1 indexbyte1 = *(pc+1);
					u1 indexbyte2 = *(pc+2);
					u1 dimensions=  *(pc+3);
					int *count = new int[dimensions];
					for(int i=dimensions-1;i>=0;i--)
						count[i]=currentFrame->pop();
						
					ClassData * arrayCData = constantPool->getClassData((indexbyte1 << 8) | indexbyte2);
					//determine the type of the array
					char * desc = arrayCData->getFQName();
					//char * desc = "[[I";
					ClassData * elementCData=NULL;
					u1 atype=0;
					//advance the pointer to point to the type of the array
					for(desc++; *desc == '['; desc++);
					
					if(*desc == 'L')                         
					{
						char className[80];
					 	desc++; //advance the pointer to point to the first char of the class name
					 	int i=0;
               			while(*desc != ';')
               			{
               				className[i++]=*desc;
               				desc++;
               				//i++;
               			}  
               			className[i]='\0';            
               			Loader * loader= Loader::getInstance();
               			elementCData=loader->getClassData(className);
					}
           			else
           			{
           				atype=getAtype(*desc);
           			}   
           			                              
               		Object * arrayref= new Object(dimensions,count,(int)atype,arrayCData,elementCData);
						
					currentFrame->push((u4)arrayref);
					cout<<"MULTIANEWARRAY: the dimensions"<<endl;
					for(int i=0;i<dimensions;i++)
					{
						cout<<"["<<i<<"]="<<count[i]<<endl;
					}
					delete [] count;
				}
				pc+=4;
				break;
			default:      
				cout<<"Fatal Error : Unrecognised opcode"<<endl;
				cout<<"the opcode"<<(unsigned int)*pc<<" doesnot exist"<<endl;
				exit(1);
		}
	}
	
	
	
				
}

void ExecutionEng::putArgInLocalVariables(Frame * invokingMethod,Frame * invokedMethod,Object * ob)
{
	//get the method block of the invoked method 
	Method * method= invokedMethod->getMethod();
	//get the descriptor of the method
	char * p = method->getDesc();
	//this varibale to hold number of the arguments
	unsigned int argCount = 0;
	//this variable to hold number of operand stack slots reserved for this number of arguments
	//it is not the same as argCount, because double or long arg corrspond to two entries in the operand stack
	unsigned int opStackArgCount=0;
	
	//calculating number of the arg,and number of entries in the operand stack occupied by this entries.
	//calNumOfArg(p,argCount,opStackArgCount);
	this->calNumOfArg(p,argCount,opStackArgCount);         
	cout<<"argCount= "<<argCount<<"\t opStackArgCount= "<<opStackArgCount<<endl;
	//reset the pointer to the beginning of the Desc string   
	if(ob != NULL)//the refrence must be put in the location 0 in the local variables
	{
		invokedMethod->setAtIndex(0,(u4)ob);
		opStackArgCount++;
	}
	p=method->getDesc();
	p++;     /* skip start ( */
	//now pop from the current frame and put in the loacal variables of the new frame
	while(*p != ')')
	{                         
       if((*p == 'J') || (*p == 'D'))
       {         
           //Insert Long and Double values in the Local Variables                                    
           //dont forget to decrement the argCount and opStackArgCount
           invokedMethod->setAtIndex(opStackArgCount-1,invokingMethod->pop());
           opStackArgCount--;
           invokedMethod->setAtIndex(opStackArgCount-1,invokingMethod->pop());
           opStackArgCount--;
           argCount--;
           p++;                                  
       }
       else 
       {                                 
           //it will make no difference what is the type of the arg is, it will be put in the local varinable as u4 without any casting to anything
           invokedMethod->setAtIndex(opStackArgCount-1,invokingMethod->pop());
           argCount--;
           opStackArgCount--;
                                                    
           if(*p == '[') 
           {
               for(p++; *p == '['; p++);         
           }
           if(*p == 'L')                         
               while(*p++ != ';');              
           else                                 
               p++;                              
       }                                        
    }   
    if(ob != NULL)
    	  invokingMethod->pop();                                   	
}


void ExecutionEng::calNumOfArg(char * p,unsigned int & argCount,unsigned int & opStackArgCount)
{
	argCount=0;
	opStackArgCount=0;
	p++;     /* skip start ( */    
	while(*p != ')')
	{                         
		if((*p == 'J') || (*p == 'D'))//arg is long or double
		{
			argCount++;
			opStackArgCount+=2;	
			p++;
		}
		else
		{
    		if(*p == '[') //array
       		{
        		//we will not increment the following 2 variables why?
        		//because if it is array, and when we will check the type of the array,
        		//we will increment them, so we will incremnet them twice and that is wrong
        		//argCount++;
        		//opStackArgCount++;
        		for(p++; *p == '['; p++);         
        	}
        
        	if(*p == 'L')//refrence
        	{
        		argCount++;  
        		opStackArgCount++;                       
           		while(*p++ != ';');
       		}
        	else //primitive types
        	{
        		argCount++;
        		opStackArgCount++;
        		p++;                                 
        	} 
		}                                        
    }                                     
}
unsigned int ExecutionEng::getRefrenceIndex(char * p)
{
	unsigned int argCount, opStackArgCount;
	calNumOfArg(p,argCount,opStackArgCount);
	return opStackArgCount;
}
//------------------------------------------------------------------------------------------------------------------
float ExecutionEng::computFloat(u4 floatValue)
{
	u4 * ptr=&floatValue;
	int bits= *(int *)ptr;
	if(floatValue ==0x7f800000)//positive infinity
	{
		cout<<"The value is positive infinity"<<endl;
		exit(1);
		return *(float *)ptr;
	}
	if(floatValue ==0xff800000)
	{
		cout<<"The value is negative infinity"<<endl;
		exit(1);
		return *(float *)ptr;
	}
	if( (0x7f800001 <=floatValue &&  floatValue<=0x7fffffff) ||(0xff800001 <= floatValue &&floatValue<= 0xffffffff))
	{
		cout<<"The value is NaN"<<endl;
		exit(1);
		return *(float *)ptr;
	}
	
	int s = ((bits >> 31) == 0) ? 1 : -1;
    int e = ((bits >> 23) & 0xff);
    int m = (e == 0) ?	(bits & 0x7fffff) << 1 : (bits & 0x7fffff) | 0x800000;
	
	float fValue = s * m * powf(2,e-150);
	
	return fValue;
}
//----------------------------------------------------------------------------------------------------------------
double ExecutionEng::computDouble(u4 low_bytes,u4 high_bytes)
{
	long long bits = ((long long) high_bytes << 32) + low_bytes;
	if(bits == 0x7ff0000000000000LL)
	{
		cout<<"The value is positive infinity"<<endl;
		exit(1);
	}
	if((unsigned long long)bits == 0xfff0000000000000LL)
	{
		cout<<"The value is negative infinity"<<endl;
		exit(1);
	}
	if((0x7ff0000000000001LL<= (unsigned long long)bits && (unsigned long long)bits <= 0x7fffffffffffffffLL)||
	   (0xfff0000000000001LL<= (unsigned long long)bits && (unsigned long long)bits<=0xffffffffffffffffLL))
	{
		cout<<"The value is NaN"<<endl;
		exit(1);
	}
	int s = ((bits >> 63) == 0) ? 1 : -1;
   	int e = (int)((bits >> 52) & 0x7ffL);
    long long m = (e == 0) ? (bits & 0xfffffffffffffLL) << 1 :	(bits & 0xfffffffffffffLL) | 0x10000000000000LL;
    
    double fDouble = s * m * powf(2,e-1075);
    return fDouble;
}
//-----------------------------------------------------------
char ExecutionEng::getType(u1 atype)
{
	 char c;
	 switch(atype)
	 {
	 	case T_BOOLEAN:
	 		c='Z';
	 		break;
		case T_CHAR: 	
			c='C';
	 		break;
		case T_FLOAT: 	
			c='F';
	 		break;
		case T_DOUBLE: 	
			c='D';
	 		break;
		case T_BYTE:
			c='B';
	 		break;
		case T_SHORT: 	
			c='S';
	 		break;
		case T_INT:	
			c='I';
	 		break;	
		case T_LONG:
			c='J';
	 		break;
		default:
			cout<<"Fatal Error : Unrecognised type"<<endl;
			exit(1);
	 }
	 return c;
		 	
}
//-------------------------------------------------------------------------------
u1 ExecutionEng::getAtype(char c)
{
	u1 atype;
	 switch(c)
	 {
	 	case 'Z':
	 		atype=T_BOOLEAN;
	 		break;
		case 'C': 	
			atype=T_CHAR;
	 		break;
		case 'F': 	
			atype=T_FLOAT;
	 		break;
		case 'D': 	
			atype=T_DOUBLE;
	 		break;
		case 'B':
			atype=T_BYTE;
	 		break;
		case 'S': 	
			atype=T_SHORT;
	 		break;
		case 'I':	
			atype=T_INT;
	 		break;	
		case 'J':
			atype=T_LONG;
	 		break;
		default:
			cout<<"Fatal Error : Unrecognised type"<<endl;
			exit(1);
	 }
	 return atype;
}
//---------------------------------------------------------------------------
bool ExecutionEng::compare(int value1,int value2,u1 opCode)
{
	switch(opCode-IFEQ )
	{
		case 0:
			cout<<"IFEQ: ";
		case 6:	
			cout<<"IF_ICMPEQ: ";
			if(value1 == value2)
				return true;
			break;
		case 1:
			cout<<"IFNE: ";
		case 7:	
			cout<<"IF_ICMPNE: ";
			if(value1 != value2)
				return true;
			break;
		case 2:
			cout<<"IFLT: ";
		case 8:	
			cout<<"IF_ICMPLT: ";
			if(value1 < value2)
				return true;
			break;
		case 3:
			cout<<"IFGE: ";
		case 9:	
			cout<<"IF_ICMPGE: ";
			if(value1>=value2)
				return true;
			break;
		case 4:
			cout<<"IFGT: ";
		case 10:	
			cout<<"IF_ICMPGT: ";
			if(value1 > value2)
				return true;
			break;
		case 5:	
			cout<<"IFLE: ";
		case 11:
			cout<<"IIF_ICMPLE: ";
			if(value1<=value2)
				return true;	
			break;
		default:
			cout<<"Fatal Error : Unrecognised opcode"<<endl;
			exit(1);
	}
	return false;
}



