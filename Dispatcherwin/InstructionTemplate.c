#include"ejvm.h"


void inst_name (void){
/* Nothing goes here */

ejvm_inst_name_start:
/* Start writing here */
PC=0;

ejvm_inst_name_core_start:	
/* Core goes here {nothing else} */
ejvm_inst_name_core_end:


ejvm_inst_name_excephandling_start:
/* Start exception handling here */
ejvm_inst_name_excephandling_end:


ejvm_inst_name_Housekeeping_start:
/* Start Housekeeping here */
ejvm_inst_name_Housekeeping_end:0;

ejvm_inst_name_end:

return;
}

