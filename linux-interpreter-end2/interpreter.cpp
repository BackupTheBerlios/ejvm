#include"ByteCode.h"
#include"ExecutionEng.h" 
#include"./src/inst.h"
#include"stk_operations.h"


/*
 * 
 * 
 * 		* * * * * * * * * * * * * * * *
 *		* Interpreter Implementation  *
 * 		* * * * * * * * * * * * * * * *
 * 
 * 
 */
 
 
  #define e_ACCESS_TOP_OF_OPERAND_STACK_AND_RETURN_AS_LEFT_VALUE(type) (*((typeof(type)*) op_stk_top ))
  #define e_ACCESS_OPERAND_STACK_AT_INDEX_AND_RETURN_AS_LEFT_VALUE(type ,index) (* ((type *) (  op_stk_top - index ) ))
      
  //#define e_ACCESS_SUB_TOP_OF_OPERAND_STK_AND_RETURN_AS_LV(T1,T2)  ( * ((T2*)( ( ( typeof(T1)* ) op_stk_top) - 1 )) )
  //T1 type on whic to perform the decrement ptr arith 
  //T2 type at which  dereference is done
  
  //#define e_ACCESS_SUB_SUB_TOP_OF_OPERAND_STK_AND_RETURN_AS_LV(T1,T2)  ( * ((T2*)( ( ( typeof(T1)* ) op_stk_top) - 2 )) )
  
  #define e_ACCESS_LOCAL_AT_INDEX_AND_RETURN_AS_LEFT_VALUE(value,indx) ((*( ( typeof(value)* )  ( locals + indx ) )))
  

  #define e_RETRACT_STAK(type)  {op_stk_top -= ( sizeof( typeof(type) )/ sizeof( typeof(op_stk_top) ) );}
  
  #define e_PROMOTE_STAK(type)  {op_stk_top += ( sizeof( typeof(type) )/ sizeof( typeof(op_stk_top) ) );}
  

  #define e_PUSH_OPERAND_STACK(value) {  e_PROMOTE_STAK( value) ; e_ACCESS_TOP_OF_OPERAND_STACK_AND_RETURN_AS_LEFT_VALUE(value) = value ;}  
  #define e_STORE_TO_LOCAL_AT_INDEX(value,indx) e_ACCESS_LOCAL_AT_INDEX_AND_RETURN_AS_LEFT_VALUE(value ,indx) = value
 
  #define e_READ_FROM_STREAM_as_Then_Cast_as(stream,T1 ,T2) ( (T2) (*( (T1*) stream ) ) ) 
  
  #define e_READ_FROM__JAVA_BYTE_STREAM_16(start,type)\
  	((e_READ_FROM_STREAM_as_Then_Cast_as(start , e_j_u_byte , type)<<8)|\
  	e_READ_FROM_STREAM_as_Then_Cast_as((start+1) , e_j_u_byte , type))

   #define e_READ_FROM__JAVA_BYTE_STREAM_32(start,type)\
  	((e_READ_FROM_STREAM_as_Then_Cast_as(start , e_j_u_byte , type)<<24)|\
  	(e_READ_FROM_STREAM_as_Then_Cast_as((start +1) , e_j_u_byte , type)<<16)|\
  	(e_READ_FROM_STREAM_as_Then_Cast_as((start +2), e_j_u_byte , type)<<16)|\
  	(e_READ_FROM_STREAM_as_Then_Cast_as((start +3), e_j_u_byte , type)))
  

  #define e_FREE_CURRENT_FRAME \
  		free(locals);\
  		free((op_stk-1));
  		
  		
  #define e_SET_CURRENT_FRAME(temp)\
  	  code = temp->code;\
	  code_sofar = temp->code_sofar;\
	  method = temp->method;\
	  locals =  temp->locals;\
	  op_stk = temp->op_stk;\
	  op_stk_top = temp->op_stk_top;\
	  constant_pool = temp->constant_pool;

 #define e_SAVE_CURRENT_FRAME(temp)\
 	  temp->code = code;\
	  temp->code_sofar = code_sofar;\
	  temp->method = method;\
	  temp->locals = locals;\
	  temp->op_stk = op_stk;\
	  temp->op_stk_top = op_stk_top;\
	  temp->constant_pool = constant_pool;
	  
  	
  #define e_PROCEDE_TO(offset)\
	 code_sofar += offset  ;\
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];
	

  		


/*
 * GLobal instruction Lookup
 */
 
 void*   e_Instruction_Label_Lookup[255];


