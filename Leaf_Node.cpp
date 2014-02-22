/* -*- C++ -*- */
#if !defined (_Leaf_Node_CPP)
#define _Leaf_Node_CPP

template <typename T>
Leaf_Node<T>::Leaf_Node (const T &item):
item_(item){
}

template <typename T>
Leaf_Node<T>::~Leaf_Node(){
}

// Return the item in the node.
template <typename T> const T & Leaf_Node<T>::item (void) const{
	return item_;
}

// Visitor.
template <typename T> void Leaf_Node<T>::accept(Visitor& v){
	v.visit(*this);
}


#endif /*_Leaf_Node_CPP*/
