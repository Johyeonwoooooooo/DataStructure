#include"HashTable.h"

void print_help()   // ��ɾ ���� ���� ����ϴ� �Լ�
{
    cout << "P <name> : Create a person record of the specified name." << endl;
    cout << "F <name1> <name2> : Record that the two specified people are friends." << endl;
    cout << "U <name1> <name2> : Record that the two specified people are no longer friends." << endl;
    cout << "L <name> : Print out the friends of the specified person." << endl;
    cout << "Q <name1> <name2> : Check whether the two people are friends." << endl;
    cout << "X : Terminate the program" << endl;
    cout << endl;
}



int main()
{
    HashTable testList;   // HashTable Ŭ���� ����
    char cmd;    // ��ɾ�
    string person1, person2;  // �̸�
    print_help();

    do
    {   
        cout << "Commnad : ";
        cin >> cmd;
        switch (cmd)   // cmd ���� ���� ��ɾ� ����
        {
        case'p':case'P':
            cin >> person1;
            testList.createPerson(person1);
            break;
        case'f':case'F':
            cin >> person1 >> person2;
            testList.follow(person1, person2);
            break;
        case'u':case'U':
            cin >> person1 >> person2;
            testList.unfollow(person1, person2);
            break;
        case'l':case'L':
            cin >> person1;
            testList.showFriend(person1);
            cout << endl;
            break;
        case'q':case'Q':
            cin >> person1 >> person2;
            if (testList.isFriend(person1, person2))
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            break;
        case'x':case'X':
            cout << "Quit Program" << endl;
            break;
        default:
            cout << "Error : Invalid Commnad " << endl;
            break;
        }
    } while (cmd != 'x' && cmd != 'X');

    return 0;
}