/*
 * e_exexute Body
 */

 int ExecutionEng::e_exexute(ConstantPool* const_pool,ByteCode* method){


//Starting Logging
e_TRACE_CREATE_TRACE_FILE("dd")

/*
 *Filling the Global Lookup table 
 */

e_Instruction_Label_Lookup[ e_VALUE_OF_nop             ] = &&e_label_nop;
e_Instruction_Label_Lookup[ e_VALUE_OF_aconst_null     ] = &&e_label_aconst_null;
e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_m1       ] = &&e_label_iconst_m1;
e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_0        ] = &&e_label_iconst_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_1        ] = &&e_label_iconst_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_2        ] = &&e_label_iconst_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_3        ] = &&e_label_iconst_3;
e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_4        ] = &&e_label_iconst_4;
e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_5        ] = &&e_label_iconst_5;
e_Instruction_Label_Lookup[ e_VALUE_OF_lconst_0        ] = &&e_label_lconst_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_lconst_1        ] = &&e_label_lconst_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_fconst_0        ] = &&e_label_fconst_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_fconst_1        ] = &&e_label_fconst_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_fconst_2        ] = &&e_label_fconst_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_dconst_0        ] = &&e_label_dconst_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_dconst_1        ] = &&e_label_dconst_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_bipush          ] = &&e_label_bipush;
e_Instruction_Label_Lookup[ e_VALUE_OF_sipush          ] = &&e_label_sipush;
e_Instruction_Label_Lookup[ e_VALUE_OF_ldc             ] = &&e_label_ldc;
e_Instruction_Label_Lookup[ e_VALUE_OF_ldc_w           ] = &&e_label_ldc_w;
e_Instruction_Label_Lookup[ e_VALUE_OF_ldc2_w          ] = &&e_label_ldc2_w;
e_Instruction_Label_Lookup[ e_VALUE_OF_iload           ] = &&e_label_iload;
e_Instruction_Label_Lookup[ e_VALUE_OF_lload           ] = &&e_label_lload;
e_Instruction_Label_Lookup[ e_VALUE_OF_fload           ] = &&e_label_fload;
e_Instruction_Label_Lookup[ e_VALUE_OF_dload           ] = &&e_label_dload;
e_Instruction_Label_Lookup[ e_VALUE_OF_aload           ] = &&e_label_aload;
e_Instruction_Label_Lookup[ e_VALUE_OF_iload_0         ] = &&e_label_iload_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_iload_1         ] = &&e_label_iload_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_iload_2         ] = &&e_label_iload_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_iload_3         ] = &&e_label_iload_3;
e_Instruction_Label_Lookup[ e_VALUE_OF_lload_0         ] = &&e_label_lload_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_lload_1         ] = &&e_label_lload_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_lload_2         ] = &&e_label_lload_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_lload_3         ] = &&e_label_lload_3;
e_Instruction_Label_Lookup[ e_VALUE_OF_fload_0         ] = &&e_label_fload_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_fload_1         ] = &&e_label_fload_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_fload_2         ] = &&e_label_fload_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_fload_3         ] = &&e_label_fload_3;
e_Instruction_Label_Lookup[ e_VALUE_OF_dload_0         ] = &&e_label_dload_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_dload_1         ] = &&e_label_dload_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_dload_2         ] = &&e_label_dload_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_dload_3         ] = &&e_label_dload_3;
e_Instruction_Label_Lookup[ e_VALUE_OF_aload_0         ] = &&e_label_aload_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_aload_1         ] = &&e_label_aload_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_aload_2         ] = &&e_label_aload_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_aload_3         ] = &&e_label_aload_3;
e_Instruction_Label_Lookup[ e_VALUE_OF_iaload          ] = &&e_label_iaload;
e_Instruction_Label_Lookup[ e_VALUE_OF_laload          ] = &&e_label_laload;
e_Instruction_Label_Lookup[ e_VALUE_OF_faload          ] = &&e_label_faload;
e_Instruction_Label_Lookup[ e_VALUE_OF_daload          ] = &&e_label_daload;
e_Instruction_Label_Lookup[ e_VALUE_OF_aaload          ] = &&e_label_aaload;
e_Instruction_Label_Lookup[ e_VALUE_OF_baload          ] = &&e_label_baload;
e_Instruction_Label_Lookup[ e_VALUE_OF_caload          ] = &&e_label_caload;
e_Instruction_Label_Lookup[ e_VALUE_OF_saload          ] = &&e_label_saload;
e_Instruction_Label_Lookup[ e_VALUE_OF_istore          ] = &&e_label_istore;
e_Instruction_Label_Lookup[ e_VALUE_OF_lstore          ] = &&e_label_lstore;
e_Instruction_Label_Lookup[ e_VALUE_OF_fstore          ] = &&e_label_fstore;
e_Instruction_Label_Lookup[ e_VALUE_OF_dstore          ] = &&e_label_dstore;
e_Instruction_Label_Lookup[ e_VALUE_OF_astore          ] = &&e_label_astore;
e_Instruction_Label_Lookup[ e_VALUE_OF_istore_0        ] = &&e_label_istore_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_istore_1        ] = &&e_label_istore_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_istore_2        ] = &&e_label_istore_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_istore_3        ] = &&e_label_istore_3;
e_Instruction_Label_Lookup[ e_VALUE_OF_lstore_0        ] = &&e_label_lstore_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_lstore_1        ] = &&e_label_lstore_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_lstore_2        ] = &&e_label_lstore_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_lstore_3        ] = &&e_label_lstore_3;
e_Instruction_Label_Lookup[ e_VALUE_OF_fstore_0        ] = &&e_label_fstore_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_fstore_1        ] = &&e_label_fstore_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_fstore_2        ] = &&e_label_fstore_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_fstore_3        ] = &&e_label_fstore_3;
e_Instruction_Label_Lookup[ e_VALUE_OF_dstore_0        ] = &&e_label_dstore_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_dstore_1        ] = &&e_label_dstore_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_dstore_2        ] = &&e_label_dstore_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_dstore_3        ] = &&e_label_dstore_3;
e_Instruction_Label_Lookup[ e_VALUE_OF_astore_0        ] = &&e_label_astore_0;
e_Instruction_Label_Lookup[ e_VALUE_OF_astore_1        ] = &&e_label_astore_1;
e_Instruction_Label_Lookup[ e_VALUE_OF_astore_2        ] = &&e_label_astore_2;
e_Instruction_Label_Lookup[ e_VALUE_OF_astore_3        ] = &&e_label_astore_3;
e_Instruction_Label_Lookup[ e_VALUE_OF_iastore         ] = &&e_label_iastore;
e_Instruction_Label_Lookup[ e_VALUE_OF_lastore         ] = &&e_label_lastore;
e_Instruction_Label_Lookup[ e_VALUE_OF_fastore         ] = &&e_label_fastore;
e_Instruction_Label_Lookup[ e_VALUE_OF_dastore         ] = &&e_label_dastore;
e_Instruction_Label_Lookup[ e_VALUE_OF_aastore         ] = &&e_label_aastore;
e_Instruction_Label_Lookup[ e_VALUE_OF_bastore         ] = &&e_label_bastore;
e_Instruction_Label_Lookup[ e_VALUE_OF_castore         ] = &&e_label_castore;
e_Instruction_Label_Lookup[ e_VALUE_OF_sastore         ] = &&e_label_sastore;
e_Instruction_Label_Lookup[ e_VALUE_OF_pop             ] = &&e_label_pop;
e_Instruction_Label_Lookup[ e_VALUE_OF_pop2            ] = &&e_label_pop2;
e_Instruction_Label_Lookup[ e_VALUE_OF_dup             ] = &&e_label_dup;
e_Instruction_Label_Lookup[ e_VALUE_OF_dup_x1          ] = &&e_label_dup_x1;
e_Instruction_Label_Lookup[ e_VALUE_OF_dup_x2          ] = &&e_label_dup_x2;
e_Instruction_Label_Lookup[ e_VALUE_OF_dup2            ] = &&e_label_dup2;
e_Instruction_Label_Lookup[ e_VALUE_OF_dup2_x1         ] = &&e_label_dup2_x1;
e_Instruction_Label_Lookup[ e_VALUE_OF_dup2_x2         ] = &&e_label_dup2_x2;
e_Instruction_Label_Lookup[ e_VALUE_OF_swap            ] = &&e_label_swap;
e_Instruction_Label_Lookup[ e_VALUE_OF_iadd            ] = &&e_label_iadd;
e_Instruction_Label_Lookup[ e_VALUE_OF_ladd            ] = &&e_label_ladd;
e_Instruction_Label_Lookup[ e_VALUE_OF_fadd            ] = &&e_label_fadd;
e_Instruction_Label_Lookup[ e_VALUE_OF_dadd            ] = &&e_label_dadd;
e_Instruction_Label_Lookup[ e_VALUE_OF_isub            ] = &&e_label_isub;
e_Instruction_Label_Lookup[ e_VALUE_OF_lsub            ] = &&e_label_lsub;
e_Instruction_Label_Lookup[ e_VALUE_OF_fsub            ] = &&e_label_fsub;
e_Instruction_Label_Lookup[ e_VALUE_OF_dsub            ] = &&e_label_dsub;
e_Instruction_Label_Lookup[ e_VALUE_OF_imul            ] = &&e_label_imul;
e_Instruction_Label_Lookup[ e_VALUE_OF_lmul            ] = &&e_label_lmul;
e_Instruction_Label_Lookup[ e_VALUE_OF_fmul            ] = &&e_label_fmul;
e_Instruction_Label_Lookup[ e_VALUE_OF_dmul            ] = &&e_label_dmul;
e_Instruction_Label_Lookup[ e_VALUE_OF_idiv            ] = &&e_label_idiv;
e_Instruction_Label_Lookup[ e_VALUE_OF_ldiv            ] = &&e_label_ldiv;
e_Instruction_Label_Lookup[ e_VALUE_OF_fdiv            ] = &&e_label_fdiv;
e_Instruction_Label_Lookup[ e_VALUE_OF_ddiv            ] = &&e_label_ddiv;
e_Instruction_Label_Lookup[ e_VALUE_OF_irem            ] = &&e_label_irem;
e_Instruction_Label_Lookup[ e_VALUE_OF_lrem            ] = &&e_label_lrem;
e_Instruction_Label_Lookup[ e_VALUE_OF_frem            ] = &&e_label_frem;
e_Instruction_Label_Lookup[ e_VALUE_OF_drem            ] = &&e_label_drem;
e_Instruction_Label_Lookup[ e_VALUE_OF_ineg            ] = &&e_label_ineg;
e_Instruction_Label_Lookup[ e_VALUE_OF_lneg            ] = &&e_label_lneg;
e_Instruction_Label_Lookup[ e_VALUE_OF_fneg            ] = &&e_label_fneg;
e_Instruction_Label_Lookup[ e_VALUE_OF_dneg            ] = &&e_label_dneg;
e_Instruction_Label_Lookup[ e_VALUE_OF_ishl            ] = &&e_label_ishl;
e_Instruction_Label_Lookup[ e_VALUE_OF_lshl            ] = &&e_label_lshl;
e_Instruction_Label_Lookup[ e_VALUE_OF_ishr            ] = &&e_label_ishr;
e_Instruction_Label_Lookup[ e_VALUE_OF_lshr            ] = &&e_label_lshr;
e_Instruction_Label_Lookup[ e_VALUE_OF_iushr           ] = &&e_label_iushr;
e_Instruction_Label_Lookup[ e_VALUE_OF_lushr           ] = &&e_label_lushr;
e_Instruction_Label_Lookup[ e_VALUE_OF_iand            ] = &&e_label_iand;
e_Instruction_Label_Lookup[ e_VALUE_OF_land            ] = &&e_label_land;
e_Instruction_Label_Lookup[ e_VALUE_OF_ior             ] = &&e_label_ior;
e_Instruction_Label_Lookup[ e_VALUE_OF_lor             ] = &&e_label_lor;
e_Instruction_Label_Lookup[ e_VALUE_OF_ixor            ] = &&e_label_ixor;
e_Instruction_Label_Lookup[ e_VALUE_OF_lxor            ] = &&e_label_lxor;
e_Instruction_Label_Lookup[ e_VALUE_OF_iinc            ] = &&e_label_iinc;
e_Instruction_Label_Lookup[ e_VALUE_OF_i2l             ] = &&e_label_i2l;
e_Instruction_Label_Lookup[ e_VALUE_OF_i2f             ] = &&e_label_i2f;
e_Instruction_Label_Lookup[ e_VALUE_OF_i2d             ] = &&e_label_i2d;
e_Instruction_Label_Lookup[ e_VALUE_OF_l2i             ] = &&e_label_l2i;
e_Instruction_Label_Lookup[ e_VALUE_OF_l2f             ] = &&e_label_l2f;
e_Instruction_Label_Lookup[ e_VALUE_OF_l2d             ] = &&e_label_l2d;
e_Instruction_Label_Lookup[ e_VALUE_OF_f2i             ] = &&e_label_f2i;
e_Instruction_Label_Lookup[ e_VALUE_OF_f2l             ] = &&e_label_f2l;
e_Instruction_Label_Lookup[ e_VALUE_OF_f2d             ] = &&e_label_f2d;
e_Instruction_Label_Lookup[ e_VALUE_OF_d2i             ] = &&e_label_d2i;
e_Instruction_Label_Lookup[ e_VALUE_OF_d2l             ] = &&e_label_d2l;
e_Instruction_Label_Lookup[ e_VALUE_OF_d2f             ] = &&e_label_d2f;
e_Instruction_Label_Lookup[ e_VALUE_OF_i2b             ] = &&e_label_i2b;
e_Instruction_Label_Lookup[ e_VALUE_OF_i2c             ] = &&e_label_i2c;
e_Instruction_Label_Lookup[ e_VALUE_OF_i2s             ] = &&e_label_i2s;
e_Instruction_Label_Lookup[ e_VALUE_OF_lcmp            ] = &&e_label_lcmp;
e_Instruction_Label_Lookup[ e_VALUE_OF_fcmpl           ] = &&e_label_fcmpl;
e_Instruction_Label_Lookup[ e_VALUE_OF_fcmpg           ] = &&e_label_fcmpg;
e_Instruction_Label_Lookup[ e_VALUE_OF_dcmpl           ] = &&e_label_dcmpl;
e_Instruction_Label_Lookup[ e_VALUE_OF_dcmpg           ] = &&e_label_dcmpg;
e_Instruction_Label_Lookup[ e_VALUE_OF_ifeq            ] = &&e_label_ifeq;
e_Instruction_Label_Lookup[ e_VALUE_OF_ifne            ] = &&e_label_ifne;
e_Instruction_Label_Lookup[ e_VALUE_OF_iflt            ] = &&e_label_iflt;
e_Instruction_Label_Lookup[ e_VALUE_OF_ifge            ] = &&e_label_ifge;
e_Instruction_Label_Lookup[ e_VALUE_OF_ifgt            ] = &&e_label_ifgt;
e_Instruction_Label_Lookup[ e_VALUE_OF_ifle            ] = &&e_label_ifle;
e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmpeq       ] = &&e_label_if_icmpeq;
e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmpne       ] = &&e_label_if_icmpne;
e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmplt       ] = &&e_label_if_icmplt;
e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmpge       ] = &&e_label_if_icmpge;
e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmpgt       ] = &&e_label_if_icmpgt;
e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmple       ] = &&e_label_if_icmple;
e_Instruction_Label_Lookup[ e_VALUE_OF_if_acmpeq       ] = &&e_label_if_acmpeq;
e_Instruction_Label_Lookup[ e_VALUE_OF_if_acmpne       ] = &&e_label_if_acmpne;
e_Instruction_Label_Lookup[ e_VALUE_OF_goto            ] = &&e_label_goto;
e_Instruction_Label_Lookup[ e_VALUE_OF_jsr             ] = &&e_label_jsr;
e_Instruction_Label_Lookup[ e_VALUE_OF_ret             ] = &&e_label_ret;
e_Instruction_Label_Lookup[ e_VALUE_OF_tableswitch     ] = &&e_label_tableswitch;
e_Instruction_Label_Lookup[ e_VALUE_OF_lookupswitch    ] = &&e_label_lookupswitch;
e_Instruction_Label_Lookup[ e_VALUE_OF_ireturn         ] = &&e_label_ireturn;
e_Instruction_Label_Lookup[ e_VALUE_OF_lreturn         ] = &&e_label_lreturn;
e_Instruction_Label_Lookup[ e_VALUE_OF_freturn         ] = &&e_label_freturn;
e_Instruction_Label_Lookup[ e_VALUE_OF_dreturn         ] = &&e_label_dreturn;
e_Instruction_Label_Lookup[ e_VALUE_OF_areturn         ] = &&e_label_areturn;
e_Instruction_Label_Lookup[ e_VALUE_OF_return          ] = &&e_label_return;
e_Instruction_Label_Lookup[ e_VALUE_OF_getstatic       ] = &&e_label_getstatic;
e_Instruction_Label_Lookup[ e_VALUE_OF_putstatic       ] = &&e_label_putstatic;
e_Instruction_Label_Lookup[ e_VALUE_OF_getfield        ] = &&e_label_getfield;
e_Instruction_Label_Lookup[ e_VALUE_OF_putfield        ] = &&e_label_putfield;
e_Instruction_Label_Lookup[ e_VALUE_OF_invokevirtual   ] = &&e_label_invokevirtual;
e_Instruction_Label_Lookup[ e_VALUE_OF_invokespecial   ] = &&e_label_invokespecial;
e_Instruction_Label_Lookup[ e_VALUE_OF_invokestatic    ] = &&e_label_invokestatic;
e_Instruction_Label_Lookup[ e_VALUE_OF_invokeinterface ] = &&e_label_invokeinterface;
e_Instruction_Label_Lookup[ e_VALUE_OF_xxxunusedxxx1   ] = &&e_label_xxxunusedxxx1;
e_Instruction_Label_Lookup[ e_VALUE_OF_new             ] = &&e_label_new;
e_Instruction_Label_Lookup[ e_VALUE_OF_newarray        ] = &&e_label_newarray;
e_Instruction_Label_Lookup[ e_VALUE_OF_anewarray       ] = &&e_label_anewarray;
e_Instruction_Label_Lookup[ e_VALUE_OF_arraylength     ] = &&e_label_arraylength;
e_Instruction_Label_Lookup[ e_VALUE_OF_athrow          ] = &&e_label_athrow;
e_Instruction_Label_Lookup[ e_VALUE_OF_checkcast       ] = &&e_label_checkcast;
e_Instruction_Label_Lookup[ e_VALUE_OF_instanceof      ] = &&e_label_instanceof;
e_Instruction_Label_Lookup[ e_VALUE_OF_monitorenter    ] = &&e_label_monitorenter;
e_Instruction_Label_Lookup[ e_VALUE_OF_monitorexit     ] = &&e_label_monitorexit;
e_Instruction_Label_Lookup[ e_VALUE_OF_wide            ] = &&e_label_wide;
e_Instruction_Label_Lookup[ e_VALUE_OF_multianewarray  ] = &&e_label_multianewarray;
e_Instruction_Label_Lookup[ e_VALUE_OF_ifnull          ] = &&e_label_ifnull;
e_Instruction_Label_Lookup[ e_VALUE_OF_ifnonnull       ] = &&e_label_ifnonnull;
e_Instruction_Label_Lookup[ e_VALUE_OF_goto_w          ] = &&e_label_goto_w;
e_Instruction_Label_Lookup[ e_VALUE_OF_jsr_w           ] = &&e_label_jsr_w;
e_Instruction_Label_Lookup[ e_VALUE_OF_breakpoint      ] = &&e_label_breakpoint;
e_Instruction_Label_Lookup[ e_VALUE_OF_impdep1         ] = &&e_label_impdep1;
e_Instruction_Label_Lookup[ e_VALUE_OF_impdep2         ] = &&e_label_impdep2;


