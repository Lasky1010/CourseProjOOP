#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include <conio.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include<chrono>
#include"Client.h"
//                  Функции
void saveUsers(vector<Client> Clients) {
	ofstream of("user.txt");
	of.clear();
	for (auto iter : Clients) {
		of << iter.getLogin() << " " << iter.getPass() << "\n";
	}
	of.close();
}
bool checkUniq(string log, vector<Client> ClientVector, Admin& a) {
	for (auto iter : ClientVector) {
		if (iter.getLogin() == log || log == a.getLog()) {
			return true;
		}
	}
	return false;

}
bool isValidName(string name) {
	if (name == string(name.length(), ' ')) return false;
	for (int i = 0; i < name.size(); i++) {
		if (name[i] == '\n' || name[i] == '\0')
			return false;
	}
	return true;
}
bool Client::isValidCard(string numb) {
	if (numb == string(numb.length(), ' ')) return false;
	if (numb.size() != 16) {
		cout << "Номер карты состоит из 16 цифр, попробуйте ещё раз\n";
		return false;
	}
	for (int i = 0; i < numb.size(); i++) {
		if (!isdigit(numb[i])) {
			cout << "Номер карты должен состоит только из цифр, попробуйте ещё раз\n";
			return false;
		}
	}
	for (int i = 0; i < numb.size(); i++) {
		if (numb[i] == '\n' || numb[i] == '\0')
			return false;
	}

	return true;
}
bool isValidPass(string name) {
	if (name == string(name.length(), ' ')) return false;
	if (name.size() < 8 || name.size() > 17)
	{
		cout << "Пароль должен содержать от 8 до 17 символов, попробуйте ещё раз\n";
		return false;
	}
	for (int i = 0; i < name.size(); i++) {
		if (name[i] == ' ')
		{
			cout << "Пароль не может содержать пробел, попробуйте ещё раз\n";
			return false;
		}
		else if (name[i] == '\n' || name[i] == '\0') {
			return false;
		}
	}
	for (int i = 0; i < name.size(); i++) {
		if (name[i] >= 192 && name[i] <= 255) {
			cout << "Кириллица не поддерживается, попробуйте ещё раз\n";
			return false;
		}
	}
	bool flag = false;
	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] >= 'A' && name[i] <= 'Z')
		{
			flag = true;
			break;
		}
	}
	if (!flag)
	{
		cout << "Пароль должен содержать хотя бы одну заглавную букву, попробуйте ещё раз\n";
		return false;
	}
	flag = false;
	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] >= '0' && name[i] <= '9')
		{
			flag = true;
			break;
		}
	}
	if (!flag)
	{
		cout << "Пароль должен содержать хотя бы одну цифру, попробуйте ещё раз\n";
		return false;
	}
	return true;
}
bool isValidLogin(string name) {
	if (name == string(name.length(), ' ')) return false;
	if (name.size() < 3 || name.size() > 15)
	{
		cout << "Логин должен содержать от 3 до 15 символов, попробуйте ещё раз\n";
		return false;
	}
	for (int i = 0; i < name.size(); i++) {
		if (name[i] >= 192 && name[i] <= 255) {
			cout << "Кириллица не поддерживается, попробуйте еще раз\n";
			return false;
		}
	}
	for (int i = 0; i < name.size(); i++) {
		if (name[i] == ' ')
		{
			cout << "Логин не может содержать пробел, попробуйте ещё раз\n";
			return false;
		}
		else if (name[i] == '\n' || name[i] == '\0') {
			return false;
		}
	}
	return true;
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
		while (true)
		{

			in >> client;
			if (in.eof()) break;
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
	bool flag;
	do {
		flag = false;
		cout << "Искать:\n1 - По бренду\n2 - По типу\n3 - По цвету\n4 - По артикулу\n5 - По размеру\n0 - Назад\n";
		//choice = input();
		//cin.ignore();
		choice = _getch();
		system("cls");
		if (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != 27) {
			cout << "Такого пункта меню нет\n";
			flag = true;
		}
	} while (flag);

	if (choice == 27) { lower.clear(); return; }
	else if (choice == 1) {
		cout << "Введите бренд: ";
		string brand;
		bool find = false;
		getline(cin, brand);
		for (char& c : brand) c = to_lowercase(c);
		for (int i = 0; i < ClothesVector.size(); i++) {
			if (ClothesVector[i].getBrand() == brand && lower[i].BRAND == brand) {
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
	else if (choice == '2') {
		cout << "Введите тип: ";
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
	else if (choice == '3') {
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
		cout << "1.Мужская\n2.Женская\n3.Детская\nEsc.Назад";
		int ch = _getch();
		string art = "";
		if (ch == 27) { return; }
		else if (ch == '1') { art = "М"; }
		else if (ch == '2') { art = "Ж"; }
		else if (ch == '3') { art = "Д"; }
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
	else if (choice == '5') {
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
	bool fl;
	do {
		fl = false;
		cout << "\n---------- Сортировать ----------\n\n";
		cout << "1.По типу    3.По размеру\n";
		cout << "2.По бренду  4.По цене\nEsc.Назад\n";
		cout << "\n---------------------------------\n->";
		key = _getch();
		system("cls");
		if (key != '1' && key != '2' && key != '3' && key != '4' && key != 27) {
			cout << "Такого пункта меню нет\n";
			fl = true;
		}

	} while (fl);
	if (key == 27) { return; }
	else if (key == '1') {
		cout << "\n--------------------\n\n1.А-Я\n2.Я-А\nEsc.Назад\n\n--------------------\n->";
		int c = _getch();
		if (c == '9') {}
		else if (c == '1') {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getType() < c1.getType();
				});
		}
		else if (c == '2') {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getType() > c2.getType();
				});
		}
	}
	else if (key == '2') {
		cout << "1.А-Я\n2.Я-А\nEsc.Назад\n->";
		int c = _getch();
		if (c == 27) {}
		else if (c == '1') {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getBrand() < c2.getBrand();
				});
		}
		else if (c == '2') {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getBrand() > c2.getBrand();
				});
		}
	}
	else if (key == '3') {
		cout << "1.По возрастанию\n2.По убыванию\nEsc.Назад\n->";
		int c = _getch();
		if (c == 27) {}
		else if (c == '1') {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getSize() < c2.getSize();
				});
		}
		else if (c == '2') {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getSize() > c2.getSize();
				});
		}
	}
	else if (key == '4') {

		cout << "1.По возрастанию\n2.По убыванию\nEsc.Назад\n->";
		int c = _getch();

		if (c == 27) {}
		else if (c == '1') {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getPrice() < c2.getPrice();
				});
		}
		else if (c == '2') {
			sort(ClothesVector.begin(), ClothesVector.end(), [](Clothes& c1, Clothes& c2)
				{
					return c1.getPrice() > c2.getPrice();
				});
		}
	}
	cout << "Успешно отсортировано\n";
}
void User::filterClothes() {
	char key;
	bool flag;
	int size;
	while (1) {
		do {
			flag = false;
			cout << "\n---------------  Фильтр  ---------------\n\n";
			cout << "1.По размеру и артикулу  4.По размеру и цвету\n\n";
			cout << "2.По размеру и бренду    5.По размеру и цене\n\n";
			cout << "3.По размеру и типу      Esc.Назад\n\n";
			cout << "\n\n--------------------------------------";
			cout << "\n->";
			key = _getch();
			system("cls");
			if (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != 27) {
				cout << "Такого пункта меню нет\n";
				flag = true;
			}
		} while (flag);
		if (key == '0') {
			return;
		}
		do {
			cout << "Введите желаемый размер: ";
			size = input();
			cin.ignore();
			if (size < 42 || size > 56)
				cout << "Пожалуйта, попробуйте ввести другой размер\n";
			else if (size % 2 != 0)
				cout << "Размер должен быть кратен 2\n";
		} while (size < 42 || size > 56 || size % 2 != 0);
		if (key == '1') {

			char ch;
			string art;
			do {
				cout << "1.Мужская\n2.Женская\n3.Детская\nEsc.Назад";
				ch = _getch();
				art = "";
				if (ch == 27) { return; }
				else if (ch == '1') { art = "М"; }
				else if (ch == '2') { art = "Ж"; }
				else if (ch == '3') { art = "Д"; }
			} while (ch != '1' && ch != '2' && ch != '3' && ch != '0');
			bool find = false;

			for (auto iter : ClothesVector)
				if (iter.getSize() == size && iter.getArt() == art) {
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
		else if (key == '2') {
			string brand;
			bool flag;
			do {
				flag = false;
				cout << "Введите бренд: ";
				string brand;
				getline(cin, brand);
				if (!isValidName(brand))
					flag = true;
			} while (flag);

			bool find = false;

			for (char& c : brand) c = to_lowercase(c);
			for (int i = 0; i < ClothesVector.size(); i++) {
				if (ClothesVector[i].getBrand() == brand && lower[i].BRAND == brand) {
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
		else if (key == '3') {
			string type;
			bool flag;
			do {
				flag = false;
				cout << "Введите тип: ";
				getline(cin, type);
				if (!isValidName(type))
					flag = true;
			} while (flag);

			bool find = false;

			for (char& c : type) c = to_lowercase(c);
			for (int i = 0; i < ClothesVector.size(); i++) {
				if (ClothesVector[i].getType() == type && lower[i].TYPE == type) {
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
		else if (key == '4') {
			string color;
			bool flag;
			do {
				flag = false;
				cout << "Введите цвет: ";
				getline(cin, color);
				if (!isValidName(color))
					flag = true;
			} while (flag);

			bool find = false;

			for (char& c : color) c = to_lowercase(c);
			for (int i = 0; i < ClothesVector.size(); i++) {
				if (ClothesVector[i].getBrand() == color && lower[i].COLOR == color) {
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
		else if (key == '5') {
			double MIN, MAX;
			bool flag;
			do {
				flag = false;
				cout << "От какой цены: "; MIN = dinput();
				cin.ignore();
				if (MIN > 50000) {
					flag = true;
					cout << "Максимум 50000$, попробуйте ещё раз\n";
				}
				cout << "До какой цены: "; MAX = dinput();
				cin.ignore();
				if (MAX > 50000) {
					flag = true;
					cout << "Максимум 50000$, попробуйте ещё раз\n";
				}
				if (MIN > MAX) {
					flag = true;
					cout << "Минимальный порог не может быть больше максимального, попробуйте ещё раз\n";
				}
			} while (flag);
			bool find = false;

			for (auto iter : ClothesVector)
				if (iter.getSize() == size && (MIN <= iter.getPrice() <= MAX)) {
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
			cin.ignore();
			if (size < 42 || size > 56)
				cout << "Пожалуйта, попробуйте ввести другой размер\n";
			else if (size % 2 != 0)
				cout << "Размер должен быть кратен 2\n";
		} while (size < 42 || size > 56 || size % 2 != 0);
		cout << "Цена: "; do {
			price = dinput();
			cin.ignore();
			if (price == 0)
				cout << "Цена должна быть выше нуля\n";
			else if (price > 50000)
				cout << "Пожалуйста, введите цену поменьше\n";
		} while (price > 50000 || price == 0);
		cout << "Количество: "; do {
			count = input();
			cin.ignore();
			if (count == 0)
				cout << "Нельзя добавить 0шт.\n";
			else if (count > 5000)
				cout << "Пожалуйста, введите меньшее количество (на один экземпляр не более 5000шт на складе)\n";
		} while (count > 5000 || count == 0);
		//cin.ignore();
		if (!ADD()) {
			continue;
		}

		CL cl;
		cl.BRAND = brand;
		cl.TYPE = type;
		cl.COLOR = color;
		lower.push_back(cl);
		Clothes newClothes(type, brand, art, size, color, price, count);
		ClothesVector.push_back(newClothes);
		cout << "Успешно добавлено" << endl;
	}
	to_lower(lower);
}
Admin::Admin() {}
void Admin::deleteClothes() {
	int inputID;
	bool flag;
	do {
		cout << "\nВведите id вещи\n";
		flag = false;
		inputID = input();
		cin.ignore();
		if (!isID(inputID)) {
			flag = true;
			cout << "Неверный ID, попробуйте ещё раз\n";
		}
	} while (flag);
	auto curr = find_if(ClothesVector.begin(), ClothesVector.end(), [inputID](Clothes& c) {
		return c.getID() == inputID;
		});
	if (DEL()) {
		ClothesVector.erase(curr);
		cout << "Успешно удалено\n";
	}
	else {
		cout << "Операция отменена\n";
	}
	

}
bool User::isID(int id) {
	for (auto iter : ClothesVector) {
		if (iter.getID() == id) {
			return true;
		}
	}
	return false;
}
void Client::addCart() {
	cout << "Какую вещь добавить в корзину ?\n";
	cout << "Введите id вещи: ";
	int id;
	bool flag;
	do {
		flag = false;
		id = input();
		cin.ignore();
		if (!isID(id)) {
			flag = true;
			cout << "Неверный ID, попробуйте ещё раз\n";
		}
	} while (flag);
	auto found = find_if(ClothesVector.begin(), ClothesVector.end(), [id](Clothes& c) {
		return c.getID() == id;
		});
	int kol;
	
	do {
		flag = false;
		cout << "Сколько единиц хотите добавить в корзину ?\n->";
		kol = input();
		cin.ignore();
		if (kol > (*found).getCount()) {
			flag = true;
			cout << "Введенное количество превышает доступное количество данного товара, попробуйте ещё раз\n";
		}
	} while (flag);
	Clothes add = *found;
	add.setCount(kol);
	cart.push_back(add);
	cout << "Вещь добавлена в корзину\n";
}
bool Client::checkCart() {
	if (cart.empty()) {
		cout << "Корзина пуста\n";
		return true;
	}
	return false;
}
void Client::menuCart() {
	char key;
	bool flag;
	while (true) {
		do {
			flag = false;
			cout << "\n------------  Меню  ------------\n\n";
			cout << "1.Просмотреть    3.Удалить\n\n";
			cout << "2.Купить         Esc.Назад";
			cout << "\n\n------------------------------";
			cout << "\n->";
			key = _getch();
			system("cls");
			if (key != '1' && key != '2' && key != '3' && key != 27) {
				cout << "Такого пункта меню нет\n";
				flag = true;
			}
		} while (flag);
		if (key == 27)
			return;
		if (key == '1')
			showCart();
		else if (key == '2')
			buy();
		else if (key == '3')
			deleteCart();
	}
}
void Client::showCart() {
	int i = 1;
	for (auto i : cart)
		priceCart += i.getPrice() * i.getCount();
	cout << "Корзина: " << priceCart << "$\n";
	for (auto iter : cart) {
		cout <<"#" <<i++<< "\n№" << iter.getID() << "\nТип: " << iter.getType() << "\nБренд: " << iter.getBrand() <<
			"\nАртикул: " << iter.getArt() << "\nРазмер: " << iter.getSize() << "\nЦвет: "
			<< iter.getColor() << "\nЦена: " << iter.getPrice() << "$\nКоличество: " << iter.getCount() <<
			"\n---------------------\n";
	}
}
void Client::deleteCart() {
	int n;
	bool flag;
	do {
		cout << "\nКакую вещь удалить из корзины по номеру: \n";
		flag = false;
		n = input();
		cin.ignore();
		if (n > cart.size()) {
			flag = true;
			cout << "Такой позиции нет, попробуйте ещё раз\n";
		}
	} while (flag);
	auto curr = cart.begin() + n-1;
	cart.erase(curr);
	priceCart -= (*curr).getPrice() * (*curr).getCount();
}
void Client::writeReport(Clothes cart,time_t end_time) {
	ofstream file("report.txt",ios::app);
	file<<"Оплачено: "+to_string(priceCart) + "$\nID: "
		+ to_string(cart.getID()) + "; "
		+ cart.getBrand() + "; "
		+ cart.getType() + "; "
		+ cart.getArt() + "; "
		+ cart.getColor() + "; "
		+ to_string(cart.getSize()) + "\n"
		+ ctime(&end_time) + "\n";

}
void Client::buy() {
	enterCard();
	int cartsize = cart.size();
	auto now = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(now);
	if (BUY()) {
		for (int j=0,i = 0; j <cartsize ; i++)
			if(cart[j].getID() == ClothesVector[i].getID()) {
				ClothesVector[i].setCount(ClothesVector[i].getCount() - cart[j].getCount());
				writeReport(cart[j], end_time);
				j++;
			}

		printBill(end_time);
		cart.clear();

	}
	else return;
}
void Client::printBill(time_t end_time) {

	ofstream file("bill.txt");
	string bill ="***************************\n"
	        	"*                         *\n"
	        	"* ООО \"Курсовой проект\"   *\n"
	        	"*     ул.Платонова, 39    *\n"
	        	"*                         *\n"
	        	"***************************\n"
	        	"                             \n"
	        	"      Оплата: онлайн        \n"
	        	"    Безналичный расчёт      \n"
	        	"           "+to_string(priceCart)+"$\n"
	        	"  " + ctime(&end_time) +"      \n"
	        	"                             \n";

	file << bill;
	cout << bill;

}
void Client::enterCard() {
	bool flag;
	
	do {
		cout << "Введите номер карты: ";
		flag = false;
		getline(cin, card.cardNumber);
		if (!isValidCard(card.cardNumber))
		{
			flag = true;
			cout << "Неверно введен номер банковской карты";
		}
	} while (flag);

	cout << "Введите месяц и год окончания действительности карты\n";
	do { 
		flag = false;
		card.month = input();
		cin.ignore();
		if (card.month > 12) {
			cout << "Месяцев 12, попробуйте ещё раз\n";
			flag = true;
		}
	} while (flag);
	do {
		flag = false;
		card.year = input();
		cin.ignore();
		if (card.year < 2023) {
			cout <<"Карта просрочена, попробуйте ещё раз\n";
			flag = true;
		}
		if (card.year > 2030) {
			cout << "Таких карт нет, попробуйте ещё раз\n";
			flag = true;
		}	
	} while (flag);

	do {
		flag = false;
		cout << "Введите CVV-код, расположенный на обратной стороне карты: ";
		card.cvv = input();
		cin.ignore();
		if (card.cvv > 999 || card.cvv < 100) {
			cout << "CVV-код должен быть трёхзначным, попробуйте ещё раз\n";
			flag = true;
		}
	} while (flag);
}
//            Методы startInteraction
vector<Clothes> Client::startInteraction() {
	char key;
	bool flag;
	while (true) {
		do {
			flag = false;
			cout << "\n----------------  Меню  ----------------\n\n";
			cout << "1.Просмотр одежды  4.Сортировка\n\n";
			cout << "2.Поиск            5.Купить\n\n";
			cout << "3.Фильтрация       6.Корзина\n\n";
			cout << "Esc.Назад            \n";
			cout << "\n----------------------------------------";
			cout << "\n->";
			key = _getch();
			system("cls");
			if (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != 27) {
				cout << "Такого пункта меню нет\n";
				flag = true;
			}
		} while (flag);
		if (key == 27) {
			return ClothesVector;
		}

		else if (key == '1') {
			if (!checkEmpty()) {
				showClothes();
			}
		}

		else if (key == '2') {
			if (!checkEmpty()) {
				findClothes();
			}
		}
		else if (key == '3') {
			if (!checkEmpty()) {
				filterClothes();
			}
		}
		else if (key == '4') {
			if (!checkEmpty()) {
				sortClothes();
			}
		}
		else if (key == '5') {
			if (!checkEmpty()) {
				showClothes();
				addCart();
			}
		}
		else if (key == '6') {
			if (!checkCart()) {
				menuCart();
			}
		}
		else if (key == '7') {

		}
	}

}
vector<Clothes> Admin::startInteraction() {
	int key;
	bool flag;
	while (true) {
		do {
			flag = false;
			cout << "\n----------------  Меню  ----------------\n\n";
			cout << "1.Добавить вещь    4.*Редактировать\n\n";
			cout << "2.Просмотр одежды  5.Удалить\n\n";
			cout << "3.Поиск            6.Сортировка\n\n";
			cout << "Esc.Назад            7.Сменить логин\\пароль";
			cout << "\n\n--------------------------------------";
			cout << "\n->";
			key = _getch();
			system("cls");
			if (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != '7' && key != 27) {
				cout << "Такого пункта меню нет\n";
				flag = true;
			}
		} while (flag);
		if (key == '0') {
			return ClothesVector;
		}
		else if (key == '1') {
			addClothes();
		}
		else if (key == '2') {
			if (!checkEmpty()) {
				showClothes();
			}
		}
		else if (key == '3') {
			if (!checkEmpty()) {
				findClothes();
			}
		}
		else if (key == '5') {
			if (!checkEmpty()) {
				showClothes();
				deleteClothes();
			}
		}
		else if (key == '6') {
			if (!checkEmpty()) {
				sortClothes();
			}
		}
		else if (key == '7') {
			editLogPass();
			saveAdminLogPass();
		}
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
void Admin::setAdminLogPass() {
	fstream adm("admin.txt", ios::in);
	getline(adm, AdminLog);
	getline(adm, AdminPass);
}

void Admin::saveAdminLogPass() {
	fstream adm("admin.txt", ios::out);
	adm.clear();
	adm << AdminLog << endl;
	adm << AdminPass;
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
		//cout << "\n1. Сменить логин и пароль\n2. Сменить логин\n3. Сменить пароль\n0. Выход";
		cout << "--------- Изменить ---------\n";
		cout << "\n1.Логин и пароль   3.Пароль\n";
		cout << "2.Логин              Esc.Назад\n\n";
		cout << "----------------------------\n->";
		key = _getch();
		if (key != '1' && key != '2' && key != '3' && key != 27) {
			cout << "Такого пункта меню нет\n";
		}
		system("cls");
	} while (key > 3);
	bool flag = true;;
	if (key == 1) {
		cout << "Введите";
		do {
			flag = true;
			cout << "\nЛогин: ";
			getline(cin, AdminLog);
			if (!isValidLogin(AdminLog))
				flag = false;
		} while (!flag);
		do {
			flag = true;
			cout << "\nПароль: ";
			getline(cin, AdminPass);
			if (!isValidPass(AdminPass))
				flag = false;
		} while (!flag);


	}
	else if (key == 2) {
		do {
			flag = true;
			cout << "\nЛогин: ";
			getline(cin, AdminLog);
			if (!isValidLogin(AdminLog))
				flag = false;
		} while (!flag);
	}
	else if (key == 3) {
		do {
			flag = true;
			cout << "\nПароль: ";
			getline(cin, AdminPass);
			if (!isValidPass(AdminPass))
				flag = false;
		} while (!flag);

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
