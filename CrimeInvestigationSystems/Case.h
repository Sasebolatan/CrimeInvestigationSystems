#ifndef CASE_H
#define CASE_H

#include "Suspect.h"
#include "Evidence.h"
#include <vector>
#include <memory>

class Case {
private:
    string caseID;
    vector<shared_ptr<Suspect>> suspects;
    vector<shared_ptr<Evidence>> evidence;

public:
    Case(string id) : caseID(id) {}

    void addSuspect(shared_ptr<Suspect> s) {
        suspects.push_back(s);
    }

    void addEvidence(shared_ptr<Evidence> e) {
        evidence.push_back(e);
    }

    void showDetails() {
        cout << "Case ID: " << caseID << endl;
        cout << "Suspects:" << endl;
        for (auto& s : suspects) {
            s->describe();
        }
        cout << "Evidence:" << endl;
        for (auto& e : evidence) {
            e->showEvidence();
        }
    }
};

#endif // CASE_H