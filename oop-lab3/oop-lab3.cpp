#include <iostream>
#include <string>
#include "EnergyBook.h"
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

double readNumber(const string& text)
{
    while (true)
    {
        cout << text;
        string s;
        getline(cin, s);
        try
        {
            size_t pos;
            double v = stod(s, &pos);
            if (pos == s.size()) return v;
        }
        catch (...) {}
        cout << "  Потрібне число, спробуйте ще раз.\n";
    }
}

void showFound(EnergyBook& book, const vector<int>& found)
{
    if (found.empty()) { cout << "Нічого не знайдено.\n"; return; }
    cout << "Знайдено записів: " << found.size() << endl;
    for (size_t i = 0; i < found.size(); i++)
    {
        cout << found[i] << ") ";
        book.get(found[i]).show();
    }
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    EnergyBook book;
    int choice = -1;

    while (choice != 0)
    {
        cout << "\n===== РОЗРАХУНКОВА КНИГА =====\n"
            << "1 - Додати запис\n"
            << "2 - Показати всі записи\n"
            << "3 - Збільшити показники запису на 1 (++)\n"
            << "4 - Зменшити показники запису на величину (-=)\n"
            << "5 - Пошук за датою\n"
            << "0 - Вихід\n";
        choice = (int)readNumber("Ваш вибір: ");

        try
        {
            switch (choice)
            {
            case 1:
            {
                double t = readNumber("Вартість 1 кВт·год (грн): ");
                int d = (int)readNumber("День: ");
                int m = (int)readNumber("Місяць: ");
                int y = (int)readNumber("Рік: ");
                double p = readNumber("Сплачена сума (грн): ");
                book.add(Record(t, d, m, y, p));
                cout << "Запис додано.\n";
                break;
            }
            case 2:
                book.show();
                break;
            case 3:
            {
                int n = (int)readNumber("Номер запису: ");
                ++book.get(n);
                cout << "Після ++: ";
                book.get(n).show();
                break;
            }
            case 4:
            {
                int n = (int)readNumber("Номер запису: ");
                double v = readNumber("На скільки зменшити: ");
                book.get(n) -= v;
                cout << "Після -=: ";
                book.get(n).show();
                break;
            }
            case 5:
            {
                cout << "Пошук: 1 - за повною датою, 2 - за місяцем і роком, 3 - за роком\n";
                int kind = (int)readNumber("Варіант: ");
                if (kind == 1)
                {
                    int d = (int)readNumber("День: ");
                    int m = (int)readNumber("Місяць: ");
                    int y = (int)readNumber("Рік: ");
                    showFound(book, book.find(d, m, y));
                }
                else if (kind == 2)
                {
                    int m = (int)readNumber("Місяць: ");
                    int y = (int)readNumber("Рік: ");
                    showFound(book, book.find(m, y));
                }
                else if (kind == 3)
                {
                    int y = (int)readNumber("Рік: ");
                    showFound(book, book.find(y));
                }
                else cout << "Немає такого варіанта.\n";
                break;
            }
            case 0:
                cout << "До побачення!\n";
                break;
            default:
                cout << "Немає такого пункту.\n";
            }
        }
        // спочатку похідні класи, потім базовий
        catch (DateError& e) { cout << "Помилка дати: " << e.what() << endl; }
        catch (ValueError& e) { cout << "Помилка значення: " << e.what() << endl; }
        catch (StateError& e) { cout << "Помилка стану: " << e.what() << endl; }
        catch (EnergyError& e) { cout << "Помилка: " << e.what() << endl; }
    }
    return 0;
}