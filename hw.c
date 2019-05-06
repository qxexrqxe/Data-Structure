#include <stdio.h>

typedef struct Treenode  //Treenode(이진 트리) 구조체 생성 ( 노드 값, 왼쪽 노드, 오른쪽 노드)
{
	int value;
	struct Treenode *left;
	struct Treenode *right;
}treenode;

treenode * ADD(treenode * root, int value); //추가
void DELETE(treenode * root, int value);    //삭제
treenode * SEARCH(treenode * root, int value); //탐색
void PREORDER(treenode * root);  //root-left-right 순서대로 나열

int main()
{
	treenode *main;    //treenode형 포인터 변수 생성
	main = NULL;       //변수 초기화
	main = ADD(main, 10);
	main = ADD(main, 13);
	main = ADD(main, 15);
	main = ADD(main, 4);
	main = ADD(main, 7);
	main = ADD(main, 2);
	main = ADD(main, 12);
	main = ADD(main, 16);
	main = ADD(main, 1);
	main = ADD(main, 3);
	main = ADD(main, 19);
	main = ADD(main, 14);
	main = ADD(main, 11);
	main = ADD(main, 6);
	main = ADD(main, 8);

	DELETE(main, 10);

	PREORDER(main);


	PREORDER(SEARCH(main, 4));

	return 0;
}

treenode * ADD(treenode * root, int value)
{
	//1) root가 아예 존재하지 않는 경우
	if (root == NULL)
	{
		root = (treenode *)malloc(sizeof(treenode));  //동적메모리할당으로 root 생성
		root->left = NULL;      //root->left, root->right 함수 NULL로 초기화
		root->right = NULL;
		root->value = value;   //root에 원하는 value 저장

		return root;     // root로 반환하는 것 잊지 말기. 함수 선언 형태를 treenode로 했으므로 
	}

	//2) 값 비교 후 작으면 왼쪽 크면 오른쪽
	if (root->value > value)
	{
		root->left = ADD(root->left, value);
	}
	else if (root->value < value)
	{
		root->right = ADD(root->right, value);
	}
	else
	{
		printf("중복된 값을 입력할 수 없습니다.\n");
	}

	return root;
}

void DELETE(treenode * root, int value)
{
	//1) 변수 생성(node, parent)
	treenode *node;
	treenode *parent;
	node = root;
	parent = NULL;


	//2) 원하는 변수 삭제
	while (node->value != value && node != NULL)     //삭제하고자 하는 변수의 값이 없고 노드가 NULL일 때까지 반복
	{
		if (node->value > value)
			node = node->left;
		else if (node->value < value)
			node = node->right;
		parent = node;
	}
	if (node == NULL)
		return;

	if (node->left == NULL && node->right == NULL)
	{
		if (parent == NULL)
			root = NULL;
		else if (parent != NULL)
		{
			if (parent->left == node)
				parent->left = NULL;
			else if (parent->right == node)
				parent->right = NULL;
		}
	}
	else if (node->left == NULL || node->right == NULL)
	{
		treenode * child;

		if (node->left == NULL)
			child = node->right;
		else
			child = node->left;


		if (parent == NULL)
			root = child;
		else if (parent != NULL)
		{
			if (parent->left == node)
			{
				parent->left = child;
			}
			else
			{
				parent->right = child;
			}
		}
	}
	else
	{
		treenode *node2;
		treenode *parent2;

		parent2 = node;
		node2 = parent2->left;
		while (node2->right != NULL)
		{
			parent2 = node2;
			node2 = node2->right;

		}

		if (parent2->left == node2)
			parent2->left = node2->left;
		else
			parent2->right = node2->left;
		node->value = node2->value;
		node = node2;

	}
	free(node);
}
treenode * SEARCH(treenode * root, int value)
{
	treenode * node;
	node = root;
	while (node->value != value)
	{
		if (root->value > value)
			node = node->left;
		else if (root->value < value)
			node = node->right;
	}

	if (node == NULL)
		printf("찾으시는 값이 없습니다.\n");


	return node;
}
void PREORDER(treenode * root)
{
	if (root != NULL)
	{
		printf("%d_", root->value);
		PREORDER(root->left);
		PREORDER(root->right);
	}
}