#include <string>
#pragma once

typedef union City{
    char name[100];
    int code;
} City;

typedef struct Call{
    int day;
    int month;
    int year;
    bool hasName;
    City city;
    int time;
    double cost;
    unsigned long long number_city;
    unsigned long long number_caller;
} Call;
