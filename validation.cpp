#pragma once
#include"validation.h"

bool NEW() {
    std::cout << "������� ��� ������ �������� ?\n";
    std::cout << "1. ��\n2. ���\n->";
    int n;
    std::cin >> n;
    system("cls");
    if (n == 1) return true;
    return false;
}

bool DEL() {
    std::cout << "������� ��� ������ ������� ?\n";
    std::cout << "1. ��\n2. ���\n->";
    int n;
    std::cin >> n;
    system("cls");
    if (n == 1) return true;
    return false;
}
bool EDIT() {
    std::cout << "������� ��� ������ ������������� ?\n";
    std::cout << "1. ��\n2. ���\n->";
    int n;
    std::cin >> n;
    system("cls");
    if (n == 1) return true;
    return false;
}