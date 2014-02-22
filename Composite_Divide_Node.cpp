#if !defined (_Composite_Divide_Node_CPP)
#define _Composite_Divide_Node_CPP

template <typename T>
Composite_Divide_Node<T>::Composite_Divide_Node 
(Component_Node<T> *left,Component_Node<T> *right):
Composite_Binary_Node<T>(left,right){
}

template <typename T>
Composite_Divide_Node<T>::~Composite_Divide_Node(){
}

// Visitor.
template <typename T> void Composite_Divide_Node<T>::accept (Visitor& v){
	v.visit(*this);
}
#endif /*_Composite_Divide_Node_CPP*/
