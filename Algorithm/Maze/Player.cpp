#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	//_pos �� �÷��̾��� ��¥ ��ġ
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	Bfs();
}

void Player::Update(uint64 deltaTick)
{
	// path��� �� �Ҹ�
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;

	// 0.1�ʰ� �����
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
	// �̵� �ϴ� �ùķ��̼� �ϱ����� �ӽ� ��ǥ
	Pos pos = _pos;

	// �ι� ȣ���ұ��
	_path.clear();
	// ���� ó�� ��ġ�� ���Ϳ� �־�α�
	_path.push_back(pos);

	// ������ �����ϱ� ������ ��� ����
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos { -1, 0},	// UP
		Pos { 0, -1},	// LEFT
		Pos { 1, 0},	// DOWN
		Pos { 0, 1},	// RIGHT
	};

	// �������� �����ϱ� ������ ����
	while (pos != dest)
	{
		// 1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ��� Ȯ��.
		// _dir - 1 �ϸ� ������ ����.
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		// ������ �������� �� �� �ִٸ� 
		// CanGo : �־��� Pos�� Empty���� ��ȯ
		if (CanGo(pos + front[newDir]))
		{
			// ������ �������� 90�� ȸ��.
			_dir = newDir;
			// ������ �� �� ����.
			pos += front[_dir];

			// �̵��ϸ� ���� ��� ���Ϳ� �־��ֱ�
			_path.push_back(pos);
		}
		// 2. ���� �ٶ󺸴� ������ �������� ������ �� �ִ��� Ȯ��.
		// _dir�� �÷��̾ ���� �ٶ󺸰� �ִ� ����
		else if (CanGo(pos + front[_dir]))
		{
			// ������ �� �� ����.
			pos += front[_dir];

			_path.push_back(pos);
		}
		else
		{
			// ���� �������� 90�� ȸ��.
			_dir = (_dir + 1) % DIR_COUNT;

		}
	}

	// path ��� ������ �������� ���ƿ��� ��� ����
	stack<Pos> s;

	//_path.size() - 1 : �������� ���������״ϱ�
	for (int i = 0; i < _path.size() - 1; i++)
	{
		// s.top() == _path[i + 1] : ���� ������ ������ ĭ�� ���ÿ� �� �ֻ��� ���� : �̹� ������ ��
		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}

	// ������ ĭ ���ÿ� �ֱ�
	if (_path.empty() == false)
		s.push(_path.back());

	// ���������� ���ư��� ��� ���Ϳ� ��
	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	// �ٽ� �������� 
	reverse(path.begin(), path.end());

	_path = path;
}


// bfs�� ��� ���������� ť�� �ְ�(���� �ƴϸ� ��������) ������ ���������� �θ� ������ �ϸ� �װ� �ִܰŸ� 
void Player::Bfs()
{
	// �̵� �ϴ� �ùķ��̼� �ϱ����� �ӽ� ��ǥ
	Pos pos = _pos;

	// ������ �����ϱ� ������ ��� ����
	Pos dest = _board->GetExitPos();

	// ����(y, x)
	Pos front[4] =
	{
		Pos { -1, 0},	// UP
		Pos { 0, -1},	// LEFT
		Pos { 1, 0},	// DOWN
		Pos { 0, 1},	// RIGHT
	};

	// �߰� �ߴ� �� ���θ� ����
	const int32 size = _board->GetSize(); // size 25 : ���ٿ� 25ĭ
	vector<vector<bool>> discovered(size, vector<bool>(size, false)); //discovered[y][x];
	
	// vector<vector<Pos>> parent;
	// Parent[A] = B; -> A�� B�� ���� �߰���/ B�� �θ�
	// m[key] = value; // map<key,value>
	map<Pos, Pos> parent;

	// Pos(int y, int x)
	queue<Pos> q;
	q.push(pos); // ������ q�� �ֱ�
	discovered[pos.y][pos.x] = true;

	// �������� �ڱ� �ڽ��� �θ�
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		// ���� �湮!
		if (pos == dest) // �����ϸ� ��
			break;

		for (int32 dir = 0; dir < 4; dir++) // pos���� �����¿�� �̵��������� üũ�ϰ� ť�� �ֱ�
		{
			// ������ǥ
			Pos nextPos = pos + front[dir];
			// �� �� �ִ� ������ �´��� Ȯ��. ���̸� false����
			if (CanGo(nextPos) == false)
				continue;

			// �̹� �߰��� �������� Ȯ��
			if (discovered[nextPos.y][nextPos.x])
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos; // nextPos�� parent�� ���� pos
		}
	}

	// TODO
	// �ι� ȣ���ұ��
	_path.clear(); // ������ �̵��� ��θ� �־��� vector

	// �Ųٷ� �Ž��� �ö󰣴�
	pos = dest;
	while (true)
	{
		_path.push_back(pos);

		// �������� �ڽ��� �� �θ��̴�/ pos�� �������̸� break
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end()); // �������κ��� �Ųٷ� �Ž��� �ö� path vector ������

	// ���� ó�� ��ġ�� ���Ϳ� �־�α�
	_path.push_back(pos);
}


