#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_
typedef unsigned char byte;
//typedef signed char byte; // was changed from unsigned to signed for the jni consistency

typedef unsigned char u1;
typedef unsigned short int  u2;
typedef unsigned int u4;

//==================ACCESS FlAGS
#define ACC_PUBLIC   0x0001  // Declared public; may be accessed from outside its package. 
#define ACC_PRIVATE   0x0002  // Declared private; accessible only within the defining class. 
#define ACC_PROTECTED   0x0004 //  Declared protected; may be accessed within subclasses. 
#define ACC_STATIC   0x0008   //Declared static. 
#define ACC_FINAL   0x0010   //Declared final; may not be overridden. 
#define ACC_SYNCHRONIZED   0x0020 //  Declared synchronized; invocation is wrapped in a monitor lock. 
#define ACC_NATIVE   0x0100  // Declared native; implemented in a language other than Java. 
#define ACC_ABSTRACT   0x0400  // Declared abstract; no implementation is provided. 
#define ACC_STRICT   0x0800  //Declared strictfp; floating-point mode is FP-strict 



#endif //TYPEDEFS_H_
