#include "Loader.h"
#include "Heap.h"
#include <stdio.h>
#include <sys/stat.h>
//#include <unistd.h>



Loader * Loader::loaderInstance = NULL;
//--------------------------------------------------------------
Loader * Loader::getInstance()
 {
 	if(loaderInstance == NULL)
 		loaderInstance = new Loader;
 	
 	return loaderInstance;
 }
 //-----------------------------------------------------
 void Loader::deleteLoader()
 {
 	delete loaderInstance;
 	loaderInstance =NULL;
 }
//---------------------------------------------------------
Loader::Loader()
{
}

//----------------------------------------------------------
byte * Loader::makeArrayInCPP(char * fileName)
{
	
	struct stat len;
	FILE *stream;
	void * classFile;
	if((stream = fopen(fileName, "rb")) == NULL)
	{
		//cout<<"File Not Found"<<endl;
		exit(1);
	}
	stat(fileName,&len);
	int size = len.st_size;
	classFile = new byte[size];
	size_t bytesRead =fread(classFile,1,(size_t)size,stream);
	//cout<<bytesRead<<" bytes read\n";
	fclose(stream);
	
	/*char ch;
	unsigned long length = 0;
	ifstream fin(fileName, ios::in | ios::binary);
	
	if(!fin)
	{
		//cout<<"Cannot open the file";
		return NULL;
	}
	
	//Calaculate the file length
	while(fin.get(ch))
		length++;
		
	fin.close();
	
	//now read the file 
	fin.open(fileName, ios::in | ios::binary);
	byte * pData=new byte[length];
	
	fin.read((char *)pData,length);
	//see how many bytes have beed read
	//cout<<fin.gcount()<<" bytes read\n";
	
	fin.close();
	
/*	char file2[80]="/Khaled/eclipseWork/hello/OPS2.class";
	ofstream fout(file2, ios::out | ios::binary);
	
	fout.write((char *)pData,length);
	//see how many bytes have beed written
	//cout<<fin.gcount()<<" bytes written\n";
	fout.close();*/
	
	//return pData ;
	return (byte *)classFile;
	
	 
	
}
//---------------------------------------------------------------------------------------------
ClassData * Loader::getClassData(const char * className)
{
	///////////////////////////class name must be without .class
	/**
	 * psudoCode:
	 * if(!(classData=lookupdClassData(className)))
	 * 		u1[] classFile = classFiel2bytes(className);
	 * 		classData = Heap->createClassData(classFile);
	 * return classData;
	 */
	// char path[80]="/Khaled/eclipseWork/testPrototype1/";
	 char path[80]="";
	 Heap * heap= Heap::getInstance();
	 ClassData * cdata =NULL;
	 byte * classFile = NULL;
	 
	 cdata = heap->lookupClassData(className);
	 
	 
	 
	 if(cdata == NULL)//Class not loaded
	 {
	 	if(*className == '[')
	 	{
	 		cdata = heap->createArrayClassData(className);
	 	}
	 	else
	 	{
	 	
	 		//prepare the path of the class file
	 		strcat(path,className);
	 		strcat(path,".class");
	 		//put the class file in array of bytes
			classFile=this->makeArrayInCPP(path);//*********************************************************************************DONT forget to uncomment
	 		//create classdata on the heap
	 		cdata = heap->createClassData(className,classFile); //*************************************************dont forget to modify it to take array of bytes or u1
	 		//after checking that there are no errors during parsing, insert in the hash
	 	}
	 	heap->addToHash(cdata);
	 }
	
	 delete [] classFile;
	 
	 return cdata;
}
