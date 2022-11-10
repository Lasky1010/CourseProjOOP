#pragma once

#include <iostream>
#include <list>
#include "conio.h"
#include <vector>
#include <fstream>
#include"Client.h"

bool checkUniq(std::string log, std::vector<Client> ClientVector) {
	for (auto iter : ClientVector) {
		if (iter.getLogin() == log) {
			return true;
		}
	}
	return false;

}


vector<Client> userFromFile() {
	vector<Client> vector;
	Client client;
	ifstream in("user.txt");
	if (in.is_open())
	{
		if (in.peek() == EOF)
		{
			cout << "Файл пуст!" << endl;
			in.close();
			return vector;
		}
		while (!in.eof())
		{
			in >> client;
			vector.push_back(client);
		}
	}
	else
	{
		cout << "Ошибка при открытии файла для чтения!" << endl;
	}
	in.close();
	return vector;
}

void saveUsers(vector<Client> Clients) {
	ofstream of("user.txt");
	for (auto iter : Clients) {
		of << iter.getLogin() << " " << iter.getPass();
	}
	of.close();
}

Client::Client(string log, string pass, vector<Clothes>CL) :login(log), password(pass) { ClothesVector = CL; }
Client::Client(vector<Clothes>ClothesVector) {
	this->ClothesVector = ClothesVector;
}
Client::Client() {
	login = "";
	password = "";
}
string Client::getLogin() { return login; }
string Client::getPass() { return password; }

void Client::startInteraction() {
	int key;
	while (true) {
		cout << "\n1.Просмотр всего ассортиментаn\n2. По определенному фильтру\n0. Назад\n";
		key = input();

		if (key == 0) {
			return;
		}

		else if (key == 1) {
			//вывод всех вещей
		}

		else if (key == 2) {
			//
		}
	}

}


ostream& operator << (ostream& os, Client& c)
{
	return os << c.login << " " << c.password<<endl;
}
istream& operator>> (istream& is, Client& c) {
	return is >> c.login >> c.password;
}

