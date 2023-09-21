#include "tree.h"

void print_help()
{
	cout << "					         <��ɾ� ���>" << endl;
	cout << "					��ɾ� �ٽ� ���� : help / Help" << endl;
	cout << "					����ϱ� : [�����] hire/Hires [�ǰ����]" << endl;
	cout << "					�ذ��ϱ� : Fire/fire [�ذ���] " << endl;
	cout << "					ȸ�� ������ ��� : print / Print" << endl;
	cout << "					ȸ�� �ʱ�ȭ : Clear/ clear / CLEAR" << endl;
	cout << "					���α׷� ���� : Quit/ End" << endl;
}
int main()
{
	Tree Company;
	string name;
	string arr[3];
	string command;
	print_help();
	while (true)
	{
		if (Company.isEmpty())
		{
			cout << "CEO�� �̸��� ����ϼ��� : ";
			cin >> name;
			cin.ignore();
			Company.CreateCEO(name);
		}
		else
		{
			cout << "Command : ";
			getline(cin, command);

			// ��ɾ ���鿡 ���� ������ arr�� �ִ� 3���� ����
			istringstream iss(command);              
			string token;
			int i = 0;
			while (getline(iss, token, ' ') && i < 3) 
			{
				arr[i] = token;
				i++;
			}

			// ��ɾ� ����
			if (arr[1] == "Hires" || arr[1] == "hires" || arr[1] == "hire" || arr[1] == "HIRE")
				Company.HireWorker(arr[0], arr[2]);
			else if (arr[0] == "Fire" || arr[0] == "fire" || arr[0] == "FIRE")
				Company.FireWorker(arr[1]);
			else if (arr[0] == "Print" || arr[0] == "print" || arr[0] == "PRINT")
				Company.show();
			else if (arr[0] == "Clear" || arr[0] == "clear" || arr[0] == "CLEAR")
				Company.clear();
			else if (arr[0] == "Quit" || arr[0] == "quit" || arr[0] == "end" || arr[0] == "End")
				break;
			else if (arr[0] == "Help" || arr[0] == "help" || arr[0] == "HELP")
				print_help();
			else cout << "Error : Invalid command" << endl;  

			for (int i = 0; i < 3; i++) 
				arr[i] = "";
		}
	}
	return 0;
}