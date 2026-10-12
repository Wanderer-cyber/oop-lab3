#pragma once
#include <string>
using namespace std;

class EnergyError                      // базовий клас винятків
{
protected:
    string msg;
public:
    EnergyError(string m) : msg(m) {}
    string what() const { return msg; }
};

class ValueError : public EnergyError  // некоректне число
{
public:
    ValueError(string m) : EnergyError(m) {}
};

class DateError : public EnergyError   // некоректна дата
{
public:
    DateError(string m) : EnergyError(m) {}
};

class StateError : public EnergyError  // порожній запис / неіснуючий номер
{
public:
    StateError(string m) : EnergyError(m) {}
};