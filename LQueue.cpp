/***************************************
Class: CS251
Assignment Number: 3
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_LQUEUE_CPP)
#define _LQUEUE_CPP

#include "LQueue.h"
#include <algorithm>
#include <cstdio>
/* static */
template <typename T> LQueue_Node<T> *
LQueue_Node<T>::free_list_ = 0;

// Allocate a new <LQueue_Node>, trying first from the
// <free_list_> and if that's empty try from the global <::operator
// new>.

template <typename T>
void * LQueue_Node<T>::operator new (size_t){
	if (free_list_ != 0){
		LQueue_Node<T> *tempNode = free_list_;
		LQueue_Node<T>::free_list_ = LQueue_Node<T>::free_list_->next_;
		return tempNode;
	}
	return ::operator new(sizeof(LQueue_Node<T>));
}

// Return <ptr> to the <free_list_>.

template <typename T>
void LQueue_Node<T>::operator delete (void *ptr){
	if (ptr!=0){
		LQueue_Node<T> *tempNode = static_cast<LQueue_Node<T> *>(ptr);
		tempNode->next_=LQueue_Node<T>::free_list_;
		LQueue_Node<T>::free_list_ = tempNode;
	}
}
// Returns all dynamic memory on the free list to the free store.

template <typename T>
void LQueue_Node<T>::free_list_release (void){
	while(LQueue_Node<T>::free_list_){
		LQueue_Node<T> *nextFree_list = free_list_->next_;
		::operator delete(free_list_);
		free_list_=nextFree_list;
	}
}

// Preallocate <n> <LQueue_Nodes> and store them on the
// <free_list_>.

template <typename T>
void LQueue_Node<T>::free_list_allocate (size_t n){
	for (size_t nodeNo = 0 ; nodeNo<n ; ++nodeNo){
		 LQueue_Node<T> *intrNode =
		(LQueue_Node<T> *)::operator new(sizeof(LQueue_Node<T>));
		intrNode->next_=free_list_;
		free_list_=intrNode;
	}
}

/*template <typename T>
LQueue_Node<T>::LQueue_Node (	const T &item,
										LQueue_Node<T> *next,
										LQueue_Node<T> *prev):
item_ (item),
next_ (next),
prev_ (prev){
}*/
//(tail_->next_,tail_)
template <typename T>
LQueue_Node<T>::LQueue_Node (LQueue_Node<T> *next,LQueue_Node<T> *prev):
next_ (next),prev_ (prev){
	next_->prev_=this;
	prev_->next_=this;
}

// this is helpful to implement the dummy node in a concise way.
template <typename T>
LQueue_Node<T>::LQueue_Node (void):
next_ (0),prev_ (0){
	next_=this;
	prev_=this;
}

template <typename T>
LQueue_Node<T>::~LQueue_Node (void){
	next_->prev_=prev_;
	prev_->next_=next_;
}

// Returns the current size.
template<typename T, typename LQUEUE_NODE> size_t 
LQueue<T, LQUEUE_NODE>::size (void) const{
  return count_;
}

// Constructor.

template<typename T, typename LQUEUE_NODE>
LQueue<T, LQUEUE_NODE>::LQueue (size_t size_hint):
tail_ (0),count_ (0){
	LQueue_Node<T>::free_list_allocate(size_hint);
	tail_=new LQUEUE_NODE();
}

template <typename T, typename LQUEUE_NODE>
void LQueue<T, LQUEUE_NODE>::swap (LQueue<T, LQUEUE_NODE> &new_queue){
	std::swap(tail_,new_queue.tail_);
	std::swap(new_queue.count_,count_);
}

// Copy constructor.
template<typename T, typename LQUEUE_NODE> struct copyQ {
	copyQ (LQueue<T, LQUEUE_NODE> &copy): copy_(copy) {}
	void operator() (const T x) {
		copy_.enqueue(x);
	}
	LQueue<T, LQUEUE_NODE> &copy_;
};

template<typename T, typename LQUEUE_NODE>
LQueue<T, LQUEUE_NODE>::LQueue (const LQueue<T, LQUEUE_NODE> &rhs):
tail_ (0),count_ (0){
	LQueue<T, LQUEUE_NODE> tempQ;
	std::for_each(rhs.begin(),rhs.end(),copyQ<T,LQUEUE_NODE>(tempQ));
	swap(tempQ);
}

// Assignment operator.
template<typename T, typename LQUEUE_NODE> LQueue<T, LQUEUE_NODE> &
LQueue<T, LQUEUE_NODE>::operator= (const LQueue<T, LQUEUE_NODE> &rhs) {
	if(this != &rhs){
		LQueue<T, LQUEUE_NODE> tempQ(rhs);
		swap(tempQ);
	}
	return *this;
}

