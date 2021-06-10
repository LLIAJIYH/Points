#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Vehicle
{
protected:
    string name;
public:
    string type;
    string get_name() const {return name;}
    Vehicle() {type="vehicle"; name = ""; cout<<"This is Vehicle default constructor\n";}
    Vehicle(const Vehicle &other)
    {
        cout<<"Called Vehicle copy constructor\n";
        this->name = other.name;
        this->type = other.type;
    }
    Vehicle(string n) {name = n; cout<<"This is Vehicle constructor\n";}
    virtual ~Vehicle() {cout<<"This is Vehicle destructor\n";}
    virtual void print() {cout<<"This vehicle is called "<<name<<endl;}
    virtual void drive() =0;
};

class Car:public virtual Vehicle
{
public:
    Car(string n="") { type="car"; name = n; cout<<"This is Car constructor\n";}
    Car(const Car &other)
    {
        cout<<"Called Car copy constructor\n";
        this->name = other.name;
        this->type = other.type;
    }

    ~Car() {cout<<"This is Car destructor\n";}
    void drive() override {cout<<"I'm driving a car "<<name<<"\n";}
};

class Bus:public Car
{
public:
    Bus(string n):Car(n) {type="bus"; cout<<"This is Bus constructor\n";}
    Bus(const Vehicle &other)
    {
        cout<<"Called Bus copy constructor\n";
        this->name = other.get_name();
        this->type = other.type;
    }
    ~Bus() {cout<<"This is Bus destructor\n";}
    void print() override {cout<<"This bus is called "<<name<<endl;}
    void drive() override {cout<<"I'm driving a bus "<<name<<"\n";}
};

class Plane:public virtual Vehicle
{
public:
    Plane(string n="") {type="plane"; name = n; cout<<"This is Plane constructor\n";}
    Plane(const Plane &other)
    {
        cout<<"Called Plane copy constructor\n";
        this->name = other.name;
        this->type = other.type;
    }

    ~Plane() {cout<<"This is Plane destructor\n";}
    void drive() override {cout<<"I'm driving a plane "<<name<<"\n";}
};

class FlyingCar:public Plane, public Car
{
public:
    FlyingCar(string n):Plane(n), Car(n)
    {
        type="flyingcar";
        cout<<"This is FlyingCar constructor\n";
    }
    FlyingCar(const Vehicle &other)
    {
        cout<<"Called FlyingCar copy constructor\n";
        this->name = other.get_name();
        this->type = other.type;
    }
    ~FlyingCar() {cout<<"This is FlyingCar destructor\n";}
    void drive() override {cout<<"I'm driving a FlyingCar "<<name<<"\n";}
    void print() override {cout<<"This FlyingCar is called "<<name<<endl;}

};

class Human
{
public:
    Human() {}
    void drive(Vehicle &v)
    {
        v.drive();
    }
};

class Garage
{
public:
    vector<Vehicle*> vehicles;
    Garage() { cout<<"This is garage\n"; }
    void add_vehicle(Vehicle *add)
    {
        Vehicle* v;
        if(add->type == "bus")
            v = new Bus(*add);
        else
            v = new FlyingCar(*add);
        vehicles.push_back(v);
    }
    void print()
    {
        for(int i=0; i<vehicles.size(); i++)
            vehicles[i]->print();
    }
    ~Garage()
    {
        for(int i=0; i<vehicles.size(); i++)
            delete vehicles[i];
    }
};

class Point
{
public:
    Point() {}
    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual int getZ() = 0;
    virtual void setX(int x_) =0;
    virtual void setY(int y_) =0;
    virtual void setZ(int z_) =0;
    virtual void print() {}
protected:
    virtual ~Point() {}
};

int main()
{
    Garage garage;
    Vehicle* vehicle1 = new FlyingCar("ComboWombo");
    Vehicle* vehicle2 = new Bus("MAZ");
    garage.add_vehicle(vehicle1);
    garage.add_vehicle(vehicle2);
    delete vehicle1;
    delete vehicle2;
    garage.print();
    //Human human;
    //human.drive(car);
    return 0;
}

/*
class Component
{
public:
    string name;
    Component(string n) { name = n;}
};class Memory:public Component
{
public:
    Memory(string n):Component(n){}
};

class CPU:public Component
{
public:
    CPU(string n):Component(n) {}
};

class PC:public CPU, public Memory
{
public:
    PC(string memory_name, string cpu_name):Memory(memory_name), CPU(cpu_name) {}
    void print() {cout<<"Memory name="<<Memory::name<<" CPU name="<<CPU::name<<endl;}
};*/
