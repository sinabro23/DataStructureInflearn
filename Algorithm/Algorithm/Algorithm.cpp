#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

// 1) 버블 정렬 (Bubble Sort)
//    2개씩 
void BubbleSort(vector<int>& v)
{
	const int n = (int)v.size();

	// 연산 횟수
	// (n-1) + (n-2) + ... + 2 + 1
	// 등차수열의 합 = N*(N-1) / 2 ==> O(n^2)
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < (n - 1 - i); j++)
		{
			if (v[j] > v[j + 1])
			{
				// 2중 for문 안에 swap
				::swap(v[j], v[j + 1]);
			}
		}
	}
}
// 2) 선택 정렬 (Selection Sort)
//    [5][J][3][K][9]
//    [3][J][5][K][9] -- 1라운드
//	  제일 작은 숫자를 찾아서 제일 앞으로
void SelectionSort(vector<int>& v)
{
	const int n = (int)v.size();

	// 연산 횟수
	// (n-1) + (n-2) + ... + 2 + 1
	// 등차수열의 합 = N*(N-1) / 2 ==> O(n^2)

	for (int i = 0; i < n - 1; i++)
	{
		int bestIdx = i;

		for (int j = i + 1; j < n; j++)
		{
			if (v[i] > v[j])
				bestIdx = j;
		}

		// 2중 for문 밖에 swap
		::swap(v[i], v[bestIdx]);
	}
}

// 3) 삽입 정렬 (Insertion Sort) 
// [5][J][9][3][K]

void InsertionSort(vector<int>& v)
{
	const int n = (int)v.size();

	// 제일 처음 데이터는 할 필요없으니 스킵하고 1번부터
	for (int i = 1; i < n; i++)
	{
		int insertData = v[i];

		int j = 0;
		for (j = i - 1; j >= 0; j--)
		{
			if (v[j] > insertData)
				v[j + 1] = v[j];
			else
				break;
		}

		v[j + 1] = insertData;
	}
}


int main()
{
	vector<int> v{ 1,5,3,4,2 };

	//BubbleSort(v);
	//SelectionSort(v);
	InsertionSort(v);

}