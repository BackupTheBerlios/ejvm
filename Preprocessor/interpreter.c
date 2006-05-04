
/*
 * 
 * 
 * 		* * * * * * * * * * * * * * * *
 *		* Interpreter Implementation  *
 * 		* * * * * * * * * * * * * * * *
 * 
 * 
 */
 



//GLobal instruction Lookup
void*   e_Instruction_Label_Lookup[255];


	


int e_exexute(const_pool_t* const_pool,method_t* method){


int d_fd = open("TraceExecution.txt" , O_RDWR);




e_Instruction_Label_Lookup [ e_VALUE_OF_ladd ] = &&l_LADD;
e_Instruction_Label_Lookup [ e_VALUE_OF_lsub ] = &&l_LSUB;

//Assertions
assert(sizeof( e_j_double ) == 8);
assert(sizeof( e_byte_t ) < 2 );
assert(sizeof( u1_t ) == 1 );
	
/*
 * Local Variables
 * ===============
 */

	unsigned int   	  pc     ;            /* 	program counter     		*/
	e_j_word*   	  op_stk ;            /* 	operand stack       		*/
	e_j_word*		  op_stk_top;         /* 	operand stack  top  		*/
	e_j_word*  	      locals ;            /* 	local variables     		*/
	e_byte_t* 		  code   ; 	  		  /* 	byte-code stream    		*/	
	e_byte_t* 		  code_sofar   ; 	  /* 	current byte-code stream    */	
	


/*
 * Allocation
 * ==========
 * 
 * 	This allocation is for the current frame
 * Dumped when 
 * 		(1)Handling exception (no exception handler found)
 * 		(2)encountering a return
 * stacked when
 * 		(1)encountering an invocation
 * 
 */
  
  
 // Allocating Local variables array
  locals = malloc( method->locals_length  * sizeof(e_j_word));
    
  //Allocating Operand Stack
  op_stk = malloc( method->operand_stack_length  * sizeof(e_j_word));
  
  
  
/* Intiailization	
 * ==============
 */
	code = method->code;
	code_sofar=code;
	pc = 0;
	op_stk_top = (op_stk);
	

/*
 * Start
 *=======
 */
 
 
  goto  *e_Instruction_Label_Lookup[ *( e_byte_t* ) code_sofar ]; 	/* execute first bytecode*/
  
 

	
	
l_LADD:
	e_CORE_iadd ;
	e_TRACE_ANNOUNCE_INSTRUCTION("LADD");
	code_sofar += e_STEP_OF_iadd ;
	goto *e_Instruction_Label_Lookup[ *( e_byte_t* ) code_sofar ];
	
	
	
/*		
inst_impl_label:
	next_addr_computation(inst)
	Debug_preexec(inst)
	Core_inst
	Denugafterexec(inst)
	Goto next
	*/
	
l_LSUB:
	*( e_j_double* )op_stk_top = *( e_j_double * ) op_stk_top - *( op_stk_top + sizeof( e_j_double ) );
	code_sofar++;
	goto *e_Instruction_Label_Lookup[ *(e_byte_t*)code_sofar ];
	



	
	
		
	
	
	
	return 0;
	}
