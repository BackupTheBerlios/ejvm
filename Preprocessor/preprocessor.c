#include"ejvm.h"

/*Tasks
 * ====
 *   Replace bytecodes by correspoinding lables
 * 
 * Problems
 * =========
 *   0- not knowing (in prior)the count of opcodes in the the bytecode
 * 	 0-0 Counting bytecodes
 *   0-1 Accounting for widened instructions
 *   0-2 Accounting for Arbitrary Operand length instructions
 *   
 *   1 Offsset and alligment of the input the bytecode
 *   1-0 why they didit!!
 *   1-1 consitency of discarding it in theoutput or follwo it as a golden ratio
 * 
 *   2 resolving labels (2-pass is a must if u want to save space and keep it simple)
 *   2-1 in gotos switch tables
 * 	 2-2 in Exception table range
 * 
 *   3 Opcode subistitution
 *   3-0 Labels for vars crossfunction refrencing
 *   
 *   4 Operand Subistiution
 *   4-1 unresoluted constant pool items
 * 
 * Getting Indepth
 * ===============
 *  0-On The Wide issue
 *     -->Widenable instructions are  
 *             aload, iload, fload, dload, lload, astore, istore, fstore, dstore, lstore, iinc, ret
 * 	   -->The operands are widened from 1byte to 2bytes
 *     so...
 *     <-- when counting despite the scheme used wide counts as 2 instructions (or one depends on 
 *     the interpreter implementation for the widened instructions)
 *     <-- the step for met wide instruction is 3 despite     
 *     <-- wide is const operands count instruction (just emphasizing)
 * 
 *  1-On The Arbitrary instruction length
 *      -->instructions are 
 *                        tableswitch lookupswitch
 *      -->
 *  
 *
 * 
 * Resolving
 * ==========
 * Problem is about( differenet) and (arbitrary) operands count  
 *	
 *  Option a (expesive memory)
 *  ========
 * 	 -preprocessor incrementer functions
 * 	   ie vector of function ptr to count instance of bytecode and 
 *        calculate step to   the next byte code
 *   cost  -
 *
 * 
 * 	 
 *   Option b
 *   ========
 *   -preprocessor optimized
 *  
 *   Option c
 *   ========
 *   -threaded preprocessor
 * 	 
 * 
 * 
 * **/
static void* ff;
 void ffrr(void){
int j=ff;

 printf("%p ",ff);
 }
 char ejvm_Parsing_incrementer[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

 int  ejvm_count_a(char* arr_bytecode , int ln_of_bytecode){
	 const ff=&&LEBD;
	/*Pass One*/
	/*
	 * Countvalid byteodes
	 * 
	 * */
	 printf("%p" , ff);
	 int itr_bytecode=0;
	 int flg_widenacceptance;
	 for(itr_bytecode = 0 ; itr_bytecode < ln_of_bytecode ;){
	 	switch( arr_bytecode[itr_bytecode] ){
	 		
	 	case  0|1|2|3|4 : /*Do common behaviour  for 0,1,2,3*/;
	 	case  7|8|9|10  : /*Do common behaviour  for 7,8,9,10*/;
	 	
	 	default:;
	  }
	  
	 }
	 
	 LEBD:
return 0;
}
