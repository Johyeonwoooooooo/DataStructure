#include"tree.h"

TreeNode::TreeNode(string name, TreeNode* child, TreeNode* friend_worker)  
{
	this->name = name;
	this->child = child;
	this->friend_worker = friend_worker;
}

Tree::Tree()
{
	CEO = nullptr;
	superior = nullptr;
}

Tree::~Tree()
{
	clear();
}

void Tree::CreateCEO(string name)
{
	CEO = new TreeNode(name); 
}

TreeNode* Tree::searching(string name)
{
	return searchingSub(name, CEO);  
}

TreeNode* Tree::searchingSub(string name, TreeNode* p)
{
	if (p->name == name)
	{
		return p;
	}
	else
	{
		TreeNode* result = nullptr;
		if (p->friend_worker != nullptr)
		{
			result = searchingSub(name, p->friend_worker);  // 직장동료 탐색 (상사 갱신 필요 X)
		}
		if (result == nullptr && p->child != nullptr)
		{
			superior = p;  // child -> 상사 설정
			result = searchingSub(name, p->child);
		}
		return result;
	}
}

void Tree::HireWorker(string hirer, string name)
{
	if (isFull())
	{

	}
	else
	{
		TreeNode* p = searching(hirer);
		if (p != nullptr)
		{
			if (p->child == nullptr)  // 후배가 없으면 새롭게 생성
			{
				p->child = new TreeNode(name);
			}
			else
			{
				TreeNode* temp = p->child;
				while (temp->friend_worker != nullptr)  // 부하의 가장 끝으로 이동
				{
					temp = temp->friend_worker;
				}
				temp->friend_worker = new TreeNode(name);  // 생성
			}
		}
		else  // hirer 가 없으면 오류
			cout << "Error : Can't find Hirer" << endl;
	}
}

void Tree::FireWorker(string name)
{
	TreeNode* p = searching(name);  // 해고자 찾기
	if (p == nullptr)  // 없으면 오류
		cout << "Error : Can't find Worker" << endl;
	else
	{
		if (p == CEO)   // 해고할 사람이 CEO 일떄
		{
			if (p->child == nullptr)  // 부하가 없으면
				clear();  // 초기화
			else
			{
				TreeNode* temp = p;
				TreeNode* temp_pre = nullptr;
				while (temp->child != nullptr)
				{
					temp_pre = temp;
					temp->name = temp->child->name;  // 이름 위로 올리기
					temp = temp->child;
				}
				temp_pre->child = temp->friend_worker;  // 동료 노드 한칸씩 밀기
				delete temp; // 마지막 노드 삭제
			}
		}
		else
		{
			if (p->child == nullptr)  // 부하가 없는 직원 해고
			{
				TreeNode* temp = superior->child;
				if (temp == p)  // 첫번째 부하인 경우
				{
					superior->child = temp->friend_worker;
					delete temp;
				}
				else
				{
					while (temp->friend_worker != p) 
					{
						temp = temp->friend_worker;
					}
					temp->friend_worker = p->friend_worker; //부하 연결 끊기
					delete p; // 삭제
				}
			}
			else  // 부하가 있는 직원 해고
			{
				TreeNode* temp = p;
				TreeNode* temp_pre = nullptr;
				while (temp->child != nullptr)  // 이름 위로 이동
				{
					temp_pre = temp;
					temp->name = temp->child->name;
					temp = temp->child;
				}
				temp_pre->child = temp->friend_worker; // 부하 리스트 이동
				delete temp;  // 삭제
			}
		}
	}
}

void Tree::show()
{
	showSub(CEO, 0);
}

void Tree::showSub(TreeNode* p, int level)
{
	if (p != nullptr)
	{
		for (int i = 0; i < level; i++)
			cout << '+';
		cout << p->name << endl;

		if (p->child != nullptr)
			showSub(p->child, level + 1);
		if (p->friend_worker != nullptr)
			showSub(p->friend_worker, level);
	}
}

void Tree::clear()  
{
	clearSub(CEO);
	CEO = nullptr;
	superior = nullptr;
}

void Tree::clearSub(TreeNode* p)
{
	if (p != nullptr)
	{
		clearSub(p->child);
		clearSub(p->friend_worker);
		delete p;
	}
}

bool Tree::isEmpty()
{
	if (CEO == nullptr)
		return true;
	else
		return false;
}

bool Tree::isFull()
{
	int result = counting_worker(CEO);
	if (result > MaxSize)
		return true;
	else
		return false;
}

int Tree::counting_worker(TreeNode* p)
{
	int count = 0;
	if (p != nullptr)
	{
		count++;
		if (p->child != nullptr)
			count += counting_worker(p->child);
		if (p->friend_worker != nullptr)
			count += counting_worker(p->friend_worker);
	}
	return count;
}