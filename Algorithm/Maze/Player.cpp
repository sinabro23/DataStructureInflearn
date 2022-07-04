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
			/*
			switch (_dir)
			{
			case DIR_UP:
				_dir = DIR_LEFT;
				break;
			case DIR_LEFT:
				_dir = DIR_DOWN;
				break;
			case DIR_DOWN:
				_dir = DIR_RIGHT;
				break;
			case DIR_RIGHT:
				_dir = DIR_UP;
				break;
			}
			*/
		}
	}
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