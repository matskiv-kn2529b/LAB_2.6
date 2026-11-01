//////////////////////////////////////////////////////////////////////////////
// Source.cpp
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif
#include "Bus.h"
#include <stdexcept>
using namespace std;

// Дзеркальні структури з тими ж полями для розміру в режимі pack(1)
#pragma pack(push, 1)
struct CarPacked { string brand; int cylinders; double power; };
struct BusPacked { CarPacked car; int seats; };
#pragma pack(pop)

static void showCounters(const char* label)
{
    cout << label << ": Bus = " << Bus::getCounter()
        << ", Bus::Car = " << Bus::Car::getCounter() << endl;
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    try
    {
        cout << "=== Лічильники об'єктів ===" << endl;
        showCounters("На початку");
        Bus b1;                                  // +1 Bus, +1 Car (вкладена)
        showCounters("Bus b1");
        Bus::Car c1;                             // окрема Car: +1 Car
        showCounters("Bus::Car c1");
        {
            Bus b2("MAN", 6, 320, 50);
            Bus b3(b2);                          // копіювання
            Bus::Car c2("Audi");
            showCounters("У блоці");
        }
        showCounters("Після блоку");

        cout << "=== Масиви ===" << endl;
        Bus arr[2] = { Bus("Neoplan", 8, 400, 60), Bus() };
        showCounters("Статичний масив Bus[2]");
        Bus* dyn = new Bus[2];
        showCounters("+ динамічний масив");
        delete[] dyn;
        showCounters("Після delete[]");
        for (int i = 0; i < 2; i++) cout << arr[i];

        cout << "=== Bus::Car: створення та операції ===" << endl;
        Bus::Car c3("BMW", 6, 250);
        Bus::Car c4(c3);
        Bus::Car c5 = c3;
        c1 = c3;
        Bus::Car c6 = ++c3;
        c6 = c3--;
        c3.setPower(300);
        c3.changePower(-50);
        cout << "c1:\n" << c1 << "c3:\n" << c3 << "c6:\n" << c6;

        cout << "=== Bus: створення та операції ===" << endl;
        Bus b4("MAN", 6, 320, 50);
        Bus b5(c3, 30);
        Bus b6(b4);
        b1 = b4;
        Bus b7 = ++b4;
        b7 = b4--;
        b4.setBrand("Mercedes");
        b4.changeSeats(10);
        cout << "b1:\n" << b1 << "b4:\n" << b4 << "b5:\n" << b5 << "b7:\n" << b7;
        cout << "Марка b4: " << b4.getBrand() << endl;
        string s = string(b5);
        cout << "Приведення до string:\n" << s;

        cout << "=== Розміри класів ===" << endl;
        cout << "Без pack(1): Car = " << sizeof(Bus::Car)
            << ", Bus = " << sizeof(Bus) << endl;
        cout << "З pack(1):   Car = " << sizeof(CarPacked)
            << ", Bus = " << sizeof(BusPacked) << endl;

        cout << "=== Введення з клавіатури ===" << endl;
        Bus b8;
        cin >> b8;
        cout << b8;
        showCounters("Наприкінці");

        cout << "=== Перевірка коректності ===" << endl;
        c1.setCylinders(100); // навмисна помилка
    }
    catch (const invalid_argument& e)
    {
        cout << "Помилка: " << e.what() << endl;
    }
    return 0;
}