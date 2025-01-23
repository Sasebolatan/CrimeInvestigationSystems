#ifndef INVESTIGATIONCONTROL_H
#define INVESTIGATIONCONTROL_H

#include "Detective.h"
#include "Suspect.h"
#include "CustomExceptions.h" // Include custom exceptions
#include <vector>
#include <memory>
#include <string>

using namespace std;

class InvestigationControl {
private:
    vector<shared_ptr<Detective>> detectives;
    vector<shared_ptr<Suspect>> suspects;

public:
    void addDetective(shared_ptr<Detective> d) {
        detectives.push_back(d);
    }

    void addSuspect(shared_ptr<Suspect> s) {
        suspects.push_back(s);
    }

    const vector<shared_ptr<Detective>>& getDetectives() const {
        return detectives;
    }

    const vector<shared_ptr<Suspect>>& getSuspects() const {
        return suspects;
    }

    // Validate if there are suspects in the system
    void validateCase() const {
        if (suspects.empty()) {
            throw EmptyCaseException();
        }
    }

    shared_ptr<Suspect> findSuspect(const string& name) {
        validateCase(); // Ensure suspects exist
        for (const auto& suspect : suspects) {
            if (suspect->getName() == name) {
                return suspect;
            }
        }
        throw SuspectNotFoundException();
    }

    void showCaughtDetails(shared_ptr<Suspect> suspect) {
        cout << "Suspect Name: " << suspect->getName() << endl;
        cout << "Caught By: " << suspect->getCaughtBy() << endl;
        cout << "Reason Caught: " << suspect->getReasonCaught() << endl;
        cout << "Guilty Status: " << (suspect->getGuiltStatus() ? "Guilty" : "Innocent") << endl;
    }
};

#endif // INVESTIGATIONCONTROL_H