//Assertions
assert(sizeof( e_j_double ) == 8);
assert(sizeof( e_byte_t ) ==1 );
assert(sizeof( e_j_float ) == 4 );
assert(sizeof( e_j_integer ) == 4 );
assert(sizeof( e_j_long ) == 8 );
assert(sizeof( e_j_char ) == 2 );
assert(sizeof( e_j_short ) == 8 );

	
/*
 * Local Variables
 * ===============
 */

	unsigned int   	  pc     ;            /* 	program counter     		*/
	e_j_word*   	  op_stk ;            /* 	operand stack       		*/
	e_j_word*	  op_stk_top;         /* 	operand stack  top  		*/
	e_j_word*  	  locals ;            /* 	local variables     		*/
	e_j_u_byte* 	  code   ; 	  		  /* 	byte-code stream    		*/	
	e_j_u_byte* 	  code_sofar   ; 	  /* 	current byte-code stream    */	
	gnrc_node_t*      java_stack   ;	
	ConstantPool*     constant_pool;


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
  locals = ((typeof(locals))  malloc( ((int)method->maxLocals)  * sizeof(e_j_word)));
    
  //Allocating Operand Stack
  op_stk = ((typeof(op_stk))  malloc( ((int)method->maxStack+1)  * sizeof(e_j_word)));

 
  

 
  
