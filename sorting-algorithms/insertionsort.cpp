#include <iostream>
#include <vector>
using namespace std;

template<class T>
void insertionSort(vector<T>& v) 
{
	for (size_t i = 1; i < v.size(); i++)
	{
		T temp = v[i];
		int j = i - 1;

		while (j >= 0 && v[j] > temp) 
		{
			v[j + 1] = v[j];
			j--;
		}

		v[j + 1] = temp;
	}
}

int main()
{
  	vector<int> vector{ 4,3,2,1,6 };
	
	insertionSort(vector);

	for (size_t i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i];
	}
}
