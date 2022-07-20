#pragma once

//		[ 10 ]
//	 [ 8 ] [ 12 ]


enum class Color
{
	Red = 0,
	Black = 1,
};

struct Node
{
	Node*	parent = nullptr;
	Node*	left = nullptr;
	Node*	right = nullptr;
	int		key = {};
	// data는 원래 따로 

	Color color = Color::Black;
};

// RBT
// 1) 모든 노드는 Red or Black
// 2) Root 는 black
// 3) Leaf(Nil)는 Black
// 4) Red노드의 자식은 Black ( red연속 안됨 )
// 5) 각 노드로 부터 리프까지 가는 경로들은 모두 같은 수의 블랙 노드를 만난다

class BinarySearchTree
{
public:

	BinarySearchTree();
	~BinarySearchTree();

	void	Print() { Print(_root, 10, 0); }
	void	Print(Node* node, int x, int y);

	Node*	Search(Node* node, int key);

	Node*	Min(Node* node);
	Node*	Max(Node* node);
	Node*	Next(Node* node);

	void	Insert(int key);
	// 규칙을 잘 지키는지 체크
	void	InsertFixup(Node* node);

	void	Delete(int key);
	void	Delete(Node* node);
	// u의 서브트리를 v서브트리로 교체
	void	Replace(Node* u, Node* v);

	// Red-Black Tree 전용함수
	void LeftRotate(Node* x);
	void RightRotate(Node* y);


	Node*	GetRootNode() { return _root; }

private:
	Node* _root = nullptr;
	Node* _nil = nullptr;
};

