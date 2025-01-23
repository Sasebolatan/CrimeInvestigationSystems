#ifndef DETECTIVE_H
#define DETECTIVE_H

#include "Person.h"

class Detective : public Person {
private:
    string skill;

public:
    // Constructor
    Detective(string n, int a, string s) : Person(n, a), skill(s) {}

    // Override describe() for polymorphism
    void describe() override {
        cout << "Detective " << name << ", Age: " << age << ", Skill: " << skill << endl;
    }

    // Getter for skill
    string getSkill() const { return skill; }
};

#endif // DETECTIVE_H
