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
		cout << "\n1.�������� ����� ������������n\n2. �� ������������� �������\n0. �����\n";
		key = input();

		if (key == 0) {
			return;
		}

		else if (key == 1) {
			//����� ���� �����
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
			cout<< "\n----------------  ����  ----------------\n\n";
			cout<<"1.�������� ����    4.�������������\n\n";
			cout<<"2.�������� ������  5.�������\n\n";
			cout<<"3.�����            6.����������\n\n";
			cout<<"0.�����            7.������� �����\\������";
			cout << "\n--------------------------------------";
			cout<<"\n->";
			key = input();
			if (key > 7 || key < 0) {
				cout << "������ ������ ���� ���\n";
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
				cout << "������:\n1 - �� ������\n2 - �� ����\n3 - �� �����\n4 - �� ��������\n5 - �� �������\n9 - �����\n";
				choice = input();
				cin.ignore();
				system("cls");
				if (choice > 4 && choice != 9) { cout << "�������� �����\n"; }
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
				cout << "������� �����: ";
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
						cout << ClothesVector[i];
					}
				}

				if (find == false) {
					cout << "�� �������\n";
				}
			}
			else if (choice == 3) {
				string color;
				cout << "������� ����: ";
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
					cout << "�� �������\n";
				}

			}
			else if (choice == 4) {
				cout << "1. �\n2. �\n3. �\n0. �����";
				int ch = input();
				cin.ignore();
				string art = "";
				if (ch == 0) { break; }
				else if (ch == 1) { art = "�"; }
				else if (ch == 2) { art = "�"; }
				else if (ch == 3) { art = "�"; }
				bool find = false;
				for (int i = 0; i < ClothesVector.size(); i++) {
					if (ClothesVector[i].getArt() == art) {
						find = true;
						cout << ClothesVector[i];
					}
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
				for (int i = 0; i < ClothesVector.size(); i++)
					if (ClothesVector[i].getSize() == size) {
						cout << ClothesVector[i];
						find = true;
					}
				if (find == false) {
					cout << "�� �������\n";
				}
			}

		}
		else if (key == 5) {
			cout << "������� id ����\n";
			cin >> $inputID;
			cin.ignore();
			$input = true;
			int id = checkInput($input, $inputID);
			if ($input) {
				if (isID(id)) {
					//deleteClothes(id);
				}
				else {
					cout << "���� �� �������\n";
				}
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

int Admin::checkInput(bool& isInputCorrect, string response) {
	try {
		return stoi(response);
	}
	catch (...) {
		isInputCorrect = false;
		cout << "������������ ����!\n";
	}
}


void Admin::addClothes() {
	int n;
	cout << "������� ����� ������ ��������: ";
	cin >> n;
	cin.ignore();
	string art, brand, color, type;
	int size;
	double price;
	cout << endl;
	for (int i = 0; i < n; i++) {

		cout << "���: "; getline(cin, type);
		cout << "�����: "; getline(cin, brand);
		cout << "����: "; getline(cin, color);
		cout << "�������: "; getline(cin, art);
		cout << "������: "; size = input();
		cout << "����: "; price = dinput();
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


