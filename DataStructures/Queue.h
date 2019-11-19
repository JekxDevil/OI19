#ifndef QUEUE_H
#define QUEUE_H

#define SIZE 50

template <class T>
class Queue{
	
	private:
		T* arrayItems;
		int _iLimit;
		int _iHead;
		int _iTail;
		int _iItemsAmount;
		
	public:
		Queue(int _size = SIZE);
		T Peek();
		void Push(T);
		T Pop();
		bool IsEmpty();
		bool IsFull();
		int Size();
};
#endif
