//******************************************************************//
//*           Automatically Generated File Please Do Edit          *//
//******************************************************************//

//Description   : An Implementation for Instruction iconst_0  (0x03) (003)        
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


#define e_CORE_iconst_0 	 \
e_CORE_iconst_0_START:\
 	e_PUSH_OPERAND_STACK((e_j_integer)0);\
e_CORE_iconst_0_END: