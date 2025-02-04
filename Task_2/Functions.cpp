#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include "Struct.h"

Call *AddSpace(Call *call, int *size){
    Call *new_call = new Call [*size + 1];
    for (int i = 0; i < *size; i++) {
        new_call[i] = call[i];
    }
    delete[] call;
    (*size)++;

    return new_call;
}

Call *DeleteSpace(Call *call, int *size){
    Call *new_call = new Call[*size - 1];
    for (int i = 0; i < *size - 1; i++) {
        new_call[i] = call[i];
    }
    delete[] call;
    (*size)--;

    return new_call;
}

int NameToCode(std::string name, std::string * cities, int * codes, int n_cities){
    for (int i = 0; i < n_cities;i++){
        if (name == cities[i]){
            return codes[i];
        }
    }

    return -1;
}

std::string CodeToName(int code, std::string * cities, int * codes, int n_cities){
    for (int i = 0; i < n_cities;i++){
        if (code == codes[i]){
            return cities[i];
        }
    }

    return "ERROR";
}

int CheckUnsigned() {
    int input;
	char next;

	while (true) {
		if (std::cin >> input && input >= 0) {
			std::cin.get(next);
			while (next == ' ') {
				std::cin.get(next);
			}

			if (next == '\n') {
				break;
			}
		}

		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Неверный формат ввода! Необходими ввести целое неотрицательное число!\n";
	}

	return input;
}

double CheckDouble() {
    double input;
	char next;

	while (true) {
		if (std::cin >> input && input >= 0) {
			std::cin.get(next);
			while (next == ' ') {
				std::cin.get(next);
			}

			if (next == '\n') {
				break;
			}
		}

		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Неверный формат ввода! Необходими ввести неотрицательное число!\n";
	}

	return input;
}

int CheckNumberOfArray(int size) {
    int input;
    while (1){
        input = CheckUnsigned();
        if (input <= size && input != 0){
            break;
        }
        std::cout << "Нет звонка с таким номером!\n";
    }

    return input;
}

std::string CheckName(std::string * cities, int n_cities){
    std::string name;
    std::cin >> name;
    bool correct = false;
    while(1) {
        correct = true;
        for (int i = 0; i < n_cities; i++){
            if (name == cities[i]){
                correct = false;
                break;
            }
        }
        if(correct){
            return name;
        }
        std::cout << "Город с таким именем уже есть!\n";
    }
}

int CheckCode(int * codes, int  n_cities){
    int code;
    code = CheckUnsigned();
    bool correct = false;
    while(1) {
        correct = true;
        for (int i = 0; i < n_cities; i++){
            if (code == codes[i]){
                correct = false;
                break;
            }
        }
        if(correct){
            return code;
        }
        std::cout << "Город с таким кодом уже есть!\n";
    }
}

int CheckDate(int type, Call call){
    int date;
    while(1){
        date = CheckUnsigned();
        if (date != 0){
            if (type == 1){
                if (call.month == 2){
                    if (call.year % 4 == 0){
                        if (date <= 28){
                            return date;
                        }
                    }else {
                        if (date <= 29){
                            return date;
                        }
                    }
                }
                else if (call.month == 2 || call.month == 4 || call.month == 6 || call.month == 9 || call.month == 11){
                    if (date <= 30){
                        return date;
                    }
                }
                else {
                    if (date <= 31){
                        return date;
                    }
                }
            }
            if (type == 2){
                if (date <= 12){
                    return date;
                }
            }
            if (type == 3){
                if (date >= 1877){
                    return date;
                }
            }
        }
        std::cout << "Неверный формат даты!\n";
    }
}

bool CheckNameOrCode(){
    int input;
    while(1){
        input = CheckUnsigned();
        if (input == 0){
            return 0;
        }
        else if (input == 1){
            return 1;
        }
        std::cout << "Неверный ответ!\n";
    }
}

