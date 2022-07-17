#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	//_pos 는 플레이어의 진짜 위치
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	//Bfs();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	// path경로 다 소모
	if (_pathIndex >= _path.size())
	{
		_board->GenerateMap();
		Init(_board);
		return;
	}

	_sumTick += deltaTick;

	// 0.1초가 경과됨
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
	// 이동 하는 시뮬레이션 하기위한 임시 좌표
	Pos pos = _pos;

	// 두번 호출할까봐
	_path.clear();
	// 제일 처음 위치도 벡터에 넣어두기
	_path.push_back(pos);

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos { -1, 0},	// UP
		Pos { 0, -1},	// LEFT
		Pos { 1, 0},	// DOWN
		Pos { 0, 1},	// RIGHT
	};

	// 목적지에 도달하기 전까지 실행
	while (pos != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인.
		// _dir - 1 하면 오른쪽 방향.
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		// 오른쪽 방향으로 갈 수 있다면 
		// CanGo : 넣어준 Pos가 Empty인지 반환
		if (CanGo(pos + front[newDir]))
		{
			// 오른쪽 방향으로 90도 회전.
			_dir = newDir;
			// 앞으로 한 보 전진.
			pos += front[_dir];

			// 이동하면 가는 경로 벡터에 넣어주기
			_path.push_back(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인.
		// _dir은 플레이어가 현재 바라보고 있는 방향
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한 보 전진.
			pos += front[_dir];

			_path.push_back(pos);
		}
		else
		{
			// 왼쪽 방향으로 90도 회전.
			_dir = (_dir + 1) % DIR_COUNT;

		}
	}

	// path 계산 끝나고 스택으로 돌아오는 경로 삭제
	stack<Pos> s;

	//_path.size() - 1 : 마지막은 도착지일테니깐
	for (int i = 0; i < _path.size() - 1; i++)
	{
		// s.top() == _path[i + 1] : 내가 다음에 가야할 칸이 스택에 들어간 최상위 원소 : 이미 지나온 곳
		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}

	// 목적지 칸 스택에 넣기
	if (_path.empty() == false)
		s.push(_path.back());

	// 목적지부터 돌아가는 길로 벡터에 들어감
	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	// 다시 역순으로 
	reverse(path.begin(), path.end());

	_path = path;
}


// bfs로 모든 인접지역을 큐에 넣고(벽이 아니면 인접지역) 끝부터 시작점까지 부모를 역추적 하면 그게 최단거리 
void Player::Bfs()
{
	// 이동 하는 시뮬레이션 하기위한 임시 좌표
	Pos pos = _pos;

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = _board->GetExitPos();

	// 방향(y, x)
	Pos front[4] =
	{
		Pos { -1, 0},	// UP
		Pos { 0, -1},	// LEFT
		Pos { 1, 0},	// DOWN
		Pos { 0, 1},	// RIGHT
	};

	// 발견 했는 지 여부를 추적
	const int32 size = _board->GetSize(); // size 25 : 한줄에 25칸
	vector<vector<bool>> discovered(size, vector<bool>(size, false)); //discovered[y][x];
	
	// vector<vector<Pos>> parent;
	// Parent[A] = B; -> A는 B로 인해 발견함/ B가 부모
	// m[key] = value; // map<key,value>
	map<Pos, Pos> parent;

	// Pos(int y, int x)
	queue<Pos> q;
	q.push(pos); // 시작점 q에 넣기
	discovered[pos.y][pos.x] = true;

	// 시작점은 자기 자신이 부모
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		// 실제 방문!
		if (pos == dest) // 도착하면 끝
			break;

		for (int32 dir = 0; dir < 4; dir++) // pos에서 상하좌우로 이동가능한지 체크하고 큐에 넣기
		{
			// 다음좌표
			Pos nextPos = pos + front[dir];
			// 갈 수 있는 지역은 맞는지 확인. 벽이면 false리턴
			if (CanGo(nextPos) == false)
				continue;

			// 이미 발견한 지역인지 확인
			if (discovered[nextPos.y][nextPos.x])
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos; // nextPos의 parent는 현재 pos
		}
	}

	// TODO
	// 두번 호출할까봐
	_path.clear(); // 실제로 이동할 경로를 넣어줄 vector

	// 거꾸로 거슬러 올라간다
	pos = dest;
	while (true)
	{
		_path.push_back(pos);

		// 시작점은 자신이 곧 부모이다/ pos가 시작점이면 break
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end()); // 목적지로부터 거꾸로 거슬러 올라간 path vector 뒤집기

}

