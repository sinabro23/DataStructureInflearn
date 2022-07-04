#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	//_pos 는 플레이어의 진짜 위치
	_pos = board->GetEnterPos();
	_board = board;

	// 이동 하는 시뮬레이션 하기위한 임시 좌표
	Pos pos = _pos;

	// 두번 호출할까봐
	_path.clear();
	// 제일 처음 위치도 벡터에 넣어두기
	_path.push_back(pos);

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = board->GetExitPos();

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