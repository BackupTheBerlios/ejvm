#ifndef FIELD_H_
#define FIELD_H_
#include "typeDefs.h"
#include <string.h>
//#include "ConstantPool.h"

class ClassData;
class ConstantPool;

class Field
{
private: 
	u2 accessFlags;
	u2 nameIndex;
	u2 descriptorIndex;
	u4 offset; /* u2 or u4 */
	ConstantPool * constantPool;
	ClassData * myClass;
	u2 constantValIndex;
	byte * staticValue;
	u1 size;

public:
	Field(const byte inputFile [], int * inputPtr, ConstantPool * cp);
	
	/**
	 * @return The byte index of the starting byte in the object representation. 
	 */
	u4 getOffset();
	
	/**
	 * @return size of the field in bytes 1,2,4 or 8
	 */
	u1 getSize(void);
	
	/**
	 * The Field should save a pntr to the owner class, i used
	 * it in putstatic instruction.
	 */
	
	/**
	 * @brief put the value of non-final static fields
	 * @param word1 is the less significant 4 bytes of the field value.
	 * @param word2 is the most significant 4 bytes of the field value.
	 */
	void putStaticValue(u4 word1,u4 word2);
	
	/**
	 * @brief reads the value of static fields
	 * We can use this function to read the final static value...
	 * @param word1 is the less significant 4 bytes of the field value.
	 * @param word2 is the most significant 4 bytes of the filed value.
	 */
	void getStaticValue(u4 &word1,u4 &word2);
	
	void setDefaultValue(void);
	void setInstanceVariableSize(void);
	void setOffset(u2 offset);
	bool isPublic(void);
	bool isPrivate(void);
	bool isProtected(void);
	bool isStatic(void);
	bool isFinal(void);
	bool isVolatile(void);
	bool isTransient(void);
	char * getName(void);
	char * getDesc(void);
	/* returns the class that declares the field */
	ClassData * getOwnerClass(void);
	
	virtual ~Field();
};

#endif /*FIELD_H_*/
