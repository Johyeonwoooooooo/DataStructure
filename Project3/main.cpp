#include "tree.h"

void print_help()
{
	cout << "					         <명령어 목록>" << endl;
	cout << "					명령어 다시 보기 : help / Help" << endl;
	cout << "					고용하기 : [고용인] hire/Hires [피고용인]" << endl;
	cout << "					해고하기 : Fire/fire [해고인] " << endl;
	cout << "					회사 조직도 출력 : print / Print" << endl;
	cout << "					회사 초기화 : Clear/ clear / CLEAR" << endl;
	cout << "					프로그램 종료 : Quit/ End" << endl;
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
			cout << "CEO의 이름을 등록하세요 : ";
			cin >> name;
			cin.ignore();
			Company.CreateCEO(name);
		}
		else
		{
			cout << "Command : ";
			getline(cin, command);

			// 명령어를 공백에 따라 나누어 arr에 최대 3개로 나눔
			istringstream iss(command);              
			string token;
			int i = 0;
			while (getline(iss, token, ' ') && i < 3) 
			{
				arr[i] = token;
				i++;
			}

			// 명령어 실행
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