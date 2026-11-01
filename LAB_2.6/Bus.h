//////////////////////////////////////////////////////////////////////////////
// Bus.h
#pragma once
#include <iostream>
#include <string>

class Bus
{
public:
    // ВКЛАДЕНИЙ КЛАС: Car існує лише в контексті Bus
    class Car
    {
    private:
        std::string brand;
        int cylinders;
        double power;
        static int counter;   // кількість наявних об'єктів Car

    public:
        std::string getBrand() const { return brand; }
        int getCylinders() const { return cylinders; }
        double getPower() const { return power; }

        void setBrand(const std::string& brand);
        void setCylinders(int cylinders);
        void setPower(double power);
        void changePower(double delta);
        void Init(const std::string& brand, int cylinders, double power);

        Car();
        explicit Car(const std::string& brand);
        Car(const std::string& brand, int cylinders, double power);
        Car(const Car& c);
        ~Car();

        Car& operator = (const Car& c);
        operator std::string() const;
        Car& operator ++ ();
        Car& operator -- ();
        Car operator ++ (int);
        Car operator -- (int);

        static int getCounter();

        friend std::ostream& operator << (std::ostream& out, const Car& c);
        friend std::istream& operator >> (std::istream& in, Car& c);
    };

private:
    Car car;
    int seats;
    static int counter;       // кількість наявних об'єктів Bus

public:
    Car getCar() const { return car; }
    int getSeats() const { return seats; }
    std::string getBrand() const { return car.getBrand(); }

    void setCar(const Car& car) { this->car = car; }
    void setSeats(int seats);
    void setBrand(const std::string& brand);
    void changeSeats(int delta);
    void Init(const Car& car, int seats);

    Bus();
    Bus(const std::string& brand, int cylinders, double power, int seats);
    Bus(const Car& car, int seats);
    Bus(const Bus& b);
    ~Bus();

    Bus& operator = (const Bus& b);
    operator std::string() const;
    Bus& operator ++ ();
    Bus& operator -- ();
    Bus operator ++ (int);
    Bus operator -- (int);

    static int getCounter();

    friend std::ostream& operator << (std::ostream& out, const Bus& b);
    friend std::istream& operator >> (std::istream& in, Bus& b);
};