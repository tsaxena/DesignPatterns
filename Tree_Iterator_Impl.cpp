/* -*- C++ -*- */
#if !defined (_Tree_Iterator_Impl_CPP)
#define _Tree_Iterator_Impl_CPP

#include "Tree_Iterator_Impl.h"
#include <iostream>

// Size for the AQueue.
const size_t AQUEUE_SIZE = 80;

// Default ctor - needed for reference counting.
template <typename T>
Tree_Iterator_Impl<T>::Tree_Iterator_Impl ():
use_ (1){
}

template <typename T>
Tree_Iterator_Impl<T>::Tree_Iterator_Impl (Tree<T> &tree,bool flag):
use_ (1){
}


// This needs to be virtual so that subclasses are correctly destroyed.
template <typename T>
Tree_Iterator_Impl<T>::~Tree_Iterator_Impl (){
}

template <typename T> QUEUE *
Level_Order_Tree_Iterator_Impl<T>::make_strategy(std::string type){
	if (type=="LQueue")
		return new LQUEUE_ADAPTER(AQUEUE_SIZE);
	else if(type=="AQueue")
		return new AQUEUE_ADAPTER(AQUEUE_SIZE);
	else{
		std::string errMsg= "Unknown Queue type - ";
		errMsg+=type+"\n";
		throw Unknown_Q(errMsg);
	}
}

template <typename T> void
Level_Order_Tree_Iterator_Impl<T>::copy_queue(Queue<Tree<T> > *input){
	std::string queue_type = Options::instance()->queue_type();

	if (queue_type == "LQueue"){
		LQUEUE_ADAPTER* cur = dynamic_cast<LQUEUE_ADAPTER *> (queue_.get());
		LQUEUE_ADAPTER* inp = dynamic_cast<LQUEUE_ADAPTER *> (input);
		(*cur) = (*inp);
	}
	else if (queue_type == "AQueue"){
		AQUEUE_ADAPTER* cur = dynamic_cast<AQUEUE_ADAPTER * > (queue_.get());
		AQUEUE_ADAPTER* inp = dynamic_cast<AQUEUE_ADAPTER * > (input);
		(*cur) = (*inp);
	}
	else{
		std::string errMsg= "Unknown Queue type - ";
		errMsg+=queue_type+"\n";
		throw Unknown_Q(errMsg);
	}
}
// Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl():
queue_(make_strategy(Options::instance()->queue_type())){
}

// Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl (Tree<T> &tree,bool flag):
queue_(make_strategy(Options::instance()->queue_type())){
	if(!tree.is_null() && flag == true)
		queue_->enqueue(tree);
}

// Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl
(const Level_Order_Tree_Iterator_Impl<T>& rhs):
queue_(make_strategy(Options::instance()->queue_type())){
	copy_queue(rhs.queue_.get());
}

template <typename T>
Level_Order_Tree_Iterator_Impl<T>::~Level_Order_Tree_Iterator_Impl(void){
  //The queue is held in an auto_ptr which will call the destructor
  //when moving out of scope
}

template <typename T>
Tree<T> Level_Order_Tree_Iterator_Impl<T>::operator* (void){
	return queue_->front();
}

template <typename T>
const Tree<T> Level_Order_Tree_Iterator_Impl<T>::operator* (void) const{
	return queue_->front();
}

template <typename T>
Level_Order_Tree_Iterator_Impl<T>& 
Level_Order_Tree_Iterator_Impl<T>::operator++ (void){
	Tree<T> node=queue_->front();
	queue_->dequeue();
	if(!node.left().is_null())
		queue_->enqueue(node.left());
	if(!node.right().is_null())
		queue_->enqueue(node.right());
	return *this;
}

/// Equality operator
template <typename T>
bool Level_Order_Tree_Iterator_Impl<T>::operator==
(const Tree_Iterator_Impl<T> &rhs) const{
	const Level_Order_Tree_Iterator_Impl<T> *lptr=
				dynamic_cast<const Level_Order_Tree_Iterator_Impl<T> *> (&rhs);
	if(lptr!=0){
		return 	(queue_->size()== lptr->queue_->size()) &&
			(queue_->size()== 0 || queue_->front() == (lptr->queue_->front()));
							// tree's equality checks
	}						// for address of two nodes
	return false;
}

/// Nonequality operator
template <typename T>
bool Level_Order_Tree_Iterator_Impl<T>::operator!=
(const Tree_Iterator_Impl<T> &rhs) const{
  return !((*this) == rhs);//use the operator==
}

//clone for post increment in the bridge class
template <typename T>
Level_Order_Tree_Iterator_Impl<T>* 
Level_Order_Tree_Iterator_Impl<T>::clone(void){
	return (new Level_Order_Tree_Iterator_Impl<T>(*this));
}

// Ctor
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::Pre_Order_Tree_Iterator_Impl():
stack_(){
}

// Ctor
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::Pre_Order_Tree_Iterator_Impl
(Tree<T> &tree, bool flag):
stack_(){
	if(!tree.is_null() && flag == true)
		stack_.push(tree);
}

// Ctor
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::Pre_Order_Tree_Iterator_Impl(
	const Pre_Order_Tree_Iterator_Impl<T>& rhs):
stack_(rhs.stack_){
}

template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::~Pre_Order_Tree_Iterator_Impl(void){
}

template <typename T>
Tree<T> Pre_Order_Tree_Iterator_Impl<T>::operator* (void){
	return stack_.top();
}

