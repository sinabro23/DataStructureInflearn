#include "pch.h"
#include <iostream>
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"

// 보트 하나 전역으로
Board board;
Player player;

int main()
{
	// 시드값넣기(랜덤으로 미로 만들기 위한)
	::srand(static_cast<unsigned>(time(nullptr)));
	// 보드 25칸 짜리로 초기화
	board.Init(25, &player);
	player.Init(&board);

	uint64 lastTick = 0;

	while (true)
	{
#pragma region 프레임 관리
		// 프레임 초당 While문 몇번 돌것인지 (현재시간)
		const uint64 currentTick = ::GetTickCount64();
		// 현재시간 - 이전시간 = 경과시간
		const uint64 deltaTick = currentTick - lastTick;
		lastTick = currentTick;
#pragma endregion

		// 입력

		// 로직
		player.Update(deltaTick);

		// 렌더링
		board.Render();


	}
}

