#ifndef EJVM_H_
#define EJVM_H_

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>



typedef char ejvm_u1;
typedef unsigned int count;
 
//Coding style

//comments follo conmmrntee 

//#define house_keeping 

int ejvm_interprete_stream(const ejvm_u1 const* inst_stream,const count inst_count );
/**
 * fires the interpreter
 * return value
 *      0 succesfully executed
 * 		1 error occured
 * 
 */







#endif /*EJVM_H_*/

