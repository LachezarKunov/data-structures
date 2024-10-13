#include <iostream>
#include <vector>
using namespace std;

template<class T>
void bubbleSort(vector<T>& v) 
{
	int n = v.size();
	bool swapped;

	for (size_t i = 0; i < n; i++)
	{
		swapped = false;
		for (size_t j = 0; j < n - i - 1; j++)
		{
			if (v[j] > v[j + 1]) 
			{
				std::swap(v[j], v[j + 1]);
				swapped = true;
			}
		}

		if (!swapped)
			break;
	}


}

int main()
{
  	vector<int> vector{ 4,3,2,1,6 };
	
	bubbleSort(vector);

	for (size_t i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i];
	}
}
