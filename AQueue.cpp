/***************************************
Class: CS251
Assignment Number: 3
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

/**
 * @class AQueue
 * @brief Defines a generic "first-in/first-out" (FIFO) Abstract Data Type (ADT) using an Array
 *        that is organized as a "circular queue."
 */

#if !defined (_AQUEUE_C)
#define _AQUEUE_C

#include "AQueue.h"
#include "Array.cpp"
//#include <iostream>
// Returns the current number of elements in the queue.

template <typename T, typename ARRAY> 
size_t AQueue<T, ARRAY>::size (void) const {
	return count_;
}

// Constructor.

template <typename T, typename ARRAY> 
AQueue<T, ARRAY>::AQueue (size_t size):
queue_(size+1),head_(0),tail_(0),count_(0){
}

// Copy constructor.

template <typename T, typename ARRAY> 
AQueue<T, ARRAY>::AQueue (const AQueue<T, ARRAY> &rhs):
queue_(rhs.queue_),head_(rhs.head_),tail_(rhs.tail_),count_(rhs.count_){
}

template <typename T, typename ARRAY>
void AQueue<T, ARRAY>::swap (AQueue<T, ARRAY> &new_aqueue){
	queue_.swap(new_aqueue.queue_);			//removed commented code
	std::swap(count_,new_aqueue.count_);
	std::swap(head_,new_aqueue.head_);
	std::swap(tail_,new_aqueue.tail_);
}

// Assignment operator.
template <typename T, typename ARRAY>
AQueue<T, ARRAY>& AQueue<T, ARRAY>::operator= (const AQueue<T, ARRAY> &rhs){
	if(this!=&rhs){
		AQueue<T, ARRAY> tempQ(rhs);		//made tempQ definition portable
		swap(tempQ);
	}
	return *this;
}

// Perform actions needed when queue goes out of scope.

