#include"stk_operations.h"
#include"ejvm.h"




int push( gnrc_node_t ** list_ptr_ptr, void const* core){
	assert(list_ptr_ptr !=NULL);
	assert(core!= NULL);
	
	gnrc_node_t* temp = ( (gnrc_node_t*) malloc( sizeof(gnrc_node_t) ) );
	temp->core = core;
	temp->nxt = *list_ptr_ptr;
	*list_ptr_ptr = temp; 
	
	return 0;
}

int pop( gnrc_node_t ** list_ptr_ptr, void const** core){
	assert(list_ptr_ptr !=NULL);
	assert(core!= NULL);
	if ( * list_ptr_ptr ==NULL){
		*core = NULL;
		return 0;
	}
	*core=(*list_ptr_ptr)->core;
	gnrc_node_t* temp=*list_ptr_ptr;
	*list_ptr_ptr=(*list_ptr_ptr)->nxt;
	free(temp);
	return 0;
}





















/*


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
*/
