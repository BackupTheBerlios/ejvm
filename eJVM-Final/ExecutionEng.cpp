#include "ExecutionEng.h"

using std::cout;
using std::endl;
//-------------------------------------------------------------------------------------------
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
void ExecutionEng::executeMethod(Object *object,Method * method,jvalue* args)
{
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
			case SIPUSH:
				{
					u1 	byte1 = *(pc+1);
					u1  byte2 = *(pc+2);
					int value = (byte1 << 8) | byte2;
					cout<<"SIPUSH: The Value="<<value<<endl;
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
					
				}
				pc+=3;
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
					//operandStack: ...=> ...,word1
					currentFrame->push(word2);
					//operandStack: ...=> ...,word1,word2
					cout<<"LLOAD: theLongValue="<<*(long long *)longValue<<endl;
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
					cout<<"FLOAD_"<<(*pc - FLOAD_0)<<": value at the top of the Stack"<<*(float *)ptr<<endl;
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
					cout<<"LSTORE: theLongValue-"<<*(long long *)longValue<<endl;
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
					cout<<"LSTORE_"<<(*pc - LSTORE_0 )<<": theLongValue-"<<*(long long *)longValue<<endl;
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
					cout<<"FSTORE_"<<(*pc - FSTORE_0 )<<": "<<"value Poped="<<*(float*)ptr<<endl;
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
			case IDIV:
				{
					u4 value2=currentFrame->pop();
					u4 value1=currentFrame->pop();
					currentFrame->push((int)value1/(int)value2);     //note temp2/temp not the reverse order temp/temp2     
					cout<<"IDIV: Value1="<<(int)value1<<" Value2="<<(int)value2<<" Result="<<(int)currentFrame->getTopOpStack()<<endl;
				}
				pc++;
				break;
			case FDIV:
				{
					u4 value2=currentFrame->pop();
					u4 * pValue2 = &value2;
					u4 value1=currentFrame->pop();
					u4 * pValue1 = &value1;
					float fresult = *(float *)pValue1 / *(float *)pValue2;
					u4 result;
					u4 * pResult = &result;
					*(float *)pResult = fresult;
					currentFrame->push(*pResult);
					cout<<"FDIV: Value1="<<*(float *)pValue1<<" Value2="<<*(float *)pValue2<<" Result="<<*(float *)pResult<<endl;
					cout<<"REsult in u4="<<*pResult<<endl;
					
				}
				pc++;
				break;
			case IF_ICMPNE:
				{
					cout<<"IF_ICMPNE: ";
					u4 value2 = currentFrame->pop();
					u4 value1 = currentFrame->pop();
					if((int)value1 != (int)value2)
					{//succeed 
						u1 branchbyte1 = *(pc+1);
						u1 branchbyte2 = *(pc+2);
						u2 offset = (branchbyte1 << 8) | branchbyte2;
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
			case IF_ICMPGE:
				{
					cout<<"IF_ICMPGE: ";
					u4 value2 = currentFrame->pop();
					u4 value1 = currentFrame->pop();
					if((int)value1 >= (int)value2)
					{
						u1 branchbyte1 = *(pc+1);
						u1 branchbyte2 = *(pc+2);
						u2 offset = (branchbyte1 << 8) | branchbyte2;
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
					u2 offset = (branchbyte1 << 8) | branchbyte2;
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
					
					cout<<"INVOKEVIRTUAL: "<<actualMethod->getName()<<"\t"<<actualMethod->getDesc()<<endl<<endl;

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
					if(((indexbyte1 << 8) | indexbyte2) == 12)
					{
						currentFrame->pop();
						cout<<"INVOKESPECIAL: OBJECT"<<endl;
						pc+=3;
						break;
					}
					Method * nonActualMethod = constantPool->getMethodData((indexbyte1 << 8) | indexbyte2);
					ClassData * nonActualMethodClass = nonActualMethod->getOwnerClassData();
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

					cout<<"INVOKESPECIAL: "<<actualMethod->getName()<<"\t"<<actualMethod->getDesc()<<endl<<endl;
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
					mainThread->getStack()->push(currentFrame);
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
			default:      
				cout<<"Fatal Error : Unrecognised opcode"<<endl;
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
        		//we will not decrement the following 2 variables why?
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









