#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

class Person  // 친구 저장할 노드
{
private:
	Person(string name, Person* nextPtr = nullptr, Person* prior = nullptr);   // 디폴트 매개변수 생성자

	Person* next;  // 링크드리스트 포인터
	Person* prior;
	string name;    // 이름

	friend class HashTable;
};

class HashTable  // 해쉬테이블 구현
{
public:
	HashTable();  // 생성자
	~HashTable();  // 소멸자
	void createPerson(string person);  // 사용자 생성
	void follow(string person1, string person2);  // 친구 추가
	void unfollow(string person1, string person2);  // 친구 삭제
	void showFriend(string person) const;    // 친구목록 출력
	bool isFriend(string person1, string person2) const;  // 친구 확인
private:
	unordered_map<string, Person*> FriendList;  // unordered_map 사용
};	