#include"interpereter.h" 
void* e_Instruction_Label_Lookup[255];






int e_exexute(const_pool_t* const_pool,method_t* method){


int d_fd = open("TraceExecution.txt" , O_RDWR);





e_Instruction_Label_Lookup [ e_VALUE_OF_ladd ] = &&l_LADD;

e_Instruction_Label_Lookup [ e_VALUE_OF_lsub ] = &&l_LSUB;



assert(sizeof( e_j_double ) == 8);

assert(sizeof( e_byte_t ) < 2 );

assert(sizeof( u1_t ) == 1 );







 unsigned int pc ;

 e_j_word* op_stk ;

 e_j_word* op_stk_top;

 e_j_word* locals ;

 e_byte_t* code ;

 e_byte_t* code_sofar ;

  locals = malloc( method->locals_length * sizeof(e_j_word));



  op_stk = malloc( method->operand_stack_length * sizeof(e_j_word));







 code = method->code;

 code_sofar=code;

 pc = 0;

 op_stk_top = (op_stk);

  goto *e_Instruction_Label_Lookup[ *( e_byte_t* ) code_sofar ];






l_LADD:

 e_CORE_iadd ;

 e_TRACE_ANNOUNCE_INSTRUCTION("LADD");

 code_sofar += e_STEP_OF_iadd ;

 goto *e_Instruction_Label_Lookup[ *( e_byte_t* ) code_sofar ];

l_LSUB:

 *( e_j_double* )op_stk_top = *( e_j_double * ) op_stk_top - *( op_stk_top + sizeof( e_j_double ) );

 code_sofar++;

 goto *e_Instruction_Label_Lookup[ *(e_byte_t*)code_sofar ];

 return 0;

 }
