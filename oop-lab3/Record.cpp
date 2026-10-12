#include "Record.h"
#include <iomanip>

Record::Record() : tariff(0), day(0), month(0), year(0), paid(0), filled(false) {}

Record::Record(double tariff, int d, int m, int y, double paid)
    : tariff(0), day(0), month(0), year(0), paid(0), filled(false)
{
    setTariff(tariff);
    setPaid(paid);
    setDate(d, m, y);
}

Record::~Record() {}

int Record::daysInMonth(int month, int year)
{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (month == 2 && leap) return 29;
    return days[month - 1];
}

void Record::checkFilled() const
{
    if (!filled) throw StateError("Запис порожній (дата не встановлена).");
}

void Record::setTariff(double value)
{
    if (value < 0) throw ValueError("Тариф не може бути від'ємним.");
    tariff = value;
}

void Record::setPaid(double value)
{
    if (value < 0) throw ValueError("Сплачена сума не може бути від'ємною.");
    paid = value;
}

void Record::setDate(int d, int m, int y)
{
    if (y < 2000 || y > 2100) throw DateError("Рік має бути від 2000 до 2100.");
    if (m < 1 || m > 12)      throw DateError("Місяць має бути від 1 до 12.");
    if (d < 1 || d > daysInMonth(m, y)) throw DateError("Такого дня в цьому місяці немає.");
    day = d; month = m; year = y;
    filled = true;
}

double Record::getTariff() const { checkFilled(); return tariff; }
double Record::getPaid() const { checkFilled(); return paid; }
int Record::getDay() const { checkFilled(); return day; }
int Record::getMonth() const { checkFilled(); return month; }
int Record::getYear() const { checkFilled(); return year; }

Record& Record::operator++()
{
    checkFilled();
    tariff += 1;
    paid += 1;
    return *this;
}

Record Record::operator++(int)
{
    Record old = *this;
    ++*this;
    return old;
}

Record& Record::operator-=(double v)
{
    checkFilled();
    if (v < 0) throw ValueError("Величина зменшення не може бути від'ємною.");
    if (tariff - v < 0 || paid - v < 0)
        throw ValueError("Показник не може стати від'ємним.");
    tariff -= v;
    paid -= v;
    return *this;
}

bool Record::sameDate(int d, int m, int y) const
{
    return filled && day == d && month == m && year == y;
}

void Record::show() const
{
    checkFilled();
    cout << setfill('0') << setw(2) << day << "." << setw(2) << month << "." << year
        << setfill(' ') << " | тариф: " << tariff << " грн/кВт·год | сплачено: "
        << paid << " грн" << endl;
}