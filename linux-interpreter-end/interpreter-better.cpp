#include"ejvm.h"
#include"log.h"




typedef unsigned char byte;

typedef unsigned char u1;

typedef unsigned short int u2;

typedef unsigned int u4;

class ExceptionTable;

class ByteCode
{
public:
 u2 nameIndex;

    u4 length;

    u2 maxStack;

    u2 maxLocals;

    u4 codeLength;

    u1 * code;

    ExceptionTable * exceptionTable;

public:
 ByteCode(){};

 ByteCode(byte inputFile [],int inPtr,u2 nameIndex, u4 length);

 virtual ~ByteCode();

};

 typedef unsigned char e_byte_t,u1_t,e_j_u_byte;

 typedef unsigned int e_j_u_integer;

 typedef unsigned long e_j_u_long;

 typedef unsigned short e_j_char;

 typedef char e_j_byte;

 typedef double e_j_double;

 typedef long e_j_long;

 typedef float e_j_float;

 typedef int e_j_integer;

 typedef int e_j_word;

 typedef short e_j_short;

 typedef int e_j_refrence;

 typedef int64_t e_j_long_long;

  typedef char e_j_wide_byte;

  typedef short e_j_wide_short;

  typedef int e_j_wide_integer;

 typedef
 typedef struct const_pool_t{};


 typedef struct method_t{
  unsigned int operand_stack_length ;

  unsigned int locals_length ;

  unsigned int byteCodeLength ;

  e_byte_t* code ;


 };


 typedef struct e_frame_t{
  unsigned int pc ;

  e_j_word* op_stk ;

  e_j_word* op_stk_top;

  e_j_word* locals ;

  e_byte_t* code ;

  e_byte_t* code_sofar ;

  }e_frame_t;

class Exec{
public: static int e_exexute(const_pool_t* const_pool,ByteCode* method);

};

 void* e_Instruction_Label_Lookup[255];

 int Exec::e_exexute(const_pool_t* const_pool,ByteCode* method){

e_TRACE_CREATE_TRACE_FILE("dd")





e_Instruction_Label_Lookup[ e_VALUE_OF_nop ] = &&e_label_nop;

e_Instruction_Label_Lookup[ e_VALUE_OF_aconst_null ] = &&e_label_aconst_null;

e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_m1 ] = &&e_label_iconst_m1;

e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_0 ] = &&e_label_iconst_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_1 ] = &&e_label_iconst_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_2 ] = &&e_label_iconst_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_3 ] = &&e_label_iconst_3;

e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_4 ] = &&e_label_iconst_4;

e_Instruction_Label_Lookup[ e_VALUE_OF_iconst_5 ] = &&e_label_iconst_5;

e_Instruction_Label_Lookup[ e_VALUE_OF_lconst_0 ] = &&e_label_lconst_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_lconst_1 ] = &&e_label_lconst_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_fconst_0 ] = &&e_label_fconst_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_fconst_1 ] = &&e_label_fconst_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_fconst_2 ] = &&e_label_fconst_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_dconst_0 ] = &&e_label_dconst_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_dconst_1 ] = &&e_label_dconst_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_bipush ] = &&e_label_bipush;

e_Instruction_Label_Lookup[ e_VALUE_OF_sipush ] = &&e_label_sipush;

e_Instruction_Label_Lookup[ e_VALUE_OF_ldc ] = &&e_label_ldc;

e_Instruction_Label_Lookup[ e_VALUE_OF_ldc_w ] = &&e_label_ldc_w;

e_Instruction_Label_Lookup[ e_VALUE_OF_ldc2_w ] = &&e_label_ldc2_w;

e_Instruction_Label_Lookup[ e_VALUE_OF_iload ] = &&e_label_iload;

e_Instruction_Label_Lookup[ e_VALUE_OF_lload ] = &&e_label_lload;

e_Instruction_Label_Lookup[ e_VALUE_OF_fload ] = &&e_label_fload;

e_Instruction_Label_Lookup[ e_VALUE_OF_dload ] = &&e_label_dload;

e_Instruction_Label_Lookup[ e_VALUE_OF_aload ] = &&e_label_aload;

e_Instruction_Label_Lookup[ e_VALUE_OF_iload_0 ] = &&e_label_iload_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_iload_1 ] = &&e_label_iload_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_iload_2 ] = &&e_label_iload_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_iload_3 ] = &&e_label_iload_3;

e_Instruction_Label_Lookup[ e_VALUE_OF_lload_0 ] = &&e_label_lload_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_lload_1 ] = &&e_label_lload_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_lload_2 ] = &&e_label_lload_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_lload_3 ] = &&e_label_lload_3;

e_Instruction_Label_Lookup[ e_VALUE_OF_fload_0 ] = &&e_label_fload_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_fload_1 ] = &&e_label_fload_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_fload_2 ] = &&e_label_fload_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_fload_3 ] = &&e_label_fload_3;

e_Instruction_Label_Lookup[ e_VALUE_OF_dload_0 ] = &&e_label_dload_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_dload_1 ] = &&e_label_dload_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_dload_2 ] = &&e_label_dload_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_dload_3 ] = &&e_label_dload_3;

e_Instruction_Label_Lookup[ e_VALUE_OF_aload_0 ] = &&e_label_aload_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_aload_1 ] = &&e_label_aload_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_aload_2 ] = &&e_label_aload_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_aload_3 ] = &&e_label_aload_3;

e_Instruction_Label_Lookup[ e_VALUE_OF_iaload ] = &&e_label_iaload;

e_Instruction_Label_Lookup[ e_VALUE_OF_laload ] = &&e_label_laload;

e_Instruction_Label_Lookup[ e_VALUE_OF_faload ] = &&e_label_faload;

e_Instruction_Label_Lookup[ e_VALUE_OF_daload ] = &&e_label_daload;

e_Instruction_Label_Lookup[ e_VALUE_OF_aaload ] = &&e_label_aaload;

e_Instruction_Label_Lookup[ e_VALUE_OF_baload ] = &&e_label_baload;

e_Instruction_Label_Lookup[ e_VALUE_OF_caload ] = &&e_label_caload;

e_Instruction_Label_Lookup[ e_VALUE_OF_saload ] = &&e_label_saload;

e_Instruction_Label_Lookup[ e_VALUE_OF_istore ] = &&e_label_istore;

e_Instruction_Label_Lookup[ e_VALUE_OF_lstore ] = &&e_label_lstore;

e_Instruction_Label_Lookup[ e_VALUE_OF_fstore ] = &&e_label_fstore;

e_Instruction_Label_Lookup[ e_VALUE_OF_dstore ] = &&e_label_dstore;

e_Instruction_Label_Lookup[ e_VALUE_OF_astore ] = &&e_label_astore;

e_Instruction_Label_Lookup[ e_VALUE_OF_istore_0 ] = &&e_label_istore_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_istore_1 ] = &&e_label_istore_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_istore_2 ] = &&e_label_istore_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_istore_3 ] = &&e_label_istore_3;

e_Instruction_Label_Lookup[ e_VALUE_OF_lstore_0 ] = &&e_label_lstore_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_lstore_1 ] = &&e_label_lstore_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_lstore_2 ] = &&e_label_lstore_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_lstore_3 ] = &&e_label_lstore_3;

e_Instruction_Label_Lookup[ e_VALUE_OF_fstore_0 ] = &&e_label_fstore_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_fstore_1 ] = &&e_label_fstore_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_fstore_2 ] = &&e_label_fstore_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_fstore_3 ] = &&e_label_fstore_3;

e_Instruction_Label_Lookup[ e_VALUE_OF_dstore_0 ] = &&e_label_dstore_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_dstore_1 ] = &&e_label_dstore_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_dstore_2 ] = &&e_label_dstore_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_dstore_3 ] = &&e_label_dstore_3;