City CheckCity(bool hasName, std::string * cities, int * codes, int n_cities){
    City city;
    while (1){
        if (hasName){
            std::cin >> city.name;
            for (int i = 0; i < n_cities;i++){
                if (city.name == cities[i]){
                    return city;
                }
            }
            std::cout << "Нет города с таким именем!\n";
        }
        else{
            city.code = CheckUnsigned();
            for (int i = 0; i < n_cities;i++){
                if (city.code == codes[i]){
                    return city;
                }
            }
            std::cout << "Нет города с таким кодом!\n";
        }
    }
}


int CheckTellNumber(bool from_city, Call call, std::string * cities, int * codes, int n_cities){
    int number;
    while (1){
        number = CheckUnsigned();
        int first_sign = number / pow(10, 8);
        int digits = log10(number) + 1;
        if ((digits == 9) && (first_sign == 8)) {
            break;
        }
        std::cout << "Неверный формат номера!\n";
    }
    if (from_city){
        int city_code;
        if (call.hasName){
            city_code = NameToCode(call.city.name, cities, codes, n_cities);
        }
        else {
            city_code = call.city.code;
        }

        while (1){
            int first_four = number / pow(10, 5) ;
            if (first_four == 8000 + city_code) {
                return number;
            }
            std::cout << "Неверный код города!\n";
            number = CheckUnsigned();
        }
    }

    return number;
}

void EnterCities(std::string * cities, int *  codes, int n_cities){
    for (int i = 0; i < n_cities;i++){
        std::cout << "Введите город: ";
        cities[i] = CheckName(cities, i);
        std::cout << "Введите код(трехзначное целое неотрицателное число): ";
        while(1){
            codes[i] = CheckUnsigned();
            if (codes[i] < 1000 && codes[i] > 99){
                break;
            }
            std::cout << "Код должен быть трехзначным!\n";
        }
    }
}

void EnterCall(Call * call, std::string * cities, int * codes, int n_cities, bool random_numbers){
    std::cout << "Введите год, когда был совершен звонок: ";
    call->year = CheckDate(3, *call);
    std::cout << "Введите месяц, когда был совершен звонок: ";
    call->month = CheckDate(2, *call);
    std::cout << "Введите день, когда был совершен звонок: ";
    call->day = CheckDate(1, *call);
    std::cout << "Ввести название города или его код? (1 - название, 0 - код): ";
    call->hasName = CheckNameOrCode();
    if (call->hasName){
        std::cout << "Введите город, из которого был совершен звонок: ";
        call->city = CheckCity(call->hasName, cities, codes, n_cities);
    }
    else {
        std::cout << "Введите код города, из которого был совершен звонок: ";
        call->city = CheckCity(call->hasName, cities, codes, n_cities);
    }
    std::cout << "Введите время звонка в минутах: ";
    call->time = CheckUnsigned();
    std::cout << "Введите стоимость одной минуты звонка: ";
    call->cost = CheckDouble();
    if (random_numbers){
        if (call->hasName){
            call->number_city = 8 * pow(10, 8) + NameToCode(call->city.name, cities, codes, n_cities) * pow(10, 5) + rand() % 99999;
        }
        else{
            call->number_city = 8 * pow(10, 8) + call->city.code * pow(10, 5) + rand() % 99999;
        }
        call->number_caller = 8 * pow(10, 8) + rand() % 99999999;
    }
    else{
        std::cout << "Номер телефона состоит из 9 цифр, начинается на 8, а затем код города.\n";
        std::cout << "Введите номер телефона в этом городе: ";
        call->number_city = CheckTellNumber(1, *call, cities, codes, n_cities);
        std::cout << "Введите номер телефона абонента: ";
        call->number_caller = CheckTellNumber(0, *call, cities, codes, n_cities);
    }
}

Call *EnterWithSize(int * size, std::string * cities, int * codes, int n_cities, bool random_numbers){
    std::cout << "Введите количество звонков: ";
    *size = CheckUnsigned();
    Call *call = new Call[*size];

    for (int i = 0; i < *size; i++){
        std::cout << i + 1 << " звонок\n";
        EnterCall(call + i, cities, codes, n_cities, random_numbers);
    }

    return call;
}

