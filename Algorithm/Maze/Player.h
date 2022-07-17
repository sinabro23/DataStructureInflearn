#pragma once

class Board;

class Player
{
	enum
	{
		MOVE_TICK = 100
	};

public:
	void		Init(Board* board);
	void		Update(uint64 deltaTick);

	void		SetPos(Pos pos) { _pos = pos; }
	Pos			GetPos() { return _pos; }

	bool		CanGo(Pos pos);

private:
	void		RightHand();
	void		Bfs();
	void		AStar();

private:
	Pos			_pos = {};
	int32		_dir = DIR_UP;
	Board* _board = nullptr;

	// Init에서 이동할 경로 다 계산 해서 push_back 해 놓을 것임, 업데이트에서 하나씩 소모하면서 이동할것
	vector<Pos>	_path;
	// 현재 vector에 들어간 경로 기준으로 어디를 이동하고있는지 체크
	uint32		_pathIndex = 0;
	// 현재까지의 Tick
	uint64		_sumTick = 0;
};

