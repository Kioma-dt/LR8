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

    while (!exit){
        std::cout << "\n-----------------------------------\n";
        std::cout << "Выберите действие:\n";
        std::cout << "1 - показать информацию\n";
        std::cout << "2 - добавить звонок\n";
        std::cout << "3 - удалить звонок\n";
        std::cout << "4 - изменить информацию о звонке\n";
        std::cout << "5 - вывести по каждому городу общее время разговора и сумму\n";
        std::cout << "6 - выйти\n";
        int input;
        input = CheckUnsigned();
        switch (input){
        case 1:
            ShowInformation(call, size);
            break;
        case 2:
            call = AddCall(call, &size, cities, codes, n_cities, random_numbers);
            break;
        case 3:
            call = ChooseForDelete(call, &size, cities, codes, n_cities);
            break;
        case 4:
            call = ChooseForChange(call, size, cities, codes, n_cities);
            break;
        case 5:
            OutputCities(call, size, cities, codes, n_cities);
            break;
        case 6:
            exit = true;
            break;
        default:
            std::cout << "Неверный номер!\n";
        }
    }

    delete[] call;
    delete[] codes;
    delete[] cities;
}