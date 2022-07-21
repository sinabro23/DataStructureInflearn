#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>
#include <map>
// 오늘의 주제 : 해시 테이블

// Q) map vs hash_map (C++11 표준 unordered_map)

// map : Red-Black Tree // 균형 이진 트리
// - 추가/탐색/삭제 0(logN)

// C# dictionary != c++ map
// C# dictionary != c++ unorderd_map(hash map)

// hash_map (unodered_map) 
// - 추가/탐색/삭제 0(1) 상수 

// 살을 내주고 뼈를 취한다
// 메모리를 내주고 속도를 취한다.
// 
// 아파트 우편함
// [201][202][203][204][205]
// [101][102][103][104][105]

// 키값 : 1~999 ex) user ID : 1~999
// 
// [1][2][3][][][][][][][][][][][999]

// '해시' '테이블'
// O(1)
void TestTable() // 테이블의 의미
{
	struct User
	{
		int userId = 0;
		string userName;
		// data
	};

	vector<User> users;
	users.resize(1000);
	
	// 777번 유저 정보 세팅
	users[777] = User{ 777, "Rookiss" };

	// 777번 유저 이름은?
	string name = users[777].userName;
	cout << name << endl;

	// 테이블의 의미
	// 키를 알면, 데이터를 단번에 찾을 수 있다. [1] [2] 통 하나

	// 문제의상황
	// 데이터 개수 int32_max개(3억~) 2147000000
	// 살을 내주는 것도 정도껏 내줘야함
	// -> 이문제를 해결 하기 위해 해시 기법
}

// 보안
// id : rookiss + pw : qwer1234 로 가입
// id : rookiss + pw : hash(qwer1234) -> sdfasdf!@#!ASDFd3(해시값) 일방적임 해시값으로 비밀번호를 돌릴 수 없음
// 
// DB에 [rookiss][sdfasdf!@#!ASDFd3] 저장
// 비밀번호 찾기 -> 아이디 입력 / 폰인증 -> 새 비밀번호 입력하세요 ( 해시값으로는 비밀번호를 알 수 없기 때문 )

void TestHash()
{
	struct User
	{
		int userId = 0; // 1 ~ INT32_MAX
		string userName;
		// data
	};

	// [][][][][][][][]
	vector<User> users;
	users.resize(1000);

	const int userId = 123456789;
	int key = (userId % 1000); // hash < 고유번호 // hash함수 : % 1000

	// 123456789번 유저 정보 세팅
	users[key] = User{ userId, "Rookiss" };

	// 123456789번 유저 이름은?
	User& user = users[key];
	if (user.userId == userId)
	{
		string name = user.userName;
		cout << name << endl;
	}
	
	// 문제점
	// 충돌 문제(동일한 키값 겹침)
	// 
	// 1) 충돌이 발생한 자리를 대신해서 다른 빈자리를 찾아나서면 된다.
	//		- 선형 조사법(linear probing)
	//			hash(key) + 1 -> hash(key) + 2 // 데이터가 뭉쳐져 있을 가능성이 높음
	//		- 이차 조사법(quadratic probing)
	//			hash(key) + 1^2 -> hash(key) + 2^2  // 데이터 분산을 위해
	
	// 체이닝 : 겹치면 세로로 다음칸에 밀어넣는 방법
	//       []
	// [][][][][][][][]
}

void TestHashTableChaining()
{
	struct User
	{
		int userId = 0; // 1 ~ INT32_MAX
		string userName;
		// data
	};

	// 천개의 칸만 사용
	// [][][][][][][][]
	vector<vector<User>> users;
	users.resize(1000);

	const int userId = 123456789;
	int key = (userId % 1000); // hash < 고유번호 // hash함수 : % 1000

	// 123456789번 유저 정보 세팅
	users[key].push_back(User{ userId, "Rookiss" });
	users[789].push_back(User{ 789, "Faker" });

	// 123456789번 유저 이름은 ? 
	vector<User>& bucket = users[key];

	for (User& user : bucket)
	{
		if(user.userId == userId)
		{
			string name = user.userName;
			cout << name << endl;
		}
	}
}

int main()
{
	//TestTable();
	//TestHash();
	TestHashTableChaining();
	
}