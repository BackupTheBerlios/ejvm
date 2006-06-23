//******************************************************************//
//*           Automatically Generated File Please Do Edit          *//
//******************************************************************//

//Description   : An Implementation for Instruction astore_2  (0x4d) (077)        
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


#define e_CORE_astore_2 	 \
	 e_CORE_astore_2_START:   \
		 e_STORE_TO_LOCAL_AT_INDEX(e_ACCESS_TOP_OF_OPERAND_STACK_AND_RETURN_AS_LEFT_VALUE(e_j_refrence) ,2); \
		 e_RETRACT_STAK(e_j_refrence);\
	 e_CORE_astore_2_END: 

