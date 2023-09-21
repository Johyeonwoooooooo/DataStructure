#include "Account.h"

int number;
string name;
string type;
int balance;

Bank::Bank()
{
	name = "";
	number = 0;
	type = "";
	balance = 0;
}

void Bank::createAccount()
{
	cout << "New Account \n";
	cout << "Enter the Name of the depositor: ";
	cin >> name;
	cout << "Enter the Account Number: ";
	cin >> number;
	cout << "Enter the Account Type: (CURR / SAVG / FD / RD / DMAT) ";
	cin >> type;
	cout << "Enter the Amount to Depoist: ";
	cin >> balance;
}

void Bank::deposit()
{
	int deposit;
	cout << "Depositing \n";
	cout << "Enter the amount to deposit: ";
	cin >> deposit;
	balance = balance + deposit;
	cout << endl;
}

void Bank::withdraw()
{
	int withdraw;
	cout << "Withdrawal";
	cout << "Enter the amount to withdraw: ";
	cin >> withdraw;
	balance = balance - withdraw;
	cout << endl;
}

void Bank::printAccount()
{
	cout << "Account Details" << "\n";
	cout << "Name of the depositor: " << name << "\n";
	cout << "Account number      : " << number << "\n";
	cout << "Account Type      : " << type << "\n";
	cout << "Balance      :$" << balance << "\n";
}