#include"HashTable.h"

Person::Person(string name, Person* nextPtr, Person* priorPtr)  // 생성자
{
    this->name = name;
    this->next = nextPtr;
    this->prior = priorPtr;
}

HashTable::HashTable()   
{
    FriendList = unordered_map<string, Person*>();  // 키 값은 string, value 는 Person 클래스를 가지는 해쉬테이블 만들기
}

HashTable::~HashTable()
{
    for (const auto& pair : FriendList)  // FriendList의 모든 원소 돌기
    {
        Person* temp = pair.second;   // pair의 second (value) 값 저장
        while (temp != nullptr)  // Person과 연결된 모든 노드를 삭제
        {
            Person* temp_prior = temp;
            temp = temp->next;
            delete temp_prior;
        }
    }
}

void HashTable::createPerson(string person)
{
    auto iter = FriendList.find(person);   // FriendList에 person의 키값을가진 노드를 탐색
    if (iter != FriendList.end())       // 만약 person과 같은 키를 가진 노드가 검색되면 채워져 있는 것
        cout << "Error : Alreday Created" << endl;   // 에러 출력
    else   
    {
        FriendList.insert({ person,nullptr });  // 키값은 person 이름, 가르키는 값은 NULL로 설정
    }
}

void HashTable::follow(string person1, string person2)  
{
    auto iter1 = FriendList.find(person1);   // person1 키값가진 노드 탐색
    auto iter2 = FriendList.find(person2);   // person2 키값가진 노드 탐색

    if (iter1 == FriendList.end() || iter2 == FriendList.end())   // 둘 중 하나라도 저장되어 있지 않으면
        cout << "Error : Can't find user" << endl;   // 오류
    else if (isFriend(person1, person2))    // 이미 둘이 친구이면
        cout << "Error : Already Freind" << endl;  // 오류
    else
    {
        Person* p1 = iter1->second;    // p1이 person1키가 가르키는 첫 노드
        if (p1 == nullptr)   // 친구가 아무도 없으면
        {
            FriendList[person1] = new Person(person2);  // 키 값이 person1인 노드에 첫 노드 생성
        }
        else
        {
            Person* newFriend = new Person(person2);   // 새로운 친구 노드 만들고
            newFriend -> next = p1;         // 리스트의 가장 앞에 넣어야하기에 next를 person1이 가르키는 첫 노드
            p1->prior = newFriend;          // 첫 노드는 newFriend를 prior로
            p1 = newFriend;              
            FriendList[person1] = newFriend;  //초기화
        }

        Person* p2 = iter2->second;   // 위 과정을 반복함
        if (p2 == nullptr)
        {
            FriendList[person2] = new Person(person1);
        }
        else
        {
            Person* newFriend = new Person(person1);
            newFriend->next = p2;
            p2->prior = newFriend;
            p2 = newFriend;
            FriendList[person2] = newFriend;
        }
    }
}

void HashTable::unfollow(string person1, string person2)
{
    auto iter1 = FriendList.find(person1);             // person1 키값가진 노드 탐색
    auto iter2 = FriendList.find(person2);             // person2 키값가진 노드 탐색

    if (iter1 == FriendList.end() || iter2 == FriendList.end())  // 해쉬테이블에 저장되어 있지 않으면 오류
    {
        cout << "Error: Can't find users" << endl;
    }
    else if (!isFriend(person1, person2))           // 이미 친구가 아니면 오류
    {
        cout << "Error: They are not friends" << endl;
    }
    else
    {
        Person* p1 = iter1->second;   // person1이 처음 가르키는 노드
        if (p1->name == person2)  // 첫노드가 삭제할 노드이면
        {
            if (p1->next == nullptr)  // 친구가 한명일땐
            {
                FriendList[person1] = nullptr;  // nullptr 넣기
                delete p1;
            }
            else
            {
                FriendList[person1] = p1->next;   // 친구가 더 있으면 다음 친구로 갱신
                p1->next->prior = nullptr;  // 갱신한 첫노드 prior null 넣기
                delete p1;
            }
        }
        else
        {
            while (p1->name != person2)  // 노드 찾기
            {
                p1 = p1->next;
            }
            if (p1->next == nullptr)  // 마지막 노드이면
            {
                p1->prior->next = nullptr;   // 전 노드와 연결 끊기
                delete p1;  // 삭제
            }
            else  // 중간노드
            {
                p1->prior->next = p1->next;  // 연결 다시 하기
                p1->next->prior = p1->prior;
                delete p1;   // 삭제
            }
        }
        Person* p2 = iter2->second;  // 위 과정 반복
        if (p2->name == person1)
        {
            if (p2->next == nullptr)
            {
                FriendList[person2] = nullptr;
                delete p2;
            }
            else
            {
                FriendList[person2] = p2->next;
                p2->next->prior = nullptr;
                delete p2;
            }
        }
        else
        {
            while (p2->name != person1)
            {
                p2 = p2->next;
            }
            if (p2->next == nullptr)
            {
                p2->prior->next = nullptr;
                delete p2;
            }   
            else
            {
                p2->prior->next = p2->next;
                p2->next->prior = p2->prior;
                delete p2;
            }
        }
    }
}


void HashTable::showFriend(string person) const
{
    auto iter = FriendList.find(person);  // 키값을 가진 노드 탐색
    if (iter != FriendList.end())    // 찾으면
    {
        Person* temp = iter->second;   // 자신의 이름을 가진 첫노드를 제외한 그 다음노드부터 접근
        if (temp == nullptr)
            cout << "Error : User have any Friend" << endl;
        else
        {
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            while (temp != nullptr)
            {
                cout << temp->name << " ";   // 이름을 출력하고
                temp = temp->prior;    // 다음 포인터로 이동
            }
        }
    }
    else   // 만약 찾을수 없으면
        cout << "Error : Can't find user" << endl;  // 오류
}

bool HashTable::isFriend(string person1, string person2) const
{
    auto iter1 = FriendList.find(person1);      // person1  키값 value 탐색
    auto iter2 = FriendList.find(person2);     // person2 키값  value 탐색
     
    int probe1 = 0;    // person1 의 노드를 탐색하고 person2 가 있으면 1 없으면 0
    int probe2 = 0;    // person1이 친구로 있으면 1 없으면 0

    if (iter1 == FriendList.end() || iter2 == FriendList.end())   // 둘 중 하나라도 저장됭 있지 않으면 
    {
        cout << "Error : Can't find user" << endl;  //오류
        return false;         // 거짓
    }
    else
    {
        Person* temp = iter1->second;   // person1의 첫 친구노드에 접근
        while (temp != nullptr)  // 모든 노드 탐색
        {
            if (temp->name == person2)   // 가진 데이터가 person2랑 같으면
            {
                probe1 = 1;   // 1로 바꾸고
                break;         // 반복문 중지
            }
            temp = temp->next;  // 다음 노드로 이동
        }

        temp = iter2->second;  // person2또한 똑같은 과정 반복
        while (temp != nullptr)
        {
            if (temp->name == person1)
            {
                probe2 = 1;
                break;
            }
            temp = temp->next;
        }

        if (probe1 == 1 && probe2 == 1)    // 둘 다 친구에서 발견해 probe값이 1이 되면 트루
            return true;
        else   // 아니면 거짓
            return false;
    }
}