#include <stdio.h>

typedef struct Treenode  //Treenode(���� Ʈ��) ����ü ���� ( ��� ��, ���� ���, ������ ���)
{
	int value;
	struct Treenode *left;
	struct Treenode *right;
}treenode;

treenode * ADD(treenode * root, int value); //�߰�
void DELETE(treenode * root, int value);    //����
treenode * SEARCH(treenode * root, int value); //Ž��
void PREORDER(treenode * root);  //root-left-right ������� ����

int main()
{
	treenode *main;    //treenode�� ������ ���� ����
	main = NULL;       //���� �ʱ�ȭ
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
	//1) root�� �ƿ� �������� �ʴ� ���
	if (root == NULL)
	{
		root = (treenode *)malloc(sizeof(treenode));  //�����޸��Ҵ����� root ����
		root->left = NULL;      //root->left, root->right �Լ� NULL�� �ʱ�ȭ
		root->right = NULL;
		root->value = value;   //root�� ���ϴ� value ����

		return root;     // root�� ��ȯ�ϴ� �� ���� ����. �Լ� ���� ���¸� treenode�� �����Ƿ� 
	}

	//2) �� �� �� ������ ���� ũ�� ������
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
		printf("�ߺ��� ���� �Է��� �� �����ϴ�.\n");
	}

	return root;
}

void DELETE(treenode * root, int value)
{
	//1) ���� ����(node, parent)
	treenode *node;
	treenode *parent;
	node = root;
	parent = NULL;


	//2) ���ϴ� ���� ����
	while (node->value != value && node != NULL)     //�����ϰ��� �ϴ� ������ ���� ���� ��尡 NULL�� ������ �ݺ�
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
		printf("ã���ô� ���� �����ϴ�.\n");


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