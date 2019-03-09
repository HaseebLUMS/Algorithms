#ifndef __PQUEUE_CPP
#define __PQUEUE_CPP
#include "pqueue.h"

template<class T>
bool Less(T a, T b);
template <class T>
MinHeap<T>::MinHeap(int cap,bool(*compareFunction)(T a, T b))
{
	capacity = cap;
	harr = new T[capacity]();
	heap_size = 0;
	compare = compareFunction;

}
template<class T>
MinHeap<T>::MinHeap(int cap)
{
	capacity = cap;
	harr = new T[capacity]();
	heap_size = 0;
	compare =  &Less;
}
template<class T>
void MinHeap<T>::MinHeapify(int i)
{
	if (i >= heap_size)
		return;
	int leftC = left(i);
	int rightC = right(i);
	int min = leftC;
	if (rightC < heap_size && compare(harr[rightC],harr[min]))
	{
		min = rightC;
	}
	if (min < heap_size && compare(harr[min] , harr[i]))
	{
		swap(harr[i],harr[min]);
		MinHeapify(min);
	}
	return;
}
template<class T>
int MinHeap<T>::parent(int i)
{
	return (i-1)/2;
}
template<class T> 
int MinHeap<T>::left(int i)
{
	return ((2*i)+1);
}
template<class T>
int MinHeap<T>::right(int i)
{
	return ((2*i)+2);
}
template<class T> 
T MinHeap<T>::extractMin()
{
	T min = harr[0];
	deleteKey(0);
	return min;
}
template<class T>
void MinHeap<T>::decreaseKey(int i, T new_val)
{
	harr[i] = new_val;
	int temp = i;
	while (compare( harr[temp],harr[parent(temp)]))
	{
		swap(harr[parent(temp)],harr[temp]);
		temp = parent(temp);
		if(temp == 0 && compare( harr[temp],harr[parent(temp)]))
		{
			swap(harr[parent(temp)],harr[temp]);
			break;
		}
	}
}
template<class T>
T MinHeap<T>::getMin()
{
	return harr[0];
}
template<class T>
void MinHeap<T>::deleteKey(int i)
{	
	if (i < heap_size)
	{
		swap(harr[i], harr[heap_size-1]);
		heap_size--;
		MinHeapify(i);
	}
}
template<class T>
void MinHeap<T>::insertKey(T k)
{
	if (heap_size == capacity)
		return;
	harr[heap_size] = k;
	int temp = heap_size;
	heap_size++;
	while (compare( harr[temp],harr[parent(temp)]))
	{
		swap(harr[parent(temp)],harr[temp]);
		temp = parent(temp);
		if(temp == 0 && compare( harr[temp],harr[parent(temp)]))
		{
			swap(harr[parent(temp)],harr[temp]);
			break;
		}
	}
}
template<class T>
T* MinHeap<T>::getHeap()
{
	return harr;
}
template<class T>
bool Less(T a, T b)
{
	return a < b;
}
// int main()
// {
// 	MinHeap<int> a(15);
// 	a.insertKey(12);
// 	a.insertKey(2);
// 	a.insertKey(54);
// 	a.insertKey(1);
// 	a.insertKey(0);
// 	a.insertKey(-1);
// 	a.insertKey(188);
// 	a.print();
// 	cout << endl;
// 	a.decreaseKey(4,-3);
// 	a.print();
// }

#endif