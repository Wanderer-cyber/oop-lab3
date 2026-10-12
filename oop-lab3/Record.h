#pragma once
#include <iostream>
#include "Errors.h"
using namespace std;

class Record
{
private:
    double tariff;      // варт≥сть 1 к¬тЈгод (грн)
    int day, month, year;
    double paid;        // сплачена сума (грн)
    bool filled;        // чи заповнений запис

    void checkFilled() const;
    static int daysInMonth(int month, int year);

public:
    Record();
    Record(double tariff, int d, int m, int y, double paid);
    ~Record();

    void setTariff(double value);
    void setPaid(double value);
    void setDate(int d, int m, int y);

    double getTariff() const;
    double getPaid() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    Record& operator++();          // преф≥ксний
    Record  operator++(int);       // постф≥ксний
    Record& operator-=(double v);

    bool sameDate(int d, int m, int y) const;
    void show() const;
};