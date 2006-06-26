#ifndef STRINGLIB_H_
#define STRINGLIB_H_

#include "typeDefs.h"
#include "ConstantPool.h"
#include "Object.h"
#include "Method.h"
#include "Loader.h"
#include "Heap.h"
#include "ExecutionEng.h"
#include "Field.h"
Object* utf8ToArrayOfUnicodeChar (byte* utf8String);
Object* arrayOfUnicodeCharToString (Object* arrayObject);
char*   stringObjectToArrayOfCChars(Object* stringObject);
#endif /*STRINGLIB_H_*/
