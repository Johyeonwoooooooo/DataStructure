#include"HouseType.h"
int main()
{
	SortedList houselist; // houselist ����
	char cmd; // ��ɾ� �ޱ�
	ifstream file("house.mf.txt");
	houselist.FileToList(houselist, file); // ���Ͽ� �ִ� �����͵� ���� ��������
	houselist.GetCommand(cmd, houselist);  // ��ɾ� ����

	ofstream file1("house.mf.txt");
	houselist.LostToFile(houselist, file1);  // ����Ʈ�� �ִ� �����͵� ���Ͽ� ����
	return 0;
}