#ifndef STK_OPERATIONS_H_
#define STK_OPERATIONS_H_




typedef struct gnrc_node_t{
		gnrc_node_t *	    nxt  ;   /*  next node 			   */ 
	 	void const*  		core ;   /*  element being stacke d*/
	 	}gnrc_node_t;



int push( gnrc_node_t ** list_ptr_ptr, void const* core);
int pop( gnrc_node_t ** list_ptr_ptr, void const** core);

#endif /*STK_OPERATIONS_H_*/

//
///*
// * Type Definintions
// * =================
// * 
// */
//
///*	generic stack node */
//typedef struct e_gnrc_stk_node_t e_gnrc_stk_node_t;
//struct e_gnrc_stk_node_t{
//	 	e_gnrc_stk_node_t *	    nxt  ;   /*  next node 			   */ 
//	 	void const*  			core ;   /*  element being stacke d*/
//	}; 
//	
//		
//		
//
///**
// * @param stk_ptr_ptr:pointer to the stack pointer
// * @param new_object : the new item to be stacked
// * @return: 0 on success
// * @return: 1 on failure
// * 
// */		
//int stk_pop (const e_gnrc_stk_node_t  **  stk_ptr_ptr, const void * new_object);
//
//
//
//
//
///**
// * @param stk_ptr_ptr:pointer to the stack pointer
// * @param stk_top_ptr_ptr :pointer to  to the place holder of the poped item
// * @return: 0 for success
// * @return: 1 on failure
// */	
//int stk_push(const e_gnrc_stk_node_t** const stk_ptr_ptr,const void** stk_top_ptr_ptr);
//
//
//


