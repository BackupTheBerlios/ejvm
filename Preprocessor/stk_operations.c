#include"interpereter.h" 
//Satck pop
int stk_pop(const void** const stk_ptr_ptr,void* stk_top){
	assert(stk_ptr_ptr != NULL)	;
	assert(stk_top != NULL);
	
	e_gnrc_stk_node_t*	new_stk;
	new_stk = malloc( sizeof( e_gnrc_stk_node_t ) );
	
	new_stk->core = stk_top;
	new_stk->nxt = (e_gnrc_stk_node_t*)*stk_ptr_ptr;
	return 0;
}

	
//Satck push	
int stk_push(const void** const stk_ptr_ptr,void* stk_top){



return 0;
}
