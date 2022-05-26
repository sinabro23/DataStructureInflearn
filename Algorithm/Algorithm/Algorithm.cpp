#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Vector // 동적배열
{
public:
	Vector()
	{

	}
	~Vector()
	{
		if (_data)
			delete[] _data;
	}

	void push_back(const T& value)
	{
		if (_size == _capacity)
		{
			// 증설 작업
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity == _capacity) // 0일 수도 있음
				newCapacity++;

			reserve(newCapacity);
		}

		// 데이터 저장
		_data[_size] = value;
		_size++;
	}

	void reserve(int capacity)
	{
		if (_capacity >= capacity)
			return;

		_capacity = capacity;

		T* newData = new T[_capacity];
		
		// 기존 데이터 복사
		for (int i = 0; i < _size; i++)
			newData[i] = _data[i];

		// 기존 데이터 삭제
		if(_data)
			delete[] _data;

		// 교체
		_data = newData;
	}

	T& operator[](const int pos) { return _data[pos]; }

	int size() { return _size; }
	int capacity() { return _capacity; }

	void clear()
	{
		if (_data)
		{
			delete[] _data;
			_data = new T[_capacity];
		}

		_size = 0;
	}

private:
	// 동적 배열의 시작 위치
	T*		_data = nullptr;
	int		_size = 0;
	int		_capacity = 0;

};

int main()
{
	vector<int> v;
	
	v.resize(10);
	v.reserve(100);

	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout << v[i] << " " << v.size() << " " << v.capacity() << endl;
	}

	v.clear();
	cout << v.size() << " " << v.capacity() << endl;
}
