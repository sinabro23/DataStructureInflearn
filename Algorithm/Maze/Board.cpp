#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"

const char* TILE = "■";

Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(int32 size, Player* player)
{
	_size = size;	
	_player = player;

	GenerateMap();
}


void Board::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);

	for (int32 y = 0; y < 25; y++)
	{
		for (int32 x = 0; x < 25; x++)
		{
			ConsoleColor color = GetTileColor(Pos{ y, x });
			ConsoleHelper::SetCursorColor(color);

			cout << TILE;
		}

		cout << endl;
	}
}

// Binary Tree 미로 생성 알고리즘
void Board::GenerateMap()
{
	for(int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			// 외곽과 2칸마다 벽으로 채우기
			if (x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}

	// Empty인 곳 기준으로 랜덤으로 우측 혹은 아래로 길을 뚫는 작업
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			// 벽인 부분은 Continue
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 끝지점에 도달하면 더이상 뚫지 않기
			if (y == _size - 2 && x == _size - 2)
				continue;
			
			// 제일 아래로 갔을 경우(아래로 뚫으면 안됨)
			if (y == _size - 2)
			{
				// 오른쪽으로만 뚫기
				_tile[y][x + 1] = TileType::EMPTY;
				continue;
			}

			// 제일 오른쪽으로 갔을 경우 (오른쪽으로 뚫으면 안됨)
			if (x == _size - 2)
			{
				// 아래로만 뚫기 뚫기
				_tile[y + 1][x] = TileType::EMPTY;
				continue;
			}


			const int32 randValue = ::rand() % 2;
			if (randValue == 0)
			{
				// 오른쪽 뚫기
				_tile[y][x + 1] = TileType::EMPTY;
			}
			else
			{
				// 아래 뚫기
				_tile[y+1][x] = TileType::EMPTY;
			}
			
		}
	}
}

TileType Board::GetTileType(Pos pos)
{
	// 범위체크
	if (pos.x < 0 || pos.x >= _size)
		return TileType::NONE;

	if (pos.y < 0 || pos.y >= _size)
		return TileType::NONE;

	return _tile[pos.y][pos.x];
	
}

ConsoleColor Board::GetTileColor(Pos pos)
{
	// 플레이어가 존재하고 플레이어 포지션이이라면 노란색으로
	if (_player && _player->GetPos() == pos)
		return ConsoleColor::YELLOW;

	// 출구는 파란색으로
	if (GetExitPos() == pos)
		return ConsoleColor::BLUE;

	// 입력받은 위치(pos)의 타일 타입을 가져와서
	TileType tileType = GetTileType(pos);

	// 타일 타입에 따른 색
	switch (tileType)
	{
	case TileType::EMPTY:
		return ConsoleColor::GREEN;
	case TileType::WALL:
		return ConsoleColor::RED;
	}

	return ConsoleColor::WHITE;
}
