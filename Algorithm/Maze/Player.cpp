#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	//_pos �� �÷��̾��� ��¥ ��ġ
	_pos = board->GetEnterPos();
	_board = board;

	// �̵� �ϴ� �ùķ��̼� �ϱ����� �ӽ� ��ǥ
	Pos pos = _pos;

	// �ι� ȣ���ұ��
	_path.clear();
	// ���� ó�� ��ġ�� ���Ϳ� �־�α�
	_path.push_back(pos);

	// ������ �����ϱ� ������ ��� ����
	Pos dest = board->GetExitPos();

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