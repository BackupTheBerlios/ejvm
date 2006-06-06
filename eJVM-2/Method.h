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
	
public:
	Method(byte inputFile[], int * inputPtr, ConstantPool * cp);	
	
	/**
	 * @return True if this method is the object initialization <init> method
	 */
	bool isInit();
	ByteCode * getByteCode();
	virtual ~Method();
	
	bool isPublic(void);
	bool isPrivate(void);
	bool isProtected(void);
	bool isStatic(void);
	bool isFinal(void);
	bool Method:: isSynchronized(void);
	bool isNative(void);
	bool isAbstract(void);
	bool isStrict(void);
	char * getName(void);
	char * getDesc(void);
	/* returns the class that declares the field */
	ClassData * getOwnerClassData(void);
	
};

#endif /*METHOD_H_*/
