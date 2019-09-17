#ifndef _ARRAYBASE_H
#define _ARRAYBASE_H

#include <cassert>
#include <cstring>
#include <iostream>

template<class DataType>
class ArrayBase
{
protected :
	DataType* m_pArray;
	int m_iMaxSize;
	int m_iGrowSize;
	int m_iNumElements;

public :
	ArrayBase(int iMaxSize = 0, int iGrowSize = 2);
	virtual ~ArrayBase();

	virtual void Push(DataType Data);
	void Pop();
	void Remove(int iIdx);
	virtual int Search(DataType Data) = 0;
	void Clear();
	void PrintArray();

	
	
	int GetSize() { return m_iNumElements; }
	int GetMaxSize() { return m_iMaxSize; }
	int GetGrowSize() { return m_iGrowSize; }
	void SetGrowSize(int iGrowSize);

	
	DataType& operator[](int iIdx);

protected:
	bool Expand();
};

template<class DataType>
ArrayBase<DataType>::ArrayBase(int iMaxSize, int iGrowSize)
	:m_pArray(nullptr), m_iMaxSize(0), m_iGrowSize(0), m_iNumElements(0)
{
	if (iMaxSize != 0)
	{
		m_iMaxSize = iMaxSize;
		m_pArray = new DataType[m_iMaxSize];
		memset(m_pArray, 0, sizeof(DataType) * m_iMaxSize);

		m_iGrowSize = (iGrowSize > 0) ? iGrowSize : 0;
	}
}

template<class DataType>
ArrayBase<DataType>::~ArrayBase()
{
	if (m_pArray != nullptr)
	{
		delete[] m_pArray;
		m_pArray = nullptr;
	}
}

template<class DataType>
void ArrayBase<DataType>::Push(DataType Data)
{
	assert(m_pArray != nullptr);

	if (m_iNumElements >= m_iMaxSize)
	{
		Expand();
	}

	m_pArray[m_iNumElements] = Data;
	++m_iNumElements;
}

template<class DataType>
void ArrayBase<DataType>::Pop()
{
	if (m_iNumElements > 0)
	{
		--m_iNumElements;
	}
}

template<class DataType>
void ArrayBase<DataType>::Remove(int iIdx)
{
	assert(m_pArray != nullptr);

	if (iIdx >= m_iNumElements)
	{
		return;
	}

	//Expensive to execute( O(N) )
	for (int i = iIdx; i < m_iNumElements - 1; ++i)
	{
		m_pArray[i] = m_pArray[i + 1];
	}
	--m_iNumElements;
}

template<class DataType>
DataType& ArrayBase<DataType>::operator[](int iIdx)
{
	//Debugging
	assert(m_pArray != nullptr && iIdx < m_iNumElements);

	return m_pArray[iIdx];
}

//Remove all items from the array
template<class DataType>
void ArrayBase<DataType>::Clear()
{
	m_iNumElements = 0;
}

template<class DataType>
void ArrayBase<DataType>::SetGrowSize(int iGrowSize)
{
	assert(iGrowSize >= 0);

	m_iGrowSize = iGrowSize;
}

template<class DataType>
void ArrayBase<DataType>::PrintArray()
{
	std::cout << "MaxSize: " << m_iMaxSize << " " << "GrowSize: " << m_iGrowSize << " " << "NumElements: " << m_iNumElements << std::endl;

	for (int i = 0; i < m_iNumElements; ++i)
	{
		std::cout << m_pArray[i] << " ";
	}
	std::cout << std::endl;
}

template<class DataType>
bool ArrayBase<DataType>::Expand()
{
	if (m_iGrowSize <= 0)
	{
		return false;
	}

	DataType* pTemp = new DataType[m_iMaxSize + m_iGrowSize];

	assert(pTemp != nullptr);

	memcpy(pTemp, m_pArray, sizeof(DataType) * m_iMaxSize);

	delete[] m_pArray;
	m_pArray = pTemp;

	m_iMaxSize += m_iGrowSize;
	m_iGrowSize = m_iGrowSize << 1;
	return true;
}

#endif