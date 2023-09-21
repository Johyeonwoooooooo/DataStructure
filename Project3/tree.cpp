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
			result = searchingSub(name, p->friend_worker);  // ���嵿�� Ž�� (��� ���� �ʿ� X)
		}
		if (result == nullptr && p->child != nullptr)
		{
			superior = p;  // child -> ��� ����
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
			if (p->child == nullptr)  // �Ĺ谡 ������ ���Ӱ� ����
			{
				p->child = new TreeNode(name);
			}
			else
			{
				TreeNode* temp = p->child;
				while (temp->friend_worker != nullptr)  // ������ ���� ������ �̵�
				{
					temp = temp->friend_worker;
				}
				temp->friend_worker = new TreeNode(name);  // ����
			}
		}
		else  // hirer �� ������ ����
			cout << "Error : Can't find Hirer" << endl;
	}
}

void Tree::FireWorker(string name)
{
	TreeNode* p = searching(name);  // �ذ��� ã��
	if (p == nullptr)  // ������ ����
		cout << "Error : Can't find Worker" << endl;
	else
	{
		if (p == CEO)   // �ذ��� ����� CEO �ϋ�
		{
			if (p->child == nullptr)  // ���ϰ� ������
				clear();  // �ʱ�ȭ
			else
			{
				TreeNode* temp = p;
				TreeNode* temp_pre = nullptr;
				while (temp->child != nullptr)
				{
					temp_pre = temp;
					temp->name = temp->child->name;  // �̸� ���� �ø���
					temp = temp->child;
				}
				temp_pre->child = temp->friend_worker;  // ���� ��� ��ĭ�� �б�
				delete temp; // ������ ��� ����
			}
		}
		else
		{
			if (p->child == nullptr)  // ���ϰ� ���� ���� �ذ�
			{
				TreeNode* temp = superior->child;
				if (temp == p)  // ù��° ������ ���
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
					temp->friend_worker = p->friend_worker; //���� ���� ����
					delete p; // ����
				}
			}
			else  // ���ϰ� �ִ� ���� �ذ�
			{
				TreeNode* temp = p;
				TreeNode* temp_pre = nullptr;
				while (temp->child != nullptr)  // �̸� ���� �̵�
				{
					temp_pre = temp;
					temp->name = temp->child->name;
					temp = temp->child;
				}
				temp_pre->child = temp->friend_worker; // ���� ����Ʈ �̵�
				delete temp;  // ����
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