#pragma once

#include <iostream>
#include <list>
#include <conio.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include"Client.h"
//                  Функции
void saveUsers(vector<Client> Clients) {
	ofstream of("user.txt");
	for (auto iter : Clients) {
		of << iter.getLogin() << " " << iter.getPass() <<"\n";
	}
	of.close();
}
bool checkUniq(std::string log, std::vector<Client> ClientVector) {
	for (auto iter : ClientVector) {
		if (iter.getLogin() == log) {
			return true;
		}
	}
	return false;

}
bool isValidName(string name) {
	if (name == string(name.length(), ' ')) return false;
	bool isa = true;
	for (int i = 0; i < name.size(); i++) {
		if (name[i] == '\n' || name[i] == '\0')
			isa = false;
		else {
			isa = true;
		}
	}
	return isa;
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

//            Методы для работы с одеждой
bool User::checkEmpty() {
	if (ClothesVector.empty()) {
		cout << "Список одежды пуст\n";
		return true;
	}
	return false;
}
void User::showClothes() {

	for (auto iter : ClothesVector) {
		cout << "№" << iter.getID() << "\nТип: " << iter.getType() << "\nБренд: " << iter.getBrand() <<
			"\nАртикул: " << iter.getArt() << "\nРазмер: " << iter.getSize() << "\nЦвет: "
			<< iter.getColor() << "\nЦена: " << iter.getPrice() << "$\nКоличество: " << iter.getCount() <<
			"\n---------------------\n";
	}
}
void User::findClothes() {
	int choice;
	do {
		cout << "Искать:\n1 - По бренду\n2 - По типу\n3 - По цвету\n4 - По артикулу\n5 - По размеру\n0 - Назад\n";
		choice = input();
		cin.ignore();
		system("cls");
		if (choice > 5) {
			cout << "Такого пункта меню нет\n";
		}
	} while (choice > 5);
	vector <CL> lower;
	for (int i = 0; i < ClothesVector.size(); i++) {
		CL cl;
		cl.BRAND = ClothesVector[i].getBrand();
		cl.TYPE = ClothesVector[i].getType();
		cl.COLOR = ClothesVector[i].getColor();
		lower.push_back(cl);
	}
	to_lower(lower);
	if (choice == 9) { lower.clear(); return; }
	else if (choice == 1) {
		cout << "Введите бренд: ";
		string brand;
		bool find = false;
		getline(cin, brand);
		for (char& c : brand) c = to_lowercase(c);
		for (int i = 0; i < ClothesVector.size(); i++) {
			if (ClothesVector[i].getBrand() == brand || lower[i].BRAND == brand) {
				find = true;
				cout << "№" << ClothesVector[i].getID() << "\nТип: " << ClothesVector[i].getType() << "\nБренд: " << ClothesVector[i].getBrand() <<
					"\nАртикул: " << ClothesVector[i].getArt() << "\nРазмер: " << ClothesVector[i].getSize() << "\nЦвет: "
					<< ClothesVector[i].getColor() << "\nЦена: " << ClothesVector[i].getPrice() << "$\nКоличество: " << ClothesVector[i].getCount() <<
					"\n---------------------\n";
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
				cout << "№" << ClothesVector[i].getID() << "\nТип: " << ClothesVector[i].getType() << "\nБренд: " << ClothesVector[i].getBrand() <<
					"\nАртикул: " << ClothesVector[i].getArt() << "\nРазмер: " << ClothesVector[i].getSize() << "\nЦвет: "
					<< ClothesVector[i].getColor() << "\nЦена: " << ClothesVector[i].getPrice() << "$\nКоличество: " << ClothesVector[i].getCount() <<
					"\n---------------------\n";
			}
		}

		if (find == false) {
			cout << "Не найдено\n";
		}
	}
	else if (choice == 3) {
		string color;
		cout << "Введите цвет: ";
		bool find = false;
		getline(cin, color);
		for (char& c : color) c = to_lowercase(c);
		for (int i = 0; i < ClothesVector.size(); i++) {
			if (ClothesVector[i].getColor() == color || lower[i].COLOR == color) {
				find = true;
				cout << "№" << ClothesVector[i].getID() << "\nТип: " << ClothesVector[i].getType() << "\nБренд: " << ClothesVector[i].getBrand() <<
					"\nАртикул: " << ClothesVector[i].getArt() << "\nРазмер: " << ClothesVector[i].getSize() << "\nЦвет: "
					<< ClothesVector[i].getColor() << "\nЦена: " << ClothesVector[i].getPrice() << "$\nКоличество: " << ClothesVector[i].getCount() <<
					"\n---------------------\n";
			}
		}
		if (find == false) {
			cout << "Не найдено\n";
		}

	}
	else if (choice == 4) {
		cout << "1.Мужская\n2.Женская\n3.Детская\n0. Назад";
		int ch = input();
		cin.ignore();
		string art = "";
		if (ch == 0) { return; }
		else if (ch == 1) { art = "М"; }
		else if (ch == 2) { art = "Ж"; }
		else if (ch == 3) { art = "Д"; }
		bool find = false;
		for (auto iter : ClothesVector)
			if (iter.getArt() == art) {
				cout << "№" << iter.getID() << "\nТип: " << iter.getType() << "\nБренд: " << iter.getBrand() <<
					"\nАртикул: " << iter.getArt() << "\nРазмер: " << iter.getSize() << "\nЦвет: "
					<< iter.getColor() << "\nЦена: " << iter.getPrice() << "$\nКоличество: " << iter.getCount() <<
					"\n---------------------\n";
				find = true;
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
		for (auto iter : ClothesVector)
			if (iter.getSize() == size) {
				cout << "№" << iter.getID() << "\nТип: " << iter.getType() << "\nБренд: " << iter.getBrand() <<
					"\nАртикул: " << iter.getArt() << "\nРазмер: " << iter.getSize() << "\nЦвет: "
					<< iter.getColor() << "\nЦена: " << iter.getPrice() << "$\nКоличество: " << iter.getCount() <<
					"\n---------------------\n";
				find = true;
			}
		if (find == false) {
			cout << "Не найдено\n";
		}
	}
}
void User::sortClothes() {
	int key;
	do {
		cout << "\n---------- Сортировать ----------\n\n";
		cout << "1.По типу    3.По размеру\n";
		cout << "2.По бренду  4.По цене\n0.Назад\n";
		cout << "\n---------------------------------\n->";
		key = input();
		cin.ignore();
		system("cls");
		if (key > 4) {
			cout << "Такого пункта меню нет\n";
		}

	} while (true);
	if (key == 0) { return; }
	else if (key == 1) {
		cout << "\n--------------------\n\n1.А-Я\n2.Я-А\n0.Назад\n\n--------------------\n->";
		int c = input();
		cin.ignore();
		if (c == 9) {}
		else if (c == 1) {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getType() < c1.getType();
				});
		}
		else if (c == 2) {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getType() > c2.getType();
				});
		}
	}
	else if (key == 2) {
		cout << "1.А-Я\n2.Я-А\n0.Назад\n->";
		int c = input();
		if (c == 0) {}
		else if (c == 1) {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getBrand() < c2.getBrand();
				});
		}
		else if (c == 2) {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getBrand() > c2.getBrand();
				});
		}
	}
	else if (key == 3) {
		cout << "1.По возрастанию\n2.По убыванию\n0.Назад\n->";
		int c = input();
		if (c == 9) {}
		else if (c == 1) {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getSize() < c2.getSize();
				});
		}
		else if (c == 2) {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getSize() > c2.getSize();
				});
		}
	}
	else if (key == 4) {

		cout << "1.По возрастанию\n2.По убыванию\n0.Назад\n->";
		int c = input();
		if (c == 9) {}
		else if (c == 1) {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getPrice() < c2.getPrice();
				});
		}
		else if (c == 2) {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getPrice() > c2.getPrice();
				});
		}
	}

}
void Admin::addClothes() {
	int n;
	cout << "Сколько вещей хотите добавить: ";
	n = input();
	cin.ignore();
	string art, brand, color, type;
	int size, count;
	double price;
	cout << endl;
	for (int i = 0; i < n; i++) {
		/*
		* рубашки, свитеры, куртки, олимпийки,джинсы, брюки, футболки, поло
		*/
		cout << "Тип: "; do { getline(cin, type); } while (!isValidName(type));
		cout << "Бренд: "; do { getline(cin, brand); } while (!isValidName(brand));
		cout << "Цвет: "; do { getline(cin, color); } while (!isValidName(color));
		cout << "Артикул : "; do {
			getline(cin, art);
			if (!isValidName(art)) {
				cout << "Введите что-нибудь\n";
			}
			else if (art != "М" && art != "M" && art != "Ж" && art != "Д")
			{
				cout << "Похоже вы ввели что-то не, попробуйте так:\n";
				cout << "М - мужская, Ж - женская, Д - детская\n";
			}
		} while (!isValidName(art) || art != "М" && art != "M" && art != "Ж" && art != "Д");
		cout << "Размер: "; do {
			size = input();
			if (size < 42 || size > 56)
				cout << "Пожалуйта, попробуйте ввести другой размер\n";
			else if (size % 2 != 0)
				cout << "Размер должен быть кратен 2\n";
		} while (size < 42 || size > 56 || size % 2 != 0);
		cout << "Цена: "; do {
			price = dinput(); 
			if (price == 0)
				cout << "Цена должна быть выше нуля\n";
			else if (price > 50000)
				cout << "Пожалуйста, введите цену поменьше\n";
		} while (price > 50000 || price == 0);
		cout << "Количество: "; do {
			count = input();
			if (count == 0)
				cout << "Нельзя добавить 0шт.\n";
			else if (count > 5000)
				cout << "Пожалуйста, введите меньшее количество (на один экземпляр не более 5000шт на складе)\n";
		} while (count > 5000 || count ==0);
		cin.ignore();
		if (!ADD()) {
			continue;
		}
		Clothes newClothes(type, brand, art, size, color, price, count);
		ClothesVector.push_back(newClothes);
		cout << "Успешно добавлено" << endl;
	}

}
void Admin::deleteClothes() {
	cout << "\nВведите id вещи\n";
	int inputID = input();
	cin.ignore();
	if (isID(inputID)) {
		auto curr = find_if(ClothesVector.begin(), ClothesVector.end(), [inputID](Clothes& c) {
			return c.getID() == inputID;
			});
		ClothesVector.erase(curr);
	}
	else {
		cout << "Вещь не найдена\n";
	}

}
bool Admin::isID(int id) {
	for (auto iter : ClothesVector) {
		if (iter.getID() == id) {
			return true;
		}
	}
	return false;
}

