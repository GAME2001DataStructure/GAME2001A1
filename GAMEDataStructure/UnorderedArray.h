#ifndef _UNORDEREDARRAY_H_
#define _UNORDEREDARRAY_H_

#include "ArrayBase.h"

template<class DataType>
class UnorderedArray : public ArrayBase<DataType>
{
private :

public:
	UnorderedArray(int iMaxSize = 0, int iGrowSize = 1);
	virtual ~UnorderedArray();

	//Search using linear search(Brute force searching)
	virtual int Search(DataType Data) override;
};

template<class DataType>
UnorderedArray<DataType>::UnorderedArray(int iMaxSize, int iGrowSize)
	:ArrayBase<DataType>(iMaxSize, iGrowSize)
{

}

template<class DataType>
UnorderedArray<DataType>::~UnorderedArray()
{
	int a = 0;
}

template<class DataType>
int UnorderedArray<DataType>::Search(DataType Data)
{
	assert(this->m_pArray != nullptr);

	//Big-O if O(N)
	for (int i = 0; i < this->m_iNumElements; ++i)
	{
		if (this->m_pArray[i] == Data)
		{
			return i;
		}
	}

	return -1;
}
#endif