// Perform actions needed when queue goes out of scope.

template<typename T, typename LQUEUE_NODE>
LQueue<T, LQUEUE_NODE>::~LQueue (void){
	while(!is_empty())
		dequeue_i();
	delete tail_;
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.
template<typename T, typename LQUEUE_NODE> bool 
LQueue<T, LQUEUE_NODE>::operator== (const LQueue<T, LQUEUE_NODE> &rhs) const{
	return count_ == rhs.count_ && std::equal(begin(),end(),rhs.begin());
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.

template<typename T, typename LQUEUE_NODE> bool 
LQueue<T, LQUEUE_NODE>::operator!= (const LQueue<T, LQUEUE_NODE> &rhs) const{
  return !(*this == rhs);
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.

template<typename T, typename LQUEUE_NODE>
void LQueue<T, LQUEUE_NODE>::enqueue (const T &new_item){
	try{
		tail_->item_ = new_item;
		tail_=new LQUEUE_NODE(tail_->next_,tail_);
		++count_;
	}
	catch(std::bad_alloc){
		throw Overflow();
	}
}

// Remove the front item on the queue.  Throws the <Underflow>
// exception if the queue is empty.

template<typename T, typename LQUEUE_NODE>
void LQueue<T, LQUEUE_NODE>::dequeue (void){
	if(is_empty())
		throw Underflow();
	dequeue_i();
}

template<typename T, typename LQUEUE_NODE>
void LQueue<T, LQUEUE_NODE>::dequeue_i (void){
	delete tail_->next_;
	count_--;
}

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 

template<typename T, typename LQUEUE_NODE>
T LQueue<T, LQUEUE_NODE>::front (void) const{
  if(is_empty())
	  throw Underflow();
  return tail_->next_->item_;
}

// Returns true if the queue is empty, otherwise returns false.

template<typename T, typename LQUEUE_NODE>
bool LQueue<T, LQUEUE_NODE>::is_empty (void) const {
	return count_==0;
}

// Returns true if the queue is full, otherwise returns false.

template<typename T, typename LQUEUE_NODE> bool
LQueue<T, LQUEUE_NODE>::is_full (void) const {
	return false;
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::iterator
LQueue<T, LQUEUE_NODE>::begin (void){
	return LQueue_Iterator<T,LQUEUE_NODE>(tail_->next_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::iterator
LQueue<T, LQUEUE_NODE>::end (void){
	return LQueue_Iterator<T,LQUEUE_NODE>(tail_);
}

// Get an iterator to the begining of the queue
template <typename T,typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_iterator
LQueue<T, LQUEUE_NODE>::begin (void) const{
	return Const_LQueue_Iterator<T,LQUEUE_NODE>(tail_->next_);
}

// Get an iterator pointing past the end of the queue
template <typename T,typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_iterator
LQueue<T, LQUEUE_NODE>::end (void) const{
	return Const_LQueue_Iterator<T,LQUEUE_NODE>(tail_);
}

// Get an iterator to the end of the queue
template <typename T,typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::reverse_iterator
LQueue<T, LQUEUE_NODE>::rbegin (void){
	return LQueue_Reverse_Iterator<T,LQUEUE_NODE>(tail_->prev_);
}

// Get an iterator pointing to the beginning of the queue
template <typename T,typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::reverse_iterator
LQueue<T, LQUEUE_NODE>::rend (void){
	return LQueue_Reverse_Iterator<T,LQUEUE_NODE>(tail_);
}

// Get an iterator to the end of the queue
template <typename T,typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_reverse_iterator
LQueue<T, LQUEUE_NODE>::rbegin (void) const{
	return Const_LQueue_Reverse_Iterator<T,LQUEUE_NODE>(tail_->prev_);
}

// Get an iterator pointing to the beginning of the queue
template <typename T,typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_reverse_iterator
LQueue<T, LQUEUE_NODE>::rend (void) const{
	return Const_LQueue_Reverse_Iterator<T,LQUEUE_NODE>(tail_);
}

template <typename T,typename LQUEUE_NODE>
T & LQueue_Iterator<T, LQUEUE_NODE>::operator* (void){
	return pos_->item_;
}

template <typename T,typename LQUEUE_NODE>
const T & LQueue_Iterator<T, LQUEUE_NODE>::operator* (void) const{
	return pos_->item_;
}

template <typename T,typename LQUEUE_NODE>
LQueue_Iterator<T, LQUEUE_NODE> & LQueue_Iterator<T, LQUEUE_NODE>::operator++ (void) {
	pos_=pos_->next_;
	return *this;
}

// Post-increment.
template <typename T,typename LQUEUE_NODE>
LQueue_Iterator<T, LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE>::operator++ (int){
	LQueue_Iterator<T, LQUEUE_NODE> dummy = *this;
	++*this;
	return dummy;
}

template <typename T,typename LQUEUE_NODE>
LQueue_Iterator<T, LQUEUE_NODE> & LQueue_Iterator<T, LQUEUE_NODE>::operator-- (void){
	pos_=pos_->prev_;
	return *this;
}

// Post-increment.
template <typename T,typename LQUEUE_NODE>
LQueue_Iterator<T, LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE>::operator-- (int) {
	LQueue_Iterator<T, LQUEUE_NODE> dummy = *this;
	--*this;
	return dummy;
}

template <typename T,typename LQUEUE_NODE>
bool LQueue_Iterator<T, LQUEUE_NODE>::operator== (const LQueue_Iterator<T, LQUEUE_NODE> &rhs) const{
	return (pos_ == rhs.pos_);
}

template <typename T,typename LQUEUE_NODE>
bool LQueue_Iterator<T, LQUEUE_NODE>::operator!= (const LQueue_Iterator<T, LQUEUE_NODE> &rhs) const{
	return !(*this == rhs);
}

template <typename T,typename LQUEUE_NODE>
LQueue_Iterator<T, LQUEUE_NODE>::LQueue_Iterator (LQUEUE_NODE *pos):
pos_ (pos){
}

template <typename T,typename LQUEUE_NODE>
const T & Const_LQueue_Iterator<T, LQUEUE_NODE>::operator* (void) const{
	return pos_->item_;
}

template <typename T,typename LQUEUE_NODE> const Const_LQueue_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator++ (void) const{
	pos_=pos_->next_;
	return *this;
}

template <typename T,typename LQUEUE_NODE> Const_LQueue_Iterator<T, LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator++ (int) const{
	Const_LQueue_Iterator<T, LQUEUE_NODE> dummy = *this;
	++*this;
	return dummy;
}

template <typename T,typename LQUEUE_NODE> const Const_LQueue_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator-- (void) const{
	pos_=pos_->prev_;
	return *this;
}

// Post-increment.
template <typename T,typename LQUEUE_NODE> Const_LQueue_Iterator<T, LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator-- (int) const{
	Const_LQueue_Iterator<T, LQUEUE_NODE> dummy = *this;
	--*this;
	return dummy;
}

template <typename T,typename LQUEUE_NODE> bool
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator== (const Const_LQueue_Iterator<T, LQUEUE_NODE> &rhs) const{
	return pos_ == rhs.pos_;
}

template <typename T,typename LQUEUE_NODE> bool
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator!= (const Const_LQueue_Iterator<T, LQUEUE_NODE> &rhs) const{
  return !(*this == rhs);
}

template <typename T,typename LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::Const_LQueue_Iterator (LQUEUE_NODE *pos):
pos_ (pos){
}

template <typename T,typename LQUEUE_NODE>
T & LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void){
	return pos_->item_;
}

template <typename T,typename LQUEUE_NODE>
const T & LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void) const{
	return pos_->item_;
}

template <typename T,typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (void) {
	pos_=pos_->prev_;
	return *this;
}

// Post-increment.
template <typename T,typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE>
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (int) {
	LQueue_Reverse_Iterator<T, LQUEUE_NODE> dummy = *this;
	++*this;
	return dummy;
}

template <typename T,typename LQUEUE_NODE> bool
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator== (const LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const{
	return pos_ == rhs.pos_;
}

template <typename T,typename LQUEUE_NODE> bool
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator!= (const LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const{
  return !(*this == rhs);
}

template <typename T,typename LQUEUE_NODE>
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::LQueue_Reverse_Iterator (LQUEUE_NODE *pos):
pos_ (pos){
}

template <typename T,typename LQUEUE_NODE>
const T & Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void) const{
  return pos_->item_;
}

template <typename T,typename LQUEUE_NODE> const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (void) const{
	pos_=pos_->prev_;
	return *this;
}

template <typename T,typename LQUEUE_NODE> Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (int) const{
	Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> dummy = *this;
	++*this;
	return dummy;
}

template <typename T,typename LQUEUE_NODE> bool
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator== (const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const{
	return pos_==rhs.pos_;
}

template <typename T,typename LQUEUE_NODE> bool
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator!= (const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const{
  return !(*this == rhs);
}

template <typename T,typename LQUEUE_NODE>
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::Const_LQueue_Reverse_Iterator (LQUEUE_NODE *pos):
pos_ (pos){
}

#endif /* _LQUEUE_CPP */