/* Intiailization	
 * ==============
 */
	code = method->code;
	code_sofar=code;
	pc = 0;
	op_stk_top = (op_stk);
	op_stk++;
	java_stack = NULL;
	constant_pool = const_pool;
	 
	

	

/*
 * Start
 *=======
 */
 
 
  goto  *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ]; 	/* execute first bytecode*/
  
e_label_nop :

	e_console_log_start(nop)
	e_CORE_nop ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(nop) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aconst_null :

	e_console_log_start(aconst_null)
	e_CORE_aconst_null ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(aconst_null) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_m1 :

	e_console_log_start(iconst_m1)
	e_CORE_iconst_m1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iconst_m1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_0 :

	e_console_log_start(iconst_0)
	e_CORE_iconst_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iconst_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_1 :

	e_console_log_start(iconst_1)
	e_CORE_iconst_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iconst_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_2 :

	e_console_log_start(iconst_2)
	e_CORE_iconst_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iconst_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_3 :

	e_console_log_start(iconst_3)
	e_CORE_iconst_3 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iconst_3) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_4 :

	e_console_log_start(iconst_4)
	e_CORE_iconst_4 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iconst_4) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_5 :

	e_console_log_start(iconst_5)
	e_CORE_iconst_5 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iconst_5) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lconst_0 :

	e_console_log_start(lconst_0)
	e_CORE_lconst_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lconst_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lconst_1 :

	e_console_log_start(lconst_1)
	e_CORE_lconst_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lconst_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fconst_0 :

	e_console_log_start(fconst_0)
	e_CORE_fconst_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fconst_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fconst_1 :

	e_console_log_start(fconst_1)
	e_CORE_fconst_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fconst_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fconst_2 :

	e_console_log_start(fconst_2)
	e_CORE_fconst_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fconst_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dconst_0 :

	e_console_log_start(dconst_0)
	e_CORE_dconst_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dconst_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dconst_1 :

	e_console_log_start(dconst_1)
	e_CORE_dconst_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dconst_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_bipush :

	e_console_log_start(bipush)
	e_CORE_bipush ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(bipush) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_sipush :

	e_console_log_start(sipush)
	e_CORE_sipush ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(sipush) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ldc :

	e_console_log_start(ldc)
	e_CORE_ldc ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ldc) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ldc_w :

	e_console_log_start(ldc_w)
	e_CORE_ldc_w ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ldc_w) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ldc2_w :

	e_console_log_start(ldc2_w)
	e_CORE_ldc2_w ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ldc2_w) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iload :

	e_console_log_start(iload)
	e_CORE_iload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iload) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lload :

	e_console_log_start(lload)
	e_CORE_lload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lload) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fload :

	e_console_log_start(fload)
	e_CORE_fload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fload) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dload :

	e_console_log_start(dload)
	e_CORE_dload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dload) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aload :

	e_console_log_start(aload)
	e_CORE_aload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(aload) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iload_0 :

	e_console_log_start(iload_0)
	e_CORE_iload_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iload_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iload_1 :

	e_console_log_start(iload_1)
	e_CORE_iload_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iload_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iload_2 :

	e_console_log_start(iload_2)
	e_CORE_iload_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iload_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iload_3 :

	e_console_log_start(iload_3)
	e_CORE_iload_3 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iload_3) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lload_0 :

	e_console_log_start(lload_0)
	e_CORE_lload_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lload_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lload_1 :

	e_console_log_start(lload_1)
	e_CORE_lload_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lload_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lload_2 :

	e_console_log_start(lload_2)
	e_CORE_lload_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lload_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lload_3 :

	e_console_log_start(lload_3)
	e_CORE_lload_3 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lload_3) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fload_0 :

	e_console_log_start(fload_0)
	e_CORE_fload_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fload_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fload_1 :

	e_console_log_start(fload_1)
	e_CORE_fload_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fload_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fload_2 :

	e_console_log_start(fload_2)
	e_CORE_fload_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fload_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fload_3 :

	e_console_log_start(fload_3)
	e_CORE_fload_3 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fload_3) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dload_0 :

	e_console_log_start(dload_0)
	e_CORE_dload_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dload_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dload_1 :

	e_console_log_start(dload_1)
	e_CORE_dload_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dload_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dload_2 :

	e_console_log_start(dload_2)
	e_CORE_dload_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dload_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dload_3 :

	e_console_log_start(dload_3)
	e_CORE_dload_3 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dload_3) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aload_0 :

	e_console_log_start(aload_0)
	e_CORE_aload_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(aload_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aload_1 :

	e_console_log_start(aload_1)
	e_CORE_aload_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(aload_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aload_2 :

	e_console_log_start(aload_2)
	e_CORE_aload_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(aload_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aload_3 :

	e_console_log_start(aload_3)
	e_CORE_aload_3 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(aload_3) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iaload :

	e_console_log_start(iaload)
	e_CORE_iaload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iaload) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_laload :

	e_console_log_start(laload)
	e_CORE_laload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(laload) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_faload :

	e_console_log_start(faload)
	e_CORE_faload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(faload) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_daload :

	e_console_log_start(daload)
	e_CORE_daload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(daload) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aaload :

	e_console_log_start(aaload)
	e_CORE_aaload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(aaload) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_baload :

	e_console_log_start(baload)
	e_CORE_baload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(baload) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_caload :

	e_console_log_start(caload)
	e_CORE_caload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(caload) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_saload :

	e_console_log_start(saload)
	e_CORE_saload ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(saload) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_istore :

	e_console_log_start(istore)
	e_CORE_istore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(istore) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lstore :

	e_console_log_start(lstore)
	e_CORE_lstore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lstore) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fstore :

	e_console_log_start(fstore)
	e_CORE_fstore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fstore) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dstore :

	e_console_log_start(dstore)
	e_CORE_dstore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dstore) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_astore :

	e_console_log_start(astore)
	e_CORE_astore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(astore) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_istore_0 :

	e_console_log_start(istore_0)
	e_CORE_istore_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(istore_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_istore_1 :

	e_console_log_start(istore_1)
	e_CORE_istore_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(istore_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_istore_2 :

	e_console_log_start(istore_2)
	e_CORE_istore_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(istore_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_istore_3 :

	e_console_log_start(istore_3)
	e_CORE_istore_3 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(istore_3) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lstore_0 :

	e_console_log_start(lstore_0)
	e_CORE_lstore_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lstore_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lstore_1 :

	e_console_log_start(lstore_1)
	e_CORE_lstore_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lstore_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lstore_2 :

	e_console_log_start(lstore_2)
	e_CORE_lstore_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lstore_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lstore_3 :

	e_console_log_start(lstore_3)
	e_CORE_lstore_3 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lstore_3) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fstore_0 :

	e_console_log_start(fstore_0)
	e_CORE_fstore_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fstore_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fstore_1 :

	e_console_log_start(fstore_1)
	e_CORE_fstore_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fstore_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fstore_2 :

	e_console_log_start(fstore_2)
	e_CORE_fstore_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fstore_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fstore_3 :

	e_console_log_start(fstore_3)
	e_CORE_fstore_3 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fstore_3) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dstore_0 :

	e_console_log_start(dstore_0)
	e_CORE_dstore_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dstore_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dstore_1 :

	e_console_log_start(dstore_1)
	e_CORE_dstore_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dstore_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dstore_2 :

	e_console_log_start(dstore_2)
	e_CORE_dstore_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dstore_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dstore_3 :

	e_console_log_start(dstore_3)
	e_CORE_dstore_3 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dstore_3) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_astore_0 :

	e_console_log_start(astore_0)
	e_CORE_astore_0 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(astore_0) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_astore_1 :

	e_console_log_start(astore_1)
	e_CORE_astore_1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(astore_1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_astore_2 :

	e_console_log_start(astore_2)
	e_CORE_astore_2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(astore_2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_astore_3 :

	e_console_log_start(astore_3)
	e_CORE_astore_3 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(astore_3) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iastore :

	e_console_log_start(iastore)
	e_CORE_iastore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iastore) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lastore :

	e_console_log_start(lastore)
	e_CORE_lastore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lastore) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fastore :

	e_console_log_start(fastore)
	e_CORE_fastore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fastore) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dastore :

	e_console_log_start(dastore)
	e_CORE_dastore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dastore) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aastore :

	e_console_log_start(aastore)
	e_CORE_aastore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(aastore) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_bastore :

	e_console_log_start(bastore)
	e_CORE_bastore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(bastore) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_castore :

	e_console_log_start(castore)
	e_CORE_castore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(castore) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_sastore :

	e_console_log_start(sastore)
	e_CORE_sastore ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(sastore) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_pop :

	e_console_log_start(pop)
	e_CORE_pop ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(pop) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_pop2 :

	e_console_log_start(pop2)
	e_CORE_pop2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(pop2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup :

	e_console_log_start(dup)
	e_CORE_dup ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dup) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup_x1 :

	e_console_log_start(dup_x1)
	e_CORE_dup_x1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dup_x1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup_x2 :

	e_console_log_start(dup_x2)
	e_CORE_dup_x2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dup_x2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup2 :

	e_console_log_start(dup2)
	e_CORE_dup2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dup2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup2_x1 :

	e_console_log_start(dup2_x1)
	e_CORE_dup2_x1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dup2_x1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup2_x2 :

	e_console_log_start(dup2_x2)
	e_CORE_dup2_x2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dup2_x2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_swap :

	e_console_log_start(swap)
	e_CORE_swap ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(swap) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iadd :

	e_console_log_start(iadd)
	e_CORE_iadd ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iadd) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ladd :

	e_console_log_start(ladd)
	e_CORE_ladd ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ladd) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fadd :

	e_console_log_start(fadd)
	e_CORE_fadd ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fadd) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dadd :

	e_console_log_start(dadd)
	e_CORE_dadd ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dadd) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_isub :

	e_console_log_start(isub)
	e_CORE_isub ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(isub) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lsub :

	e_console_log_start(lsub)
	e_CORE_lsub ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lsub) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fsub :

	e_console_log_start(fsub)
	e_CORE_fsub ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fsub) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dsub :

	e_console_log_start(dsub)
	e_CORE_dsub ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dsub) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_imul :

	e_console_log_start(imul)
	e_CORE_imul ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(imul) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lmul :

	e_console_log_start(lmul)
	e_CORE_lmul ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lmul) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fmul :

	e_console_log_start(fmul)
	e_CORE_fmul ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fmul) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dmul :

	e_console_log_start(dmul)
	e_CORE_dmul ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dmul) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_idiv :

	e_console_log_start(idiv)
	e_CORE_idiv ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(idiv) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ldiv :

	e_console_log_start(ldiv)
	e_CORE_ldiv ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ldiv) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fdiv :

	e_console_log_start(fdiv)
	e_CORE_fdiv ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fdiv) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ddiv :

	e_console_log_start(ddiv)
	e_CORE_ddiv ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ddiv) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_irem :

	e_console_log_start(irem)
	e_CORE_irem ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(irem) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lrem :

	e_console_log_start(lrem)
	e_CORE_lrem ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lrem) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_frem :

	e_console_log_start(frem)
	e_CORE_frem ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(frem) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_drem :

	e_console_log_start(drem)
	e_CORE_drem ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(drem) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ineg :

	e_console_log_start(ineg)
	e_CORE_ineg ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ineg) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lneg :

	e_console_log_start(lneg)
	e_CORE_lneg ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lneg) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fneg :

	e_console_log_start(fneg)
	e_CORE_fneg ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fneg) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dneg :

	e_console_log_start(dneg)
	e_CORE_dneg ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dneg) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ishl :

	e_console_log_start(ishl)
	e_CORE_ishl ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ishl) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lshl :

	e_console_log_start(lshl)
	e_CORE_lshl ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lshl) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ishr :

	e_console_log_start(ishr)
	e_CORE_ishr ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ishr) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lshr :

	e_console_log_start(lshr)
	e_CORE_lshr ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lshr) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iushr :

	e_console_log_start(iushr)
	e_CORE_iushr ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iushr) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lushr :

	e_console_log_start(lushr)
	e_CORE_lushr ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lushr) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iand :

	e_console_log_start(iand)
	e_CORE_iand ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iand) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_land :

	e_console_log_start(land)
	e_CORE_land ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(land) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ior :

	e_console_log_start(ior)
	e_CORE_ior ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ior) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lor :

	e_console_log_start(lor)
	e_CORE_lor ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lor) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ixor :

	e_console_log_start(ixor)
	e_CORE_ixor ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ixor) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lxor :

	e_console_log_start(lxor)
	e_CORE_lxor ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lxor) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iinc :

	e_console_log_start(iinc)
	e_CORE_iinc ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iinc) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2l :

	e_console_log_start(i2l)
	e_CORE_i2l ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(i2l) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2f :

	e_console_log_start(i2f)
	e_CORE_i2f ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(i2f) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2d :

	e_console_log_start(i2d)
	e_CORE_i2d ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(i2d) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_l2i :

	e_console_log_start(l2i)
	e_CORE_l2i ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(l2i) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_l2f :

	e_console_log_start(l2f)
	e_CORE_l2f ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(l2f) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_l2d :

	e_console_log_start(l2d)
	e_CORE_l2d ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(l2d) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_f2i :

	e_console_log_start(f2i)
	e_CORE_f2i ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(f2i) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_f2l :

	e_console_log_start(f2l)
	e_CORE_f2l ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(f2l) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_f2d :

	e_console_log_start(f2d)
	e_CORE_f2d ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(f2d) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_d2i :

	e_console_log_start(d2i)
	e_CORE_d2i ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(d2i) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_d2l :

	e_console_log_start(d2l)
	e_CORE_d2l ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(d2l) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_d2f :

	e_console_log_start(d2f)
	e_CORE_d2f ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(d2f) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2b :

	e_console_log_start(i2b)
	e_CORE_i2b ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(i2b) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2c :

	e_console_log_start(i2c)
	e_CORE_i2c ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(i2c) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2s :

	e_console_log_start(i2s)
	e_CORE_i2s ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(i2s) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lcmp :

	e_console_log_start(lcmp)
	e_CORE_lcmp ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lcmp) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fcmpl :

	e_console_log_start(fcmpl)
	e_CORE_fcmpl ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fcmpl) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fcmpg :

	e_console_log_start(fcmpg)
	e_CORE_fcmpg ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(fcmpg) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dcmpl :

	e_console_log_start(dcmpl)
	e_CORE_dcmpl ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dcmpl) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dcmpg :

	e_console_log_start(dcmpg)
	e_CORE_dcmpg ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dcmpg) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ifeq :

	e_console_log_start(ifeq)
	e_CORE_ifeq ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ifeq) ;
