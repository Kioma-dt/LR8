#pragma once
#include <string>

typedef union addr{
    char street[1000];
    int district;
} addr;

typedef struct Client{
    std::string last_name;
    std::string first_name;
    std::string patronymic;
    bool hasStreet;
    addr address;
    int house;
    int flat;
    int discount;
} Client;