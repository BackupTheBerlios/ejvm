#ifndef STRINGLIB_H_
#define STRINGLIB_H_

#include "typeDefs.h"
#include "ConstantPool.h"
#include "Object.h"
#include "Method.h"
#include "Loader.h"
Object* utf8ToArrayOfUnicodeChar (byte* utf8String);
Object* arrayOfUnicodeCharToString (Object* arrayObject);
#endif /*STRINGLIB_H_*/