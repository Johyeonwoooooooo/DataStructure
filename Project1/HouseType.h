#pragma once
#include<iostream>
#include<fstream>

enum RelationType { Different,Equal }; // RalationType ������ ����
using namespace std;

class HouseList  // ���� ������ �̸�,�ּ�,����,���,�氹���� �����ϰ� ����ũ�带 ���� ������ �ΰ��� ������ Ŭ����
{
public:
	HouseList(HouseList* priorPtr, HouseList* nextPtr); // ���� ������ �Ʒ� �Լ��� �߰��ϱ� ������ �����͸� �����ڿ� �߰�
	void GetFromFile(ifstream& file);  // ������ ������ �о� ������
	void WriteToFile(ofstream& file) const; // Ŭ������ü�� ������ ������ ���Ͽ� �����
	void GetFromUser();  // ������ �ƴ� �����κ��� ���� �޾ƿ�
	void PrintHouseToScreen() const;  // ���� ������ �����
	void GetNameFromUser();   // ������ ���� �̸��� ����
	void PrintNameToScreen() const;  // ���� ������ �̸��� �����
	RelationType CompareTo(HouseList* house) const;  // �������� �̸��� ���ϴ� �Լ�

private:
	string name;
	string address;
	string price;
	string square_meter;
	string room;
	HouseList* next;
	HouseList* prior;

	friend class SortedList;
};

typedef char CommandType;
class SortedList // �� Houselist ��ü���� ����ũ��� �����ϱ� ���� Ŭ����
{
public:
	SortedList();
	~SortedList();
	void Insertitem(HouseList* house); // houselist�� ����ũ�� ����Ʈ�� �߰���
	void Deleteitem();  // ����
	HouseList* Retrieveitem(string wanted_name); // ���ϴ� �̸��� ���� houselist�� ã�� �����ͷ� ����Ŵ ������ nullptr
	void clear();  // �ʱ�ȭ
	int LengthIs() const; // ���̰��
	bool isEmpty() const; // ������� Ȯ����
	bool isFull() const;  // ����Ʈ�� ��� á���� Ȯ����
	void FileToList(SortedList& houselist, ifstream& masterIn);  // ���Ͽ� �ִ� ������ ������ ����Ʈ�� ����
	void LostToFile(SortedList& houselist, ofstream& masterOut); // �������� �� ����Ʈ�� �ִ� ��� ������ ���Ͽ� ����
	void AddHouse(SortedList& houselist);  // �������� ���� ������ ����Ʈ�� ���� �̸��� ������ ����Ʈ�� �߰�
	void DeleteHouse(SortedList& houselist);  // ����Ʈ�ȿ� �ִ� ��ü �� �̸��� ������ ����
	void PrintHouse(SortedList houselist);   // �̸��� �ް� ���� �̸��� ������ �Ź��� ���
	void PrintAllHouse(SortedList houselist); // ����Ʈ�ȿ� �ִ� ��� ��ü ���
	void GetCommand(CommandType& command, SortedList& houselist);  // Ŀ��带 �ް� �׿� �´� ��ɾ ����
private:
	HouseList* head;   
	HouseList* tail;   // ���̺Ͽ��� ��� tail�� ���
	HouseList* cursor;  // insert�� delete�� ���
};
