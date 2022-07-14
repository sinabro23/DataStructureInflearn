#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

struct Vertex
{

};

vector<Vertex> vertices;
vector<vector<int>> adjacent; // 인접 행렬

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1)); // 2차원 배열

	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	adjacent[1][0] = 35;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;
}

void Dijikstra(int here)
{
	// 가중치
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	// queue로 하지 않은 이유는 코스트가 있기 때문에
	list<VertexCost> discovered;
	// 각 정점별로 지금까지 발견한 최단 거리
	vector<int> best(6, INT32_MAX);
	vector<int> parent(6, -1);

	discovered.push_back(VertexCost({ here, 0 })); // here정점에 0대입 출발점이니깐
	best[here] = 0; // 시작점이니깐 최단 거리 0
	parent[here] = here;

	while (discovered.empty() == false)
	{
		// 제일 좋은 후보를 찾는다
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		// 순회
		for (auto it = discovered.begin(); it != discovered.end(); ++it)
		{
			if (it->cost < bestCost) // 더 우월한 후보일 때
			{
				bestCost = it->cost;
				bestIt = it;
			}
		}

		// q에서 pop하던것
		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		// 방문 ? 더 짧은 경로를 뒤늦게 찾았다면 스킵
		if (best[here] < cost)
			continue;

		// 진짜 방문
		for (int there = 0; there < 6; there++)
		{
			// 연결되지 않았으면 스킵.
			if (adjacent[here][there] == -1)
				continue;

			// 더 좋은 경로를 과거에 찾았으면 스킵.
			int nextCost = best[here] + adjacent[here][there];
			if (nextCost >= best[there])
				continue;

			// ( 3, 35 ) ( 3, 25 )
			discovered.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}
	}

	int a = 3;
}

int main()
{
	CreateGraph();
	Dijikstra(0);
}