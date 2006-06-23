#include"stk_operations.h"
#include"ejvm.h"




//Satck pop
int stk_pop(const e_gnrc_stk_node_t  **  stk_ptr_ptr, const void * new_object){
	
	assert(stk_ptr_ptr != NULL)	;
	assert(new_object  != NULL);
	
 	e_gnrc_stk_node_t *	new_stk_node;
	new_stk_node = (typeof(new_stk_node))malloc( sizeof( e_gnrc_stk_node_t ) );
	
	new_stk_node->core = new_object;
	new_stk_node->nxt = (typeof(new_stk_node->nxt)) *stk_ptr_ptr;
	
	return 0;
}

	
//Satck push	
int stk_push(const e_gnrc_stk_node_t** const stk_ptr_ptr,const void** stk_top_ptr_ptr){
		assert(stk_ptr_ptr != NULL)	;
		assert(stk_top_ptr_ptr != NULL);
		
		*stk_top_ptr_ptr = (*stk_ptr_ptr)->core;
		*stk_ptr_ptr = (*stk_ptr_ptr)->nxt;
		
		free(stk_ptr_ptr);
		return 0;
}
