#ifndef LOG_H_
	#define LOG_H_


#define  e_STRINGIFY(x) #x 

#define  e_CAT(x,y) x##y

#define  e_XCAT(x,y) e_CAT( x , y)




#define e_TRACE_EXEC_ENG

#ifndef e_TRACE_EXEC_ENG

		#define e_TRACE_CREATE_TRACE_FILE(distinct);
		#define  e_TRACE_ANNOUNCE_INSTRUCTION(inst) ;
		#define  e_TRACE_ADD_TRACE_ENTRY(entry);		
		#define  e_TRACE_CLOSE() 	;

#else   //e_TRACE_EXEC_ENG is defined

	 	#define e_TRACE_CREATE_TRACE_FILE(distinct)\
	 		char* data;\
	 		char* data_start;\
	 		int d_fd;\
	 		d_fd = open("TRACE.txt",  O_WRONLY | O_CREAT | O_TRUNC);  \
	 		assert(d_fd != -1);\
	 		data_start =((char* ) malloc(1024*64));\
	 		data = data_start;

		#define  e_TRACE_ANNOUNCE_INSTRUCTION( inst ) \
			data += sprintf(data ,"\t Instruction: " e_STRINGIFY(inst) " is Executed \n" ) ;
		
		//#define  e_TRACE_ANNOUNCE( thing  ) 
//			data += sprintf(data ,thing) ;
	
		#define  e_TRACE_ADD_TRACE_ENTRY( entry ) \
				data += sprintf(data,e_STRINGIFY(( entry )"\n") ;
	
		#define  e_TRACE_CLOSE() \
				write(d_fd , data_start,(data - data_start));\
				free(data_start);\
				close(d_fd);




#define e_console_log_start(inst){\
  	printf("\n" e_STRINGIFY(inst) "\n");\
  	printf("\t before :\n\t\toperand stack:\n");\
		for(int i = (op_stk_top -op_stk) ; i >= 0  ;i --){\
			printf("\t\t\t [%d]=%-10d \t\t [%d]=%-32.4f \t\t [%d]=%lf \n",i,op_stk[i],i,((float*)op_stk)[i],i,*((double*)(op_stk+i)));\
		}\
		printf("\t\t local variables :\n");\
		for(int i = 0 ; i < method->maxLocals  ;i++){\
			printf("\t\t\t [%d]=%-10d \t\t [%d]=%-32.4f \t\t [%d]=%lf \n",i,locals[i],i,((float*)locals)[i],i,*((double*)(locals+i)));\
		}}	
		


 #define e_console_log_end {\
	printf("\t after :\n\t\toperand stack:\n");\
		for(int i = (op_stk_top -op_stk) ; i >= 0  ;i --){\
			printf("\t\t\t [%d]=%-10d \t\t [%d]=%-32.4f \t\t [%d]=%lf \n",i,op_stk[i],i,((float*)op_stk)[i],i,*((double*)(op_stk+i)));\
		}\
		printf("\t\t local variables :\n");\
		for(int i = 0 ; i < method->maxLocals  ;i++){\
			printf("\t\t\t [%d]=%-10d \t\t [%d]=%-32.4f \t\t [%d]=%lf \n",i,locals[i],i,((float*)locals)[i],i,*((double*)(locals+i)));\
		}}	
		
		
#endif //e_TRACE_EXEC_ENG

#endif //LOG_H_