//            Методы startInteraction
vector<Clothes> Client::startInteraction() {
	int key;
	while (true) {
		cout << "\n1.Просмотр всего ассортиментаn\n2. По определенному фильтру\n0. Назад\n";
		key = input();

		if (key == 0) {
			return ClothesVector;
		}

		else if (key == 1) {
			//вывод всех вещей
		}

		else if (key == 2) {
			//
		}
	}

}
vector<Clothes> Admin::startInteraction() {
	int key;
	bool $input;
	string $inputID;

	while (true) {
		do {
			cout << "\n----------------  Меню  ----------------\n\n";
			cout << "1.Добавить вещь    4.Редактировать\n\n";
			cout << "2.Просмотр одежды  5.Удалить\n\n";
			cout << "3.Поиск            6.Сортировка\n\n";
			cout << "0.Назад            7.Сменить логин\\пароль";
			cout << "\n\n--------------------------------------";
			cout << "\n->";
			key = input();
			system("cls");
			if (key > 7) {
				cout << "Такого пункта меню нет\n";
			}
		} while (key > 7);
		if (key == 0) {
			return ClothesVector;
		}
		else if (key == 1) {
			addClothes();
		}
		else if (key == 2) {
			if (!checkEmpty()) {
				showClothes();
			}
		}
		else if (key == 3) {
			if (!checkEmpty()) {
				findClothes();
			}
		}
		else if (key == 5) {
			if (!checkEmpty()) {
				showClothes();
				deleteClothes();
			}
		}
		else if (key == 6) {
			if (!checkEmpty()) {
				sortClothes();
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

//            Client
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


//           Admin
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
int Admin::checkInput(bool& isInputCorrect, string response) {
	try {
		return stoi(response);
	}
	catch (...) {
		isInputCorrect = false;
		cout << "Неправильный ввод!\n";
	}
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

// Перегрзки
ostream& operator << (ostream& os, Client& c)
{
	return os << c.login << " " << c.password << endl;
}
istream& operator>> (istream& is, Client& c) {
	return is >> c.login >> c.password;
}
