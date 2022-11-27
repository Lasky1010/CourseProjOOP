#pragma once

#include <string>
#include <iostream>
#include <windows.h>
#include <ctime>
#include"Clothes.h"
#include <iomanip>
#include<vector>
#include<conio.h>
#include<fstream>

using namespace std;
//               Функции
void saveClothes(vector<Clothes> ClothesVector) {
	ofstream of("Clothes.txt");
	for (auto iter :ClothesVector) {
		
		of << iter.getID() << "\n" << iter.getType() << "\n" << iter.getBrand() <<
			"\n" << iter.getArt() << "\n" <<iter.getSize() << "\n"
			<< iter.getColor() << "\n" << iter.getPrice()<<"\n"<<iter.getCount()<<"\n";
	}
	of.close();
}
vector<Clothes> clothesFromFile() {
	vector<Clothes> ClothesVector;
	ifstream in("Clothes.txt");
	if (in.is_open())
	{
		if (in.peek() == EOF)
		{
			cout << "Файл пуст!" << endl;
			in.close();
			return ClothesVector;
		}
		int i = 1;
		int id,count, size;
		string art, type, brand,color;
		double price;
		while (true) {
			in >> id;
			if (in.eof()) break;
			in >> type;
			in >> brand;
			in >> art;
			in >> size;
			in >> color;
			in >> price;
			in >> count;
			Clothes c(id,type,brand,art,size,color,price,count);
			ClothesVector.push_back(c);
		}
	}
	else
	{
		cout << "Ошибка при открытии файла для чтения!" << endl;
	}
	in.close();
	return ClothesVector;
}
char to_lowercase(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'А' && c <= 'Я'))
	{
		return c + 32;
	}

	return c;
}
void to_lower(vector<CL>& lower) {
	for (int i = 0; i < lower.size(); i++) {
		for (char& c : lower[i].TYPE) {
			c = to_lowercase(c);
		}
		for (char& c : lower[i].BRAND) {
			c = to_lowercase(c);
		}
		for (char& c : lower[i].COLOR) {
			c = to_lowercase(c);
		}
	}
}
int input()
{
	int n;
	while (true) {
		try {
			if (!(cin >> n))
			{
				throw runtime_error("Вы ввели не число\n");
			}
			else if (n < 0) {
				throw runtime_error("Вы ввели отрицательное число\n");
			}
			return n;
		}
		catch (runtime_error& err) {
			cout << err.what();
			cin.clear();
			while (cin.get() != '\n');
		}
	}
}
double dinput()
{
	double n;
	while (true) {
		try {
			if (!(cin >> n))
			{
				throw runtime_error("Вы ввели не число\n");
			}
			else if (n < 0) {
				throw runtime_error("Вы ввели отрицательное число\n");
			}
			return n;
		}
		catch (runtime_error& err) {
			cout << err.what();
			cin.clear();
			while (cin.get() != '\n');
		}
	}
}
bool BUY() {
	char n; 
	do {
		cout << "\nУверены что хотите купить ?\n";
		cout << "     1.Да\t2.Нет\n->";
		n = _getch();
		system("cls");
	} while (n != '1' && n != '2');
	if (n == '1') return true;
	return false;
}
bool ADD() {
	char n;
	do {
		cout << "\nУверены что хотите добавить ?\n";
		cout << "     1.Да\t2.Нет\n->";
		n = _getch();
		system("cls");
	} while (n != '1' && n != '2');
	if (n == '1') return true;
	return false;
}
bool DEL() {
	char n;
	do {
		cout << "\nУверены что хотите удалить ?\n";
		cout << "     1.Да\t2.Нет\n->";
		n = _getch();
		system("cls");
	} while (n != '1' && n != '2');
	if (n == '1') return true;
	return false;
}
bool EDIT() {
	char n;
	do {
		cout << "\nУверены что хотите изменить ?\n";
		cout << "     1.Да\t2.Нет\n->";
		n = _getch();
		system("cls");
	} while (n != '1' && n != '2');
	if (n == '1') return true;
	return false;
}

//              Clothes
Clothes::Clothes(int id, string type, string brand, string art, int size, string color, double price, int count):id(id), type(type), brand(brand), art(art), size(size), color(color), price(price), count(count) {}
int Clothes::createID() {
	srand(unsigned(time(0)));
	int randomVariable = rand() % 100;
	int randomVariable2 = rand() % 100 - rand() % 9;
	string stringID = to_string(randomVariable) + to_string(randomVariable2);
	int createdID = stoi(stringID);
	return createdID;
}
void Clothes::setCount(int count) {
	this->count = count;
}
int Clothes::getCount() {
	return this->count;
}
Clothes::Clothes(string type, string brand, string art, int size, string color, double price,int count) :type(type), brand(brand), art(art), size(size), color(color), price(price) ,count(count) { this->id = createID(); }
Clothes :: Clothes(){
	id = 0;
	size = 0;
	price = 0;
	type = "";
	brand = "";
	color = "";
	art = "";
	count = 0;
}
Clothes::Clothes(const Clothes&obj) {
	this->art = obj.art;
	this->size = obj.size;
	this->brand = obj.brand;
	this->color = obj.color;
	this->count = obj.count;
	this->price = obj.price;
	this->id = obj.id;
	this->type = obj.type;
}
void Clothes::setType(string type) {
	this->type = type;
}
string Clothes::getType() {
	return type;
}
void Clothes::setID(int id) {
	this->id = id;
}
int Clothes::getID() {
	return id;
}
void Clothes::setBrand(string Brand) {
	brand = Brand;
}
string Clothes::getBrand() {
	return brand;
}
void Clothes::setSize(int size) {
	this->size = size;
}
int Clothes::getSize() {
	return size;
}
void Clothes::setColor(string color) {
	this->color = color;
}
string Clothes::getColor() {
	return color;
}
void Clothes::setPrice(double price) {
	this->price = price;
}
double Clothes::getPrice() {
	return price;
}
void Clothes::setArt(string Art) {
	art = Art;
}
string Clothes::getArt() {
	return art;
}



// Перегрузки
ostream& operator << (ostream& os, Clothes& C)
{
	return os << C.id << "\n" << C.type << "\n" << C.brand <<
		"\n" << C.art << "\n" << C.size << "\n"
		<< C.color << "\n" << C.price << "$\n" << C.count << "шт";
}

istream& operator >> (istream& is, Clothes& C)
{
	return is >> C.id >> C.type >> C.brand >>
		C.art >> C.size >>
		C.color >> C.price>>C.count;
}
