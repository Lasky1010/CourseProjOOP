#pragma once
#include <string>
#include <iostream>
#include <ctime>
#include <iomanip>
#include<vector>
#include <windows.h>
using namespace std;
class CL {
public:
	string TYPE, BRAND, COLOR;
};
char to_lowercase(char c);
void to_lower(vector<CL>& lower);

int input();
double dinput();


class Clothes {
protected:
	int id, size;
	string art, brand, color, type;
	double price;

	int createID();
public:
	Clothes(string , string , string , int , string , double);
	Clothes();
	void setType(string );
	string getType();
	void setID(int );
	int getID();
	void setBrand(string d);
	string getBrand();
	void setSize(int );
	int getSize();
	void setColor(string );
	string getColor();
	void setPrice(double );
	double getPrice();
	void setArt(string );
	string getArt();
	friend ostream& operator<< (ostream&, Clothes&);
	friend istream& operator>> (istream&, Clothes&);
};

vector<Clothes> clothesFromFile();
void saveClothes(vector<Clothes>);
