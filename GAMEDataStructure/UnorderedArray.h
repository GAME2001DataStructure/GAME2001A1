#pragma once
#include <iostream>
#include <cassert>

template<class T>
class UnorderedArray
{
public:
	//COnsructor
	UnorderedArray(int iSize, int iGrowBy = 1)
		:m_Array(nullptr), m_iMaxSize(0), m_iGrowSize(0), m_iNumElemetns(0)
	{
		if (iSize != 0)
		{
			m_iMaxSize = iSize;
			m_Array = new T[m_iMaxSize];
			memset(m_Array, 0, sizeof(T) * m_iMaxSize);

			m_iGrowSize = (iGrowBy > 0) ? iGrowBy : 0;
		}
	}

	//Destructor
	~UnorderedArray()
	{
		if (m_Array != nullptr)
		{
			delete[] m_Array;
			m_Array = nullptr;
		}
	}

	//Add elements to the array at the end
	void push(T val)
	{
		//Check if array is null
		assert(m_Array != nullptr);

		if (m_iNumElemetns >= m_iMaxSize)
		{
			Expand();
		}

		m_Array[m_iNumElemetns] = val;
		++m_iNumElemetns;
	}

	//Remove element fromthe array(3 ways)
	//Remove the last item that was inserted
	void pop()
	{
		//Gain a little bit ofa performance boost
		if (m_iNumElemetns > 0)
		{
			--m_iNumElemetns;
		}
	}

	//Remove an index from the array by overriding the index to delete
	void remove(int index)
	{
		assert(m_Array != nullptr);

		if (index >= m_iNumElemetns)
		{
			return;
		}

		//Expensive to execute( O(N) )
		for (int i = index; i < m_iNumElemetns; ++i)
		{
			if (i + 1 < m_iNumElemetns)
			{
				m_Array[i] = m_Array[i + 1];
			}
		}
		--m_iNumElemetns;
	}

	//Overload the [] operator
	T& operator[](int index)
	{
		//Debugging
		assert(m_Array != nullptr && index < m_iNumElemetns);

		return m_Array[index];
	}

	//Search using linear search(Brute force searching)
	int search(T val)
	{
		assert(m_Array != nullptr);

		//Big-O if O(N)
		for (int i = 0; i < m_iNumElemetns; ++i)
		{
			if (m_Array[i] == val)
			{
				return i;
			}
		}

		return -1;
	}

	//Remove all items from the array
	void clear()
	{
		m_iNumElemetns = 0;
	}

	int GetSize()
	{
		return m_iNumElemetns;
	}

	int GetMaxSize()
	{
		return m_iMaxSize;
	}

	int GetGrowSize()
	{
		return m_iGrowSize;
	}

	void SetGrowSize(int val)
	{
		assert(val >= 0);
		m_iGrowSize = val;
	}

private :
	bool Expand()
	{
		if (m_iGrowSize <= 0)
		{
			return false;
		}

		T* temp = new T[m_iMaxSize + m_iGrowSize];
		assert(temp != nullptr);

		memcpy(temp, m_Array, sizeof(T) * m_iMaxSize);

		delete[] m_Array;
		m_Array = temp;

		m_iMaxSize += m_iGrowSize;
		return true;
	}

private:
	T* m_Array;
	int m_iMaxSize;	//Maximum size of the array
	int m_iGrowSize; //How much can our array grow?
	int m_iNumElemetns; //How many items are currently in the array?
};