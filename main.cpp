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

//int ClothesClass::key;

int entry(vector<Client>);
int authentication(string, string,vector<Client>);
bool isValidName(string);
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    vector<Clothes> Clothesvector = clothesFromFile();
    vector<Client>Clientvector = userFromFile();
    int key;
    bool menu = true;
    int access = entry(Clientvector);
    if (access == 9) {
        Exit(Clothesvector, Clientvector);
    }
    while (menu) {
        if (access == 1) {
            Admin admin(Clothesvector);
            admin.startInteraction();
            access = entry(Clientvector);
            if (access == 9) {
                Exit(Clothesvector, Clientvector);
            }
        }
        else if (access == 2) {
            Client client(Clothesvector);
            client.startInteraction();
            access = entry(Clientvector);
            if (access == 9) {
                Exit(Clothesvector, Clientvector);
            }
        }//user
        else if (access == 3) {
            cout << "�������: ";
            int regChoice = input();
            system("cls");
            if (regChoice == 1)
            {
                bool flag;
                string login, pass;
                cout << "----- ����������� -----" << endl;
                cout << "������� �����: ";
                cin >> login;
                flag = checkUniq(login, Clientvector);
                /*if (flag == false)
                {
                    cout << "������� ������: ";
                    cin >> pass;
                    flag = NEW();
                    if (flag == false) break;
                    Client c(login, pass);
                    Clientvector.push_back(c);
                    access = entry(Clothesvector, Clientvector);
                }*/
                if (flag == false)
                {
                    cout << "������� ������: ";
                    cin >> pass;
                    flag = NEW();
                    if (flag == false) break;
                    Client c(login, pass,Clothesvector);
                    Clientvector.push_back(c);
                    c.startInteraction();
                    access = entry(Clientvector);
                    if (access == 9) {
                        Exit(Clothesvector, Clientvector);
                    }
                }
                else cout << "������������ ��� ������� \"" << login << "\" ��� ����!" << endl;
            }
            else if (regChoice == 2) {
                access = entry(Clientvector);
                if (access == 9) {
                    Exit(Clothesvector, Clientvector);
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
    cout << "������� \"exit\", ���� ������ �����\n";
    cout << "�����:\t";
    cin >> login;
    if (login == "exit") return 9;
    cout << "������:\t";
    cin >> pass;
    if (pass == "exit") return 9;
    access = authentication(login, pass,Clientvector);
    return access;
}
int authentication(string login, string password, vector<Client>ClientVector) {
    ifstream file("admin.txt");
    string alog, apass;
    //vector<Client> ClientVector = userFromFile();
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
        cout << "\n����� ��� ������ ������ �����������!\n��� ������ ������������ �� ����������\n������ ������������������ ?\n1 - ��\n2 - ���\n";
        return 3;
    }
}