e_label_ifne :

	e_console_log_start(ifne)
	e_CORE_ifne ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ifne) ;
e_label_iflt :

	e_console_log_start(iflt)
	e_CORE_iflt ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(iflt) ;
e_label_ifge :

	e_console_log_start(ifge)
	e_CORE_ifge ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ifge) ;
e_label_ifgt :

	e_console_log_start(ifgt)
	e_CORE_ifgt ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ifgt) ;
e_label_ifle :

	e_console_log_start(ifle)
	e_CORE_ifle ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ifle) ;
e_label_if_icmpeq :

	e_console_log_start(if_icmpeq)
	e_CORE_if_icmpeq ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(if_icmpeq) ;
e_label_if_icmpne :

	e_console_log_start(if_icmpne)
	e_CORE_if_icmpne ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(if_icmpne) ;
e_label_if_icmplt :

	e_console_log_start(if_icmplt)
	e_CORE_if_icmplt ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(if_icmplt) ;
e_label_if_icmpge :

	e_console_log_start(if_icmpge)
	e_CORE_if_icmpge ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(if_icmpge) ;
e_label_if_icmpgt :

	e_console_log_start(if_icmpgt)
	e_CORE_if_icmpgt ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(if_icmpgt) ;
e_label_if_icmple :

	e_console_log_start(if_icmple)
	e_CORE_if_icmple ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(if_icmple) ;
