#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>
using namespace std;

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}


void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr)
		return;

	SetCursorPosition(x, y);
	cout << node->key ;
	Print(node->left, x - (5 / (y + 1)) , y + 1);
	Print(node->right, x + (5 / (y + 1)) , y + 1);
}

void BinarySearchTree::Print_Inorder(Node* node)
{
	// 전위 순회 (preorder traverse)
	// 중위 순회 (inorder)
	// 후위 순회 (postorder)
	
	//   [중]
	// [좌][우]

	if (node == nullptr)
		return;

	// 전위 순회 (중간 노드가 언제 오는지) [중][좌][우] -> 전위순회
	cout << node->key << endl;
	Print_Inorder(node->left);
	Print_Inorder(node->right);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == nullptr || key == node->key)
		return node;

	if (key < node->key)
		return Search(node->left, key);
	else
		return Search(node->right, key);

}

Node* BinarySearchTree::Search2(Node* node, int key)
{
	while (node && key != node->key)
	{
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	return node;
}

Node* BinarySearchTree::Min(Node* node)
{
	while (node->left)
		node = node->left;

	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node->right)
		node = node->right;

	return node;
}

Node* BinarySearchTree::Next(Node* node)
{
	// 오른쪽 노드가 있다면
	if (node->right) 
		return Min(node->right);

	Node* parent = node->parent;

	// 나를 왼쪽 차일드로 들고 있는 부모를 만날때까지
	while (parent && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;

}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	Node* node = _root;
	Node* parent = nullptr;

	while (node)
	{
		parent = node;
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	newNode->parent = parent;

	if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;
}

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	//child 하나 이거나 없거나
	if (node->left == nullptr)
		Replace(node, node->right); // 없어도 null이 차지하게됨
	else if(node->right == nullptr)
		Replace(node, node->left);
	else // 양쪽의 child가 있을때
	{
		// 다음 데이터 찾기
		Node* next = Next(node);
		// 데이터이전
		node->key = next->key;
		Delete(next);
	}

}

// u 서브트리를 v서브트리로 교체
// 그리고 delete u

void BinarySearchTree::Replace(Node* u, Node* v)
{
	// u가 최상위 노드였다면
	if (u->parent == nullptr)
		_root = v;
	// u가 왼쪽 자식이였다면
	else if (u == u->parent->left)
		u->parent->left = v;
	// u가 오른쪽 자식이였다면
	else
		u->parent->right = v;
	
	// nullptr로 밀어주고 싶을때도 쓰기 위해 (v를 null로 밀면)
	if (v)
		v->parent = u->parent;

	delete u;
}
