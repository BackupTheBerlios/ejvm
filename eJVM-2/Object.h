#ifndef OBJECT_H_
#define OBJECT_H_

#include"typeDefs.h"
class ClassData;
class Field;

class Object
{
public:
	Object();
	/**@brief update the value of an instance variable at byte offset = offset.
	 * @param field the field block from which the object will know the required data to retrieve the value.
	 * @param word1 is the less significant 4 bytes of the field value.
	 * @param word2 is the most significant 4 bytes of the filed value.
	 */
	void putField(Field * field, u4 word1, u4 word2);
	
	/**@brief reads the value of an instance variable at byte offset = offset.
	 * @param field the field block from which the object will know the required data to retrieve the value.
	 * @param word1 after return will hold the less significant 4 bytes of the field value.
	 * @param word2 after return will hold is the most significant 4 bytes of the filed value.
	 */
	void getField(Field * field, u4 &word1, u4 &word2);
	/**
	 * @return pointer to the ClassData from which this Object was inistantiated.
	 */
	ClassData * getClassData();
	virtual ~Object();
};

#endif /*OBJECT_H_*/
