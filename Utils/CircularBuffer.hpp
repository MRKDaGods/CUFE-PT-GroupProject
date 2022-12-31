#pragma once

#include <exception>
#include <cstring>

template<typename T>
using CircularBufferCleanup = void(*)(T*);

//A circular buffer is a ring-like array
//If we try to insert an element when the array is full, the very first element is popped, and the array is shifted
//and then our element is placed at the last index, etc
template<typename T, int size>
class CircularBuffer
{
private:
	T m_Buffer[size];
	int m_Head;
	int m_Tail;
	int m_Count;

	//A cleanup function that may be specified to cleanup objects/ptrs when removed
	//ie prevent memory leaks for the Action class
	CircularBufferCleanup<T> m_Cleanup;

	int Mod(int x, int m);
public:
	CircularBuffer(CircularBufferCleanup<T> cleanup = 0);
	void Push(T item, bool clean = true);
    void Pop();
    void Reset();

    //Tries to look for the next element (head+1)
    T PeekNext();

	int GetCount();

	T operator[](int index);
};

template<typename T, int size>
inline CircularBuffer<T, size>::CircularBuffer(CircularBufferCleanup<T> cleanup)
{
    //reset everything
    Reset();

    //set cleanup
    m_Cleanup = cleanup;
}

template<typename T, int size>
inline int CircularBuffer<T, size>::Mod(int x, int m)
{
    return (x % m + m) % m;
}

template<typename T, int size>
inline void CircularBuffer<T, size>::Push(T item, bool clean)
{
    m_Head = (m_Head + 1) % size;

    //clean up if needed
    if (clean && m_Buffer[m_Head] != 0 && m_Cleanup != 0)
    {
        try
        {
            m_Cleanup(&(m_Buffer[m_Head]));
        }
        catch (...)
        {
        }
    }

    m_Buffer[m_Head] = item;

    if (m_Count == size)
    {
        m_Tail = (m_Tail + 1) % size;
    }
    else
    {
        m_Count++;
    }
}

template<typename T, int size>
inline void CircularBuffer<T, size>::Pop()
{
    if (m_Count == 0) return;

    //we will just shift our head to the left
    m_Head--;
    if (m_Head < 0)
    {
        m_Head = size - 1;
    }

    m_Count--;
}

template<typename T, int size>
inline void CircularBuffer<T, size>::Reset()
{
    //init to 0
    m_Head = 0;
    m_Tail = 0;
    m_Count = 0;

    //zero out our buffer
    memset(m_Buffer, 0, sizeof(T) * size);
}

template<typename T, int size>
inline T CircularBuffer<T, size>::PeekNext()
{
    int next = (m_Head + 1) % size;
    return m_Buffer[Mod(next, size)];
}

template<typename T, int size>
inline int CircularBuffer<T, size>::GetCount()
{
    return m_Count;
}

template<typename T, int size>
inline T CircularBuffer<T, size>::operator[](int index)
{
    //check if index is within bounds
    if (index < 0 || index >= size)
    {
        throw std::exception("Index out of bounds");
    }

    return m_Buffer[Mod((m_Head - index), size)];
}
