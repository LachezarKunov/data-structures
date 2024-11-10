#include <iostream>
using namespace std;

template<class T>
size_t partition(T* arr, size_t len) 
{
	T pivot = arr[len / 2];

	int i = 0;
	int j = len - 1;

	while (true) 
	{
		while (arr[i] < pivot) 
		{
			i++;
		}
		while (arr[j] > pivot) 
		{
			j--;
		}
		if (arr[i] == arr[j]) 
		{
			i++;
		}
		if (i < j)
		{
			std::swap(arr[i], arr[j]);
		}
		else
		{
			return j;
		}
	}
}

template<class T>
void QuickSort(T* arr, size_t len) 
{
	if (len <= 1)
		return;

	size_t pivotIndex = partition(arr, len);
	QuickSort(arr, pivotIndex);
	QuickSort(arr + pivotIndex + 1, len - pivotIndex - 1);
}

int main()
{
	int arr[]{ 7,3,2,-5,4,5,2,1 };
	QuickSort(arr, 8);
	for (size_t i = 0; i < 8; i++)
		cout << arr[i] << " ";
}
