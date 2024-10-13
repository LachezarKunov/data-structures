#include <iostream>
#include <vector>
using namespace std;

template<class T>
void selectionSort(vector<T>& v) 
{
	for (size_t i = 0; i < v.size() - 1; i++)
	{
		int minIndex = i;

		for (size_t j = i + 1; j < v.size(); j++)
		{
			if (v[j] < v[minIndex])
				minIndex = j;
		}

		if(minIndex != i) 
			swap(v[i], v[minIndex]);
	}
}

template<class T>
void print(vector<T>& v) 
{
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
}

int main()
{
    vector<int> v{ 4,3,2,1,6 };
	
	selectionSort(v);

	print(v);
}
