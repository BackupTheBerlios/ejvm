/**@file 
 * @brief The starting file of the EJVM (the main() function).
 * 
 * This file contains the main function and some procedures for 
 * VM initialization and exit.
 */
#include "typeDefs.h"
#include "ClassData.h"
#include "Loader.h"
#include "Heap.h"
#include "Method.h"
#include "ByteCode.h"
#include <stdarg.h>
#include <iostream>
//#include <io.h>
//#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Loader.h"
#include "ExecutionEng.h"
#include"stringLib.h"

void testJNI(void);


/**@brief The main function.
 * 
 * return zero for success running and 1 for failure.
 */

 
 void vArg(int a, ...);
int main(int argc, char** argv){
//===================================Test JNI functions=======================================
	//testJNI();


	
	
//===================================end Test JNI functions===================================
	Loader * l= Loader::getInstance();
	Heap * h= 	Heap::getInstance();
	ExecutionEng * exec =ExecutionEng::getInstance();
	char className[80];
	ClassData * cptr=NULL;
	Method * m = NULL;
	ByteCode * b= NULL;
	
		cout<<"Enter calssName: ";
		//cin>> className;
		strcpy(className,argv[1]);
		
		cptr = l->getClassData(className);
	//	cptr->prepare();
		cout<<"Class name is: "<<cptr->getFQName()<<endl;
		
 		cout<<"Initialize the class"<<endl;
		cptr->initialize();
		
		ConstantPool * cp = cptr->constantPool;
		
		Object * string = cp->getStringObject(17);
		
		char * str=stringObjectToArrayOfCChars(string);
		
		cout<<str<<endl;
		
	/*	cout<<"Hash size: "<<h->HashSize()<<endl;
		
		m=cptr->lookupMethod("<clinit>","()V");
		
		cout<<"method name: "<<m->getName()<<endl<<"describtor :"<<m->getDesc()<<endl;
		
		exec->executeMethod(NULL,m);*/
		
//		m=cptr->lookupMethod("main","()V");
//		
//		cout<<endl<<endl<<"method name: "<<m->getName()<<endl<<"describtor :"<<m->getDesc()<<endl;
		
	/*	b=m->getByteCode();
		
		for(int i =0 ; i<b->codeLength;i++)
		{
			cout<<(int)b->code[i]<<endl;
		}*/
		
		
//		exec->executeMethod(NULL,m);
		
		
		/*-cout<<"Enter calssName: ";
		cin>> className;
		
		cptr = l->getClassData(className);
		
		cout<<"Class name is: "<<cptr->getFQName()<<endl;
		
		cout<<"Hash size: "<<h->HashSize()<<endl;*/

	/*	u4 word1,word2;
	int index [1];
	byte * sam=(byte *)"samehIsmail";
	Object * Array = utf8ToArrayOfUnicodeChar (sam);
	for(int i=0; i<=10;i++)
	{
		index[0] = i;
		Array->getElement(index,word1,word2);
		printf("%c\n",(char) word1);
	}*/
			
		
		Loader::deleteLoader();
		Heap::deleteHeap();
		ExecutionEng::deleteExec();
/*	int * j=NULL;
	cout<<u4(j)<<"\t"<<j<<endl;
	int i=-1000000;
	vArg(12,123.777,-1,'a',false,&i);*/

}



void vArg(int a,...){
	va_list args;
	u4 i=100;
	u4 j;
	u4 * vPtr = &i;
	va_start(args,a);

	//write
	*(float*)vPtr = va_arg(args,double);
	//read
	printf("%f \n",*(float*)vPtr);
	j=*vPtr;
	
	
	vPtr=&j;
	cout<<*(float*)vPtr<<endl;
	
	vPtr=&i;
	
	*vPtr = va_arg(args,int);
	cout<<*(int*)vPtr<<endl;
	
	*vPtr = va_arg(args,u4);
	cout<<*(char*)vPtr<<endl;
	
	*vPtr = va_arg(args,u4);
	cout<<*(bool *)vPtr<<endl;
	
	*vPtr = va_arg(args,u4);
	cout<<*(int *)(*vPtr)<<endl;
	j=*vPtr;
	
	vPtr=&j;
	cout<<*(int *)(*vPtr)<<endl;
	
	va_end(args);
}


