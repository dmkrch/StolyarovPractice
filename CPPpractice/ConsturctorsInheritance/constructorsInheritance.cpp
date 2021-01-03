#include <iostream>
using namespace std;

class Device {
    public:
        // constructor
        Device() {
            cout << "Device constructor called" << endl;
        }
        // destructor
        ~Device() {
            cout << "Device destructor called" << endl;
        }
    private:
        int a;
};

class Computer: public Device {
    public:
        Computer() {
            cout << "Computer constructor called" << endl;
        }
        ~Computer() {
            cout << "Computer destructor called" << endl;
        }

        void CheckPrivate()
        {
            
        }
};

class Laptop: public Computer {
    public:
        Laptop() {
            cout << "Laptop constructor called" << endl;
        }
        ~Laptop() {
            cout << "Laptop destructor called" << endl;
        }
};

int main() {
    cout << "\tConstructors" << endl;
    Laptop Laptop_instance;
    cout << "\tDestructors" << endl;

    Computer comp;

    
    return 0;
}


/*
constructors: Device -> Computer -> Laptop.
destructors: Laptop -> Computer -> Device.
*/