#define eSTAR /**********************************************************/
#define eCOMMENT /*       Automatically-generated file. Do not edit!       */
eSTAR
eCOMMENT		
eSTAR


//#define E_INLINE_FUNCTIONS

/*
 * DELIMITER
 */
#ifndef E_INLINE_FUNCTIONS
	#define DELIMITER ;
#else
	#define DELIMITER \\

#endif

/*
 * RETURN_TYPE
 */
#ifndef E_INLINE_FUNCTIONS
	#define RETURN_TYPE void
#else
	#define RETURN_TYPE #define
#endif


RETURN_TYPE longmacro() {   DELIMITER
	int x=0; 			    DELIMITER
}
	
	
int main( void ){
	
	
	
	longmacro()    ;
	
	return 0;
}
