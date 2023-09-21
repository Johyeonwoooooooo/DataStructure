#include<iostream>
#include<string>
#include <sstream>
#define MaxSize 1000
using namespace std;

class TreeNode
{
private:
	TreeNode(string name, TreeNode* child = nullptr, TreeNode* freind_worker = nullptr);
	string name;
	TreeNode* child;
	TreeNode* friend_worker;  // ���� ������ ����

	friend class Tree;
};

class Tree
{
public:
	Tree();  // ������
	~Tree(); // �Ҹ���
	void CreateCEO(string name);  // CEO ����
	void HireWorker(string hirer, string name);  // ���  
	void FireWorker(string name);  // �ذ�
	void show(); // ���
	void clear();  // ȸ�� �ʱ�ȭ
	bool isEmpty(); 
	bool isFull();

private:
	void showSub(TreeNode* p, int level);  // show ���
	void clearSub(TreeNode* p);    // clear ���
	TreeNode* searching(string name);  // ���,�ذ��� ã������
	TreeNode* searchingSub(string name, TreeNode* p);
	int counting_worker(TreeNode* p);  // ȸ�� �������� ���� �˱� ����

	TreeNode* superior;  // �ذ��� ����ϱ� ����, �˻��� �ι��� ��縦 �����ϴ� �뵵
	TreeNode* CEO;
};