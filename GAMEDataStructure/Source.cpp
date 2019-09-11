#include "OrderedArray.h"

int main()
{
	OrderedArray<int> array(2, 1);

	array.PrintArray();

	array.Push(1);
	array.PrintArray();
	array.Push(3);
	array.PrintArray();
	array.Push(5);
	array.PrintArray();
	array.Push(7);
	array.PrintArray();
	array.Push(9);
	array.PrintArray();
	array.Push(11);
	array.PrintArray();
	array.Push(13);
	array.PrintArray();
	array.Push(13);
	array.PrintArray();
	array.Push(13);
	array.PrintArray();
	array.Push(13);
	array.PrintArray();
	array.Push(13);
	array.PrintArray();

	std::cout << array[array.Search(9)] << std::endl;


	return 0;
}