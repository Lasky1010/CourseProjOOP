#include <windows.h>
#include <conio.h>
#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include "Clothes.h"
#include "Client.h"
#include"validation.h"
using namespace std;

void Exit(vector<Clothes> , vector<Client> );
int input();


int entry(vector<Client>);
int authentication(string, string,vector<Client>);
bool isValidName(string);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    vector<Clothes> ClothesVector = clothesFromFile();
    vector<Client>ClientVector = userFromFile();
    int key;
    int access = entry(ClientVector);
    if (access == 9) {
        Exit(ClothesVector, ClientVector);
    }
    while (true) {
        if (access == 1) {
            Admin admin(ClothesVector);
            admin.startInteraction();
            access = entry(ClientVector);
            if (access == 9) {
                Exit(ClothesVector, ClientVector);
            }
        }
        else if (access == 2) {
            Client client(ClothesVector);
            client.startInteraction();
            access = entry(ClientVector);
            if (access == 9) {
                Exit(ClothesVector, ClientVector);
            }
        }
        else if (access == 3) {
            cout << "Введите: ";
            int regChoice = input();
            system("cls");
            if (regChoice == 1)
            {
                bool flag;
                string login, pass;
                cout << "----- Регистрация -----" << endl;
                cout << "Введите логин: ";
                cin >> login;
                flag = checkUniq(login, ClientVector);
                /*if (flag == false)
                {
                    cout << "Введите пароль: ";
                    cin >> pass;
                    flag = NEW();
                    if (flag == false) break;
                    Client c(login, pass);
                    Clientvector.push_back(c);
                    access = entry(Clothesvector, Clientvector);
                }*/
                if (flag == false)
                {
                    cout << "Введите пароль: ";
                    cin >> pass;
                    flag = NEW();
                    if (flag == false) break;
                    Client c(login, pass,ClothesVector);
                    ClientVector.push_back(c);
                    c.startInteraction();
                    access = entry(ClientVector);
                    if (access == 9) {
                        Exit(ClothesVector, ClientVector);
                    }
                }
                else cout << "Пользователь под логином \"" << login << "\" уже есть!" << endl;
            }
            else if (regChoice == 2) {
                access = entry(ClientVector);
                if (access == 9) {
                    Exit(ClothesVector, ClientVector);
                }
            }
        }
    }
    return 0;
}

void Exit(vector<Clothes> Clothesvector, vector<Client> Clientvector) {
    saveClothes(Clothesvector);
    saveUsers(Clientvector);
    exit(0);
}



int entry(vector<Client> Clientvector) {
    int access = 0;
    string login, pass;
    cout << "Введите \"exit\", если хотите выйти\n";
    cout << "Логин:\t";
    cin >> login;
    if (login == "exit") return 9;
    cout << "Пароль:\t";
    cin >> pass;
    if (pass == "exit") return 9;
    access = authentication(login, pass,Clientvector);
    return access;
}
int authentication(string login, string password, vector<Client>ClientVector) {
    ifstream file("admin.txt");
    string alog, apass;
    if (file.is_open()) {
        getline(file, alog);
        getline(file, apass);
        file.close();
    }
    if (login == alog && password == apass) {
        return 1;
    }
    else if (ClientVector.size() != 0) {
        for (int i = 0; i < ClientVector.size(); i++) {
            if (ClientVector[i].getLogin() == login && ClientVector[i].getPass() == password) 
            {
                return 2;
            }
        }
        cout << "\nЛогин или пароль введен неправильно!\nИли такого пользователя не существует\nХотите зарегестрироваться ?\n1 - Да\n2 - Нет\n";
        return 3;
    }
}