e_Instruction_Label_Lookup[ e_VALUE_OF_astore_0 ] = &&e_label_astore_0;

e_Instruction_Label_Lookup[ e_VALUE_OF_astore_1 ] = &&e_label_astore_1;

e_Instruction_Label_Lookup[ e_VALUE_OF_astore_2 ] = &&e_label_astore_2;

e_Instruction_Label_Lookup[ e_VALUE_OF_astore_3 ] = &&e_label_astore_3;

e_Instruction_Label_Lookup[ e_VALUE_OF_iastore ] = &&e_label_iastore;

e_Instruction_Label_Lookup[ e_VALUE_OF_lastore ] = &&e_label_lastore;

e_Instruction_Label_Lookup[ e_VALUE_OF_fastore ] = &&e_label_fastore;

e_Instruction_Label_Lookup[ e_VALUE_OF_dastore ] = &&e_label_dastore;

e_Instruction_Label_Lookup[ e_VALUE_OF_aastore ] = &&e_label_aastore;

e_Instruction_Label_Lookup[ e_VALUE_OF_bastore ] = &&e_label_bastore;

e_Instruction_Label_Lookup[ e_VALUE_OF_castore ] = &&e_label_castore;

e_Instruction_Label_Lookup[ e_VALUE_OF_sastore ] = &&e_label_sastore;

e_Instruction_Label_Lookup[ e_VALUE_OF_pop ] = &&e_label_pop;

e_Instruction_Label_Lookup[ e_VALUE_OF_pop2 ] = &&e_label_pop2;

e_Instruction_Label_Lookup[ e_VALUE_OF_dup ] = &&e_label_dup;

e_Instruction_Label_Lookup[ e_VALUE_OF_dup_x1 ] = &&e_label_dup_x1;

e_Instruction_Label_Lookup[ e_VALUE_OF_dup_x2 ] = &&e_label_dup_x2;

e_Instruction_Label_Lookup[ e_VALUE_OF_dup2 ] = &&e_label_dup2;

e_Instruction_Label_Lookup[ e_VALUE_OF_dup2_x1 ] = &&e_label_dup2_x1;

e_Instruction_Label_Lookup[ e_VALUE_OF_dup2_x2 ] = &&e_label_dup2_x2;

e_Instruction_Label_Lookup[ e_VALUE_OF_swap ] = &&e_label_swap;

e_Instruction_Label_Lookup[ e_VALUE_OF_iadd ] = &&e_label_iadd;

e_Instruction_Label_Lookup[ e_VALUE_OF_ladd ] = &&e_label_ladd;

e_Instruction_Label_Lookup[ e_VALUE_OF_fadd ] = &&e_label_fadd;

e_Instruction_Label_Lookup[ e_VALUE_OF_dadd ] = &&e_label_dadd;

e_Instruction_Label_Lookup[ e_VALUE_OF_isub ] = &&e_label_isub;

e_Instruction_Label_Lookup[ e_VALUE_OF_lsub ] = &&e_label_lsub;

e_Instruction_Label_Lookup[ e_VALUE_OF_fsub ] = &&e_label_fsub;

e_Instruction_Label_Lookup[ e_VALUE_OF_dsub ] = &&e_label_dsub;

e_Instruction_Label_Lookup[ e_VALUE_OF_imul ] = &&e_label_imul;

e_Instruction_Label_Lookup[ e_VALUE_OF_lmul ] = &&e_label_lmul;

e_Instruction_Label_Lookup[ e_VALUE_OF_fmul ] = &&e_label_fmul;

e_Instruction_Label_Lookup[ e_VALUE_OF_dmul ] = &&e_label_dmul;

e_Instruction_Label_Lookup[ e_VALUE_OF_idiv ] = &&e_label_idiv;

e_Instruction_Label_Lookup[ e_VALUE_OF_ldiv ] = &&e_label_ldiv;

e_Instruction_Label_Lookup[ e_VALUE_OF_fdiv ] = &&e_label_fdiv;

e_Instruction_Label_Lookup[ e_VALUE_OF_ddiv ] = &&e_label_ddiv;

e_Instruction_Label_Lookup[ e_VALUE_OF_irem ] = &&e_label_irem;

e_Instruction_Label_Lookup[ e_VALUE_OF_lrem ] = &&e_label_lrem;

e_Instruction_Label_Lookup[ e_VALUE_OF_frem ] = &&e_label_frem;

e_Instruction_Label_Lookup[ e_VALUE_OF_drem ] = &&e_label_drem;

e_Instruction_Label_Lookup[ e_VALUE_OF_ineg ] = &&e_label_ineg;

e_Instruction_Label_Lookup[ e_VALUE_OF_lneg ] = &&e_label_lneg;

e_Instruction_Label_Lookup[ e_VALUE_OF_fneg ] = &&e_label_fneg;

e_Instruction_Label_Lookup[ e_VALUE_OF_dneg ] = &&e_label_dneg;

e_Instruction_Label_Lookup[ e_VALUE_OF_ishl ] = &&e_label_ishl;

e_Instruction_Label_Lookup[ e_VALUE_OF_lshl ] = &&e_label_lshl;

e_Instruction_Label_Lookup[ e_VALUE_OF_ishr ] = &&e_label_ishr;

e_Instruction_Label_Lookup[ e_VALUE_OF_lshr ] = &&e_label_lshr;

e_Instruction_Label_Lookup[ e_VALUE_OF_iushr ] = &&e_label_iushr;

e_Instruction_Label_Lookup[ e_VALUE_OF_lushr ] = &&e_label_lushr;

e_Instruction_Label_Lookup[ e_VALUE_OF_iand ] = &&e_label_iand;

e_Instruction_Label_Lookup[ e_VALUE_OF_land ] = &&e_label_land;

e_Instruction_Label_Lookup[ e_VALUE_OF_ior ] = &&e_label_ior;

e_Instruction_Label_Lookup[ e_VALUE_OF_lor ] = &&e_label_lor;

e_Instruction_Label_Lookup[ e_VALUE_OF_ixor ] = &&e_label_ixor;

e_Instruction_Label_Lookup[ e_VALUE_OF_lxor ] = &&e_label_lxor;

e_Instruction_Label_Lookup[ e_VALUE_OF_iinc ] = &&e_label_iinc;

e_Instruction_Label_Lookup[ e_VALUE_OF_i2l ] = &&e_label_i2l;

e_Instruction_Label_Lookup[ e_VALUE_OF_i2f ] = &&e_label_i2f;

e_Instruction_Label_Lookup[ e_VALUE_OF_i2d ] = &&e_label_i2d;

e_Instruction_Label_Lookup[ e_VALUE_OF_l2i ] = &&e_label_l2i;

e_Instruction_Label_Lookup[ e_VALUE_OF_l2f ] = &&e_label_l2f;

e_Instruction_Label_Lookup[ e_VALUE_OF_l2d ] = &&e_label_l2d;

e_Instruction_Label_Lookup[ e_VALUE_OF_f2i ] = &&e_label_f2i;

e_Instruction_Label_Lookup[ e_VALUE_OF_f2l ] = &&e_label_f2l;

e_Instruction_Label_Lookup[ e_VALUE_OF_f2d ] = &&e_label_f2d;

e_Instruction_Label_Lookup[ e_VALUE_OF_d2i ] = &&e_label_d2i;

e_Instruction_Label_Lookup[ e_VALUE_OF_d2l ] = &&e_label_d2l;

e_Instruction_Label_Lookup[ e_VALUE_OF_d2f ] = &&e_label_d2f;

