//******************************************************************//
//*           Automatically Generated File Please Do Edit          *//
//******************************************************************//

//Description   : An Implementation for Instruction aload  (0x19) (025)        
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


#define e_CORE_aload 	 \
	 e_CORE_aload_START:   \
	 	e_PUSH_OPERAND_STACK((e_j_refrence) e_ACCESS_LOCAL_AT_INDEX_AND_RETURN_AS_LEFT_VALUE(e_j_refrence,e_READ_FROM_STREAM_as_Then_Cast_as((code_sofar+1),e_j_u_byte , e_j_u_byte))) ;\
	 e_CORE_aload_END: \

