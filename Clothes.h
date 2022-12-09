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
bool ADD();
bool BUY();
bool DEL();
bool EDIT();

class Clothes {
protected:
	int id, size,count;
	string art, brand, color, type;
	double price;

	int createID();
public:
	
	Clothes(string , string , string , int , string , double,int);
	Clothes(int,string, string, string, int, string, double, int);
	Clothes(const Clothes&);
	Clothes();
	void setCount(int);
	int getCount();
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

vector<Clothes> clothesFromFile(vector<CL>&);
void saveClothes(vector<Clothes>);
