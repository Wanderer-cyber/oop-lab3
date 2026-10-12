#include "EnergyBook.h"

EnergyBook::EnergyBook() {}
EnergyBook::~EnergyBook() {}

void EnergyBook::add(const Record& r) { records.push_back(r); }
int EnergyBook::count() const { return (int)records.size(); }

Record& EnergyBook::get(int index)
{
    if (index < 1 || index > count())
        throw StateError("Запису з таким номером немає.");
    return records[index - 1];
}

void EnergyBook::show() const
{
    if (records.empty()) { cout << "Книга порожня.\n"; return; }
    for (size_t i = 0; i < records.size(); i++)
    {
        cout << i + 1 << ") ";
        records[i].show();
    }
}

vector<int> EnergyBook::find(int d, int m, int y) const
{
    vector<int> res;
    for (size_t i = 0; i < records.size(); i++)
        if (records[i].sameDate(d, m, y)) res.push_back((int)i + 1);
    return res;
}

vector<int> EnergyBook::find(int m, int y) const
{
    vector<int> res;
    for (size_t i = 0; i < records.size(); i++)
        if (records[i].getMonth() == m && records[i].getYear() == y) res.push_back((int)i + 1);
    return res;
}

vector<int> EnergyBook::find(int y) const
{
    vector<int> res;
    for (size_t i = 0; i < records.size(); i++)
        if (records[i].getYear() == y) res.push_back((int)i + 1);
    return res;
}