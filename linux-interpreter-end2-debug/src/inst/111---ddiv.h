//******************************************************************//
//*           Automatically Generated File Please Do Edit          *//
//******************************************************************//

//Description   : An Implementation for Instruction ddiv  (0x6f) (111)        
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


#define e_CORE_ddiv 	 \
	 e_CORE_ddiv_START:   \
          	e_ACCESS_OPERAND_STACK_AT_INDEX_AND_RETURN_AS_LEFT_VALUE(e_j_double,2) =   e_ACCESS_OPERAND_STACK_AT_INDEX_AND_RETURN_AS_LEFT_VALUE(e_j_double,2)/e_ACCESS_TOP_OF_OPERAND_STACK_AND_RETURN_AS_LEFT_VALUE(e_j_double);\
        	e_RETRACT_STAK(e_j_double);\
	 e_CORE_ddiv_END: \

