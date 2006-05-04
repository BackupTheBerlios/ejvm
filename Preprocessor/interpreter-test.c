#include"interpereter.h" 

void test( void){
	char byte_code[]={e_VALUE_OF_ladd,e_VALUE_OF_ladd,e_VALUE_OF_ladd};

	method_t  method = {6,6,2,byte_code};
	
 e_exexute(NULL,&method);

}