void OutputCall(Call call){
    std::cout << "Год: ";
    std::cout << call.year;
    std::cout << "\nМесяц: ";
    std::cout << call.month;
    std::cout << "\nДень: ";
    std::cout << call.day;
    if (call.hasName){
        std::cout << "\nГород: ";
        std::cout << call.city.name;
    }
    else{
        std::cout << "\nКод города: ";
        std::cout << call.city.code;
    }
    std::cout << "\nВремя звонка в минутах: ";
    std::cout << call.time;
    std::cout << "\nCтоимость одной минуты звонка: ";
    std::cout << call.cost;
    std::cout << "\nНомер телефона в этом городе: ";
    std::cout << call.number_city;
    std::cout << "\nНомер телефона абонента: ";
    std::cout << call.number_caller;
    std::cout << "\n";
}

void ShowInformation(Call * call, int size){
    if (size == 0){
        std::cout << "Нет звонков!\n";
        return;
    }
    int number;
    std::cout << "Введите номер звонка (0 - показать все звонки): ";
    while (1){
        number = CheckUnsigned();
        if (number <= size){
            break;
        }
        std::cout << "Нет звонка с таким номером!\n";
    }
    if (number == 0){
        for (int i = 0; i < size;i++){
            std::cout << i + 1 << " звонок\n";
            OutputCall(call[i]);
            std::cout << '\n';
        }
    }
    else {
        std::cout << number << " звонок\n";
        OutputCall(call[number - 1]);
        std::cout << '\n';
    }
}

Call *AddCall(Call * call, int * size, std::string * cities, int * codes, int n_cities, bool random_numbers){
    call = AddSpace(call, size);
    
    EnterCall(call + *size - 1, cities, codes, n_cities, random_numbers);

    return call;
}

int FindCall(Call * call, int start, int end, int n_feature, int feature_i, double feature_d, std::string feature_s, std::string * cities, int * codes, int n_cities){
    for (int i = start; i < end;i++){
        std::string city_name;
        int city_code;
        switch(n_feature){
        case 1:
            if (call[i].year == feature_i){
                return i;
            }
            break;
        case 2:
            if (call[i].month == feature_i){
                return i;
            }
            break;
        case 3:
            if (call[i].day == feature_i){
                return i;
            }
            break;
        case 4:
            if (!call[i].hasName){
                city_name = CodeToName(call[i].city.code, cities, codes, n_cities);
            } 
            else {
                city_name = call[i].city.name;
            }
            if (city_name == feature_s){
                return i;
            }
            break;
        case 5:
            if (call[i].hasName){
                city_code = NameToCode(call[i].city.name, cities, codes, n_cities);
            } 
            else {
                city_code = call[i].city.code;
            }
            if (city_code == feature_i){
                return i;
            }
            break;
        case 6:
            if (call[i].time == feature_i){
                return i;
            }
            break;
        case 7:
            if (call[i].cost == feature_d){
                return i;
            }
            break;
        case 8:
            if (call[i].number_city == feature_i){
                return i;
            }
            break;
        case 9:
            if (call[i].number_caller == feature_i){
                return i;
            }
            break;
        }
    }

    return -1;
}

