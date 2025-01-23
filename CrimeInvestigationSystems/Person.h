#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    // Constructor
    Person(string n, int a) : name(n), age(a) {}

    // Pure virtual function for polymorphism
    virtual void describe() = 0;

    // Getter for name
    string getName() const { return name; }

    // Virtual destructor
    virtual ~Person() {}
};

#endif // PERSON_H
