#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	//_pos 는 플레이어의 진짜 위치
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	Bfs();
}

void Player::Update(uint64 deltaTick)
{
	// path경로 다 소모
	if (_pathIndex >= _path.size())
		return;

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

void Player::Bfs()
{
	// 이동 하는 시뮬레이션 하기위한 임시 좌표
	Pos pos = _pos;

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos { -1, 0},	// UP
		Pos { 0, -1},	// LEFT
		Pos { 1, 0},	// DOWN
		Pos { 0, 1},	// RIGHT
	};

	// 발견 했는 지 여부를 추적
	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false));
	
	// vector<vector<Pos>> parent;
	// Parent[A] = B; -> A는 B로 인해 발견함
	map<Pos, Pos> parent;

	// Pos(int y, int x)
	queue<Pos> q;
	q.push(pos);
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

		for (int32 dir = 0; dir < 4; dir++)
		{
			// 다음좌표
			Pos nextPos = pos + front[dir];
			// 갈 수 있는 지역은 맞는지 확인.
			if (CanGo(nextPos) == false)
				continue;

			// 이미 발견한 지역인지 확인
			if (discovered[nextPos.y][nextPos.x])
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}

	// TODO
	// 두번 호출할까봐
	_path.clear();

	// 거꾸로 거슬러 올라간다
	pos = dest;
	while (true)
	{
		_path.push_back(pos);

		// 시작점은 자신이 곧 부모이다
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end());

	// 제일 처음 위치도 벡터에 넣어두기
	_path.push_back(pos);
}
