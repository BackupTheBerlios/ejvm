#ifndef interpreter_H_
	#define interpreter_H_

#include"ByteCode.h"
#include"ConstantPool.h"

/*
 * Type Definintions
 * =================
 * 
 */
	#define e_j_NULL 	    NULL
	typedef unsigned char          e_byte_t,u1_t,e_j_u_byte;		/*Java byte   */
	typedef unsigned int           e_j_u_integer;
	typedef unsigned short         e_j_char;
	typedef unsigned long long     e_j_u_long;
	
	typedef char              e_j_byte; 
	typedef short             e_j_short;
	typedef int     	  e_j_integer;  		/*Java integer */
	typedef int     	  e_j_word;			/*Java word    */
	typedef float   	  e_j_float;			/*Java float   */
	
	typedef double  	  e_j_double; 			/*Java double  */
	typedef long long    	  e_j_long; 			/*Java long    */

	

	typedef int               e_j_refrence;
	typedef int64_t           e_j_long_long;
	
	#ifndef WIDE
		typedef char              e_j_wide_byte; 
		typedef short             e_j_wide_short;
		typedef int     	  e_j_wide_integer;
	#else
		typedef short             e_j_wide_byte;
		typedef int               e_j_wide_short;
		typedef long     	  e_j_wide integer;
	#endif
	
	
	
	
	typedef struct ConstantPool{int i;};
	typedef struct ConstantPool ConstantPool;

 struct e_frame_t{
ConstantPool* constant_pool;
e_j_u_byte*		code;
e_j_u_byte*    code_sofar;
ByteCode*     method ;
e_j_word*     locals ;
e_j_word*      op_stk ;
e_j_word* op_stk_top ;
};
typedef  struct e_frame_t e_frame_t;








/*
 * Routines declaration
 * ====================
 * 
 */


//int e_exexute(const_pool_t* const_pool,method_t* method);
//int e_exexute(const_pool_t* const_pool,ByteCode* method);
class ExecutionEng{ 
public: static int e_exexute(ConstantPool* const_pool,ByteCode* method);

};




	
#endif //interpreter_H_
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
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
	
	/*
	 
		#define  e_STRINGIFY(x) #x 
		#define  e_CAT(x,y) x##y
		#define  e_XCAT(x,y) e_CAT( x , y)
	
	#define e_TRACE_EXEC_ENG
	
	#ifndef e_TRACE_EXEC_ENG
		#define e_TRACE_CREATE_TRACE_FILE ;
	#else 
	 	#define e_TRACE_CREATE_TRACE_FILE(distinct)\
	 		int d_fd = open("Trace.txt",  O_WRONLY | O_CREAT | O_TRUNC);\
	 		assert(d_fd!=-1);\
	 		char* data = mmap(NULL ,1024*4,PROT_WRITE, MAP_SHARED, d_fd, 0);\
	 		char* data2=data;\
	 		
	 		
	#endif //e_TRACE_EXEC_ENG
	
	
	#ifndef e_TRACE_EXEC_ENG
		#define  e_TRACE_ANNOUNCE_INSTRUCTION( inst ) ;
	#else
		#define  e_TRACE_ANNOUNCE_INSTRUCTION( inst ) \
				data += sprintf(data ,"\t Instruction:"e_STRINGIFY(inst)"is Execuyted\n") ;
	
	#endif //e_TRACE_EXEC_ENG
	
	#ifndef e_TRACE_EXEC_ENG
		#define  e_TRACE_ADD_TRACE_ENTRY(entry);		
	#else
		#define  e_TRACE_ADD_TRACE_ENTRY( entry ) \
				data += sprintf(data,e_STRINGIFY(entry)"\n") ;
	#endif //e_TRACE_EXEC_ENG
	
	#ifndef e_TRACE_EXEC_ENG
		#define  e_TRACE_CLOSE( ) ;		
	#else
		#define  e_TRACE_CLOSE( ) \
				msync(data2,1024*4,MS_SYNC) ;\
				munmap(data2,1024*4);\
				close(d_fd);
	#endif //e_TRACE_EXEC_ENG
	  */
	  
	
