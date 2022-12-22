
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <map>
#include <conio.h>
#include "Account.h"
#include "Admin.h"
#include "Seller.h"
#include "Authentification.h"
using namespace std;

map <string, Account> readAccounts();                     //��������� ������ � ���� ���������
map <string, User> readUser();
map <string, FlowerAdmin> readFlowers();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "���� ��������������� ��������" << endl << endl;
	map <string, Account> accounts = readAccounts();
	map <string, User> users = readUser();
	map <string, FlowerAdmin> flowers = readFlowers();
	updateUserCart(users, flowers);
	cout << endl;
	system("pause");
	system("cls");

	while (true)
	{
		cout << "����� ���������� � �������" << endl << endl << "(�� ���� ���� �� ������ ��������� ������� ���������)" << endl << endl;
		authentification(accounts, users, flowers);
		system("cls");
	}

	return 0;
}

map <string, Account> readAccounts()  //��������� ������ � ���� ���������
{
	string name, login, password;
	bool role;
	map <string, Account> accounts;
	ifstream in("accounts", ios::binary | ios::in);
	if (!in.is_open())
	{
		cout << "��������! ���� ��������� ���������� ���������� ��� ������. ����� ������ ����� ����" << endl;
		in.close();
		ofstream out("accounts", ios::binary | ios::out);
		out.close();
		return accounts;
	}

	while (!in.eof())
	{
		in.read((char*)&role, sizeof(role));     //���������� ����
		if (in.eof())
			break;

		size_t len;
		char* buf;

		in.read((char*)&len, sizeof(len));
		buf = new char[len];
		in.read(buf, len);
		name = buf;                              //���������� �����
		delete[] buf;

		in.read((char*)&len, sizeof(len));
		buf = new char[len];
		in.read(buf, len);
		login = buf;                             //���������� ������
		delete[] buf;

		in.read((char*)&len, sizeof(len));
		buf = new char[len];
		in.read(buf, len);
		password = buf;                          //���������� ������
		delete[] buf;

		Account acc(name, login, password, role);
		accounts.insert(make_pair(login, acc));
	}

	in.close();
	if (!in.bad())
		cout << "���������� ������ ��������� ������ �������." << endl;
	else
	{
		cout << "���������� ������ ��������� � �������. �������� �������� �� ������" << endl;
		in.clear();
	}
	return accounts;
}

map <string, User> readUser()
{
	map <string, User> users;
	string name, login, password;
	int ID;
	Order cart;

	ifstream in("users", ios::binary | ios::in);
	if (!in.is_open())
	{
		cout << "��������! ���� ��������� ������������� ���������� ��� ������. ����� ������ ����� ����" << endl;
		in.close();
		ofstream out("users", ios::binary | ios::out);
		out.close();
		return users;
	}

	while (!in.eof())
	{
		in.read((char*)&ID, sizeof(ID));     //���������� ����
		if (in.eof())
			break;

		size_t len;
		char* buf;

		in.read((char*)&len, sizeof(len));
		buf = new char[len];
		in.read(buf, len);
		name = buf;                              //���������� �����
		delete[] buf;

		in.read((char*)&len, sizeof(len));
		buf = new char[len];
		in.read(buf, len);
		login = buf;                             //���������� ������
		delete[] buf;

		in.read((char*)&len, sizeof(len));
		buf = new char[len];
		in.read(buf, len);
		password = buf;                          //���������� ������
		delete[] buf;

		in >> cart;

		User user(name, login, password, users.size() + 1, cart);
		users.insert(make_pair(login, user));
	}

	in.close();
	if (!in.bad())
		cout << "���������� ������ ��������� ������������� ������ �������." << endl;
	else
	{
		cout << "���������� ������ ��������� � �������. �������� �������� �� ������" << endl;
		in.clear();
	}

	return users;
}

map<string, FlowerAdmin> readFlowers()
{
	map<string, FlowerAdmin> flowers;

	ifstream in("flowers", ios::binary | ios::in);
	if (!in.is_open())
	{
		cout << "��������! ���� �������� � ������ ���������� ��� ������. ����� ������ ����� ����" << endl;
		in.close();
		ofstream out("flowers", ios::binary | ios::out);
		out.close();
		return flowers;
	}

	while (in.peek() != in.eof())
	{
		FlowerAdmin flower;
		if (in.eof())
			break;
		in >> flower;
		flowers.insert(make_pair(flower.returnName(), flower));
	}

	in.close();
	if (!in.bad())
		cout << "���������� ������ ������� ������ �������." << endl;
	else
	{
		cout << "���������� ������ ��������� � �������. �������� �������� � �������" << endl;
		in.clear();
	}

	return flowers;
}
