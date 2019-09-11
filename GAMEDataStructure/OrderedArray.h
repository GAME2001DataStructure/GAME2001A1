#ifndef _ORDREDARRAY_H_
#define _ORDREDARRAY_H_

#include "ArrayBase.h"

template<class DataType>
class OrderedArray : public ArrayBase<DataType>
{
private :
	bool m_bPreventDuplicate;

public :
	OrderedArray(int iMaxSize = 0, int iGrowSize = 1, bool bPreventDuplicate = true);
	virtual ~OrderedArray();

	virtual void Push(DataType Data) override;
	//Searching using binary search
	virtual int Search(DataType Data) override;
};

template<class DataType>
OrderedArray<DataType>::OrderedArray(int iMaxSize, int iGrowSize, bool bPreventDuplicate)
	:ArrayBase<DataType>(iMaxSize, iGrowSize), m_bPreventDuplicate(bPreventDuplicate)
{

}
template<class DataType>
OrderedArray<DataType>::~OrderedArray()
{

}

template<class DataType>
void OrderedArray<DataType>::Push(DataType Data)
{
	assert(this->m_pArray != nullptr);

	//Check duplicate
	if (this->Search(Data) != -1)
	{
		//DUPLICATED DATA!
		return;
	}

	if (this->m_iNumElements >= this->m_iMaxSize)
	{
		this->Expand();
	}

	//Find place for new data in ascending
	int i, k;
	for (i = 0; i < this->m_iNumElements; ++i)
	{
		if (this->m_pArray[i] > Data)
		{
			break;
		}
	}

	for (k = this->m_iNumElements; k > i; --k)
	{
		this->m_pArray[k] = this->m_pArray[k - 1];
	}
	this->m_pArray[i] = Data;
	this->m_iNumElements++;
}

template<class DataType>
int OrderedArray<DataType>::Search(DataType Data)
{
	assert(this->m_pArray != nullptr);

	int lowerBound = 0;
	int upperBound = this->m_iNumElements - 1;
	int current = 0;

	while (1)
	{
		current = (lowerBound + upperBound) >> 1;

		if (this->m_pArray[current] == Data)
		{
			return current; //FOUND
		}
		else if (lowerBound > upperBound) //Checked through entire array
		{
			return -1; //NOT FOUND
		}
		else
		{
			if (this->m_pArray[current] < Data) //key in upper bound
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

#endif