#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include "Clothes.h"


class User {
protected:
	vector<Clothes> ClothesVector;
	void showClothes(vector<Clothes>);
	virtual void startInteraction()=0;
};


class Client : public User {
protected:
	string login, password;
public:
	Client();
	Client(string , string, vector<Clothes>);
	Client(vector<Clothes>);
	string getLogin();
	string getPass();
	void startInteraction();
	friend ostream& operator<< (ostream& , Client&);
	friend istream& operator>> (istream& , Client&);
};
class Admin : public User {
private:
	string AdminLog = "admin";
	string AdminPass = "admin";
public:
	string getPass();
	string getLog();
	Admin(vector<Clothes>);
	void setList(vector<Clothes> );
	bool isDataCorrect(string , string );
	void startInteraction();
private:
	int checkInput(bool& , string );

	void addClothes();
	//void deleteClothes(int );

	bool isID(int);

	void editLogPass();
};

vector <Client>userFromFile();
void saveUsers(vector<Client>);
bool checkUniq(string , vector<Client> );