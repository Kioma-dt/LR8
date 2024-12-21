#pragma once
#include <string>

typedef union addr{
    char street[50];
    int district;
} addr;

typedef struct Client{
    char last_name[50];
    char first_name[50];
    char patronymic[50];
    bool hasStreet;
    addr address;
    int house;
    int flat;
    int discount;
} Client;