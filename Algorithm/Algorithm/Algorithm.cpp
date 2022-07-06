#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// Queue : FIFO
// 대기열
template<typename T>
class Queue
{

};

int main()
{
	queue<int> q;

	for (int i = 0; i < 100; i++)
		q.push(i);

	while (q.empty() == false)
	{
		int value = q.front();
		q.pop();
		cout << value << endl;
	}

	int size = q.size();

	cout << size;
}