#include <string>
#include "Struct.h"

Call *AddSpace(Call *, int *);
Call *DeleteSpace(Call *, int *);
int NameToCode(std::string, std::string *, int *, int);
std::string CodeToName(int, std::string *, int *, int);
unsigned long long CheckUnsigned();
int CheckNumberOfArray(int);
int CheckDate(int type, Call);                                              // Проверка даты(type = 1 - день, type = 2 - месяц, type = 3 - год)
bool CheckNameOrCode();
City CheckCity(bool, std::string *, int *, int);
unsigned long long CheckTellNumber(bool, Call, std::string *, int *, int);
void EnterCities(std::string *, int *, int);
void EnterCall(Call *, std::string *, int *, int, bool);
Call *EnterWithSize(int *, std::string *, int *, int, bool);
void OutputCall(Call);