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
vector<bool> visited;

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6);
	
	// 인접 리스트 버전
	/*adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);*/

	// 인접 행렬
	adjacent = vector<vector<int>>
	{
		{0, 1, 0, 1, 0, 0},
		{1, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0},
	};
}

//DFS

// here : 시작 위치
// Dfs(0)
// -Dfs(1)
// --Dfs(2)
// --Dfs(3)
// ---Dfs(4)
// 시작점과 연결 된 정점만 순회함.

void Dfs(int here)
{
	// 방문 했는지 기록 해야함
	visited[here] = true;
	cout << "Visited : " << here << endl;

	// 인접 리스트 버전
	// 모든 인접 정점을 순회한다.
	//for (int i = 0; i < adjacent[here].size(); i++)
	//{
	//	//there은 목적지
	//	//ex) adjacent[0][0] -> 1 (1번 정점) // 0과 1은 연결
	//	//ex) adjacent[0][1] -> 3 (3번 정점) // 0과 3은 연결
	//	int there = adjacent[here][i];

	//	// 방문한 적이 없는 정점이라면
	//	if (visited[there] == false)
	//		Dfs(there);
	//}

	// 인접 행렬 버전
	// 모든 인접 정점을 순회한다.
	for (int there = 0; there < 6; there++)
	{
		// 연결이 안됐다.
		if (adjacent[here][there] == 0)
			continue;

		// 아직 방문하지 않은 곳 이 있으면 방문한다
		if (visited[there] = false)
			Dfs(there);
	}
}


// 연결 안된 정점도 순회하기 위한 함수
void DfsAll()
{
	visited = vector<bool>(6, false);

	for (int i = 0; i < vertices.size(); i++)
		if (visited[i] == false)
			Dfs(i);
}

int main()
{
	CreateGraph();

	// 6개 모두 false로 초기화
	//visited = vector<bool>(6, false);

	// 시작위치를 정점 0으로부터 시작 탐색
	//Dfs(0);

	DfsAll();
}