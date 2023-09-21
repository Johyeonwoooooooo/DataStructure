#include"HouseType.h"
#include<string>  // getline 함수 쓰기 위함
#include<iostream>
using namespace std;

HouseList::HouseList(HouseList* priorPtr, HouseList* nextPtr)  // Houselist의 next,prior 포인터를 설정
{
	prior = priorPtr;
	next = nextPtr;
}

void HouseList::GetFromFile(ifstream& file)
{
	if (!file) // 파일을 찾을 수 없으면 에러
	{
		cout << "Error : Can't find file" << endl;
	}
	else
	{
		getline(file, name, '\n');     // 줄바꿈이 나올때까지 이름으로 입력받기
		getline(file, address, '\n');  // 줄바꿈이 나올때까지 주소로 입력받기
		getline(file, price, ' ');     // 공백나올때까지 가격으로 입력받기
		getline(file, square_meter, ' ');  // 공백나올때까지 평수로 입력받기
		getline(file, room);    // 방갯수 입력받기
	}
}

void HouseList::WriteToFile(ofstream& file) const  
{
	if (!file)  // 파일을 찾을 수 없으면 에러
	{
		cout << "Error : Can't find file" << endl;
	}
	else
	{
		file << name << endl;   // 이름을 출력하고 줄바꿈
		file << address << endl;  // 주소를 출력하고 줄바꿈
		file << price << ' ';    // 가격을 출력하고 공백출력 
		file << square_meter << ' ';  // 평수를 출력하고 공백출력
		file << room << endl;    // 방갯수를 출력하고 줄바꿈
	}
}

void HouseList::GetFromUser()
{
	cout << "Enter name; press return ";
	cin.ignore();  // 개행문자 무시
	getline(cin, name);
	cout << "Enter adderss; press return : ";
	getline(cin, address); 
	cout << "Enter price, square meter(pyung), number of bedrooms; press retrun : ";
	cin >> price;
	cin >> square_meter;
	cin >> room;
	cout << endl;
}

void HouseList::PrintHouseToScreen() const  // 출력
{
	cout << "이름 : " << name << endl;  
	cout << "주소 : " << address << endl;
	cout << "가격 : " << price << "억 " << endl;
	cout << "평형 : " << square_meter << "평, 방: " << room << endl << endl;
}

void HouseList::GetNameFromUser()  // 이름 입력받기
{
	cout << "Enter name; press return : ";
	cin >> name ;
}

void HouseList::PrintNameToScreen() const  // 이름 스크린에 출력
{
	cout << name << endl;
}

RelationType HouseList::CompareTo(HouseList* house) const
{
	if (name == house->name)  // 이름을 비교해 비교하려는 이름과 같으면 Equal
		return Equal;
	else
		return Different;
}

SortedList::SortedList()  // 생성자
{
	head = nullptr;
	tail = nullptr;
	cursor = nullptr;
}

SortedList::~SortedList()  // 소멸자
{
	clear();
}

void SortedList::clear()  // 초기화
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

	if (temp == nullptr)  // temp가 더이상 만들어지지 않으면 Full
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
		while (temp != tail)// 헤드부터 테일에 도착할때까지 한칸씩 옮기며 갯수 계산하기
		{
			temp = temp->next;
			length++;
		}
		return length;
	}
}

void SortedList::Insertitem(HouseList* house)  // 더블링크드 리스트에 집정보 입력하기
{
	if (isFull())  // 가득찼을 경우 오류
	{
		cout << "Error : Full List" << endl;
	}
	HouseList* newHouse = new HouseList(*house);  // 받은 house포인터를 복사
	if (isEmpty()) //처음 만들경우 헤드와 테일을 지정해줘야함
	{
		head = newHouse;  // 헤드 지정
		tail = newHouse;  // 테일 지정
		cursor = newHouse;  // 커서 지정
		newHouse->next = nullptr;  // newhouse의 next지정
		newHouse->prior = nullptr; // newhouse의 prior지정
	}
	else  // 무조건 리스트 맨뒤에 입력
	{
		newHouse->prior = tail;
		newHouse->next = nullptr;
		tail->next = newHouse;
		tail = newHouse;
	}
}

void SortedList::Deleteitem() // 커서가 가르키는 것을 삭제
{
	if (isEmpty())  // 리스트가 비어 있으면 오류
	{
		cout << "Error : Empty List" << endl;
	}
	else if (cursor == head && cursor == tail) // 하나만 남았을경우 삭제하면 리스트를 초기화
	{
		clear();
	}
	else  
	{
		cursor->next->prior = cursor->prior;  
		cursor->prior->next = cursor->next;
		cursor = head; // 커서 초기화
	}
}

HouseList* SortedList::Retrieveitem(string wanted_name)  // Delete와 PrintHouse 함수에서 원하는 이름과 같은 객체를 가르키는 포인터로 저장해 cursor로 지정하여 삭제,출력 예정이어서 포인터형식
{
	if (isEmpty()) // 리스트가 비어있으면 찾을 수 없음
	{
		cout << "Error : Empty List" << endl;
		return nullptr; // 없어서 nullptr
	}
	else
	{
		HouseList* temp = head; //  검사하기 위한 포인터
		HouseList H(nullptr, nullptr);  // compareTo 사용하기 위해 임의로 생성
		H.name = wanted_name; // 이름을 원하는 이름으로 설정
		while (temp != tail) // 모든 리스트를 탐색
		{
			if (H.CompareTo(temp) == Equal) // 이름이 같으면
			{
				return temp; // 탐색하던 포인터를 출력
				break;
			}
			temp = temp->next;  // 그 다음포인터로 이동
		}
		return nullptr;  // 같은것이 없을경우 null 값을 가짐
	}
}

void SortedList::FileToList(SortedList& houselist, ifstream& masterIn)
{
	HouseList* newhouse; // newhouse 정의
	newhouse = new HouseList(nullptr, nullptr); // 생성자 초기화
	while (masterIn.eof() ==false ) // 파일에 값이 남아있는 동안
	{
		newhouse->GetFromFile(masterIn);  // newhouse의 정보를 파일에서 가지고 옴
		if(newhouse->name != "" && newhouse->address !="" && newhouse -> price != "" && newhouse -> square_meter !="" && newhouse->room !="") // 하나라도 비어있으면 넣지 않음
			houselist.Insertitem(newhouse);  // newhouse를 Insertitem으로 넣음
   }
	masterIn.close();  // 파일 닫기
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
