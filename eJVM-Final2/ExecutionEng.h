#ifndef EXECUTIONENG_H_
#define EXECUTIONENG_H_
#include "Object.h"
#include "Method.h"
#include "typeDefs.h"
#include "thread.h"
#include "ByteCode.h"
#include <stdarg.h>
#include "inst.h"
#include "ConstantPool.h"
#include "Heap.h"
#include "jni.h"
#include "Loader.h"
#include <cmath>
class ExecutionEng
{
public:

	static ExecutionEng * geInstance(){
		//this method should be implemented , for now it will return NULL
		return NULL;
	}
	 
	/**
	* The constructor 
	*    -creates the main thread data structure
	*    -May take as an argument the max size of Thread stack...		
	*/
	ExecutionEng();
	/**
	* @brief This method takes a method and executes it either in java or calling native implementation of the functoin	   * 
	* PseudoCode:
	*	1- get the current stack (with single thread, we only have the stack of mainThread).
		2- push dummy frame in the stack to mark the beginning of execution
		3- from the given method, get max_locals and max_operandStack
		4- push new frame 
		5- get the signature of the given method (function name and its arguments)
		6- use the signature and the given va_list to put the arguments into local variables
		7- get ByteCode
		8- call interpret with the ByteCode and currentThread (now it is the mainThread).	
	*/
	void executeMethod(Object *object,Method * method,...);
	/*This version of executeMethod takes Valist as an argumetn instead of the ...
	*/
	void executeMethod(Object *object,Method * method,va_list args);
	
	void executeMethod(Object *object,Method * method,jvalue* args);

	/**
	* @brief This method takes a thread which is active now and ready to execute (i.e have a new frame pushed in its 
		stack.
	* PseudoCode:
		1- get top frame from the given thread.
		2- let PC be a pointer to the first byte in the byte code.
		3- while(true)
			switch(*PC){
				case 0:
				case 1:
				.
				.
				.
				case Invoke:
					save PC in the current frame;
					get the method
					push new frame
					update the state variables (PC, currentFrame, ...) to point to the new method
				.
				.
				.
				case return:
					pop frame;
					check if the next frame is the dummy frame (used to mark end of execution)
					if so , pop this dummy frame and return //this case is the only case in which this 						function returns.
				.
				.
				.
				default: error ("unsupported OPCODE");
			}
	*/
	void interpret(Thread * thread);
	static float computFloat(u4 floatValue);
	static double computDouble(u4 word1,u4 word2);
	
	
	~ExecutionEng();

private:
	Thread * mainThread;
	void putArgInLocalVariables(Frame * invokingMethod, Frame * invokedMethod,Object * ob);
	void calNumOfArg(char * p,unsigned int & argCount,unsigned int & opStackArgCount);
	unsigned int getRefrenceIndex(char * p);
	char getType(u1 atype);
};

#endif /*EXECUTIONENG_H_*/