template <typename T, typename ARRAY>
AQueue<T, ARRAY>::~AQueue (void){
  // There's nothing to do here since we didn't dynamically
  // allocate any memory. The queue_ dtor handles that.
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.
template <typename T, typename ARRAY>
bool AQueue<T, ARRAY>::operator== (const AQueue<T, ARRAY> &rhs) const{
	if (count_ == rhs.count_)
		return std::equal(rhs.begin(),rhs.end(),begin());
	return false;
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.

template <typename T, typename ARRAY>
bool AQueue<T, ARRAY>::operator!= (const AQueue<T, ARRAY> &rhs) const{
	return !(*this == rhs);
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.

template <typename T, typename ARRAY>
void AQueue<T, ARRAY>::enqueue (const T &new_item){
	if(is_full())					//removed commented code
		throw Overflow();
	queue_[tail_]=new_item;
	tail_=increment(tail_);
	count_++;
}

// Remove the front item on the queue.  Throws the <Underflow>
// exception if the queue is empty.

template <typename T, typename ARRAY>
void AQueue<T, ARRAY>::dequeue (void){
	if (is_empty())
		throw Underflow();
	head_=increment(head_);
	count_--;
}

// Returns the front queue item without removing it.  Throws the
// <Underflow> exception if the queue is empty.

template <typename T, typename ARRAY>
T AQueue<T, ARRAY>::front (void) const{
	if(is_empty())
		throw Underflow();
	else
		return queue_[head_];
}

// Returns true if the queue is empty, otherwise returns false.

template <typename T, typename ARRAY>
bool AQueue<T, ARRAY>::is_empty (void) const {
	return count_ == 0;
}

// Returns true if the queue is full, otherwise returns false.

template <typename T, typename ARRAY>
bool AQueue<T, ARRAY>::is_full (void) const {
	return count_== queue_.size()-1;
}

// Get an iterator to the begining of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::iterator
AQueue<T, ARRAY>::begin (void){
	return AQueue_Iterator<T, ARRAY> (*this,head_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::iterator
AQueue<T, ARRAY>::end (void){
	return AQueue_Iterator<T, ARRAY>(*this,tail_);
}

// Get an iterator to the begining of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_iterator AQueue<T, ARRAY>::begin (void) const{
	return Const_AQueue_Iterator<T, ARRAY>  (*this, head_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_iterator AQueue<T, ARRAY>::end (void) const{
	return Const_AQueue_Iterator<T, ARRAY>  (*this, tail_);
}

// Get an iterator to the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::reverse_iterator AQueue<T, ARRAY>::rbegin (void){
	return AQueue_Reverse_Iterator<T, ARRAY>  (*this, decrement(tail_));
}

// Get an iterator pointing to the beginning of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::reverse_iterator AQueue<T, ARRAY>::rend (void){
	return AQueue_Reverse_Iterator<T, ARRAY>  (*this, decrement(head_));
}

// Get an iterator to the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_reverse_iterator
AQueue<T, ARRAY>::rbegin (void) const{
	return Const_AQueue_Reverse_Iterator<T,ARRAY>  (*this, decrement(tail_));
}

// Get an iterator pointing to the beginning of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_reverse_iterator
AQueue<T, ARRAY>::rend (void) const{
	return Const_AQueue_Reverse_Iterator<T,ARRAY>  (*this, decrement(head_));
}

/// Calculate the appropriate index when incrementing.
template <typename T, typename ARRAY>
size_t AQueue<T, ARRAY>::increment (size_t index) const{
	return (index +1) % (queue_.size());	//made it simpler
}

/// Calculate the appropriate index when decrementing.
template <typename T, typename ARRAY>
size_t AQueue<T, ARRAY>::decrement (size_t index) const{
	return ((index + queue_.size())-1) % (queue_.size()); //made it portable
}

template <typename T, typename ARRAY>
T & AQueue_Iterator<T, ARRAY>::operator* (void){
	return queue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
const T & AQueue_Iterator<T, ARRAY>::operator* (void) const{
	return queue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY> & AQueue_Iterator<T, ARRAY>::operator++ (void){
	pos_=queue_ref_.increment(pos_);
	return *this;
}

// Post-increment.
template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY>  AQueue_Iterator<T, ARRAY>::operator++ (int) {
	AQueue_Iterator<T, ARRAY> dummy(*this);
	++*this;				//used pre-increment operator
	return dummy;
}

template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY> & AQueue_Iterator<T, ARRAY>::operator-- (void){
	pos_=queue_ref_.decrement(pos_);
	return *this;
}

// Post-decrement.
template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY> AQueue_Iterator<T, ARRAY>::operator-- (int) {
	AQueue_Iterator dummy(*this);
	--*this;				//used pre-decrement operator
	return dummy;
}

template <typename T, typename ARRAY>
bool AQueue_Iterator<T, ARRAY>::operator==
(const AQueue_Iterator<T, ARRAY> &rhs) const{
	return ((pos_==rhs.pos_)&&(&queue_ref_ == &rhs.queue_ref_));
}

template <typename T, typename ARRAY>
bool AQueue_Iterator<T, ARRAY>::operator!=
(const AQueue_Iterator<T, ARRAY> &rhs) const{
  return !(*this == rhs);
}

template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY>::AQueue_Iterator
(AQueue<T, ARRAY> &queue_ref,size_t pos):
queue_ref_(queue_ref),
pos_(pos){
}

template <typename T, typename ARRAY>
const T & Const_AQueue_Iterator<T, ARRAY>::operator* (void) const{
	return queue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
const Const_AQueue_Iterator<T, ARRAY> &
Const_AQueue_Iterator<T, ARRAY>::operator++ (void) const{
	pos_=queue_ref_.increment(pos_);
	return *this;
}

template <typename T, typename ARRAY>
Const_AQueue_Iterator<T, ARRAY>
Const_AQueue_Iterator<T, ARRAY>::operator++ (int) const{
	Const_AQueue_Iterator<T, ARRAY> dummy(*this);
	++*this;				//used pre-increment operator
	return dummy;
}

template <typename T, typename ARRAY>
const Const_AQueue_Iterator<T, ARRAY> &
Const_AQueue_Iterator<T, ARRAY>::operator-- (void) const{
	pos_=queue_ref_.decrement(pos_);
	return *this;
}

// Post-decrement.
template <typename T, typename ARRAY>
Const_AQueue_Iterator<T, ARRAY>
Const_AQueue_Iterator<T, ARRAY>::operator-- (int) const{
	Const_AQueue_Iterator<T, ARRAY> dummy(*this);
	--*this;				//used pre-decrement operator
	return dummy;
}

template <typename T, typename ARRAY>
bool Const_AQueue_Iterator<T, ARRAY>::operator==
(const Const_AQueue_Iterator<T, ARRAY> &rhs) const{
	return ((pos_==rhs.pos_)&&(&queue_ref_ == &rhs.queue_ref_));
}

template <typename T, typename ARRAY>
bool Const_AQueue_Iterator<T, ARRAY>::operator!=
(const Const_AQueue_Iterator<T, ARRAY> &rhs) const{
  return !(*this == rhs);
}

template <typename T, typename ARRAY>
Const_AQueue_Iterator<T, ARRAY>::Const_AQueue_Iterator
(const AQueue<T, ARRAY> &queue_ref,size_t pos):
queue_ref_(queue_ref),pos_(pos){
}

template <typename T, typename ARRAY>
T & AQueue_Reverse_Iterator<T, ARRAY>::operator* (void){
	return queue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
const T & AQueue_Reverse_Iterator<T, ARRAY>::operator* (void) const{
	return  queue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T,ARRAY> & AQueue_Reverse_Iterator<T,ARRAY>::operator++
(void){
	pos_=queue_ref_.decrement(pos_);
	return *this;
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY> AQueue_Reverse_Iterator<T, ARRAY>::operator++
(int) {
	AQueue_Reverse_Iterator<T, ARRAY> dummy(*this);
	++*this;				//used pre-increment operator
	return dummy;
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T,ARRAY> & AQueue_Reverse_Iterator<T,ARRAY>::operator--
(void){
	pos_=queue_ref_.increment(pos_);
	return *this;
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY> AQueue_Reverse_Iterator<T, ARRAY>::operator--
(int) {
	AQueue_Reverse_Iterator<T, ARRAY> dummy(*this);
	--*this;				//used pre-decrement operator
	return dummy;
}

template <typename T, typename ARRAY>
bool AQueue_Reverse_Iterator<T, ARRAY>::operator==
(const AQueue_Reverse_Iterator<T, ARRAY> &rhs) const{
	return ((pos_==rhs.pos_)&&(&queue_ref_ == &rhs.queue_ref_));
}

template <typename T, typename ARRAY>
bool
AQueue_Reverse_Iterator<T, ARRAY>::operator!=
(const AQueue_Reverse_Iterator<T, ARRAY> &rhs) const{
	return !(*this == rhs);
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY>::AQueue_Reverse_Iterator
(AQueue<T, ARRAY> &queue_ref,size_t pos):
queue_ref_(queue_ref),pos_(pos){
}

template <typename T, typename ARRAY>
const T & Const_AQueue_Reverse_Iterator<T, ARRAY>::operator* (void) const{
	return queue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
const Const_AQueue_Reverse_Iterator<T, ARRAY> &
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator++ (void) const{
	pos_=queue_ref_.decrement(pos_);
	return *this;
}

template <typename T, typename ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator++ (int) const{
	Const_AQueue_Reverse_Iterator<T, ARRAY> dummy(*this);
	++*this;				//used pre-increment operator
	return dummy;
}

template <typename T, typename ARRAY>
const Const_AQueue_Reverse_Iterator<T, ARRAY> &
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator-- (void) const{
	pos_=queue_ref_.increment(pos_);
	return *this;
}

template <typename T, typename ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator-- (int) const{
	Const_AQueue_Reverse_Iterator<T, ARRAY> dummy(*this);
	--*this;				//used pre-decrement operator
	return dummy;
}

template <typename T, typename ARRAY>
bool Const_AQueue_Reverse_Iterator<T, ARRAY>::operator==
(const Const_AQueue_Reverse_Iterator<T, ARRAY> &rhs) const{
	return ((pos_==rhs.pos_)&&(&queue_ref_ == &rhs.queue_ref_));
}

template <typename T, typename ARRAY>
bool Const_AQueue_Reverse_Iterator<T, ARRAY>::operator!=
(const Const_AQueue_Reverse_Iterator<T, ARRAY> &rhs) const{
	return !(*this == rhs);
}

template <typename T, typename ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>::Const_AQueue_Reverse_Iterator
(const AQueue<T, ARRAY> &queue_ref,size_t pos):
queue_ref_(queue_ref),pos_(pos){
}
#endif /* _AQUEUE_C */
