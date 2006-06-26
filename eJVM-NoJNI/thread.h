#ifndef THREAD_H_
#define THREAD_H_

#include <iostream>
#include "typeDefs.h"
#include "Method.h"


//typedef unsigned int u4;//how u cant accep the negative the value

class Frame
{
public:
      //  Frame(u2 localVariableSize,u2 operandStackSize,bool f,Method * method);
        Frame(bool f,Method * method);
        ~Frame();        //destructor;
        u4 getAtIndex(u4);
        bool setAtIndex(u4 index,u4 value);
        u4 pop();
        bool push(u4);
        bool isTopOfJavaInvoc(){return firstFrame;}
        Method * getMethod(){return method;}
        u4 getTopOpStack(){return operandStack[top];}
        u4 getAtIndexInOpStack(u4 index)const;
        u4* getOperandStack(){return operandStack;} //added for the jni to get the arguments of the native method....
        unsigned char* PC;
private:
        u4 * localVariables;
        u4 * operandStack;
        u2 localVariablesSize;
        u2 operandStackSize;
        bool firstFrame;// firstFrame=True then it is the first (in the top) fram in the invokation equivelant to dummy frame in Jam
        int top;
        Method * method;
       
};

/****************List Node***************************/
class Node
{
public:
        Node(Frame * f);
        Node(Frame *,Node * next);
        ~Node();        //destructor;
        Frame * GetFrame();
        void ignaoreFrame(){myFrame = NULL;}
        Node * GetNext();
        bool SetNext(Node * next);
private:
        Frame * myFrame;
        Node * next;
};

//***********************Stack Class*****************************
class Stack
{
public:
        Stack();
        ~Stack();
        int GetCount(){return this->count;}
        Frame * push(Frame * f); //AddFront
        Frame * pop();      //pop DeleteFront
        bool DeleteAll();
        Frame * getTopFrame(); // return the top of the stack with poping it 
//        Frame * getHead(void){return head;}
     
private:
       Node * head;
       Node * tail;
       int count;
};
//*******************Thread Class*************************************
class Thread
{
public:
		Thread();
		~Thread();
		Stack * getStack(){return stack;}
		
private:
		Stack * stack;
		//may take as an argument the max size of the stack
};

#endif /*THREAD_H_*/
