#include <iostream>
#include <string>

using namespace std;

// Base class car
class car {
private:
    string name;
    int modelYear;

protected:
    // Protected assign function to allow derived classes to use it
    void assign(const car& c) {
        name = c.name;
        modelYear = c.modelYear;
    }

public:
    // Constructor to initialize car object
    car(const string& n, const int my) : name(n), modelYear(my) {}

    // Virtual print function to allow overriding
    virtual void print() const {
        cout << "Name: " << name << " model Year: " << modelYear << endl;
    }

    // Virtual assignment operator
    virtual const car& operator=(const car& c) {
        if (this != &c) {
            assign(c);
        }
        return *this;
    }

    // Virtual destructor
    virtual ~car() = default;
};

// Derived class sedan
class sedan : public car {
private:
    int mileage;

public:
    // Constructor to initialize sedan object
    sedan(const string& n, const int my, const int m) : car(n, my), mileage(m) {}

    // Overriding print function
    virtual void print() const override {
        cout << "Name: " << name << " model Year: " << modelYear << " Mileage: " << mileage << endl;
    }

    // Overriding assignment operator
    virtual const sedan& operator=(const sedan& s) {
        if (this != &s) {
            car::operator=(s); // Call base class assignment operator
            mileage = s.mileage;
        }
        return *this;
    }
};

// Derived class suv
class suv : public car {
private:
    int miles;

public:
    // Constructor to initialize suv object
    suv(const string& n, const int my, const int m) : car(n, my), miles(m) {}

    // Overriding print function
    virtual void print() const override {
        cout << "Name: " << name << " model Year: " << modelYear << " Miles driven: " << miles << endl;
    }

    // Overriding assignment operator
    virtual const suv& operator=(const car& c) override {
        if (const suv* s = dynamic_cast<const suv*>(&c)) {
            car::operator=(c); // Call base class assignment operator
            miles = s->miles;
        }
        return *this;
    }

    // Overriding assignment operator for same type
    virtual const suv& operator=(const suv& s) {
        if (this != &s) {
            car::operator=(s); // Call base class assignment operator
            miles = s.miles;
        }
        return *this;
    }
};

// Function to print car information
void printCarInfo(const car& c) {
    c.print();
}

int main() {
    car tesla = car("tesla", 2019);
    sedan hyundai = sedan("Hyundai", 2020, 23);
    suv ford = suv("Ford", 2012, 20000);

    printCarInfo(tesla);
    printCarInfo(hyundai);

    printCarInfo(ford);
    suv ford2 = suv("Ford", 2017, 10000);
    ford = ford2;
    printCarInfo(ford);

    return 0;
}
