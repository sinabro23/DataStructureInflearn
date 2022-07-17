#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	//_pos �� �÷��̾��� ��¥ ��ġ
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	//Bfs();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	// path��� �� �Ҹ�
	if (_pathIndex >= _path.size())
	{
		_board->GenerateMap();
		Init(_board);
		return;
	}

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

}

struct PQNode // Priority_Queue
{
	// ���� �񱳸� ���� �����ڿ����ε�
	// greater<PQNode>�� ����
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
	// ���� �ű��
	// F = G + H 
	// F : ���� ����(���� ���� ����,  ��ο� ���� �޶���)
	// G : ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ��� (���� ���� ����, ��ο� ���� �޶���)
	// H : ���������� �󸶳� �������(���� ���� ����, ��ο� ���� �޶���)


	// �̵� �ϴ� �ùķ��̼� �ϱ����� �ӽ� ��ǥ
	Pos start = _pos;

	// ������ �����ϱ� ������ ��� ����
	Pos dest = _board->GetExitPos();

	enum
	{
		DIR_COUNT = 8 // �밢�� ������� ������ ���ϱ� ���� (4������ �밢�� �Ⱦ�)
	};

	// ����(y, x)
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

	// �̵��� �� ��� ���
	int32 cost[] =
	{
		10,		// UP
		10,		// LEFT
		10,		// DOWN
		10,		// RIGHT
		14,		// UP_LEFT // 10 * 1.4 ��Ʈ 2 ����
		14,		// DOWN_LEFT
		14,		// DOWN_RIGHT
		14,		// UP_RIGHT
	};

	// �߰� �ߴ� �� ���θ� ����
	const int32 size = _board->GetSize(); // size 25 : ���ٿ� 25ĭ

	// CloseList 
	// close[y][x] -> (y, x)�� �湮�� ���� �ִ��� ����
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	// best[y][x] -> ���ݱ��� (y, x)�� ���� ���� ���� ���(f) (���� ���� ����)
	vector<vector<int>> best(size, vector<int>(size, INT32_MAX));
	
	// �θ� ���� �뵵
	map<Pos, Pos> parent; // parent[A] = B; A�� �θ�� B;

	// OpenList : �湮�� ���� �ʾ����� �߰��� �͵��� OpenList�� ����// ���� ���� ������ ������ ��������
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// 1) ����(�߰�) �ý��� ����
	// 2) �ڴʰ� �� ���� ��ΰ� �߰ߵ� �� ���� -> ���� ó�� �ʼ�

	// �ʱⰪ
	{
		int32 g = 0; // G : ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ��� (���� ���� ����, ��ο� ���� �޶���)
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x)); 	// H : ���������� �󸶳� �������(���� ���� ����, ��ο� ���� �޶���) // 10�� �밢���� �ƴ� �� ĭ �̵��Ҷ��� �̵����
		pq.push(PQNode{ g + h, g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		// ���� ���� �ĺ��� ã�´�
		PQNode node = pq.top();
		pq.pop();

		// ������ ��ǥ�� ���� ��η� ã�Ƽ� �� ���� ��η� ���� �̹� �湮��(closed) ��� ��ŵ
		if (closed[node.pos.y][node.pos.x])
			continue;
		// �� ����� �ĺ��� �̹� ����
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;
		
		// �湮
		closed[node.pos.y][node.pos.x] = true;

		// �������� ���������� �ٷ� ����
		if (node.pos == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			// �� �� �ִ� ������ �´��� Ȯ��
			if (CanGo(nextPos) == false)
				continue;

			// [����] �̹� �湮�� ���̸� ��ŵ
			if (closed[nextPos.y][nextPos.x])
				continue;	

			// ��� ���
			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			// �ٸ� ��ο��� �� ���� ���� ã������ ��ŵ
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// ���� ����
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}

	}

	// �Ųٷ� �Ž��� �ö󰣴�
	Pos pos = dest;

	_pathIndex = 0;
	_path.clear(); // ������ �̵��� ��θ� �־��� vector

	while (true)
	{
		_path.push_back(pos);

		// �������� �ڽ��� �� �θ��̴�/ pos�� �������̸� break
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end()); // �������κ��� �Ųٷ� �Ž��� �ö� path vector ������

}


