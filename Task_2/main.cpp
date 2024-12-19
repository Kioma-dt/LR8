#include <iostream>
#include <string>
#include "Functions.h"

int main(){
    bool exit = false;
    bool random_numbers = false;
    Call *call;
    int size = 0;
    int *codes;
    std::string *cities;
    int n_cities = 0;

    std::cout << "Введите количество городов, которые вы хотите использовать: ";
    n_cities = CheckUnsigned();
    cities = new std::string[n_cities];
    codes = new int[n_cities];
    EnterCities(cities, codes, n_cities);

    std::cout << "Генерировать рандомные телефонные номера?(0,1): ";
    std::cin >> random_numbers;
    std::cout << "\n---------------------------------------------\n";
    call = EnterWithSize(&size, cities, codes, n_cities, random_numbers);

    for (int i = 0; i < size;i++){
        std::cout << '\n' << i + 1 << " звонок\n";
        OutputCall(call[i]);
    }
}