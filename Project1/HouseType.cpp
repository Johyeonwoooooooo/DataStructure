#include"HouseType.h"
#include<string>  // getline �Լ� ���� ����
#include<iostream>
using namespace std;

HouseList::HouseList(HouseList* priorPtr, HouseList* nextPtr)  // Houselist�� next,prior �����͸� ����
{
	prior = priorPtr;
	next = nextPtr;
}

void HouseList::GetFromFile(ifstream& file)
{
	if (!file) // ������ ã�� �� ������ ����
	{
		cout << "Error : Can't find file" << endl;
	}
	else
	{
		getline(file, name, '\n');     // �ٹٲ��� ���ö����� �̸����� �Է¹ޱ�
		getline(file, address, '\n');  // �ٹٲ��� ���ö����� �ּҷ� �Է¹ޱ�
		getline(file, price, ' ');     // ���鳪�ö����� �������� �Է¹ޱ�
		getline(file, square_meter, ' ');  // ���鳪�ö����� ����� �Է¹ޱ�
		getline(file, room);    // �氹�� �Է¹ޱ�
	}
}

void HouseList::WriteToFile(ofstream& file) const  
{
	if (!file)  // ������ ã�� �� ������ ����
	{
		cout << "Error : Can't find file" << endl;
	}
	else
	{
		file << name << endl;   // �̸��� ����ϰ� �ٹٲ�
		file << address << endl;  // �ּҸ� ����ϰ� �ٹٲ�
		file << price << ' ';    // ������ ����ϰ� ������� 
		file << square_meter << ' ';  // ����� ����ϰ� �������
		file << room << endl;    // �氹���� ����ϰ� �ٹٲ�
	}
}

void HouseList::GetFromUser()
{
	cout << "Enter name; press return ";
	cin.ignore();  // ���๮�� ����
	getline(cin, name);
	cout << "Enter adderss; press return : ";
	getline(cin, address); 
	cout << "Enter price, square meter(pyung), number of bedrooms; press retrun : ";
	cin >> price;
	cin >> square_meter;
	cin >> room;
	cout << endl;
}

void HouseList::PrintHouseToScreen() const  // ���
{
	cout << "�̸� : " << name << endl;  
	cout << "�ּ� : " << address << endl;
	cout << "���� : " << price << "�� " << endl;
	cout << "���� : " << square_meter << "��, ��: " << room << endl << endl;
}

void HouseList::GetNameFromUser()  // �̸� �Է¹ޱ�
{
	cout << "Enter name; press return : ";
	cin >> name ;
}

void HouseList::PrintNameToScreen() const  // �̸� ��ũ���� ���
{
	cout << name << endl;
}

RelationType HouseList::CompareTo(HouseList* house) const
{
	if (name == house->name)  // �̸��� ���� ���Ϸ��� �̸��� ������ Equal
		return Equal;
	else
		return Different;
}

SortedList::SortedList()  // ������
{
	head = nullptr;
	tail = nullptr;
	cursor = nullptr;
}

SortedList::~SortedList()  // �Ҹ���
{
	clear();
}

void SortedList::clear()  // �ʱ�ȭ
{
	head = nullptr;
	tail = nullptr;
}

bool SortedList::isEmpty() const  
{
	if (head == nullptr && tail == nullptr)
		return true;
	else
		return false;
}

bool SortedList::isFull() const
{
	HouseList* temp = new(nothrow)HouseList(nullptr, nullptr);

	if (temp == nullptr)  // temp�� ���̻� ��������� ������ Full
		return true;
	else
		return false;
}

int SortedList::LengthIs() const
{
	int length = 0;
	if (isEmpty())
		return length;
	else
	{
		length = 1;
		HouseList* temp = head;  
		while (temp != tail)// ������ ���Ͽ� �����Ҷ����� ��ĭ�� �ű�� ���� ����ϱ�
		{
			temp = temp->next;
			length++;
		}
		return length;
	}
}

void SortedList::Insertitem(HouseList* house)  // ����ũ�� ����Ʈ�� ������ �Է��ϱ�
{
	if (isFull())  // ����á�� ��� ����
	{
		cout << "Error : Full List" << endl;
	}
	HouseList* newHouse = new HouseList(*house);  // ���� house�����͸� ����
	if (isEmpty()) //ó�� ������ ���� ������ �����������
	{
		head = newHouse;  // ��� ����
		tail = newHouse;  // ���� ����
		cursor = newHouse;  // Ŀ�� ����
		newHouse->next = nullptr;  // newhouse�� next����
		newHouse->prior = nullptr; // newhouse�� prior����
	}
	else  // ������ ����Ʈ �ǵڿ� �Է�
	{
		newHouse->prior = tail;
		newHouse->next = nullptr;
		tail->next = newHouse;
		tail = newHouse;
	}
}

