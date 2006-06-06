/**@file 
 * @brief The starting file of the EJVM (the main() function).
 * 
 * This file contains the main function and some procedures for 
 * VM initialization and exit.
 */
#include"typeDefs.h"
#include"ClassData.h"
#include"Loader.h"
#include"Heap.h"
#include"assert.h"

#include <iostream>
//#include <io.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
/**@brief The main function.
 * 
 * return zero for success running and 1 for failure.
 */
int main(){


	struct stat len;
	std::cout << "This is our prototype---Rabena yesahhelha...AAAAmeeeeen\n";
	FILE *stream;
	void * classFile;
	stream = fopen(".\\Simple.class", "rb");
	assert(stream!=NULL);
	stat(".\\Simple.class",&len);
	int size = len.st_size;
	classFile = new byte[size];
	fread(classFile,1,(size_t)size,stream);
	fclose(stream);
	ClassData demo =  ClassData((byte *)classFile);
	printf("Hosny KLOTTTT");
	return 0;	
}