Call *DeleteCall(Call * call, int * size, int number){
    for (int i = number + 1; i < *size; i++){
        std::swap(call[i], call[i - 1]);
    }

    call = DeleteSpace(call, size);

    return call;
}                 
Call *ChooseForDelete(Call * call, int * size, std::string * cities, int * codes, int n_cities){
    if (*size == 0){
        std::cout << "Нет звонков!\n";
        return call;
    }
    int input, find;
    int feature_i = -1;
    double feature_d = -1;
    std::string feature_s = "ERROR";
    std::cout << "Введите признак, по которому необходимо удалить звонок:\n";
    std::cout << "1 - Год\n2 - Месяц\n3 - День\n4 - Город по названию\n5 - Город по коду\n6 - Время звонка\n";
    std::cout << "7 - Стоимость минуты\n8 - Номер телефона из города\n9 - Номер телефона абонента\n10 - Номер\n";
    while (1){
        input = CheckUnsigned();
        if (input <= 10 && input >= 1){
            break;
        }
        std::cout << "Неверный номер!\n";
    }

    if (input == 10){
        std::cout << "Введите номер клинта, которого необходимо удалить: ";
        feature_i = CheckNumberOfArray(*size);
        call = DeleteCall(call, size, feature_i - 1);
    }
    else if (input <= 3 || input == 5 || input == 6 || input >=8){
        std::cout << "Введите значение признака: ";
        feature_i = CheckUnsigned();
        find = FindCall(call, 0, *size, input, feature_i, feature_d, feature_s, cities, codes, n_cities);
        while (find != -1){
            call = DeleteCall(call, size, find);
            find = FindCall(call, find, *size, input, feature_i, feature_d, feature_s, cities, codes, n_cities);
        }
    }
    else if(input == 7){
        std::cout << "Введите значение признака: ";
        feature_d = CheckDouble();
        find = FindCall(call, 0, *size, input, feature_i, feature_d, feature_s, cities, codes, n_cities);
        while (find != -1){
            call = DeleteCall(call, size, find);
            find = FindCall(call, find, *size, input, feature_i, feature_d, feature_s, cities, codes, n_cities);
        }
    }
    else {
        std::cout << "Введите значение признака: ";
        std::cin >> feature_s;
        find = FindCall(call, 0, *size, input, feature_i, feature_d, feature_s, cities, codes, n_cities);
        while (find != -1){
            call = DeleteCall(call, size, find);
            find = FindCall(call, find, *size, input, feature_i, feature_d, feature_s, cities, codes, n_cities);
        }
    }

    return call;
} 

Call *ChooseForChange(Call * call, int size, std::string * cities, int * codes, int n_cities){
    if (size == 0){
        std::cout << "Нет звонков!\n";
        return call;
    }
    int number;
    std::cout << "Введите номер звонка, данные которого вы хотите поменять: ";
    number = CheckNumberOfArray(size);
    number--;
    bool exit = false;
    while (!exit){
        std::cout << "Выберите, что вы хотите поменять:\n";
        std::cout << "1 - Дата\n2 - Название города\n3 - Код города\n4 - Время звонка\n";
        std::cout << "5 - Стоимость минуты\n6 - Номер телефона из города\n7 - Номер телефона абонента\n8 - Выйти\n";
        int input;
        input = CheckUnsigned();
        switch (input){
        case 1:
            std::cout << "Введите новый год: ";
            call[number].year = CheckDate(3, call[number]);
            std::cout << "Введите новый месяц: ";
            call[number].month = CheckDate(2, call[number]);
            std::cout << "Введите новый день: ";
            call[number].day = CheckDate(1, call[number]);
            break;
        case 2:
            std::cout << "Введите новое название города: ";
            call[number].hasName = 1;
            call[number].city = CheckCity(call[number].hasName, cities, codes, n_cities);
            break;
        case 3:
            std::cout << "Введите новый код города: ";
            call[number].hasName = 0;
            call[number].city = CheckCity(call[number].hasName, cities, codes, n_cities);
            break;
        case 4:
            std::cout << "Введите новое врямя звонка: ";
            call[number].time = CheckUnsigned();
            break;
        case 5:
            std::cout << "Введите новую стоимость минуты: ";
            call[number].cost = CheckDouble();
            break;
        case 6:
            std::cout << "Введите новый номер телефона из города: ";
            call[number].number_city = CheckTellNumber(1, call[number], cities, codes, n_cities);
            break;
        case 7:
            std::cout << "Введите новый номер телефона абонента: ";
            call[number].number_caller = CheckTellNumber(0, call[number], cities, codes, n_cities);
            break;
        case 8:
            exit = true;
            break;
        default:
            std::cout << "Неверный номер!\n";
        }
    }

    return call;
}

