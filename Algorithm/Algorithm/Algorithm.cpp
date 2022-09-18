#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// 정점 자체에 간선 정보 저장
void CreateGraph_1()
{
	struct Vertex
	{
		vector<Vertex*> edges;
		int data;
	};

	vector<Vertex> v;
	v.resize(6);

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	// 0 번 -> 3번 정점이 연결?
	bool connected = false;
	for (Vertex* edge : v[0].edges)
	{
		if (edge == &v[3])
		{
			connected = true;
			break;
		}
	}
}
// 정점 간선 따로관리
void CreateGraph_2()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex*> edges;

	vector<Vertex> v;
	v.resize(6);

	// 연결된 목록을 따로 관리하자
	vector<vector<int>> adjacent(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// 0 번 -> 3번 정점이 연결?
	bool connected = false;
	//for (int vertex : adjacent[0])
	//{
	//	if (vertex == 3)
	//	{
	//		connected = true;
	//		break;
	//	}
	//}

	//STL
	vector<int>& adj = adjacent[0];
	connected = (std::find(adj.begin(), adj.end(), 3) != adj.end());
	
}
// 순회없이 바로 접근 가능한 그래프
void CreateGraph_3()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v;
	v.resize(6);
	

	// 읽는 방법 : adjacent[from][to]
	// 빠른접근 가능
	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;
	
	// 0->3 연결?
	bool connected = adjacent[0][3];

	vector<vector<int>> adjacent2 =
	{
		vector<int> { -1, 15, -1, 35, -1, -1 },
		vector<int> { 15, -1, +5, 10, -1, -1 },
		vector<int> { -1, -1, -1, -1, -1, -1 },
		vector<int> { -1, -1, -1, -1, +5, -1 },
		vector<int> { -1, -1, -1, -1, -1, -1 },
		vector<int> { -1, -1, -1, -1, +5, -1 },
	};


}

int main()
{
	CreateGraph_1();
	CreateGraph_2();
	return 0;
}