e_Instruction_Label_Lookup[ e_VALUE_OF_i2b ] = &&e_label_i2b;

e_Instruction_Label_Lookup[ e_VALUE_OF_i2c ] = &&e_label_i2c;

e_Instruction_Label_Lookup[ e_VALUE_OF_i2s ] = &&e_label_i2s;

e_Instruction_Label_Lookup[ e_VALUE_OF_lcmp ] = &&e_label_lcmp;

e_Instruction_Label_Lookup[ e_VALUE_OF_fcmpl ] = &&e_label_fcmpl;

e_Instruction_Label_Lookup[ e_VALUE_OF_fcmpg ] = &&e_label_fcmpg;

e_Instruction_Label_Lookup[ e_VALUE_OF_dcmpl ] = &&e_label_dcmpl;

e_Instruction_Label_Lookup[ e_VALUE_OF_dcmpg ] = &&e_label_dcmpg;

e_Instruction_Label_Lookup[ e_VALUE_OF_ifeq ] = &&e_label_ifeq;

e_Instruction_Label_Lookup[ e_VALUE_OF_ifne ] = &&e_label_ifne;

e_Instruction_Label_Lookup[ e_VALUE_OF_iflt ] = &&e_label_iflt;

e_Instruction_Label_Lookup[ e_VALUE_OF_ifge ] = &&e_label_ifge;

e_Instruction_Label_Lookup[ e_VALUE_OF_ifgt ] = &&e_label_ifgt;

e_Instruction_Label_Lookup[ e_VALUE_OF_ifle ] = &&e_label_ifle;

e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmpeq ] = &&e_label_if_icmpeq;

e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmpne ] = &&e_label_if_icmpne;

e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmplt ] = &&e_label_if_icmplt;

e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmpge ] = &&e_label_if_icmpge;

e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmpgt ] = &&e_label_if_icmpgt;

e_Instruction_Label_Lookup[ e_VALUE_OF_if_icmple ] = &&e_label_if_icmple;

e_Instruction_Label_Lookup[ e_VALUE_OF_if_acmpeq ] = &&e_label_if_acmpeq;

e_Instruction_Label_Lookup[ e_VALUE_OF_if_acmpne ] = &&e_label_if_acmpne;

e_Instruction_Label_Lookup[ e_VALUE_OF_goto ] = &&e_label_goto;

e_Instruction_Label_Lookup[ e_VALUE_OF_jsr ] = &&e_label_jsr;

e_Instruction_Label_Lookup[ e_VALUE_OF_ret ] = &&e_label_ret;

e_Instruction_Label_Lookup[ e_VALUE_OF_tableswitch ] = &&e_label_tableswitch;

e_Instruction_Label_Lookup[ e_VALUE_OF_lookupswitch ] = &&e_label_lookupswitch;

e_Instruction_Label_Lookup[ e_VALUE_OF_ireturn ] = &&e_label_ireturn;

e_Instruction_Label_Lookup[ e_VALUE_OF_lreturn ] = &&e_label_lreturn;

e_Instruction_Label_Lookup[ e_VALUE_OF_freturn ] = &&e_label_freturn;

e_Instruction_Label_Lookup[ e_VALUE_OF_dreturn ] = &&e_label_dreturn;

e_Instruction_Label_Lookup[ e_VALUE_OF_areturn ] = &&e_label_areturn;

e_Instruction_Label_Lookup[ e_VALUE_OF_return ] = &&e_label_return;

e_Instruction_Label_Lookup[ e_VALUE_OF_getstatic ] = &&e_label_getstatic;

e_Instruction_Label_Lookup[ e_VALUE_OF_putstatic ] = &&e_label_putstatic;

e_Instruction_Label_Lookup[ e_VALUE_OF_getfield ] = &&e_label_getfield;

e_Instruction_Label_Lookup[ e_VALUE_OF_putfield ] = &&e_label_putfield;

e_Instruction_Label_Lookup[ e_VALUE_OF_invokevirtual ] = &&e_label_invokevirtual;

e_Instruction_Label_Lookup[ e_VALUE_OF_invokespecial ] = &&e_label_invokespecial;

e_Instruction_Label_Lookup[ e_VALUE_OF_invokestatic ] = &&e_label_invokestatic;

e_Instruction_Label_Lookup[ e_VALUE_OF_invokeinterface ] = &&e_label_invokeinterface;

e_Instruction_Label_Lookup[ e_VALUE_OF_xxxunusedxxx1 ] = &&e_label_xxxunusedxxx1;

e_Instruction_Label_Lookup[ e_VALUE_OF_new ] = &&e_label_new;

e_Instruction_Label_Lookup[ e_VALUE_OF_newarray ] = &&e_label_newarray;

e_Instruction_Label_Lookup[ e_VALUE_OF_anewarray ] = &&e_label_anewarray;

e_Instruction_Label_Lookup[ e_VALUE_OF_arraylength ] = &&e_label_arraylength;

e_Instruction_Label_Lookup[ e_VALUE_OF_athrow ] = &&e_label_athrow;

e_Instruction_Label_Lookup[ e_VALUE_OF_checkcast ] = &&e_label_checkcast;

e_Instruction_Label_Lookup[ e_VALUE_OF_instanceof ] = &&e_label_instanceof;

e_Instruction_Label_Lookup[ e_VALUE_OF_monitorenter ] = &&e_label_monitorenter;

e_Instruction_Label_Lookup[ e_VALUE_OF_monitorexit ] = &&e_label_monitorexit;

e_Instruction_Label_Lookup[ e_VALUE_OF_wide ] = &&e_label_wide;

e_Instruction_Label_Lookup[ e_VALUE_OF_multianewarray ] = &&e_label_multianewarray;

e_Instruction_Label_Lookup[ e_VALUE_OF_ifnull ] = &&e_label_ifnull;

e_Instruction_Label_Lookup[ e_VALUE_OF_ifnonnull ] = &&e_label_ifnonnull;

e_Instruction_Label_Lookup[ e_VALUE_OF_goto_w ] = &&e_label_goto_w;

e_Instruction_Label_Lookup[ e_VALUE_OF_jsr_w ] = &&e_label_jsr_w;

e_Instruction_Label_Lookup[ e_VALUE_OF_breakpoint ] = &&e_label_breakpoint;

e_Instruction_Label_Lookup[ e_VALUE_OF_impdep1 ] = &&e_label_impdep1;

e_Instruction_Label_Lookup[ e_VALUE_OF_impdep2 ] = &&e_label_impdep2;




assert(sizeof( e_j_double ) == 8);

assert(sizeof( e_byte_t ) < 2 );