e_label_if_acmpeq :

	e_console_log_start(if_acmpeq)
	e_CORE_if_acmpeq ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(if_acmpeq) ;
e_label_if_acmpne :

	e_console_log_start(if_acmpne)
	e_CORE_if_acmpne ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(if_acmpne) ;
e_label_goto :

	e_console_log_start(goto)
	e_CORE_goto ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(goto) ;
e_label_jsr :

	e_console_log_start(jsr)
	e_CORE_jsr ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(jsr) ;
e_label_ret :

	e_console_log_start(ret)
	e_CORE_ret ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ret) ;
e_label_tableswitch :

	e_console_log_start(tableswitch)
	e_CORE_tableswitch ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(tableswitch) ;
e_label_lookupswitch :

	e_console_log_start(lookupswitch)
	e_CORE_lookupswitch ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lookupswitch) ;
e_label_ireturn :

	e_console_log_start(ireturn)
	e_CORE_ireturn ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ireturn) ;
e_label_lreturn :

	e_console_log_start(lreturn)
	e_CORE_lreturn ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(lreturn) ;
e_label_freturn :

	e_console_log_start(freturn)
	e_CORE_freturn ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(freturn) ;
e_label_dreturn :

	e_console_log_start(dreturn)
	e_CORE_dreturn ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(dreturn) ;
