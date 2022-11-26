#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include "Clothes.h"

class User {
protected:
	vector <CL> lower;
	vector<Clothes> ClothesVector;
	virtual vector <Clothes>startInteraction() = 0;
	void showClothes();
	void findClothes();
	void sortClothes();
	bool checkEmpty();
	void filterClothes();
	bool isID(int);
};



class Client : public User {
protected:
	string login, password;
	vector<Clothes> cart;
	double priceCart = 0;
	class Card {
	public:
		string cardNumber;
		int month, year, cvv;
	};
	Card card;
public:
	Client();
	Client(string , string, vector<Clothes>);
	Client(vector<Clothes>);
	string getLogin();
	string getPass();
	void menuCart();
	void addCart();
	bool checkCart();
	void showCart();
	void deleteCart();
	void buy();
	void enterCard();
	void printBill(time_t);
	void writeReport(Clothes,time_t);
	bool isValidCard(string);
	vector <Clothes> startInteraction();
	friend ostream& operator<< (ostream& , Client&);
	friend istream& operator>> (istream& , Client&);
};
class Admin : public User {
private:
	string AdminLog;
	string AdminPass;
public:
	Admin();
	string getPass();
	string getLog();
	void setAdminLogPass();
	void saveAdminLogPass();
	Admin(vector<Clothes>);
	void setList(vector<Clothes> );
	bool isDataCorrect(string , string );
	vector <Clothes>startInteraction();
private:
	int checkInput(bool& , string );

	void addClothes();
	void deleteClothes();
	void editLogPass();
};



vector <Client>userFromFile();
void saveUsers(vector<Client>);
bool checkUniq(string , vector<Client>,Admin& );
bool isValidName(string);
bool isValidLogin(string);
bool isValidPass(string);