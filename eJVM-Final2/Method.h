#ifndef METHOD_H_
#define METHOD_H_

#include "typeDefs.h"
#include <string.h>
//#include "ByteCode.h"

class ClassData;
class ByteCode;
class ConstantPool;
class ByteCode;

class Method
{

private:
	u2 accessFlags;
    u2 nameIndex;
    u2 descriptorIndex;
    ClassData * myClass;
	ConstantPool * constantPool;
	ByteCode * byteCode;
	u2 *exceptionIndexTable;
	
public:
	Method(const byte inputFile[], int * inputPtr, ConstantPool * cp);	
	
	/**
	 * @return True if this method is the object initialization <init> method
	 */
	bool isInit();
	ByteCode * getByteCode();
	~Method();
	
	bool isPublic(void);
	bool isPrivate(void);
	bool isProtected(void);
	bool isStatic(void);
	bool isFinal(void);
	bool isSynchronized(void);
	bool isNative(void);
	bool isAbstract(void);
	bool isStrict(void);
	char * getName(void);
	char * getDesc(void);
	u2 getMaxLoacals();
	u2 getMaxStack();
	/* returns the class that declares the field */
	ClassData * getOwnerClassData(void);
	ConstantPool * getConstantPool(){return constantPool;}
	
};

#endif /*METHOD_H_*/
