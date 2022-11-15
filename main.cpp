#include <windows.h>
#include <conio.h>
#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include "Clothes.h"
#include "Client.h"
using namespace std;

void Exit(vector<Clothes> , vector<Client> );
int input();


int entry(vector<Client>,Admin&);
int authentication(string, string,vector<Client>,Admin&);
bool isValidName(string);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    vector<Clothes> ClothesVector = clothesFromFile();
    vector<Client>ClientVector = userFromFile();
    int key;
    Admin a;
    int access = entry(ClientVector,a);
    if (access == 9) {
        Exit(ClothesVector, ClientVector);
    }
    while (true) {
        if (access == 1) {
            Admin admin(ClothesVector);
            ClothesVector=admin.startInteraction();
            access = entry(ClientVector,a);
            if (access == 9) {
                Exit(ClothesVector, ClientVector);
            }
        }
        else if (access == 2) {
            Client client(ClothesVector);
            ClothesVector=client.startInteraction();
            access = entry(ClientVector,a);
            if (access == 9) {
                Exit(ClothesVector, ClientVector);
            }
        }
        else if (access == 3) {
            int regChoice;
            do {
                cout << "\nЛогин или пароль введен неправильно!";
                cout<<"\nИли такого пользователя не существует\nХотите зарегестрироваться ? \n1.Да\n2.Нет\n->";
                regChoice = input();
                system("cls");
                if (regChoice > 2) {
                    cout << "Пожалуйста, введите либо 1, либо 2\n->";
                }
            } while (regChoice > 2);
            if (regChoice == 1)
            {
                string login, pass;
                bool flag;
                do{
                    cout << "------ Регистрация ------" << endl;
                    cout << "Введите логин: ";
                    cin >> login;
                    flag = checkUniq(login, ClientVector, a);
                    if (flag == true) {
                        cout << "Пользователь под логином \"" << login << "\" уже есть!" << endl;
                    }
                } while (flag ==true);
                cout << "Введите пароль: ";
                cin >> pass;
                Client c(login, pass,ClothesVector);
                ClientVector.push_back(c);
                ClothesVector=c.startInteraction();
                access = entry(ClientVector,a);
                if (access == 9) {
                    Exit(ClothesVector, ClientVector);
                }
            }
            else if (regChoice == 2) {
                access = entry(ClientVector,a);
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



int entry(vector<Client> Clientvector,Admin &a) {
    a.setAdminLogPass();
    int access = 0;
    string login, pass;
    cout << "Введите \"exit\", если хотите выйти\n";
    cout << "Логин:\t";
    cin >> login;
    if (login == "exit") return 9;
    cout << "Пароль:\t";
    cin >> pass;
    if (pass == "exit") return 9;
    access = authentication(login, pass,Clientvector,a);
    return access;
}
int authentication(string login, string password, vector<Client>ClientVector,Admin&a) {
    if (login ==a.getLog() && password == a.getPass()) {
        return 1;
    }
    else {
        for (int i = 0; i < ClientVector.size(); i++) {
            if (ClientVector[i].getLogin() == login && ClientVector[i].getPass() == password) 
            {
                return 2;
            }
        }
        return 3;
    }
}

