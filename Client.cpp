#pragma once

#include <iostream>
#include <list>
#include <conio.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include"Client.h"
//                  �������
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
			cout << "���� ����!" << endl;
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
		cout << "������ ��� �������� ����� ��� ������!" << endl;
	}
	in.close();
	return vector;
}

//            ������ ��� ������ � �������
bool User::checkEmpty() {
	if (ClothesVector.empty()) {
		cout << "������ ������ ����\n";
		return true;
	}
	return false;
}
void User::showClothes() {

	for (auto iter : ClothesVector) {
		cout << "�" << iter.getID() << "\n���: " << iter.getType() << "\n�����: " << iter.getBrand() <<
			"\n�������: " << iter.getArt() << "\n������: " << iter.getSize() << "\n����: "
			<< iter.getColor() << "\n����: " << iter.getPrice() << "$\n����������: " << iter.getCount() <<
			"\n---------------------\n";
	}
}
void User::findClothes() {
	int choice;
	do {
		cout << "������:\n1 - �� ������\n2 - �� ����\n3 - �� �����\n4 - �� ��������\n5 - �� �������\n0 - �����\n";
		choice = input();
		cin.ignore();
		system("cls");
		if (choice > 5) {
			cout << "������ ������ ���� ���\n";
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
		cout << "������� �����: ";
		string brand;
		bool find = false;
		getline(cin, brand);
		for (char& c : brand) c = to_lowercase(c);
		for (int i = 0; i < ClothesVector.size(); i++) {
			if (ClothesVector[i].getBrand() == brand || lower[i].BRAND == brand) {
				find = true;
				cout << "�" << ClothesVector[i].getID() << "\n���: " << ClothesVector[i].getType() << "\n�����: " << ClothesVector[i].getBrand() <<
					"\n�������: " << ClothesVector[i].getArt() << "\n������: " << ClothesVector[i].getSize() << "\n����: "
					<< ClothesVector[i].getColor() << "\n����: " << ClothesVector[i].getPrice() << "$\n����������: " << ClothesVector[i].getCount() <<
					"\n---------------------\n";
			}
		}
		if (find == false) {
			cout << "�� �������\n";
		}
	}
	else if (choice == 2) {
		cout << "������� ���: ";
		cin.ignore();
		string type;
		bool find = false;
		getline(cin, type);
		for (char& c : type) c = to_lowercase(c);
		for (int i = 0; i < ClothesVector.size(); i++) {
			if (ClothesVector[i].getBrand() == type || lower[i].TYPE == type) {
				find = true;
				cout << "�" << ClothesVector[i].getID() << "\n���: " << ClothesVector[i].getType() << "\n�����: " << ClothesVector[i].getBrand() <<
					"\n�������: " << ClothesVector[i].getArt() << "\n������: " << ClothesVector[i].getSize() << "\n����: "
					<< ClothesVector[i].getColor() << "\n����: " << ClothesVector[i].getPrice() << "$\n����������: " << ClothesVector[i].getCount() <<
					"\n---------------------\n";
			}
		}

		if (find == false) {
			cout << "�� �������\n";
		}
	}
	else if (choice == 3) {
		string color;
		cout << "������� ����: ";
		bool find = false;
		getline(cin, color);
		for (char& c : color) c = to_lowercase(c);
		for (int i = 0; i < ClothesVector.size(); i++) {
			if (ClothesVector[i].getColor() == color || lower[i].COLOR == color) {
				find = true;
				cout << "�" << ClothesVector[i].getID() << "\n���: " << ClothesVector[i].getType() << "\n�����: " << ClothesVector[i].getBrand() <<
					"\n�������: " << ClothesVector[i].getArt() << "\n������: " << ClothesVector[i].getSize() << "\n����: "
					<< ClothesVector[i].getColor() << "\n����: " << ClothesVector[i].getPrice() << "$\n����������: " << ClothesVector[i].getCount() <<
					"\n---------------------\n";
			}
		}
		if (find == false) {
			cout << "�� �������\n";
		}

	}
	else if (choice == 4) {
		cout << "1.�������\n2.�������\n3.�������\n0. �����";
		int ch = input();
		cin.ignore();
		string art = "";
		if (ch == 0) { return; }
		else if (ch == 1) { art = "�"; }
		else if (ch == 2) { art = "�"; }
		else if (ch == 3) { art = "�"; }
		bool find = false;
		for (auto iter : ClothesVector)
			if (iter.getArt() == art) {
				cout << "�" << iter.getID() << "\n���: " << iter.getType() << "\n�����: " << iter.getBrand() <<
					"\n�������: " << iter.getArt() << "\n������: " << iter.getSize() << "\n����: "
					<< iter.getColor() << "\n����: " << iter.getPrice() << "$\n����������: " << iter.getCount() <<
					"\n---------------------\n";
				find = true;
			}
		if (find == false) {
			cout << "�� �������\n";
		}
	}
	else if (choice == 5) {
		cout << "������� ������: ";
		bool find = false;
		int size = input();
		cin.ignore();
		for (auto iter : ClothesVector)
			if (iter.getSize() == size) {
				cout << "�" << iter.getID() << "\n���: " << iter.getType() << "\n�����: " << iter.getBrand() <<
					"\n�������: " << iter.getArt() << "\n������: " << iter.getSize() << "\n����: "
					<< iter.getColor() << "\n����: " << iter.getPrice() << "$\n����������: " << iter.getCount() <<
					"\n---------------------\n";
				find = true;
			}
		if (find == false) {
			cout << "�� �������\n";
		}
	}
}
void User::sortClothes() {
	int key;
	do {
		cout << "\n---------- ����������� ----------\n\n";
		cout << "1.�� ����    3.�� �������\n";
		cout << "2.�� ������  4.�� ����\n0.�����\n";
		cout << "\n---------------------------------\n->";
		key = input();
		cin.ignore();
		system("cls");
		if (key > 4) {
			cout << "������ ������ ���� ���\n";
		}

	} while (true);
	if (key == 0) { return; }
	else if (key == 1) {
		cout << "\n--------------------\n\n1.�-�\n2.�-�\n0.�����\n\n--------------------\n->";
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
		cout << "1.�-�\n2.�-�\n0.�����\n->";
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
		cout << "1.�� �����������\n2.�� ��������\n0.�����\n->";
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

		cout << "1.�� �����������\n2.�� ��������\n0.�����\n->";
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
	cout << "������� ����� ������ ��������: ";
	n = input();
	cin.ignore();
	string art, brand, color, type;
	int size, count;
	double price;
	cout << endl;
	for (int i = 0; i < n; i++) {
		/*
		* �������, �������, ������, ���������,������, �����, ��������, ����
		*/
		cout << "���: "; do { getline(cin, type); } while (!isValidName(type));
		cout << "�����: "; do { getline(cin, brand); } while (!isValidName(brand));
		cout << "����: "; do { getline(cin, color); } while (!isValidName(color));
		cout << "������� : "; do {
			getline(cin, art);
			if (!isValidName(art)) {
				cout << "������� ���-������\n";
			}
			else if (art != "�" && art != "M" && art != "�" && art != "�")
			{
				cout << "������ �� ����� ���-�� ��, ���������� ���:\n";
				cout << "� - �������, � - �������, � - �������\n";
			}
		} while (!isValidName(art) || art != "�" && art != "M" && art != "�" && art != "�");
		cout << "������: "; do {
			size = input();
			if (size < 42 || size > 56)
				cout << "���������, ���������� ������ ������ ������\n";
			else if (size % 2 != 0)
				cout << "������ ������ ���� ������ 2\n";
		} while (size < 42 || size > 56 || size % 2 != 0);
		cout << "����: "; do {
			price = dinput(); 
			if (price == 0)
				cout << "���� ������ ���� ���� ����\n";
			else if (price > 50000)
				cout << "����������, ������� ���� ��������\n";
		} while (price > 50000 || price == 0);
		cout << "����������: "; do {
			count = input();
			if (count == 0)
				cout << "������ �������� 0��.\n";
			else if (count > 5000)
				cout << "����������, ������� ������� ���������� (�� ���� ��������� �� ����� 5000�� �� ������)\n";
		} while (count > 5000 || count ==0);
		cin.ignore();
		if (!ADD()) {
			continue;
		}
		Clothes newClothes(type, brand, art, size, color, price, count);
		ClothesVector.push_back(newClothes);
		cout << "������� ���������" << endl;
	}

}
void Admin::deleteClothes() {
	cout << "\n������� id ����\n";
	int inputID = input();
	cin.ignore();
	if (isID(inputID)) {
		auto curr = find_if(ClothesVector.begin(), ClothesVector.end(), [inputID](Clothes& c) {
			return c.getID() == inputID;
			});
		ClothesVector.erase(curr);
	}
	else {
		cout << "���� �� �������\n";
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

//            ������ startInteraction
vector<Clothes> Client::startInteraction() {
	int key;
	while (true) {
		cout << "\n1.�������� ����� ������������n\n2. �� ������������� �������\n0. �����\n";
		key = input();

		if (key == 0) {
			return ClothesVector;
		}

		else if (key == 1) {
			//����� ���� �����
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
			cout << "\n----------------  ����  ----------------\n\n";
			cout << "1.�������� ����    4.�������������\n\n";
			cout << "2.�������� ������  5.�������\n\n";
			cout << "3.�����            6.����������\n\n";
			cout << "0.�����            7.������� �����\\������";
			cout << "\n\n--------------------------------------";
			cout << "\n->";
			key = input();
			system("cls");
			if (key > 7) {
				cout << "������ ������ ���� ���\n";
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
			cout << "������� id ����\n";
			cin >> $inputID;
			$input = true;
			int id = checkInput($input, $inputID);
			if ($input) {
				if (isID(id)) {
					editClothes(id);
				}
				else {
					cout << "���� �� �������\n";
				}
			}
		}*/
		/*else if (key == 6) {
			ClothesVector.sort(SortClothes());
			cout << "������ ������������\n";
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
		cout << "������������ ����!\n";
	}
}
void Admin::editLogPass() {
	int key;

	/**/
	do {
		cout << "\n1. ������� ����� � ������\n2. ������� �����\n3. ������� ������\n0. �����";
		key = input();
		if (key > 3 || key < 0) {
			cout << "������ ������ ���� ���\n";
		}
		system("cls");
	} while (key > 3 || key < 0);

	if (key == 1) {
		cout << "\n������� �����\n";
		cin >> this->AdminLog;
		cout << "\n������� ������\n";
		cin >> this->AdminLog;
	}
	else if (key == 2) {
		cout << "\n������� �����\n";
		cin >> this->AdminLog;
	}
	else if (key == 3) {
		cout << "\n������� ������\n";
		cin >> this->AdminLog;
	}
	else if (key == 0) {
		return;
	}
}

// ���������
ostream& operator << (ostream& os, Client& c)
{
	return os << c.login << " " << c.password << endl;
}
istream& operator>> (istream& is, Client& c) {
	return is >> c.login >> c.password;
}
