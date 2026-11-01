//////////////////////////////////////////////////////////////////////////////
// UnitTest.cpp
#include "pch.h"  
#include "CppUnitTest.h"
#include <string>
#include <sstream>
#include <stdexcept>

#include "C:\Users\Mackiv\source\repos\LAB_2.6\LAB_2.6\Bus.h"
#include "C:\Users\Mackiv\source\repos\LAB_2.6\LAB_2.6\Bus.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(CounterTests)
    {
    public:
        TEST_METHOD(BusCreatesNestedCar)
        {
            int busBefore = Bus::getCounter();
            int carBefore = Bus::Car::getCounter();
            {
                Bus b1;
                Bus b2(b1);
                Assert::AreEqual(busBefore + 2, Bus::getCounter());
                Assert::AreEqual(carBefore + 2, Bus::Car::getCounter());
            }
            Assert::AreEqual(busBefore, Bus::getCounter());
            Assert::AreEqual(carBefore, Bus::Car::getCounter());
        }

        TEST_METHOD(StandaloneCarCountsOnlyCar)
        {
            int busBefore = Bus::getCounter();
            int carBefore = Bus::Car::getCounter();
            {
                Bus::Car c("Audi");
                Assert::AreEqual(busBefore, Bus::getCounter());
                Assert::AreEqual(carBefore + 1, Bus::Car::getCounter());
            }
            Assert::AreEqual(carBefore, Bus::Car::getCounter());
        }

        TEST_METHOD(DynamicArrayCounters)
        {
            int busBefore = Bus::getCounter();
            Bus* arr = new Bus[3];
            Assert::AreEqual(busBefore + 3, Bus::getCounter());
            delete[] arr;
            Assert::AreEqual(busBefore, Bus::getCounter());
        }

        TEST_METHOD(CountersSurviveConstructorException)
        {
            int busBefore = Bus::getCounter();
            int carBefore = Bus::Car::getCounter();
            Assert::ExpectException<std::invalid_argument>([&] { Bus b("MAN", 6, 320, 0); });
            Assert::ExpectException<std::invalid_argument>([&] { Bus::Car c("X", 4, 0); });
            Assert::AreEqual(busBefore, Bus::getCounter());
            Assert::AreEqual(carBefore, Bus::Car::getCounter());
        }
    };

    TEST_CLASS(CarTests)
    {
    public:
        TEST_METHOD(DefaultAndInit)
        {
            Bus::Car d;
            Assert::IsFalse(d.getBrand().empty());
            Assert::AreEqual(4, d.getCylinders());
            Assert::AreEqual(100.0, d.getPower());

            Bus::Car c("BMW", 6, 250);
            Assert::AreEqual("BMW", c.getBrand().c_str());
            Assert::AreEqual(6, c.getCylinders());
            Assert::AreEqual(250.0, c.getPower());
        }

        TEST_METHOD(CopyAndAssign)
        {
            Bus::Car a("Audi", 4, 150);
            Bus::Car b(a);
            Bus::Car c;
            c = a;
            Assert::AreEqual("Audi", b.getBrand().c_str());
            Assert::AreEqual(150.0, c.getPower());
        }

        TEST_METHOD(SettersValidate)
        {
            Bus::Car c;
            Assert::ExpectException<std::invalid_argument>([&] { c.setBrand(""); });
            Assert::ExpectException<std::invalid_argument>([&] { c.setCylinders(17); });
            Assert::ExpectException<std::invalid_argument>([&] { c.setPower(-5); });
            Assert::ExpectException<std::invalid_argument>([&] { c.changePower(-500); });
        }

        TEST_METHOD(IncrementDecrement)
        {
            Bus::Car c("Ford", 4, 100);
            Bus::Car r = ++c;
            Assert::AreEqual(101.0, r.getPower());
            Bus::Car old = c--;
            Assert::AreEqual(101.0, old.getPower());
            Assert::AreEqual(100.0, c.getPower());
            Bus::Car low("Ford", 4, 1);
            --low;
            Assert::AreEqual(1.0, low.getPower());
        }

        TEST_METHOD(ToStringAndOutput)
        {
            Bus::Car c("BMW", 6, 250);
            std::string expected = "brand = BMW\ncylinders = 6\npower = 250\n";
            std::string s = std::string(c);
            Assert::AreEqual(expected.c_str(), s.c_str());
            std::ostringstream out;
            out << c;
            std::string o = out.str();
            Assert::AreEqual(expected.c_str(), o.c_str());
        }
    };

    TEST_CLASS(BusTests)
    {
    public:
        TEST_METHOD(DefaultAndInit)
        {
            Bus b;
            Bus::Car defaultCar;
            Assert::AreEqual(defaultCar.getBrand().c_str(), b.getBrand().c_str());
            Assert::AreEqual(20, b.getSeats());

            Bus b1("MAN", 6, 320, 50);
            Assert::AreEqual("MAN", b1.getBrand().c_str());
            Assert::AreEqual(50, b1.getSeats());
            Assert::AreEqual(320.0, b1.getCar().getPower());

            Bus b2(Bus::Car("Volvo", 6, 300), 40);
            Assert::AreEqual("Volvo", b2.getBrand().c_str());
        }

        TEST_METHOD(CopyAndAssign)
        {
            Bus a("MAN", 6, 320, 50);
            Bus b(a);
            Bus c;
            c = a;
            Assert::AreEqual(50, b.getSeats());
            Assert::AreEqual("MAN", c.getBrand().c_str());
        }

        TEST_METHOD(SettersValidate)
        {
            Bus b;
            Assert::ExpectException<std::invalid_argument>([&] { b.setSeats(0); });
            Assert::ExpectException<std::invalid_argument>([&] { b.setSeats(201); });
            Assert::ExpectException<std::invalid_argument>([&] { b.setBrand(""); });
            Assert::ExpectException<std::invalid_argument>([&] { b.changeSeats(-100); });
        }

        TEST_METHOD(SetBrandAndChangeSeats)
        {
            Bus b("MAN", 6, 320, 50);
            b.setBrand("Mercedes");
            b.changeSeats(10);
            Assert::AreEqual("Mercedes", b.getBrand().c_str());
            Assert::AreEqual(60, b.getSeats());
        }

        TEST_METHOD(IncrementDecrement)
        {
            Bus b("MAN", 6, 320, 50);
            Bus r = ++b;
            Assert::AreEqual(51, r.getSeats());
            Bus old = b--;
            Assert::AreEqual(51, old.getSeats());
            Assert::AreEqual(50, b.getSeats());
            Bus lo("MAN", 6, 320, 1);
            --lo;
            Assert::AreEqual(1, lo.getSeats());
            Bus hi("MAN", 6, 320, 200);
            ++hi;
            Assert::AreEqual(200, hi.getSeats());
        }

        TEST_METHOD(ToStringAndOutput)
        {
            Bus b("MAN", 6, 320, 50);
            std::string expected = "brand = MAN\ncylinders = 6\npower = 320\nseats = 50\n";
            std::string s = std::string(b);
            Assert::AreEqual(expected.c_str(), s.c_str());
            std::ostringstream out;
            out << b;
            std::string o = out.str();
            Assert::AreEqual(expected.c_str(), o.c_str());
        }
    };
}