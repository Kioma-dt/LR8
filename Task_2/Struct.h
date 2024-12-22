#include <string>
#pragma once

typedef union City{
    char name[50];
    int code;
} City;

typedef struct Call{
    int year;
    int month;
    int day;
    bool hasName;
    City city;
    int time;
    double cost;
    int number_city;
    int number_caller;
} Call;
