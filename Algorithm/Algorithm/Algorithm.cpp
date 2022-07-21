#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>


// Quick Sort 
// pivot(기준점, 제일 첫데이터), low(pivot다음), high(제일끝)
// 
// 1단계)
//	- pivot >= arr[low]일 동안 low를 오른쪽으로 이동
//  - pivot <= arr[high]일 동안 high를 왼쪽으로 이동
// 2단계)
//	- low < high 라면, arr[low]와 arr[high] 데이터 교체
// 3단계)
//	- high<=low면 빠져나오고, pivot과 arr[high] 교체

int Partition(vector<int>&v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	// O(N)
	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
			low++;
		while (high >= left + 1 && pivot <= v[high])
			high--;

		// 역전이 안됐으면 스왑
		if (low < high)
			swap(v[low], v[high]);
	}

	// 3단계
	swap(v[left], v[high]);

	// 스왑된 위치의 인덱스
	return high;
}

//  p  l                    h
// [5][1][3][7][9][2][4][6][8]
// O(N^2) 최악
// O(NlogN) 평균
void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
		return;

	int pivot = Partition(v, left, right);
	QuickSort(v, left, pivot - 1); // 왼쪽
	QuickSort(v, pivot + 1, right); // 오른쪽
}

int main()
{
	vector<int> v;

	srand(time(0));

	for (int i = 0; i < 50; i++)
	{
		int randValue = rand() % 100;
		v.push_back(randValue);
	}

	//BubbleSort(v);
	//SelectionSort(v);
	//InsertionSort(v);
	//HeapSort(v);
	//MergeSort(v, 0, v.size() - 1);

	QuickSort(v, 0, v.size() - 1);
}