e_label_areturn :

	e_console_log_start(areturn)
	e_CORE_areturn ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(areturn) ;
e_label_return :
	
	e_console_log_start(return)
	e_TRACE_ANNOUNCE_INSTRUCTION(return);
	e_TRACE_CLOSE( )
	e_CORE_return ;
	e_console_log_end
	

	e_TRACE_CLOSE( )
	return 0;

e_label_getstatic :

	e_console_log_start(getstatic)
	e_CORE_getstatic ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(getstatic) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_putstatic :

	e_console_log_start(putstatic)
	e_CORE_putstatic ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(putstatic) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_getfield :

	e_console_log_start(getfield)
	e_CORE_getfield ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(getfield) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_putfield :

	e_console_log_start(putfield)
	e_CORE_putfield ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(putfield) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_invokevirtual :

	e_console_log_start(invokevirtual)
	e_CORE_invokevirtual ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(invokevirtual) ;
e_label_invokespecial :

	e_console_log_start(invokespecial)
	e_CORE_invokespecial ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(invokespecial) ;
e_label_invokestatic :

	e_console_log_start(invokestatic)
	e_CORE_invokestatic ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(invokestatic) ;
e_label_invokeinterface :

	e_console_log_start(invokeinterface)
	e_CORE_invokeinterface ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(invokeinterface) ;
