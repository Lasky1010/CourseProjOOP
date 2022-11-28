#include <windows.h>
#include <conio.h>
#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include "Clothes.h"
#include "Client.h"
using namespace std;

void Exit(vector<Clothes>, vector<Client>);
int input();
void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

int entry(vector<Client>, Admin&);
int authentication(string, string, vector<Client>, Admin&);
bool isValidName(string);

int main()
{
	hidecursor();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	vector<Clothes> ClothesVector = clothesFromFile();
	vector<Client>ClientVector = userFromFile();
	int key;
	Admin a;
	int access = entry(ClientVector, a);
	if (access == 9) 
		Exit(ClothesVector, ClientVector);
	while (true) {
		if (access == 1) {
			Admin admin(ClothesVector);
			ClothesVector = admin.startInteraction();
			access = entry(ClientVector, a);
			if (access == 9) 
				Exit(ClothesVector, ClientVector);
		}
		else if (access == 2) {
			Client client(ClothesVector);
			ClothesVector = client.startInteraction();
			access = entry(ClientVector, a);
			if (access == 9) 
				Exit(ClothesVector, ClientVector);
		}
		else if (access == 3) {
			int regChoice;
			do {
				cout << "\nЛогин или пароль введен неправильно!";
				cout << "\nИли такого пользователя не существует\nХотите зарегистрироваться ?\n     1.Да\t2.Нет\n->";
				regChoice = _getch();
				system("cls");
				if (regChoice != '2' && regChoice !='1')
					cout << "Пожалуйста, нажмите либо 1, либо 2\n->";
			} while (regChoice != '2' && regChoice != '1');
			if (regChoice == '1')
			{
				string login, pass;
				bool flag, flag2;
				do {
					cout << "------ Регистрация ------" << endl;
					do
					{
						flag2 = false;
						cout << "Введите логин:\t";
						getline(cin, login);
						if (!isValidLogin(login))
							flag2 = true;
					} while (flag2);

					flag = checkUniq(login, ClientVector, a);
					if (flag) 
						cout << "Пользователь под логином \"" << login << "\" уже есть!" << endl;
				} while (flag);
				char kod;
				do {
					flag2 = false;
					pass = "";
					cout << "Пароль:\t";
					while (true) {

						kod = _getch();
						if (kod == 8) {
							if (!pass.length()) continue;
							else
								cout << "\b \b";
							pass.resize(pass.length() - 1);
						}
						else if (kod == 13) {
							break;
						}
						else {
							pass += kod;
							cout << "*";
						}
					}
					cout << endl;
					if (!isValidPass(pass))
						flag2 = true;
				} while (flag2);
				Client c(login, pass, ClothesVector);
				ClientVector.push_back(c);
				ClothesVector = c.startInteraction();
				access = entry(ClientVector, a);
				if (access == 9) 
					Exit(ClothesVector, ClientVector);
			}
			else if (regChoice == '2') {
				access = entry(ClientVector, a);
				if (access == 9) 
					Exit(ClothesVector, ClientVector);
			}
		}
	}
	return 0;
}

void Exit(vector<Clothes> Clothesvector, vector<Client> Clientvector) {
	saveClothes(Clothesvector);
	saveUsers(Clientvector);
	exit(0);
}

int entry(vector<Client> Clientvector, Admin& a) {
	a.setAdminLogPass();
	int access = 0;
	string login, pass;
	cout << "Введите \"Exit\", если хотите выйти\n";
	bool flag;
	do
	{
		flag = false;
		cout << "Логин:\t";
		getline(cin, login);
		if (!isValidLogin(login)) 
			flag = true;
	} while (flag);
	if (login == "Exit") return 9;
	char kod;
	do {
		pass = "";
		flag = false;
		cout << "Пароль:\t";
		while (true) {

			kod = _getch();
			if (kod == 8) {
				if (!pass.length()) continue;
				else
					cout << "\b \b";
				pass.resize(pass.length() - 1);
			}
			else if (kod == 13) {
				break;
			}
			else {
				pass += kod;
				cout << "*";
			}
		}
		cout << endl;
		if (!isValidPass(pass)) 
			flag = true;
	} while (flag);
	
	
	if (pass == "Exit") return 9;
	access = authentication(login, pass, Clientvector, a);
	return access;
}
int authentication(string login, string password, vector<Client>ClientVector, Admin& a) {
	if (login == a.getLog() && password == a.getPass()) {
		return 1;
	}
	else {
		for (int i = 0; i < ClientVector.size(); i++) {
			if (ClientVector[i].getLogin() == login && ClientVector[i].getPass() == password)
			{
				return 2;
			}
		}
		return 3;
	}
}