template <typename T>
const Tree<T> Pre_Order_Tree_Iterator_Impl<T>::operator* (void) const{
	return stack_.top();
}

template <typename T>
Pre_Order_Tree_Iterator_Impl<T>& 
Pre_Order_Tree_Iterator_Impl<T>::operator++ (void){
	Tree<T> node=stack_.top();
	stack_.pop();
	if (!(node.right().is_null()))
		stack_.push(node.right());
	if (!(node.left().is_null()))
		stack_.push(node.left());
	return *this;
}

/// Equality operator
template <typename T>
bool Pre_Order_Tree_Iterator_Impl<T>::operator== 
(const Tree_Iterator_Impl<T> &rhs) const{
	const Pre_Order_Tree_Iterator_Impl<T> *lptr=
				dynamic_cast<const Pre_Order_Tree_Iterator_Impl<T> *> (&rhs);
	if(lptr!=0){
		return 	(stack_.size()== lptr->stack_.size()) &&
					(stack_.size()== 0 || stack_.top() == (lptr->stack_.top()));
							// tree's equality checks
	}						// for address of two nodes
	return false;
}

/// Nonequality operator
template <typename T>
bool Pre_Order_Tree_Iterator_Impl<T>::operator!= 
(const Tree_Iterator_Impl<T> &rhs) const{
	return !((*this) == rhs);//use the operator==
}

//clone for post increment in the bridge class
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>* 
Pre_Order_Tree_Iterator_Impl<T>::clone(void){
	return (new Pre_Order_Tree_Iterator_Impl<T>(*this));
}

// Ctor
template <typename T>
Post_Order_Tree_Iterator_Impl<T>::Post_Order_Tree_Iterator_Impl():
dummy_(),
cur_(dummy_){
}

// Ctor
template <typename T>
Post_Order_Tree_Iterator_Impl<T>::Post_Order_Tree_Iterator_Impl
(Tree<T> &tree, bool flag):
dummy_(),
cur_(dummy_){//the current node is assigned the  dummy node
	if (!tree.is_null() && flag == true){
		populateStack(tree);
		cur_ = stack_.top();
	}
}

// Ctor
template <typename T>
Post_Order_Tree_Iterator_Impl<T>::Post_Order_Tree_Iterator_Impl(
const Post_Order_Tree_Iterator_Impl<T>& rhs):
dummy_(),
cur_(dummy_),//the current node is assigned the  dummy node
stack_(rhs.stack_){
	if(!stack_.empty())
		cur_ = stack_.top();//use the newly defined operator=
}

template <typename T>
Post_Order_Tree_Iterator_Impl<T>::~Post_Order_Tree_Iterator_Impl(void){
}

template <typename T>
Tree<T> Post_Order_Tree_Iterator_Impl<T>::operator* (void){
  //1) cur is used here to respect the compiler warning of returning 
  // temporary object when queue->front was returned
  //2) This makes it simple to return cur which contains either
  // stack_.top or the dummy node based on the circumstances
  return (cur_);//return the content of cur
}

template <typename T>
const Tree<T> Post_Order_Tree_Iterator_Impl<T>::operator* (void) const
{
  //1) cur is used here to respect the compiler warning of returning 
  // temporary object when queue->front was returned
  //2) This makes it simple to return cur which contains either
  // stack_.top or the dummy node based on the circumstances
  return (cur_);//return the content of cur
}

template <typename T>
Post_Order_Tree_Iterator_Impl<T>& 
Post_Order_Tree_Iterator_Impl<T>::operator++ (void){
	//makes sense to perform anything only when the stack is not empty
	Tree<T> root = stack_.top();//get the top of the queue
	//check if the left and right nodes of the top node
	// are not null. If not, enqueue them
	stack_.pop();//remove the top element
	//set the cur entity based on the current state of the queue
	if (!stack_.empty())
	  cur_ = stack_.top();
	else
		  cur_ = dummy_;
  return (*this);
}

/// Equality operator
template <typename T> bool Post_Order_Tree_Iterator_Impl<T>::operator== 
(const Tree_Iterator_Impl<T> &rhs) const{
	//dynamically cast the rhs to PreOrder_Tree_Iterator
	 const Post_Order_Tree_Iterator_Impl<T>* temp =
					dynamic_cast<const Post_Order_Tree_Iterator_Impl<T>*>(&rhs);

	// cur is being compared here just for consistency with the rest of the
	// code. It is equivalent to comparing stack_.top when the stack's 
	// are not empty.
	// when either queue is empty, the above method won't work and additional
	// checks would be required for this.
	// using cur simplifies the code here.
	if(temp)//if the casting is valid{
		return (cur_==temp->cur_); // compare the two cur entries
		// which is equal to comparing the two
		// root node pointers
	return false; 
}

/// Nonequality operator
template <typename T> bool Post_Order_Tree_Iterator_Impl<T>::operator!= 
(const Tree_Iterator_Impl<T> &rhs) const{
	return !((*this) == rhs);//use the operator==
}

//clone for post increment in the bridge class
template <typename T> Post_Order_Tree_Iterator_Impl<T>* 
Post_Order_Tree_Iterator_Impl<T>::clone(void){
	return (new Post_Order_Tree_Iterator_Impl<T>(*this));
}

template <typename T> void 
Post_Order_Tree_Iterator_Impl<T>::populateStack(Tree<T> tree){
	stack_.push(tree);
	if (!tree.right().is_null())
		populateStack(tree.right());
	if (!tree.left().is_null())
		populateStack(tree.left());
}

#endif /*_Tree_Iterator_Impl_CPP */
