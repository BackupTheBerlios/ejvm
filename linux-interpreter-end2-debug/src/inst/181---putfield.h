//******************************************************************//
//*           Automatically Generated File Please Do Edit          *//
//******************************************************************//

//Description   : An Implementation for Instruction putfield  (0xb5) (181)        
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


#define e_CORE_putfield 	 \
	 e_CORE_putfield_START:   \
		{\
		auto u4 word1,word2;\
		Field * field = constant_pool->getFieldData(e_READ_FROM__JAVA_BYTE_STREAM_16((code_sofar+1) , e_j_char));\
		char * p = field->getDesc();\
		if((*p == 'J') || (*p == 'D'))\
		{\
		auto e_j_u_long ultemp = e_ACCESS_TOP_OF_OPERAND_STACK_AND_RETURN_AS_LEFT_VALUE(e_j_u_long);\
		e_RETRACT_STAK(e_j_u_long);\
		word1 = (e_j_u_integer) ((ultemp >>32)& 0xFFFFFFFF);\
		word2 = (e_j_u_integer) (ultemp &  0xFFFFFFFF);\
		}\
		else\
		{\
		word1 = e_ACCESS_TOP_OF_OPERAND_STACK_AND_RETURN_AS_LEFT_VALUE( e_j_u_integer);\
		e_RETRACT_STAK(e_j_u_integer);\
		}\
		Object * object = (Object *) e_ACCESS_TOP_OF_OPERAND_STACK_AND_RETURN_AS_LEFT_VALUE(e_j_refrence);\
		e_RETRACT_STAK(e_j_refrence);\
		object->putField(field,word1,word2);\
		}\
	 e_CORE_putfield_END: \

