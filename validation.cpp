#pragma once
#include"validation.h"

bool NEW() {
    std::cout << "Уверены что хотите добавить ?\n";
    std::cout << "1. Да\n2. Нет\n->";
    int n;
    std::cin >> n;
    system("cls");
    if (n == 1) return true;
    return false;
}

bool DEL() {
    std::cout << "Уверены что хотите удалить ?\n";
    std::cout << "1. Да\n2. Нет\n->";
    int n;
    std::cin >> n;
    system("cls");
    if (n == 1) return true;
    return false;
}
bool EDIT() {
    std::cout << "Уверены что хотите редактировать ?\n";
    std::cout << "1. Да\n2. Нет\n->";
    int n;
    std::cin >> n;
    system("cls");
    if (n == 1) return true;
    return false;
}