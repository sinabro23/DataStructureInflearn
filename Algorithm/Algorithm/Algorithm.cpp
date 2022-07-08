#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;



struct Vertex
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

// 방문한 정점인지 확인하기 위해
vector<bool> discovered;

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6);
	
	// 인접 리스트 버전
	adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);

	// 인접 행렬
	//adjacent = vector<vector<int>>
	//{
	//	{0, 1, 0, 1, 0, 0},
	//	{1, 0, 1, 1, 0, 0},
	//	{0, 0, 0, 0, 0, 0},
	//	{0, 0, 0, 0, 1, 0},
	//	{0, 0, 0, 0, 0, 0},
	//	{0, 0, 0, 0, 1, 0},
	//};
}


void Bfs(int here)
{
	// 누구에 의해서 발견 되었는지?
	vector<int> parent(6, -1); // -1로 초기화
	// 시작점에서 얼마나 떨어져 있는지
	vector<int> distance(6, -1); // -1로 초기화

	queue<int> q;
	q.push(here);
	discovered[here] = true;

	parent[here] = here; // 시작점은 자기 자신에 의해 발견됨
	distance[here] = 0;

	// 0 q[  ]
	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		// 방문은 이 때 ( != 발견 )
		cout << "Visited : " << here << endl;

		// bfs는 발견만하고 방문은 안 할 수 있음.(DFS는 발견하면 방문하는 것이었음)
		for (int there : adjacent[here])
		{
			// 이미 발견된 곳이라면
			if (discovered[there])
				continue;	

			// 0 일때 1, 3 이 q에 예약이 들어감
			q.push(there);
			// 0 일때 1, 3 이 발견됨
			discovered[there] = true;

			parent[there] = here; // here라는 정점에 의해 there로 발견 됐다.
			distance[there] = distance[here] + 1; // 시작점에서 here까지의 거리에 + 1만하면 there까지의 거리
		}
	}


}

void BfsAll()
{
	for (int i = 0; i < 6; i++)
		if (discovered[i] == false)
			Bfs(i);
}

int main()
{
	CreateGraph();
	discovered = vector<bool>(6, false);
	Bfs(0);
}