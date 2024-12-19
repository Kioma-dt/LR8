#include <iostream>
#include <string>
#include <cmath>
#include "Struct.h"

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

unsigned long long CheckUnsigned() {
    unsigned long long  input;
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
        std::cout << "Нет клиента с таким номером!\n";
    }

    return input;
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
                return date;
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
            std::cin >> city.code;
            for (int i = 0; i < n_cities;i++){
                if (city.code == codes[i]){
                    return city;
                }
            }
            std::cout << "Нет города с таким кодом!\n";
        }
    }
}


unsigned long long CheckTellNumber(bool from_city, Call call, std::string * cities, int * codes, int n_cities){
    unsigned long long number;
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
        std::cin >> cities[i];
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
            call->number_caller = 8 * pow(10, 8) + NameToCode(call->city.name, cities, codes, n_cities) * pow(10, 5) + rand() % 99999;
        }
        else{
            call->number_caller = 8 * pow(10, 8) + call->city.code * pow(10, 5) + rand() % 99999;
        }
        call->number_city = 8 * pow(10, 8) + rand() % 99999999;
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
    std::cout << call.number_caller;
    std::cout << "\nНомер телефона абонента: ";
    std::cout << call.number_city;
    std::cout << "\n";
}