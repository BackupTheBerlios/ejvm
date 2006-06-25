//******************************************************************//
//*           Automatically Generated File Please Do Edit          *//
//******************************************************************//

//Description   : An Implementation for Instruction if_icmplt  (0xa1) (161)        
//Generated by  : Eslam Al-Morshdy (eslam@gmx.de)                        
//for Bugs      :                                         				  
//Last Edited by:												      



//========
//CAUTIONS :
//========
//	 (1) - Nothig Goes Here or it will be Lost in later Modification !
//	 (2) - Namming Convention  for local variables of an instruction 
//	        implementation should have a prefix that refrence the instruction 



//=========
//VARIABLES :
//=========
//	 unsigned int   	  pc     ;    /* program counter   */	
//	 unsigned int*  	  op_stk ;    /* operand stack     */	
//	 unsigned int*  	  locals ;    /* local variables   */	
//	 e_byte_t*            code  ;    /*byte-code stream   */	


#define e_CORE_if_icmplt 	 \
	 e_CORE_if_icmplt_START:   \
	if( e_ACCESS_TOP_OF_OPERAND_STACK_AND_RETURN_AS_LEFT_VALUE(e_j_integer) < e_ACCESS_OPERAND_STACK_AT_INDEX_AND_RETURN_AS_LEFT_VALUE(e_j_integer,1)){\
		/*TRUE*/\
		e_RETRACT_STAK(e_j_long);\
		e_PROCEDE_TO(e_READ_FROM_STREAM_as_Then_Cast_as((code_sofar+1),e_j_short,e_j_integer));\
	}else{\
		/*FALSE*/\
		e_RETRACT_STAK(e_j_long);\
		e_PROCEDE_TO(e_STEP_OF_ifeq);\
	}\
	 e_CORE_if_icmplt_END: \

