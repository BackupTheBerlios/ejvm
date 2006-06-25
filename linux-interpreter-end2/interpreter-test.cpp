#include"ejvm.h"
#include"ExecutionEng.h" 
#include"ByteCode.h"

void test( void){
e_byte_t byte_code[]={e_VALUE_OF_iconst_0 , e_VALUE_OF_istore_1 , e_VALUE_OF_iconst_0 , e_VALUE_OF_istore_2 , e_VALUE_OF_iload_1 , e_VALUE_OF_iconst_1 , e_VALUE_OF_iadd , e_VALUE_OF_istore_2 , e_VALUE_OF_return };

ByteCode*  method = new	ByteCode;
method->nameIndex=0;
method->length=0;
method->maxStack=6;
method->maxLocals=6;
method->codeLength=6;
method->code=byte_code;
method->exceptionTable=NULL;
	
 ExecutionEng::e_exexute(NULL,method);

}
