#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

class Person  // ģ�� ������ ���
{
private:
	Person(string name, Person* nextPtr = nullptr, Person* prior = nullptr);   // ����Ʈ �Ű����� ������

	Person* next;  // ��ũ�帮��Ʈ ������
	Person* prior;
	string name;    // �̸�

	friend class HashTable;
};

class HashTable  // �ؽ����̺� ����
{
public:
	HashTable();  // ������
	~HashTable();  // �Ҹ���
	void createPerson(string person);  // ����� ����
	void follow(string person1, string person2);  // ģ�� �߰�
	void unfollow(string person1, string person2);  // ģ�� ����
	void showFriend(string person) const;    // ģ����� ���
	bool isFriend(string person1, string person2) const;  // ģ�� Ȯ��
private:
	unordered_map<string, Person*> FriendList;  // unordered_map ���
};	