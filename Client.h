#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include "Clothes.h"

class User {
protected:
	vector <CL>lower;
	vector<Clothes> ClothesVector;
	virtual vector <Clothes>startInteraction() = 0;
	void showClothes();
	void findClothes();
	void sortClothes();
	void editClothes();
	bool checkEmpty();
	void filterClothes();
	bool isID(int);
};



class Client : public User {
private:
	template<typename T>
	class Card {
	public:
		T cardNumber;
		int month, year, cvv;
		
	};
	Card<string> card;
	string login, password;
	vector<Clothes> cart;
	double priceCart = 0;

public:
	static int count_reg_users;
	static int getRegUsers();
	Client();
	Client(string , string, vector<Clothes>,vector<CL>);
	Client(vector<Clothes>);
	string getLogin();
	template <typename T>
	string getPass();
	void menuCart();
	void addCart();
	bool checkCart();
	void showCart();
	void deleteCart();
	void buy();
	void enterCard();
	void printBill(time_t,string);
	void writeReport(Clothes);
	void writeReport2( time_t, string);
	bool isValidCard(string);
	vector <Clothes> startInteraction();
	friend ostream& operator<< (ostream& , Client&);
	friend istream& operator>> (istream& , Client&);
};
class Admin : public User {
private:
	string AdminLog;
	string AdminPass;
	int checkInput(bool&, string);

	void saveAdminLogPass();
	void addClothes();
	void deleteClothes();
	void editLogPass();
public:
	Admin();
	void setVectors(vector<Clothes>,vector<CL>);
	Admin(vector<Clothes>,vector<CL>);
	string getPass();
	string getLog();
	friend void setAdminLogPass(unique_ptr<Admin>&);
	void setList(vector<Clothes> );
	bool isDataCorrect(string, string);
	vector <Clothes>startInteraction();
	
};



vector <Client>userFromFile();
void saveUsers(vector<Client>);
bool checkUniq(string , vector<Client>,unique_ptr<Admin>& );
bool isValidString(string);
bool isValidLogin(string);
bool isValidPass(string);