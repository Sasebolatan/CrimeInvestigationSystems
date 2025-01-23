#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <exception>
using namespace std;

// Exception: No suspects available in the system
class EmptyCaseException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: No suspects available in the system!";
    }
};

// Exception: Suspect not found
class SuspectNotFoundException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Suspect not found!";
    }
};

// Exception: Invalid input provided
class InvalidInputException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Invalid input provided. Please check your entry.";
    }
};

// Exception: Server query error (e.g., connection issues)
class ServerQueryException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Unable to query the server. Please check your connection.";
    }
};

#endif // CUSTOM_EXCEPTIONS_H
