#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <string>
#include <iostream>
using namespace std;

class Evidence {
private:
    string type;
    string description;

public:
    Evidence(string t, string d) : type(t), description(d) {}

    void showEvidence() {
        cout << "Evidence Type: " << type << ", Description: " << description << endl;
    }
};

#endif // EVIDENCE_H

