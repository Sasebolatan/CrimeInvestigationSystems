#ifndef SUSPECT_H
#define SUSPECT_H

#include "Person.h"

class Suspect : public Person {
private:
    string alibi;       // Suspect's alibi
    string caughtBy;    // Detective who caught the suspect
    string reasonCaught; // Reason for being caught
    bool isGuilty;      // Guilt status

public:
    // Constructor
    Suspect(string n, int a, string alibi, string caughtBy, string reason, bool guilty)
        : Person(n, a), alibi(alibi), caughtBy(caughtBy), reasonCaught(reason), isGuilty(guilty) {}

    // Override describe() for polymorphism
    void describe() override {
        cout << "Suspect " << name << ", Age: " << age
            << ", Alibi: " << alibi << endl;
    }

    // Get who caught the suspect
    string getCaughtBy() const { return caughtBy; }

    // Get the reason why the suspect was caught
    string getReasonCaught() const { return reasonCaught; }

    // Check if the suspect is guilty
    bool getGuiltStatus() const { return isGuilty; }
};

#endif // SUSPECT_H