void User::showClothes(vector<Clothes> ClothesVector) {
	for (int i = 0; i < ClothesVector.size(); i++) {
		cout << ClothesVector[i] << endl;
	}
}
string Admin::getPass() { return AdminPass; }
string Admin::getLog() { return AdminLog; }
Admin::Admin(vector<Clothes>ClothesVector) {
	this->ClothesVector = ClothesVector;
}
void Admin::setList(vector<Clothes> ClothesVector) {
	this->ClothesVector = ClothesVector;
}
bool Admin::isDataCorrect(string login, string pass) {
	if (this->AdminLog == login && this->AdminPass == pass) {
		return true;
	}
	return false;
}
void Admin::startInteraction() {
	int key;
	bool $input;
	string $inputID;

	while (true) {
		do {
			cout<< "\n----------------  Меню  ----------------\n\n";
			cout<<"1.Добавить вещь    4.Редактировать\n\n";
			cout<<"2.Просмотр одежды  5.Удалить\n\n";
			cout<<"3.Поиск            6.Сортировка\n\n";
			cout<<"0.Назад            7.Сменить логин\\пароль";
			cout << "\n--------------------------------------";
			cout<<"\n->";
			key = input();
			if (key > 7 || key < 0) {
				cout << "Такого пункта меню нет\n";
			}
		} while (key > 7 || key < 0);
		if (key == 0) {
			return;
		}
		else if (key == 1) {
			addClothes();
		}
		else if (key == 2) {
			showClothes(ClothesVector);
		}
		else if (key == 3) {
			int choice;
			do {
				cout << "Искать:\n1 - По бренду\n2 - По типу\n3 - По цвету\n4 - По артикулу\n5 - По размеру\n9 - Назад\n";
				choice = input();
				cin.ignore();
				system("cls");
				if (choice > 4 && choice != 9) { cout << "Неверный выбор\n"; }
			} while (choice > 4 && choice != 9);
			vector <CL> lower;

			for (int i = 0; i < ClothesVector.size(); i++) {
				CL cl;
				cl.BRAND = ClothesVector[i].getBrand();
				cl.TYPE = ClothesVector[i].getType();
				cl.COLOR = ClothesVector[i].getColor();
				lower.push_back(cl);
			}

			to_lower(lower);
			if (choice == 9) { lower.clear(); break; }
			else if (choice == 1) {
				cout << "Введите бренд: ";
				string brand;
				bool find = false;
				getline(cin, brand);
				for (char& c : brand) c = to_lowercase(c);
				for (int i = 0; i < ClothesVector.size(); i++) {
					if (ClothesVector[i].getBrand() == brand || lower[i].BRAND == brand) {
						find = true;
						cout << ClothesVector[i];
					}
				}
				if (find == false) {
					cout << "Не найдено\n";
				}
			}
			else if (choice == 2) {
				cout << "Введите тип: ";
				cin.ignore();
				string type;
				bool find = false;
				getline(cin, type);
				for (char& c : type) c = to_lowercase(c);
				for (int i = 0; i < ClothesVector.size(); i++) {
					if (ClothesVector[i].getBrand() == type || lower[i].TYPE == type) {
						find = true;
						cout << ClothesVector[i];
					}
				}

				if (find == false) {
					cout << "Не найдено\n";
				}
			}
			else if (choice == 3) {
				string color;
				cout << "Введите цвет: ";
				cin.ignore();
				bool find = false;
				getline(cin, color);
				for (char& c : color) c = to_lowercase(c);
				for (int i = 0; i < ClothesVector.size(); i++) {
					if (ClothesVector[i].getColor() == color || lower[i].COLOR == color) {
						find = true;
						cout << ClothesVector[i];
					}
				}
				if (find == false) {
					cout << "Не найдено\n";
				}

			}
			else if (choice == 4) {
				cout << "1. М\n2. Ж\n3. Д\n0. Назад";
				int ch = input();
				cin.ignore();
				string art = "";
				if (ch == 0) { break; }
				else if (ch == 1) { art = "М"; }
				else if (ch == 2) { art = "Ж"; }
				else if (ch == 3) { art = "Д"; }
				bool find = false;
				for (int i = 0; i < ClothesVector.size(); i++) {
					if (ClothesVector[i].getArt() == art) {
						find = true;
						cout << ClothesVector[i];
					}
				}
				if (find == false) {
					cout << "Не найдено\n";
				}

			}
			else if (choice == 5) {
				cout << "Введите размер: ";
				bool find = false;
				int size = input();
				cin.ignore();
				for (int i = 0; i < ClothesVector.size(); i++)
					if (ClothesVector[i].getSize() == size) {
						cout << ClothesVector[i];
						find = true;
					}
				if (find == false) {
					cout << "Не найдено\n";
				}
			}

		}
		else if (key == 5) {
			cout << "Введите id вещи\n";
			cin >> $inputID;
			cin.ignore();
			$input = true;
			int id = checkInput($input, $inputID);
			if ($input) {
				if (isID(id)) {
					//deleteClothes(id);
				}
				else {
					cout << "Вещь не найдена\n";
				}
			}
		}
		/*else if (key == 4) {
			cout << "Введите id вещи\n";
			cin >> $inputID;
			$input = true;
			int id = checkInput($input, $inputID);
			if ($input) {
				if (isID(id)) {
					editClothes(id);
				}
				else {
					cout << "Вещь не найдена\n";
				}
			}
		}*/
		/*else if (key == 6) {
			ClothesVector.sort(SortClothes());
			cout << "Список отсортирован\n";
		}*/
		else if (key == 7) {
			editLogPass();
		}
		/*else if (key == 8) {
			filterClothes();
		}*/
	}
}

int Admin::checkInput(bool& isInputCorrect, string response) {
	try {
		return stoi(response);
	}
	catch (...) {
		isInputCorrect = false;
		cout << "Неправильный ввод!\n";
	}
}


void Admin::addClothes() {
	int n;
	cout << "Сколько вещей хотите добавить: ";
	cin >> n;
	cin.ignore();
	string art, brand, color, type;
	int size;
	double price;
	cout << endl;
	for (int i = 0; i < n; i++) {

		cout << "Тип: "; getline(cin, type);
		cout << "Бренд: "; getline(cin, brand);
		cout << "Цвет: "; getline(cin, color);
		cout << "Артикул: "; getline(cin, art);
		cout << "Размер: "; size = input();
		cout << "Цена: "; price = dinput();
		Clothes newClothes(type, brand, art, size, color, price);
		ClothesVector.push_back(newClothes);
		cout << endl;
	}

}


bool Admin::isID(int id) {
	for (auto iter:ClothesVector) {
		if (iter.getID() == id) {
			return true;
		}
	}
	return false;
}

void Admin::editLogPass() {
	int key;

	/**/
	do {
		cout << "\n1. Сменить логин и пароль\n2. Сменить логин\n3. Сменить пароль\n0. Выход";
		key = input();
		if (key > 3 || key < 0) {
			cout << "Такого пункта меню нет\n";
		}
		system("cls");
	} while (key > 3 || key < 0);

	if (key == 1) {
		cout << "\nВведите логин\n";
		cin >> this->AdminLog;
		cout << "\nВведите пароль\n";
		cin >> this->AdminLog;
	}
	else if (key == 2) {
		cout << "\nВведите логин\n";
		cin >> this->AdminLog;
	}
	else if (key == 3) {
		cout << "\nВведите пароль\n";
		cin >> this->AdminLog;
	}
	else if (key == 0) {
		return;
	}
}


