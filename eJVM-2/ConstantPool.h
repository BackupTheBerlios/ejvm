#ifndef CONSTANTPOOL_H_
#define CONSTANTPOOL_H_
#include "typeDefs.h"
//#include "ClassData.h"

class ClassData;
class Field;
class Method;

class ConstantPool
{
	
private: 
	/* private attributes */
	u2 CPCount; 				/* number of entries in the constant pool */
	byte ** entryTable; 		/* the table of entries */	
	void ** pointerTable;		/* the table of pointers */
	ClassData * myClass;		/* used in access permission */
	
	/* private methods */
	
	/* this method returns the name or type 
 	* of the NameAndType entry*/
	char * getNameAndType(u2 nameTypeIndex,int option);
	/* if the method contaons a pointer
	 * to its class, hen we will not need the first argument*/
	void accessPermissionField(Field * theField);
	void accessPermissionMethod(Method * theMethod);
	void accessPermissionClass(ClassData * theClass);
	
public:

	/* the constructor accepts the class file stream, number 
 	* of entries and the pointer of the current position of
 	* the input file */
	ConstantPool(byte inputFile [],int CPCount, int * inputPtr,
	ClassData * myClass);
	
	
	/**
	 * psudoCode:
	 * if (resolved) return the pointer to the classData stored in this entry;
	 * className ;//get the fully qualified class name from the constantPool entry .
	 * classData = loader->getClassData(className);
	 * write the classData into the entry...
	 * return classData;
	 */
	ClassData * getClassData(u2 index);
	
	
	/**
	 * psudoCode:
	 * if (resolved) return the pointer to the Field stored in this entry;
	 * classIndex = get the index of the field owner  (CONSTANT_Fieldref_info.class_index)
	 * classData = getClassData(classIndex);
	 * get fieldName and fieldDesc;
	 * field = classData->lookupField(filedName,fieldDesc);
	 * replace the resolved entry with  field
	 * return field;
	 */
	Field * getFieldData(u2 index);
	
	
	/**
	 * psudoCode:
	 * if (resolved) return the pointer to the Method stored in this entry;
	 * classIndex = get the index of the method owner (CONSTANT_Methodref_info.class_index)
	 * classData = getClassData(classIndex);
	 * get methodName and methodDesc;
	 * if (the current entry of constantpool is of type  CONSTANT_InterfaceMethodref_info)
	 * 		method = classData->lookupInterfaceMethod(methodName,methodDesc);
	 * else if (the current entry of constantpool is of type CONSTANT_Methodref_info)
	 * 		method = classData->lookupMethod(methodName,methodDesc);
	 * replace the resolved entry with  method
	 * return method;
	 */	
	Method * getMethodData(u2 index);
	
	
	/**
	 * This method used to read a value of 
	 * 1-int 
	 * 2-float //note the conversions (this part still need investigation)
	 * 3-reference to a String Object (literal).
	 */
	void getWord(u2 index,u4 &word);
 	
 	
 	/**
 	 * This method is used to read a value of 
 	 * 1- Double
 	 * 2- Long
 	 * @param word1 after return will hold the less significant word.
 	 * @param word2 after return will hold is the most significant word.
 	 */
	void get2Words(u2 index,u4 &word1,u4 &word2);
	virtual ~ConstantPool();
	void exception(void);
	
	/* this method resolves the UTF-8 entry 
	 * the UTF-8 entry is kept as it is because 
 	 * this funcion is called just once for each CPEntry */
	char * getString(u2 UTF8Index);
	ClassData * getOwnerClassData(void);
	
	/* get the name of the class at the
	 * entry #  classIndex. Usaully this class
	 * is the class that owns this constantPool */
	char * getClassName(u2 classIndex);
};

#endif /*CONSTANTPOOL_H_*/
