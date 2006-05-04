#ifndef interpreter_H_
	#define interpreter_H_
		
	#include"ejvm.h"
	#include"./src/const.h"
	#include"./src/inst.h"
	#include"./src/step.h"
	#include<fcntl.h>
	/* Macros
	 * ====== 
	 */
	 
	/*didn't work
	 #define e_DEBUG_PRE_EXEC   
	  
	 #define e_DEBUG_PRE_EXEC(inst)      \
	 	#ifndef e_DEBUG_PRE_EXEC#inst    \
	 	 	e_DEBUG_PRE_EXEC_normal      \ 
	 	#else						     \
	 		e_DEBUG_PRE_EXEC#inst		 \
	 	#endif 	\					 
	 		
	*/
	
	//#define e_TRACE_EXEC_ENG
	
	#ifndef e_TRACE_EXEC_ENG
		#define e_TRACE_CREATE_TRACE_FILE ;
	#else 
	 	#define e_TRACE_CREATE_TRACE_FILE\
	 		d_fd = open("TraceExecution.txt" , O_RDWR);\
	 		char* data =mmap(NULL ,1024*4,PROT_WRITE, MAP_SHARED, d_fd, 0);\
	 		
	#endif //e_TRACE_EXEC_ENG
	
	
	#ifndef e_TRACE_EXEC_ENG
		#define  e_TRACE_ANNOUNCE_INSTRUCTION( inst ) ;
	#else
		#define  e_TRACE_ANNOUNCE_INSTRUCTION( inst ) \
				data += sprintf(data , "\t Instruction:"##inst"is Execuyted") ;
	
	#endif //e_TRACE_EXEC_ENG
	
	#ifndef e_TRACE_EXEC_ENG
		#define  e_TRACE_ADD_TRACE_ENTRY(entry);		
	#else
		#define  e_TRACE_ADD_TRACE_ENTRY( entry ) \
				data += sprintf(data,entry##"\n") ;
	#endif //e_TRACE_EXEC_ENG
	
	#ifndef e_TRACE_EXEC_ENG
		#define  e_TRACE_CLOSE( ) ;		
	#else
		#define  e_TRACE_CLOSE( ) \
				data += sprintf(data , "\t Instruction:"##inst"is Execuyted") ;
	#endif //e_TRACE_EXEC_ENG
	
	
		
	
	
	/*
	 * Type Definintions
	 * =================
	 * 
	 */
	 
	typedef unsigned char e_byte_t,u1_t;			/*Java byte   */
	typedef double  	  e_j_double; 				/*Java double */
	typedef long    	  e_j_long; 				/*Java long */
	typedef float   	  e_j_float;				/*Java float  */
	typedef int     	  e_j_integer;				/*Java integer*/
	typedef int     	  e_j_word;				    /*Java word   */
	typedef short         e_j_short;
			
	typedef struct const_pool_t{}const_pool_t;	/**/
	
	typedef struct method_t{
		unsigned int 	operand_stack_length    ;		/* operand stack length   */
		unsigned int	locals_length  ;				/* local-variables length */
		unsigned int	byteCodeLength ;				/* byteCodeStream length  */
		e_byte_t* 		code ;							/* byteCodeStream		  */	
	    
	}method_t;
	 
	typedef struct e_frame_t{
		unsigned int   	  pc     ;            /* 	program counter     		*/
		e_j_word*   	  op_stk ;            /* 	operand stack       		*/
		e_j_word*		  op_stk_top;         /* 	operand stack  top  		*/
		e_j_word*  	      locals ;            /* 	local variables     		*/
		e_byte_t* 		  code   ; 	  		  /* 	byte-code stream    		*/	
		e_byte_t* 		  code_sofar   ; 	  /* 	current byte-code stream    */	
		}e_frame_t; 
		
		
	typedef struct e_gnrc_stk_node_t e_gnrc_stk_node_t;
	struct e_gnrc_stk_node_t{
	 	e_gnrc_stk_node_t *	    nxt  ;   /*  next node 			   */ 
	 	const void* 			core ;   /*  element being stacke d*/
	}; 
	
		
		
	/*
	 * Routines declaration
	 * ====================
	 * 
	 */
	
		
	int stk_pop(const void** const stk_ptr_ptr,void* stk_top);
	
	
	int stk_push(const void** const stk_ptr_ptr,void* stk_top);
	
	
		
		
	
	int e_exexute(const_pool_t* const_pool,method_t* method);
	
#endif //interpreter_H_
	
	
	
	
