/***************************************
Class: CS251
Assignment Number: 2
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef ARRAY_CPP
#define ARRAY_CPP

#include <sys/types.h>

#include <algorithm>
#include <sstream>

#include "Array.h"

#if !defined (__INLINE__)
#define INLINE
#include "Array.inl"
#endif /* __INLINE__ */

template <typename T>
Array<T>::Array (size_t size):
 max_size_(size),
 cur_size_(size),
 default_value_(0),
 array_(new T[size]){
}

template <typename T>
Array<T>::Array (size_t size,const T &default_value):
max_size_(size),
cur_size_(size),
default_value_(new T(*default_value)),
array_(0){
	scoped_array<T> temp_array (new T[max_size_]);
	std::fill(temp_array.get(), temp_array.get()+max_size_, *default_value);
	temp_array.swap(array_);
}

// The copy constructor (performs initialization).
template <typename T>
Array<T>::Array (const Array<T> &s):
max_size_(s.max_size_),
cur_size_(s.cur_size_),
default_value_((s.default_value_.get())?(new T (*s.default_value_)):0), //changed
array_(0){
	scoped_array<T> temp_array (new T[s.max_size_]);
	std::copy(s.array_.get(),s.array_.get()+s.cur_size_,temp_array.get());
	temp_array.swap(array_);
}

template <typename T> void Array<T>::swap (Array<T> &new_array){
	new_array.array_.swap(array_);
	std::swap(new_array.cur_size_,cur_size_);
	std::swap(new_array.max_size_,max_size_);
	default_value_=new_array.default_value_;	//Added default value swap
}

// Assignment operator (performs assignment). 
template <typename T> void Array<T>::operator= (const Array<T> &s){
	if(!(this == &s)){
		Array<T> temp(s);
		swap(temp);							//used swap instead of explicit assigning
	}
}

// Clean up the array (e.g., delete dynamically allocated memory).
template <typename T> Array<T>::~Array (void){}

// = Set/get methods.
// Set an item in the array at location index.  

template <typename T> void Array<T>::set (const T &new_item, size_t index){
	if(!in_range(index))//(index !<cur_size)				//changed set function
		resize(index+1);
	array_[index]=new_item;
}

template <typename T> void Array<T>::resize (size_t new_size){
	if(new_size>max_size_){
		scoped_array<T> temp_array (new T[2*new_size]);
		std::copy(array_.get(),array_.get()+cur_size_,temp_array.get());
		if (default_value_.get())
			std::fill(temp_array.get()+max_size_,
						 temp_array.get()+2*new_size,
						 *default_value_);
		temp_array.swap(array_);
		max_size_=2*new_size;
	}
	else if(new_size<cur_size_){
		if (default_value_.get())
			std::fill(array_.get(),
						 array_.get()+new_size,
						 *default_value_);
	}
	else{
		if (default_value_.get())
			std::fill(array_.get()+cur_size_,
						 array_.get()+new_size,
						 *default_value_);
	}
	cur_size_=new_size;
}

// Get an item in the array at location index.
template <typename T> void Array<T>::get (T &item, size_t index){
	if(this->in_range(index))
		item = this->array_[index];
	else{
		std::stringstream index_str;
		index_str << static_cast <int> (index);
		throw std::out_of_range(index_str.str());
	}
}

// Compare this array with <s> for equality.
template <typename T> bool Array<T>::operator== (const Array<T> &s) const{
	if(cur_size_ == s.cur_size_)
		return std::equal(array_.get(),array_.get()+cur_size_,s.array_.get());
	else
		return false;
}

// Compare this array with <s> for inequality.
template <typename T> bool Array<T>::operator!= (const Array<T> &s) const{
	return !(*this == s);
}

template <typename T>
Array_Iterator<T>::Array_Iterator (Array<T> &array, size_t pos):
array_(array),pos_(pos){
}

template <typename T>
Const_Array_Iterator<T>::Const_Array_Iterator (const Array<T> &array, size_t pos):
array_(array),pos_(pos){
}

#endif /* ARRAY_CPP */
