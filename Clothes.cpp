#pragma once

#include <string>
#include <iostream>
#include <windows.h>
#include <ctime>
#include"Clothes.h"
#include <iomanip>
#include<vector>
#include<fstream>

using namespace std;
bool isValidName();

void saveClothes(vector<Clothes> ClothesVector) {
	ofstream of("Clothes.txt");
	for (auto iter :ClothesVector) {
		
		of << "№" << iter.getID() << " " << iter.getType() << " " << iter.getBrand() <<
			" " << iter.getArt() << " " <<iter.getSize() << " "
			<< iter.getColor() << " " << iter.getPrice();
	}
	of.close();
}
vector<Clothes> clothesFromFile() {
	vector<Clothes> ClothesVector;
	Clothes c;
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
		while (!in.eof())
		{
			in >> c;
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

int Clothes::createID() {
	srand(unsigned(time(0)));
	int randomVariable = rand() % 100;
	int randomVariable2 = rand() % 100 - rand() % 9;
	string stringID = to_string(randomVariable) + to_string(randomVariable2);
	int createdID = stoi(stringID);
	return createdID;
}


Clothes::Clothes(string type, string brand, string art, int size, string color, double price) :type(type), brand(brand), art(art), size(size), color(color), price(price) { this->id = createID(); }
Clothes :: Clothes(){
	id = 0;
	size = 0;
	price = 0;
	type = "";
	brand = "";
	color = "";
	art = "";
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


ostream& operator << (ostream& os, Clothes& C)
{
	return os << "№" << C.id << "\n" << C.type << "\n" << C.brand <<
		"\n" << C.art << "\n" << C.size << "\n"
		<< C.color << "\n" << C.price << "$";
}

istream& operator >> (istream& is, Clothes& C)
{
	return is >> C.id >> C.type >> C.brand >>
		C.art >> C.size >>
		C.color >> C.price;
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
		if (!(cin >> n))
		{
			cout << "Вы ввели не число\n";
		}
		else if (n < 0) {
			cout << "Вы ввели отрицательное число\n";
		}
		return n;
	}
}
double dinput()
{
	double n;
	while (true) {
		if (!(cin >> n))
		{
			cout << "Вы ввели не число\n";
		}
		else if (n < 0) {
			cout << "Вы ввели отрицательное число\n";
		}
		return n;
	}
}
bool isValidName(string name) {
	/*if (name == "") return false;
	else */if (name == string(name.length(), ' ')) return false;
	bool isa = true;
	for (int i = 0; i < name.size(); i++) {
		if ( name[i] == '\n' || name[i] == '\0')
			isa = false;
		else {
			isa = true;
		}
	}
	return isa;
}