void OutputCities(Call * call, int size, std::string * cities, int * codes, int n_cities) {
    for (int i = 0; i < n_cities; i++) {
        int total_time = 0;
        double total_cost = 0;
        std::cout << "Город: " << cities[i] << "\nКод города: " << codes[i];
        int find = FindCall(call, 0, size, 5, codes[i], 0, "\0", cities, codes, n_cities);
        while (find != -1){
            total_time += call[find].time;
            total_cost += call[find].time * call[find].cost;
            find = FindCall(call, find + 1, size, 5, codes[i], 0, "\0", cities, codes, n_cities);
        }
        std::cout << "\nОбщее время звонков в городе: " << total_time;
        std::cout << "\nОбщая сумма за звонки в город: " << total_cost << '\n';
    }
}
void WriteText(Call * call, int size){
    std::fstream file("Text.txt", std::ios::out | std::ios::trunc | std::ios::in);
    for (int i = 0; i < size; i++) {
        file << call[i].year << '\n';
        file << call[i].month << '\n';
        file << call[i].day << '\n';
        if (call[i].hasName){
            file << call[i].city.name << '\n';
        }
        else{
            file << call[i].city.code << '\n';
        }
        file << call[i].time << '\n';
        file << call[i].cost << '\n';
        file << call[i].number_city << '\n';
        file << call[i].number_caller << '\n';
        file << '\n';
    }
    file.close();
}

Call *ChangeText(Call * call, int size, std::string * cities, int * codes, int n_cities){
    if (size == 0){
        std::cout << "Нет звонков!\n";
        return call;
    }
    int number;
    std::cout << "Введите номер звонка, данные которого вы хотите поменять: ";
    number = CheckNumberOfArray(size);
    number--;
    bool exit = false;
    while (!exit){
        std::cout << "Выберите, что вы хотите поменять:\n";
        std::cout << "1 - Дата\n2 - Название города\n3 - Код города\n4 - Время звонка\n";
        std::cout << "5 - Стоимость минуты\n6 - Номер телефона из города\n7 - Номер телефона абонента\n8 - Выйти\n";
        int input;
        input = CheckUnsigned();
        switch (input){
        case 1:
            std::cout << "Введите новый год: ";
            call[number].year = CheckDate(3, call[number]);
            WriteText(call, size);
            std::cout << "Введите новый месяц: ";
            call[number].month = CheckDate(2, call[number]);
            WriteText(call, size);
            std::cout << "Введите новый день: ";
            call[number].day = CheckDate(1, call[number]);
            WriteText(call, size);
            break;
        case 2:
            std::cout << "Введите новое название города: ";
            call[number].hasName = 1;
            call[number].city = CheckCity(call[number].hasName, cities, codes, n_cities);
            WriteText(call, size);
            break;
        case 3:
            std::cout << "Введите новый код города: ";
            call[number].hasName = 0;
            call[number].city = CheckCity(call[number].hasName, cities, codes, n_cities);
            WriteText(call, size);
            break;
        case 4:
            std::cout << "Введите новое врямя звонка: ";
            call[number].time = CheckUnsigned();
            WriteText(call, size);
            break;
        case 5:
            std::cout << "Введите новую стоимость минуты: ";
            call[number].cost = CheckDouble();
            WriteText(call, size);
            break;
        case 6:
            std::cout << "Введите новый номер телефона из города: ";
            call[number].number_city = CheckTellNumber(1, call[number], cities, codes, n_cities);
            WriteText(call, size);
            break;
        case 7:
            std::cout << "Введите новый номер телефона абонента: ";
            call[number].number_caller = CheckTellNumber(0, call[number], cities, codes, n_cities);
            WriteText(call, size);
            break;
        case 8:
            exit = true;
            break;
        default:
            std::cout << "Неверный номер!\n";
        }
    }

    return call;
}