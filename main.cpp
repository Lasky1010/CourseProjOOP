#include <windows.h>
#include <memory>
#include <conio.h>
#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include "Clothes.h"
#include "Client.h"
using namespace std;

namespace CenterConsole {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	void GoToXY(short x, short y)
	{
		SetConsoleCursorPosition(hStdOut, { x, y });
	}
	void hidecursor()
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = FALSE;
		SetConsoleCursorInfo(consoleHandle, &info);
	}
	void centerLoadingStars() {
		system("cls");
		int x = 39;
		Sleep(300); GoToXY(x, 10); cout << "* ";
		Sleep(250); GoToXY(x + 2, 10); cout << "* ";
		Sleep(250); GoToXY(x + 4, 10); cout << "* ";
		Sleep(250); GoToXY(x + 6, 10); cout << "* ";
		Sleep(250); GoToXY(x + 8, 10); cout << "*"; Sleep(200);
		system("cls");
	}

}

void Exit(vector<Clothes>, vector<Client>);
int entry(vector<Client>, unique_ptr<Admin>&, string&, string&);
int input();


void enterPass(string&);

int authentication(string, string, vector<Client>, unique_ptr<Admin>&);
bool isValidString(string);

int main()
{
	CenterConsole::hidecursor();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	vector <CL> lower;
	unique_ptr<Admin> adm(new Admin());
	vector<Clothes> ClothesVector = clothesFromFile(lower);
	vector<Client>ClientVector = userFromFile();
	string entry_login, entry_password;
	int key;
	int access = entry(ClientVector, adm, entry_login, entry_password);
	if (access == 9)
		Exit(ClothesVector, ClientVector);
	while (true) {
		if (access == 1) {
			adm->setVectors(ClothesVector, lower);
			ClothesVector = adm->startInteraction();
			access = entry(ClientVector, adm, entry_login, entry_password);
			if (access == 9)
				Exit(ClothesVector, ClientVector);
		}
		else if (access == 2) {
			Client client(entry_login, entry_password, ClothesVector,lower);
			ClothesVector = client.startInteraction();
			access = entry(ClientVector, adm, entry_login, entry_password);
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
				if (regChoice != '2' && regChoice != '1')
					cout << "Пожалуйста, нажмите либо 1, либо 2\n->";
			} while (regChoice != '2' && regChoice != '1');
			if (regChoice == '1')
			{
				string reg_login, reg_pass;
				bool flag, flag2;
				do {
					cout << "------ Регистрация ------" << endl;
					do
					{
						flag2 = false;
						cout << "Введите логин:\t";
						getline(cin, reg_login);
						if (!isValidLogin(reg_login))
							flag2 = true;
						else if (reg_login == "Exit") {
							flag2 = true;
							cout << "Логин не может быть словом \"Exit\"\n";
						}
							
					} while (flag2);

					flag = checkUniq(reg_login, ClientVector, adm);
					if (flag)
						cout << "Пользователь под логином \"" << reg_login << "\" уже есть!" << endl;
				} while (flag);

				enterPass(reg_pass);
				Client c(reg_login, reg_pass, ClothesVector,lower);
				ClientVector.push_back(c);
				Client::count_reg_users++;
				ClothesVector = c.startInteraction();
				access = entry(ClientVector, adm, entry_login, entry_password);
				if (access == 9)
					Exit(ClothesVector, ClientVector);
			}
			else if (regChoice == '2') {
				access = entry(ClientVector, adm, entry_login, entry_password);
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

int entry(vector<Client> Clientvector, unique_ptr<Admin>& a, string& login, string& pass) {
	setAdminLogPass(a);
	int access = 0;
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
	enterPass(pass);
	if (pass == "Exit") return 9;
	CenterConsole::centerLoadingStars();
	access = authentication(login, pass, Clientvector, a);
	return access;
}
int authentication(string login, string password, vector<Client>ClientVector, unique_ptr<Admin>& a) {
	if (login == a->getLog() && password == a->getPass()) {
		return 1;
	}
	else {
		for (int i = 0; i < ClientVector.size(); i++) {
			if (ClientVector[i].getLogin() == login && ClientVector[i].getPass<string>() == password)
			{
				return 2;
			}
		}
		return 3;
	}
}

void enterPass(string& pass) {
	char kod;
	bool flag;
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
}
