#include"HouseType.h"
int main()
{
	SortedList houselist; // houselist 설정
	char cmd; // 명령어 받기
	ifstream file("house.mf.txt");
	houselist.FileToList(houselist, file); // 파일에 있는 데이터들 먼저 가져오기
	houselist.GetCommand(cmd, houselist);  // 명령어 실행

	ofstream file1("house.mf.txt");
	houselist.LostToFile(houselist, file1);  // 리스트에 있는 데이터들 파일에 저장
	return 0;
}