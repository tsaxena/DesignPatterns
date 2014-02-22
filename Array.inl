/***************************************
Class: CS251
Assignment Number: 2
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

// Returns the current size of the array.

template <typename T> INLINE size_t 
Array<T>::size (void) const{
	return cur_size_;
}

template <typename T> INLINE bool
Array<T>::in_range (size_t index) const{
	return (index < cur_size_);
}

template <typename T> INLINE T &
Array<T>::operator[] (size_t index){
	return array_[index];
}

template <typename T> INLINE const T &
Array<T>::operator[] (size_t index) const{
	return array_[index];
}

// Get an iterator to the begniing of the array
template <typename T> INLINE typename Array<T>::iterator
Array<T>::begin (void){
	return iterator(*this);
}

// Get an iterator pointing past the end of the array
template <typename T> INLINE typename Array<T>::iterator
Array<T>::end (void){
	return iterator(*this,cur_size_);
}

// Get an iterator to the begniing of the array
template <typename T> INLINE typename Array<T>::const_iterator
Array<T>::begin (void) const{
	return const_iterator(*this);
}

// Get an iterator pointing past the end of the array
template <typename T> INLINE typename Array<T>::const_iterator
Array<T>::end (void) const{
	return const_iterator(*this,cur_size_);
}

template <typename T> INLINE T &
Array_Iterator<T>::operator* (void){
	return array_[pos_];
}

template <typename T> INLINE const T &
Array_Iterator<T>::operator* (void) const{
	return array_[pos_];		//Doubt NO AUTO COMPLETION
}

template <typename T> INLINE Array_Iterator<T> &
Array_Iterator<T>::operator++ (void){
	pos_++;
	return *this;
}

template <typename T> INLINE Array_Iterator<T> 
Array_Iterator<T>::operator++ (int){
	Array_Iterator<T> dummy = *this;
	pos_++;
	return dummy;
}

template <typename T> INLINE Array_Iterator<T> &
Array_Iterator<T>::operator-- (void){
	pos_--;
	return *this;
}

template <typename T> INLINE Array_Iterator<T>
Array_Iterator<T>::operator-- (int) {
	Array_Iterator<T> dummy = *this;
	pos_--;
	return dummy;
}

template <typename T> INLINE bool
Array_Iterator<T>::operator== (const Array_Iterator<T> &rhs) const{
	return ((pos_==rhs.pos_)&&(&array_ == &rhs.array_));
}

template <typename T> INLINE bool
Array_Iterator<T>::operator!= (const Array_Iterator<T> &rhs) const{
	return !(*this == rhs);
}

template <typename T> INLINE const T &
Const_Array_Iterator<T>::operator* (void) const{
	return array_[pos_];
}

template <typename T> INLINE const Const_Array_Iterator<T> &
Const_Array_Iterator<T>::operator++ (void) const{
	pos_++;
	return *this;
}

template <typename T> INLINE Const_Array_Iterator<T> 
Const_Array_Iterator<T>::operator++ (int) const{
	Array_Iterator<T> dummy = *this;
	pos_++;
	return dummy;
}

template <typename T> INLINE const Const_Array_Iterator<T> &
Const_Array_Iterator<T>::operator-- (void) const{
	pos_--;
	return *this;
}

template <typename T> INLINE Const_Array_Iterator<T>
Const_Array_Iterator<T>::operator-- (int) const{
	Const_Array_Iterator<T> dummy = *this;
	pos_--;
	return dummy;
}

template <typename T> INLINE bool
Const_Array_Iterator<T>::operator== (const Const_Array_Iterator<T> &rhs) const{
	return ((pos_==rhs.pos_)&&(array_ == rhs.array_));
}

template <typename T> INLINE bool
Const_Array_Iterator<T>::operator!= (const Const_Array_Iterator<T> &rhs) const{
	return (!(*this==rhs));
}

