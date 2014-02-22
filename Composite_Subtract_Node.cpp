
#if !defined (_Composite_Subtract_Node_CPP)
#define _Composite_Subtract_Node_CPP

template <typename T>
Composite_Subtract_Node<T>::Composite_Subtract_Node 
(Component_Node<T> *left,Component_Node<T> *right):
Composite_Binary_Node<T>(left,right){
}

template <typename T>
Composite_Subtract_Node<T>::~Composite_Subtract_Node(){
}
// Visitor.
template <typename T> void Composite_Subtract_Node<T>::accept (Visitor& v){
	v.visit(*this);
}
#endif /*_Composite_Subtract_Node_CPP*/
