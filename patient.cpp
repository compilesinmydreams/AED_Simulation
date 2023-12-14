#include "patient.h"

// Public static variable
int Patient::p_count = 1;

// Constructor
Patient::Patient(bool isAdult, int status, QObject *parent): QObject(parent) {
    // Each patient is generated and numbered 1, 2, 3, ...
    num = p_count;
    p_count++;

    this->isAdult = isAdult;
    this->status = status;
}

// destructor
Patient::~Patient() {}

// Getters
bool Patient::getIsAdult() {
    return isAdult;
}

int Patient::getStatus() {
    return status;
}

// Setters
void Patient::setStatus(int newStatus) {
    status = newStatus;
}