e_label_xxxunusedxxx1 :

	e_console_log_start(xxxunusedxxx1)
	e_CORE_xxxunusedxxx1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(xxxunusedxxx1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_new :

	e_console_log_start(new)
	e_CORE_new ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(new) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_newarray :

	e_console_log_start(newarray)
	e_CORE_newarray ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(newarray) ;
	code_sofar += 2 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_anewarray :

	e_console_log_start(anewarray)
	e_CORE_anewarray ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(anewarray) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_arraylength :

	e_console_log_start(arraylength)
	e_CORE_arraylength ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(arraylength) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_athrow :

	e_console_log_start(athrow)
	e_CORE_athrow ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(athrow) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_checkcast :

	e_console_log_start(checkcast)
	e_CORE_checkcast ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(checkcast) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_instanceof :

	e_console_log_start(instanceof)
	e_CORE_instanceof ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(instanceof) ;
	code_sofar += 3 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_monitorenter :

	e_console_log_start(monitorenter)
	e_CORE_monitorenter ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(monitorenter) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_monitorexit :

	e_console_log_start(monitorexit)
	e_CORE_monitorexit ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(monitorexit) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_wide :

	e_console_log_start(wide)
	e_CORE_wide ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(wide) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_multianewarray :

	e_console_log_start(multianewarray)
	e_CORE_multianewarray ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(multianewarray) ;
	code_sofar += 4 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ifnull :

	e_console_log_start(ifnull)
	e_CORE_ifnull ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ifnull) ;
e_label_ifnonnull :

	e_console_log_start(ifnonnull)
	e_CORE_ifnonnull ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(ifnonnull) ;
e_label_goto_w :

	e_console_log_start(goto_w)
	e_CORE_goto_w ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(goto_w) ;
e_label_jsr_w :

	e_console_log_start(jsr_w)
	e_CORE_jsr_w ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(jsr_w) ;
e_label_breakpoint :

	e_console_log_start(breakpoint)
	e_CORE_breakpoint ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(breakpoint) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_impdep1 :

	e_console_log_start(impdep1)
	e_CORE_impdep1 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(impdep1) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_impdep2 :

	e_console_log_start(impdep2)
	e_CORE_impdep2 ;
	e_console_log_end
	e_TRACE_ANNOUNCE_INSTRUCTION(impdep2) ;
	code_sofar += 1 ;
	goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];


	
/*		
inst_impl_label:
	next_addr_computation(inst)
	Debug_preexec(inst)
	Core_inst
	Denugafterexec(inst)
	Goto next
	*/
	
FAULT:
e_TRACE_CLOSE( )
	
return 0;

}

/*************************************************************************************************/
//
//void ExecutionEng::calNumOfArg(char * p,unsigned int & argCount,unsigned int & opStackArgCount)
//{
//	argCount=0;
//	opStackArgCount=0;
//	p++;     /* skip start ( */    
//	while(*p != ')')
//	{                         
//		if((*p == 'J') || (*p == 'D'))//arg is long or double
//		{
//			argCount++;
//			opStackArgCount+=2;	
//			p++;
//		}
//		else
//		{
//    		if(*p == '[') //array
//       		{
//        		//we will not increment the following 2 variables why?
//        		//because if it is array, and when we will check the type of the array,
//        		//we will increment them, so we will incremnet them twice and that is wrong
//        		//argCount++;
//        		//opStackArgCount++;
//        		for(p++; *p == '['; p++);         
//        	}
//        
//        	if(*p == 'L')//refrence
//        	{
//        		argCount++;  
//        		opStackArgCount++;                       
//           		while(*p++ != ';');
//       		}
//        	else //primitive types
//        	{
//        		argCount++;
//        		opStackArgCount++;
//        		p++;                                 
//        	} 
//



