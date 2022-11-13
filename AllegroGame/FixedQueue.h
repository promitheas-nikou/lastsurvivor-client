#pragma once
#include <stdlib.h>
#include <exception>

template<typename T>
class FixedQueue
{
private:
	size_t size;
	size_t curSize;
	size_t frontInd;
	size_t backInd;
	T* list;
	void ThrowOutOfRangeException() const;
public:
	bool TryPush(const T& obj);
	bool TryPop(T* dest);
	void Push(const T& obj);
	T& Pop();
	bool TryPeekFront(T* dest);
	bool TryPeekBack(T* dest);
	T& GetFront();
	T& GetBack();
	int GetMaxSize() const;
	int GetCurSize() const;
	T& Get(int i) const;
	FixedQueue(size_t size, const T& init = T());
	~FixedQueue();
};

template<typename T>
inline void FixedQueue<T>::ThrowOutOfRangeException() const
{
	throw std::exception("out of range");
}

template<typename T>
inline bool FixedQueue<T>::TryPush(const T& obj)
{
	if (curSize >= size)
		return false;
	list[frontInd++] = obj;
	if (frontInd >= size)
		frontInd = 0;
	curSize++;
	return true;
}

template<typename T>
inline bool FixedQueue<T>::TryPop(T* dest)
{
	if (curSize == 0)
		return false;

	if(dest)
		*dest = list[backInd];
	if (++backInd >= size)
		backInd = 0;
	curSize--;
	
	return true;
}

template<typename T>
inline void FixedQueue<T>::Push(const T& obj)
{
	(void)TryPush(obj);
}

template<typename T>
inline T& FixedQueue<T>::Pop()
{
	if (curSize == 0)
		ThrowOutOfRangeException();
	curSize--;
	T& r = list[backInd];
	if (++backInd >= size)
		backInd = 0;
	return r;
}

template<typename T>
inline bool FixedQueue<T>::TryPeekFront(T* dest)
{
	if (curSize == 0)
		return false;
	if (dest)
		*dest = list[backInd]; //because front of the queue is the least recent element added
	return true;
}

template<typename T>
inline bool FixedQueue<T>::TryPeekBack(T* dest)
{
	if (curSize == 0)
		return false;
	if (dest)
		*dest = list[frontInd]; //because back of the queue is the most recent element added
	return true;
}

template<typename T>
inline T& FixedQueue<T>::GetFront()
{
	return this->Get(0);
}

template<typename T>
inline T& FixedQueue<T>::GetBack()
{
	return this->Get(curSize);
}

template<typename T>
inline int FixedQueue<T>::GetMaxSize() const
{
	return size;
}

template<typename T>
inline int FixedQueue<T>::GetCurSize() const
{
	return curSize;
}

template<typename T>
inline T& FixedQueue<T>::Get(int i) const
{
	if (i < 0 || i>curSize)
		ThrowOutOfRangeException();
	return list[(backInd + i) % size];
}

template<typename T>
inline FixedQueue<T>::FixedQueue(size_t size, const T& init) : size{ size }, frontInd{ 0 }, backInd{ 0 }
{
	list = new T[size];
}

template<typename T>
inline FixedQueue<T>::~FixedQueue()
{
	if (size == 0)
		return;
	delete[] list;
}

