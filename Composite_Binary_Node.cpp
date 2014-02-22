/* -*- C++ -*- */
#if !defined (_Composite_Binary_Node_CPP)
#define _Composite_Binary_Node_CPP


template <typename T>
Composite_Binary_Node<T>::Composite_Binary_Node 
(Component_Node<T> *left,Component_Node<T> *right):
Composite_Unary_Node<T>(right),
left_(left){
}

template <typename T>
Composite_Binary_Node<T>::~Composite_Binary_Node(){
}


// Return the left child.
template <typename T> Component_Node<T> *
Composite_Binary_Node<T>::left (void) const{
	return left_.get();
}

#endif /*_Composite__Binary_Node_CPP*/
