#pragma once
#include <cassert>

template<class T>
class OrdredArray
{
public :
	OrdredArray(int iSize, int iGrowBy = 1)
		:m_Array(nullptr), m_iMaxSize(0), m_iGrowSize(0), m_iNumElements(0)
	{
		if (iSize != 0)
		{
			m_iMaxSize = iSize;
			m_Array = new T[m_iMaxSize];
			memset(m_Array, 0, sizeof(T) * m_iMaxSize);
		}
	}

	~OrdredArray()
	{
		if (m_Array != nullptr)
		{
			delete[] m_Array;
			m_Array = nullptr;
		}
	}

	int push(T val)
	{
		assert(m_Array != nullptr);

		if (m_iNumElements >= m_iMaxSize)
		{
			Expand();
		}

		int i, k;
		for (i = 0; i < m_iNumElements; ++i)
		{
			if (m_Array[i] > val)
			{
				break;
			}
		}

		for (k = m_iNumElements; k > i; --k)
		{
			m_Array[k] = m_Array[k - 1];
		}
		m_Array[i] = val;
		m_iNumElements++;

		return 1;
	}

	//Removes the last item in the arrays
	void pop()
	{
		if (m_iNumElements > 0)
		{
			--m_iNumElements;
		}
	}

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

	const T& operator[](int index)
	{
		assert(m_Array != nullptr && index < m_iNumElements);
		return m_Array[index];
	}

	//Search
	int search(T searchKey)
	{
		assert(m_Array != nullptr);

		int lowerBound = 0;
		int upperBound = m_numElements - 1;
		int current = 0;

		while (1)
		{
			current = (lowerBound + upperBound) >> 1;

			if (m_Array[current] == searchKey)
			{
				return current; //FOUND
			}
			else if (lowerBound > upperBound) //Checked through entire array
			{
				return -1; //NOT FOUND
			}
			else
			{
				if (m_Array[current] < searchKey) //key in upper bound
				{
					lowerBound = current + 1;
				}
				else //key in lowerbound
				{
					upperBound = current - 1;
				}
			}
		}

		return -1;
	}

	//Clear
	void CLear()
	{
		m_iNumElements = 0;
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

private :
	T* m_Array;
	int m_iMaxSize;
	int m_iGrowSize;
	int m_iNumElements;
};