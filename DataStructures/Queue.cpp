#include "Queue.h"
#include <iostream>
#include <cstdlib>

template <class T>
Queue<T>::Queue(int _size) {
	arrayItems = new T[_size];
	_iLimit = _size;
	_iHead = _iTail = _iItemsAmount = 0;
}

template <class T>
T Queue<T>::Peek(){
	return arrayItems[_iHead];
}

template <class T>
void Queue<T>::Push(T _item){
	if(IsFull()){
		std::cout << "Overflow - Already Full!" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	_iItemsAmount++;
	arrayItems[++_iTail] = _item;
}

template <class T>
T Queue<T>::Pop(){
	if(IsEmpty()){
		std::cout << "Underflow - Is Empty!" << std::endl;
		exit(EXIT_FAILURE);
	}

	_iItemsAmount--;
	return arrayItems[_iHead++];
}

template <class T>
bool Queue<T>::IsEmpty(){
	return (Size() == 0) ? true : false;
}

template <class T>
bool Queue<T>::IsFull(){
	return (Size() == _iLimit) ? true : false;
}

template <class T>
int Queue<T>::Size(){
	return _iItemsAmount;
}
