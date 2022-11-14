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
	void findClothes(vector<Clothes>);
	virtual vector <Clothes>startInteraction()=0;
	bool checkEmpty(vector<Clothes>);
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
	vector <Clothes> startInteraction();
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
	vector <Clothes>startInteraction();
private:
	int checkInput(bool& , string );

	void addClothes();
	void deleteClothes(vector<Clothes>&);

	bool isID(int);

	void editLogPass();
};

vector <Client>userFromFile();
void saveUsers(vector<Client>);
bool checkUniq(string , vector<Client> );