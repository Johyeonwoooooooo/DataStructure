#pragma once
#include<iostream>
#include<fstream>

enum RelationType { Different,Equal }; // RalationType 열거형 정의
using namespace std;

class HouseList  // 집의 정보인 이름,주소,가격,평수,방갯수를 저장하고 더블링크드를 위한 포인터 두개를 포함한 클래스
{
public:
	HouseList(HouseList* priorPtr, HouseList* nextPtr); // 방의 정보는 아래 함수로 추가하기 때문에 포인터만 생성자에 추가
	void GetFromFile(ifstream& file);  // 파일의 정보를 읽어 저장함
	void WriteToFile(ofstream& file) const; // 클래스객체가 저장한 정보를 파일에 출력함
	void GetFromUser();  // 파일이 아닌 유저로부터 값을 받아옴
	void PrintHouseToScreen() const;  // 집의 정보를 출력함
	void GetNameFromUser();   // 유저로 부터 이름을 받음
	void PrintNameToScreen() const;  // 집의 소유자 이름을 출력함
	RelationType CompareTo(HouseList* house) const;  // 소유자의 이름을 비교하는 함수

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
class SortedList // 위 Houselist 객체들을 더블링크드로 구현하기 위한 클래스
{
public:
	SortedList();
	~SortedList();
	void Insertitem(HouseList* house); // houselist를 더블링크드 리스트에 추가함
	void Deleteitem();  // 삭제
	HouseList* Retrieveitem(string wanted_name); // 원하는 이름과 같은 houselist를 찾고 포인터로 가르킴 없으면 nullptr
	void clear();  // 초기화
	int LengthIs() const; // 길이계산
	bool isEmpty() const; // 비었는지 확인함
	bool isFull() const;  // 리스트가 모두 찼는지 확인함
	void FileToList(SortedList& houselist, ifstream& masterIn);  // 파일에 있는 정보를 가져와 리스트에 저장
	void LostToFile(SortedList& houselist, ofstream& masterOut); // 마무리할 때 리스트에 있는 모든 정보를 파일에 저장
	void AddHouse(SortedList& houselist);  // 유저에게 받은 정보를 리스트안 같은 이름이 없으면 리스트에 추가
	void DeleteHouse(SortedList& houselist);  // 리스트안에 있는 객체 중 이름이 같으면 삭제
	void PrintHouse(SortedList houselist);   // 이름을 받고 같은 이름이 있으면 매물을 출력
	void PrintAllHouse(SortedList houselist); // 리스트안에 있는 모든 객체 출력
	void GetCommand(CommandType& command, SortedList& houselist);  // 커멘드를 받고 그에 맞는 명령어를 실행
private:
	HouseList* head;   
	HouseList* tail;   // 자이북에서 배운 tail을 사용
	HouseList* cursor;  // insert와 delete에 사용
};
