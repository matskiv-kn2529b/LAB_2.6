//////////////////////////////////////////////////////////////////////////////
// Bus.cpp
#include "Bus.h"
#include <sstream>
#include <stdexcept>

////////////////////////////////////////////////////////////
// class Bus::Car (у методах Car "counter" - це Car::counter)
int Bus::Car::counter = 0;

void Bus::Car::setBrand(const std::string& value)
{
    if (value.empty())
        throw std::invalid_argument("Марка машини не може бути порожньою");
    brand = value;
}

void Bus::Car::setCylinders(int value)
{
    if (value < 1 || value > 16)
        throw std::invalid_argument("Кількість циліндрів має бути від 1 до 16");
    cylinders = value;
}

void Bus::Car::setPower(double value)
{
    if (value <= 0 || value > 2000)
        throw std::invalid_argument("Потужність має бути більшою за 0 і не більшою за 2000");
    power = value;
}

void Bus::Car::changePower(double delta) { setPower(power + delta); }

void Bus::Car::Init(const std::string& newBrand, int newCylinders, double newPower)
{
    setBrand(newBrand);
    setCylinders(newCylinders);
    setPower(newPower);
}

Bus::Car::Car() : brand("Не вказано"), cylinders(4), power(100.0) { ++counter; }

Bus::Car::Car(const std::string& newBrand) : cylinders(4), power(100.0)
{
    setBrand(newBrand);
    ++counter;   // після перевірок: при виняткові лічильник не змінюється
}

Bus::Car::Car(const std::string& newBrand, int newCylinders, double newPower)
    : cylinders(4), power(100.0)
{
    Init(newBrand, newCylinders, newPower);
    ++counter;
}

Bus::Car::Car(const Car& c)
    : brand(c.brand), cylinders(c.cylinders), power(c.power) {
    ++counter;
}

Bus::Car::~Car() { --counter; }

Bus::Car& Bus::Car::operator = (const Car& c)
{
    if (this != &c) { brand = c.brand; cylinders = c.cylinders; power = c.power; }
    return *this;
}

Bus::Car::operator std::string() const
{
    std::ostringstream ss;
    ss << "brand = " << brand << '\n'
        << "cylinders = " << cylinders << '\n'
        << "power = " << power << '\n';
    return ss.str();
}

Bus::Car& Bus::Car::operator ++ () { changePower(1.0); return *this; }
Bus::Car& Bus::Car::operator -- () { if (power > 1.0) changePower(-1.0); return *this; }
Bus::Car Bus::Car::operator ++ (int) { Car old(*this); ++(*this); return old; }
Bus::Car Bus::Car::operator -- (int) { Car old(*this); --(*this); return old; }

int Bus::Car::getCounter() { return counter; }

std::ostream& operator << (std::ostream& out, const Bus::Car& c)
{
    out << std::string(c);
    return out;
}

std::istream& operator >> (std::istream& in, Bus::Car& c)
{
    std::string brand;
    int cylinders;
    double power;
    std::cout << "brand = ? ";
    in >> brand;
    std::cout << "cylinders = ? ";
    in >> cylinders;
    std::cout << "power = ? ";
    in >> power;
    if (in) c.Init(brand, cylinders, power);
    return in;
}

////////////////////////////////////////////////////////////
// class Bus (тут "counter" - це Bus::counter)
int Bus::counter = 0;

void Bus::setSeats(int value)
{
    if (value < 1 || value > 200)
        throw std::invalid_argument("Кількість місць має бути від 1 до 200");
    seats = value;
}

void Bus::setBrand(const std::string& brand) { car.setBrand(brand); }
void Bus::changeSeats(int delta) { setSeats(seats + delta); }

void Bus::Init(const Car& newCar, int newSeats)
{
    setCar(newCar);
    setSeats(newSeats);
}

Bus::Bus() : car(), seats(20) { ++counter; }

Bus::Bus(const std::string& brand, int cylinders, double power, int newSeats)
    : car(brand, cylinders, power), seats(20)
{
    setSeats(newSeats);
    ++counter;
}

Bus::Bus(const Car& newCar, int newSeats) : car(newCar), seats(20)
{
    setSeats(newSeats);
    ++counter;
}

Bus::Bus(const Bus& b) : car(b.car), seats(b.seats) { ++counter; }
Bus::~Bus() { --counter; }

Bus& Bus::operator = (const Bus& b)
{
    if (this != &b) { car = b.car; seats = b.seats; }
    return *this;
}

Bus::operator std::string() const
{
    std::ostringstream ss;
    ss << std::string(car) << "seats = " << seats << '\n';
    return ss.str();
}

Bus& Bus::operator ++ () { if (seats < 200) changeSeats(1); return *this; }
Bus& Bus::operator -- () { if (seats > 1) changeSeats(-1); return *this; }
Bus Bus::operator ++ (int) { Bus old(*this); ++(*this); return old; }
Bus Bus::operator -- (int) { Bus old(*this); --(*this); return old; }

int Bus::getCounter() { return counter; }

std::ostream& operator << (std::ostream& out, const Bus& b)
{
    out << std::string(b);
    return out;
}

std::istream& operator >> (std::istream& in, Bus& b)
{
    Bus::Car c;
    int seats;
    std::cout << "car:" << std::endl;
    in >> c;
    std::cout << "seats = ? ";
    in >> seats;
    if (in) b.Init(c, seats);
    return in;
}