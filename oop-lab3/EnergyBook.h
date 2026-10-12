#pragma once
#include <vector>
#include "Record.h"
using namespace std;

class EnergyBook
{
private:
    vector<Record> records;

public:
    EnergyBook();
    ~EnergyBook();

    void add(const Record& r);
    int count() const;
    Record& get(int index);
    void show() const;

    // перевантажений метод пошуку за датою
    vector<int> find(int d, int m, int y) const;
    vector<int> find(int m, int y) const;
    vector<int> find(int y) const;
};