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
	// data�� ���� ���� 

	Color color = Color::Black;
};

// RBT
// 1) ��� ���� Red or Black
// 2) Root �� black
// 3) Leaf(Nil)�� Black
// 4) Red����� �ڽ��� Black ( red���� �ȵ� )
// 5) �� ���� ���� �������� ���� ��ε��� ��� ���� ���� �� ��带 ������

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
	// ��Ģ�� �� ��Ű���� üũ
	void	InsertFixup(Node* node);

	void	Delete(int key);
	void	Delete(Node* node);
	// u�� ����Ʈ���� v����Ʈ���� ��ü
	void	Replace(Node* u, Node* v);

	// Red-Black Tree �����Լ�
	void LeftRotate(Node* x);
	void RightRotate(Node* y);


	Node*	GetRootNode() { return _root; }

private:
	Node* _root = nullptr;
	Node* _nil = nullptr;
};

