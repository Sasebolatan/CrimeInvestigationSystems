#include "InvestigationControl.h"
#include "WinsockClient.h"
#include "CustomExceptions.h"
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Function to display the main menu
void displayMenu() {
    cout << "\n--- Crime Investigation System Menu ---\n";
    cout << "1. View Suspect Database\n";
    cout << "2. View Detective Database\n";
    cout << "3. Search for a Suspect\n";
    cout << "4. Query Server for Suspect Information\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

// Function to view all suspects in the database
void viewSuspectDatabase(const InvestigationControl& control) {
    cout << "\n--- Suspect Database ---\n";
    for (const auto& suspect : control.getSuspects()) {
        suspect->describe();
    }
}

// Function to view all detectives in the database
void viewDetectiveDatabase(const InvestigationControl& control) {
    cout << "\n--- Detective Database ---\n";
    for (const auto& detective : control.getDetectives()) {
        detective->describe();
    }
}

// Function to query the server for suspect information
void queryServer(const string& suspectName) {
    try {
        WinsockClient client;
        client.initialize("127.0.0.1", 8080); // Replace with server IP and port
        client.connectToServer();

        string response = client.sendAndReceive(suspectName); // Send query and receive response
        cout << "Server Response: " << response << endl;

        client.cleanup();
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

int main() {
    // Initialize InvestigationControl
    InvestigationControl control;

    // Add detectives
    auto detective1 = make_shared<Detective>("Sherlock Holmes", 40, "Deduction");
    auto detective2 = make_shared<Detective>("Hercule Poirot", 50, "Observation");
    auto detective3 = make_shared<Detective>("Nancy Drew", 30, "Forensics");
    auto detective4 = make_shared<Detective>("Miss Marple", 60, "Interrogation");
    auto detective5 = make_shared<Detective>("Columbo", 45, "Disguise");
    auto detective6 = make_shared<Detective>("L Lawliet", 25, "Logic");
    auto detective7 = make_shared<Detective>("Veronica Mars", 28, "Research");
    auto detective8 = make_shared<Detective>("Philip Marlowe", 55, "Stakeout");
    auto detective9 = make_shared<Detective>("Jessica Fletcher", 65, "Writing");
    auto detective10 = make_shared<Detective>("Ace Ventura", 35, "Animal Clues");

    control.addDetective(detective1);
    control.addDetective(detective2);
    control.addDetective(detective3);
    control.addDetective(detective4);
    control.addDetective(detective5);
    control.addDetective(detective6);
    control.addDetective(detective7);
    control.addDetective(detective8);
    control.addDetective(detective9);
    control.addDetective(detective10);

    // Add suspects
    auto suspect1 = make_shared<Suspect>("John Doe", 30, "At home", "Sherlock Holmes", "Caught with fingerprints on the safe", true);
    auto suspect2 = make_shared<Suspect>("Jane Smith", 25, "With a friend", "Hercule Poirot", "Witness identified her at the scene", false);
    auto suspect3 = make_shared<Suspect>("Robert Brown", 40, "In a meeting", "Nancy Drew", "Surveillance footage showed him entering the building", true);
    auto suspect4 = make_shared<Suspect>("Emily White", 35, "Shopping", "Miss Marple", "Her DNA was found on the weapon", false);
    auto suspect5 = make_shared<Suspect>("Tom Johnson", 50, "At the gym", "Columbo", "He confessed during interrogation", true);
    auto suspect6 = make_shared<Suspect>("Lucy Gray", 27, "On vacation", "Sherlock Holmes", "Caught fleeing the scene with stolen items", false);
    auto suspect7 = make_shared<Suspect>("Paul Green", 33, "Driving", "L Lawliet", "A phone call placed him at the crime scene", true);
    auto suspect8 = make_shared<Suspect>("Olivia Black", 29, "Cooking", "Veronica Mars", "Her car was spotted near the location of the robbery", false);
    auto suspect9 = make_shared<Suspect>("Charlie Blue", 42, "Jogging", "Philip Marlowe", "He left his wallet at the crime scene", true);
    auto suspect10 = make_shared<Suspect>("Sophia Gold", 38, "Reading", "Ace Ventura", "An anonymous tip led to her arrest", false);

    control.addSuspect(suspect1);
    control.addSuspect(suspect2);
    control.addSuspect(suspect3);
    control.addSuspect(suspect4);
    control.addSuspect(suspect5);
    control.addSuspect(suspect6);
    control.addSuspect(suspect7);
    control.addSuspect(suspect8);
    control.addSuspect(suspect9);
    control.addSuspect(suspect10);

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
        case 1: // View Suspect Database
            viewSuspectDatabase(control);
            break;

        case 2: // View Detective Database
            viewDetectiveDatabase(control);
            break;

        case 3: { // Search for a Suspect
            string suspectName;
            cout << "\nEnter the suspect's name to search: ";
            getline(cin, suspectName);

            try {
                auto suspect = control.findSuspect(suspectName);
                control.showCaughtDetails(suspect);
            }
            catch (const SuspectNotFoundException& e) {
                cout << e.what() << endl;
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        }

        case 4: { // Query Server for Suspect Information
            string suspectName;
            cout << "\nEnter the suspect's name to query: ";
            getline(cin, suspectName);
            queryServer(suspectName);
            break;
        }

        case 5: // Exit
            cout << "Exiting the system. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