assert(sizeof( u1_t ) == 1 );







 unsigned int pc ;

 e_j_word* op_stk ;

 e_j_word* op_stk_top;

 e_j_word* locals ;

 e_j_u_byte* code ;

 e_j_u_byte* code_sofar ;

  locals = ((typeof(locals)) malloc( ((int)method->maxLocals) * sizeof(e_j_word)));

  op_stk = ((typeof(op_stk)) malloc( ((int)method->maxStack) * sizeof(e_j_word)));

 code = method->code;

 code_sofar=code;

 pc = 0;

 op_stk_top = (op_stk);

  goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_nop :
 e_CORE_nop_START: e_CORE_nop_END:
 e_TRACE_ANNOUNCE_INSTRUCTION(nop) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aconst_null :
 e_CORE_aconst_null_START: { (*((typeof(( (e_j_refrence) NULL))*) op_stk_top )) = ( (e_j_refrence) NULL) ;
};
 {op_stk_top += ( sizeof( typeof(( (e_j_refrence) NULL)) )/ sizeof( typeof(op_stk_top) ) );
} e_CORE_aconst_null_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(aconst_null) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_m1 :
 e_CORE_iconst_m1_START: { (*((typeof((e_j_integer)-1)*) op_stk_top )) = (e_j_integer)-1 ;
};
 {op_stk_top += ( sizeof( typeof((e_j_integer)-1) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_iconst_m1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iconst_m1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_0 :
 e_CORE_iconst_0_START: { (*((typeof((e_j_integer)0)*) op_stk_top )) = (e_j_integer)0 ;
};
 {op_stk_top += ( sizeof( typeof((e_j_integer)0) )/ sizeof( typeof(op_stk_top) ) );
};
e_CORE_iconst_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iconst_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_1 :
 e_CORE_iconst_1_START: { (*((typeof(( e_j_integer)1)*) op_stk_top )) = ( e_j_integer)1 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_integer)1) )/ sizeof( typeof(op_stk_top) ) );
};
e_CORE_iconst_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iconst_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_2 :
 e_CORE_iconst_2_START: { (*((typeof(( e_j_integer)2)*) op_stk_top )) = ( e_j_integer)2 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_integer)2) )/ sizeof( typeof(op_stk_top) ) );
};
e_CORE_iconst_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iconst_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_3 :
 e_CORE_iconst_3_START: { (*((typeof(( e_j_integer)3)*) op_stk_top )) = ( e_j_integer)3 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_integer)3) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_iconst_3_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iconst_3) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_4 :
 e_CORE_iconst_4_START: { (*((typeof(( e_j_integer)4)*) op_stk_top )) = ( e_j_integer)4 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_integer)4) )/ sizeof( typeof(op_stk_top) ) );
};
e_CORE_iconst_4_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iconst_4) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iconst_5 :
 e_CORE_iconst_5_START: { (*((typeof(( e_j_integer)5)*) op_stk_top )) = ( e_j_integer)5 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_integer)5) )/ sizeof( typeof(op_stk_top) ) );
};
e_CORE_iconst_5_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iconst_5) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lconst_0 :
 e_CORE_lconst_0_START: { (*((typeof(( e_j_long)0)*) op_stk_top )) = ( e_j_long)0 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_long)0) )/ sizeof( typeof(op_stk_top) ) );
};
e_CORE_lconst_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lconst_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lconst_1 :
 e_CORE_lconst_1_START: { (*((typeof(( e_j_long)1)*) op_stk_top )) = ( e_j_long)1 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_long)1) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lconst_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lconst_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fconst_0 :
 e_CORE_fconst_0_START: { (*((typeof(( e_j_float)0)*) op_stk_top )) = ( e_j_float)0 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_float)0) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fconst_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fconst_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fconst_1 :
 e_CORE_fconst_1_START: { (*((typeof(( e_j_float)1)*) op_stk_top )) = ( e_j_float)1 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_float)1) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fconst_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fconst_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fconst_2 :
 e_CORE_fconst_2_START: { (*((typeof(( e_j_float)2)*) op_stk_top )) = ( e_j_float)2 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_float)2) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fconst_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fconst_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dconst_0 :
 e_CORE_dconst_0_START: { (*((typeof(( e_j_double)0)*) op_stk_top )) = ( e_j_double)0 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_double)0) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dconst_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dconst_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dconst_1 :
 e_CORE_dconst_1_START: { (*((typeof(( e_j_double)1)*) op_stk_top )) = ( e_j_double)1 ;
};
 {op_stk_top += ( sizeof( typeof(( e_j_double)1) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dconst_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dconst_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_bipush :
 e_CORE_bipush_START: { (*((typeof((( (e_j_integer) (*( (e_byte_t*) (code_sofar+1) ) ) ) ))*) op_stk_top )) = (( (e_j_integer) (*( (e_byte_t*) (code_sofar+1) ) ) ) ) ;
};
 {op_stk_top += ( sizeof( typeof((( (e_j_integer) (*( (e_byte_t*) (code_sofar+1) ) ) ) )) )/ sizeof( typeof(op_stk_top) ) );
} e_CORE_bipush_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(bipush) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_sipush :
 e_CORE_sipush_START: { (*((typeof((( (e_j_integer) (*( (e_j_short*) (code_sofar+1) ) ) ) ))*) op_stk_top )) = (( (e_j_integer) (*( (e_j_short*) (code_sofar+1) ) ) ) ) ;
};
 {op_stk_top += ( sizeof( typeof((( (e_j_integer) (*( (e_j_short*) (code_sofar+1) ) ) ) )) )/ sizeof( typeof(op_stk_top) ) );
} e_CORE_sipush_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(sipush) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ldc :
 e_CORE_ldc_START: e_CORE_ldc_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ldc) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ldc_w :
 e_CORE_ldc_w_START: e_CORE_ldc_w_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ldc_w) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ldc2_w :
 e_CORE_ldc2_w_START: e_CORE_ldc2_w_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ldc2_w) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iload :
 e_CORE_iload_START: (*((typeof(e_j_integer)*) op_stk_top )) = ((*( ( typeof(e_j_integer)* ) ( locals + ( (e_j_integer) (*( (e_j_u_byte*) code_sofar ) ) ) ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_iload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iload) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lload :
 e_CORE_lload_START: (*((typeof(e_j_long)*) op_stk_top )) = ((*( ( typeof(e_j_long)* ) ( locals + ( (e_j_integer) (*( (e_j_u_byte*) code_sofar ) ) ) ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lload) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fload :
 e_CORE_fload_START: (*((typeof(e_j_float)*) op_stk_top )) = ((*( ( typeof(e_j_float)* ) ( locals + ( (e_j_integer) (*( (e_j_u_byte*) code_sofar ) ) ) ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fload) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dload :
 e_CORE_dload_START: (*((typeof(e_j_double)*) op_stk_top )) = ((*( ( typeof(e_j_double)* ) ( locals + ( (e_j_integer) (*( (e_j_u_byte*) code_sofar ) ) ) ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dload) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aload :
 e_CORE_aload_START: (*((typeof(e_j_refrence)*) op_stk_top )) = ((*( ( typeof(e_j_refrence)* ) ( locals + ( (e_j_integer) (*( (e_j_u_byte*) code_sofar ) ) ) ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_refrence) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_aload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(aload) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iload_0 :
 e_CORE_iload_0_START: (*((typeof(e_j_integer)*) op_stk_top )) = ((*( ( typeof(e_j_integer)* ) ( locals + 0 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_iload_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iload_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iload_1 :
 e_CORE_iload_1_START: (*((typeof(e_j_integer)*) op_stk_top )) = ((*( ( typeof(e_j_integer)* ) ( locals + 1 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_iload_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iload_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iload_2 :
 e_CORE_iload_2_START: (*((typeof(e_j_integer)*) op_stk_top )) = ((*( ( typeof(e_j_integer)* ) ( locals + 2 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_iload_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iload_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iload_3 :
 e_CORE_iload_3_START: (*((typeof(e_j_integer)*) op_stk_top )) = ((*( ( typeof(e_j_integer)* ) ( locals + 3 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_iload_3_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iload_3) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lload_0 :
 e_CORE_lload_0_START: (*((typeof(e_j_long)*) op_stk_top )) = ((*( ( typeof(e_j_long)* ) ( locals + 0 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lload_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lload_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_byte_t* ) code_sofar ];

e_label_lload_1 :
 e_CORE_lload_1_START: (*((typeof(e_j_long)*) op_stk_top )) = ((*( ( typeof(e_j_long)* ) ( locals + 1 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lload_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lload_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lload_2 :
 e_CORE_lload_2_START: (*((typeof(e_j_long)*) op_stk_top )) = ((*( ( typeof(e_j_long)* ) ( locals + 2 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lload_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lload_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lload_3 :
 e_CORE_lload_3_START: (*((typeof(e_j_long)*) op_stk_top )) = ((*( ( typeof(e_j_long)* ) ( locals + 3 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lload_3_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lload_3) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fload_0 :
 e_CORE_fload_0_START: (*((typeof(e_j_float)*) op_stk_top )) = ((*( ( typeof(e_j_float)* ) ( locals + 0 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fload_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fload_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fload_1 :
 e_CORE_fload_1_START: (*((typeof(e_j_float)*) op_stk_top )) = ((*( ( typeof(e_j_float)* ) ( locals + 1 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fload_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fload_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fload_2 :
 e_CORE_fload_2_START: (*((typeof(e_j_float)*) op_stk_top )) = ((*( ( typeof(e_j_float)* ) ( locals + 2 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fload_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fload_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fload_3 :
 e_CORE_fload_3_START: (*((typeof(e_j_float)*) op_stk_top )) = ((*( ( typeof(e_j_float)* ) ( locals + 3 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fload_3_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fload_3) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dload_0 :
 e_CORE_dload_0_START: (*((typeof(e_j_double)*) op_stk_top )) = ((*( ( typeof(e_j_double)* ) ( locals + 0 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dload_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dload_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dload_1 :
 e_CORE_dload_1_START: (*((typeof(e_j_double)*) op_stk_top )) = ((*( ( typeof(e_j_double)* ) ( locals + 1 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dload_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dload_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dload_2 :
 e_CORE_dload_2_START: (*((typeof(e_j_double)*) op_stk_top )) = ((*( ( typeof(e_j_double)* ) ( locals + 2 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dload_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dload_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dload_3 :
 e_CORE_dload_3_START: (*((typeof(e_j_double)*) op_stk_top )) = ((*( ( typeof(e_j_double)* ) ( locals + 3 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dload_3_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dload_3) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aload_0 :
 e_CORE_aload_0_START: (*((typeof(e_j_refrence)*) op_stk_top )) = ((*( ( typeof(e_j_refrence)* ) ( locals + 0 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_refrence) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_aload_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(aload_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aload_1 :
 e_CORE_aload_1_START: (*((typeof(e_j_refrence)*) op_stk_top )) = ((*( ( typeof(e_j_refrence)* ) ( locals + 1 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_refrence) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_aload_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(aload_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aload_2 :
 e_CORE_aload_2_START: (*((typeof(e_j_refrence)*) op_stk_top )) = ((*( ( typeof(e_j_refrence)* ) ( locals + 2 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_refrence) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_aload_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(aload_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aload_3 :
 e_CORE_aload_3_START: (*((typeof(e_j_refrence)*) op_stk_top )) = ((*( ( typeof(e_j_refrence)* ) ( locals + 3 ) ))) ;
 {op_stk_top += ( sizeof( typeof(e_j_refrence) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_aload_3_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(aload_3) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iaload :
 e_CORE_iaload_START: e_CORE_iaload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iaload) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_laload :
 e_CORE_laload_START: e_CORE_laload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(laload) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_faload :
 e_CORE_faload_START: e_CORE_faload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(faload) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_daload :
 e_CORE_daload_START: e_CORE_daload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(daload) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aaload :
 e_CORE_aaload_START: e_CORE_aaload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(aaload) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_baload :
 e_CORE_baload_START: e_CORE_baload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(baload) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_caload :
 e_CORE_caload_START: e_CORE_caload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(caload) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_saload :
 e_CORE_saload_START: e_CORE_saload_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(saload) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_istore :
 e_CORE_istore_START: ((*( ( typeof((*((typeof(e_j_integer)*) op_stk_top )))* ) ( locals + ( (e_j_integer) (*( (e_j_u_byte*) code_sofar ) ) ) ) ))) = (*((typeof(e_j_integer)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_istore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(istore) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lstore :
 e_CORE_lstore_START: ((*( ( typeof((*((typeof(e_j_long)*) op_stk_top )))* ) ( locals + ( (e_j_integer) (*( (e_j_u_byte*) code_sofar ) ) ) ) ))) = (*((typeof(e_j_long)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lstore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lstore) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fstore :
 e_CORE_fstore_START: ((*( ( typeof((*((typeof(e_j_float)*) op_stk_top )))* ) ( locals + ( (e_j_integer) (*( (e_j_u_byte*) code_sofar ) ) ) ) ))) = (*((typeof(e_j_float)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fstore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fstore) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dstore :
 e_CORE_dstore_START: ((*( ( typeof((*((typeof(e_j_double)*) op_stk_top )))* ) ( locals + ( (e_j_integer) (*( (e_j_u_byte*) code_sofar ) ) ) ) ))) = (*((typeof(e_j_double)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dstore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dstore) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_astore :
 e_CORE_astore_START: ((*( ( typeof((*((typeof(e_j_refrence)*) op_stk_top )))* ) ( locals + ( (e_j_integer) (*( (e_j_u_byte*) code_sofar ) ) ) ) ))) = (*((typeof(e_j_refrence)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_refrence) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_astore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(astore) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_istore_0 :
 e_CORE_istore_0_START: ((*( ( typeof((*((typeof(e_j_integer)*) op_stk_top )))* ) ( locals + 0 ) ))) = (*((typeof(e_j_integer)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_istore_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(istore_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_istore_1 :
 e_CORE_istore_1_START: ((*( ( typeof((*((typeof(e_j_integer)*) op_stk_top )))* ) ( locals + 1 ) ))) = (*((typeof(e_j_integer)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_istore_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(istore_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_istore_2 :
 e_CORE_istore_2_START: ((*( ( typeof((*((typeof(e_j_integer)*) op_stk_top )))* ) ( locals + 2 ) ))) = (*((typeof(e_j_integer)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_istore_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(istore_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_istore_3 :
 e_CORE_istore_3_START: ((*( ( typeof((*((typeof(e_j_integer)*) op_stk_top )))* ) ( locals + 3 ) ))) = (*((typeof(e_j_integer)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_istore_3_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(istore_3) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lstore_0 :
 e_CORE_lstore_0_START: ((*( ( typeof((*((typeof(e_j_long)*) op_stk_top )))* ) ( locals + 0 ) ))) = (*((typeof(e_j_long)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lstore_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lstore_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lstore_1 :
 e_CORE_lstore_1_START: ((*( ( typeof((*((typeof(e_j_long)*) op_stk_top )))* ) ( locals + 1 ) ))) = (*((typeof(e_j_long)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lstore_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lstore_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lstore_2 :
 e_CORE_lstore_2_START: ((*( ( typeof((*((typeof(e_j_long)*) op_stk_top )))* ) ( locals + 2 ) ))) = (*((typeof(e_j_long)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lstore_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lstore_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lstore_3 :
 e_CORE_lstore_3_START: ((*( ( typeof((*((typeof(e_j_long)*) op_stk_top )))* ) ( locals + 3 ) ))) = (*((typeof(e_j_long)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lstore_3_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lstore_3) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fstore_0 :
 e_CORE_fstore_0_START: ((*( ( typeof((*((typeof(e_j_float)*) op_stk_top )))* ) ( locals + 0 ) ))) = (*((typeof(e_j_float)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fstore_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fstore_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fstore_1 :
 e_CORE_fstore_1_START: ((*( ( typeof((*((typeof(e_j_float)*) op_stk_top )))* ) ( locals + 1 ) ))) = (*((typeof(e_j_float)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fstore_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fstore_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fstore_2 :
 e_CORE_fstore_2_START: ((*( ( typeof((*((typeof(e_j_float)*) op_stk_top )))* ) ( locals + 2 ) ))) = (*((typeof(e_j_float)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fstore_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fstore_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fstore_3 :
 e_CORE_fstore_3_START: ((*( ( typeof((*((typeof(e_j_float)*) op_stk_top )))* ) ( locals + 3 ) ))) = (*((typeof(e_j_float)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fstore_3_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fstore_3) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dstore_0 :
 e_CORE_dstore_0_START: ((*( ( typeof((*((typeof(e_j_double)*) op_stk_top )))* ) ( locals + 0 ) ))) = (*((typeof(e_j_double)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dstore_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dstore_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dstore_1 :
 e_CORE_dstore_1_START: ((*( ( typeof((*((typeof(e_j_double)*) op_stk_top )))* ) ( locals + 1 ) ))) = (*((typeof(e_j_double)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dstore_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dstore_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dstore_2 :
 e_CORE_dstore_2_START: ((*( ( typeof((*((typeof(e_j_double)*) op_stk_top )))* ) ( locals + 2 ) ))) = (*((typeof(e_j_double)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dstore_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dstore_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dstore_3 :
 e_CORE_dstore_3_START: ((*( ( typeof((*((typeof(e_j_double)*) op_stk_top )))* ) ( locals + 3 ) ))) = (*((typeof(e_j_double)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dstore_3_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dstore_3) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_astore_0 :
 e_CORE_astore_0_START: ((*( ( typeof((*((typeof(e_j_refrence)*) op_stk_top )))* ) ( locals + 0 ) ))) = (*((typeof(e_j_refrence)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_refrence) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_astore_0_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(astore_0) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_astore_1 :
 e_CORE_astore_1_START: ((*( ( typeof((*((typeof(e_j_refrence)*) op_stk_top )))* ) ( locals + 1 ) ))) = (*((typeof(e_j_refrence)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_refrence) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_astore_1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(astore_1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_astore_2 :
 e_CORE_astore_2_START: ((*( ( typeof((*((typeof(e_j_refrence)*) op_stk_top )))* ) ( locals + 2 ) ))) = (*((typeof(e_j_refrence)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_refrence) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_astore_2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(astore_2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_astore_3 :
 e_CORE_astore_3_START: ((*( ( typeof((*((typeof(e_j_refrence)*) op_stk_top )))* ) ( locals + 3 ) ))) = (*((typeof(e_j_refrence)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_refrence) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_astore_3_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(astore_3) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iastore :
 e_CORE_iastore_START: e_CORE_iastore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iastore) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lastore :
 e_CORE_lastore_START: e_CORE_lastore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lastore) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fastore :
 e_CORE_fastore_START: e_CORE_fastore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fastore) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dastore :
 e_CORE_dastore_START: e_CORE_dastore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dastore) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_aastore :
 e_CORE_aastore_START: e_CORE_aastore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(aastore) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_bastore :
 e_CORE_bastore_START: e_CORE_bastore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(bastore) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_castore :
 e_CORE_castore_START: e_CORE_castore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(castore) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_sastore :
 e_CORE_sastore_START: e_CORE_sastore_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(sastore) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_pop :
 e_CORE_pop_START: {op_stk_top -= ( sizeof( typeof(e_j_word) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_pop_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(pop) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_pop2 :
 e_CORE_pop2_START: {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_pop2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(pop2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup :
 e_CORE_dup_START: {op_stk_top += ( sizeof( typeof(e_j_word) )/ sizeof( typeof(op_stk_top) ) );
};
 (*((typeof(e_j_word)*) op_stk_top )) = (* ((e_j_word *) ( op_stk_top - 1 ) ));
 e_CORE_dup_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dup) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup_x1 :
 e_CORE_dup_x1_START: {op_stk_top += ( sizeof( typeof(e_j_word) )/ sizeof( typeof(op_stk_top) ) );
};
 (*((typeof(e_j_long)*) op_stk_top )) = (* ((e_j_long *) ( op_stk_top - 1 ) ));
 (* ((e_j_integer *) ( op_stk_top - 2 ) )) = (*((typeof(e_j_word)*) op_stk_top )) ;
 e_CORE_dup_x1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dup_x1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup_x2 :
 e_CORE_dup_x2_START: {op_stk_top += ( sizeof( typeof(e_j_word) )/ sizeof( typeof(op_stk_top) ) );
};
 (*((typeof(e_j_long_long)*) op_stk_top )) = (* ((e_j_long_long *) ( op_stk_top - 1 ) ));
 (* ((e_j_integer *) ( op_stk_top - 3 ) )) = (*((typeof(e_j_word)*) op_stk_top )) ;
 e_CORE_dup_x2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dup_x2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup2 :
 e_CORE_dup2_START: {op_stk_top += ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 (*((typeof(e_j_long)*) op_stk_top )) = (* ((e_j_long *) ( op_stk_top - 2 ) ));
 e_CORE_dup2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dup2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup2_x1 :
 e_CORE_dup2_x1_START: {op_stk_top += ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 (*((typeof(e_j_long_long)*) op_stk_top )) = (* ((e_j_long_long *) ( op_stk_top - 2 ) ));
 (* ((e_j_long *) ( op_stk_top - 3 ) )) = (*((typeof(e_j_long)*) op_stk_top )) ;
 e_CORE_dup2_x1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dup2_x1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dup2_x2 :
 e_CORE_dup2_x2_START: {op_stk_top += ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 (*((typeof(e_j_long_long)*) op_stk_top )) = (* ((e_j_long_long *) ( op_stk_top - 2 ) ));
 (* ((e_j_long *) ( op_stk_top - 4 ) )) = (*((typeof(e_j_long)*) op_stk_top )) ;
 e_CORE_dup2_x2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dup2_x2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_swap :
 e_CORE_swap_START: {auto e_j_word swap_lv_temp = (*((typeof(e_j_word)*) op_stk_top ));
 (*((typeof(e_j_word)*) op_stk_top )) = (* ((e_j_word *) ( op_stk_top - 1 ) )) ;
 (* ((e_j_word *) ( op_stk_top - 1 ) )) = swap_lv_temp;
} e_CORE_swap_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(swap) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iadd :
 e_CORE_iadd_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) += (*((typeof(e_j_integer)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_iadd_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iadd) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ladd :
 e_CORE_ladd_START: (* ((e_j_long *) ( op_stk_top - 1 ) )) += (*((typeof(e_j_long)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_ladd_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ladd) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fadd :
 e_CORE_fadd_START: (* ((e_j_float *) ( op_stk_top - 1 ) )) += (*((typeof(e_j_float)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fadd_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fadd) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dadd :
 e_CORE_dadd_START: (* ((e_j_double *) ( op_stk_top - 1 ) )) += (*((typeof(e_j_double)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dadd_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dadd) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_isub :
 e_CORE_isub_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_integer)*) op_stk_top )) - (* ((e_j_integer *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_isub_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(isub) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lsub :
 e_CORE_lsub_START: (* ((e_j_long *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_long)*) op_stk_top )) - (* ((e_j_long *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lsub_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lsub) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fsub :
 e_CORE_fsub_START: (* ((e_j_float *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_float)*) op_stk_top )) - (* ((e_j_float *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fsub_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fsub) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dsub :
 e_CORE_dsub_START: (* ((e_j_double *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_double)*) op_stk_top )) - (* ((e_j_double *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_dsub_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dsub) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_imul :
 e_CORE_imul_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) *= (*((typeof(e_j_integer)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_imul_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(imul) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lmul :
 e_CORE_lmul_START: e_CORE_lmul_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lmul) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fmul :
 e_CORE_fmul_START: e_CORE_fmul_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fmul) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dmul :
 e_CORE_dmul_START: e_CORE_dmul_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dmul) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_idiv :
 e_CORE_idiv_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_integer)*) op_stk_top )) / (* ((e_j_integer *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_idiv_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(idiv) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ldiv :
 e_CORE_ldiv_START: (* ((e_j_long *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_long)*) op_stk_top )) / (* ((e_j_long *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_ldiv_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ldiv) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fdiv :
 e_CORE_fdiv_START: (* ((e_j_float *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_float)*) op_stk_top )) / (* ((e_j_float *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_fdiv_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fdiv) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ddiv :
 e_CORE_ddiv_START: (* ((e_j_double *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_double)*) op_stk_top )) / (* ((e_j_double *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_ddiv_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ddiv) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_irem :
 e_CORE_irem_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_integer)*) op_stk_top )) % (* ((e_j_integer *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_irem_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(irem) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lrem :
 e_CORE_lrem_START: (* ((e_j_long *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_long)*) op_stk_top )) % (* ((e_j_long *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lrem_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lrem) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_frem :
 e_CORE_frem_START: (* ((e_j_float *) ( op_stk_top - 1 ) )) = fmodf((*((typeof(e_j_float)*) op_stk_top )) , (* ((e_j_float *) ( op_stk_top - 1 ) )));
 {op_stk_top -= ( sizeof( typeof(e_j_float) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_frem_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(frem) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_drem :
 e_CORE_drem_START: (* ((e_j_double *) ( op_stk_top - 1 ) )) = fmod( (*((typeof(e_j_double)*) op_stk_top )) , (* ((e_j_double *) ( op_stk_top - 1 ) )));
 {op_stk_top -= ( sizeof( typeof(e_j_double) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_drem_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(drem) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ineg :
 e_CORE_ineg_START: (*((typeof(e_j_integer)*) op_stk_top )) *= (e_j_integer) -1 ;
 e_CORE_ineg_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ineg) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lneg :
 e_CORE_lneg_START: (*((typeof(e_j_long)*) op_stk_top )) *= (e_j_long) -1 ;
 e_CORE_lneg_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lneg) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fneg :
 e_CORE_fneg_START: (*((typeof(e_j_float)*) op_stk_top )) *= (e_j_float) -1 ;
 e_CORE_fneg_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fneg) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dneg :
 e_CORE_dneg_START: (*((typeof(e_j_double)*) op_stk_top )) *= (e_j_double) -1 ;
 e_CORE_dneg_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dneg) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ishl :
 e_CORE_ishl_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_integer)*) op_stk_top )) << (0x1F & (* ((e_j_integer *) ( op_stk_top - 1 ) )));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_ishl_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ishl) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lshl :
 e_CORE_lshl_START: (* ((e_j_long *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_long)*) op_stk_top )) << (0x1F & (* ((e_j_long *) ( op_stk_top - 1 ) )));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lshl_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lshl) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ishr :
 e_CORE_ishr_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_integer)*) op_stk_top )) >> (0x1F & (* ((e_j_integer *) ( op_stk_top - 1 ) )));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_ishr_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ishr) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lshr :
 e_CORE_lshr_START: (* ((e_j_long *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_long)*) op_stk_top )) >> (0x1F & (* ((e_j_long *) ( op_stk_top - 1 ) )));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lshr_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lshr) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iushr :
 e_CORE_iushr_START: (* ((e_j_u_integer *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_u_integer)*) op_stk_top )) >> (0x1F && (* ((e_j_u_integer *) ( op_stk_top - 1 ) )));
 {op_stk_top -= ( sizeof( typeof(e_j_u_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_iushr_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iushr) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lushr :
 e_CORE_lushr_START: (* ((e_j_u_long *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_u_long)*) op_stk_top )) >> (0x1F & (* ((e_j_u_long *) ( op_stk_top - 1 ) )));
 {op_stk_top -= ( sizeof( typeof(e_j_u_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lushr_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lushr) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iand :
 e_CORE_iand_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_integer)*) op_stk_top )) & (* ((e_j_integer *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_iand_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iand) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_land :
 e_CORE_land_START: (* ((e_j_long *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_long)*) op_stk_top )) & (* ((e_j_long *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_land_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(land) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ior :
 e_CORE_ior_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_integer)*) op_stk_top )) | (* ((e_j_integer *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_ior_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ior) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lor :
 e_CORE_lor_START: (* ((e_j_long *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_long)*) op_stk_top )) | (* ((e_j_long *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lor_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lor) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ixor :
 e_CORE_ixor_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_integer)*) op_stk_top )) ^ (* ((e_j_integer *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_ixor_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ixor) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lxor :
 e_CORE_lxor_START: (* ((e_j_long *) ( op_stk_top - 1 ) )) = (*((typeof(e_j_long)*) op_stk_top )) ^ (* ((e_j_long *) ( op_stk_top - 1 ) ));
 {op_stk_top -= ( sizeof( typeof(e_j_long) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_lxor_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lxor) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_iinc :
 e_CORE_iinc_START: ((*( ( typeof(e_j_integer)* ) ( locals + (( (e_j_u_byte) (*( (e_j_u_byte*) (code_sofar + 1) ) ) )) ) ))) += ( (e_j_integer) (*( (e_j_byte*) (code_sofar + 2) ) ) ) ;
 e_CORE_iinc_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iinc) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2l :
 e_CORE_i2l_START: {op_stk_top += ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 (*((typeof(e_j_long)*) op_stk_top )) = (e_j_integer) (* ((e_j_integer *) ( op_stk_top - 1 ) ));
 e_CORE_i2l_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(i2l) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2f :
 e_CORE_i2f_START: {op_stk_top += ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 (*((typeof(e_j_float)*) op_stk_top )) = (e_j_integer) (* ((e_j_integer *) ( op_stk_top - 1 ) ));
 e_CORE_i2f_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(i2f) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2d :
 e_CORE_i2d_START: {op_stk_top += ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 (*((typeof(e_j_double)*) op_stk_top )) = (e_j_integer) (* ((e_j_integer *) ( op_stk_top - 1 ) ));
 e_CORE_i2d_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(i2d) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_l2i :
 e_CORE_l2i_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) = 0xFFFFFFFF & (*((typeof(e_j_long)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_l2i_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(l2i) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_l2f :
 e_CORE_l2f_START: (*((typeof(e_j_float)*) op_stk_top )) = (*((typeof(e_j_long)*) op_stk_top ));
 e_CORE_l2f_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(l2f) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_l2d :
 e_CORE_l2d_START: (*((typeof(e_j_double)*) op_stk_top )) = (*((typeof(e_j_long)*) op_stk_top ));
 e_CORE_l2d_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(l2d) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_f2i :
 e_CORE_f2i_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) = (e_j_integer) (*((typeof(e_j_float)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_f2i_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(f2i) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_f2l :
 e_CORE_f2l_START: (*((typeof(e_j_long)*) op_stk_top )) =(e_j_long) (*((typeof(e_j_float)*) op_stk_top ));
 e_CORE_f2l_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(f2l) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_f2d :
 e_CORE_f2d_START: (*((typeof(e_j_double)*) op_stk_top )) = (e_j_double) (*((typeof(e_j_float)*) op_stk_top ));
 e_CORE_f2d_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(f2d) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_d2i :
 e_CORE_d2i_START: (* ((e_j_integer *) ( op_stk_top - 1 ) )) = (e_j_integer) (*((typeof(e_j_double)*) op_stk_top ));
 {op_stk_top -= ( sizeof( typeof(e_j_integer) )/ sizeof( typeof(op_stk_top) ) );
};
 e_CORE_d2i_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(d2i) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_d2l :
 e_CORE_d2l_START: (*((typeof(e_j_long)*) op_stk_top )) =(e_j_long) (*((typeof(e_j_double)*) op_stk_top ));
 e_CORE_d2l_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(d2l) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_d2f :
 e_CORE_d2f_START: (*((typeof(e_j_float)*) op_stk_top )) =(e_j_float) (*((typeof(e_j_double)*) op_stk_top ));
 e_CORE_d2f_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(d2f) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2b :
 e_CORE_i2b_START: (*((typeof(e_j_integer)*) op_stk_top )) =((e_j_integer) (0xFF & (*((typeof(e_j_integer)*) op_stk_top ))));
 e_CORE_i2b_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(i2b) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2c :
 e_CORE_i2c_START: (*((typeof(e_j_integer)*) op_stk_top )) =((e_j_u_integer) (((e_j_u_integer) 0xFFFF) & (*((typeof(e_j_integer)*) op_stk_top ))));
 e_CORE_i2c_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(i2c) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_i2s :
 e_CORE_i2s_START: (*((typeof(e_j_integer)*) op_stk_top )) =((e_j_integer) (0xFFFF & (*((typeof(e_j_integer)*) op_stk_top ))));
 e_CORE_i2s_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(i2s) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_lcmp :
 e_CORE_lcmp_START: e_CORE_lcmp_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lcmp) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fcmpl :
 e_CORE_fcmpl_START: e_CORE_fcmpl_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fcmpl) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_fcmpg :
 e_CORE_fcmpg_START: e_CORE_fcmpg_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(fcmpg) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dcmpl :
 e_CORE_dcmpl_START: e_CORE_dcmpl_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dcmpl) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_dcmpg :
 e_CORE_dcmpg_START: e_CORE_dcmpg_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dcmpg) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ifeq :
 e_CORE_ifeq_START: e_CORE_ifeq_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ifeq) ;

e_label_ifne :
 e_CORE_ifne_START: e_CORE_ifne_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ifne) ;

e_label_iflt :
 e_CORE_iflt_START: e_CORE_iflt_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(iflt) ;

e_label_ifge :
 e_CORE_ifge_START: e_CORE_ifge_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ifge) ;

e_label_ifgt :
 e_CORE_ifgt_START: e_CORE_ifgt_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ifgt) ;

e_label_ifle :
 e_CORE_ifle_START: e_CORE_ifle_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ifle) ;

e_label_if_icmpeq :
 e_CORE_if_icmpeq_START: e_CORE_if_icmpeq_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(if_icmpeq) ;

e_label_if_icmpne :
 e_CORE_if_icmpne_START: e_CORE_if_icmpne_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(if_icmpne) ;

e_label_if_icmplt :
 e_CORE_if_icmplt_START: e_CORE_if_icmplt_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(if_icmplt) ;

e_label_if_icmpge :
 e_CORE_if_icmpge_START: e_CORE_if_icmpge_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(if_icmpge) ;

e_label_if_icmpgt :
 e_CORE_if_icmpgt_START: e_CORE_if_icmpgt_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(if_icmpgt) ;

e_label_if_icmple :
 e_CORE_if_icmple_START: e_CORE_if_icmple_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(if_icmple) ;

e_label_if_acmpeq :
 e_CORE_if_acmpeq_START: e_CORE_if_acmpeq_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(if_acmpeq) ;

e_label_if_acmpne :
 e_CORE_if_acmpne_START: e_CORE_if_acmpne_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(if_acmpne) ;

e_label_goto :
 e_CORE_goto_START: e_CORE_goto_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(goto) ;

e_label_jsr :
 e_CORE_jsr_START: e_CORE_jsr_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(jsr) ;

e_label_ret :
 e_CORE_ret_START: e_CORE_ret_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ret) ;

e_label_tableswitch :
 e_CORE_tableswitch_START: e_CORE_tableswitch_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(tableswitch) ;

e_label_lookupswitch :
 e_CORE_lookupswitch_START: e_CORE_lookupswitch_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lookupswitch) ;

e_label_ireturn :
 e_CORE_ireturn_START: e_CORE_ireturn_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ireturn) ;

e_label_lreturn :
 e_CORE_lreturn_START: e_CORE_lreturn_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(lreturn) ;

e_label_freturn :
 e_CORE_freturn_START: e_CORE_freturn_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(freturn) ;

e_label_dreturn :
 e_CORE_dreturn_START: e_CORE_dreturn_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(dreturn) ;

e_label_areturn :
 e_CORE_areturn_START: e_CORE_areturn_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(areturn) ;

e_label_return :
 e_CORE_return_START: e_CORE_return_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(return) ;

e_label_getstatic :
 e_CORE_getstatic_START: e_CORE_getstatic_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(getstatic) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_putstatic :
 e_CORE_putstatic_START: e_CORE_putstatic_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(putstatic) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_getfield :
 e_CORE_getfield_START: e_CORE_getfield_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(getfield) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_putfield :
 e_CORE_putfield_START: e_CORE_putfield_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(putfield) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_invokevirtual :
 e_CORE_invokevirtual_START: e_CORE_invokevirtual_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(invokevirtual) ;

e_label_invokespecial :
 e_CORE_invokespecial_START: e_CORE_invokespecial_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(invokespecial) ;

e_label_invokestatic :
 e_CORE_invokestatic_START: e_CORE_invokestatic_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(invokestatic) ;

e_label_invokeinterface :
 e_CORE_invokeinterface_START: e_CORE_invokeinterface_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(invokeinterface) ;

e_label_xxxunusedxxx1 :
 e_CORE_xxxunusedxxx1_START: e_CORE_xxxunusedxxx1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(xxxunusedxxx1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_new :
 e_CORE_new_START: e_CORE_new_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(new) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_newarray :
 e_CORE_newarray_START: e_CORE_newarray_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(newarray) ;

 code_sofar += 2 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_anewarray :
 e_CORE_anewarray_START: e_CORE_anewarray_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(anewarray) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_arraylength :
 e_CORE_arraylength_START: e_CORE_arraylength_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(arraylength) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_athrow :
 e_CORE_athrow_START: e_CORE_athrow_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(athrow) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_checkcast :
 e_CORE_checkcast_START: e_CORE_checkcast_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(checkcast) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_instanceof :
 e_CORE_instanceof_START: e_CORE_instanceof_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(instanceof) ;

 code_sofar += 3 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_monitorenter :
 e_CORE_monitorenter_START: e_CORE_monitorenter_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(monitorenter) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_monitorexit :
 e_CORE_monitorexit_START: e_CORE_monitorexit_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(monitorexit) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_wide :
 e_CORE_wide_START: e_CORE_wide_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(wide) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_multianewarray :
 e_CORE_multianewarray_START: e_CORE_multianewarray_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(multianewarray) ;

 code_sofar += 4 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_ifnull :
 e_CORE_ifnull_START: e_CORE_ifnull_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ifnull) ;

e_label_ifnonnull :
 e_CORE_ifnonnull_START: e_CORE_ifnonnull_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(ifnonnull) ;

e_label_goto_w :
 e_CORE_goto_w_START: e_CORE_goto_w_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(goto_w) ;

e_label_jsr_w :
 e_CORE_jsr_w_START: e_CORE_jsr_w_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(jsr_w) ;

e_label_breakpoint :
 e_CORE_breakpoint_START: e_CORE_breakpoint_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(breakpoint) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_impdep1 :
 e_CORE_impdep1_START: e_CORE_impdep1_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(impdep1) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

e_label_impdep2 :
 e_CORE_impdep2_START: e_CORE_impdep2_END: ;

 e_TRACE_ANNOUNCE_INSTRUCTION(impdep2) ;

 code_sofar += 1 ;

 goto *e_Instruction_Label_Lookup[ *( e_j_u_byte* ) code_sofar ];

FAULT:
e_TRACE_CLOSE( )
 return 0;

 }
