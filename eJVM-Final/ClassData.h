#ifndef CLASSDATA_H_
#define CLASSDATA_H_
#include"typeDefs.h"
#include <stdio.h>
class Method;
class Field;
class ConstantPool;
class Object;

class ClassData
{
private: 
	/* attributes */
 //ConstantPool * constantPool;
	u2 accessFlags;
	u2 thisClass; /* not ude till now */
	u2 superClass;
	u2 interfacesCount;
	u2 * interfaces;
	u2 fieldsCount;
	Field ** fields;
	u2 methodsCount;
	Method ** methods;
	u1 state;       	 	   		// if the class is loaded, linked, initialized, ...
	bool initialized;				// if the class is initialized
	u2 objectSize;  		  		// the size of an object of that class in the heap
	Method ** methodTable;  		// the method table
	u2 methodTableEntriesCount;		// number of entries in the method table

	/* methods */
	/* this function is called in preparation phase
	 * to construct the method table of this class */
	void createMethodTable(void);
	/* to be used in the above method */
	Method ** getMethodTable(void);
	/* this function is used to get the size of object */
	
	/* used in "canCastedTo" method */
	bool isImplement(ClassData * theInterface);

public:
ConstantPool * constantPool;
	ClassData(const char *name,const byte []);
/*****************ARRAY USAGE**********************/

	ClassData(const char*  arrayName);

/*****************ARRAY USAGE**********************/

	
	/**
	 * @return True if the class represented by this
	 * classData was initialized before
	 */
	bool isInitialized();

	/**
	 * initialize superclass and call clinit for this class, but not interfaces implemented by this class.
	 *
	 * psudoCode:
	 * super = getSuperClassData();
	 * if(super->isInitialized())
	 * 		super->initialize();
	 * get method block of clinit and the current constantPool
	 * call the executionEng
	 * 
	 */
	void initialize();
	/**
	 * 
	 * see the checkcast or instanceof instructions in the 
	 * VMSpecs for a detailed description of the 
	 * procedure used...
	 */
	bool canCastedTo(ClassData *classData);
		
	/**
	 * This method uses the methodTable (given the index from the given
	 * methodData) to get the actual methodData for invoking.
	 * If we don't implement the method table this method will 
	 * just call the method "lookupActualMethod()"
	 * which uses the procedure mentioned in the describtion of
	 * the invokeVirtual instruction in the specs to get the actual method
	 * 
	 * @param nonActualMethod The method returned from the
	 * constantPool. This method may not be the actual method
	 * to be invoked, like in invokevirtual, invokeinterface and
	 * invokespecial
	 * @return  The actual method to be invoked.
	 */
	Method *getActualMethod(Method* nonActualMethod);
	
	/**
	 * @return True if ACC_SUPER is set and false if ACC_SUPER is not set
	 */
	bool treatSuperMethodsSpecially();
	bool isInterface(void);
	bool isPublic(void);
	bool isFinal(void);
	bool isAbstract(void);
	
	/**
	 * @return True if classData represents a super class (not necessary 
	 * a direct super class) of this class (i.e if classData is ancestor of this class)
	 */
	bool isDescendentOf(ClassData* classData);
	
	ClassData* getSuperClassData();
	
	/**
	 * This method applies the alogrithm described in the specs sec 5.4.3.3 (Method resolution) 
	 * to find the method block identified by name and desc
	 */
	 
	Method* lookupMethod(const char *name,const char*desc);
	
	/**
	 * This method applies the alogrithm described in the specs sec 5.4.3.4 (Interface Method resolution) 
	 * to find the method block identified by name and desc
	 */
	Method* lookupInterfaceMethod(const char *name,const char *desc);
	
	/**
	 * This method applies the alogrithm described in the specs sec 5.4.3.2 (Field resolution) 
	 * to find the field block identified by name and desc
	 */
	Field * lookupField(const char *name,const  char*desc);
	
	void prepare(void);
	char * getFQName(void);
	u2 getObjectSize(void);
	
	
	/**@brief This method returns the java.lang.Class instance related to this Class Data
	 */
	 Object * getClassInstance(void){
	 	//To be implemented...
	 	return NULL;
	 }
	~ClassData();
};

#endif /*CLASSDATA_H_*/
