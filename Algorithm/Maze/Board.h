#pragma once
#include "ConsoleHelper.h"

enum
{
	BOARD_MAX_SIZE = 100
};

enum class TileType
{
	NONE = 0,
	EMPTY,
	WALL,
};

class Player;
class Board
{
public:
	Board();
	~Board();

	void			Init(int32 size, Player* player);
	void			Render();

	// 사이즈 크기 만큼의 맵 만드는 함수
	void			GenerateMap();
	// 위치값에 어떠한 타일이 있는지 반환
	TileType		GetTileType(Pos pos);
	// 위치의 어떠한 색상을 입혀야하는지 반환
	ConsoleColor	GetTileColor(Pos pos);

	// 시작 포지션
	Pos				GetEnterPos() { return Pos{ 1 ,1 };	}
	// 출구 포지션
	Pos				GetExitPos() { return Pos{ _size - 2 , _size - 2 };	}
	int32			GetSize() { return _size; }


private:
	TileType		_tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
	int32			_size = 0;
	Player*			_player = nullptr;
};