struct PQNode // Priority_Queue
{
	// 점수 비교를 위한 연산자오버로딩
	// greater<PQNode>의 기준
	bool operator<(const PQNode& other) const
	{
		return f < other.f;
	}

	bool operator>(const PQNode& other) const
	{
		return f > other.f;
	}

	int32	f; // f = g + h
	int32	g;
	Pos		pos;
};

void Player::AStar()
{
	// 점수 매기기
	// F = G + H 
	// F : 최종 점수(작을 수록 좋음,  경로에 따라 달라짐)
	// G : 시작점에서 해당 좌표까지 이동하는데 드는 비용 (작을 수록 좋음, 경로에 따라 달라짐)
	// H : 목적지에서 얼마나 가까운지(작을 수록 좋음, 경로에 따라 달라짐)


	// 이동 하는 시뮬레이션 하기위한 임시 좌표
	Pos start = _pos;

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = _board->GetExitPos();

	enum
	{
		DIR_COUNT = 8 // 대각선 사용할지 안할지 정하기 위함 (4까지면 대각선 안씀)
	};

	// 방향(y, x)
	Pos front[] =
	{
		Pos { -1, 0},	// UP
		Pos { 0, -1},	// LEFT
		Pos { 1, 0},	// DOWN
		Pos { 0, 1},	// RIGHT
		Pos { -1, -1},  // UP_LEFT
		Pos { 1, -1},	// DOWN_LEFT
		Pos { 1, 1},	// DOWN_RIGHT
		Pos { -1, 1},	// UP_RIGHT
	};

	// 이동할 때 드는 비용
	int32 cost[] =
	{
		10,		// UP
		10,		// LEFT
		10,		// DOWN
		10,		// RIGHT
		14,		// UP_LEFT // 10 * 1.4 루트 2 정도
		14,		// DOWN_LEFT
		14,		// DOWN_RIGHT
		14,		// UP_RIGHT
	};

	// 발견 했는 지 여부를 추적
	const int32 size = _board->GetSize(); // size 25 : 한줄에 25칸

	// CloseList 
	// close[y][x] -> (y, x)에 방문한 적이 있는지 여부
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	// best[y][x] -> 지금까지 (y, x)에 대한 가장 좋은 비용(f) (작을 수록 좋음)
	vector<vector<int>> best(size, vector<int>(size, INT32_MAX));
	
	// 부모 추적 용도
	map<Pos, Pos> parent; // parent[A] = B; A의 부모는 B;

	// OpenList : 방문은 하지 않았지만 발견한 것들을 OpenList로 관리// 제일 작은 숫자의 점수가 먼저나옴
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// 1) 예약(발견) 시스템 구현
	// 2) 뒤늦게 더 좋은 경로가 발견될 수 있음 -> 예외 처리 필수

	// 초기값
	{
		int32 g = 0; // G : 시작점에서 해당 좌표까지 이동하는데 드는 비용 (작을 수록 좋음, 경로에 따라 달라짐)
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x)); 	// H : 목적지에서 얼마나 가까운지(작을 수록 좋음, 경로에 따라 달라짐) // 10은 대각선이 아닌 한 칸 이동할때의 이동비용
		pq.push(PQNode{ g + h, g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾는다
		PQNode node = pq.top();
		pq.pop();

		// 동일한 좌표를 여러 경로로 찾아서 더 빠른 경로로 인해 이미 방문된(closed) 경우 스킵
		if (closed[node.pos.y][node.pos.x])
			continue;
		// 더 우수한 후보가 이미 있음
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;
		
		// 방문
		closed[node.pos.y][node.pos.x] = true;

		// 목적지에 도착했으면 바로 종료
		if (node.pos == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			// 갈 수 있는 지역은 맞는지 확인
			if (CanGo(nextPos) == false)
				continue;

			// [선택] 이미 방문한 곳이면 스킵
			if (closed[nextPos.y][nextPos.x])
				continue;	

			// 비용 계산
			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			// 다른 경로에서 더 빠른 길을 찾았으면 스킵
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// 예약 진행
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}

	}

	// 거꾸로 거슬러 올라간다
	Pos pos = dest;

	_pathIndex = 0;
	_path.clear(); // 실제로 이동할 경로를 넣어줄 vector

	while (true)
	{
		_path.push_back(pos);

		// 시작점은 자신이 곧 부모이다/ pos가 시작점이면 break
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end()); // 목적지로부터 거꾸로 거슬러 올라간 path vector 뒤집기

}


