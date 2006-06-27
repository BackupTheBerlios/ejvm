#include "thread.h"
using namespace std;

//Frame::Frame(u2 lSize,u2 oSize, bool f,Method * m):
Frame::Frame(bool f,Method * m):
        //localVariablesSize(lSize),
        //operandStackSize(oSize),
        firstFrame(f),
        method(m)
{
        localVariablesSize=m->getMaxLoacals();
        operandStackSize=m->getMaxStack();
        this->localVariables=new u4[localVariablesSize];
        if(this->localVariables==NULL)
        {
        	//cout<<"thread:Frame: localVariables"<<endl;
        	exit(1);
        }
        this->operandStack=new u4[operandStackSize];
        if(this->operandStack==NULL)
        {
        	//cout<<"thread:Frame: operandStack"<<endl;
        	exit(1);
        }
        //initialize empty stack
        top = -1;     
        PC=NULL;
}
//-------------------------------------------------------------------------
Frame::~Frame()
{
	//cout<<"Frame Destructor \n";
	delete [] this->localVariables;
	delete [] this->operandStack;
	//delete next;
}
//--------------------------------------------------------------------------
//Stack array from Horowitz,Shani,A. Fred, Fundamental of Data Structures in C, Chapter 3,sec 3.1
bool Frame::push(u4 item)
{
		if(top >= int(operandStackSize-1)	)//check if the stack is full
		{
			//cout<<"Error:OperandStack is Full"<<endl;
			return 	false;
		}
		
		this->operandStack[++this->top] = item;
		return true;
}
//-------------------------------------------------------------------------
u4 Frame::pop()
{
	if(this->top == -1)//check if the stack is empty
	{
		//cout<<"Error:OperandStack is empty"<<endl;
		return 9999999;
	}
	
	return operandStack[this->top--];
}
//-----------------------------------------------------------------------
u4 Frame::getAtIndex(u4 index)
{
	if(index<0 || index > localVariablesSize-1)
	{
		//cout<<"Error: Invalid Index"<<endl;
		return 9999999;
	}
	
	return localVariables[index];
	
}
//------------------------------------------------------------------
u4 Frame::getAtIndexInOpStack (u4 index)const
{
	if(top-index<0 || index > operandStackSize-1)
	{
		//cout<<"Error: Invalid Index"<<endl;
		return 9999999;
	}
	
	return operandStack[top-index];
}
//------------------------------------------------------------------
bool Frame::setAtIndex(u4 index,u4 value)
{
	if(index<0 || index > localVariablesSize-1)
	{
		//cout<<"Error: Invalid Index"<<endl;
		return false;
	}
	
	localVariables[index] = value;
	return true;
}
//------Node Methods---------------------
Node::Node(Frame * f):
        myFrame(f),
        next(NULL)
{
}
//-------------------------------------
Node::Node(Frame * f,Node * n):
        myFrame(f),
        next(n)
{
}
//--------------------------------------
Node::~Node()
{
		//cout<<"Node destructor"<<endl;
		delete myFrame;
        delete next;
}
//---------------------------------------
Frame * Node::GetFrame()
{
        return this->myFrame;
}
//--------------------------------------
Node * Node::GetNext()
{
        return this->next;
}
//-----------------------------------------
bool Node::SetNext(Node * n)
{
        this->next=n;
        return true;
}
//--------------------------------------------------------------
//-------Stacke Methods----------------------------------------------------------
Stack::Stack()
{
	 this->head=this->tail=NULL;
     this->count=0;
}
//----------------------------------------------------------------
Stack::~Stack()
{
	//cout<<"Stack Destrucotr\n";
	delete head;
}
//------------------------------------------------------------------------------------------
Frame *  Stack::push(Frame * f)
{
	if(this->count==0)
    	this->head = tail = new Node(f);
    else
    	head = new Node(f,head);
    
    if(head == NULL)
    {
    	//cout<<"thread: Stack::push No suffiecient memory"<<endl;
    	exit(1);
    }
    this->count++;
    return head->GetFrame();
}
//-----------------------------------------------------------------------------------------
Frame * Stack::pop()
{
        if(this->count == 0)//if the stack is empty
        {
                return  NULL;
        }
        Frame * removedFrame = head->GetFrame();
        head->ignaoreFrame();
       	Node  * ptr=head;
        if(this->head == this->tail)// The list has just one frame
                head=tail=NULL;
        else
                head=head->GetNext();

        ptr->SetNext(NULL);
	    delete ptr;
        this->count--;
        return removedFrame;
}
//--------------------------------------------------------------------------------------------
bool Stack::DeleteAll()
{
        Node * ptr=this->head;
        head=tail=NULL;
        this->count=0;
        delete ptr;
        return true;
}

//-------------------------------------------------------------------------------------
Frame * Stack::getTopFrame()
{
	return head->GetFrame();
}
//*****************************Thread Method******************************************
Thread::Thread()
{
	this->stack = new Stack();
	if(this->stack == NULL)
	{
		//cout<<"thread: Thread: no sufficient memory"<<endl;
		exit(1);
	}
}
//-------------------------------------
Thread::~Thread()
{
	delete this->stack;
}



