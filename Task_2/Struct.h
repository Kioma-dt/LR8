#include <string>
#pragma once

typedef union City{
    char name[1000];
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
    unsigned long long number_city;
    unsigned long long number_caller;
} Call;