void SortedList::Deleteitem() // Ŀ���� ����Ű�� ���� ����
{
	if (isEmpty())  // ����Ʈ�� ��� ������ ����
	{
		cout << "Error : Empty List" << endl;
	}
	else if (cursor == head && cursor == tail) // �ϳ��� ��������� �����ϸ� ����Ʈ�� �ʱ�ȭ
	{
		clear();
	}
	else  
	{
		cursor->next->prior = cursor->prior;  
		cursor->prior->next = cursor->next;
		cursor = head; // Ŀ�� �ʱ�ȭ
	}
}

HouseList* SortedList::Retrieveitem(string wanted_name)  // Delete�� PrintHouse �Լ����� ���ϴ� �̸��� ���� ��ü�� ����Ű�� �����ͷ� ������ cursor�� �����Ͽ� ����,��� �����̾ ����������
{
	if (isEmpty()) // ����Ʈ�� ��������� ã�� �� ����
	{
		cout << "Error : Empty List" << endl;
		return nullptr; // ��� nullptr
	}
	else
	{
		HouseList* temp = head; //  �˻��ϱ� ���� ������
		HouseList H(nullptr, nullptr);  // compareTo ����ϱ� ���� ���Ƿ� ����
		H.name = wanted_name; // �̸��� ���ϴ� �̸����� ����
		while (temp != tail) // ��� ����Ʈ�� Ž��
		{
			if (H.CompareTo(temp) == Equal) // �̸��� ������
			{
				return temp; // Ž���ϴ� �����͸� ���
				break;
			}
			temp = temp->next;  // �� ���������ͷ� �̵�
		}
		return nullptr;  // �������� ������� null ���� ����
	}
}

void SortedList::FileToList(SortedList& houselist, ifstream& masterIn)
{
	HouseList* newhouse; // newhouse ����
	newhouse = new HouseList(nullptr, nullptr); // ������ �ʱ�ȭ
	while (masterIn.eof() ==false ) // ���Ͽ� ���� �����ִ� ����
	{
		newhouse->GetFromFile(masterIn);  // newhouse�� ������ ���Ͽ��� ������ ��
		if(newhouse->name != "" && newhouse->address !="" && newhouse -> price != "" && newhouse -> square_meter !="" && newhouse->room !="") // �ϳ��� ��������� ���� ����
			houselist.Insertitem(newhouse);  // newhouse�� Insertitem���� ����
   }
	masterIn.close();  // ���� �ݱ�
}

void SortedList::LostToFile(SortedList& houselist, ofstream& masterOut)
{
	cursor = head;
	int length = houselist.LengthIs();
	for (int i = 0; i < length; i++)
	{
		cursor->WriteToFile(masterOut);
		cursor = cursor->next;
	}
	masterOut.close();
}

void SortedList::AddHouse(SortedList& houselist)
{
	HouseList* newhouse;
	newhouse = new HouseList(nullptr, nullptr);
	newhouse->GetFromUser();
	if (houselist.Retrieveitem(newhouse->name) != nullptr)
		cout << "Error : Duplicate name; operation aborted" << endl << endl;
	else
	{
		houselist.Insertitem(newhouse);
		cout << "Operation completed." << endl << endl;
	}
}

void SortedList::DeleteHouse(SortedList& houselist)
{
	HouseList* house;
	house = new HouseList(nullptr, nullptr);
	house->GetNameFromUser();
	cursor = houselist.Retrieveitem(house->name);
	if (cursor == nullptr)
		cout << "Error : Owner not in list" << endl;
	else
	{
		houselist.Deleteitem();
		cout << "Operation completed." << endl <<endl;
	}
}

void SortedList::PrintHouse(SortedList houselist)
{
	HouseList* found_house;
	found_house = new HouseList(nullptr, nullptr);
	found_house->GetNameFromUser();
	if (houselist.Retrieveitem(found_house->name) == nullptr)
		cout << "Error : Owner not in list" << endl;
	else
	{
		cursor = houselist.Retrieveitem(found_house->name);
		cursor->PrintHouseToScreen();
	}
}

void SortedList::PrintAllHouse(SortedList houselist)
{
	cursor = head;
	int length = houselist.LengthIs();
	for (int i = 0; i < length; i++)
	{
		cursor->PrintHouseToScreen();
		cursor = cursor->next;
	}
}

void SortedList::GetCommand(CommandType& command, SortedList& houselist)
{
	cout << "Operations are listed below." << endl;
	cout << "Enter the appropriate uppercase letter and press return." << endl;
	cout << "A : Add a house to list of house" << endl;
	cout << "D : Delete a specific owner's house" << endl;
	cout << "P : Print the information about and owner's house" << endl;
	cout << "L : Print all the names on the screen." << endl;
	cout << "Q : Quit processing" << endl <<endl;

	do {
		cout << "command : ";
		cin >> command;
		switch (command)
		{
		case'a':case'A':
			AddHouse(houselist);
			break;
		case'd': case'D':
			DeleteHouse(houselist);
			break;
		case'p': case'P':
			PrintHouse(houselist);
			break;
		case'l':case'L':
			PrintAllHouse(houselist);
			break;
		case'q':case'Q':
			cout << "Quit programming";
			break;
		default:
			cout << "Error : Invalid Command" << endl;
			break;
		}
	} while (command != 'Q' && command != 'q');
}
