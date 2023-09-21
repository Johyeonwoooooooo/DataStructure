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
	TreeNode* friend_worker;  // 같은 직급의 동료

	friend class Tree;
};

class Tree
{
public:
	Tree();  // 생성자
	~Tree(); // 소멸자
	void CreateCEO(string name);  // CEO 생성
	void HireWorker(string hirer, string name);  // 고용  
	void FireWorker(string name);  // 해고
	void show(); // 출력
	void clear();  // 회사 초기화
	bool isEmpty(); 
	bool isFull();

private:
	void showSub(TreeNode* p, int level);  // show 재귀
	void clearSub(TreeNode* p);    // clear 재귀
	TreeNode* searching(string name);  // 고용,해고에서 찾기위함
	TreeNode* searchingSub(string name, TreeNode* p);
	int counting_worker(TreeNode* p);  // 회사 구성원의 수를 알기 위해

	TreeNode* superior;  // 해고에서 사용하기 위해, 검색한 인물의 상사를 저장하는 용도
	TreeNode* CEO;
};