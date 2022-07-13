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

vector<Vertex> vertices; // 0,1,2,3,4,5 정점
vector<vector<int>> adjacent; // 정점에서 인접한 애들 넣어줄 벡터 ex) adjacent[0]은 0번 정점에 인접한 정점의 번호를 담고 있음
vector<bool> discovered; // 발견 타이밍 != 방문 타이밍

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6);

	// 인접 리스트
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
	//	{ 0, 1, 0, 1, 0, 0},
	//	{ 1, 0, 1, 1, 0, 0},
	//	{ 0, 0, 0, 0, 0, 0},
	//	{ 0, 0, 0, 0, 1, 0},
	//	{ 0, 0, 0, 0, 0, 0},
	//	{ 0, 0, 0, 0, 1, 0},
	//};
}

void Bfs(int here)
{
	// 추가정보들
	vector<int> parent(vertices.size(), -1); // 누구에 의해 발견 됐는지
	vector<int> distance(vertices.size(), -1); // 출발점으로부터 거리가 얼만큼인지

	queue<int> q; // 발견한 순서를 넣어주는 예약시스템
	q.push(here); // 예약시스템으로 queue사용 첫번째 정점 q에 삽입
	discovered[here] = true;

	parent[here] = here;
	distance[here] = 0;
	
	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		cout << "Visited : " << here << endl; // 이때 방문해서 데이터 실행

		for (int there : adjacent[here]) // here에서 인접한 애들 찾아서 예약시스템에 넣어주는 것
		{
			// discovered 가 true라는건 이미 발견해서 q에 예약이 됐다는것
			if (discovered[there] == true)
				continue;

			q.push(there);
			discovered[there] = true;

			parent[there] = here;
			distance[there] = distance[here] + 1;

		}
	}

}

void BfsAll()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (discovered[i] == false)
			Bfs(i);
	}
}

int main()
{
	CreateGraph();
	discovered = vector<bool>(6, false);
	BfsAll();
}