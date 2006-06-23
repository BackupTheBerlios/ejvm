#ifndef INST_H_
#define INST_H_

#define NOP                         0
#define ACONST_NULL                 1
#define ICONST_M1                   2
#define ICONST_0                    3
#define ICONST_1                    4
#define ICONST_2                    5
#define ICONST_3                    6
#define ICONST_4                    7
#define ICONST_5                    8
#define LCONST_0                    9
#define LCONST_1                    10
#define FCONST_0                    11
#define FCONST_1                    12
#define FCONST_2                    13
#define DCONST_0                    14
#define DCONST_1                    15
#define BIPUSH                      16
#define SIPUSH                      17
#define LDC                         18
#define LDC_W                       19
#define LDC2_W                      20
#define ILOAD                       21
#define LLOAD                       22
#define FLOAD                       23
#define DLOAD                       24
#define ALOAD                       25
#define ILOAD_0                     26
#define ILOAD_1                     27
#define ILOAD_2                     28
#define ILOAD_3                     29
#define LLOAD_0                     30
#define LLOAD_1                     31
#define LLOAD_2                     32
#define LLOAD_3                     33
#define FLOAD_0                     34
#define FLOAD_1                     35
#define FLOAD_2                     36
#define FLOAD_3                     37
#define DLOAD_0                     38
#define DLOAD_1                     39
#define DLOAD_2                     40
#define DLOAD_3                     41
#define ALOAD_0                     42
#define ALOAD_1                     43
#define ALOAD_2                     44
#define ALOAD_3                     45
#define IALOAD                      46
#define LALOAD                      47
#define FALOAD                      48
#define DALOAD                      49
#define AALOAD                      50
#define BALOAD                      51
#define CALOAD                      52
#define SALOAD                      53
#define ISTORE                      54
#define LSTORE                      55
#define FSTORE                      56
#define DSTORE                      57
#define ASTORE                      58
#define ISTORE_0                    59
#define ISTORE_1                    60
#define ISTORE_2                    61
#define ISTORE_3                    62
#define LSTORE_0                    63
#define LSTORE_1                    64
#define LSTORE_2                    65
#define LSTORE_3                    66
#define FSTORE_0                    67
#define FSTORE_1                    68
#define FSTORE_2                    69
#define FSTORE_3                    70
#define DSTORE_0                    71
#define DSTORE_1                    72
#define DSTORE_2                    73
#define DSTORE_3                    74
#define ASTORE_0                    75
#define ASTORE_1                    76
#define ASTORE_2                    77
#define ASTORE_3                    78
#define IASTORE                     79
#define LASTORE                     80
#define FASTORE                     81
#define DASTORE                     82
#define AASTORE                     83
#define BASTORE                     84
#define CASTORE                     85
#define SASTORE                     86
#define POP                         87
#define POP2                        88
#define DUP                         89
#define DUP_X1                      90
#define DUP_X2                      91
#define DUP2                        92
#define DUP2_X1                     93
#define DUP2_X2                     94
#define SWAP                        95
#define IADD                        96

#define FADD						 98
#define DADD						 99

#define ISUB						100

#define IMUL						104
#define LMUL						105

#define IDIV						108

#define FDIV						110

#define IF_ICMPNE					160

#define IF_ICMPGE					162

#define GOTO						167

#define IRETURN					172

#define RETURN                     177
#define GETSTATIC					178
#define PUTSTATIC					179
#define GETFIELD					180 
#define PUTFIELD					181
#define INVOKEVIRTUAL              182
#define INVOKESPECIAL              183
#define INVOKESTATIC               184
#define INVOKEINTERFACE			185


#define NEW						187
#define NEWARRAY					188






#endif /*INST_H_*/
