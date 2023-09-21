#include"HashTable.h"

Person::Person(string name, Person* nextPtr, Person* priorPtr)  // ������
{
    this->name = name;
    this->next = nextPtr;
    this->prior = priorPtr;
}

HashTable::HashTable()   
{
    FriendList = unordered_map<string, Person*>();  // Ű ���� string, value �� Person Ŭ������ ������ �ؽ����̺� �����
}

HashTable::~HashTable()
{
    for (const auto& pair : FriendList)  // FriendList�� ��� ���� ����
    {
        Person* temp = pair.second;   // pair�� second (value) �� ����
        while (temp != nullptr)  // Person�� ����� ��� ��带 ����
        {
            Person* temp_prior = temp;
            temp = temp->next;
            delete temp_prior;
        }
    }
}

void HashTable::createPerson(string person)
{
    auto iter = FriendList.find(person);   // FriendList�� person�� Ű�������� ��带 Ž��
    if (iter != FriendList.end())       // ���� person�� ���� Ű�� ���� ��尡 �˻��Ǹ� ä���� �ִ� ��
        cout << "Error : Alreday Created" << endl;   // ���� ���
    else   
    {
        FriendList.insert({ person,nullptr });  // Ű���� person �̸�, ����Ű�� ���� NULL�� ����
    }
}

void HashTable::follow(string person1, string person2)  
{
    auto iter1 = FriendList.find(person1);   // person1 Ű������ ��� Ž��
    auto iter2 = FriendList.find(person2);   // person2 Ű������ ��� Ž��

    if (iter1 == FriendList.end() || iter2 == FriendList.end())   // �� �� �ϳ��� ����Ǿ� ���� ������
        cout << "Error : Can't find user" << endl;   // ����
    else if (isFriend(person1, person2))    // �̹� ���� ģ���̸�
        cout << "Error : Already Freind" << endl;  // ����
    else
    {
        Person* p1 = iter1->second;    // p1�� person1Ű�� ����Ű�� ù ���
        if (p1 == nullptr)   // ģ���� �ƹ��� ������
        {
            FriendList[person1] = new Person(person2);  // Ű ���� person1�� ��忡 ù ��� ����
        }
        else
        {
            Person* newFriend = new Person(person2);   // ���ο� ģ�� ��� �����
            newFriend -> next = p1;         // ����Ʈ�� ���� �տ� �־���ϱ⿡ next�� person1�� ����Ű�� ù ���
            p1->prior = newFriend;          // ù ���� newFriend�� prior��
            p1 = newFriend;              
            FriendList[person1] = newFriend;  //�ʱ�ȭ
        }

        Person* p2 = iter2->second;   // �� ������ �ݺ���
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
    auto iter1 = FriendList.find(person1);             // person1 Ű������ ��� Ž��
    auto iter2 = FriendList.find(person2);             // person2 Ű������ ��� Ž��

    if (iter1 == FriendList.end() || iter2 == FriendList.end())  // �ؽ����̺� ����Ǿ� ���� ������ ����
    {
        cout << "Error: Can't find users" << endl;
    }
    else if (!isFriend(person1, person2))           // �̹� ģ���� �ƴϸ� ����
    {
        cout << "Error: They are not friends" << endl;
    }
    else
    {
        Person* p1 = iter1->second;   // person1�� ó�� ����Ű�� ���
        if (p1->name == person2)  // ù��尡 ������ ����̸�
        {
            if (p1->next == nullptr)  // ģ���� �Ѹ��϶�
            {
                FriendList[person1] = nullptr;  // nullptr �ֱ�
                delete p1;
            }
            else
            {
                FriendList[person1] = p1->next;   // ģ���� �� ������ ���� ģ���� ����
                p1->next->prior = nullptr;  // ������ ù��� prior null �ֱ�
                delete p1;
            }
        }
        else
        {
            while (p1->name != person2)  // ��� ã��
            {
                p1 = p1->next;
            }
            if (p1->next == nullptr)  // ������ ����̸�
            {
                p1->prior->next = nullptr;   // �� ���� ���� ����
                delete p1;  // ����
            }
            else  // �߰����
            {
                p1->prior->next = p1->next;  // ���� �ٽ� �ϱ�
                p1->next->prior = p1->prior;
                delete p1;   // ����
            }
        }
        Person* p2 = iter2->second;  // �� ���� �ݺ�
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
    auto iter = FriendList.find(person);  // Ű���� ���� ��� Ž��
    if (iter != FriendList.end())    // ã����
    {
        Person* temp = iter->second;   // �ڽ��� �̸��� ���� ù��带 ������ �� ���������� ����
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
                cout << temp->name << " ";   // �̸��� ����ϰ�
                temp = temp->prior;    // ���� �����ͷ� �̵�
            }
        }
    }
    else   // ���� ã���� ������
        cout << "Error : Can't find user" << endl;  // ����
}

bool HashTable::isFriend(string person1, string person2) const
{
    auto iter1 = FriendList.find(person1);      // person1  Ű�� value Ž��
    auto iter2 = FriendList.find(person2);     // person2 Ű��  value Ž��
     
    int probe1 = 0;    // person1 �� ��带 Ž���ϰ� person2 �� ������ 1 ������ 0
    int probe2 = 0;    // person1�� ģ���� ������ 1 ������ 0

    if (iter1 == FriendList.end() || iter2 == FriendList.end())   // �� �� �ϳ��� ����� ���� ������ 
    {
        cout << "Error : Can't find user" << endl;  //����
        return false;         // ����
    }
    else
    {
        Person* temp = iter1->second;   // person1�� ù ģ����忡 ����
        while (temp != nullptr)  // ��� ��� Ž��
        {
            if (temp->name == person2)   // ���� �����Ͱ� person2�� ������
            {
                probe1 = 1;   // 1�� �ٲٰ�
                break;         // �ݺ��� ����
            }
            temp = temp->next;  // ���� ���� �̵�
        }

        temp = iter2->second;  // person2���� �Ȱ��� ���� �ݺ�
        while (temp != nullptr)
        {
            if (temp->name == person1)
            {
                probe2 = 1;
                break;
            }
            temp = temp->next;
        }

        if (probe1 == 1 && probe2 == 1)    // �� �� ģ������ �߰��� probe���� 1�� �Ǹ� Ʈ��
            return true;
        else   // �ƴϸ� ����
            return false;
    }
}